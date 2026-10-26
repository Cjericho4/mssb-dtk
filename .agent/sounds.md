# Voices, announcer, sound effects and music (R4)

*GYQE01. Compiled 2026-10-24 (R4); §6-§7 updated 2026-10-25 with the #29 clone-voice work. Owns:
the MusyX sound groups (`sound.N`), voice banks and voice lines, announcer calls, the sample
format, both music systems, voice swaps, clone voices and the ARAM budget.
Tools: `tools/datamap/mssb_files.py sound-list / sound-export / sound-import / voice-swap /
music-export` (`tools/datamap/README.md`); code in `tools/datamap/sound.py`. Confidence: **high** =
read in code or asm and checked on all retail data by `test_mssb_files.py`; **medium** = one call
site or a name-based guess backed by data; **low** = guess.*

## 1. TL;DR

* **Every sound effect, voice and announcer line is a MusyX SFX** inside one of 48 stored
  sound-group files (`sound.0..47`, DOL table `lbl_800EF508`, also copied in challenge.rel
  `sound_ch`). Each file = `{offset, size}` x4 header + proj, sdir, pool, samp chunks. 842 samples,
  all DSP-ADPCM (compType 0). (high)
* **Voices:** character voice bank = `sound.(5 + u)`, u = unique index (0..31,
  `lbl_800E8558[charID].uniqueIdx`, colour variants share it). Group id `lbl_3_data_8148[u]`,
  SFX ids `characterSoundArray[charID] + line` (game.rel `lbl_3_data_8168`, 54 u16), 13 lines per
  character, 7..10 samples per bank. All 54 charIDs agree (test). At match start every one of the
  18 roster players' banks is loaded (`fn_3_5A28C` loop over `lbl_800EF808.unk39A`). (high)
* **Announcer:** name call = `lbl_80108DF4[u]` (33 u16, SFX 0x1C4..0x1E5, entry 32 = Birdo alt) in
  `sound.37` (group 32, 22050 Hz, one sample per name). `sound.37` also holds the 76.6 s stereo
  menu music (SFX 0x1E4). (high)
* **Music:** two systems. (a) 15 DVD-streamed `snd/my_snd_h/*.adp` files (stadium themes,
  replay, results, Challenge), Nintendo stream ADPCM, stereo 48 kHz, played by path only, so a
  replacement can have any length: data-only. (b) MusyX sequenced songs: 19 in-match songs in
  `sound.1` group 29 with arrangements in `game_set.0`, menu songs in `sound.2`. (high / medium)
* **Mods that are now data-only, with tools:** replace any sample (`sound-export` -> edit WAV ->
  `sound-import`), give a voice bank another character's voice (`voice-swap`), export music
  (`music-export`). A voice per charID (not per unique index) needs a game.rel table edit too (§6).

## 2. Sound-group files (`sound.N`)

```
file (stored, no LZSS)          from fn_80021650 / fn_80021758 -> fn_80021518
  0x00 {u32 off, u32 size} x4   relocated to pointers; chunk order proj, sdir, pool, samp
  proj  GROUP_DATA list         {nextOff (from proj start), u16 id, u16 type (1 SFX, 0 songs),
                                 macroOff, sampleOff, curveOff, keymapOff, layerOff, data}
                                 + id lists (u16; 0x8000|first,last = range of 3+) + FX_DATA
                                 {u16 n, u16 0, FX_TAB[n] {id, macro, maxVoices, prio, vol, pan, key, vgroup}}
  sdir  SDIR_DATA[] 0x20 each   {u16 id, u16 refcnt, u32 samp offset, u32 0, info = rootKey<<24 | rate,
                                 length = compType<<24 | samples, loopStart, loopLength, extra}
        0xFFFF end, then        SNDADPCMinfo 0x28 each at sdir+extra {u16 8, u8 initialPS, u8 loopPS,
                                 s16 loopY0, loopY1, s16 coef[8][2]}
  pool  POOL_DATA {macroOff, curveOff, keymapOff, layerOff} + MEM_DATA lists {u32 nextOff
        (relative), u16 id, u16 0, data}; macros = MSTEP {u32, u32}, opcode = w0 & 0x7F,
        0x10 StartSample (sample id = w0 >> 8 & 0xFFFF), 2/3/6/8/0xA/0x13/0x25/0x28 name a macro (w0 >> 16)
  samp  DSP-ADPCM frames, each sample 0x20-aligned in sdir order
```

