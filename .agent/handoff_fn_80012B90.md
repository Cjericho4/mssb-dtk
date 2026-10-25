# fn_80012B90 continuation

2026-10-24, codex-matches-r3. Explicit unlimited continuation used; **not MATCH**.
Best retained: **78 feedback entries / 98.828575% fuzzy**, starting at 183 / 92.61%.
`ninja` succeeds; 3967 exact matches; no per-function score decreases against session baseline.
fn_80013680 remains 77 entries / 98.66079%.

Retained: use the byte-returning readiness wrapper at every normal-mode finalization site,
including loadAlternatingSubItem; call it finishReadySubItemLoad since it now serves both modes.
The target has the return-one/return-zero and clrlwi guard at each site; direct readiness checks
omitted them. The preceding fn_80013680 commit's g_subItemLoadObj->buf access also improves this
function. No new model-selection or relocation semantics were introduced.

Exhausted additional searches: all 120 top-level declaration orders, s32/int/s8/u8 slot locals,
separate slot initialization, texture initialized at entry, signed header slot field (no change),
register hint (no change), moving the complete final case to a static inline with direct return
(91 entries, rejected). Prior handoff's root-header reload / four-argument fn_800238E0 findings
still apply; do not replace the repeated obj->buf casts with a cached root pointer.

Remaining: slotKind r31 vs target r29; case-specific texture/layout/geometry/actor-slot registers;
initialization quotient scratch registers; queue argument scheduling; switch continuation sharing.
Complete feedback below (objdiff instruction indices; relocation-label-only differences are ignored
by feedback_diff.py). A build alone is not a match.

