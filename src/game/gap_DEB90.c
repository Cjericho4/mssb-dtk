#include "game/gap_DEB90.h"

#include "UnknownHeaders.h"
#include "game/gap_1658F0.h"
#include "game/rep_1838.h"
#include "game/gap_E1964.h"
#include "game/gap_5985C.h"
extern s32 fn_3_90DD8(void);
#include "game/rep_3090.h"
extern void fn_3_FBD58(void);
extern void fn_3_FBD70(void);
#include "static/UnknownHomes_Static.h"

extern void fn_8001D0D0();
extern f32 lbl_3_data_18D98[];
extern void fn_3_10C81C(void);
extern s16 lbl_3_data_18C48[];
void fn_3_754B8(void);
void initializeInMemBatter(void);
void fn_3_FBA8(void);
void fn_3_595C4(void);
void fn_3_1E328(void);
void possiblyTransitionBlackScreen(void);
void fn_3_5BAC(void);
extern u8 lbl_3_data_21270[];
extern u8 lbl_3_data_18980[];
extern u8 lbl_3_data_18944[];
extern u8 lbl_3_data_189A4[];
extern int fn_3_E8AC8(void);
extern s32 fn_800203E0(s32, s32);
extern s32 fn_80016F7C(void);
extern s32 fn_3_6C938(s32, s32);
extern void changeScene(s32, s32);


typedef struct {
    u8 highLevelSimulationFlag;
    u8 _1;
    u8 _2;
} HighLevelSimulation;
extern HighLevelSimulation lbl_803CBC3C;

#include "game/rep_E08.h"
#include "game/rep_2940.h"
extern void fn_3_F578(void);
extern void fn_3_753E8(s32 param_1);
extern void setBatterContactConstants(void);
extern void fn_3_58E50(void);
extern void fn_3_2E87C(void);
extern void fn_3_1E154(void);
extern int someAnimationIndFunction(void);
extern void fn_3_DE744(void);
extern int fn_3_9EE24(int max);

typedef struct GapDEB90Entry2D94 {
    u8 _pad0[0x14];
    f32 field_0x14;
} GapDEB90Entry2D94;

typedef struct {
    u8 _pad[2];
    s16 unk2;
} Data18BB0Entry;
extern Data18BB0Entry lbl_3_data_18BB0[];
extern f32 lbl_3_data_18DD0;

typedef struct {
    void* unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 _pad18[0xC];
    u8 _pad24[2];
    u8 unk26;
    u8 _pad27;
} GapDEB90E0668Entry;

// .text:0x000DEB90 size:0x47C mapped:0x8071DC24
void fn_3_DEB90(void) {
    return;
}

// .text:0x000DF00C size:0x250 mapped:0x8071E0A0
void fn_3_DF00C(void) {
    MiniGameStruct* mg;

    switch (g_GameLogic._125) {
    case 0:
        if (g_Minigame._19A6 == 1) {
            if ((u8)fn_3_E8AC8() == 0) {
                return;
            }
            g_Minigame._19A6 = 0;
        }
        if (g_Minigame._19A2 != 0) {
            g_Minigame._19A2--;
        }
        g_Minigame.minigameFielderIndex[0] = -1;
        g_Minigame.minigameFielderIndex[1] = -1;
        g_Minigame.minigameFielderIndex[2] = -1;
        g_Minigame.minigameFielderIndex[3] = -1;
        fn_3_DEB90();
        fn_3_F578();
        fn_3_753E8(0);
        setBatterContactConstants();
        fn_3_58E50();
        fn_3_2E87C();
        fn_3_1E154();
        fn_3_E1370(0);
        lbl_3_common_bss_32234.unk1 = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        lbl_803CBC3C._2 = 0;
        g_GameLogic._125++;
        break;
    case 1:
        if (g_Minigame._19C7 != 0) {
            if (someAnimationIndFunction() == 0) {
                return;
            }
            lbl_3_common_bss_32234.unk1 = 1;
            g_GameLogic._125++;
        } else {
            g_GameLogic._125++;
        }
        break;
    default:
        fn_3_DE744();
        if (++g_Minigame._190F == 1) {
            g_Minigame._1911 = 1;
        }
        mg = &g_Minigame;
        if (mg->toyField_turnNumber < 0x7FFE) {
            mg->toyField_turnNumber++;
        } else {
            mg->toyField_turnNumber = 0x7FFF;
        }
        if (mg->toyField_turnNumber < g_Minigame.toyField_selectedTurns) {
            if (mg->toyField_turnNumber % 10 == 1) {
                g_Minigame.toyField_next_CoinsX2_TurnNumber = fn_3_9EE24(6) + 4 + mg->toyField_turnNumber;
            }
        }
        if (g_Minigame.toyField_next_CoinsX2_TurnNumber == mg->toyField_turnNumber) {
            g_Minigame.toyField_pointMultiplier = 2;
        } else {
            g_Minigame.toyField_pointMultiplier = 1;
        }
        break;
    }
}

