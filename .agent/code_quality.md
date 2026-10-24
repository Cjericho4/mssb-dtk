# Code quality for mssb-dtk: rules, cleanup, tooling

> **Status (2026-10-24): adopted.** The ten rules are summarised in `CLAUDE.md` "Code Quality
> Standards"; this file keeps the rationale. Citations of other projects (zeldaret, pret, SM64, Melee, …)
> were written from memory, not from those projects' docs; verify one before quoting it. §4 findings come
> from real greps; §4a records the first cleanup pass.

Goal: matched C that a human (or a modding tool author) can read. A match proves the bytes; it proves
nothing about the names, types or comments. Every rule below is safe to apply to matched code because
`ninja && python3 tools/feedback_diff.py <fn>` (and `tools/find_matches.py` count) proves nothing moved.

## 1. The rules

### Naming
1. **Name only what you understand; keep the address otherwise.** `fn_3_XXXX`, `lbl_8XXXXXXX`,
   `unk_0xNN` are honest placeholders. A guessed name is worse than none (zeldaret/oot STYLE.md,
   pret "don't name things you don't understand"). Renames go through `symbols.txt` so the linker
   symbol stays consistent (dtk-template, Melee).
2. **Functions:** `Subsystem_VerbObject` or `camelCase` with a module prefix, one style per module
   (oot: `Actor_UpdateBgCheckInfo`; Melee `ftCo_`, `grLib_`). Statics/inlines lowerCamel. Globals
   `g`/`s` prefix for globals/file statics (oot `gSaveContext`, `sTimer`). Use the Ghidra name from
   `exported_symbols.csv` when it is accurate, normalised to our style (e.g. `hugeAnimStruct` →
   `g_hugeAnimStruct` is the existing pattern; keep it).
3. **Struct fields:** `unk_0xNN` (offset in hex, matching the existing project convention) until
   understood; then a real name with the offset in a trailing comment `/* 0x94 */`
   (oot, mm, tp all comment offsets). Padding is `u8 _pad0x10[0x84];` never a named field.
   Booleans named as predicates (`isActive`, `hasBall`), flag words as `flags` with `#define`/enum bits.
4. **Types:** one canonical struct per memory object, named after the object, not the file it was
   found in. `Gap8001196CStadiumObj` / `MenusLineupChoice` style names (file-prefixed) are
   temporary scaffolding; rename to `StadiumObj`, `CharStaticInfo` once understood.
