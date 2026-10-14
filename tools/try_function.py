#!/usr/bin/env python3
"""Try a candidate implementation of one function and diff it against the target.

Replaces the definition of FUNCTION in SOURCE with the contents of CODE_FILE,
rebuilds via tools/feedback_diff.py, and prints the diff. The source file is
restored unless the result is an exact match (or --keep is given).

Usage:
    python3 tools/try_function.py src/game/rep_3090.c fn_3_104B20 candidate.c [--keep]
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def find_function(src, name):
    m = re.search(r"^[^\n;{}]*[ *]" + re.escape(name) + r"\([^)]*\)\s*\{", src, re.M)
    if not m:
        return None
    i, depth = m.end(), 1
    while depth and i < len(src):
        depth += {"{": 1, "}": -1}.get(src[i], 0)
        i += 1
    return m.start(), i


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("source")
    ap.add_argument("function")
    ap.add_argument("code_file")
    ap.add_argument("--keep", action="store_true", help="keep the candidate even if it does not match")
    args = ap.parse_args()

    path = ROOT / args.source if not Path(args.source).is_absolute() else Path(args.source)
    original = path.read_text()
    span = find_function(original, args.function)
    if span is None:
        sys.exit(f"{args.function} not found in {args.source}")
    candidate = Path(args.code_file).read_text().strip("\n")
    path.write_text(original[: span[0]] + candidate + original[span[1]:])

    out = subprocess.run(
        [sys.executable, "tools/feedback_diff.py", args.function], cwd=ROOT, capture_output=True, text=True
    ).stdout
    lines = [l for l in out.splitlines() if not l.startswith(("Building", "Build succ"))]
    matched = "MATCH!" in out
    if "Feedback" not in out:
        print("Build failed (run ninja to see the compiler error)")
    else:
        print("\n".join(lines[:40]))
        mismatches = sum(1 for l in lines if l.startswith("Line "))
        print(f"\n{'MATCH' if matched else f'{mismatches} mismatching lines shown'}")
    if not matched and not args.keep:
        path.write_text(original)
        print("(source restored)")


if __name__ == "__main__":
    main()
