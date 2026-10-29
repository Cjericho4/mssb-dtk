#include "challenge/rep_0138.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXHardware.h"

// .text:0x00004E98 size:0x648
void fn_1_4E98(void) {
    return;
}

// .text:0x000054E0 size:0x60
void fn_1_54E0(Mtx view) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], view);
    }
}

// .text:0x00005540 size:0x4
void fn_1_5540(void) {
    return;
}

// .text:0x00005544 size:0x154
void fn_1_5544(void) {
    return;
}

// .text:0x00005698 size:0x28C
extern GXTexObj lbl_1_bss_4E4;
void C_MTXOrtho(Mtx44 matrix, f32 top, f32 bottom, f32 left, f32 right, f32 nearZ, f32 farZ);
/* Draw the texture preview as a 256-pixel quad in an orthographic viewport. */
void fn_1_5698(void) {
    Mtx44 projection;
    Mtx view;
    C_MTXOrtho(projection, 0.0f, 448.0f, 0.0f, 640.0f, -0.0f, -0.5f);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    PSMTXIdentity(view);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 2);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXLoadTexObj(&lbl_1_bss_4E4, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = 100.0f; GXWGFifo.f32 = 0.0f;
    GXWGFifo.u16 = 0; GXWGFifo.u16 = 0;
    GXWGFifo.f32 = 0.0f; GXWGFifo.f32 = 356.0f; GXWGFifo.f32 = 0.0f;
    GXWGFifo.u16 = 0; GXWGFifo.u16 = 4;
    GXWGFifo.f32 = 256.0f; GXWGFifo.f32 = 356.0f; GXWGFifo.f32 = 0.0f;
    GXWGFifo.u16 = 4; GXWGFifo.u16 = 4;
    GXWGFifo.f32 = 256.0f; GXWGFifo.f32 = 100.0f; GXWGFifo.f32 = 0.0f;
    GXWGFifo.u16 = 4; GXWGFifo.u16 = 0;
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}

// .text:0x00005924 size:0x19C
void fn_1_5924(void) {
    return;
}

// .text:0x00005AC0 size:0x590
void fn_1_5AC0(void) {
    return;
}

// .text:0x00006050 size:0x528
void fn_1_6050(u16* pixels, s32 width, s32 height, f32 scale) {
    return;
}

// .text:0x00006578 size:0x14C
void fn_1_6578(GXTexObj* texture, u16* pixels, s32 width, s32 height) {
    s32 filter;
    f32* scale;
    s32 mipWidth = width;
    s32 mipHeight = height;
    s32 offset = 0;
    s32 i;
    ChallengeMipSettings* settings = &lbl_1_data_2A8;
    if (settings->levels == 0) {
        width /= 4;
        height /= 4;
        fn_1_6050(pixels, width, height, 1.0f);
        filter = 1;
    } else {
        scale = settings->scales;
        for (i = 0; i <= settings->levels; i++) {
            fn_1_6050(&pixels[offset], mipWidth, mipHeight, *scale);
            offset += mipWidth * mipHeight;
            mipWidth /= 2;
            mipHeight /= 2;
            scale++;
        }
        filter = settings->filter;
    }
    GXInitTexObj(texture, pixels, width, height, GX_TF_IA8, GX_REPEAT, GX_REPEAT, settings->levels);
    GXInitTexObjLOD(texture, filter, GX_LINEAR, 0.0f, settings->levels, settings->bias, 0, 0, 0);
}

// .text:0x000066C4 size:0x184
void fn_1_66C4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 mode, option;
    fn_800AD038(lbl_80366158.unk8);
    scene->loadingState = 0;
    mode = lbl_1_common_bss_472B4.mode;
    option = lbl_1_common_bss_472B4.option;
    memset(&lbl_1_common_bss_472B4, 0, sizeof(ChallengePreviewState));
    lbl_1_common_bss_472B4.mode = mode;
    lbl_1_common_bss_472B4.option = option;
    lbl_1_common_bss_472B4.pixels = _OSAllocFromHeap(0x20, 0x80000);
    lbl_1_common_bss_472B4.position.x = -6.0f;
    lbl_1_common_bss_472B4.position.y = -10.666667f;
    lbl_1_common_bss_472B4.flags = 0xF36C;
    lbl_1_common_bss_472B4.position.z = 0.63f;
    lbl_1_common_bss_472B4.selection = -1;
    lbl_1_common_bss_472B4.active = 0;
    PSMTXIdentity(lbl_1_common_bss_472B4.poses[0].transform);
    lbl_1_common_bss_472B4.poses[0].draw = fn_1_77EC;
    lbl_1_common_bss_472B4.poses[1] = lbl_1_common_bss_472B4.poses[0];
    lbl_1_common_bss_472B4.poses[2].draw = fn_800B472C;
    lbl_1_common_bss_472B4.poses[3] = lbl_1_common_bss_472B4.poses[2];
    lbl_803CC1B8->aFunctionPointer = fn_1_6848;
}

