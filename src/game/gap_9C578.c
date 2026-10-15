#include "game/gap_9C578.h"
#include "UnknownHeaders.h"
#include "game/gap_AC9F8.h"
#include "game/rep_1770.h"
#include "game/rep_16B8.h"

// .text:0x0009C578 size:0x21C
void fn_3_9C578(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724.unk_A5 == 0) {
        lbl_3_common_bss_32724.unk_A5 = 1;
        lbl_3_common_bss_32724.unk_A6 = 0;
        lbl_3_common_bss_32724.unk_A7 = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        fn_800B0A5C_insertQueue(fn_3_9B7F4, 2);
        if (lbl_3_common_bss_32724.unk_A8 == 0) {
            fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
        }
        if (g_Batter.chemLinksOnBase != 0) {
            fn_800B0A5C_insertQueue(fn_3_99CFC, 2);
        }
    }
    if (lbl_3_common_bss_32724.unk_AC == 1 && g_GameLogic.FrameCountOfCurrentPitch == 10) {
        fn_800B0A5C_insertQueue(fn_3_955CC, 2);
        lbl_3_common_bss_32724.unk_AC = 2;
    }
    if (lbl_3_common_bss_32724.unk_A5 != 0 && lbl_3_common_bss_32724.unk_A6 < 0xFF) {
        if (lbl_3_common_bss_32724.unk_A6 < 0xF0) {
            lbl_3_common_bss_32724.unk_A6 += 0x10;
        } else {
            lbl_3_common_bss_32724.unk_A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724.unk_A7 != 0 && lbl_3_common_bss_32724.unk_A7 < 0xFF) {
        if (lbl_3_common_bss_32724.unk_A7 <= 0x10) {
            lbl_3_common_bss_32724.unk_A7 = 0;
            lbl_3_common_bss_32724.unk_A5 = 0;
        } else {
            lbl_3_common_bss_32724.unk_A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724.unk_A5 != 0) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            if (!g_Batter.moonShotInd || g_Ball.framesSinceHit > 1) {
                lbl_3_common_bss_32724.unk_A7 = 0xF0;
            }
        }
        if (lbl_3_common_bss_34C90.field_0x1D5 != 0) {
            lbl_3_common_bss_32724.unk_A7 = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724.unk_A7 = 0;
        lbl_3_common_bss_32724.unk_A5 = 0;
    }
}

// .text:0x0009C794 size:0x35C
typedef struct {
    u8 _pad0[0xF8];
    s8 unkF8;   /* 0xF8 */
    s8 unkF9;   /* 0xF9 */
    s8 unkFA;   /* 0xFA */
    s8 unkFB;   /* 0xFB */
    s8 unkFC;   /* 0xFC */
    s8 unkFD;   /* 0xFD */
    s8 unkFE;   /* 0xFE */
    s8 unkFF;   /* 0xFF */
    u8 unk100;  /* 0x100 */
    u8 _pad101[0x108 - 0x101];
} Lbl80353A90Struct9C; // size: 0x108

extern Lbl80353A90Struct9C lbl_80353A90;

void fn_3_9C794(void) {
    s32 fieldingScore = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score;
    s32 battingScore = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score;
    s32 prevScore = g_Scores.prevScore;
    s32 count;
    s32 i;
    BOOL flag = FALSE;

    if (g_Scores.unkC2 == 0) {
        return;
    }
    if (prevScore == 0 && battingScore == 0) {
        lbl_3_common_bss_32A94.unk7D = g_Scores.highscore;
        lbl_3_common_bss_32A94.unk7E = g_Scores.unkAD;
        lbl_3_common_bss_32A94.unk88 = g_Scores.highscore;
        lbl_3_common_bss_32A94.unk89 = g_Scores.unkAD;
        lbl_80353A90.unkF8 = g_Pitcher.rosterID;
        flag = TRUE;
    } else if (fieldingScore == battingScore) {
        lbl_3_common_bss_32A94.unk7F = g_Scores.highscore;
        lbl_3_common_bss_32A94.unk80 = g_Scores.unkAD;
        lbl_3_common_bss_32A94.unk81++;
    } else if (fieldingScore > battingScore) {
        if (prevScore == battingScore) {
            if (lbl_3_common_bss_32A94.unk7F != 0 && lbl_3_common_bss_32A94.unk80 == g_Scores.unkAD) {
                lbl_3_common_bss_32A94.unk82 = g_Scores.highscore;
                lbl_3_common_bss_32A94.unk83 = g_Scores.unkAD;
                lbl_3_common_bss_32A94.unk84++;
                lbl_3_common_bss_32A94.unk88 = g_Scores.highscore;
                lbl_3_common_bss_32A94.unk89 = g_Scores.unkAD;
            } else {
                lbl_3_common_bss_32A94.unk85 = g_Scores.highscore;
                lbl_3_common_bss_32A94.unk86 = g_Scores.unkAD;
                lbl_3_common_bss_32A94.unk87++;
                lbl_3_common_bss_32A94.unk88 = g_Scores.highscore;
                lbl_3_common_bss_32A94.unk89 = g_Scores.unkAD;
            }
            lbl_80353A90.unkF8 = g_Pitcher.rosterID;
            flag = TRUE;
        } else if (prevScore < battingScore) {
            lbl_3_common_bss_32A94.unk82 = g_Scores.highscore;
            lbl_3_common_bss_32A94.unk83 = g_Scores.unkAD;
            lbl_3_common_bss_32A94.unk84++;
            lbl_3_common_bss_32A94.unk88 = g_Scores.highscore;
            lbl_3_common_bss_32A94.unk89 = g_Scores.unkAD;
            lbl_80353A90.unkF8 = g_Pitcher.rosterID;
            flag = TRUE;
        }
    }

    if (fieldingScore > battingScore && g_Scores.highscore >= g_Scores.threshold && g_Scores.unkAD != 0) {
        lbl_3_common_bss_32A94.unk8A = g_Scores.highscore;
        lbl_80353A90.unkFA = g_Batter.rosterID;
        if (g_Ball.deadBallReason == 1) {
            lbl_80353A90.unkF9 = g_Batter.rosterID;
            lbl_80353A90.unkFB = g_Batter.rosterID;
        } else {
            count = 0;
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    count++;
                    if (prevScore + count > battingScore) {
                        lbl_80353A90.unkF9 = g_Runners[i].rosterID;
                        break;
                    }
                }
            }
        }
    }

    if (!flag) {
        return;
    }
    if (g_Scores.unkAC >= 3) {
        if (lbl_3_common_bss_32A94.unk22 > 0) {
            lbl_80353A90.unkFC = g_GameLogic.teamBatting;
            lbl_80353A90.unkFD = g_Batter.rosterID;
        } else {
            lbl_80353A90.unkFC = -1;
            lbl_80353A90.unkFD = -1;
        }
    }
    lbl_80353A90.unkFE = g_GameLogic.teamBatting;
    lbl_80353A90.unkFF = g_Batter.rosterID;
    if (lbl_3_common_bss_32A94.unk22 > 0) {
        lbl_80353A90.unk100 = 1;
    } else {
        lbl_80353A90.unk100 = 0;
    }
}
