# Character modding roadmap

The order the user set (2026-10-23). Details live in `.agent/character_modding_report.md` and
`.agent/character_select.md`.

**Bar for modding work: "understood and documented", not "100% matched".** A function is ready for
modding once it has a complete, documented C body that is semantically faithful. Matching continues
alongside for the byte-exact rebuild goal, but a later phase never waits on a match.

## Done
- Data-only clone patcher (`tools/modding/clone_character.py`): recoloured clones on donor slots,
  `.iso` input, game.rel re-packed in aaaa.dat (voice/timing), `--ui source` (announcer, voice bank,
  HUD card, menu name / mini picture / grid portrait, colour word), per-character colour regions;
  recolour leftovers (#16: Luigi's emblem, Wario specks, Noki stripe, Birdo, tint recolours for
  white/black/grey characters, Petey). Tested in Rio: model, recolour and Mario's voice/announcer.
- **GUI** (`tools/modding/clone_gui.py`): PRSH-style theme, colour-region checkboxes, full preview,
  narrow-window layout (#17); Windows exe built by `.github/workflows/build-gui.yml`.
- **Phase 2** (#1): menu art traced and patched (`character_select.md` §8).
- **R1 data map** (#9) and **R2 roster flow** (#10), below.

## In progress / waiting
- Rio tests by the user: menu art (#2), restyled GUI + non-Mario clones (#3).
- `fn_2_3624` match, five lines left (#4, `handoff_fn_2_3624.md`).
- Docs consolidation (#19).
- Clone Maker port to Tauri (Rust core + web UI), Windows first (#30; stages #31–#34, Mac #35). The
  Python patcher stays the reference: the Rust output must be byte-identical (`tools/clonemaker/difftest.py`).

## Phases
1. **Character-select code: understood and documented, matched where practical.**
   One agent per function until it matches; merge each and ask the user before starting the next.
   Order: `fn_2_2FC0` → `fn_2_4970` → `fn_2_7DDC` → `fn_2_DFAC` → `fn_2_3624`.
   **Status 2026-10-24: done for modding.** All match (plus `fn_2_348C`, `fn_2_C698`) except
   `fn_2_3624`: complete documented body, 5 scheduling lines left (`.agent/handoff_fn_2_3624.md`).
   Phase 2 may start once these are decompiled and documented, even if some don't match yet.
2. **Custom sprites everywhere** ✅ (#1). Trace how the menus pick portraits, mini-screen sprites and name
   banners. Clones showed the donor's own portrait in menus (`character_select.md` §7); make
   them show the source's, or a custom recoloured, portrait on every screen.
   Done 2026-10-24: the menu name, mini picture and grid portrait are charID-keyed files
   (ZZZZ+0x1A9FE800, +0x18AEE800); `--ui source` retargets the donor's textures to the source's
   (recoloured, files re-packed in place) and drops the colour word; the large banner archive is the
   Challenge ending and needs no patch. Details: `character_select.md` §8. Rio test: #2.
3. **Skin picker in the menu: no lost slots** (#5). The real goal: choose a character, then a colour or
   skin, without replacing another character. A per-player skin byte (`StatTable.UnusedBytes[0]`),
   chosen in the select code instead of moving the pick to another charID, rendered through a
   `skinPairs[charID][skin]` extension of the body/overlay mechanism (`lbl_800F73B8`), plus the
   sprites from phase 2. Design notes: `roster_flow.md` §6 (the R2 result: where the byte survives and
   where it is re-applied), `character_modding_report.md` §4c, `character_select.md`.
4. **Chemistry for clones** (#6). Give clone↔source and clone↔clone good chemistry instead of the
   source's self-chemistry (a few lines in the patcher).
5. **Animations** (#7). R5 findings and remaining work: `animations.md`.
   1. Map which subfile track (2..14, 16..18 per character in `lbl_800F1D78`) holds which moves.
   2. Parse/document the anim bank (SDK charPipeline `ANIMGet` format; track 15 is one more bank)
      and the bone hierarchy (the body `.gpc`'s actor layout), eventually exporting to Blender.
   3. Swap whole animation banks between characters (data-only; the patcher already rewires tracks).
   4. Author new animations: a Blender → game converter against the character's bone layout.
6. **New characters beyond 54** (#8). Every per-character table is 54 entries, the select grid has 32
   cells, and portrait/announcer/stat files and many bounds checks (`charID < 0x36`) are fixed-size.
   Needs table relocation and code changes on top of everything above (`character_select.md`).

## Research tracks: decomp and data mapping that make mods easier
Added 2026-10-24 at the user's request so they aren't forgotten. They feed the phases above;
the "enables" line says what each unlocks. Status: ⏳ not started, 🟡 in progress, ✅ done.

- **R1. Full game file map** ✅ (#9). Catalogue every file in `ZZZZ.dat` /
  `aaaa.dat` / FST: every descriptor table in the DOL and RELs, the menu resource-ID table
  `lbl_8023D6C0`, coverage of every byte range, a format sniffer per file family, and a safe
  `tools/datamap/mssb_files.py` (list / info / extract / replace into a new folder or ISO, updating
  every descriptor copy). Docs: `.agent/data_map.md`. *Enables:* finding anything instantly;
  replacing any asset safely; the base for every other track.
- **R2. Roster → match data flow** ✅ (#10). Documented in
  `.agent/roster_flow.md`: the exhibition copy is `fn_2_8940` (pick order, now matched) +
  `characterSelectScreen` (re-copy in fielding-position order), re-copies in-game by the star toggle
  (`transferStatsToInMemRoster`, decompiled) and substitutions (`fn_800471F4`); fielders/runners load
  with `variant = 0` (disc track 1), only the batter uses the ARAM pair; `fn_8001500C` decompiled.
  `StatTable` +0x05..+0x1F has no field reader/writer anywhere, but +0x05..+0x1D sit inside the
  `memcpy(0x1E)` of every rebuild and +0x1E/+0x1F are padding that stays with the slot. Design in
  roster_flow.md §6: menu choice in the free `lbl_803C6724.unk38[2][9]`, entry byte +0x05 re-applied
  at the three static->entry copies, slot byte 0x253 (free) read in `fn_8001758C`, body pair /
  track-1 subfile keyed on (charID, skin). `fn_80016344/710/17814` remain documented, unmatched.
- **R3. Character stats and gameplay tables** 🟡 partial (#11). Documented in `stats.md`:
  `stats.0` layout (54 rows, zero block, 12 captain-team blocks), every `CharacterStats` field
  traced to its reader (high confidence), star skills / abilities / star bonus, chemistry,
  game.rel tables 0x6EF8, 0x7690, 0x7870, 0x7E34, 0x8168, 0x17000 and the 15 DOL animation-window
  tables. Tool: `mssb_files.py stats-export / stats-import` (byte-identical round trip, tested).
  Open: meaning of the runner (0x7870), fielder (0x7E34) and DOL window fields, captain lineups
  1..3, what the chemistry thresholds gate.
- **R4. Voices and sounds** ✅ (#12). Documented in `.agent/sounds.md`: 48 MusyX groups (every
  row's role and loader), voice bank = `sound.(5+u)` with group `lbl_3_data_8148[u]` and SFX
  `lbl_3_data_8168[charID] + line` (13 lines, 8 of them traced to call sites), announcer names in
  `sound.37`, DSP-ADPCM sample format, `.adp` music (stereo 48 kHz stream ADPCM, opened by path:
  data-only swap) and MusyX songs (`game_set.0`). Tools: `mssb_files.py sound-list / sound-export /
  sound-import / voice-swap / music-export` (identity round trip of all 48 groups, tested).
  Open: lines 1, 2, 6, 8, 12; an `.adp` encoder. Clone voices (#29): `--ui donor` and
  `--ui source --no-gameplay` clones are silent in main; the fix (copy `8168` always, merge the
  source into the donor bank, ARAM budget check) is on branch `voice-merge`, waiting for a Rio
  test (sounds.md §6-§7).
- **R5. Animation banks** 🟡 partial (#13, groundwork for phase 5). Documented in
  `animations.md`: code-backed track/action selection (7/8 unresolved), ANIM records and setting
  quantization, body hierarchy and bone-ID binding, sharing audit, playback and timing links.
  Tools: `tools/datamap/animations.py`, `audit_animations.py`, synthetic unittest. All 544 distinct
  disc banks / 3,829,384 keys / 108 bodies parse; all 54 master/disc track-15 pairs agree.
  Open: track7/8 callers, extra-pose names, visual identity of 0x2E, auxiliary curves and Blender
  conventions; data-only swap recipe documented but no Dolphin validation or authoring round trip.
- **R6. Model format (`.gpc`)** ⏳ (#14). Geometry, display lists, skinning; `f_InitActorWithLayout`
  (111 feedback lines from matching) is the key function. *Enables:* editing or importing models, not just
  textures; a step toward phase 6.
- **R7. Menu text and graphics** ⏳ (#15). Names are CI4 images (111x18), not text; map every menu
  resource, sequence and font (`inspect_menu_ui.py` is the start). *Enables:* custom names, logos and
  menu art for new or renamed characters.

Suggested order: R4–R7 as the phases need them; R3 leftovers (stats.md §8) when phase 4 needs them.
