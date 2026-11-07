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