* `fn_80021518(gid, res)` = `sndPushGroup(proj, gid, samp, sdir, pool)` (src/Musyx/s_data.c);
  push copies each sample to MusyX's ARAM heap (`dataAddSampleReference` -> `hwSaveSample`), then
  `fn_800ACF78(res, samp - res)` shrinks the RAM copy to proj+sdir+pool. MusyX ARAM =
  `sndInit(64 voices, 48, 16, 1 studio, flags 1, 0x800000)` from `lbl_800EFBB4` (8 MB; budget in
  §7). (high)
* Ids are global across groups (`src/Musyx/synthdata.c`): sample lookup (`dataGetSample`) takes the
  first pushed sdir with that id; a duplicate sample id pushed later gets `ref_cnt = 0xFFFF`
  (`dataInsertSDir`) and is neither used nor uploaded again; a duplicate macro id only bumps its
  refCount; `dataGetFX` binary-searches each pushed group's FX table in push order and takes the
  first hit, so **an FX table must be sorted by id**. Groups are popped with `sndPopGroup()` (top of
  stack, no gid; `fn_3_90AB0` etc.), so a later duplicate is always removed before its original.
  Retail pushes duplicates (two Toad colours load `sound.18` twice; `sound.38` reuses captains'
  sample ids, `sound.1`/`sound.3` share ids) with identical data, so it is harmless there. (high)
* The 32 voice banks share no FX, sample, macro, curve, keymap or layer id with each other (max FX
  0x2D5, sample 0x337, macro 0x195), so one bank's sounds can be added to another under their
  retail ids (§6). (high, checked on the disc)
* Every file rebuilds byte-identically from the parse (`Group.with_samples({})`; FX-group projs
  through `build_proj`); `initialPS` = first frame header for all 842 samples. (high, test)
* Samples: rates 16000..48000; voices 32000 (a few 44100/22050), announcer 22050. Loops only in
  SFX/music groups, none in voices. Sample length is in samples; bytes = ceil(n/14)*8. (high)

### Which row is what (`mssb_files.py sound-list <disc>`)

| row | gid | SFX ids | what | loaded by (pushed gid) | conf. |
|---|---|---|---|---|---|
| 0 | 30 | 0x1B7..0x1C3 | boot-resident SFX (13 one-sample SFX, use not traced) | `fn_8002158C` at boot | high (load) |
| 1 | 28, 29 | 0x151..0x1B6 | in-match common SFX + 19 sequenced in-match songs | game `fn_3_5A28C` -> `fn_3_910AC` (0x1C, 0x1D) | high |
| 2 | 31 | - | sequenced menu songs (type 0) | menus `fn_2_554` (row 2), `fn_2_10FC` (0x1F) | medium |
| 3 | 28, 54 | 0x151..0x1B6 | smaller copy of the common SFX + song group 54 (practice song, `practiceSongs`) | game `fn_3_59C2C` -> `fn_3_91064` (0x1C, 0x36) | medium |
| 4 | 0 | 0x0 | menus options/records SFX (2 looping samples) | `fn_800627C4`; menus `fn_2_549B4` | medium |
| 5..36 | `lbl_3_data_8148[u]` | 13 per bank | voice bank of unique index u = row - 5 (§3) | `fn_3_5A28C` / `fn_3_90B14` / `fn_3_90DD8` -> `fn_3_90F48` | high |
| 37 | 32 | 0x1C4..0x1E6 | announcer names, menu music 0x1E4, 0x1E6 (§4) | menus `fn_2_6D3C`, game `fn_3_90928` -> `fn_8006285C` (0x20) | high |
| 38 | 49 | 0x284..0x2C8 | menu set: clips copied from eight voice banks (Mario, Peach, DK, Yoshi, Bowser, Wario, Bowser Jr, Toad; same sample ids) + menu SFX/jingles | menus `fn_2_1B7B4` queues row 0x26; `fn_800627F8` pushes gid 0x31 from `resources[38]` (link between them not traced) | high (each), medium (use) |
| 39..45 | `lbl_3_data_81D4[s]` = 42, 43, 44, 52, 2, 1, 6 | | stadium SFX, row 0x27 + stadium (Mario Stadium, Bowser Castle, Wario Palace, Yoshi Park, Peach Garden, DK Jungle, Toy Field) | `fn_3_90A18` -> `fn_3_90798` | high |
| 46 | 51 | 0x2D6..0x30E | in-match SFX, loaded unless game mode 6 (which loads row 45 instead) | `fn_3_59F40` -> `fn_3_90764` (0x33) | high (load) |
| 47 | 53 | 0x317..0x318 | two SFX | `fn_80069A68` (0x35) | high (load) |

