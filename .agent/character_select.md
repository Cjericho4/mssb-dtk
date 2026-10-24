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
4. Announcer/voice and some lineup portraits use **unique/grid index** (`fn_800698F8` =
   `findCharacterID`). The select grid, roster mini images and preview names have separate
   **charID** lookups, including colour variants. See §8; the earlier universal-grid-key claim
   was disproved by §7's test and the phase-2 trace.

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

This was the phase-1 lookup map. **Correction from phase 2:** select-grid portraits, roster mini
images and preview names also use **charID**, with separate art for variants (§8). The
unique-index routes below still agree for all 54 retail charIDs (test_clone.py checks it):
`lbl_800E8558[charID].uniqueIdx` == `fn_800698F8(charID)`.

| What | Keyed by | Lookup | Asset |
|---|---|---|---|
| Announcer name call-out | unique (via `fn_800698F8`) | `fn_800628D4(charID)` (matched this pass): `useAltBirdoGrid = 1; sfx = lbl_80108DF4[grid]; sndFXStartEx(sfx, lbl_80108B18[0], 63, 0); sndFXCtrl(h, 0x5B, 0)` | `lbl_80108DF4` 33 u16 SFX ids 0x1C4..0x1E5 (Musyx group loaded by menus/game; entry 0x20 = Birdo alt).  Callers: menus `fn_2_12A70` (captain pick), game `fn_3_10CC20` x2 (batter/pitcher intro), `fn_3_B49D4` |
| Character voice bank | unique (via `fn_800698F8`) | game `fn_3_90F48` / `fn_3_90B14` / `fn_3_5A28C`: `fn_800216F8(grid + 5, cb)` then `fn_80021518(lbl_3_data_8148[grid], file)` = `sndPushGroup` | `lbl_800EF508[5 + grid]` (48 DiskFileDesc, uncompressed Musyx project/sdir/pool files in ZZZZ.dat; 0..4 and 38..47 are common/stadium banks), group id `lbl_3_data_8148[33]` (game.rel .data 0x8148) |
| Per-grid gameplay row | unique (via `fn_800698F8`) | DOL `fn_8004B284`: `lbl_800FBF10 + 0x214 + grid*14 + k*2` -> `getAnimRelatedCoordinates` | `lbl_800FBF10` (u16[33][7] at +0x214) |
| Small portraits in menus (lineup/team/results) and in-game | unique (`lbl_800E8558[c].uniqueIdx`) | menus `fn_2_4EB2C` (slot 0x15), `fn_2_5ED3C` (slot 0xA); game `fn_3_59F40` (slot 0x14) via `fn_80035838(desc, slot)` | ZZZZ.dat 0x18ED7000 (menus `lbl_2_data_1324C` / `lbl_2_data_20BF0`, game `lbl_3_data_3D60+0x70`): 180 textures, the 32 CI8 50x50 at indices 53..84 are unique 0..31 (byte-identical to the 54-file's for the 26 base cells) |
| HUD batter/pitcher card | **charID** | game `fn_3_91D1C` (rep_16B8): pane frame `pane->unk5C = stats.CharID << 16` (also `fn_3_EA340`, `fn_3_EAEF4`, `fn_3_EB6E0`, `fn_3_11F02C`, `fn_3_121304`, `fn_3_127B68`, `fn_3_11E364/7C4`) | ZZZZ.dat 0x1A6B3000 (DOL `lbl_800EEFD0+0x10` -> slot 0xD in `fn_80020388`, `lbl_800E8AA8+0x70`; game `lbl_3_data_21EC8/F538/10598 +0x10`): 102 textures, the 54 CI8 50x50 + 256-entry RGB5A3 TLUT at indices 30..83 are charID 0..53 (each colour variant has its own) |
| Challenge Special ending / staff-roll presentation (§8.4) | fixed animation timeline; no character key | `fn_2_4E970` loads `lbl_2_data_132DC` into slot0x17; `24238` / `2587C` play sequence0x64 | ZZZZ.dat 0x19135800: 427 textures, including 139 long CI4 strips; no clone patch needed |
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
5. (Phase 2, §8.3) charID-keyed menu art: roster preview name, mini picture and grid portrait of S :=
   C's (pictures recoloured), and the colour word dropped (`--colour-word none`, default).

Confirmed scope: this redirects announcer/voice, unique-index presentation and the HUD card.
The claim that it also fixed every menu/grid face was wrong (§7): the charID-keyed files in §8
were not patched by 1..4; step 5 (implemented 2026-10-24, §8.3) adds them. A base donor's records
row changes because it is `isBase`. `--ui donor` skips 1..3 and 5.

## 7. User test feedback (2026-10-23, Project Rio, default four-Toad clones, `--ui source`)
- Working: picking an extra Toad gives Mario's voice and announcer call.
- **Bug: menus and in-menu mini-screen sprites show the donor's own portrait** (the user could pick only one
  Toad without a multi-pick mod; it got the Purple Toad slot and the menus showed Purple Toad). So the menus
  don't take their portrait from the unique index (fn_800698F8 rewrite) or the charID-keyed HUD file. Needs
  tracing: which file and texture index the menu portraits/name banners use, and how the index is computed
  (likely menus character-select code fn_2_2FC0/3624/4970/7DDC/DFAC).
