# Handoff (2026-10-16)

State: main at HEAD, everything committed. Game: 1306 / 2406 functions, 325,696 bytes matched. Build: `export PATH=$PWD/.venv/bin:$PATH; ninja`.

## Where to pick up
- **rep_AC8.c** (fielder AI): 116 left, smallest first: fn_3_55CC4, 57488, 27FF4, 2DAC4, 38000, 3B764, 55370. Near-match: fn_3_596F8 (94%, notes in .agent/attempts).
- **rep_3880.c**: 30 left (Codex ran out of credits): fn_3_14D2C0 (88 B), 14E894, 153F8C, 1573AC, 15767C, 1549F0, 150D84.
- **Allocation-size family** (idiom from fn_3_E4EF4, see .agent/attempts/fn_3_E4EF4.c): fn_3_C82B4, E4FC4, D6514, D67CC, FA3C0, F6C60, E763C.
- Near-matches: fn_3_70768 (1 line), fn_3_4CFB0 (99.2%), fn_3_596F8.

## How (read .agent/decomp_knowledge.md sections 5-7 first)
- rep_AC8 top-of-file `static inline` helpers cover most bodies: setFielderTarget / setFielderTargetIdx / aimFielderAt (the atan2+sqrt target block, three variants), setFielderReadyAction, readyFielderIfValid, stopFielder, fielderFramesToReach, getLeadRunnerChaseBase, releaseFielderBase, updateFielderHeading, beginFielderCatchAnim, startFielderChase, sendFielderToHome. Duplicated asm block = one of these, or a new helper.
- Loop over g_Fielders with a stray `mr` copying the base: use index form `g_Fielders[i].x`, not a walking pointer.
- Workflow: write candidate.c, then `python3 tools/try_function.py <src> <fn> <cand.c>`. Count true diffs with `python3 tools/sbs.py <fn> | grep -c '^\*'` (feedback_diff caps output at 10 lines; a failed build leaves sbs stale).
- Regression check before each commit: `ninja build/GYQE01/report.json && python3 tools/find_matches.py build/GYQE01/report.json`; nothing may drop out.
- Parallel agents: give each its own worktree (see .agent/workflows/parallel_batch.md) and one file each, then cherry-pick their commits into main.

## Triage
.agent/categorize/hard_triage.csv (script: triage_hard.py) and fable_review.csv rank the old "hard" list by likely speed.