Challenge.rel has its own copies: `sound_ch` (50 rows, same files; row r at challenge `.data` s5 +
0x196C + r*0x10; rows 34..36 appear twice, so find the copies by descriptor match;
`mssb_files.py info sound.N` lists every copy), `lbl_1_data_FC0` (= game's 0x8148 gid table + 0x8168
SFX bases at +0x20), `lbl_1_data_17A4` (32 gids in a different order) and `lbl_1_data_17C4` (first 18
SFX bases). The tables are read only by `fn_1_A8B4` / `fn_1_A908` (load by a raw unique index) and
the `fn_1_B5B8` sound-test-like player (OSReport), not on the match path; a clone needs no change
there except the `sound_ch` descriptor when a bank file moves. (medium)

## 3. Voice banks

| Step | Code | Data | conf. |
|---|---|---|---|
| which file | `fn_3_90F48`: charID (roster slot `unk39A`, or practice / minigame / state 0xE overrides) -> `u = fn_800698F8(charID)` | `lbl_800EF508[5 + u]` | high |
| which group | same: `fn_80021518(lbl_3_data_8148[u], resources[5 + u])` | game .data 0x8148 `u8[32]`: 27..10, 35, 7, 9, 33, 34, 8, 48, 46, 39, 47, 50, 37, 36, 38 (symbols.txt calls it `float`; it is bytes) | high |
| which SFX | `fn_3_90220` (`playCharacterSound(charID, line)`) = `sndFXStartEx(lbl_3_data_8168[charID] + line, vol[line], 63, 0)` + `sndFXCtrl(0x5B, pan[line])`; `fn_3_90150` is the same with volume and pan scaled by the float at game .data 0x8830 | game .data 0x8168 `u16[54]` (Mario 0x144, Luigi 0x137, ...); per-line mix `lbl_3_data_8530` (volume 100 for lines 0..11, 127 for 12; pan 0) | high |
| cutscene timing | `fn_3_23CEC` (line 0) / `fn_3_22C20` (line 7) compare the anim frame with `lbl_3_data_7F7C[u][0]` / `[u][3]` | game .data 0x7F7C `s16[32][4]` per unique index | medium |

Each voice group has exactly 13 SFX = lines 0..12 (`sound-list <disc> 5`); some lines share a
sample (Mario: 0/1, 7/8, 11/12). Line meanings from the 26 `fn_3_90220` call sites (game.rel):

| line | played when | evidence | conf. |
|---|---|---|---|
| 0 | positive: catch made (`fn_3_261E8`, `fn_3_4DC14` success branch), chemistry throw (`fn_3_ABDD0`), home-run end and post-replay celebration (`fn_3_23CEC`, `fn_3_240F8`), a minigame event (`fn_3_13EA30`) | call sites | medium |
| 3 | pitcher result sad | pitcher anim 69 frame 1 (`fn_3_64BDC`) | high (code), medium (anim name) |
| 4 | pitcher result happy | pitcher anim 68 frame 1 | high / medium |
| 5 | regular throw | `fn_3_ABDD0` voice type 5 (`stats.md` §4) | medium |
| 7 | championship / win screen (`fn_3_22C20`), `fn_3_657E4` | call sites | medium |
| 9 | `fn_3_657E4` via `fn_3_90150` (anims 0x70/0x71) | call site | low |
| 10 | negative: batter strikeout anims 93..96 and hit-by-pitch 98 (`fn_3_63AF8`), hazards / knock-downs (`fn_3_253A4`, `fn_3_61B64`, `fn_3_631AC`, `fn_3_60E90`), body check / slide (`fn_3_7F494`), bobbled catch, anti-chemistry throw, minigame hit (`fn_3_136220`) | call sites | medium |
| 11 | fielder set on fire (anim 16, `fn_3_61B64`), wall splat (`fn_3_2F924`) | call sites | medium |
| 1, 2, 6, 8, 12 | no constant call site found in game.rel | searched every `bl fn_3_90220` / `fn_3_90150`; menus/challenge may play them through their own tables | unknown |

