# Model buffer and ARAM limits (USA Rev 0, 2026-11-01)

The formulas below were checked against the target assembly of all three functions.
`fn_800227E4` MATCHes. `fn_80018024` is 76.17007%; `fn_800145F8` is
98.208694%. The latter two implement the sizing/initialization semantics but their
instruction scheduling/register allocation is not identical. No runtime importer
or modified-game test was performed.

## Descriptor fields and units

Both descriptor families use 16-byte records:

| Offset | C field | Meaning for these functions |
| --- | --- | --- |
| +0x00 | flags | Not consulted by either RAM sizing pass |
| +0x04 | sizeFlags | Low 28 bits are the decompressed file length in bytes |
| +0x08 | discOffset | Disc offset for disc subfiles; blob-relative offset for ARAM master entries |
| +0x0C | compressedSize | Stored/read byte length; not consulted by either RAM sizing pass |

Define `size(d) = d.sizeFlags & 0x0FFFFFFF` and
`align32(n) = (n + 31) & ~31` using 32-bit unsigned arithmetic.
The compression/other high-nibble flags do not contribute to the RAM maxima.
These are file-byte budgets, not vertex, triangle, texture or bone-count limits.

## fn_80018024: four body buffers

Inputs are the **runtime disc subfile descriptors** at `lbl_803CB790` (initial
source table `lbl_800F1D78`), 19 descriptors per character. It does not use the
body master descriptor or the body/overlay pairing table for this calculation.
It always visits all 54 charIDs, 0 through 53, regardless of the selected roster:

```
B = align32(max(size(subfiles[c * 19 + 0]) for c in 0..53))
A = align32(max(size(subfiles[c * 19 + 1]) for c in 0..53))
```

The target loop has 18 iterations with three character rows unrolled each time;
it visits 54 rows, not 18. It stores B at `g_hugeAnimStruct + 0x2D64`.

* Outside mode 6: `_OSAllocFromHeap(32, 4 * B)`; slot i, i=0..3,
  gets `fileBuffer = pool + i * B`.
* Mode 6: `_OSAllocFromHeap(32, 4 * (B + A))`; slot i gets
  `fileBuffer = pool + i * (B + A)` and
  `alternateFileBuffer = pool + i * (B + A) + B`.
* The pool pointer is at global +0x2C8C. Slot stride is 0x27C, slots start
  at global +0xC04, and the two file pointers are slot +0x08/+0x0C.
* It clears `stadiumObj`/`subItems` at slot +0x2C/+0x30 for slots 0..3;
  mode 6 additionally clears those fields for slots 4..7. It does **not** assign
  body file buffers to slots 4..7 in this function.

Retail values, computed from the existing C initializer in
`src/Unknown/gap_8001E460.c` (no original assets copied):

| Value | Bytes | Hex | Largest source row |
| --- | ---: | --- | --- |
| Track 0 maximum before alignment | 153396 | 0x25734 | charID 1 |
| B | 153408 | 0x25740 | charID 1 |
| A (track 1 maximum already aligned) | 81536 | 0x13E80 | charID 3 |
| Normal pool | 613632 | 0x95D00 | 4 * B |
| Mode-6 pool | 939776 | 0xE5700 | 4 * (B + A) |

There is no fixed maximum body file length here beyond descriptor encoding and
available main-memory heap. There is no allocation-failure or per-load slice
bounds check here. A replacement's decompressed length must be reflected in the
**runtime track descriptor before this allocator runs**. Patching only a master
body/overlay size does not grow these buffers. Increasing any character's track
maximum grows all four corresponding slices; existing allocations do not resize.

## fn_800145F8: thirteen sub-item pairs

The entry parameter is a signed 32-bit selector (`cmpwi r3,0` in the target):

* Zero: visit all 18 roster positions, `inMemRoster[team][player].charID`,
  team=0..1 and player=0..8. There is no invalid-charID guard before table indexing.
* Any nonzero value: visit every charID 0..53.

