# Address lookup (GYQE01 modding): grep an address or symbol name; each row points at the source doc section. Where docs disagree, the later/corrected fact is recorded.

DOL RAM addresses unless prefixed. DOL `.data` file offset = RAM - 0x800E8300 + 0xE5300. Docs: `character_modding_report.md` (CMR), `character_select.md` (CS), `data_map.md` (DM), `modding_roadmap.md` (RM), `character_modding.md` (CM, older).

## 1. DOL tables

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| 0x800E8AA8 | `rel` | 3 REL descriptors: 0 menus, 1 game, 2 challenge (LZSS, in aaaa.dat) | data_map.md §4 |
| 0x800E8AD8 | `boot` | 3 boot files: LZSS 14/5 model, stored binary, small CI4 texarc | data_map.md §4 |
| 0x800E8B08 | `res` | 62 common UI resource descriptors, resource id 0..61 | data_map.md §4 |
| 0x800E8B18 (res+0x10) | `res[1]` | HUD portraits file, slot 0xD per CS (see conflicts); charID c -> texture 30+c | character_select.md §6 |
| 0x800E8BF8 (=lbl_800E8AA8+0x150) | `res[15]` | menu common file: names c<29?c:c+28, mini images 153+c; ZZZZ+0x1A9FE800 | character_select.md §8.2 |
| 0x800E8CD8 (=lbl_800E8AA8+0x230) | `res[29]` | select-grid portraits, charID c -> 4+c; ZZZZ+0x18AEE800 | character_select.md §8.2 |
| 0x800E8558 | `lbl_800E8558` / `characterStaticIndexes` | 54x6 B {family, baseCharID, uniqueIdx, isBase, isCaptain, colourIdx} per charID | character_select.md §1 |
| 0x800E869C | `lbl_800E869C` | 32 B grid index -> base charID (twin of mainCharArray) | character_select.md §1 |
| 0x800E33A0 | music path strings | 15 `snd/my_snd_h/*.adp` paths; order = music track index | data_map.md §4 |
| 0x800EE910 | `game_common` | 5 field/game common files (4 = 23 minigame strings) | data_map.md §4 |
| 0x800EEAAC (0xEBAAC) | `lbl_800EEAAC` | 54 u16 glove/attachment bone-list base (= charID*6 retail) | character_modding_report.md §3 |
| 0x800EEB18 | `lbl_800EEB18` | 54 s16 charID -> model id (variants share base id, -1 none); picks master 486+id event script | data_map.md §4 |
| 0x800EEC40 | `jumptable_800EEC40` | 48-entry per-charID setup switch in fn_80017814 | character_modding_report.md §3 |
| 0x800EEFD0 | `res_dol2` | copy 2 of 62 UI resources; res_dol2[lbl_803CB7CC[stadium]+0x26] = stadium art | data_map.md §4 |
| 0x800EEFD0+0xF0 | `res_dol2[15]` | copy of common-file descriptor | character_select.md §8.3 |
| 0x800EEFD0+0x1D0 | `res_dol2[29]` | copy of grid-portrait descriptor | character_select.md §8.3 |
| 0x800EF508 | `sound` / `lbl_800EF508` | 48 MusyX group descriptors (stored); voice bank = [5+grid] | data_map.md §4 |
| 0x800EFBE8 | `stadium` / `lbl_800EFBE8` | 21 stadium model descriptors, index stadium*3+variant (13 distinct) | data_map.md §4 |
| 0x800EFD38 (0xECD38) | `master` / `lbl_800EFD38` | 515 ARAM master descriptors {flags,0x40000000\|size,blob offset,comp}; blob-relative | data_map.md §4 |
| 0x800EFD38 +[0..32] | master bodies | 33 base body models (not charID-indexed) | data_map.md §4 |
| 0x800EFD38 +[33..53] | master overlays | 21 texture overlays (texarc), via lbl_800F73B8 | character_modding_report.md §3 |
| 0x800EFD38 +[54+charID*7+k] | master sub-items | k0..3 models (hand/glove/bat, 1-seq ANIM at +0x20), k4..6 event scripts | data_map.md §4 |
| 0x800EFD38 +[432+charID] | master track-15 bank | 54 entries; the track-15 ANIM bank (not skeleton) | data_map.md §4 |
| 0x800EFD38 +[486+id] | master event scripts | 29 keyed event scripts, id = lbl_800EEB18[charID]; not stadium objects | data_map.md §4 |
| 0x800F1D68 | `blob` / master[515] | {0,0x4D6600,ZZZZ+0x1A15E800,0x4D6600}, the 4.9 MB ARAM blob | character_modding_report.md §3 |
| 0x800F1D78 (0xEED78) | `lbl_800F1D78` / `subfile` | 54x19x16 B per-character disc subfiles, index charID*19+track | character_modding_report.md §3 |
| 0x800F1D78 track 0 | subfile track 0 | hi-detail body .gpc; == master body (256x256 textures); pre-blob fallback | character_modding_report.md §8 |
| 0x800F1D78 track 1 | subfile track 1 | low-detail body .gpc, same 37 bones, skinFileID 1; both get recoloured | character_modding_report.md §8 |
| 0x800F1D78 tracks 2..14, 16..18 | subfile anim tracks | 16 ANIM banks (SDK ANIMBank); shared within colour families | data_map.md §5 |
| 0x800F1D78 track 15 | subfile track 15 | a 12-sequence ANIM bank (NOT skeleton); fn_80021BBC fallback | data_map.md §5 |
| 0x800F5D98 | `subitem` / `lbl_800F5D98` | 54x6x16 B sub-item disc files, index charID*6+itemSlot (disc path) | character_modding_report.md §3 |
| 0x800F71D8 | `model_script` | 30 per-model event scripts; disc fallback of master 486+id (fn_80021ADC); shrunk to 0x1E0 | data_map.md §4 |
| 0x800F73B8 (0xF43B8) | `lbl_800F73B8` | 54x2 s8 {bodyEntry, overlayEntry or -1} per charID; ARAM in-game path | character_modding_report.md §3 |
| 0x800F7424 | `lbl_800F7424` | 2x6x2 sub-item pair rows {k1,k2} | character_modding_report.md §3 |
| 0x800F743C | `lbl_800F743C` | 54 per-character sub-item row index | character_modding_report.md §3 |
| 0x800F7478 | end of gap_8001E460.c `.data` split | split is 0x800EFBE8..0x800F7478 | character_modding_report.md §6 |
| 0x800FB798 | `lbl_800FB798` | 15x54 s16 per-character animation parameters | character_modding_report.md §8 |
| 0x800FB5B0 | `menu_title` | title/main-menu UI copy (res.30) | data_map.md §4 |
| 0x800FBF10 (+0x214) | `lbl_800FBF10` | u16[33][7] per-grid gameplay row, grid*14+k*2 (fn_8004B284) | character_select.md §6 |
| 0x800FDE84 | `lbl_800FDE84` | 36 u8 roster grid cells -> base charID (0xFF empty); 26 used | character_select.md §1 |
| 0x800FDE60 | `lbl_800FDE60` | per-cell grid draw order | character_select.md §8.1 |
| 0x800FE5D4 | `lbl_800FE5D4` | 12 u8 captain grid {0,1,4,6,2,9,5,17,11,3,10,19} | character_select.md §1 |
| 0x80108B18 | `lbl_80108B18` | announcer sndFX arg table ([0] used by fn_800628D4) | character_select.md §6 |
| 0x80108DB8 | `lbl_80108DB8` / `mainCharArray` | 33 u8 grid index -> base charID | character_select.md §1 |
| 0x80108DDC | `lbl_80108DDC` / `secondaryCharacterArray` | 22 u8 variant charIDs, mapped via jumptable_801091F4 | character_select.md §1 |
| 0x80108DF4 | `lbl_80108DF4` | 33 u16 announcer name SFX ids 0x1C4..0x1E5 per grid index (0x20 = Birdo alt) | character_select.md §6 |
| 0x80108EDC | `lbl_80108EDC` | 9x5 s16 colour-family lists (-1 padded); symbol 0x11C long | character_select.md §1 |
| 0x80109044 | `text_sys` | system text bank, 11 strings, to ARAM | data_map.md §4 |
| 0x801091F4 | `jumptable_801091F4` | variant charID -> base grid index switch in fn_800698F8 | character_select.md §1 |
| 0x801092C8 | `opening` | opening movie set: 0 HVQM4 82 MB, 1 data, 2 UI (= res.34) | data_map.md §4 |
| 0x80109AE8 (+unique*0x64) | `lbl_80109AE8` | records/star screen rows, keyed by unique (isBase only) | character_select.md §6 |
| 0x8023D6C0 | `lbl_8023D6C0` | menu logical resource-id table (fn_80034F50 resolves scene byte +0x14) | character_select.md §8.1; modding_roadmap.md R1 |
| 0x803CB790 (sdata) | `lbl_803CB790` | pointer to runtime subfile table | character_modding_report.md §3 |
| 0x803CB7E0 (sdata) | `lbl_803CB7E0` | 4 u16 master tier counts {54,378,54,29} | character_modding_report.md §3 |
| 0x803CB7CC (sdata) | `lbl_803CB7CC` | {0..6} stadium -> res offset (res 38..44 = stadium art) | data_map.md §4 |
| 0x803CB748 (sdata) | `lbl_803CB748` | 6 u8 unique idx needing unlock (fn_80024C04, fn_2_348C) | character_select.md §1 |
| 0x8034E9A0 (.bss) | `lbl_8034E9A0` / `Static_Stats_Tables` | 54x0xA0 CharacterStats, loaded from ZZZZ+0x6CF8800; roster state follows | character_select.md §1 |
| 0x8034E9A0+0x4757 | `charsOnCharacterGridSelected` | 54 u8 per-charID taken flags | character_select.md §1 |
| 0x8036E548 | `g_hugeAnimStruct` | 0x3154-byte animation/actor struct | CLAUDE.md (not in these docs); character_modding_report.md §1 |
| 0x803716B8 | `lbl_803716B8` | load-queue state (ARAM addrs, ring, flags) | character_modding.md §1.3 |
| 0x80118220 | `lbl_80118220` | 13 model objects x 0x64 bytes, stadium/model object buffers | character_modding.md §1.2 |
| 0x80001840 | OS low memory | NOT a DOL table; fork's batting-style hook was an emulator poke | character_modding_report.md §5 |

