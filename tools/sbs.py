"""Side-by-side target vs current asm for one function (uses the last build).

Usage: python3 tools/sbs.py <function> [unit]
Lines starting with '*' differ. Easier than feedback_diff.py for spotting
register-assignment swaps.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(__file__))
import feedback_diff as fd


def fmt(i):
    ins = (i or {}).get('instruction') or {}
    return (ins.get('formatted') or '')[:45]


def main():
    fn = sys.argv[1]
    unit = sys.argv[2] if len(sys.argv) > 2 else fd.find_unit_for_symbol(fn)
    left, right = fd.get_symbol_data(fd.run_objdiff(unit, fn), fn)
    L, R = left.get('instructions', []), right.get('instructions', [])
    for i in range(max(len(L), len(R))):
        a = fmt(L[i]) if i < len(L) else ''
        b = fmt(R[i]) if i < len(R) else ''
        kind = R[i].get('diff_kind', '') if i < len(R) else ''
        print(f"{'  ' if kind in ('None', '') else '* '}{a:45} | {b}")


if __name__ == '__main__':
    main()
