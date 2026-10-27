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
**2026-10-26 (anim-playback branch):** the playback chain is now matched C
(`ANIMGet`, `ANIMGetKeyFrameFromTrack`, `ACTSetAnimation`, `ACTSetBoneTrack`, `ANIMTick`,
`f_InitBone`; `f_InitActorWithLayout` 25 feedback lines off on this checkout) and the channel decoders were read from asm:
§2.1 gives every interpolation formula and the auxiliary payload layout, §5.1 the local-matrix
composition. **Incomplete:** tracks 7/8 have no identified request path; individual extra-bank
poses, the visual identity of 0x2E, a Blender round trip and live validation of the ease edge cases need more work.
The 2026-10-26 codex-anim audit below resolves the flip rules and default time factor from asm;
it does not claim new matches for the channel decoders. No Dolphin swap or authoring round trip was performed.

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

### 1.1 Tracks 7/8 request audit (2026-10-26, codex-anim)

**High confidence: no request found in the statically traced character-bank loaders.** This is
strong negative evidence, not proof of unreachability under every runtime pointer value.
The only direct DOL code reference to `lbl_800F1D78` is `fn_80021BBC` at
**0x80021C60..84**, hardcoded to `charID*19+15`. Its other address reference initializes
`lbl_803CB790` at **0x803CB790**. Searching DOL and all three REL asm trees finds **30 code
references** to that pointer, all in DOL `gap_8001196C` / `gap_8001B200`, and no store replacing it.
These references were followed through the descriptor arithmetic, rather than searching for
immediate 7/8 (which also occur as loader step numbers and game-mode tests).

Actual transfer consumers are `fn_80014A18`, `14D4C`, `14E50`, `14F40`, `15468`, `16344`,
`16710`, `16B60`, `17340`, `1758C`, `1C588`, `1C67C_animation`, `1C920`, plus `21BBC`.
Their selections are the constants/branches in §1: bodies 0/1 and banks
2/3/4/5/6/9/10/11/12/13/14/15/16/17/18. For example the four-slot loader's mode and state
branches choose 4/13 at **0x80016BD8..C10**, 11/12/14 at **0x80016C90..CE4**, 5/18 at
**0x80016D6C..DA8**, 2/9/10 at **0x80016E30..E8C**, and 16 at **0x80016F00..30**.
State **7/8** at **0x80016E04..EB4** is a loading state for batting banks, not disc track 7/8.

The remaining pointer consumers (`fn_80018024`, `18270`, `189E4`, `18B74`, `18DEC`) compute
allocation maxima and do not request files. In particular `18B74` reads descriptor size words
at +0x24/+0x44/+0x94/+0xC4/+0xD4/+0xE4/+0x104/+0x124 with character stride 0x130
(**0x80018BB0..C78**); `18DEC`'s practice/non-practice branches similarly scan specific bank
columns. None is a hidden table-driven request for 7/8. No caller chain to those banks was
found. The menu path `fn_2_481F4 -> fn_80016710 -> fn_80021BBC` or track 16 remains an
extra-bank path, not evidence for 8. Absolute-address arithmetic bypassing the symbol table,
externally supplied descriptors and dynamically modified pointers were not exhaustively proven
absent; instrumentation at `ARAMTransfer` would close that remaining gap. Purpose/names remain unknown.

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

`GetData(type, src, dst, count, scale)` (0x800B560C; prototype from asm, high) decodes `count`
values of `type` = quantizeInfo **high nibble**: 0=u8, 1=s8, 2=u16, 3=s16, 4=f32, each multiplied
by `scale`; the callers pass `scale = 2^−lowNibble` (floats too, so a float track with a nonzero
low nibble is scaled). Element width `elem` = 1/1/2/2/4 bytes.
**Rotation quaternions are a separate fixed s16 / 16384 encoding** (four s16, 8 B), read with
globals 0x803CBB48/4C=1/16384 and 0x803CBB50/51=3; quantizeInfo=0x30 with animType=8 does not mean
integer quaternions. **The scale quaternion is not**: it is four track-quantized values
(4×`elem`, `DoScaleAnimation` 0x800B6530, `DoTranslationAnimation` 0x800B5E9C..5EE8). 2,763 tracks
in 88 of the 544 character banks use it (types 0x2A/0x2B/0x23 = scale + scale quaternion with
quaternion or translation, always scale mode 1 and quaternion mode 6); most are quantized 0x3E,
where the parser's fixed s16/16384 decode coincides, but 0x38, 0x35, 0x3D, 0x3C and 0x3B tracks
exist, where that decode is wrong.

