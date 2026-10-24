# Character modding report: load chain, character tables, clone recipes

*Mario Superstar Baseball (GYQE01), mssb-dtk. Home of the character load chain, the per-character
tables and the clone recipes. Disc formats and every descriptor table: `data_map.md` §4–§5.
Roster → match data flow and the per-player skin design: `roster_flow.md`. Menu art and select
screen: `character_select.md`. Addresses: `addresses.md`.*

**Goal:** several copies of one character on the field at once (e.g. three Marios), each with its own
textures/colours, ideally without giving up other roster slots.

## TL;DR

1. **The engine already does colour variants.** Pianta B/R/Y, the five Toads, the Shy Guys and the
   other families are separate charIDs. They share animation banks, and each variant's body is the
   base body plus a same-size **texture overlay** (`lbl_800F73B8` = `{body, overlay}`).
2. **Data-only cloning works inside the 54 slots** (`tools/modding/clone_character.py`, tested in
   Rio), but every clone costs a donor slot. Past 54 needs code: every table is fixed at 54 and the
   code bounds-checks `charID < 0x36`.
3. **Per-player skin without losing a slot** (phase 3): keep `charID` for gameplay, add a cosmetic
   skin byte read in `fn_8001758C` / `fn_8002204C`. Design: `roster_flow.md` §6. The character disc
   tables are editable C arrays and the build links modified code (`configure.py --non-matching`, §4d).

---

## 1. The load chain: charID → model / textures / animations

Identity: `enumCharacterID` 0..53 (mario=0, luigi=1, DK=2, …, PiantaB/R/Y=21/22/23, toads 13/29..32,
broB=53; `in_game.h`). Per player: `inMemRoster[team][slot].stats.CharID` (s16 @ +0x24). Per
on-screen actor: the slot record `Gap8001196CAnim` (0x27C, `g_hugeAnimStruct.slots[13]`; full
layout in `roster_flow.md` §1): `charID` 0x252, `slotKind` 0x254 (9 = batter), `blockIndex` 0x255,
`team/player` 0x256/0x257, `variant` 0x259, arm/stance 0x25A/0x25B (from roster bytes 0x26/0x27),
`isBatter` 0x278, `boneIndices[120]` 0x162.

```
fn_80017098  request a load / reuse a loaded slot (entry point; callers: roster_flow.md §5)
  └ fn_8001758C  state 0: fill the slot record, track = charID*19 + (variant==0), body load:
  │   ├ cached batter/runner model memcpy (g_hugeAnimStruct 0x2D54/0x2D3C), or
  │   ├ variant 1: fn_8002204C(charID, buf)  ARAM body + overlay via lbl_800F73B8, else
  │   └ ARAMTransfer(&lbl_803CB790[track])   disc track 0 (hi) / 1 (low-detail body)
  │   state 1: wait for lbl_803716B8.loadBusy == 0, then fn_80017814
  ├ fn_80016344 / fn_80016710   menu/cutscene slot state machines: anim banks, per-model script,
  │   │                         bat/glove (fielders/batter use fn_8001594C / fn_8001500C instead)
  │   ├ fn_80021BBC  track-15 ANIM bank: master 432+charID, else disc track 15
  │   ├ fn_80016B60 / fn_80016F7C  stream 5 anim banks (tracks 4/12/5/2/16)
  │   └ fn_80012B90 / fn_80013680  bat + glove loaders; fn_80021CA4 = sub-item pair loader,
  │                                fn_8002244C = queue callback chaining the 2nd sub-item
  └ fn_80017814  relocate the .gpc root {texture, layout, geo, skin, extra}
      ├ convertTextureHeader(root->texture)      texture offsets → pointers
      ├ LoadActorLayout / convertGeometryAndSknHeader → LoadGeoPalette, SKNLoadFile
      ├ fn_800BD190(geo, tex)                     binds textures to geometry
      ├ fn_8002399C → f_InitActorWithLayout       build the actor; crash site 0x800233A0
      ├ bone-index map, bone setup calls
      └ per-charID switch (jumptable_800EEC40)    character-specific setup
Disc reads: ARAMTransfer → DVDReadAsyncPrio → DecompressDiskData (Namco LZSS; size bit 30)
```

