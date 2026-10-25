# GYQE01 data map: every file in ZZZZ.dat and aaaa.dat

*Mario Superstar Baseball (GameCube, USA rev 0). Compiled 2026-10-24 on branch `data-map`.
Tool: `tools/datamap/mssb_files.py` (see `tools/datamap/README.md`). Every number below comes
from `mssb_files.py coverage/list/tables` and `test_mssb_files.py`. Rerun those to check.*

## 1. TL;DR

* The disc has 20 FST files. All game data except music and the banner is in **`files/ZZZZ.dat`**
  (450,041,856 B) and **`files/aaaa.dat`** (1,538,048 B, the three RELs). Neither has a directory.
  The game addresses files only through **16-byte disk-file descriptors** compiled into
  `main.dol` and the RELs.
* **67 descriptor tables** (3,119 descriptor rows) name **1,571 distinct files**: 3 in aaaa.dat,
  1,223 in ZZZZ.dat and 345 inside the 4.9 MB ARAM blob. Most files have several descriptor copies
  (the 62 common UI resources have up to 21 rows each), so a relocation must rewrite every copy.
  `mssb_files.py replace` does that.
* **Coverage:** ZZZZ.dat is **56.61%** referenced, plus 0.28% sector padding. The other **43.10%
  (194 MB in 7 gaps) is referenced by no descriptor** anywhere: not in the DOL, not in any REL,
  not inside any decoded file (all three were scanned). aaaa.dat is **99.57%** referenced, plus a
  0x800-byte header and 0.30% padding.
* Every listed file decompresses to its declared size (`MSSB_SLOW=1 test_mssb_files.py`).
  1,492 files are LZSS 11/4 (`flags 0x40B`), 1 is LZSS 14/5 (`0x50E`, the boot model) and 78 are
  stored.
* Main finds: the **five text banks** (all game dialogue, character bios and tutorials:
  a lossless `text-export`/`text-import` exists), an **82 MB opening HVQM4 movie** at
  ZZZZ+0x12000, the **MusyX sound-group table** (48 groups, 1,861 samples), the per-stadium
  **field-object sets**, the **Challenge board and map** files, and nine identical copies of the
  16-slot **menu resource set**.

## 2. Containers, descriptors, loaders

```
DiskFileDesc (16 bytes, big endian)
  u32 flags     0 = stored; else (repeatBits << 8) | lookbackBits of the Namco LZSS stream
  u32 sizeWord  bit 30 = compressed; low 28 bits = unpacked size
  u32 offset    byte offset in the container (sector-aligned, 0x800, in ZZZZ/aaaa;
                0x20-aligned inside the ARAM blob)
  u32 packed    bytes read from disc (LZSS stream length; stored files round up to 4)
```

* **Read path.** `PrepFilesToBeLoaded` resolves `ZZZZ.dat` / `aaaa.dat` to entry numbers
  (`lbl_803CBBD4` / `lbl_803CBBD0`). The boot state machine `fn_800097A0` switches the "current
  file" (`lbl_803C6CF8+0x718`) to aaaa.dat for the RELs and to ZZZZ.dat for everything else. Every
  read is `ARAMTransfer(desc, dst, ...)`, `fn_80035838(desc, slot)` (UI resource into a logical
  slot) or a queue wrapper around them, followed by `DVDFastOpen` + `DVDReadAsyncPrio` in 0x8000
  chunks into a staging buffer, and `DecompressDiskData` (LZSS) when bit 30 is set. Movies stream
  through the sNp HVQM4 player (`fn_800A6E24` / `fn_800A6D10`). Nothing else opens ZZZZ.dat.
* **LZSS:** 32-bit big-endian words read LSB first. Flag bit 1 = 8-bit literal; 0 = (lookback-1,
  `lb` bits), (length-2, `rp` bits). `lzss_compress_optimal` in `tools/modding` produces streams
  the game accepts, and they are smaller than retail.
* **ARAM blob.** `master[515]` (DOL `0x800F1D68`) = `{0, 0x4D6600, ZZZZ+0x1A15E800, 0x4D6600}` is
  streamed to ARAM at boot by `fn_800227E4`. The allocation size is hard-coded at
  `0x800227EC/F4`. `master[0..514]` (DOL `0x800EFD38`) are blob-relative. Growing a member means
  moving the blob and patching both. The tool does this.
* **Sectioned files.** Almost every packed file starts with a u32 offset table whose first word is
  the header length (`.gpc` models: 8 words `{texture, layout, geo, skin, extra}`; stadiums: 16
  words; UI resources: `{0x20 texture archive, sprite bank}`; field sets: 24..88 words). The
  loaders add the load address to each word (`fn_80017814` for characters, `fn_3_5EC0` for
  stadiums, the menu bank relocation for UI files).

