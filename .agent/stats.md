# Character stats and gameplay tables (research track R3, 2026-10-24)

Owns: the `stats.0` file layout, every `CharacterStats` field, star skills and abilities, the
chemistry table, the captain-team presets, the game.rel per-character tables and the DOL
animation-window tables. Tool: `mssb_files.py stats-export / stats-import` (`tools/datamap/README.md`).

## 0. TL;DR

* **One file holds the editable stats:** `stats.0` = ZZZZ.dat+0x06CF8800, 0x46E0 bytes, stored
  (not compressed). Layout: 54 `CharacterStats` rows of 0xA0 (charID order), 0x21C0 bytes nothing
  reads as stats (zero), then 12 captain blocks of 0x48 (Challenge starting teams and 3 more
  lineups each). Edit it with `stats-export` / `stats-import`; the round trip is byte-identical.
* **Every gameplay byte of the row is named and its reader found** (section 2): five pitching
  stats, eight batting stats, speed, arm, class, weight, captain flag, the three star types, a
  14-bit fielding-ability mask, four menu bars and 54 chemistry bytes. High confidence: each one
  is traced from the row into `g_Batter`, `g_Pitcher`, the runner or fielder struct.
* **Unused in the row:** +0x05..+0x1D (25 bytes), +0x71 and +0x74..+0x9D (21 halfwords) are
  copied with the row but never read; all zero in retail. +0x1E/+0x1F, +0x72/+0x73, +0x9E/+0x9F
  are padding. Free for mods (roster_flow.md §6.1 plans +0x05 as the skin byte).
* **Star skills** live in the row (+0x34 captain star, +0x35 swing star, +0x36 pitch star, +0x20
  abilities). The *star-player bonus* is not in the row: it is DOL `lbl_800E86F0` (+50 to every
  stat except the two pitch speeds, which get +20; +2 per bar) applied by `transferStatsToInMemRoster`.
  *Star unlocked* is save data (`lbl_80361B20.characterFlags[charID]`), not the row.
* **Chemistry** is the row's +0x3B..+0x70: 0..99, 50 with itself, stored twice (A,B and B,A;
  symmetric in retail). In-match checks compare it (plus a Challenge item bonus, capped at 100)
  with 90 for positive links and 20 for anti-chemistry throws (`lbl_3_data_4638`, section 4.1).
* **game.rel tables** (section 6): batter reach box (`BatterHitbox`), charge frames, runner turn /
  lead-off frames, fielder action frames, voice ids, foot-contact heights. Layout known for all;
  runner/fielder timing reads are traced in section 6; the foot table remains less certain.
* **DOL `lbl_800FB798`** is 15 consecutive s16[54] tables: seven start/end pairs and
  one exact-frame event. All animation IDs are mapped in section 7; 99 usually disables an event.

## 1. Load chain

`fn_2_554` (menus boot) loads `stats.0` whole into `Static_Stats_Tables` = `lbl_8034E9A0` (DOL
.bss, rows `[charID/9][charID%9]`; the menu state starts right after, at +0x46E0). The roster
copiers copy rows into `inMemRoster[2][9]` (roster_flow.md §2–§3, `COPY_STATS_ROW`). game.rel
copies `inMemRoster` fields into the actor structs at the start of each at-bat / play:
`setInMemBatterConstants` (fn_3_6DE60), `fn_3_6EBB4` (pitcher), `fn_3_6D964` (runner),
`setFielderValues` (fn_3_6E24C). Minigames copy rows with `fn_3_10C450`. A debug path
(`maybeProcessTeamData`, game.rel, descriptor `stats_game`) loads the same file and copies
`file + team*0x5A0` (nine rows) into `inMemRoster`, treating the file as 12 teams of nine rows.

Edits to `stats.0` change every mode. Mid-match the game re-copies rows from the static table
when the star toggle is switched off (`transferStatsToInMemRoster`), so a mod must not rely on
patching `inMemRoster` alone.

## 2. `CharacterStats` row (0xA0, `include/game/UnknownHomes_Game.h`)

Readers were found by a register-taint scan of the asm over `inMemRoster` / `lbl_8034E9A0`
(linear, so not exhaustive) plus reading the copy functions. JSON key = `stats-export` name.

