#!/bin/bash
# usage: probe.sh file.c  -> compiles with game flags, disassembles to file.s
set -e
cd "$(dirname "$0")/../.."
src="$1"; base="${src%.c}"
build/tools/wibo build/tools/sjiswrap.exe build/compilers/GC/2.6/mwcceppc.exe -proc gekko -nodefaults -Cpp_exceptions off -RTTI off -fp hard -fp_contract on -O4,p -maxerrors 1 -enum int -inline auto -str reuse,readonly -nosyspath -use_lmw_stmw on -sdata 8 -sdata2 8 -DVERNUM=0 -i include -i include/stl -DNDEBUG=1 -sdata 0 -sdata2 0 -O4,p -sym on -inline noauto -pool off -requireprotos -lang=c -c "$src" -o "$base.o" 2>&1 >/dev/null 2>&1 || true
build/tools/dtk elf disasm "$base.o" "$base.s" >/dev/null 2>&1
echo "disasm -> $base.s"
