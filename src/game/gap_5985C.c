#include "game/gap_5985C.h"
#include "game/rep_1188.h"
#include "game/rep_1038.h"
#include "game/gap_6D4A0.h"
#include "game/m_sound.h"
#include "game/gap_DEB90.h"
#include "game/gap_157DB8.h"
#include "game/gap_6B4C8.h"
#include "game/gap_1658F0.h"

typedef struct {
    u8 highLevelSimulationFlag;
    u8 _1;
    u8 _2;
} HighLevelSimulation_5985C;
extern HighLevelSimulation_5985C lbl_803CBC3C;
#include "game/rep_1C0.h"
#include "game/rep_868.h"
#include "game/rep_540.h"
#include "game/game_batter.h"

// .text:0x0005985C size:0x74 mapped:0x806988F0
void fn_3_5985C(s32 idx, s32 arg1) {
    s32 offset = idx * 0x268;
    s32 temp_r6;
    u8* temp_r7 = (u8*)g_Fielders + offset;

    if (idx == -1) {
        return;
    }
    ((Fielder*)temp_r7)->unk1D3 = arg1;
    temp_r6 = *(s32*)((u8*)&lbl_3_data_3C40 + (arg1 * 8));
    if (temp_r6 >= 0) {
        g_FieldingLogic.unk_F8[idx] = (u8)temp_r6;
    }
    ((Fielder*)temp_r7)->unk1D5 = 0;
    ((Fielder*)temp_r7)->unk1D6 = 0;
    ((Fielder*)temp_r7)->unk1A4 = 0;
    ((Fielder*)temp_r7)->unk1AC = 0;
    ((Fielder*)temp_r7)->unk1FF = 0;
    if (arg1 == 0x18) {
        g_FieldingLogic.unkBC = idx;
    }
}

// .text:0x000598D0 size:0x48 mapped:0x80698964
void fn_3_598D0(void) {
    fn_3_58688();
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fn_3_583B8();
        return;
    }
    fn_3_3B9E4();
}

// .text:0x00059918 size:0x178 mapped:0x806989AC
void fn_3_59918(s32 arg0, s32 arg1) {
    return;
}

// .text:0x00059A90 size:0x30 mapped:0x80698B24
void fn_3_59A90(void) {
    g_UnkSound_32718._02 = 0;
    g_UnkSound_32718._03 = 0;
    g_UnkSound_32718._04 = 0;
    g_UnkSound_32718._05 = 0;
    g_UnkSound_32718._06 = 0;
    g_UnkSound_32718._00 = 0;
    g_UnkSound_32718._07 = 0;
    g_UnkSound_32718._08 = 0;
}

// .text:0x00059AC0 size:0x24 mapped:0x80698B54
void fn_3_59AC0(s32 arg0, s32 arg1, s32 arg2) {
    fn_80017D28(arg2);
}

// .text:0x00059AE4 size:0x3C mapped:0x80698B78
s32 fn_3_59AE4(void) {
    if (g_d_GameSettings.GameModeSelected == 6) {
        return fn_80022B68();
    }
    return 1;
}

// .text:0x00059B20 size:0xAC mapped:0x80698BB4
void fn_3_59B20(void) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 4; i++) {
            AnimationStruct* anim = &g_hugeAnimStruct.fielderStructs[i];
            fn_80022CB4(&lbl_800F1D78[anim->unk252 * 19 + 1], anim->field3_0xc, 0, 0, fn_3_59AC0, anim);
        }
    }
}

// .text:0x00059BCC size:0x60 mapped:0x80698C60
s32 fn_3_59BCC(s32 arg0) {
    DrawingSceneStruct *r31 = lbl_803CC1B8;
    if (arg0 < 1) {
        return 0;
    }
    if (arg0 == 1) {
        fn_8001AAA4();
    }
    if (r31->loadingState != 0) {
        fn_3_6AEC0();
        return 1;
    }
    return 0;
}

// .text:0x00059C2C size:0x314 mapped:0x80698CC0
void fn_3_59C2C(void) {
    return;
}

