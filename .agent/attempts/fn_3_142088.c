/* fn_3_142088 (rep_37A8.c) NONMATCHING best attempt (~58 diff lines, mostly register numbering).
 * The texel index is fn_3_142030(x, y, 4) inlined; target keeps (y/4)*16 in r5 and (y%4)*4 in r6 and sums
 * ((x/4)*16 + r6) + x%4, then r5 + that; no ordering of the 4 terms reproduces that exact association
 * (brute-forced all permutations/groupings). Also needs `#include "Dolphin/gx.h"` in rep_37A8.c.
 */
/* Overlay of the file-static bss block at lbl_3_bss_B7C0. */
typedef struct {
    u8 unk0;            /* 0x00 */
    u8 unk1;            /* 0x01 (lbl_3_bss_B7C1) */
    u8 _pad2[2];
    GXTexObj texObj;    /* 0x04 */
    s32 unk24;          /* 0x24 (lbl_3_bss_B7E4) */
    u8 _pad28[0x40 - 0x28];
    u8 tex[0x40];       /* 0x40 (lbl_3_bss_B800) */
} Rep37A8Bss;
extern Rep37A8Bss lbl_3_bss_B7C0;

static inline s32 texelIndex(s32 a, s32 b, s32 c) {
    s32 bq = b / 4;
    s32 br = b % 4;
    return br * 4 + (a / 4) * 16 + bq * 4 * c + (a % 4);
}

// .text:0x00142088 size:0x1D4 mapped:0x8078111C
void fn_3_142088(void) {
    Rep37A8Bss* bss = &lbl_3_bss_B7C0;
    u32 y;
    s32 x;
    u32 off;
    u8* p;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            off = texelIndex(x, y, 4) * 4;
            if (off < 0x20) {
                p = bss->tex;
                p += off;
                p[0] = p[2] = 0xFF;
                p[1] = p[3] = 0x96;
            } else {
                p = bss->tex;
                p += off;
                p[0] = p[2] = 0;
                p[1] = p[3] = 0;
            }
        }
    }
    GXInitTexObj(&bss->texObj, bss->tex, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&bss->texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    bss->unk24 = 0;
    lbl_3_data_266A4 = -1;
    bss->unk1 = 0;
}

