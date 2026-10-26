Extended Rep0B08Obj with byte controls at C0/C4/CA/CD/CE/CF and halfword B4, using existing scene object array.
Extended MenusSceneState with Rep1028Obj array at 21E0 (extent unknown); reused Rep1028Obj and added controls A8/B4.
New Gap3C03CObj (34 bytes), scene array at zero, signed byte 5 and flag 31.
New MenusSaveState for lbl_8034E9A0: pairs of time words at 46E8/46F0; reused MenusTimeState for clock source.
New MenusInputFlags: per-input bytes at D of lbl_803C66B0.
Gave up fn_2_145C: word-comparison loop matches operations, but first/second value registers swapped and feedback treats entry backedge as relocation; recursion adds call frame. Restored stub after 2 attempts.
New MenusVisibilityState with visibility bytes at 50; reused hugeAnimStruct/HugeAnimEntry2D94 for menus render state.
New MenusTransitionFlags and containing MenusTransitionState, flags at lbl_803CBBC2+2.
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
New opaque MenusAnimationAux; extended existing AnimationStruct with aux pointer8, preserving fieldC and size27C.
New MenusControllerInput (20 bytes), added controller-array union view to existing MenusInputState; Rep10C0State inputIndex signed byte197863.
New MenusResourceTables with table pointers at798, lbl_80366B18.
New MenusSceneFlags (bytes37/38) and opaque MenusSceneScript; extended MenusSaveState with scene pointer4748 and flag48AF.
New MenusDisplayPanel (1EA bytes) and MenusDisplayState panels at162657, based on paired flag accesses; Rep10C0State displayMode at1978FB.
New MenusTextBufferState: lengths401C, two 256-u16 source buffers4020 and output buffers4420.
Gave up fn_2_50D40 after 2 attempts: compiler folds sub-array bases and length index into address temporaries, unlike target separate bases/indexed halfword operations. Restored stub and removed unused buffer type.
New MenusExitState flag3E, lbl_803C5F04; extended MenusRuntimePreferences with mode byte0.
New MenusLoadingState, fields state30 and flag34; extended Rep10C0State with flags1972BC/1972C0 and halfword1976D6.
New MenusChoiceState (6 bytes), scene table3x3 at40B8.
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
Extended MenusResourceSlot with halfwords state4/bankC and inferred s16 fn_2_53BC8(MenusResourceSlot*) from caller/asm.
Gave up fn_2_512C0 during asm review: redundant control-code dispatch branches match known dead-branch patterns; retained stub.
Gave up fn_2_86EC after 2 attempts: li first argument vs opponent-byte load/address scheduling differs; restored stub. Rep0568State extent54 established by reset in7D44.
New Rep0B08AnimationConfig (6 bytes), animation0/time2/flag4 for data3C84; extended Rep10C0State with animations at197756.
Consolidated Menus16870State into Rep0568State: active14/counters1C/values46 overlap flags40; established total54.
New MenusRosterTransition (mode5/pendingE) and MenusRosterScripts (script blocksBAC/CCC/DCC).
Gave up fn_2_978 after3 attempts: four-case switch becomes compare tree rather than target jump table, including explicit empty cases and s32 local. Restored stub.
New MenusQueueState with pending47 at lbl_803C50E8; extended MenusTransitionConfig nextC8.
New MenusCameraConfig (18 bytes), two Vecs; reused in Rep10C0State camera197668 with enabled197855.
Gave up fn_2_1FF14 after1 attempt: typed controller held-field access keeps offset4 on lhz, whereas target keeps a shifted array base+4 for lhzx; inline pointer getter does not fix. Restored stub.
Gave up fn_2_1FFC4 during asm review: identical shifted-controller-array obstacle as1FF14; retained stub.
Consolidated Rep0788Item into existing MenusResourceSlot, adding signed index atE.
Gave up fn_2_90DE4 after5 attempts: negative-sine inline fixed zero-clamp copy; three remaining differences are amplitude/negative-sine f2/f3 allocation and fmuls operand order. Restored stub.
New MenusTeamSelections: signed first/second nine-byte arrays at2/B of lbl_803C6724.
New MenusResourceState, ten existing5100-byte banks and pending32A86, at lbl_2_bss_1A8230.
New MenusTransitionEntry (10 bytes) with next8; added array view to existing MenusTransitionConfig preserving named scalar offsets.
Gave up fn_2_7EF68 after4 attempts: split index web gets within6 register differences (first sum r4 vsr0); expression and inline getter reassociate index additions and shift all scratch regs. Restored stub.
Gave up fn_2_73BF0 after1 attempt: target duplicated return54 branch is folded, with additional tail arithmetic/register differences. Restored stub.
New ChallengeLineupEntry (6 bytes), signed value3; extended existing ChallengeSaveData with nine entries at40B8 for menus comparison helper.
New opaque MenusSceneArchive via tagged pointer; extended MenusResourceTables with archive7A8.
New MenusSelectionPair (8 bytes) for value-copy of MenusGameChoiceState selections at10; repeatFlags at Rep0568State10.
Gave up fn_2_12B60 after3 attempts: pointer induction is hoisted before initial condition, and saved registers differ; restored stub and removed unused pair/repeat layouts and tentative callee signatures.
Gave up fn_2_8DC00 during asm review: allocates runtime-sized aligned per-animation aux chunks, requiring raw byte slicing/casting to assign opaque aux pointers; no field-only typed representation identified. Stub retained.
Gave up fn_2_79688 after1 attempt: same index-add web vs temporary-register obstacle as7EF68, plus unrolled iteration constants left separate. Stub restored.
Correction: fn_2_4E970 already had a matched BOOL prototype/body; no return-zero placeholder was introduced.
Correction: fn_2_53BC8 returns s32, with caller explicitly checking its low s16 before storing; prototype and typed stub reflect that.
Revisited fn_2_442E8: new flat nine-entry s16[3] table view and plain9-loop unrolling matched44368, unlike prior nested3x3-record approach.
Revisited fn_2_95E80 with existing matched __cntlzw predicate pattern discovered in nearby helpers; remaining attempt budget2.
New MenusSequenceConfig (6 bytes): group0/song2/resource4 for lbl_2_data_128; reused sequence handle and selection arrays.
Gave up fn_2_14BB8 after5 attempts: case0 needs an extra saved byte-index register and mr before flag store; local and inline forms coalesce with parameter or repeat truncation. Restored stub.
New MenusLineupChoice (6 bytes), byte2/flag3 for lbl_800E8558; MenusLineupSlot (A bytes), signed id0, ten entries per lbl_80109AE8 row.
Gave up fn_2_49F7C after3 attempts: explicit setup/copy labels match all target instructions, but MWCC emits trailing blr assigned by target to next4-byte fn_2_4A064; symbol-size fix is outside scope. Restored stub.
Gave up fn_2_50B0C after4 attempts: otherwise identical instructions, but converted value r10 vsr7 shifts global base/zero/load temps; locals, two-step cast and inline helper unchanged. Restored stub and unused fields.
Gave up fn_2_698EC after5 attempts: negative-sine inline reduces to3 differences, same fneg/amplitude f2/f3 swap as90DE4; extern amplitude worsens scheduling. Restored stub and unused phase field.
Gave up fn_2_A1A0 after1 attempt: control-flow and hoisted globals agree, but team/index address web allocates r10/r11 vsr11/r12 and computes index+2 inside each branch, unlike target shared displacement. Restored stub and unused fields.
New MenusAnimationResource (10 bytes), resource0/size4 with packed size flags for lbl_2_data_2F990; reused hugeAnimStruct allocation fields and animation slots.
New MenusSortEntry (8 bytes), signed key0/value4; fn_2_44414 sorts54 entries using element0 as a sentinel.
New MenusAnimationTask union reuses QueueEntry with byte current1C/state1D; Rep0568State now names write/read indices0/1 and ten command bytes2.
Gave up fn_2_51470 after2 attempts: every target instruction matches with s32 return, code-before-pointer declaration and unsigned shift; extra trailing blr belongs to next4-byte fn_2_51568. Config size fix is outside scope; restored stub.
Gave up fn_2_6B024 after1 attempt: same negative-sine/amplitude f2/f3 allocation obstacle as698EC/90DE4 (4 remaining diffs), despite inlined bounce and sine helpers. Restored stub/unused phase.
Gave up fn_2_6784 after4 attempts: struct-member table base folds +C into lbz instead of target relocation addend; explicit pointer hoists into extra saved register. Also first-save readiness store reuses r31 instead of reloading global. Restored stub and unused types.
New MenusExitTransition: state halfword10/step18 at lbl_2_bss_340234; extended MenusQueueState with active byte0.
Gave up fn_2_4906C after 5 attempts: source index+1 is hoisted into separate unrolled offsets/lwzx, adding saved registers; pointer/struct/inline forms do not reproduce target add+lwz. Stub restored.
New MenusResourceLoads: six CompressedDiskRead mode descriptors at offset3D4 of lbl_2_data_12EA8, reusing the existing disk descriptor type.
Gave up fn_2_432EC after 5 attempts: direct tables reproduce instructions with saved-register permutation; explicit bases fix some saved regs but reassociate table offsets and reorder comparisons. Stub restored.
Gave up fn_2_6B120 during asm review: repeats negative-sine/amplitude f2/f3 allocation obstacle documented for 6B024/698EC/90DE4; retained stub.
Gave up fn_2_450E4 after 5 attempts: all instructions match except six cmpw operand orders in unrolled child-choice checks; swapping expressions, casts and int/s8 locals failed. Stub restored and unused fields removed.
Gave up fn_2_54890 after 5 attempts: transition loads/stores schedule differently; resource loop unrolls or retains counter instead of target 43-iteration CTR loop. Stub restored.
Gave up fn_2_6B4FC during asm review: repeats documented negative-sine/amplitude f2/f3 allocation obstacle from 6B024/6B120; retained stub.
Gave up fn_2_6B620 during asm review: repeats documented negative-sine/amplitude f2/f3 allocation obstacle from 6B024/6B120; retained stub.
Gave up fn_2_42FC8 after 5 attempts: all operations agree, but three loop-pointer registers permute (choice/object offset/team); explicit pointer induction adds an mr and changes scheduling. Stub restored.
Gave up fn_2_74E14 after 5 attempts: constant-first index sums fixed base folding, but row and byte-side saved registers remain swapped; explicit side local shifts all saved values. Stub restored.
Gave up fn_2_477C0 during asm review: dynamically aligned per-animation aux chunks require byte slicing, like documented 8DC00; no field-only typed layout identified. Stub retained.
Gave up fn_2_95FE0 after 5 attempts: all instructions agree except li total=1 scheduled before argument constants instead of after; post-call init, comma expression and inline out-parameter helper failed. Stub restored.
New MenusRenderAnimation (90 bytes) embeds ActRelatedSub, with visibility byte6C; MenusRenderList has count0 and these entries at34.
Gave up fn_2_348C after 4 attempts (matched later, decomp_knowledge.md §13): nested loops and byte stores reproduce target unrolling, but team/boolean temps and five induction/base registers allocate differently. Stub restored and unused flag array removed.
Gave up fn_2_190DC after 5 attempts: all operations agree but input-list and animation-entry saved registers r28/r29 are swapped; declaration ordering and explicit global pointer unchanged. Stub restored and unused fields/prototypes removed.
Gave up fn_2_1C0D4 after 2 attempts: save-global pointer is sunk until after memset instead of anchored in r31 before call; direct and inline initializer forms differ in scheduling. Stub restored and unused fields removed.
New MenusChoiceConfig (1C bytes), group0/level1; replaced Gap3C03CObj initial padding with its config pointer.
Gave up fn_2_5184 after 3 attempts: explicit cached pointers restore saved-register count, but prologue scheduling and shifted team-row address bases differ throughout. Stub restored and unused fields removed.
New MenusProjectionState at lbl_2_bss_1010C: state30/step32/value38/target3C/position48/flags54.
Gave up fn_2_45204 after 5 attempts: nested unsigned counting loop matches target lhau unrolling, but outer index/choice r30/r31 swapped; explicit pointer fixes registers but adds prologue mr. Stub restored.
Gave up fn_2_466AC after 3 attempts: declaration ordering fixes value registers, leaving7 differences in choice/object-offset/team pointer permutation, same obstacle as42FC8; direct team access drops required saved pointer. Stub restored.
Gave up fn_2_80E0C after 5 attempts: total+=4 fixes saved registers, leaving only li total=2 / li third argument20 scheduling swapped; post-call total initialization is late. Stub restored.
- fn_2_1B1BC: ASM review deferred resource-relative pointer fixup; no compliant typed relocation idiom identified, stub retained.
- fn_2_8B2C0: ASM review deferred twelve relative resource pointer fixups; shared HugeAnimStruct slots require a typed relocation view, stub retained.
- New structs MenusSavedRoster / MenusSavedRosters in gap_4B1AC.h: persisted roster records, stride 0x4508, enabled byte 0x1606 and alternate flag 0x441B.
- fn_2_EAE0: two candidates retain selection-offset induction register and three saved registers versus target five; infinite controller loop register allocation differs substantially, stub restored and unused fields removed.