// .text:0x000DF25C size:0x17C mapped:0x8071E2F0
void fn_3_DF25C(void) {
    s32 i;
    s32 j;
    s32 remaining;
    s32 pick;
    s32 slot;

    g_Scores.highscore++;
    g_Scores.unkAC = fn_3_5C530(g_Scores.highscore);
    g_Strikes.outs = 0;
    g_Strikes.unk_C = 0;
    lbl_3_common_bss_32724.unk_D5 = 1;
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame._190D = 3;
    g_Minigame.panelHitInd = 0;
    g_Minigame._19A5 = 1;
    g_Minigame._190F = 0;
    g_Minigame._1910 = 3;
    g_Minigame._1911 = 0;
    g_Minigame._1914[0] = 0;
    g_Minigame._1914[1] = 0;
    g_Minigame._1914[2] = 0;
    g_Minigame._1914[3] = 0;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        g_Minigame.players.playerOrder[i] = i;
    }
    remaining = g_Minigame.miniGameNumberOfParticipants;
    slot = 0;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        pick = fn_3_9EE24(remaining);
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.players.playerOrder[j] >= 0) {
                if (pick == 0) {
                    g_Minigame.players.battingOrder[slot] = j;
                    remaining--;
                    slot++;
                    g_Minigame.players.playerOrder[j] = -1;
                    break;
                }
                pick--;
            }
        }
    }
    changeScene(1, 6);
    fn_3_5A6D4(3);
}

// .text:0x000DF3D8 size:0x230 mapped:0x8071E46C
void fn_3_DF3D8(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_E8AC8();
        fn_800203E0(7, 0);
        g_Minigame.toyField_selectedTurns = (s16)lbl_3_data_189A4[g_Minigame._1A24[0]];
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            g_Minigame.toyField_selectedTurns = (s16)lbl_3_data_189A4[5];
        }
        g_hugeAnimStruct.renderStadiumFlag = 1;
        g_hugeAnimStruct.field209_0x2d8e = 0;
        g_hugeAnimStruct.field269_0x307a = 3;
        if (g_Minigame._190A != 0) {
            g_GameLogic._125 = 1;
            return;
        }
        fn_3_59B20();
        g_GameLogic._125 = 2;
        break;
    case 1:
        fn_3_10C81C();
        if (g_Minigame._1A0F[0] >= 0) {
            return;
        }
        fn_3_59B20();
        g_GameLogic._125 = 2;
        break;
    case 2:
        if (fn_3_59AE4() == 0) return;
        g_GameLogic._125 = 3;
        if (fn_80016F7C() == 0) return;
        if (g_Minigame._1A38 != 0) {
            g_GameLogic._125 = 6;
        } else {
            g_GameLogic._125 = 4;
        }
        lbl_3_common_bss_34C58._2C = 0;
        break;
    case 3:
        if (fn_3_90DD8() == 0) return;
        g_GameLogic._125 = 6;
        break;
    case 4:
        if (lbl_8037169C._12 == 0) return;
        if (g_GameLogic.FrameCountOfCurrentPitch < 0xF0) {
            if ((s32)fn_3_FD9FC() == 0) return;
        }
        if (fn_3_6C938(1, 0x1300) == 0) return;
        g_GameLogic._125 = 7;
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C._13 == 0) return;
        fn_3_FBD70();
        fn_3_FBD58();
        g_GameLogic._125 = 8;
        break;
    case 7:
    case 8:
        fn_3_E1964();
        g_Minigame._1A38 = 0;
        g_Minigame._19A2 = 0;
        g_hugeAnimStruct.field269_0x307a = 1;
        fn_3_5A6D4(6);
        break;
    }
}

