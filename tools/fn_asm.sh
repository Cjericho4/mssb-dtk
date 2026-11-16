#!/bin/sh
# usage: tools/fn_asm.sh <function>
# Prints the target assembly of one function (address/byte columns stripped) from the dtk-split
# asm of the last build, then every place the name appears in src/ and include/ (stub, callers,
# prototypes). Faster to read than initialize_function.py when you only need the asm.
f=$(grep -l "^\.fn $1," build/GYQE01/asm/Unknown/*.s build/GYQE01/game/asm/game/*.s \
    build/GYQE01/menus/asm/menus/*.s build/GYQE01/challenge/asm/challenge/*.s 2>/dev/null | head -1)
[ -z "$f" ] && { echo "no asm for $1 (run ninja first?)" >&2; exit 1; }
awk -v fn="$1" '$0 ~ "^\\.fn "fn","{p=1} p{print} $0 ~ "^\\.endfn "fn{p=0}' "$f" |
    sed 's#/\* [0-9A-F]* [0-9A-F]*  .. .. .. .. \*/##' | cut -c1-100
grep -rn "\b$1\b" src include 2>/dev/null | cut -c1-160 | head -12