ANIM type bits (not CTRL type bits): **1=translation, 2=scale, 4=Euler, 8=quaternion,
0x10=matrix, 0x20=scale quaternion**. Setting record order: scale (3×elem) if bit 2, then scale
quaternion (4×elem) if bit 0x20, then rotation (quaternion 8 B fixed, or Euler 3×elem), then
translation (3×elem). Matrix tracks (0x10) are handled in `ANIMTick` alone: the twelve f32 of the
**current** key are multiplied **in place** by 2^−lowNibble every tick (compounding unless the low
nibble is 0) and passed to `CTRLSetMatrix`; no interpolation.

### 2.1 Interpolation (from `DoTranslationAnimation`/`DoScaleAnimation`/`DoEulerAnimation`/`DoQuatAnimation`/`Squad` asm, 2026-10-26)

Confidence high for every formula below (read instruction by instruction; the functions are not
matched but the arithmetic is unambiguous). `cur`/`next` are the keys from
`ANIMGetKeyFrameFromTrack` (matched): starting at the cached `pipe->keyIndex` (reset to 0 when
`keys[cached].time > time`), it walks forward with wrap until `keys[i].time <= time < keys[i+1].time`
and returns (`keys[i]`, `keys[i+1]`); on the last key it returns (`keys[last]`, `keys[0]`).

**Normalized time** `u` (identical in all four decoders): `d = pipe->time − cur.time`;
`u = 0` if `d == 0`; else if `next.time > cur.time`: `u = d / (next.time − cur.time)`; else (wrapped
pair): `u = 1` when `duration >= cur.time` (always, for sane data), otherwise
`d / (duration − cur.time)`. So a track whose last key time is below its duration **snaps to key 0**
for the remainder; all 268,320 retail character tracks end exactly on their duration (`ANIMTick`
clamps there), so this never fires.

| Channel (bits of +E) | Mode | Formula |
|---|---|---|
| translation 1..0, scale 3..2, Euler 6..4 | 0 | hold `cur` |
| same | 1 | lerp: `(1−u)·cur + u·next`; Euler first wraps each axis: if `cur−next > 180` then `cur −= 360`, if `< −180` then `next −= 360` (degrees) |
| same | 2 | cubic Bezier `(1−u)³·cur + 3u(1−u)²·(cur + cur.out) + 3u²(1−u)·(next + next.in) + u³·next` (control points are **offsets** from the key values) |
| translation, scale | 3 | eased Hermite: `h00·cur + h01·next + h10·cur.out + h11·next.in` with `h00 = 2u³−3u²+1`, `h01 = 3u²−2u³`, `h10 = u³−2u²+u`, `h11 = u³−u²`; tangents are used as-is (not multiplied by the segment length); `u` is first remapped by the ease rule below |
| Euler | 3 | `OSPanic` (unsupported) |
| quaternion 6..4 | 0 | hold `cur` |
| quaternion | 4 | `Squad(cur, cur.out, next.in, next, u)` = slerp(slerp(cur,next,u), slerp(cur.out,next.in,u), 2u(1−u)) |
| quaternion | 5 | ease-remap `u`, then as mode 4 |
| quaternion | 6 | slerp(cur, next, u) |
| anything else | | `OSPanic` |

slerp (shared by 6, `Squad`, the scale-quaternion path and the control blend): `c = dot(a,b)`;
if `1 + c > 1e−6`: if `1 − c > 1e−6` then `w0 = sin((1−u)θ)/sinθ, w1 = sin(uθ)/sinθ` with
`θ = acos(c)`, else `w0 = 1−u, w1 = u`; result `w0·a + w1·b`. If `1 + c <= 1e−6` (antipodal)
it blends `a` with the perpendicular to **b**, `(−b.y, b.x, −b.w, b.z)` by `sin((1−u)π/2)`, `sin(uπ/2)`.
**No sign flip for `c < 0`**: consecutive keys must already be in the same hemisphere; an exporter
has to neighbourhood its quaternions. The identity-check epsilon is `lbl_803CCF88 = 1e−6`.

**Ease remap** (translation/scale mode 3, quaternion mode 5), from two s16/16384 values `a`
(ease-in, read from `cur`) and `b` (ease-out, read from `next`), skipped when `u == 0`, `u == 1`
or `a + b == 0`: if `a + b > 1` then `a /= (a+b)`, `b /= (a+b)`, `k = 0.5 − 1/(a+b)` (pre-normalization
sum) else `k = 0.5 − 1/(a+b)`; then `u < a`: `u = u²·k/a`; `a <= u < 1−b`: `u = k·(2u − a)`;
else `u = 1 − (1−u)²·k/b`. **As written this curve is not continuous and `k` is negative for
0 < a+b < 2** (retail constant 0x803CCF94 = 0.5 and the operand order re-checked in the DOL; not
run in Dolphin). Across all 544 character banks, 296,174 of the 296,522 mode-3 translation keys
store `(0, 0)`; the 348 others (`(0, 35)`, `(0, 34)`, `(0, 224)` /16384, i.e. a tiny ease-in on
342 mid-track keys) are all in the track-7 and track-17 banks of Goomba, Paragoomba and Dry
Bones. With the retail arithmetic those segments evaluate far outside [0, 1]; whether that is
visible is untested. No quaternion mode 5 or scale mode 3 track exists. An exporter should write
zeros.

