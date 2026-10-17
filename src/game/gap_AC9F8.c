#include "game/gap_AC9F8.h"
#include "game/gap_B3B70.h"
#include "game/gap_1E154.h"
#include "game/rep_540.h"
#include "game/rep_1038.h"
#include "game/rep_E08.h"
#include "game/rep_1B70.h"
#include "game/rep_1188.h"
extern u8 lbl_803CBC3C;
void fn_3_BF158(void);
void fn_3_BF1AC(void);
#include "musyx/musyx.h"
#include "game/rep_1838.h"
#include "game/rep_1C0.h"

typedef struct {
    /* 0x0 */ s16 power;
    /* 0x2 */ s16 verticalAngle;
    /* 0x4 */ s16 horizontalAngle;
} PracticeHitParams; /* size: 0x6 */
extern PracticeHitParams lbl_3_data_FB08[10];
extern PracticeHitParams lbl_3_data_FB44[10];
extern PracticeHitParams lbl_3_data_FB80[10];
extern PracticeHitParams lbl_3_data_FBBC[10];
extern s16 lbl_3_data_FBF8[8];

// .text:0x000AC9F8 size:0x100 mapped:0x806EBA8C
void fn_3_AC9F8(void) {
    if (lbl_3_common_bss_32724.unk_C3 != 0) {
        return;
    }
    if (lbl_3_common_bss_34C90.field_0x06 & 0x200) {
        lbl_3_common_bss_34C90.field_0x1D2 = 5;
        sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
    } else if (g_d_GameSettings.GameModeSelected != 6) {
        if ((lbl_3_common_bss_34C90.field_0x08 & 1) && lbl_3_common_bss_34C90.unk_221 != 0) {
            lbl_3_common_bss_34C90.unk_221--;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        } else if ((lbl_3_common_bss_34C90.field_0x08 & 2) && lbl_3_common_bss_34C90.unk_221 < lbl_3_common_bss_34C90.field_0x222 - 1) {
            lbl_3_common_bss_34C90.unk_221++;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        }
    }
}

// .text:0x000ACAF8 size:0x240 mapped:0x806EBB8C
void fn_3_ACAF8(void) {
    return;
}

// .text:0x000ACD38 size:0x42C mapped:0x806EBDCC
void fn_3_ACD38(void) {
    return;
}

// .text:0x000AD164 size:0x13C mapped:0x806EC1F8
void fn_3_AD164(s32 arg0) {
    switch (lbl_3_common_bss_34C90.field_0x1D2) {
    case 0:
        lbl_3_common_bss_34C90.field_0x23F[lbl_3_common_bss_34C90.field_0x00] = 0;
        if (g_GameLogic._13E[lbl_3_common_bss_34C90.field_0x00 ^ 1] == 0) {
            lbl_3_common_bss_34C90.field_0x23F[lbl_3_common_bss_34C90.field_0x00 ^ 1] = 1;
        } else {
            lbl_3_common_bss_34C90.field_0x23F[lbl_3_common_bss_34C90.field_0x00 ^ 1] = 0xFF;
        }
        lbl_3_common_bss_34C90.field_0x1D2 = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.field_0x12 = 0;
        lbl_3_common_bss_34C90.field_0x1D2 = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.field_0x12 > 20) {
            lbl_3_common_bss_34C90.field_0x1D2 = 3;
        }
        break;
    case 3:
        fn_3_ACD38();
        break;
    case 4:
        lbl_3_common_bss_34C90.field_0x12 = 0;
        lbl_3_common_bss_34C90.field_0x1D2 = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.field_0x12 > 20) {
            lbl_3_common_bss_34C90.field_0x1D2 = 6;
        }
        break;
    case 6:
        if (arg0 == 0) {
            lbl_3_common_bss_34C90.field_0x1D1 = 2;
            lbl_3_common_bss_34C90.field_0x1D2 = 0;
            lbl_3_common_bss_34C90.field_0x0C = 0;
            lbl_3_common_bss_34C90.field_0x0E = 0;
            lbl_3_common_bss_34C90.field_0x10 = 0;
        } else {
            lbl_3_common_bss_34C90.field_0x1D1 = 9;
            lbl_3_common_bss_34C90.field_0x1D2 = 0;
            lbl_3_common_bss_34C90.field_0x0C = 0;
            lbl_3_common_bss_34C90.field_0x0E = 0;
            lbl_3_common_bss_34C90.field_0x10 = 0;
        }
        break;
    }
}

