/* fn_3_169600 NONMATCHING (9 diff lines): only the first nested loop's register use differs.
 * Target: outer counter r29, inner r28, and a copy 'mr r30, r29' at the top of each outer iteration used as
 * the y arg (no separate increment). Every form (y = i in body/for-init, inline helper param, block-local copy,
 * variable reuse with 2nd loop) gets copy-propagated; best (below) keeps a separately incremented y.
 * Needs kinoko.h: anonymous union over KinokoState._unk08 { s32 counter; GXTexObj tex0C, tex2C; u8 _pad4C[0x14]; u8 buf60[0x40]; u8 bufA0[0x40]; }
 * plus in kinoko.c: extern s8 lbl_3_data_2A330; u32 fn_800247E4(s32 x, s32 y, s32 w, s32 h); */
void fn_3_169600(void) {
    u32 x;
    u32 i;
    u32 y;
    u32 off;
    u8* p;
    KinokoState* state = &lbl_3_bss_BA00;

    for (i = 0, y = 0; i < 4; i++, y++) {
        for (x = 0; x < 4; x++) {
            off = fn_800247E4(x, y, 4, 4);
            if (off < 0x20) {
                p = state->bufA0;
                p += off;
                p[0] = p[2] = 0xFF;
                p[1] = p[3] = 0x9B;
            } else {
                p = state->bufA0;
                p += off;
                p[0] = p[2] = 0;
                p[1] = p[3] = 0xFF;
            }
        }
    }
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            off = fn_800247E4(x, y, 4, 4);
            if (off < 0x20) {
                p = state->buf60;
                p += off;
                p[0] = p[2] = 0xFF;
                p[1] = p[3] = 0;
            } else {
                p = state->buf60;
                p += off;
                p[0] = p[2] = 0x9B;
                p[1] = p[3] = 0xFF;
            }
        }
    }
    GXInitTexObj(&state->tex2C, state->bufA0, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&state->tex2C, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXInitTexObj(&state->tex0C, state->buf60, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&state->tex0C, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    lbl_3_data_2A330 = -1;
    state->counter = 0;
}
