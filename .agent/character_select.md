# Character select / roster: how a pick becomes a charID (partial map, 2026-10-23)

Goal: a real per-player colour/skin choice, and eventually more than 54 characters.  This is the
map of the code and tables involved.  Function status from `build/GYQE01/report.json`;
addresses are DOL RAM unless prefixed `fn_2_` (menus.rel) / `fn_3_` (game.rel).

## 1. Tables

| Table | Where | Shape | Meaning |
|---|---|---|---|
| `lbl_800E8558` (`characterStaticIndexes`) | DOL .data 0x800E8558 | 54 × 6 B | per slot: `{family 0..9, baseCharID, uniqueIdx 0..31, isBase, isCaptain, colourIdx}`. Family ids: 1 koopa, 2 toad, 3 shy guy, 4 paratroopa, 5 pianta, 6 noki, 7 bros, 8 magikoopa, 9 dry bones. |
| `lbl_80108EDC` | DOL .data | 9 × 5 s16 (−1 padded) | colour-family lists: `[12,42] [13,29..32] [20,43] [16,44..47] [21,22,23] [24,25,26] [33..36] [48..51] [27,52,53]` (the symbol is 0x11C long; other data follows) |
| `lbl_80108DB8` (`mainCharArray`) | DOL | 33 u8 | grid index → base charID (also `lbl_800E869C`, 32 B) |
| `lbl_80108DDC` (`secondaryCharacterArray`) | DOL | 22 u8 | variant charIDs, mapped to their base's grid index by the `jumptable_801091F4` switch in `fn_800698F8` |
| `lbl_800FDE84` | DOL | 36 u8 (0xFF empty) | exhibition roster grid cells (base charIDs only) |
| `lbl_800FE5D4` | DOL | 12 u8 | captain grid `{0,1,4,6,2,9,5,17,11,3,10,19}` |
| `lbl_8034E9A0 + 0x4757` (`charsOnCharacterGridSelected`) | .bss | 54 u8 | per-charID "taken" flags while building rosters |
| `lbl_8034E9A0` (`Static_Stats_Tables`) | .bss 0x4C28 | 54 × 0xA0 `CharacterStats` first | loaded from ZZZZ.dat+0x06CF8800 by menus.rel `gap_0.c:161` at boot; copied into `inMemRoster[team][slot]` by game.rel `fn_3_B4124` / `fn_3_10C450` (`memcpy(..., &lbl_8034E9A0[charId], 0xA0)`) |
| `lbl_80108DF4` | DOL | 33 u16 | announcer name call-out SFX per grid index (`fn_800628D4`) |
| game.rel `.data+0x8168` | game.rel | 54 u16 | voice SFX base per charID (`m_sound.c` `fn_3_90220`) |
| `lbl_803CB748` | sdata | 6 u8 | unique indices that need an unlock (`fn_80024C04`, matched) |

Readers of `lbl_800E8558` (DOL): fn_80024C04, fn_8004D460/4F0, fn_8004E504/5B4, fn_80050138,
fn_800506E8, fn_800596D4, fn_8006CDC0, the star-mission menu functions; menus.rel: fn_2_2FC0,
fn_2_348C, fn_2_7DDC, fn_2_1C860, fn_2_42708..fn_2_466AC (records/star screens); game.rel: 20+.
Readers of `lbl_80108EDC`: fn_800415A8 (CPU team builder), fn_80067AC8, fn_80067B40, fn_80067F70;
menus.rel: fn_2_104FC, fn_2_3624, fn_2_4970, fn_2_6884, fn_2_6D3C, fn_2_7DDC, fn_2_A040, fn_2_C324,
fn_2_C484, fn_2_DFAC, fn_2_F200, fn_2_FAA0, fn_2_FCB4.

## 2. The select flow

1. Grid → base charID: the roster/captain grids hold base charIDs (`lbl_800FDE84`, `lbl_800FE5D4`),
   read through `lbl_800E8558[charID].baseCharID`.  `fn_800506E8` (matched), `fn_8004E504` /
   `fn_8004E5B4` (matched, captain grid), `fn_8004D460` / `fn_8004D4F0` (matched, other grid set).
