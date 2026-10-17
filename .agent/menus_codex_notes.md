Extended Rep0B08Obj with byte controls at C0/C4/CA/CD/CE/CF and halfword B4, using existing scene object array.
Extended MenusSceneState with Rep1028Obj array at 21E0 (extent unknown); reused Rep1028Obj and added controls A8/B4.
New Gap3C03CObj (34 bytes), scene array at zero, signed byte 5 and flag 31.
New MenusSaveState for lbl_8034E9A0: pairs of time words at 46E8/46F0; reused MenusTimeState for clock source.
New MenusInputFlags: per-input bytes at D of lbl_803C66B0.
Gave up fn_2_145C: word-comparison loop matches operations, but first/second value registers swapped and feedback treats entry backedge as relocation; recursion adds call frame. Restored stub after 2 attempts.
New MenusVisibilityState with visibility bytes at 50; reused hugeAnimStruct/HugeAnimEntry2D94 for menus render state.
New MenusTransitionFlags and containing MenusTransitionState, flags at lbl_803CBBC2+2.
Gave up fn_2_72A58: MWCC folds flags subobject +2 into each field instead of target symbol+2 base; restored stub and removed unused transition types.
New MenusControllerState (1F), MenusPreferences (6/7/8), MenusRuntimePreferences (25) for preference-copy helpers; reused Lbl800EF808.
Gave up fn_2_19520 after 4 attempts: identical instructions except destination lis scheduled before controller addi. Restored stub.
Gave up fn_2_19778 after 1 attempt: same destination-lis scheduling difference as 19520; restored stub and removed unused MenusPreferences.
New MenusSystemState at lbl_803297E0, mode byte CD5F; inferred fn_2_2FC0(u8,s32,s32).
Corrected MenusSystemState.mode offset to CF5F from target addis +1 / lbz -30A1.
Extended existing QueueEntry with halfwords 1A/1C; new MenusResourceEntry (10 bytes) for fn_2_54354 source tables, and inferred pointer/count prototype.
New MenusCommandQueue with byte indices 15/16 and 32 commands at 17.
New MenusChoiceRecord (A bytes) with choice at3, scene array at40F0; Gap3C03CObj.unk31 is signed.
New MenusDisplayConfig for 8-byte entries indexed by lbl_803CBBC0; existing DOL BdcArrayElement prototype requires a typed pointer cast.
Gave up fn_2_1258 during asm review: generic byte-offset load dispatch for 1/2/4-byte values needs an untyped byte-offset interface; retained stub.
New MenusPreferences pending byte F at lbl_2_bss_1033C for scene-removal helper.
Gave up fn_2_10AC during asm review: self-relative pointer fixups require interpreting binary offsets; no compliant typed field-only implementation identified. Stub retained.
New MenusSceneTransition (state 0/current8/previous9) and MenusTransitionConfig (next58) for scene enqueue wrapper.
Gave up fn_2_35D0 after 3 attempts: byte-index register/base ordering and lbzu vs lbz+addi remain; restored stub.
Gave up fn_2_79634 after 2 attempts: flag address kept in separate temporary, emits addi/lbz instead of lbzu; restored stub.
New opaque MenusSceneAsset declaration for external resource passed to fn_8001CB10; no fields inferred.
New Rep0568State: count2D and per-animation flags40; reused AnimationStruct/AnimationStructPtrs.
New MenusCompletionState, 5 rows of 4 bytes at C6 and allCompleted F4.
Gave up fn_2_14F8 after 3 attempts: min/RNG/range scratch register assignment and scheduling differ; branch fixed with <=. Restored stub.
New MenusSoundState with current voice ID at0, lbl_2_data_134.
New MenusEffectState: type word0; used through lbl_2_data_13374 and fn_80031CA4(Vec*,MenusEffectState*).
New opaque MenusLight type; added typed menuLights[4] union view to existing hugeAnimStruct AC/B0/B4/B8 slots.
New MenusPanelState (1E90 bytes), reused in Rep10C0State at19542C with mode at1972B8.
New MenusRosterState with side F4; extended MenusSaveState with player words46E0/46E4 and declared 6-byte roster table rows.
Gave up fn_2_7302C after 1 attempt: compiler uses CTR loop and different roster/player scratch regs; target compares index against computed count. Stub restored, unused roster type removed.
New MenusLightMatrixState: Mtx at14, lbl_2_bss_10164; reused MenusLight and hugeAnimStruct.menuLights.
New MenusLoadingState with state halfword30 at lbl_2_bss_1A823C; extended existing scene with byte4420.
New MenusPlayerInput (6 bytes), used at MenusSaveState472C for controller-button words.
Gave up fn_2_16F0C during asm review: needs reconciliation of hugeAnimStruct header slot at140 and nine following D4 actor records; retained stub.
Gave up fn_2_93BF8 after 3 attempts: scene-base address/lwz/addis uses r3 instead of target r4 while preserving argument in r31. Restored stub.
New opaque MenusAnimationAux; extended existing AnimationStruct with aux pointer8, preserving fieldC and size27C.
New MenusControllerInput (20 bytes), added controller-array union view to existing MenusInputState; Rep10C0State inputIndex signed byte197863.
New MenusResourceTables with table pointers at798, lbl_80366B18.
New MenusSceneFlags (bytes37/38) and opaque MenusSceneScript; extended MenusSaveState with scene pointer4748 and flag48AF.
New MenusDisplayPanel (1EA bytes) and MenusDisplayState panels at162657, based on paired flag accesses; Rep10C0State displayMode at1978FB.
New MenusTextBufferState: lengths401C, two 256-u16 source buffers4020 and output buffers4420.
Gave up fn_2_50D40 after 2 attempts: compiler folds sub-array bases and length index into address temporaries, unlike target separate bases/indexed halfword operations. Restored stub and removed unused buffer type.
Gave up fn_2_729E0 during asm review: same lbl_803CBBC2+2 subobject base folding issue established by fn_2_72A58; retained stub.
Gave up fn_2_72DDC during asm review: same lbl_803CBBC2+2 subobject base folding issue established by fn_2_72A58; retained stub.
Gave up fn_2_728C0 during asm review: same lbl_803CBBC2+2 subobject base folding issue established by fn_2_72A58; retained stub.
Gave up fn_2_72D60 during asm review: same lbl_803CBBC2+2 subobject base folding issue established by fn_2_72A58; retained stub.
New MenusExitState flag3E, lbl_803C5F04; extended MenusRuntimePreferences with mode byte0.
New MenusLoadingState, fields state30 and flag34; extended Rep10C0State with flags1972BC/1972C0 and halfword1976D6.
New MenusChoiceState (6 bytes), scene table3x3 at40B8.
Gave up fn_2_442E8 after 2 attempts: target advances scene base by12h with dead counter+=2; C table indexing keeps separate index and base. Restored stub and removed unused MenusChoiceState.
New MenusTextBufferState for word arrays0/8/10 at55E8; extended MenusPanelState with word array80 and QueueEntry unsigned halfword10 alias.
Gave up fn_2_5135C after 1 attempt: global/sub-array address folding and scratch register allocation differ throughout; restored stub and removed unused declarations.
New Rep1028Config (14 bytes), Vec0/valueC; reused for data369C and data3198 initialization tables.
Gave up fn_2_513E8 after 2 attempts: control-code widths need different truncation/branch merging and scratch regs; restored stub.
New MenusResourceSlot (18 bytes) and MenusResourceBank (5100 bytes); reused MenusDisplayState with 70 banks before panel flags.
New MenusRosterState modeF6 and MenusGameChoiceState selection50; inferred fn_2_8A008(DrawingSceneStruct*).
Extended MenusVisibilityState with values[8] at30..4C; reused existing ActRelatedEntry/ActRelatedSub view for seven setup helpers, including known adjacent sub-record floats at5C/60.
New MenusMenuBuffer with4000-byte data; extended Rep10C0State buffer pointer197684 and reset words19768C/690/694.
Gave up fn_2_4A0C4 during asm review: entry backedge uses the same global relocation normalization issue as fn_2_145C, while recursion introduces a call frame. Stub retained.
Gave up fn_2_75B58 after 3 attempts: only scheduling of li30 / total++ / final index addi remains after splitting index web and reordering locals; restored stub.
Rep1028Obj scene array extent established as29 by fn_2_904A8 init loop; extended object fields38/3C/7C/80/84/92/94/AA/AC/AD/AE/B2 without changing BC stride.
Inferred s32 return for fn_2_4E970 from matched caller1B52C; kept typed return-zero placeholder.
Gave up fn_2_83744 during asm review: lbl_803CBCD0+8 is the same subobject-base folding obstacle as72A58; retained stub.
Correction: fn_2_4E970 already had a matched BOOL prototype/body; no return-zero placeholder was introduced.
Extended MenusResourceSlot with halfwords state4/bankC and inferred s16 fn_2_53BC8(MenusResourceSlot*) from caller/asm.
Correction: fn_2_53BC8 returns s32, with caller explicitly checking its low s16 before storing; prototype and typed stub reflect that.
Gave up fn_2_512C0 during asm review: redundant control-code dispatch branches match known dead-branch patterns; retained stub.
Gave up fn_2_86EC after 2 attempts: li first argument vs opponent-byte load/address scheduling differs; restored stub. Rep0568State extent54 established by reset in7D44.
