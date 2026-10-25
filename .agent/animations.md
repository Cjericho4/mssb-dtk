# Character animations (R5 / issue #13, GYQE01, 2026-10-24)

## TL;DR

**A bank swap can be data-only, but bone IDs, sequence slots, timing and all load paths must agree.**
`lbl_800F1D78[charID*19+track]` tracks **2..18 are ANIM banks**; 0/1 are bodies.
Track 15 also has an independent ARAM copy at `master[432+charID]`. Neither is a skeleton file.
The skeleton is inside each body's `.gpc` actor layout. Binding searches **bone ID**, not the
bone's position in an array. The often quoted 37 bones applies to Mario, not the roster.

**High confidence:** bank layouts/quantization, gameplay ID partition, traced load branches,
family descriptor sharing, bone binding, playback and event-window association. All 918 disc
bank references resolve to 544 distinct files; the parser decoded their **3,829,384 key records**,
all 108 body layouts, and verified all 54 master/disc track-15 pairs byte-for-byte.
**Incomplete:** tracks 7/8 have no identified request path; individual extra-bank poses, the
visual identity of 0x2E, auxiliary interpolation payload semantics and Blender conventions need
more work. No Dolphin swap or authoring round trip was performed. R5 remains partial.

Tools: `tools/datamap/animations.py` (bank/keys/body hierarchy), `audit_animations.py` (whole-roster
checks and per-character event-window export), `test_animations.py` (synthetic unittest).
These operate on local user-provided files. No extracted asset or key-value dump is committed.

## 1. Disc tracks, actions and requesting states

Two meanings of “track”: a **disc subfile track** below is an entire bank; an **ANIM track** is a
bone's keyframe stream inside one sequence. All integers in the file are big endian.

The action proof is the partition in `fn_8001BA44` at **0x8001BB88..0x8001BC08** and its twin
`fn_8001BE50` at **0x8001BF88..0x8001BFFC**. Both select a pointer from slot +0x10 + group*4:

| Gameplay animation ID (inclusive) | Group / slot pointer | Sequence ID | Action class (confidence) |
|---|---|---|---|
| 0..44 (0x00..0x2C) | 2 / +0x18 | ID | Fielding: ready, locomotion, catches, pickup/dive, throws, tag, stun, wall moves (high class, medium individual exported names) |
| 45..60 (0x2D..0x3C) | 1 / +0x14 | ID−45 | Running, walk/skid/turn/dive, lead-off, waiting and runner celebrations (high class) |
| 61..62 (0x3D..0x3E) | 4 / +0x20 | ID−61 | Two pitcher idles (medium names; high partition) |
| 63..74 (0x3F..0x4A) | 3 / +0x1C | ID−63 | Pitch windup/recovery, happy/sad/tired/stretch/taunt/await (high class) |
| 75..104 (0x4B..0x68) | 0 / +0x10 | ID−75 | Batting: stance, swing/bunt, strikeouts/walk/HBP, entrance/recovery (high class) |
| ≥105 (0x69) | 5 / +0x24 | ID−105 | Extra poses; banks below have 12 sequences, so 105..116 fit. Exported ID 107 = WinningCelebration (medium name) |

These are numeric ranges, **not enums stored in the bank**. `ANIMGetSequence` selects by sequence
array index when name=NULL. Retail character sequence names inspected here are empty; names in
`in_game.h: EnumCharacterAnimation_short` are reverse-engineering annotations, not author labels.
The selector checks sequence bounds for a non-NULL bank. A bank with a wrong sequence order can
animate successfully and still perform the wrong action.

