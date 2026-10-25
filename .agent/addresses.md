# Address lookup (GYQE01 modding): grep an address or symbol name; each row points at the doc section that owns the fact. Rows and docs must agree: fix both together.

DOL RAM addresses unless prefixed. DOL `.data` file offset = RAM - 0x800E8300 + 0xE5300. REL symbols (`fn_2_`/`lbl_2_` menus, `fn_3_`/`lbl_3_` game, `fn_1_`/`lbl_1_` challenge) are section offsets: the RELs are relocated at load, so they have no fixed RAM address. Docs: CMR `character_modding_report.md`, CS `character_select.md`, DM `data_map.md`, RF `roster_flow.md`, RM `modding_roadmap.md`, DK `decomp_knowledge.md`, SN `sounds.md`, ST `stats.md`, AN `animations.md`. Status = `tools/feedback_diff.py` lines (DK §2), 2026-10-24.

## 1. DOL tables and globals

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| 0x800E8AA8 | `lbl_800E8AA8` (0x440) = `rel` | 3 REL descriptors: 0 menus, 1 game, 2 challenge (LZSS, in aaaa.dat); followed by `boot` and `res` in the same symbol; read by fn_800097A0 | DM §4 |
| 0x800E8AD8 | `boot` | 3 boot files: LZSS 14/5 model, stored binary, small CI4 texarc | DM §4 |
| 0x800E8B08 | `res` | 62 common UI resource descriptors, resource id 0..61 (`res[n]` = 0x800E8B08 + n*0x10) | DM §4 |
| 0x800E8B18 (res+0x10) | `res[1]` | HUD card file; in-game loaded by game.rel fn_3_5BD40 from its own copy (lbl_3_data_6130+0x10) into UI slot 0xC (only fixed-offset loader found); charID c -> texture 30+c | CS §6 |
| 0x800E8BF8 (res+0xF0) | `res[15]` | menu common file, boot-loaded into UI slot 1: names c<29?c:c+28, mini images 153+c; ZZZZ+0x1A9FE800 | CS §8.2 |
| 0x800E8CD8 (res+0x1D0) | `res[29]` | select-grid portraits, charID c -> 4+c; ZZZZ+0x18AEE800 | CS §8.2 |
| 0x800E8D58 (res+0x250) | `res[37]` | strips file, boot-loaded into UI slot 0 | DM §4 |
| 0x800E8558 | `lbl_800E8558` / `characterStaticIndexes` | 54x6 B {family, baseCharID, uniqueIdx, isBase, isCaptain, colourIdx} per charID | CS §1 |
| 0x800E869C | `lbl_800E869C` | 32 B grid index -> base charID (twin of mainCharArray) | CS §1 |
| 0x800E86F0 | `lbl_800E86F0` (Ghidra `stonNiceContactIncrement`) | 12 star-player bonus bytes {50 x7, 20, 20, 50 x3} | ST §3; RF §2.4 |
| 0x800E63A0 | music path strings | 15 `snd/my_snd_h/*.adp` paths, named by `lbl_800E87B4` | SN §5.1 |
| 0x800E87B4 | `lbl_800E87B4` | 15 music tracks {path, size, 0, size}; only the path is used (fn_8006877C, game fn_3_8B094) | SN §5.1 |
| 0x800EE910 | `game_common` | 5 field/game common files (4 = 23 minigame strings) | DM §4 |
| 0x800EEAAC (0xEBAAC) | `lbl_800EEAAC` | 54 u16 glove/attachment bone-list base (= charID*6 retail) | CMR §1.1, §3 |
| 0x800EEB18 | `lbl_800EEB18` | 54 s16 charID -> per-model script id (variants share base id, -1 none); master 486+id; retail values in CMR §3 | CMR §3; DM §4 |
| 0x800EEC40 | `jumptable_800EEC40` | 48-entry per-charID setup switch in fn_80017814 | CMR §1.1 |
| 0x800EEFD0 | `lbl_800EEFD0` = `res_dol2` | copy 2 of the 62 UI resources; fn_80020388 loads [lbl_803CB7CC[stadium]+0x26] (stadium art) into slot 0xD, fn_80020278(n) loads [n+0x2D] (stills) | DM §4 |
| 0x800EEFE0 / 0x800EF0C0 / 0x800EF1A0 | `res_dol2[1]` / `[15]` / `[29]` | copies of the HUD card / common / grid descriptors | CS §6, §8.3 |
| 0x800EF508 | `sound` / `lbl_800EF508` | 48 MusyX group descriptors (stored); voice bank = [5+u]; every row | SN §2 |
| 0x800EF808 | `lbl_800EF808` | sound state: resources[48] (+4), pushed gids (+0x340), roster slot being loaded unk39A | SN §3 |
| 0x800EFBB4 | `lbl_800EFBB4` | sndInit config {64 voices, 48, 16, 1 studio, flags 1, ARAM 0x800000} | SN §2 |
| 0x800EFBE8 | `stadium` / `lbl_800EFBE8` | 21 stadium model descriptors, index stadium*3+variant (13 distinct); anchor of gap_8001E460.c `.data` | DM §4; CMR §6 |
| 0x800EFD38 (0xECD38) | `master` / `lbl_800EFD38` | 515 ARAM master descriptors {flags,0x40000000\|size,blob offset,comp}; blob-relative | DM §4; CMR §3 |
| 0x800EFD38 +[0..32] | master bodies | 33 base body models (not charID-indexed) | CMR §3 |
| 0x800EFD38 +[33..53] | master overlays | 21 texture overlays (texarc), via lbl_800F73B8 | CMR §3 |
| 0x800EFD38 +[54+charID*7+k] | master sub-items | k0..3 models (hand/glove/bat, 1-seq ANIM at +0x20), k4..6 event scripts | DM §4 |
| 0x800EFD38 +[432+charID] | master track-15 bank | 12-sequence ANIM bank (there is no skeleton file) | CMR §1; DM §4 |
| 0x800EFD38 +[486+id] | master event scripts | 29 keyed event scripts, id = lbl_800EEB18[charID] | DM §4 |
| 0x800F1D68 | `blob` / master[515] | {0,0x4D6600,ZZZZ+0x1A15E800,0x4D6600}, the 4.9 MB ARAM blob | CMR §8; DM §2 |
| 0x800F1D78 (0xEED78) | `lbl_800F1D78` / `subfile` | 54x19x16 B per-character disc subfiles, index charID*19+track | CMR §3 |
| 0x800F1D78 track 0 / 1 | body subfiles | hi-detail body (== master body) / low-detail body (Mario: 37 bones, different record order, skinFileID 1); both recoloured | CMR §3 |
| 0x800F1D78 tracks 2..18 | ANIM banks | track/action map, 544 distinct descriptors / 487 decoded byte patterns; 15 also master[432+c]; 7/8 usage unresolved | AN §1, §4 |
| 0x800F5D98 | `subitem` / `lbl_800F5D98` | 54x6x16 B sub-item disc files, index charID*6+itemSlot | CMR §3 |
| 0x800F71D8 | `model_script` | 30 per-model event scripts; disc fallback of master 486+id (fn_80021ADC); 0x1E0 | DM §4; CMR §3 |
| 0x800F73B8 (0xF43B8) | `lbl_800F73B8` | 54x2 s8 {bodyEntry, overlayEntry or -1} per charID; retail values in CMR §3 | CMR §3 |
| 0x800F7424 / 0x800F743C | `lbl_800F7424` / `lbl_800F743C` | 2x6x2 sub-item pair rows {k1,k2} / 54 per-character row index | CMR §3 |
| 0x800F7478 | end of gap_8001E460.c `.data` split | split is 0x800EFBE8..0x800F7478 | CMR §6 |
| 0x800FB798..0x800FBD80 | `lbl_800FB798` + 14 more 0x6C tables | 15 x s16[54]: 7 intervals + one exact-frame event; animation IDs mapped, 99 usually disables | ST §7 |
| 0x800FB798 / 804 | runner dive turn-around window | anim 0x32, fn_8004B284 +0x5C | ST §7 |
| 0x800FB870 / 8DC | runner body-check window | anim 0x33, +0xC0 | ST §7 |
| 0x800FB948 / 9B4 | runner dive side-turn window | anim 0x34, +0x124 | ST §7 |
| 0x800FBA20 / A8C | fielder pickup window | anim 0x1A, +0x188 | ST §7 |
| 0x800FBAF8 / B64 | fielder dive window | anim 0x1B, +0x1EC | ST §7 |
| 0x800FBBD0 / C3C | runner skid-stop window | anim 0x30, +0x250 | ST §7 |
| 0x800FBCA8 / D14 | fielder on-fire window | anim 0x10, fn_8004BEB0 | ST §7 |
| 0x800FBD80 | hit-by-pitch exact-frame event | anim 0x62 via fn_8004ACF4 -> fn_8004C510 | ST §7 |
| 0x800FBDEC / 0x800FBE64 | animation callback routing | byte[117] -> callback pointer[11]; establishes 0x10 and 0x62 window IDs | ST §7 |
| g_FieldingLogic +0xF6 / +0x13E | bodyCheckStageCountdown / chemistryThrowState | timer stages in fn_3_A96FC / 90-chem throw qualification in fn_3_ABDD0 | ST §6.1, §4.1 |

