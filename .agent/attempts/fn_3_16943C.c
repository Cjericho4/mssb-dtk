/* fn_3_16943C NONMATCHING: only the counter access differs. Target: lis r4, lbl_3_bss_BA00+0x8@ha; lwzu r3, lbl_3_bss_BA00+0x8@l(r4); ...; stw r3,0(r4)
 * (counter accessed as its own symbol+8 with update form). Ours: lis/addi BA00 base then lwz/stw 0x8(r4).
 * Tried: union field, real struct fields (KinokoState {ptr0,ptr4,counter,buf0C,buf2C,buf60,bufA0} - fn_3_1695A4 still matches),
 * pointer to field, (&g)->field, explicit a = a + b. Possibly counter was a separate static in the original.
 * Full working-tree diff (incl. kinoko.h restructure, rep_1E08.h include, externs) in .scratch/fn_3_16943C.diff */
void fn_3_16943C(void) {
    s32 v;
    s32 i;

    lbl_3_bss_BA00.counter += (lbl_80366158._28 == 0);
    if (lbl_3_bss_BA00.counter & 1) {
        return;
    }
    v = lbl_3_bss_BA00.ptr0[fn_800247E4(0, 0, 4, 4)];
    v += lbl_3_data_2A330 * 2;
    if (v > 0xFF) {
        v = 0xFF;
    } else if (v < 0) {
        v = 0;
    }
    for (i = 0; i < 32; i += 2) {
        lbl_3_bss_BA00.ptr0[i] = v;
    }
    DCFlushRange(lbl_3_bss_BA00.ptr0, 4);
    if (v + lbl_3_data_2A330 * 2 > 0xFF || v + lbl_3_data_2A330 * 2 < 0) {
        lbl_3_data_2A330 *= -1;
    }
}