Anim names are the Ghidra enum `EnumCharacterAnimation_short` (in_game.h).

## 4. Announcer

* `fn_800628D4(charID)` (MATCH): `u = fn_800698F8` with `useAltBirdoGrid = 1`, plays
  `lbl_80108DF4[u]` at volume `lbl_80108B18[0]` = 110 (`character_select.md` §6 for callers). (high)
* All 33 name calls are one-sample SFX in `sound.37` (22050 Hz, 0.7..2.3 s); the SFX ids are not
  in u order (DK 0x1CA, Daisy 0x1C7, Birdo 0x1CD, Birdo alt 0x1E5 = sample 0x1B7). (high)
* `sound.37` SFX 0x1E4 = layer of two 76.6 s 32 kHz samples (0x33B, 0x33C: left/right),
  started by `fn_80062A94` with a fade: the menu background music (high). 0x1E6 (sample 0x2B,
  44.1 kHz): two `li r3, 0x1E6` sites in `gap_800528AC`, not confirmed as SFX arguments (low).
* Umpire / "strike" / "home run" calls are not in `sound.37`; candidates are the 22050..48000 Hz
  samples of `sound.1`/`sound.46` (not identified). (unknown)
* Changing what the announcer says for a character: replace that name's sample with
  `sound-import sound.37`; changing which call a character gets: `lbl_80108DF4` (DOL data).

## 5. Music

### 5.1 DVD-streamed `.adp` (stadium themes, replay, results, Challenge)

* Track table `lbl_800E87B4` (DOL, 15 rows `{path, size, 0, size}`) -> path strings at
  0x800E63A0. `fn_8006877C(track)` (menus) -> `fn_800A8E30`, and game.rel's sound queue
  `fn_3_8B094` -> `LoadFile` (0x800A8CBC), both: row -> `ConvertPathToEntryNum` -> `DVDFastOpen`,
  later `DVDPrepareStreamAsync(file, 0, 0)` = the whole file as the FST gives it. The size words are not read there, so a replacement of any
  length works. (high for the open path; the size words have no other reference)
* Track 12 (`cha_end_jin`) is started with `fn_800A8AB0(0)`, the others with 2 (likely no-loop vs
  loop). (medium)
* Format: Nintendo DVD stream ADPCM. 32-byte frames: header bytes L, R, L, R (filter << 4 | shift,
  filter 0..3 with fixed pairs (0,0), (60,0), (115,-52), (98,-55) / 64), then 28 bytes of nibbles
  (low = left, high = right): 28 stereo samples per frame. Every frame of all 17 files has a valid
  header and the duplicate bytes agree; files are multiples of 32 KB. Rate 48 kHz
  (`AIInit` -> `__AI_set_stream_sample_rate(1)`, never changed). Decoder: `sound.adp_decode`,
  smooth output with L/R correlation 0.9 on mario_01_h. (high)