| Disc track | Sequences (all characters unless stated) | Requests and triggering state; evidence | Confidence |
|---:|---:|---|---|
| 0 / 1 | — | Body hi/lo; `fn_8001758C`, cached body helpers `fn_80014E50/F40`; `variant` chooses body, not an ANIM sequence | High |
| 2 | 30 | Batting group 0. `fn_80014D4C` caches 2 (10 in practice); `fn_8001C67C_animation` installs it for the current batter. `someAnimationIndFunction` (game 0x14388) passes the batter charID/slot, or minigame participant | High |
| 3 | 16 | Running group 1. `fn_8001500C` state 2 calls `fn_80017340`; its 0x800174F0..540 branch loads 3, or 11 in practice, into +0x14. Used for runner/batter slot loading, with bank reuse by charID | High |
| 4 | 45 | Fielding group 2. `fn_80014A18` / `fn_80015468` load +0x18 when `g_hugeAnimStruct+0x2D7C == 0`; nonzero loads 17 into +0x24. Driven by `fn_8001594C` (game field load, e.g. game 0x6BE80). Also `fn_80016B60` steps 1/2, except mode 7 | High |
| 5 | 12 | Pitching group 3. `fn_8001C920` loads 5 unless settings +0x11 !=0 or mode=2, then 18. Caller `fn_3_750DC` obtains the fielding team's pitcher charID and waits for this bank. Also `fn_80016B60` steps 5/6 | High |
| 6 | 2 | Pitcher-idle group 4. `fn_8001C588` loads 6 into shared +0x2CE8 and installs +0x20 if absent on slotPtrs[1]. Called during field/team setup (game 0x5D8D4, 0x5FD30; also 0xADCF4/AF570) | High partition/load; medium visual name |
| 7 | 12 | Unknown. Resembles extra-bank sequence count, but no group/load association proven. Includes additional target IDs (Mario 36/0xFFFF) | Unknown purpose |
| 8 | 2/3/4/9 | Unknown. Varying sequence counts and extra targets; do not call it “menu animations” on count alone | Unknown purpose |
| 9 | 30 | Batting group 0 minigame variant: `fn_8001C67C_animation`, settings +0x11 !=0 **and** mode=7. Its +0x11!=0, mode!=7 branch instead loads 2 | High |
| 10 | 30 | Batting group 0 practice variant: `fn_80014D4C` and `fn_8001C67C_animation`, mode=2 on normal (+0x11==0) path | High |
| 11 | 16 | Running group 1 practice: `fn_80017340` mode=2, also `fn_80016B60` steps 3/4 mode=2 | High |
| 12 | 16 | Running group 1 in four-slot loader `fn_80016B60` steps 3/4 except mode 2/6 (default, including minigames). This differs from ordinary runner loader's track 3 | High |
| 13 | 45 | Fielding group 2 in `fn_80016B60` mode=7 | High |
| 14 | 16 | Running group 1 in `fn_80016B60` mode=6 (Toy Field) | High |
| 15 | 12 | Extra group 5: `fn_80021BBC` reads master[432+c] if loader flags +0x1EA bit1 set, otherwise disc 15. `fn_80016344/16710`: mode 2 shared bank; otherwise slots<9 per-slot bank | High load/group; individual poses unknown |
| 16 | 12 | Extra group 5: `fn_80016344/16710` non-practice slots≥9 (except explicit slot 12 in 16344); also `fn_80016B60` steps9/10 | High |
| 17 | 12 | Extra group 5: `fn_80016344` slot 12; also `fn_80014A18/15468` +0x2D7C!=0 branch. Complements 4 in alternate field-load pass | High |
| 18 | 12 | Pitching group 3: `fn_8001C920`, settings+0x11!=0 or mode=2; same predicate in `fn_80016B60` | High |

Mode labels: `EnumGameType` in `in_game.h`: 0 exhibition, 2 practice, 4 demo, 5 challenge,
6 Toy Field, 7 minigames. Settings+0x11 is called `minigamesEnabled` in game-side headers;
keep its actual predicate above because it is a separate byte from mode.

`fn_80016F7C` drives `fn_80016B60` for slots0..3, sharing into4..7 in mode 6. Callers include
game 0x10AFE0 and 0xDF4E4. After loading track 5/18, **step 6 jumps to9** and shares block 0's
+0x2CF8 bank. The track 2/9/10 code at steps7/8 exists but is skipped by this path; the active
batter loader above supplies it. This explains why inspecting just this function is insufficient.