**Recheck, high confidence (2026-10-26): this is a retail arithmetic quirk, not a missing
reciprocal in the prose.** At **0x800B6278..88** the instructions compute `f1=1/(a+b)`,
normalize both ease values, then `f2=0.5-f1`; **0x800B6290..98** computes the same coefficient
without normalization. The constant is explicitly `.float 0.5` at **0x803CCF94**.
The comparison uses `a` at **0x800B629C**, `1-b` at **0x800B62B4..BC**, and the last branch
uses `1-(1-u)^2*k/b` at **0x800B62D4..E0**. Scale repeats this at **0x800B6B10..78**,
quaternion at **0x800B7450..B8**. For an illustrative synthetic pair `a=b=0.25`, `k=-1.5`:
the middle branch approaches −1.875 as u approaches 0.75 from below, while the last branch
returns 1.375 at u=0.75. Do not silently substitute the conventional continuous ease curve.
The example is arithmetic evidence, not a claim that this ease pair occurs in retail assets.

**Auxiliary payload** (key +8 pointer, per key, laid out per channel in the order scale,
rotation, translation; a channel contributes only in the modes listed):

| Channel / mode | Bytes | Contents |
|---|---|---|
| scale mode 2 | 6·elem | `in[3]`, `out[3]` (track quantization, same `scale`) |
| scale mode 3 | 6·elem + 4 | `in[3]`, `out[3]`, `s16 ease[2]` (/16384) |
| Euler mode 2 | 6·elem | `in[3]`, `out[3]` (degrees) |
| Euler mode 3 | 6·elem + 4 | reserved by the offset maths, never read (`OSPanic`) |
| quaternion mode 4 | 0x10 | `in[4]`, `out[4]` as s16/16384 (x, y, z, w) |
| quaternion mode 5 | 0x14 | `in[4]`, `out[4]`, `s16 ease[2]` |
| translation mode 2 | 6·elem | `in[3]`, `out[3]` |
| translation mode 3 | 6·elem + 4 | `in[3]`, `out[3]`, `s16 ease[2]` |

Which half is used: `cur` always contributes its **second** vector/quaternion (`out`) and `next`
its **first** (`in`). The ease pair is read asymmetrically: translation and scale take
`cur.ease[1]` as ease-in and `next.ease[0]` as ease-out, and quaternion mode 5 reads them the same
way (corrected 2026-10-27, Codex: 0x800B73D8 reads `next`+aux+0x10 = `next.ease[0]` via r30 = arg 3,
0x800B73F8 reads `cur`+aux+0x12 = `cur.ease[1]` via r29 = arg 2; earlier text had them swapped)
(asm 0x800B61C4..623C and 0x800B73D8..7414). Roster-wide
(544 banks, 268,320 tracks, 3,829,384 keys, `.scratch` survey 2026-10-26): translation mode-3 keys
store equal `in`/`out` tangents in 282,734 cases and different ones in 13,788; Squad keys equal
control quaternions in 504,798 cases, different in 3,674. The `(quant,type,interp)` set is:
(0x30,8,0x60) 239,958 tracks (quaternion slerp), (0x3E,9,0x63) 11,748 and (0x3D/0x3C/0x3B,9,0x63)
622 (slerp + translation Hermite), (0x30,8,0x40) 11,305 (Squad), (0x3E,42,0x64) 2,519 plus 184 at
other quantizations (scale lerp + scale-quaternion slerp + rotation slerp), (0x3E,1,0x3) 899
(translation Hermite only), (0x3E/0x3D/0x3C/0x3B,9,0x43) 1,022 (Squad + Hermite), (0x3E,35,0x7)
10, (0x3E/0x3D,43,0x67) 8, (0x30,8,0x0) 2 (hold), (0x3E,2,0x8) 1. No Euler, Bezier or matrix
track exists in the character banks.

`ANIMGetKeyFrameFromTrack` (0x800B4E9C, MATCH) keeps a cached key index (`pipe->keyIndex`, the
fifth argument), restarts from 0 if time moved before the cached key, and returns the surrounding
keys; after the final key the next key is key 0. `totalFrames` in SDK naming is the **number of
key records**, not duration; a 40-frame hold can have only two keys. The parser
(`tools/datamap/animations.py` in mssb-modding) still returns only the aux pointer and packed
modes; decoding the payload above is the next parser step.

## 3. Body bones and binding