// .text:0x000AD2A0 size:0x11C mapped:0x806EC334
void fn_3_AD2A0(void) {
    s32 i;
    s32 j;
    s32 pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];

    for (i = 0; i < 9; i++) {
        for (j = 1; j < 10; j++) {
            if (i == g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][0]) {
                if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][1] !=
                    lbl_3_common_bss_34C90.field_0x242[i]) {
                    lbl_3_common_bss_34C90.field_0x260 = 1;
                }
                g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][1] =
                    lbl_3_common_bss_34C90.field_0x242[i];
                if (lbl_3_common_bss_34C90.field_0x242[i] == 0) {
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0] = i;
                    if (pitcher != g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]) {
                        g_GameLogic.playOverInd = 1;
                    }
                }
            }
        }
    }
    fn_3_596F8();
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
}

// .text:0x000AD3BC size:0x510 mapped:0x806EC450
void fn_3_AD3BC(void) {
    return;
}

// .text:0x000AD8CC size:0x170 mapped:0x806EC960
void fn_3_AD8CC(void) {
    return;
}

// .text:0x000ADA3C size:0x4A0 mapped:0x806ECAD0
void fn_3_ADA3C(void) {
    return;
}

// .text:0x000ADEDC size:0x458 mapped:0x806ECF70
void fn_3_ADEDC(void) {
    return;
}

// .text:0x000AE334 size:0x43C mapped:0x806ED3C8
void fn_3_AE334(void) {
    return;
}

// .text:0x000AE770 size:0x190 mapped:0x806ED804
void fn_3_AE770(void) {
    return;
}

// .text:0x000AE900 size:0x350 mapped:0x806ED994
void fn_3_AE900(void) {
    return;
}

// .text:0x000AEC50 size:0x3A8 mapped:0x806EDCE4
void fn_3_AEC50(void) {
    return;
}

// .text:0x000AEFF8 size:0x114 mapped:0x806EE08C
void fn_3_AEFF8(void) {
    s32 i;

    lbl_3_common_bss_34C90.unk254 = -1;
    lbl_3_common_bss_34C90.unk258 = -1;
    lbl_3_common_bss_34C90.unk256 = -1;
    lbl_3_common_bss_34C90.unk25A = -1;
    for (i = 0; i < 9; i++) {
        if (lbl_80354720[lbl_3_common_bss_34C90.field_0x00][i].unk2 == 0) {
            lbl_3_common_bss_34C90.unk25C = i;
        }
        if (lbl_80354720[lbl_3_common_bss_34C90.field_0x00][i].unk2 == 1) {
            lbl_3_common_bss_34C90.unk25E = i;
        }
    }
}

// .text:0x000AF10C size:0x31C mapped:0x806EE1A0
void fn_3_AF10C(void) {
    return;
}

// .text:0x000AF428 size:0x17C mapped:0x806EE4BC
void fn_3_AF428(void) {
    return;
}

// .text:0x000AF5A4 size:0x4C0 mapped:0x806EE638
void fn_3_AF5A4(void) {
    return;
}

// .text:0x000AFA64 size:0x100 mapped:0x806EEAF8
void fn_3_AFA64(void) {
    if (lbl_3_common_bss_34C90.field_0x0C < 0x7FFE) {
        lbl_3_common_bss_34C90.field_0x0C++;
    } else {
        lbl_3_common_bss_34C90.field_0x0C = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (lbl_3_common_bss_34C90.field_0x0C > 0x3C) {
        if (lbl_3_common_bss_34C90.field_0x1D8 == 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                lbl_3_common_bss_34C90.field_0x1D0 = 2;
            } else {
                lbl_3_common_bss_34C90.field_0x1D0 = 0;
            }
        } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
            lbl_3_common_bss_34C90.field_0x1D0 = 3;
        } else {
            lbl_3_common_bss_34C90.field_0x1D0 = 1;
        }
        lbl_3_common_bss_34C90.field_0x1D1 = 1;
        lbl_3_common_bss_34C90.field_0x1D2 = 0;
        lbl_3_common_bss_34C90.field_0x0C = 0;
        lbl_3_common_bss_34C90.field_0x0E = 0;
        lbl_3_common_bss_34C90.field_0x10 = 0;
        fn_3_5A6D4(0xB);
        fn_3_BF1AC();
        fn_3_BF158();
    } else {
        fn_3_31594();
        fn_3_8A958();
    }
}

// .text:0x000AFB64 size:0x1E4 mapped:0x806EEBF8
void fn_3_AFB64(void) {
    return;
}

// .text:0x000AFD48 size:0x38 mapped:0x806EEDDC
s32 fn_3_AFD48(s16 arg0) {
    if ((s8) lbl_3_common_bss_34C90.field_0x206 <= 0) {
        lbl_3_common_bss_34C90.field_0x04 = arg0;
        lbl_3_common_bss_34C90.field_0x06 = arg0;
        lbl_3_common_bss_34C90.field_0x08 = arg0;
        lbl_3_common_bss_34C90.field_0x206 = 0xD;
        return 1;
    }
    return 0;
}