| track | file | length | use (by name) |
|---|---|---|---|
| 0..5 | mario_01_h, koopa_h, wario_h, yoshi_h, peach_h, donkey_h | ~5 min each | stadium themes (Mario Stadium, Bowser Castle, Wario Palace, Yoshi Park, Peach Garden, DK Jungle) |
| 6, 7 | replay_h, result_h | 193 s | replay, results |
| 8 | cha_victry_h | 206 s | Challenge victory |
| 9 | toy_h | 307 s | Toy Field |
| 10..13 | cha_map_h, cha_demo_h, cha_end_jin_h, cha_s_roll_h | 185 / 31 / 4 / 234 s | Challenge map, demo, ending jingle, staff roll (menus `fn_2_20D08` 10, `fn_2_379D0` 11, `fn_2_3D878` 12, `fn_2_1B7B4` 13) |
| 14 | home_in_h | 5 s | home-run jingle (guess) |
| - | star_01_h, star_03_h | 15 s | on the disc, no path string in the DOL or any REL: unused |

* Replacing one: decode/encode with any DTK-capable tool, or export with `music-export` to check;
  put the new `.adp` in an extracted disc folder (Dolphin rebuilds the FST). `replace` does not
  write FST files. **No encoder in the tools yet** (pure Python is too slow for 5-minute stereo).

### 5.2 MusyX sequenced songs

* In-match: `SongEntry lbl_3_data_88E0[19]` (game .data 0x8148+0x798) = `{u16 group 29, u16 song
  0..18, u16}`; `fn_3_9056C` / `fn_3_90674` call `sndSeqPlayEx(group, song, arr[song])`, volume
  `lbl_3_data_830C`. (The decomp's `SongEntry` names the first two fields `seqID`, `groupID`; the
  MusyX signature `sndSeqPlayEx(sgid, sid, ...)` says group, then song.) (high)
* `arr` = `lbl_3_bss_1774`, the relocated offset table of the file loaded from `lbl_3_data_3D60[0]`
  = **`game_set.0`** (19 sections) by `fn_3_59F40` / `fn_3_906FC` (20 offsets, 1 in practice:
  `practiceSongs` = group 54 song 21). (high for game_set.0, medium for practice)
* Samples of these songs are the gid 29 part of `sound.1`; macros/keymaps in its pool. Editing the
  sequences themselves is not covered (MusyX song format not parsed).

## 6. Voice swaps and clone voices

