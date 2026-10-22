# Character modding research: per-player character variants ("three Marios")

Goal: let a game have several copies of one character, each with its own look (textures/colours),
ideally without losing other roster slots.  This note records what the binary actually does
(verified against the target asm in `build/GYQE01/asm/` and the DOL data tables), compares it with the
unverified fork `fork/feat/character-cloning-texture-decoupling` (commit `f393e8a1`,
`CHARACTER_CLONING_GUIDE.md`, `tools/patch_character_v6.py`), and recommends a plan.

Addresses are RAM addresses; DOL file offset = RAM - 0x800E8300 + 0xE5300 for `.data`.

## 1. The char-ID -> model/texture/skeleton/glove lookup chain

### 1.1 Identifiers
* `enumCharacterID` (0..53): mario=0, luigi=1, DK=2, ..., PiantaB=21, PiantaR=22, PiantaY=23,
  toadR=13/toadB=29/toadY=30/toadG=31/toadP=32, ..., broB=53 (`in_game.h` 1112-1167).
  The 54 slots are the *only* character identity the engine knows; every table below is sized 54.
* Per-player: `inMemRoster[team][slot]` (`CharacterStats`, 0xA0 each) carries the character in
  `stats.CharID` (s16 @ +0x24) plus the stat block copied from the character tables.
* Per-actor (on-screen object): `AnimationStruct.unk252` (s8, char ID), `unk254` (actor/role index),
  `unk256` team, `unk257` roster slot, `unk25A/unk25B` fielding arm / batting stance
  (`include/UnknownHeaders.h`, written by `fn_8001758C`).

### 1.2 Disc data tables (all in DOL `.data`, fixed size)
| Table | RAM / DOL off | Shape | Meaning |
|---|---|---|---|
| `lbl_800F1D78` | 0x800F1D78 / 0xEED78 | 1026 x 16 B = 54 chars x 19 tracks | Section-1 **subfile table**: `{u32 flags(0x40B), u32 (0x40000000\|uncompSize), u32 discOffset, u32 compSize}`. Index = `charID*19 + track`. Track 0 = body `.gpc`, track 1 = equipment/hands `.gpc`, tracks 2..14 = animation banks, **track 15 = skeleton rig** (`fn_80021BBC` falls back to `lbl_800F1D78[charID*19+15]` when not in ARAM), 16..18 more anim banks. `lbl_803CB790` (sdata) points at the runtime copy used by `fn_8001758C`/`fn_80016344`. |
| `lbl_800EFD38` | 0x800EFD38 / 0xECD38 | 515 x 16 B (+`lbl_800F1D68`, 1 x 16 B, same format => 516) | **Master descriptor table** (ARAM/section-2 objects), same entry format but word2 is an ARAM/section offset. Tiers come from `lbl_803CB7E0` = `{0x36, 0x17A, 0x36, 0x1D}`: entries 0..53 body models, 54..431 = `54 + charID*7 + k` sub-items (hands/bats/grips, see `fn_8002244C`: `entry = 54 + (id>>16)`), 432..485 = `432 + charID` skeleton rigs (`fn_80021BBC`), 486..514 = `486 + id` stadium objects (`fn_80021ADC`, id < 0x1D). |
| `lbl_800EEAAC` | 0x800EEAAC / 0xEBAAC | 54 x u16 | **Glove/attachment bone-list base**: value is `charID*6` in the retail DOL, i.e. the start index of that character's 6-entry attachment-bone list. Read as `lhax(table, actor->unk252*2)` in `fn_80011CA8`, `LoadModel`, `fn_80013680` (animateModelArmsGlovesBats), `fn_80014204`, `fn_800145F8`, `fn_8001D180` (updateAnimationAction); each walks the actor's bone list (`actor+0x30`) from that index. Setting a clone's entry to the source character's value (DK = 0x000C) is what the fork does. |
| `lbl_800EEB18` | 0x800EEB18 | 54 x u16 | **Model ID map** (identity 0..53 in retail, -1 = none). `fn_8001500C`, `fn_8001594C`, `fn_80016344`, `fn_80016710`, `fn_80019C00`, `fn_8001A3FC` use `lhax(table, charID*2)` to pick the model/anim set (`lbl_80118220[modelID]`, 0x64 stride). This is the cheapest existing "charID -> model" indirection. |
| `lbl_803CB7E0` | sdata | 4 x u16 | descriptor tier counts (54, 378, 54, 29). |

