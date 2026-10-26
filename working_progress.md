# Working Progress

## Current Focus
**Source of truth:** Always follow `queue.log`. If this file disagrees with `queue.log`, `queue.log` wins.
**Strategy:** Work through functions listed in `queue.log` (plain entries at the bottom, after all COMPLETED/NONMATCHING lines)
**Queue file:** `queue.log`
**Next function to attempt:** queue is empty; continue smallest never-attempted (score_functions.py filtered against queue.log + this file's tables). Next up: fn_3_BC54, fn_3_3D6AC, fn_3_3F124, fn_3_7EBD4. 2026-10-16 solo batches: 25/30, 45/50 (+ fn_3_12F9D4 fixed), 4/4.

To find the next function: look for the first plain entry (not prefixed with COMPLETED/NONMATCHING/SKIPPED) in `queue.log` that hasn't been committed yet.

---

## Recently Completed (from queue.log)
| Function | Notes |
|---|---|
| fn_3_B3A4C | matched |
| fn_3_3CB8C | matched |
| fn_3_2A164 | matched |
| fn_3_B6320 | matched |
| fn_3_9E84 | matched |
| fn_3_B2630 | matched |
| fn_3_45860 | matched |
| fn_3_3E34C | matched |
| fn_3_1FF48 | matched |
| fn_3_13F6C8 | matched |
| fn_3_7FD90 | matched |
| fn_3_1DC30 | matched |
| fn_3_12FD6C | matched |
| fn_3_DE4FC | matched |
| fn_3_AEFF8 | matched |
| fn_3_B6F6C | matched |
| fn_3_871BC | matched |
| fn_3_870AC | matched |
| fn_3_85744 | matched |
| fn_3_82F80 | matched |
| fn_3_27764 | matched |
| fn_3_E2F4C | matched |
| fn_3_7CE90 | matched |
| fn_3_1179EC | matched |
| fn_3_113950 | matched |
| fn_3_B1CB0 | matched |
| fn_3_89028 | matched |
| fn_3_35D28 | matched |
| fn_3_6A160 | matched |
| fn_3_3F034 | matched |
| fn_3_39DC4 | matched |
| fn_3_11D2C8 | matched |
| fn_3_13F7E4 | matched |
| fn_3_135520 | matched |
| fn_3_97800 | matched |
| fn_3_81AEC | matched |
| fn_3_10AE18 | matched |
| fn_3_B6E98 | matched |
| fn_3_1DB5C | matched |
| fn_3_B60F0 | matched |
| fn_3_A020 | matched |
| fn_3_10AD48 | matched |
| fn_3_810C4 | matched |
| fn_3_5D51C | matched |
| fn_3_FD5A8 | matched |
| fn_3_145AD0 | matched |
| fn_3_6D4A0 | matched |
| fn_3_13DDE0 | matched |
| fn_3_13BB30 | matched (inlined target-speed init) |
| fn_3_CB7E8 | matched |
| fn_3_8A4E4 | matched |
| fn_3_2DCF4 | matched |
| fn_3_30564 | matched |
| fn_3_2C238 | matched |
| fn_3_14A4 | matched (cubic spline eval) |
| fn_3_483CC | matched |
| fn_3_706B8 | matched |
| fn_3_754B8 | matched |
| fn_3_115AB4 | matched |
| fn_3_17760 | matched |
| fn_3_20E50 | matched |
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
| fn_3_55CC4 | Codex attempt; 15 lines off, mostly r4/r5 swaps around g_FieldingLogic.unkF4 stores |
| fn_3_70768 | final interpolation: target computes z-prevZ into f4 first and uses non-fused fmuls+fadds; only FP register assignment differs (6 lines) |
| fn_3_7D2E0 | CW hoists g_Stats.unk40 load above replay-frame stores (target reloads after); inline-helper and indexing variants didn't block it |
| fn_3_11881C | register allocation / scheduling (see git log) |
| fn_3_1354BC | CW register allocation: uses f4 for diff1 and f1 for diff2, generating different fsubs destinations (f4/f1 vs f1/f2); li r3,0 placement also differs — unfixable |
| fn_3_117588 | register allocation / scheduling (see git log) |
| fn_3_A32B8 | nested-struct field load folded to single lwz |
| fn_3_141A30 | regalloc only; jump table lives in rep_36D8 .data (split fix needed) |
| fn_3_ED058 | scene pointer loaded into temp then mr r3 |
| fn_3_FF98 | regalloc only (0 diffs ignoring registers) |
| fn_3_119EE0, fn_3_119E30 | 0x34 offset folded into lwzx index |
| fn_3_8B094 | offset-indexed vs pointer form for table entry |
| fn_3_14E894 | 9 lines: zero init `li r30,0; mr r31,r30` vs separate `li r31,0`, plus a node/want register swap (attempt: .agent/attempts/fn_3_14E894.c) |
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
| fn_3_1573AC | same-file static data off one base (&lbl_3_data_266A8 in r31 across calls) — known unfixable (.agent/attempts/fn_3_1573AC.c + .headers.diff) |
| fn_3_169600 | 9 lines: target keeps non-propagated copy `mr r30,r29` of outer loop counter for first nested loop; all forms copy-propagated (.agent/attempts/fn_3_169600.c + .headers.diff) |
| fn_3_15F648 | same base-reg pattern as fn_3_1573AC (addi r3,r30,0x148; lwz 4(r3)) plus colour build clrlslwi/rlwimi diffs (.agent/attempts/fn_3_15F648.c + .headers.diff) |
| fn_3_CD968 | corner-setup float block: freg numbering and w*0.5 fmuls operand order (.agent/attempts/fn_3_CD968.c) |
| fn_3_E3044 | 2 small diffs: lbz before `mr r31`, deg->rad load order (.agent/attempts/fn_3_E3044.c + .headers.diff) |
| fn_3_7AFE4 | 4 lines: lis/addi pairing of g_Scores vs g_GameLogic; needs the fn_3_7AEEC loop as an inline copy (attempt: .agent/attempts/fn_3_7AFE4.c) |
| fn_3_6FA28 | 24 lines: second g_Ball base and stadium-table index registers, constant load order (attempt: .agent/attempts/fn_3_6FA28.c) |
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
| fn_3_103C30 | ~75/150 lines: stack layout of 36-byte by-value inline param + param addr caching (target recomputes addi) + camPos/camTarget load order (.agent/attempts/fn_3_103C30.c + .headers.diff) |
| fn_3_EF55C | ~38/150 lines: r27/r28 swap edge-table ptr vs sign counter + 6 component load/sub/store scheduling; 720 stmt perms tried. Real proto is u8 fn_3_EF55C(Vec*, u8) (EF55C_Arg is wrong) (.agent/attempts/fn_3_EF55C.c + .headers.diff) |

**Retry candidates** (new tips may fix): none left from the 2026-10-16 list (fn_3_B7CDC, fn_3_B7C2C, fn_3_14DC80, fn_3_90AB0 and fn_3_90B14 all match now).
| fn_3_6BD6C | 16 lines with `s32 i; s32 team; hugeAnimStruct* has;` and the `has` local after the unk9B store; left: constants 1/0 in r5/r7 swapped (all 4 store orders tried) and the epilogue `lwz r31` interleaved with the `!= 0` tail |
| fn_3_DF6D4 | 21 lines: target shares one `li r0,0` between the unrolled `player != 0` compare and `_19DA[player] = 0`, ours emits two; post-loop constant-1 stores allocate differently (attempt: .agent/attempts/fn_3_DF6D4.c) |
| fn_3_D9868 | 37 lines: two g_Minigame anchors and loop-counter registers swapped; declaration brute force and for-loop forms no help (attempt: .agent/attempts/fn_3_D9868.c; the MiniGameStruct 0x192B s16 and fieldOrder[4] layout fixes are in) |
| fn_3_6B870 | inlined unloadEmptyBaseRunners loop: i in r30 and the &runnerOnBase walker in r31, target reversed; an explicit s16* walker gets r30 but folds the offset as 0x8 instead of 0x2+0x6; do-while, s16 i, `<= 3`, base local, struct-pointer param tried |
| fn_3_11897C | Register allocation mismatch: target uses lwzx+r8 for entries_68 array access, compiler generates add+lwz; register number differences (r8/r7 vs r0/r6) |
| fn_3_135600 | register allocation / scheduling (see git log) |
| fn_3_20AE0 | first rodata float address materialized via addi, load deferred. gap_20A60 merged into rep_8C8.c (2026-10-16) so constants are now same-TU literals; still mismatches in every literal/decl-order/helper form |
| fn_3_142030 | CW processes r3 before r4 regardless of expression order; instruction count and formula are correct but register scheduling differs. Co-Authored-By: Claude Sonn |
| fn_3_FCEB0 | register allocation / scheduling (see git log) |
| fn_3_11741C | target computes state as `nor; srawi; andc r6,r0(=2),r3`; every `2 & ~(~(a|b) >> 31)` spelling (s16/s32/u32 state, separate mask locals) gives or+nor or nor+rlwinm; a ternary gives another idiom |
| fn_3_B27A4 | 3 lines after adding the g_GameLogic._140[1]/[0] stores and dropping two dead stores: only `addi r3,g_GameLogic@l` is scheduled before `li r0,-1` and the first sth (attempt: .agent/attempts/fn_3_B27A4.c) |
| fn_3_9056C | 2 lines: `addi r4,r30,0x1c4` scheduled before `slwi r0,r28,1`; pointer `+=` forms give the unfolded bases, dropping the seq local fixed the stores (attempt: .agent/attempts/fn_3_9056C.c) |
| fn_3_C0854 | sound-id local in r5; target keeps it in r0 with store temps in r4/r5 (`slwi r4; li r5,-1; li r0,0x18; sthx; beq; li r0,0x17; clrlwi r3,r0`). Tried every int width, block scope, declaration and store order, ternary and if/else (both go branchless); u8 drops the clrlwi |
| fn_3_E4658 | Register allocation of the 0.24f/0.0f constant loads before CTRLSetRotation. |
| fn_3_105ACC | Quaternion-to-matrix; float register allocation and frame size differ. |
| fn_3_16E1EC | snapshot stores need a separate `addi r7,r31,0x10` sub-base (same-file static lbl_3_bss_D6F0 addressed off the D6E0 overlay) and an extra `neg` before `cntlzw` on the NULL test; local bss/snapshot pointers all fold into r31 displacements (same class as fn_3_BD80C) |
| fn_3_D8A10 | 6 lines: the j loop over mg->_1918/_1914 lacks the target's walker (`lbz 0x1919(r3); addi r3,r3,1`); i reuse, do/while, u8..s16 j, direct g_Minigame (walker but off r3, not r31), inline helpers, u8* walkers tried. Head fixed by an `s16 c = unk4C` local (attempt: .agent/attempts/fn_3_D8A10.c) |
| fn_3_BD80C | target keeps &lbl_3_common_bss_35154 in r5 plus a separate `addi r30,r5,0x3e4` sub-object pointer; MWCC folds 0x3e4 into every displacement whatever local/global form (same-file static off one base, decomp_knowledge.md §1 Known Unfixable) |
| fn_3_BF070 | 53 lines: target keeps &lbl_3_data_111A8 (r30) and &g_d_GameSettings (r31) in saved registers across the two calls (stmw r27); pointer locals change nothing. Inlined by fn_3_BF6C0 |
| fn_3_90220 | 14 lines: argument evaluation order (lhzx, lbzx to r0, add, lbz pan, mr r4) not reproduced by any local or pointer order (attempt: .agent/attempts/fn_3_90220.c) |
| fn_3_FCE38 | 13 lines: two index-based while loops; the target has one IV-reset block at the end reached from both forward-loop exits (an MWCC preheader, as in fn_3_FCEB0, .agent/easy_wins_notes.md), plus a p/IV swap (attempt: .agent/attempts/fn_3_FCE38.c) |
| fn_3_117494 | `rep_3310` setup/order mismatch: MWCC keeps `g_Minigame` live in `r3` too long, delays `r30 = &g_Minigame`, and lowers the `_CCC` guard through the wrong even/odd test shape |
| fn_3_E1964 | target induction init `li r29,0; mr r27,r29` (byte-offset IV copied from i); every loop form, dual counter, u8..u32 i and byte-offset cast emits two `li` with i/IV swapped (decomp_knowledge.md §11 negative results). `rand() % 4096` matches the tail (attempt: .agent/attempts/fn_3_E1964.c) |
| fn_3_DF608 | 10 lines: r4/r5 swap for g_d_GameSettings vs g_Minigame@ha in the prologue, same zero/lis-order family as fn_3_DF6D4 (attempt: .agent/attempts/fn_3_DF608.c) |

## Skipped
- minigamesSetSomePointers, minigamesSetSomePointers2: DOL code below 0x8006D024 has no splits yet; needs DOL split setup first.