// .text:0x000AFD80 size:0x24 mapped:0x806EEE14
void fn_3_AFD80(u8 arg0) {
    lbl_3_common_bss_34C90.field_0x1D1 = arg0;
    lbl_3_common_bss_34C90.field_0x1D2 = 0;
    lbl_3_common_bss_34C90.field_0x0C = 0;
    lbl_3_common_bss_34C90.field_0x0E = 0;
    lbl_3_common_bss_34C90.field_0x10 = 0;
}

// .text:0x000AFDA4 size:0x1C mapped:0x806EEE38
void fn_3_AFDA4(void) {
    lbl_3_common_bss_34C90.field_0x1D5 = 0;
    lbl_3_common_bss_34C90.field_0x1D6 = 0;
    lbl_3_common_bss_34C90.field_0x1D7 = 0;
}

// .text:0x000AFDC0 size:0x4C mapped:0x806EEE54
void fn_3_AFDC0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

// .text:0x000AFE0C size:0x230 mapped:0x806EEEA0
void fn_3_AFE0C(void) {
    InputStruct* in;
    s16 limit;

    limit = 0x78;
    in = &g_Controls[g_Practice.homeAway];
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator != 0) {
            limit = 0x3C;
        } else {
            g_FieldingLogic.unkAE = 0;
            return;
        }
    } else if (g_Ball.AtBat_ContactResult == 0) {
        g_FieldingLogic.unkAE = 0;
        return;
    } else if (g_Practice.guidedPracticeCompletionRelated != 0) {
        g_FieldingLogic.unkAE = 0;
        return;
    } else if (g_Ball.deadBallReason == 1) {
        if (g_Practice._1B0 == 0) {
            if (in->newButtonInput & 0x1100) {
                g_Practice._1B0 = 1;
            }
            limit = 0x12C;
        } else {
            limit = 0x2D;
        }
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 0x1E;
    } else if (g_Ball.framesSinceHit > 0xB4) {
        limit = 0x78;
    }
    if (g_FieldingLogic.unkAE < 0x7FFE) {
        g_FieldingLogic.unkAE++;
    } else {
        g_FieldingLogic.unkAE = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > limit && g_FieldingLogic.unkAE > limit - 0x5A) {
        g_FieldingLogic.unkAE = 0;
        g_FieldingLogic.unkEE = 0;
    }
    if (g_FieldingLogic.unkAE >= limit) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
    } else if (g_FieldingLogic.unkAE >= limit - 6) {
        changeScene(3, 6);
    } else if (g_FieldingLogic.unkAE == limit - 0x1E) {
        g_FieldingLogic.unk10E = 1;
        g_FieldingLogic.unkEE = 1;
    }
    g_GameLogic.framePlayEnd = limit;
    g_GameLogic.CountdownUntilFade = limit - g_FieldingLogic.unkAE;
}

// .text:0x000B003C size:0x1A4 mapped:0x806EF0D0
void fn_3_B003C(void) {
    return;
}

// .text:0x000B01E0 size:0x7C mapped:0x806EF274
void fn_3_B01E0(void) {
    ballPhysica();
    fn_3_598D0();

    if (g_Ball.framesSinceHit == 0x3C) {
        g_Fielders[0].pos[0] = g_Pitcher.pitcherCoord.x;
        g_Fielders[0].pos[2] = g_Pitcher.pitcherCoord.z;
    }

    fn_3_AFE0C();

    if (g_Practice.instructionNumber < 0 && g_Practice.guidedPracticeCompletionRelated2 == 0) {
        fn_3_B003C();
    }
}

// .text:0x000B025C size:0x4C mapped:0x806EF2F0
void fn_3_B025C(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        fn_3_75560();
        atBat_batter();
        fn_3_8A958();
        fn_3_31594();
    }
}

// .text:0x000B02A8 size:0x148 mapped:0x806EF33C
extern s16 lbl_3_data_FC1C[2];
void fn_3_B02A8(void) {
    fn_3_5F720();
    if ((u8) g_Practice.practiceLevel == 4) {
        g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_FC1C[1];
    }
    g_Strikes.unk_C = g_Strikes.outs;
    g_Strikes.unk_18[0] = -1;
    g_Strikes.unk_18[1] = -1;
    g_Strikes.unk_18[2] = -1;
    g_Strikes.unk_20 = g_Strikes.balls + (g_Strikes.strikes * 0x10);
    g_Strikes.unk_14 = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.unk10E = 0;
    g_FieldingLogic.unkEE = 0;
    g_FieldingLogic.unk10F = 0;
    g_FieldingLogic.unk110 = 0;
    g_FieldingLogic.unk128 = 0;
    g_FieldingLogic.unk129 = 0;
    g_RunningLogic.unk13 = 0;
    if ((u8) g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    g_Practice._1B0 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1U);
    fn_3_6C0E0();
    if ((u8) lbl_3_common_bss_34C58._2A != 0) {
        lbl_3_common_bss_34C58._2A = 2;
        lbl_3_common_bss_34C58._24 = 0x78;
    }
}

