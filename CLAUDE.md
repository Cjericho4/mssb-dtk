# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a matching decompilation project for Mario Superstar Baseball (GameCube, GYQE01). The goal is to create C code that, when compiled with Metrowerks CodeWarrior GC/1.3.2, produces the exact same binary as the original game.

Progress is tracked at: https://decomp.dev/roeming/mssb-dtk

## Project Structure

- `src/` decompiled (or partially decompiled) C code
  - `src/game/` main game logic (~95 files, primary decompilation focus)
  - `src/Dolphin/` Dolphin SDK framework code
  - `src/C3/` C3 audio library
  - `src/Musyx/` Musyx music system
- `include/` headers for decompiled C code
  - `include/game/UnknownHomes_Game.h` major game structs (Batter, Pitcher, Runners, etc.)
  - `include/UnknownHeaders.h` global structs for symbols identified via Ghidra (e.g. `hugeAnimStruct`)
  - `include/mssbTypes.h` core type definitions (BOOL, Vec3D, etc.)
- `config/GYQE01/` symbol addresses, code/data splits, and build configuration
  - `symbols.txt` top-level DOL symbols with absolute addresses (`fn_80XXXXXX`, `lbl_80XXXXXX`)
  - `game/symbols.txt` game REL symbols with section-relative addresses (`fn_3_XXXX`, `lbl_3_XXXX`)
  - `challenge/symbols.txt` challenge REL symbols (`fn_1_XXXX`, `lbl_1_XXXX`)
  - `menus/symbols.txt` menus REL symbols (`fn_2_XXXX`, `lbl_2_XXXX`)
  - `splits.txt` for code/data section splits
- `build/GYQE01/` generated build artifacts (asm, obj files)
- `orig/GYQE01/` original game files (main.dol, REL files)
- `tools/` custom Python decompilation and build tools
  - `tools/aidecomp/` ADS Dashboard web app (FastAPI + uvicorn)
- `.agent/` AI agent workflow files and knowledge base. **Start at `.agent/INDEX.md`**: it says which doc sections to read per task; grep `.agent/addresses.md` for any address or table name instead of reading whole docs.
- `exported_symbols.csv` Ghidra-exported symbols with names, addresses, types, namespaces, and ref counts
- `in_game.h` Ghidra-exported C definitions (structs, enums, typedefs, function prototypes)

## Build System

The project uses **Ninja** with Python-based configuration:

```bash
# Configure (generates build.ninja)
python3 configure.py

# Build
ninja

# Build and check progress
ninja report
```

The toolchain consists of:
- **Metrowerks CodeWarrior** (GC/1.3.2) via **WiBo** wrapper on Linux
- **decomp-toolkit (dtk)** for binary manipulation and linking
- **objdiff-cli** for binary diffing and match verification
- **PowerPC binutils** for assembly

## Tools