## 3. Coverage map

`py mssb_files.py coverage <disc> --probe` prints this.

| Region | Bytes | % of ZZZZ.dat | What |
|---|---:|---:|---|
| referenced by descriptors | 254,779,396 | 56.61 | 1,223 files + the ARAM blob |
| sector padding after files | 1,277,948 | 0.28 | retail fills it with stale bytes, not zeros |
| unreferenced gaps | 193,984,512 | 43.10 | 7 gaps, see below |

| Gap (ZZZZ offsets) | Size | Best guess |
|---|---:|---|
| `0x00000000..0x00012000` | 72 KB | three stored CMPR texture archives (8/8/9 textures, 16..128 px) at 0x0, 0x6000, 0xC000: unused leftovers |
| `0x08F2E800..0x09438800` | 5.0 MB | starts with an `'AdGCForm'` header (`d0735000 0b040000 "AdGCForm"`): an unknown container, not loaded |
| `0x0CE16800..0x0E581000` | 23.4 MB | LZSS-looking data, no magic: stale build data |
| `0x0EAE4000..0x0EAF7000` | 76 KB | LZSS-looking data, sits between the Challenge map UI and the per-character menu models |
| `0x0F12C800..0x186A1800` | 149.8 MB | dense, structured (zlib ratio 0.84..0.94), no sector-aligned headers, no magic: stale build data (most likely old character/animation files) |
| `0x18AC5000..0x18AC7000` | 8 KB | tail after the Challenge "partial read" file |
| `0x19A6F800..0x1A15E800` | 6.9 MB | five `'AdGCForm'` containers (0x19F49000, 0x1A025800, 0x1A03B000, 0x1A0E8800, 0x1A15D800): unknown, not loaded |

Evidence that the gaps are dead: no 16-byte record anywhere in the DOL or RELs (any flags, any
size) names an offset inside them. No `lis/addi` immediate builds their start or sector number.
No decoded file contains a descriptor into them. The slack after *every* referenced file is also
non-zero, so the disc builder reused an old ZZZZ.dat in place. **For modding, the gaps are free
space:** `replace --reuse-gaps` puts grown files there, so an ISO keeps the retail size of
1,459,978,240 B (the retail disc is full: ZZZZ.dat ends 26 KB before the end of the image).

aaaa.dat: `0x0..0x800` is an unreferenced header of 0x40-ish `u16 value, u16 0` pairs (build
checksums?). Then menus.rel at 0x800 (0x5A818 packed), game.rel at 0x5B800 (0xF4450 packed, 0x3B0
bytes of slack before challenge.rel) and challenge.rel at 0x150000 (0x271C0 packed). The FST
also has loose `menus.rel`/`game.rel`/`challenge.rel` in dtk's extraction. The game never reads
them.

The ARAM blob: 345 member files use 99.91% of its 0x4D6600 bytes.

## 4. Descriptor tables

Ids are what `mssb_files.py` uses: a file's id is `<table>.<index>` of the first row naming it,
and every other row is an alias. Index meanings marked "guess" or "not traced" are inferred from the
content, not from a caller. "rows / own files" = descriptor rows in the table / files whose
id comes from this table (0 = every row is a copy of a file owned elsewhere). Loader names are from
`config/GYQE01/*symbols.txt` (`tools/datamap/dev_tables.py` regenerates the raw list).

