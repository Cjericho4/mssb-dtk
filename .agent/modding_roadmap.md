# Character modding roadmap

The order the user set (2026-10-23). Details live in `.agent/character_modding_report.md` and
`.agent/character_select.md`.

**Bar for modding work: "understood and documented", not "100% matched".** A function is ready for
modding once it has a complete, documented C body that is semantically faithful. Matching continues
alongside for the byte-exact rebuild goal, but a later phase never waits on a match.

## Done
- Data-only clone patcher (`tools/modding/clone_character.py`): recoloured clones on donor slots,
  `.iso` input, game.rel re-packed in aaaa.dat (voice/timing), `--ui source` (announcer, voice bank,
  HUD card), per-character colour regions for every character. Tested in Rio: model, recolour and
  Mario's voice/announcer work.
- **GUI** (`tools/modding/clone_gui.py`): PRSH-style theme, colour-region checkboxes, full preview,
  lag fixed; Windows exe built by `.github/workflows/build-gui.yml`.

## In progress
- Phase 2's last step: menu names / mini pictures / grid portraits + colour word in the patcher and GUI
  (branch `gui-tool`), then the user's Rio test.
- Research track R1 (data map), branch `data-map`.

## Phases
1. **Character-select code: understood and documented, matched where practical.**
   One agent per function until it matches; merge each and ask the user before starting the next.
   Order: `fn_2_2FC0` → `fn_2_4970` → `fn_2_7DDC` → `fn_2_DFAC` → `fn_2_3624`.
   **Status 2026-10-24: done for modding.** All match (plus `fn_2_348C`, `fn_2_C698`) except
   `fn_2_3624`: complete documented body, 5 scheduling lines left (`.agent/handoff_fn_2_3624.md`).
   Phase 2 may start once these are decompiled and documented, even if some don't match yet.
2. **Custom sprites everywhere.** Trace how the menus pick portraits, mini-screen sprites and name
   banners. Today clones show the donor's own portrait in menus (`character_select.md` §7). Make
   clones show the source's, or a custom recoloured, portrait on every screen.
   **2026-10-24: selection/roster trace understood and documented** (`character_select.md` §8).
   Found charID-keyed common names/52x60 mini images at ZZZZ+0x1A9FE800 and grid portraits at
   +0x18AEE800; exact texture formulas, palette aliases, descriptor copies and patcher steps recorded.
   Pick/ready/auto-fill/open, cursor and L-colour refresh paths have documented C bodies;
   new matches `fn_2_7265C` / `fn_800363D8` (3963 -> 3965 total).
   Read-only inspector verifies all 162 mappings.
   **2026-10-24: patcher extension implemented** (`--ui source`): donor name, mini picture and grid
   portrait := source's (pictures recoloured, private palettes, shared buffers never written), both
   files re-packed in place; colour word dropped by default (`--colour-word none|donor`, one menus.rel
   relocation addend per clone); GUI checkbox under Advanced. Offline tests pass (`test_clone.py`
   incl. aliased-buffer and forced-relocation configs, `test_matrix.py --menu-art`).
   **Still to do:** user test in Rio; the older large-banner archive hypothesis remains unverified.
   Optional `fn_2_3624` match refinement remains at five scheduling feedback lines.
3. **Skin picker in the menu: no lost slots.** The real goal: choose a character, then a colour or
   skin, without replacing another character. A per-player skin byte (`StatTable.UnusedBytes[0]`),
   chosen in the select code instead of moving the pick to another charID, rendered through a
   `skinPairs[charID][skin]` extension of the body/overlay mechanism (`lbl_800F73B8`), plus the
   sprites from phase 2. Design notes: `character_modding_report.md` §4c, `character_select.md`.
4. **Chemistry for clones.** Give clone↔source and clone↔clone good chemistry instead of the
   source's self-chemistry (a few lines in the patcher).
5. **Animations.**
   1. Map which subfile track (2..14, 16..18 per character in `lbl_800F1D78`) holds which moves.
   2. Parse/document the anim bank (SDK charPipeline `ANIMGet` format) and skeleton (track 15),
      eventually exporting to Blender.
   3. Swap whole animation banks between characters (data-only; the patcher already rewires tracks).
   4. Author new animations: a Blender → game converter against the character's skeleton.
6. **New characters beyond 54.** Every per-character table is 54 entries, the select grid has 32
   cells, and portrait/announcer/stat files and many bounds checks (`charID < 0x36`) are fixed-size.
   Needs table relocation and code changes on top of everything above (`character_select.md`).

## Research tracks: decomp and data mapping that make mods easier
Added 2026-10-24 at the user's request so they aren't forgotten. They feed the phases above;
the "enables" line says what each unlocks. Status: ⏳ not started, 🟡 in progress, ✅ done.

- **R1. Full game file map** 🟡 (Opus, branch `data-map`). Catalogue every file in `ZZZZ.dat` /
  `aaaa.dat` / FST: every descriptor table in the DOL and RELs, the menu resource-ID table
  `lbl_8023D6C0`, coverage of every byte range, a format sniffer per file family, and a safe
  `tools/datamap/mssb_files.py` (list / info / extract / replace into a new folder or ISO, updating
  every descriptor copy). Docs: `.agent/data_map.md`. *Enables:* finding anything instantly;
  replacing any asset safely; the base for every other track.
- **R2. Roster → match data flow** ⏳ (Fable). How a picked team becomes the match roster
  (`fn_3_B4124`, `fn_3_10C450`, `inMemRoster` / `StatTable`) and reaches the character loaders
  (`fn_80016344`, `fn_80016710`, `fn_80017814` are documented but unmatched). *Enables:* phase 3's
  per-player skin byte surviving from the menu into the match. **Critical path.**
- **R3. Character stats and gameplay tables, fully named** ⏳ (Fable for the readers, then a write-up).
  The 54×0xA0 `CharacterStats` rows (ZZZZ+0x06CF8800), game.rel per-character tables (hitbox,
  charge frames, running timing, voice, 0x7E34, 0x17000), DOL `lbl_800FB798` 15×54 animation
  parameters, star skills and abilities. *Enables:* a stat editor (power, speed, abilities), tuned
  clone stats, and chemistry editing (phase 4).
- **R4. Voices and sounds** ⏳. Per-character voice banks (`lbl_800EF508`, Musyx group files,
  `lbl_3_data_8148`), announcer SFX ids (`lbl_80108DF4`), the sample format, and `snd/` music
  streams. *Enables:* custom voices, voice swaps independent of the character, custom music.
- **R5. Animation banks** ⏳ (groundwork for phase 5). Which subfile track holds which moves; the
  SDK ANIM bank and skeleton formats. *Enables:* animation swaps (data-only), later authoring.
- **R6. Model format (`.gpc`)** ⏳. Geometry, display lists, skinning; `f_InitActorWithLayout`
  (98 lines from matching) is the key function. *Enables:* editing or importing models, not just
  textures; a step toward phase 6.
- **R7. Menu text and graphics** ⏳. Names are CI4 images (111x18), not text; map every menu
  resource, sequence and font (`inspect_menu_ui.py` is the start). *Enables:* custom names, logos and
  menu art for new or renamed characters.

Suggested order: R1 (in progress) and R2 next (critical path), then R3 (most visible to players), then
R4–R7 as the phases need them.
