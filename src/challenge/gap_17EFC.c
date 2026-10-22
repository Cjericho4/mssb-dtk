#include "challenge/gap_17EFC.h"

// .text:0x00017EFC size:0x2C
s32 fn_1_17EFC(Gap17EFCEntry* a, Gap17EFCEntry* b) {
    if (a->sortKey < b->sortKey) {
        return 1;
    }
    if (a->sortKey > b->sortKey) {
        return -1;
    }
    return 0;
}

// .text:0x00017F28 size:0xC8
ChallengeSortNode* fn_1_17F28(ChallengeSortNode* head, s32 count) {
    Gap17EFCEntry* allocation = _OSAllocFromHeap(0x20, count * sizeof(Gap17EFCEntry));
    Gap17EFCEntry* entry = allocation;
    ChallengeSortNode* node = head;
    while (node != 0) {
        entry->node = node;
        entry->sortKey = node->sortKey;
        entry++;
        node = node->next;
    }
    fn_800246D4(fn_1_17EFC, allocation, allocation, sizeof(Gap17EFCEntry), count);
    head = allocation->node;
    entry = allocation;
    while (--count != 0) {
        entry->node->next = entry[1].node;
        entry++;
    }
    entry->node->next = 0;
    fn_800ACFB0(allocation);
    return head;
}

// .text:0x00017FF0 size:0x184
void fn_1_17FF0(void) {
    return;
}

// .text:0x00018174 size:0x14C
void fn_1_18174(void) {
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