```
Line 7: Mismatch
  Target: lbz r29, 0x254(r3)
  Current: lbz r0, 0x254(r3)
Line 10: Mismatch
  Target: extsb r29, r29
  Current: extsb r31, r0
Line 12: Mismatch
  Target: mulli r4, r29, 0x27c
  Current: mulli r4, r31, 0x27c
Line 20: Mismatch
  Target: mulli r4, r29, 0x3
  Current: mulli r4, r31, 0x3
Line 30: Mismatch
  Target: mulli r4, r29, 0x3
  Current: mulli r4, r31, 0x3
Line 71: Mismatch
  Target: srwi r3, r5, 31
  Current: srwi r4, r5, 31
Line 72: Mismatch
  Target: mulli r4, r29, 0x3
  Current: mulli r3, r31, 0x3
Line 74: Mismatch
  Target: add r3, r5, r3
  Current: add r4, r5, r4
Line 76: Mismatch
  Target: add r3, r3, r4
  Current: add r4, r4, r3
Line 77: Mismatch
  Target: clrlslwi r0, r3, 25, 1
  Current: clrlslwi r0, r4, 25, 1
Line 78: Mismatch
  Target: slwi r3, r3, 1
  Current: slwi r3, r4, 1
Line 104: Extra instruction in your code.
  Current: lbz r3, 0xcf(r28)
Line 106: Missing instruction in your code.
  Target: lbz r3, 0xcf(r28)
Line 108: Extra instruction in your code.
  Current: lwz r5, 0x0(r5)
Line 111: Missing instruction in your code.
  Target: lwz r5, 0x0(r5)
Line 156: Mismatch
  Target: lwzx r25, r6, r3
  Current: lwzx r26, r6, r3
Line 157: Mismatch
  Target: addi r29, r5, 0x34
  Current: addi r24, r5, 0x34
Line 158: Mismatch
  Target: lwzx r26, r6, r0
  Current: lwzx r25, r6, r0
Line 159: Mismatch
  Target: mr r3, r25
  Current: mr r3, r26
Line 160: Mismatch
  Target: add r29, r4, r29
  Current: add r24, r4, r24
Line 162: Mismatch
  Target: mr r3, r26
  Current: mr r3, r25
Line 165: Mismatch
  Target: mr r3, r25
  Current: mr r3, r26
Line 166: Mismatch
  Target: mr r4, r26
  Current: mr r4, r25
Line 168: Mismatch
  Target: mr r3, r26
  Current: mr r3, r25
Line 172: Mismatch
  Target: mr r6, r25
  Current: mr r6, r26
Line 180: Mismatch
  Target: li r24, lbl_803CB7C4@sda21
  Current: li r25, lbl_803CB7C4@sda21
Line 181: Mismatch
  Target: lbz r0, 0x2(r24)
  Current: lbz r0, 0x2(r25)
Line 185: Mismatch
  Target: lbz r0, 0x2(r24)
  Current: lbz r0, 0x2(r25)
Line 186: Mismatch
  Target: mr r4, r29
  Current: mr r4, r24
Line 219: Mismatch
  Target: lwz r31, lbl_803CBC08@sda21
  Current: lwz r29, lbl_803CBC08@sda21
Line 279: Mismatch
  Target: lwzx r28, r6, r3
  Current: lwzx r26, r6, r3
Line 280: Mismatch
  Target: addi r25, r5, 0x34
  Current: addi r28, r5, 0x34
Line 281: Mismatch
  Target: lwzx r26, r6, r0
  Current: lwzx r31, r6, r0
Line 282: Mismatch
  Target: mr r3, r28
  Current: mr r3, r26
Line 283: Mismatch
  Target: add r25, r4, r25
  Current: add r28, r4, r28
Line 285: Mismatch
  Target: mr r3, r26
  Current: mr r3, r31
Line 288: Mismatch
  Target: mr r3, r28
  Current: mr r3, r26
Line 289: Mismatch
  Target: mr r4, r26
  Current: mr r4, r31
Line 291: Mismatch
  Target: mr r3, r26
  Current: mr r3, r31
Line 292: Mismatch
  Target: mr r4, r31
  Current: mr r4, r29
Line 295: Mismatch
  Target: mr r6, r28
  Current: mr r6, r26
Line 309: Mismatch
  Target: mr r4, r25
  Current: mr r4, r28
Line 337: Mismatch
  Target: lwz r31, lbl_803CBC08@sda21
  Current: lwz r29, lbl_803CBC08@sda21
Line 396: Mismatch
  Target: lwzx r28, r6, r3
  Current: lwzx r31, r6, r3
Line 397: Mismatch
  Target: addi r25, r5, 0x34
  Current: addi r26, r5, 0x34
Line 398: Mismatch
  Target: lwzx r26, r6, r0
  Current: lwzx r28, r6, r0
Line 399: Mismatch
  Target: mr r3, r28
  Current: mr r3, r31
Line 400: Mismatch
  Target: add r25, r4, r25
  Current: add r26, r4, r26
Line 402: Mismatch
  Target: mr r3, r26
  Current: mr r3, r28
Line 405: Mismatch
  Target: mr r3, r28
  Current: mr r3, r31
Line 406: Mismatch
  Target: mr r4, r26
  Current: mr r4, r28
Line 408: Mismatch
  Target: mr r3, r26
  Current: mr r3, r28
Line 409: Mismatch
  Target: mr r4, r31
  Current: mr r4, r29
Line 412: Mismatch
  Target: mr r6, r28
  Current: mr r6, r31
Line 426: Mismatch
  Target: mr r4, r25
  Current: mr r4, r26
Line 454: Mismatch
  Target: lwz r31, lbl_803CBC08@sda21
  Current: lwz r29, lbl_803CBC08@sda21
Line 514: Mismatch
  Target: lwzx r28, r6, r3
  Current: lwzx r31, r6, r3
Line 515: Mismatch
  Target: addi r25, r5, 0x34
  Current: addi r26, r5, 0x34
Line 516: Mismatch
  Target: lwzx r26, r6, r0
  Current: lwzx r28, r6, r0
Line 517: Mismatch
  Target: mr r3, r28
  Current: mr r3, r31
Line 518: Mismatch
  Target: add r25, r4, r25
  Current: add r26, r4, r26
Line 520: Mismatch
  Target: mr r3, r26
  Current: mr r3, r28
Line 523: Mismatch
  Target: mr r3, r28
  Current: mr r3, r31
Line 524: Mismatch
  Target: mr r4, r26
  Current: mr r4, r28
Line 526: Mismatch
  Target: mr r3, r26
  Current: mr r3, r28
Line 527: Mismatch
  Target: mr r4, r31
  Current: mr r4, r29
Line 530: Mismatch
  Target: mr r6, r28
  Current: mr r6, r31
Line 544: Mismatch
  Target: mr r4, r25
  Current: mr r4, r26
Line 572: Mismatch
  Target: lwz r31, lbl_803CBC08@sda21
  Current: lwz r29, lbl_803CBC08@sda21
Line 632: Mismatch
  Target: addi r25, r5, 0x34
  Current: addi r26, r5, 0x34
Line 633: Mismatch
  Target: lwzx r26, r6, r0
  Current: lwzx r25, r6, r0
Line 635: Mismatch
  Target: add r25, r4, r25
  Current: add r26, r4, r26
Line 637: Mismatch
  Target: mr r3, r26
  Current: mr r3, r25
Line 641: Mismatch
  Target: mr r4, r26
  Current: mr r4, r25
Line 643: Mismatch
  Target: mr r3, r26
  Current: mr r3, r25
Line 644: Mismatch
  Target: mr r4, r31
  Current: mr r4, r29
Line 661: Mismatch
  Target: mr r4, r25
  Current: mr r4, r26
Line 685: Mismatch
  Target: mulli r4, r29, 0x27c
  Current: mulli r4, r31, 0x27c
```