- **Chemistry (parked until custom sprites work everywhere, per user):** clones copy Mario's chemistry row/column, so clone↔Mario and clone↔clone have Mario's
  self-chemistry (none). Expected: good chemistry between Mario and his clones and among the clones.

## 8. Menu portraits, banners and sprites

Phase-2 trace, 2026-10-24, USA Rev 0. **The missing menu keys are charIDs.** Changing
`uniqueIdx` and `fn_800698F8` does not change them. The donor portrait reported in §7 is
explained by two additional texture files, not by a failed announcer/HUD patch.

### 8.1 Pick, cursor and draw chains

The roster scene is created by `fn_2_8279C` with script `lbl_2_data_2B59C`; its update callback
is `fn_2_81628`. Pane numbers below are relative to `scene->unkIndex`. A pane's `field_0x5C`
is a 16.16 animation frame, `unk64` is its sequence, and `field_0x66` identifies the loaded
resource slot. Scene scripts store the **logical resource ID at byte +0x14**, not the flags
halfword at +0x10. `fn_80034F50` resolves that ID through `lbl_8023D6C0`.

```
confirmed pick: fn_2_DFAC -> teams[side][slot] = charID -> fn_800625A4(side, 0xF)
               -> fn_2_81628 -> fn_2_7F8BC -> mini image + chemistry + fn_2_74F40
cursor move:   fn_2_3624 -> fn_800625A4(side, 0xE)
               -> fn_2_81628 -> fn_2_7DAB8 -> fn_2_74F40
colour cycle:  fn_2_3624 -> teams[side][slot] changes, unk50[side] = 1
               -> fn_2_776A0 -> mini image + fn_2_74F40, then unk50 = 0
```

`fn_800625A4` only writes `lbl_803C66B0.flags5D[side]` and clears the transition-stage
bytes. The command-0xE consumer is **menus `fn_2_81628`**, not DOL `fn_800559EC` or
`fn_80060184`. Its `jumptable_2_data_2D920` indexes commands 9..0x1D.