## 2. DOL functions

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_80017098 | load request | request character load / reuse slot (entry point); MATCH | character_modding_report.md §2 |
| fn_8001758C | slot record + track pick | fills slot, track = charID*19+(variant==0), body load; MATCH | character_modding_report.md §2 |
| fn_8002204C | body model loader | body-item pair -> master descriptor, else disc track 0; MATCH | character_modding_report.md §2 |
| fn_80021CA4 | sub-item pair loader | bat/glove pair loader using lbl_800F743C/7424/5D98; MATCH | character_modding_report.md §2 |
| fn_80021BBC | track-15 bank loader | master 432+charID else subfile track 15; charID<0x36; MATCH | character_modding_report.md §2 |
| fn_8002244C | sub-item queue callback | packedID=charID<<16\|itemID, chains 2nd sub-item; MATCH | character_modding_report.md §2 |
| fn_8002254C | overlay loader | decompresses master[overlay] over body texture archive (block+root->texture) | character_modding_report.md §3 |
| fn_80022620 / fn_80022634 | load completion cb | queue completion callbacks | character_modding.md §1.3 |
| fn_80022CB4 | queue descriptor | ring of 18 records in lbl_803716B8 | character_modding.md §1.3 |
| fn_800227E4 | ARAM blob streamer | allocs hard-coded 0x4D6600 (0x800227EC/F4), streams master[515] | data_map.md §2 |
| fn_80021ADC | event script loader | master 486+modelID (id<0x1D), disc fallback model_script | data_map.md §4 |
| fn_8002399C | actor slot init | calls f_InitActorWithLayout; MATCH | character_modding_report.md §2 |
| f_InitActorWithLayout (0x800232E0) | actor builder | carve actor/skin/bones; crash 0x800233A0 if skinFileID>=numDescriptors; 98 diff lines | character_modding_report.md §2 |
| fn_80016344 | per-slot state machine | anim banks, model map, stadium obj; 33 diff lines | character_modding_report.md §2 |
| fn_80016710 | fielder state machine | same as fn_80016344; 32 diff lines | character_modding_report.md §2 |
| fn_80016B60 | streams 5 anim banks | tracks 4/12/5/2/16; MATCH | character_modding_report.md §2 |
| fn_80016F7C | drives fn_80016B60 | slots 0..3; MATCH | character_modding_report.md §2 |
| fn_80017814 | root relocation | texture bind, actor build, bone map, jumptable switch; 54 diff lines | character_modding_report.md §2 |
| fn_800BD190 | bind textures to geo | texture-swap hook (geo, tex) | character_modding_report.md §1 |
| convertTextureHeader (0x800C0770) | texture offset fixup | MATCH | character_modding_report.md §2 |
| LoadGeoPalette (0x800BCB44) | geo palette fixup | MATCH | character_modding_report.md §2 |
| DecompressDiskData (0x800A6654) | LZSS expansion | bit 30 of size word = compressed; 31 diff lines | character_modding_report.md §2 |
| fn_80012B90 | bat/glove loader | 3 pairs x 2 models; first decompile (0xAF0), unmatched | character_modding_report.md §2 |
| fn_80013680 | mode-2 bat/glove loader | cache + bone attach; first decompile (0xB84) | character_modding_report.md §2 |
| fn_800638B4 | DK setup | jumptable case charID 2 | character_modding.md §1.3 |
| fn_80063010 | Magikoopa setup | cases 33..36 | character_modding.md §1.3 |
| fn_8004B7B4 | setup case 19 | per-charID switch | character_modding.md §1.3 |
| fn_800637BC | setup 20/43 | paratroopas | character_modding.md §1.3 |
| fn_800637D4 + fn_8004BD6C | setup 41 | Paragoomba; 38 also uses fn_8004BD6C | character_modding.md §1.3 |
| fn_80052634 | setup 14/37 | per-charID switch | character_modding.md §1.3 |
| fn_80062ED4 | setup 16/44..47 | shy guys | character_modding.md §1.3 |
| fn_800698F8 | findCharacterID | charID -> grid/unique index; decompiled, 24 diffs; patched by --ui source | character_select.md §5 |
| fn_800628D4 | announcer call-out | sets useAltBirdoGrid, plays lbl_80108DF4[grid]; MATCH | character_select.md §6 |
| fn_80067AC8 | family column lookup | row[column] of lbl_80108EDC or -1; MATCH | character_select.md §2 |
| fn_80067B40 | family taken-flag writer | value to every family member unless mode 2; 8 register diffs | character_select.md §5 |
| fn_80067C48 | chemistry ranking | sorts ids by chemistry into lbl_8034E9A0+0x478D+idx*54; stub | character_select.md §2 |
| fn_80067F70 | CPU auto-pick | random from top 20 ranked free ids, marks family taken; stub | character_select.md §2 |
| fn_800415A8 | CPU team builder | tries family columns 1..4 (0xAD4) | character_select.md §5 |
| fn_800506E8 | cell badge writer | lbl_803C6028.slots[cell] by base charID; MATCH | character_select.md §2 |
| fn_8004E504 / fn_8004E5B4 | captain grid | MATCH | character_select.md §2 |
| fn_8004D460 / fn_8004D4F0 | other grid set | MATCH | character_select.md §2 |
| fn_80024C04 | unlock check | reads lbl_803CB748; MATCH | character_select.md §1 |
| fn_800625A4 | request menu command | writes lbl_803C66B0.flags5D[side] only | character_select.md §8.1 |
| fn_80051D00 | build DOL grid scene | cell -> lbl_800FDE84; resource 9 / seq 0x19; non-matching C | character_select.md §8.1 |
| fn_800363D8 | set pane texture | (scene,pane,layer,seq,frame); MATCH | character_select.md §8.1 |
| fn_80035838 | UI resource loader | (desc, logical slot) | character_select.md §6 |
| fn_80035B50 | find UI slot | by id | character_select.md §6 |
| fn_80034F50 | resolve resource id | through lbl_8023D6C0 | character_select.md §8.1 |
| fn_8000CEF0 | sprite query decoder | complete C, non-matching; records descending frame order | character_select.md §8.2 |
| fn_8000D838 / fn_8000D164 | sprite rendering | drive sprite draw | character_select.md §8.2 |
| fn_8000BA3C | packed-bank traversal | nested sequence index at 0x8000C104..C13C | character_select.md §8.4 |
| fn_8004B284 | per-grid gameplay row | lbl_800FBF10+0x214 | character_select.md §6 |
| fn_800216F8 / fn_80021518 | voice bank load | sndPushGroup path (lbl_800EF508[5+grid]) | character_select.md §6 |
| fn_800215F8 / fn_80021758 | sound group loaders | table `sound` | data_map.md §4 |
| fn_80020278 / fn_80020388 | res_dol2 loaders | fn_80020388 loads res_dol2[stadium+0x26] into slot 0xD | data_map.md §4 |
| fn_800188C0 | game_common loader | table 0x800EE910 | data_map.md §4 |
| fn_800097A0 | boot state machine | switches current file aaaa.dat / ZZZZ.dat; loads RELs | data_map.md §2 |
| ARAMTransfer / DVDFastOpen / DVDReadAsyncPrio | disc read path | 0x8000-byte chunks to staging buffer | data_map.md §2 |
| fn_800A6E24 / fn_800A6D10 | sNp HVQM4 player | movie streaming | data_map.md §2 |
| fn_800697B0 / fn_8006AF9C / fn_8004A1BC | text_sys / opening / menu_title loaders | per descriptor tables | data_map.md §4 |
| fn_80011CA8, LoadModel, fn_80014204, fn_800145F8, fn_8001D180 | glove-table readers | read lbl_800EEAAC[unk252*2] | character_modding.md §1.2 |
| fn_8001500C, fn_8001594C, fn_80019C00, fn_8001A3FC | model-map readers | read lbl_800EEB18[charID*2] | character_modding.md §1.2 |
| fn_800B2B74 / fn_800B2B54 / fn_800B2BA8 / fn_800B2C08 / fn_800BD548 / fn_8001FC4C | fn_80017814 bone setup calls | ids 19/25/36, 3/2/1/46 | character_modding.md §1.3 |
| fn_80064918 | charID -> category switch | 0..51 range | character_select.md §4 |
| fn_800671FC / fn_800649BC / fn_800678CC / fn_80069854 / fn_80050138 / fn_80050FE8 | roster rebuild helpers | called from fn_2_2FC0 / fn_2_7DDC | character_select.md §5 |
| fn_800675C4, fn_8006CDC0 | grid / records readers | | character_select.md §6 |