| Off | Type | JSON key / C name | Retail range | Meaning, reader | Conf. |
|---|---|---|---|---|---|
| 0x00 | u8 | `curveball_speed` / CurveBallSpeed | 110..130 | -> `g_Pitcher.curveBallSpeed` (+0x142), fn_3_6EBB4 | high |
| 0x01 | u8 | `fastball_speed` / FastBallSpeed | 150..175 | -> `g_Pitcher.fastBallSpeed` (+0x143) | high |
| 0x02 | u8 | `cursed_ball` / cursedBall | 40..90 | -> `g_Pitcher.cursedBallStat` (+0x144); lerps batted-ball power down by contact quality (`game_batter.c`, `lbl_3_data_5E80`): a "heavy ball" stat | high (read), medium (name) |
| 0x03 | u8 | `curve` / Curve | 30..90 | -> `g_Pitcher.curveStat` (+0x146) | high |
| 0x04 | u8 | `curve_control` / curveControl | 40..90 | -> `g_Pitcher.curveControlStat` (+0x145) | high |
| 0x05 | u8[25] | `unknown."0x05"` / UnusedBytes | 0 | inside the memcpy(0x1E) of every copy, never read | high |
| 0x1E | u8[2] | (in `"0x05"`) / _pad1E | 0 | padding, never copied | high |
| 0x20 | u32 | `fielding_abilities` / FieldingStats | bits 0..13 | ability mask, `checkFieldingStat(team, slot, bit)`; section 3 | high |
| 0x24 | s16 | `char_id` / CharID | = row | identity used everywhere (models, HUD, voices): do not change | high |
| 0x26 | u8 | `throwing_hand` / FieldingArm | 0/1 | -> `g_Pitcher.handedness` (+0x141), fielder, glove side (`fn_8001758C`) | high (read), medium (1 = left) |
| 0x27 | u8 | `batting_hand` / BattingStance | 0/1 | `BATTING_HAND` 0 right, 1 left -> `g_Batter.batterHand` | high |
| 0x28 | u8 | `slap_contact` / SlapContactSize | 30..90 | -> `g_Batter.contactSize_raw[SLAP]` | high |
| 0x29 | u8 | `charge_contact` / ChargeContactSize | 10..45 | -> `contactSize_raw[CHARGE]` | high |
| 0x2A | u8 | `slap_power` / SlapHitPower | 5..60 | -> `hitPower_raw[SLAP]` | high |
| 0x2B | u8 | `charge_power` / ChargeHitPower | 1..95 | -> `hitPower_raw[CHARGE]` | high |
| 0x2C | u8 | `bunt_contact` / BuntingContactSize | 10..80 | -> `g_Batter.buntingContactSize` | high |
| 0x2D | u8 | `trajectory_push_pull` / HitTrajectoryPushPull | 0..2 | -> `g_Batter.trajectoryPushPull` | high |
| 0x2E | u8 | `trajectory_high_low` / HitTrajectoryHighLow | 0..2 | -> `g_Batter.trajectoryHighLow` | high |
| 0x2F | u8 | `speed` / Speed | 10..90 | -> runner `speed` (+0x120, capped at 200; fn_3_6D964), fielder | high |
| 0x30 | u8 | `throwing_arm` / ThrowingArm | 30..100 | fielder throw strength (`setFielderValues`) | high (read) |
| 0x31 | u8 | `character_class` / CharacterClass | 0..3 | `CHARACTER_CLASS` balanced/power/speed/technique -> batter, pitcher, runner | high |
| 0x32 | u8 | `weight` / Weight | 0..4 | -> runner `weight` (+0x11D) | high (read) |
| 0x33 | u8 | `captain` / Captain | 0/1 | 1 for the 12 captains (menus) | high |
| 0x34 | u8 | `captain_star` / CaptainStarHitPitch | 0..12 | `CAPTAIN_STAR_TYPE` -> `g_Batter.captainStarHitPitch` and `g_Pitcher.captainStarPitch` (+0x147); menus (`fn_2_760CC`) | high |
| 0x35 | u8 | `star_swing` / NonCaptainStarSwing | 1..3 | `REGULAR_STAR_SWING` popfly/grounder/linedrive -> `g_Batter.noncaptainStarSwing` | high |
| 0x36 | u8 | `star_pitch` / NonCaptainStarPitch | 1..3 | curve/fastball/change-up -> `g_Pitcher.nonCaptainStarPitch` (+0x148) | high |
| 0x37..0x3A | u8 ×4 | `batting_bar` .. `fielding_bar` / ...StatBar | 1..9 | menu ratings (`fn_2_74F40`; character_select.md §8.1); the scan found no game.rel reader (scan is not exhaustive) | high |
| 0x3B | u8[54] | `chemistry` / chemistry | 5..99 | section 4 | high |
| 0x71 | u8 | `unknown."0x71"` / BytesAfterChemistry[0] | 0 | copied, never read | high |
| 0x72 | u8[2] | (in `"0x71"`) | 0 | padding | high |
| 0x74 | u16[21] | `unknown."0x74"` / UnusedShorts | 0 | copied, never read | high |
| 0x9E | u8[2] | (in `"0x74"`) | 0 | padding | high |