**There is no skeleton file.** The bone hierarchy is the actor layout inside the body `.gpc` (37
bones in both bodies). Subfile track 15 and master `432+charID` are a 12-sequence ANIM bank like the
other tracks. `fn_80021BBC` and fields such as `skeletonAramAddrs` / `unk1EA` bit 1 keep their old
"skeleton" names in src.

### 1.1 Step details

* **`fn_8001758C`** state 0 memcpy's a cached model when `cachedBatterCharID == charID` (variant 1,
  slotKind 9) or `cachedFielderCharID == charID` (variant 0, runners). Who passes which `variant`:
  `roster_flow.md` §5.5.
* **`fn_8002204C(charID, buf)`**: allocates `buf` from the master entry size if NULL (no caller
  does). If `lbl_803716B8.unk1EA & 1` (bodies in ARAM) it reads `lbl_800F73B8[charID] = {body,
  overlay}` and queues master `body` from `lbl_803716B8.bodyAramAddrs[body]` (callback
  `fn_80022620`, or `fn_8002254C(overlay)`, which decompresses `master[overlay]` over the body's
  texture archive at `block + root->texture`); otherwise subfile track 0 from disc. Then
  `unk1E8 = 1`, registers `fn_80022634` with `fn_800B0A5C_insertQueue` and kicks the ring.
* **Load queue:** `fn_80022CB4` queues a descriptor into a ring of 18 records in `lbl_803716B8`
  (`head`, `current`, `loadBusy`, per-tier ARAM address arrays = `aramBase + master[i].offset`).
  Sub-items: `fn_8002244C(arg, block, packedID = charID<<16 | itemID)` stores the aligned size of
  master `54+charID` at `block->size` and queues `54+itemID` into `block+size` from
  `subItemAramAddrs[itemID]`, callback `fn_80022620`.
* **`fn_80016344` / `fn_80016710`** (callers: fn_80016344 ← game `fn_3_6B4C8`, `fn_3_6B5D8`;
  fn_80016710 ← game `fn_3_10C81C` (minigames), menus `fn_2_481F4` (preview); state byte `g_hugeAnimStruct.loadState` 0x2D77): 2 register
  `slotPtrs[slot]` (0x2C50; fn_80016344 also copies `stance` to 0x25A/0x25B), clear `bankLoadStep`
  (0x2D8D); 3 record `loadedCharID[slot]` (0x2D7F) and load the anim bank: game mode 2 →
  `fn_80021BBC` into `sharedAnimBank` (0x2CAC); slot ≥ 9 → track 16 into `sharedAnimBank`; slot 12
  (fn_80016344 only) → track 17 into `batterAnimBank` (0x2CBC); else `fn_80021BBC` into the slot's
  bank (0x2CFC + slot*0x14); `ANIMGet` once `lbl_803C6CF8.allowLoad == 1`. 4 per-model script:
  `modelID = lbl_800EEB18[charID]`; if ≠ −1 and the root's `extra` word (0x10) is set,
  `fn_80021ADC(modelID, lbl_80118220[k].buf)` loads master `486+modelID` (a keyed event script;
  disc fallback `model_script`) and `fn_80025FFC(root->extra, &obj)` binds it; stored in
  `slots[slot].stadiumObj` (+0x2C, legacy name). `lbl_80118220` = 13 objects × 0x64. 5
  `fn_80013680` (mode 2) / `fn_80012B90`.
* **`fn_80021BBC(charID, buf)`**: `ARAMTransfer(&master[432+charID], buf, 3,
  skeletonAramAddrs[charID])` when `unk1EA & 2`, else subfile `charID*19 + 15`.
* **`fn_80017814(anim, index, slotKind, cb)`**: relocates root words 0x00/04/08/0C/10 (each
  `+= base` when non-zero; a zero word stops the chain), `convertTextureHeader` (0x800C0770),
  `LoadActorLayout`, `convertGeometryAndSknHeader`, `haveActLayoutPointToGeoHeader`,
  `fn_800BD190(geo, tex)`, then `fn_8002399C(&actorEntries[index].slot, anim->blockIndex, index,
  layout, slotKind < 9 ? anim+0x18 : anim+0x14, skn)` → `f_InitActorWithLayout`. After the
  actor exists: `boneIndices[boneID] = actorBoneIdx` (0xFFFF absent), `fn_800B2B74` for bones
  19/25/36, `fn_800B2B54(actor, boneIndices[3], 0xD)`, `fn_800BD548(slot, 4, …)`, bones 3/2/1/46
  marked with `fn_800B2BA8` + `bone->0x136 = 1`, `fn_800B2C08(actor, boneIndices[4])`,
  `fn_8001FC4C(anim)`, anim ids 0x60..0x6E reset to −1 and flags 0x25D..0x273 cleared.
