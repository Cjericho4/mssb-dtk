# Skin picker trace (mssb-modding #3, Codex 2026-10-27, static trace)

Research only, USA GYQE01 Rev 0. No source/include/config edits. Confidence: M=matched C or direct table; A=asm or documented m2c trace; I=design inference awaiting runtime test. DOL addresses are RAM; fn_2_ is menus.rel offset, fn_3_ is game.rel offset. Evidence sources: .agent/roster_flow.md, character_modding_report.md, character_select.md, stats.md, sounds.md, data_map.md, animations.md; mssb-modding/tools/clonemaker/core/src/{constants.rs,clone.rs}.

## Summary and recommended hook

Use fn_8001758C @0x8001758C state 0 to read a per-player skin byte beside the existing inMemRoster arm/stance reads. Keep the real charID for stats, chemistry, animations and gameplay. Store the skin in anim slot +0x253. Redirect BOTH body routes: variant 1 calls fn_8002204C @0x8002204C, selecting the ARAM body/overlay pair at lbl_800F73B8 @0x800F73B8; variant 0 selects disc track charID*19+1 at lbl_800F1D78 @0x800F1D78. Batter/menu/cutscene are variant 1; fielders/runners are variant 0. The .gpc body contains textures, so replacing a compatible body/overlay changes the field appearance without changing charID. [M/A: roster_flow §§5.3-5.5; character_modding_report §1]

Store menu choice in lbl_803C6724.unk38[side][slot] (+0x38), currently unreferenced; copy it into inMemRoster row +0x05, currently unread, while patching roster rebuilds to preserve it. Restamp anim slot +0x253 on every load. Add skin to fn_80017098 reuse and the two charID-only model cache keys, or bypass cache for nonzero skin. This is a proposed path; retail does not propagate those bytes. [A/I: roster_flow §§1-4,6]

Body redirection does not select menu names/images, grid/select model, HUD card, small lineup portraits, voice/announcer, bat/glove, animation banks, per-character special setup or hitbox/scale/timing. A texture-only skin can deliberately use base identity for these. Different rigs/bones need a deeper patch. [A/I: character_select §§6,8; character_modding_report §1]

## Menu to match identity path

| Stage | Copy/reader, address | Result | Confidence |
|---|---|---|---|
| Pick and colour | menus fn_2_DFAC; fn_2_3624 -> fn_2_A040 | teams[side][slot] in lbl_803C6724+0x02. L colour currently changes real charID. order at +0x14; proposed skin at +0x38 is not copied by retail. | M/A |
| Ready | menus fn_2_5444 @0x5444 | Exhibition only changes state. Challenge stores charID/order to save lineup and CharID in inMemRoster; finalisation still runs. | A |
| Finalise | menus fn_2_3204 -> fn_2_2FC0 -> fn_2_8940 @0x8940 | Static_Stats_Tables lbl_8034E9A0[teams[side][n]] copied to inMemRoster[side][n] @0x80353BE0, stride 0xA0; +0x24 CharID, +0x3B chemistry. lbl_80354720[side][n].unk2 receives order. Still pick order. | M |
| Assign fielding positions | DOL characterSelectScreen @0x80065DEC | Snapshots nine charIDs, then re-copies static rows into roster entries by position. A skin in the first copy is LOST unless paired and reapplied. | A |
| Other roster writers | DOL transferStatsToInMemRoster @0x800426DC, fn_800471F4 @0x800471F4, fn_80068838, fn_800415A8; game fn_3_B4124, fn_3_10C450 | Star toggle recopies static row; substitution swaps rows then reassigns positions; saved/CPU and minigames make independent copies. | M/A |
| Fielders | game fn_3_6BD6C -> DOL fn_8001594C @0x8001594C | Position link chooses inMemRoster[teamFielding][player]; loads nine variant-0 slots. | A |
| Batter/runners | game fn_3_6BA64 -> DOL fn_8001500C @0x8001500C | g_Runners[i].rosterID chooses inMemRoster[teamBatting][player]; batter slot 9 variant 1, runners 10..12 variant 0. | A |
| Cutscene/preview | game fn_3_6B4C8 / fn_3_6B5D8 -> DOL fn_80016344 @0x80016344; menus fn_2_481F4 -> fn_80016710 @0x80016710 | Explicit charID override, variant 1; helpers hard-code team0 for roster arm/stance reads, so skin provenance for team1 needs proof. | A |
| Request/load | DOL fn_80017098 @0x80017098 -> fn_8001758C @0x8001758C | Roster CharID enters load task; slot g_hugeAnimStruct @0x8036E548 +0xC04 + slot*0x27C stores charID +0x252, team/player +0x256/+0x257, variant +0x259, arm/stance +0x25A/+0x25B. | M |
| Construct | fn_80017814 @0x80017814 -> fn_8002399C, f_InitActorWithLayout @0x800232E0 | Relocates .gpc texture/layout/geo/skin/extra and constructs actor. | A |

