# Roster -> match data flow (research track R2, 2026-10-24)

How a team picked on the roster screen becomes the in-match roster, and how each player's
roster entry reaches the character loaders.  Written for phase 3 (the skin picker): the point is to
know where a per-player skin byte can live so that it survives from the menu into the match and is
read by the loaders that pick the body and textures.

Addresses are DOL RAM unless prefixed `fn_2_` (menus.rel) / `fn_3_` (game.rel).  Function status
is from `build/GYQE01/report.json` and `tools/feedback_diff.py` (2026-10-24).  The model load chain
below `fn_8001758C` is in `character_modding_report.md` §1.  The reader/writer audit in section 4
comes from a register-taint scan of every `.s` unit that references `inMemRoster`
(`scan_roster.py`, described there); the rest from reading the matched C and the target asm.

## 0. TL;DR (answers to the three questions)

1. **Menu -> roster.**  The picks live in menus.rel `lbl_803C6724.teams[side][slot]` (s8 charIDs)
   and `.order[side][slot]` (batting order).  On "ready" (`fn_2_5444`) nothing is copied for an
   exhibition game; the copy happens in the roster finalisation `fn_2_3204 -> fn_2_2FC0(mode, 1, 1)`,
   mode 9/10:
   `fn_2_8940` copies `Static_Stats_Tables[teams[side][n]]` into `inMemRoster[side][n]` **in pick
   order** (and `lbl_80354720[side][n].unk2 = order[side][n]`), then the DOL
   `characterSelectScreen(side)` (0x80065DEC) **re-copies the nine entries in fielding-position
   order** (position <- charID, from `lbl_80109054` class preferences + chemistry + random).  Both
   use the same field-by-field copy of the 0xA0 row (section 3.4) that was clearly one inlined helper
   in the original.  Challenge mode writes only `stats.CharID` in `fn_2_5444` and relies on the same
   `fn_2_8940` pass.  Practice/minigames build the roster from game.rel (`fn_3_B4124`,
   `fn_3_10C450`, whole-row `memcpy` 0xA0).
   **`StatTable.UnusedBytes` (+0x05..+0x1F) is never read or written as a field by any module**,
   but it is *not* untouched: bytes +0x05..+0x1D sit inside the `memcpy(dst, src, 0x1E)` that every
   field-wise copy starts with, so each rebuild resets them from the static row (all zero in retail
   `ZZZZ.dat+0x06CF8800`); bytes +0x1E/+0x1F (and +0x72/+0x73, +0x9E/+0x9F) are structure padding
   that only the whole-row `memcpy(0xA0)` / `memcpy(0x5A0)` paths touch.
2. **Roster -> actor.**  game.rel drives three DOL state machines:
   `fn_3_6BD6C -> fn_8001594C(g_GameLogic.teamFielding)` (nine fielders),
   `fn_3_6BA64 -> fn_8001500C(teamBatting, g_Runners[i].rosterID, 9 + i)` (batter + 3 runners) and
   `fn_3_6B4C8 / fn_3_6B5D8 -> fn_80016344(charID, 12 or 9, ...)` (cutscene/star slots).  All end in
   `fn_80017098(team, player, arg1B, slotKind, variant, -1)`, which reads `inMemRoster[team][player]
   .stats.CharID` into a load task, and `fn_8001758C`, which stamps the slot record (`charID` 0x252,
   `team` 0x256, `player` 0x257, `variant` 0x259, roster bytes 0x26/0x27 -> 0x25A/0x25B) and picks
   the body file.  **`variant` is 1 only for the batter (slotKind 9) and for menu/cutscene loads**;
   fielders (0..8) and runners (10..12) load with `variant = 0`, i.e. the low-detail body from disc
   subfile track `charID*19 + 1`, never the ARAM body pair.  The smallest skin hook is in
   `fn_8001758C` state 0: read the skin from the same `inMemRoster[team][player]` entry it already
   reads for 0x26/0x27, store it in the free slot byte 0x253, and branch the two body sources on it.
3. **Lifetime.**  Characters are unloaded by `fn_80011BE4(slot)` (runners at 3 outs / after each
   play in `fn_3_6B870`, batter per at-bat) and re-loaded through the same drivers: fielders at each
   half-inning change (`fn_3_5CDB4` / `fn_3_5D5E8` -> `fn_3_6BD6C`), batter and runners at every
   at-bat (`fn_3_6BA64`), substitutions via the pause menu (`fn_800471F4` swaps the roster entries,
   `fn_80047CE0`/`pauseMenuSelection` re-run `characterSelectScreen`).  Every re-load goes through
   `fn_80017098 -> fn_8001758C`, which re-reads `inMemRoster[team][player]`, and `fn_80017098`'s
   reuse scan keys on (team, player, charID, 0x26, 0x27, unk258, variant).  So a skin that lives in
   (or is re-applied into) the roster entry persists for the whole match; one that lived only in the
   slot record would not, because slot records are rebuilt on every load.

## 1. Structures

