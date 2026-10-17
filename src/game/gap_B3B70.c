#include "game/gap_B3B70.h"
#include "game/rep_E08.h"
#include "game/rep_1038.h"
#include "game/gap_9CD90.h"
#include "game/gap_AC9F8.h"
#include "game/gap_6AEC0.h"
#include "game/m_sound.h"
#include "musyx/musyx.h"
#include "game/rep_AC8.h"
#include "game/rep_1188.h"
#include "game/rep_13B8.h"
#include "game/gap_6D4A0.h"
#include <string.h>
#include "game/rep_1C0.h"

// .text:0x000B3B70 size:0x60 mapped:0x806F2C04
void fn_3_B3B70(void) {
    g_GameLogic.freeFieldingPracticeInd = 0;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = 0;
    g_hugeAnimStruct.renderStadiumFlag = 1;
    g_hugeAnimStruct.field269_0x307a = 1;
    fn_3_6AEC0();
    fn_3_8F1C8();
    fn_3_59338();
}

// .text:0x000B3BD0 size:0x94 mapped:0x806F2C64
void fn_3_B3BD0(void) {
    s32 i;
    InMemRunnerType* runner;

    for (i = 0; i < 4; i++) {
        runner = &g_Runners[i];
        if (g_Practice.runnerActive[i] != 0) {
            if (g_GameLogic.secondaryGameMode == 0xE) {
                fn_3_6D964(i - 1, i);
            }
            runner->runnerOnFieldOrOutOrScored = 1;
        } else {
            runner->runnerOnFieldOrOutOrScored = 0;
            runner->rosterID = -1;
        }
    }
}

// .text:0x000B3C64 size:0x14 mapped:0x806F2CF8
void fn_3_B3C64(void) {
    g_GameLogic.framesOfExitingToMenu = 1;
}

// .text:0x000B3C78 size:0x1C mapped:0x806F2D0C
void fn_3_B3C78(u8 arg0) {
    g_Practice.practiceState = 0;
    g_Practice.tutorialState = arg0;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
}

// .text:0x000B3C94 size:0x18 mapped:0x806F2D28
void fn_3_B3C94(u8 arg0) {
    g_Practice.practiceState = arg0;
    g_Practice.framesInCurrTransitionState = 0;
}

// .text:0x000B3CAC size:0x28 mapped:0x806F2D40
void fn_3_B3CAC(u8 arg0) {
    g_GameLogic.secondaryGameMode = arg0;
    g_Practice.totalFrames = 0;
    g_Practice.framesInCurrTransitionState = 0;
    g_Practice.practiceState = 0;
}

// .text:0x000B3CD4 size:0x314 mapped:0x806F2D68
void fn_3_B3CD4(void) {
    return;
}

// .text:0x000B3FE8 size:0x13C mapped:0x806F307C
void fn_3_B3FE8(void) {
    fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
    fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
    g_hugeAnimStruct.renderStadiumFlag = 0;
    g_Practice.practiceType = 0;
    g_Practice.runnerActive[0] = 0;
    g_Practice.runnerActive[1] = 0;
    g_Practice.runnerActive[2] = 0;
    g_Practice.__0x1aapadding[2] = 0;
    g_Practice.__0x1aapadding[4] = 0;
    g_Practice.__0x1aapadding[5] = 0;
    g_Practice._19F = 0;
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.freePracticeInd_writeOnly = 0;
    g_Practice.__0x1aapadding[0] = 0;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = 0;
    g_Practice.loadingGuidedPractice = 0;
    g_Practice._1D5 = 0;
    {
        s32 i;
        s32 j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                g_Practice.practiceCompleted[i][j] = lbl_80354768.practiceCompleted[i][j];
            }
        }
    }
}

// .text:0x000B4124 size:0x184 mapped:0x806F31B8
void fn_3_B4124(s32 team, s32 slot, s32 charId, s32 hand) {
    if (team == 0 && slot == 0) {
        g_GameLogic.battingOrderAndPositionMapping[team][0][0] = slot;
    }
    g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0] = slot;
    g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][1] = slot;
    lbl_80354720[team][slot].unk0 = slot;
    lbl_80354720[team][slot].unk1 = slot;
    lbl_80354720[team][slot].unk2 = slot;
    if (slot >= 0 && slot <= 8) {
        fn_80011BE4(slot);
    }
    memcpy(&inMemRoster[team][slot], &lbl_8034E9A0[charId], sizeof(CharacterStats));
    if (hand >= 0) {
        if (hand == 0 || hand == 1) {
            inMemRoster[team][slot].stats.FieldingArm = 0;
        } else {
            inMemRoster[team][slot].stats.FieldingArm = 1;
        }
        if (hand == 0 || hand == 2) {
            inMemRoster[team][slot].stats.BattingStance = 0;
        } else {
            inMemRoster[team][slot].stats.BattingStance = 1;
        }
    }
}


