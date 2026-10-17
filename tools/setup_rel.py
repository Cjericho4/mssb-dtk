#!/usr/bin/env python3
"""One-off: add gap_ text splits for a REL module, regenerate its configure.py
object list from splits.txt, and write stub src/include files.
Usage: setup_rel.py <module>   (run from repo root)"""
import re, sys
from pathlib import Path

mod = sys.argv[1]
cfg = Path(f"config/GYQE01/{mod}")
splits_p, syms_p = cfg / "splits.txt", cfg / "symbols.txt"

# --- functions ---
funcs = []
for l in syms_p.read_text().splitlines():
    m = re.match(r"(\S+) = \.text:0x([0-9A-Fa-f]+); // type:function size:0x([0-9A-Fa-f]+)", l)
    if m:
        funcs.append((int(m[2], 16), int(m[3], 16), m[1]))
funcs.sort()
text_end = max(a + s for a, s, _ in funcs)

# --- parse splits: header + ordered units ---
text = splits_p.read_text()
header, body = text.split("\n\n", 1)
units = []  # [name, [section lines]]
for block in body.strip().split("\n\n"):
    lines = block.splitlines()
    units.append([lines[0].rstrip(":"), lines[1:]])

def text_range(secs):
    for s in secs:
        m = re.match(r"\s*\.text\s+start:0x([0-9A-F]+) end:0x([0-9A-F]+)", s)
        if m:
            return int(m[1], 16), int(m[2], 16)

covered = sorted(r for _, s in units if (r := text_range(s)))
gaps, pos = [], 0
for a, b in covered + [(text_end, text_end)]:
    if a > pos:
        gaps.append((pos, a))
    pos = max(pos, b)

for a, b in gaps:
    g = [f"{mod}/gap_{a:X}.c", [f"\t.text       start:0x{a:08X} end:0x{b:08X}"]]
    idx = next((i for i, (_, s) in enumerate(units) if (r := text_range(s)) and r[0] > a), len(units))
    units.insert(idx, g)

splits_p.write_text(header + "\n\n" + "\n\n".join(n + ":\n" + "\n".join(s) for n, s in units) + "\n")

# --- configure.py object list ---
conf = Path("configure.py")
c = conf.read_text()
pat = re.compile(r'(Rel\(\s*"%s",\s*\[\n)(.*?)(\n\s*\]\s*\))' % mod, re.S)
objs = "\n".join(f'            Object(NonMatching, "{n}"),' for n, _ in units)
c, n = pat.subn(lambda m: m[1] + objs + m[3], c)
assert n == 1, "Rel block not found"
conf.write_text(c)

# --- stubs ---
for name, secs in units:
    r = text_range(secs)
    if not r:
        continue
    stem = Path(name).stem
    fs = [(a, s, f) for a, s, f in funcs if r[0] <= a < r[1]]
    src, inc = Path("src") / name, Path("include") / mod / f"{stem}.h"
    if src.exists():
        continue
    src.parent.mkdir(parents=True, exist_ok=True)
    inc.parent.mkdir(parents=True, exist_ok=True)
    guard = f"__{mod.upper()}_{stem}_H_"
    inc.write_text(f"#ifndef {guard}\n#define {guard}\n\n#include \"mssbTypes.h\"\n\n"
                   + "".join(f"void {f}(void);\n" for _, _, f in fs) + f"\n#endif // !{guard}\n")
    src.write_text(f'#include "{mod}/{stem}.h"\n'
                   + "".join(f"\n// .text:0x{a:08X} size:0x{s:X}\nvoid {f}(void) {{\n    return;\n}}\n" for a, s, f in fs))

print(f"{len(gaps)} gaps added, {len(units)} units, {len(funcs)} functions")
