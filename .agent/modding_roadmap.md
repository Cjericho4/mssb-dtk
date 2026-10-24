# Character modding roadmap

The order the user set (2026-10-23). Finish a phase before starting the next unless the user says
otherwise. Details live in `.agent/character_modding_report.md` and `.agent/character_select.md`.

## Done
- Data-only clone patcher (`tools/modding/clone_character.py`): recoloured clones on donor slots,
  `.iso` input, game.rel re-packed in aaaa.dat (voice/timing), `--ui source` (announcer, voice bank,
  HUD card). Tested in Rio: model, recolour and Mario's voice/announcer work.

## In progress
- **GUI** for non-technical users (`tools/modding/clone_gui.py` + a Windows exe build), branch `gui-tool`.
- **Phase 1: character-select functions**, one agent per function until it matches, merging each and
  asking the user before starting the next. Order: `fn_2_2FC0` (running) → `fn_2_4970` → `fn_2_7DDC` →
  `fn_2_DFAC` → `fn_2_3624`.

## Next
- **Phase 2: custom sprites everywhere.** Trace how the menus pick portraits, mini-screen sprites and
  name banners. Today they show the donor's own portrait (see `character_select.md` §7). Then make
  clones show the source's (or a custom recoloured) portrait in every menu.
- **Phase 3: chemistry for clones.** Parked until phase 2 works. Give clone↔source and clone↔clone good
  chemistry instead of the source's self-chemistry.

## Later: after everything needed for modded characters is mapped and understood
- **Phase 4: animations.**
  1. Map which subfile track (2..14, 16..18 per character in `lbl_800F1D78`) holds which moves.
  2. Parse/document the anim bank (SDK charPipeline `ANIMGet` format) and skeleton (track 15),
     eventually exporting to Blender.
  3. Swap whole animation banks between characters (data-only, patcher already rewires tracks).
  4. Author new animations: a Blender → game converter against the character's skeleton.
