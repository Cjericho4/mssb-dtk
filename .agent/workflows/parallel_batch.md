---
description: Run a 100-function batch with 4 parallel worker agents in git worktrees, then merge
---

Proven on 2026-10-14/15: easy tier (79/93), medium batches 1 and 2 (93/100, 92/100).

## 1. Queue
Pick the next unqueued functions from `.agent/categorize/functions.csv`, smallest first:
```bash
grep -oE 'fn_3_[0-9A-F]+' queue.log | sort -u > /tmp/q.txt
awk -F, '$4=="medium"{print $2, $1}' .agent/categorize/functions.csv | sort -n \
  | awk '{print $2}' | grep -vxFf /tmp/q.txt | head -100 > /tmp/batch.txt
cat /tmp/batch.txt >> queue.log && git commit -qam "queue Codex medium tier, next 100"
```
Split into 4 lists **grouped by source unit** (report.json `units[].functions[]`), so two
workers never edit the same `.c` file.

## 2. Worktrees
Each worker needs its own build dir; never share `build/GYQE01`. Untracked inputs are symlinked:
```bash
W=/home/plex/repos/mssb-dtk-w1   # w1..w4
git worktree add $W main -b queue-w1        # or: git -C $W checkout -B queue-w1 main
mkdir -p $W/build $W/orig/GYQE01
ln -s $PWD/build/compilers $W/build/compilers; ln -s $PWD/build/tools $W/build/tools
ln -s $PWD/orig/GYQE01/files $W/orig/GYQE01/files; ln -s $PWD/orig/GYQE01/sys $W/orig/GYQE01/sys
ln -s $PWD/.venv $W/.venv
(cd $W && source .venv/bin/activate && python3 configure.py && ninja)
```
The first build sometimes fails when several run at once; rerun `ninja` serially. Verify with
`python3 tools/feedback_diff.py fn_3_9C794` → `MATCH!`.

## 3. Worker prompt (one general-purpose agent per worktree, background)
Include: worktree path + branch; `source .venv/bin/activate`; read CLAUDE.md and
`.agent/decomp_knowledge.md` (incl. Known Unfixable Patterns); scratch files only in
`<worktree>/.scratch/`; the function list; ~6 attempts per function; on MATCH commit
`matched <fn>` (no Co-Authored-By), each commit must build, compare
`tools/find_matches.py` counts to prove nothing regressed; on no match restore and save the
best attempt in `.scratch/`; don't touch queue.log/working_progress.md; report one line per
function plus shared-header changes and new tips.

**Merge hygiene to put in the prompt** (the recurring merge breakages):
- grep for an existing declaration before adding any global/typedef/prototype; never add a
  file-local copy of a shared struct. Known shared ones: `Lbl8037169C`/`lbl_8037169C`,
  `Lbl3Data21278`/`lbl_3_data_21278`, `Set_803cb848` (UnknownHeaders.h);
  `UnkSimulation31AC0`/`g_UnkSimulation_31AC0` (UnknownHomes_Game.h).
- don't move typedefs/externs between headers; add struct fields by carving padding in place.
- `rep_1E08.h`'s `lbl_80366158` conflicts with `game_batter.h`/`rep_37A8.c`; declare needed
  prototypes locally instead of including both.

## 4. Merge (in the main checkout, as each worker finishes)
```bash
git cherry-pick $(git merge-base main queue-wN)..queue-wN
```
- Resolve conflicts **hunk by hunk** (keep both sides' fields). Never `git checkout --theirs`
  a whole `.c` file: it silently reverted three matched functions once.
- Re-resolving with `git checkout -m <file>` writes `<<<<<<< ours`/`>>>>>>> theirs` markers (not `HEAD`); always
  `git grep -c '^<<<<<<<' -- src include` before `cherry-pick --continue`. `checkout --ours` drops the commit's other hunks too.
- After the last commit: `ninja`, then
  `python3 tools/find_matches.py build/GYQE01/report.json | grep -c fn_3_` must rise by exactly
  the worker's match count. A clean cherry-pick can still fail to build (duplicate typedefs from
  two workers) — fix and commit separately.
- Mark results in queue.log (`COMPLETED`/`NONMATCHING`), add new tips to
  `.agent/decomp_knowledge.md`, add non-matches with reasons to working_progress.md and copy
  best attempts into `.agent/attempts/`.

## Codex
`codex exec` cannot verify matches: its workspace-write sandbox blocks wibo (ninja exits 159).
Use it only for draft candidates, run with `</dev/null` (it otherwise waits on stdin forever),
then have a worker finish them with `tools/try_function.py`.