For each visited charID, read signed s16 `base = lbl_800EEAAC[charID]`.
If base < 0, skip that character. Otherwise read the six **runtime disc sub-item**
descriptors `lbl_803CB7A8[base + k]`, k=0..5. The initial disc descriptor table is
`lbl_800F5D98`. These are the six hand/glove model-plus-script file choices;
this scan does not use the seven-per-character ARAM master tier.

```
S = align32(max(0, size(subitems[base(c) + k])
                  for visited c with base(c) >= 0, k in 0..5))
pool = _OSAllocFromHeap(32, 26 * S)
entry[i].obj0.buf = pool + (2 * i) * S
entry[i].obj1.buf = pool + (2 * i + 1) * S    # i = 0..12
```

The pool is saved at `lbl_803CBC24`; S is not saved as a dedicated global by
this function. Cache entries begin at global +0x140 and have stride 0xD4.
There are **13 complete entries**, ending exactly at +0xC04, rather than the
old header's 12 entries plus padding. The two model records have stride 0x64.

It resets each entry's charID, previous slot and current slot to -1, arm/stance
to 0xFF, texture archive to NULL, valid to zero, and actor entry IDs to 2*i/2*i+1.
The target unrolls buffer assignment six pairs at a time (two batches plus one
remainder); metadata initialization still iterates over all 13 entries.

In the retail all-character table, maximum decompressed file size is 0xA3B0
(41904 B), charID 2, choices 1 and 4. Thus S=0xA3C0 (41920 B), and
26*S=0x10A180 (1089920 B). A roster-specific allocation can be smaller.
The zero-selector path is **not** a maximum over all characters available later.
A subsequently loaded character/file must fit the S established at allocation,
or the pool must be reallocated. Descriptor corrections made after allocation do
not enlarge slices. Negative bases exclude a character; no descriptor-count,
heap-failure, later-load-size or slice-overflow check is implemented here.

## fn_800227E4: model blob resident in ARAM (MATCH)

1. Calls `fn_800A6418(0x4D6600)`; saves its u32 ARAM address at
   `lbl_803716B8 + 0x1D4`; sets byte +0x1E9 to 1.
2. Uses 515 entries of the RAM address array `lbl_8017E320` across four tiers.
   Tier lengths are u16 `lbl_803CB7E0[0..3]`, retail {54,378,54,29}:

   | Tier | Master indices | Address table pointer in lbl_803716B8 |
   | --- | --- | --- |
   | Bodies/overlays | 0..53 | +0x1D8 |
   | Sub-items (54 * 7) | 54..431 | +0x1DC |
   | Skeletons | 432..485 | +0x1E0 |
   | Stadium/extra models | 486..514 | +0x1E4 |

   For each master entry j in ascending order, it writes
   `address[j] = aramBase + master[j].discOffset`. Counts partition the RAM
   pointer array; they do not reserve separate ARAM regions. Offsets determine
   placement inside the single blob. No descriptor size participates in this step.
3. Queues **master descriptor 515** (`lbl_800F1D68`) with destination aramBase,
   mode 2, NULL additional ARAM address, callback `fn_800227A0`, parameter 0.
   Retail descriptor 515 is `{flags=0, sizeFlags=0x4D6600,
   discOffset=0x1A15E800, compressedSize=0x4D6600}`: the whole blob is copied
   from that disc location. Individual master entries refer to stored payloads
   inside the blob; their offsets are not absolute disc offsets on this path.
4. The completion callback clears +0x1E9 and ORs bits 0..3 into +0x1EA,
   marking all four tiers resident. The setup function discards queue insertion's
   result; a full ring does not get an in-function retry.

The literal is used for **allocation only**, never as a checked bound for the
master offsets or the later transfer. It is not derived from descriptor 515.
An importer growing/repacking this blob must keep the literal, descriptor 515's
read/decompressed lengths and disc location, and all blob-relative offsets
consistent. Each stored entry's offset plus stored length must fit inside the
blob. Updating the allocation literal alone does not increase bytes read from disc.
The 515 used pointers occupy 0x80C bytes. `config/GYQE01/symbols.txt` gives
`lbl_8017E320` an extent of 0x820 bytes; the extra 0x14 bytes may be alignment
padding, so they are not a verified extension budget. Increasing tier counts
requires checking/resizing this reserved region and updating the master/tier
indexing consumers; this function has no count-sum guard.

