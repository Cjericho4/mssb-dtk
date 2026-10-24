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
   * `fn_80067F70` (0x534, stub): the remaining candidate for "next free colour" (loops bounded by
     `0x36`, uses `lbl_80108EDC` + `fn_80067AC8`).  **Decompile this one first.**  menus.rel callers: `fn_2_2FC0`, `fn_2_3624`, `fn_2_4970`, `fn_2_7DDC`, `fn_2_DFAC`
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
2. `fn_800698F8` (0x170): `findCharacterID`, grid index mapping (asm dumped above; a 32-entry
   `mainCharArray` scan, then a 22-entry `secondaryCharacterArray` scan with a per-variant switch).
3. menus.rel `fn_2_2FC0`, `fn_2_3624`, `fn_2_4970`, `fn_2_7DDC`, `fn_2_DFAC` (src/menus/gap_1254):
   the roster screen logic that calls the above.
4. `fn_800415A8` (0xAD4): CPU team builder (colour columns 1..4).
5. game.rel `fn_3_B4124`, `fn_3_10C450`: roster → `inMemRoster` copy (skin byte lands here).
6. `fn_80067B40(arg0 unused, s16 charID, u8 value)`: 8 register-choice diffs left (key should land
   in r7, walkers r6/r4); value == 2 is the "query only" mode.