**High confidence:** `LoadActorLayout` 0x800B4910 relocates the hierarchy root, palette name,
user data when present, and each bone's five pointer words relative to **layout start**.
`fn_80017814` separately relocates the `.gpc` root to obtain that layout. The C types are
`ActLayout` / `ActBoneLayout` (file) and `GameActor` / `ActBone` (runtime) in `include/C3/actor.h`
(2026-10-26). File hierarchy:

| Record | Fields |
|---|---|
| Body root | +4 u32 layout offset (relative to body start); other sections in `data_map.md` §5 |
| ActorLayout,0x20 | +0 version; +4 u16 actorID; +6 u16 totalBones; +8 tree offset; +C root offset; +10 palette-name offset (replaced with palette pointer at runtime); +14 u16 skinFileID; +16 padding; +18 u32 userDataSize; +1C userData offset |
| ActorBone,0x1C, contiguous at layout+0x20 | +0 orientation-control offset; +4 previous; +8 next; +C parent; +10 children; +14 u16 geoFileID; +16 u16 **boneID**; +18 inheritance; +19 drawing priority; +1A padding |

Null branch links mean no relation; nonzero links name ActorBone starts, relative to layout.
The parser outputs array indices **and parent bone IDs**. It preserves the stored tree-offset
word; the retail constructor traverses +0x10 children/+8 siblings directly.

### 3.1 Rest pose and runtime bones (`f_InitBone` MATCH, `f_InitActorWithLayout` 25 feedback lines off on this checkout, 2026-10-26)

`f_InitActorWithLayout(layout, mem)` (0x800232E0) carves everything from one 32-byte-granular
block: [skin `ActDisplayObj`, 4 blocks + its data via fn_80023078] `GameActor` (0xA0) | `boneArray`
(totalBones×4) | `forwardMtxArray` (totalBones×0x30) | `skinMtxArray` | `orientationInvMtxArray` |
`skinInvTransposeMtxArray` (the last three only with a skin; the last only when the skin has
lighting data) | bone records (totalBones×0x140) | per-bone display objects and `ANIMPipe`s. It
then sets `worldControl.type = 0`, runs `f_InitBone`, panics ("objinit.c", 0x209) if the bone count
differs from `totalBones`, builds the inverse bind matrices (`BuildBoneSkinOrientationMatrix`,
skin only), sorts the draw list (`ACTSort`) and resets the game fields (+0x8C blend weight = 1).

`f_InitBone(parent, layout, actor, &count, bones, cursor)` walks the sibling chain (`+8 next`) and
recurses into `+0x10 children` **before** the next sibling, so `boneArray[i]` / matrix slot `i` is
the **pre-order depth-first index** of the file hierarchy (parents precede children). Each bone:
`DSInsertBranchBelow` under its parent; `boneID`, `inheritanceFlag`, `drawingPriority` copied from
the layout; `orientationCtrl.type = 0` then, if the layout's +0 pointer is set, the **whole 0x44-byte
control copied** (`ControlExt`): this is the rest pose, `type` bits CTRL_SCALE 1 / ROT_EULER 2 /
ROT_QUAT 4 / TRANS 8 / MTX 0x10 / SCALE_QUAT 0x20 with the SRT payload at +4 (scale xyz, rotation
quaternion xyzw or Euler degrees xyz0, translation xyz, scale quaternion xyzw; a 0x10 matrix
control holds a 3×4 Mtx instead). A bone without a control is identity. `geoFileID != 0xFFFF`
attaches `pal->descriptorArray[geoFileID]` as the bone's display object (OSReport + no object when
out of range). The bone's `ANIMPipe` is carved from the cursor (0x20 stride) with time 0, speed 1,
no track, forward, loop; `animFlags` (+0x134) = 1, +0x136/+0x137 = 0; forward/skin/inverse-bind/
inverse-transpose matrices are set to identity. Runtime `ActBone` offsets (0x140 bytes): +0 boneID,
+2 inheritanceFlag, +3 drawingPriority, +4 DSBranch, +0x14 dispObj (+0x18 copy), +0x1C
orientationCtrl, +0x60 animationCtrl, +0xA4 blendFromCtrl, +0xE8 animPipe, +0xEC forwardMtx,
+0xF0 skinMtx, +0xF4 skinInvTransposeMtx, +0xF8 orientationInvMtx, +0xFC drawPriorityLink,
+0x134 u16 animFlags, +0x136 u8 holdTranslation. For Blender: the bind pose is the
`orientationCtrl` of every bone composed down the hierarchy exactly as in §5.1 with no animation.
Missing geometry/skin descriptors are a separate layout/palette error, not an ANIM bank error.

