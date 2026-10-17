#!/usr/bin/env python3
"""Re-triage 'hard' functions by how fast they are likely to finish.

Signals: current fuzzy %, unit closeness (finishing links the object),
clone families (opcode-shape identical to another function), existing attempts.
Writes .agent/categorize/hard_triage.csv.
"""
import csv, hashlib, json, re
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CAT = ROOT / ".agent/categorize"
ASM = ROOT / "build/GYQE01/game/asm"
INSN_RE = re.compile(r"\*/\s*([A-Za-z][\w.]*)")

report = json.load(open(ROOT / "build/GYQE01/report.json"))
info, unit_stats, data_ok = {}, {}, {}
for u in report["units"]:
    if not u["name"].startswith("game/"):
        continue
    left = 0
    for f in u.get("functions", []):
        pct = f.get("fuzzy_match_percent", 0)
        info[f["name"]] = (u["name"], int(f["size"]), pct)
        if pct < 100:
            left += int(f["size"])
    unit_stats[u["name"]] = left
    data_ok[u["name"]] = u["measures"].get("matched_data_percent", 0) >= 100

def shape(unit, name):
    """sha1 of the opcode sequence (operands dropped) -> clone detection."""
    p = ASM.joinpath(*unit.split("/")[1:-1]) / (unit.split("/")[-1] + ".s")
    if not p.exists():
        return None
    lines, out, on = p.read_text().splitlines(), [], False
    for l in lines:
        if l.startswith(".fn " + name + ","):
            on = True
        elif on and l.startswith(".endfn"):
            break
        elif on and (m := INSN_RE.search(l)):
            out.append(m.group(1))
    return hashlib.sha1(" ".join(out).encode()).hexdigest()[:12] if out else None

# ponytail: shape hash over all game fns, O(n * file size); fine for ~3k fns
shapes, by_shape = {}, defaultdict(list)
for name, (unit, size, pct) in info.items():
    if size >= 64 and (h := shape(unit, name)):
        shapes[name] = h
        by_shape[h].append(name)

attempts = {p.stem.split(".")[0] for p in (ROOT / ".agent/attempts").glob("fn_*")}
rows = [r for r in csv.DictReader(open(CAT / "functions.csv")) if r["difficulty"] == "hard"]
out = []
for r in rows:
    fn = r["function"]
    unit, size, pct = info.get(fn, ("?", int(r["size_bytes"]), 0))
    sib = [s for s in by_shape.get(shapes.get(fn), []) if s != fn]
    matched_sib = [s for s in sib if info[s][2] >= 100]
    unit_left = unit_stats.get(unit, size)
    blockers = r["blockers"].split(";") if r["blockers"] else []
    real = [b for b in blockers if b not in ("int_to_float", "float_to_int", "sin_cos")]
    if pct >= 100:
        tier = "Z_already_matched"
    elif matched_sib:
        tier = "A_clone_of_matched"
    elif pct >= 90:
        tier = "B_almost_done"
    elif unit_left == size and data_ok.get(unit):
        tier = "C_last_in_unit"
    elif sib:
        tier = "D_clone_family"
    elif not real and size <= 1200:
        tier = "E_mislabeled_float_only"
    elif "jump_table" in blockers or size > 3000:
        tier = "G_truly_hard"
    else:
        tier = "F_normal"
    out.append(dict(function=fn, unit=unit, size=size, fuzzy=round(pct, 1), tier=tier,
                    unit_bytes_left=unit_left, clones=";".join(sib[:5]),
                    matched_clone=";".join(matched_sib[:3]), has_attempt=fn in attempts,
                    category=r["category"], blockers=r["blockers"]))

out.sort(key=lambda d: (d["tier"], -d["fuzzy"], d["size"]))
with open(CAT / "hard_triage.csv", "w", newline="") as f:
    w = csv.DictWriter(f, fieldnames=list(out[0]))
    w.writeheader(); w.writerows(out)

from collections import Counter
c = Counter(d["tier"] for d in out); b = Counter()
for d in out: b[d["tier"]] += d["size"]
for t in sorted(c): print(f"{t:26} {c[t]:5} fns {b[t]:8} bytes")
