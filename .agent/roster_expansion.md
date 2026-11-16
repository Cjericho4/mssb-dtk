# Roster expansion (phase 6): what is sized for 54 characters, and a plan to move it

**First-pass inventory**, 2026-11-15: rows marked med or low and everything under "unverified"
have not been traced. Owns: the list of everything keyed by charID or sized 54, the list of
code sites that use 54 as a number, and the relocation plan. Table *meanings* stay in their owning
docs (linked per row). Nothing here has been tried in the game yet.

Reproduce: `python3 tools/roster_scan.py --tables --refs --derived` (needs a built tree). It rewrites
`.agent/roster_expansion_sites.csv` (uses of 54) and `.agent/roster_expansion_refs.csv` (every
instruction that forms an address inside a per-character table), and prints the 54 × N data
symbols whose colour-variant rows equal their base's row.

## 1. TL;DR

* There are **four limits, not one**: 54 charIDs, 32 unique characters (`uniqueIdx`), the
  32/36-cell select grid, and switch tables that stop at charID 47 or 51. A new character with its
  own voice, portrait and grid cell hits all four; a new *variant* of an existing character hits
  only the first.
* **41 code tables** are indexed by charID (25 in the DOL, 12 in game.rel, 2 in challenge.rel,
  2 descriptor tables in menus.rel), plus the stats file and the menu art files. Four of the
  game.rel ones and both challenge.rel ones were not in any doc before this pass (§3).
* The number 54 appears as an immediate at **368 candidate sites in 136 functions** (252 of them in
  menus.rel, where `character_select.md` §4 documents 54 as the "empty slot" value). By shape: 130
  range tests (`< 54`: bounds and loops), 119 equality tests (54 or 53 as a marker), 75 loads
  of the constant, 44 `54 - i` counts. 97 functions also name a known per-character symbol;
  39 do not (§5, CSV).
* The hard part is not the tables, it is two layouts that embed 54: the `CharacterStats` row
  (a 54-byte chemistry row inside each 0xA0 row) and the ARAM master descriptor tiers
  (`54 + charID*7 + k`, `432 + charID`, `486 + id`: every later tier base moves when 54 grows).
* Recommended first experiment: **relocate with N still 54** and poison the old copies. It changes
  no behaviour, so any difference in an emutest run is a missed reference. Grow N only after that
  passes (§6). The reference list for it exists (`roster_expansion_refs.csv`, §3.5): most tables
  are addressed by their own symbol; the five descriptor tables of `gap_8001E460` are reached as
  *unit anchor + offset* and through two data pointers.

## 2. The limits

| Limit | Value | Where it is enforced | Owner |
|---|---|---|---|
| charID count | 54 (`0x36`); 54 also means "none / empty slot" in the menus | every table in §3, the sites in §5 | this doc |
| unique characters | 32 (`uniqueIdx` 0..31 in `lbl_800E8558`) | voice group `u8[32]` (game `.data+0x8148`, challenge `.data+0xFC0`), unlock list `lbl_803CB748`, announcer and portrait files keyed by grid index | `character_select.md` §1, `sounds.md` §3 |
| select grid | 32 cells (+0x20 alternate), roster grid `lbl_800FDE84` 36 cells (26 used), captain grid 12 | `mainCharArray` 33, `lbl_800E869C` 32, `secondaryCharacterArray` 22, `lbl_80108DF4` 33 u16, menu layout resources | `character_select.md` §1, §4, §8 |
| per-charID switches | `jumptable_800EEC40` 48 entries (charID 0..47, `fn_80017814`), `fn_80064918` 0..51, `jumptable_801091F4` in `fn_800698F8`; candidates: a jump table used within 14 instructions of a read of the actor's charID byte (+0x252), index not traced: `jumptable_800EED00` (48 entries, `fn_80017DBC`), `jumptable_800EEB84` (38, `fn_80011468`), `jumptable_800EEE24` (38, `fn_8001D2D4`), `jumptable_800EEF4C` (32, `fn_8001FC4C`), `jumptable_800F7720` / `jumptable_800F77A8` (34 each, `fn_80024C6C`), menus `jumptable_2_data_2FEEC` (48, `fn_2_8D270`), challenge `jumptable_1_data_F690` (48, `fn_1_135C0`) | a charID past the table takes the default case or panics (`fn_800698F8`) | `character_modding_report.md` §1.1, `character_select.md` §4 |
| field widths | the actor slot record keeps charID as **`s8` at +0x252** (read with `extsb` in `fn_8004BEB0`, `fn_8004C510` and the loaders), so charIDs stop at 127; the challenge lineup stores it as `s16`; `lbl_800F73B8` is `s8` (master body entry ≤ 127); other charID fields not audited | none found that blocks 55..126 | `roster_flow.md` §2 |

