/* fn_3_EECF4 NONMATCHING (sta_c5.c). Needs header carve in StaC5Bss_AEE0: 0x38 u8 unk38[0x200]; 0x238 u8* noiseTex; 0x23C Mtx23 indMtx; 0x254 GXTexObj noiseTexObj.
 * Plus externs lbl_3_rodata_2DB8/2DC4 (char[]), fn_800247E4 proto.
 * Remaining diff: target keeps bss base in r30 for the whole fn and stores mtx[0][0] via r30, rest via r4=&indMtx;
 * ours folds all mtx stores to r30 offsets and rematerializes lis/addi AEE0 around the fn_3_B9534 call. Loop body matches. */
void fn_3_EECF4(void) {
    StaC5Bss_AEE0* bss = &lbl_3_bss_AEE0;
    u32 y;
    u32 x;
    u32 off;

    f32 (*m)[3] = bss->indMtx;

    m[0][0] = 0.01f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 0.01f;
    m[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    bss->noiseTex = fn_3_B9534(16, 16, &bss->noiseTexObj);
    if (bss->noiseTex == NULL) {
        OSPanic(lbl_3_rodata_2DB8, 0x1028, lbl_3_rodata_2DC4);
    }
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            off = fn_800247E4(x, y, 16, 2);
            bss->noiseTex[off] = (u8)(rand() % 200) + 0x1B;
            bss->noiseTex[off + 1] = (u8)(rand() % 200) + 0x1B;
        }
    }
    memset(bss->unk38, 1, 0x200);
}