| Function | Role and relevant key | Body/status this pass |
|---|---|---|
| `fn_2_DFAC` | Confirm charID from `gridPick[side]`, update roster/taken flags, announcer, chemistry; request 0xF. No art loaded here. | Existing match preserved; misleading dispatcher comment corrected. |
| `fn_2_1C34` | Exact button-value switch: A=0x1B8 confirm, B=0x1B9 alert, directions=0x1B7 move. Other listed buttons do nothing. No character key. | Existing match rechecked; documented. |
| `fn_2_102C8` | Count empty/54 team slots; temporarily reserve the other side's pending pick; choose nonrepeating random fill strategy 0..2 (`FCB4`/`FAA0`/`F200`), rebuild positions and request 0x16. Full team -> cursor9, command0x11. Release temporary reservation afterward. | Complete documented C, non-matching; side/other registers and scheduling remain. |
| `fn_2_5444` | Ready: challenge copies team0 charIDs/order into save lineup, in-memory roster and batting-order data, sends 0x13 to both sides and advances state8. Shared pad hands control to side1 or exits state3; two-pad mode waits for both ready, then state7. | Complete documented C, non-matching; unrolled copy/register scheduling remains. |
| `fn_2_7265C` | Open grid: scan 54 `lbl_80361B20.characterFlags` for transition1/2; challenge uses 0x13 and once-only extra queues. Queue `fn_80051D00`. | **MATCH**. |
| `fn_80051D00` | Build DOL grid scene. Cell c -> `lbl_800FDE84[c]` base charID; unavailable cell substitutes54. Bind portrait via resource9/sequence0x19. `lbl_800FDE60[c]` is draw order; picked-controller badges are separate. | Complete documented C, non-matching; loops/register scheduling remain. |
| `fn_2_7F8BC` | Command0xF starts card animation. Search `order[side][]` for the cursor, then set pane `0x58 + side*9 + cursor` frame to `teams[side][slot] << 16`. Call `75BE4`, `74F40`; advance transition stage. | Complete documented C, non-matching. |
| `fn_2_75BE4` | Five chemistry stars: average nonzero slot chemistry excluding captain, thresholds15/35/55/70. No art key. | Complete documented C, non-matching. |
| `fn_2_7DAB8` | Command0xE animates old/new roster focus and held swap card; calls `74F40`. It retains each mini image's existing charID frame. | Complete documented C, non-matching. |
| `fn_2_74F40` | Name/stat preview. Pending grid pick -> `gridPick[side]`; ordinary roster cursor -> search `order[]`, read `teams[]`; ready/clear -> no character. Captain-select path instead uses captain-grid tables. | Complete documented C, non-matching; repeated stat bars expressed as a loop. |
| `fn_2_776A0` | Per-pad maintenance, maps pad to side. Refreshes `74F40` when cursor/grid hover changes; consumes L-colour `unk50` to write the mini image's new charID frame and refresh name/stats. Also Start/ready/popup animations. | Complete documented C, non-matching. |
| `fn_800363D8` | `(scene, pane, layer, sequence, frame)`: query list0 in **destination pane's resource**, store expanded record's +6 texture index in `textureOverrides[layer]` at pane+0xAC. `sequence` is not another pane. | **MATCH**; typed header views added. |

In `74F40`, name pane `0xB0 + side` uses **common resource1 / sequence0x82 / frame=charID**.
The mini-image pane uses **common resource1 / sequence0x83 / frame=charID**. Initial roster
population in `7AE3C` uses the same mini-image frame assignment (assembly inspected).
The four stat bars read `CharacterStats` bytes +0x37 batting, +0x38 pitching, +0x39 running,
+0x3A fielding. These are display ratings, not texture indices.

Colour text is separate: pane `0xAE + side` uses common sequence0x7B with a **hard-coded charID
switch** choosing labels0..6; the family query `fn_80067B40(0, charID, 2)` gates it. It does not
read the modified `uniqueIdx` or `colourIdx`. To suppress donor colour words for a clone, patch
its case to label0 (or customize that shared label/sequence deliberately); changing the name
texture alone preserves the retail donor colour prefix. Challenge hides the colour-label path.

### 8.2 Files, formats and exact index math

All offsets are in **ZZZZ.dat**, not aaaa.dat. Disk descriptors are four big-endian words
`{compressionConstants, flaggedUnpackedSize, offset, packedSize}`. Both new files use LZSS
constants0x40B; 0x40000000 marks the compressed size word.

| Art | File and descriptor | Runtime key -> texture index | Retail format |
|---|---|---|---|
| Roster preview name | **0x1A9FE800**, unpacked0x106568, packed0x68C10; DOL `lbl_800E8AA8+0x150` = **0x800E8BF8**, also `lbl_800EEFD0+0xF0` | Common slot1, sequence0x82, charID c -> **c if c<29, else c+28** | 54 × **111x18 CI4** (GX8), shared 16-entry **RGB565** TLUT (format0). |
| Roster/mini-screen character image | Same common file (440 total textures) | Common slot1, sequence0x83, c -> **153+c**; frame54 placeholder -> texture434 | 54 × **52x60 CI8** (GX9), 256-entry **RGB5A3** TLUT (format2). |
| Select-grid portrait | **0x18AEE800**, unpacked0xADFFC, packed0x4BAB0; DOL `lbl_800E8AA8+0x230` = **0x800E8CD8**; menus `lbl_2_data_180+0x2D4` / `lbl_2_data_720+0x604` | Slot9, query sequence0x19, grid charID c -> **4+c**; unavailable54 -> texture118 | 54 × **50x50 CI8**, 256-entry **RGB5A3** TLUT. |
| Existing HUD card | 0x1A6B3000 (§6) | charID c -> 30+c | 50x50 CI8, RGB5A3; already patched. |
| Other small lineup/results portraits | 0x18ED7000 (§6) | uniqueIdx u -> 53+u | 32 × 50x50 CI8; unique-index redirection already covers source appearance. |