* **Per-charID switch** (`jumptable_800EEC40`, 48 entries): 2 DK → `fn_800638B4`; 33..36
  Magikoopas → `fn_80063010`; 19 → `fn_8004B7B4`; 12/21/22/23/42 and 24/25/26 → `actor->unk99 = 1`;
  20/43 → `fn_800637BC`; 38 → `unk99 = 1` + `fn_8004BD6C`; 41 → `fn_800637D4` + `fn_8004BD6C`;
  14/37 → `fn_80052634`; 16/44..47 → `fn_80062ED4`. Mario (0) has no case.
* **`f_InitActorWithLayout`** (0x800232E0, charPipeline `InitActorWithLayout`): sizes bones from
  `layout->totalBones`; if `skinFileID != 0xFFFF` it looks the skin up in
  `geoPalette->descriptorArray[skinFileID]`. `skinFileID >= numDescriptors` → `OSReport`, then a
  NULL dereference at **0x800233A0**: a layout/palette mismatch (wrong body for the slot).
* **Textures** live inside the body `.gpc`: `TextureArchiveHeader {u16 count; u16 0;
  TextureHeader[count]}` at 0x20, 0x20-byte headers, offsets relative to the archive start.
  Nothing re-reads textures from another table.
* **Gloves:** `lbl_800EEAAC[charID]` (= charID*6) is the start of the actor's 6-entry
  attachment-bone list, read as `lhax(tbl, charID*2)` by `fn_80011CA8`, `LoadModel`,
  `fn_80013680`, `fn_80014204`, `fn_800145F8`, `fn_8001D180`.

## 2. Function status

All have full documented C bodies in `src/` (purpose, tables, chain position, skin-hook point)
except the last row. Diff counts are `tools/feedback_diff.py` lines (`decomp_knowledge.md` §2),
2026-10-24.

| Function | Source file | Role | Status |
|---|---|---|---|
| `fn_80017098`, `fn_8001758C` | gap_8001196C.c | load request / slot record + body load | **MATCH** |
| `fn_8002204C`, `fn_80021CA4`, `fn_80021BBC` | gap_8001E460.c | body / sub-item pair / track-15 loaders | **MATCH** |
| `fn_8002244C`, `fn_8002399C` | gap_8002244C.c | sub-item queue callback / actor slot init | **MATCH** |
| `fn_80016B60`, `fn_80016F7C` | gap_8001196C.c | stream 5 anim banks / drive it for slots 0..3 | **MATCH** |
| `convertTextureHeader`, `LoadGeoPalette` | gap_800BD3A0.c / gap_800B993C.c | texture / geo palette fixups | **MATCH** |
| `fn_80016344` / `fn_80016710` | gap_8001196C.c | slot state machines | 32 / 28 lines: two CSE temps vs params (`decomp_knowledge.md` §14) |
| `fn_80017814` | gap_8001196C.c | relocation, textures, actor, switch | 48 lines: prologue, bone-loop init, call-arg scheduling |
| `f_InitActorWithLayout` | gap_8002244C.c | carve actor/skin/bones | 111 lines: original keeps cursor/skin object in stack memory |
| `DecompressDiskData` | File_0x800a64e0.c | LZSS | 36 lines: saved-register set, ctr loop (`decomp_knowledge.md` §12) |
| `fn_80012B90` / `fn_80013680` | gap_8001196C.c | bat/glove loaders | first decompile, registers untuned (619 / 693 lines) |
| `fn_8002254C`, `fn_800227E4`, `fn_80021ADC` | gap_8002244C.c / gap_8001E460.c | overlay / blob / script loaders | asm only (behaviour read from asm) |

## 3. Character tables

DOL `.data` file offset = RAM − 0x800E8300 + 0xE5300. Rows marked † are byte-exact C arrays at the
top of `src/Unknown/gap_8001E460.c` (split `.data 0x800EFBE8..0x800F7478`, §6). Descriptor formats
and per-index file meanings: `data_map.md` §4 (`stadium`, `master`, `subfile`, `subitem`,
`model_script`).

