#!/usr/bin/env python3
"""Read assembly context and create the requested function categorization."""
import csv
import re
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INPUT = ROOT / "build/categorize/input.tsv"
ASM = ROOT / "build/GYQE01/game/asm"
OUT = ROOT / "build/categorize/functions.csv"
SUMMARY = ROOT / "build/categorize/summary.md"

INSN_RE = re.compile(r"\*/\s*([A-Za-z][\w.]*)\s*(.*)$")
PC_RE = re.compile(r"/\*\s*([0-9A-Fa-f]{8})")
LOCAL_RE = re.compile(r"\.L_([0-9A-Fa-f]+)")
FIELD_RE = re.compile(r"(?:g_[A-Za-z0-9_]+|lbl_3_common_bss_[A-Za-z0-9_]+)(?:@(?:ha|l))?")
OFFSET_RE = re.compile(r"(-?0x[0-9A-Fa-f]+|-?\d+)\(r(\d+)\)")

FLOAT_ARITH = re.compile(r"^(?:f(?:add|sub|mul|div|madd|msub|nmadd|nmsub|sqrt|res|sel|cmp|neg|abs|rsqrt)|ps_(?:add|sub|mul|madd|msub|nmadd|nmsub|div|res|rsqrt|sum|merge|mrgh|mrgl|sel|neg|abs))")
INDEXED_MEM = {"lbzx", "lhzx", "lhax", "lwzx", "stbx", "sthx", "stwx", "lfsx", "stfsx", "lfdx", "stfdx"}


def assembly_path(unit):
    parts = unit.split("/")[1:]
    directory = ASM.joinpath(*parts[:-1]) if len(parts) > 1 else ASM
    return directory / (parts[-1] + ".s")


def get_body(lines, name):
    start = next(i for i, line in enumerate(lines) if line.startswith(".fn " + name))
    body = []
    for line in lines[start + 1:]:
        if line.startswith(".endfn"):
            return body
        body.append(line)
    raise ValueError("unterminated function " + name)


