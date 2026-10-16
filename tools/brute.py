#!/usr/bin/env python3
# usage: brute.py src fn template.c  -- template has lines between "//PERM_BEGIN" and "//PERM_END" to permute
import itertools, subprocess, sys, re
src, fn, tpl = sys.argv[1:4]
limit = int(sys.argv[4]) if len(sys.argv) > 4 else 100000
t = open(tpl).read()
pre, rest = t.split('//PERM_BEGIN\n')
mid, post = rest.split('//PERM_END\n')
lines = [l for l in mid.split('\n') if l.strip()]
best = None
seen = 0
for perm in itertools.permutations(lines):
    # dependency check: a line defining var v must precede lines using it
    ok = True
    defined = {}
    for idx, l in enumerate(perm):
        m = re.match(r'\s*(\w+) =', l)
        if m: defined[m.group(1)] = idx
    for idx, l in enumerate(perm):
        rhs = l.split('=', 1)[1] if '=' in l else l
        for v, d in defined.items():
            if re.search(r'\b%s\b' % v, rhs) and d > idx:
                ok = False
    if not ok: continue
    seen += 1
    if seen > limit: break
    open('.scratch/_cand.c', 'w').write(pre + '\n'.join(perm) + '\n' + post)
    out = subprocess.run(['python3', 'tools/try_function.py', src, fn, '.scratch/_cand.c'], capture_output=True, text=True).stdout
    if 'MATCH!' in out:
        print('MATCH', perm); sys.exit(0)
    score = out.count('Mismatch') + out.count('Missing') + out.count('Extra')
    if best is None or score < best[0]:
        best = (score, perm); print(score, perm, flush=True)
print('best', best)