| Table | RAM (DOL off) | Shape | Meaning |
|---|---|---|---|
| `lbl_800EFBE8` † | 0x800EFBE8 | 21 × 16 B | stadium descriptors (`data_map.md` `stadium`); anchor of the unit's `.data` |
| `lbl_800EFD38` + `lbl_800F1D68` † | 0x800EFD38 (0xECD38) | 515 + 1 × 16 B | ARAM master descriptors, blob-relative; [515] = the blob. Tiers (`lbl_803CB7E0` = {54, 378, 54, 29}): 0..32 bodies, 33..53 texture overlays (**not** charID-indexed; via `lbl_800F73B8`), `54+charID*7+k` sub-items, `432+charID` track-15 ANIM bank, `486+id` keyed event scripts |
| `lbl_800F1D78` † | 0x800F1D78 (0xEED78) | 54 × 19 × 16 B | disc subfiles `charID*19 + track`: 0 hi-detail body (== ARAM master body, 256×256 textures), 1 low-detail body (same 37 bones, `skinFileID` 1), 2..18 ANIM banks |
| `lbl_800F5D98` † | 0x800F5D98 | 54 × 6 × 16 B | disc sub-item files `charID*6 + itemSlot` |
| `lbl_800F71D8` † | 0x800F71D8 | 30 × 16 B (0x1E0) | `model_script`, disc fallback of master 486+id |
| `lbl_800F73B8` † | 0x800F73B8 (0xF43B8) | 54 × 2 s8 | `{bodyEntry, overlayEntry or −1}` (values below) |
| `lbl_800F7424` † / `lbl_800F743C` † | 0x800F7424 / 0x800F743C | 2 × 6 × 2 / 54 | sub-item pair rows `{k1, k2}` / per-character row index (`fn_80021CA4`) |
| `lbl_800EEAAC` | 0x800EEAAC (0xEBAAC) | 54 × u16 | glove/attachment bone-list base, = charID*6 (verified) |
| `lbl_800EEB18` | 0x800EEB18 | 54 × s16 | per-model script id (values below; variants share their base's id) |
| `jumptable_800EEC40` | 0x800EEC40 | 48 entries | per-charID setup switch (§1.1) |
| `lbl_803CB790` / `lbl_803CB7E0` | sdata | pointer / 4 × u16 | runtime subfile table / master tier counts |

Retail values (dumped from main.dol):

```
lbl_800F73B8 {body,overlay} by charID (a bare number = body with overlay -1):
  0..21 = charID; 22 {21,43} 23 {21,44} 24 22  25 {22,45} 26 {22,46} 27 {32,47} 28 23
  29 {13,34} 30 {13,35} 31 {13,36} 32 {13,37} 33 24  34 {24,49} 35 {24,50} 36 {24,51} 37 25
  38 26  39 27  40 28  41 29  42 {12,33} 43 {20,42} 44 {16,38} 45 {16,39} 46 {16,40} 47 {16,41}
  48 30  49 {30,52} 50 31  51 {30,53} 52 32  53 {32,48}
lbl_800EEB18 by charID:
  0..13 = charID, 14 -1, 15 14, 16 -1, 17 15, 18 16, 19 17, 20 18, 21..23 19, 24..26 20, 27 21,
  28 22, 29..32 13, 33..36 23, 37 -1, 38 -1, 39 25, 40 26, 41 27, 42 12, 43 18, 44..47 -1,
  48..51 28, 52 21, 53 21
```

Retail variants share every ANIM track and differ only in tracks 0/1, e.g. the Piantas
(ZZZZ offsets):

```
21 PiantaB t0 0B95C800 t1 0B96D800 t2 0B977800 t3 0B9AF000 t15 0BAD6800
22 PiantaR t0 0BB0F000 t1 0BB1F000 (t2.. same as 21)
23 PiantaY t0 0BB29000 t1 0BB39000 (t2.. same as 21)
```

Families sharing tracks 2..14: {12,42} koopa, {13,29–32} toads, {16,44–47} shy guys, {20,43}
paratroopas, {21–23} piantas, {24–26} nokis, {27,52,53} bros, {33–36} magikoopas, {48–51} dry bones.
Verified: `track0(BlueToad) == master[13]` with `master[34]` written at `+0x20`; overlay length ==
`layoutOff − 0x20`; variant track files differ from the base only inside the texture region.

## 4. How to add recoloured duplicate characters

### 4a. Data-only slot clone (implemented: `clone_character.py`, `tools/modding/README_WINDOWS.md`)
For each clone slot S of source character C:
1. **Subfile rows** `lbl_800F1D78[S*19 + t]`: alias C's rows for tracks 2..18. Point tracks 0 and 1
   (both bodies) at recoloured `.gpc` files appended to `files/ZZZZ.dat`.
2. **Master descriptors:** copy C's 7 sub-items to `54 + S*7 + k`; set `432 + S` to C's.
3. **Body/overlay pair:** `lbl_800F73B8[S] = {C's body, O}` where O is S's own overlay entry (or its
   body entry when no other slot uses it) repointed at a recoloured copy of C's texture archive,
   appended to the ARAM blob (§8).
