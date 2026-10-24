# Character Modding Report: duplicate characters with unique designs

*Mario Superstar Baseball (GYQE01), mssb-dtk. Compiled 2026-10-22 from three Fable passes:
`.agent/character_modding.md` (full working notes), `.scratch/fable_notes.md` in the Fable worktree,
and the doc comments above each chain function in `src/`.*

**Goal:** several copies of one character on the field at once (e.g. three Marios), each with its own
textures/colours, ideally without giving up other roster slots.

## TL;DR

1. **The engine already does colour variants.** Pianta B/R/Y, the five Toads, the Shy Guys and the
   other variant families are separate character slots. They share animation and skeleton files but
   point at their own two model files (`.gpc`). A "variant" is just a slot whose model rows differ.
2. **Data-only cloning works inside the 54 slots, but every clone costs a roster slot.** Going past
   54 needs code changes, because every table is fixed at 54 and the code bounds-checks `charID < 0x36`.
3. **A source-level "skin variant" works and is now practical.** Keep `charID` for gameplay and add
   a cosmetic `skin` byte consulted in four lookups. Most of the functions involved are now matched
   or fully decompiled. The character disc tables are editable C arrays, and the build can link
   modified code (`configure.py --non-matching`).
4. **Cheapest experiment:** a texture-only swap in `fn_80017814`. Replace the texture-archive pointer
   before `convertTextureHeader` / `fn_800BD190(geo, tex)` and you get the same model with different
   textures.

---

## 1. The load chain: charID → model / texture / skeleton / gloves

Identity: `enumCharacterID` 0..53 (mario=0, luigi=1, DK=2, …, PiantaB/R/Y=21/22/23, broB=53).
Per player it lives in `inMemRoster[team][slot].stats.CharID` (s16 @ +0x24). Per on-screen actor it
lives in `AnimationStruct.charID` (@ 0x252).

```
fn_80017098  request a character load / reuse an already-loaded slot (entry point)
  └ fn_8001758C  fill the slot record (charID 0x252, slotKind 0x254, team/player 0x256/7,
  │              variant 0x259, arm/stance 0x25A/B), track = charID*19 + (variant==0)
  │   ├ cached batter/fielder model memcpy (g_hugeAnimStruct 0x2D54/0x2D3C), or
  │   ├ fn_8002204C(charID, buf)        body model: body-item pair → master descriptor, or disc track 0
  │   └ ARAMTransfer(&lbl_803CB790[track])
  ├ fn_80016344 / fn_80016710   per-slot state machine: anim banks (tracks 16/17),
  │   │                         skeleton, stadium object (lbl_800EEB18 model map), sub-items
  │   ├ fn_80021BBC  skeleton rig: master descriptor 432+charID, else disc track 15
  │   ├ fn_80016B60 / fn_80016F7C  stream the 5 animation banks (tracks 4/12/5/2/16)
  │   └ fn_80012B90 / fn_80013680  bat + glove loaders; fn_80021CA4 = sub-item pair loader,
  │                                fn_8002244C = load-queue callback chaining the 2nd sub-item
  └ fn_80017814  relocate the .gpc root header {texture, layout, geo, skin, extra}
      ├ convertTextureHeader(root->texture)      texture offsets → pointers
      ├ LoadActorLayout / convertGeometryAndSknHeader → LoadGeoPalette
      ├ fn_800BD190(geo, tex)                     ← binds textures to geometry (texture-swap hook)
      ├ fn_8002399C → f_InitActorWithLayout       build the actor; crash site 0x800233A0
      ├ bone-index map (anim->boneIndices[120] @0x162), bone setup calls
      └ per-charID switch (jumptable_800EEC40)    character-specific setup
Disc reads: ReadDataFromDisk → DecompressDiskData (Namco LZSS; bit 30 of the size word = compressed)
Gloves:     lbl_800EEAAC[charID] (= charID*6) = start of that character's 6-entry attachment-bone list
```

Textures live **inside** the slot's model `.gpc` (a `TextureArchiveHeader {u16 count; TextureHeader[count]}`
whose offsets are relative to the archive start). Nothing re-reads textures from a separate table, so
recolouring means either pointing a slot at different model files or swapping the archive pointer.

## 2. Function status

