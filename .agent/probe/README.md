# Probe harness (one compile, many variants)

Put N variants of one function (different names) in a scratch `.c` file that includes the same
headers as the unit, then:

    .agent/probe/probe.sh path/to/variants.c        # mwcc with the game flags, then dtk elf disasm -> variants.s
    python3 .agent/probe/tail.py variants.s 12       # last 12 instructions of every variant
    python3 .agent/probe/check3.py variants.s 5      # group identical tails, rank by distance to the target in the script
    python3 .agent/probe/bytail.py variants.s        # one line per distinct tail with the variant's source body

`check3.py` carries the fn_3_70768 target tail; edit `target` for another function. The `.s` is produced by
`dtk elf disasm`, so rodata literals show as `"@NNN"` instead of `lbl_3_rodata_*` (those lines are not real diffs).
