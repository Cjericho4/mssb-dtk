// 22 register-only diff lines in unrolled loop; needs Bss32A38Entry s8 fields at 2,3,4.
// .text:0x0007AD68 size:0x140 mapped:0x806B9DFC
// Refresh tracked fielding positions after clearing the pitcher's pending state.
void fn_3_7AD68(void) {
    s32 team = g_GameLogic.awayTeamBattingInd_battingTeam;
    s32 pitcher = g_GameLogic.battingOrderAndPositionMapping[team][0][0];
    s32 i;

    if (lbl_3_common_bss_32A38[g_GameLogic.teamFielding][pitcher].unk_0x02 < 0) {
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding][pitcher].unk_0x02 = 0;
    } else {
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding][pitcher].unk_0x04 = 0;
    }
    for (i = 1; i < 10; i++) {
        s32 slot = g_GameLogic.battingOrderAndPositionMapping[team][i][0];
        s32 position = g_GameLogic.battingOrderAndPositionMapping[team][i][1];
        if (position > 0 && lbl_3_common_bss_32A38[g_GameLogic.teamFielding][slot].unk_0x02 == 0 &&
            position != lbl_3_common_bss_32A38[g_GameLogic.teamFielding][slot].unk_0x03) {
            lbl_3_common_bss_32A38[g_GameLogic.teamFielding][slot].unk_0x03 = position;
        }
    }
}