Menu/non-match actors: menus `fn_2_481F4` calls `fn_80016710` at menus 0x486EC; it therefore
uses the **15/16 extra-bank rules**, not an independently proven track 8 rule. Menus also load
`menu_char_a/b` scene files (`data_map.md` §4); this pass does not equate their embedded animations
with the character subfile banks. No complete celebration/menu pose catalogue is claimed.

## 2. Bank format and decoder

**High confidence for record layouts.** Sources: `include/C3/anim.h`, `include/C3/unktypes.h`,
retail `ANIMGet` 0x800B508C..5168, and the readers below. Generic SDK prototypes here are not all
accurate for this game: retail **ANIMGet takes the bank buffer in r3**, relocates it in place,
and has no name argument. Existing declarations conflict (`ANIMBank**` vs `u8*` vs stub `(void)`);
this research adds no speculative header rename or signature change.

| Record | Offsets and types |
|---|---|
| Bank, 0x18 B | +0 u32 version=0x007B7960; +4 u32 sequence offset; +8 u16 bankID; +A/C/E u16 sequence/track/key counts; +10 u32 userDataSize; +14 u32 userData offset |
| Sequence, 0xC B | +0 u32 name offset; +4 u32 first-track offset; +8 u16 totalTracks; +A u16 padding |
| Bone track, 0x10 B | +0 f32 duration; +4 u32 first-key offset; +8 u16 key count; +A u16 bone/track ID; +C u8 quantizeInfo; +D u8 animType; +E u8 interpolationType; +F u8 replaceHierarchyCtrl |
| Key, 0xC B | +0 f32 time; +4 u32 setting offset; +8 u32 interpolation payload offset |

All those offsets are **relative to the start of this bank**, not to their own record. Tables
are contiguous: sequences at+0x18, then `numSequences*12`, tracks `numTracks*16`, keys
`numKeyFrames*12`, then referenced payloads/names. `ANIMGet` hardcodes this table walk even though
it also relocates the header sequence pointer. Shared payloads and non-monotonic payload addresses
are legal. Do not infer key size from differences between setting pointers. Relocate only once;
export the unrelocated extracted file, never runtime RAM pointers.

`GetData` (0x800B560C) uses quantizeInfo's **high nibble**: 0=u8, 1=s8, 2=u16, 3=s16,
4=f32. Integer values are multiplied by **2^−lowNibble**; floats are copied directly.
**Quaternion settings are a separate fixed s16 / 16384 encoding** (four components, 8 B), read
using globals 0x803CBB48/4C=1/16384 and 0x803CBB50/51=3. These override the track quantization
for quaternion components; quantizeInfo=0x30 with animType=8 does not mean integer quaternions.

ANIM type bits (not CTRL type bits): **1=translation, 2=scale, 4=Euler, 8=quaternion,
0x10=matrix, 0x20=scale quaternion**. Settings order: scale if present (3 quantized values),
optional scale quaternion (8 B), rotation (quaternion8 B or Euler3 values), translation3 values.
The matrix branch reads twelve f32s and multiplies by 2^−lowNibble. Evidence:
`ANIMTick` 0x800B775C..78E8; `DoTranslationAnimation` 0x800B5DA8; `DoScaleAnimation`
0x800B63DC; `DoEulerAnimation` 0x800B6E0C; `DoQuatAnimation` 0x800B71C0.

Interpolation is **packed per channel**:

| Bits of +E | Channel | Decoder / confidence |
|---|---|---|
| 1..0 | Translation | 0 holds start value; 1 linear; 2 cubic using auxiliary vectors; 3 cubic with additional fixed-point parameters (high dispatch; full auxiliary authoring semantics unresolved) |
| 3..2 | Scale | 0/1/2/3 analogous dispatch, with optional scale-quaternion path (high dispatch) |
| 6..4 | Rotation | Euler 0 hold,1 linear,2 cubic,3 hold-start path; quaternion 0 hold,4 `Squad`,5 additional-parameter spherical path,6 spherical interpolation (high dispatch; medium mathematical naming) |