| id | location | rows / own files | in | what | index | loader |
|---|---|---|---|---|---|---|
| `rel` | DOL `0x800E8AA8` | 3 / 3 | aaaa | REL modules (LZSS in aaaa.dat) (rel 3) | 0 menus.rel, 1 game.rel, 2 challenge.rel | fn_800097A0 (boot state machine) -> ARAMTransfer |
| `boot` | DOL `0x800E8AD8` | 3 / 3 | ZZZZ | boot files (model 1, unknown 1, texarc 1) | 0 .gpc model with one 1024x132 CI4 texture (LZSS 14/5), 1 stored binary, 2 small CI4 texture archive | fn_800097A0 (boot state machine) |
| `res` | DOL `0x800E8B08` | 62 / 62 | ZZZZ | common UI resources (resource id 0..61) (ui 45, texarc 17) | resource id: 1 HUD portraits (charID->30+c), 5 lineup portraits, 15 menu common (names/mini images), 29 select-grid portraits, 30 title/main menu, 38..44 stadium art (38 + stadium); guesses: 0 HUD, 6..13 full-screen screens, 16..28 captain banners/emblems, 45..61 stills | fn_800097A0 / fn_80035838(desc, slot); the same 62 rows are copied into game.rel/challenge.rel |
| `res_dol2` | DOL `0x800EEFD0` | 62 / 0 | ZZZZ | common UI resources (copy 2) (ui 45, texarc 17) | resource id (same as res) | fn_80020388: res_dol2[lbl_803CB7CC[stadium] + 0x26] into slot 0xD (stadium art); fn_80020278(n): res_dol2[n + 0x2D] (stills 45..61) by ARAMTransfer into a heap buffer |
| `game_common` | DOL `0x800EE910` | 5 / 5 | ZZZZ | field/game common set (unknown 2, sectioned 2, text 1) | 0..1 0x140-header data, 2..3 actor sets (guess), 4 text bank (23 minigame strings) | fn_800188C0 |
| `sound` | DOL `0x800EF508` | 48 / 48 | ZZZZ | MusyX sound groups (stored) (musyx 48) | sound group slot (each file = proj+pool+sdir+samp; group id at +0x24) | fn_800215F8 / fn_80021758 |
| `stadium` | DOL `0x800EFBE8` | 21 / 13 | ZZZZ | stadium models (stadium 21) | stadium*3 + variant (g_d_GameSettings.unk9 / unkA): Mario Stadium, Bowser Castle, Wario Palace, Yoshi Park, Peach Garden, DK Jungle, Toy Field | game.rel manageStadiumLoading -> ARAMTransfer; relocated by fn_3_5EC0 |
| `master` | DOL `0x800EFD38` | 515 / 345 | blob | ARAM master descriptors (blob-relative) (sectioned 215, script 192, anim 54, model 33, texarc 21) | 0..32 bodies, 33..53 texture overlays (via lbl_800F73B8[charID]), 54+charID*7+k attachments (k 0..3 models, 4..6 event scripts), 432+charID track-15 ANIM bank, 486+id per-model event scripts (id = lbl_800EEB18[charID]) | fn_800227E4 streams the blob to ARAM; fn_8002204C / fn_8002254C / fn_80021BBC / fn_8002244C / fn_80021ADC read members |
| `blob` | DOL `0x800F1D68` | 1 / 1 | ZZZZ | ARAM blob (master[515]) (blob 1) | - | fn_800227E4 (ARAM alloc size hard-coded at 0x800227EC/F4) |
| `subfile` | DOL `0x800F1D78` | 1026 / 652 | ZZZZ | per-character disc subfiles (anim 918, model 108) | charID*19 + track (0/1 body hi/lo, 2..18 ANIM banks; 15 = the 12-sequence bank also in master 432+charID) | fn_8001758C / fn_80016344 / fn_80016710 / fn_80016B60 / fn_80021BBC |
| `subitem` | DOL `0x800F5D98` | 324 / 198 | ZZZZ | per-character sub-item models (bat/glove) (sectioned 324) | charID*6 + itemSlot | fn_80021CA4 / fn_8002244C (disc path) |
| `model_script` | DOL `0x800F71D8` | 30 / 30 | ZZZZ | per-model event scripts (disc fallback of master 486+id) (script 29, unknown 1) | model id from lbl_800EEB18[charID] (colour variants share their base's id) | fn_80021ADC |
| `menu_title` | DOL `0x800FB5B0` | 1 / 0 | ZZZZ | title/main menu UI (copy) (ui 1) | - | fn_8004A1BC |
| `text_sys` | DOL `0x80109044` | 1 / 1 | ZZZZ | system text bank (11 strings, to ARAM) (text 1) | - | fn_800697B0 |
| `opening` | DOL `0x801092C8` | 3 / 2 | ZZZZ | opening movie set (ui 1, hvqm 1, unknown 1) | 0 opening HVQM4 movie (82 MB, stored), 1 0x20-rooted data, 2 UI resource (= res.34) | fn_8006AF9C |
| `stats` | menus `.data+0xC8` | 1 / 1 | ZZZZ | CharacterStats block (54 x 0xA0 + tail) (stats 1) | - | fn_2_554 (menus boot); game.rel maybeProcessTeamData reads the same file |
| `menu_set` | menus `.data+0x444` | 16 / 0 | ZZZZ | menu scene resource set (16 logical slots) (ui 16) | logical UI slot: 0 title/main menu (res.30), 1 grid portraits (res.29), 2 res.33, 3 res.16, 4..15 res.17..28 | fn_2_27E0 (and 8 identical copies, see aliases) |
| `menu_set_b` | menus `.data+0xD14` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | fn_2_6D3C |
| `menu_set_c` | menus `.data+0x1314` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | fn_2_11340 |
| `menu_set_d` | menus `.data+0x18B4` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | inside lbl_2_data_15C8 (no direct code reference) |
| `menu_set_e` | menus `.data+0x1CD4` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | fn_2_16460 |
| `menu_set_f` | menus `.data+0x2A9B4` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | inside lbl_2_data_2A3C0 (no direct code reference) |
| `menu_set_g` | menus `.data+0x2B3DC` | 16 / 0 | ZZZZ | menu scene resource set (character select) (ui 16) | logical UI slot (1 = grid portraits) | fn_2_73994 / fn_2_760CC / fn_2_7BFF8 (character select) |
| `menu_set_h` | menus `.data+0x2E1EC` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | fn_2_834F0 |
| `menu_set_i` | menus `.data+0x302BC` | 16 / 0 | ZZZZ | menu scene resource set (copy) (ui 16) | logical UI slot | inside lbl_2_data_2FFF8 (no direct code reference) |
| `menu_char_a` | menus `.data+0x241C` | 54 / 54 | ZZZZ | per-character menu 3D scene A (stadium 54) | charID (use: guess, select/intro poses) | fn_2_17C88 / fn_2_17ED8 / fn_2_18148 / fn_2_188EC |
| `menu_model42` | menus `.data+0x4B90` | 1 / 1 | ZZZZ | shared .gpc model (42 textures) (model 1) | - | fn_2_1B1BC |
| `movie` | menus `.data+0x12170` | 2 / 2 | ZZZZ | HVQM4 movies (stored) (hvqm 2) | 0 short movie, 1 attract/intro | fn_2_37630 -> sNp movie streamer (fn_800A6E24) |
| `text_menu` | menus `.data+0x12298` | 1 / 1 | ZZZZ | menu text bank (954 strings) (text 1) | - | fn_2_409CC |
| `menu_char_b` | menus `.data+0x12EC0` | 54 / 0 | ZZZZ | per-character menu 3D scene B (same files as A) (stadium 54) | charID | fn_2_47540 / fn_2_477C0 / fn_2_478F4 / fn_2_481F4 |
| `challenge_ui` | menus `.data+0x1323C` | 11 / 9 | ZZZZ | Challenge-mode UI resources (ui 11) | 3 Challenge scene (lbl_2_data_1326C), 10 Challenge Special ending / staff roll (lbl_2_data_132DC) | fn_2_4EB64 / fn_2_4E970 / fn_2_4EABC -> fn_80035838 |
| `menu_1f884` | menus `.data+0x1F884` | 2 / 0 | ZZZZ | menu UI pair (ui 2) | - | fn_2_53408 |
| `menu_1ff84` | menus `.data+0x1FF84` | 3 / 2 | ZZZZ | options/records set (ui 1, text 1, stadium 1) | 0 UI, 1 text bank (599 strings), 2 scene | fn_2_549B4 |
| `menu_20bf0` | menus `.data+0x20BF0` | 2 / 0 | ZZZZ | lineup screen set (ui 1, text 1) | 0 lineup portraits UI, 1 text bank | fn_2_5ED3C |
| `menu_scene_2e9a4` | menus `.data+0x2E9A4` | 1 / 1 | ZZZZ | menu 3D scene (stadium 1) | - | fn_2_8563C / fn_2_85D6C |
| `menu_2f944` | menus `.data+0x2F944` | 2 / 0 | ZZZZ | menu UI pair (ui 2) | - | fn_2_8ABFC |
| `menu_scene_2f990` | menus `.data+0x2F990` | 67 / 52 | ZZZZ | menu 3D scene models (67) (stadium 67) | scene id | fn_2_8DB14 / fn_2_8DC00 / fn_2_8DCD8 / fn_2_8E8A4 / fn_2_8EA80 |
| `menu_2fe48` | menus `.data+0x2FE48` | 2 / 1 | ZZZZ | menu 3D scene pair (stadium 1, sectioned 1) | - | fn_2_8E478 |
| `stats_game` | game `.data+0x0` | 1 / 0 | ZZZZ | CharacterStats block (copy) (stats 1) | - | maybeProcessTeamData |
| `stadium_game` | game `.data+0x7EC` | 21 / 0 | ZZZZ | stadium models (copy) (stadium 21) | stadium*3 + variant | fn_3_64DC |
| `game_set` | game `.data+0x3D60` | 69 / 4 | ZZZZ | game resource set (ui 45, texarc 17, sectioned 4, text 2, unknown 1) | 0..1 field files, 2..63 = res 0..61, 64..68 field effect/text files | fn_3_59F40 / fn_3_5A28C |
| `game_res_a` | game `.data+0x6130` | 62 / 0 | ZZZZ | common UI resources (copy) (ui 45, texarc 17) | resource id | fn_3_5BD40 |
| `game_res_b` | game `.data+0xF538` | 62 / 0 | ZZZZ | common UI resources (copy) (ui 45, texarc 17) | resource id | fn_3_AF10C |
| `game_res_c` | game `.data+0x10578` | 64 / 0 | ZZZZ | results/replay resource set (ui 45, texarc 17, text 1, sectioned 1) | 0 text bank (168 strings), 1 actor set, 2..63 = res 0..61 | fn_3_B43E8 |
| `field` | game `.data+0x10ACC` | 7 / 7 | ZZZZ | per-stadium field object sets (sectioned 7) | stadium (0..6) | fn_3_B9BB4 (g_hugeAnimStruct.stadiumObjectLoadingPtr) |
| `game_model42` | game `.data+0x11380` | 1 / 0 | ZZZZ | shared .gpc model (copy) (model 1) | - | fn_3_BF878 |
| `game_115ec` | game `.data+0x115EC` | 1 / 1 | ZZZZ | 44-section data file (sectioned 1) | - | fn_3_BEFF8 |
| `camera` | game `.data+0x20FDC` | 1 / 1 | ZZZZ | camera data (unknown 1) | - | fn_3_106E50 (g_Camera.unk1B4) |
| `minigame_res` | game `.data+0x21EC8` | 62 / 0 | ZZZZ | common UI resources (minigame copy) (ui 45, texarc 17) | resource id (minigame index + 6 picks a screen) | fn_3_10B8D0 / fn_3_10F3D8 / fn_3_10FDC8 |
| `game_225f0` | game `.data+0x225F0` | 3 / 0 | ZZZZ | field effect/actor set (copy) (sectioned 2, text 1) | 0..1 actor sets, 2 text | fn_3_116840 ... (g_hugeAnimStruct.ActorPointer) |
| `game_284e8` | game `.data+0x284E8` | 2 / 0 | ZZZZ | results text + actor set (text 1, sectioned 1) | 0 text bank (168), 1 actor set | fn_3_1665E4 |
| `field_ch` | challenge `.data+0x0` | 7 / 0 | ZZZZ | per-stadium field object sets (copy) (sectioned 7) | stadium | fn_1_1538 |
| `stadium_ch` | challenge `.data+0x8D0` | 21 / 0 | ZZZZ | stadium models (copy) (stadium 21) | stadium*3 + variant | fn_1_73B8 |
| `menu_title_ch` | challenge `.data+0xB70` | 1 / 0 | ZZZZ | title/main menu UI (copy) (ui 1) | - | fn_1_88D0 |
| `challenge_map_ui` | challenge `.data+0xF0C` | 11 / 11 | ZZZZ | Challenge map UI pieces (ui 11) | piece id | fn_1_8CD4 / fn_1_8DBC / fn_1_8F34 |
| `sound_ch` | challenge `.data+0x196C` | 50 / 0 | ZZZZ | MusyX sound groups (Challenge copy) (musyx 50) | sound group slot | fn_1_9F04 |
| `challenge_board` | challenge `.data+0xA3D8` | 86 / 34 | ZZZZ | Challenge board data (sectioned 44, script 29, stadium 10, unknown 3) | 0..1 = game_common.0/1, 2..31 = model_script.0..29, 32..85 board pieces (use not traced) | fn_1_16978 |
| `challenge_a950` | challenge `.data+0xA950` | 1 / 0 | ZZZZ | menu 3D scene (copy) (stadium 1) | - | fn_1_10560 |
| `challenge_model42` | challenge `.data+0xADE0` | 1 / 0 | ZZZZ | shared .gpc model (copy) (model 1) | - | fn_1_10560 |
| `challenge_models` | challenge `.data+0xF968` | 24 / 24 | ZZZZ | Challenge map models (sectioned 16, model 8) | model id | fn_1_1CBE4 |
| `debug_browser` | challenge `.data+0xFB98` | 63 / 0 | ZZZZ | sprite/resource debug browser list (ui 46, texarc 17) | browser ordinal (0 = ending archive, 1.. = res) | fn_1_26AF8 / fn_1_26928 / fn_1_267F4 |
| `challenge_104f4` | challenge `.data+0x104F4` | 1 / 1 | ZZZZ | small data file (sectioned 1) | - | fn_1_20F8C |
| `stadium_ch2` | challenge `.data+0x10518` | 21 / 0 | ZZZZ | stadium models (copy) (stadium 21) | stadium*3 + variant | fn_1_2004C |
| `stadium_ch3` | challenge `.data+0x10674` | 21 / 0 | ZZZZ | stadium models (copy) (stadium 21) | stadium*3 + variant | fn_1_1DCE4 |
| `challenge_model42b` | challenge `.data+0x108F8` | 1 / 0 | ZZZZ | shared .gpc model (copy) (model 1) | - | fn_1_27BB8 |
| `movie_viewer` | challenge `.data+0x112D8` | 1 / 0 | ZZZZ | debug movie viewer (TEST MOVIE 0) (hvqm 1) | movie id | challenge rep_7BA0 (0x28398) -> fn_800ADB04 |
| `partial_ch` | challenge `.data+0xA940` | 1 / 1 | ZZZZ | header read (0x200 bytes of a 0x15450-byte file) (unknown 1) | - | fn_1_10560 |

The challenge `.data+0xAC` table (15 rows `{0, size, cumulativeOffset, size}`, loader `fn_1_1E0`)
describes the 15 `snd/*.adp` streams as if they were concatenated, in the order of the path
strings at DOL `0x800E33A0`. It doesn't point into ZZZZ.dat, so it's not a file table. It's the
**music track index** (`FST_MUSIC_TABLE` in catalog.py).

### Notable index meanings (verified in code)

* **Stadiums** (`stadium`, 21 rows): `manageStadiumLoading` (game.rel) reads
  `lbl_800EFBE8[g_d_GameSettings.unk9 * 3 + unkA]`. The stadium order is `EnumStadiumIDs4`: Mario
  Stadium, Bowser Castle, Wario Palace, Yoshi Park, Peach Garden, DK Jungle, Toy Field.
  `in_game.h` `enumDiskLocations.MarioStadium = 0x6CFD000` confirms row 0. Variants 0..2 are
  probably time of day: Mario Stadium and Peach Garden have three distinct files, Yoshi Park and
  DK Jungle two, the rest one aliased three times. 13 distinct files.
* **Per-stadium field objects** (`field`, 7 rows): `fn_3_B9BB4` stores
  `ARAMTransfer(&lbl_3_data_10ACC[stadium])` in `g_hugeAnimStruct.stadiumObjectLoadingPtr`.
* **Characters**: `subfile` = `charID*19 + track`. Track 0/1 = hi/lo `.gpc` body. Tracks 2..14 and
  16..18 = ANIM banks (Mario: 30, 16, 45, 12, 2, 12, 3, 30, 30, 16, 16, 45, 16, 12, 12, 12, 12
  sequences). Track 15 = a 12-sequence ANIM bank (`fn_80021BBC`; there is no separate skeleton
  file, the bones are in the body's actor layout). `master` tiers: 0..32 bodies, 33..53 texture
  overlays (`lbl_800F73B8[charID] = {body, overlay}`), 54+charID*7+k attachments (k 0..3 =
  hand/glove/bat models with a 1-sequence ANIM bank at +0x20, k 4..6 = keyed event scripts),
  432+charID = the track-15 bank, 486+id = 29 keyed event scripts. The model-id map
  `lbl_800EEB18[charID]` picks id, and colour variants share their base's id (values:
  `character_modding_report.md` §3). `model_script` (DOL `0x800F71D8`, 30 rows) is its disc fallback
  (`fn_80021ADC`).
* **Common UI resources** (`res`, 62 rows = boot table rows 6..67): one resource id, up to nine
  copies. Boot (`fn_800097A0`) loads res 37 into UI slot 0 and res 15 into slot 1. In game.rel, `fn_3_5BD40` loads `lbl_3_data_6130[1]` into slot 0xC (HUD portraits),
  `fn_3_AF10C` loads `[2]` into slot 0x13 and the minigame loader loads `[minigame + 6]`.
  `fn_80020388` loads `res_dol2[lbl_803CB7CC[stadium] + 0x26]` into slot 0xD. `lbl_803CB7CC` is
  `{0..6}`, so res 38..44 is one illustration per stadium.

| res | ZZZZ offset | Contents | Known use |
|---:|---|---|---|
| 0 | 0x1A635000 | UI, 369 textures, 284 sequences | in-game HUD |
| 1 | 0x1A6B3000 | UI, 102 textures | HUD batter/pitcher cards (game.rel `fn_3_5BD40`, slot 0xC), charID c -> texture 30+c (`clone_character.py --ui`) |
| 2 | 0x1A6D4800 | UI, 55 textures | game.rel slot 0x13 |
| 3 | 0x1A6E8000 | UI, 504 textures, 389 sequences | large in-game UI set |
| 4 | 0x1A748800 | UI, 88 textures | |
| 5 | 0x18ED7000 | UI, 180 textures | lineup/results portraits, uniqueIdx u -> 53+u |
| 6..13 | 0x1A769800.. | UI, 21..30 textures each, 640x448 | eight full-screen screens |
| 14 | 0x1A9E3800 | UI, 69 textures | |
| 15 | 0x1A9FE800 | UI, 440 textures, 313 sequences | menu common file, boot-loaded into UI slot 1: roster names c<29?c:c+28, mini images 153+c (`character_select.md` §8) |
| 16 | 0x0E97A800 | UI, 144 textures (153x54) | captain banners |
| 17..28 | 0x0EA16800.. | UI, 12 textures each | twelve captain/team emblem sets (one per captain) |
| 29 | 0x18AEE800 | UI, 202 textures | select-grid portraits, charID c -> 4+c |
| 30 | 0x18B3A800 | UI, 122 textures, 3.6 MB | title / main menu (also `menu_title`, `menu_title_ch`, menu_set slot 0) |
| 31 | 0x18ED3800 | UI, 31 textures | records/options UI |
| 32 | 0x18F0E000 | UI, 74 textures | |
| 33 | 0x191B8800 | UI, 25 textures | menu_set slot 2 |
| 34..36 | 0x06C96000, 0x06CC3000, 0x18D43800 | UI, 640x448 screens | opening/attract stills |
| 37 | 0x1AA67800 | UI, 19 strips 640x48 | boot-loaded into UI slot 0 (`fn_800097A0`) |
| 38..44 | 0x1AA74800.. | UI, 1..2 textures | one illustration per stadium (38 + stadium id, `fn_80020388`, slot 0xD) |
| 45..61 | 0x1AA81000.. | stored texture archive, one 640x256 CI8 | 17 stills (stadium previews / loading pictures; `fn_80020278`) |

## 5. File families and formats

| Format id | Files | Structure | Parser |
|---|---:|---|---|
| `anim` | 576 | charPipeline `ANIMBank` (`include/C3/anim.h`): version `0x007B7960`, sequences (0xC each), tracks, keyframes; pointers are file offsets | `formats.describe` lists sequences; `animations.py` lists tracks/keys (R5: `animations.md`) |
| `sectioned` | 389 | u32 offset header; includes attachment models with an embedded ANIM bank, field-object sets (24..88 sections), Challenge board pieces | section list |
| `model` | 151 | `.gpc`: root `{texture 0x20, layout, geo, skin, extra}`; TextureArchiveHeader at 0x20 (CMPR for characters) | texture list, bones, skinFileID |
| `stadium` | 124 | 16-word root (`fn_3_5EC0`: word0 actor layout, word2 relocation list, word3 geometry, word5 texture archive); also the menu 3D scenes and per-character menu models | section list + texture archive |
| `ui` | 65 | `MenuUiFileHeader {texture archive @0x20, sprite bank}`; sprite bank -> sequence table -> frame lists (`include/menus/menu_ui.h`, `tools/modding/inspect_menu_ui.py`) | texture list, sequence count |
| `texarc` | 39 | bare `TextureArchiveHeader {u16 count, u16 0, 0x20-byte headers}`; texture overlays (master 33..53), stills | texture list |
| `script` | 158 | `{u32 count, u32 0x28, ...}` 0x28-byte header + count offsets to keyed records (`0x0064 0005 ...`) | entry count |
| `musyx` | 48 | stored: `{0x20, size}` x4 chunk table: proj, pool, sdir (0x20-byte entries), samp (DSP-ADPCM); u16 group id at +0x24 | chunk sizes, sample count |
| `text` | 5 | `{u16 count, u16 0x0131, u32 offsets[count]}` + strings of u16 glyph codes ending in 0x4000. Glyphs: A-Z 0x20.., a-z 0x3E.., 0-9 0x0F.., `! " ' ( ) , - . ?` = 00 01 06 07 08 0B 0C 0D 1E. Control: 0x4001 newline, 0x4002 space, 0x40xx colour/box/voice. `>= 0x8000` = icons | lossless `text-export` / `text-import` |
| `hvqm` | 3 | Hudson HVQM4 1.3 movies, stored (3.3 MB, 24 MB, 82 MB) | header |
| `rel` | 3 | REL modules (LZSS in aaaa.dat) | section table |
| `stats` | 1 | `CharacterStats[54]` (0xA0 each), 0x21C0 zero bytes, 12 captain-team blocks: `stats.md` §1, §5 | `stats-export` / `stats-import` |
| unknown | 8 | `camera.0` (0x73538, `{0x4F0, 0x5F0, ...}` header), `game_common.0/1` (0x140-word header), `opening.1`, `game_set.1`, `boot.1` (stored 0xB5D6), `partial_ch.0` (0x20-byte float records, only 0x200 B read) | head bytes |

MusyX groups: 48 sound-group slots (`sound`, DOL `0x800EF508`, loaders `fn_800215F8` /
`fn_80021758`; Challenge has its own 50-row copy). Rows 5..22 are 18-sample groups with ids
27..10, probably per-character voice sets (not traced). Large groups: row 1 (gid 28, 386 samples, 4.1 MB), row 3
(gid 28, 249 samples), row 37 (gid 32, 3.2 MB) and row 46 (gid 51, 121 samples). Music isn't
MusyX. It's the 15 DVD-streamed `snd/my_snd_h/*.adp` files in the FST.

## 6. What each family enables for modding

| Goal | Files | How |
|---|---|---|
| **Dialogue, bios, tutorials, minigame text** | `text_menu.0`, `menu_1ff84.1`, `game_284e8.0`, `game_common.4`, `text_sys.0` | `text-export`, edit, `text-import`, `replace`. Lengths are free (stored files; growing ones are appended). Fan translations are now a text-editing job. |
| **Stats / chemistry** | `stats.0` (ZZZZ+0x6CF8800, stored) | `stats-export`, edit the JSON, `stats-import` (`stats.md`) |
| **Character models / recolours** | `subfile.(c*19+0/1)`, `master.0..53` | `extract`, edit `.gpc` textures, `replace`. Overlays keep their size. `clone_character.py` builds on the same tables. |
| **Animations** | 17 ANIM banks per character (`subfile.c*19+2..18`), `master.432+c` | swapping banks between characters is a descriptor copy. Banks can be re-imported with `replace`. |
| **Menus, HUD, portraits, logos** | 65 UI files (`res.*`, `challenge_ui.*`, `menu_*`) | texture archives inside UI files: same-size edits in place, bigger files appended. Every copy is updated automatically (up to 21 rows). |
| **Stadiums** | `stadium.0..20` (13 distinct), `field.0..6` | replace the stadium model or field-object set per stadium / variant |
| **Voices / SFX** | `sound.0..47` (stored MusyX groups) | replace a group with a re-built proj/pool/sdir/samp of the same layout |
| **Music** | `snd/my_snd_h/*.adp` (FST) | replace the .adp in an extracted folder. The challenge music table and `lbl_800E33A0` paths name them. |
| **Movies** | `movie.0/1`, `opening.0` | replace with another HVQM4 1.3 stream |
| **Free space** | 194 MB of unreferenced ZZZZ.dat | `replace --reuse-gaps` keeps the ISO at retail size |

## 7. What's still unknown

1. **The 194 MB of gaps.** Most likely stale build data. The `'AdGCForm'` containers (6 of them)
   are an unidentified format, and none is loaded.
2. **Index meanings without a traced caller:** `menu_scene_2f990` (67 menu 3D scenes:
   `fn_2_8DB14` selects by `lbl_2_bss_1A824C->unk7746 - 0x19`), `menu_char_a/b` (per-charID 3D
   models used by `fn_2_17C88..` / `fn_2_47540..`: probably the select-screen and team-intro
   poses), `challenge_models` (24) and `challenge_board` rows 32..85, `game_common` /
   `game_225f0` actor sets, and the exact ANIM sequence each subfile track holds (sequence names
   are absent: the name pointers are 0).
3. **Formats without a parser:** the keyed event `script` records, `camera.0`, the 0x140-word
   `game_common.0/1` field files, the stadium sections beyond layout/geo/texture, and `boot.1`.
   (The stats tail is now in `stats.md` §5.)
4. aaaa.dat `0x0..0x800` header (u16 values with u16 zero padding): never read by the game.
5. Glyph codes 0x02..0x05, 0x09, 0x0A, 0x0E, 0x19..0x1D, 0x1F and `>= 0x8000` (button icons)
   aren't named. The text tools keep them as `{XXXX}`.

## 8. Reproduce

```
export PATH=$PWD/.venv/bin:$PATH
python3 tools/datamap/mssb_files.py tables
python3 tools/datamap/mssb_files.py coverage orig/GYQE01 --probe
python3 tools/datamap/mssb_files.py list orig/GYQE01 --csv files.csv
python3 tools/datamap/test_mssb_files.py                       # 21 tests (2 need MSSB_SLOW=1), ~20 s
MSSB_SLOW=1 python3 tools/datamap/test_mssb_files.py RealDisc  # + full decompress, real replace (~2.5 min)
python3 tools/datamap/dev_tables.py orig/GYQE01                # raw table runs + referencing functions
```