## 3. menus.rel (fn_2_* / lbl_2_*)

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_2_554 | stats loader (boot) | loads CharacterStats from ZZZZ+0x6CF8800 | data_map.md §4 |
| fn_2_2FC0 | roster rebuild | (mode, finish, rebuild); taken flags, locked uniques, auto-pick; MATCH | character_select.md §5 |
| fn_2_348C | locked-unique loop | taken[c]=locked per lbl_803CB748; MATCH | character_select.md §5 |
| fn_2_3624 | colour cycle / cursor | roster pick logic; 5 scheduling lines left | modding_roadmap.md Phase 1 |
| fn_2_4970 | undo pick | (side, captainID) B-button path; MATCH | character_select.md §5 |
| fn_2_7DDC | open roster screen | clears taken flags, sets cursors, gridPick; MATCH | character_select.md §5 |
| fn_2_DFAC | confirm pick | teams[side][slot]=charID, request 0xF; MATCH | character_select.md §8.1 |
| fn_2_C698 | markSlotTaken | charTaken=1, badge, family taken; MATCH | modding_roadmap.md Phase 1 |
| fn_2_1C34 | button switch | A=0x1B8, B=0x1B9, dirs=0x1B7; MATCH | character_select.md §8.1 |
| fn_2_102C8 | random fill | strategies FCB4/FAA0/F200; non-matching C | character_select.md §8.1 |
| fn_2_5444 | ready handler | challenge lineup copy, sends 0x13; non-matching C | character_select.md §8.1 |
| fn_2_7265C | open grid | scans characterFlags; MATCH | character_select.md §8.1 |
| fn_2_7F8BC | command 0xF | card anim, pane 0x58+side*9+cursor frame teams<<16 | character_select.md §8.1 |
| fn_2_75BE4 | chemistry stars | thresholds 15/35/55/70 | character_select.md §8.1 |
| fn_2_7DAB8 | command 0xE | roster focus anim | character_select.md §8.1 |
| fn_2_74F40 | name/stat preview | name pane 0xB0+side seq 0x82, mini 0x83, frame=charID | character_select.md §8.1 |
| fn_2_776A0 | per-pad maintenance | consumes L-colour unk50, writes mini image frame | character_select.md §8.1 |
| fn_2_81628 | roster scene update cb | command consumer; jumptable_2_data_2D920 cmds 9..0x1D | character_select.md §8.1 |
| fn_2_8279C | roster scene create | script lbl_2_data_2B59C | character_select.md §8.1 |
| fn_2_7AE3C | initial roster population | uses mini-image frame=charID | character_select.md §8.1 |
| fn_2_3204 / fn_2_8ED4C | fn_2_2FC0 callers | (mode,1,1) / (9,0,1) | character_select.md §5 |
| fn_2_86EC / fn_2_CCBC / fn_2_110B0 | fn_2_7DDC callers | | character_select.md §5 |
| fn_2_CE44 | B-button path | calls fn_2_4970 | character_select.md §5 |
| fn_2_12A70 | captain pick | calls fn_800628D4 | character_select.md §6 |
| fn_2_1C860, fn_2_45204, fn_2_454E8 | records/star screens | lbl_80109AE8 + unique*0x64 | character_select.md §6 |
| fn_2_4EB2C / fn_2_5ED3C | small portraits | slots 0x15 / 0xA, unique-keyed | character_select.md §6 |
| fn_2_4E970 / fn_2_4EABC | Challenge UI loaders | slot 0x17: ending archive / Challenge scene | character_select.md §8.4 |
| fn_2_1B7B4 | Challenge special transition | load path 0x1BAEC..0x1BB1C, difficulty +0x4415>=3 | character_select.md §8.4 |
| fn_2_2587C | pane1 callback | ending pane; MATCH | character_select.md §8.4 |
| fn_2_24238 / fn_2_2460C | ending scene | script lbl_2_data_1059C, callbacks lbl_2_data_105FC | character_select.md §8.4 |
| fn_2_8DB14 | menu scene select | by lbl_2_bss_1A824C->unk7746 - 0x19 | data_map.md §7 |
| fn_2_17C88 / 17ED8 / 18148 / 188EC | menu_char_a users | per-charID 3D scene A | data_map.md §4 |
| fn_2_47540 / 477C0 / 478F4 / 481F4 | menu_char_b users | per-charID 3D scene B | data_map.md §4 |
| menus .data+0xC8 | `stats` | CharacterStats block (ZZZZ+0x6CF8800), 54x0xA0 + 0x2520 tail | data_map.md §4 |
| menus .data+0x444 | `menu_set` | 16-slot menu resource set (slot 1 = grid portraits); 8 copies | data_map.md §4 |
| menus .data+0x454 / 0xD24 / 0x1324 / 0x18C4 / 0x2A9C4 / 0x2B3EC / 0x2E1FC / 0x302CC | grid descriptor copies | 8 listed, 9 found (one more) | character_select.md §8.3 |
| menus .data+0x2B3DC | `menu_set_g` | character-select resource set (fn_2_73994/760CC/7BFF8) | data_map.md §4 |
| menus .data+0x241C | `menu_char_a` | 54 per-charID menu 3D scenes | data_map.md §4 |
| menus .data+0x12EC0 | `menu_char_b` | 54-row copy of A | data_map.md §4 |
| menus .data+0x12170 | `movie` | 2 HVQM4 movies | data_map.md §4 |
| menus .data+0x12298 | `text_menu` | 954-string menu text bank | data_map.md §4 |
| menus .data+0x1F884 / 0x1FF84 / 0x20BF0 | menu sets | UI pair / options+records (599 strings) / lineup | data_map.md §4 |
| menus .data+0x132DC | `lbl_2_data_132DC` | Challenge ending archive descriptor, ZZZZ+0x19135800 | character_select.md §8.4 |
| menus .data+0x1326C | `lbl_2_data_1326C` | Challenge scene UI, ZZZZ+0x18E92800 (slot 0x17 reused) | character_select.md §8.4 |
| menus .data+0x1323C | `challenge_ui` | 11 Challenge UI resources | data_map.md §4 |
| menus .data+0x2F990 | `menu_scene_2f990` | 67 menu 3D scene models | data_map.md §4 |
| jumptable_2_data_2D844 | colour-word jumptable | 42 entries charIDs 12..53, R_PPC_ADDR32 addends; li r0,N at 0x7556C+8*(N-1), label 0 at 0x7559C | character_select.md §8.3 |
| menus .text 0x7556C..0x7559C | colour-word switch | pane 0xAE seq 0x7B labels 0..6 | character_select.md §8.3 |
| lbl_2_data_2D920 | jumptable_2_data_2D920 | commands 9..0x1D in fn_2_81628 | character_select.md §8.1 |
| lbl_2_bss_F468 | cursor/flags37/flags3D | roster cursor[side], pick-pending bytes | character_select.md §5 |
| lbl_2_bss_F410 | gridPick[side] | cached grid pick | character_select.md §5 |
| 0x5A818 / aaaa+0x800 | menus.rel packed | 0x5A818 B packed; re-packed in place (355584 B in room 372736) | data_map.md §3; character_select.md §8.3 |

