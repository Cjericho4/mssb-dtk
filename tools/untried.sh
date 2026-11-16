#!/bin/sh
# usage: tools/untried.sh [module] [max-size]     (defaults: dol 300)
# Lists unmatched functions nobody has attempted yet: score_functions.py output minus every
# name found in queue.log, working_progress.md, .agent/*_notes.md and .agent/attempts/.
# Sorted by size. A function with a body in src/ but no log entry still shows up: check it
# with tools/sbs.py before starting over.
mod=${1:-dol}; max=${2:-300}
python3 tools/score_functions.py --module "$mod" --max-size "$max" --limit 1000 2>/dev/null |
    awk '$4 ~ /dol|game|menus|challenge/ {print $1, $2, $NF}' |
    while read fn sz unit; do
        grep -qlw "$fn" queue.log working_progress.md .agent/*_notes.md .agent/attempts/* 2>/dev/null ||
            echo "$sz $fn ${unit##*/}"
    done | sort -n