2. Colour assignment: a family's members are "taken" in `charsOnCharacterGridSelected`.
   * `fn_80067AC8(charID, column)` (matched): family row lookup; returns `row[column]` or −1.
   * `fn_80067B40(charID, value, mode)` (decompiled this pass, see gap_80067AC8.c): writes `value`
     into the taken flag of every member of charID's family unless `mode == 2`; returns 1 if the
     charID is in a family.
   * `fn_80067C48(u8 idx)` (0x328, stub, asm read): NOT colour resolution. It takes roster entry
     `lbl_8034E9A0.selected[idx]` (team = v/9, slot = v%9 → `CharacterStats` row), copies the row's
     54 chemistry bytes (+0x3B..) and the ids 0..53 into two stack arrays, selection-sorts them by
     chemistry descending, and stores the sorted id list at `lbl_8034E9A0 + 0x478D + idx*54`
     ("characters ranked by chemistry with this player", used by the roster UI).
   * `fn_80067F70(s32 player)` (0x534, stub, asm read; the player index is passed as 0/1): the **auto-pick**.  Stores `selected[idx]` into
     `lbl_803C6724[idx*9+2]`, calls `fn_80067C48(idx)` (chemistry ranking), builds a 54-byte stack
     list of ranked ids whose taken flag is 0 (unrolled 9×6), compacts the −1 holes, then
     `randRange_FUN_80042bf0(0, 19)` picks one of the first 20 candidates (retry while −1), marks it
     taken and marks its whole `lbl_80108EDC` family taken (same walk as fn_80067B40).  So the "next
     free colour" for a *human* pick is decided in menus.rel (fn_2_2FC0/3624/4970/7DDC/DFAC use
     `fn_80067AC8(charID, column)` to step to the next family column); the DOL side only has the
     taken flags, the family walk and this CPU picker.  menus.rel callers: `fn_2_2FC0`, `fn_2_3624`, `fn_2_4970`, `fn_2_7DDC`, `fn_2_DFAC`
     (src/menus/gap_1254).  CPU teams: `fn_800415A8` tries family columns 1..4.
   * There is no colour button in the UI: the n-th pick of a family base gets the next free member.
3. charID → roster: game.rel `fn_3_B4124` / `fn_3_10C450` memcpy the `CharacterStats` row (CharID at
   +0x24) into `inMemRoster[team][slot]`; `fn_8001758C` later copies `stats.CharID` into the actor.
4. Names / portraits / voice are keyed by **grid index** (`fn_800698F8` = `findCharacterID`,
   charID → 0..31, OSPanic if the id is in neither array), not by charID; so variants share their
   base's name/portrait/call-out.

## 3. Where a per-player skin choice could live

* Storage: `inMemRoster[team][slot].stats.UnusedBytes[0]` (per roster entry, survives into the
  actor via `fn_8001758C` → `AnimationStruct._rest253`).  It must be set per *entry*, not per charID
  (the stats row is shared by every copy of a character).
* UI: the natural hook is the colour resolution in `fn_80067C48` / `fn_80067F70`: instead of (or in
  addition to) moving the pick to another charID, write a skin index into the roster entry and keep
  the charID.  The menus.rel callers above are where the pick is confirmed.
* Rendering: `lbl_800F73B8[charID]` → `{body, overlay}` is the ARAM texture mechanism; a
  `skinPairs[charID][skin]` extension consulted by `fn_8002204C` (matched) gives the look.  See
  `.agent/character_modding_report.md` §9.

## 4. What must change to exceed 54 characters

* Every table above is sized 54 (or 33/22/32 grid-side): `lbl_800E8558`, `lbl_800F73B8`,
  `lbl_800F1D78` (54×19), master descriptor tiers (`lbl_803CB7E0` = {54, 378, 54, 29}),
  `lbl_800EEAAC`, `lbl_800EEB18`, `lbl_800FB798` (15×54), the stats block (54×0xA0, and the
  54-byte chemistry row inside each entry), game.rel's charID tables, the jump tables (0..47).
* Bounds checks: `fn_80021BBC` / `fn_8002204C` / `fn_80021CA4` (`charID < 0x36`), `fn_80067C48` /
  `fn_80067F70` (`cmpwi 0x36` loops), `fn_800698F8` (OSPanic if not in main/secondary arrays),
  "0x36 = empty slot" sentinel in many menu loops, `fn_80064918` (charID → category switch 0..51).
* Grid/UI: grid index space is 0..31 (+0x20 alternate Birdo); portraits/names/call-outs are
  grid-keyed, so new characters need new grid cells (`lbl_800FDE84` has 36 cells, 26 used) and new
  entries in `mainCharArray`, `lbl_800E869C`, `lbl_80108DF4`, plus the menus layout resources.
* Practical path: keep 54 charIDs, add skins (section 3).  Going beyond 54 means relocating every
  table in a `--non-matching` build (`gap_8001E460.c` already defines the disc tables as C arrays).