### 1.3 Load path (function chain)
1. `fn_8001758C(u8* state, s32 slot, u8 charID, u8 team, u8 player, u8 arg6, u8 slotKind, u8 variant)`
   (gap_8001196C.c, **now matched and typed** as `Gap8001196CAnim`): state 0 fills the slot record
   (`charID` 0x252, `slotKind` 0x254, `team/player` 0x256/0x257, `variant` 0x259, roster bytes
   0x26/0x27 -> 0x25A/0x25B, `isBatter = slotKind == 9` -> 0x278), computes
   `track = charID*19 + (variant == 0 ? 1 : 0)`, and either memcpy's a cached batter/fielder model
   (`g_hugeAnimStruct` 0x2D54/0x2D3C, keyed by charID at 0x2D5C/0x2D44), or
   `fn_8002204C(charID, buf)` (variant != 0) falling back to `ARAMTransfer(&lbl_803CB790[track], buf)`;
   state 1 waits for `lbl_803716B8.loadBusy == 0` then calls `fn_80017814(anim, anim->unk255, slotKind, fn_8001FDD4)`.
2. `fn_80016344` / `fn_80016710` (called from game `fn_3_6B4C8`, `fn_3_6B5D8`, `fn_3_10C81C`, menus
   `fn_2_481F4`): state machine that loads skeleton (`fn_80021BBC(charID, buf)`, **now matched** in
   gap_8001E460.c: `_OSAllocFromHeap(0x20, size)` if `buf == NULL`, then
   `ARAMTransfer(&lbl_800EFD38[432 + charID], buf, 3, lbl_803716B8.skeletonAramAddrs[charID])` when
   `lbl_803716B8.unk1EA & 2`, else `ARAMTransfer(&lbl_800F1D78[charID*19 + 15], buf, 0, NULL)`), animation banks (`lbl_803CB790[charID*19 + 16/17]`),
   and body/equipment subfiles; stores the actor in `g_hugeAnimStruct.AnimationStructPtrs[i]` (+0x2c50).
3. `fn_80017814` (`FUN_80017814(ACTActor*, actorIndex, flag, userData)`): relocates the `.gpc` root
   header in place (words 0x08/0x0C/0x10 += base), then calls **`convertTextureHeader`**
   (= Ghidra `AdjustTextureHeaderPointers`, 0x800C0770, now matched in `src/Unknown/gap_800BD3A0.c`)
   on the texture archive pointed to by word 0 of the root header, then `fn_8002399C`
   (`characterAndBallDisplayRelated`, **now matched**: `memset(lbl_8017EBB0[slotIdx], 0, lbl_803CBC5C)`,
   `layout->actorID = actorID`, `slot->actor = f_InitActorWithLayout(layout, lbl_8017EBB0[slotIdx])`,
   `actor->skHeader = skHeader`, then resets the `Gap8002244CActorSlot` fields) -> **`f_InitActorWithLayout`** (0x800232E0).
   Sub-items go through the load queue: `fn_8002244C(arg0, block, packedID)` (**now matched**) is the
   queue callback that, given `packedID = charID << 16 | itemID`, stores the aligned size of descriptor
   `54 + charID` at `block->size` and queues descriptor `54 + itemID` (`fn_80022CB4`, ring of 18
   `Gap8002244CRecord`s in `lbl_803716B8`) into `block + size` with ARAM source
   `lbl_803716B8.subItemAramAddrs[itemID]` and completion callback `fn_80022620`.
4. `convertGeometryAndSknHeader` -> **`LoadGeoPalette`** (0x800BCB44, now matched in
   `src/Unknown/gap_800B993C.c`): converts the on-disc `GEOPalette`
   (`GeoPaletteHdr` -> `GeoDescriptor[] {layout, name}` -> `GeoLayout {position, color,
   texture[numTextureChannels] {coords, texturePaletteName}, lighting, display {primitiveBank,
   stateList[n].primitiveList}, unk18}`) from file-relative offsets to pointers; returns the
   position array of the descriptor whose `compCount == 6`.  Then `SKNLoadFile` for the skin.
5. **`f_InitActorWithLayout(ActLayout* layout, ACTActor* act)`** (`objinit.c::InitActorWithLayout`,
   Dolphin charPipeline `ACTGet` derivative): sizes bone/matrix arrays from `layout->totalBones`,
   and if `layout->skinFileID != 0xFFFF` looks the skin up in `layout->geoPalettePtr->descriptorArray[skinFileID]`
   via `fn_80023078`.  If `skinFileID >= geoPalettePtr->numDescriptors` it `OSReport`s, stores NULL
   in a stack slot and immediately dereferences it at **0x800233A0** (`lwz r0,0xc(r3)` with r3 = NULL)
   — that is the crash the fork saw.  It is caused by a layout/palette mismatch (wrong skeleton or
   body file for the slot), *not* by the glove table; the glove table only feeds the bone-list walk in
   step 1.3/`LoadModel`.  Then `DSInitTree`, `f_InitBone` per bone, `BuildBoneSkinOrientationMatrix`, `ACTSort`.