## 3. Per-character tables

"Readers" are the functions that name the symbol: a lower bound, because a unit reaches its data
from one anchor plus an offset (`fn_80021CA4` reads `lbl_800F743C` and the descriptor tables through
`lbl_800EFBE8`, and names none of them). "Conf." is how sure the charID indexing is: **high** = the reader's index is traced to a charID in
a doc or in asm read for this pass; **med** = 54 rows with family-equal contents and a reader that
indexes by a 16-bit field, index source not traced.

### 3.1 main.dol

| Table | Shape | What | Conf. | Owner |
|---|---|---|---|---|
| `charSizeMultipliers` 0x800E8300 | 54 × 2 f32 | model scale (game, menu) | high | `stats.md` §6 |
| `lbl_800E8558` | 54 × 6 B | family, base charID, uniqueIdx, isBase, isCaptain, colour; 62 reader functions | high | `character_select.md` §1 |
| `lbl_800EEAAC` | 54 u16 | glove bone-list base (= charID*6) | high | `character_modding_report.md` §3 |
| `lbl_800EEB18` | 54 s16 | model script id | high | same |
| `lbl_800F1D78` | 54 × 19 × 16 B | disc subfiles `charID*19 + track` | high | same |
| `lbl_800F5D98` | 54 × 6 × 16 B | disc sub-item files `charID*6 + slot` | high | same |
| `lbl_800F73B8` | 54 × 2 s8 | body entry, overlay entry | high | same |
| `lbl_800F743C` | 54 u8 | sub-item pair row | high | same |
| `lbl_800EFD38` (+ `lbl_800F1D68`) | 516 × 16 B | ARAM master descriptors; tiers from `lbl_803CB7E0` = {54, 378, 54, 29}: `54 + charID*7 + k` sub-items, `432 + charID` track-15 bank, `486 + id` scripts | high | same; `data_map.md` §4 |
| `lbl_800FB798` .. `lbl_800FBD80` | 15 × s16[54] | animation event windows (two of them, 0x800FB804 and 0x800FB9B4, are byte-identical) | high | `stats.md` §7 |
| **`lbl_800FC494`** (new) | 54 × 3 s32 (+4 B) | effect position offset per charID, ×1e-5, added at bone 4 by the fielder-on-fire handler `fn_8004BEB0` (matched); **all zero in retail**, so neither table heuristic can see it | high | here |

Runtime (`.bss`) and save data:

| Object | 54-sized part | Conf. | Owner |
|---|---|---|---|
| `lbl_8034E9A0` (0x4C28) | `CharacterStats[54]` (0x21C0 bytes) at +0; taken flags `u8[54]` at +0x4757; chemistry-ranked ids at `+0x478D + idx*54`; chemistry rows at +0x47F9 | high | `stats.md` §1, `character_select.md` §1–2 |
| `CharacterStats` row | chemistry row `u8[54]` at +0x3B **inside** the 0xA0 row | high | `stats.md` §4 |
| `starMissionCompletionTracker` (0x4508, saved; `ChallengeSaveData` in `UnknownHomes_Game.h`) | `ChallengeTrackingStruct missions[54]` (0x34 each, +0..0xAF7, indexed by charID), `u8[54]` at +0x43D6, newly-recruited flags `u8[54]` at +0x444D. `fn_8006C9D8` (decompiled, registers only) loops the 54 records and sets state 1 + the +0x444D flag when a character's scout-flag count is met. Growing N changes the save layout | high | `roster_flow.md` §2 |
| `lbl_80354768` | 54-byte `memcpy`s at an offset past +0x10000 in `fn_8003C00C` (7 sites) and `fn_80041150` (2); contents not identified | low | — |

### 3.2 game.rel (`.data`)