- `./decomp.sh <function_name>` find the source file, module, and target assembly for a function.
- `./decomp.sh --m2c <function_name>` auto-decompile a function from assembly to C using m2c.
- `python3 tools/feedback_diff.py <function_name>` compare compiled output against target assembly. Reports `MATCH!` on success or line-by-line instruction differences. Can also take explicit unit: `python3 tools/feedback_diff.py <unit_name> <function_name>`.
- `python3 tools/kappa_context.py <function_name>` gather decompilation context: assembly, dependencies (bl calls), and referenced symbols.
- `python3 tools/decomp_helper.py <function_name>` locate a function's source file, address, module, and extract its assembly.
- `python3 tools/m2c_helper.py <function_name>` run m2c decompiler with full compilation context to generate initial C code.
- `python3 tools/score_functions.py [--module MODULE] [--max-size N] [--min-size N]` find the easiest unmatched functions to decompile, ranked by size.
- `python3 tools/check_pointer_arithmetic.py <file_or_directory>` detect pointer arithmetic with casts that should be replaced with struct field access. Use `--strict` to fail on violations.
- `python3 tools/find_matches.py report.json` list functions that are already 100% matched.
- `python3 tools/try_function.py <src_file> <function> <candidate.c> [--keep]` swap one function's definition for a candidate, build, and diff; restores the file unless it matches.
- `python3 tools/rodata_value.py <lbl_3_rodata_XXXX>...` print constant values so `extern` rodata floats can be written as literals.
- `python3 tools/literalize_rodata.py` sweep unmatched game functions replacing extern rodata floats with literals, keeping only improvements (slow; runs ninja repeatedly).
- `python3 tools/sbs.py <function> [unit]` side-by-side target/current asm from the last build (best for register swaps).
- `python3 tools/brute.py <src_file> <function> <template.c> [limit]` permute the lines between `//PERM_BEGIN` and `//PERM_END` in a candidate (decl/statement order) via try_function.py until MATCH.
- `.agent/workflows/parallel_batch.md` how to run a 100-function batch with 4 parallel worktree agents and merge it.
- `.agent/attempts/` best non-matching attempts (indexed in working_progress.md's Almost Matched table).
- `.agent/categorize/functions.csv` per-function category/difficulty for unmatched game functions (Codex-generated heuristic; use for picking batches).
- **ADS Dashboard** (`python3 tools/aidecomp/server.py`, http://localhost:8000) — Web UI for decompilation, symbol lookup, and the **Symbols DB** browser.

## Code Quality Standards

### Rules (full text and rationale: `.agent/code_quality.md` §1)

Apply these rules to new or cleaned-up game code. Legacy violations outside the cleanup scope
can remain for a separate pass; SDK/library interfaces retain their established API types and names.

1. **Name only what you understand.** Otherwise keep `fn_`/`lbl_` and offset-based field names.
   Rename in C, headers and `config/GYQE01/**/symbols.txt` in one commit, then rebuild and check matches.
2. **Naming:** named global variables use `g_camelCase`, file-static variables `s` + camelCase,
   and static helpers lowerCamel (`satAddS16`). Preserve established subsystem conventions for
   external functions. Remove Ghidra junk suffixes (`randRange_FUN_80042bf0` → `randRange`).
3. **Struct fields:** new unknown fields use `unk_0xNN`; existing layouts also use `unkNN`/`unkN`.
   Once understood, use a real name with a `/* 0xNN */` offset comment. Padding uses `_padNN[]`
   (or a scalar byte for one byte), never a name that implies meaningful data.
4. **One type per memory object, one prototype per function.** Include the owning header rather
   than repeating declarations. Existing conflicting struct views may block inclusion; document
   the conflict and any prototype disagreement until the types can be reconciled. A `FAKEMATCH`
   note explains codegen, but does not establish type correctness. Stubs need evidence-backed
   parameter/return declarations, not placeholder `(void)` signatures.
5. **`STATIC_ASSERT(sizeof(T) == 0xNN)`** (`mssbTypes.h`) after non-trivial structs with known complete
   layouts, especially those used as table elements or strides. Add offset checks where needed;
   do not claim the size of a partial view is the full object's size.
6. **Use typed structs for objects, not `void*` or manual byte offsets** (see "Struct Usage" below).
   File-buffer relocation may convert offsets to pointers inside a clearly named relocation helper.
7. **No meaningful magic numbers:** charIDs use `CHAR_ID` (`CHAR_ID_NONE`, `NUM_CHOOSABLE_CHARACTERS`);
   use existing constants or add an enum/`#define` for other IDs, counts and flags. Pure arithmetic
   literals and saturation limits are fine.
8. **One-line summary above every non-trivial implemented function** saying what it does for the game,
   with units (frames, cents, fixed-point) where relevant. Keep the `// .text:0x... size:0x...` header.
   Empty unmatched stubs do not need invented descriptions.
9. **Mark every matching trick** with `/* FAKEMATCH: <what it forces> */`: register-only temporaries,
   odd casts, reordered statements, pragmas, inlines kept only for codegen. Delete a pragma when
   removing it preserves matches and does not regress affected functions.
10. **No slop in committed code:** no m2c names (`temp_r3`, `var_r31`, `arg0`, `sp10`) in matched
    functions, no commented-out attempts, no unused locals, no numbered copy-paste helpers.

### Struct Usage

**Do not access object fields through manual byte offsets.** Define and use proper structs.
File-buffer relocation is the limited exception described in rule 6.

**Use typed arguments and return values for game objects.** Name structs after their usage.
Preserve SDK/library APIs; opaque file buffers can use byte pointers until their layout is understood.

**BAD - Pointer Arithmetic:**

```c
f32 getField(void* arg0) {
    return *(f32*)((u8*)arg0 + 0x94);
}
```

**GOOD - Proper Structs:**

```c
// In the appropriate header file
typedef struct {
    u8 _pad0[0x94];
    f32 someField;  // 0x94
} SomeStruct;

f32 getField(SomeStruct* object) {
    return object->someField;
}
```

### Struct Definition Guidelines

When you see pointer arithmetic patterns like `*(type*)((u8*)ptr + offset)`:

1. **Identify the access pattern:**
   - What offset is being accessed? (e.g., `0x94` means field at offset 148)
   - Is it accessing an array element? (e.g., `idx * 36` means 36-byte elements)
   - What field within the element?

2. **Create appropriate structs:**
   - Define the struct with correct field offsets
   - Use meaningful names or `unk_0x[Offset]` naming convention
   - Always check `include/game/UnknownHomes_Game.h` for existing struct layouts

3. **Verify struct sizes:**
   - Calculate total size to ensure it matches any array multiplier
   - Ensure offsets align with the assembly's load/store offsets

### When Decompiling

If you write code with pointer arithmetic:
- **STOP immediately**
- Create proper struct definitions first
- Then write the function using struct access
- This applies to object-field access; use the rule 6 helper exception for file relocation.

## Tasks

### Decompile a function to C code

Follow the iterative decompilation workflow:

1. **Initialize**: Run `./decomp.sh <function_name>` to identify the source file, module, and target assembly.
2. **Gather context**: Run `python3 tools/kappa_context.py <function_name>` for dependencies and symbols.
3. **Optionally get m2c output**: Run `./decomp.sh --m2c <function_name>` for an initial C approximation.
4. **Implement**: Open the identified source file and write the C implementation.
5. **Iterate** (max 10 attempts):
   a. Compile: `ninja`
   b. Diff: `python3 tools/feedback_diff.py <function_name>`
   c. If `MATCH!` → done. Otherwise analyze feedback and refine.
6. **If matched**, commit with message `matched <function_name>`.
7. **If not matched** after attempts, document the remaining differences and best attempt.

### Find easy functions to decompile

Use `python3 tools/score_functions.py` to find small, simple unmatched functions. Start with the smallest ones as they are typically easiest to match.

### Decompile a directory of functions

1. Use `python3 tools/score_functions.py --module <module>` to find the easiest function in a module.
2. Follow the "Decompile a function" workflow above.
3. If matched, commit and return to step 1.
4. If not matched after several attempts, move on to the next function.

## Symbol Naming Conventions & Cross-Referencing

### Codebase Symbol Names
- **`fn_3_XXXX` / `lbl_3_XXXX`**: Game REL module functions/labels (section-relative addresses in `config/GYQE01/game/symbols.txt`)
- **`fn_1_XXXX` / `lbl_1_XXXX`**: Challenge REL module
- **`fn_2_XXXX` / `lbl_2_XXXX`**: Menus REL module
- **`fn_80XXXXXX` / `lbl_80XXXXXX`**: DOL functions/labels (absolute addresses in `config/GYQE01/symbols.txt`)

### Cross-Reference Workflow
To identify what a symbol really is:
1. Find the symbol's address in the appropriate `symbols.txt`
2. Look up that address in `exported_symbols.csv` to find the **Ghidra name** (e.g., `lbl_8036E548` → `hugeAnimStruct`)
3. Search `in_game.h` for the Ghidra name to get the full struct/enum/function definition
4. Create a proper typedef in `include/UnknownHeaders.h` or the appropriate header, using the Ghidra name

### Known Global Structs
- `hugeAnimStruct g_hugeAnimStruct` @ `0x8036E548` — Large animation struct (0x3154 bytes), referenced by 122 functions

## Compiler Behavior Patterns (Metrowerks CodeWarrior / PowerPC)

### Global Address Re-loading
The compiler often re-loads the base address of a global variable (using `lis`/`addi`) even if already in a register.
- **Trap**: Local pointers (`Batter* b = &g_Batter;`) cause the compiler to hold the address in one register, mismatching the original.
- **Fix**: Use direct global access (`g_Batter.field = ...;`) in distinct logical blocks.

### Structure Assignments and Update-Form Instructions
The binary uses "load/store with update" instructions (`lfsu`, `stfsu`).
- **Pattern**: Generated by structure-level assignments: `g_Runners[0].position = g_Batter.batterPos;`
- **Trap**: Point-by-point field assignment (`p.x = b.x; p.z = b.z;`) won't trigger update-form instructions.

### Register Steering ("Anchoring")
Registers `r31` and `r30` are typically used for major object base pointers.
- **Pattern**: Define a local pointer at the exact line where assembly first allocates the base register.
- **Trap**: Defining it at the top of a function causes the compiler to use a temporary register instead.

### ROData Ordering
Float constants are stored in `.rodata` in the order first encountered in C code.
- **Problem**: If your code uses `1.0f` before `0.0f` but the original did the reverse, rodata labels mismatch.
- **Fix**: Order your references to match the assembly's order.

### Casting and Sign Extension
- Use explicit casts to match `extsh` (sign-extend halfword) and `extsb` (sign-extend byte) instructions.
- Ensure `lwz` vs `lhz` vs `lbz` matches your struct field types.

## Verification

**IMPORTANT**: Always verify with a full build before declaring success.

```bash
ninja
python3 tools/feedback_diff.py <function_name>
```

The ONLY acceptable success condition is `MATCH!` from `feedback_diff.py`. A function that compiles without errors is NOT necessarily matched.

## Self-Review Checklist

Before declaring a decompilation complete, verify:

- [ ] No pointer arithmetic with manual offset calculations
- [ ] All struct field accesses use `->` or `.` operators
- [ ] No `void*` parameters that should be typed structs
- [ ] Struct sizes match the assembly access patterns
- [ ] Prototypes agree with the owning header; matching tricks carry a `FAKEMATCH` comment
- [ ] `python3 tools/find_matches.py build/GYQE01/report.json | wc -l` did not drop
- [ ] `ninja` builds successfully
- [ ] `python3 tools/feedback_diff.py <function_name>` reports `MATCH!`
