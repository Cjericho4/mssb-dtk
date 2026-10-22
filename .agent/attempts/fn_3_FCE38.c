// Best attempt (13 sbs lines): two while loops over elems[arg0]/elems[arg0-1] (no pointer arithmetic). Left: p/IV regs swapped (target computes arg0<<6 before loading DE94) and the shared reset block (both forward-loop exits jump to `slwi r6,r3,6` at the end + dead `b`).
s32 fn_3_FCE38(s32 arg0, f32 arg1) {
    Struct_DE94_Inner* p = lbl_3_common_bss_DE94;
    s32 count = p->unk3C;

    while (arg0 < count && arg1 > ((DE94ArrayElement*)p->unk34)[arg0].value) {
        arg0++;
    }
    while (arg0 > 0 && arg1 <= ((DE94ArrayElement*)p->unk34)[arg0 - 1].value) {
        arg0--;
    }
    return arg0;
}