// .text:0x00059F40 size:0x34C mapped:0x80698FD4
void fn_3_59F40(void) {
    return;
}

// .text:0x0005A28C size:0x3F8 mapped:0x80699320
void fn_3_5A28C(void) {
    return;
}

// .text:0x0005A684 size:0x1C mapped:0x80699718
void fn_3_5A684(void) {
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
    g_Strikes.unk_10 = 0;
}

// .text:0x0005A6A0 size:0x34 mapped:0x80699734
void fn_3_5A6A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp = arg1 ^ arg0;
    g_GameLogic.homeTeamBattingInd_fieldingTeam = arg0;
    g_GameLogic.awayTeamBattingInd_battingTeam = arg0 ^ 1;
    g_GameLogic.homeTeamInd = arg1;
    g_GameLogic.teamBatting = temp;
    g_GameLogic.teamFielding = temp ^ 1;
    g_GameLogic._1C = arg2;
    g_GameLogic._20 = arg3;
}

// .text:0x0005A6D4 size:0x28 mapped:0x80699768
void fn_3_5A6D4(u8 arg0) {
    GameControlsStruct* gl = &g_GameLogic;
    gl->FrameCountOfCurrentPitch = 0;
    gl->gameStatus_prev = gl->gameStatus;
    gl->gameStatus = arg0;
    gl->FrameCountOfCurrentAtBat_Copy = 0;
    gl->_125 = 0;
}

// .text:0x0005A6FC size:0x180 mapped:0x80699790
void fn_3_5A6FC(void) {
    return;
}

// .text:0x0005A87C size:0x424 mapped:0x80699910
void fn_3_5A87C(void) {
    return;
}

// .text:0x0005ACA0 size:0x16C mapped:0x80699D34
void fn_3_5ACA0(void) {
    return;
}

// .text:0x0005AE0C size:0x90 mapped:0x80699EA0
void fn_3_5AE0C(void) {
    fn_3_6D4A0();
    g_UnkSimulation_31AC0.unk8 = 0;
    g_UnkSimulation_31AC0.unk7 = 0;
    fn_3_5A87C();
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_3_DFA20();
    } else if (g_d_GameSettings.GameModeSelected == 7) {
        fn_3_10FBE4();
    }
    g_Minigame._19AB = 0;
    fn_3_6C150();
    fn_3_8F1C8();
    lbl_803CC1B8->unk_00 = fn_3_5B0C4;
}

// .text:0x0005AE9C size:0x228 mapped:0x80699F30
void fn_3_5AE9C(void) {
    return;
}

// .text:0x0005B0C4 size:0x15C mapped:0x8069A158
void fn_3_5B0C4(void) {
    return;
}

// .text:0x0005B220 size:0x148 mapped:0x8069A2B4
void fn_3_5B220(void) {
    return;
}

// .text:0x0005B368 size:0x18 mapped:0x8069A3FC
void fn_3_5B368(void) {
    g_GameLogic.frames_memoryCardWriteOnMVP = 0;
    g_GameLogic.endGameStage = 0;
}

extern s32 fn_8004CA6C(s32 arg0);
extern void fn_8004CC2C(void);

// .text:0x0005B380 size:0x88 mapped:0x8069A414
s32 fn_3_5B380(s32 arg0) {
    s32 result;

    if (g_GameLogic.frame_exitMenuShowing < 0x7FFE) {
        g_GameLogic.frame_exitMenuShowing++;
    } else {
        g_GameLogic.frame_exitMenuShowing = 0x7FFF;
    }
    if (g_GameLogic.frame_exitMenuShowing > 20) {
        result = fn_8004CA6C(arg0);
        if (result == 1) {
            return 1;
        } else if (result == 2) {
            fn_8004CC2C();
        } else if (result == 4) {
            return 2;
        }
    }
    return 0;
}

// .text:0x0005B408 size:0x14 mapped:0x8069A49C
void fn_3_5B408(void) {
    g_GameLogic.frame_exitMenuShowing = 0;
}