| Object | Where | Layout |
|---|---|---|
| `inMemRoster[2][9]` | DOL .bss 0x80353BE0, 0xB40 | `CharacterStats` 0xA0 each: `StatTable stats` (0x3B), `chemistry[54]` (+0x3B), `BytesAfterChemistry[3]` (+0x71), `UnusedShorts[21]` (+0x74), 2 pad |
| `StatTable` | +0x00 | `CurveBallSpeed, FastBallSpeed, cursedBall, Curve, curveControl` (+0..4), **`UnusedBytes[27]` (+0x05..+0x1F)**, `FieldingStats` u32 (+0x20), `CharID` s16 (+0x24), `FieldingArm` (+0x26), `BattingStance` (+0x27), contact/power/… bytes (+0x28..+0x36), 4 stat bars (+0x37..+0x3A) |
| `lbl_8034E9A0` (`Static_Stats_Tables` / `MenusSaveState`) | DOL .bss, 0x4C28 | 54 rows of 0xA0 loaded from `ZZZZ.dat+0x06CF8800` at boot (menus `gap_0.c:161`), indexed `[charID/9][charID%9]`; then menu state: `selected[2]` (+0x46E0 captain charIDs), `indices[2]` (+0x4708 captain roster index, misnamed `captainVariant` in gap_6B4C8.c), `charTaken[54]` (+0x4757), `rankedByChemistry[5][54]` (+0x478D), per-(side,slot) chemistry rows (+0x47F9 + side*0x51 + slot*9, 9 bytes, written by `fn_80066EAC`), **star flags `resetData[18]` (+0x489B + side*9 + slot)**, star-toggle counters (+0x4720 + side*4) |
| `lbl_803C6724` (`MenusTeamSelections`) | DOL .bss | `teams[2][9]` (+0x02), `order[2][9]` (+0x14), `selectionFlags[2][9]` (+0x26), **`unk38[2][9]` (+0x38): no reader or writer in any module (free)**, `unk4A[2][9]` (+0x4A, badge bytes used by menus and `fn_2_79764/81628`), +0x53..+0x5B flags |
| `lbl_80354720[2][9]` | DOL .bss, 0x48 | 4 bytes per slot `{unk0, unk1, unk2 = batting order / position link, byte3}`; all four bytes are referenced (byte 3: 40 accesses), none free |
| `lbl_802E4B00[18]` | DOL .bss | copy of the star flags for game.rel (written by `transferStatsToInMemRoster`, `fn_800471F4`) |
| `starMissionCompletionTracker.lineup[9]` | +0x40B8 | challenge lineup `{s16 charID; u8 slot; s8 order; u8 pad[2]}` (6 bytes, two spare) |
| `g_hugeAnimStruct` (0x8036E548) | DOL .bss | `slots[13]` (+0xC04, `Gap8001196CAnim` 0x27C), `slotPtrs[13]` (+0x2C50), `loadState` (+0x2D77), reuse result (+0x2D78), `currentSlot` (+0x2D79), runner cursor (+0x2D7A), fielder cursor (+0x2D7B), `loadedCharID[13]` (+0x2D7F), `bankLoadStep` (+0x2D8D), fielder-bank step (+0x2D8E), cached batter model {ptr +0x2D54, size +0x2D58, charID +0x2D5C}, cached runner model {+0x2D3C, +0x2D40, +0x2D44} |
| `Gap8001196CAnim` (slot record) | 0x27C | `fileBuffer` (+0x08), anim banks (+0x10..+0x24), `stadiumObj` (+0x2C), `subItems` (+0x30), `charID` s8 (+0x252), **`_pad253` (+0x253): no access in any module, neither as `0x253(slotPtr)` nor as `g_hugeAnimStruct+0xE57+n*0x27C`; the game.rel `0x253` hits are `Fielder.unk253` in `g_Fielders`** , `slotKind` (+0x254), `blockIndex` (+0x255), `team` (+0x256), `player` (+0x257), `unk258`, `variant` (+0x259), roster 0x26/0x27 copies (+0x25A/+0x25B), `isBatter` (+0x278) |

## 2. Menu -> roster, step by step

### 2.1 Picking (menus.rel, `src/menus/gap_1254.c`)
* `fn_2_DFAC` (matched): confirm the hovered grid charID into `lbl_803C6724.teams[side][slot]`,
  `order[side][slot]`, taken flags, badge (`fn_800506E8`), chemistry ranking; requests UI 0xF.
* `fn_2_3624` (5 scheduling lines left): cursor moves; the **L colour cycle** calls
  `fn_2_A040(group, choice, side, slot)` (matched) which replaces `teams[side][slot]` with the next
  free member of the `lbl_80108EDC` family row.  This is the retail "variant" mechanism: a colour
  is another charID.  Phase 3 replaces it with a skin index that keeps the charID.
* `fn_2_4970` (matched): undo a pick; clears `teams/selectionFlags/unk4A[side][slot]`.
* `fn_2_102C8`: auto-fill.  `fn_2_7DDC` (matched): open the screen.

