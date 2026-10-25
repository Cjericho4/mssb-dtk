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
  with 90 (`lbl_3_data_4638`).
* **game.rel tables** (section 6): batter reach box (`BatterHitbox`), charge frames, runner turn /
  lead-off frames, fielder action frames, voice ids, foot-contact heights. Layout known for all;
  meaning medium to low for the runner, fielder and foot tables.
* **DOL `lbl_800FB798`** is 15 consecutive s16[54] tables: frame windows (start, end; 99 = never)
  in which `fn_8004B284` / `fn_8004BEB0` / `fn_8004C510` attach an effect to a bone (section 7).

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
`fn_3_4DC14`, `fn_3_8913C` (which in-match effect each one gates: not traced). Batting with
chemistry links on base multiplies power by `lbl_3_data_4618.chemBattingMult`. Menus: star
display `fn_2_75BE4` (character_select.md §8.1), ranking `fn_80067C48` (character_select.md §2),
per-slot rows at `lbl_8034E9A0+0x47F9` (`fn_80066EAC`). Phase 4 edits only the 54×54 bytes;
keep both directions equal.

Header note: `ChemistryTable` names 0x0C `RedKoopa` and 0x2A `GreenKoopa`; `CHAR_ID` says 0x0C is
`KOOPA_GREEN` (the tool uses the CHAR_ID names).

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
* Lineups 1..3 (captain + 4, captain + 4, captain alone) are read by `fn_2_A288` (lineup 1),
  `fn_2_4C3EC`, `fn_2_B920`, `fn_2_BF90` (all stubs): probably CPU / Challenge opponent teams.
  Low.
* The 9 bytes after each lineup (0x0A) are read by the debug path as a per-member value
  defaulting to 0x0A in `lbl_80354720` (a position / link byte); real readers unknown. Low.

## 6. game.rel per-character tables (section 5 `.data`)

Indexed by charID; retail values for Mario / DK / Peach.

| `.data` off | Symbol (Ghidra) | Layout | Readers | Meaning | Mario / DK / Peach | Conf. |
|---|---|---|---|---|---|---|
| 0x6EF8 | `BatterHitbox` | 54 × `BatterReachStruct` (9 f32) | setInMemBatterConstants, calculateContactAndHitType, batterInBoxMovement, setBatterContactConstants, fn_3_1F998 | bat reach box: horizontal near/far, vertical front/back, bat offset x/z, box move speed, pitching height, trimmed bat (0/1) | {-0.65 .55 -0.2 1.5 -2.1 -1.0 .05 1 0} / {-0.55 .65 0.4 1.4 -2.65 -1.0 .05 1 1} / {-0.75 .5 .1 1.5 -1.9 -1.3 .05 1 0} | high (fields named in header) |
| 0x7690 | `ChargePowerConstants` | 54 × u8[2] | setDefaultInMemBatter | `g_Batter.frameFullyCharged`, `frameChargeDownBegins` | 30,60 / 60,60 / 30,60 | high |
| 0x7870 | – | 54 × s16[3] | fn_3_631AC, fn_3_63874 (runner) | [0] frames of a turn-around (vs runner `framesSinceLastDirectionChange`); [1] lead-off anim 0x35 length (minus `leadOffTotalFrameCountDown`); [2] anim 0x2E start frame (-10) | 25,75,42 / 25,75,42 / 27,55,32 | low |
| 0x7E34 | `bodyCheckFrameRelatedConstants` | 54 × u8[4] | fn_3_60E90, fn_3_A96FC (fielder) | [0] start frame passed to anims 0x21/0x23; [1] frame threshold vs `g_FieldingLogic`+0xF6; [2] action length written to +0xF6; [3] window subtracted from [2] | 13,30,120,5 / 6,8,120,5 / 6,8,120,5 | low |
| 0x8148 | `unkCharacterArray` | voice group ids | m_sound | see character_select.md §6 | | (CS) |
| 0x8168 | `characterSoundArray` | 54 × u16 | fn_3_90220 | voice SFX base id | 324 / 298 / 272 | high (CS §1) |
| 0x17000 | – | 54 × s32 | fn_3_BC274, fn_3_BC2DC | foot height threshold ×1e-5 (bones 0x1E / 0x22 vs the actor's y) -> anim-slot flag bits 2/3 at +0x276 (foot down: dust / footsteps) | 55000 / 50000 / 50000 (babies 24000) | medium |

Neighbours that are per *something else*: 0x76FC `hitByPitchHitboxes`, 0x7760 `runnerConstants?`,
0x79B4 `FielderHitboxConsts`, 0x7F10 `barrelCollisionHitboxes`, 0x4744 (contact lerp table).
A clone with a new charID needs a row in every table above (character_modding_report.md §8).

## 7. DOL animation event windows (`lbl_800FB798` .. `lbl_800FBD80`, 15 × s16[54])

Fifteen consecutive 0x6C tables. `fn_8004B284(slot, anim, kind, frame)` switches on the animation
and uses six (start, end) pairs: 798/804, 870/8DC, 948/9B4, A20/A8C, AF8/B64, BD0/C3C. When the
current frame is inside [start, end] it spawns an effect at a bone picked from `lbl_800FBF10`
(+0x214 table, by `fn_800698F8(charID)` and the pair index). `fn_8004BEB0` uses the pair CA8/D14,
`fn_8004C510` the single frame D80. 99 = never. Mario / DK / Peach: 804 = 28 / 36 / 14,
870..8DC = 20..32 / 20..27 / 5..13, D80 = 22 / 99 / 28. Which animation each pair belongs to: not
traced (the jump table `jumptable_800FC318` maps animation ids). Medium (layout), low (meaning).

## 8. Still unknown (R3 partial)

* Meaning of the 0x7870, 0x7E34 and 0x17000 fields beyond "frame / threshold" (section 6), and
  which animation each DOL window pair serves (section 7).
* Captain lineups 1..3 and the 0x0A bytes (section 5); the `lbl_3_data_4638[1]` = 20 threshold.
* What the chemistry checks gate in play (throws, catches, batting links).

## 9. Reproduce

`py mssb_files.py stats-export <disc> stats.json`; the tests (`test_mssb_files.py`: StatsFormat,
`test_stats_round_trip_and_edit`, `test_stats_retail`, `MSSB_SLOW=1` `test_real_stats_import_identical`)
pin the layout and retail values. Game tables: `.obj` blocks in
`build/GYQE01/game/asm/auto_04_*_data.s`; readers: grep the symbol in `build/GYQE01/**/asm`.