def extract(lines):
    insns = []
    for line in lines:
        match = INSN_RE.search(line)
        if match:
            pc_match = PC_RE.search(line)
            insns.append((match.group(1).lower(), match.group(2), int(pc_match.group(1), 16) if pc_match else None, line))
    ops = [op for op, _, _, _ in insns]
    calls = [o for o in insns if o[0] in ("bl", "bctrl")]
    direct_targets = []
    for op, operands, _, _ in calls:
        if op == "bl":
            target = re.match(r"([^,\s]+)", operands)
            if target:
                direct_targets.append(target.group(1))
    float_ops = [o for o in ops if FLOAT_ARITH.match(o)]
    fmem = sum(o in {"lfs", "lfd", "stfs", "stfd", "lfsu", "lfdu", "stfsu", "stfdu"} or o.startswith("psq_") for o in ops)
    branches = []
    backedges = 0
    for op, operands, pc, _ in insns:
        if op.startswith("b") and op not in ("bl", "bctrl", "blr", "bctr", "bcctr", "bclrl"):
            branches.append((op, operands))
            target = LOCAL_RE.search(operands)
            if target and pc is not None and int(target.group(1), 16) <= pc:
                backedges += 1
    jump_table = "bctr" in ops or "bcctr" in ops
    indirect_calls = ops.count("bctrl")
    saved = set()
    for op, operands, _, _ in insns:
        if op == "stmw":
            match = re.match(r"r(\d+)", operands)
            if match:
                saved.update(range(int(match.group(1)), 32))
        elif op in ("stw", "std"):
            match = re.match(r"r(\d+),\s*(?:0x[0-9A-Fa-f]+|[-+]?\d+)\(r1\)", operands)
            if match and int(match.group(1)) >= 14:
                saved.add(int(match.group(1)))
    symbols = Counter()
    for _, _, _, line in insns:
        for sym in re.findall(r"\b(?:lbl_[A-Za-z0-9_]+|g_[A-Za-z0-9_]+)@(?:ha|l|sda21)", line):
            symbols[sym.split("@")[0]] += 1
    table_syms = {s: n for s, n in symbols.items() if "data" in s.lower() or "table" in s.lower()}
    indexed = sum(op in INDEXED_MEM for op in ops)
    mulli = ops.count("mulli")
    # Collect effective offsets only where a global address relocation occurs nearby.
    # Track relocated global bases through simple address copies so that an
    # unresolved offset is attached to the actual global, not an unrelated one.
    reg_bases = {}
    global_fields = defaultdict(set)
    for op, operands, _, _ in insns:
        args = [x.strip() for x in operands.split(",")]
        dest = args[0] if args and re.fullmatch(r"r\d+", args[0]) else None
        reloc = re.search(r"\b(g_[A-Za-z0-9_]+|lbl_3_common_bss_[A-Za-z0-9_]+)@(?:ha|l)\b", operands)
        if op in {"lbz", "lhz", "lha", "lwz", "lfs", "lfd", "stb", "sth", "stw", "stfs", "stfd", "lbzx", "lhzx", "lwzx", "stbx", "sthx", "stwx", "lfsx", "stfsx", "lmw", "stmw"}:
            for mem in OFFSET_RE.finditer(operands):
                value_text, base_reg = mem.groups()
                base_reg = "r" + base_reg
                if base_reg in reg_bases:
                    value = int(value_text, 0) if "0x" in value_text.lower() else int(value_text, 10)
                    if value > 0:
                        global_fields[reg_bases[base_reg]].add(value)
        if op in ("bl", "bctrl"):
            reg_bases = {r: sym for r, sym in reg_bases.items() if int(r[1:]) >= 14}
            continue
        if op in ("lis", "addis") and dest:
            if reloc:
                reg_bases[dest] = reloc.group(1)
            else:
                reg_bases.pop(dest, None)
        elif op == "addi" and len(args) >= 3 and dest:
            if reloc:
                reg_bases[dest] = reloc.group(1)
            elif args[1] in reg_bases:
                reg_bases[dest] = reg_bases[args[1]]
            else:
                reg_bases.pop(dest, None)
        elif op == "mr" and len(args) >= 2 and dest:
            if args[1] in reg_bases:
                reg_bases[dest] = reg_bases[args[1]]
            else:
                reg_bases.pop(dest, None)
        elif op == "add" and len(args) >= 3 and dest:
            sources = [reg_bases.get(x) for x in args[1:3]]
            mapped = [x for x in sources if x]
            if mapped and len(set(mapped)) == 1:
                reg_bases[dest] = mapped[0]
            else:
                reg_bases.pop(dest, None)
        elif dest and not (op.startswith("st") or op in ("cmpw", "cmpwi", "cmplw", "cmplwi", "mtctr", "mtlr")):
            reg_bases.pop(dest, None)
        if op == "lmw" and args:
            first = re.match(r"r(\d+)", args[0])
            if first:
                for number in range(int(first.group(1)), 32):
                    reg_bases.pop("r" + str(number), None)
    offsets = set().union(*global_fields.values()) if global_fields else set()
    loads = sum(o in ("lbz", "lhz", "lha", "lwz", "lfs", "lfd") or o.endswith("x") and o.startswith(("lbz", "lhz", "lwz")) for o in ops)
    stores = sum(o in ("stb", "sth", "stw", "stfs", "stfd") or o.endswith("x") and o.startswith(("stb", "sth", "stw")) for o in ops)
    return {
        "insns": insns, "ops": ops, "count": len(ops), "calls": calls,
        "call_count": len(calls), "direct_targets": direct_targets,
        "float_ops": len(float_ops), "float_ratio": len(float_ops) / max(1, len(ops)),
        "float_mem": fmem, "branches": branches, "branch_count": len(branches),
        "backedges": backedges, "jump_table": jump_table,
        "indirect_calls": indirect_calls, "saved": len(saved), "symbols": symbols,
        "table_syms": table_syms, "indexed": indexed, "mulli": mulli,
        "offsets": offsets, "loads": loads, "stores": stores,
        "global_symbols": {s: n for s, n in symbols.items() if s.startswith("g_") or "common_bss" in s},
        "global_fields": dict(global_fields),
    }


