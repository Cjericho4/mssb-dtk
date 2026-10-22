#include "challenge/rep_7730.h"

// .text:0x0001D694 size:0x2B0
void fn_1_1D694(void) {
    return;
}

// .text:0x0001D944 size:0x110
void fn_1_1D944(void) {
    return;
}

// .text:0x0001DA54 size:0x290
void fn_1_1DA54(void) {
    return;
}

// .text:0x0001DCE4 size:0x64
void fn_1_1DCE4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    scene->unk14 = ARAMTransfer(&lbl_1_data_10674, 0, 0, 0);
    lbl_803CC1B8->aFunctionPointer = fn_1_1DA54;
}

// .text:0x0001DD48 size:0x4C
f32 fn_1_1DD48(u16 buttons, s32 negate, f32 value, f32 stepA, f32 step, f32 stepB, f32 min, f32 max) {
    if (buttons & 0x40) {
        step = stepA;
    } else if (buttons & 0x20) {
        step = stepB;
    }
    if (negate) {
        step = -step;
    }
    value += step;
    if (value < min) {
        value = min;
    }
    if (value > max) {
        value = max;
    }
    return value;
}

// .text:0x0001DD94 size:0x50
void fn_1_1DD94(void) {
    Vec vec;
    vec.x = lbl_1_bss_6BE4.value4;
    vec.y = lbl_1_bss_6BE4.value8;
    vec.z = lbl_1_bss_6BE4.valueC;
    fn_80037B18(&lbl_1_bss_6BF4, &vec, lbl_1_bss_6BE4.value0);
}

// .text:0x0001DDE4 size:0x10
void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4.valueC = value;
}

// .text:0x0001DDF4 size:0x10
void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4.value8 = value;
}

// .text:0x0001DE04 size:0x10
void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4.value4 = value;
}

// .text:0x0001DE14 size:0xC
void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4.value0 = value;
}

// .text:0x0001DE20 size:0x10
f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4.valueC;
}

// .text:0x0001DE30 size:0x10
f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4.value8;
}

// .text:0x0001DE40 size:0x10
f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4.value4;
}

// .text:0x0001DE50 size:0xC
f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4.value0;
}

// .text:0x0001DE5C size:0x4
void fn_1_1DE5C(void) {
    return;
}

// .text:0x0001DE60 size:0x42C
void fn_1_1DE60(void) {
    return;
}

// .text:0x0001E28C size:0x4
void fn_1_1E28C(void) {
    return;
}

// .text:0x0001E290 size:0x340
void fn_1_1E290(void) {
    return;
}

// .text:0x0001E5D0 size:0x2F0
void fn_1_1E5D0(Rep7730Unk6BF4* arg0) {
    return;
}

// .text:0x0001E8C0 size:0x4C
void fn_1_1E8C0(s32 arg) {
    lbl_1_data_1066C[((ChallengeScene*)lbl_803CC1B8)->mode28]((s16)(arg - 8));
}

// .text:0x0001E90C size:0x6E8
void fn_1_1E90C(void) {
    return;
}

// .text:0x0001EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(&lbl_1_bss_6D48, 0);
    fn_1_AF4(0x14, 0x14, 1.0f);
    if (((ChallengeScene*)lbl_803CC1B8)->flags2C & 2) {
        fn_1_1E5D0(&lbl_1_bss_6BF4);
    }
}

// .text:0x0001F05C size:0x1E0
void fn_1_1F05C(void) {
    return;
}

// .text:0x0001F23C size:0x9C
void fn_1_1F23C(Rep7730Unk6BF4* camera) {
    fn_800385F0(&lbl_1_bss_6BF4, ((ChallengeScene*)lbl_803CC1B8)->parameters[0], ((ChallengeScene*)lbl_803CC1B8)->parameters[1], ((ChallengeScene*)lbl_803CC1B8)->parameters[2], ((ChallengeScene*)lbl_803CC1B8)->parameters[3]);
    camera->angle = -((ChallengeScene*)lbl_803CC1B8)->parameters[4];
    camera->time += 2.0f;
    ((ChallengeScene*)lbl_803CC1B8)->flags2C &= ~2;
    ((ChallengeScene*)lbl_803CC1B8)->flags2C |= 2;
}

// .text:0x0001F2D8 size:0x140
void fn_1_1F2D8(void) {
    return;
}

// .text:0x0001F418 size:0x200
void fn_1_1F418(void) {
    return;
}

// .text:0x0001F618 size:0x2E8
void fn_1_1F618(void) {
    return;
}

// .text:0x0001F900 size:0x478
void fn_1_1F900(void) {
    return;
}

// .text:0x0001FD78 size:0x2D4
void fn_1_1FD78(void) {
    return;
}

// .text:0x0002004C size:0x258
void fn_1_2004C(void) {
    return;
}

// .text:0x000202A4 size:0x168
void fn_1_202A4(void) {
    return;
}

// .text:0x0002040C size:0x110
void fn_1_2040C(void) {
    return;
}

// .text:0x0002051C size:0x124
void fn_1_2051C(void) {
    return;
}

// .text:0x00020640 size:0x194
void fn_1_20640(void) {
    return;
}

// .text:0x000207D4 size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// .text:0x00020890 size:0xC0
void fn_1_20890(void) {
    Mtx mtx;

    C_MTXOrtho(lbl_1_bss_47010, 0.0f, 448.0f, 0.0f, 640.0f, 0.5f, -1.0f);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 0x20);
    fn_80048E00(1, 0);
}

