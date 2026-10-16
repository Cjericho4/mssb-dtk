# Working Progress

## Current Focus
**Source of truth:** Always follow `queue.log`. If this file disagrees with `queue.log`, `queue.log` wins.
**Strategy:** Work through functions listed in `queue.log` (plain entries at the bottom, after all COMPLETED/NONMATCHING lines)
**Queue file:** `queue.log`
**Next function to attempt:** queue is empty. Next: queue the next 100 medium functions and run `.agent/workflows/parallel_batch.md` (~316 medium left). Done: easy tier 79/93, medium batch 1 93/100, batch 2 92/100 (2026-10-14/15; 824 game functions matched).

To find the next function: look for the first plain entry (not prefixed with COMPLETED/NONMATCHING/SKIPPED) in `queue.log` that hasn't been committed yet.

---

## Recently Completed (from queue.log)
| Function | Notes |
|---|---|
| fn_3_120F5C | matched |
| fn_3_33458 | matched |
| fn_3_25844 | matched |
| fn_3_4DB84 | matched |
| fn_3_9DB5C | matched |
| fn_3_1658F0 | matched (Bss37400Sub[9] at 0x12) |
| fn_3_115828 | matched |
| fn_3_75434 | matched (smallest never-attempted hard fn) |
| fn_3_E19E8 | matched (inlined fn_3_E0668 loop) |
| fn_3_24ADC | matched |
| fn_3_6C938 | matched (inline button-check helper) |
| fn_3_6BA64 | matched |
| fn_3_A36BC, fn_3_BB07C, fn_3_E45F0, fn_3_14F544, fn_3_1C0B0, fn_3_1C130 | matched by replacing extern rodata floats with literals |
| fn_3_DF00C | matched |
| fn_3_DF3D8 | matched (FrameCountOfCurrentPitch → u16) |
| fn_3_8FC0C | matched |
| fn_3_6620 | already matched; queue entry updated |
| fn_3_5985C | matched |
| fn_3_1AE44 | already matched; queue entry updated |
| fn_3_59BCC | matched |
| fn_3_9E7D4 | matched |
| fn_3_B03F0 | matched |
| fn_3_D24E8 | matched |
| fn_3_DCED0 | matched |
| fn_3_F8B34 | matched |
| fn_3_112558 | matched |
| fn_3_167CC4 | matched (new gap_167CC4.c) |
| fn_3_76C78 | matched (new gap_759BC.c) |
| fn_3_E1C60 | matched |
| fn_3_E587C | matched |
| fn_3_DF820 | matched |
| fn_3_E1D00 | matched |
| fn_3_1665E4 | matched (new gap_1665E4.c) |

---

