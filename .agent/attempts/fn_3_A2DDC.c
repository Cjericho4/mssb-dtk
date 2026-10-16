/* fn_3_A2DDC NONMATCHING (src/game/rep_18E8.c) - skipped after one check.
   Uses the known-unfixable lbl_3_bss_17F8 file-static block pattern: r31 = &lbl_3_bss_17F8 with
   unfolded sub-bases (addi r3,r31,0x10 / addi r30,r31,0x10 then constant-offset loads). MWCC folds a
   local sub-object pointer into the base displacement (see .scratch/fn_3_A295C.c for an overlay attempt). */
