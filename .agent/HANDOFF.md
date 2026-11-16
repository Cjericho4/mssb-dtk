# Handoff: where the decomp stands and how to pick it up (written 2026-11-16)

Read this after `INDEX.md`. It is the short path to being productive; the long reference is
`decomp_knowledge.md` (§15 holds the lessons of the session this file was written after).

## State

* 4,228 of 6,478 functions match (28.3% of code): DOL 39%, challenge 38%, game 25%, menus 18%.
  Fresh numbers: `ninja` prints them; `python3 tools/find_matches.py build/GYQE01/report.json | wc -l`.
* Custom characters do not wait on matching (`modding_roadmap.md`). The three goals:
  1. custom model / animation on an existing slot: importers and the Dolphin harness are on
     branch `model-importer` of mssb-modding (worktree `../mssb-modding-model`), harness
     installed and locked, all seven suites PASS (2026-11-15); not merged, no Rio test yet;
  2. skin picker (no lost slots): designed, prototype on branch `phase3-proto`;
  3. more than 54 characters: inventory and plan in `roster_expansion.md`; next step there is a
     relocation patcher for one self-addressed table (game.rel `.data+0x7F10` is the simplest)
     and a poison run through the harness.
* Game-module functions under 220 bytes have all been attempted. The untried small functions
  are in the DOL game units (`src/Unknown/gap_*.c`): `tools/untried.sh dol 300 | grep gap_`.
  Skip SDK look-alikes there unless you know the SDK source: `gap_800DFDD4` is the THP video
  decoder, `gap_800A1A70` is the GD display-list library (old-style prologue, `mflr` first).

## The fast loop (about 2 minutes per small function)

```bash
export PATH=$PWD/.venv/bin:$PATH          # ninja lives in .venv
tools/fn_asm.sh fn_XXXXXXXX               # target asm + every mention in src/ and include/
tools/put_stub.py src/Unknown/gap_X.c fn_XXXXXXXX include/Unknown/gap_X.h "new prototype;" <<'EOF'
// One-line summary.
<function>
EOF
ninja 2>&1 | grep -E "^#|Error" | head    # only compiler errors
python3 tools/feedback_diff.py fn_XXXXXXXX | head -12
python3 tools/sbs.py fn_XXXXXXXX | grep '^\*'   # only the differing lines, side by side
```

Commit each match (`matched fn_X`, no trailers) after checking the match count did not drop.
Record a near-match with a `/* Non-matching: ... */` note in the function, a `NONMATCHING`
line in `queue.log` and a row in `working_progress.md`; stop after about three register-only
attempts.

## What to check before writing a function

1. **Is it already matched?** Many functions referenced by docs as "unknown" have matched C:
   `python3 tools/feedback_diff.py <fn> | tail -1`, then read the source instead of the asm.
2. **Does the unit already have the types?** `grep -n "<symbol>" include/Unknown/gap_X.h`.
   Each DOL unit keeps its own views of shared structs (`Gap<unit>...`); a sibling function a
   few lines away usually shows the idiom to copy. `UnknownHeaders.h` cannot be included by
   most DOL units (their own PSMTX / struct views clash), so add a small local view with a
   comment naming the owning struct.
3. **Is a neighbour function the same code?** Look at the functions next to it in address
   order; a matched sibling often differs by one constant.

## Traps that cost time this session

* Do not `sed`/replace a common token across a whole file (`ring->`, `task->`): it rewrote an
  unrelated function and a commit went in broken. Scope edits to the function, or rebuild
  before committing.
* `put_stub.py` needs the stub in the exact `... fn(void) {\n    return;\n}` form; when it
  asserts, the stub has a different signature or a previous attempt: read it.
* A prototype placed in a header before the typedefs it uses gives `')' expected`; move it
  below them.
* An `extern` struct of 8 bytes or less is addressed as small data (`@sda21`). If the target
  uses `lis/addi`, pad the view past 8 bytes; if the target uses `@sda21`, the view must be a
  complete type of 8 bytes or less.
* `ninja report` is not a target; plain `ninja` rewrites `report.json`.
* Dolphin harness runs take 5 to 20 minutes each; start them in the background and keep
  working.