| Offset | Shape | What | Readers | Conf. | Owner |
|---|---|---|---|---|---|
| 0x6EF8 `BatterHitbox` | 54 × 9 f32 | bat reach box | 5 | high | `stats.md` §6 |
| 0x7690 | 54 × u8[2] | charge frames | `setDefaultInMemBatter` | high | same |
| 0x7870 | 54 × s16[3] | runner frames | `fn_3_631AC`, `fn_3_63874` | high | same |
| 0x79B4 | 54 × 8 s16 | fielder hitbox | `setFielderValues` | high | same |
| 0x7E34 | 54 × u8[4] | body-check frames | `fn_3_60E90`, `fn_3_A96FC` | high | same |
| 0x7F10 | 54 s16 | character height | 7 | high | same |
| 0x8168 | 54 u16 | voice SFX base | `fn_3_90220` | high | `sounds.md` §3 |
| 0x17000 | 54 s32 | foot height | `fn_3_BC274`, `fn_3_BC2DC` | high | `stats.md` §6 |
| **0x3B4C** (new) | 54 s32 | 9 for everyone except Bowser 78 and charID 38 = 52; stored to an object's +0x938 | `fn_3_FDB30`: index = `InMemRunnerType.charID` (+0xE2; the asm reads `-0xB12(g_Runners + i*0x154)` for i = 9..12, which is runner `i-9` +0xE2) or the s16 at fielder +0x17A (unnamed in the `Fielder` struct, so that is the fielder's charID copy); `fn_3_106270` | high (index), unknown (meaning) | here |
| **0x37AC** (new) | 54 s32 (+1) | 56..87, one value per unique character (variants share), stored as s16 at +0x940 | `fn_3_FDB30` (index = s16 at +0xE2 of a record whose base was not traced; +0xE2 is `charID` in `InMemRunnerType`) | med | here |
| **0x111C8** (new) | 54 × 2 f32 (+1 row) | 1.2/1.2, 1.4/1.4, 1.0/1.0 ... passed to `fn_8003A688` | `fn_3_BC850(_, index)` | med | here |
| **0x285A8** (new) | 54 s32 | −150000 .. −350000 (fixed point ×1e-5?) | `fn_3_168704`, `fn_3_168DFC` | med | here |

`--tables` also prints 0x1BE94 and 0x28680. Neither is per-character: 0x1BE94 is read with a
0x6C stride through `lbl_803CBBC0`, and 0x28680 is mostly zero rows.

### 3.3 challenge.rel and menus.rel

| Where | Shape | What | Conf. |
|---|---|---|---|
| challenge `.data+0xFC0` / `+0xFE0` | u8[32] / 54 u16 | byte-identical copies of game.rel 0x8148 / 0x8168 (voice group, voice SFX base). The Clone Maker writes the game.rel 0x8168 row for a clone; no write to the challenge.rel copy was found. **No reader of the copy was found either**: `fn_1_B5B8` names `lbl_1_data_FC0` only as its unit's data anchor (it reads +0xCE2), and no instruction forms an address in 0xFC0..0x104B. Probably dead data linked in with shared source | high (the copy), med (unused) |
| challenge `lbl_1_data_A978` | 54 s16 (+ padding to 0xDC) | identity 0..53, read by the 54-loop in `fn_1_17B5C` | med |
| menus `lbl_2_data_241C` (`menu_char_a`) | 54 × 16 B | per-charID menu 3D scene descriptors (`data_map.md` §4) | high |
| menus `lbl_2_data_2FA60` | 54 × 16 B | same descriptor shape, reader `fn_2_8E6A4`; not identified | low |
| menus portrait descriptors (`.data+0x21ED8`, `0xF548`, `0x105A8`), 9 grid descriptor copies | — | charID- and grid-keyed art (`character_select.md` §8.2–8.3) | high |

No other duplicate of a per-character table exists in any of the four binaries: a byte search of
every table in §3.1–3.2 finds only itself, apart from the identical window pair and the window
tables that are constant (all 0 or all 99), which match any run of the same value.

### 3.5 How the code reaches each table (`roster_expansion_refs.csv`)