6. Textures: `TextureArchiveHeader {u16 count; u16 pad; TextureHeader[count]}` with 0x20-byte
   `TextureHeader {dataOffset, clutOffset, h, w, wrap/filters, lodBias, minLOD, maxLOD, format,
   tlut...; texId (set to index)}`; offsets are relative to the archive start (0x20 into the `.gpc`
   for `donkey00.gpc`, matching the fork's finding).  The engine never re-reads the texture bytes
   from a table — they live inside the slot's track-0 `.gpc`.  **Colour variants are therefore
   purely a matter of which track-0/track-1 subfile a slot points at.**
7. Disc streaming: `ReadDataFromDisk` -> **`DecompressDiskData`** (0x800A6654, `read.c`, Namco LZSS,
   `gDataDecompressorValues`; bit 30 of the size word selects LZSS) — unchanged by any of this.

### 1.4 How the retail game already does variants
Rows of `lbl_800F1D78` for the stock colour variants share every animation/skeleton track and differ
only in tracks 0/1:

```
slot 21 PiantaB t0 0B95C800 t1 0B96D800 t2 0B977800 t3 0B9AF000 t15 0BAD6800
slot 22 PiantaR t0 0BB0F000 t1 0BB1F000 t2 0B977800 t3 0B9AF000 t15 0BAD6800
slot 23 PiantaY t0 0BB29000 t1 0BB39000 t2 0B977800 t3 0B9AF000 t15 0BAD6800
```
Groups sharing tracks 2..14: {12,42} koopa, {13,29,30,31,32} toads, {16,44,45,46,47} shy guys,
{20,43} paratroopas, {21,22,23} piantas, {24,25,26} nokis, {27,52,53} bros, {33..36} magikoopas,
{48..51} dry bones.  So a "variant" in this engine *is* a slot whose model subfiles differ and whose
animation/skeleton rows alias another slot.  Three Marios = three slots whose rows 2..18 alias
Mario's and whose track 0/1 (and descriptor entries 54+S*7.., 432+S) point at recoloured copies.

## 2. Where a per-player "skin variant" ID could be added

Option A — **no new ID, reuse a slot** (what the fork does): clone onto an existing slot.  Costs a
roster character.  Data-only.

Option B — **new slots beyond 53**: every table is a fixed `.data` array of 54 (or 54x19 / 516):
`lbl_800F1D78`, `lbl_800EFD38(+lbl_800F1D68)`, `lbl_800EEAAC`, `lbl_800EEB18`, `lbl_803CB7E0`, the
stat tables (`CharacterStats`/`StatTable` sources, names, portraits, menu order...), and bounds
checks such as `fn_80021BBC` (`charID < 0x36`).  Growing them means moving the arrays (relinking or a
code patch), so it is **not** data-only.

Option C — **variant ID that only affects cosmetics** (recommended for "three Marios without losing
slots"): keep `charID` for gameplay/stats and add a `skin` byte per actor/player.
* Room: `AnimationStruct` has unused bytes at `0x253` (`_rest253`) and `0x255..0x259` region
  (`unk258/unk259` are written by `fn_8001758C` from caller args), and `inMemRoster[][]`'s
  `StatTable` has `UnusedBytes[27]` at `+0x05` — a `skinVariant` can live in `StatTable.UnusedBytes[0]`
  (per roster entry) and be copied into `AnimationStruct._rest253` by `fn_8001758C` next to the
  arm/stance copy.
* Lookups that must switch from `charID` to `(charID, skin)`: only the *cosmetic* ones —
  `fn_8001758C`'s subfile index (`charID*19 + 0/1` -> variant's body/equipment subfile),
  `fn_8002244C`'s sub-item descriptor (`54 + charID*7 + k`), `fn_80016344`'s body/equipment loads,
  and `fn_8001500C`/`fn_80016710`'s `lbl_800EEB18` model map.  Skeleton (track 15 / descriptor
  432+S), the glove list (`lbl_800EEAAC`), animation banks, stats, names, voice, AI and the
  `AnimationStruct.unk252` comparisons in game code (`rep_F80.c`, `rep_E08.c`, `rep_AC8.c`,
  `gap_6B4C8.c`, `gap_62578.c`) all stay on `charID` untouched.
* Simplest implementation: a `skinTable[charID][skin]` of extra subfile rows (track 0/1 pairs +
  the 7 sub-item descriptors) appended as new `.data`, indexed in those four places; `skin == 0`
  means "retail row", so an unmodded save/roster behaves identically.

## 3. Can the fork's data-only approach be extended to N extra slots?
* Within the 54 slots: yes — it is exactly what the retail variants do, and the fork's patcher
  (subfile rows for tracks 0..18, descriptors 0..53/54+S*7../432+S, glove entry, LZSS re-pack with
  bit 30, 32-byte DMA alignment, `files/ZZZZ.dat` free arena) is a plausible recipe.  Note the fork
  copies *all* 19 tracks per clone (2 MB/clone in the "free arena"); aliasing tracks 2..18 to the
  source slot like the retail variants do makes a clone cost only its two `.gpc` files.
