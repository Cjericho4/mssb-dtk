# fn_80013680 continuation

2026-10-24, codex-matches-r3. Explicit unlimited continuation used; not MATCH.
Best retained: **77 feedback entries, 98.66079% fuzzy** (started 307 / 96.4749%).
Build succeeds; 3967 exact matches; no function fuzzy score decreased against the session baseline.
The shared queue-buffer change initially improved fn_80012B90 to 168 entries / 93.924286%.
Its subsequent readiness-wrapper continuation reaches 78 entries / 98.828575%, with no change here.

Retained changes:
- Assign the raw slot byte in the first signed comparison and re-extend in the second;
  this recovers the missing extsb without volatile accesses.
- Reload the slot byte in the release scan; form the free-entry pointer only after its test.
- Read queue buffer through g_subItemLoadObj, preserving the target obj1 argument address.
- Explicit typed actor walker, declared before actor, reproduces the first attachment register webs.
- Byte arm flags plus explicit second-site narrowing retain both equality calculations;
  enclosing the work in a positive readiness guard shares the final return-zero block.
- Keep charID signed: the unsigned experiment had fewer feedback entries (73) but lost the
  required sign extension and had a worse fuzzy score (98.05%).

Exhausted experiments (hundreds of compiled variants, all rejected unless above): declaration
permutations / placements, int vs s32 vs s8/u8 char and slot initializers, separated initialization,
all flag type and narrowing combinations, boolean/inverted forms, variable reuse for armByte /
slotKind, explicit pointer vs indexed actor walks, direct vs cached subItems, alternate texture
store aliases, predicate inline helpers, first-stage / both-stage helpers and whole phase-2 inline
splits. Larger helpers emit out of line; small stage helpers still reorder registers. No dead
attempts retained. New C/struct changes should start here rather than repeating these searches.

Remaining: initial charID/slot scratch registers, attachment tail walker/load registers,
free-entry store scheduling, stolen-entry search register webs; phase-2 armSet/isFielder/equality,
texture and header-index saved-register permutation, and signed vs unsigned predicate compares.
Feedback entry line numbers and target/current below (line numbers are objdiff instruction indices):