5. **Files:** `gap_XXXX.c` / `rep_XXXX.c` are dtk split placeholders. Rename to a subsystem name
   (`menus/char_select.c`) when the unit's purpose is known; update `configure.py`/`splits.txt`
   in the same commit (pret/dtk-template practice: file names mirror the original's where known).

### Structs and headers
6. **One home per type and per extern.** A type lives in one header; other files include it. No
   per-file "view" structs of the same global, no file-local `extern` prototypes for functions that
   have a header (oot/mm: `functions.h`/`variables.h`; Melee: per-module headers, `extern` in .c is a
   lint error). If two code paths really treat the same bytes as two things, use one struct with a
   `union` and comment why.
7. **Size asserts on every non-trivial struct:** `STATIC_ASSERT(sizeof(X) == 0x30)` and field-offset
   asserts where a table depends on it (Melee, tp `static_assert`; MWCC: emulate with a negative-size
   array typedef). Catches layout drift instantly, costs zero bytes.
8. **No `void*` and no `*(T*)((u8*)p + off)`** (our CLAUDE.md; oot/mm/Melee all forbid raw offsets in
   matched code). Relocation-style casts on file buffers are OK only inside one clearly named helper.

### Enums, constants, data
9. **No magic numbers that have meaning.** charIDs, team sizes (54 characters, 9 batters), button
   masks, state machine values, sound IDs: enum or `#define` (oot `ACTOR_*`, pret `SPECIES_*`,
   SM64 `ACT_*`). MWCC emits the same code for an enum constant as for the literal. Keep literals
   for pure arithmetic (`0x7FFF` saturation is fine as `S16_MAX` or as-is).
10. **Data tables in C, not blobs, when understood** (pret, oot): typed initialisers with enum/macro
    fields; generated tables must say where they came from (we do this in `gap_8001E460.c`: good).

### Comments and documentation
11. **Every matched non-trivial function gets a one-line summary** above it saying what it does for
    the game, not what the asm does (oot doc conventions; pmret). Note units of fields (cents, frames,
    radians, fixed-point) and non-obvious invariants. Keep `// .text:0x... size:0x...` headers.
12. Comments explain *why* a weird construct exists when it is there for matching (see §Hacks).

### Allowed matching hacks, and how to mark them
Allowed when no clean version matches, and always marked so a reader knows it is not "real" logic
(oot `FAKE_MATCH`/`// fake` comments, SM64 `#ifdef AVOID_UB`, Melee `/// @todo fake`, mm `//! @bug`):
- Tolerated, comment required: temporaries that only exist for register allocation, statement
  reordering, `do {} while (0)`, extra parens/casts for `extsh`/`extsb`, `volatile` locals/tables,
  `#pragma dont_inline`/`#pragma optimization_level`, inline helpers that reproduce an original inline
  (§13 of decomp_knowledge.md). Mark: `/* FAKEMATCH: <what it forces> */`.
- Add a project macro `FAKEMATCH` comment tag and `NONMATCHING` guard: unmatched bodies live behind
  `#ifdef NONMATCHING` with the asm fallback, so the build never ships a lie (oot/mm/SM64/Melee all do).
- **Forbidden (slop):** permuter output kept verbatim (`temp_r3_2`, `var_r31`, `phi_*` names, nonsense
  `if (x) {}`), `goto` chains not in the original control flow, unused locals left behind,
  pointer-offset arithmetic, names copied from m2c (`arg0`, `sp10`) in matched code, duplicate struct
  views, commented-out dead attempts, numbered copy-paste helpers (`helper2`, `helper3`).

### Renaming without breaking a match
- Rename in C, header and `config/GYQE01/**/symbols.txt` in one commit; rebuild; run `find_matches.py`
  and compare the count to before. Never rename a symbol only in C (the linker map diverges).
- Changing a field type (`s32`→enum, `u8`→`BOOL8`) can change codegen (sign/zero extension, compare
  width): always re-diff the functions touching that field, not just the one you edited.
- Moving data definitions between units can change addressing (same-TU anchor; see `gap_8001E460.c`
  header): don't move tables across files without a full rebuild + diff.

## 2. Cleanup checklist for matched code
Per file, then `ninja && python3 tools/find_matches.py` (count must not drop):
- [ ] Replace file-local `extern` prototypes with the owning header's include.
- [ ] Merge duplicate struct views of one global into one type (biggest wins first, e.g. `lbl_800E8558`).
- [ ] Rename `argN`/`varN`/`temp_rN` locals to roles (`charID`, `slot`).
- [ ] Replace meaningful literals with enums (`0x36` → `CHAR_COUNT` / `CHAR_NONE`).
- [ ] Add a one-line summary to each function; add `/* 0xNN */` offsets to struct fields.
- [ ] Tag every matching trick `/* FAKEMATCH: ... */`; delete dead code and old attempts.
- [ ] Add size asserts to structs you touched.
- [ ] Group includes at the top (system, project, local), no includes after declarations.
- [ ] Repeated casts of the same buffer (`((RootHeader*)obj->buf)->x` ×8) → one typed local, *if* it
      still matches; otherwise keep and mark FAKEMATCH.
- [ ] Rename the unit off `gap_` once its subsystem is clear.

## 3. Tooling, ranked by value/effort
1. **`tools/lint_quality.py`** (extend `check_pointer_arithmetic.py`; ~250 lines, 1 day). Checks:
   `extern` declarations inside .c files whose symbol is declared in a header; same global declared
   with different types across headers (`lbl_800E8558`: 4 types); duplicate `typedef struct X`
   names; m2c leftovers (`temp_r\d`, `var_r\d`, `sp[0-9A-F]+`, `arg\d` in matched fns); functions
   without a preceding comment; per-file `unk` density and literal-number density; matching tricks
   without a `FAKEMATCH` tag. Output a per-file score so cleanup can be prioritised. Highest value.
2. **Rename tool** `tools/rename_symbol.py old new` (~150 lines): rewrites symbols.txt, src, include,
   and .agent docs atomically, then runs ninja + find_matches. Removes the main fear of renaming.
   (Melee/tp use similar scripts; decomp-toolkit symbols.txt is the source of truth.)
3. **CI gate** (GitHub Action or a `ninja check` target; ~50 lines): build, `find_matches` count
   ≥ baseline, lint in "no new violations" mode (baseline file), so quality ratchets up
   (oot/mm/Melee/tp all run build+progress CI; Melee runs clang-format check).
4. **Size/offset asserts generator** (~100 lines): from struct definitions + known sizes in
   `in_game.h`, emit `STATIC_ASSERT`s; flags structs whose size disagrees with Ghidra.
5. **clang-format** (config tweak, ~1 hour + one mass-format commit): a `.clang-format` already
   exists; check it covers `src/game` `src/menus` `src/Unknown`, set `SortIncludes: false`
   (include order can affect pragma state), `ReflowComments: false`, `ColumnLimit: 120`, and
   exclude SDK/Musyx. Formatting never changes codegen, but verify with a full diff once.
6. **Progress categories** in `configure.py` (dtk-template `progress_categories`): split game / menus /
   SDK so the "game logic" percentage shows on decomp.dev. ~20 lines.
7. **Documented-symbol progress** (pmret/oot track "documented" vs "matched"): count named vs
   `fn_`/`lbl_` symbols per unit; ~60 lines on top of the lint.

## 4. Current state: top problems found (sampled files)
1. **Duplicate struct views of one global.** `lbl_800E8558` is declared as four different types:
   `include/Unknown/gap_800506E8.h:94` (`Gap800506E8Character`), `include/Unknown/gap_8002244C.h:134`
   (`Gap8002244CStageEntry`), `include/Unknown/gap_8004CA48.h:65` (`Gap8004CA48CharInfo`),
   `include/menus/gap_3C03C.h:53` (`MenusLineupChoice`); `include/menus/gap_1254.h:81` even comments
   on the conflict. Also duplicate typedef names repo-wide (`ActLayout`, `ANIMBank`, `KeyFrame`,
   `Control`, `MenuUiSequence`, ...).
2. **Externs and includes scattered through .c files.** `src/menus/gap_1254.c:2-32`: 16 local
   `extern`s interleaved with 12 `#include`s, untyped helpers (`fn_800506E8`, `fn_80050FE8`) with
   no header. Ghidra-name junk leaks into identifiers (`randRange_FUN_80042bf0`, line 14).
3. **Placeholder names everywhere.** 114 of 266 source files are `gap_*`; types are prefixed with
   the file (`Gap8001196CStadiumObj`, 93 `Gap*` mentions in `include/Unknown/gap_8001196C.h`);
   `include/game/UnknownHomes_Game.h` has 255 `unk` lines. Globals like `lbl_803CBC1C`,
   `lbl_803CBC0C` in `src/Unknown/gap_8001196C.c:43-44` are clearly "current load obj" and "load
   busy" and already described in comments but not named.
4. **Magic numbers with meaning.** `src/menus/gap_1254.c:720` `c == 0x36` (charID count / none);
   `lbl_2_bss_100B4 = 1` (lines 634, 972, 1060) with no name for the flag; `0x0000040B` in every
   row of `src/Unknown/gap_8001E460.c:10+` (a file-type/flag constant).
5. **Cast noise and unmarked tricks.** `src/Unknown/gap_8001196C.c:66-90` repeats
   `((Gap8001196CRootHeader*)obj->buf)->...` eight times and indexes `((u32*)obj->buf)[...]` instead of
   using the `root` local it already has; if that is needed for the match it must say so. No
   FAKEMATCH/NONMATCHING convention exists in the repo (0 uses); `#pragma dont_inline on`
   (`gap_8001196C.c:38`) is not explained. Stubs (`return;` bodies, `gap_8001196C.c:3-36`) are
   fine as placeholders but should be grouped/marked as unmatched.
Good examples to copy: the provenance comment on the generated tables (`gap_8001E460.c:3-6`), the
behavioural comments on `finishSubItemLoad` (`gap_8001196C.c:48-51`), the handedness note
(`gap_1254.c:27`), and the small saturating helpers (`gap_1254.c:44-67`) (which only need names
like `SatAddS16`).

## 4a. First cleanup pass (2026-10-24, branch `code-quality`)
Scope: `src/menus/gap_1254.c`, `src/Unknown/gap_8001196C.c` and the stubs their externs point at.
Match count 3967 before and after; no function's fuzzy score dropped.
- **Prototypes:** stubs `randRange`, `sndFXRelated`, `fn_80066EAC`, `fn_80050FE8`, `fn_8004EEF4`,
  `fn_80050138`, `fn_800625A4` now carry caller-compatible signatures in header and definition (were `(void)`).
  These remain provisional C types until the bodies are decompiled: for example, the target masks
  `sndFXRelated`'s input to 16 bits and `fn_80066EAC`'s side to 8 bits; an `s32` caller declaration
  alone does not prove the original parameter width.
  `randRange_FUN_80042bf0` renamed `randRange` (symbols.txt too).
- **Rule 6 is blocked by duplicate struct views.** Every `Unknown/gap_8*.h` that `gap_1254.c` needs
  fails to include there: each declares its own type for a shared global (`lbl_803297E0`,
  `lbl_80361B20`, `lbl_803C66B0`, `fn_80034CEC`'s argument, ...). So `gap_1254.c` keeps one grouped,
  commented block of externs; the two disagreements are listed below. Merging the views is its own issue.
- **Two prototypes cannot agree yet:** `fn_800506E8`'s matched body needs `(s8, s32, BOOL)` but its
  callers in `gap_1254.c` only match with `s32` (4 functions unmatch otherwise; marked FAKEMATCH).
  `fn_80067B40` (unmatched) has a different signature in its header than at its callers.
- **Magic numbers:** charID checks use `CHAR_ID_NONE` / `NUM_CHOOSABLE_CHARACTERS`.
- **Names:** `satAddS16/U8/U16/S32` (were `fn_2_12A0/12CC/12F8/1328`), `g_subItemLoadObj`,
  `g_subItemLoadBusy` (were `lbl_803CBC1C`, `lbl_803CBC0C`).
- **`#pragma dont_inline` was harmful.** All seven pragma lines in `gap_8001196C.c` were removed:
  no match changed, and the helpers now inline, taking `fn_80012B90` from 26% to 88% and
  `fn_80013680` from 32% to 81%. Lesson: test a pragma by deleting it.
- **Repeated `obj->buf` casts are load-bearing** in `finishSubItemLoad`: using the `root` local makes
  `fn_80012B90` worse. Review reproduced 330 → 437 feedback lines by replacing only the repeated
  named-field casts with `root->`; the earlier 140-line figure did not reproduce. Kept and marked FAKEMATCH.
- `STATIC_ASSERT` added to `mssbTypes.h`, first use on `MenusTeamSelections` (0x5C).

## 5. Python modding-tool guidelines (tools/modding, tools/datamap)
- Stdlib only, Python 3.8+ (no walrus-heavy 3.10 syntax: no `match`, no `X | Y` types); `pathlib`
  everywhere, never hard-coded `/` paths; open binaries with `"rb"`/`"r+b"`, text with
  `encoding="utf-8"` (Windows default is cp1252).
- Structure: one module per format (descriptor table, text bank, ISO/FST) with pure parse/build
  functions; CLI in `main()` via `argparse`; GUI (tkinter) only calls those functions.
- Offsets/sizes/table counts come from one constants module that cites the `.agent` doc section or
  the decomp symbol (`lbl_800EFD38`); never duplicate them in GUI code.
- Type hints on public functions; `struct` format strings named (`DISK_DESC = struct.Struct(">IIII")`;
  big-endian always).
- Tests: `unittest`, round-trip (parse → build == original bytes) against a small fixture, plus a
  test that each table's count matches the C declaration. Run on Windows and Linux.
- Never write in place without a backup; refuse unknown game IDs (check `GYQE01`).

## Sources
- zeldaret/oot STYLE.md: https://github.com/zeldaret/oot/blob/main/docs/STYLE.md
- zeldaret/oot CONTRIBUTING: https://github.com/zeldaret/oot/blob/main/docs/CONTRIBUTING.md
- zeldaret/mm STYLE.md: https://github.com/zeldaret/mm/blob/main/docs/STYLE.md
- zeldaret/tp: https://github.com/zeldaret/tp
- pret pokeemerald: https://github.com/pret/pokeemerald (and wiki https://github.com/pret/pokeemerald/wiki)
- SM64 decomp: https://github.com/n64decomp/sm64
- Paper Mario (pmret): https://github.com/pmret/papermario (CONTRIBUTING.md)
- Melee: https://github.com/doldecomp/melee (CONTRIBUTING.md, .clang-format, CI)
- Pikmin: https://github.com/projectPiki/pikmin
- dtk-template: https://github.com/encounter/dtk-template (progress categories, symbols.txt workflow)
- decomp-toolkit: https://github.com/encounter/decomp-toolkit
- decomp.me / permuter: https://decomp.me , https://github.com/simonlindholm/decomp-permuter
- Linux kernel coding style: https://www.kernel.org/doc/html/latest/process/coding-style.html
- SEI CERT C: https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard
- Barr Group Embedded C: https://barrgroup.com/embedded-systems/books/embedded-c-coding-standard
- LLVM coding standards: https://llvm.org/docs/CodingStandards.html
- Python packaging/testing: https://docs.python.org/3/library/unittest.html , https://docs.python.org/3/library/pathlib.html