* Beyond 54: no.  Every table is fixed-size `.data` with hard bounds (`fn_80021BBC`: `charID < 0x36`,
  `fn_80021ADC`: `< 0x1D`), and the stats/menu side has the same limit, so extra slots need code or
  table relocation.
* Caveats on the fork's claims: (1) "batting style hook at 0x80001840" is OS low memory, not a DOL
  table — no DOL symbol or code reference to 0x800018xx exists (checked `symbols.txt` and the asm), so
  that part of the fork must have been an emulator-side poke, i.e. its "zero code change" claim does
  not hold for that step; (2) the 0x800233A0 crash is the `skinFileID >= numDescriptors` NULL
  dereference in `f_InitActorWithLayout` (palette/skeleton mismatch), the glove table is a separate
  (and smaller) bone-list issue; (3) the guide's byte-exact `.gpc` texture map (10 textures,
  `0x180..0x4F00`, archive header at `0x20`) is consistent with `TextureArchiveHeader` /
  `convertTextureHeader` but was not re-verified here against the disc image (orig/ untouched).

## 4. Can the build link modified (shifted) code?  Is a source-level mod feasible?
* `configure.py --non-matching` builds `Equivalent` objects from C instead of the target asm,
  keeps `NonMatching` objects linked from asm, and skips the DOL hash check.  Tested here:
  `python3 configure.py --non-matching && ninja` links `build/GYQE01/main.dol` + all three RELs with
  no errors (output byte-identical, 1139968 B, because no object is currently marked `Equivalent`).
  The link uses dtk's generated `ldscript.lcf`; a modified object simply shifts the following
  symbols (dtk v1.8.3 supports this "modding" mode).  The tree was re-configured back to matching mode
  afterwards.
* So a source-level mod is feasible *today* for any function in a file whose other functions are
  all matched or asm-linked: mark the file `Equivalent` in `configure.py`, edit the C, build with
  `--non-matching`.  Residual risks: unsymbolized absolute addresses in data (`.4byte 0x80xxxxxx`
  literals in `auto_*_data.s`) do not get relocated, and the RELs' dependencies on DOL symbol
  addresses are handled by the linker only for symbols it knows.
* The code needed for Option C is small and now mostly in matched/typed files: `fn_8001758C`
  (gap_8001196C.c, matched), `fn_8002244C` and `fn_8002399C` (gap_8002244C.c, matched),
  `fn_80021BBC` (gap_8001E460.c, matched), and the roster -> actor copy.  `convertTextureHeader` and `LoadGeoPalette` are matched and typed
  (`TextureArchiveHeader`, `GeoPaletteHdr`...), `f_InitActorWithLayout` and `DecompressDiskData`
  are unmatched (`f_InitActorWithLayout` is typed, best attempt in `.agent/attempts/`; `DecompressDiskData` keeps its inline-asm source), which does not block a shifted build.

## 5. Recommended plan
1. **Prototype with data only (today):** pick the "three Marios" as three slots.  Build a patcher
   like the fork's, but make the clones alias Mario's rows for tracks 2..18 and descriptor
   `432+S`, give them new track-0/track-1 `.gpc` files (recoloured textures inside the
   `TextureArchiveHeader` region, Zone-B geometry untouched), copy Mario's 7 sub-item descriptors to
   `54+S*7..`, set `lbl_800EEAAC[S] = lbl_800EEAAC[0]`, `lbl_800EEB18[S] = 0` (or S), and copy the stat
   row.  This sacrifices the three donor slots (choose rarely used ones, e.g. shy-guy colours).
2. **Verify the crash story:** confirm `layout->skinFileID` / palette consistency rather than only
   the glove table when a clone crashes at 0x800233A0.
3. **Then go source-level for "no lost slots":** implement Option C — `StatTable.UnusedBytes[0]` as
   `skinVariant`, copied into `AnimationStruct` by `fn_8001758C`, and a small appended
   `skinTable[charID][skin]` consulted by `fn_8001758C`, `fn_8002244C`, `fn_80016344` and the
   `lbl_800EEB18` users; everything else keeps using `charID`.  Build with `--non-matching`
   (Equivalent objects for gap_8001196C.c and gap_8002244C.c).  The roster UI needs a way to set
   the byte (a menu REL change) or the patcher can preset it in the default roster data.
4. Keep orig/ read-only; produce the modded `main.dol`/RELs from `build/GYQE01/` and the modded
   `files/ZZZZ.dat` from the patcher, and assemble the ISO outside this repo.