// .text:0x000B03F0 size:0x74 mapped:0x806EF484
void fn_3_B03F0(void) {
    fn_3_F578();
    fn_3_753E8(0);
    setBatterContactConstants();
    fn_3_8A1D8();
    fn_3_58E50();
    fn_3_1E154();
    fn_3_59A90();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_B02A8();
    fn_3_6714C(0);
}

// .text:0x000B0464 size:0x108 mapped:0x806EF4F8
s32 fn_3_B0464(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return 0;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return 0;
    }
    if (g_UnkSound_32718._07 != 0) {
        return 0;
    }
    if (++g_Practice._186 > 150) {
        if (g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.practiceCompletedChanged = 1;
            g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            lbl_80354768.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
        }
        g_Practice._1C7 = 1;
        fn_3_B3A28();
        fn_3_B1DA4(g_Practice.practiceLevel + 4, 1);
        return 1;
    }
    return 0;
}

// .text:0x000B056C size:0x308 mapped:0x806EF600
void fn_3_B056C(void) {
    return;
}

// .text:0x000B0874 size:0x214 mapped:0x806EF908
void fn_3_B0874(void) {
    return;
}

// .text:0x000B0A88 size:0x24 mapped:0x806EFB1C
void fn_3_B0A88(void) {
    fn_3_B3C78(0);
}

// .text:0x000B0AAC size:0xB0 mapped:0x806EFB40
void fn_3_B0AAC(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_B0874();
        break;
    case 1:
        fn_3_B056C();
        break;
    case 2:
        if (fn_3_B254C() == FALSE) {
            fn_3_B056C();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel + 4, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B056C();
        break;
    }
    g_GameLogic.TeamStars[0] = g_GameLogic.TeamStars[1] = 5;
}

// .text:0x000B0B5C size:0x198 mapped:0x806EFBF0
void fn_3_B0B5C(void) {
    PracticeStruct* practice = &g_Practice;
    s32 idx;

    if (practice->hitVariablesSetIndicator != 0) {
        return;
    }
    if (++practice->_152 < lbl_3_data_FBF8[0]) {
        return;
    }
    if (practice->practiceLevel == 0) {
        idx = fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = lbl_3_data_FB08[idx].power;
        g_Ball.Hit_VerticalAngle = lbl_3_data_FB08[idx].verticalAngle;
        g_Ball.Hit_HorizontalAngle = lbl_3_data_FB08[idx].horizontalAngle;
    } else if (practice->practiceLevel == 1) {
        idx = fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = lbl_3_data_FB44[idx].power;
        g_Ball.Hit_VerticalAngle = lbl_3_data_FB44[idx].verticalAngle;
        g_Ball.Hit_HorizontalAngle = lbl_3_data_FB44[idx].horizontalAngle;
    } else if (practice->practiceLevel == 2) {
        idx = fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = lbl_3_data_FB80[idx].power;
        g_Ball.Hit_VerticalAngle = lbl_3_data_FB80[idx].verticalAngle;
        g_Ball.Hit_HorizontalAngle = lbl_3_data_FB80[idx].horizontalAngle;
    } else if (practice->practiceLevel == 3) {
        idx = fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = lbl_3_data_FBBC[idx].power;
        g_Ball.Hit_VerticalAngle = lbl_3_data_FBBC[idx].verticalAngle;
        g_Ball.Hit_HorizontalAngle = lbl_3_data_FBBC[idx].horizontalAngle;
    }
    practice->hitVariablesSetIndicator = 1;
    if (g_Practice.maybeCommandData[0] < 0x7FFE) {
        g_Practice.maybeCommandData[0]++;
    } else {
        g_Practice.maybeCommandData[0] = 0x7FFF;
    }
}

// .text:0x000B0CF4 size:0x38 mapped:0x806EFD88
s32 fn_3_B0CF4(void) {
    if (g_Practice.aiBuntIndicator == 0) {
        return 0;
    }
    return g_Ball.pitchHangtimeCounter > 0;
}

// .text:0x000B0D2C size:0x4C mapped:0x806EFDC0
void fn_3_B0D2C(void) {
    if (g_Practice.aiBuntIndicator != 0) return;
    if ((g_Pitcher.framesUntilUnhittable + 1) != swingSoundFrame[0][1]) return;
    g_AiLogic.batterAISwingInd = 1;
}