## Almost Matched (do not retry)
| Function | Issue |
|---|---|
| fn_3_49EA8 | &unk_F8[idx] base: target reuses one reg (add r6; addi r6,r6,0xf8), CW allocates a separate temp; register-only |
| fn_3_FD51C | CW coalesces camera elem base and &elem->unk13C into one reg (target keeps separate r5/r7 and schedules stw 0x144 after addi), register/scheduling only |
| fn_3_105C28 | register allocation / scheduling (see git log) |
| fn_3_E6798 | register allocation / scheduling (see git log) |
| fn_3_11881C | register allocation / scheduling (see git log) |
| fn_3_129370 | register allocation / scheduling (see git log) |
| fn_3_135E38 | register allocation / scheduling (see git log) |
| fn_3_14DC80 | register allocation / scheduling (see git log) |
| fn_3_14F8D0 | register allocation / scheduling (see git log) |
| fn_3_150010 | register allocation / scheduling (see git log) |
| fn_3_1354BC | CW register allocation: uses f4 for diff1 and f1 for diff2, generating different fsubs destinations (f4/f1 vs f1/f2); li r3,0 placement also differs — unfixable |
| fn_3_90AB0 | r0/r4 register swap in index base+offset computation, and lwz vs lwzu update form — both unfixable from C |
| fn_3_10FB74 | beq+b double-branch vs bne/fallthrough — CW branch direction codegen, unfixable from C |
| fn_3_112070 | CW sign-bit register allocation: target reuses srwi r5 from % 30 division as 3rd fn_3_155288 arg; add result goes to r0 in target but r5 in compile, causing ext |
| fn_3_125850 | fn_80034E20 called with 2 args in target (no r5 setup), but global 3-arg declaration forces NULL→li r5,0 before call; local redecl rejected by -requireprotos |
| fn_3_117588 | register allocation / scheduling (see git log) |
| fn_3_90C14 | fn_800216F8 called with 3 args here, 2 elsewhere in file; one prototype can't satisfy both |
| fn_3_A32B8 | nested-struct field load folded to single lwz |
| fn_3_B7CDC, fn_3_B7C2C | adjacent-constant compares merged into range check |
| fn_3_B7E44 | int-to-double/0.06 constant load form shifts scheduling |
| fn_3_141A30 | regalloc only; jump table lives in rep_36D8 .data (split fix needed) |
| fn_3_ED058 | scene pointer loaded into temp then mr r3 |
| fn_3_FF98 | regalloc only (0 diffs ignoring registers) |
| fn_3_119EE0, fn_3_119E30 | 0x34 offset folded into lwzx index |
| fn_3_8B094 | offset-indexed vs pointer form for table entry |
| fn_3_9EE24 | regalloc (max/abs in r10/r3) |
| fn_3_14E894 | zero init `li r30,0; mr r31,r30` vs separate `li r31,0` (2 lines) |
| fn_3_A31E8 | nested-struct field load folded (same as fn_3_A32B8) |
| fn_3_C0D10 | `base+1` kept in r31 across memcpy with `stbx`; no layout reproduces it |
| fn_3_142C18 | r27-r29 order; loop shared with fn_3_146928 (matched via inline do-while) |
| fn_3_E7388 | volatile r3/r5/r8 swapped + extra mr |
| fn_3_90150 | int-to-float order / pan register (47 lines); attempt: .agent/attempts/fn_3_90150.* |
| fn_3_20EEC | max loaded before min; division result register (10 lines) |
| fn_3_E68A8 | obj/actor r31/r30 swapped, time via f1→fmr; attempt: .agent/attempts/fn_3_E68A8.diff |
| fn_3_E7424 | lbl_3_bss_AE80 addressed off AE50 base (second base reg); attempt: .agent/attempts/fn_3_E7424.* |
| fn_3_6A9B0 | compare scheduled before 100*chargeDown product; attempt: .agent/attempts/fn_3_6A9B0.c |
| fn_3_8C4F0 | three saved regs in reverse order; needs Bss1760 overlay; attempt: .agent/attempts/fn_3_8C4F0.c |
| fn_3_EA340 | `((unkIndex+i)+3)<<3; lwzx` add order (33 lines); attempt: .agent/attempts/fn_3_EA340.c |
| fn_3_15F574 | `add`+`stw 0(rX)` vs our `stwx`; attempt: .agent/attempts/fn_3_15F574.* |
| fn_3_10030 | add-chain reassociation (4 lines); attempt: .agent/attempts/fn_3_10030.c |
| fn_3_219CC | split base+`idx*4+0xF4` lwzx and dead counter (45 lines); needs `s8 unk257` in AnimationStruct; attempt: .agent/attempts/fn_3_219CC.c |
| fn_3_1048E0 | same-file static data addressed off one base reg (r31+0x4f44...); externs reload lis/addi — unfixable until data moves into the .c (.agent/attempts/fn_3_1048E0.c) |
| fn_3_EECF4 | bss base kept in r30 for whole fn, mtx[0][0] via r30 and rest via &indMtx; separate statics sharing a compiler base — struct overlay can't reproduce (.agent/attempts/fn_3_EECF4.c) |
| fn_3_F22FC | r29/r30 swap between `s8 idx` and `&g_Fielders[idx]`; all decl orders + inline tried (.agent/attempts/fn_3_F22FC.c + .headers.diff) |
| fn_3_A2B6C | rep_18E8 file-static bss off one base reg, array sub-bases unfolded in target; overlay struct folds them (.agent/attempts/fn_3_A2B6C.c) |
| fn_3_A2C9C | same as fn_3_A2B6C (.agent/attempts/fn_3_A2C9C.c) |
| fn_3_1412BC | identical insns, saved-reg permutation only (i wants r26); decl order/loop forms tried (.agent/attempts/fn_3_1412BC.c) |
| fn_3_90CB0 | target strength-reduces both inner loops to incrementing byte ptrs with mg copy in r29; MWCC emits add/lbzx (.agent/attempts/fn_3_90CB0.c) |
| fn_3_21C90 | dead double `b` after 2-case switch dispatch — known unfixable (.agent/attempts/fn_3_21C90.c + .headers.diff) |
| fn_3_21DE4 | same as fn_3_21C90 (.agent/attempts/fn_3_21DE4.c) |
| fn_3_16943C | target `lwzu` on lbl_3_bss_BA00+0x8 counter; struct/union/ptr forms all give lis/addi+lwz (.agent/attempts/fn_3_16943C.c + .diff) |
| fn_3_E4760 | r3/r4 swap on the two `lis` after PSVECScale (0.24f/0.0f); same prefix as unmatched fn_3_E4658 (.agent/attempts/fn_3_E4760.c + .headers.diff) |
| fn_3_E48D0 | same lis r3/r4 swap as fn_3_E4760/E4658 (.agent/attempts/fn_3_E48D0.c + .headers.diff) |
| fn_3_88C24 | regalloc only: loop counter r9 vs hoisted g_FieldingLogic._108 r3, reversed in target (.agent/attempts/fn_3_88C24.c) |
| fn_3_8A618 | regalloc in unrolled 4-runner loop (ptr r5/_107 r4 vs r6/r5) (.agent/attempts/fn_3_8A618.c + .headers.diff) |
| fn_3_678B8 | file-static bss/data array sub-bases off one base — known unfixable; needs 10-arg fn_3_67EF0 proto (.agent/attempts/fn_3_678B8.c analysis) |
| fn_3_ECBB0 | dead double `b end` after 2-case switch — known unfixable; plus add operand order (.agent/attempts/fn_3_ECBB0.c) |
| fn_3_CB3AC | ~48 lines: target keeps extra base reg for segment array + separate byte-offset counter over 6660 pair table; MWCC folds to lhzu walk (.agent/attempts/fn_3_CB3AC.c + .headers.diff) |
| fn_3_CB538 | regalloc: arg0/idx r28/r29 swapped, one stwx vs add+stw; decl-order brute force failed (.agent/attempts/fn_3_CB538.c + .headers.diff) |
| fn_3_13E21C | regalloc only (~19 lines): strength-reduced loop ptr/counter reg order (.agent/attempts/fn_3_13E21C.c + .headers.diff) |
| fn_3_BC6D8 | skipped: lwzu on global counter lbl_3_bss_9968 + same-file data off one lbl_3_data_111A8 base — known unfixable (.agent/attempts/fn_3_BC6D8.c note) |
| fn_3_BD504 | skipped: dead double `b end` — known unfixable |
| fn_3_BF6C0 | skipped: same-file static data off one base (r29=111A8 +0x1D0/+0x20/+0x444); inlines unmatched fn_3_BF070 (.agent/attempts/fn_3_BF6C0.c note) |
| fn_3_B5694 | 3 lines: placement of `lis lbl_3_common_bss_32724@ha` in tail (.agent/attempts/fn_3_B5694.c + .headers.diff) |
| fn_3_111038 | 68 lines, register numbering only; insn sequence identical (.agent/attempts/fn_3_111038.c) |
| fn_3_90DD8 | 5 lines: scheduling of 2-arg fn_800216F8 call setup (.agent/attempts/fn_3_90DD8.c) |
| fn_3_168DFC | skipped: same-file static data off one base (lbl_3_data_285A8 +0x120/+0x360) — known unfixable (.agent/attempts/fn_3_168DFC.c note) |
| fn_3_C11CC | same-file static .data off one base (r30=&lbl_3_data_17248, 17260 at +0x18) — known unfixable (.agent/attempts/fn_3_C11CC.c) |
| fn_3_F9164 | 1 line: u8 index on lbl_3_data_81DC emits clrlslwi vs slwi; s32 index moves the 81DC load above the vol if/else (.agent/attempts/fn_3_F9164.c + .headers.diff) |
| fn_3_F99F0 | same clrlslwi issue as fn_3_F9164 plus selector-load form/regs (.agent/attempts/fn_3_F99F0.c + .headers.diff) |
| fn_3_79414 | r5/r6 swap between runner ptr and cached status byte; decl-order + loop variants failed (.agent/attempts/fn_3_79414.c + .headers.diff) |
| fn_3_A295C | rep_18E8 lbl_3_bss_17F8 file-static sub-base (addi r30,r31,0x10) folded by MWCC — known unfixable (.agent/attempts/fn_3_A295C.c) |
| fn_3_A2DDC | skipped: same 17F8 sub-base pattern (.agent/attempts/fn_3_A2DDC.c note) |
| fn_3_A2FD8 | skipped: same 17F8 sub-base pattern (.agent/attempts/fn_3_A2FD8.c note) |
| fn_3_EE96C | after PSMTXCopy: target stores indMtx[1][1] via separate addi r3,r31,0x23c ptr, addi+lfs 0 consts; MWCC folds (.agent/attempts/fn_3_EE96C.c + .headers.diff) |
| fn_3_5C68 | saved-reg assignment only (obj r29, j r28, i r27, count r26); all 48 decl orders tried (.agent/attempts/fn_3_5C68.c + .headers.diff) |
| fn_3_168704 | skipped: same-file static data off one base (&lbl_3_data_285A8) — known unfixable (.agent/attempts/fn_3_168704.c note) |
| fn_3_C2AA0 | ~11 lines float regalloc in corner setup; 720 stmt/decl perms tried (.agent/attempts/fn_3_C2AA0.c + .headers.diff) |
| fn_3_C1004 | reg numbering: target keeps (&lbl_3_bss_9D40 + 1) and j*16 in saved regs (6), MWCC folds to displacements (5) (.agent/attempts/fn_3_C1004.c is a git diff) |
| fn_3_C1770 | skipped: same-file static data off one base (&lbl_3_data_17248 +0x18/+0x64/+0xA4), like fn_3_C11CC (.agent/attempts/fn_3_C1770.c note) |
| fn_3_16D5E4 | greg alloc only: idx r30, (u8)(idx-1) r29, fielder ptr r31 vs ours r31/r30/r29; decl+stmt order brute-forced (.agent/attempts/fn_3_16D5E4.c + .headers.diff) |
| fn_3_14BCB0 | 12 lines float-const load scheduling (0.5 before 2.0f, 2.0f must be a variable); 15+ forms tried (.agent/attempts/fn_3_14BCB0.c) |
| fn_3_1573AC | same-file static data off one base (&lbl_3_data_266A8 in r31 across calls) — known unfixable (.agent/attempts/fn_3_1573AC.c + .headers.diff) |
| fn_3_169600 | 9 lines: target keeps non-propagated copy `mr r30,r29` of outer loop counter for first nested loop; all forms copy-propagated (.agent/attempts/fn_3_169600.c + .headers.diff) |
| fn_3_15F648 | same base-reg pattern as fn_3_1573AC (addi r3,r30,0x148; lwz 4(r3)) plus colour build clrlslwi/rlwimi diffs (.agent/attempts/fn_3_15F648.c + .headers.diff) |
| fn_3_CD968 | corner-setup float block: freg numbering and w*0.5 fmuls operand order (.agent/attempts/fn_3_CD968.c) |
| fn_3_E3044 | 2 small diffs: lbz before `mr r31`, deg->rad load order (.agent/attempts/fn_3_E3044.c + .headers.diff) |
| fn_3_142088 | ~58 lines: inlined fn_3_142030 texel index associated differently; all term orders brute-forced (.agent/attempts/fn_3_142088.c) |
| fn_3_144ADC | ~38 lines lerp load scheduling (.agent/attempts/fn_3_144ADC.c + .headers.diff) |
| fn_3_215AC | ~32 lines float reg numbering only (.agent/attempts/fn_3_215AC.c) |
| fn_3_C937C | ~11 lines regalloc around player-entry update (.agent/attempts/fn_3_C937C.c + .headers.diff) |
| fn_3_105E00 | target has no extsh before x+w (needs s32 params) but that breaks matched caller fn_3_105CDC (.agent/attempts/fn_3_105E00.c + .headers.diff) |
| fn_3_15C3F8 | counters/quads base ptrs kept unfolded (addi rX,r31,0) + rodata order (.agent/attempts/fn_3_15C3F8.c) |
| fn_3_EEFD4 | one freg: acos result in f1 not f2, frsp after dir.z load (.agent/attempts/fn_3_EEFD4.c + .headers.diff + .src.diff) |
| fn_3_9497C | unrolled j-loop: target `(scene->unkIndex + J) + E758[i]` with lhz first; MWCC reassociates (.agent/attempts/fn_3_9497C.c) |
| fn_3_58F58 | 4 lines: mulli/slwi scratch regs r6/r7 swapped in lbl_3_data_4554[idx-2][col] lookup (.agent/attempts/fn_3_58F58.c + .headers.diff) |
| fn_3_F8878 | 2 lines: `stfs 0x14` (unk14 = 0.123f) lands after if/else instead of loop header; moving it reorders f30/f31 (.agent/attempts/fn_3_F8878.c + .headers.diff; header comment lists needed same-file edits) |
| fn_3_CBF80 | regalloc after `bl cos`: target cos in f1, 2.4f f0, 0.15f f2; one expression fuses to fmadds, every temp form swaps regs; 720 decl perms tried (.agent/attempts/fn_3_CBF80.c) |
| fn_3_1559E4 | all insns/regs match; only frame size: target 0xC0 with int->double slots at 0x98/0xA0/0xA8, ours 0xB0 (8 unexplained bytes after ctrl@0x50) (.agent/attempts/fn_3_1559E4.c + .headers.diff) |
| fn_3_103C30 | ~75/150 lines: stack layout of 36-byte by-value inline param + param addr caching (target recomputes addi) + camPos/camTarget load order (.agent/attempts/fn_3_103C30.c + .headers.diff) |
| fn_3_EF55C | ~38/150 lines: r27/r28 swap edge-table ptr vs sign counter + 6 component load/sub/store scheduling; 720 stmt perms tried. Real proto is u8 fn_3_EF55C(Vec*, u8) (EF55C_Arg is wrong) (.agent/attempts/fn_3_EF55C.c + .headers.diff) |