4. **Gloves** `lbl_800EEAAC[S] = lbl_800EEAAC[C]`; **model map** `lbl_800EEB18[S]` = C's entry.
5. **Per-character setup:** if C has a case in `jumptable_800EEC40` (§1.1), S needs it too.
6. **Recolour** only CMPR colour endpoints inside the texture archive; geometry, display lists and
   palettes stay byte-exact.
7. Copy C's stat row if the clone should play like C. UI side (voice, announcer, HUD card, menu
   art): `character_select.md` §6, §8.3.

**Limits:** 54 characters total; each clone replaces a donor.

### 4b. Texture-only swap in `fn_80017814`
Replacing `root->texture` before `convertTextureHeader` / `fn_800BD190` would give a per-actor
texture swap, but the engine already does this through `fn_8002254C`'s body + overlay load, so a
skin should reuse the overlay mechanism (§4c) rather than add a second one. Not built.

### 4c. Per-player skin (no lost slots)
Design and copy-site audit: `roster_flow.md` §6. Summary: menu choice in
`lbl_803C6724.unk38[2][9]`; roster entry byte `StatTable.UnusedBytes[0]` (+0x05) re-applied at the
static→entry copies; slot byte 0x253 written by `fn_8001758C`; `skinPairs[charID][skin]` beside
`lbl_800F73B8` for the batter (ARAM) and skin subfiles for the low-detail body (fielders/runners,
disc track 1). Everything else (anim banks, gloves, switch, stats, voice, the `charID` compares in
game code: rep_F80, rep_E08, rep_AC8, gap_6B4C8, gap_62578) stays on charID.
The static rows are per charID, so the skin cannot be preset there; the quickest prototype is
"n-th duplicate on a team gets skin n", computed in `fn_8001758C` from team/player
(`roster_flow.md` §6.5).

### 4d. Building a modded binary
1. Mark the edited units `Equivalent` in `configure.py` (e.g. `Unknown/gap_8001196C.c`,
   `Unknown/gap_8002244C.c`, `Unknown/gap_8001E460.c`).
2. `python3 configure.py --non-matching && ninja` links C objects in place of the target asm and
   skips the hash check; shifted symbols relocate (dtk modding mode). Tested: main.dol and all
   three RELs link. Reconfigure without the flag afterwards.
3. Assemble the ISO from `build/GYQE01/` plus the patched `files/ZZZZ.dat` outside the repo;
   `orig/` stays read-only.
4. **Risks:** absolute `.4byte 0x80xxxxxx` literals in unsplit data aren't relocated; non-matching
   units are semantically checked but untested at runtime.

## 5. Corrections to the fork's guide (`fork/feat/character-cloning-texture-decoupling`)

* **"Zero code change" doesn't hold.** The "batting style hook at 0x80001840" is OS low memory: no
  DOL symbol or code references 0x800018xx, so it was an emulator-side poke.
* **The crash at 0x800233A0 is not the glove table** but the `skinFileID` NULL dereference in
  `f_InitActorWithLayout` (§1.1). The glove table only feeds the bone-list walk.
* **It misses tables:** `lbl_800F73B8` (body/overlay) and `jumptable_800EEC40`.
* **It wastes space:** copying all 19 tracks (~2 MB per clone); aliasing tracks 2..18 costs only
  the two bodies.
* **Consistent but not re-checked against the disc:** DK's `.gpc` texture map (archive at 0x20,
  ten textures in 0x180..0x4F00).