// .text:0x000B0D78 size:0x4 mapped:0x806EFE0C
void fn_3_B0D78(void) {
    return;
}

// .text:0x000B0D7C size:0x34 mapped:0x806EFE10
void fn_3_B0D7C(void) {
    g_Pitcher.handedness = g_Fielders[0].unk1C7;
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
}

// .text:0x000B0DB0 size:0x50 mapped:0x806EFE44
void fn_3_B0DB0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7U);
}

// .text:0x000B0E00 size:0x320 mapped:0x806EFE94
void fn_3_B0E00(void) {
    return;
}

// .text:0x000B1120 size:0x4C mapped:0x806F01B4
void fn_3_B1120(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        ballPhysica();
        fn_3_598D0();
        fn_3_8A958();
        fn_3_B0E00();
    }
}

// .text:0x000B116C size:0x64 mapped:0x806F0200
void fn_3_B116C(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        if ((u8)g_Practice.hitVariablesSetIndicator == 0) {
            fn_3_B0B5C();
        }
        fn_3_75560();
        atBat_batter();
        fn_3_8A958();
        fn_3_31594();
    }
}

// .text:0x000B11D0 size:0x128 mapped:0x806F0264
void fn_3_B11D0(void) {
    fn_3_5F720();
    g_Pitcher.handedness = g_Fielders->unk1C7;
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
    g_Strikes.unk_C = g_Strikes.outs;
    g_Strikes.unk_18[0] = -1;
    g_Strikes.unk_18[1] = -1;
    g_Strikes.unk_18[2] = -1;
    g_Strikes.unk_20 = g_Strikes.balls + (g_Strikes.strikes * 0x10);
    g_Strikes.unk_14 = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.unk10E = 0;
    g_FieldingLogic.unkEE = 0;
    g_FieldingLogic.unk10F = 0;
    g_FieldingLogic.unk110 = 0;
    g_FieldingLogic.unk128 = 0;
    g_FieldingLogic.unk129 = 0;
    g_RunningLogic.unk13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.hitVariablesSetIndicator = 0;
    g_Practice._1E4[0] = 0;
    g_Practice._1CB = 0;
    g_Strikes.outs = 0;
    g_Practice._152 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1U);
    fn_3_6C0E0();
}

// .text:0x000B12F8 size:0x178 mapped:0x806F038C
void fn_3_B12F8(void) {
    fn_3_F578();
    fn_3_753E8(0);
    setBatterContactConstants();
    fn_3_8A1D8();
    fn_3_58E50();
    fn_3_1E154();
    fn_3_59A90();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_5F720();
    g_Pitcher.handedness = g_Fielders->unk1C7;
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
    g_Strikes.unk_C = g_Strikes.outs;
    g_Strikes.unk_18[0] = -1;
    g_Strikes.unk_18[1] = -1;
    g_Strikes.unk_18[2] = -1;
    g_Strikes.unk_20 = g_Strikes.balls + (g_Strikes.strikes * 0x10);
    g_Strikes.unk_14 = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.unk10E = 0;
    g_FieldingLogic.unkEE = 0;
    g_FieldingLogic.unk10F = 0;
    g_FieldingLogic.unk110 = 0;
    g_FieldingLogic.unk128 = 0;
    g_FieldingLogic.unk129 = 0;
    g_RunningLogic.unk13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.hitVariablesSetIndicator = 0;
    g_Practice._1E4[0] = 0;
    g_Practice._1CB = 0;
    g_Strikes.outs = 0;
    g_Practice._152 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1U);
    fn_3_6C0E0();
    fn_3_6714C(0);
}

// .text:0x000B1470 size:0x108 mapped:0x806F0504
s32 fn_3_B1470(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return 0;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return 0;
    }
    if (g_UnkSound_32718._07 != 0) {
        return 0;
    }
    if (++g_Practice._186 > 150) {
        if (g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.practiceCompletedChanged = 1;
            g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            lbl_80354768.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
        }
        g_Practice._1C7 = 1;
        fn_3_B3A28();
        fn_3_B1DA4(g_Practice.practiceLevel + 8, 1);
        return 1;
    }
    return 0;
}

// .text:0x000B1578 size:0x4B8 mapped:0x806F060C
void fn_3_B1578(void) {
    return;
}

// .text:0x000B1A30 size:0x19C mapped:0x806F0AC4
void fn_3_B1A30(void) {
    return;
}

// .text:0x000B1BCC size:0x48 mapped:0x806F0C60
void fn_3_B1BCC(void) {
    g_Practice.__0x1e1padding[1] = 0;
    g_Practice.__0x1e1padding[2] = 0;
    g_Practice.__0x1e1padding[3] = 0;
    g_Practice.__0x1e1padding[4] = 0;
    g_Practice._1E2 = 0;
    g_Practice.maybeCommandData[0] = 0;
    fn_3_B3C78(0);
}