| 0x800FB5B0 | `menu_title` | title/main-menu UI copy (res 30) | DM §4 |
| 0x800FBF10 (+0x214) | `lbl_800FBF10` | u16[33][7] per-grid gameplay row, grid*14+k*2 (fn_8004B284) | CS §6 |
| 0x800FDE84 | `lbl_800FDE84` | 36 u8 roster grid cells -> base charID (0xFF empty); 26 used | CS §1 |
| 0x800FDE60 | `lbl_800FDE60` | per-cell grid draw order | CS §8.1 |
| 0x800FE5D4 | `lbl_800FE5D4` | 12 u8 captain grid {0,1,4,6,2,9,5,17,11,3,10,19} | CS §1 |
| 0x80108B18 | `lbl_80108B18` | announcer sndFX arg table ([0] used by fn_800628D4) | CS §6 |
| 0x80108DB8 | `lbl_80108DB8` / `mainCharArray` | 33 u8 grid index -> base charID | CS §1 |
| 0x80108DDC | `lbl_80108DDC` / `secondaryCharacterArray` | 22 u8 variant charIDs, mapped via jumptable_801091F4 | CS §1 |
| 0x80108DF4 | `lbl_80108DF4` | 33 u16 announcer name SFX ids 0x1C4..0x1E5 per unique index (0x20 = Birdo alt), samples in sound.37 | SN §4; CS §6 |
| 0x80108EC4 / 0x80109054 | `lbl_80108EC4` / `lbl_80109054` | pitcher list / per-class preferred fielding positions (class*5+k) | RF §2.3 |
| 0x80108EDC | `lbl_80108EDC` | 9x5 s16 colour-family lists (-1 padded); symbol 0x11C long | CS §1 |
| 0x80109044 | `text_sys` | system text bank, 11 strings, to ARAM | DM §4 |
| 0x801091F4 | `jumptable_801091F4` | variant charID -> base grid index switch in fn_800698F8 | CS §1 |
| 0x801092C8 | `opening` | opening movie set: 0 HVQM4 82 MB, 1 data, 2 UI (= res 34) | DM §4 |
| 0x80109AE8 (+unique*0x64) | `lbl_80109AE8` | records/star screen rows, keyed by unique (isBase only) | CS §6 |
| 0x80118220 (.bss, 0x520) | `lbl_80118220` | 13 per-model script objects x 0x64 (`loadStadiumObject`) | CMR §1.1 |
| 0x8023D6C0 | `lbl_8023D6C0` | menu logical resource-id table (fn_80034F50 resolves scene byte +0x14) | CS §8.1 |
| 0x802E4B00 (.bss) | `lbl_802E4B00` | copy of the 18 star flags for game.rel | RF §1 |
| 0x803CB790 (sdata) | `lbl_803CB790` | pointer to runtime subfile table | CMR §3 |
| 0x803CB7E0 (sdata) | `lbl_803CB7E0` | 4 u16 master tier counts {54,378,54,29} | CMR §3 |
| 0x803CB7CC (sdata) | `lbl_803CB7CC` | {0..6} stadium -> res offset (res 38..44 = stadium art) | DM §4 |
| 0x803CB748 (sdata) | `lbl_803CB748` | 6 u8 unique idx needing unlock (fn_80024C04, fn_2_348C) | CS §1 |
| 0x8034E9A0 (.bss, 0x4C28) | `lbl_8034E9A0` / `Static_Stats_Tables` | 54x0xA0 CharacterStats, loaded from ZZZZ+0x6CF8800; menu state follows (selected +0x46E0, indices +0x4708, charTaken +0x4757, rankedByChemistry +0x478D, chemistry rows +0x47F9, star flags +0x489B) | RF §1; CS §1 |
| 0x80353BE0 (.bss, 0xB40) | `inMemRoster[2][9]` | in-match roster, CharacterStats 0xA0 each | RF §1 |
| 0x80354720 (.bss, 0x48) | `lbl_80354720[2][9]` | 4 B per slot, unk2 = batting order / position link | RF §1 |
| 0x803C5EA4 (.bss) | `lbl_803C5EA4` | s16 mirror of teams[] written by fn_2_8940 | RF §2.3 |
| 0x803C6724 (.bss, 0x5C) | `lbl_803C6724` / `MenusTeamSelections` | teams +0x02, order +0x14, selectionFlags +0x26, **unk38[2][9] +0x38 free** (planned skin choice), unk4A +0x4A | RF §1, §6.1 |
| 0x8036E548 (.bss, 0x3154) | `g_hugeAnimStruct` | animation/actor struct: slots[13] +0xC04, loader state | RF §1; CMR §1.1 |
| 0x803716B8 | `lbl_803716B8` | load-queue state (ring of 18, ARAM address arrays, flags) | CMR §1.1 |
| 0x80001840 | OS low memory | NOT a DOL table; fork's batting-style hook was an emulator poke | CMR §5 |

