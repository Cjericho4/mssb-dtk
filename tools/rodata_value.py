#!/usr/bin/env python3
"""Print the value of rodata/data labels from the generated game assembly.

Use this to replace `extern f32 lbl_3_rodata_XXXX` references with the literal
value (see .agent/decomp_knowledge.md, "Float Constants: Use Literals").

Usage:
    python3 tools/rodata_value.py lbl_3_rodata_2B28 lbl_3_rodata_3100
"""
import glob
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    files = glob.glob(str(ROOT / "build/GYQE01/game/asm/**/*.s"), recursive=True)
    wanted = set(sys.argv[1:])
    found = {}
    for path in files:
        lines = Path(path).read_text().splitlines()
        for i, line in enumerate(lines):
            if line.startswith(".obj "):
                name = line.split()[1].rstrip(",")
                if name in wanted:
                    values = []
                    for v in lines[i + 1:]:
                        if v.startswith(".endobj"):
                            break
                        values.append(v.strip())
                    found[name] = " | ".join(values)
    for name in sys.argv[1:]:
        print(f"{name} = {found.get(name, '(not found; run ninja first)')}")


if __name__ == "__main__":
    main()
