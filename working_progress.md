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
| fn_3_A1F3C | r3/r4 swap for the runner index. |
| fn_3_B97DC | ACTSetAnimation's time argument arrives in f2 in the target; the C3 prototype only has one float parameter. |
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
