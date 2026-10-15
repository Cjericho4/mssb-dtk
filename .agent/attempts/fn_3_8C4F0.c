BOOL fn_3_8C4F0(u32 div, u8 thresh) {
    Bss1760* s = &lbl_3_bss_1760;
    u16 v;
    u8 hi;
    u8 lo;
    s16 d;
    u8 active;

    v = fn_800A8864();
    active = s->active;
    lbl_3_common_bss_34C58._2F = 0;
    hi = v >> 8;
    lo = v;
    if (active == 0) {
        s->active = 1;
        s->hi = hi / div;
        s->lo = lo / div;
    }
    d = hi - s->hi;
    if (d <= thresh || div == 1) {
        s->active = 0;
        fn_800A8878(thresh, thresh);
        return FALSE;
    }
    fn_800A8878(d, lo - s->lo);
    return TRUE;
}