**Retry candidates** (new tips may fix): fn_3_B7CDC, fn_3_B7C2C (unsigned-compare workaround), fn_3_14DC80 (`bge`+`b` early exit), fn_3_90AB0 (index-in-local tip), fn_3_90B14 (regressed 7→13 lines after fn_800216F8 lost its prototype).
| fn_3_24EA0 | register allocation / scheduling (see git log) |
| fn_3_6BD6C | Register numbering of the 1/0 constants in the init block; loop matches. |
| fn_3_DF6D4 | Scheduling of the player-index/zero setup before the AI-strength loop. |
| fn_3_DFA20 | Model per-player arrays at 0x19D2/0x1A0F/0x1A13; register numbering differs. |
| fn_3_D9868 | Fix MiniGameStruct layout at 0x192B (odd-offset s16) and add fieldOrder[4]; remaining differences are register allocation. |
| fn_3_76A9C | Add BatterStatEntry runs/steals fields and a team[2] view of g_Scores; second loop's counter/pointer registers are swapped. |
| fn_3_6B870 | Inlined empty-base runner loop; i/pointer register swap remains. |
| fn_3_104B20 | Register swap only: x,y,z correctly map to pos.x/y/z but CW allocates them in f0,f2,f1 instead of f2,f1,f0; cannot be fixed from C |
| fn_3_5A6D4 | Register swap only: CW uses r5 as struct base pointer (addi r5,r4,@l) and r4 as temp for old gameStatus; current generates addi r4,r4,@l instead |
| fn_3_11897C | Register allocation mismatch: target uses lwzx+r8 for entries_68 array access, compiler generates add+lwz; register number differences (r8/r7 vs r0/r6) |
| fn_3_135600 | register allocation / scheduling (see git log) |
| fn_3_FF4C | Register swap only: Int1/Int2 loaded into r0/r3 instead of r3/r9; all arithmetic operations correct |
| fn_3_20AE0 | register allocation / scheduling (see git log) |
| fn_3_10F564 | Correct logic: (s8)_1A2C == -1 guard, lbl_3_data_228[0x10] != 0 check, store lbl_3_data_18910[GameMode_MiniGame] to _1A2C. 20/22 instructions match; only `li r3 |
| fn_3_142030 | CW processes r3 before r4 regardless of expression order; instruction count and formula are correct but register scheduling differs. Co-Authored-By: Claude Sonn |
| fn_3_909B0 | CW generates (stadiumID+0x27)*4 offset but struct field layout produces 0x9C+stadiumID*4 separately; matching requires treating lbl_800EF808 as flat void*[] fro |
| fn_3_CB344 | Epilogue restore order swapped (lwz r0/r31 order): CW scheduling artifact Co-Authored-By: Claude Sonnet 4.6 <noreply@anthropic.com> |
| fn_3_FCEB0 | register allocation / scheduling (see git log) |
| fn_3_11741C | register allocation / scheduling (see git log) |
| fn_3_6530 | register allocation / scheduling (see git log) |
| fn_3_90B14 | One extra li: target reuses the zero register for loadingState and the third fn_800216F8 argument. |
| fn_3_B27A4 | One scheduling swap (addi g_GameLogic vs li -1) in the prologue. |
| fn_3_112450 | Add flat players overlay for MiniGameStruct 0x18CC; both functions differ only in register numbering. |
| fn_3_58E50 | Add flat players overlay for MiniGameStruct 0x18CC; both functions differ only in register numbering. |
| fn_3_9056C | register allocation / scheduling (see git log) |
| fn_3_C0854 | Register numbering for the sound-id/-1 temporaries. |
| fn_3_D2684 | r29/r30 swap between the id-list pointer and the g_hugeAnimStruct base. |
| fn_3_E4658 | Register allocation of the 0.24f/0.0f constant loads before CTRLSetRotation. |
| fn_3_105ACC | Quaternion-to-matrix; float register allocation and frame size differ. |
| fn_3_14C3BC | Register numbering around the int-to-float conversion constants. |
| fn_3_1CAC0 | One commutative fmul operand swap in the FOV expression. |
| fn_3_88B18 | r7/r8 swap for the force-state variable. |
| fn_3_A1F3C | matched (stub fn_3_A46A0 given s32 idx param) |
| fn_3_B97DC | matched (ACTSetAnimation prototype gained the hidden f32 before time) |
| fn_3_16E1EC | Register allocation of the reset-condition terms and bss base pointer. |
| fn_3_D8A10 | scheduling of score-table loads; unrolled _1918 loop uses const offsets vs running pointer |
| fn_3_249E8 | register allocation of loop induction vars (r31/r30/r29) |
| fn_3_BD6AC | bge+b+bl branch direction — CW codegen, unfixable |
| fn_3_BD80C | bss/transRot base register split (r5+r30 vs r30 only) |
| fn_3_BF070 | stmw r27 vs 4 individual stw's |
| fn_3_BDE14 | register allocation: r25-r28+stmw vs r29-r31 individual stw |
| fn_3_BDCA4 | register allocation: CW assigns r6/r5 instead of r5/r4 → stfsx vs stfs |
| fn_3_107B9C | nonmatching |
| fn_3_107BD0 | nonmatching |
| fn_3_5A6A0 | nonmatching |
| fn_3_107C04 | nonmatching |
| fn_3_107D34 | nonmatching |
| fn_3_107988 | nonmatching |
| fn_3_EBFD4 | nonmatching |
| fn_3_107C40 | nonmatching |
| fn_3_107C88 | nonmatching |
| fn_3_8A5A4 | persistent register swap: `g_Runners` base in `r5` and `-1` in `r6`, target wants `r6`/`r5` |
| fn_3_7AEEC | CW running-pointer on bss struct (addi r6,r6,2 then +1) not reproducible from C struct field access |
| fn_3_7AF68 | same pattern as fn_3_7AEEC |
| fn_3_90220 | register allocation of the 8530/8168 table bases (now struct-typed, 7 diffs) |
| fn_3_99C88 | single remaining `rlwimi` form mismatch: current code emits equivalent `rlwimi r4, r0, 0, 0, 23` / `stw r4` instead of target `rlwimi r0, r4, 0, 24, 31` / `stw r0` |
| fn_3_FCE38 | branch-layout artifact in `rep_3090`: MWCC shortcuts the non-`bgt` path directly into the backward check instead of branching to the bottom `slwi` reset block first |
| fn_3_10C7A4 | register-allocation artifact in `gap_106DFC`: target wants `r29 = &g_Minigame` and `r28 = loop index`, current code keeps swapping base/index through an extra temp |
| fn_3_11741 | boolean materialization and register-allocation mismatch in `rep_3310`: current code stays on `or/not/rlwinm/extsh` with swapped base regs instead of target `subi/subfic/nor/srawi/andc` flow |
| fn_3_117494 | `rep_3310` setup/order mismatch: MWCC keeps `g_Minigame` live in `r3` too long, delays `r30 = &g_Minigame`, and lowers the `_CCC` guard through the wrong even/odd test shape |
| fn_3_E0758 | CW assigns rand-mod temp to r4 instead of r0, causing slwi/srwi register swap and preventing in-place rotlwi — unfixable from C |
| fn_3_E1964 | Same modulo register swap as E0758 + prologue counter/global init order mismatch (mr vs li) — CW scheduler artifacts |
| fn_3_E5924 | CW assigns loop counter to r5 instead of r4 in unrolled lbzu scan — volatile register swap |
| fn_3_6B5D8 | CW uses lbz r0 instead of destructive lbz r3 for lbl_80353A90 field load — volatile register swap |
| fn_3_DF608 | r4/r5 swap for g_d_GameSettings vs g_Minigame@ha init — cascades through whole function |

## Skipped
- minigamesSetSomePointers, minigamesSetSomePointers2: DOL code below 0x8006D024 has no splits yet; needs DOL split setup first.