### Actual allocator interval and capacity

`src/Unknown/File_0x800a6304.c` supplies the evidence, independently of the blob
literal. `fn_800A648C` initializes the game's ARAM arena to
`[0x00804000, 0x01000000)`, capacity **0x7FC000 = 8372224 bytes**.
`fn_800A6418` allocates from the low end, aligns length to 32, and updates its
free-byte arithmetic against the high-end allocator `fn_800A6354`.
It does **not** reject overlap/exhaustion. Current low/high allocations reduce
available space; the arena capacity is not a safe per-blob allowance at runtime.

The retail blob is **0x4D6600 = 5072384 bytes**, leaving **0x325A00** of that
arena only if there are no other allocations. A larger blob must satisfy the
current arena gap after 32-byte rounding, not merely be below 16 MiB. The sound
sample arena is below the game's 0x804000 start (see `.agent/sounds.md` section 7).
This allocation function does not query hardware ARAM size or provide a new limit
for additional memory configurations.

## Separate runtime actor workspace

These three functions do not prove an imported mesh fits every runtime buffer.
`fn_80023B04` allocates a separate **0x86A0-byte actor workspace per slot**
(`ACTOR_MEM_BLOCK_SIZE` in `gap_8002244C.h`). `f_InitActorWithLayout` carves
bone arrays, matrix arrays and per-bone/display data from that workspace.
Growing a body file allocation does not grow the actor workspace. Deriving
allowed geometry/bone expansion requires accounting for that independent layout;
there is no general vertex-count ceiling established by the three functions here.


2026-11-01 latest matching continuation: all sizing formulas above remain unchanged.
fn_800145F8 remains 98.208694%; fn_80018024 remains 76.17007%. Each received
five refinements and retains its prior source. Final ninja succeeds and all 4141
exact matches are preserved. Complete remaining instruction diffs are in
`fn_800145F8.final.diff` and `fn_80018024.final.diff`; no runtime asset test was run.

## Runtime limits for a new body on an existing skeleton (Codex read-only audit, 2026-11-08)

All from target asm; no custom-model runtime test yet.

### 1. Actor workspace: exact allocation and headroom

**The 0x86A0-byte workspace limits runtime structure size, not mesh size directly.**

`fn_80023B04` allocates `count × 0x86A0`, with consecutive slots spaced by that amount: `mullw` at **80023B20**, allocation at **80023B28**, stride at **80023B48–50**. Neither it nor the builders checks the final cursor against the slot’s end.

Evidence: [actor builders, C](../src/Unknown/gap_8002244C.c:319), [target assembly](../build/GYQE01/asm/Unknown/gap_8002244C.s).

Let `A(x) = (x + 31) & ~31`, `N = totalBones`, `S = 1` when `skinFileID != 0xFFFF`, and `L = 1` when the skin display object has lighting data.

```text
workspace =
    0xA0                         actor
  + A(4N)                        bone pointer array
  + (1 + 2S + S·L) × A(0x30N)   matrix arrays
  + 0x140N                       runtime bones
  + 0x20N                        animation pipes
  + sum(display-object costs)
```

Matrix arrays are forward matrices, plus skin and inverse-orientation matrices when skinned, plus inverse-transpose matrices when lit.

For **each instantiated display object**:

```text
D(layout) =
    0x80
  + 0x20 × (position-header-present
          + colour-header-present
          + lighting-header-present
          + display-header-present)
  + A(0x10 × textureChannelCount)  [when texture data and count are nonzero]
```

The instantiated objects are the skin object plus **one per bone with a valid geometry reference**. Reusing a descriptor on several bones still creates several copies.

Evidence:

- `f_InitActorWithLayout`: bone-pointer/matrix sizing **80023314–34**; actor `0xA0`, bone stride `0x140`, reservation arithmetic **800233C0–80023418**.
- `f_InitBone`: reserves `0x80` before calling `fn_80023078` at **80022ECC**; each animation pipe advances the cursor by `0x20` at **80022F0C**.
- `fn_80023078`: copies only headers. Position/colour/lighting/display each advance by `0x20` at **800230A8**, **800230E8**, **800231C4**, **8002320C**; texture-header storage is `A(16T)` at **80023138–50**.

**Nothing here scales directly with vertex count, triangle count, skin-list counts, morph-shape counts, or uninstantiated geometry descriptors.** Their payloads remain in the loaded file.

| Retail body | Workspace used | Remaining |
|---|---:|---:|
| Largest workspace: Dry Bones family, IDs 48–51, both tracks; 52 bones, 12 bone display objects plus skin | `0x7E80` / 32,384 B | **`0x820` / 2,080 B** |
| Largest file: Luigi track 0; 37 bones, one bone display object plus skin | `0x5260` / 21,088 B | **`0x3440` / 13,376 B** |
| Mario, either track | `0x5260` | `0x3440` |

There is a bone-count consistency panic **after construction**, not a workspace-capacity check. An oversized layout can already have overwritten memory.

### 2. Runtime skinning: list limits and output storage

**There is fixed skinning scratch space, independent of the actor workspace.**

`SKNInit` assigns locked-cache addresses at **800BF230–8C**:

| Path | Alternating scratch regions | Required transfer footprint for s16 position+normal records |
|---|---|---|
| SK1 | `E0000000`, `E0002000`: **0x2000 bytes each** | `A(offset + 12n) ≤ 0x2000` |
| SK2 | vertex regions at `+0000/+2000`, weights at `+1000/+3000` | `A(offset + 12n) ≤ 0x1000`; `A(2n) ≤ 0x1000` |
| Accumulator | source at `+0000/+2000`, indices at `+1000/+3000`, weights at `+1800/+3800` | `A(12n) ≤ 0x1000`; `A(2n) ≤ 0x800`; `A(n) ≤ 0x800` |

Thus the zero-offset **scratch-capacity ceilings** are SK1 **682**, SK2 **341**, accumulator **341** contributions per list. Offsets reduce the first two. These are derived capacity ceilings, **not tested safe boundary cases**; kernels also perform read-ahead loads.

Evidence: [skinning assembly](../build/GYQE01/asm/Unknown/gap_800BD3A0.s), especially `fn_800BF2A8`:

- SK1 `12 × count + offset`: **800BF2F0–800BF30C**.
- SK2 vertex and weight block counts: **800BF464–800BF4B4**.
- Accumulator source/index/weight block counts: **800BF6AC–800BF710**.

Additional constraints:

- **SK1/SK2 lists should contain at least two vertices.** Their kernels load CTR with `count−1` and enter an unconditional `bdnz` loop: `fn_800BFF9C` **800BFFA8–B8**, **800C002C–78**; `fn_800C02C8` **800C02D0–800C0308**. Counts 0/1 are unsafe. Accumulator lists require a positive count.
- List counts are **u16** at skin-header `+0/+2/+4`; vertex counts are u16 at SK1 `+0x3A`, SK2 `+0x70`, accumulator `+0x42`. No smaller fixed list-count array or total-contribution ceiling was found.
- Bone indices address the actor’s **runtime traversal order**, not stable bone IDs: e.g. **800BF370–80** indexes `boneArray[boneIndex]`.
- Accumulator destination indices are **u16** and multiplied by **12** at **800C063C–68**. Repeated contributions allow more than two influences; no eight-influence runtime cap was found.
- Use **32-byte-aligned DMA bases**, reserve complete rounded transfer ranges, and preserve readable kernel padding. SK1/SK2 store whole rounded ranges, including bytes surrounding their logical vertices; arrange overlapping boundary blocks consistently.

