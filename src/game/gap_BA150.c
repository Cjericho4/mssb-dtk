#include "game/gap_BA150.h"
#include "UnknownHeaders.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "game/rep_1E08.h"

extern void fn_800246D4(s32 (*compareFn)(BA150SortItem*, BA150SortItem*), BA150SortItem* out, BA150SortItem* in, u32 elemSize, u32 count);

// .text:0x000BA150 size:0x24 mapped:0x806F91E4
void fn_3_BA150(void) {
    pitchingMachinePitching(0x19);
}

// .text:0x000BA174 size:0x2C mapped:0x806F9208
s32 fn_3_BA174(BA150SortItem* a, BA150SortItem* b) {
    if (a->sortKey < b->sortKey) {
        return 1;
    }
    if (a->sortKey > b->sortKey) {
        return -1;
    }
    return 0;
}

// .text:0x000BA1A0 size:0xC8 mapped:0x806F9234
BA150Node* fn_3_BA1A0(BA150Node* list, u32 count) {
    BA150SortItem* items = _OSAllocFromHeap(0x20, count * 8);
    BA150SortItem* p = items;
    BA150Node* n;

    for (n = list; n != NULL; n = n->next) {
        p->node = n;
        p->sortKey = n->sortKey;
        p++;
    }
    fn_800246D4(fn_3_BA174, items, items, 8, count);
    list = items->node;
    p = items;
    while (--count != 0) {
        p->node->next = p[1].node;
        p++;
    }
    p->node->next = NULL;
    fn_800ACFB0(items);
    return list;
}

// .text:0x000BA268 size:0x184 mapped:0x806F92FC
void fn_3_BA268(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768(0)->mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768(0)->proj, GX_PERSPECTIVE);
}

// .text:0x000BA3EC size:0x14C mapped:0x806F9480
void fn_3_BA3EC(void) {
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
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
}