## 2. DOL functions

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_80017098 | load request | request character load / reuse slot (entry point); MATCH | CMR §1; RF §5.4 |
| fn_8001758C | slot record + track pick | fills slot, track = charID*19+(variant==0), body load; MATCH | CMR §1; RF §5.4 |
| fn_8002204C | body model loader | {body, overlay} pair -> master, else disc track 0; MATCH | CMR §1.1 |
| fn_80021CA4 | sub-item pair loader | bat/glove pair loader using lbl_800F743C/7424/5D98; MATCH | CMR §3 |
| fn_80021BBC | track-15 bank loader | master 432+charID else subfile track 15; charID<0x36; MATCH | CMR §1.1 |
| fn_8002244C | sub-item queue callback | packedID=charID<<16\|itemID, chains 2nd sub-item; MATCH | CMR §1.1 |
| fn_8002254C | overlay loader | decompresses master[overlay] over the body texture archive; asm only | CMR §1.1 |
| fn_80022620 / fn_80022634 | load completion cbs | queue completion callbacks | CMR §1.1 |
| fn_80022CB4 | queue descriptor | ring of 18 records in lbl_803716B8 | CMR §1.1 |
| fn_800227E4 | ARAM blob streamer | allocs hard-coded 0x4D6600 (0x800227EC/F4), streams master[515] | CMR §8; DM §2 |
| fn_80021ADC | event script loader | master 486+modelID (id<0x1D), disc fallback model_script | CMR §1.1; DM §4 |
| fn_8002399C | actor slot init | calls f_InitActorWithLayout; MATCH | CMR §1.1 |
| f_InitActorWithLayout (0x800232E0) | actor builder | carve actor/skin/bones; crash 0x800233A0 if skinFileID>=numDescriptors; 111 lines | CMR §1.1, §2 |
| fn_80016344 / fn_80016710 | slot state machines | anim banks, per-model script, bat/glove; 32 / 28 lines | CMR §1.1, §2; DK §14 |
| fn_80016B60 / fn_80016F7C | anim bank streaming | mode-dependent 4/13,12/11/14,5/18,16; skips steps7/8 (2/9/10), shares block0 bank; slots0..3 | AN §1; CMR §2 |
| fn_80014D4C / fn_8001C67C_animation (0x8001C67C) | batting bank cache/install | tracks2/10 (practice),9 (mode7/+0x11); current batter loader | AN §1 |
| fn_80017340 | runner bank loader | +0x14 <- track3, practice11; called by fn_8001500C | AN §1 |
| fn_8001C588 / fn_8001C920 | pitcher idle / action banks | track6 -> +0x20; track5/18 -> +0x1C | AN §1 |
| AnimateCharacter (0x8001B990) / QueueCharacterAnimation (0x8001B918) | animation requests | pending ID+0x64 / queued follow-on | AN §5 |
| fn_8001BA44 / fn_8001BE50 | animation ID partition | ID -> group0..5 and sequence; slot bank+0x10+group*4 | AN §1, §5 |
| fn_8001C234 / fn_800BD8C4 | apply pending animation / instance update | set bank/sequence/time/speed, bind, tick; effect callback dispatch | AN §5 |
| f_InitBone (0x80022DAC) / LoadActorLayout (0x800B4910) | actor hierarchy | layout-relative pointer relocation, recursive bone constructor; IDs differ from indices | AN §3 |
| ACTSetAnimation (0x800B4D64) / ANIMGetTrackFromSequence (0x800B4F9C) | bone binding | runtime boneID -> sequence trackID, linear ID search | AN §3 |
| ANIMGet (0x800B508C) / ANIMGetSequence (0x800B4FEC) | bank relocation / sequence lookup | retail ANIMGet(buffer), contiguous sequence/track/key tables; SDK prototypes conflict | AN §2 |
| ANIMGetKeyFrameFromTrack (0x800B4E9C) | key interval lookup | cached index, backward restart, last->first wrap | AN §2 |
| GetData (0x800B560C) / DoTranslationAnimation (0x800B5DA8) / DoScaleAnimation (0x800B63DC) / DoEulerAnimation (0x800B6E0C) / DoQuatAnimation (0x800B71C0) | channel decoders | quantization, packed interpolation modes, fixed-point quaternion exception | AN §2 |
| ANIMTick (0x800B7718) / ANIMBind (0x800B79A0) / ACTSetBoneTrack (0x800B79D0) / AnimateActorBones (0x800B4B38) | bone playback | channel evaluation, direction/speed/loop/clamp, interpolation overrides | AN §2, §5 |
| 0x803CBB48 / 0x803CBB4C / 0x803CBB50 / 0x803CBB51 | quaternion quantization | two f32=1/16384 and two u8=3 (s16 encoding) | AN §2 |
| game fn_3_631AC (0x631AC), 0x63258..63300 | runner0x2E request | runner sequence1, flying-family direction-change transition; exact visual name unknown | AN §4; ST §6.1 |
| fn_80017814 | root relocation | texture bind, actor build, bone map, jumptable switch; 48 lines | CMR §1.1 |
| fn_800BD190 | bind textures to geo | (geo, tex) | CMR §1 |
| convertTextureHeader (0x800C0770) / LoadGeoPalette (0x800BCB44) | texture / palette fixups | MATCH | CMR §2 |
| DecompressDiskData (0x800A6654) | LZSS expansion | bit 30 of size word = compressed; 36 lines | CMR §2; DK §12 |
| fn_80012B90 / fn_80013680 | bat/glove loaders | first decompile, hundreds of lines | CMR §2 |
| fn_800638B4, fn_80063010, fn_8004B7B4, fn_800637BC, fn_800637D4, fn_8004BD6C, fn_80052634, fn_80062ED4 | per-charID setup | cases 2 / 33..36 / 19 / 20,43 / 41 / 38,41 / 14,37 / 16,44..47 of jumptable_800EEC40 | CMR §1.1 |
| fn_800B2B74 / fn_800B2B54 / fn_800B2BA8 / fn_800B2C08 / fn_800BD548 / fn_8001FC4C | fn_80017814 bone setup calls | ids 19/25/36, 3/2/1/46 | CMR §1.1 |
| fn_8001500C, fn_8001594C, fn_80016344, fn_80016710, fn_80019C00, fn_8001A3FC | model-map readers | read lbl_800EEB18[charID] | CMR §3 |
| fn_80011CA8, LoadModel, fn_80013680, fn_80014204, fn_800145F8, fn_8001D180 | glove-table readers | lhax(lbl_800EEAAC, charID*2) | CMR §1.1 |
| fn_8001500C | batter + runners driver | fn_80017098(team, player, 1, slotKind, variant = slotKind==9); 48 lines | RF §5.3 |
| fn_8001594C | fielder driver | nine fielders, variant 0; stub | RF §5.2 |
| fn_80015468 | fielder anim banks | prunes loadedCharID, streams track 4/17; stub | RF §5.2 |
| fn_80011BE4 | unload slot | slotPtrs[slot]=NULL, frees slotOwner (0x2D6A) entries; stub | RF §5.6 |
| fn_80014E50 / fn_80014F40 | model caches | batter / runner model cache fill (keyed on charID); stubs | RF §5.4 |
| fn_80018270 | allocation | invalidates the model caches; stub | RF §5.4 |
| transferStatsToInMemRoster (0x800426DC) | star toggle | re-copies a roster entry from the static row; 26 lines | RF §2.4 |
| characterSelectScreen (0x80065DEC) | fielding positions | re-copies the nine entries in position order; stub | RF §2.3 |
| unsure_FillRosterPositions (0x80064A04) | roster bookkeeping | no inMemRoster access; stub | RF §2.3 |
| fn_800678CC / fn_80066EAC / fn_80069854 | select bookkeeping / chemistry rows +0x47F9 / captain index | stub / stub / MATCH | RF §2.3 |
| fn_800471F4 | substitution | swaps two roster entries (pause menu fn_8004617C); stub | RF §2.4 |
| fn_80047CE0 / pauseMenuSelection (0x80047FE4) | after substitution | re-run characterSelectScreen; stubs | RF §2.4 |
| startGameRelated (0x80048EB8) / fn_8005A350 | star toggle callers | pre-game lineup / star menu | RF §2.4 |
| fn_80068838 | saved lineup load | into inMemRoster and teams[]; stub | RF §2.3 |
| fn_800415A8 | CPU team builder | family columns 1..4 (0xAD4); stub | CS §5; RF §2.3 |
| fn_800698F8 | findCharacterID | charID -> grid/unique index; 36 lines; head patched by --ui source | CS §5, §6 |
| fn_800628D4 | announcer call-out | sets useAltBirdoGrid, plays lbl_80108DF4[grid]; MATCH | CS §6 |
| fn_80067AC8 | family column lookup | row[column] of lbl_80108EDC or -1; MATCH | CS §2 |
| fn_80067B40 | family taken-flag writer | (unused, charID, value); value 2 = query; 8 lines | CS §2 |
| fn_8004B284 / fn_8004BEB0 / fn_8004C510 | anim events | 6 bone windows / on-fire interval / hit-by-pitch exact frame; mapped in ST | ST §7 |
| fn_80067C48 | chemistry ranking | sorts ids by chemistry into lbl_8034E9A0+0x478D+idx*54; stub, next to decompile | CS §2, §5 |
| fn_80067F70 | CPU auto-pick | random from top 20 ranked free ids, marks family taken; stub, next to decompile | CS §2, §5 |
| fn_800506E8 | cell badge writer | lbl_803C6028.slots[cell] by base charID; MATCH | CS §5 |
| fn_8004E504 / fn_8004E5B4 / fn_8004D460 / fn_8004D4F0 | captain / other grid | MATCH | CS §2 |
| fn_80024C04 | unlock check | reads lbl_803CB748; MATCH | CS §1 |
| fn_800625A4 | request menu command | writes lbl_803C66B0.flags5D[side] only | CS §8.1 |
| fn_80051D00 | build DOL grid scene | cell -> lbl_800FDE84; resource 9 / seq 0x19; non-matching C | CS §8.1 |
| fn_800363D8 | set pane texture | (scene,pane,layer,seq,frame); MATCH | CS §8.1 |
| fn_80035838 / fn_80035B50 / fn_80034F50 | UI resource load (desc, slot) / find slot / resolve id via lbl_8023D6C0 | | CS §6, §8.1 |
| fn_8000CEF0 | sprite query decoder | complete C, non-matching; records descending frame order | CS §8.2, §8.4 |
| fn_8000D838 / fn_8000D164 | sprite rendering | asm only | CS §8.2 |
| fn_8000BA3C | packed-bank traversal | nested sequence index at 0x8000C104..C13C | CS §8.4 |
| fn_8004B284 | per-grid gameplay row | lbl_800FBF10+0x214 | CS §6 |
| fn_800216F8 / fn_80021518 | sound group load / push | queue a row load; fn_80021518(gid, res) = sndPushGroup(proj, gid, samp, sdir, pool) | SN §2 |
| fn_8006877C / LoadFile / fn_800A8E30 | music stream start | track -> lbl_800E87B4 row -> DVDFastOpen + DVDPrepareStreamAsync(0, 0) | SN §5.1 |
| fn_80062A94 | menu music | sndFXStartEx(0x1E4) with fade (sound.37) | SN §4 |
| fn_800215F8 / fn_80021758 / fn_80021650 | sound group loaders | ARAMTransfer the row, relocate the 4 chunk offsets, call back | SN §2 |
| fn_80020388 | stadium art loader | res_dol2[lbl_803CB7CC[stadium]+0x26] into UI slot 0xD | DM §4 |
| fn_80020278 | stills loader | res_dol2[n+0x2D] (res 45..61) by ARAMTransfer into a heap buffer | DM §4 |
| fn_800188C0 | game_common loader | table 0x800EE910 | DM §4 |
| fn_800097A0 | boot state machine | switches aaaa.dat / ZZZZ.dat; loads RELs; res 37 -> slot 0, res 15 -> slot 1 | DM §2, §4 |
| ARAMTransfer / DVDFastOpen / DVDReadAsyncPrio | disc read path | 0x8000-byte chunks to staging buffer | DM §2 |
| fn_800A6E24 / fn_800A6D10 | sNp HVQM4 player | movie streaming | DM §2 |
| fn_800697B0 / fn_8006AF9C / fn_8004A1BC | text_sys / opening / menu_title loaders | per descriptor tables | DM §4 |
| fn_80064918 | charID -> category switch | 0..51 range | CS §4 |
| fn_800671FC / fn_800649BC / fn_80050138 / fn_80050FE8 | roster rebuild helpers | called from fn_2_2FC0 / fn_2_7DDC | CS §5 |
| fn_800675C4, fn_8006CDC0 | grid / records readers | | CS §6 |

