# fn_80013680 continuation

2026-10-24, load-chain. Five refinement attempts exhausted; explicit continuation required.
Final: 307 feedback lines, 96.4749% fuzzy (original baseline 545 lines, 81.23881%). Not MATCH.
The preceding fn_80012B90 commit improved this to 525 lines before these attempts.

Retained changes:
- Restore the retail one-iteration actor countdown using a typed actors[1] union view at offset 0.
  Only index 0 is read. Signed slot indexing, s32 bone index, and explicit s16 glove-list test
  reproduce the omitted sign-extension and loop instructions. Bone counter declaration order
  now gives the target destination-bone and bone-count registers.
- Capture lbl_803CBC00 before either model queue call. The old shared helper incorrectly selected
  lbl_803CBC08, the non-mode-2 texture global. Both models still finalize through finishSubItemLoad.
- A u8-returning readiness wrapper reproduces the boolean result and clrlwi test in the target.
- Use direct indexed fields for cache comparisons/release; retain original charID and slotKind in
  claimSubItemEntry, with indexed stores after the texture store through the entry pointer.
- Separate arm-byte assignments avoid an extra byte mask; narrow equality result to u8 in an s32
  local. Repeating equality for the second model is currently CSE'd by MWCC.

Attempts:
1. Countdown/types, readiness wrapper, and mode-2 texture: 492 lines.
2. Move phase 2 into loadChallengeSubItems inline + direct cache references: 659 lines;
   helper was emitted out of line, rejected and removed.
3. Restore direct phase 2 and keep indexed cache references: 475 lines.
   Inspection found the scripted adaptation in attempts 1-3 had accidentally omitted the second
   finalization call. These intermediate results are invalid candidates; none was committed.
4. Restore second finalization through the wrapper, use separate arm-byte assignments and
   byte-narrowed signed predicate: 397 lines, 94.56445%, valid.
5. Pass original IDs to indexed claim helper, swap equality operands/recompute at second site,
   move bone counter declaration: 307 lines, 96.4749%, retained.

Remaining differences:
- Initial charID and slotKind scratch registers swapped (r4/r3 vs r3/r4); cached-entry stores,
  free-entry and stolen-entry scans still differ in address reuse and register scheduling.
- Attachment loop walker and sub-entry pointer registers swapped (e.g. r10/r8 vs r8/r10).
- Phase-2 armSet is folded into a single preserved equality predicate; target saves armSet in r27
  and recomputes equality for obj0. Ours saves from r20 rather than target r19.
- Texture/object/header-index/layout/geometry/actor-slot saved registers consequently differ.
- Readiness guard takes an early return branch where target shares the final return-zero tail;
  obj1 queue argument address is folded differently.

Validation: ninja succeeds; feedback_diff.py reports 307 lines, no MATCH. fn_80012B90 remains
183 lines / 92.61%. Report comparison across all functions shows no fuzzy-score decreases
against the original baseline. Final exact-match count remains 3967. No orig files modified.