def source_function_body(source_path, function, cache):
    if source_path not in cache:
        cache[source_path] = source_path.read_text() if source_path.exists() else ""
    source = cache[source_path]
    definition = re.search(r"\b" + re.escape(function) + r"\s*\([^;{}]*\)\s*\{", source)
    if not definition:
        return "", True
    body_start = definition.end()
    # Project function closing braces are on their own unindented line.
    closing = re.search(r"\n\}", source[body_start:])
    body = source[body_start:body_start + closing.start()] if closing else source[body_start:]
    clean = re.sub(r"/\*.*?\*/|//[^\n]*", "", body, flags=re.S)
    stub = not clean.strip() or re.fullmatch(r"\s*return(?:\s+[^;]+)?;?\s*", clean) is not None
    return body, stub


def classify(row, m, source_stub):
    n = m["count"]
    float_heavy = m["float_ops"] >= 8 and (m["float_ratio"] >= 0.12 or (m["float_ops"] >= 30 and m["float_ratio"] >= 0.08))
    state_machine = (
        m["call_count"] >= 3 and m["branch_count"] >= 8 and "lbz" in m["ops"]
    )
    data_driven = m["jump_table"] or (
        len(m["table_syms"]) >= 3 and (m["indexed"] >= 2 or m["mulli"] >= 2)
    )
    loop_table = m["backedges"] > 0 and (
        m["indexed"] > 0 or m["mulli"] > 0 or len(m["table_syms"]) >= 2
    )
    call_sequence = m["call_count"] >= 3 and m["backedges"] == 0 and m["branch_count"] <= 12
    leaf = n <= 48 and m["call_count"] <= 2 and m["backedges"] == 0 and m["branch_count"] <= 5 and not m["jump_table"] and not float_heavy

    if float_heavy:
        category = "float_math"
    elif state_machine:
        category = "state_machine"
    elif m["jump_table"]:
        category = "data_driven"
    elif loop_table:
        category = "loop_table"
    elif call_sequence:
        category = "call_sequence"
    elif data_driven:
        category = "data_driven"
    elif leaf:
        category = "leaf_setter"
    else:
        category = "other"

    blockers = []
    if m["jump_table"]:
        blockers.append("jump_table")
    if m["indirect_calls"]:
        blockers.append("unknown_callee_sig:indirect")
    if "xoris" in m["ops"] and "lfd" in m["ops"] and m["float_ops"]:
        blockers.append("int_to_float")
    if any(x in m["ops"] for x in ("fctiwz", "fctiw", "fctid", "fctidz")):
        blockers.append("float_to_int")
    if any("sin" in t.lower() or "cos" in t.lower() for t in m["direct_targets"]):
        blockers.append("sin_cos")
    unresolved = {s: offsets for s, offsets in m["global_fields"].items() if len(offsets) >= 6}
    struct_unclear = bool(unresolved and source_stub)
    if struct_unclear:
        symbol = sorted(unresolved, key=lambda s: (-len(unresolved[s]), s))[0]
        offset = max(unresolved[symbol])
        blockers.append(f"needs_struct:{symbol}+0x{offset:X}")

    if n > 150 or float_heavy or m["saved"] >= 8 or struct_unclear:
        difficulty = "hard"
    elif n <= 48 and m["call_count"] <= 2 and m["backedges"] == 0 and not m["jump_table"]:
        difficulty = "easy"
    else:
        difficulty = "medium"

    note_parts = [f"{n} insns"]
    if category == "float_math":
        note_parts.append(f"{m['float_ops']} FP arithmetic ops")
    elif category == "loop_table":
        note_parts.append(f"{m['backedges']} loop backedge" + ("s" if m["backedges"] != 1 else ""))
    elif category == "data_driven":
        note_parts.append("jump table" if m["jump_table"] else f"{len(m['table_syms'])} data symbols")
    elif category in ("state_machine", "call_sequence"):
        note_parts.append(f"{m['call_count']} call" + ("s" if m["call_count"] != 1 else ""))
    elif m["call_count"]:
        note_parts.append(f"{m['call_count']} call" + ("s" if m["call_count"] != 1 else ""))
    if m["saved"] >= 8:
        note_parts.append(f"{m['saved']} saved regs")
    if struct_unclear:
        note_parts.append("global fields unresolved")
    return category, difficulty, ";".join(blockers), ", ".join(note_parts[:3])