## 6. The in-unit table experiment (it matched)

`fn_8002204C` and `fn_80021CA4` addressed four `.data` symbols from one anchor (`lbl_800EFBE8 +
0x150` master, `+0x2190` subfiles, `+0x77D0` pairs; `addi r4,r31,0x2190` then `lwzx`). That means the
original source *defined* the tables in the same file. Defining them as initialized C arrays in
`gap_8001E460.c` reproduced the codegen:
* `config/GYQE01/splits.txt`: `.data start:0x800EFBE8 end:0x800F7478` on `Unknown/gap_8001E460.c`.
* `config/GYQE01/symbols.txt`: `lbl_800F71D8` shrunk to 0x1E0; new `lbl_800F73B8` (0x6C),
  `lbl_800F7424` (0x18), `lbl_800F743C` (0x36).
* Both functions MATCH, the unit's 30,864-byte `.data` matches, the DOL hash check passes.
* **Open rule exception:** `masterDescSizeFlags()` reads `*(u32*)((u8*)lbl_800EFD38 + idx*16 + 4)`,
  the unit's only pointer arithmetic; every struct/array form folds the +4 into the displacement and
  breaks the `lwzx` match. Needs a maintainer decision: keep it (documented) or lose the match.
* Rule: when a function forms `(base + const) + idx` across several adjacent symbols, give the unit
  a `.data` split (`decomp_knowledge.md` §1).

## 7. Open items

1. Remaining matches (§2): fn_80016344/fn_80016710 (one register-allocation issue shared by both),
   fn_80017814, f_InitActorWithLayout (find the non-escaping aggregate shape), DecompressDiskData,
   then tune fn_80012B90/fn_80013680.
2. Phase 3 skin build (`roster_flow.md` §6.5).

## 8. Patcher findings (`clone_character.py`)

* **The ARAM path:** `fn_800227E4` allocates a hard-coded 0x4D6600 B of ARAM (`lis r3,0x4d / addi
  r3,r3,0x6600` @ 0x800227EC/F4), sets every tier's ARAM address to `aramBase + master[i].offset`,
  streams master[515] disc→ARAM, and the callback sets `lbl_803716B8.unk1EA |= 0xF`. Only the
  batter and menu/cutscene loads use it (variant 1); fielders and runners stream disc track 1
  (`roster_flow.md` §5.5). The patcher covers both because it patches tracks 0, 1 and the pair.
* **Growing the blob:** other data follows it on disc, so the patcher moves the blob to the end of
  ZZZZ.dat and patches master[515] and the two immediates (the only `.text` change, 8 bytes).
* **Disc offsets** are offsets into ZZZZ.dat (`ARAMTransfer` → `DVDFastOpen` →
  `DVDReadAsyncPrio(file, staging, min(comp, 0x8000), desc->offset)`). Reads land in a staging
  buffer drained only by the LZSS thread, so **files must stay compressed** (clearing bit 30 does
  not work). Appending to ZZZZ.dat is safe: nothing references its last 0x5C0 bytes, and Dolphin
  rebuilds the FST from the folder (`sys/fst.bin` is patched anyway).
* **Selection UI:** no colour button; the L button cycles a family's free colours
  (`roster_flow.md` §2.1). Stats: `ZZZZ.dat+0x06CF8800`, 54 × 0xA0 `CharacterStats`, loaded by
  menus.rel at boot. Other charID-indexed tables: game.rel `.data` (section 5) voice base 0x8168,
  BatterHitbox 0x6EF8, charge frames 0x7690, runner timing 0x7870, 0x7E34, 0x17000; DOL
  `lbl_800FB798` 15 × 54 s16 animation parameters (R3, issue #11).
* Pure-Python LZSS (11/4) round-trips every retail file tried; optimal packing beats retail (Mario's
  body 76992 B vs 77284 B).
* **Base donors (e.g. `--slot Luigi:green`):** the clone's overlay goes into the donor's own body
  entry (`master[1]`), so `master[1].sizeFlags` becomes the archive size (0xC2C0). Harmless:
  retail already has `master[charID].size` smaller than the body it loads (BlueToad 29: 0x18028 vs
  body 13's 0x195B0; BlueShyGuy 44: 0x5BE0 vs 0x16320), and `fn_8002204C` only uses it when
  `buf == NULL`. Do not "fix" it by resizing the entry.