## CharID lookup inventory

R=roster stats row, T=load task charID, S=anim slot charID, C=explicit caller argument. “Yes” means the recommended body-source hook covers it. Some downstream gameplay functions' exact key field is not proven; identified below.

| Lookup/data | Reading function @ address | Which charID copy | Body hook? / confidence |
|---|---|---|---|
| Disc body tracks 0/1, subfile @0x800F1D78 (54*19*16); .gpc geometry/layout/texture | fn_8001758C @0x8001758C, fn_8002204C @0x8002204C fallback; fn_80017814 @0x80017814 relocates | T -> S/body buffer | Yes, if variant 0 and 1 both patched. M/A |
| ARAM body master[0..53] @0x800EFD38, pair @0x800F73B8, overlay | fn_8002204C @0x8002204C; overlay callback fn_8002254C @0x8002254C | T passed as arg | Yes, variant 1. M/A |
| Special actor setup jumptable @0x800EEC40 (48 entries) | fn_80017814 @0x80017814 | S | No. A |
| Animation banks tracks 2..18, master[432+c] track15 | fn_80016B60 @0x80016B60, fn_80016F7C @0x80016F7C, fn_80021BBC @0x80021BBC, fn_80015468 @0x80015468 (track4/17) | S / loadedCharID from S | No. M/A. Tracks7/8 lack identified request path, not verified free |
| Bat/glove/attachments: lbl_800EEAAC @0x800EEAAC, pair @0x800F7424, row kind @0x800F743C, disc @0x800F5D98, master[54+c*7+k] | fn_80012B90 @0x80012B90, fn_80013680 @0x80013680, fn_80021CA4 @0x80021CA4, fn_8002244C @0x8002244C | S (allocator also scans R) | No. M/A |
| Extra model script map @0x800EEB18 -> master[486+id] / disc @0x800F71D8 | fn_8001500C @0x8001500C, fn_8001594C @0x8001594C, fn_80016344 @0x80016344, fn_80021ADC @0x80021ADC | S/C | No. A |
| Model scale 54*2 f32 @0x800E8300 | fn_8001D2D4 @0x8001D2D4; setBatterContactConstants; setFielderValues | S for actor; R for gameplay | No. A |
| Batter reach/hitbox game .data+0x6EF8, 54*0x24 | setInMemBatterConstants fn_3_6DE60; calculateContactAndHitType, batterInBoxMovement, setBatterContactConstants, fn_3_1F998 | R CharID at init; later copy not rechecked | No. A |
| Charge thresholds game .data+0x7690, 54*2 | setDefaultInMemBatter (address unresolved this pass) | R/initialized batter identity, needs exact-field check | No. A |
| Runner timing game .data+0x7870, 54*6 | fn_3_631AC @0x631AC, fn_3_63874 @0x63874 | runner identity; exact field not rechecked | No. A |
| Fielder reaction game .data+0x7E34, 54*4 | fn_3_60E90 @0x60E90, fn_3_A96FC @0xA96FC | fielder identity; exact field not rechecked | No. A |
| Fielder hitbox/height game .data+0x79B4, 54*0x10; +0x7F10, 54*2 | setFielderValues fn_3_6E24C; fn_3_60A98 @0x60A98, fn_3_128C18 @0x128C18, fn_3_142DB4 @0x142DB4, fn_3_1430D0 @0x1430D0 | R at setFielderValues; downstream field needs check | No. A |
| Foot-height game .data+0x17000, 54*4 | fn_3_BC274 @0xBC274, fn_3_BC2DC @0xBC2DC | likely S/fielder identity; exact field unverified | No. A/I |
| DOL anim event windows 15*54*s16 @0x800FB798..0x800FBD80 | fn_8004B284 @0x8004B284, fn_8004BEB0 @0x8004BEB0, fn_8004ACF4 @0x8004ACF4 | S/passed charID, call sites need check | No. A |
| Stat row/chemistry in R @0x80353BE0 (+0x3B..+0x70 chemistry) | game fn_3_6DE60, fn_3_6EBB4, fn_3_6D964, fn_3_6E24C; chemistry fn_3_6D658 @0x6D658, fn_3_ABDD0 @0xABDD0, fn_3_4DC14 @0x4DC14, fn_3_8913C @0x8913C | R fields and other player's R.CharID as chemistry column | No. A |
| Voice bank: family uniqueIdx @0x800E8558, sound groups @0x800EF508, game .data+0x8148 | fn_3_90F48 @0x90F48 -> fn_800698F8 @0x800698F8; sound row 5+uniqueIdx | R charID or practice override -> uniqueIdx | No. A |
| Voice line base game .data+0x8168, 54*u16 | fn_3_90220 @0x90220; fn_3_90150 @0x90150 | C charID from gameplay caller, often R/batter/fielder identity; all callers not audited | No. A |
| Announcer name by uniqueIdx @0x80108DF4 | fn_800628D4 @0x800628D4 -> fn_800698F8; game fn_3_10CC20 @0x10CC20 | C charID -> uniqueIdx | No. M/A |
| HUD card res[1] desc @0x800E8B18, ZZZZ+0x1A6B3000, frame 30+c | fn_3_91D1C @0x91D1C; fn_3_EA340 @0xEA340 and other character_select §6 callers | R.CharID | No. A |
| Other lineup/results portrait ZZZZ+0x18ED7000, frame 53+uniqueIdx | fn_3_59F40 @0x59F40; menus fn_2_4EB2C @0x4EB2C, fn_2_5ED3C @0x5ED3C | C/R -> uniqueIdx | No. A |
| Menu mini/name/grid/preview model, common files and menu_char_a[c] | menus fn_2_776A0 @0x776A0, fn_2_74F40 @0x74F40, DOL fn_80051D00 @0x80051D00, menus fn_2_18398 @0x18398 / fn_2_18148 @0x18148 | menu teams/gridPick C | No. A |