Units are the game's own (pitch speeds look like km/h; bars are 1..10). Challenge items scale
several fields in place at game start (`fn_3_6EF1C`, multipliers `lbl_3_data_5FC4`).

Retail examples (from `stats-export`):

| Field | Mario (0) | DK (2) | Peach (4) |
|---|---|---|---|
| curveball / fastball / cursed / curve / control | 130 / 168 / 60 / 53 / 50 | 130 / 165 / 70 / 35 / 50 | 125 / 165 / 50 / 70 / 90 |
| hands (throw, bat) | right, right | right, left | right, right |
| slap / charge contact, slap / charge power, bunt | 65 / 35, 50 / 64, 35 | 30 / 15, 60 / 80, 20 | 80 / 45, 46 / 45, 45 |
| push-pull, high-low, speed, arm | 0, 0, 50, 60 | 1, 1, 40, 70 | 2, 2, 50, 40 |
| class, weight, captain | balanced, 2, 1 | power, 4, 1 | technique, 2, 1 |
| captain / swing / pitch star | mario / popfly / fastball | dk / popfly / curve | peach / grounder / changeup |
| abilities | wall_jump, sliding_catch | clamber, laser | quick_throw, super_catch |
| bars | 6 6 5 6 | 8 7 4 4 | 4 8 5 7 |
| chemistry with Mario, Luigi, Bowser | 50, 99, 15 | 30, 35, 41 | 95, 90, 9 |

## 3. Star skills and abilities

* **Fielding abilities** (+0x20, u32 mask, `FIELDING_ABILITIES` / `EnumFieldingAbilities`):
  bit 0 wall splat, 1 wall jump, 2 clamber, 3 sliding catch, 4 laser, 5 quick throw, 6 super
  jump, 7 magical catch, 8 tongue catch, 9 suction, 10 super catch, 11 ball dash, 12 body check,
  13 super curve (a *batting* ability: the batted ball curves, `game_batter.c`; a line-drive star swing grants it too). Bits 14..31 unused (0).
* **Captain star** +0x34 (`CAPTAIN_STAR_TYPE`, 0 none, 1 Mario .. 12 Daisy, one per captain);
  used for both the star swing and the star pitch. **Non-captain stars**: +0x35 swing, +0x36
  pitch. Every character has both; captains also have them (used when not captain).
* **Star player bonus**: `lbl_800E86F0[12]` = {50 slap contact, 50 charge contact, 50 slap
  power, 50 charge power, 50 bunt, 50 speed, 50 arm, 20 curveball speed, 20 fastball speed, 50
  cursed, 50 curve, 50 control}, added by `transferStatsToInMemRoster` (+2 to each bar, capped
  at 10) and by `fn_3_10C450` for minigames. Unlock flags: `lbl_80361B20.characterFlags[54]`.

## 4. Chemistry