## 3. menus.rel (fn_2_* / lbl_2_*)

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_2_554 | stats loader (boot) | loads stats.0 (ZZZZ+0x6CF8800) into lbl_8034E9A0 | ST §1 |
| fn_2_12238 / fn_2_12CD8 / fn_2_12F88 | Challenge start team | copies captain block lineup 0 (lbl_8034E9A0+0x4380+i*0x48) to team 0 | ST §5 |
| fn_2_A288 / fn_2_B920 | captain templates 1/2/3 | exclude opponent captain from templates 1/2, choose an available one or captain-only 3 | ST §5 |
| fn_2_4C3EC / fn_2_BF90 | captain lineup 0 | Challenge availability mask / side-1 starting roster | ST §5 |
| fn_2_2FC0 | roster rebuild | (mode, finish, rebuild); taken flags, locked uniques, auto-pick, fn_2_8940; MATCH | CS §5; RF §2.3 |
| fn_2_3204 / fn_2_8ED4C | fn_2_2FC0 callers | (mode,1,1) / (9,0,1) | CS §5; RF §2.3 |
| fn_2_8940 | roster copy | Static_Stats_Tables[teams] -> inMemRoster in pick order; MATCH | RF §2.3 |
| fn_2_348C | locked-unique loop | taken[c]=locked per lbl_803CB748; MATCH | CS §5 |
| fn_2_3624 | cursor / L colour cycle | roster pick logic; 5 lines (issue #4) | handoff_fn_2_3624.md; RF §2.1 |
| fn_2_A040 | colour cycle step | teams[side][slot] = next free family member; MATCH | RF §2.1 |
| fn_2_4970 | undo pick | (side, captainID) B-button path; MATCH | CS §5 |
| fn_2_7DDC | open roster screen | clears taken flags, sets cursors, gridPick; MATCH | CS §5 |
| fn_2_5F80 | rebuild teams[] from inMemRoster | MATCH | RF §2.3 |
| fn_2_8CF8 / fn_2_9ACC / fn_2_11EA8 / fn_2_5163C / fn_2_20D08 | other roster copies / lineup backup, saved lineup | stubs | RF §2.3 |
| fn_2_DFAC | confirm pick | teams[side][slot]=charID, request 0xF; MATCH | CS §8.1; RF §2.1 |
| fn_2_C698 | markSlotTaken | charTaken=1, badge, family taken; MATCH | CS §5 |
| fn_2_1C34 | button switch | A=0x1B8, B=0x1B9, dirs=0x1B7; MATCH | CS §8.1 |
| fn_2_102C8 | random fill | strategies FCB4/FAA0/F200; non-matching C | CS §8.1 |
| fn_2_5444 | ready handler | challenge lineup copy, sends 0x13; non-matching C | CS §8.1; RF §2.2 |
| fn_2_7265C | open grid | scans characterFlags; MATCH | CS §8.1 |
| fn_2_7F8BC | command 0xF | card anim, pane 0x58+side*9+cursor frame teams<<16 | CS §8.1 |
| fn_2_75BE4 | chemistry stars | thresholds 15/35/55/70 | CS §8.1 |
| fn_2_7DAB8 | command 0xE | roster focus anim | CS §8.1 |
| fn_2_74F40 | name/stat preview | name pane 0xB0+side seq 0x82, mini 0x83, frame=charID; colour-word switch | CS §8.1, §8.3 |
| fn_2_776A0 | per-pad maintenance | consumes L-colour unk50, writes mini image frame | CS §8.1 |
| fn_2_81628 | roster scene update cb | command consumer via jumptable_2_data_2D920 (cmds 9..0x1D); stub | CS §8.1 |
| fn_2_8279C / fn_2_7AE3C | roster scene create (script lbl_2_data_2B59C) / initial population | stubs | CS §8.1 |
| fn_2_86EC / fn_2_CCBC / fn_2_110B0 | fn_2_7DDC callers | | CS §5 |
| fn_2_CE44 | B-button path | calls fn_2_4970 | CS §5 |
| fn_2_12A70 | captain pick | calls fn_800628D4 | CS §6 |
| fn_2_481F4 | character preview | fn_80016710(charID, slot) | RF §5.1 |
| fn_2_1C860, fn_2_45204, fn_2_454E8 | records/star screens | lbl_80109AE8 + unique*0x64 | CS §6 |
| fn_2_4EB2C / fn_2_5ED3C | small portraits | slots 0x15 / 0xA, unique-keyed | CS §6 |
| fn_2_4E970 / fn_2_4EABC | Challenge UI loaders | slot 0x17: ending archive / Challenge scene | CS §8.4 |
| fn_2_1B7B4 | Challenge special transition | load path 0x1BAEC..0x1BB1C, difficulty +0x4415>=3 | CS §8.4 |
| fn_2_2587C | pane1 callback | ending pane; MATCH | CS §8.4 |
| fn_2_24238 / fn_2_2460C | ending scene | script lbl_2_data_1059C, callbacks lbl_2_data_105FC | CS §8.4 |
| fn_2_8DB14 | menu scene select | by lbl_2_bss_1A824C->unk7746 - 0x19 | DM §7 |
| fn_2_17C88 / 17ED8 / 18148 / 188EC | menu_char_a users | per-charID 3D scene A | DM §4 |
| fn_2_47540 / 477C0 / 478F4 / 481F4 | menu_char_b users | per-charID 3D scene B | DM §4 |
| menus .data+0xC8 | `stats` | descriptor of stats.0 (ZZZZ+0x6CF8800) | DM §4; ST §1 |
| menus .data+0x444 / 0xD14 / 0x1314 / 0x18B4 / 0x1CD4 / 0x2A9B4 / 0x2B3DC / 0x2E1EC / 0x302BC | `menu_set`..`menu_set_i` | nine identical 16-slot menu resource sets (slot 1 = grid portraits); 0x2B3DC = character select (fn_2_73994/760CC/7BFF8) | DM §4 |
| menus .data+0x454 / 0xD24 / 0x1324 / 0x18C4 / 0x1CE4 / 0x2A9C4 / 0x2B3EC / 0x2E1FC / 0x302CC | grid descriptor copies | slot 1 of the nine sets (9 copies) | CS §8.3 |
| menus .data+0x241C | `menu_char_a` | 54 per-charID menu 3D scenes | DM §4 |
| menus .data+0x12EC0 | `menu_char_b` | 54-row copy of A | DM §4 |
| menus .data+0x12170 | `movie` | 2 HVQM4 movies | DM §4 |
| menus .data+0x12298 | `text_menu` | 954-string menu text bank | DM §4 |
| menus .data+0x1F884 / 0x1FF84 / 0x20BF0 | menu sets | UI pair / options+records (599 strings) / lineup | DM §4 |
| menus .data+0x132DC | `lbl_2_data_132DC` | Challenge ending archive descriptor, ZZZZ+0x19135800 | CS §8.4 |
| menus .data+0x1326C | `lbl_2_data_1326C` | Challenge scene UI, ZZZZ+0x18E92800 (slot 0x17 reused) | CS §8.4 |
| menus .data+0x1323C | `challenge_ui` | 11 Challenge UI resources | DM §4 |
| menus .data+0x2F990 | `menu_scene_2f990` | 67 menu 3D scene models | DM §4 |
| menus .data+0x2D844 (0xA8) | `jumptable_2_data_2D844` | colour-word switch, 42 entries charIDs 12..53, R_PPC_ADDR32 addends | CS §8.3 |
| menus .text 0x7556C..0x7559C | colour-word cases | `li r0,N` at 0x7556C+8*(N-1), label 0 at 0x7559C; pane 0xAE seq 0x7B | CS §8.3 |
| menus .data+0x2D920 (0x54) | `jumptable_2_data_2D920` | 21 entries, commands 9..0x1D in fn_2_81628 | CS §8.1 |
| menus .bss+0xF468 (0xC4C) | `lbl_2_bss_F468` | cursor[side], flags37/flags3D pick-pending bytes | CS §5 |
| menus .bss+0xF410 (0x58) | `lbl_2_bss_F410` | gridPick[side], cached grid pick | CS §5 |
| aaaa+0x800 (0x5A818 packed) | menus.rel | re-packed in place by the colour-word patch (355584 B in room 372736) | DM §3; CS §8.3 |

## 4. game.rel (fn_3_* / lbl_3_*)

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_3_B4124 / fn_3_10C450 | practice/minigame roster copy | memcpy(&lbl_8034E9A0[charId], 0xA0); MATCH | RF §2.4 |
| fn_3_6BD6C | fielder driver | -> fn_8001594C(teamFielding) at half-inning changes | RF §5.1 |
| fn_3_6BA64 | batter/runner driver | -> fn_8001500C per at-bat | RF §5.1 |
| fn_3_6B870 | unload runners | fn_80011BE4 | RF §5.6 |
| fn_3_6B4C8 / fn_3_6B5D8 | fn_80016344 callers | fn_3_6B4C8 (star cutscene) / fn_3_6B5D8 (called from fn_3_5BD40) | RF §5.1 |
| fn_3_10C81C | fn_80016710 caller | minigames | RF §5.1 |
| fn_3_5EC0 | stadium relocation | 16-word stadium root loader | DM §2 |
| fn_3_64DC | stadium loader copy | stadium_game table | DM §4 |
| manageStadiumLoading | stadium loader | reads lbl_800EFBE8[unk9*3+unkA] | DM §4 |
| fn_3_90220 / fn_3_90150 | `playCharacterSound(charID, line)` | SFX lbl_3_data_8168[charID] + line; 26 call sites = voice-line table | SN §3 |
| setInMemBatterConstants (fn_3_6DE60) / fn_3_6EBB4 / fn_3_6D964 / setFielderValues | row -> actor | copy CharacterStats fields into g_Batter / g_Pitcher / runner / fielder | ST §2 |
| fn_3_6EF1C | Challenge item buffs | scales inMemRoster stats by lbl_3_data_5FC4 at game start | ST §2 |
| fn_3_6D658 | chemistry(team, a, b) | static row +0x3B+b, + Challenge item bonus, max 100; compared with lbl_3_data_4638 {90,20,90,90} | ST §4 |
| checkFieldingStat (fn_3_6D604) | ability test | inMemRoster[t][s].FieldingStats & (1 << bit) | ST §3 |
| fn_3_90F48 / fn_3_90B14 / fn_3_5A28C | voice bank loaders | fn_800216F8(u+5), push lbl_3_data_8148[u]; 5A28C loops over all 18 roster slots | SN §3 |
| fn_3_9056C / fn_3_90674 / fn_3_906FC | MusyX songs | sndSeqPlayEx(group 29, song, game_set.0 arrangement) | SN §5.2 |
| fn_3_91D1C | HUD card pane | pane->unk5C = CharID<<16 (+ EA340, EAEF4, EB6E0, 11F02C, 121304, 127B68) | CS §6 |
| fn_3_10CC20 / fn_3_B49D4 | announcer callers | batter/pitcher intro | CS §6 |
| fn_3_59F40 / fn_3_5A28C | game_set loaders | slot 0x14 portraits (row 7 = res 5) | DM §4; CS §6 |
| fn_3_59C2C | UI loader | lbl_3_data_3D80 res 0 / 14 / 29 into slots 2 / 0xB / 9 | DM §4 |
| fn_3_5BD40 | HUD card loader | lbl_3_data_6130+0x10 (res 1) into UI slot 0xC | DM §4; CS §6 |
| fn_3_AF10C | res loader | lbl_3_data_F538[2] into slot 0x13 | DM §4 |
| fn_3_B43E8 | results loader | game_res_c | DM §4 |
| fn_3_B9BB4 | field object sets | stores ARAMTransfer(&lbl_3_data_10ACC[stadium]) in stadiumObjectLoadingPtr | DM §4 |
| fn_3_10B8D0 / 10F3D8 / 10FDC8 | minigame loaders | minigame_res [minigame+6] | DM §4 |
| fn_3_BF878 / fn_3_BEFF8 / fn_3_106E50 / fn_3_1665E4 | misc loaders | model42 / 44-section / camera / results text | DM §4 |
| game .data+0x0 | `stats_game` | stats.0 descriptor for the debug loader maybeProcessTeamData (file as 12 teams x 9 rows) | DM §4; ST §1 |
| game .data+0x7EC | `stadium_game` | 21 stadium descriptors | DM §4 |
| game .data+0x8168 | `characterSoundArray` | voice SFX base, 54 u16 per charID (lines base+0..12) | SN §3 |
| game .data+0x8148 | `lbl_3_data_8148` | u8[32] voice group id per unique index (symbols.txt says float) | SN §3 |
| game .data+0x7F7C | `lbl_3_data_7F7C` | s16[32][4] per unique index: anim frame of voice line 0 (HR end) / 7 (championship) | SN §3 |
| game .data+0x81D4 | `lbl_3_data_81D4` | u8[7] stadium SFX group ids (rows 39..45) | SN §2 |
| game .data+0x8530 | `lbl_3_data_8530` | voice line volume[0x180] / pan[0x180] | SN §3 |
| game .data+0x88E0 | `lbl_3_data_88E0` | 19 SongEntry {group, song, _} in-match songs | SN §5.2 |
| game .data+0x6EF8 | `BatterHitbox` | 54 x BatterReachStruct (9 f32): batter reach box | ST §6 |
| game .data+0x7690 | `ChargePowerConstants` | 54 x u8[2]: frameFullyCharged, frameChargeDownBegins | ST §6 |
| game .data+0x7870 | runner frames | 54 x s16[3]: turn-state cutoff, lead-off frame anchor, anim 0x2E anchor minus 10 (formulas high) | ST §6 |
| game .data+0x7E34 | `bodyCheckFrameRelatedConstants` | 54 x u8[4]: reaction start / countdown threshold / knockback duration / elapsed frames to result processing | ST §6 |
| game .data+0x17000 | foot height | 54 x s32, /100000 = foot-down height (bones 0x1E/0x22) | ST §6 |
| game .data+0x4638 | chemistry thresholds | s16 {90 throw qualification, 20 exclusive anti-chem upper bound, 90 bobble assistance, 90 batting links} | ST §4.1 |
| game .data+0x76FC (unique*3) | `lbl_3_data_76FC` | gameplay check by kind (rep_1200) | CS §6 |
| game .data+0x3D60 | `game_set` | 69 rows; rows 2..63 = res 0..61 (`lbl_3_data_3D80`); row 7 (+0x70) lineup portraits | DM §4 |
| game .data+0x3D80 / 0x6130 / 0xF538 / 0x10598 / 0x21EC8 | res copies (game_set+0x20, game_res_a, game_res_b, game_res_c+0x20, minigame_res) | +0x10 HUD card, +0xF0 common, +0x1D0 grid descriptor | CS §6, §8.3; DM §4 |
| game .data+0x10ACC | `field` | 7 per-stadium field object sets | DM §4 |
| game .data+0x11380 / 0x115EC / 0x20FDC | model42 / 44-section / camera | | DM §4 |
| game .data+0x225F0 / 0x284E8 | actor/text sets | | DM §4 |
| aaaa+0x5B800 | game.rel packed | 0xF4450 packed; 0x3B0 slack before challenge.rel | DM §3 |

## 5. challenge.rel

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| challenge .data+0x0 | `field_ch` | 7 field sets copy (fn_1_1538) | DM §4 |
| challenge .data+0x8D0 / 0x10518 / 0x10674 | stadium copies | 21 rows each (fn_1_73B8 / 2004C / 1DCE4) | DM §4 |
| challenge .data+0xB70 | `menu_title_ch` | title UI copy | DM §4 |
| challenge .data+0xF0C | `challenge_map_ui` | 11 map UI pieces | DM §4 |
| challenge .data+0xAC | music track index | 15 rows as if concatenated .adp; loader fn_1_1E0; not a file table | DM §4 |
| challenge .data+0x196C | `sound_ch` | 50-row MusyX copy (fn_1_9F04) | DM §4 |
| challenge .data+0xFC0 / 0x17A4 / 0x17C4 | `lbl_1_data_FC0` / `17A4` / `17C4` | copies of the voice gid + SFX base tables; 17A4 = gids in another order, 17C4 = 18 bases (fn_1_A8B4, fn_1_B5B8) | SN §2 |
| challenge .data+0xA3D8 | `challenge_board` | 86 rows: 0..1 game_common, 2..31 model_script, 32..85 pieces | DM §4 |
| challenge .data+0xA940 / 0xA950 / 0xADE0 | partial_ch / scene / model42 | header read 0x200 of 0x15450 B file (fn_1_10560) | DM §4 |
| challenge .data+0xF968 | `challenge_models` | 24 map models (fn_1_1CBE4) | DM §4 |
| challenge .data+0xFB98 | `debug_browser` | 63-row sprite debug browser; [0] = ending archive, [1+n] = res n (fn_1_267F4) | CS §8.4; DM §4 |
| challenge .data+0xFC98 / +0xFD78 (file 0x41818 / 0x418F8) | `debug_browser[16]` / `[30]` | the challenge.rel copy of the common / grid descriptors; `.data` starts at file offset 0x31B80 of the unpacked REL | CS §8.3 |
| challenge .data+0x104F4 / 0x108F8 / 0x112D8 | small file / model42 / movie viewer | | DM §4 |
| aaaa+0x150000 | challenge.rel packed | 0x271C0 packed | DM §3 |

## 6. ZZZZ.dat / aaaa.dat files

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| DiskFileDesc (16 B BE) | {flags,sizeWord,offset,packed} | flags 0=stored else (repeat<<8)\|lookback (0x40B); size bit30=LZSS; offset 0x800-aligned (0x20 in blob) | DM §2 |
| ZZZZ+0x00000000..0x12000 | gap | 3 stored CMPR texarcs, unused | DM §3 |
| ZZZZ+0x12000 | opening movie | 82 MB HVQM4, stored | DM §1 |
| ZZZZ+0x06C96000 / 0x06CC3000 / 0x18D43800 | res 34..36 | 640x448 opening stills | DM §4 |
| ZZZZ+0x06CF8800 | `stats.0` | 0x46E0 stored: 54x0xA0 CharacterStats, 0x21C0 zero, 12x0x48 captain teams (+0x4380); stats-export/-import | ST §0, §5 |
| ZZZZ+0x06CFD000 | MarioStadium | enumDiskLocations.MarioStadium, stadium row 0 | DM §4 |
| ZZZZ+0x08F2E800..0x09438800 | gap | 5 MB, AdGCForm header, not loaded | DM §3 |
| ZZZZ+0x0B95C800.. | Pianta rows | slot 21 t0 0B95C800 t1 0B96D800; t2 0B977800 t3 0B9AF000 t15 0BAD6800 shared | CMR §3 |
| ZZZZ+0x0BB0F000 / 0BB1F000 / 0BB29000 / 0BB39000 | Pianta R/Y t0/t1 | slot 22 t0/t1, slot 23 t0/t1 | CMR §3 |
| ZZZZ+0x0CE16800..0x0E581000 | gap | 23.4 MB LZSS-looking, stale | DM §3 |
| ZZZZ+0x0E97A800 | res 16 | 144 captain banner textures 153x54 | DM §4 |
| ZZZZ+0x0EA16800.. | res 17..28 | 12 captain/team emblem sets | DM §4 |
| ZZZZ+0x0EAE4000..0x0EAF7000 | gap | 76 KB between Challenge map UI and menu models | DM §3 |
| ZZZZ+0x0F12C800..0x186A1800 | gap | 149.8 MB dense stale data | DM §3 |
| ZZZZ+0x18AC5000..0x18AC7000 | gap | 8 KB tail after Challenge partial file | DM §3 |
| ZZZZ+0x18AEE800 | res 29 grid portraits | 202 textures, 54x50x50 CI8 + RGB5A3 TLUT; c->4+c; unavailable 54->118; unpacked 0xADFFC packed 0x4BAB0; 17 descriptor copies | CS §8.2, §8.3 |
| ZZZZ+0x18B3A800 | res 30 | title/main menu, 122 textures, 3.6 MB | DM §4 |
| ZZZZ+0x18E92800 | Challenge scene UI | lbl_2_data_1326C target | CS §8.4 |
| ZZZZ+0x18ED3800 | res 31 | records/options UI | DM §4 |
| ZZZZ+0x18ED7000 | res 5 | 180 textures; unique u -> 53+u (32 CI8 50x50 at 53..84) | CS §6 |
| ZZZZ+0x18F0E000 / 0x191B8800 | res 32 / 33 | UI / menu_set slot 2 | DM §4 |
| ZZZZ+0x19135800 | Challenge ending archive | unpacked 0x23491C packed 0x82928, 427 textures, 101 seqs; not charID-keyed | CS §8.4 |
| ZZZZ+0x19A6F800..0x1A15E800 | gap | 6.9 MB, five AdGCForm containers | DM §3 |
| ZZZZ+0x1A15E800 | ARAM blob | 0x4D6600 B; 345 members; move + patch master[515] and 0x800227EC/F4 to grow | DM §2; CMR §8 |
| ZZZZ+0x1A635000 | res 0 | in-game HUD, 369 textures | DM §4 |
| ZZZZ+0x1A6B3000 | res 1 HUD card | 102 textures; CI8 50x50 + TLUT at 30..83 = charID 0..53; UI slot 0xC (fn_3_5BD40); 8 descriptor copies | CS §6 |
| ZZZZ+0x1A6D4800 / 0x1A6E8000 / 0x1A748800 | res 2 / 3 / 4 | game.rel slot 0x13 / large UI / 88 textures | DM §4 |
| ZZZZ+0x1A769800.. | res 6..13 | 8 full-screen 640x448 screens | DM §4 |
| ZZZZ+0x1A9E3800 | res 14 | 69 textures | DM §4 |
| ZZZZ+0x1A9FE800 | res 15 common menu file | unpacked 0x106568 packed 0x68C10; 440 textures; UI slot 1; 8 descriptor copies | CS §8.2, §8.3 |
| ZZZZ+0x1A9FE800 name index | roster preview name | seq 0x82: c<29 ? c : c+28; 111x18 CI4, shared RGB565 16-entry TLUT | CS §8.2 |
| ZZZZ+0x1A9FE800 mini index | roster mini image | seq 0x83: 153+c; 52x60 CI8, RGB5A3 TLUT; 54 placeholder -> 434; 48 buffers (alias groups {12,42} {20,43} {27,52,53} {48,49,51}) | CS §8.2 |
| ZZZZ+0x1AA67800 / 0x1AA74800.. / 0x1AA81000.. | res 37 / 38..44 / 45..61 | strips (UI slot 0) / stadium art (38+stadium, slot 0xD) / 17 stills 640x256 CI8 | DM §4 |
| ZZZZ end -0x5C0 | unreferenced tail | appending to ZZZZ.dat is safe; FST rebuilt by Dolphin | CMR §8 |
| aaaa+0x0..0x800 | header | unreferenced u16 pairs, never read | DM §3 |
| aaaa+0x800 / 0x5B800 / 0x150000 | menus / game / challenge .rel | packed RELs | DM §3 |
| .gpc root | {texture 0x20, layout, geo, skin, extra} | 8-word header; each word += base if nonzero, a zero stops the chain; TextureArchiveHeader at 0x20; CMPR for characters | DM §2; CMR §1.1 |
| donkey00.gpc 0x180..0x4F00 | DK textures | 10 textures; recolour CMPR endpoints only; not re-checked against the disc | CMR §5 |
| overlay file | texarc at +0x20 of body | length == layoutOff-0x20; written at body+0x20 | CMR §3 |
| master[13]/master[34] | BlueToad body/overlay | track0(BlueToad)==master[13] + master[34] at +0x20; pair {13,34} | CMR §3 |
| master[29] size 0x18028 vs body 13 size 0x195B0 | size < body | harmless; do not resize; only used if buf==NULL | CMR §8 |
| master[44] size 0x5BE0 vs body 0x16320 | same | BlueShyGuy | CMR §8 |
| lbl_800F73B8[41] | Paragoomba | {29,-1} | CMR §3 |
| ANIM bank | `anim` | ANIMBank version 0x007B7960, sequences 0xC each | DM §5 |
| UI file | `ui` | MenuUiFileHeader {texarc @0x20, sprite bank}; bank+8 -> seq table | DM §5; CS §8.2 |
| text bank | `text` | {u16 count,u16 0x0131,u32 offsets[]}, u16 glyphs end 0x4000 | DM §5 |
| musyx group | `musyx` | {0x20,size}x4 chunks proj/sdir/pool/samp; group id u16 at +0x24 | SN §2 |
| text banks (5) | text_menu.0, menu_1ff84.1, game_284e8.0, game_common.4, text_sys.0 | export/import lossless | DM §6 |
| sound rows 5..36 / 37 / 39..45 | voice banks / announcer / stadium SFX | sound.(5+u) voice of unique index u; sound.37 names + menu music; 0x27+stadium | SN §2 |
| game_set.0 | MusyX song arrangements | 19 sections = in-match songs of group 29 | SN §5.2 |
| snd/my_snd_h/*.adp | music streams | DVD stream ADPCM, stereo 48 kHz; star_01/03 unused | SN §5.1 |
| LZSS 11/4 | flags 0x40B | 1,492 files; 1 file LZSS 14/5 (0x50E); 78 stored | DM §1 |
| coverage | referenced 56.61% / gaps 43.10% | 194 MB in 7 gaps free for --reuse-gaps; retail ISO 1,459,978,240 B | DM §3 |

## 7. Struct fields that matter for modding

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| inMemRoster[team][slot].stats.CharID @ +0x24 | CharacterStats.CharID | s16 per-player charID | RF §1 |
| CharacterStats +0x00..+0x9F | CharacterStats | every field: offset, range, reader | ST §2 |
| CharacterStats size 0xA0 | CharacterStats | union over StatTable; chemistry at +0x3B (DK §14) | RF §1 |
| CharacterStats +0x37/+0x38/+0x39/+0x3A | display ratings | batting, pitching, running, fielding (not texture ids) | CS §8.1 |
| CharacterStats +0x3B.. | chemistry row | 54 bytes, 0..99, 50 self, symmetric | ST §4; CS §2 |
| CharacterStats +0x20 / +0x34..+0x36 | abilities / stars | u32 ability mask; captain, swing, pitch star | ST §3 |
| charID 0x0C / 0x2A | Green Koopa / Red Koopa | retail HUD textures 42/72 + both Ghidra enums; fixed ChemistryTable and catalogue colour swap | ST §4.2 |
| charID 0x1C | Toadsworth | no colour suffix in CHAR_ID / Ghidra; removed catalogue ToadsworthR label | ST §4.2 |
| StatTable.UnusedBytes[0] @ +0x05 | planned roster skin byte | no field access anywhere, but inside the memcpy(0x1E) of every roster copy: re-applied at the copy sites; static rows are per charID | RF §4, §6.1 |
| StatTable +0x1E/+0x1F | padding | stays with the slot across field-wise copies; don't use | RF §3.4 |
| Gap8001196CAnim (0x27C) | slot record | g_hugeAnimStruct.slots[13] at +0xC04 | RF §1; CMR §1 |
| slot record .charID @ 0x252 | actor charID | s8 | CMR §1 |
| slot record ._pad253 @ 0x253 | spare byte | no access in any module; planned slot skin byte | RF §1, §6.1 |
| slot record .slotKind @ 0x254 | role index | 0..8 fielders, 9 batter, 10..12 runners | CMR §1; RF §5 |
| slot record .blockIndex @ 0x255 | memory block index | passed to fn_8002399C | CMR §1.1 |
| slot record .team/.player @ 0x256/0x257 | team, roster slot | n-th-duplicate skin fallback | RF §6.5 |
| slot record .variant @ 0x259 | body source | 1 batter + menu/cutscene (ARAM body via lbl_800F73B8); 0 fielders/runners (disc track 1) | RF §5.5 |
| slot record @ 0x25A/0x25B | arm / stance | copied from roster bytes 0x26/0x27 | CMR §1 |
| slot record .isBatter @ 0x278 | batter flag | slotKind==9 | CMR §1 |
| slot record .boneIndices @ 0x162 | 120 u16 | boneID -> actor bone idx, 0xFFFF absent | CMR §1.1 |
| slot record 0x25D..0x273, ids 0x60..0x6E | flags / anim ids | reset in fn_80017814 | CMR §1.1 |
| slot record .stadiumObj @ +0x2C | per-model script object | legacy name; set after fn_80025FFC | CMR §1.1 |
| g_hugeAnimStruct 0x2D54 / 0x2D3C (keys 0x2D5C / 0x2D44) | cached batter / runner model | memcpy'd by fn_8001758C; keyed on charID only | RF §1, §5.4 |
| g_hugeAnimStruct.loadState @ 0x2D77 | load state | state machines 2..6 | CMR §1.1; RF §1 |
| g_hugeAnimStruct 0x2C50 / 0x2D7F / 0x2D8D | slotPtrs / loadedCharID / bankLoadStep | per-slot | CMR §1.1; RF §1 |
| g_hugeAnimStruct 0x2D6A | slotOwner[13] | freed by fn_80011BE4 | RF §5.6 |
| g_hugeAnimStruct 0x2CAC / 0x2CBC / 0x2CFC+slot*0x14 | shared / batter / slot anim banks | sharedAnimBank, batterAnimBank, slot banks | CMR §1.1 |
| g_hugeAnimStruct.stadiumObjectLoadingPtr | field set pointer | set by fn_3_B9BB4 | DM §4 |
| lbl_803716B8.unk1EA bit0 / bit1 | bodies / track-15 banks in ARAM | blob callback ORs 0xF | CMR §1.1, §8 |
| lbl_803716B8.bodyAramAddrs / skeletonAramAddrs / subItemAramAddrs | per-tier ARAM addresses | aramBase+master[i].offset | CMR §1.1, §8 |
| lbl_803716B8.unk1E8 / loadBusy / current | queue state | 1 when body queued; busy flag; ring current | CMR §1.1 |
| TextureArchiveHeader | {u16 count,u16 0,TextureHeader[count]} | offsets relative to archive start | CMR §1.1 |
| TextureHeader (0x20 B) | texture header | +0 pixel off, +4 clut off, +8 h, +0xA w, +0x17 GX fmt, +0x18 pal count, +0x1A TLUT fmt | CS §8.2 |
| ActLayout.skinFileID | skin lookup | >= numDescriptors -> NULL deref at 0x800233A0 | CMR §1.1 |
| lbl_8034E9A0.useAltBirdoGrid @ 0x48AE | Birdo alt flag | | CS §5 |
| lbl_8034E9A0 +0x46E0 / +0x4708 | selected[2] / indices[2] | captain charIDs / captain roster index | RF §1 |
| lbl_8034E9A0 +0x478D + idx*54 | chemistry-ranked ids | per player | CS §2 |
| lbl_803C6724 .teams[side][slot] / .order / .unk38 | picks / batting order / free (planned skin) | menus selections | RF §1, §6.1 |
| lbl_803C6028.slots[cell] | grid pick badge | controller index or -1, by base charID | CS §5 |
| lbl_803C66B0.flags5D[side] | menu command flag | | CS §8.1 |
| lbl_803297E0.mode | menu mode | fn_2_2FC0 key | CS §5 |
| lbl_80361B20.characterFlags | per-char flags | transition1/2 scan; star unlocked | CS §8.1; RF §2.4 |
| g_d_GameSettings.charUnlocked @ 0x1A..0x1F | unlock bytes | 6 locked uniques | CS §5 |
| g_d_GameSettings.unk9 / unkA | stadium / variant | index stadium*3+variant | DM §4 |
| menu pane +0x5C / +0x64 / +0x66 / +0xAC | pane fields | 16.16 frame / sequence / resource slot / textureOverrides[layer] | CS §8.1 |
| scene script byte +0x14 | logical resource id | not flags at +0x10 | CS §8.1 |
| panes 0x58+side*9+cursor / 0xAE+side / 0xB0+side | card / colour word / name | frame teams<<16 / seq 0x7B / seq 0x82 | CS §8.1 |
| lbl_2_bss_1A8248->unk44F4 / +0x4415 | Challenge special flag / difficulty | >=3 = Special | CS §8.4 |