The DOL lbl_800E8558 @0x800E8558 row contains family/base/unique/isBase/isCaptain/colourIdx; a model swap does not redirect uniqueIdx paths. [A: character_select §§1,6]

## Storage audit and copies

| Candidate | Evidence and lifetime | Verdict |
|---|---|---|
| lbl_803C6724+0x38, 2*9 bytes | No found field access/object-spanning copy; menu-only, absent from fn_2_8940. [A: roster_flow §§1-2] | Good UI choice byte after explicit clear/copy/re-entry patches |
| inMemRoster @0x80353BE0 row +0x05..+0x1D | No field reads in 1,429-access scan. Field-wise copy includes memcpy 0x1E, so entry->entry swap/backup moves it but static->entry rebuild resets it. Static retail rows zero. [A: roster_flow §§3-4] | Use +0x05 with explicit preservation in fn_2_8940, characterSelectScreen @0x80065DEC, transferStatsToInMemRoster @0x800426DC |
| row +0x1E/+0x1F, +0x72/+0x73, +0x9E/+0x9F | Padding skipped by field-wise copy, so remains with slot index; whole-row 0xA0 copy overwrites. [A] | Poor per-player storage |
| row +0x71, +0x74..+0x9D | No observed semantic reads, but explicitly recopied from static row. [A] | No persistence advantage over +0x05 |
| lbl_80354720[2][9], 4 bytes/row | Every byte read/written. [A] | No spare byte |
| anim slot +0x253 at 0x8036E548+0xC04+slot*0x27C | No found access; rebuilt by fn_8001758C. [A] | Good runtime copy if restamped every load; add to reuse key |
| Challenge save lineup two pad bytes | 6-byte row has 2 pads, but save/load compatibility not established; exhibition save stores charIDs only. [A/I] | Persistence investigation only |

