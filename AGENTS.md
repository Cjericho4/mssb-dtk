# Agent workflow for mssb-dtk

These instructions apply to Codex and other sessions that honor `AGENTS.md`.
They supplement the project documentation; for conflicts, these safety and
budget rules take precedence over older agent workflows in this checkout.

## Environment and data boundaries

- Work from this checkout on the Plex host. Use the project virtual environment:
  `source .venv/bin/activate`.
- Recreate its Python tools with `python -m pip install -r requirements-dev.txt`.
- Run `tools/setup_dev_tools.sh` once to fetch m2c (`tools/m2c_repo`) and an
  objdiff-cli with JSON diff output (`.venv/bin/objdiff`, used by
  `tools/feedback_diff.py`).
- The build requires a user-provided USA Rev 0 game dump at
  `orig/GYQE01/sys/main.dol` and `orig/GYQE01/files/aaaa.dat`. If it is absent,
  stop before configuring/building and tell the user what is missing. Never
  download, commit, upload, or include original game files/assets in prompts.
- Codex CLI runs repository commands locally, but model inference is remote.
  Keep prompts to source, relevant assembly/context, and diff output; never use
  Codex Cloud or another hosted workspace for this repository unless asked.
- Do not invoke `tools/langgraph_decomp` or `tools/aidecomp` by default. They are
  optional stacks; the LangGraph runner can call non-Codex cloud providers and
  can create branches and commit automatically.

## Session start and task selection

1. Check `git status --short --branch`; do not overwrite or discard existing
   user changes.
2. Read `working_progress.md` and `queue.log`. `queue.log` is the function queue
   source of truth; reconcile stale progress notes before selecting work.
3. Work on one function per task. Prefer small, unmatched candidates identified
   by `tools/score_functions.py`; skip entries already marked completed or
   nonmatching unless the user specifically asks to revisit them.
4. Read `CLAUDE.md` (tools, struct rules, compiler patterns) and
   `.agent/decomp_knowledge.md` before decompiling.
   Iterate on a candidate with `python tools/try_function.py <src> <fn> <candidate.c>`
   and look up constants with `python tools/rodata_value.py`.
5. Use the repo helpers (`decomp.sh`, `tools/kappa_context.py`,
   `tools/m2c_helper.py`) to collect only the target function's context.

## Implementation and verification

- Preserve matching-decomp style: use typed structs and named fields, not
  manual pointer-offset arithmetic or speculative `void *` interfaces.
- Run the configured build with `ninja`, then
  `python tools/feedback_diff.py <function_name>`.
- A function is complete only when the build succeeds and the diff reports
  `MATCH!`; compiling alone is not a match.
- Limit a session to five AI refinement attempts for a function. If it still
  does not match, stop, summarize the remaining instruction differences, and
  leave it for a later explicit continuation rather than looping or escalating
  to another provider. Existing project notes may describe a larger limit.
- Do not edit generated build output to force a match. Keep changes scoped to
  the relevant source/header files.

## Git and tracking

- Do not commit, push, publish, or update `queue.log`/`working_progress.md`
  automatically. Report the diff and verification result for review first.
- Never run broad cleanup/reset commands. Preserve unrelated worktree changes.
- For routine planning, produce a short read-only shortlist from the queue and
  score report; do not schedule unattended source edits or commits.