// .text:0x000DF608 size:0xCC mapped:0x8071E69C
void fn_3_DF608(void) {
    MiniGameStruct* mg;
    u8* p;
    u8 idx;
    idx = g_d_GameSettings._35;
    g_Minigame._19DA[idx] = 0;
    mg = &g_Minigame;
    p = lbl_3_data_18980;
    if (idx != 0) {
        mg->minigameControlStruct[0].aIStrength[0] = *p;
        p++;
    }
    if (idx != 1) {
        mg->minigameControlStruct[0].aIStrength[1] = *p;
        p++;
    }
    if (idx != 2) {
        mg->minigameControlStruct[0].aIStrength[2] = *p;
        p++;
    }
    if (idx != 3) {
        mg->minigameControlStruct[0].aIStrength[3] = *p;
    }
    mg->_1907 = 1;
    mg->multiPlayerInd = 1;
    mg->miniGameNumberOfParticipants = lbl_3_data_18944[mg->GameMode_MiniGame] + 1;
    g_Scores.threshold = 1;
}

// .text:0x000DF6D4 size:0x14C mapped:0x8071E768
void fn_3_DF6D4(void) {
    s32 player;
    u8* strength;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        player = g_d_GameSettings._35;
        g_Minigame._19DA[player] = 0;
        strength = lbl_3_data_18980;
        for (i = 0; i < 4; i++) {
            if (player != i) {
                g_Minigame.players.aIStrength[i] = *strength++;
            }
        }
        g_Minigame._1907 = 1;
        g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
        g_Minigame.multiPlayerInd = 1;
        g_Scores.threshold = 1;
        g_GameLogic._125++;
        break;
    }
    g_Minigame._190A = 1;
    g_Minigame._19DA[g_d_GameSettings._35] = g_d_GameSettings._35;
    lbl_3_common_bss_37400.playerIndex = g_d_GameSettings._35;
    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame._19DF = 0x1E;
    fn_3_5A6D4(0x1B);
}

// .text:0x000DF820 size:0xB4 mapped:0x8071E8B4
void fn_3_DF820(void) {
    s32 count;
    s32 i;
    fn_3_10C81C();
    count = 0;
    for (i = 0; i < 4; i++) {
        if ((s8)g_Minigame.teamEntries[i].fieldA != (s8)g_Minigame.teamEntries[i].fieldB) break;
        count++;
    }
    if (count >= 4) {
        fn_3_5A6D4(0x1d);
    }
}

// .text:0x000DF8D4 size:0x14C mapped:0x8071E968
void fn_3_DF8D4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] = lbl_3_data_18C48[0];
        g_Minigame.players._18E8[i] = 0;
        g_Minigame.players.fielderRosterIDs[i] = -1;
        g_Minigame.minigameFielderIndex[i] = -1;
        g_Minigame._18FC[i] = -1;
        g_Minigame.players.battingOrder[i] = -1;
        g_Minigame.players.playerOrder[i] = i;
        g_Minigame.playerResult[i][0] = 0xFF;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame._1914[i] = 0;
    }
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame._1939 = 0;
    g_Minigame._190D = 3;
    g_Minigame._19A6 = 0;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = 1;
    g_Minigame._19A9 = 0;
    g_Minigame._1911 = 0;
    g_Minigame.toyField_pointMultiplier = 1;
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
    g_Minigame._19CD = 0;
    g_Minigame._19CE = 0;
    g_Minigame._19CF = 0;
    g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[g_Minigame._1A24[0]];
    g_Minigame.toyField_turnNumber = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[5];
    }
    fn_3_754B8();
    initializeInMemBatter();
    fn_3_FBA8();
    fn_3_595C4();
    fn_3_1E328();
}

