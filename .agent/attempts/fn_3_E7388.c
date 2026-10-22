// Best attempt (18 sbs lines, from a stub): both countdown loops/stores match; left: first loop i is a copy of the count-1 temp (mr r8,r3) and second loop p/elem regs swapped (r3/r4). Separate pointer locals, CSE forms and decl orders did not move it.
void fn_3_E7388(s32 unused, E7388Out* out) {
    E7388Out* p;
    StadiumObjectElem* elem;
    s32 i;

    p = out;
    i = lbl_3_common_bss_350E4[0].memcpyCount - 1;
    elem = &lbl_3_common_bss_350E4[0].src[lbl_3_common_bss_350E4[0].memcpyCount - 1];
    do {
        if (!elem->flag90_80) {
            p->id = i;
            p++;
        }
        elem--;
    } while (i-- != 0);
    i = lbl_3_common_bss_350E4[0].memcpyCount - 1;
    elem = &lbl_3_common_bss_350E4[0].src[i];
    p = &out[lbl_3_common_bss_350E4[0].memcpyCount];
    do {
        if (elem->flag90_80) {
            p--;
            p->id = i;
            p->val = 1.0f;
        }
        elem--;
    } while (i-- != 0);
}
