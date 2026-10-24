# Character modding roadmap

The order the user set (2026-10-23). Details live in `.agent/character_modding_report.md` and
`.agent/character_select.md`.

**Bar for modding work: "understood and documented", not "100% matched".** A function is ready for
modding once it has a complete, documented C body that is semantically faithful. Matching continues
alongside for the byte-exact rebuild goal, but a later phase never waits on a match.

## Done
- Data-only clone patcher (`tools/modding/clone_character.py`): recoloured clones on donor slots,
  `.iso` input, game.rel re-packed in aaaa.dat (voice/timing), `--ui source` (announcer, voice bank,
  HUD card). Tested in Rio: model, recolour and Mario's voice/announcer work.

## In progress
- **GUI** for non-technical users (`tools/modding/clone_gui.py` + a Windows exe build), branch `gui-tool`.

## Phases
1. **Character-select code: understood and documented, matched where practical.**
   One agent per function until it matches; merge each and ask the user before starting the next.
   Order: `fn_2_2FC0` (running) → `fn_2_4970` → `fn_2_7DDC` → `fn_2_DFAC` → `fn_2_3624`.
   Phase 2 may start once these are decompiled and documented, even if some don't match yet.
2. **Custom sprites everywhere.** Trace how the menus pick portraits, mini-screen sprites and name
   banners. Today clones show the donor's own portrait in menus (`character_select.md` §7). Make
   clones show the source's, or a custom recoloured, portrait on every screen.
   **2026-10-24: selection/roster trace understood and documented** (`character_select.md` §8).
   Found charID-keyed common names/52x60 mini images at ZZZZ+0x1A9FE800 and grid portraits at
   +0x18AEE800; exact texture formulas, palette aliases, descriptor copies and patcher steps recorded.
   Pick/ready/auto-fill/open, cursor and L-colour refresh paths have documented C bodies;
   new matches `fn_2_7265C` / `fn_800363D8` (3963 -> 3965 total).
   Read-only inspector verifies all 162 mappings. **Still to do:** implement the two-file patcher
   extension and test in Rio; the older large-banner archive hypothesis remains unverified.
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