def main():
    with INPUT.open(newline="") as f:
        rows = list(csv.DictReader(f, delimiter="\t"))
    records = []
    caches = {}
    source_cache = {}
    for row in rows:
        asm_path = assembly_path(row["unit"])
        if asm_path not in caches:
            caches[asm_path] = asm_path.read_text().splitlines()
        asm_lines = caches[asm_path]
        metrics = extract(get_body(asm_lines, row["function"]))
        filepart = row["unit"].split("/")[-1]
        file_directive = next((line for line in asm_lines if line.startswith(".file ")), "")
        file_match = re.search(r'\.file\s+"([^"]+)"', file_directive)
        source_file = file_match.group(1) if file_match else filepart + ".c"
        _, source_stub = source_function_body(ROOT / "src/game" / source_file, row["function"], source_cache)
        category, difficulty, blockers, notes = classify(row, metrics, source_stub)
        records.append({
            "function": row["function"], "size_bytes": int(row["size_bytes"]),
            "category": category, "difficulty": difficulty,
            "blockers": blockers, "notes": notes,
            "source_file": source_file, "metrics": metrics,
        })

    with OUT.open("w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=["function", "size_bytes", "category", "difficulty", "blockers", "notes"])
        writer.writeheader()
        for record in records:
            writer.writerow({k: record[k] for k in writer.fieldnames})

    counts = Counter((r["category"], r["difficulty"]) for r in records)
    grouped = defaultdict(list)
    promising = [r for r in records if r["difficulty"] in ("easy", "medium")]
    promising.sort(key=lambda r: (r["size_bytes"] / (1 if r["difficulty"] == "easy" else 2), r["size_bytes"]), reverse=True)
    ranked = promising[:50]
    for rank, record in enumerate(ranked, 1):
        grouped[record["source_file"]].append(record)
    with SUMMARY.open("w") as f:
        f.write("# Function categorization summary\n\n")
        f.write(f"Processed **{len(records)}** functions from `input.tsv`.\n\n")
        f.write("## Counts by category and difficulty\n\n")
        f.write("| Category | Easy | Medium | Hard | Total |\n|---|---:|---:|---:|---:|\n")
        categories = ["leaf_setter", "state_machine", "loop_table", "float_math", "call_sequence", "data_driven", "other"]
        for category in categories:
            values = [counts[(category, d)] for d in ("easy", "medium", "hard")]
            f.write(f"| {category} | {values[0]} | {values[1]} | {values[2]} | {sum(values)} |\n")
        f.write(f"| **Total** | {sum(counts[(c, 'easy')] for c in categories)} | {sum(counts[(c, 'medium')] for c in categories)} | {sum(counts[(c, 'hard')] for c in categories)} | {len(records)} |\n\n")
        f.write("## 50 promising easy/medium functions\n\n")
        f.write("Ranked by `size_bytes / difficulty_weight` (easy = 1, medium = 2), grouped by source file.\n\n")
        for source_file in sorted(grouped):
            f.write(f"### `src/game/{source_file}`\n\n")
            f.write("| Rank | Function | Size | Category | Difficulty | Value | Notes |\n|---:|---|---:|---|---|---:|---|\n")
            for r in grouped[source_file]:
                weight = 1 if r["difficulty"] == "easy" else 2
                value = r["size_bytes"] / weight
                rank = ranked.index(r) + 1
                f.write(f"| {rank} | `{r['function']}` | {r['size_bytes']} | {r['category']} | {r['difficulty']} | {value:.0f} | {r['notes']} |\n")
            f.write("\n")

    # Concise diagnostic output helps review the heuristics without persisting extra data.
    print(f"wrote {len(records)} functions")
    print("category/difficulty:", dict(sorted(counts.items())))
    for category in ("float_math", "state_machine", "loop_table", "call_sequence", "data_driven", "leaf_setter", "other"):
        samples = [r for r in records if r["category"] == category][:3]
        print(category, [(r["function"], r["size_bytes"], r["notes"]) for r in samples])


if __name__ == "__main__":
    main()
