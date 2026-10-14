#!/usr/bin/env python3
"""Sweep unmatched game functions, replacing extern float/double rodata constants with
literals; keep per-function changes only where the match percentage improves.
Runs ninja repeatedly (slow). Usage: python3 tools/literalize_rodata.py"""
import json, re, subprocess, glob, sys

ROOT = str(__import__('pathlib').Path(__file__).resolve().parent.parent)
MAGIC = {'4503599627370496', '4503601774854144'}  # int<->float conversion constants


def report():
    r = subprocess.run(['ninja', '-k', '0'], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        errs = re.findall(r'File: (\S+)\n.*?\n#\s+(\d+): (.*?)\n#\s+Error:.*?\n#\s+(.*?)\n', r.stdout, re.S)
        print('BUILD FAILED:', errs[:10] or r.stdout[-1500:])
    d = json.load(open(f'{ROOT}/build/GYQE01/report.json'))
    out = {}
    for u in d['units']:
        if u['name'].startswith('game/'):
            for f in u.get('functions', []):
                out[f['name']] = f.get('fuzzy_match_percent', 0) or 0
    return out


def rodata_values():
    types = {}
    for line in open(f'{ROOT}/config/GYQE01/game/symbols.txt'):
        m = re.match(r'(lbl_3_rodata_\w+) = .*size:0x(\w+).*data:(float|double)', line)
        if m:
            types[m.group(1)] = (int(m.group(2), 16), m.group(3))
    vals = {}
    for path in glob.glob(f'{ROOT}/build/GYQE01/game/asm/game/*.s'):
        lines = open(path).read().splitlines()
        for i, l in enumerate(lines):
            m = re.match(r'\.obj (lbl_3_rodata_\w+),', l)
            if m and m.group(1) in types:
                size, kind = types[m.group(1)]
                v = lines[i + 1].split()
                if len(v) == 2 and v[0] == '.' + kind and size == (4 if kind == 'float' else 8):
                    vals[m.group(1)] = literal(v[1], kind)
    return {k: v for k, v in vals.items() if v}


def literal(v, kind):
    if v in MAGIC or 'nan' in v.lower() or 'inf' in v.lower():
        return None
    if not re.search(r'[.e]', v):
        v += '.0'
    return v + 'f' if kind == 'float' else v


def functions(src):
    """Yield (name, start, end) of top-level function bodies."""
    for m in re.finditer(r'^[^\n;{}#/]*?[ *](fn_3_\w+|\w+)\(([^)]*)\)\s*\{', src, re.M):
        i = m.end(); depth = 1
        while depth and i < len(src):
            depth += {'{': 1, '}': -1}.get(src[i], 0); i += 1
        yield m.group(1), m.start(), i


def literalize(body, vals):
    return re.sub(r'(?<![&\w])(lbl_3_rodata_\w+)\b(?!\s*\[)',
                  lambda m: vals.get(m.group(1), m.group(1)), body)


def main():
    vals = rodata_values()
    base = report()
    files = {}
    for path in sorted(glob.glob(f'{ROOT}/src/game/*.c')):
        src = open(path).read()
        new, changed, pos = [], [], 0
        for name, s, e in functions(src):
            if base.get(name, 100) >= 100:
                continue
            body = src[s:e]
            lit = literalize(body, vals)
            if lit != body:
                new.append(src[pos:s]); new.append(lit); pos = e; changed.append((name, s, e, lit))
        if changed:
            new.append(src[pos:])
            files[path] = (src, changed)
            open(path, 'w').write(''.join(new))
    print(f'{sum(len(c) for _, c in files.values())} functions in {len(files)} files changed')
    after = report()
    keep_total = []
    for path, (orig, changed) in files.items():
        keep = [c for c in changed if after.get(c[0], 0) > base.get(c[0], 0)]
        for c in changed:
            print(f'  {c[0]:<16} {base.get(c[0], 0):6.2f} -> {after.get(c[0], 0):6.2f} {"KEEP" if c in keep else "revert"}')
        out, pos = [], 0
        for name, s, e, lit in keep:
            out.append(orig[pos:s]); out.append(lit); pos = e
        out.append(orig[pos:])
        open(path, 'w').write(''.join(out))
        keep_total += [c[0] for c in keep]
    final = report()
    regress = [n for n in base if final.get(n, 0) < base[n] - 1e-6]
    matched = [n for n in keep_total if final.get(n, 0) >= 100]
    print('NEWLY MATCHED:', ' '.join(matched))
    print('IMPROVED (not matched):', ' '.join(n for n in keep_total if n not in matched))
    print('REGRESSIONS:', ' '.join(regress) or 'none')


if __name__ == '__main__':
    main()
