Introduced ChallengeResource (opaque) and ChallengeResources in rep_02A8.h, extending the existing resource-pointer layout at lbl_800EF808 through offset 0x38C.
Introduced ChallengeResetFlags in gap_85A8.h: count at 0, ten flag bytes at 2, active at 0xC.
ChallengeResetFlags refined to an 11-byte flag view at 2 overlapping active at 0xC: target clears indices 10 through 1, then clears active again.
fn_1_15CC: skipped after asm review; stored resource-relative texture pointer needs excluded relocation arithmetic, as in other modules; stub retained.
Introduced ChallengeFog in rep_0138.h: color/type union at 0/3, start/end at 4/8.
Introduced ChallengeSelection (state3, pending5, choices6..9) and Rep74A0Globals (heap8) in rep_74A0.h.
fn_1_1D514: two attempts sink the selection base until after the first call, losing target r31 anchor; restored stub and removed unused ChallengeSelection/Rep74A0Globals types.
Introduced ChallengeView (stride0x38, matrix8) and ChallengeViewState (matrix0x58) in rep_0610.h.
Introduced ChallengeAnimation (time0/dataC), ChallengeModelObject (animationE8), ChallengeModel (count6/objects18) in rep_0610.h.
Introduced Gap1538View (0x18 bytes) and Gap1538Resources (seven disk descriptors, two views at0x70, width/heightA0/A4) in gap_1538.h.
fn_1_1538: first candidate rematerializes resource base across call and folds view displacement into field offsets; restored stub and removed unused Gap1538View/Gap1538Resources.
Introduced ChallengeRenderModel (opaque), ChallengeRenderObject (model14/children74/worldEC/next100), ChallengeRenderTask (object0/callback8) in rep_74A0.h.
fn_1_CC24: out-parameter inline attempt still folds nested items base0x3748 into loads374C/3750; retained preexisting compiling implementation.
fn_1_168C8: asm review shows identical callback stores on both sides of an otherwise unused animation-aux test; optimizer likely merges branches; left stub.
Introduced ChallengeScriptEntry (stride2C), ChallengeScript (1C), ChallengeScriptContext (data30), ChallengeScriptGlobals (bounds0/default120/choices124/context1B4/scripts62C) in rep_7BF0.h.
fn_1_28C34: one candidate folds scripts/context member bases into loads and merges the leading non-null branch; restored stub.
ChallengeScriptGlobals retained only bounds0/mode34 for matched fn_1_2935C; removed unused ChallengeScriptEntry/ChallengeScript/ChallengeScriptContext and trailing global fields.
fn_1_4DD8: asm review shows stored relative resource offsets converted in place; excluded relocation arithmetic, stub retained.
Introduced ChallengeLightPosition (Vec plus w, stride0x10) in rep_74A0.h, and extended Rep74A0State with view matrix at0x10.
fn_1_1B038: five attempts; best differs only in r30/r31 constant-base registers on two lfs instructions, explicit pointers reorder prologue; stub restored and unused ChallengeLightPosition removed.
Introduced ChallengeSortNode (next0/sortKeyC) in gap_17EFC.h; extended existing Gap17EFCEntry with node0.
fn_1_20 and fn_1_E8: asm review shows identical resource-relative pointer fixups; excluded relocation arithmetic, both stubs retained.
Introduced ChallengeModelGroup (count6) and ChallengeSelection (selected0/group2/matrix18C) in rep_74A0.h.
Introduced ChallengeOrbit (position10) and ChallengeOrbitConfig (radius4) in rep_74A0.h.
Introduced ChallengeAxes (six controller bytes) in challenge.h; extended ChallengeInput with axes at0x10 and ChallengeScene with parentC/flags34/choice36/cursor37.
fn_1_28118: asm review shows stored texture-relative pointer relocation; stub retained under offset-arithmetic restriction.
Introduced ChallengeLayoutPosition (signed x/y14/16), ChallengeLayoutConfig (ID14) in rep_0250.h.
Introduced ChallengeLayoutState in rep_0250.h (selected2/mode7/previous11).
Introduced ChallengeAnimChoice (four signed halfwords, stride8) in rep_0610.h at lbl_1_bss_3218.
fn_1_26C2C: two inline initializer candidates retain different zero/one constant bases and fold bitfield-byte base11 into accesses; stub restored, unused Anim extension removed.
Introduced ChallengeScript (0x1C bytes, kind8/enabled14) in rep_7A28.h; extended shared ChallengeScene union with integer words and float values2C/30 for camera editor setup.
Moved ChallengeScript to challenge.h, refined named fields, introduced opaque ChallengeScriptData and ChallengeScriptEntry (stride2C, data4); extended ChallengeScriptGlobals selection38/pending39.
Introduced ChallengeChoiceSource (stride8), ChallengeChoiceRecord (stride50), ChallengeChoiceRecords (records4), ChallengeAnimDuration (time0), ChallengeAnimMetadata (strideC,duration4) in rep_0610.h.
fn_1_D7A4: first typed choice-array candidate uses base+50 with fields0 instead of target base+40 with fields10, and fails to hoist animation selection; stub restored and unused choice-source/metadata types removed.
fn_1_717C: asm review shows repeated resource-base plus stored byte-offset conversions; excluded relocation arithmetic, stub retained.
Introduced ChallengeTiming (time0/end4) in rep_0610.h; extended ChallengeViewState with angle50.
fn_1_10458: four attempts; best differs only in add r3,r4,r3 versus target add r3,r3,r4; split temporaries change global-base allocation; stub restored and unused busy field removed.
Introduced ChallengeTileImage in gap_1D590.h: data0, height8, widthA.
fn_1_1D590: three attempts; index products recover target mr induction initialization, but tile/row offset/destination-y registers remain permuted and tile/counter updates swap; restored stub and unused ChallengeTileImage.
Introduced ChallengeCopyValues (0x10 bytes, existing Triple plus fourth word) in rep_0610.h; extended ChallengeState page38.
fn_1_10560: asm review shows stored resource-relative texture pointer relocation; stub retained under offset-arithmetic restriction.
fn_1_1644C: asm review deferred binding at control-entry subobject+0x68, beyond existing entry stride; no consistent object layout yet, stub retained.
Introduced ChallengeImageFrame (stride20, pixels4) and ChallengeImageDraw (stride1C, texture8/pixelsC/palette10/dimensions14/16/active18) in rep_7730.h; added halfword/byte views to shared scene parameters.
fn_1_1D944: two candidates schedule draw-descriptor base before frame-index loads, yielding persistent scratch-register and instruction-order differences; restored stub, removed unused ChallengeImageFrame/ChallengeImageDraw.
Introduced ChallengeSoundState in rep_02A8.h, pending byteE0 at lbl_1_common_bss_49994.
Introduced ChallengeCurveConfig (step18/square1C/count20/inverse24), ChallengeCurvePoint (stride40/positionC/flags3C), ChallengeCurveState (endpoint3D0/config3E0/points408) in rep_7730.h.
fn_1_21180: two candidates including inline config initializer still fold nested3E0 base into stores3F8..404 and differ in float scheduling/vector copy; restored stub and removed unused curve types.
fn_1_D8A0: one candidate sinks state base past projection calls and folds camera388C+view10 into389C; restored stub and unused state matrix/camera fields.
Introduced ChallengeMenuChoice in rep_02A8.h: selection0/pending1 at lbl_1_common_bss_49A78.
Reused existing Gap9EA0State instead of new ChallengeMenuChoice; moved definition to shared challenge.h and exposed selection0/pending1 in its initial padding.
fn_1_9F04: one candidate matches behavior but resource-view base/index scratch registers differ in store and load arms; stub restored and unused callback/byte1A declarations removed.
Introduced ChallengeViewVectors in rep_74A0.h: target3C/eye48 at lbl_1_bss_6B7C.
fn_1_1B6BC: two candidates leave zero and eye-Y constant bases swapped, changing float registers and prologue scheduling; restored stub and removed unused ChallengeViewVectors.
Introduced ChallengeTexture in rep_7730.h: pixel/palette pointers0/4, dimensions8/A, wrap/filterC..F,bias10,LOD15/16,format17,palette count18/format1A.
fn_1_2051C: four attempts match main body, but return-bool neg/or/srwi stay before register restores instead of interleaved; restored stub and removed unused ChallengeTexture.
fn_1_E8D4: asm review repeats D7A4 strided choice-view base+40/fields10 and animation-base hoisting obstacle; stub retained.
fn_1_27594: three candidates match body but prologue global/zero-Vec copy scratch registers r3..r6 remain permuted; restored stub and removed unused scene-vector alias/prototypes.
Introduced ChallengeSpriteHeader (indices8), ChallengeSpriteSlot (stride3C,header38) in rep_7730.h.
Reused Gap26AF8Entry for sprite-load table FB98 (not a disk descriptor); moved it into rep_7730.h and replaced its void pointer with opaque ChallengeSpriteResource*.
Introduced ChallengeMotionState at lbl_1_bss_6BD8 in rep_7730.h: valuesC/camera1C/view170.
fn_1_1F2D8: one candidate sinks motion-state base across initialization calls and folds camera subobject offsets, changing saved register/prologue and float scheduling; stub restored, unused ChallengeMotionState removed.
Introduced ChallengeMovePoint (stride40,scale0), opaque ChallengeMoveState in rep_7730.h.
fn_1_247A0: one candidate differs in signed/unsigned conversion stack allocation, float registers and shifted scale-table address; stub restored and unused move types removed.
fn_1_7280: asm review deferred overlapping 0x6C draw records at offsets5C and134 plus separately anchored data2A8; consistent shared object layout not established, stub retained.
fn_1_1347C: asm review repeats 1B6BC zero/Y constant-base and float-allocation issue in projection initialization; stub retained.
Introduced ChallengeMipSettings in rep_0138.h: levels778/scales77C/bias78C/filter790 at lbl_1_data_2A8.
Introduced ChallengeIndirectState in rep_0138.h (matrixMode11/scaleY14/scaleX18/flags1C/texture424); extended ChallengeMipSettings warp7C5/exponent7C8/matrix7CC.
fn_1_5544: three attempts; state-flags read rematerializes global base, saved-base prologue differs, and SDK s8 exponent prototype adds extension versus target int; stub restored and unused indirect fields/types removed.
Introduced ChallengeWaveSettings overlay in rep_7730.h: spacing924/speed928/damping92C relative to dataFB98.
fn_1_22F4C: one candidate recovers wave math but strength-reduced loop indices save fewer registers and float coefficients swap; stub restored and unused ChallengeWaveSettings removed.
fn_1_2948C: three candidates fail to preserve separate raw-input and saved-input registers/copies, and mode-argument scheduling differs; restored stub and unused prototype.
fn_1_22DF4: asm review repeats 21180 curve config3E0 base-folding/float-scheduling obstacle in inlined setup; stub retained.
fn_1_126CC: one candidate differs extensively in six signed/unsigned controller conversions, stack slots and float scheduling; stub restored and unused rotation extern removed.
fn_1_1B2C8: asm review repeats 126CC six-controller-conversion scheduling issue with a scene-selected actor; stub retained.
- fn_1_17D90: deferred after assembly review; packed source records and legacy huge-animation table require coordinated type reconstruction.
- ChallengeCurvePoint (rep_7730.h): 0x40-byte point records with Vec position at 0xC, inferred from fn_1_21298.
- fn_1_21298: four candidates preserve behavior but introduce a loop-counter copy and different register allocation; restored stub and temporary curve type.
- ChallengeIndexPair (rep_0610.h): two u16 indices per swap-table record; Rep0610Obj remap/indices extend the existing object view (context overlaps remap head).
- fn_1_14710: two candidates match unrolled initialization but compiler collapses sentinel index into an updating pointer; restored temporary index-table views.
- ChallengeLayoutInput (rep_0250.h): mode byte at 0x69; extended existing layout state with index4/loaded6/item24 for fn_1_8DBC.
- ChallengeRenderCamera (gap_17EFC.h): projection0/view40, camera returned by fn_80052768 for fn_1_17FF0.
- ChallengeModelPose/ChallengePreviewState (rep_0138.h): 0x6C-byte copied pose records at 0x5C and preview controls through 0x234, inferred from fn_1_66C4.
- fn_1_DF14: deferred after review; same nested ChallengeState item/table layout and base folding obstacles as fn_1_D8A0.
- fn_1_20E00: deferred after review; relocates packed resource offsets into actor/geometry pointers, blocked by no manual pointer-offset rule.
- fn_1_179CC: deferred after assembly review; repeats fn_1_126CC mixed signed/unsigned six-axis conversion scheduling obstacle.
