// Best attempt (4 sbs lines, from a stub): needs a static inline copy of the fn_3_7AEEC loop (setRunnerOnBaseFlags) inlined in the cur==1 branch, plus CommonBss32A94 fields unk20/unk26/unk2B[7]/unk61 (added to UnknownHeaders.h). Left: g_Scores addi lands in r4 (target r5) with g_GameLogic lis in r5 (target r4).
void fn_3_7AFE4(void) {
    u8 team = g_Scores.unkAD;
    s32 cur = g_GameLogic.currentBatterPerTeam[team];

    lbl_3_common_bss_32A94.unk22 = -1;
    lbl_3_common_bss_32A94.unk23 = 0;
    lbl_3_common_bss_32A94.unk24 = 0;
    lbl_3_common_bss_32A94.unk20 = -1;
    lbl_3_common_bss_32A94.unk25 = 0;
    lbl_3_common_bss_32A94.unk26 = 0;
    if (lbl_3_common_bss_32A94.unk61 < 0xFE) {
        lbl_3_common_bss_32A94.unk61++;
    } else {
        lbl_3_common_bss_32A94.unk61 = 0xFF;
    }
    if (cur == 1) {
        if (!(lbl_3_common_bss_32A94.unk61 <= 1 && g_Scores.highscore == 1)) {
            lbl_3_common_bss_32A94.unk44[team]++;
        }
        setRunnerOnBaseFlags();
    }
    lbl_3_common_bss_32A94.unk2B[0] = 0;
    lbl_3_common_bss_32A94.unk2B[1] = 0;
    lbl_3_common_bss_32A94.unk2B[2] = 0;
    lbl_3_common_bss_32A94.unk2B[3] = 0;
    lbl_3_common_bss_32A94.unk2B[4] = 0;
    lbl_3_common_bss_32A94.unk2B[5] = 0;
    lbl_3_common_bss_32A94.unk2B[6] = 0;
}
