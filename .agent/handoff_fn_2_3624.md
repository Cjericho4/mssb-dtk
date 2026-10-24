# Handoff: fn_2_3624 (menus.rel, 0x134C)

## Current state (Codex continuation, 2026-10-24)

- Worktree `/home/plex/repos/mssb-dtk-fable`, branch `fable-menus` only. Never push or modify orig/.
- Complete, documented C body remains in `src/menus/gap_1254.c`.
- **Down from 414 operand mismatches + 30 missing/extra lines to FIVE feedback lines.**
  All instructions outside the colour-search initializer match, including the prologue, register
  allocation, challenge-mode loop, swap loop, colour cycling, markSlotTaken and final Z popup path.
- `ninja` succeeds; no MATCH yet (still 5 lines on main, 2026-10-24; total matches 3967).
- No queue/progress files changed. Untracked `.venv` is pre-existing; preserve it.
- The user's explicit continuation overrides AGENTS.md's attempt limit and authorizes commits.
  On MATCH commit `matched fn_2_3624`, no trailers. Before every commit run
  `ninja build/GYQE01/report.json && python3 tools/find_matches.py build/GYQE01/report.json | wc -l`;
  never below the current count (3967 on 2026-10-24). When out of budget without matching, commit best as `wip fn_2_3624`.

## Changes that worked

1. `side` must be **s32**, declared **last** among locals. This alone fixes saved-register count
   (`r25..r31`, save area +0x14) and puts side in r31, padSide base in r28. The 6-byte input buffer
   was already at +8 on both sides; +20 vs +16 described the saved-register area, not that buffer.
2. Declare `s8 slot` **after** the swap temporaries a/va. This puts it in r26 in both slot searches.
3. `closePopup`'s argument must be **u8**, consistent with fn_2_35D0. This preserves the indexed
   flags45 array base in the final Z-button path and eliminates its extra instruction. Other
   closePopup expansions remain correct; fn_2_35D0 and all existing matches still match.
4. The challenge-mode copy **must use chained assignments**, in this order:
   ```c
   starMissionCompletionTracker.lineup[n].charID =
       inMemRoster[0][n].stats.CharID = lbl_803C6724.teams[0][n];
   starMissionCompletionTracker.lineup[n].slot = n;
   starMissionCompletionTracker.lineup[n].order =
       lbl_80354720[0][n].unk2 = lbl_803C6724.order[0][n];
   ```
   This makes the entire loop exact, including n in r25, four walkers, scheduling and load reuse.
   Permuting the original five independent stores, moving declarations, sharing counters and
   wrapping the copy/loop in inline helpers did not solve it.

## Exact remaining diff

At feedback lines 918..922, just after `cursor[side] != 9` and before the colour-family search:

```
Target:                                  Current:
lis  r3, lbl_2_bss_F468@ha                lis  r4, lbl_2_bss_F468@ha
li   r9, 0                               lis  r3, lbl_80108EDC@ha
addi r4, r3, lbl_2_bss_F468@l             addi r4, r4, lbl_2_bss_F468@l
lis  r3, lbl_80108EDC@ha                  li   r9, 0
```

Everything from the next `add r8, r4, r31; stbu r9, 0x50(r8)` onward matches. Same function size.
The source for that setup and loop remains:

```c
lbl_2_bss_F468.unk50[side] = i = 0;
for (; i < 9; i++) {
    for (j = 0; j < 5; j++) {
        if (c == lbl_80108EDC[i][j]) {
            lbl_2_bss_F468.unk50[side] = 1;
            goto found;
        }
    }
}
found:
if (lbl_2_bss_F468.unk50[side] == 0) return;
```

`sbs.py` additionally marks switch-table relocation names and their associated lwzx instructions;
feedback normalizes those and they are NOT additional mismatches.

## Experiments already tried (no improvement over five lines)

- Local declaration-position searches for n, slot and i; shared counters n/k/i/j/cell/next/t;
  int vs s32 (s32 is signed long here), narrow/unsigned loop-counter types, register declarations;
  c/state types and merging c/state. Narrow types usually add sign extensions; unsigned changes
  compares. Preserve the current declarations.
- Split, reversed, comma and cast flag/i initialization; moving initialization earlier; extra
  zero assignments; clearing with &= or *=; local/reset/setter helpers with value or reference args.
- for/while/do/count-at-head/count-at-tail loops, explicit loop labels/gotos, continue comparisons,
  nested breaks, local found boolean or flag guards. Most either retain the same five differences
  or cause many more differences. The direct nested loops plus goto are still best.
- Explicit typed pointers to the table, row, global state, and flag; pointers declared at top
  or in block; const row pointers; comma table initializers; named cursor temporary.
- Inline helpers around per-entry/whole challenge copy, family scan, whole colour handler,
  table/member/roster getters. No improvement on the initializer.
- Table extern extent/const/declaration placement (including local externs), struct vs u16[3]
  input record, expression temporaries. A volatile-store diagnostic made things worse and was
  discarded; do not add unsupported volatility or compiler barriers to force a match.

Scratch scripts/candidates and detailed notes are in `.scratch/`; read `.scratch/codex_notes.md`.
Best function-only candidate after documentation/formatting: `.scratch/documented_best.c`.
Earlier unformatted best: `.scratch/form_best.c`.
**Caution:** try_function --keep replaces only the named function. An experimental helper included
before the candidate function can remain in the source when the next trial replaces the function;
remove unused experimental helpers explicitly. The committed best has no experimental helpers.

## Phase-2 side quest (still open; do after MATCH)

Record in `.agent/character_select.md` what happens after a pick is confirmed (fn_2_DFAC's callees
fn_2_5444, fn_2_102C8, fn_2_1C34) and what updates the visible preview while fn_2_3624 moves the
cursor. Trace the actual portrait/name/mini-screen sprite selection and its key; donor clones still
show the donor portrait. Commit this documentation separately after the matched function commit.

- fn_2_1C34 is implemented: button-to-SFX dispatch (A=0x1B8, B=0x1B9, directions=0x1B7), no textures.
- fn_2_5444 and fn_2_102C8 remain stubs; inspect target assembly. Prior notes already describe
  ready/auto-fill behavior, but visual keys need verification.
- fn_800625A4's target writes command to `lbl_803C66B0.flags5D[side]` and resets transition bytes;
  target saved in `.scratch/625A4.target`. fn_2_3624 calls it with 0xE for ordinary cursor movement,
  0x18 for ready, 0x1B/1C/1D for edit operations. L changes team charID and taken flags directly.
- **Correct a misleading old comment while tracing:** fn_800559EC dispatches commands 0x29..0x31,
  fn_80060184 dispatches 0x38..0x46, so neither is directly the 0xE cursor command consumer. Existing
  fn_2_DFAC comment points at those generically; do not assume it identifies the actual renderer.
  Need locate the dispatcher for 0xE and then the pane/resource lookup.