## 4. game.rel (fn_3_* / lbl_3_*)

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| fn_3_B4124 / fn_3_10C450 | roster -> inMemRoster | memcpy(&lbl_8034E9A0[charId], 0xA0); skin byte lands here | character_select.md §2 |
| fn_3_5EC0 | stadium relocation | 16-word stadium root loader | data_map.md §2 |
| fn_3_64DC | stadium loader copy | stadium_game table | data_map.md §4 |
| manageStadiumLoading | stadium loader | reads lbl_800EFBE8[unk9*3+unkA] | data_map.md §4 |
| fn_3_6B4C8 / fn_3_6B5D8 / fn_3_10C81C | fn_80016344 callers | | character_modding.md §1.3 |
| fn_3_90220 | voice SFX base | game .data+0x8168 | character_select.md §1 |
| fn_3_90F48 / fn_3_90B14 / fn_3_5A28C | voice bank loaders | fn_800216F8(grid+5), lbl_3_data_8148[grid] | character_select.md §6 |
| fn_3_91D1C | HUD card pane | pane->unk5C = CharID<<16 (+ EA340, EAEF4, EB6E0, 11F02C, 121304, 127B68) | character_select.md §6 |
| fn_3_10CC20 / fn_3_B49D4 | announcer callers | batter/pitcher intro | character_select.md §6 |
| fn_3_59F40 / fn_3_5A28C | game_set loaders | slot 0x14 portraits | data_map.md §4 |
| fn_3_5BD40 | HUD portraits loader | lbl_3_data_6130[1] into slot 0xC | data_map.md §4 |
| fn_3_AF10C | res loader | lbl_3_data_F538[2] into slot 0x13 | data_map.md §4 |
| fn_3_B43E8 | results loader | game_res_c | data_map.md §4 |
| fn_3_B9BB4 | field object sets | stores ARAMTransfer(&lbl_3_data_10ACC[stadium]) in stadiumObjectLoadingPtr | data_map.md §4 |
| fn_3_10B8D0 / 10F3D8 / 10FDC8 | minigame loaders | minigame_res [minigame+6] | data_map.md §4 |
| fn_3_BF878 / fn_3_BEFF8 / fn_3_106E50 / fn_3_1665E4 | misc loaders | model42 / 44-section / camera / results text | data_map.md §4 |
| game .data+0x0 | `stats_game` | CharacterStats block copy (maybeProcessTeamData) | data_map.md §4 |
| game .data+0x7EC | `stadium_game` | 21 stadium descriptors | data_map.md §4 |
| game .data (section 5) +0x8168 | voice base | 54 u16 per charID | character_modding_report.md §8 |
| game .data+0x8148 | `lbl_3_data_8148` | voice group ids, 33 entries | character_select.md §6 |
| game .data+0x6EF8 | BatterHitbox table | charID-indexed | character_modding_report.md §8 |
| game .data+0x7690 | charge frames | charID-indexed | character_modding_report.md §8 |
| game .data+0x7870 | runner timing | charID-indexed | character_modding_report.md §8 |
| game .data+0x7E34 / 0x17000 | per-charID tables | meaning unnamed (R3) | character_modding_report.md §8 |
| game .data+0x76FC (unique*3) | `lbl_3_data_76FC` | gameplay check by kind (rep_1200) | character_select.md §6 |
| game .data+0x3D60 (+0x70, +0xF0, +0x1D0) | `game_set` | 69 rows; +0x70 lineup portraits; +0xF0 common copy; +0x1D0 grid copy | data_map.md §4; character_select.md §8.3 |
| game .data+0x6130 / 0xF538 / 0x10578(0x10598) / 0x21EC8 | UI resource copies | +0x10 HUD, +0xF0 common, +0x1D0 grid descriptor | character_select.md §8.3 |
| game .data+0x10ACC | `field` | 7 per-stadium field object sets | data_map.md §4 |
| game .data+0x11380 / 0x115EC / 0x20FDC | model42 / 44-section / camera | | data_map.md §4 |
| game .data+0x225F0 / 0x284E8 | actor/text sets | | data_map.md §4 |
| game.rel aaaa+0x5B800 | game.rel packed | 0xF4450 packed; 0x3B0 slack before challenge.rel | data_map.md §3 |