Row byte +0x3B+k is this character's chemistry with charID k. Retail: 5..99, diagonal 50,
symmetric, colour variants share rows (21–23, 24–26, 29–32, 33–36, 44–47, 48–51). Readers:
`fn_3_6D658(team, a, b)` (game; adds `lbl_3_data_5FC4.unk_28` when the Challenge chemistry item
is bought, caps at 100) compared against `lbl_3_data_4638` = s16 {90, 20, 90, 90} by `fn_3_ABDD0`,
`fn_3_4DC14`, `fn_3_8913C` (effects and exact inequalities below). Batting with
chemistry links on base multiplies power by `lbl_3_data_4618.chemBattingMult`. Menus: star
display `fn_2_75BE4` (character_select.md §8.1), ranking `fn_80067C48` (character_select.md §2),
per-slot rows at `lbl_8034E9A0+0x47F9` (`fn_80066EAC`). Phase 4 edits only the 54×54 bytes;
keep both directions equal.

### 4.1 Threshold gates, traced in retail code (2026-10-24)

The four halfwords have independent uses; 20 is an **exclusive upper bound**, not a second
positive-chemistry threshold. Confidence **high** for each branch and state change:

| Offset / value | Reader and evidence | Gate in play |
|---|---|---|
| +0 / 90 | `fn_3_ABDD0` (`makeThrowVariables` in exported_symbols.csv), 0xABEBC..0xABEFC | Chemistry >=90 between thrower and receiving fielder enables `g_FieldingLogic`+0x13E, provided target is base 0..3 and recipient +0x1F5 equals that base. This is the chemistry-throw state; it selects voice type 0 at 0xAC998, versus regular type 5. Later code consumes/decrements throw-speed state +0x106 and can change the chemistry state 1 -> 2 (0xAC534..0xAC574). This does not establish a universal speed multiplier for every throw. |
| +2 / 20 | same function, 0xABF00..0xABF94 | Chemistry <20 permits a random anti-chemistry throw. Chance is mapped with bytes at 0x4908/4909 (both 20 in retail), then tested against RandomInt_Game(100); practice with `g_Practice`+0x1C2 >=0 suppresses it. Success sets `g_Ball.IsAntichemistryThrow` and perturbs the intended throw angle (0xAC088..0xAC0C8); voice type 10 at 0xAC9B4. Thus low chemistry enables a probabilistic inaccurate throw, not a guaranteed error on every throw. |
| +4 / 90 | `fn_3_4DC14` (`bobbleDirection`), 0x4DCB4..0x4DD30 and 0x4DDC8..0x4DE54 | On a bobble, choose the nearest other fielder whose chemistry >=90 and distance is below the appropriate `lbl_3_data_4618` limit. The subsequent ball direction is aimed toward that teammate with random angular spread, and speed uses the chemistry-indexed `lbl_3_data_5CDC` multiplier. Plays SFX 0x1AB. This is bobble assistance, rather than a catch-success threshold. |
| +6 / 90 | `fn_3_8913C`, 0x897F8..0x8984C | For each occupied runner slot 1..3, chemistry >=90 with the batter increments `g_Batter.chemLinksOnBase` and sets its bit in +0xAB. `game_batter.c` then uses `chemBattingMult[links-1]` for positive charged power. |

`in_game.h` independently names +0x13E `IsChemistryThrow` and voice types 0/5/10
chemistryThrow/regularThrow/antiChemThrow. These support the branch tracing; they are not the
sole evidence. No threshold is a chemistry catch-probability stat.

### 4.2 Character-ID naming audit (2026-10-24)

**High confidence: 0x0C / 12 = Green Koopa, 0x2A / 42 = Red Koopa.** Keep the existing
`CHAR_ID_KOOPA_GREEN` / `CHAR_ID_KOOPA_RED` values. Corrected the two `ChemistryTable`
field names and the reversed `KoopaR` / `KoopaG` labels in `tools/datamap/catalog.py`;
no chemistry bytes, character IDs, or field offsets were swapped.

Evidence, with ID-only checks so the tool's own display labels do not decide the result:

* Retail HUD archive `res.1` (ZZZZ+0x1A6B3000), textures **30+charID**: texture 42 (ID 12)
  has green shell-colour texels; texture 72 (ID 42) has red. Local RGB5A3/CI8 palette analysis
  using `clone_character.TextureFile` / `texture_colour_counts` counted **0 red / 27 green**
  saturated opaque texels for ID12 and **30 red / 0 green** for ID42 (S>=0.5, V>=0.25;
  red H<0.05 or >0.95, green 0.20<H<0.48). The same independent check gives red for ID20
  (25/0), green for ID43 (0/26), agreeing with the Paratroopa names.
* Both user-defined Ghidra enums, `enumCharacterID_byte` and `enumCharacterID_int` in
  `in_game.h`, explicitly give `koopa(G)=12`, `koopaR=42`. Both name ID28 `toadsworth`.
* Retail `stats-export`: both Koopa rows are balanced class, with identical chemistry rows
  (including 50 with each other); ID12 charge power/speed =50/40, ID42 =60/30. Chemistry and
  class therefore **cannot distinguish their colours**; these are consistency checks on row
  identity, not colour evidence.
* `lbl_800E8558` rows: ID12 `{1,12,12,1,0,0}`, ID42 `{1,12,12,0,0,1}`; both share family/base/
  unique index 12, and the latter is its variant. Voice table `lbl_3_data_8168` gives both
  SFX base 168; announcer lookup uses the shared unique index. Voice/announcer identity
  likewise cannot distinguish colours and should not be relabelled as colour-specific audio.
* `extract res.15` and `inspect_menu_ui.py` verify the name-frame map (ID12 -> texture12,
  ID42 -> texture70, ID28 -> texture28) and all 162 name/mini/grid mappings. The name glyph
  textures are distinct, share a greyscale palette, and were not treated as shell-colour evidence.
  Extracted assets stayed outside the checkout; no assets were sent for image interpretation.

Swept `include/`, `src/`, `tools/modding`, `tools/datamap` and `.agent` for character-name
lists and ID/name comments. Normalizing colour prefix/suffix order and catalogue abbreviations,
all **54** `ChemistryTable` fields, `clone_character.CHAR_NAMES`, `stats.NAMES`, and
`catalog.CHAR_NAMES` now agree with `CHAR_ID`. The only other disagreement was catalogue ID28
`ToadsworthR`: removed the unsupported R suffix to match both enums and the other tools.
The clone patcher's default recolour specifications (e.g. a donor recoloured green) describe
requested output colours, not the retail identity, so those remain intact. No further naming
conflicts were found in the scoped source/header/doc sweep.

## 5. The rest of `stats.0`

| File offset | Size | Content | Readers | Conf. |
|---|---|---|---|---|
| 0x21C0 | 0x21C0 | zero; no reader except the debug `maybeProcessTeamData` (as rows 54..107) | none in play | high |
| 0x4380 | 12 × 0x48 | captain blocks, order Mario, Peach, Wario, DK, Yoshi, Bowser, Luigi, Daisy, Waluigi, Diddy, Birdo, Bowser Jr. Each = 4 lineups × {9 charIDs (0xFF empty), 9 bytes (all 0x0A)} | see below | |

* Lineup 0 = the Challenge starting team (9 charIDs; only the six Challenge captains and block 11,
  Bowser Jr with Dry Bones, have one). `fn_2_12238` (and twins `fn_2_12CD8`, `fn_2_12F88`) finds
  the captain's block index (0..5, else `OSPanic`) and copies it into
  `lbl_803C6724.teams[0]` and `starMissionCompletionTracker.lineup`. `fn_80068838` reads block 11.
  High.
* **Lineups 1/2 are roster-select templates; lineup 3 is the captain-only fallback. High.**
  `fn_2_A288` checks both candidate templates against the opposing captain: it starts at
  block+0x12+1 and checks eight member bytes, then advances by 0x12 for the second template
  (0xA3A8..0xA4C0), so it deliberately excludes each template's own captain slot.
  `fn_2_B920` calls that check and randomly selects a usable template: result 0 -> lineup 1,
  result 1 -> lineup 2, none -> lineup 3 (0xBB4C..0xBBE8). It copies the chosen side-0 template
  to `lbl_803C6724.teams[0]`; side 1 starts with lineup 3 (0xBBE8..0xBCEC).
  `fn_2_BF90` independently starts side 1 with lineup 0. Thus these are menu team presets,
  not four CPU difficulty levels. The exact UI conditions choosing each entry path are not
  fully traced. Retail export corrects the earlier shorthand "captain +4": lineup 1 has
  **4..7** members and lineup 2 **4..5**, varying by captain; every lineup 3 has one.
  `fn_2_4C3EC` reads lineup 0 while forming the Challenge availability mask, not lineups 1..3.
