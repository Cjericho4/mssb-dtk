#include "game/rep_31F0.h"
#include "UnknownHeaders.h"
#include "game/gap_106DFC.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_E08.h"
#include "header_rep_data.h"
#include "stl/mem.h"
#include "game/rep_1188.h"
#include "game/rep_540.h"
#include "game/rep_1200.h"
#include "game/rep_AC8.h"
#include "game/rep_1E08.h"
void setDefaultInMemBatter(void);
#include "game/rep_13B8.h"
#include "game/gap_FBCD0.h"
void setBatterContactConstants(void);
int someAnimationIndFunction(void);
void fn_3_8F21C(void);

extern f32 shortAngleToRad(s16 ang);
extern f32 lbl_3_rodata_3268;
extern s16 lbl_3_data_18C48[];
s32 fn_3_6C938(s32 arg0, s32 arg1);
extern void fn_8003A540(s32 arg0, GameControlsStruct* arg1);

// .text:0x00110634 size:0x3D0 mapped:0x8074F6C8
void fn_3_110634(void) {
    return;
}

// .text:0x00110A04 size:0x34 mapped:0x8074FA98

void fn_3_110A04(void) {
    /* * lis r3, g_Minigame@ha
     * li r4, 0
     * addi r3, r3, g_Minigame@l
     * li r5, 0x78
     * addi r3, r3, 0x1d7c   <-- This offset corresponds to _1D7C
     * bl memset
     */
    memset(g_Minigame._1D7C, 0, 0x78);
}

// .text:0x00110A38 size:0x9C mapped:0x8074FACC
s32 fn_3_110A38(void) {
    if (g_Pitcher.starPitchInd != 0) {
        switch (g_Pitcher.starPitchType) {
        case 1:
            return 20;
        default:
            return 20;
        }
    }
    return 35.0f + -0.18867925f * ((f32)g_Minigame.minigamePitchSpeedAdjustment - 138.0f);
}

// .text:0x00110AD4 size:0x564 mapped:0x8074FB68
void fn_3_110AD4(void) {
    return;
}

// .text:0x00111038 size:0x198 mapped:0x807500CC
void fn_3_111038(void) {
    return;
}

static inline void fn_3_1111D0_inline(void) {
    InMemRunnerType* runners = g_Runners;
    s32 angle;

    if (lbl_3_common_bss_32220.field_0x08 == 4) {
        angle = g_Ball.Hit_HorizontalAngle;
        
        if (angle < 0x200) {
            angle = 0x200;
        }
        
        if (angle > 0x600) {
            angle = 0x600;
        }
        
        runners[0].runningAngle = -shortAngleToRad(angle) - lbl_3_rodata_3268;
    }
}

// .text:0x001111D0 size:0x80 mapped:0x80750264
void fn_3_1111D0(void) {
    InMemRunnerType* runners = g_Runners;
    s32 angle;

    if (lbl_3_common_bss_32220.field_0x08 == 4) {
        angle = g_Ball.Hit_HorizontalAngle;
        
        if (angle < 0x200) {
            angle = 0x200;
        }
        
        if (angle > 0x600) {
            angle = 0x600;
        }
        
        runners[0].runningAngle = -shortAngleToRad(angle) - lbl_3_rodata_3268;
    }
}

// .text:0x00111250 size:0x64 mapped:0x807502E4
void fn_3_111250(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_8003A540(0, &g_GameLogic);
    if ((u8)g_Minigame.pointsTargetReachedInd == 1) {
        fn_3_5A6D4(8);
        return;
    }
    fn_3_5A6D4(0);
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void fn_3_1112B4(void) {
    return;
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
extern struct {
    f32 _00;
    f32 _04;
    f32 _08;
    f32 _0C;
} lbl_3_data_21438;

void fn_3_111738(void) {
    s32 i;

    ballPhysica();
    fn_3_1111D0_inline();
    if (g_Ball.bODQualifyingHitInd != 0 && g_Ball.deadBallReason == 1 &&
        (g_Ball.ballDistanceFromHome > lbl_3_data_21438._0C || g_Minigame.bODRelated3 != 0)) {
        fn_3_110AD4();
        g_Minigame.bOD_hitFinishedInd = 1;
    }
    for (i = 0; i < 10; i++) {
        if (g_Minigame.bODRelated5[i] != 0) {
            g_Minigame.bODRelated5[i]--;
            if (g_Minigame.bODRelated5[i] == 0) {
                fn_3_6C854(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
            }
        }
    }
    if (g_Ball.deadBallReason == 2) {
        g_Minigame.bOD_hitFinishedInd = 1;
    }
    fn_3_8F21C();
    fn_3_1112B4();
}

// .text:0x001118B4 size:0x1D4 mapped:0x80750948
void fn_3_1118B4(void) {
    return;
}

// .text:0x00111A88 size:0x3C mapped:0x80750B1C


void fn_3_111A88(void) {
    // Note: We access fields directly through the global to force the 
    // lis/addi g_GameLogic sequence seen in the assembly.
    
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;

    // The compiler will put 0x8 in r3 and the address of g_GameLogic in r4
    fn_3_5A6D4(8);
}

extern s16 lbl_3_data_21448;
void fn_3_155288(void);
enum { MINIGAME_END_SUCCESS_SOUND = 0x1BE };

// .text:0x00111AC4 size:0x198 mapped:0x80750B58
// Count down the Bob-omb Derby turn ending and play its success cue before fading.
void fn_3_111AC4(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
            if (g_Minigame.miniGameTurnCounter >= g_Minigame.bODRoundStartingNumPitches) {
                g_Minigame.turnOverStatus = 1;
                g_Minigame.pointsTargetReachedInd = 1;
            }
            g_Minigame.bODCharacterHRStreakTracker[(s8)g_Minigame.rosterID * 2] = 0;
            fn_3_155288();
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_21448;
        }
        g_GameLogic.CountdownUntilFade--;
        if (g_Minigame.pointsTargetReachedInd != 0 &&
            (g_Minigame.multiPlayerInd == 0 ||
             (g_Minigame.multiPlayerInd != 0 && g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
              g_Scores.highscore >= g_Scores.threshold)) &&
            g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 67) {
            sndFXStartEx(MINIGAME_END_SUCCESS_SOUND, lbl_800EFBA4.unk7, 0x3F, 0);
        }
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(SCENE_ID_REPLAY_AT_BAT, 6);
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudLoadingRelated = 1;
            fn_3_5A6D4(GAME_STATUS_TRANSITION);
        }
    }
}