`tools/roster_scan.py --refs` follows `lis`/`addi`/`addis`/`mr` chains from a symbol through each
function and records every instruction whose address lands inside a table: 2,620 sites. "named"
= the instruction carries the table's own symbol; "anchor+offset" = a constant offset from a
tracked base; "indexed" = a tracked base used in `add` / `lbzx`-style forms. "Via" lists the
symbols the bases came from.

| Table | Functions | named | anchor+offset | indexed | Via |
|---|---|---|---|---|---|
| `charSizeMultipliers` | 8 | 9 | 0 | 10 | itself |
| `lbl_800E8558` | 62 | 94 | 163 | 101 | itself (the offsets are fields of a row) |
| `lbl_800EEAAC` / `lbl_800EEB18` | 6 / 6 | 11 / 8 | 4 / 4 | 9 / 6 | itself |
| `lbl_800EFD38` (master) | 7 | 9 | 11 | 13 | itself, `lbl_800F1D68`, **`lbl_800EFBE8`** |
| `lbl_800F1D78` | 4 | 4 | 1 | 5 | itself (`fn_80021BBC`, game `fn_3_59B20`, challenge `fn_1_1E0`), **`lbl_800EFBE8`** (`fn_8002204C`) |
| `lbl_800F5D98` | 1 | 0 | 1 | 1 | **`lbl_800EFBE8`** only (`fn_80021CA4`) |
| `lbl_800F73B8` | 1 | 0 | 1 | 2 | **`lbl_800EFBE8`** only (`fn_8002204C`) |
| `lbl_800F743C` | 1 | 0 | 1 | 1 | **`lbl_800EFBE8`** only (`fn_80021CA4`) |
| 15 window tables | 1 each | 1 | 0 | 1 | itself (`fn_8004B284`, `fn_8004BEB0`, `fn_8004C510`) |
| `lbl_800FC494` | 1 | 1 | 0 | 2 | itself (`fn_8004BEB0`) |
| `lbl_8034E9A0` (whole 0x4C28 block) | 212 | 588 | 918 | 451 | itself, `lbl_8034E978` |
| game 0x37AC, 0x6EF8, 0x7690, 0x79B4, 0x7E34, 0x7F10, 0x17000 | 1, 5, 1, 2, 2, 7, 2 | all | 0 | — | itself |
| game 0x3B4C / 0x285A8 | 2 / 2 | 5 / 2 | 2 / 1 | 5 / 1 | itself |
| game 0x7870 | 3 | 3 | 2 | 3 | itself, `g_hitFloats` |
| game 0x8168 | 3 | 1 | 9 | 10 | itself, `lbl_3_data_8148` |
| game 0x111C8 | 3 | 1 | 8 | 4 | itself, `lbl_3_data_111A8` |
| challenge 0xA978 | 4 | 6 | 10 | 6 | itself, `lbl_1_data_1DC0` |
| challenge 0xFE0 | 0 | — | — | — | no reader found |
| menus 0x241C / 0x2FA60 | 4 / 1 | 4 / 1 | 0 | 10 / 1 | itself |

