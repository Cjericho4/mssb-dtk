#include "game/gap_FBCD0.h"
#include "UnknownHeaders.h"
#include "game/rep_1D58.h"

extern u32 lbl_3_data_20E0C[];

typedef struct {
    u8 _pad0[0x38];
    Mtx mtx;               /* 0x38 */
    u8 _pad68[0x6C - 0x68];
} CameraSlot_1BE94;        /* size 0x6C */

typedef struct {
    u8 _pad0[0x40];
    Mtx mtx; /* 0x40 */
} CameraMtx_FBCD0;

extern u8 lbl_803CBBC0;
extern CameraSlot_1BE94 lbl_3_data_1BE94[];
extern CameraMtx_FBCD0* fn_80052768(s32 arg0);
extern void fn_800A7D4C(s32 arg0, CameraSlot_1BE94* slot);

// .text:0x000FBCD0 size:0x88 mapped:0x8073AD64
void fn_3_FBCD0(void) {
    fn_3_B939C();
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSMTXCopy(fn_80052768(0)->mtx, lbl_3_data_1BE94[lbl_803CBBC0].mtx);
        fn_800A7D4C(1, &lbl_3_data_1BE94[lbl_803CBBC0]);
    }
}

// .text:0x000FBD58 size:0x18 mapped:0x8073ADEC
void fn_3_FBD58(void) {
    lbl_3_common_bss_DE94->field_0x9AC = 0;
}

// .text:0x000FBD70 size:0x3C mapped:0x8073AE04
void fn_3_FBD70(void) {
    BssDE94Item* p = lbl_3_common_bss_DE94;
    p->field_0x9AF = 0;
    lbl_3_common_bss_DE94->field_0x9B0 = 0;
    lbl_3_common_bss_DE94->field_0x9AE = 0;
    lbl_3_common_bss_DE94->field_0x9AB = 0;
    lbl_3_common_bss_DE94->field_0x9B6 = 0;
    p->field_0x18 = 0;
}

// .text:0x000FBDAC size:0x78 mapped:0x8073AE40
void fn_3_FBDAC(u32 arg0) {
    BssDE94Item* p = lbl_3_common_bss_DE94;
    p->field_0x9AB = 1;
    lbl_3_common_bss_DE94->field_0x9AC = 1;
    lbl_3_common_bss_DE94->field_0x9AF = 1;
    lbl_3_common_bss_DE94->field_0x9B0 = 1;
    p->field_0x18 = 0;
    p->unk_08 = 0;
    p->unk_14 = 0;
    lbl_3_common_bss_DE94->unk_92C = arg0;
    lbl_3_common_bss_DE94->unk_00 = lbl_3_data_20E0C[arg0];
    lbl_3_common_bss_DE94->field_0x9AE = 1;
    lbl_3_common_bss_DE94->unk_118 = 0;
    lbl_3_common_bss_DE94->unk_944 = 0;
}

// .text:0x000FBE24 size:0x4D8 mapped:0x8073AEB8
void fn_3_FBE24(void) {
    return;
}

// .text:0x000FC2FC size:0x14C mapped:0x8073B390
Vec fn_3_FC2FC(Vec* pos, Vec* anchor, Vec* anchorVel, f32 dt, f32 stiffness, f32 damping, f32 restLen) {
    Vec dir;
    Vec scaled;
    Vec rel;
    f32 dist;
    f32 force;

    PSVECSubtract(pos, anchor, &dir);
    dist = PSVECDistance(pos, anchor);
    PSVECSubtract(anchorVel, anchor, &rel);
    PSVECScale(&rel, dt, &scaled);
    force = stiffness * (restLen - dist) + damping * (PSVECDotProduct(&scaled, &dir) / dist);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, force * dt, &dir);
    PSVECAdd(pos, &dir, pos);
    return *pos;
}

