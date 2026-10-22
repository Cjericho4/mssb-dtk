// Best attempt (7 sbs diff lines): goto-structured loop with the count/IV init block at the end reproduces the target layout incl. the stray blr; left: p in r5 vs r6 (IV swap) and one extra trailing blr after the final `goto check`.
s32 fn_3_FCEB0(f32 arg0) {
    s32 i = 0;
    Struct_DE94_Inner *p = lbl_3_common_bss_DE94;
    s32 count;

    if (arg0 < lbl_3_rodata_3100) {
        return -1;
    }
    goto init;
loop:
    i++;
check:
    if (i >= count) {
        goto done;
    }
    if (arg0 > ((DE94ArrayElement *)p->unk34)[i].value) {
        goto loop;
    }
done:
    if (i >= count) {
        return -1;
    }
    return i;
init:
    count = p->unk3C;
    goto check;
}