| Want | How | Tool / status |
|---|---|---|
| Replace a voice line, a name call, any SFX | re-encode that sample in its group | `sound-export` + `sound-import` (lossy DSP-ADPCM, ~40 dB SNR) |
| Character family X sounds like Y | `sound.(5+u_X)` := `sound.(5+u_Y)` retargeted to X's group id and SFX ids, sample/macro ids moved to 0x400 + u_X*0x20 (no clash with Y's own bank or another swap) | `voice-swap <disc> X Y`; lossless; affects every charID with X's unique index (all colours, and `--ui source` clones of X) |
| One charID (e.g. a clone on Blue Toad's slot) speaks with Y's voice, the rest of X's family unchanged | add Y's 13 FX (and their macros, samples, curves) to X's bank **under Y's retail ids** (voice-bank ids are disjoint, §2) and set `lbl_3_data_8168[charID]` = `8168[Y]` | merged bank below; Rust core on branch `voice-merge` only (#29), no Python tool |

**Which keys pick a voice.** The bank is chosen by unique index (`fn_3_90F48`: `u =
fn_800698F8(charID)`, `sound.(5+u)`), the SFX ids by charID (`lbl_3_data_8168[charID] + line`). A
clone S of source C on donor D's slot gets, from the patcher in main
(`clone_character.py`, Rust core in `tools/clonemaker/core`):

| flags | unique idx of S | `8168[S]` | bank loaded | SFX asked | result |
|---|---|---|---|---|---|
| `--ui source` (default) | u_C (`fn_800698F8` rewritten, `character_select.md` §6) | 8168[C] | source's | source's | source voice |
| `--ui source --no-gameplay` | u_C | donor's | source's | donor's | **silent** unless a u_D character is in the match (from code) |
| `--ui donor` | u_D | 8168[C] | donor's | source's | **silent** unless a u_C character is in the match (confirmed in Rio: Mario on a Toad slot) |
| `--ui donor --no-gameplay` | u_D | donor's | donor's | donor's | donor voice |

`8168` (REL_VOICE) is copied only with the gameplay tables; the unique index only with `--ui source`.
(high)

**Fix (#29, Rust core on branch `voice-merge`, not merged):** copy `8168[C]` to S in every mode
(`--no-gameplay` then still re-packs game.rel for that one table), and with `--ui donor` rebuild the
donor family's bank `sound.(5+u_D)` with the source's sounds added (nothing to do when u_C ==
u_D). The merged bank keeps the retail layout (§2): one GROUP_DATA with the donor's gid; id lists =
sorted unions (runs of 3+ as `0x8000|first, last`); FX_DATA = donor's 13 FX + source's 13 FX
**sorted by id**; sdir = union sorted by id with recomputed samp offsets, `0xFFFFFFFF` end, ADPCM
infos after it; pool = header {macro, curve, keymap, layer} offsets (0 = none), each list donor
objects then source objects, `0xFFFFFFFF` end; samp in sdir order, 0x20-aligned. An id in both
inputs must have identical bytes and is kept once, so re-merging adds nothing and a second source
can be merged in. All 32 retail banks rebuild byte-identically and all 992 donor/source pairs merge
and verify. The bank no longer fits its slot (Toad + Mario = 0x23EA0 + ~0x2B500), so it is appended
to ZZZZ.dat (0x800-aligned) and the descriptors are rewritten: DOL `0x800EF508 + (5+u_D)*0x10` and
every challenge.rel `sound_ch` copy of that row. One merged bank per donor family.
Side effects: non-clone members of the donor family keep their voice and only carry the extra
samples; the cutscene timing `lbl_3_data_7F7C[u]` stays the donor's (line 0/7 may fire slightly
early or late); menu clips in `sound.38` are not touched. A `voice-swap` on the donor family must
happen before the merge.

* **Gap:** the menu captain clips in `sound.38` reuse captains' sample ids; a `sound-import` into a
  captain's voice bank leaves the menu copy unchanged (and whichever group is pushed first wins
  while both are loaded). (high)

## 7. ARAM budget

* MusyX's sample heap is ARAM `0x4500..0x804000` = 8,387,328 B (`sndInit` 8 MB at
  `ARGetBaseAddress()` 0x4000, plus a 0x500 zero buffer; `src/Musyx/hw_aramdma.c`). The game's own
  ARAM use starts at 0x804000 (`fn_800A648C`), so the character blob does not compete. When the heap
  is full, `aramStoreData` refuses (no MusyX streams are linked, so `aramStream` = `aramTop`) and that
  sample plays as silence. (high)
* A group's samples stay in ARAM until it is popped: `fn_800214D0` = `sndPopGroup`, called by
  `fn_3_9081C` (row 1), `fn_3_908E8` (announcer), `fn_3_909B0` (stadium row), `fn_3_90AB0` (a voice
  bank), each followed by `fn_800ACFB0` (free). Menu groups are popped before game.rel loads
  (`fn_80021410`). (high)
* Exhibition match stack: row 0 (174,144 B of samples) + row 1, gids 28/29 (4,254,368 B) + 18 voice
  banks + the stadium row (largest Mario Stadium, 294,112 B). Retail worst case (the 18 largest
  banks): 7,962,080 B, **425,248 B free**. With one merged bank (source samples counted once, worst
  over all 32 sources): 8,097,664 B, 289,664 B free. The `voice-merge` core computes this worst case
  from the disc on every donor-mode run and refuses ("...use --ui source") if it would not fit.
  Practice and minigames have more than 1.2 MB free. (high, computed from the disc)
* Caveats: demo/attract mode pushes row 47 last and is already near the limit in retail; the main-RAM
  buffer for loading a bank (read whole, then shrunk) grows from at most 252 KB to 490 KB with a
  merged bank (not traced). Keep `sound-import` replacements near the retail size (it reports growth).

## 8. Unknown / not done
* Lines 1, 2, 6, 8, 12 triggers; `fn_3_657E4` (line 7 / 9) context.
* Rows 0, 4, 46, 47 SFX meanings; umpire calls; `sound.38` FX-by-FX use; menu voices of a
  donor-mode clone.
* ADP encoder; MusyX sequence (song) format; main-RAM headroom for a merged bank.
* Merged voice banks: Rio test of the `voice-merge` build (silent case, heavy 18-character match).