// .text:0x0005B41C size:0x184 mapped:0x8069A4B0
void fn_3_5B41C(void) {
    return;
}

// .text:0x0005B5A0 size:0x48C mapped:0x8069A634
void fn_3_5B5A0(void) {
    return;
}

// .text:0x0005BA2C size:0x314 mapped:0x8069AAC0
void fn_3_5BA2C(void) {
    return;
}

// .text:0x0005BD40 size:0x6D8 mapped:0x8069ADD4
void fn_3_5BD40(void) {
    return;
}

// .text:0x0005C418 size:0x118 mapped:0x8069B4AC
void fn_3_5C418(void) {
    return;
}

// .text:0x0005C530 size:0x98 mapped:0x8069B5C4
u8 fn_3_5C530(s32 inning) {
    if (inning > g_Scores.threshold) {
        return 5;
    }
    if (g_Scores.threshold <= 3) {
        if (g_Scores.threshold == inning && g_Scores.unkAD != 0) {
            return 4;
        }
        return 0;
    }
    if (inning == g_Scores.threshold) {
        return 4;
    }
    if ((g_Scores.threshold == 9 && inning >= 7) || (g_Scores.threshold == 7 && inning >= 6)) {
        return 3;
    }
    if (inning >= 4) {
        return 2;
    }
    return 1;
}

// .text:0x0005C5C8 size:0xD4 mapped:0x8069B65C
void fn_3_5C5C8(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY ||
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DEAD_BALL) {
            g_Scores.field_0x9C++;
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DURING_PLAY;
        }
    }
}

// .text:0x0005C69C size:0xB0 mapped:0x8069B730
void fn_3_5C69C(s32 arg0) {
    g_Ball.framesSinceHit = 100;
    g_Ball.framesSincePickOff = 0;
    g_FieldingLogic._107 = arg0 + 1;
    g_FieldingLogic.unk106 = 3;
    fn_3_5A6D4(2);
    g_FieldingLogic.unkAE = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    fn_3_32090();
    fn_3_8911C();
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 5;
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = 4;
    }
}

// .text:0x0005C74C size:0x5D8 mapped:0x8069B7E0
void fn_3_5C74C(s32 arg0) {
    return;
}

// .text:0x0005CD24 size:0x90 mapped:0x8069BDB8
void fn_3_5CD24(void) {
    if (g_GameLogic._125 == 0) {
        lbl_3_common_bss_32724.unk9A = 0;
        fn_3_8A1D8();
        fn_3_6C108();
        fn_3_6B870();
        g_GameLogic._125++;
    } else if (g_GameLogic._125 == 1) {
        if (fn_3_6BA64() != 0) {
            lbl_803CBC3C._2 = 0;
            fn_3_5A6D4(0);
        }
    }
}

// .text:0x0005CDB4 size:0x21C mapped:0x8069BE48
void fn_3_5CDB4(void) {
    return;
}

// .text:0x0005CFD0 size:0xC4 mapped:0x8069C064
void fn_3_5CFD0(void) {
    s16 val;
    ChallengeSaveData* tracker = &starMissionCompletionTracker;
    s32 captain = tracker->challengeCaptain;
    s32 opponent = tracker->opponentCaptain;

    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        val = g_Scores.unkA4;
        if (val <= 1) {
            if (val ^ (g_GameLogic.homeTeamInd == lbl_3_common_bss_37400.playerIndex)) {
                if ((tracker->unk4422 >= 4 && opponent == 5) ||
                    (tracker->unk4422 >= 5 && (s32)tracker->unk44EF == 1 && captain == 5)) {
                    g_GameLogic.playOverFadeOutStarted = 0;
                }
                starMissionRelated2();
            }
        }
    }
}

// .text:0x0005D094 size:0x368 mapped:0x8069C128
void fn_3_5D094(s32 arg0) {
    return;
}

// .text:0x0005D3FC size:0x120 mapped:0x8069C490
void fn_3_5D3FC(void) {
    return;
}

