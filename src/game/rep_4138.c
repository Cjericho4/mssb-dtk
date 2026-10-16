#include "game/rep_4138.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "stl/mem.h"
#include "game/rep_3E58.h"
#include "game/rep_1E08.h"
s32 fn_8005268C(void);
#include "Dolphin/gx.h"

extern void fn_80033B58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

static inline void setupGX_16D9B0(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768(fn_8005268C())->mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768(fn_8005268C())->proj, GX_PERSPECTIVE);
    fn_80033B58((s32)lbl_3_bss_D6E4, lbl_3_bss_D6E8, 0, 0);
}

// .text:0x0016D810 size:0x1A0 mapped:0x807AC8A4
void fn_3_16D810(void) {
    return;
}

// .text:0x0016D9B0 size:0x1BC mapped:0x807ACA44
void fn_3_16D9B0(void) {
    setupGX_16D9B0();
}

// .text:0x0016DB6C size:0x458 mapped:0x807ACC00
void fn_3_16DB6C(u8 idx) {
    return;
}

// .text:0x0016DFC4 size:0x1DC mapped:0x807AD058
void fn_3_16DFC4(void) {
    u32 i;

    setupGX_16D9B0();
    for (i = 0; i < 6; i++) {
        fn_3_16DB6C(i);
    }
}

// .text:0x0016E1A0 size:0x4C mapped:0x807AD234
void fn_3_16E1A0(void) {
    // Note: Local variables to hold loaded values.
    // This prevents the compiler from storing too early.
    s32 s1, s0, inn;
    s32 str, bal, out;

    // Register Steering: Initialization order anchors r6, r5, and r8.
    Scores* scores = &g_Scores;           // Anchors scores base to r6
    Strikes* strikes = &g_Strikes;        // Anchors strikes base to r5
    GameStateBss* dest = &lbl_3_bss_D6F0; // Anchors destination base to r8

    // PERFORM ALL LOADS FIRST
    // The sequence of 'lha' and 'lwz' must match the target register indices
    s1 = scores->ScoreTeam1; // lha r9, 0x2a(r6)
    s0 = scores->ScoreTeam0; // lha r7, 0x4(r6)
    inn = scores->highscore;    // lwz r6, 0x0(r6) -- Note r6 is overwritten here;

    str = strikes->strikes;  // lwz r4, 0x0(r5)
    bal = strikes->balls;    // lwz r3, 0x4(r5)
    out = strikes->outs;     // lwz r0, 0x8(r5)

    // PERFORM ALL STORES SECOND
    // stw r9, 0x0(r8) -> stw r7, 0x4(r8) ...
    dest->val0 = s1;
    dest->val1 = s0;
    dest->val2 = inn;
    dest->val3 = str;
    dest->val4 = bal;
    dest->val5 = out;
}

typedef struct {
    u8 _pad[8];
} Data2A498Entry;
extern Data2A498Entry lbl_3_data_2A498[];
extern u8 lbl_803CBBC0;

// .text:0x0016E1EC size:0x110 mapped:0x807AD280
void fn_3_16E1EC(void) {
    if ((lbl_3_bss_D6E0.ptr == NULL) | (lbl_3_bss_D6E0.flag | (g_hugeAnimStruct.displayObjects == 0))) {
        lbl_3_bss_D6E0.ptr = NULL;
        lbl_3_bss_D6E0.index = -1;
        lbl_3_bss_D6E0.flag = 0;
        fn_800B0A14_removeQueue();
    }
    if ((g_GameLogic.gameStatus != 0x13) & (g_GameLogic.gameStatus != 0x14)) {
        lbl_3_bss_D6E0.snapshot.scoreTeam1 = g_Scores.ScoreTeam1;
        lbl_3_bss_D6E0.snapshot.scoreTeam0 = g_Scores.ScoreTeam0;
        lbl_3_bss_D6E0.snapshot.inning = g_Scores.highscore;
        lbl_3_bss_D6E0.snapshot.strikes = g_Strikes.strikes;
        lbl_3_bss_D6E0.snapshot.balls = g_Strikes.balls;
        lbl_3_bss_D6E0.snapshot.outs = g_Strikes.outs;
    }
    fn_800A7D4C(1, (BdcArrayElement*)&lbl_3_data_2A498[lbl_803CBBC0]);
}

// .text:0x0016E2FC size:0x2C mapped:0x807AD390
void fn_3_16E2FC(u16 *ptr, s32 index) {
    if (ptr == NULL) {
        return;
    }

    // lhz r5, 0(r3) -> subi r0, r5, 1 -> cmpw r0, r4
    if ((s32)(ptr[0] - 1) < index) {
        return;
    }

    // Direct access triggers lis/stw for each global
    lbl_3_bss_D6E4 = ptr;
    lbl_3_bss_D6E8 = index;
}

// .text:0x0016E328 size:0x10 mapped:0x807AD3BC
void fn_3_16E328(void) {
    lbl_3_bss_D6EC = TRUE;
}

// .text:0x0016E338 size:0x6C mapped:0x807AD3CC
void fn_3_16E338(u16 *ptr, s32 index) {
    Rep4138Bss *bss = &lbl_3_bss_D6E0;
    u8 zero = 0;

    if (ptr == NULL) {
        return;
    }

    if ((s32)(ptr[0] - 1) < index) {
        return;
    }

    bss->ptr = ptr;
    bss->index = index;
    bss->flag = zero;
    memset(&bss->snapshot, zero, sizeof(bss->snapshot));
    fn_800B0A5C_insertQueue(fn_3_16E1EC, 5);
}