// .text:0x000B42A8 size:0x140 mapped:0x806F333C
void fn_3_B42A8(void) {
    return;
}

// .text:0x000B43E8 size:0x444 mapped:0x806F347C
void fn_3_B43E8(void) {
    return;
}

// .text:0x000B482C size:0x1A8 mapped:0x806F38C0
void fn_3_15B610(void);
s32 fn_80014F40(s16 id);
s32 fn_80014D4C(s16 id);

void fn_3_B482C(void) {
    g_Practice.readyToMoveToNextInstruction = 0;
    if (g_Practice._19F != 0) {
        fn_3_B2E20();
        fn_3_8FC80();
        return;
    }
    if (g_Practice.framesInCurrTransitionState < 0xFFFE) {
        g_Practice.framesInCurrTransitionState++;
    } else {
        g_Practice.framesInCurrTransitionState = 0xFFFF;
    }
    if (g_Practice.framesSincePracticeMenuDefaultTransition < 0xFFFE) {
        g_Practice.framesSincePracticeMenuDefaultTransition++;
    } else {
        g_Practice.framesSincePracticeMenuDefaultTransition = 0xFFFF;
    }
    if (g_Practice.totalFrames < 0xFFFE) {
        g_Practice.totalFrames++;
    } else {
        g_Practice.totalFrames = 0xFFFF;
    }
    switch (g_GameLogic.secondaryGameMode) {
    case 18:
        fn_3_B43E8();
        break;
    case 10:
        fn_3_B5D78();
        break;
    case 11:
        fn_3_B6BA4();
        break;
    case 12:
        fn_3_B0AAC();
        break;
    case 13:
        fn_3_B1C14();
        break;
    case 14:
        fn_3_B77DC();
        break;
    case 15:
    case 16:
        fn_3_15B610();
        break;
    case 17:
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
    fn_3_8FC80();
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2) {
        if (lbl_3_common_bss_32724.unk9E >= 0 && fn_80014F40(lbl_3_common_bss_32724.unk9E)) {
            lbl_3_common_bss_32724.unk9E = -1;
        }
        if (lbl_3_common_bss_32724.unkA0 >= 0 && fn_80014D4C(lbl_3_common_bss_32724.unkA0)) {
            lbl_3_common_bss_32724.unkA0 = -1;
        }
    }
}

// .text:0x000B49D4 size:0x26C mapped:0x806F3A68
void fn_3_B49D4(void) {
    return;
}

// .text:0x000B4C40 size:0x450 mapped:0x806F3CD4
void fn_3_B4C40(void) {
    return;
}

// .text:0x000B5090 size:0x154 mapped:0x806F4124
typedef struct {
    u8 count;
    u8 levels[4];
} PracticeLevelTable; // size: 0x5
extern PracticeLevelTable lbl_3_data_FACC[];