// .text:0x00111C5C size:0x324 mapped:0x80750CF0
void fn_3_111C5C(void) {
    return;
}

// .text:0x00111F80 size:0xF0 mapped:0x80751014
void fn_3_111F80(void) {
    switch (g_GameLogic._125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100))) {
            changeScene(3, 6);
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (lbl_8037169C._13) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// .text:0x00112070 size:0x70 mapped:0x80751104
void fn_3_112070(void) {
    extern void fn_3_DE4FC(void);

    fn_3_DE4FC();
    fn_3_5A6D4(0xE);
    g_Minigame._18A6 = rand() % 30 + 0xF;
    fn_3_155288();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
}

// .text:0x001120E0 size:0x48 mapped:0x80751174

void fn_3_1120E0(void) {
    // stwu r1, -0x10(r1) : Prologue
    // lis r3, g_Scores@ha / addi r4, r3, g_Scores@l : Load struct base into r4
    
    // The comparison: if (highscore < threshold) jump to .L_00112110 (the '6' case)
    // This is logically: if (highscore >= threshold) call 0xF else call 0x6
    if (g_Scores.highscore >= g_Scores.threshold) {
        fn_3_5A6D4(0xF);
    } else {
        fn_3_5A6D4(0x6);
    }
    
}

/// .text:0x00112128 size:0x7C mapped:0x807511BC
void fn_3_112128(void) {
    g_Minigame.turnNumberWithinRound++;
    if (g_Minigame.multiPlayerInd == 0) {
        fn_3_5A6D4(0xF);
    } else if (g_Minigame.turnNumberWithinRound >= g_Minigame.miniGameNumberOfParticipants) {
        fn_3_5A6D4(0x19);
    } else {
        fn_3_5A6D4(0x7);
    }
    lbl_3_common_bss_32724.unk_B7 = 1;
}

// .text:0x001121A4 size:0x8C mapped:0x80751238
void fn_3_1121A4(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(g_Minigame._1D7C, 0, 0x78);
    fn_3_BF1AC();
    Set_803cb848(1);
    g_FieldingLogic.unkAE = 0;
    g_UnkSimulation_31AC0.unk5 = 0;
    g_UnkSimulation_31AC0.unk6 = 4;
}

// .text:0x00112230 size:0x220 mapped:0x807512C4
void fn_3_112230(void) {
    return;
}

typedef struct {
    u8 highLevelSimulationFlag;
    u8 _1;
    u8 _2;
} HighLevelSimulation_31F0;
extern HighLevelSimulation_31F0 lbl_803CBC3C;

// .text:0x00112450 size:0x108 mapped:0x807514E4
void fn_3_112450(void) {
    switch (g_GameLogic._125) {
    case 0:
        g_Minigame.rosterID = g_Minigame.players.battingOrder[g_Minigame.turnNumberWithinRound];
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_Minigame.miniGameTurnCounter = 0;
        g_Minigame.pointsTargetReachedInd = 0;
        g_Minigame.bOD_HRStreak = 0;
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(g_Minigame.rosterID);
        lbl_803CBC3C._2 = 0;
        g_GameLogic._125++;
        break;
    case 1:
        if (someAnimationIndFunction() != 0) {
            lbl_3_common_bss_32234.unk1 = 1;
            g_GameLogic._125++;
        }
        break;
    default:
        lbl_3_common_bss_32724.unk_B6 = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00112558 size:0x78 mapped:0x807515EC
void fn_3_112558(void) {
    s32 score;

    score = g_Scores.highscore + 1;
    g_Minigame.turnNumberWithinRound = 0;
    g_Scores.highscore = score;

    if ((u8)g_Minigame.multiPlayerInd == 0) {
        fn_3_5A6D4(7);
        return;
    }

    if (score == 1) {
        fn_3_10AD48();
    }

    fn_3_5A6D4(7);
    fn_3_10F550(4, 0);
}

// .text:0x001125D0 size:0x40 mapped:0x80751664

void fn_3_1125D0(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4.volume, 0x3F, 0);
    fn_3_5A6D4(6);
}

// .text:0x00112610 size:0x2D8 mapped:0x807516A4
void fn_3_112610(void) {
    return;
}

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void fn_3_1128E8(void) {
    return;
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
void fn_3_1128EC(void) {
    return;
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
void fn_3_112BD8(void) {
    return;
}
