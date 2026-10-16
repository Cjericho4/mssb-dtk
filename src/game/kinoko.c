#include "game/kinoko.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/rep_3E58.h"
#include "stl/mem.h"
#include "game/rep_1E08.h"
#include "Dolphin/gx.h"

s32 fn_8005268C(void);

static KinokoState lbl_3_bss_BA00;
s32 fn_8001B728(s32 index, s32 type, VecXYZ* out);

// .text:0x0016917C size:0x2C0 mapped:0x807A8210
void fn_3_16917C(void) {
    return;
}

// .text:0x001695A0 size:0x4 mapped:0x807A8634
void fn_3_1695A0(void) {
}

// .text:0x001695A4 size:0x5C mapped:0x807A8638
void fn_3_1695A4(s8 arg1, u8 arg2) {
    KinokoState *state = &lbl_3_bss_BA00;
    if (arg2 == 0) {
        state->ptr0 = &state->_unk08[0x98];
        state->ptr4 = &state->_unk08[0x24];
    } else {
        state->ptr0 = &state->_unk08[0x58];
        state->ptr4 = &state->_unk08[0x4];
    }
    fn_80011604(arg1, fn_3_16917C);
}

// .text:0x00169600 size:0x204 mapped:0x807A8694
void fn_3_169600(void) {
    return;
}

// .text:0x00169804 size:0x180 mapped:0x807A8898
void fn_3_169804(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768(fn_8005268C())->mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768(fn_8005268C())->proj, GX_PERSPECTIVE);
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
void fn_3_169984(void) {
    return;
}

// .text:0x00169D00 size:0x170 mapped:0x807A8D94
void fn_3_169D00(KinokoSegment* segs, u32* count) {
    KinokoSegment* cur;
    KinokoSegment* prev;
    u32 i;

    i = 24;
    cur = &segs[24];
    for (; i != 0 && *count < 0x95; cur--, i--) {
        if (cur->active != 0) {
            prev = &segs[i - 1];
            PSVECAdd(&cur->pos, &prev->pos, &lbl_3_bss_BAE0.quads[*count].center);
            PSVECScale(&lbl_3_bss_BAE0.quads[*count].center, 0.5f, &lbl_3_bss_BAE0.quads[*count].center);
            lbl_3_bss_BAE0.quads[*count].verts[0].pos = &prev->left;
            lbl_3_bss_BAE0.quads[*count].verts[0].color = &prev->color;
            lbl_3_bss_BAE0.quads[*count].verts[1].pos = &prev->right;
            lbl_3_bss_BAE0.quads[*count].verts[1].color = &prev->color;
            lbl_3_bss_BAE0.quads[*count].verts[2].pos = &cur->right;
            lbl_3_bss_BAE0.quads[*count].verts[2].color = &cur->color;
            lbl_3_bss_BAE0.quads[*count].verts[3].pos = &cur->left;
            lbl_3_bss_BAE0.quads[*count].verts[3].color = &cur->color;
            lbl_3_bss_BAE0.quads[*count].active = 1;
            (*count)++;
        }
    }
}

// .text:0x00169E70 size:0x20C mapped:0x807A8F04
void fn_3_169E70(void) {
    return;
}

// .text:0x0016A07C size:0x140C mapped:0x807A9110
void fn_3_16A07C(void) {
    return;
}

// .text:0x0016B488 size:0x12C mapped:0x807AA51C
void fn_3_16B488(VecXYZ* out, s8 type) {
    if (out == NULL) {
        OSPanic("kinoko.c", 0x11C, "Ribbon Effect Pos Data None\n");
    }
    memset(out, 0, sizeof(VecXYZ));
    if (fn_8001B728(lbl_3_data_28928.unk_19DC, type, out) == 0) {
        switch (type) {
        case 28:
            fn_8001B728(lbl_3_data_28928.unk_19DC, 0x1E, out);
            break;
        case 32:
            fn_8001B728(lbl_3_data_28928.unk_19DC, 0x22, out);
            break;
        case 7:
            fn_8001B728(lbl_3_data_28928.unk_19DC, 0x5, out);
            break;
        case 18:
            fn_8001B728(lbl_3_data_28928.unk_19DC, 0x13, out);
            break;
        case 24:
            fn_8001B728(lbl_3_data_28928.unk_19DC, 0x19, out);
            break;
        }
    }
}

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(void) {
    return;
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
void fn_3_16B884(void) {
    return;
}

// .text:0x0016C394 size:0x78 mapped:0x807AB428
void fn_3_16C394(s8 arg0) {
    memset(&lbl_3_data_28928, 0, 0x19E0);
    memset(&lbl_3_bss_BAE0, 0, 0x1BF0);
    lbl_3_data_28928.unk_19DC = arg0;
    lbl_3_data_28928.unk_19DD = 1;
    lbl_3_data_28928.unk_19D4 = 1;
    fn_3_16B884();
    fn_800B0A5C_insertQueue(fn_3_16A07C, 0);
}