Inside `lbl_8034E9A0`, by offset: stats rows (+0..0x21BF, which includes every plain load of the
block's address) 1,166 sites in 207 functions; +0x21C0..0x4756 519 sites in 122; taken flags
(+0x4757) 86 in 19; ranked ids (+0x478D) 24 in 1; chemistry rows (+0x47F9..) 162 in 33.

Pointers held in data (not visible to the register tracking), from a scan of every DOL data word
and every REL `ADDR32` relocation:

* `lbl_803CB790` -> `lbl_800F1D78` (the documented runtime subfile pointer) and `lbl_803CB7A8` ->
  `lbl_800F5D98`. Code that loads through these two words reads the tables without naming them:
  `lbl_803CB7A8` in `fn_80014204` and `fn_800145F8`; `lbl_803CB790` in 18 functions
  (`fn_80014A18`, `fn_80014D4C`, `fn_80014E50`, `fn_80014F40`, `fn_80015468`, `fn_80016344`,
  `fn_80016710`, `fn_80016B60`, `fn_80017340`, `fn_8001758C`, `fn_80018024`, `fn_80018270`,
  `fn_800189E4`, `fn_80018B74`, `fn_80018DEC`, `fn_8001C588`, `fn_8001C67C_animation`,
  `fn_8001C920`). Moving the tables only needs the two words rewritten; growing the rows per
  character (19, 6) would need these functions' index math.
* menus.rel `.data+0x277C`, `+0x13220`, `+0x2FE40` -> `lbl_800F5D98`.
* No REL data word points into a game.rel, challenge.rel or menus.rel table of §3.2–3.3.

Limits of the tracking: control flow is ignored, calls clear the volatile registers, and a base
passed to another function or stored in memory is lost. Checked against the docs: the six
readers of `lbl_800EEB18` and the 62 of `lbl_800E8558` are all found; game 0x7870 and 0x8168
gain readers the docs did not list (3 functions each, was 2 and 1).

### 3.4 Files on the disc

`stats.0` (54 rows + captain blocks, `stats.md` §5), the menu name / mini picture / grid portrait
files (`153 + c` indexing, 48 mini buffers with alias groups, `character_select.md` §8.2), voice
banks `sound.(5+u)` per unique index and announcer names in `sound.37` (`sounds.md`), the body,
sub-item and ANIM files named by the descriptor tables above. All of these are file contents the
existing tools already rewrite; growing them is data work once the tables that point at them grow.

## 4. Index spaces derived from 54

These are why "append 10 rows" is not enough:

* **Master descriptor tiers.** Tier bases are sums of `lbl_803CB7E0` = {54, 378, 54, 29}. With N
  characters the sub-item tier becomes N*7 and the track-15 tier N, so the bases 54, 432 and 486
  all move. `fn_80021CA4` adds the first base as an immediate (`addi rX, rY, 0x36`, three
  times), so the counts in `lbl_803CB7E0` are not the only copy; sites that use 432 or 486 as an
  immediate are listed below.
* **Body entries 0..32 / overlay entries 33..53** in the same master table are *not* charID-keyed;
  they are reached through `lbl_800F73B8`. A new unique body needs a new entry there, which the
  first tier (54) currently has no room for.
* **Immediates derived from 54** (`--derived`; candidates, the values are common numbers):
  `mulli x, 19` (tracks per character) 46 sites in 18 functions, the same set that loads through
  `lbl_803CB790` plus `fn_80021BBC`, game `fn_3_59B20`, challenge `fn_1_1E0` and `fn_1_16978`;
  432 in `fn_80021BBC` (2 sites: the track-15 tier base) and 17 unread sites elsewhere; 486 in
  `fn_80021ADC` (2: the script tier base), `fn_8005B298`, `fn_80060184`; 1026 (54 × 19) at 5
  unread sites; no `0x21C0` immediate anywhere.
* **`CharacterStats` stride.** The row is 0xA0 with the 54-byte chemistry row inside it. More
  characters means either a wider row (every `mulli 0xA0`, every `memcpy(..., 0xA0)`, the
  `inMemRoster` copies and `stats.0`) or chemistry moved to its own N × N table with the three
  readers patched (`stats.md` §4). The second is far smaller.
* **`uniqueIdx`** selects the voice group and the unlock entry; a 33rd unique character needs
  `u8[32]` grown in game.rel and challenge.rel.

## 5. Code sites that use 54 or 53

Full list: `.agent/roster_expansion_sites.csv` (module, function, address, instruction, the
per-character tables that function references). Forms scanned: `cmpwi`/`cmplwi`/`li`/`subfic`
with `0x36` or `0x35`. Not scanned: `addi` (almost all struct offsets), sizes such as `0x21C0`,
`0x402`, `0x1B0`, `0x1E6`, and counts loaded from data.

| Module | Sites | Functions | Of which name a per-character symbol | range | equals | load | count |
|---|---|---|---|---|---|---|---|
| main.dol | 93 | 24 | 20 | 21 | 42 | 26 | 4 |
| game.rel | 17 | 14 | 7 | 3 | 7 | 7 | 0 |
| challenge.rel | 6 | 3 | 1 | 2 | 1 | 2 | 1 |
| menus.rel | 252 | 95 | 69 | 104 | 69 | 40 | 39 |

The last four columns are the CSV's `kind`: **range** = a compare followed by `blt`/`bge`/`ble`/
`bgt` (a bound or a loop end: must become N), **equals** = followed by `beq`/`bne` (54 or 53 used
as a marker: must become N only if the marker has to stay outside the charID range), **load** =
`li` (a loop count, a marker being stored, or a size), **count** = `subfic` (`54 - i`, an
unrolled loop's remaining count).

An empty `evidence` column does not mean the function reads no table (anchor + offset access,
§3), and a filled one does not prove the 0x36 in it is a character count.

Asm context read for this pass:

* **Bound on a file lookup**: `fn_80021CA4` (`cmpwi r26, 0x36` after loading the `lbl_800EFBE8`
  anchor).
* **54 as "not found", then tested**: `fn_80051D00` (`li r22, 0x36` ... `cmpwi r22, 0x36`).
* **54-iteration loops**: `fn_8006C9D8` (over `starMissionCompletionTracker.missions`, see §3.1), challenge
  `fn_1_17B5C` (over `lbl_1_data_A978`); `fn_1_1496C` wraps a byte counter at 54.
* **Loop over every character's subfile row**: `fn_80018B74` (`li r0, 0x36; mtctr`, stride 0x130
  = 19 descriptors through `lbl_803CB790`): takes the largest size of five track groups over
  all 54 characters and sizes the exhibition animation pools from them (`model_limits.md`). At
  N characters the count must be N, or new characters' banks are not counted and can overflow
  the pool.
* **54-byte copies**: `fn_8003C00C`, `fn_80041150` (`memcpy(..., 0x36)` into `lbl_80354768`),
  game `fn_3_12CA90` (`li r6, 0x36` with `lbl_8034E978`).
* **Not a character count**: `fn_80021518(0x36, ...)` in game `fn_3_91064` and challenge
  `fn_1_A838`, and `fn_80021518(0x35, lbl_800EF808.soundC0)` in `fn_80069A68` (matched C: a
  resource index, called next to index 0x1C with the same buffer).
* **Probably not a character count**: game `fn_3_FDB30` (`cmpwi 0x36` on a word fetched through a
  pointer that is then advanced by 8: a script opcode case); game `fn_3_B6C9C`
  (`cmpwi r0, 0x36; bne`, then `li r3, 3`).

From other docs, not re-read here: `fn_80021BBC`, `fn_8002204C` (`charID < 0x36`), `fn_80067C48`,
`fn_80067F70` (54 loops), `fn_800698F8`, `fn_80064918` (`character_select.md` §4); `fn_800415A8`
(CPU team builder, 45 sites) and `fn_80068838` (saved lineup) by their role in `roster_flow.md`;
`fn_8004B284` switches on animation IDs 0x1A–0x34 (`stats.md` §7), so its `cmpwi 0x35` is
probably that switch's bound.

Unverified, context not read: DOL `DrawSprite`, `fn_8000FA9C` (compares a value with 0x36, then
0x27); game `fn_3_12A6C4`, `fn_3_12B7A0`, `fn_3_B6D80`, `fn_3_B7184`;
every menus.rel site, including the 26 functions with an empty `evidence` column (the
`fn_2_44504`..`fn_2_46ADC` and `fn_2_4D378`..`fn_2_4E1C0` runs neighbour known readers of
`lbl_800E8558`).

## 6. Relocation plan

Each step is testable on its own; none needs a matching build.

1. **Move without growing (N = 54).** For each table in §3.1–3.2: copy it to new space, retarget
   every reference, then fill the old copy with a poison pattern. Behaviour must be identical; a
   missed reader shows as garbage or a crash. Judge with emutest (golden frames and bones). This
   step proves the reference list, which is the main risk, because **references cannot be listed
   by symbol**:
   * DOL code loads one anchor per unit (`lis/addi` of the unit's first data symbol) and reaches
     every table in that unit as anchor + 16-bit offset. `gap_8001E460` reads `lbl_800EFD38`,
     `lbl_800F1D78`, `lbl_800F5D98`, `lbl_800F73B8` and `lbl_800F743C` this way from
     `lbl_800EFBE8`; none of the last three is named by any instruction.
   * So a table moves either with its whole unit pool (retarget the anchor's `@ha/@l` pairs; the
     offsets stay valid, but a table in the middle still cannot grow), or alone, by rewriting each
     `anchor + offset` access into a load of the new address (needs room for an extra instruction
     or a 32-bit offset form at every site).
   * `roster_expansion_refs.csv` is that reference list (§3.5). What it shows: only the
     `gap_8001E460` pool (`lbl_800EFBE8`: master, subfile, sub-item, pair and row-kind tables) and
     four REL tables (game 0x7870, 0x8168, 0x111C8, challenge 0xA978) are reached from a
     neighbour's symbol; every other table is addressed by its own symbol, so retargeting its
     `@ha/@l` pairs (DOL) or relocation entries (REL) moves it. The five `gap_8001E460` tables
     have 20 anchor-relative sites in two functions (`fn_80021CA4`, `fn_8002204C`), plus the two
     data pointers `lbl_803CB790` / `lbl_803CB7A8` (20 loader functions, §3.5) and three
     menus.rel pointers.
   * Not covered yet: bases passed as arguments or kept in memory, and the tracking's blind
     spots (§3.5). The poison run is what catches those.
   **Space** (read from the binaries, untested): main.dol uses 9 of its 11 data section slots
   and 2 of 7 text slots, so it can carry a new section. `.bss` ends at 0x803CD30E, the stack
   top is 0x803DD310 and `OSInit` sets the arena start to 0x803DF320 (`lis/addi` pairs at
   0x8006D3DC and 0x8006D414). A new section at 0x803DF320 with those two pairs raised by its
   size takes the space from the arena; every table at N = 64 is a few tens of KB against the
   1.3 MB the exhibition heap leaves free (`model_limits.md`). The RELs cannot simply grow: the
   patcher re-packs each REL inside its original compressed size in aaaa.dat, so REL tables
   would move into the DOL section too (their readers are relocation entries, which can point
   at the DOL). Still open: how the 54-sized parts of `lbl_8034E9A0` are split out.
2. **Chemistry out of the stats row.** Move the 54-byte rows to an N × N table and patch the
   readers, keeping the 0xA0 row stride. Removes the worst embedded 54.
3. **Raise N for variants only** (new charIDs that reuse an existing unique character: its voice,
   grid cell, portrait slot and switch case via its base charID). Needs: the tables at N rows, the
   §5 bounds and loops at N, the master tiers re-based (§4), `stats.0` and the taken-flags /
   ranked-ids arrays at N, and the "54 = none" marker changed to N (the `equals` sites in the CSV:
   69 in menus.rel, 42 in the DOL). The save file changes size if `starMissionCompletionTracker` grows: decide
   between a new save format and leaving new characters out of mission tracking.
4. **New unique characters.** Adds the 32-unique limit, grid cells and layout resources, the
   charID switches, announcer and portrait files, body entries in the master table.

The skin picker (phase 3) delivers "more looks without losing a slot" without any of this, and a
custom model on an existing slot needs none of it either. Steps 1–2 are still worth doing first:
they are behaviour-neutral, and they turn the rest into data edits.

## 7. Open items

* Trace the index of game 0x37AC, 0x111C8 (`fn_3_BC850` has no direct caller: it is reached
  through a pointer) and 0x285A8, and name the four new tables.
* Identify `lbl_80354768`'s 54-byte block, `lbl_2_data_2FA60`, `lbl_8034E978`.
* Read the unread derived-immediate sites (§4) and scan the `mulli` strides 6, 7 and 0xA0.
* `addi rX, rY, 0x36` is not in the sites CSV. `fn_80021CA4` uses it three times as the master
  tier base (`54 + charID*7 + k`), so that base is an immediate, not only a count read from
  `lbl_803CB7E0`. The other `addi 0x36` sites (`fn_8002244C`, `fn_8005B760`, `fn_8005DE14`,
  `fn_80060184`, game `fn_3_12A910`) are unread.
* Read the 39 functions with no evidence; decide per `equals` site whether its marker must move.
* Per-charID switch tables: trace the index of the eight candidates (§2).
* The table list is not proven complete: `lbl_800FC494` was found only by decompiling its
  reader. A search for data symbols used near a read of the actor's charID byte (+0x252) also
  turns up `lbl_800FC720`, `lbl_80108BF0`, `lbl_80108D30`, game `lbl_3_data_4444`, `lbl_3_data_49DC`,
  `lbl_3_data_7D24`, `lbl_3_data_266A8`; none is 54 rows by size, none has been read. Other charID
  sources (`InMemRunnerType.charID` +0xE2, `CharacterStats.charID`) are not searched this way yet.