// .text:0x000B1C14 size:0x9C mapped:0x806F0CA8
void fn_3_B1C14(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_B1A30();
        break;
    case 1:
        fn_3_B1578();
        break;
    case 2:
        if (fn_3_B254C() == FALSE) {
            fn_3_B1578();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel + 8, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B1578();
        break;
    }
}

extern s16 lbl_3_data_104B8[16][2][3];

// .text:0x000B1CB0 size:0xF4 mapped:0x806F0D44
BOOL fn_3_B1CB0(void) {
    InputStruct* in = &g_Controls[g_Practice._192];

    if (g_Practice.loadingGuidedPractice == 0) {
        return FALSE;
    }
    if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2) {
        return FALSE;
    }
    if (g_Practice._188 < 0x7FFE) {
        g_Practice._188++;
    } else {
        g_Practice._188 = 0x7FFF;
    }
    if (g_Practice._188 > 90 && (in->newButtonInput & 0x1100)) {
        u8 step = g_Practice._1D8 + 1;

        g_Practice._1D8 = step;
        if (step >= 3 || lbl_3_data_104B8[g_Practice.practiceLevel_2][g_Practice._1D7][step] < 0) {
            g_Practice.loadingGuidedPractice = 0;
        }
    }
    return TRUE;
}

// .text:0x000B1DA4 size:0x2C mapped:0x806F0E38
void fn_3_B1DA4(s32 arg0, u8 arg1) {
    g_Practice.loadingGuidedPractice = 1;
    g_Practice._1D5 = 0;
    g_Practice.practiceLevel_2 = arg0;
    g_Practice._1D7 = arg1;
    g_Practice._1D8 = 0;
    g_Practice._188 = 0;
}

// .text:0x000B1DD0 size:0x77C mapped:0x806F0E64
void fn_3_B1DD0(void) {
    return;
}

// .text:0x000B254C size:0xE4 mapped:0x806F15E0

BOOL fn_3_B254C(void) {
    if (g_Practice.transitioningIndicator == 0) {
        lbl_80366158._28 = 1;
        switch (g_Practice.practiceState) {
        case 0:
            g_Practice.framesInCurrTransitionState = 0;
            g_Practice.practiceState++;
            break;
        case 1:
            if (g_Practice.framesInCurrTransitionState > 30) {
                changeScene(3, 6);
                g_Practice.practiceState++;
            }
            break;
        case 2:
            if (lbl_8037169C._13 != 0) {
                g_Practice.practiceState++;
            }
            break;
        case 3:
            goto done;
        }
    } else {
    done:
        minigamesSetSomePointers();
        fn_3_B3A4C();
        return TRUE;
    }
    return FALSE;
}

// .text:0x000B2630 size:0x11C mapped:0x806F16C4
void fn_3_B2630(void) {
    InputStruct *temp_r7;

    temp_r7 = &g_Controls[g_Practice.homeAway];
    if (g_Practice.framesOnAllInstructions < 0x7FFE) {
        g_Practice.framesOnAllInstructions += 1;
    } else {
        g_Practice.framesOnAllInstructions = 0x7FFF;
    }
    if ((g_Practice.instructionComplete_readyToAdvance == 0) && (g_Practice.allInstructionsComplete == 0)) {
        if (g_Practice.framesOnCurrInstruction < 0x7FFE) {
            g_Practice.framesOnCurrInstruction += 1;
        } else {
            g_Practice.framesOnCurrInstruction = 0x7FFF;
        }
    }
    if ((g_Practice.tutorialState == 1) && (temp_r7->newButtonInput & 0x1000)) {
        if (g_Practice.tutorialState != 2) {
            g_Practice.practiceState = 0;
            g_Practice.tutorialState = 2;
            g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        }
    } else if (g_Practice.allInstructionsComplete != 0) {
        if ((temp_r7->newButtonInput & 0x100) && (g_Practice.tutorialState != 2)) {
            g_Practice.practiceState = 0;
            g_Practice.tutorialState = 2;
            g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        }
    } else {
        fn_3_B1DD0();
    }
}

// .text:0x000B274C size:0x58 mapped:0x806F17E0
void fn_3_B274C(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        g_Practice.inputs[i].controlStickAngle = -1;
        g_Practice.inputs[i].controlStickMagnitude = 0;
        g_Practice.inputs[i].buttonInput = 0;
        g_Practice.inputs[i].newButtonInput = 0;
        g_Practice.inputs[i]._08 = 0;
        g_Practice.inputs[i].right_left = 0;
        g_Practice.inputs[i].up_down = 0;
        g_Practice.inputs[i].rightTriggerDistance = 0;
        g_Practice.inputs[i].leftTriggerDistance = 0;
    }
}