Examples from the full audit: `(quant,type,interp)=(0x30,8,0x60)` is quaternion-only with
rotation mode 6; `(0x3E,9,0x43)` is quaternion+translation with rotation mode 4, translation mode 3.
The +8 key pointer addresses auxiliary data, **not another key or a generic f32 tangent array**.
The parser returns that pointer and packed channel modes, and decodes **setting values**. It does
not evaluate curves or decode the auxiliary payloads. It is an inspection/export foundation,
not a lossless animation writer or Blender converter. Curve-preserving authoring still needs
those payloads and the runtime's per-bone interpolation overrides understood.

`ANIMGetKeyFrameFromTrack` (0x800B4E9C) keeps a cached key index (extra r6 argument), restarts the
search if time moved backwards, and returns the surrounding keys; after the final key, the next
key is the first key. `Do*Animation` uses track duration for the wrap interval. `totalFrames` in
SDK naming is the **number of key records**, not duration; a 40-frame hold can have only two keys.

## 3. Body bones and binding

**High confidence:** `LoadActorLayout` 0x800B4910 relocates the hierarchy root, palette name,
user data when present, and each bone's five pointer words relative to **layout start**.
`fn_80017814` separately relocates the `.gpc` root to obtain that layout. File hierarchy:

| Record | Fields |
|---|---|
| Body root | +4 u32 layout offset (relative to body start); other sections in `data_map.md` §5 |
| ActorLayout,0x20 | +0 version; +4 u16 actorID; +6 u16 totalBones; +8 tree offset; +C root offset; +10 palette-name offset (replaced with palette pointer at runtime); +14 u16 skinFileID; +16 padding; +18 u32 userDataSize; +1C userData offset |
| ActorBone,0x1C, contiguous at layout+0x20 | +0 orientation-control offset; +4 previous; +8 next; +C parent; +10 children; +14 u16 geoFileID; +16 u16 **boneID**; +18 inheritance; +19 drawing priority; +1A padding |

Null branch links mean no relation; nonzero links name ActorBone starts, relative to layout.
The parser outputs array indices **and parent bone IDs**. It preserves the stored tree-offset
word; the retail constructor traverses +0x10 children/+8 siblings directly. `f_InitActorWithLayout`
(0x800232E0) allocates by totalBones, resolves skinFileID through the geometry palette, and calls
**f_InitBone (0x80022DAC)** recursively. `f_InitBone` copies orientation control (0x44 B), boneID,
inheritance and drawing priority; it constructs runtime bone arrays in traversal order.
Missing geometry/skin descriptors are a separate layout/palette error, not an ANIM bank error.

`ACTSetAnimation` 0x800B4D64 gets the sequence then loops actor bones: runtime bone +0 supplies
boneID to `ANIMGetTrackFromSequence` (0x800B4F9C), which linearly compares track +0xA IDs.
It passes the result (possibly NULL) to `ACTSetBoneTrack` 0x800B79D0. **Matching array indices or
bone counts alone is neither necessary nor sufficient.** Unmatched bones do not receive the
intended track; no automatic retargeting maps a Mario limb to another skeleton's limb.

Retail body checks, hi/lo counts (metadata only, all characters audited):