`ACTSetAnimation(actor, bank, name, seqNum, time, blendStep)` 0x800B4D64 (MATCH) gets the sequence
then loops actor bones: runtime bone +0 supplies boneID to `ANIMGetTrackFromSequence` (0x800B4F9C),
which linearly compares track +0xA IDs. It passes the result (possibly NULL) to
`ACTSetBoneTrack(bone, track, time, blend)` 0x800B79D0 (MATCH) with `blend = actor.blendWeight(+0x8C)
< 1 && bone.animFlags != 0`, then sets bone flag 0x20 iff `animFlags & 0x1C`; finally
`blendWeight = blendStep ? 0 : 1` and `+0x90 = blendStep` (AnimateActorBones adds it per tick,
clamped to 1). `ACTSetBoneTrack`: a NULL track unbinds (control type 0, no track); otherwise it
snapshots the blend source into `blendFromCtrl` (the current `animationCtrl` if it has a type, else
the rest pose), `ANIMBind`s (control type 0, time = previousTime = `time`, keyIndex 0,
replaceHierarchyCtrl from track +0xF), clears the translation mode bits when `holdTranslation`
(+0x136) is set, and **copies every rest-pose channel the track does not animate** (translation,
scale with scale-quaternion or identity, Euler or quaternion rotation) from `orientationCtrl` into
`animationCtrl`; without blending the snapshot is overwritten with the result. So a track that
animates only rotation keeps the bone's rest translation/scale. **Matching array indices or bone
counts alone is neither necessary nor sufficient.** Unmatched bones do not receive the intended
track; no automatic retargeting maps a Mario limb to another skeleton's limb.

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
   `fn_80018B74` (Codex reading, 2026-10-27, not matched): it scans all 54 characters' descriptors for
   tracks 4/13, 12/14, 18, 2/9 and 16, takes each group's largest uncompressed size (`sizeFlags & 0x0FFFFFFF`),
   rounds it up to 32 B and allocates one buffer holding four bank slots. So a **bigger custom bank is safe
   when its disc descriptor carries the new size before this runs** (a patched disc does); the limit is
   heap room for the larger maximum, not a fixed constant.
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
fn_8001BA44 / fn_8001BE50 -> actor instance bank+sequence -> fn_8001DB74 (characters) / fn_800BD8C4 (extra tables) ->
ACTSetAnimation -> ACTSetBoneTrack / ANIMBind -> AnimateActorBones -> ANIMTick -> CTRL setters`

`AnimateCharacter` records loop/transition parameters and starting frame, avoiding some redundant
requests. `QueueCharacterAnimation` (0x8001B918) supplies a queued follow-on request.
`fn_8001C234` dispatches the pending animation, copies current+0x62 to previous+0x60, pending to
current, then clears pending to −1. The two dispatchers implement the partition in §1 and set
instance bank/sequence, flags, blend increment and initial time = requested frame × slot+0x4C.
The frame readback divides by that slot factor; raw ANIM time is not automatically a gameplay
frame. **Default slot factor is 0.5**, so default key-time units are nominally 30 Hz while
gameplay frame numbers count the nominal 60 Hz updates (details below).

`fn_800BD8C4(table, cullMatrix)` (0x800BD8C4, size 0x160) is a **table** updater, not a
single-actor speed setter. Header +0 is a u16 count; entries begin at table+0x34 with stride
0x90. In the asm r31 is `table + i*0x90`; below, offsets are relative to that r31 base
(subtract 0x34 to get offsets within an entry):

| Predicate / address | Effect |
|---|---|
| +0x34 actor pointer non-NULL, 0x800BD8F0..F8 | process this entry |
| +0x8C nonzero, 0x800BD8FC..91C | `ACTSetAnimation(actor, +0x38 bank, NULL, +0x42 sequence, 0.0f, +0x94 blendStep)` |
| +0x8D nonzero, 0x800BD920..934 | `fn_800B4CA0(actor, +0x90 time)` writes every existing pipe's **time +0**, at 0x800B4CC0; does not write previousTime |
| +0x8E nonzero, 0x800BD938..94C | `fn_800B4C04(actor, +0x88 speed)` writes every existing pipe's **speed +8**, at 0x800B4C24 |
| +0x8F bit1 set, 0x800BD950..964 | `fn_800B4AFC(actor, flags&1)` writes pipe loop byte +0x18 |
| always, 0x800BD968..970 | install +0x9C remap pointer into actor+0x88 (`Set_FUN_800b2b6c`) |
| +0xA0 nonzero, 0x800BD974..9B8 | copy +0x44 ControlExt to actor+0x1C, set +0x98/+0x9A bone indices, then `AnimateActorBones -> fn_800B3F20 -> fn_800B313C` |
| 0x800BD9BC..9F8 | cull via fn_800B3C04, update actor+0x98 low flags; clear +0x8C/8D/8E and bit1 of +0x8F |

The bank is initially bound at time zero, then a pending time is applied, then speed, then the
first tick. The second argument is passed to culling at **0x800BD9CC**, not used as delta time.
**Correction to the earlier chain:** the ordinary characters use **fn_8001D2D4 -> fn_8001DB74
at 0x8001D6CC**, not fn_800BD8C4. That specialized updater repeats the pending-state sequence
at **0x8001DBDC..DC50**, using entry-relative +0x58/59/5A/5B flags, +0x5C time, +0x54 speed,
+0x60 blend step and +0x68 remap. It invokes fn_800BDA24 at **0x8001DC64** when entry+0x6C
is enabled; that wrapper ticks and builds matrices. The extra object tables at
g_hugeAnimStruct+0x64/+0x68 use fn_800BD8C4 at **0x8001DA64 / 0x8001DB28**. Their timing
operations agree, but their culling/dispatch differs.

**Time conversion, high confidence for update units:** `challengeMapMaybe` initializes each
of the 13 slot records' +0x4C to **0.5** at **0x8001F4CC / 0x8001F4F0** (base+0xC04,
store+0xC50; constant **0x803CC4D0 = 0.5**, stride 0x27C). `fn_8001D2D4` copies slot+0x4C to
entry speed +0x54 and sets speed-dirty +0x5A at **0x8001D5CC..DC**; adding the table header
0x34 gives the updater's +0x88/+0x8E above. Its freeze branch writes zero speed at
**0x8001D56C..580**. The initial requested frame is multiplied by slot+0x4C at
**0x8001BCF8..D0C** (twin **0x8001C0DC..F0**); readback divides raw time by it at
**0x8001C314..328**. Consequently **one gameplay frame = one enabled game update; one raw ANIM
frame = two updates at the default 0.5 speed**. The renderer samples first and advances after,
so the first displayed sample is the requested starting time.

**Nominal wall-clock rate: high confidence for the normal USA video path, no live timing
measurement.** The queued callback is registered as fn_800090B4 at **0x8000914C..5C**, calls
fn_8001D2D4 at **0x80009130**, and is dispatched by RunDrawScripts at **0x800093FC**.
The main loop sleeps for video pacing at **0x8000944C -> fn_800A7DB0 -> OSSleepThread
(0x800A7DC8)**. VI pre-retrace callback fn_800A84C4 wakes that queue at **0x800A8504**;
its retrace divider +0x394 and counter +0x395 start at zero at **0x800A813C..40**, so it
permits one loop per retrace, not one per pair of fields. Thus normal NTSC operation is
nominally **60 updates/s and 30 raw key-time units/s** (approximately 59.94/29.97 with NTSC
video timing). Pauses, disabled +0xA0 entries, slow frames and explicit speed changes break a
universal wall-clock mapping. For a normal-speed Blender clip, use 30 fps for raw bank times,
or multiply key times by 2 on a 60 fps scene. Preserve gameplay event windows in 60 Hz update
units; do not apply raw bank times to them without the factor.

`ANIMTick(pipe, mode)` (0x800B7718, MATCH): with a bound track it samples the channels
(scale incl. scale quaternion, quaternion **or** Euler, then translation), stores
`previousTime = time`, then steps. Forward (+0x17 == 1): `time += speed`; past duration,
wrap once if looping, else clamp to duration. Backward: `time -= speed`; below zero,
wrap once if looping, else clamp to zero. Matrix tracks take an early-return path.
Bone+0x136 clears translation interpolation bits when binding (**0x800B7B64..80**).
Matrix construction/skinning follows the updated controls (§5.1).

### 5.1 Local and world matrices (matrix builders MATCH; pose traversal read from asm)

`CTRLBuildMatrix(control, m)` (src/C3/control/control.c, matched): a 0x10 matrix control is copied.
Otherwise `R` = `PSMTXQuat(r)` for CTRL_ROT_QUAT (xyzw, Dolphin convention), or for CTRL_ROT_EULER
the product **Rz·Ry·Rx** of the three axis rotations with angles in **degrees** (applied X first,
then Y, then Z to a column vector); `T` enters as the translation column of that same matrix;
`S` = diag(scale); with CTRL_SCALE_QUAT `Qs` = `PSMTXQuat(q)`. The result is
`M = (T·R) · Qs · S · Qs⁻¹` (`PSMTXConcat` chain d,b,c,a). It reduces to `T·R·S`
only without a scale-axis quaternion. **Correction:** retail tracks do have scale
quaternions (§2; its old survey count 2,763 differs from the listed 2,703 subtotal, not rerun here); do not discard Qs when exporting those tracks. The matched Euler
block has a retail quirk: when X and Z are both nonzero, the `a[0][2]` term of the Z step uses
`m[1][2]` (still identity = 0) instead of `a[1][2]` (= −sin X), so such triples are not exactly
Rz·Ry·Rx; retail character banks use quaternions, where this does not apply.

**Ordinary pose path:** `fn_800B313C` (**matched C**, 2026-10-27; `GameActor.boneRemap` / `remapCallback` at +0x88 / +0x94) builds actorWorld at **0x800B3164..74**, then walks
boneArray. On remapped actors it postmultiplies actorWorld by
`diag(−1,+1,−1)` (**0x80111640**, used at **0x800B3184..94**, a 180° Y rotation, determinant +1).
If animationCtrl.type is nonzero, blend it from blendFromCtrl by the actor weight
(fn_800B84AC); otherwise blend the rest control from blendFromCtrl. Bone animFlags&3 selects
weight 1 (0/default), actor weight (1), or squared actor weight (2), as in
**0x800B31C0..1F4** / **0x800B2E00..3C**. Flag 0x20, with channel bits 4/8/0x10, first restores
selected rest-translation components into blendFromCtrl (**0x800B2E40..7C**).

**Remap/flip rules, high confidence:** for an animated bone and actor+0x88 == NULL,
blend its own control and call plain CTRLBuildMatrix (**0x800B2E8C..EB8**). With a remap table,
actor+0x94 is an optional callback: `(destinationBone, actor->boneArray[remap[0]], outMatrix,
weight)`; a nonzero return means it supplied the matrix and skips the default remap/flip
(**0x800B2EBC..EF0**). Otherwise find the destination's boneID in boneArray, use that array
index to read a **u16 source index** from remap, and blend the source bone's control
(**0x800B2EF4..F58**). The destination's parent pointer selects **FlipY if non-NULL**
(**0x800B2F5C..74**), **FlipX if NULL** (**0x800B2F78..80**). These rules apply to every
animated bone in that path; they are not a hardcoded limb-ID list. A bone without animationCtrl
bypasses remapping/flips and builds its blended rest pose (**0x800B3044..60**).
The regular walker duplicates the same rules at **0x800B3244..3300**.

FlipX/FlipY are conjugations **F·M·F**, with F respectively diag(−1,1,1) at **0x801116D0**
and diag(1,−1,1) at **0x801116A0**. A matrix-type control returns a copy before these flips.
`CTRLBuildMatrix_Flip(control,m,mask)` uses bits 1/2/4 for X/Y/Z reflections and the same
conjugation; **fn_800B2DD0 does not call this mask variant**. Other consumers are
fn_80062F38 at **0x80062F98 / FC0 / FE8** and fn_800637DC at **0x8006383C / 88C**.
`CTRLBuildMatrix_FlipX` C previously used flipY for both concats despite standardized
feedback saying MATCH; corrected to flipX in codex-anim. Relocation/data identity matters.

On the fallback remap path only, **destination byte +0x137** selects an additional local
rotation: 1 → X, 2 → Y, 3 → Z, otherwise none. Every branch passes **π radians**
(**0x803CCF60 = 3.1415927**, `.float`), with axis character 'X'/'Y'/'Z' at
**0x800B2FAC..3000**; concat order **local = flippedLocal · Raxis(π)** at
**0x800B2FBC..3010**. The regular walker repeats it at **0x800B3304..3390**.
Thus there is no single fixed axis for this constant.

If pipe->replaceHierarchyCtrl == 0, build the destination rest control too and
`local = Rest · Anim` (**0x800B3014..303C**, regular path **0x800B3394..33BC**).
When inheritanceFlag == 1 and parent exists, `forward = parent.forward · local`; otherwise
the regular walker uses actorWorld (**0x800B33E4..3420**). Then
`skin = forward · inverseBind`, and lighting uses `(skin⁻¹)ᵀ`
(**0x800B30B4..F4**, duplicated by the regular walker). Actor blending and the per-bone
callback can modify a pose independently of the bank.

**fn_800B2DD0 is a subtree rebuild, not the ordinary frame updater.** Its only external direct
DOL call found is **fn_80026134 at 0x800263C8**, after that function writes a procedurally
adjusted quaternion into bone animationCtrl (**0x800263A8..BC**). It selects the bone through
slot+0x174 (**0x800261D8..1FC**, bone-ID lookup index 9 in the +0x162 table), then recursively
rebuilds children/siblings (**0x800B30F8..3114**). Challenge callers are **fn_1_1073C at REL
0x10788**, and **fn_1_12F8C at REL 0x130B8** after fn_800BDA24 at 0x13060 and when byte
+0x11 is nonzero: both form a direction toward the challenge target. No ordinary per-tick
call to this recursive routine was found. Its no-parent/non-inheriting fallback at
**0x800B3090..9C** reads a stack matrix at +0x98 with no initialization visible in this
function; it must not be cited as proof of actorWorld construction. The normal walker and
fn_800B34B4 provide that evidence. Export the normal pose path and apply procedural aiming
separately if that challenge behavior is wanted.

**CTRLBuildInverseMatrix (already MATCH):** do not assume it is a general inverse of every
CTRLBuildMatrix output. Matrix controls call PSMTXInverse; decomposed controls ignore the
scale-axis quaternion and divide rows by scale. The quaternion path negates all four
components before PSMTXQuat (same rotation for q and −q), **0x800B8848..8888**; the initial
Euler Z test uses the X component for its angle. These are source/asm quirks, not a recommended
exporter inverse. Compute inverse bind matrices from the actual built rest matrices.

### 5.2 Axes and Blender conversion (2026-10-26)

**High confidence: +Y up, right-handed world/transform convention, column-vector affine
matrices.** Camera initialization sets up=(0,1,0): stores at
**0x800BEF50 / 58 / 60** to camera+0xC/+0x10/+0x14, using constants 0/1/0
(**0x803CD070 / 0x803CD07C**). `fn_800BE158` passes that vector to C_MTXLookAt at
**0x800BE438 / 0x800BE454**, and restores its Y component to +1 normally or −1 for
fn_800BEC00's inverted-view mode. `C_MTXLookAt` **0x8007565C** forms
`back=normalize(eye-target)`, `right=normalize(up×back)`, `up=back×right`; its rows are
right/up/back, so camera forward is −Z. The positive-angle X rotation in CTRLBuildMatrix
(**0x800B95B0..9610**) has `[1][2]=−sin`, `[2][1]=sin`, consistent with right-handed
rotation, not a world-space left-handed mirror. Flip conjugations are actor-specific;
they do not change the global coordinate convention.

One proper-rotation conversion to Blender (+Z up) is **(x,y,z)game → (x,−z,y)Blender**
(+90° about X), determinant +1. For full transforms use `M_B = C M_G C⁻¹` (including
translation/rest/inverse bind), quaternion `q_B = q_C q_G q_C⁻¹`, i.e. `(x,−z,y,w)` in xyzw.
No global winding reversal is required by this conversion. Choose the desired horizontal
facing separately; keep the bank's unit scale until a reference measurement establishes units.
This is derived from the matrices; a rendered Blender/Dolphin round trip remains untested.

**Correction (2026-10-27, Blender round trip):** character actor space is **head toward −Y**,
not +Y up. In all 54 bodies the skin vertices and the rest skeleton have feet at Y=0, head at −Y,
face toward −Z; the root bone's +90° X rest rotation maps the Z-up authoring frame there, and
sta_c2.c places objects with `CTRLSetTranslation(.., x, −y, z)`. The mssb-modding glTF exporter
turns every root bone 180° about X (a rotation, not a mirror) so models stand along +Y. GX front
faces wind clockwise: write glTF triangles reversed. Which setup (player worldControl / camera)
flips Y at runtime is not traced.

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
108 body layouts and 54 equal master/disc pairs; build succeeds with 4020 matches (anim-playback).**
Checks cover Mario, Luigi, DK, Peach, Boo, Shy Guy, Dry Bones and every other character,
both body variants; pointer bounds, record spans, finite numbers and key-time monotonicity pass.
Synthetic tests cover all five numeric encodings, fixed quaternion versus track quantization,
sequence/key bounds, decreasing times and hierarchy ID/index distinction. No game C/header ABI
was changed; build/match result is recorded with the commits/final handoff.

Open experiments, with confidence limits:

* **Track 7/8 names / dynamic closure:** §1.1 audits direct and pointer-based DOL/REL
  references and finds no request; high confidence for the traced loaders, not a whole-program
  reachability proof. Instrument ARAMTransfer during menus/challenge/minigames before declaring
  these banks unused. Their visual names remain unknown.
* **Extra pose names:** numeric 105..116 slots established; variants 15/16/17 have sparse/static
  replacements. Do not apply a single pose list to every bank without viewing it.
* **Blender round trip:** the default 0.5 raw-frame/update factor (§5), callback/remap/flip
  conditions (§5.1), +Y up and right-handed conversion (§5.2) are now established from asm.
  Remaining: live timing under pause/slowdown, procedural challenge aiming, and a rendered
  retail-clip round trip. Export recommendations: raw keys at nominal 30 fps; translation
  mode 3 with zero ease or mode 1; neighbourhooded quaternion mode 6; last key at duration.
  Nonzero ease really uses the discontinuous coefficient in §2.1; do not silently repair it.
* **Matching:** constructor remains unchanged after five bounded variants (25 feedback lines
  on this checkout, not the prior note's 12). DoTranslationAnimation/DoScaleAnimation/
  DoEulerAnimation/DoQuatAnimation/Squad remain stubs after scratch candidate experiments;
  no new decoder match is claimed. All five matrix builders already report MATCH; FlipX's
  wrong source matrix reference was corrected separately. See `.scratch/codex_report.md` for
  final source diffs and attempt results. Build remains at 4020 matches.
* **Parser fix needed** (`tools/datamap/animations.py`, mssb-modding): `scale_quaternion` uses the
  track quantization, not fixed s16 (§2); decode the auxiliary payload per §2.1.
