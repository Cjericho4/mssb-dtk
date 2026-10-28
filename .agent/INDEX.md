# .agent index: read this first, then only the sections you need

Docs here total about 70k tokens; don't read them whole. Find your task below, read the listed
sections (`grep -n '^#' <file>` gives line numbers), and look up addresses in `addresses.md`
instead of searching prose. Each fact has one home (the "owns" column); other docs link to it.

**Modding tools live in [mssb-modding](https://github.com/Cjericho4/mssb-modding)** (checkout at
`../mssb-modding`): every `tools/clonemaker`, `tools/modding`, `tools/datamap` and
`tools/inspect_banner_archive.py` path in these docs is in that repo. Game knowledge stays here.
Modding issues moved there too; old `mssb-dtk` issue links redirect. Numbers in these docs are the
old ones: #2→1, #3→2, #5→3, #6→4, #7→5, #8→6, #18→7, #25→8, #26→9, #27→10, #28→11, #30→12,
#33→13, #34→14, #35→15, #36→16, #37→17 (closed ones such as #29 and #38 stayed here).

## Start here by task
| Task | Read |
|---|---|
| Match a function (any module) | CLAUDE.md "Tasks"; `decomp_knowledge.md` §1 "Quick Fixes" + "Known Unfixable Patterns", §2 (diff counts), §13 (loops/inlines/store order) |
| Match a menus.rel character-select function | the above + `character_select.md` §1 (tables), §5 (function list and status) |
| Extend the clone patcher / GUI | `tools/clonemaker/API.md`, `tools/clonemaker/core/README.md`, `tools/clonemaker/app/README.md` (Rust core and Tauri window); `tools/modding/clone_character.py` (patcher) and `tools/modding/clone_gui.py` (Python logic reference), `character_modding_report.md` TL;DR, §3, §4a, §8; `character_select.md` §6 (UI lookups), §8.2–8.3 (menu art) |
| Design the skin picker (per-player looks, mssb-modding #3) | `skin_picker.md` (menu → match charID path, every charID-keyed lookup, the `fn_8001758C` body hook, storage bytes, buffer limits, Rio questions); `character_select.md` "Skin-picker hook" |
| Find, extract or replace a game file | `data_map.md` §1 TL;DR, §4 (tables), §5 (formats); tool: `tools/datamap/README.md` |
| Edit in-game text | `data_map.md` §1, §6; `tools/datamap/README.md` (text-export / text-import) |
| Edit stats, chemistry, abilities; per-character gameplay tables | `stats.md` §0, then the section for the table; tool: `tools/datamap/README.md` (stats-export / stats-import) |
| Voices, announcer, SFX, music; voice swaps | `sounds.md` §1, then §2 (files), §3 (voice lines), §4 (announcer), §5 (music), §6 (swaps, clone voices), §7 (ARAM budget); tool: `tools/datamap/README.md` (sound-* / voice-swap / music-export) |
| Skin picker (phase 3) | `roster_flow.md` §6 (design), §1–§5 (data flow); `modding_roadmap.md` phase 3 |
| Character load chain (models, textures, anim banks, gloves) | `character_modding_report.md` §1–§3 |
| Hands and gloves (sub-items: files, attachment, morph shapes, event scripts) | `character_modding_report.md` §3.1 |
| Animation bank swaps, sequences, bone binding, playback (R5) | `animations.md` (owns R5); parser: `tools/datamap/animations.py`; full audit: `audit_animations.py` |
| Menu portraits, names, colour word | `character_select.md` §8.1–8.3 |
| What's planned / status | `modding_roadmap.md`; live status on the GitHub board (users/Cjericho4/projects/3, issues on Cjericho4/mssb-dtk) |
| Pick up an interrupted function | `handoff_<fn>.md` if present |

## Files
| File | Owns | Size |
|---|---|---|
| `addresses.md` | index only: address / table / file → name → meaning → owning doc section | ~10k tokens; grep it |
| `modding_roadmap.md` | phases 1–6, research tracks R1–R7, done / in progress, issue numbers | ~2k |
| `character_modding_report.md` | character load chain, per-character tables (with retail values), clone recipes, patcher findings | ~5k |
| `character_select.md` | select/roster screen code, UI and announcer lookups, menu art files, index math and descriptor copies | ~10k |
| `data_map.md` | every descriptor table and file in ZZZZ.dat / aaaa.dat, formats, coverage, UI slots, unknowns | ~7k |
| `roster_flow.md` | roster → match data flow (R2): copy sites, skin-byte audit, actor drivers, re-load points, phase-3 skin design | ~8k |
| `animations.md` | character ANIM track/action map, bank/key format, body bone hierarchy, sharing, playback, swap requirements and R5 unknowns | ~6k |
| `stats.md` | stats.0 layout, every CharacterStats field, star skills, chemistry, captain teams, game.rel per-character tables, DOL animation windows (R3) | ~5k |
| `sounds.md` | MusyX sound groups (every row), voice banks and voice-line table, announcer, DSP-ADPCM format, `.adp` streams and MusyX songs, voice swaps and clone voices (R4, #29), ARAM budget | ~6k |
| `decomp_knowledge.md` | compiler idioms and matching tricks by date; §1 and §13 are the most reused | ~14k |
| `code_quality.md` | code-quality rules (adopted; summary in CLAUDE.md), cleanup checklist, tooling, cleanup log | ~4k |
| `handoff_fn_*.md` | state of an interrupted match: `fn_2_3624` (the one unmatched phase-1 function), `fn_80012B90`, `fn_80013680` (bat/glove loaders) | ~2k each |
| `character_modding.md` | retired stub pointing at the report | skip |
| `*_codex_notes.md` | give-up logs from Codex batches (menus, dol, challenge); grep for a function name | skip |
| `easy_wins_notes.md` | near-miss log for 15 small game/menus functions (decoded C + the one remaining diff each); grep for a function name | skip |
| `attempts/`, `categorize/`, `workflows/`, `probe/` | best non-matching attempts, difficulty CSV, parallel-batch procedure, probe harness + roster scanner | as needed |

## Conventions
- Bar for modding work: understood and documented; matching is not required.
- Function status in docs, where given: MATCH, "N lines" (`tools/feedback_diff.py` entries, `decomp_knowledge.md` §2), or "stub" (asm only). Re-run before quoting.
- Commits: no Co-Authored-By or other trailer lines. Match count (`tools/find_matches.py`) must never drop.
- User runs mods on Windows (Dolphin / Project Rio); tools are stdlib Python 3.8+.