## 5. challenge.rel

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| challenge .data+0x0 | `field_ch` | 7 field sets copy (fn_1_1538) | data_map.md §4 |
| challenge .data+0x8D0 / 0x10518 / 0x10674 | stadium copies | 21 rows each (fn_1_73B8 / 2004C / 1DCE4) | data_map.md §4 |
| challenge .data+0xB70 | `menu_title_ch` | title UI copy | data_map.md §4 |
| challenge .data+0xF0C | `challenge_map_ui` | 11 map UI pieces | data_map.md §4 |
| challenge .data+0xAC | music track index | 15 rows as if concatenated .adp; loader fn_1_1E0; not a file table | data_map.md §4 |
| challenge .data+0x196C | `sound_ch` | 50-row MusyX copy (fn_1_9F04) | data_map.md §4 |
| challenge .data+0xA3D8 | `challenge_board` | 86 rows: 0..1 game_common, 2..31 model_script, 32..85 pieces | data_map.md §4 |
| challenge .data+0xA940 / 0xA950 / 0xADE0 | partial_ch / scene / model42 | header read 0x200 of 0x15450 B file (fn_1_10560) | data_map.md §4 |
| challenge .data+0xF968 | `challenge_models` | 24 map models (fn_1_1CBE4) | data_map.md §4 |
| challenge .data+0xFB98 | `debug_browser` | 63-row sprite debug browser; [0] = ending archive (fn_1_267F4) | character_select.md §8.4 |
| challenge .data+0x104F4 / 0x108F8 / 0x112D8 | small file / model42 / movie viewer | | data_map.md §4 |
| challenge .data+0x41818 (file off) | common-file descriptor copy x1 | updated when common file moves | character_select.md §8.3 |
| challenge .data+0x418F8 (file off) | grid-file descriptor copy x1 | updated when grid file moves | character_select.md §8.3 |
| aaaa+0x150000 | challenge.rel packed | 0x271C0 packed | data_map.md §3 |

