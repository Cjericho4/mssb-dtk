#include "game/gap_9CD90.h"

extern u8 lbl_80361B20[];

// .text:0x0009CD90 size:0xE8 mapped:0x806DBE24
void fn_3_9CD90(void) {
    CommonBss32A94* bss = &lbl_3_common_bss_32A94;
    s32 i;

    if (bss->unk2 != 0) {
        return;
    }
    if (g_Strikes.unk_14 == 3) {
        bss->unk0 = 0x10;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
        if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) {
            if (g_Ball.Hit_VerticalAngle > 0xA0) {
                bss->unk2 = 0x12;
            } else {
                bss->unk2 = 0x13;
            }
        } else {
            bss->unk2 = 0x15;
        }
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].forceOutCd == 2) {
            bss->unk2 = 0x15;
        }
    }
}

// .text:0x0009CE78 size:0x2C8 mapped:0x806DBF0C
void fn_3_9CE78(void) {
    return;
}

// .text:0x0009D140 size:0x234 mapped:0x806DC1D4
void fn_3_9D140(void) {
    return;
}

// .text:0x0009D374 size:0x1DC mapped:0x806DC408
BOOL fn_3_9D374(void) {
    s32 runs;
    BOOL flag = FALSE;

    if (g_Strikes.unk_14 == 1) {
        runs = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score - g_Scores.prevScore;
        if (runs == 1 && g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
            flag = TRUE;
        }
        if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == 0 && g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
            lbl_3_common_bss_32A94.unk0 = 5;
        } else if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == 3) {
            if (runs != 0 && !flag) {
                lbl_3_common_bss_32A94.unk0 = 6;
            } else {
                lbl_3_common_bss_32A94.unk2 = 0xB;
            }
        } else if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == 2) {
            if (runs != 0 && !flag) {
                lbl_3_common_bss_32A94.unk0 = 7;
            } else {
                lbl_3_common_bss_32A94.unk2 = 0xC;
            }
        } else if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == 1) {
            if (g_Ball.ballZoneWhenCaught_s8 >= 0 && g_Ball.ballZoneWhenCaught_s8 <= 1) {
                if (runs != 0 && !flag) {
                    lbl_3_common_bss_32A94.unk0 = 9;
                } else {
                    lbl_3_common_bss_32A94.unk2 = 0xE;
                }
            } else {
                if (runs != 0 && !flag) {
                    lbl_3_common_bss_32A94.unk0 = 8;
                } else {
                    lbl_3_common_bss_32A94.unk2 = 0xD;
                }
            }
        } else {
            if (runs != 0 && !flag) {
                lbl_3_common_bss_32A94.unk2 = 0xA;
            } else {
                lbl_3_common_bss_32A94.unk2 = 0xF;
            }
        }
        return TRUE;
    }
    return FALSE;
}

// .text:0x0009D550 size:0x44 mapped:0x806DC5E4
void fn_3_9D550(void) {
    if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
        lbl_3_common_bss_32A94.unk0 = 0x27;
        return;
    }
    lbl_3_common_bss_32A94.unk0 = 0x2C;
}

// .text:0x0009D594 size:0x6C mapped:0x806DC628
void fn_3_9D594(void) {
    switch (g_RunningLogic.unk12) {
    case 4:
        lbl_3_common_bss_32A94.unk0 = 1;
        return;
    case 3:
        lbl_3_common_bss_32A94.unk0 = 2;
        return;
    case 2:
        lbl_3_common_bss_32A94.unk0 = 3;
        return;
    default:
        lbl_3_common_bss_32A94.unk0 = 4;
        return;
    }
}

// .text:0x0009D600 size:0xA4 mapped:0x806DC694
void fn_3_9D600(void) {
    if (g_Pitcher.strikeOutOrWalk == 1) {
        if (g_Batter.missedBuntStatus != 0) {
            lbl_3_common_bss_32A94.unk2 = 0x26;
        } else if (g_Batter.missSwingOrBunt != 0) {
            lbl_3_common_bss_32A94.unk2 = 0x24;
        } else {
            lbl_3_common_bss_32A94.unk2 = 0x25;
        }
    } else if (g_Pitcher.strikeOutOrWalk == 2) {
        lbl_3_common_bss_32A94.unk2 = 0x2A;
    } else if (g_Pitcher.strikeOutOrWalk == 3) {
        lbl_3_common_bss_32A94.unk0 = 0x2B;
    }
}

// .text:0x0009D6A4 size:0x4B8 mapped:0x806DC738
void fn_3_9D6A4(void) {
    return;
}