// .text:0x0005D51C size:0xCC mapped:0x8069C5B0
void fn_3_5D51C(void) {
    return;
}

// .text:0x0005D5E8 size:0x410 mapped:0x8069C67C
void fn_3_5D5E8(void) {
    return;
}

// .text:0x0005D9F8 size:0xA4 mapped:0x8069CA8C
void fn_3_5D9F8(void) {
    if (g_Stats.unk36 == 0) {
        g_Pitcher._15C = 0;
        if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.unkAD == 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            fn_3_5A6D4(9);
        } else {
            fn_3_5A6D4(3);
        }
    }
}

// .text:0x0005DA9C size:0x244 mapped:0x8069CB30
void fn_3_5DA9C(void) {
    return;
}

// .text:0x0005DCE0 size:0x50 mapped:0x8069CD74
s32 fn_3_5DCE0(void) {
    s32 result = 0;
    if (g_Pitcher.strikeOutOrWalk == 1) {
        fn_3_736CC();
        return 1;
    }
    if (g_Pitcher.strikeOutOrWalk == 2) {
        fn_3_735A8();
        result = 1;
    }
    return result;
}

// .text:0x0005DD30 size:0x224 mapped:0x8069CDC4
void fn_3_5DD30(void) {
    return;
}

// .text:0x0005DF54 size:0x370 mapped:0x8069CFE8
void fn_3_5DF54(void) {
    return;
}

// .text:0x0005E2C4 size:0xAD4 mapped:0x8069D358
void fn_3_5E2C4(void) {
    return;
}

// .text:0x0005ED98 size:0x40 mapped:0x8069DE2C
void fn_3_5ED98(void) {
    fn_3_5A6D4(2);
    g_FieldingLogic.unkAE = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
}

// .text:0x0005EDD8 size:0x80 mapped:0x8069DE6C
void fn_3_5EDD8(void) {
    ballPhysica();
    fn_3_598D0();
    fn_3_8A958();

    if (g_Ball.deadBallReason != 0) {
        fn_3_5DD30();
    }

    fn_3_5C74C(0);
    fn_3_5E2C4();

    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        fn_3_79ACC();

        if (g_Strikes.outs >= 3) {
            fn_3_5D094(0);
        }
    }
}

// .text:0x0005EE58 size:0x194 mapped:0x8069DEEC
void fn_3_5EE58(void) {
    return;
}

// .text:0x0005EFEC size:0x168 mapped:0x8069E080
void fn_3_5EFEC(void) {
    return;
}

// .text:0x0005F154 size:0x2A8 mapped:0x8069E1E8
void fn_3_5F154(void) {
    return;
}

// .text:0x0005F3FC size:0x324 mapped:0x8069E490
void fn_3_5F3FC(void) {
    return;
}

// .text:0x0005F720 size:0x88 mapped:0x8069E7B4
void fn_3_5F720(void) {
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    fn_3_1DEB8();
    Set_803cb848(1);
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_FieldingLogic.unkAE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    g_UnkSimulation_31AC0.unk5 = 0;
    g_UnkSimulation_31AC0.unk6 = 4;
}

// .text:0x0005F7A8 size:0x188 mapped:0x8069E83C
void fn_3_5F7A8(void) {
    return;
}

// .text:0x0005F930 size:0x558 mapped:0x8069E9C4
void fn_3_5F930(void) {
    return;
}

// .text:0x0005FE88 size:0x88 mapped:0x8069EF1C
void fn_3_5FE88(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
        g_GameLogic._125 = 1;
        break;
    case 1:
        fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
        g_GameLogic._125 = 2;
        break;
    default:
        fn_3_5A6D4(5);
        break;
    }
}

// .text:0x0005FF10 size:0x20C mapped:0x8069EFA4
void fn_3_5FF10(void) {
    return;
}

// .text:0x0006011C size:0x64C mapped:0x8069F1B0
void fn_3_6011C(void) {
    return;
}
