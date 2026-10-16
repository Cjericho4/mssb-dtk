#include "game/gap_1D86C.h"
#include "game/gap_9CD90.h"
#include "game/gap_AC9F8.h"
#include "game/UnknownHomes_Game.h"

// .text:0x0001D86C size:0x2F0 mapped:0x8065C900
void fn_3_1D86C(void) {
    return;
}

// .text:0x0001DB5C size:0xD4 mapped:0x8065CBF0
void fn_3_1DB5C(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        lbl_3_common_bss_34C90.battingOrder[g_GameLogic.teamFielding][i][0].cur = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
        lbl_3_common_bss_34C90.battingOrder[g_GameLogic.teamFielding][i][0].orig = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
        lbl_3_common_bss_34C90.battingOrder[g_GameLogic.teamFielding][i][1].cur = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
        lbl_3_common_bss_34C90.battingOrder[g_GameLogic.teamFielding][i][1].orig = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
    }
    fn_3_1D86C();
}

// .text:0x0001DC30 size:0x118 mapped:0x8065CCC4
void fn_3_1DC30(void) {
    return;
}

// .text:0x0001DD48 size:0x20 mapped:0x8065CDDC
void fn_3_1DD48(void) {
    fn_3_1FF48();
}

// .text:0x0001DD68 size:0x150 mapped:0x8065CDFC
void fn_3_1DD68(void) {
    s16 a;
    s16 b;
    s32 n;

    g_AiLogic._48 = 1;
    n = 0;
    if (g_RunningLogic.basesOccupied & 0x1000) {
        n = 1;
    }
    if (g_RunningLogic.basesOccupied & 0x100) {
        n++;
    }
    if (g_Scores.unkAC >= 4 && g_Scores.unkAD != 0 && n != 0) {
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score + n > g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score) {
            g_AiLogic._48 = 4;
            return;
        }
    }
    if (g_Scores.unkAC >= 3 && n != 0) {
        a = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score;
        b = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score;
        if (a < b && a + n >= b) {
            g_AiLogic._48 = 3;
            return;
        }
        if (a == b) {
            g_AiLogic._48 = 2;
            return;
        }
    }
    if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score + 5 < g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score) {
        g_AiLogic._48 = 0;
    }
}