All of these have full, documented bodies in `src/`. Each block comment covers purpose, parameters,
tables and globals, where it sits in the chain, its match status, and the skin-hook point.

| Function | Source file | Role | Status |
|---|---|---|---|
| `fn_80017098` | src/Unknown/gap_8001196C.c | load request / slot reuse | **MATCH** |
| `fn_8001758C` | src/Unknown/gap_8001196C.c | slot record + track pick + body load | **MATCH** |
| `fn_8002204C` | src/Unknown/gap_8001E460.c | body model loader | **MATCH** |
| `fn_80021CA4` | src/Unknown/gap_8001E460.c | sub-item (bat/glove) pair loader | **MATCH** |
| `fn_80021BBC` | src/Unknown/gap_8001E460.c | skeleton loader | **MATCH** |
| `fn_8002244C` | src/Unknown/gap_8002244C.c | sub-item queue callback | **MATCH** |
| `fn_8002399C` | src/Unknown/gap_8002244C.c | actor slot init | **MATCH** |
| `fn_80016B60` | src/Unknown/gap_8001196C.c | streams 5 anim banks | **MATCH** |
| `fn_80016F7C` | src/Unknown/gap_8001196C.c | drives fn_80016B60 for slots 0..3 | **MATCH** |
| `convertTextureHeader` | src/Unknown/gap_800BD3A0.c | texture offset fixup | **MATCH** |
| `LoadGeoPalette` | src/Unknown/gap_800B993C.c | geometry palette fixup | **MATCH** |
| `fn_80016344` | src/Unknown/gap_8001196C.c | per-slot load state machine | 33 diff lines: two common-subexpression temps land in r26 instead of r30/r29 |
| `fn_80016710` | src/Unknown/gap_8001196C.c | same, fielder variant | 32 diff lines: same two temps, swapped |
| `fn_80017814` | src/Unknown/gap_8001196C.c | root relocation, texture bind, actor build, per-char switch | 54 diff lines: prologue snapshot register, bone-loop init, call-argument scheduling |
| `f_InitActorWithLayout` | src/Unknown/gap_8002244C.c | carve actor/skin/bones from memory block | 98 diff lines: original keeps cursor/skin object in stack memory (0x110 frame); the escaping local struct makes MWCC reload and CSE differently |
| `DecompressDiskData` | src/Unknown/File_0x800a64e0.c | LZSS expansion | 31 diff lines: saved-register set and ctr copy loop (now clean C, inline asm removed) |
| `fn_80012B90` | src/Unknown/gap_8001196C.c | bat/glove pair loader (3 pairs × 2 models, 9 steps) | first decompile (0xAF0 bytes): control flow, offsets and arguments verified, registers untuned |
| `fn_80013680` | src/Unknown/gap_8001196C.c | mode-2 bat/glove loader with cache + bone attach | first decompile (0xB84 bytes): same |

## 3. Tables and addresses

DOL file offset = RAM − 0x800E8300 + 0xE5300 for `.data`. The tables in rows 1–7 are now
byte-exact C arrays at the top of `src/Unknown/gap_8001E460.c`
(split `.data 0x800EFBE8..0x800F7478`), so a source mod can edit them directly.

