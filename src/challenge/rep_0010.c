#include "challenge/rep_0010.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTransform.h"
#include "challenge/challenge.h"

/* gap_800AD780.h has incompatible queue-node and OSGetTime declarations with
   this unit; retain its exact callback prototype until those views are unified. */
void fn_800B0C80(void (*callback)(void));

// .text:0x000005EC size:0x508
void fn_1_5EC(void) {
    return;
}

// .text:0x00000AF4 size:0x438
void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2) {
    return;
}

// .text:0x00000F2C size:0x1D8
/* Configure direct vertices and the single-stage challenge material pipeline. */
void fn_1_F2C(s32 mode, s32 texFraction, s32 normals) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    if (normals) {
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_NBT, GX_F32, 0);
    }
    switch (mode) {
    case 0:
    case 4:
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        if (mode == 4) break;
        /* fall through */
    case 3:
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        if (texFraction == -1) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        } else {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, texFraction);
        }
        break;
    }
    GXSetTevOrder(GX_TEVSTAGE0, mode == 4 ? GX_TEXCOORD_NULL : GX_TEXCOORD0,
                  mode == 4 ? GX_TEXMAP_NULL : GX_TEXMAP0,
                  mode == 3 ? GX_COLOR_NULL : GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(mode != 3);
    GXSetNumTexGens(mode != 4);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, mode);
}

// .text:0x00001104 size:0x4
void _epilog(void) {
    return;
}

// .text:0x00001108 size:0x4
void _unresolved(void) {
    return;
}

// .text:0x0000110C size:0x3C
// Register the challenge scene and initialize its display buffers.
void _prolog(void) {
    fn_800B0C80(fn_1_1148);
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
}

// .text:0x00001148 size:0x88
void fn_1_1148(void) {
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    scene->state16 = 0;
    scene->state14 = 0;
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
}

// .text:0x000011D0 size:0x70
void fn_1_11D0(void) {
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
}

// .text:0x00001240 size:0x2F8
#include "Dolphin/GX/GXFifo.h"
struct TextureHeader;
void SetDisplayStateTexture(struct TextureHeader* texture, s32 map, s32 palette);
void gOz_GXSetTexture(s32 map, s32 mode, s32 flags);
void fn_1_1240(ChallengeTextureQuad* quad) {
    Mtx44 projection;
    Mtx matrix;
    GXColor color;
    SetDisplayStateTexture((struct TextureHeader*)&quad->archive->entries[quad->texture], 0, 0);
    PSMTXIdentity(matrix);
    C_MTXOrtho(projection, 0, 448, 0, 640, 0, 1);
    GXLoadPosMtxImm(matrix, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    gOz_GXSetTexture(0, 0, 0);
    color.r = quad->color.r; color.g = quad->color.g;
    color.b = quad->color.b; color.a = quad->color.a;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    if (quad->mode == 1) {
        GXSetTevOrder(0, 0, 0, GX_COLOR0A0);
        GXSetTevColorIn(0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevAlphaIn(0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    } else if (quad->mode == 2) {
        GXSetTevOrder(0, 0, 0, GX_COLOR0A0);
        GXSetTevOp(0, GX_MODULATE);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0, 0, 0); GXColor1u32(0xFFFFFFFF); GXTexCoord2u16(0, 0);
    GXPosition3f32(256, 0, 0); GXColor1u32(0xFFFFFFFF); GXTexCoord2u16(1, 0);
    GXPosition3f32(256, 256, 0); GXColor1u32(0xFFFFFFFF); GXTexCoord2u16(1, 1);
    GXPosition3f32(0, 256, 0); GXColor1u32(0xFFFFFFFF); GXTexCoord2u16(0, 1);
}