```
Line 6: Mismatch
  Target: lbz r3, 0x252(r3)
  Current: lbz r3, 0x254(r3)
Line 7: Mismatch
  Target: lbz r4, 0x254(r31)
  Current: lbz r4, 0x252(r31)
Line 26: Mismatch
  Target: cmpw r5, r3
  Current: cmpw r5, r4
Line 58: Mismatch
  Target: lis r3, g_hugeAnimStruct@ha
  Current: lis r5, g_hugeAnimStruct@ha
Line 59: Mismatch
  Target: addi r5, r8, 0x140
  Current: addi r4, r8, 0x140
Line 60: Mismatch
  Target: addi r6, r3, g_hugeAnimStruct@l
  Current: addi r6, r5, g_hugeAnimStruct@l
Line 62: Mismatch
  Target: add r3, r6, r9
  Current: add r5, r6, r9
Line 63: Mismatch
  Target: stb r4, 0x210(r3)
  Current: stb r3, 0x210(r5)
Line 65: Mismatch
  Target: stw r5, 0x30(r31)
  Current: stw r4, 0x30(r31)
Line 244: Extra instruction in your code.
  Current: addi r5, r5, g_hugeAnimStruct@l
Line 245: Mismatch
  Target: stw r6, lbl_803CBC20@sda21
  Current: stw r0, 0x208(r7)
Line 246: Missing instruction in your code.
  Target: addi r5, r5, g_hugeAnimStruct@l
Line 248: Missing instruction in your code.
  Target: stw r0, 0x208(r7)
Line 249: Mismatch
  Target: stb r3, 0x20f(r5)
  Current: stb r4, 0x20f(r5)
Line 251: Extra instruction in your code.
  Current: stw r6, lbl_803CBC20@sda21
Line 253: Mismatch
  Target: stb r4, 0x210(r5)
  Current: stb r3, 0x210(r5)
Line 267: Mismatch
  Target: li r10, 0x0
  Current: li r9, 0x0
Line 270: Mismatch
  Target: clrlwi r0, r10, 24
  Current: clrlwi r0, r9, 24
Line 272: Mismatch
  Target: mulli r9, r0, 0xd4
  Current: mulli r8, r0, 0xd4
Line 273: Mismatch
  Target: add r5, r6, r9
  Current: add r5, r6, r8
Line 274: Mismatch
  Target: addi r7, r5, 0x140
  Current: addi r10, r5, 0x140
Line 275: Mismatch
  Target: stw r7, lbl_803CBC20@sda21
  Current: stw r10, lbl_803CBC20@sda21
Line 279: Mismatch
  Target: lwz r8, 0x2c50(r5)
  Current: lwz r7, 0x2c50(r5)
Line 280: Mismatch
  Target: cmplwi r8, 0x0
  Current: cmplwi r7, 0x0
Line 282: Mismatch
  Target: lbz r5, 0xcf(r7)
  Current: lbz r5, 0xcf(r10)
Line 283: Mismatch
  Target: lbz r0, 0x252(r8)
  Current: lbz r0, 0x252(r7)
Line 298: Mismatch
  Target: stw r6, 0xc8(r7)
  Current: stw r6, 0xc8(r10)
Line 299: Mismatch
  Target: add r5, r0, r9
  Current: add r5, r0, r8
Line 300: Mismatch
  Target: stb r3, 0x20f(r5)
  Current: stb r4, 0x20f(r5)
Line 303: Mismatch
  Target: stb r4, 0x210(r5)
  Current: stb r3, 0x210(r5)
Line 309: Mismatch
  Target: addi r10, r10, 0x1
  Current: addi r9, r9, 0x1
Line 310: Mismatch
  Target: clrlwi r0, r10, 24
  Current: clrlwi r0, r9, 24
Line 313: Mismatch
  Target: lwz r3, lbl_803CBC20@sda21
  Current: lwz r4, lbl_803CBC20@sda21
Line 315: Mismatch
  Target: stb r0, 0xc1(r3)
  Current: stb r0, 0xc1(r4)
Line 316: Mismatch
  Target: lwz r3, lbl_803CBC20@sda21
  Current: lwz r4, lbl_803CBC20@sda21
Line 317: Mismatch
  Target: stb r0, 0x5d(r3)
  Current: stb r0, 0x5d(r4)
Line 321: Mismatch
  Target: cmpwi r4, 0x9
  Current: cmpwi r3, 0x9
Line 323: Mismatch
  Target: lbz r8, 0x25a(r31)
  Current: lbz r7, 0x25a(r31)
Line 325: Mismatch
  Target: lbz r8, 0x25b(r31)
  Current: lbz r7, 0x25b(r31)
Line 326: Mismatch
  Target: li r6, 0x9
  Current: li r4, 0x9
Line 327: Mismatch
  Target: neg r7, r8
  Current: neg r6, r7
Line 328: Mismatch
  Target: xor r0, r6, r4
  Current: xor r0, r4, r3
Line 331: Mismatch
  Target: or r7, r7, r8
  Current: or r6, r6, r7
Line 332: Mismatch
  Target: and r0, r0, r6
  Current: and r0, r0, r4
Line 335: Mismatch
  Target: srwi r27, r7, 31
  Current: srwi r25, r6, 31
Line 336: Mismatch
  Target: srwi r23, r0, 31
  Current: srwi r26, r0, 31
Line 338: Mismatch
  Target: subf r0, r23, r27
  Current: subf r0, r26, r25
Line 343: Mismatch
  Target: li r22, lbl_803CB7C4@sda21
  Current: li r23, lbl_803CB7C4@sda21
Line 344: Mismatch
  Target: extrwi r26, r0, 8, 19
  Current: extrwi r27, r0, 8, 19
Line 349: Mismatch
  Target: lwz r25, lbl_803CBC00@sda21
  Current: lwz r22, lbl_803CBC00@sda21
Line 356: Mismatch
  Target: cmpwi r23, 0x0
  Current: cmplwi r26, 0x0
Line 363: Mismatch
  Target: cmpwi r26, 0x0
  Current: cmpwi r27, 0x0
Line 409: Mismatch
  Target: lbz r0, 0x1(r22)
  Current: lbz r0, 0x1(r23)
Line 427: Mismatch
  Target: mr r4, r25
  Current: mr r4, r22
Line 438: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 442: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 448: Mismatch
  Target: lbz r0, 0x3(r22)
  Current: lbz r0, 0x3(r23)
Line 454: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 473: Mismatch
  Target: subf r3, r23, r27
  Current: subf r3, r26, r25
Line 483: Mismatch
  Target: cmpwi r23, 0x0
  Current: cmplwi r26, 0x0
Line 535: Mismatch
  Target: lbz r0, 0x1(r22)
  Current: lbz r0, 0x1(r23)
Line 564: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 568: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 574: Mismatch
  Target: lbz r0, 0x3(r22)
  Current: lbz r0, 0x3(r23)
Line 580: Mismatch
  Target: lbz r0, 0x2(r22)
  Current: lbz r0, 0x2(r23)
Line 624: Mismatch
  Target: mr r7, r9
  Current: mr r8, r9
Line 628: Mismatch
  Target: lhax r8, r4, r0
  Current: lhax r4, r4, r0
Line 629: Mismatch
  Target: extsh. r0, r8
  Current: extsh. r0, r4
Line 630: Mismatch
  Target: lwz r4, 0x0(r7)
  Current: lwz r7, 0x0(r8)
Line 637: Mismatch
  Target: lwz r6, 0x18(r4)
  Current: lwz r6, 0x18(r7)
Line 661: Mismatch
  Target: subi r7, r7, 0x4
  Current: subi r8, r8, 0x4
Line 683: Mismatch
  Target: mr r6, r8
  Current: mr r7, r8
Line 687: Mismatch
  Target: lhax r7, r3, r0
  Current: lhax r3, r3, r0
Line 688: Mismatch
  Target: extsh. r0, r7
  Current: extsh. r0, r3
Line 689: Mismatch
  Target: lwz r3, 0x0(r6)
  Current: lwz r6, 0x0(r7)
Line 696: Mismatch
  Target: lwz r5, 0x18(r3)
  Current: lwz r5, 0x18(r6)
Line 720: Mismatch
  Target: subi r6, r6, 0x4
  Current: subi r7, r7, 0x4
```
