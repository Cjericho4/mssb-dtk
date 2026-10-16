/* fn_3_C937C (rep_21F8.c) NONMATCHING best attempt (~11 diff lines, register allocation only).
 * Remaining: around the player-entry update the target loads data->noDepth (lbz 0x2e8) into r0 before
 * computing &players[idx] (idx in r4, (base+0x26c) in r4, product in r5); here idx/flag/product land in
 * r0/r5/r4. Brute-forced statement orders and p forms.
 * File changes: replace `#include "game/rep_1E08.h"` with gx.h + UnknownHeaders.h and the local
 * declarations below; prototype in rep_21F8.h becomes `BOOL fn_3_C937C(void);` (fn_3_C937C.headers.diff).
 */
typedef struct Rep21F8Player {
    u8 _pad0[4];
    s32* frameSrc;  /* 0x04 */
    u8 _pad8[0x14 - 0x8];
    f32 time;       /* 0x14 */
} Rep21F8Player; /* size: 0x18 */

/* Overlay of the file-static data block at lbl_3_data_17898. */
typedef struct Rep21F8Data {
    u8 _pad0[0x26C];
    Rep21F8Player players[5];   /* 0x26C */
    u8 _pad2E4[0x2E8 - 0x2E4];
    u8 noDepth;                 /* 0x2E8 */
    u8 _pad2E9[3];
    f32 scales[1];              /* 0x2EC */
} Rep21F8Data;

/* Overlay of the file-static bss block at lbl_3_bss_9F20. */
typedef struct Rep21F8Bss {
    u8 idx;         /* 0x00 */
    u8 _pad1[3];
    u8 unk4[0xC];   /* 0x04 */
    f32 time;       /* 0x10 */
    u8 state;       /* 0x14 (lbl_3_bss_9F34) */
} Rep21F8Bss;

extern Rep21F8Data lbl_3_data_17898;
extern Rep21F8Bss lbl_3_bss_9F20;
f32 fn_3_BFDA4(struct Rep21F8Key* keys, u8 count, s32 arg2, u8 cur, u8* curOut, f32 t);
void fn_3_BF8F8(Rep21F8Player* player, Mtx m, u8* arg2, void (*cb)(Rep21F8Anim*, s32, Mtx, f32));
void fn_80034120(Mtx m);

BOOL fn_3_C937C(void) {
    Rep21F8Data* data = &lbl_3_data_17898;
    Rep21F8Bss* bss = &lbl_3_bss_9F20;
    Mtx sm;
    Mtx base = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
    };
    Mtx m;
    f32* scales;
    f32 sc;
    u8 nd;
    Rep21F8Player* p;

    switch (bss->state) {
    case 0:
        bss->state = 1;
        bss->time = 0.0f;
    case 1:
        bss->time += 1.0f;
        if (bss->time >= 16.0f) {
            bss->state = 2;
        }
        break;
    }
    fn_80034120(m);
    PSMTXConcat(m, base, m);
    scales = data->scales;
    scales += bss->idx;
    sc = *scales;
    PSMTXScale(sm, sc, sc, sc);
    PSMTXConcat(m, sm, m);
    nd = data->noDepth;
    p = data->players + bss->idx;
    p->time = bss->time;
    p->frameSrc = &lbl_3_common_bss_35154.unk4;
    if (nd) {
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    p = data->players;
    p += bss->idx;
    fn_3_BF8F8(p, m, bss->unk4, fn_3_C9590);
    if (data->noDepth) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    return bss->state == 2;
}