### 2.2 Ready (`fn_2_5444`, menus 0x5444, 0x3A4, documented non-matching)
* Challenge (GameModeSelected 5): for n<9 `starMissionCompletionTracker.lineup[n] = {teams[0][n], n,
  order[0][n]}`, `inMemRoster[0][n].stats.CharID = teams[0][n]`, `lbl_80354720[0][n].unk2 =
  order[0][n]`; UI 0x13 to both sides; `lbl_803CBBCC->state = 8`.
* Exhibition: only state changes (`state = 3` hand-over on a shared pad, `state = 7` when both sides
  are ready).  **No roster write.**

### 2.3 Finalisation (`fn_2_3204 -> fn_2_2FC0(lbl_803297E0.mode, finish=1, rebuild=1)`, matched)
Mode 9/10 (also `fn_2_8ED4C -> fn_2_2FC0(9, 0, 1)` and `fn_2_8EEC8`, `fn_2_11698`, `fn_2_323C`):
1. `charTaken` reset, captains taken, `markLockedCharsTaken()`, `fn_80067F70(0/1)` (CPU auto-pick).
2. **`fn_2_8940`** (menus .text 0x8940, 0x3B8, MATCH): for side 0..1, n 0..8:
   `copyStatsRow(&inMemRoster[side][n], &Static_Stats_Tables[teams[side][n]])` (section 3.4),
   `lbl_80354720[side][n].unk2 = order[side][n]`; in challenge mode side 0's `FieldingArm/
   BattingStance` come from the per-character handedness save `lbl_2_bss_3A8[lineup[n].charID]`.
   Then mirrors `teams[0][]` / `teams[1][]` into `lbl_803C5EA4` (+0x12.., s16) and calls
   `fn_80066EAC(0)`, `fn_80066EAC(1)` (per-(side,slot) good-chemistry rows, +0x47F9).
   Roster order here = **pick order**.
3. `fn_800678CC(side)` (0x800678CC, 0x1FC, stub): select-screen bookkeeping
   (`fn_80067264`, `fn_800675C4`); no roster write.
4. `unsure_FillRosterPositions(side)` (0x80064A04, 0x13E8, stub): reads `lbl_803C6724`,
   `lbl_8034E9A0`, three `randRange` calls; no `inMemRoster` access.
5. **`characterSelectScreen(side)`** (0x80065DEC, 0x10C0, stub; asm + m2c read): the
   fielding-position assignment.  Snapshots the nine current `inMemRoster[side][i].stats.CharID`
   and `lbl_803C6724.order[side][i]`; builds `pos[9]` (stack, -1 = empty) with the first slot's
   (captain's) preferred position `lbl_80109054[class*5]`, pitchers from `lbl_80108EC4`, each
   remaining charID into its class's first free preferred position (`lbl_80109054[class*5 + k]`,
   k<5, with chemistry ordering through `rankedByChemistry`), random free position when all five
   are taken; then `for pos<9: copyStatsRow(&inMemRoster[side][pos], &Static_Stats_Tables[pos[pos]])`
   and rebuilds `lbl_80354720[side][]` links.  Roster order after it = **fielding position**
   (slot 0 pitcher … 8).  Callers: `fn_2_2FC0`, `fn_80047CE0` and `pauseMenuSelection`
   (in-game pause menu, after a substitution).
6. `fn_80069854` (matched): `indices[side]` = roster index of the captain.
7. `fn_800671FC` (stadium), `fn_800649BC` (start).

Re-entering the roster screen: `fn_2_5F80` (matched) rebuilds `teams[team][i]` from
`inMemRoster[team][j].stats.CharID` through the `lbl_80354720[].unk2` link and resets `order`.
`fn_2_8CF8` (0x8E0) / `fn_2_9ACC` (0x4A4) copy whole rosters between `inMemRoster`,
`lbl_80354720`, `lbl_2_bss_3E4` and the menus backups `lbl_2_bss_E8CC` (2×0x5A0) /
`lbl_2_bss_DCE8` (2×0x24) with the same field-wise copy (lineup edit backup/restore);
`fn_2_11EA8` (`fn_2_12F88`) and `fn_2_5163C` (`fn_2_51C58`) are two more static-row copies on
other menu screens.  `fn_2_20D08 -> fn_80068838` (0x80068838, 0xF78, stub) loads a saved lineup
(`lbl_8034E9A0 + 0x4380 + idx*0x48`, or +0x4698) into `inMemRoster` and `teams[]` with the same
copy.  `fn_800415A8` (0x800415A8, 0xAD4, stub) builds CPU teams the same way.

### 2.4 Other roster writers
* **Practice / minigames (game.rel):** `fn_3_B4124(team, slot, charId, hand)` (matched):
  `memcpy(&inMemRoster[team][slot], &lbl_8034E9A0[charId], 0xA0)` then `FieldingArm/
  BattingStance` from `hand`; sets `g_GameLogic.battingOrderAndPositionMapping` and
  `lbl_80354720[team][slot]`, `fn_80011BE4(slot)` unload.  `fn_3_10C450(slot, charID)` (matched):
  same whole-row copy into team 0 plus the star bonus `lbl_800E86F0[12]` when
  `g_Minigame.players._18D0[slot+4]`.  Also whole-row copies in `fn_3_108C54`, `fn_3_10C58C`,
  `fn_3_10E60C`, `fn_3_10F91C`, `fn_3_10FDC8`, `fn_3_B42A8`, `fn_3_B43E8`.
* **Debug team select (game.rel `maybeProcessTeamData`, rep_0):** pad-driven; `ARAMTransfer
  (lbl_3_data_0)` then `memcpy(inMemRoster[0], buf + a*0x5A0, 0x5A0)`, `memcpy(inMemRoster[1],
  buf + b*0x5A0, 0x5A0)`.  Not reachable from the menus.
* **Star toggle (`transferStatsToInMemRoster(side)`, 0x800426DC, 0x514, decompiled, 26 lines):**
  called by `startGameRelated` (pre-game lineup screen, 0x80048EB8) and `fn_8005A350` (star menu).
  Not in challenge mode.  slot = `lbl_803297E0+0xCF46+side` (1-based cursor) - 1; requires
  `lbl_80361B20.characterFlags[CharID]` (star unlocked); toggles `resetData[side*9+slot] ^= 1` and
  copies the side's 9 flags to `lbl_802E4B00[side*9]`; then `copyStatsRow` from the static row and,
  if the flag is set, adds `lbl_800E86F0[k]` to the 12 ability bytes and +2 to each stat bar
  (capped at 10).  **This re-copy overwrites +0x00..+0x1D of the entry in-game.**
* **Substitution (`fn_800471F4`, 0x800471F4, ~0xAEC, stub; m2c read):** called twice by
  `fn_8004617C` (pause menu).  Swaps two roster entries through a stack copy with the field-wise
  copy, and swaps the parallel per-slot rows (`+0x47F9` chemistry, `+0x489B` star flag,
  `lbl_802E4B00`, `lbl_80354720`).  Followed by `fn_80047CE0` / `pauseMenuSelection ->
  characterSelectScreen(side)`.

### 2.5 Saves and replays
* The game save (`g_d_GameSettings`, `starMissionCompletionTracker`) never contains `inMemRoster`;
  the challenge lineup is 9 × `ChallengeLineupEntry` (charID, slot, order, 2 pad bytes) and is
  re-expanded by `fn_2_8940` on load.  Saved exhibition lineups (`fn_80068838`) store charIDs only.
* There is no saved-replay feature.  The in-match replay (`g_ReplayCopies` 0x114BC /
  `g_ReplayLogic`, game.rel .bss) snapshots game.rel state; no module copies `inMemRoster` into it.
* challenge.rel never references `inMemRoster`.

## 3. The copy itself

### 3.4 `copyStatsRow(dst, src)` (inlined in every DOL/menus copier)
Identical instruction sequence in `fn_2_8940`, `fn_2_8CF8` (4×), `fn_2_9ACC` (2×), `fn_2_11EA8`,
`fn_2_5163C`, `characterSelectScreen`, `fn_80068838` (2×), `fn_800415A8`,
`transferStatsToInMemRoster`, `fn_800471F4` (3×):

```
memcpy(dst, src, 0x1E);                       /* +0x00..+0x1D  pitching + UnusedBytes[0..24] */
dst->CharID = src->CharID;                    /* +0x24 (lha/sth) */
dst->FieldingArm = …; dst->BattingStance = …; /* +0x26, +0x27 */
memcpy(dst+0x28, src+0x28, 2); memcpy(dst+0x2A, src+0x2A, 2);
+0x2C..+0x34 byte by byte; memcpy(+0x35, 2); dst->FieldingStats = src->FieldingStats (+0x20, lwz/stw);
memcpy(+0x37, 4); memcpy(+0x3B, 0x36);        /* stat bars, chemistry */
+0x71 byte; +0x74..+0x9C 21 halfwords.
```
Never copied: **+0x1E, +0x1F**, +0x72, +0x73, +0x9E, +0x9F.  That is exactly the alignment padding
of a struct `{u8 pitch[0x1E]; u32 fielding; s16 charID; …; u8 chem[54]; u8 b71; s16 shorts[21];}`,
so the original `StatTable` almost certainly ends its first byte block at +0x1D and
`UnusedBytes` is really 25 bytes + 2 pad.

## 4. Every reader and writer of `inMemRoster` bytes +0x05..+0x1F

Method: `.agent/probe/scan_roster.py` (`python3 .agent/probe/scan_roster.py inMemRoster a0
$(grep -rl inMemRoster build/GYQE01/*/asm build/GYQE01/asm)`) taints every register derived from
`inMemRoster@l` (`addi`, `add`, `mr`, `addi` chains, update-form loads) inside each function of
every `.s` unit that mentions the symbol (DOL 7 units, game.rel 25, menus 4, challenge 0) and
reports each load/store displacement mod 0xA0, every `memcpy`/`memset` with a tainted r3/r4, and
every other `bl` with a tainted r3..r8 (to catch pointers passed down).  1429 accesses.

* **Field accesses:** histogram of in-entry offsets = {0x00..0x04, 0x20, 0x24 (401×), 0x26..0x3A,
  0x3B..0x40, 0x71, 0x74..0x9C}.  **Zero accesses at 0x05..0x1F** in any module.
* **Block copies that cover the range:**
  * `memcpy(entry, staticRow, 0x1E)` in the 11 `copyStatsRow` users above (+0x05..+0x1D reset).
  * `memcpy(entry, staticRow, 0xA0)`: `fn_3_B4124`, `fn_3_10C450`, `fn_3_108C54`, `fn_3_10C58C`,
    `fn_3_10E60C`, `fn_3_10F91C`, `fn_3_10FDC8`, `fn_3_B42A8`, `fn_3_B43E8` (practice/minigames).
  * `memcpy(inMemRoster[t], debugBuf, 0x5A0)`: `maybeProcessTeamData` (debug).
  * menus backups: `fn_2_8CF8`/`fn_2_9ACC` entry <-> `lbl_2_bss_E8CC` (field-wise, so +0x05..+0x1D
    travel with the entry, +0x1E/+0x1F do not).
* **Pointers passed to callees** (checked, none touch the range): `fn_8001594C` (team row),
  `fn_8001C588` (×4, entry: anim lookups), `fn_3_1659A0`, `fn_3_9EE24` (×2), `fn_8006C398`,
  `fn_80014D4C`, `fn_3_90220`, `fn_800698F8` (×2), `fn_3_90C14`, `fn_800363D8` (×2),
  `fn_8005C830`, `fn_80064918` (×2), `translateStarPitchHitIndex`, `sndFXStartEx`,
  `fn_8001C67C_animation`, `fn_8001C920`, `_OSAllocFromHeap`, `fn_800675C4`,
  `fn_800B0A5C_insertQueue` (task fields 0x26/0x27 are the roster bytes, not pointers).
* **Static rows** (`lbl_8034E9A0[charID]`, the source): the 54 retail rows have all of
  +0x05..+0x1F = 0; the block is loaded once from disc and only `fn_3_10C450`-style bonuses write
  the roster copy, never the static rows.

Conclusion: nothing *reads* the bytes, so a value there cannot be misread; but a value at
+0x05..+0x1D is **overwritten by every rebuild** (ready, position assignment, substitution,
star toggle, lineup edits, CPU team build, saved-lineup load), and a value at +0x1E/+0x1F stays
with the *slot* (not the player) across the field-wise re-copies and is reset by the 0xA0 copies.

## 5. Roster -> actor

### 5.1 Drivers (game.rel -> DOL)
| Driver | When | Call |
|---|---|---|
| `fn_3_6BD6C` (gap_6B4C8.c) | game scene states `fn_3_5CDB4` (0x5CDB4) and `fn_3_5D5E8` (0x5D5E8) from the dispatcher `fn_3_6011C` (start of a half-inning / after the inning-change cutscene); minigames `fn_3_ADA3C`; practice `fn_3_B43E8/B51E4/B5818/B6994`; `fn_3_15B494`; DOL `challengeMapRelated` | first call: `fn_8001196C()`, resets 0x2D77/0x2D7B/0x2D7C; in gameStatus 9 forces arm/stance for class 0x19; then `fn_8001594C(g_GameLogic.teamFielding)` until it returns 1 |
| `fn_3_6BA64` | every at-bat (states calling it in gap_5985C.c:637, gap_B3B70.c:783/835, gap_AC9F8.c:714/1019) after `fn_3_6B870` unloaded the runner slots | for runner i = 3..0: `fn_8001500C(g_GameLogic.teamBatting, g_Runners[i].rosterID, 9 + i)` if `rosterID >= 0` |
| `fn_3_6B4C8` (`fn_3_22C20`, star cutscene) | | `fn_80016344(lbl_8034E9A0.selected[humanTeam], 12, 1, lbl_8034E9A0.indices[humanTeam])` then re-points `slotPtrs` |
| `fn_3_6B5D8` (`fn_3_5BD40`) | | `fn_80016344(lbl_80353A90.field_0x103, 9, 0, 0)` |
| menus `fn_2_481F4` (rep_08E8) | character preview | `fn_80016710(charID, slot)` |
| game `fn_3_10C81C` (gap_106DFC) | minigames | `fn_80016710` (×2) |

### 5.2 `fn_8001594C(team)` (0x8001594C, 0x9F8, stub; asm read): the nine fielders
State byte `g_hugeAnimStruct+0x2D7B` is the fielder slot being loaded, `+0x2D77` the shared
load state.  loadState 2 -> register `slotPtrs[cursor] = &slots[currentSlot]`, cursor++;
cursor 9 -> 10.  Then per cursor:
* 10: `fn_80015468(team)` (0x80015468, 0x4E4, stub): clears `loadedCharID[0..8]` of charIDs that no
  loaded slot carries, then for the first slot whose charID is not yet in `loadedCharID` streams
  its shared anim bank: `ARAMTransfer(&lbl_803CB790[charID*19 + 4])` into `animBankA` (+0x18)
  (or track 17 into `animBank` +0x24 when `+0x2D7C` is set), `ANIMGet` when `lbl_803C6CF8.allowLoad`.
  Returns 1 when all nine charIDs have their bank.  Fielders that share a charID share the bank
  (`+0x2CC0[n]` per charID).
* 11: stadium/extra object per slot through `lbl_80118220` (same `loadStadiumObject` logic as
  `fn_80016344`, with `lbl_803CBBF8/BC2C/BC34` deciding which slots need one).
* 12: `fn_80013680(slotPtrs[k])` (bat/glove loader) for k = 0..8, then back to the slot search.
* otherwise (a slot still empty): find `k` with `lbl_80354720[team][k].unk2 == cursor` (the roster
  index playing this position; 9 if none) and **`fn_80017098(team, k, 0, cursor, variant = 0, -1)`**;
  on reuse (returns 1) loadState = 2.

### 5.3 `fn_8001500C(team, player, slotKind)` (0x8001500C, 0x45C, decompiled, 48 lines): batter and runners
loadState 2 -> `slotPtrs[slotKind] = &slots[currentSlot]`, 3 -> `fn_80017340()` + stadium-object
decision (`lbl_803CBC34` bytes), 4 -> stadium object (`loadStadiumObject`), 5 -> `fn_80013680`,
else **`fn_80017098(team, player, 1, slotKind, variant = (slotKind == 9), -1)`**: the batter gets
the ARAM hi-detail body, runners the low-detail disc body.

### 5.4 `fn_80017098` -> task -> `fn_800177B4` -> `fn_8001758C` (matched)
* `fn_80017098(team, player, arg1B, slotKind, variant, charIDOverride)`: with override < 0 it scans
  the 13 slots for `charID == inMemRoster[team][player].stats.CharID && 0x25A/0x25B == entry 0x26/
  0x27 && player == player && team == team && unk258 == arg1B && variant == variant` and re-owns the
  slot without any file read; otherwise queues a `Gap8001196CLoadTask {slot, team, player, arg1B,
  slotKind, variant, charID = entry.CharID}`.
* `fn_8001758C(state, slot, charID, team, player, arg6, slotKind, variant)` state 0: stamps the slot
  record, copies `inMemRoster[team][player]` bytes 0x26/0x27, `track = charID*19 + (variant == 0)`,
  then the body: cached batter model (`cachedBatterCharID == charID`, variant 1, slotKind 9) or
  cached runner model (`cachedFielderCharID == charID`, variant 0, slotKind 10..12) by `memcpy`;
  else `variant == 1`: `fn_8002204C(charID, buf)` (ARAM master body `lbl_800F73B8[charID][0]` +
  overlay `[1]`), falling back to `ARAMTransfer(&lbl_803CB790[track])` (disc track 0 / 1).
  State 1 -> `fn_80017814(anim, blockIndex, slotKind, fn_8001FDD4)` (relocation, textures, actor).
* The two model caches are filled by `fn_80014E50(charID)` (batter) / `fn_80014F40(charID)`
  (runner) from game.rel, and invalidated (-1) by `fn_80018270` (allocation) and `fn_3_5AE9C`
  (scene init).  They are keyed on charID only.

### 5.5 Variant byte
`Gap8001196CAnim.variant` (0x259) = 1: body from the ARAM blob through `lbl_800F73B8` (hi-detail
track-0 file + optional texture overlay); = 0: body streamed from disc, subfile track 1 (low-detail).
Callers: batter (slotKind 9) 1, runners 0, fielders 0, `fn_80016344`/`fn_80016710` 1.  The
data-only patcher covers both because it patches tracks 0 and 1 and the ARAM pair.

### 5.6 Lifetime
* `fn_80011BE4(slot)` (0x80011BE4, 0xC4, stub; asm read): `slotPtrs[slot] = NULL`, releases the
  stadium object (`index1 = -1`, `unk5C = -2`) and the sub-item entry, clears `unk25C`, and sets
  every `slotOwner[i]` (0x2D6A, 13 bytes) equal to `slot` to -1 (frees the owner mapping; the same
  loop shape ends `fn_8001594C` at 0x80016200).  `loadedCharID[]` (0x2D7F) is pruned separately by
  `fn_80015468`.  Called by `fn_3_6B870` (runners whose base is
  empty, all four batter/runner slots at 3 outs), `fn_3_B4124`, minigame resets.
* Fielders persist through a half-inning; the other team's nine are loaded at the change by
  `fn_3_6BD6C`.  Slots are reused when `fn_80017098`'s scan matches (same team/player/charID/…),
  so no disc read happens when the same player returns.  The model caches short-cut the
  batter -> runner transition for the same charID.
* Because every (re)load path ends in `fn_8001758C` reading `inMemRoster[team][player]`, a byte in
  the roster entry is re-applied to the slot record on every load; nothing else carries per-actor
  state across unloads.

## 6. Phase-3 design (per-player skin without losing a roster slot)

### 6.1 Storage
1. **Menu choice:** `lbl_803C6724.unk38[2][9]` (DOL .bss, +0x38), verified unreferenced by every
   module (no field access, and no `memcpy`/`memset` over the object either: the scanner's
   call rows for `lbl_803C6724` are only scalar arguments; `lbl_803C66B0`'s 0x64-byte reset in
   `fn_2_1BAC` ends before it): rename it `skin[2][9]`.  Written by the L-button path in `fn_2_3624` / `fn_2_A040`
   (cycle `skin[side][slot]` modulo `skinCount[charID]` instead of changing `teams[side][slot]` for
   characters that have skins), cleared with the slot in `fn_2_4970` and `fn_2_DFAC`, read by the
   mini-image refresh (`fn_2_776A0`, `fn_2_74F40`) to pick a frame.
2. **Roster entry:** `StatTable.UnusedBytes[0]` (+0x05), inside the 0x1E block.  Choosing a byte
   *inside* the block is deliberate: the field-wise swap in `fn_800471F4` and the backups in
   `fn_2_8CF8/9ACC` then move the skin with the player for free; the three static->entry copies on
   the exhibition path must re-apply it (6.2).  Do not use +0x1E/+0x1F: they stay with the slot
   index across swaps.
3. **Slot record:** `Gap8001196CAnim._pad253` (0x253) -> `skin`, written once per load by
   `fn_8001758C`.

### 6.2 Writers (static->entry copies that must carry the skin)
| Site | Change |
|---|---|
| `fn_2_8940` (menus) | after `copyStatsRow`: `inMemRoster[side][n].stats.UnusedBytes[0] = lbl_803C6724.skin[side][n]` (pick order = roster order here) |
| `characterSelectScreen` (DOL) | it already snapshots the nine CharIDs before re-copying; snapshot the nine skins too and, when writing position `pos` from charID `c`, take the skin of the first not-yet-consumed old entry with `CharID == c`.  Duplicates then keep their pick-order skins. |
| `transferStatsToInMemRoster` (DOL) | `u8 skin = e->UnusedBytes[0]; copyStatsRow(); e->UnusedBytes[0] = skin;` |
| `fn_800471F4` (DOL) | nothing: entry <-> entry copies include +0x05 |
| `fn_800415A8`, `fn_80068838`, `fn_2_11EA8`, `fn_2_5163C`, practice 0xA0 copies | nothing (skin 0 = retail look); saved lineups lose the skin unless the 0x48-byte lineup record is extended (two spare bytes per `ChallengeLineupEntry`, none known in the exhibition record) |

### 6.3 Readers (the loader)
| Site | Change |
|---|---|
| `fn_8001758C` state 0 (matched; `gap_8001196C.c`) | `anim->skin = entry->stats.UnusedBytes[0];` next to the 0x26/0x27 copy; body choice: `variant == 1` -> `fn_8002204C_skin(charID, skin, buf)`; else `ARAMTransfer(skin ? &skinSubfiles[charID][skin-1] : &lbl_803CB790[track], …)` |
| `fn_80017098` reuse scan (matched) | add `slots[i].skin == inMemRoster[team][player].stats.UnusedBytes[0]` (the scan already keys on player, so this only matters if a skin changes mid-match; cheap to add) |
| `fn_8002204C` (matched; `gap_8001E460.c`) | `lbl_800F73B8[charID]` -> `skinPairs[charID][skin]` = `{bodyEntry, overlayEntry}` (skin 0 = retail row); overlays appended to the ARAM blob exactly as `clone_character.py` does (blob move + `fn_800227E4` size immediates) |
| model caches `fn_80014E50` / `fn_80014F40` / the two compares in `fn_8001758C` | compare `(charID, skin)` or skip the cache when `skin != 0` |
| `fn_80016344` / `fn_80016710` / `fn_80017814` / anim banks (incl. track 15) / gloves / `jumptable_800EEC40` / stats / voice | unchanged (all keyed on charID; a texture skin needs none of them) |

### 6.4 Data
* `skinPairs[54][N]` (s8 pairs) and `skinSubfiles[54][N-1]` (`DiskFileDesc`, low-detail bodies for
  fielders/runners) as initialised C arrays next to `lbl_800F73B8` / `lbl_800F1D78` in
  `src/Unknown/gap_8001E460.c`; `skinCount[54]`.  Skin files: a recoloured copy of the hi-detail
  texture archive (overlay, ARAM path) and a recoloured low-detail `.gpc` (disc path), both produced
  by the existing patcher code paths.
* Menu art: `fn_2_74F40` / `fn_2_776A0` use common sequence 0x83 / 0x82 with frame = charID; a skin
  needs either extra frames (append to the common file's sequence) or the base frame plus a label.

### 6.5 Minimal first build
`configure.py --non-matching` with `Equivalent` units `Unknown/gap_8001196C.c` (fn_8001758C,
fn_80017098), `Unknown/gap_8001E460.c` (fn_8002204C + tables), `menus/gap_1254.c` (fn_2_8940,
fn_2_3624/fn_2_A040) and `Unknown/gap_80041348.c` (transferStatsToInMemRoster).  The position
re-copy in `characterSelectScreen` can be deferred for a first test by making the skin choice
"n-th duplicate gets skin n" (count earlier same-charID entries in `inMemRoster[team]` inside
`fn_8001758C`): zero menu changes, survives every re-copy, and proves the loader side in Rio.

### 6.6 Risks
* `characterSelectScreen` (0x10C0) and `fn_800471F4` are undecompiled: patching them means
  finishing their C first (asm/m2c read is complete; the copy loops are mechanical).
* The star toggle and substitution screens re-copy entries in-game; any site missed resets the
  skin to 0 silently (visible as the retail look, never a crash).
* `fn_80017098`'s reuse scan would keep an old skin's model if the roster skin changed while the
  slot stayed loaded; adding the 0x253 compare closes it.
* The overlay mechanism replaces the texture archive in place: a skin archive must have the same
  texture count/dimensions as the base (the patcher already checks this).
* The override path (`fn_80016344` / `fn_80016710` -> `fn_80017098(0, player, ...)`) hard-codes
  `team = 0`, so `fn_8001758C` reads `inMemRoster[0][player]` for 0x26/0x27 and would read the skin
  from team 0 even for a team-1 captain cutscene.  Retail behaviour for arm/stance; the design
  inherits it (use `lbl_8034E9A0.indices[team]` with the right team if it matters).
* "Slot 0 = pitcher" in 2.3 step 5 is inferred from the `lbl_80108EC4` pitcher list and the
  `lbl_80109054` preference rows, not verified against the game's position numbering.
* The audit scanner is a linear register-taint pass without control flow: a roster pointer stored
  to a global and reloaded elsewhere would be missed (no such store was seen in the hits).
* Shared-header changes made with R2 (`CharacterStats` union, `fn_80025FFC` with two arguments):
  the match count confirms no matched function regressed, but the unmatched callers of
  `fn_80025FFC` (`fn_80012B90`'s helper, `fn_80016344`, `fn_80016710`) changed shape.

## 7. Function status on this path

| Function | Module / unit | Size | Status (2026-10-24) |
|---|---|---|---|
| `fn_2_DFAC`, `fn_2_4970`, `fn_2_7DDC`, `fn_2_2FC0`, `fn_2_A040`, `fn_2_5F80` | menus gap_1254 | | MATCH |
| `fn_2_3624`, `fn_2_5444`, `fn_2_102C8` | menus gap_1254 | | documented, non-matching |
| `fn_2_8940` | menus gap_1254 | 0x3B8 | **MATCH** (`copyStatsRow` / `COPY_STATS_ROW` helper, `CharacterStats` layout fixed) |
| `fn_2_8CF8`, `fn_2_9ACC`, `fn_2_11EA8`, `fn_2_5163C`, `fn_2_20D08` | menus | | stubs; purpose documented above (m2c read) |
| `characterSelectScreen` | DOL gap_80064754 | 0x10C0 | stub; documented (asm + m2c) |
| `unsure_FillRosterPositions`, `fn_800678CC`, `fn_80066EAC`, `fn_80068838`, `fn_800415A8` | DOL | | stubs; roles documented |
| `transferStatsToInMemRoster` | DOL gap_80041348 | 0x514 | decompiled, 26 lines (saved-register numbering, one CSE'd base) |
| `fn_800471F4`, `fn_80047CE0`, `pauseMenuSelection`, `startGameRelated`, `fn_8005A350` | DOL | | stubs; roles documented |
| `fn_3_B4124`, `fn_3_10C450`, `fn_80069854`, `fn_80017098`, `fn_8001758C`, `fn_8002204C` | | | MATCH |
| `fn_3_6BD6C`, `fn_3_6BA64`, `fn_3_6B4C8`, `fn_3_6B5D8`, `fn_3_6B870` | game gap_6B4C8 | | C bodies present |
| `fn_8001500C` | DOL gap_8001196C | 0x45C | decompiled, 48 lines (loop temporaries one register apart) |
| `fn_80015468`, `fn_8001594C`, `fn_80011BE4`, `fn_80018270` | DOL gap_8001196C | | stubs; documented in section 5 |
| `fn_80016344`, `fn_80016710` | DOL gap_8001196C | 0x3CC, 0x450 | documented, non-matching: 32 / 28 lines (two CSE temps vs. params; `charID` is s32, `fn_80025FFC` takes 2 args) |
| `fn_80017814` | DOL gap_8001196C | 0x514 | documented, non-matching (48 lines, prologue scheduling) |