// .text:0x000B27A4 size:0x104 mapped:0x806F1838
void fn_3_B27A4(void) {
    g_Practice.framesOnAllInstructions = 0;
    g_Practice._164 = 0;
    g_Practice.framesOnCurrInstruction = 0;
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.lakituTextIndex_stored = -1;
    g_Practice.diagramTextChannelIndex = -1;
    g_Practice.diagramTitleTextIndex_stored = -1;
    g_Practice.cpuCommandDuration = 0;
    g_Practice.instructionNumber = 0;
    g_Practice.currentMessageDoneTyping = 0;
    g_Practice.commandIndex = 0;
    g_Practice.allInstructionsComplete = 0;
    g_Practice.instructionComplete_readyToAdvance = 0;
    g_Practice.allowPlayToEndIndicator = 0;
    g_Practice._1C7 = 0;
    g_Practice.guidedPracticeCompletionRelated = 0;
    g_Practice.guidedPracticeCounter = 0;
    g_Practice.maybeControlFlag1 = 0;
    g_Practice.maybeControlFlag2 = 0;
    g_Practice.practice_runner_countInputForMashing = 0;
    g_Practice.practice_fielding_enableSprinting = 0;
    g_Practice._1C6 = 0;
    g_Practice.textRelatedIndicator = 0;
    g_Practice.maybePreviousInput = 0;
    g_Practice._17A = 0;
    g_Practice.cpu_inputDuration = 0;
    g_Practice._17E = 0;
    g_Practice._186 = 0;
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.inputs[0].controlStickAngle = -1;
    g_Practice.inputs[0].controlStickMagnitude = 0;
    g_Practice.inputs[0].buttonInput = 0;
    g_Practice.inputs[0].newButtonInput = 0;
    g_Practice.inputs[0]._08 = 0;
    g_Practice.inputs[0].right_left = 0;
    g_Practice.inputs[0].up_down = 0;
    g_Practice.inputs[0].rightTriggerDistance = 0;
    g_Practice.inputs[0].leftTriggerDistance = 0;
    g_Practice.inputs[1].controlStickAngle = -1;
    g_Practice.inputs[1].controlStickMagnitude = 0;
    g_Practice.inputs[1].buttonInput = 0;
    g_Practice.inputs[1].newButtonInput = 0;
    g_Practice.inputs[1]._08 = 0;
    g_Practice.inputs[1].right_left = 0;
    g_Practice.inputs[1].up_down = 0;
    g_Practice.inputs[1].rightTriggerDistance = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.batterHandedness[1] = 0;
    g_GameLogic.batterHandedness[0] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.teamAIInd[0] = 0;
    g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.battingAIInd[1] = 0;
    g_GameLogic.battingAIInd[0] = 0;
    g_Practice.inputs[1].leftTriggerDistance = 0;
}

extern CompressedDiskRead lbl_3_data_10598[];
s32 fn_80035838(CompressedDiskRead* list, s32 count);
void fn_80035B50(s32 arg0);

// .text:0x000B28A8 size:0x1F8 mapped:0x806F193C
void fn_3_B28A8(void) {
    InputStruct* in = &g_Controls[g_Practice.homeAway];

    switch (lbl_3_common_bss_34C90.field_0x1D3) {
    case 0:
        lbl_3_common_bss_34C90.unk_221 = 1;
        lbl_3_common_bss_34C90.field_0x222 = 3;
        lbl_3_common_bss_34C90.field_0x1D9 = 1;
        lbl_3_common_bss_34C90.field_0x1D3 = 1;
        break;
    case 1:
        if (fn_80035838(&lbl_3_data_10598[2], 0x13) != 0) {
            lbl_3_common_bss_34C90.field_0x1D3 = 2;
        }
        break;
    case 2:
        if (lbl_3_common_bss_34C90.field_0x1D9 == 3) {
            lbl_3_common_bss_34C90.field_0x1D3 = 3;
        }
        break;
    case 3:
        lbl_3_common_bss_34C90.field_0x1D3 = 4;
        break;
    case 4:
        if (lbl_3_common_bss_32724.unk_C3 == 0) {
            lbl_3_common_bss_34C90.field_0x1D3 = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_32724.unk_C3 != 0) {
            break;
        }
        if (in->newButtonInput & 0x200) {
            lbl_3_common_bss_34C90.field_0x1D3 = 6;
            sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
        } else if ((in->_08 & 1) && lbl_3_common_bss_34C90.unk_221 != 0) {
            lbl_3_common_bss_34C90.unk_221--;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        } else if ((in->_08 & 2) && lbl_3_common_bss_34C90.unk_221 < lbl_3_common_bss_34C90.field_0x222 - 1) {
            lbl_3_common_bss_34C90.unk_221++;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        }
        break;
    case 6:
        lbl_3_common_bss_34C90.field_0x1D3 = 7;
        break;
    case 7:
        if (lbl_3_common_bss_32724.unk_C3 == 0) {
            fn_80035B50(0x13);
            lbl_3_common_bss_34C90.field_0x1D2 = 0;
        }
        break;
    }
}

