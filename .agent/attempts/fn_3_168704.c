/* fn_3_168704 NONMATCHING (src/game/rep_3F60.c) - skipped after one check.
   Known-unfixable same-file static data off one base register: r31 = &lbl_3_data_285A8 and all data is
   addressed relative to it (+0x360/+0x36C byte arrays = lbl_3_data_28908/28914, +0x120 2D struct array,
   'addi r3,r31,0xd8; lwz 0x34(r3)' = lbl_3_data_28680[13] with an unfolded sub-base, even 'addi r3,r31,0x0').
   Same reason sibling fn_3_168DFC was skipped. Queue obj is Rep3F60QueueObj (r30 = lbl_803CC1B8). */
