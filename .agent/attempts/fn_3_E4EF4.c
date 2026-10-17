// Best non-matching shape: 3 mismatched lines (in-tree expression form gives 4).
// Target add tree: add r0 = n*2 + n*4; add r30 = r0 + n*24; add r30 = n*4 + r30, with count in r4 / mulli in r3.
// Statement form below gets the operand order right but accumulates in r30 instead of using r0 for the
// first partial sum. Single-expression forms with the right tree (e.g. ((n*2 + n*4) + n*4) + n*24)
// swap the count/mulli registers (r3/r4) instead. 60-variant sweeps (all orders x 5 parenthesizations,
// with and without an n local) never beat 3.
void fn_3_E4EF4(void) {
    UnknownStruct_350E4* p = lbl_3_common_bss_350E4;
    u32 n = p->memcpyCount;
    u32 size;
    s32 a;
    s32 b;

    size = n * 4 + n * 2;
    size += n * 24;
    size = n * 4 + size;
    if (p->unk48 == NULL) {
        p->unk48 = _OSAllocFromHeap(4, size);
        lbl_3_common_bss_350E4[0].unk3C = (u32*)&p->unk48[p->memcpyCount * 2];
        lbl_3_common_bss_350E4[0].unk44 = lbl_3_common_bss_350E4[0].unk3C + p->memcpyCount;
        lbl_3_common_bss_350E4[0].unk40 = (u16*)(lbl_3_common_bss_350E4[0].unk44 + p->memcpyCount);
    }
    memset(p->unk48, 0, size);
    a = 0;
    b = 0;
    fn_3_E4CB0(&a, &b);
    lbl_3_common_bss_350E4[0].unk64 = a;
}