// .text:0x000DFA20 size:0x18C mapped:0x8071EAB4
void fn_3_DFA20(void) {
    s32 i;

    g_GameLogic.secondaryGameMode = 1;
    fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
    fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
    g_d_GameSettings._33 = 0;
    g_Minigame.GameMode_MiniGame = 0;
    g_Minigame._19DF = 0x1E;
    g_Minigame._1A2C = -1;
    g_Minigame._1A0C = -1;
    g_Minigame._19E6 = 2;
    g_Minigame._19E7 = 1;
    g_Minigame._1A3C = 0;
    g_Minigame._19A7 = lbl_3_data_21270[0];
    g_Minigame._1A38 = 0;
    g_Minigame._1A39 = 0;
    g_Minigame.battingHandedness[5] = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame._19DA[i] = -1;
        g_Minigame.teamEntries[i].fieldA = -1;
        g_Minigame.teamEntries[i].fieldB = -1;
        g_Minigame.teamEntries[i]._3 = -1;
        g_Minigame._1A0F[i] = -1;
        g_Minigame._19D2[i] = 20;
        g_Minigame._1A13[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame.players.characterIndex[i] = -1;
        g_Minigame.players.battingHandedness[i] = 0;
    }
    g_Minigame.miniGameNumberOfParticipants = 0;
    lbl_3_common_bss_34C58._30 = 0;
    fn_3_DF8D4();
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        g_Minigame._190A = 1;
        fn_3_5A6D4(0x25);
    } else {
        fn_3_5A6D4(0x1B);
    }
}

// .text:0x000DFBAC size:0xABC mapped:0x8071EC40
void fn_3_DFBAC(void) {
    return;
}

// .text:0x000E0668 size:0xF0 mapped:0x8071F6FC
void fn_3_E0668(void) {
    GapDEB90E0668Entry* entry;
    s32 i;

    for (i = 0; i < 0x1E; i++) {
        entry = (GapDEB90E0668Entry*)&g_hugeAnimStruct.entries_2D94[i];
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 0) {
            entry->unk26 = 0;
        } else if (g_Minigame.wallBall_coinsVisibleFrameCounter[0] > lbl_3_data_18BB0[g_Minigame._199E].unk2
                   && (g_Minigame.wallBall_coinsVisibleFrameCounter[0] & 1)) {
            entry->unk26 = 0;
        } else {
            entry->unk26 = 1;
            entry->unk4 = g_Minigame.wallBall_coinCoordinates[i].x;
            entry->unk8 = -g_Minigame.wallBall_coinCoordinates[i].y;
            entry->unkC = g_Minigame.wallBall_coinCoordinates[i].z;
            entry->unk14 = fn_3_9FEA8(entry->unk14 + lbl_3_data_18DD0);
        }
    }
}

// .text:0x000E0758 size:0x84 mapped:0x8071F7EC
void fn_3_E0758(void) {
    s32 offset;
    GapDEB90Entry2D94* entry;
    s32 i;

    i = 0;
    offset = 0;
    do {
        entry = (GapDEB90Entry2D94*)((u8*)g_hugeAnimStruct.entries_2D94 + offset);
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        {
            u32 r = (u32)rand();
            u32 shifted = r << 20;
            r >>= 31;
            shifted -= r;
            shifted = (shifted << 12) | (shifted >> 20);
            shifted += r;
            entry->field_0x14 = shortAngleToRad_Capped((s16)shifted);
        }
        i++;
        offset += 0x28;
    } while (i < 0x1E);
}

// .text:0x000E07DC size:0xA04 mapped:0x8071F870
void fn_3_E07DC(void) {
    return;
}
