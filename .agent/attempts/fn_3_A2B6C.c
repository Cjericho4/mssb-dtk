/* fn_3_A2B6C NONMATCHING (src/game/rep_18E8.c). Remaining diffs: target addresses file-static block lbl_3_bss_17F8 via base reg and keeps
   sub-array bases unfolded (addi r29,r31,0x10; lwz 0xc(r29) and addi r4,r31,4; lbz 3(r4)); MWCC folds these to lwz 0x1c(r31)/lbz 7(r31)
   (same as known-unfixable nested-struct fold). Also needs fn_3_A46A0(s32 runnerIdx) prototype (A1F3C still matches when passing idx).
   Also the ">= 0.5f || unk3" test should be written !(x < 0.5f) (target bge, no cror).
   Header carve: FieldingLogic.unkD6 @0xD6, Fielder.unkB4 @0xB4. Overlay struct below. */
typedef struct {
    /* 0x00 */ u8 _0[4];
    /* 0x04 */ Bss17FC x17FC;
    /* 0x08 */ u32 x1800;
    /* 0x0C */ u8 _C[4];
    /* 0x10 */ Bss1808 x1808;
    /* 0x24 */ s32 x181C;
    /* 0x28 */ s32 x1820;
    /* 0x2C */ u32 x1824;
    /* 0x30 */ s32 x1828[4];
    /* 0x40 */ s32 x1838[8];
    /* 0x60 */ s32 x1858[42];
} Bss17F8;
extern Bss17F8 lbl_3_bss_17F8;
static inline s32 getRunner3(Bss1808* p) {
    return p->runnerIndex[3];
}

BOOL fn_3_A2B6C(void) {
    s32 idx;
    s16 fielder;

    if (g_Runners[getRunner3(&lbl_3_bss_17F8.x1808)].percentTowardsNextBase >= 0.25f) {
        if (lbl_3_bss_17F8.x1858[getRunner3(&lbl_3_bss_17F8.x1808)] <= 3 && fn_3_A46A0(getRunner3(&lbl_3_bss_17F8.x1808))) {
            return TRUE;
        }
        if (lbl_3_bss_17F8.x1800 & 0x6000) {
            idx = getRunner3(&lbl_3_bss_17F8.x1808);
            if (lbl_3_bss_17F8.x1858[idx] <= 4) {
                fielder = g_FieldingLogic.unkD6;
                if (fielder >= 0 && !(g_Fielders[fielder].unkB4 > 4.0f)) {
                    if (g_Runners[idx].percentTowardsNextBase >= 0.5f || lbl_3_bss_17F8.x17FC.unk3 != 0) {
                        if (fn_3_A46A0(idx)) {
                            return TRUE;
                        }
                    }
                }
            }
        }
    }
    return FALSE;
}