## 6. ZZZZ.dat / aaaa.dat files

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| DiskFileDesc (16 B BE) | {flags,sizeWord,offset,packed} | flags 0=stored else (repeat<<8)\|lookback (0x40B); size bit30=LZSS; offset 0x800-aligned (0x20 in blob) | data_map.md §2 |
| ZZZZ+0x00000000..0x12000 | gap | 3 stored CMPR texarcs, unused | data_map.md §3 |
| ZZZZ+0x12000 | opening movie | 82 MB HVQM4, stored | data_map.md §1 |
| ZZZZ+0x06C96000 / 0x06CC3000 / 0x18D43800 | res 34..36 | 640x448 opening stills | data_map.md §4 |
| ZZZZ+0x06CF8800 | CharacterStats | 54x0xA0 stats (stored) + 0x2520 tail; edit in place | character_modding_report.md §8 |
| ZZZZ+0x08F2E800..0x09438800 | gap | 5 MB, AdGCForm header, not loaded | data_map.md §3 |
| ZZZZ+0x0B95C800.. | Pianta rows | slot21 t0 0B95C800 t1 0B96D800; t2 0B977800 t3 0B9AF000 t15 0BAD6800 shared | character_modding.md §1.4 |
| ZZZZ+0x0BB0F000 / 0BB1F000 / 0BB29000 / 0BB39000 | Pianta R/Y t0/t1 | slot22 t0/t1, slot23 t0/t1 | character_modding.md §1.4 |
| ZZZZ+0x0CE16800..0x0E581000 | gap | 23.4 MB LZSS-looking, stale | data_map.md §3 |
| ZZZZ+0x0E97A800 | res 16 | 144 captain banner textures 153x54 | data_map.md §4 |
| ZZZZ+0x0EA16800.. | res 17..28 | 12 captain/team emblem sets | data_map.md §4 |
| ZZZZ+0x0EAE4000..0xEAF7000 | gap | 76 KB between Challenge map UI and menu models | data_map.md §3 |
| ZZZZ+0x0F12C800..0x186A1800 | gap | 149.8 MB dense stale data | data_map.md §3 |
| ZZZZ+0x18AC5000..0x18AC7000 | gap | 8 KB tail after Challenge partial file | data_map.md §3 |
| ZZZZ+0x18AEE800 | res 29 grid portraits | 202 textures, 54x50x50 CI8 + RGB5A3 TLUT; c->4+c; unavailable 54->118; unpacked 0xADFFC packed 0x4BAB0 | character_select.md §8.2 |
| ZZZZ+0x18B3A800 | res 30 | title/main menu, 122 textures, 3.6 MB | data_map.md §4 |
| ZZZZ+0x18E92800 | Challenge scene UI | lbl_2_data_1326C target | character_select.md §8.4 |
| ZZZZ+0x18ED3800 | res 31 | records/options UI | data_map.md §4 |
| ZZZZ+0x18ED7000 | res 5 | 180 textures; unique u -> 53+u (32 CI8 50x50 at 53..84) | character_select.md §6 |
| ZZZZ+0x18F0E000 / 0x191B8800 | res 32 / 33 | UI / menu_set slot 2 | data_map.md §4 |
| ZZZZ+0x19135800 | Challenge ending archive | unpacked 0x23491C packed 0x82928, 427 textures, 101 seqs; not charID-keyed | character_select.md §8.4 |
| ZZZZ+0x19A6F800..0x1A15E800 | gap | 6.9 MB, five AdGCForm containers | data_map.md §3 |
| ZZZZ+0x1A15E800 | ARAM blob | 0x4D6600 B; 345 members; move + patch master[515] and 0x800227EC/F4 to grow | data_map.md §2 |
| ZZZZ+0x1A635000 | res 0 | in-game HUD, 369 textures | data_map.md §4 |
| ZZZZ+0x1A6B3000 | res 1 HUD card | 102 textures; CI8 50x50 + TLUT at 30..83 = charID 0..53; unpacked slot 136224 B | character_select.md §6 |
| ZZZZ+0x1A6D4800 / 0x1A6E8000 / 0x1A748800 | res 2 / 3 / 4 | game.rel slot 0x13 / large UI / 88 textures | data_map.md §4 |
| ZZZZ+0x1A769800.. | res 6..13 | 8 full-screen 640x448 screens | data_map.md §4 |
| ZZZZ+0x1A9E3800 | res 14 | 69 textures | data_map.md §4 |
| ZZZZ+0x1A9FE800 | res 15 common menu file | unpacked 0x106568 packed 0x68C10; 440 textures; slot 1 | character_select.md §8.2 |
| ZZZZ+0x1A9FE800 name index | roster preview name | seq 0x82: c<29 ? c : c+28; 111x18 CI4, shared RGB565 16-entry TLUT | character_select.md §8.2 |
| ZZZZ+0x1A9FE800 mini index | roster mini image | seq 0x83: 153+c; 52x60 CI8, RGB5A3 TLUT; 54 placeholder -> 434; 48 buffers for 54 images | character_select.md §8.2 |
| ZZZZ+0x1AA67800 / 0x1AA74800.. / 0x1AA81000.. | res 37 / 38..44 / 45..61 | strips / stadium art (38+stadium) / 17 stills 640x256 CI8 | data_map.md §4 |
| ZZZZ+0x6CFD000 | MarioStadium | enumDiskLocations.MarioStadium, stadium row 0 | data_map.md §4 |
| ZZZZ end -0x5C0 | unreferenced tail | appending to ZZZZ.dat is safe; FST rebuilt by Dolphin | character_modding_report.md §8 |
| aaaa+0x0..0x800 | header | unreferenced u16 pairs, never read | data_map.md §3 |
| aaaa+0x800 / 0x5B800 / 0x150000 | menus / game / challenge .rel | packed RELs | data_map.md §3 |
| .gpc root | {texture 0x20, layout, geo, skin, extra} | 8-word header; TextureArchiveHeader at 0x20; CMPR for characters | data_map.md §2 |
| donkey00.gpc 0x180..0x4F00 | DK textures | 10 textures; recolour CMPR endpoints only; unverified vs disc | character_modding_report.md §4a |
| overlay file | texarc at +0x20 of body | length == layoutOff-0x20; written at body+0x20 | character_modding_report.md §8 |
| master[13]/master[34] | BlueToad body/overlay | track0(BlueToad)==master[13] + master[34] at +0x20; pair {13,34} | character_modding_report.md §8 |
| master[29] size 0x18028 vs body 13 size 0x195B0 | size < body | harmless; do not resize; only used if buf==NULL | character_modding_report.md §8 |
| master[44] size 0x5BE0 vs body 0x16320 | same | BlueShyGuy | character_modding_report.md §8 |
| lbl_800F73B8[41] | Paragoomba | {29,-1} | character_modding_report.md §3 |
| ANIM bank | `anim` | ANIMBank version 0x007B7960, sequences 0xC each | data_map.md §5 |
| UI file | `ui` | MenuUiFileHeader {texarc @0x20, sprite bank}; bank+8 -> seq table | data_map.md §5; character_select.md §8.2 |
| text bank | `text` | {u16 count,u16 0x0131,u32 offsets[]}, u16 glyphs end 0x4000 | data_map.md §5 |
| musyx group | `musyx` | {0x20,size}x4 chunks proj/pool/sdir/samp; group id u16 at +0x24 | data_map.md §5 |
| text banks (5) | text_menu.0, menu_1ff84.1, game_284e8.0, game_common.4, text_sys.0 | export/import lossless | data_map.md §6 |
| sound rows 5..22 | voice groups | 18-sample groups ids 27..10, probably per-character voices | data_map.md §5 |
| LZSS 11/4 | flags 0x40B | 1,492 files; 1 file LZSS 14/5 (0x50E); 78 stored | data_map.md §1 |
| coverage | referenced 56.61% / gaps 43.10% | 194 MB in 7 gaps free for --reuse-gaps; retail ISO 1,459,978,240 B | data_map.md §3 |

