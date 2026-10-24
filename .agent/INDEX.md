# .agent index: read this first, then only the sections you need

Docs here total about 60k tokens; don't read them whole. Find your task below, read the listed
sections (`grep -n '^#' <file>` gives line numbers), and look up addresses in `addresses.md`
instead of searching prose.

## Start here by task
| Task | Read |
|---|---|
| Match a function (any module) | CLAUDE.md "Tasks"; `decomp_knowledge.md` §1 "Quick Fixes" + "Known Unfixable Patterns", §13 (loops/inlines/store order) |
| Match a menus.rel character-select function | the above + `character_select.md` §1 (tables), §5 (function list and status) |
| Extend the clone patcher / GUI | `tools/modding/README_WINDOWS.md`, `character_modding_report.md` §TL;DR, §3, §8; `character_select.md` §6 (UI lookups), §8.2–8.3 (menu art) |
| Find, extract or replace a game file | `data_map.md` §1 TL;DR, §4 (tables), §5 (formats); tool: `tools/datamap/README.md` |
| Edit in-game text | `data_map.md` §1, §6; `tools/datamap/README.md` (text-export / text-import) |
| Skin picker (phase 3) | `roster_flow.md` §6 (design), §1–§5 (data flow); `modding_roadmap.md` phase 3 |
| Character load chain (models, textures, skeleton, gloves) | `character_modding_report.md` §1–§3 |
| Menu portraits, names, colour word | `character_select.md` §8.1–8.3 |
| What's planned / status | `modding_roadmap.md`; live status on the GitHub board (users/Cjericho4/projects/3, issues on Cjericho4/mssb-dtk) |
| Pick up an interrupted function | `handoff_<fn>.md` if present |

## Files
| File | What it is | Size |
|---|---|---|
| `addresses.md` | one table: address / table / file → name → meaning → doc section | small; grep it |
| `modding_roadmap.md` | phases 1–6 and research tracks R1–R7, with status | ~2k tokens |
| `character_modding_report.md` | **current** reference for the character load chain, tables, clone recipes, patcher findings | ~5k |
| `character_modding.md` | older working notes, superseded by the report (kept for history) | skip |
| `character_select.md` | select/roster flow, UI and announcer lookups, menu art files and index math | ~10k |
| `data_map.md` | every descriptor table and file in ZZZZ.dat / aaaa.dat, formats, coverage, unknowns | ~7k |
| `decomp_knowledge.md` | compiler idioms and matching tricks by date; §1 and §13 are the most reused | ~12k |
| `roster_flow.md` | roster → match data flow (R2): copy sites, skin-byte audit, loader path, re-load points, phase-3 design | ~7k |
| `handoff_fn_2_3624.md` | state of the one unmatched phase-1 function | ~1k |
| `*_codex_notes.md` | give-up logs from Codex batches (menus, dol, challenge); grep for a function name | skip |
| `attempts/`, `categorize/`, `workflows/` | best non-matching attempts, difficulty CSV, parallel-batch procedure | as needed |

## Conventions
- Bar for modding work: understood and documented; matching is not required.
- Commits: no Co-Authored-By or other trailer lines. Match count (`tools/find_matches.py`) must never drop.
- User runs mods on Windows (Dolphin / Project Rio); tools are stdlib Python 3.8+.
