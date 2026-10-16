/* fn_3_A2C9C NONMATCHING (src/game/rep_18E8.c). Same issue as fn_3_A2B6C: target addresses the file-static block
   lbl_3_bss_17F8 via one base register (r31) and keeps sub-array bases unfolded (addi r3,r31,0x10; lwz 8(r3);
   addi r4,r31,0x60; lwzx). MWCC folds the overlay-struct access (lwz 0x18(r5), add+lwz 0x60) and doesn't keep base in r31.
   Requires fn_3_A46A0(s32 runnerIdx) prototype; logic/branches otherwise line up. */
typedef struct {
    /* 0x00 */ u8 _0[0x10];
    /* 0x10 */ s32 runnerIndex[4];
    /* 0x20 */ s32 x1818;
    /* 0x24 */ s32 x181C;
    /* 0x28 */ s32 x1820;
    /* 0x2C */ u32 x1824;
    /* 0x30 */ s32 x1828[4];
    /* 0x40 */ s32 x1838[8];
    /* 0x60 */ s32 x1858[42];
} Bss17F8;
extern Bss17F8 lbl_3_bss_17F8;
BOOL fn_3_A2C9C(void) {
    s32 v;

    if ((lbl_3_bss_17F8.x1824 & 0x100) && g_Ball.ballDistanceFromBase[3] < 5.0f &&
        lbl_3_bss_17F8.x1858[lbl_3_bss_17F8.runnerIndex[2]] <= 2 && fn_3_A46A0(lbl_3_bss_17F8.runnerIndex[2])) {
        return TRUE;
    }
    if (lbl_3_bss_17F8.x1818 != 0 && fn_3_A46A0(lbl_3_bss_17F8.runnerIndex[1])) {
        return TRUE;
    }
    v = lbl_3_bss_17F8.x1858[lbl_3_bss_17F8.runnerIndex[1]];
    if (v <= 4 && g_Strikes.outs == g_Strikes.unk_C) {
        if (g_Ball.ballDistanceFromBase[1] < 2.5f && v <= 2 && fn_3_A46A0(lbl_3_bss_17F8.runnerIndex[0])) {
            return TRUE;
        }
        if (fn_3_A46A0(lbl_3_bss_17F8.runnerIndex[1])) {
            return TRUE;
        }
    }
    return FALSE;
}