// .text:0x00020950 size:0x288
void fn_1_20950(void) {
    return;
}

// .text:0x00020BD8 size:0x1F0
void fn_1_20BD8(void) {
    return;
}

// .text:0x00020DC8 size:0x38
void fn_1_20DC8(void) {
    DrawingSceneStruct* entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_20BD8, 1);
    entry->field14_0x24[1] = 0;
    entry->loadingState = 0;
}

// .text:0x00020E00 size:0x18C
void fn_1_20E00(void) {
    return;
}

// .text:0x00020F8C size:0xB4
void fn_1_20F8C(void) {
    DrawingSceneStruct* item = lbl_803CC1B8->currentDrawingItem;

    switch (lbl_803CC1B8->loadingState) {
    case 0:
        if (lbl_803C6CF8.allowLoad == 1) {
            item->unk14 = ARAMTransfer(&lbl_1_data_104F4, 0, 0, 0);
            lbl_803CC1B8->loadingState++;
        }
        break;
    case 1:
        if (lbl_803C6CF8.allowLoad == 1) {
            item->loadingState = 1;
        }
        break;
    }
}

// .text:0x00021040 size:0x140
void fn_1_21040(void) {
    return;
}

// .text:0x00021180 size:0x118
void fn_1_21180(void) {
    return;
}

// .text:0x00021298 size:0x170
void fn_1_21298(void) {
    return;
}

// .text:0x00021408 size:0x8E0
void fn_1_21408(void) {
    return;
}

// .text:0x00021CE8 size:0x8D0
void fn_1_21CE8(void) {
    return;
}

// .text:0x000225B8 size:0x8C
void fn_1_225B8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    DrawingSceneStruct* entry;

    switch (scene->field14_0x24[1]) {
    case 0:
        entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_20BD8, 1);
        entry->field14_0x24[1] = 0;
        entry->loadingState = 0;
        scene->field14_0x24[1]++;
        break;
    case 1:
        if (scene->loadingState != 0) {
            scene->aFunctionPointer = fn_1_21408;
        }
        break;
    }
}

// .text:0x00022644 size:0x230
void fn_1_22644(void) {
    return;
}

// .text:0x00022874 size:0x580
void fn_1_22874(void) {
    return;
}

// .text:0x00022DF4 size:0x158
void fn_1_22DF4(void) {
    return;
}

// .text:0x00022F4C size:0x14C
void fn_1_22F4C(void) {
    return;
}

// .text:0x00023098 size:0x76C
void fn_1_23098(void) {
    return;
}

// .text:0x00023804 size:0x2D4
void fn_1_23804(void) {
    return;
}

// .text:0x00023AD8 size:0x7C
void fn_1_23AD8(Mtx44 projection, Vec* eye, Vec* target) {
    eye->x = 0.0f;
    eye->y = 0.0f;
    eye->z = -10.0f;
    target->x = 0.0f;
    target->y = 0.0f;
    target->z = 0.0f;
    C_MTXFrustum(projection, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
}

// .text:0x00023B54 size:0x8BC
void fn_1_23B54(void) {
    return;
}

// .text:0x00024410 size:0x29C
void fn_1_24410(void) {
    return;
}

// .text:0x000246AC size:0xCC
void fn_1_246AC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_803C77B8.pressed & 8) {
        if (scene->flag14 == 0) scene->flag14 = 4;
        scene->flag14--;
    } else if (lbl_803C77B8.pressed & 4) {
        scene->flag14++;
        if (scene->flag14 == 4) scene->flag14 = 0;
    } else if (lbl_803C77B8.held & 0x100) {
        scene->aFunctionPointer = lbl_1_data_104A8[scene->flag14];
    } else if (lbl_803C77B8.held & 0x200) {
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00024778 size:0x28
void fn_1_24778(void) {
    lbl_803CC1B8->flag14 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_246AC;
}

// .text:0x000247A0 size:0x11C
void fn_1_247A0(void) {
    return;
}

// .text:0x000248BC size:0x1D0
void fn_1_248BC(void) {
    return;
}

// .text:0x00024A8C size:0x1C0
void fn_1_24A8C(void) {
    return;
}

// .text:0x00024C4C size:0x418
void fn_1_24C4C(void) {
    return;
}

// .text:0x00025064 size:0xC04
void fn_1_25064(void) {
    return;
}

// .text:0x00025C68 size:0x330
void fn_1_25C68(void) {
    return;
}

// .text:0x00025F98 size:0x824
void fn_1_25F98(void) {
    return;
}

// .text:0x000267BC size:0x38
void fn_1_267BC(void) {
    if (lbl_803CC1B8->loadingState != 0) {
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000267F4 size:0x134
void fn_1_267F4(void) {
    return;
}

// .text:0x00026928 size:0x10C
void fn_1_26928(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_803C77B8.pressed & 2) {
        scene->byte20++;
        if (scene->byte20 == scene->byte1F) scene->byte20 = 0;
    } else if (lbl_803C77B8.pressed & 1) {
        if (scene->byte20 == 0) scene->byte20 = scene->byte1F;
        scene->byte20--;
    } else if (lbl_803C77B8.held & 0x100) {
        scene->byte1E = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_267F4;
    } else if (lbl_803C77B8.held & 0x200) {
        fn_800AD038(lbl_80366158.unk8);
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
    } else if (lbl_803C77B8.held & 0x1000) {
        scene->aFunctionPointer = fn_1_25C68;
    }
    fn_800B24D4(4);
    fn_800B1188();
}

// .text:0x00026A34 size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}