* **The nine 0x0A bytes feed a debug batting-order/link field; authoring intent still uncertain.**
  High confidence for data flow, medium for the sentinel interpretation. In `maybeProcessTeamData`,
  0x128..0x214, each of nine roster slots searches lineup-0 members for its slot index. On a hit,
  byte `block[9 + memberIndex]` goes into `lbl_80354720[team][slot].unk2`; missing entries default
  to 10 as well. Normal menu code writes `lbl_803C6724.order` into that same field
  (`fn_2_4970`, `fn_2_8940`), and `fn_2_5F80` uses it to restore batting-order links.
  Retail `stats-export` and `extract stats.0` confirm all **432** extra bytes are 0x0A,
  including unused lineups. No normal roster-select reader of these extra bytes was found.
  Ten is outside the nine valid order slots, consistent with "unassigned"; it is not evidence
  for an AI difficulty or character stat. The debug loader also treats the first 0x4380 bytes
  as twelve nine-row teams, unlike the normal 54-row file, so do not assume its schema is the
  retail menu schema. Keep the JSON key `extra` until an active authoring/use case is established.

## 6. game.rel per-character tables (section 5 `.data`)

Indexed by charID; retail values for Mario / DK / Peach.

| `.data` off | Symbol (Ghidra) | Layout | Readers | Meaning | Mario / DK / Peach | Conf. |
|---|---|---|---|---|---|---|
| 0x6EF8 | `BatterHitbox` | 54 × `BatterReachStruct` (9 f32) | setInMemBatterConstants, calculateContactAndHitType, batterInBoxMovement, setBatterContactConstants, fn_3_1F998 | bat reach box: horizontal near/far, vertical front/back, bat offset x/z, box move speed, pitching height, trimmed bat (0/1) | {-0.65 .55 -0.2 1.5 -2.1 -1.0 .05 1 0} / {-0.55 .65 0.4 1.4 -2.65 -1.0 .05 1 1} / {-0.75 .5 .1 1.5 -1.9 -1.3 .05 1 0} | high (fields named in header) |
| 0x7690 | `ChargePowerConstants` | 54 × u8[2] | setDefaultInMemBatter | `g_Batter.frameFullyCharged`, `frameChargeDownBegins` | 30,60 / 60,60 / 30,60 | high |
| 0x7870 | – | 54 × s16[3] | fn_3_631AC, fn_3_63874 (runner) | [0] turn-around state duration; [1] lead-off animation end-frame anchor; [2] animation 0x2E entry-frame anchor (minus 10). Evidence below. | 25,75,42 / 25,75,42 / 27,55,32 | high (timing/data flow), unknown (physical meaning of 0x2E) |
| 0x7E34 | `bodyCheckFrameRelatedConstants` | 54 × u8[4] | fn_3_60E90, fn_3_A96FC (fielder) | [0] body-check reaction animation entry frame; [1] countdown threshold before looped reaction starts; [2] knockback/recovery countdown; [3] elapsed frames before collision-result processing. Evidence below. | 13,30,120,5 / 6,8,120,5 / 6,8,120,5 | high (timer operations), medium (animation labels) |
| 0x8148 | `unkCharacterArray` | u8[32] voice group id per unique index | fn_3_90F48 | see sounds.md §3 | | (SN) |
| 0x8168 | `characterSoundArray` | 54 × u16 | fn_3_90220 | voice SFX base id (lines +0..12) | 324 / 298 / 272 | high (SN §3) |
| 0x17000 | – | 54 × s32 | fn_3_BC274, fn_3_BC2DC | foot height threshold ×1e-5 (bones 0x1E / 0x22 vs the actor's y) -> anim-slot flag bits 2/3 at +0x276 (foot down: dust / footsteps) | 55000 / 50000 / 50000 (babies 24000) | medium |
| 0x79B4 | `FielderHitboxConsts` | 54 × 16 B (8 s16) | setFielderValues | fielder collision geometry, scaled by `charSizeMultipliers[charID][0]` | | high (#38) |
| 0x7F10 | `barrelCollisionHitboxes` | 54 × s16 | fn_3_60A98, fn_3_128C18, fn_3_142DB4, fn_3_1430D0 | character height, scaled by `charSizeMultipliers` | 200 / 240 / 240 (Toads 150) | high (#38) |

Neighbours that are per *something else*: 0x76FC `hitByPitchHitboxes`, 0x7760 `runnerConstants?`,
0x4744 (contact lerp table). (0x79B4 and 0x7F10 were listed here before #38; both are indexed by
`CharacterStats.charID` in `setFielderValues`.)

**Model scale (main.dol, not game.rel):** `charSizeMultipliers` at 0x800E8300 (file 0xE5300), 54 ×
{f32 in game, f32 menu scene}, indexed by charID. `fn_8001D2D4` passes it to `CTRLSetScale` for every
actor (column 1 only when `g_hugeAnimStruct.field269_0x307a == 5`, set by menus.rel). It also scales
the batter's bat height (`setBatterContactConstants`: `PitchingHeight * charSize[id][0]`) and the two
fielder tables above. Mario 1.18 / 1.10, DK 1.11 / 1.00, Peach 1.18 / 1.08, Toads 1.40 / 1.32. A clone
must take its source's row together with 0x79B4 and 0x7F10 (#38).
A clone with a new charID needs a row in every table above (character_modding_report.md §8).

### 6.1 Timing evidence (2026-10-24)

* **Runner +0, high:** `fn_3_63874` chooses tracking state 7 while turningAroundInd is set and
  framesSinceLastDirectionChange < this value, otherwise state 2. It is a turn-state cutoff,
  not a speed/acceleration scalar.
* **Runner +2, high:** `fn_3_631AC` at 0x637B8..0x637F8 (tracking state 0x10, selected by
  leadOffStatus ==2) starts nonlooped animation **0x35** at `value - leadOffTotalFrameCountDown`.
  `in_game.h` calls it RunnerWalkAwayFrom2ndBase. The anchor gives the correct elapsed frame
  when resuming a lead-off; it is not independently proven to be the entire animation length.
* **Runner +4, high for formula, still unknown for physical animation:** same function at
  0x63298..0x63300 selects **0x2E** at `value - 10` during the initial <10 frames of direction
  change, for family/grid IDs 0x0E/0x14/0x1A/0x1E and outside secondary mode 6.
  Ghidra's name is only Runner_Tpose; no stronger animation name is justified.
* **Fielder +0/+1, high for formula:** `fn_3_60E90`, 0x61070..0x61100, enters nonlooped
  animation **0x21** at byte 0, or starts looped **0x23** at that frame once
  `bodyCheckStageCountdown <= byte 1`. The exported enum calls 0x23 FielderStunned;
  0x21's FielderTagBase? label is uncertain and is not adopted as a field name.
* **Fielder +2/+3, high:** `fn_3_A96FC` (`fielderBodyCheck_setStatus+Pos+Velo` in the export)
  enters stage 3 with countdown = byte 2 (0xA97B0..0xA9804), applies decaying knockback velocity,
  decrements each frame, and at exactly `countdown == byte2 - byte3` calls `fn_3_A9354(idx,0)`
  and updates knockout/ball-control flags (0xA9820..0xA986C). Stage ends at countdown <=0.
  Thus byte 3 is elapsed frames to that processing event, **not a final-five-frames window**.
  Byte 2 is 120 and byte 3 is 5 in the cited Mario/DK/Peach rows. The exact collision-result
  handling of `fn_3_A9354` remains unnamed; the event itself is established.

## 7. DOL animation event windows (`lbl_800FB798` .. `lbl_800FBD80`, 15 × s16[54])

The complete animation mapping is now traced. **High confidence for IDs/table associations**;
**medium for physical animation names**, which use the user-defined exported enum in `in_game.h`
(`EnumCharacterAnimation_short/int`) and agree with runner/fielder call sites.

| Start / end table | Animation ID | Exported animation name | Selection evidence |
|---|---|---|---|
| 0x800FB798 / 0x800FB804 | 0x32 (50) | RunnerDiveTurnAround | `jumptable_800FC318[0x32-0x1A]` -> fn_8004B284+0x5C |
| 0x800FB870 / 0x800FB8DC | 0x33 (51) | Runner_BodyCheck | jump table -> +0xC0 |
| 0x800FB948 / 0x800FB9B4 | 0x34 (52) | RunnerDiveTurnSide | jump table -> +0x124 |
| 0x800FBA20 / 0x800FBA8C | 0x1A (26) | FielderPickUpBall | jump table -> +0x188 |
| 0x800FBAF8 / 0x800FBB64 | 0x1B (27) | FielderDive | jump table -> +0x1EC |
| 0x800FBBD0 / 0x800FBC3C | 0x30 (48) | RunnerSkidStop | jump table -> +0x250 |
| 0x800FBCA8 / 0x800FBD14 | 0x10 (16) | FielderOnFire | `lbl_800FBDEC[0x10]` =1 -> `lbl_800FBE64[1]` = fn_8004BEB0 |
| 0x800FBD80 (single frame) | 0x62 (98) | BatterHitByBall | `lbl_800FBDEC[0x62]` =9 -> fn_8004ACF4 -> callback [2] = fn_8004C510 |

`fn_8004B284` accepts an inclusive [start,end] frame interval, chooses a bone from
`lbl_800FBF10+0x214` by grid and pair kind (0,1,2,4,5,6), and spawns an effect there.
The final single-frame callback checks **frame equality**, not an interval, and gets the slot's
coordinates with `fn_8001B728(slot,4,...)`. Its wrapper also marks a special early hit-by-pitch
flag for Dry Bones IDs 48..51 at frame <0.5. Do not describe all fifteen arrays as bone windows.
`fn_8004BEB0` also uses an inclusive interval; its separate per-character coordinates are in
`lbl_800FC494`. Retail Mario / DK / Peach examples remain 804 =28/36/14,
870..8DC =20..32 / 20..27 / 5..13, D80 =22/99/28. The common 99 values appear to disable events
for these animations; a universal "never" interpretation outside their frame lengths is not proven.

## 8. Still unknown (R3)

* Visual identity of runner animation 0x2E remains unknown. R5 traced runner sequence1 and
  the flying families, and found moving versus placeholder clips: `animations.md` §4. The entry
  frame formula remains table+4 minus ten (section 6.1); no physical C name is justified.
* The 0x17000 foot-height table's exact dust/footstep effect selection (outside this pass).
* Original authoring meaning / active retail use of the captain extra 0x0A bytes beyond their
  debug batting-order/link destination. Tried all four menu captain-table readers and the
  debug loader; ordinary menu paths copy only the nine character IDs (section 5).
* Full UI path selection for captain-template presets, and a single physical name for every
  body-check reaction animation. The roster-template exclusion logic and timer operations are
  established; no speculative C names were added for those uncertain parts.

## 9. Reproduce

`py mssb_files.py stats-export <disc> stats.json`; the tests (`test_mssb_files.py`: StatsFormat,
`test_stats_round_trip_and_edit`, `test_stats_retail`, `MSSB_SLOW=1` `test_real_stats_import_identical`)
pin the layout and retail values. Game tables: `.obj` blocks in
`build/GYQE01/game/asm/auto_04_*_data.s`; readers: grep the symbol in `build/GYQE01/**/asm`.

2026-10-24 evidence reproduction in this checkout: `stats-export orig/GYQE01 /tmp/r3-stats.json`
and `extract orig/GYQE01 stats.0 /tmp/r3-retail` (read-only input). Captain counts and all 432
extra bytes were checked against those retail outputs. Animation dispatch and all gameplay
branches above were read from `build/GYQE01/{asm,game/asm,menus/asm}` and cross-checked with
`src/`, `exported_symbols.csv`, and `in_game.h`; no game assets are checked in with these notes.
