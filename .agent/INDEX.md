# .agent index: read this first, then only the sections you need

Docs here total about 70k tokens; don't read them whole. Find your task below, read the listed
sections (`grep -n '^#' <file>` gives line numbers), and look up addresses in `addresses.md`
instead of searching prose. Each fact has one home (the "owns" column); other docs link to it.

## Start here by task
| Task | Read |
|---|---|
| Match a function (any module) | CLAUDE.md "Tasks"; `decomp_knowledge.md` §1 "Quick Fixes" + "Known Unfixable Patterns", §2 (diff counts), §13 (loops/inlines/store order) |
| Match a menus.rel character-select function | the above + `character_select.md` §1 (tables), §5 (function list and status) |
| Extend the clone patcher / GUI | `tools/modding/README_WINDOWS.md`, `character_modding_report.md` TL;DR, §3, §4a, §8; `character_select.md` §6 (UI lookups), §8.2–8.3 (menu art) |
| Find, extract or replace a game file | `data_map.md` §1 TL;DR, §4 (tables), §5 (formats); tool: `tools/datamap/README.md` |
| Edit in-game text | `data_map.md` §1, §6; `tools/datamap/README.md` (text-export / text-import) |
| Edit stats, chemistry, abilities; per-character gameplay tables | `stats.md` §0, then the section for the table; tool: `tools/datamap/README.md` (stats-export / stats-import) |
| Skin picker (phase 3) | `roster_flow.md` §6 (design), §1–§5 (data flow); `modding_roadmap.md` phase 3 |
| Character load chain (models, textures, anim banks, gloves) | `character_modding_report.md` §1–§3 |
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
| `stats.md` | stats.0 layout, every CharacterStats field, star skills, chemistry, captain teams, game.rel per-character tables, DOL animation windows (R3) | ~5k |
| `decomp_knowledge.md` | compiler idioms and matching tricks by date; §1 and §13 are the most reused | ~14k |
| `code_quality.md` | code-quality rules (adopted; summary in CLAUDE.md), cleanup checklist, tooling, cleanup log | ~4k |
| `handoff_fn_2_3624.md` | state of the one unmatched phase-1 function | ~2k |
| `character_modding.md` | retired stub pointing at the report | skip |
| `*_codex_notes.md` | give-up logs from Codex batches (menus, dol, challenge); grep for a function name | skip |
| `attempts/`, `categorize/`, `workflows/`, `probe/` | best non-matching attempts, difficulty CSV, parallel-batch procedure, probe harness + roster scanner | as needed |

## Conventions
- Bar for modding work: understood and documented; matching is not required.
- Function status in docs, where given: MATCH, "N lines" (`tools/feedback_diff.py` entries, `decomp_knowledge.md` §2), or "stub" (asm only). Re-run before quoting.
- Commits: no Co-Authored-By or other trailer lines. Match count (`tools/find_matches.py`) must never drop.
- User runs mods on Windows (Dolphin / Project Rio); tools are stdlib Python 3.8+.