// .text:0x0009DB5C size:0x88 mapped:0x806DCBF0
void fn_3_9DB5C(void) {
    s32 i;

    for (i = 4; i > 0; i--) {
        lbl_3_common_bss_32A94.unk6[i] = lbl_3_common_bss_32A94.unk6[i - 1];
    }
    lbl_3_common_bss_32A94.unk6[0] = lbl_3_common_bss_32A94.unk0;
    lbl_3_common_bss_32A94.unk0 = 0;
    lbl_3_common_bss_32A94.unk2 = 0;
    lbl_3_common_bss_32A94.unk4 = 0;
    lbl_3_common_bss_32A94.unk10[0] = -1;
    lbl_3_common_bss_32A94.unk10[1] = -1;
    lbl_3_common_bss_32A94.unk10[2] = -1;
    lbl_3_common_bss_32A94.unk10[3] = -1;
    lbl_3_common_bss_32A94.unk10[4] = -1;
    lbl_3_common_bss_32A94.unk10[5] = -1;
    lbl_3_common_bss_32A94.unk10[6] = -1;
    lbl_3_common_bss_32A94.unk10[7] = -1;
    lbl_3_common_bss_32A94.unk10[8] = -1;
    lbl_3_common_bss_32A94.unk10[9] = -1;
    lbl_3_common_bss_32A94.unk10[10] = -1;
    lbl_3_common_bss_32A94.unk10[11] = -1;
    lbl_3_common_bss_32A94.unk10[12] = -1;
    lbl_3_common_bss_32A94.unk10[13] = -1;
    lbl_3_common_bss_32A94.unk10[14] = -1;
    lbl_3_common_bss_32A94.unk10[15] = -1;
}

// .text:0x0009DBE4 size:0x34 mapped:0x806DCC78
void fn_3_9DBE4(void) {
    lbl_3_common_bss_32A94.unk7D = 0;
    lbl_3_common_bss_32A94.unk7F = 0;
    lbl_3_common_bss_32A94.unk81 = 0;
    lbl_3_common_bss_32A94.unk82 = 0;
    lbl_3_common_bss_32A94.unk84 = 0;
    lbl_3_common_bss_32A94.unk85 = 0;
    lbl_3_common_bss_32A94.unk87 = 0;
    lbl_3_common_bss_32A94.unk88 = 0;
    lbl_3_common_bss_32A94.unk8A = 0;
}

// .text:0x0009DC18 size:0x460 mapped:0x806DCCAC
void fn_3_9DC18(u8* arr, u32 count, s32 arg2) {
    return;
}

// .text:0x0009E078 size:0x2F0 mapped:0x806DD10C
void fn_3_9E078(s32* order, u8 count, s32 arg2) {
    return;
}

static inline int randomIntInline(int max) {
    int ret;
    int absmax = ABS(max);

    if (absmax <= 1) {
        return 0;
    }

    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) +
                              g_Ball.StaticRandomInt2 / absmax + g_Ball.totalFramesAtPlay;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_Ball.StaticRandomInt1 += rand();
    }

    ret = g_Ball.StaticRandomInt1 % absmax;
    ret = ABS(ret);
    if (max < 0) {
        return -ret;
    } else {
        return ret;
    }
}

// .text:0x0009E368 size:0x238 mapped:0x806DD3FC
s32 fn_3_9E368(s32* weights, s32 count) {
    s32 local[10];
    s32 total = 0;
    s32 r;
    s32 i;

    for (i = 0; i < count; i++) {
        local[i] = weights[i];
        total += local[i];
    }
    r = randomIntInline(total);
    for (i = 0; i < count; i++) {
        if (r < local[i]) {
            return i;
        }
        r -= local[i];
    }
    return 0;
}


// .text:0x0009E5A0 size:0x234 mapped:0x806DD634
s32 fn_3_9E5A0(u8* weights, s32 count) {
    s32 local[10];
    s32 total = 0;
    s32 r;
    s32 i;

    for (i = 0; i < count; i++) {
        local[i] = weights[i];
        total += local[i];
    }
    r = randomIntInline(total);
    for (i = 0; i < count; i++) {
        if (r < local[i]) {
            return i;
        }
        r -= local[i];
    }
    return 0;
}

// .text:0x0009E7D4 size:0x60 mapped:0x806DD868
void fn_3_9E7D4(s32 arg0) {
    if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        return;
    }
    if (g_GameLogic.currentBatterPerTeam[arg0] == 9) {
        g_GameLogic.currentBatterPerTeam[arg0] = 1;
        return;
    }
    g_GameLogic.currentBatterPerTeam[arg0]++;
}

// .text:0x0009E834 size:0x1E8 mapped:0x806DD8C8
BOOL fn_3_9E834(void) {
    s32 i;

    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        for (i = 0; i < 54; i++) {
            if (starMissionCompletionTracker.unk43D6[i] != 0) {
                return TRUE;
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            if (lbl_80361B20[i] != 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x0009EA1C size:0xC8 mapped:0x806DDAB0
BOOL fn_3_9EA1C(s32 team) {
    s32 i;

    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[team][i][1] % 10 == 9) {
            return TRUE;
        }
    }
    return FALSE;
}