fn_80017098 @0x80017098 reuses on team/player/charID/arm/stance/unk258/variant, excluding skin. fn_8001758C also uses batter/runner model caches keyed by charID; filled by fn_80014E50 @0x80014E50 and fn_80014F40 @0x80014F40. Add skin to key or bypass nonzero-skin hits. Shared animation bank by charID in fn_80015468 is appropriate only for skins compatible with base animations. [M/A/I: roster_flow §5.4]

## Descriptor capacity and buffers

**Confirmed unused character descriptor slots: 0.** Master @0x800EFD38 contains 515 member entries: 54 body/overlay + 378 attachments + 54 track-15 banks + 29 scripts; master[515] @0x800F1D68 is whole blob. Disc subfiles @0x800F1D78 define 54*19=1026 entries; sub-items @0x800F5D98 define 54*6=324; model scripts @0x800F71D8 define 30. Master 515 rows name 345 distinct files because of aliases, not spare descriptor addresses. Track 7/8 gives 108 descriptors with no identified request path, yet they are defined and not proven unused. [M/A: data_map §4, animations §1] Append new descriptor data in patched code and point the skin branch to it; ZZZZ has 193,984,512 bytes of unreferenced gaps for payloads, which is data capacity rather than descriptor capacity. [M/I: data_map §§1,3]

Body: fn_80018024 @0x80018024 sizes four main body buffers (plus mode-specific alternates) from largest track-0/1 declared unpacked size over 54 charIDs, 32-byte rounded. A skin descriptor outside that scan can exceed allocation. Include skins in sizing or cap at retail maximum; separately verify menu preview allocation. [A/I: character_modding_report §1]

ARAM: fn_800227E4 @0x800227E4 allocates hard-coded 0x4D6600 via immediates @0x800227EC/0x800227F4; master[515] describes blob. 345 members occupy 99.91%; added overlays require blob relocation/size and allocation patch. No member-offset bound check was established. [A: data_map §2, character_modding_report §8]

Sub-items: fn_80014204 @0x80014204 scans all 54; fn_800145F8 @0x800145F8 can scan only active 18 and allocates 13*2 slices using largest low-28-bit size rounded to 32. Larger skin-specific bats/gloves need new sizing/reallocation; texture skins using base items do not. [A: character_modding_report §1]

Overlay archive must have compatible texture count/dimensions. A full body must preserve layout/geo/skin links and expected bone IDs. f_InitActorWithLayout @0x800232E0 can fail at @0x800233A0 if skinFileID exceeds geo palette descriptors. [A: character_modding_report §1]

## Rio/Dolphin questions

1. Watch +0x05 through ready, position assignment, star toggle, substitution, reload; pair duplicate charIDs with their individual skins. Check menu re-entry fn_2_5F80 and saves.
2. Test batter ARAM/overlay and fielder/runner disc track1, plus cutscene/preview explicit-charID paths. fn_80016344/fn_80016710 currently use team0 for roster arm/stance, which may pick team0 skin for team1.
3. Change a skin while slot reuse/model caches are hot; verify invalidation.
4. Verify skeleton/bone/texture compatibility, allocation sizes, ARAM headroom and menu preview heap with a larger file.
5. Instrument tracks7/8 before reusing any descriptor. Confirm exact charID field in timing, foot-height, voice-line and animation-event callers marked uncertain above.
6. Decide whether the picker changes menu mini/name/grid art, preview model, HUD and unique-index portraits; all remain base identity under the body-only hook.

This is a static trace, not a runtime validation.