## 5. Next functions to decompile (ranked)

1. `fn_80067C48` (0x328) and `fn_80067F70` (0x534), gap_80067AC8.c: the colour resolution; the
   skin hook goes here.  Both only use `lbl_80108EDC`, `lbl_8034E9A0` and `fn_80067AC8`.
2. `fn_800698F8` (0x170): decompiled (24 diffs: prologue hoist + local jump-table name), body in
   gap_80067AC8.c; `lbl_8034E9A0.useAltBirdoGrid` (0x48AE) added to the struct.
3. menus.rel `fn_2_2FC0` (**matched 2026-10-23**), `fn_2_3624`, `fn_2_4970`, `fn_2_7DDC`, `fn_2_DFAC`
   (src/menus/gap_1254): the roster screen logic that calls the above.
   * `fn_2_2FC0(u8 mode, s32 finish, s32 rebuild)`: the roster rebuild entry, keyed on the menu mode
     (`lbl_803297E0.mode`).  Modes 9/10: memset the 54 taken flags (`charsOnCharacterGridSelected`,
     `lbl_8034E9A0.charTaken`), mark both players' picks (`lbl_8034E9A0 + 0x46E0/0x46E4`) taken, then
     for each of the 6 locked uniques `lbl_803CB748[i]` set the taken flag of every charID with that
     `lbl_800E8558[c].uniqueIdx` to `!g_d_GameSettings.charUnlocked[i]` (bytes 0x1A..0x1F), then
     `fn_80067F70(0/1)` (auto-pick + family walk), `fn_2_8940`, `fn_800678CC(0/1)`,
     `unsure_FillRosterPositions(0/1)`, `characterSelectScreen(0/1)`, `fn_80069854`; mode 12 (or
     `rebuild` after 9/10): `fn_800671FC` and, if `finish`, `fn_800649BC`.  Mode 9 runs `fn_800684A4`
     first.  Callers: `fn_2_3204` (mode, 1, 1), `fn_2_8ED4C` (9, 0, 1).  So locked characters are
     excluded from the colour walk the same way as already-picked ones: a modded extra charID is
     only hidden from picking if its uniqueIdx is one of the six in `lbl_803CB748` and the flag is 0.
     `fn_2_348C` (0x144, **matched 2026-10-23**) is the same locked-unique loop standing alone
     (no `bl` to it in menus.rel): `for i<6: locked = (charUnlocked[i] == 0); for c<54: if
     (lbl_803CB748[i] == lbl_800E8558[c].uniqueIdx) charTaken[c] = locked`.
   * `fn_2_4970(u8 side, s32 captainID)` (**matched 2026-10-23**): undo the latest pick of a side (B button
     path of `fn_2_CE44`, captainID = `lbl_8034E9A0.players[side]`).  Finds the slot whose
     `lbl_803C6724.order[side][k]` equals the cursor `lbl_2_bss_F468.cursor[side]`; captain slot -> only
     step the cursor back; else record `prevCursor[side]`, step back, and release the slot's character:
     `markSlotTaken()` (the fn_2_C698 body as a static inline: charTaken=1, `fn_800506E8(owner, id, 1)`
     cell badge, `fn_80067B40(side, id, 1)` family taken) then `fn_800506E8(side, id, 0)`,
     `fn_80067B40(side, id, 0)`, `charTaken[id] = 0`; challenge mode (GameModeSelected 5) instead
     un-takes the family *base* (`fn_80067AC8(id, 0)`) only if no other member of the family is still
     on the team.  Then `selectionFlags/teams(-1)/unk4A[side][slot]` are cleared, `flags37[side] = 0`,
     `fn_800625A4(side, 0x10)`.  `lbl_2_bss_F468.flags37/flags3D[side]` are "pick pending" bytes: when
     set, the release happens without moving the cursor.  `fn_800506E8(value, charID, set)` (DOL,
     matched) finds the `lbl_800FDE84` grid cell holding charID's base and writes `value`
     (controller index) or -1 into `lbl_803C6028.slots[cell]`: that is the per-cell "picked by Pn"
     badge, keyed by **base charID**, so a clone donor's cell is what gets badged.
   * `fn_2_7DDC(void)` (**matched 2026-10-23**): opens the roster screen (callers `fn_2_86EC`, `fn_2_CCBC`,
     `fn_2_110B0`).  Clears the taken flags (not in challenge mode), builds the pad-role bytes for
     `fn_80050FE8` (DOL stub) from `lbl_8034E9A0.controllerIndices` and `g_d_GameSettings._10`, sets both
     cursors (`lbl_2_bss_F468.cursor[]`) to 10 (9 after menu 0xB or in challenge mode), then: challenge
     mode = `markChallengeRecruits()` (recruited `starMissionCompletionTracker.missions[c]._31 == 1` ->
     free, else taken; badge unless the family base is recruited) + team 0's charIDs taken with their
     whole family; normal = `markLockedCharsTaken()` + both teams' charIDs taken/badged/family-taken.
     Then per side `lbl_2_bss_F410.gridPick[side]` = charID 0 (P1) / 9 (P2), or the first free cell of
     `lbl_800FDE84[0..31]`, placed with `fn_80050138` (DOL stub), and `fn_800625A4(side, 9|0xA)`.
     Nothing in it chooses portraits/banners: everything is keyed by charID or by base charID
     (`fn_800506E8`'s cell lookup).
4. `fn_800415A8` (0xAD4): CPU team builder (colour columns 1..4).
5. game.rel `fn_3_B4124`, `fn_3_10C450`: roster → `inMemRoster` copy (skin byte lands here).
6. `fn_80067B40(arg0 unused, s16 charID, u8 value)`: 8 register-choice diffs left (key should land
   in r7, walkers r6/r4); value == 2 is the "query only" mode.

## 6. UI / announcer lookup map (2026-10-23, pass 5) and the `--ui source` patch

Everything that *presents* a character is keyed by the **unique index** (0..31, one per distinct
character; variants share their base's) or, for one HUD element, by **charID** into a per-charID
texture set.  The two unique-index routes agree for all 54 retail charIDs (test_clone.py checks it):
`lbl_800E8558[charID].uniqueIdx` == `fn_800698F8(charID)`.

| What | Keyed by | Lookup | Asset |
|---|---|---|---|
| Announcer name call-out | unique (via `fn_800698F8`) | `fn_800628D4(charID)` (matched this pass): `useAltBirdoGrid = 1; sfx = lbl_80108DF4[grid]; sndFXStartEx(sfx, lbl_80108B18[0], 63, 0); sndFXCtrl(h, 0x5B, 0)` | `lbl_80108DF4` 33 u16 SFX ids 0x1C4..0x1E5 (Musyx group loaded by menus/game; entry 0x20 = Birdo alt).  Callers: menus `fn_2_12A70` (captain pick), game `fn_3_10CC20` x2 (batter/pitcher intro), `fn_3_B49D4` |
| Character voice bank | unique (via `fn_800698F8`) | game `fn_3_90F48` / `fn_3_90B14` / `fn_3_5A28C`: `fn_800216F8(grid + 5, cb)` then `fn_80021518(lbl_3_data_8148[grid], file)` = `sndPushGroup` | `lbl_800EF508[5 + grid]` (48 DiskFileDesc, uncompressed Musyx project/sdir/pool files in ZZZZ.dat; 0..4 and 38..47 are common/stadium banks), group id `lbl_3_data_8148[33]` (game.rel .data 0x8148) |
| Per-grid gameplay row | unique (via `fn_800698F8`) | DOL `fn_8004B284`: `lbl_800FBF10 + 0x214 + grid*14 + k*2` -> `getAnimRelatedCoordinates` | `lbl_800FBF10` (u16[33][7] at +0x214) |
| Small portraits in menus (lineup/team/results) and in-game | unique (`lbl_800E8558[c].uniqueIdx`) | menus `fn_2_4EB2C` (slot 0x15), `fn_2_5ED3C` (slot 0xA); game `fn_3_59F40` (slot 0x14) via `fn_80035838(desc, slot)` | ZZZZ.dat 0x18ED7000 (menus `lbl_2_data_1324C` / `lbl_2_data_20BF0`, game `lbl_3_data_3D60+0x70`): 180 textures, the 32 CI8 50x50 at indices 53..84 are unique 0..31 (byte-identical to the 54-file's for the 26 base cells) |
| HUD batter/pitcher card | **charID** | game `fn_3_91D1C` (rep_16B8): pane frame `pane->unk5C = stats.CharID << 16` (also `fn_3_EA340`, `fn_3_EAEF4`, `fn_3_EB6E0`, `fn_3_11F02C`, `fn_3_121304`, `fn_3_127B68`, `fn_3_11E364/7C4`) | ZZZZ.dat 0x1A6B3000 (DOL `lbl_800EEFD0+0x10` -> slot 0xD in `fn_80020388`, `lbl_800E8AA8+0x70`; game `lbl_3_data_21EC8/F538/10598 +0x10`): 102 textures, the 54 CI8 50x50 + 256-entry RGB5A3 TLUT at indices 30..83 are charID 0..53 (each colour variant has its own) |
| Name banners (menus) | unique (presumed; not traced to a draw site) | `fn_2_4E970` loads `lbl_2_data_132DC` into slot 0x17 | ZZZZ.dat 0x19135800: 75 x 420x20 + 64 x 400x20 CI4 |
| Records / star screens | unique, only if `isBase` | `fn_2_1C860`, `fn_2_45204`, `fn_2_454E8`, `fn_8006CDC0`: `lbl_80109AE8 + unique*0x64` | DOL `lbl_80109AE8` |
| Unlock flags | unique | `fn_2_348C`, `fn_2_7DDC`: `lbl_803CB748` (6 locked uniques) -> taken flag per charID | |
| Select grid cells | **grid cell -> base charID** (not the reverse) | `lbl_800FDE84`, `lbl_800FE5D4`, `fn_2_F200` scans `lbl_80108DB8`, `fn_800675C4` | untouched by the patcher |
| Gameplay checks by kind | unique | game `rep_1200` (`lbl_3_data_76FC[unique*3]`), `gap_106DFC` (`lbl_803616CC + unique*0x16`), `cmplwi 0x19/0xE/0x14/0x1A/0x1E` special cases, `fn_3_6BD6C` | |

Not presentation: `lbl_800EF508` was first mistaken for portraits; it is sound only (`fn_80021518` is
`sndPushGroup`).  `fn_80035838(desc, slotId)` loads a UI resource into a numbered slot,
`fn_80035B50(id)` finds the slot, `fn_800363D8(layout, pane, field, list, index)` sets a pane texture.

### What the patcher does (`clone_character.py --ui source`, default)

1. `lbl_800E8558[S].uniqueIdx := lbl_800E8558[C].uniqueIdx` (family/base/colour untouched, so the
   colour assignment on the grid still works).
2. `fn_800698F8` head (DOL 0x800698F8, 16 instructions) rewritten to `return lbl_800E8558[charID].uniqueIdx`
   with the Birdo flag contract kept (`cmpwi 0x11` / `useAltBirdoGrid` -> 0x20, flag cleared on every
   return).  **No data-only route exists for a variant donor:** the switch cases are `li r3, <base cell>`
   (no `li r3, 0`), `mainCharArray` holds one charID per cell, and the variant loop count (0x16) and the
   jump table are fixed; pointing a jump-table entry at the `li r3, 0` after `OSPanic` would skip the
   flag clear.  `lbl_80108DB8` / `lbl_80108DDC` / `jumptable_801091F4` are left alone (`fn_2_F200`
   iterates `mainCharArray` as the candidate list).
3. HUD portrait file: texture `30 + S` := texture `30 + C` (CI8 indices copied, TLUT recoloured with the
   slot's spec), file re-packed with the optimal LZSS encoder **in place** (134-135 KB vs the retail
   136224 B slot; descriptors untouched because the uncompressed size is unchanged and the decoder stops
   at it).
4. Nothing per grid index is copied (announcer SFX, voice bank, `fn_8004B284` row): with 1+2 the clone
   resolves to the source's grid index everywhere.

Consequences: a colour-variant donor (Toad 29..32, Shy Guy 44..47, ...) keeps the select grid intact
and shows/sounds as the source in lineups, HUD, results and the announcer.  A main-character donor
(Luigi) is itself the clone: its grid cell shows the source's face/name (two "Mario" cells) and, being
`isBase`, its records row becomes the source's.  `--ui donor` skips 1..3.

## 7. User test feedback (2026-10-23, Project Rio, default four-Toad clones, `--ui source`)
- Working: picking an extra Toad gives Mario's voice and announcer call.
- **Bug: menus and in-menu mini-screen sprites show the donor's own portrait** (the user could pick only one
  Toad without a multi-pick mod; it got the Purple Toad slot and the menus showed Purple Toad). So the menus
  don't take their portrait from the unique index (fn_800698F8 rewrite) or the charID-keyed HUD file. Needs
  tracing: which file and texture index the menu portraits/name banners use, and how the index is computed
  (likely menus character-select code fn_2_2FC0/3624/4970/7DDC/DFAC).
- **Chemistry (parked until custom sprites work everywhere, per user):** clones copy Mario's chemistry row/column, so clone↔Mario and clone↔clone have Mario's
  self-chemistry (none). Expected: good chemistry between Mario and his clones and among the clones.