| Character/family charIDs | High / low bones |
|---|---:|
| 0 Mario;1 Luigi | 37/37;37/36 |
| 2 DK;3 Diddy;4 Peach;5 Daisy;6 Yoshi | 39/39;44/46;40/40;37/37;47/40 |
| 7 Baby Mario,8 Baby Luigi;9 Bowser | 36/36;46/46 |
| 10 Wario;11 Waluigi;12/42 Koopas | 37/37;36/36;38/38 |
| 13,29..32 Toads;14 Boo;15 Toadette | 37/37;44/44;51/51 |
| 16,44..47 Shy Guys;17 Birdo;18 Monty | 51/51;46/46;41/41 |
| 19 Bowser Jr;20/43 Paratroopas;21..23 Piantas | 43/41;40/40;40/40 |
| 24..26 Nokis;27/52/53 Bros;28 Toadsworth | 37/37;36/36;39/38 |
| 33..36 Magikoopas;37 King Boo;38 Petey;39 Dixie | 45/45;45/45;41/41;41/41 |
| 40 Goomba,41 Paragoomba;48..51 Dry Bones | 47/47;52/52 |

Within each colour/animation-sharing family in §4, the high-body ordered `(boneID,parentID)`
signatures agree; the same is true within the low-body family. Additional **high-body** signature
matches: Baby Mario/Baby Luigi and Goomba/Paragoomba. This is a structural comparison, not proof
of equal rest transforms or animation interchangeability. High/low layouts may reorder bones:
Mario's 37 IDs/parents agree as a multiset, but its root 71 moves from first record to last.
15 charIDs even differ in the multiset of `(boneID,parentID)` between high and low bodies.
The audit JSON exposes exact signatures; do not assume a “universal 37-bone skeleton”.

## 4. Sharing, swaps and 0x2E

**High confidence, full descriptor audit:** the following groups share **all 17 disc banks**,
tracks 2..18 (same descriptor tuples, so identical compressed bytes at the same location):

| Family | charIDs |
|---|---|
| Koopa | 12,42 |
| Toad | 13,29,30,31,32 |
| Shy Guy | 16,44,45,46,47 |
| Paratroopa | 20,43 |
| Pianta | 21,22,23 |
| Noki | 24,25,26 |
| Bro | 27,52,53 |
| Magikoopa | 33,34,35,36 |
| Dry Bones | 48,49,50,51 |