void fn_3_B5090(void) {
    PracticeStruct* practice = &g_Practice;
    InputStruct* input = &g_Controls[practice->homeAway];
    s32 count = lbl_3_data_FACC[practice->practiceType_2].count;

    if (input->newButtonInput & INPUT_BUTTON_A) {
        practice->practiceLevel = lbl_3_data_FACC[practice->practiceType_2].levels[practice->subMenuCursor];
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        fn_3_B3C94(3);
    } else if (input->newButtonInput & INPUT_BUTTON_B) {
        fn_3_B3C94(5);
        sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
    } else if (input->_08 & 8) {
        if (practice->subMenuCursor != 0) {
            practice->subMenuCursor--;
        } else {
            practice->subMenuCursor = count - 1;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    } else if (input->_08 & 4) {
        if (++practice->subMenuCursor >= count) {
            practice->subMenuCursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    }
}

// .text:0x000B51E4 size:0x4B0 mapped:0x806F4278
void fn_3_B51E4(void) {
    return;
}

// .text:0x000B5694 size:0x184 mapped:0x806F4728
void fn_3_B5694(void) {
    return;
}

// .text:0x000B5818 size:0x49C mapped:0x806F48AC
void fn_3_B5818(void) {
    return;
}

// .text:0x000B5CB4 size:0x98 mapped:0x806F4D48
void fn_80062A94(void);

void fn_3_B5CB4(void) {
    switch (g_Practice.returnToPracticeMenuState) {
    case 1:
        fn_3_8B318(-1);
        g_Practice.returnToPracticeMenuState = 2;
        lbl_3_common_bss_34C58._2C = 0;
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 1;
    case 2:
        g_Practice.returnToPracticeMenuState = 3;
        break;
    default:
        fn_800B0A5C_insertQueue(fn_80062A94, 1);
        g_Practice.returnToPracticeMenuState = 0;
        break;
    }
}

// .text:0x000B5D4C size:0x2C mapped:0x806F4DE0
void fn_3_B5D4C(u8 arg0) {
    g_Practice.practiceType_1 = arg0;
    g_Practice.practiceState = 0;
    lbl_3_common_bss_34C90.field_0x1D2 = 0;
    g_Practice.practiceMenu_framesOnCurrMenuScreen = 0;
    g_Practice.framesInCurrTransitionState = 0;
}


// .text:0x000B5D78 size:0x104 mapped:0x806F4E0C
void fn_3_B5D78(void) {
    if (g_Practice.returnToPracticeMenuState != 0) {
        switch (g_Practice.returnToPracticeMenuState) {
        case 1:
            fn_3_8B318(-1);
            g_Practice.returnToPracticeMenuState = 2;
            lbl_3_common_bss_34C58._2C = 0;
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 1;
        case 2:
            g_Practice.returnToPracticeMenuState = 3;
            break;
        default:
            fn_800B0A5C_insertQueue(fn_80062A94, 1);
            g_Practice.returnToPracticeMenuState = 0;
            break;
        }
        return;
    }
    if (g_Practice.practiceMenu_framesOnCurrMenuScreen < 0xFFFE) {
        g_Practice.practiceMenu_framesOnCurrMenuScreen++;
    } else {
        g_Practice.practiceMenu_framesOnCurrMenuScreen = 0xFFFF;
    }
    switch (g_Practice.practiceType_1) {
    case 0:
        fn_3_B5818();
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        fn_3_B51E4();
        break;
    case 6:
        fn_3_B4C40();
        break;
    }
}

extern u8 lbl_3_data_FAF4[][4];

// .text:0x000B5E7C size:0x100 mapped:0x806F4F10
void fn_3_B5E7C(void) {
    if (g_Practice.practiceType_2 == 4) {
        return;
    }
    if (g_Pitcher.pitcherActionState != 4) {
        return;
    }
    switch (g_Practice.practiceLevel) {
    case 0:
        g_Practice.guidedPracticeCounter++;
        break;
    case 1:
        if (g_Pitcher.ChargePitchType >= 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 2:
        if (g_Pitcher.TypeOfPitch == 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 3:
        if (g_Pitcher.starPitchType != 0) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    }
    if (g_Practice.guidedPracticeCounter >= lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
        g_Practice.guidedPracticeCompletionRelated = 1;
    }
    g_Practice.guidedPracticeCompletionRelated2 = 1;
}

// .text:0x000B5F7C size:0x174 mapped:0x806F5010
void fn_3_B5F7C(void) {
    return;
}

// .text:0x000B60F0 size:0xD0 mapped:0x806F5184
void fn_3_B60F0(void) {
    fn_3_5F720();
    g_Strikes.unk_C = g_Strikes.outs;
    g_Strikes.unk_18[0] = -1;
    g_Strikes.unk_18[1] = -1;
    g_Strikes.unk_18[2] = -1;
    g_Strikes.unk_20 = g_Strikes.balls + g_Strikes.strikes * 16;
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
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
}

// .text:0x000B61C0 size:0x160 mapped:0x806F5254
void fn_3_B61C0(void) {
    return;
}

// .text:0x000B6320 size:0x120 mapped:0x806F53B4
BOOL fn_3_B6320(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return 0;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return 0;
    }
    if (g_Pitcher.miniGameRelated == 0) {
        return 0;
    }
    if (g_UnkSound_32718._07 != 0) {
        return 0;
    }
    if (++g_Practice._186 > 90) {
        if (g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.practiceCompletedChanged = 1;
            g_Practice.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            lbl_80354768.practiceCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
        }
        g_Practice._1C7 = 1;
        fn_3_B3A28();
        fn_3_B1DA4(g_Practice.practiceLevel, 1);
        return 1;
    }
    return 0;
}

// .text:0x000B6440 size:0x554 mapped:0x806F54D4
void fn_3_B6440(void) {
    return;
}

// .text:0x000B6994 size:0x1DC mapped:0x806F5A28
void fn_3_B6994(void) {
    return;
}

// .text:0x000B6B70 size:0x34 mapped:0x806F5C04
void fn_3_B6B70(void) {
    g_Practice._1DB = 0;
    fn_3_B3C78(0);
}

// .text:0x000B6BA4 size:0xAC mapped:0x806F5C38
void fn_3_B6BA4(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_B6994();
        break;
    case 1:
        fn_3_B6440();
        break;
    case 2:
        if (fn_3_B254C() == FALSE) {
            fn_3_B6440();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B6440();
        break;
    }
    g_GameLogic.TeamStars[0] = g_GameLogic.TeamStars[1] = 5;
}

// .text:0x000B6C50 size:0x4C mapped:0x806F5CE4
void fn_3_B6C50(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

// .text:0x000B6C9C size:0xE4 mapped:0x806F5D30
static inline void practicePlayEndUpdate(void) {
    PracticeStruct* practice;

    if (g_Practice.instructionNumber >= 0) {
        practice = &g_Practice;
        if (practice->allowPlayToEndIndicator == 0) {
            g_FieldingLogic.unkAE = 0;
            return;
        }
    } else {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == 3) {
            g_Practice.guidedPracticeCompletionRelated = 1;
        }
        return;
    }
    if (g_FieldingLogic.unkAE < 0x7FFE) {
        g_FieldingLogic.unkAE++;
    } else {
        g_FieldingLogic.unkAE = 0x7FFF;
    }
    if (g_FieldingLogic.unkAE >= 0x3C) {
        practice->allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
    } else if (g_FieldingLogic.unkAE == 0x36) {
        changeScene(3, 6);
    }
}

void fn_3_B6C9C(void) {
    practicePlayEndUpdate();
}

// .text:0x000B6D80 size:0x118 mapped:0x806F5E14
void fn_3_B6D80(void) {
    PracticeStruct* practice = &g_Practice;

    if (practice->instructionNumber < 0 && fn_3_B32B8() != 0) {
        return;
    }
    fn_3_8A958();
    practicePlayEndUpdate();
}

// .text:0x000B6E98 size:0xD4 mapped:0x806F5F2C
void fn_3_B6E98(void) {
    fn_3_5F720();
    g_Strikes.unk_C = g_Strikes.outs;
    g_Strikes.unk_18[0] = -1;
    g_Strikes.unk_18[1] = -1;
    g_Strikes.unk_18[2] = -1;
    g_Strikes.unk_20 = g_Strikes.balls + g_Strikes.strikes * 16;
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
    g_Practice._1EC = 0;
    g_Practice._1ED = 0;
    changeScene(1, 6);
    fn_3_5A6D4(2);
    fn_3_6C0E0();
}

// .text:0x000B6F6C size:0x110 mapped:0x806F6000
void fn_3_B6F6C(void) {
    fn_3_8A4E4();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_5F720();
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
    g_Practice._1EC = 0;
    g_Practice._1ED = 0;
    changeScene(1, 6);
    fn_3_5A6D4(2);
    fn_3_6C0E0();
    fn_3_6714C(0);
}

// .text:0x000B707C size:0x108 mapped:0x806F6110
s32 fn_3_B707C(void) {
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
        fn_3_B1DA4(g_Practice.practiceLevel + 0xC, 1);
        return 1;
    }
    return 0;
}

// .text:0x000B7184 size:0x49C mapped:0x806F6218
void fn_3_B7184(void) {
    return;
}

// .text:0x000B7620 size:0x15C mapped:0x806F66B4
void fn_3_B7620(void) {
    return;
}

// .text:0x000B777C size:0x18 mapped:0x806F6810
void fn_3_B777C(u8 arg0) {
    g_Practice._1E4[1] = arg0;
    g_Practice.maybeCommandData[2] = 0;
}

// .text:0x000B7794 size:0x48 mapped:0x806F6828
void fn_3_B7794(void) {
    g_Practice._1E4[4] = 1;
    g_Practice._1E4[5] = 1;
    g_Practice._1E4[6] = 0;
    g_Practice._1E4[7] = 0;
    g_Practice._1E4[3] = 0;
    fn_3_B3C78(0);
}

// .text:0x000B77DC size:0x1D0 mapped:0x806F6870
void fn_3_B77DC(void) {
    return;
}

