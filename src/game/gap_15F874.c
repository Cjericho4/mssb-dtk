#include "game/gap_15F874.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"

extern s32 lbl_3_data_27F10[];

extern void gOz_GXSetTexture(s32, s32, s32);

// Data block at .data:0x27EC0 (fade quad resources).
typedef struct {
    /* 0x000 */ u8 _0[0x244];
    /* 0x244 */ Mtx44 projection;
    /* 0x284 */ u8 _284[0x2A0 - 0x284];
    /* 0x2A0 */ u8 displayList[0x20];
    /* 0x2C0 */ f32 positionsA[16];
    /* 0x300 */ f32 positionsB[16];
} Data27EC0;
extern Data27EC0 lbl_3_data_27EC0;

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void fn_3_15F874(s32 arg0) {
    Data27EC0* data = &lbl_3_data_27EC0;
    Mtx mtx;

    GXSetProjection(data->projection, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    gOz_GXSetTexture(4, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    if (arg0 != 0) {
        GXSetArray(GX_VA_POS, data->positionsB, 12);
    } else {
        GXSetArray(GX_VA_POS, data->positionsA, 12);
    }
    GXCallDisplayList(data->displayList, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void fn_3_15F998(void) {
    lbl_3_common_bss_35154.unk_470 = 0;
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void fn_3_15F9AC(void) {
    lbl_3_common_bss_35154.unk_471 = 1;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void fn_3_15F9C0(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    lbl_803CC1B8->loadingState--;
    lbl_3_common_bss_35154.unk_468 = lbl_3_data_27F10[0] * (lbl_3_data_27F10[1] - lbl_803CC1B8->loadingState) / lbl_3_data_27F10[1];
    if (lbl_803CC1B8->loadingState == 0) {
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void fn_3_15FA58(s32 count, s32* values) {
    QueueEntry* entry = fn_800B0A5C_insertQueue(fn_3_15F9C0, lbl_803CC1B8->priority);

    lbl_3_common_bss_35154.unk_470 = 1;
    lbl_3_common_bss_35154.unk_471 = 0;
    lbl_3_common_bss_35154.unk_468 = 0;
    lbl_3_common_bss_35154.unk_472 = 0;
    while (count != 0) {
        lbl_3_common_bss_35154.unk_473[lbl_3_common_bss_35154.unk_472++] = *values++;
        count--;
    }
    entry->unk10 = lbl_3_data_27F10[1];
}