// .text:0x00006848 size:0x5CC
void fn_1_6848(void) {
    return;
}

// .text:0x00006E14 size:0x368
void fn_1_6E14(void) {
    return;
}

// .text:0x0000717C size:0x104
void fn_1_717C(void) {
    return;
}

// .text:0x00007280 size:0x138
void fn_1_7280(void) {
    return;
}

// .text:0x000073B8 size:0x434
void fn_1_73B8(Rep0138Model* model, s32 count, ...) {
    return;
}

// .text:0x000077EC size:0x5C
void fn_1_77EC(Rep0138Model* model) {
    GXSetCullMode(lbl_1_data_8C4);
    fn_1_73B8(model, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x00007848 size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}

// .text:0x0000786C size:0x78
void fn_1_786C(void) {
    fn_80048D4C();
    GXSetCopyClear(lbl_1_data_858, 0xFFFFFF);
    SetFog(lbl_1_bss_4E0->type, lbl_1_bss_4E0->color, lbl_1_bss_4E0->start, lbl_1_bss_4E0->end, 1.0f, 512.0f);
}

// .text:0x000078E4 size:0x7C
void fn_1_78E4(void) {
    GXSetCopyClear(lbl_1_data_858, 0xFFFFFF);
    if (lbl_1_bss_C4.cullNone != 0) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode(GX_CULL_BACK);
    }
    SetFogNoneAgain();
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

// .text:0x00007960 size:0x4A4
void fn_1_7960(void) {
    return;
}

// .text:0x00007E04 size:0xF4
void fn_1_7E04(f32 scale) {
    Mtx44 projection;
    f32 inverse = 1.0f / scale;
    C_MTXFrustum(projection, -0.175f * inverse, 0.175f * inverse, 0.25f * inverse, -0.25f * inverse, 1.0f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f * inverse, 240.0f * inverse, -320.0f * inverse, 320.0f * inverse, -512.0f, -1.0f, 1280.0f);
}

// .text:0x00007EF8 size:0x100
void fn_1_7EF8(void) {
    switch (lbl_803C77B8.pressed) {
    case 4:
    case 8:
        lbl_1_bss_C2 = !lbl_1_bss_C2;
        break;
    case 1:
        fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) - 1);
        break;
    case 2:
        fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) + 1);
        break;
    case 0x100:
        lbl_1_data_85C = !lbl_1_data_85C;
        if (lbl_1_data_85C != 0) fn_80048C14(0x3F);
        else fn_80048C14(0);
        break;
    }
}

// .text:0x00007FF8 size:0x370
/* Edit fog type, RGB color, and start/end distances in the preview menu. */
void fn_1_7FF8(void) {
    switch (lbl_803C77B8.pressed) {
    case 8:
        if (--lbl_1_common_bss_472B4.fogSelection < 0) lbl_1_common_bss_472B4.fogSelection = 5;
        break;
    case 4:
        if (++lbl_1_common_bss_472B4.fogSelection >= 6) lbl_1_common_bss_472B4.fogSelection = 0;
        break;
    case 1:
        switch (lbl_1_common_bss_472B4.fogSelection) {
        case 0:
            switch (--lbl_1_bss_4E0->type) {
            case 255: lbl_1_bss_4E0->type = 7; break;
            case 3: lbl_1_bss_4E0->type = 2; break;
            case 1: lbl_1_bss_4E0->type = 0; break;
            }
            break;
        case 1: lbl_1_bss_4E0->rgb[0]--; break;
        case 2: lbl_1_bss_4E0->rgb[1]--; break;
        case 3: lbl_1_bss_4E0->rgb[2]--; break;
        case 4:
            if ((lbl_1_bss_4E0->start -= 1.0f) < 0) lbl_1_bss_4E0->start = 0;
            break;
        case 5:
            if ((lbl_1_bss_4E0->end -= 1.0f) < 0) lbl_1_bss_4E0->end = 0;
            break;
        }
        break;
    case 2:
        switch (lbl_1_common_bss_472B4.fogSelection) {
        case 0:
            switch (++lbl_1_bss_4E0->type) {
            case 1: lbl_1_bss_4E0->type = 2; break;
            case 3: lbl_1_bss_4E0->type = 4; break;
            case 8: lbl_1_bss_4E0->type = 0; break;
            }
            break;
        case 1: lbl_1_bss_4E0->rgb[0]++; break;
        case 2: lbl_1_bss_4E0->rgb[1]++; break;
        case 3: lbl_1_bss_4E0->rgb[2]++; break;
        case 4:
            if ((lbl_1_bss_4E0->start += 1.0f) > 512) lbl_1_bss_4E0->start = 512;
            break;
        case 5:
            if ((lbl_1_bss_4E0->end += 1.0f) > 512) lbl_1_bss_4E0->end = 512;
            break;
        }
        break;
    }
}

// .text:0x00008368 size:0x240
void fn_1_8368(void) {
    return;
}