Grid cell identity and art identity are separate: the grid stores **base** charIDs, so a variant
donor need not have its own visible grid cell. Patching portrait `4+S` fixes every consumer that
actually asks for S; it does not change the base Toad cell into an independently selectable clone.

The earlier candidate `0x19135800`/slot0x17 is **the fixed Challenge ending presentation**, not
the roster name resource or a charID/unique-index name bank. The trace and no-patch verdict are
in §8.4.

Named views are in `include/menus/menu_ui.h`: `MenusSceneScript`, `MenuUiFileHeader`,
`MenuUiSpriteBank`, `MenuUiSequenceTable`, `MenuUiSequence`, `MenuUiFrameList`, `MenuUiFrame`,
`MenuUiWordDelta`. Runtime views name grid cell unavailable flags, badge variants, cached grid
picks, and display ratings. Texture headers use the existing `TextureFile` parser:
archive at root word0, count at archive+0, 0x20-byte headers at archive+4+index*0x20,
archive-relative pixel/TLUT offsets at header+0/+4, height/width at +8/+0xA,
GX format at +0x17, palette count at +0x18 and TLUT format at +0x1A.

Sprite bank is root word1; bank+8 points to a relative sequence table. Each sequence has a
relative list-offset table. The character image/name list is list0 (the second list pointer,
after the header list). **Records are stored in descending frame order**; their frame halfword
is not a texture index. Type0 supplies a full 0x2C-byte template; type2 supplies replacement
words. The expanded record's texture is at +6. `fn_8000CEF0` is the generic query decoder
(complete documented C, non-matching; three refinement attempts), while `fn_8000D838`/`fn_8000D164` drive sprite
rendering. These are UI animation records, not skeletal `ANIMBank` tracks.

Reproduce all 162 mappings without exporting assets:

```
export PATH=$PWD/.venv/bin:$PATH
python tools/modding/inspect_menu_ui.py orig/GYQE01
```

The inspector validates both retail descriptors, expands the actual character lists and checks
every frame's texture/format. It also reports **48 pixel/palette buffers for 54 mini images**:
some entries alias each other. All 54 name textures share one palette. Grid portraits have
54 distinct pixel and palette buffers.

### 8.3 Concrete patcher recommendation

**Implemented 2026-10-24** in `clone_character.py --ui source` (`patch_menu_art`, `MenuTextures`,
`patch_colour_word`); checked by `test_clone.py` and `test_matrix.py --menu-art`. Not yet seen in
Rio. How it differs from the recommendation below:

- **Header retargeting, not copying.** All three donor textures (name, mini picture, grid portrait)
  get the source's pixel offset in their header; the name also keeps the shared text palette. The
  two pictures get a private 512-byte palette recoloured with `rc.for_palette()` (as the HUD card).
  It goes into a buffer that no header references any more, in order: the donor's old palette, its
  old pixels, buffers freed by earlier donors (each donor's 1344-byte name pixels are always freed).
  The files therefore never grow and nothing shared is written; the aliased mini pictures
  (12/42, 20/43, 27/52/53, 48/49/51) are covered (`--slot 42 --slot 53 --slot 49 --slot 51` test).
  Appending is kept as a last-resort path (`MenuTextures._alloc`).
- **In place.** Optimal LZSS re-packs fit easily: common 420-421 KB of 429072 B, grid 303.8 KB of
  309936 B (about 8.8 KB / 6 KB spare for the default config). If a file did not fit (or with the
  test-only `--relocate-menu-art`) it is appended to ZZZZ.dat and every tuple copy is rewritten.
- **Descriptor copies (full 16-byte tuple search) differ from the table below:** common file:
  main.dol x2, menus.rel x0, game.rel x5, **challenge.rel x1** (.data file offset 0x41818); grid
  file: main.dol x2, **menus.rel x9** (one more than listed), game.rel x5, **challenge.rel x1**
  (0x418F8). The patcher asserts these counts when it moves a file.
- **Colour word:** `jumptable_2_data_2D844` (menus .data, 42 entries for charIDs 12..53) is empty
  in the file; each entry is an `R_PPC_ADDR32` self-relocation against .text whose addend is the
  case (`li r0, N` at 0x7556C + 8*(N-1); label 0 at 0x7559C). `--colour-word none` (default)
  rewrites the 4-byte addend of each donor's entry to 0x7559C, after checking every retail addend
  against the C switch and every case instruction. menus.rel is re-packed in place in aaaa.dat
  (355584 B, room 372736 B). Label 0 is what every single-colour character (Mario) shows; its
  exact on-screen look is unverified. `--colour-word donor` keeps the retail entries.

Extend `clone_character.py --ui source` with **data changes in these two files**, retaining the
existing unique-index/announcer/voice/HUD changes. For each donor S and source C:

1. Common file: set texture `name(S)` to source `name(C)` (`name(c)=c<29?c:c+28`). All names have
   identical dimensions/format. Copy the CI4 pixels or redirect the donor header's pixel offset;
   keep the shared text palette. This fixes the name used by the roster preview.
2. Common file: set texture **153+S** to source **153+C**, optionally recolouring the source TLUT
   with the slot's palette transform. **Do not overwrite a shared donor pixel/TLUT buffer.**
   For source appearance, redirect the donor header's pixel/TLUT offsets to the source buffers.
   For independent recolours, allocate private pixel and 512-byte palette buffers and point only
   that donor header at them. This fixes picked cards, initial rosters and L-colour updates alike.
3. Grid file: set texture **4+S** to **4+C**, copying CI8 pixels and recoloured 512-byte TLUT, or
   redirect headers for un-recoloured source appearance. No grid/family/base-charID edits needed.
4. The colour prefix is a separate policy: retain the donor prefix, or make clone cases in
   `74F40` select label0. The source name pixels can be correct even with a donor colour word.
   For a data-only default, retain the prefix; suppressing it requires the tiny switch change.
5. Repack the resources. Prefer the existing in-place method if the new compressed file fits the
   old reserved slot and the unpacked size is unchanged; validate by decompressing again.
   If private buffers grow the file or it does not fit, append the packed resource to ZZZZ.dat
   on a 0x20 boundary and rewrite **all matching descriptor tuples**, including copies in RELs.
   Appended pixel/TLUT buffers use archive-relative offsets; preserve existing bank/table offsets.
   Repack changed RELs into aaaa.dat through the patcher's existing descriptor machinery.

For example, donor29 from Mario0 needs common **name57 <- name0**, common **sprite182 <- sprite153**,
grid **portrait33 <- portrait4**, plus the already-existing HUD **59 <- 30** and unique-index fix.
No changes to actual roster charIDs, `lbl_800FDE84`, `lbl_80108EDC`, chemistry or model keys are
needed for those image/name replacements.

Descriptor aliases to update **if relocation/unpacked-size changes require descriptor edits**:

| Module | Common file descriptor | Grid file descriptor |
|---|---|---|
| DOL | `lbl_800E8AA8+0x150`, `lbl_800EEFD0+0xF0` | `lbl_800E8AA8+0x230`, `lbl_800EEFD0+0x1D0` |
| menus.rel | None found (uses boot-loaded common slot1) | `.data+0x454`, `+0xD24`, `+0x1324`, `+0x18C4`, `+0x2A9C4`, `+0x2B3EC`, `+0x2E1FC`, `+0x302CC` |
| game.rel | Each of `lbl_3_data_3D80`, `6130`, `F538`, `10598`, `21EC8` **+0xF0** | Same five bases **+0x1D0** |

These are descriptor starts, not their offset-word addresses. Compare the full original tuple
before replacing, rather than globally replacing an offset word. No copies found in challenge.rel.
In-place, size-preserving replacement leaves these aliases valid automatically.

For independent recolours in the **32-portrait** lineup/results resource, the existing unique-index
route still makes source and clones share art. The two-file change above fixes source appearance
there through the existing unique-index patch, and independent recolours in the newly traced
54-character menus. Distinct recolours in every 32-index consumer need a further change: expand
that portrait bank to 54 frames using the charID-keyed 50x50 art, and change those callers from
`uniqueIdx` to charID (or explicitly route them to a loaded 54-image bank). Do not recolour the
source's shared `53+uniqueIdx` texture and call it a per-clone fix. That extension was not
implemented or runtime-tested here.

A single global charID->uniqueIdx hook would not fix these files: these are 54-frame banks with
variant-specific images, while uniqueIdx addresses a different 32-character ordering. If choosing
a code-remap alternative, use a separate 54-entry **UI charID** map at these identified frame/query
sites, preserving stats, taken flags, grid badges and model charIDs.

### 8.4 Large banner archive

**Verdict: a character clone does not need this archive patched.** ZZZZ.dat **0x19135800** is
an authored **Challenge Special ending / staff-roll presentation**, with animated character
illustrations and long text strips. It is not the roster-name bank, and none of its texture
choices on this path is keyed by charID, family, colour or `uniqueIdx`. The screen identification
is from the static scene/animation trace below; it has not been checked in a new Rio run.

**Loader and screens.** The exact descriptor is `{0x40B, 0x4023491C, 0x19135800, 0x82928}`:
unpacked **0x23491C**, LZSS-packed **0x82928**. In menus.rel it is
`lbl_2_data_132DC` (`.data+0x132DC`). Already-matched **`fn_2_4E970`** calls
`fn_80035838(descriptor, 0x17)` and returns whether loading succeeded.

The live call site in **`fn_2_1B7B4`**, at `0x1BAEC..0x1BB1C`, takes this load path when the
special-transition flag `lbl_2_bss_1A8248->unk44F4` is set and **difficulty byte +0x4415 >=3**
(Special; the other difficulties bypass this presentation). The following stages queue the movie
helper `fn_2_37460`, then at `0x1BB98..0x1BB9C` start the UI with **`fn_2_2460C`**. That queues
**`fn_2_24238`**, which instantiates script **`lbl_2_data_1059C`** through `fn_2_4E878` /
`fn_80034E20`. Its **pane1 binds logical resource0x17 / sequence0x64**, and callback table
`lbl_2_data_105FC` binds pane1 to **`fn_2_2587C`**. Pane0 is a separate common-resource pane.
`fn_2_2587C` now has a **MATCH** C body: command2 shows the pane, enables playback and resets
its 16.16 frame to **zero**; commands5/6/7 stop and hide it. It never reads a character ID.
`fn_2_24238` performs the normal scene draw/update and removes the scene on panel shutdown.
The standalone load wrapper `fn_2_1B52C` also calls `4E970`, but no reference to `1B52C` was
found in the original code/data; it is not evidence of another reachable player screen.

**Slot0x17 is reused.** `fn_2_4EABC` loads a *different* descriptor, `lbl_2_data_1326C`
(ZZZZ+0x18E92800), into the same logical slot during the ordinary Challenge scene path
`fn_2_379D0`. That path queues `fn_2_245C8` / `fn_2_2416C` with script `1061C`. Those ordinary
Challenge panes must not be attributed to the ending archive merely because their resource ID
is also0x17. `fn_2_4E898` / `fn_2_4E8E0` release the reused slot.

There is a second descriptor copy at **challenge.rel `.data+0xFB98`**, the first entry of
`lbl_1_data_FB98`. It belongs to the **sprite/resource debug browser**, not the character-select
screen: `fn_1_26AF8` counts resource descriptors; `fn_1_26928` changes the selected resource
ordinal with directional input; **`fn_1_267F4`** loads that descriptor into **slot0**, creates
the sprite viewer and enters `fn_1_25F98`. Thus resource ordinal0 can display this same archive
in the browser. The browser's keys are resource/sequence/frame selections, not roster IDs.
No full descriptor copies were found in the DOL or game.rel. If deliberately relocating this
archive later, update **both** the menus and challenge descriptors.

**Texture inventory.** There are **427 texture headers** and **101 sequences (0..0x64)**.
All textures have **16-entry palettes**, including the CI8 ones. The bank is 640x448 at 60fps;
`recordWords=20` means an **80-byte expanded query buffer**, even when a list's template is only
0x2C bytes. The long strips are:

| Dimensions | Count | Texture indices | Format |
|---|---:|---|---|
| 400x20 | 64 | 95..143, 223..233, 406, 409..411 | CI4 (GX8), RGB565 TLUT0 |
| 420x20 | 75 | 234..291, 407..408, 412..426 | CI4 (GX8), RGB565 TLUT0 |

The remaining **288** textures are illustrations/animation frames and presentation elements:
**254 CI4** (253 RGB565, one RGB5A3 at index147, 447x57), and **34 CI8 / RGB5A3 TLUT2**
(8x56x80, 9x85x78, 10x71x87, 7x71x78). These are not 32 or 54 equal-sized character-name
entries. The full dimensions/counts/index ranges of the remaining CI4 textures are reproduced
by the inspector below; sizes range from16x16 to640x100, including the 640x29 and640x25 strips,
595x88 panel,357x86 graphic and numerous variable-sized animation cells.

**Actual indexing.** `sequence0x64` is a fixed timeline: its header ends at **frame9900**
(mode1), with additional stored transition keys through10876. Its records reference other
sequences through **record flags high byte3 / index at+6**; leaf texture records have
**flags high byte4 / texture index at+6**. The packed-bank traversal in `fn_8000BA3C`
(`0x8000C104..0x8000C13C`) follows the nested sequence index and subtracts the record's start
time; this is authored timing, not a character lookup. Do not mistake these nested indices
for textures or assume that every expanded +6 field is an image when its flags say otherwise.

The complete conservative sequence0x64 graph references **425 textures**, including **all139
long strips**; only texture44 and50 are outside that query-record graph. For example, nested
sequence0x3A's layers0..5 reference **96,97,98,99,100,141** directly, and sequence0x35's
layers0..6 reference **234,235,236,249,224,223,143**. The sequence0x64 timeline chooses these
panels at fixed times. There is **no `base+charID`, `base+uniqueIdx`, or clone texture-index
formula** here. Editing it would customize the fixed ending/browser presentation for everyone,
not fix a donor's roster label or portrait. The charID patches in §8.3 remain sufficient for
the menu images traced there; this verdict does not claim that every other game UI is covered.

**Read-only reproduction:**

```
export PATH=$PWD/.venv/bin:$PATH
python tools/inspect_banner_archive.py orig/GYQE01
python tools/inspect_banner_archive.py orig/GYQE01 --sequences
```

The script imports the existing disc/LZSS/texture readers, validates the retail descriptor,
prints every texture size/format/index range and both descriptor aliases, expands all image
lists with all four query-record cases, and checks nested-sequence bounds and all139-strip
coverage. It prints metadata only and writes no assets. `--sequences` lists each layer's
flags and fixed indices so the examples and graph can be checked independently of this prose.

**Decoder details added this pass:** `fn_8000CEF0` skips `count-frame-1` packed records in
descending order; its `frame` argument is an ordinal, not a search for a stored key time.
Type0 zero-fills80 bytes and copies the first full template (0x2C in the character lists);
type1 copies an independent80-byte full record. Type2 starts with the template payload,
copies its own first word (type/frame), then overwrites indexed words backwards from the packed
record's tail: **output word = 1 + wordIndex**. Type3 copies byte ranges relative to output+4.
For image records the texture halfword is at **+6**, beside flags at+4. The complete typed C
body is committed non-matching; table-address folding, register choices and delta-loop codegen
remain different after three attempts. No match was lost.

### 8.5 Verification and remaining scope

`ninja` green; baseline **3963 -> 3965** matches. New matches: `fn_2_7265C`, `fn_800363D8`.
All other new bodies are complete semantic decompilations, explicitly non-matching. Existing
`fn_2_1C34` and `fn_80036214` rechecked MATCH. `fn_2_3624` remains at its original five scheduling
feedback lines; its optional match refinement was not attempted in this pass.

The dispatcher/initial-population routines (`81628`, `8279C`, `7AE3C`) were inspected in assembly;
their existing stubs remain. The art-selection path now has documented bodies through pick,
cursor, colour refresh and grid texture binding. Generic sprite querying now has a complete C body; rendering remains assembly-inspected. Patcher implementation and a new Project Rio run remain future work:
this pass establishes the data/code targets, not an already-tested patched game. The older large-banner hypothesis has now been resolved in §8.4. No assets were exported,
and no runtime Rio test was performed for this documentation pass.

2026-10-24 follow-up: `fn_8000CEF0` semantic body committed; `fn_2_2587C` newly matched.
`ninja` green, **3965 -> 3966** matches; read-only banner inspector verified all101 sequences
and139 long strips. Both descriptor copies (including the debug browser) are documented above.