| Table | RAM (DOL off) | Shape | Meaning |
|---|---|---|---|
| `lbl_800EFBE8` | 0x800EFBE8 | 21 × 16 B | misc disc-file descriptors (anchor of the unit's `.data`) |
| `lbl_800EFD38` + `lbl_800F1D68` | 0x800EFD38 (0xECD38) | 516 × 16 B | **master descriptors** `{flags, 0x40000000\|size, offset, compSize}`; offsets are relative to the 4.9 MB section-2 blob (entry 515 = `{0, 0x4D6600, disc 0x1A15E800, 0x4D6600}`, streamed to ARAM by `fn_800227E4`). Tiers from `lbl_803CB7E0` = {54, 378, 54, 29}: **0..53 is NOT charID-indexed**: 0..32 are the 33 base bodies, 33..53 are 21 texture overlays, mapped through `lbl_800F73B8`; `54 + charID*7 + k` sub-items, `432 + charID` skeletons, `486 + id` stadium objects |
| `lbl_800F1D78` | 0x800F1D78 (0xEED78) | 54 × 19 × 16 B | **per-character disc subfiles**, index `charID*19 + track`: tracks 0/1 = the two body `.gpc` files (**verified:** track 0 = hi-detail body, byte-identical to the ARAM master body; track 1 = low-detail body, same 37 bones, `skinFileID` 1), 2..14 anim banks, **15 skeleton**, 16..18 more anim banks |
| `lbl_800F5D98` | 0x800F5D98 | 54 × 6 × 16 B | disc files for sub-items (`charID*6 + itemSlot`) |
| `lbl_800F73B8` | 0x800F73B8 (0xF43B8) | 54 × 2 s8 | **body/overlay pairs** `{bodyEntry, overlayEntry or -1}` (ARAM path, the normal in-game path). `fn_8002254C` decompresses `master[overlay]` straight over the body's texture archive (`block + root->texture`): the overlay is a same-size replacement `TextureArchiveHeader`. E.g. BlueToad 29 = `{13, 34}`, Paragoomba 41 = `{29, -1}` |
| `lbl_800F7424` | 0x800F7424 | 2 × 6 × 2 | sub-item pair rows `{k1, k2}` |
| `lbl_800F743C` | 0x800F743C | 54 | per-character sub-item row index |
| `lbl_800EEAAC` | 0x800EEAAC (0xEBAAC) | 54 × u16 | glove/attachment bone-list base (= charID*6 in retail) |
| `lbl_800EEB18` | 0x800EEB18 | 54 × s16 | model ID map → stadium-object tier (**not** identity: variants map to their base's id, e.g. Toads → 13, Piantas → 19; -1 = none) |
| `jumptable_800EEC40` | 0x800EEC40 | 48 entries | per-charID setup switch in `fn_80017814` |
| `lbl_803CB790` | sdata | pointer | runtime pointer to the subfile table |

Retail variant evidence (`lbl_800F1D78` rows): Piantas 21/22/23 share tracks 2, 3, 15 (`0B977800`,
`0B9AF000`, `0BAD6800`) and differ only in tracks 0/1. Families that share tracks 2..14:
{12,42} koopa, {13,29–32} toads, {16,44–47} shy guys, {20,43} paratroopas, {21–23} piantas,
{24–26} nokis, {27,52,53} bros, {33–36} magikoopas, {48–51} dry bones.

## 4. How to add new textures or recoloured duplicate characters

### 4a. Data-only slot clone (works today, costs one roster slot per clone)
For each clone slot S of source character C:
1. **Subfile rows** `lbl_800F1D78[S*19 + t]`: alias C's rows for tracks 2..18 (as the retail variants
   do). Point tracks 0/1 at new recoloured `.gpc` files appended to `files/ZZZZ.dat`: 32-byte
   aligned, LZSS packed, size word `0x40000000 | uncompSize`. Patch **both** track 0 and track 1,
   since which one is the body is unverified.
2. **Master descriptors:** copy C's 7 sub-items to `54 + S*7 + k`, and set `432 + S` (skeleton) to C's.
3. **Body-item pair** `lbl_800F73B8[S]` = C's pair. The fork doesn't know this table, and it's used
   on the ARAM-resident path.
4. **Gloves** `lbl_800EEAAC[S]` = `lbl_800EEAAC[C]`. **Model map** `lbl_800EEB18[S]` = C's entry.
5. **Per-character setup:** if C has a case in `jumptable_800EEC40`, S needs it too. DK (2) →
   `fn_800638B4`, Magikoopas 33–36 → `fn_80063010`, and others. Mario (0) has no case, so a Mario
   clone needs no jump-table patch.
6. **Recolour textures in place:** edit only the CMPR colour endpoints inside the texture-archive
   region of the `.gpc` (for `donkey00.gpc` that's 0x180..0x4F00). Leave geometry, display lists and
   palettes byte-exact.
7. Copy C's stat row if the clone should play like C.

**Limits:** max 54 characters total; each clone replaces a donor (pick rarely used slots such as the
Shy Guy colours); names, portraits and menus still belong to the donor unless patched too.

### 4b. Texture-only swap (smallest code change)
In `fn_80017814`, right after the root header is relocated, replace `root->texture` with an
alternative `TextureArchiveHeader` (loaded or embedded per skin) **before** it's passed to
`convertTextureHeader` and `fn_800BD190(geo, tex)`. Same model and skeleton, different textures.
The archive must have the same texture count and dimensions as the original.

### 4c. Full source-level skin variant (no lost slots, recommended end state)
*R2 result (2026-10-24, `.agent/roster_flow.md` §6): the design below is confirmed, with three
corrections. (1) `UnusedBytes[0]` is inside the `memcpy(dst, src, 0x1E)` that every roster rebuild
starts with, so the byte is reset from the static row at ready (`fn_2_8940`), at the fielding-position
re-copy (`characterSelectScreen`), at the in-game star toggle (`transferStatsToInMemRoster`) and at
lineup edits; those copy sites must re-apply it from the menu choice (`lbl_803C6724.unk38[2][9]`, free).
(2) Fielders and runners load with `variant = 0`, i.e. the low-detail body from disc track
`charID*19 + 1`, not the ARAM pair: the skin must redirect both `fn_8002204C` (batter) and the
`ARAMTransfer(&lbl_803CB790[track])` fallback in `fn_8001758C` (everyone else). (3) The batter/runner
model caches (`cachedBatterCharID`, `cachedFielderCharID`) are keyed on charID only.*
* **Store the skin:** `StatTable.UnusedBytes[0]` per roster entry (`inMemRoster`, +0x05). Copy it in
  `fn_8001758C` into a spare `AnimationStruct` byte (`_rest253`, verified unused by every module),
  next to the arm/stance copy.
* **Switch these lookups to `(charID, skin)`:**
  1. `fn_8001758C`: the subfile track index (`charID*19 + (variant==0)`)
  2. `fn_8002204C`: `lbl_800F73B8[charID]`, master `[charID]` size, `lbl_800F1D78[charID*19 + 0]`
  3. `fn_8002244C` / `fn_80021CA4`: sub-item descriptors `54 + charID*7 + k` (only if bats/gloves change)
  4. `fn_80016344` / `fn_80016710`: `lbl_800EEB18[charID]` (only if the stadium object changes)
* **Leave on `charID`:** animation banks, skeleton (track 15 / 432+charID), gloves, the
  `fn_80017814` switch, stats, AI, voice, and every `AnimationStruct.charID` comparison in game code.
* **Data:** append `skinTable[54][N]` of extra subfile/descriptor rows to the C tables in
  gap_8001E460.c. `skin == 0` means the retail row, so unmodded saves behave identically.
* **UI:** a roster/menu REL change to choose a skin, or preset it in default roster data.

### 4d. Building a modded binary
1. In `configure.py`, mark the units you edit as `Equivalent`. Here that's
   `Unknown/gap_8001196C.c`, `Unknown/gap_8002244C.c` and `Unknown/gap_8001E460.c`
   (only the units you change).
2. `python3 configure.py --non-matching && ninja`. This links C objects in place of the target
   asm and skips the hash check. Tested: it links main.dol and all 3 RELs, and shifted symbols
   relocate.
3. Take `build/GYQE01/main.dol` and the RELs plus the patched `files/ZZZZ.dat`, and assemble the ISO
   outside the repo. Keep `orig/` read-only.
4. **Risks:** absolute `.4byte 0x80xxxxxx` literals in unsplit data aren't relocated. The
   non-matching units (fn_80012B90/fn_80013680 especially) are semantically checked but untested at
   runtime, so test in Dolphin.

## 5. Corrections to the fork's guide (`fork/feat/character-cloning-texture-decoupling`)

The guide is AI-written and largely unverified. Against the matched code:
* **The "zero code change" claim doesn't fully hold.** The "batting style hook at 0x80001840" is OS
  low memory, not a DOL table. No code or symbol references it, so it was an emulator-side poke.
* **The crash at 0x800233A0 is not the glove table.** It's the NULL dereference in
  `f_InitActorWithLayout` when `layout->skinFileID >= geoPalette->numDescriptors`, a layout/palette
  mismatch (wrong skeleton or body file for the slot). The glove table only feeds the bone-list walk.
* **It misses tables:** the body-item pair table (`lbl_800F73B8`) and the per-charID setup switch
  (`jumptable_800EEC40`). A DK clone needs case 2 → `fn_800638B4`.
* **It wastes space:** copying all 19 tracks (~2 MB per clone) is unnecessary. Aliasing tracks 2..18,
  as the retail variants do, costs only the two `.gpc` files.
* **Consistent but unverified:** the `.gpc` texture map (archive at 0x20, ten textures in
  0x180..0x4F00 for DK) agrees with `TextureArchiveHeader`/`convertTextureHeader`, but nobody has
  re-checked it against the disc.

## 6. The in-unit table experiment (outcome: it worked)

`fn_8002204C` and `fn_80021CA4` addressed four separate `.data` symbols as `&lbl_800EFBE8 + const`
(`addi r4,r31,0x2190` then `lwzx`). That pattern means the original source *defined* the tables in
the same file, and MWCC addresses file-local data from one anchor. Defining them as initialized C
arrays in `gap_8001E460.c` reproduced the codegen exactly:
* `config/GYQE01/splits.txt`: `.data start:0x800EFBE8 end:0x800F7478` added to `Unknown/gap_8001E460.c`.
* `config/GYQE01/symbols.txt`: `lbl_800F71D8` shrunk to 0x1E0; new `lbl_800F73B8` (0x6C),
  `lbl_800F7424` (0x18), `lbl_800F743C` (0x36).
* Result: both functions MATCH, the unit's 30,864-byte `.data` is 100% matched, the DOL hash
  check passes, and nothing regressed.
* **One open rule exception:** `masterDescSizeFlags()` in gap_8001E460.c reads
  `*(u32*)((u8*)lbl_800EFD38 + idx*16 + 4)`, the only pointer arithmetic in the unit. Every
  struct/array form folds the +4 into the displacement and breaks the `lwzx` match. **It needs a
  maintainer decision:** keep it (documented) or revert to the struct form and lose the match.
* **Lesson for the knowledge base:** when a function forms `(base + const) + idx` across several
  adjacent symbols, the data is defined in that unit, so give the unit a `.data` split.

## 7. Open questions / next steps

1. **Verify tracks 0/1:** which one is the body `.gpc` and which the equipment. Dump both for one
   character from `files/ZZZZ.dat`.
2. **Data-only prototype:** three recoloured Marios on three spare slots (4a), tested in Dolphin.
   Mario needs no jump-table patch.
3. **Texture-swap prototype** (4b) in a `--non-matching` build: the smallest code change that
   proves per-actor textures.
4. **Remaining matches:** fn_80016344/fn_80016710 (one register-allocation issue shared by both),
   fn_80017814, f_InitActorWithLayout (find the non-escaping aggregate shape), DecompressDiskData
   (ctr loop), then tune fn_80012B90/fn_80013680.
5. **Doc cleanup (done in this commit):** `.agent/character_modding.md` said "Mario = 2 → fn_800638B4" (charID 2 is DK; Mario is 0) and that DecompressDiskData kept inline asm (it is now C).
6. Dump the retail body-item pairs (`lbl_800F73B8`) and model map values into the notes. They're
   now readable directly from the C arrays.

## 8. Pass 4 (2026-10-23): the patcher, and what it corrected

`tools/modding/clone_character.py` (+ `test_clone.py`, `README_WINDOWS.md`) implements recipe 4a
for Windows with the standard library only.  What this pass established:

* **Open question 1 resolved.** Track 0 is the hi-detail body (== master body entry, 256×256
  textures); track 1 the low-detail body (`skinFileID` 1).  Both are full models with the same 37-bone
  layout and both get recoloured.
* **The ARAM path is the in-game path.** `fn_800227E4` allocates a hard-coded 0x4D6600 B of ARAM
  (`lis r3,0x4d / addi r3,r3,0x6600` @ 0x800227EC/F4), sets every tier's ARAM address to
  `aramBase + master[i].offset`, streams master[515] disc→ARAM and the callback sets
  `lbl_803716B8.unk1EA |= 0xF`.  **Correction (R2, roster_flow.md §5.5):** only the batter
  (`fn_8001500C`, slotKind 9) and the menu/cutscene loads (`fn_80016344`/`fn_80016710`) pass
  `variant = 1` (ARAM body via `lbl_800F73B8`); the nine fielders (`fn_8001594C`) and the runners
  pass `variant = 0` and stream the low-detail body from disc track `charID*19 + 1`.  The patcher is
  unaffected because it patches tracks 0 and 1 and the ARAM pair.
* **Retail variants are body + texture overlay.** Verified: `track0(BlueToad) == master[13]` with
  `master[34]` written at `+0x20`; overlay length == `layoutOff − 0x20`; variant track files differ
  from the base only inside the texture region.  So a clone on donor S is `pair[S] = {source body,
  O}` where O is S's own overlay entry (or its body entry when no other slot uses it) repointed at a
  recoloured copy of the source's archive.  The blob must grow for that; other data follows it on disc,
  so the patcher moves the blob to the end of ZZZZ.dat and patches master[515] and the two
  immediates (the only `.text` change, 8 bytes).
* **Disc offsets** are file-relative offsets into ZZZZ.dat (`ARAMTransfer` → `DVDFastOpen(entry)` →
  `DVDReadAsyncPrio(file, staging, min(comp,0x8000), desc->offset)`).  Reads always land in a staging
  buffer that only the LZSS thread drains, so **files must stay compressed** (clearing bit 30 does not
  work).  Appending to ZZZZ.dat is safe: nothing references the last 0x5C0 bytes and Dolphin rebuilds
  the FST from the folder (`sys/fst.bin` is patched anyway).
* **Selection UI:** there is no colour button.  `lbl_800E8558` (family/base/colour per slot) and
  `lbl_80108EDC` (9 family lists) make the roster screen hand out the next free colour when a family's
  base is picked several times.  Names/portraits/announcer stay the donor's (grid-index keyed, no
  per-charID name table exists).  Stats: `ZZZZ.dat+0x06CF8800`, 54 × 0xA0 `CharacterStats`, loaded by
  menus.rel at boot; game.rel `.data` (section 5) holds voice base 0x8168, BatterHitbox 0x6EF8, charge
  frames 0x7690, runner timing 0x7870, 0x7E34, 0x17000, all charID-indexed; DOL `lbl_800FB798` is 15 ×
  54 s16 animation parameters.
* Pure-Python LZSS (11/4) round-trips every retail file tried and compresses Mario's body to 76992 B
  (retail 77284 B).
* **Base donors (e.g. `--slot Luigi:green`):** the clone's overlay goes into the donor's own body entry
  (`master[1]`), so `master[1].sizeFlags` becomes the archive size (0xC2C0).  That is harmless: retail
  already has `master[charID].size` smaller than the body it loads (BlueToad 29: 0x18028 vs body 13's
  0x195B0; BlueShyGuy 44: 0x5BE0 vs 0x16320), and `fn_8002204C` only uses it when `buf == NULL`, which
  no caller does.  Do not "fix" it by resizing the entry.

## 9. Recipe 4b/4c status (source-level), 2026-10-23

Not built tonight, on purpose:
* **4b is already what the engine does.** The per-actor texture swap in `fn_80017814` would
  reimplement `fn_8002254C`'s body + overlay load.  The data-only patcher uses that mechanism, so a
  second, untested binary would only widen tonight's test matrix.
* **4c needs a per-roster-entry skin source, not a per-charID byte.** `StatTable.UnusedBytes[0]`
  is per charID: the roster `memcpy` copies the same `CharacterStats` row for every Mario, so three
  Marios would all get skin 0.  Design for next time: in `fn_8001758C`, derive `skin` from the actor's
  team/player bytes (0x256/0x257) by counting earlier same-team roster entries with the same charID
  ("n-th duplicate gets skin n"), then index a `skinPairs[charID][skin]` extension of `lbl_800F73B8`
  in gap_8001E460.c (body entry + overlay entry).  `fn_8001758C` and `fn_8002204C` are matched, so
  this is a `--non-matching` build with two `Equivalent` units (`gap_8001196C.c`, `gap_8001E460.c`)
  plus the overlays appended to the blob exactly as `clone_character.py` does (reuse its
  `lzss_compress`, blob move and `fn_800227E4` size patch).  Everything else (animations, skeleton,
  gloves, stats, menus) keeps using charID, so no roster slot is lost.