**Output lives inside the loaded model file.** `LoadGeoPalette` finds the position array with `compCount == 6`; `convertGeometryAndSknHeader` saves that pointer at palette `+8`. Skinning adds each list’s destination offset to that base: **800BF3BC–C8**, **800BF5B4–C4**, **800BF7BC–E0**. There is no vertex-sized heap allocation here.

Provide one coherent interleaved output array of **12 bytes per s16 position+normal record**, with valid padding and destination ranges. Avoid multiple competing `compCount==6` arrays: palette loading selects the last, while actor initialization searches from the first.

Retail maxima observed: **681 SK1**, **340 SK2**, **146 accumulator** entries per list; largest skinned output array **1,551 records**. These are retail usage, not total-model limits.

### 3. Geometry descriptors and display lists

**The generic body path does not require a character-specific descriptor count.** It consumes the file’s palette count, bone `geoFileID`s and layout `skinFileID`.

- `skinFileID` and bone geometry IDs must reference existing descriptors, or use `0xFFFF` for absence. Invalid bone IDs report and omit that display object; invalid **skin** IDs report, then dereference NULL at **800233A0**.
- Descriptor numbers also appear in **morph array/target bindings**. `fn_80025C58` directly indexes `descriptorArray[id]` at **80025D3C–50**, without a bounds check.
- No additional fixed descriptor-number requirement was found in the inspected character setup paths. **An exhaustive proof covering every character-specific gameplay/effect consumer remains unverified.** Those paths also depend on stable bone IDs.

Evidence: [geometry C](../src/Unknown/gap_800B993C.c:145), [renderer assembly](../build/GYQE01/asm/Unknown/gap_800B993C.s).

`DOVARender` walks the file’s display-state records, calls `SetState`, then passes each primitive buffer directly to `GXCallDisplayList`: **800BC778–800BC7C0**, call at **800BC7A8**. It does **not** parse or require triangles rather than strips.

`SetState` recognizes IDs **1–4**:

- 1: texture state.
- 2: vertex descriptor.
- 3: custom state handler.
- 4: matrix state.

Evidence: dispatch **800BBB5C–88**; vertex-descriptor decoding **800BBD64–800BBEAC**. Supply the appropriate states before drawing; arbitrary IDs do not establish missing GX state.

Vertex descriptor fields retain their two-bit GX modes, so **u8 and u16 indexed attributes are supported**; the runtime does not force every index to u16. There is no u32 indexed mode in this encoding. Attribute array counts are u16, so keep advertised counts and all referenced indices consistent. Display-list lengths/counts do not consume actor workspace.

### 4. Morph data: optional, but referenced shapes must exist

**A body may have morph pointer zero.** `fn_80017814` skips morph relocation/binding when root `+0x10 == 0`; `fn_80025FFC` returns immediately for a NULL morph pointer at **80025FFC–80026000**. `fn_80024FA4` also exits for NULL morph data or a NULL array table at **80024FC4–80024FF4**.

Retail confirms this: **every track-1 body has no morph block**, and several track-0 bodies also lack one.

When morphing is retained:

- Event keys select shapes by number, including caller-selected shapes under flag `0x2000`: **800252F0–80025350**.
- `fn_80024FA4` multiplies selected shape IDs by four and directly loads target shape pointers at **80025350–64**, **800254BC–D4**.
- **No selected-shape-versus-shape-count check was found.** Fewer shapes than scripts request causes out-of-range pointer reads, not automatic clamping.
- Morph targets must be rebuilt for the new vertex arrays/runs. Keeping retail targets while changing vertex order can overwrite incorrect vertices or exceed the new array.
- Morph data and optional work storage are file-resident: `fn_80025DDC` relocates array work pointers at **80025EC0–D8**; these are not additions to the actor workspace.

Evidence: [morph application assembly](../build/GYQE01/asm/auto_fn_80024FA4_text.s), [binding assembly](../build/GYQE01/asm/auto_fn_80025C58_text.s).

