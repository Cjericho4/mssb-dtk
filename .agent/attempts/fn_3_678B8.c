/* fn_3_678B8 NONMATCHING (not attempted beyond analysis): hits the Known Unfixable
 * "file-static bss block off one base with array members" pattern -- lbl_3_bss_200 (r31) and
 * lbl_3_data_6820 (r30) array sub-bases are formed as addi base,off + add idx*stride
 * (e.g. addi r5,r31,0x320; add r5,r5,mulli(idx,0x5a0)). Also needs a 10-arg prototype for
 * fn_3_67EF0 (r3..r10 + f1, with __cvt_fp2unsigned of bss.unk14A8) returning s32.
 */