// .text:0x000B2AA0 size:0x380 mapped:0x806F1B34
void fn_3_B2AA0(void) {
    return;
}

// .text:0x000B2E20 size:0x468 mapped:0x806F1EB4
void fn_3_B2E20(void) {
    return;
}

// .text:0x000B3288 size:0x30 mapped:0x806F231C
void fn_3_B3288(void) {
    g_Practice.pauseMenuLoading = 0;
    g_Practice._19F = 1;
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90.field_0x1D2 = 0;
    lbl_3_common_bss_34C90.field_0x1DA = 0;
}

// .text:0x000B32B8 size:0x190 mapped:0x806F234C
s32 fn_3_B32B8(void) {
    PracticeStruct* practice = &g_Practice;
    InputStruct* controls = &g_Controls[practice->homeAway];

    if (g_hugeAnimStruct.maybe_loadingBatterModel_State != 0) {
        return 0;
    }
    if (g_hugeAnimStruct.maybe_relatedToLoadingBatter != 0) {
        return 0;
    }
    if (practice->_186 != 0 || practice->guidedPracticeCompletionRelated != 0) {
        return 0;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0x1E || lbl_8037169C._10 != 0) {
        return 0;
    }
    if (practice->pauseMenuLoading != 0) {
        lbl_80366158._28 = 1;
        if (++practice->frames_sinceTimeCalled >= 0x3C) {
            practice->pauseMenuLoading = 0;
            practice->_19F = 1;
            practice->frames_onPauseScreen = 0;
            lbl_3_common_bss_34C90.field_0x1D2 = 0;
            lbl_3_common_bss_34C90.field_0x1DA = 0;
        }
        return 1;
    }
    if (practice->practiceType_2 == 4 && g_Pitcher.pitchTotalTimeCounter > 0) {
        return 0;
    }
    if (controls->newButtonInput & 0x1000) {
        lbl_80366158._28 = 1;
        fn_3_59918(0xE, 0);
        practice->pauseMenuLoading = 1;
        g_Practice.frames_sinceTimeCalled = 0;
        return 1;
    }
    return 0;
}

typedef struct {
    u8 count;   /* 0x0 */
    u8 vals[4]; /* 0x1 */
} PracticeMenuRow; /* size: 0x5 */
extern PracticeMenuRow lbl_3_data_FAE8[];

// .text:0x000B3448 size:0x1D8 mapped:0x806F24DC
void fn_3_B3448(void) {
    InputStruct* in = &g_Controls[g_Practice.homeAway];
    s32 row = 0;

    if (g_Practice.practiceLevel == 3) {
        row = 1;
    }
    if (in->newButtonInput & 0x100) {
        if (g_Practice.currentMessageDoneTyping == 0) {
            return;
        }
        switch (lbl_3_data_FAE8[row].vals[(s8)lbl_3_common_bss_34C90.field_0x1DA]) {
        case 0:
            lbl_3_common_bss_34C90.field_0x1D2 = 10;
            break;
        case 1:
            lbl_3_common_bss_34C90.field_0x1D2 = 4;
            break;
        case 2:
            lbl_3_common_bss_34C90.field_0x1D2 = 6;
            break;
        case 3:
            fn_3_5B408();
            lbl_3_common_bss_34C90.field_0x1D2 = 12;
            break;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
    } else if (in->_08 & 4) {
        lbl_3_common_bss_34C90.field_0x1DA++;
        if ((s8)lbl_3_common_bss_34C90.field_0x1DA >= lbl_3_data_FAE8[row].count) {
            lbl_3_common_bss_34C90.field_0x1DA = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    } else if (in->_08 & 8) {
        lbl_3_common_bss_34C90.field_0x1DA--;
        if ((s8)lbl_3_common_bss_34C90.field_0x1DA < 0) {
            lbl_3_common_bss_34C90.field_0x1DA = lbl_3_data_FAE8[row].count - 1;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    }
}

// .text:0x000B3620 size:0x408 mapped:0x806F26B4
void fn_3_B3620(void) {
    return;
}

// .text:0x000B3A28 size:0x24 mapped:0x806F2ABC
void fn_3_B3A28(void) {
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90.field_0x1D2 = 0;
    lbl_3_common_bss_34C90.field_0x1DA = 0;
}