Omitting body morphs disables those deformations. The inspected paths tolerate absence; **complete visual/character-specific behavior without them is unverified**. Hand/glove morphs belong to separate sub-item files and remain relevant.

### 5. Low-detail body, track 1

`fn_8001758C` selects:

```text
track = charID × 19 + (variant == 0)
```

Normal fielders and runners use variant 0; batters and menu/cutscene actors use variant 1. Evidence: [loader C](../src/Unknown/gap_8001196C.c:1190), including cached runner/batter branches.

**The low body can structurally be the same model as the high body.** There is no separate low-body skeleton-order rule in this loader. It must satisfy its own file-buffer capacity, workspace budget and skin/morph bindings; using high detail for all fielders also increases rendering cost.

Mario’s retail bodies both have 37 bones, but different record order and different `skinFileID`—high 0, low 1. That is **file-local organization**, not a required high/low convention.

Preserve stable bone IDs, hierarchy and bind transforms. If records/traversal change, regenerate skin-list bone indices accordingly. `f_InitBone` constructs runtime order by recursively walking children and siblings; `fn_80017814` separately builds the gameplay bone-ID map.

**Same bone count alone is insufficient.** The gameplay map has 120 entries; non-sentinel bone IDs are written without a range check. Preserve the existing skeleton’s IDs, including attachment bones.

### 6. Additional buffers and constraints

**Important omission from `model_limits.md`: `fn_80018270`.**

Its target assembly in [gap_8001196C.s](../build/GYQE01/asm/Unknown/gap_8001196C.s) establishes another body allocation:

- Ordinary path: **nine low-body slots + four high-body slots + one cache of each**.
- With aligned maxima `H` and `L`, total allocation is **`5H + 10L`**: arithmetic **80018714–40**; slot/cache placement **80018760–800187F0**.
- Selector 0 scans the active roster. The nonzero/non-2 path scans high tracks for IDs **0–47**, low tracks for **0–53**. Do not assume every later replacement contributes to its allocation.
- **Selector 2 uses fixed fielder allocations:** slot 0 gets **0x13E80**, slots 1–8 get **0x12C40** each: **8001829C–800182E4**. Its low-body cache is also **0x13E80**, at **800183F0–80018418**. Descriptor growth does not enlarge these constants.
- Cached copies use the established cache size, without checking the destination: **800176A4–AC**, **800176EC–F4**.

For textures, no independent body texture-byte staging allocation was found: `convertTextureHeader` relocates the archive in place. However:

- Sub-items use the **body’s texture archive**; preserve their texture IDs or update them.
- ARAM overlays overwrite at `body + root.texture`: `fn_8002254C`, **80022558**, **80022584**. An old overlay can corrupt a repacked body if its destination region no longer fits or has changed meaning.

The four-buffer allocator, sub-item pools and ARAM blob limits already documented in `model_limits.md` still apply. **No exhaustive whole-game allocation audit or runtime heap-headroom measurement was performed.**

### Importer rules

1. Preserve the existing skeleton’s IDs, hierarchy and bind transforms; regenerate skin bone indices if traversal order changes.
2. Compute the workspace formula and require **`used ≤ 0x86A0`**. Count instantiated display objects, including repeated descriptor references.
3. Split skin lists to fit the locked-cache partitions; prohibit SK1/SK2 counts below two, and reserve DMA rounding/read-ahead padding.
4. Store correctly sized skinned output inside the body file; validate every destination, accumulator index and bone index.
5. Keep geometry, skin, morph and texture references internally consistent. Triangles and strips are both usable; encode indices according to the supplied GX vertex descriptor.
6. Either rebuild every referenced morph shape/run or omit the body morph block, accepting lost deformation.
7. Validate **both tracks against every applicable allocator**, especially `fn_80018270`’s fixed selector-2 buffers. High-body duplication into track 1 is not universally safe through descriptor edits alone.
8. Rebuild or disable incompatible texture overlays, preserve sub-item texture bindings, and update file/ARAM descriptors before allocation.