All other charIDs have distinct complete descriptor vectors. That yields **32 vectors ×17=544
files**, versus 918 table entries. SHA-256 of decoded files finds **487 distinct byte patterns**.
Eight groups also share bytes across distinct descriptor locations (representative charIDs below;
include each representative's colour aliases from the family table):

| Track | Representatives with identical decoded banks |
|---:|---|
| 14 | All 54 characters (one identical 16-sequence bank despite distinct locations/skeletons) |
| 8 | 1,3,5,7,8,9,10,11,12,13,15,16,17,19,20,27 |
| 8 | 18,28,33,38,39,40,41 |
| 6 | 7,8 |
| 6 | 14,37 |
| 11 | 14,37 |
| 12 | 14,37 |
| 13 | 14,37 |

The audit's `identical_distinct_files` lists exact file IDs. Byte equality proves sharing, not
that every sequence contains useful character-specific motion (Mario track 14 is static).
Every one of the 54 ARAM track 15 banks decodes identically to that character's disc track 15.
ARAM descriptors are separate: do not infer that rewriting disc15 changes master432+c.

A data-only swap recipe (high for requirements; **not emulator-validated**):

1. Choose an action bank and its same-purpose mode variants from §1. Preserve every required
   sequence slot (e.g. batting77 always selects sequence 2), target bone IDs and intended
   inheritance/rest-space meaning. Compare both body variants with `--layout`; compare track IDs
   with those body IDs. Identical family banks provide a conservative initial test.
2. Redirect the recipient's complete16-byte descriptors to donor banks, or replace bank bytes
   using the datamap tool into a **new output disc**. Rewiring an individual recipient row and
   replacing a shared file have different scopes: `mssb_files.py replace` updates **every alias**,
   including colour-family users. Do not overwrite donor content to isolate one character.
3. For track 15, handle **both** `subfile[c*19+15]` and `master[432+c]`; the ARAM flag selects which
   one runs. With new/growing content, use the tool's container/blob size and compression handling.
   Reader buffers are sized in loader allocation routines, including maxima across characters
   (`fn_80018B74`); changing descriptor sizes after that allocation is unsafe.
4. Keep character-specific gameplay/event timing consistent. Animation swaps do not transfer
   `stats.0`, runner/pitch/bat timings, DOL event windows, attachment-bone maps or model scripts.
   Audit those alongside the new clip. Whole-character cloning already copies more than banks;
   that is not evidence that isolated cross-skeleton swaps will work.
5. Test live transitions, both handednesses, runner/field/batter roles and relevant modes in
   Dolphin. Check effects, glove/bat attachment, ball-release/contact frames, loops and recovery.

Cross-skeleton obstacles: missing/differently purposed IDs, different parent transforms,
proportions/rest poses, inherited channels, auxiliary geometry tracks (including 0xFFFF), per-model
scripts/attachments and timing events. Equal bone count is insufficient. A bone ID remap without
transform retargeting can still give wrong motion; the runtime does not supply that retargeting.

**0x2E: high confidence for location/use; visual name unknown.** It is **runner sequence 1**,
normal track 3 (practice 11; alternate loader 12/14). `fn_3_631AC` at game 0x63258..63300 checks
`lbl_800E8558[charID].grid` in {0x0E,0x14,0x1A,0x1E}: **Boo 14, Paratroopa 20/43,
King Boo 37, Paragoomba 41**. While turningAroundInd=1, direction-change age<10 and secondary
mode!=6, it requests nonlooped 0x2E at `lbl_3_data_7870[charID].s16_at_4−10`.
Boo/King Boo track 3 sequence 1 each have 12 changing bone tracks over 30 frames; Paragoomba has 26
over 18 frames. Mario's corresponding sequence is a 40-frame static hold. This disproves a
universal meaningful “Runner_Tpose” name, but does not establish a specific visible manoeuvre.
Tried: both exported enums, selector, triggering state, key counts and changing settings.
Need: view those flying-family clips or instrument the turn in Dolphin; no speculative C name.

## 5. Playback and per-character frame events

**High confidence**, source/retail assembly chain:

`game state -> AnimateCharacter (0x8001B990) -> slot pending ID +0x64 -> fn_8001C234 ->
fn_8001BA44 / fn_8001BE50 -> actor instance bank+sequence -> fn_800BD8C4 ->
ACTSetAnimation -> ACTSetBoneTrack / ANIMBind -> AnimateActorBones -> ANIMTick -> CTRL setters`

`AnimateCharacter` records loop/transition parameters and starting frame, avoiding some redundant
requests. `QueueCharacterAnimation` (0x8001B918) supplies a queued follow-on request.
`fn_8001C234` dispatches the pending animation, copies current+0x62 to previous+0x60, pending to
current, then clears pending to −1. The two dispatchers implement the partition in §1 and set
instance bank/sequence, flags, blend increment and initial time = requested frame × slot+0x4C.
The frame readback divides by that slot factor; raw ANIM time is not automatically a gameplay
frame. Do not assume a universal seconds/60 conversion for export.

`fn_800BD8C4` applies pending sequence/time/speed/loop state and invokes `AnimateActorBones`.
The latter updates actor blend and ticks every bone. `ANIMTick` samples surrounding keys, decodes
channels, writes CTRL, then advances time by speed (or subtracts on reverse), clamping or wrapping
at track duration. Matrix tracks take a separate early-return path. Bone+0x136 can clear the
translation interpolation bits when binding (0x800B7B64..80); file modes are not the whole runtime
behaviour. Matrix construction/skinning follows the updated controls.

DOL windows remain owned by [stats.md §7](stats.md).
They are **15 signed 16 arrays of 54 characters**, stride 0x6C, at 0x800FB798..0x800FBD80.
`audit_animations.py` exports `event_windows[c].values` in ascending table order:

| Values indices | Animation / sequence / default bank | Effect selection |
|---|---|---|
| 0,1 | 0x32 /5 /track 3 | Runner dive turn-around interval |
| 2,3 | 0x33 /6 /track 3 | Runner body-check interval |
| 4,5 | 0x34 /7 /track 3 | Runner side-dive interval |
| 6,7 | 0x1A /26 /track 4 | Fielder pickup interval |
| 8,9 | 0x1B /27 /track 4 | Fielder dive interval |
| 10,11 | 0x30 /3 /track 3 | Runner skid interval |
| 12,13 | 0x10 /16 /track 4 | Fielder-on-fire interval |
| 14 | 0x62 /23 /track 2 | Hit-by-pitch **exact-frame** event |

`fn_8001C234` calls `fn_8004B208(currentID,time)` at 0x8001C4F8; callback routing via
`lbl_800FBDEC/800FBE64` reaches `fn_8004B284`, `fn_8004BEB0` and `fn_8004C510` as documented in
stats.md. Intervals are inclusive, final event is equality. Values 99 often suppress events
relative to clip lengths; no universal disabled sentinel is proven. These windows gate effects,
not every gameplay animation transition. Runner 0x2E's entry-frame formula is a separate game.rel
per-character table (`stats.md` §6.1), not one of these fifteen arrays.

## 6. Reproduce, validation and remaining work

From this checkout (stdlib Python 3.8+):

```sh
python3 tools/datamap/mssb_files.py extract orig/GYQE01 subfile.2 /tmp/mssb-r5-local
python3 tools/datamap/mssb_files.py extract orig/GYQE01 subfile.0 /tmp/mssb-r5-local
python3 tools/datamap/animations.py /tmp/mssb-r5-local/subfile.2.anim --out /tmp/mario-bank.json
python3 tools/datamap/animations.py /tmp/mssb-r5-local/subfile.2.anim --sequence 2 --keyframes --out /tmp/mario-swing.json
python3 tools/datamap/animations.py /tmp/mssb-r5-local/subfile.0.gpc --layout --out /tmp/mario-bones.json
python3 -m unittest discover -s tools/datamap -p test_animations.py
python3 tools/datamap/audit_animations.py orig/GYQE01 /tmp/r5-audit.json
export PATH=/home/plex/repos/mssb-dtk/.venv/bin:$PATH
ninja build/GYQE01/report.json
python3 tools/find_matches.py build/GYQE01/report.json | wc -l
```

Extraction resolves aliases to canonical filenames: a requested `subfile.N` may be saved with
another subfile ID, or a master ID for blob members. Use the printed output/manifest locally.
Audit results: **544 distinct disc files, 487 decoded byte patterns, 3,829,384 key records,
108 body layouts and 54 equal master/disc pairs; build succeeds with 3967 matches.**
Checks cover Mario, Luigi, DK, Peach, Boo, Shy Guy, Dry Bones and every other character,
both body variants; pointer bounds, record spans, finite numbers and key-time monotonicity pass.
Synthetic tests cover all five numeric encodings, fixed quaternion versus track quantization,
sequence/key bounds, decreasing times and hierarchy ID/index distinction. No game C/header ABI
was changed; build/match result is recorded with the commits/final handoff.

Open experiments, with confidence limits:

* **Track 7/8 callers and names:** searched every DOL runtime-subfile-table reference, the load
  routines and their callers. None of the request sites found selects 7/8. Also inspected sequence
  counts/extra target IDs. This is not proof that no indirect/table-selected path can request them.
* **Extra pose names:** numeric 105..116 slots established; variants 15/16/17 have sparse/static
  replacements. Do not apply a single pose list to every bank without viewing it.
* **Blender:** next implement auxiliary curves or reproduce game evaluation by baking, decode the
  body's complete orientation controls, verify local/rest transforms, quaternion convention,
  handedness, coordinate axes, scale and time factor, then round-trip one same-skeleton clip.
  No axis conversion, Euler unit or FPS is asserted from file shape alone.