## 7. Struct fields that matter for modding

| Address / offset | Name | Meaning | Where documented |
|---|---|---|---|
| inMemRoster[team][slot].stats.CharID @ +0x24 | CharacterStats.CharID | s16 per-player charID | character_modding_report.md §1 |
| CharacterStats size 0xA0 | CharacterStats | 54 rows; copied per roster entry | character_select.md §1 |
| CharacterStats +0x37/+0x38/+0x39/+0x3A | display ratings | batting, pitching, running, fielding (not texture ids) | character_select.md §8.1 |
| CharacterStats +0x3B.. | chemistry row | 54 bytes | character_select.md §2 |
| StatTable.UnusedBytes[0] @ +0x05 | skin byte home | per-charID row shared by all copies; NOT per roster entry | character_modding_report.md §9 |
| AnimationStruct.charID @ 0x252 | actor charID | s8 | character_modding_report.md §1 |
| AnimationStruct._rest253 @ 0x253 | spare byte | planned skin copy | character_modding_report.md §4c |
| AnimationStruct.slotKind @ 0x254 | role index | 9 = batter | character_modding.md §1.1 |
| AnimationStruct @ 0x255 | memory block index | passed to fn_8002399C | character_modding.md §1.3 |
| AnimationStruct.team/player @ 0x256/0x257 | team, roster slot | proposed skin derivation by counting earlier duplicates | character_modding_report.md §9 |
| AnimationStruct.variant @ 0x259 | variant arg | fn_8001758C; every caller passes 1 (ARAM path) | character_modding_report.md §8 |
| AnimationStruct @ 0x25A/0x25B | arm / stance | copied from roster bytes 0x26/0x27 | character_modding.md §1.3 |
| AnimationStruct.isBatter @ 0x278 | batter flag | slotKind==9 | character_modding.md §1.3 |
| AnimationStruct.boneIndices @ 0x162 | 120 u16 | boneID -> actor bone idx, 0xFFFF absent | character_modding_report.md §1 |
| AnimationStruct 0x25D..0x273, ids 0x60..0x6E | flags / anim ids | reset in fn_80017814 | character_modding.md §1.3 |
| g_hugeAnimStruct 0x2D54 / 0x2D3C (keys 0x2D5C / 0x2D44) | cached batter / fielder model | memcpy'd by fn_8001758C | character_modding_report.md §1 |
| g_hugeAnimStruct.loadState @ 0x2D77 | load state | fn_80016344/710 state machine 2..5 | character_modding.md §1.3 |
| g_hugeAnimStruct 0x2C50 / 0x2D7F / 0x2D8D | slotPtrs / loadedCharID / cleared | per-slot | character_modding.md §1.3 |
| g_hugeAnimStruct 0x2CAC / 0x2CBC / 0x2CFC+slot*0x14 | shared / batter / slot anim banks | sharedAnimBank, batterAnimBank, slotBanks | character_modding.md §1.3 |
| g_hugeAnimStruct.stadiumObjectLoadingPtr | field set pointer | set by fn_3_B9BB4 | data_map.md §4 |
| ActorSlot.stadiumObj @ +0x2C | model-object ptr | set after fn_80025FFC | character_modding.md §1.3 |
| lbl_803716B8.unk1EA bit0 / bit1 | bodies / skeletons in ARAM | blob callback ORs 0xF | character_modding.md §1.3; character_modding_report.md §8 |
| lbl_803716B8.bodyAramAddrs/skeletonAramAddrs/subItemAramAddrs | per-tier ARAM addresses | aramBase+master[i].offset | character_modding_report.md §8 |
| lbl_803716B8.unk1E8 / loadBusy / current | queue state | 1 when body queued; busy flag; ring current | character_modding.md §1.3 |
| .gpc root words 0x00/04/08/0C/10 | texture/layout/geo/skin/extra | each += base if nonzero; chain stops at zero | character_modding.md §1.3 |
| TextureArchiveHeader | {u16 count,u16 0,TextureHeader[count]} | offsets relative to archive start | character_modding.md §1.3 |
| TextureHeader (0x20 B) | texture header | +0 pixel off, +4 clut off, +8 h, +0xA w, +0x17 GX fmt, +0x18 pal count, +0x1A TLUT fmt | character_select.md §8.2 |
| ActLayout.skinFileID | skin lookup | >= numDescriptors -> NULL deref at 0x800233A0 | character_modding_report.md §5 |
| lbl_8034E9A0.useAltBirdoGrid @ 0x48AE | Birdo alt flag | | character_select.md §5 |
| lbl_8034E9A0 +0x46E0 / +0x46E4 | player picks | marked taken in fn_2_2FC0 | character_select.md §5 |
| lbl_8034E9A0 +0x478D + idx*54 | chemistry-ranked ids | per player | character_select.md §2 |
| lbl_803C6724 [idx*9+2] / .order[side][k] | selected / pick order | roster order bytes | character_select.md §2 |
| lbl_803C6028.slots[cell] | grid pick badge | controller index or -1, by base charID | character_select.md §5 |
| lbl_803C66B0.flags5D[side] | menu command flag | | character_select.md §8.1 |
| lbl_803297E0.mode | menu mode | fn_2_2FC0 key | character_select.md §5 |
| lbl_80361B20.characterFlags | per-char flags | transition1/2 scan | character_select.md §8.1 |
| g_d_GameSettings.charUnlocked @ 0x1A..0x1F | unlock bytes | 6 locked uniques | character_select.md §5 |
| g_d_GameSettings.unk9 / unkA | stadium / variant | index stadium*3+variant | data_map.md §4 |
| menu pane +0x5C / +0x64 / +0x66 / +0xAC | pane fields | 16.16 frame / sequence / resource slot / textureOverrides[layer] | character_select.md §8.1 |
| scene script byte +0x14 | logical resource id | not flags at +0x10 | character_select.md §8.1 |
| panes 0x58+side*9+cursor / 0xAE+side / 0xB0+side | card / colour word / name | frame teams<<16 / seq 0x7B / seq 0x82 | character_select.md §8.1 |
| lbl_2_bss_1A8248->unk44F4 / +0x4415 | Challenge special flag / difficulty | >=3 = Special | character_select.md §8.4 |
