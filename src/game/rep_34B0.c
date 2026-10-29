#include "game/rep_34B0.h"
#include "game/m_sound.h"
#include "game/rep_E08.h"
// game_batter.h currently pulls in a conflicting lbl_80366158 struct view.
extern void setBatterContactConstants(void);
extern int someAnimationIndFunction(void);

#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/gap_106DFC.h"
#include "game/gap_5985C.h"
#include "game/UnknownHomes_Game.h"
#include "stl/mem.h"
#include "game/rep_1188.h"
#include "game/rep_540.h"
#include "game/rep_1200.h"
#include "game/rep_13B8.h"
#include "game/rep_AC8.h"
#include "game/gap_FBCD0.h"

// Partial view of the simulation flags; older units have local partial views.
typedef struct SimulationFlags {
    u8 unk_0x0;
    u8 unk_0x1;
    u8 unk_0x2;
} SimulationFlags;
extern SimulationFlags lbl_803CBC3C;
extern u8 lbl_3_data_21798[];

extern void fn_3_BF158(void);
extern void fn_3_BF1AC(void);
extern void setDefaultInMemBatter(void);

// .text:0x0012E8FC size:0x214 mapped:0x8076D990
void fn_3_12E8FC(void) {
    return;
}

// .text:0x0012EB10 size:0x270 mapped:0x8076DBA4
void fn_3_12EB10(void) {
    return;
}

// .text:0x0012ED80 size:0xE8 mapped:0x8076DE14
BOOL fn_3_12ED80(void) {
    s32 i;

    for (i = 1; i < 15; i += 3) {
        if (g_Minigame.barrels[i].replacingBarrelInd != 0) {
            return FALSE;
        }
        if (g_Minigame.barrels[i + 1].replacingBarrelInd != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

// .text:0x0012EE68 size:0x13C mapped:0x8076DEFC
void fn_3_12EE68(void) {
    return;
}

// .text:0x0012EFA4 size:0x2E8 mapped:0x8076E038
void fn_3_12EFA4(void) {
    return;
}

// .text:0x0012F28C size:0x198 mapped:0x8076E320
void fn_3_12F28C(void) {
    return;
}

// .text:0x0012F424 size:0x200 mapped:0x8076E4B8
void fn_3_12F424(s32 idx, s16 delay, s32 force) {
    s32 n;
    s32 colour;

    colour = g_Minigame.barrels[idx].barrelColour;
    if (idx % 3 != 2) {
        n = idx + 1;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (idx % 3) {
        n = idx - 1;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (idx / 3 > 0) {
        n = idx - 3;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
    if (idx / 3 < 4) {
        n = idx + 3;
        if (g_Minigame.barrels[n].barrelState == 2 && n != g_Minigame.bB_bombBarrelID &&
            (g_Minigame.barrels[n].barrelColour == colour || force != 0)) {
            g_Minigame.barrels[n].barrelState = 3;
            g_Minigame.barrels[n].animationCounter = 0;
            g_Minigame.barrels[n].delayUntilBlownUp = delay;
        }
    }
}

// .text:0x0012F624 size:0x3B0 mapped:0x8076E6B8
void fn_3_12F624(void) {
    return;
}

extern f32 lbl_3_data_21770[6];
void fn_8004C108(VecXYZ* pos, s32 arg1);

// .text:0x0012F9D4 size:0xF0 mapped:0x8076EA68
void fn_3_12F9D4(s32 idx) {
    BB_barrelStruct* b = &g_Minigame.barrels[idx];
    VecXYZ pos;
    f32 desiredY;

    g_Minigame.barrels[idx].currentPos.y += lbl_3_data_21770[1];
    if (g_Minigame.barrels[idx].currentPos.y < (desiredY = g_Minigame.barrels[idx].desiredPos.y)) {
        b->currentPos.y = desiredY;
        if (b->posAtStartOfTurn.y != b->desiredPos.y) {
            pos.x = b->currentPos.x;
            pos.y = b->currentPos.y;
            pos.z = b->currentPos.z;
            pos.y = -pos.y;
            pos.z -= 1.0f;
            if (b->currentPos.y <= 0.0f) {
                fn_8004C108(&pos, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(&pos, 0);
                fn_3_90064(0x2E5);
            }
        }
        b->barrelState = 2;
    }
}

// .text:0x0012FAC4 size:0x2A8 mapped:0x8076EB58
void fn_3_12FAC4(void) {
    return;
}

// .text:0x0012FD6C size:0x118 mapped:0x8076EE00
void fn_3_12FD6C(void) {
    s32 i;

    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState != 0) {
            g_Minigame.barrels[i].posAtStartOfTurn.x = g_Minigame.barrels[i].currentPos.x;
            g_Minigame.barrels[i].posAtStartOfTurn.y = g_Minigame.barrels[i].currentPos.y;
            g_Minigame.barrels[i].posAtStartOfTurn.z = g_Minigame.barrels[i].currentPos.z;
            g_Minigame.barrels[i].barrelState = 1;
        }
        g_Minigame.barrels[i].animationCounter = 0;
    }
}

extern Vec lbl_3_data_216BC[15];

// .text:0x0012FE84 size:0x150 mapped:0x8076EF18
// Reset Barrel Batter barrels with randomized fall heights and colors.
void fn_3_12FE84(void) {
    s32 i;
    for (i = 0; i < 15; i++) {
        g_Minigame.barrels[i].barrelState = 1;
        g_Minigame.barrels[i].animationCounter = 0;
        g_Minigame.barrels[i].replacingBarrelInd = 0;
        g_Minigame.barrels[i].desiredPos.x = lbl_3_data_216BC[i].x;
        g_Minigame.barrels[i].desiredPos.y = lbl_3_data_216BC[i].y;
        g_Minigame.barrels[i].desiredPos.z = lbl_3_data_216BC[i].z;
        g_Minigame.barrels[i].currentPos.x = lbl_3_data_216BC[i].x;
        g_Minigame.barrels[i].currentPos.y = lbl_3_data_216BC[i].y;
        g_Minigame.barrels[i].currentPos.z = lbl_3_data_216BC[i].z;
        g_Minigame.barrels[i].currentPos.y += lbl_3_data_21770[0];
        g_Minigame.barrels[i].currentPos.y += (i % 3) * 10 - fn_3_9EE24(101) * 5 / 100.0;
        g_Minigame.barrels[i].barrelColour = fn_3_9EE24(3);
    }
}

// .text:0x0012FFD4 size:0x2B4 mapped:0x8076F068
void fn_3_12FFD4(void) {
    return;
}

// .text:0x00130288 size:0x548 mapped:0x8076F31C
void fn_3_130288(void) {
    return;
}

// .text:0x001307D0 size:0x2B0 mapped:0x8076F864
void fn_3_1307D0(void) {
    return;
}

// .text:0x00130A80 size:0x4C mapped:0x8076FB14



void fn_3_130A80(void) {
    g_Minigame.bB_bombBarrelID = -1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_5A6D4(8);
}

// .text:0x00130ACC size:0x1A0 mapped:0x8076FB60
void fn_3_130ACC(void) {
    return;
}

// .text:0x00130C6C size:0x4A8 mapped:0x8076FD00
void fn_3_130C6C(void) {
    return;
}

// .text:0x00131114 size:0x88 mapped:0x807701A8
void fn_3_131114(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(g_Minigame._1D7C, 0, 0x78);
    fn_3_BF1AC();
    fn_3_BF158();
    g_FieldingLogic.unkAE = 0;
    g_UnkSimulation_31AC0.unk5 = 0;
    g_UnkSimulation_31AC0.unk6 = 4;
}

extern s16 lbl_3_data_18C48[];
extern s32 fn_3_6C938(s32, s32);

// .text:0x0013119C size:0xF0 mapped:0x80770230
void fn_3_13119C(void) {
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
        if (lbl_8037169C._13 != 0) {
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

// .text:0x0013128C size:0x48 mapped:0x80770320



void fn_3_13128C(void) {
    if ((s32) g_Scores.highscore >= (s32) g_Scores.threshold) {
        fn_3_5A6D4(0xF);
        return;
    }
    fn_3_5A6D4(6);
}

// .text:0x001312D4 size:0x26C mapped:0x80770368
void fn_3_1312D4(void) {
    return;
}

// .text:0x00131540 size:0x748 mapped:0x807705D4
void fn_3_131540(void) {
    return;
}

// .text:0x00131C88 size:0x23C mapped:0x80770D1C
void fn_3_131C88(void) {
    return;
}

// Initialize the Barrel Batter turn and wait for the batter animation to finish.
// .text:0x00131EC4 size:0x138 mapped:0x80770F58
void fn_3_131EC4(void) {
    GameControlsStruct* logic = &g_GameLogic;
    MiniGameStruct* minigame;
    switch (logic->_125) {
    case 0:
        minigame = &g_Minigame;
        minigame->rosterID = minigame->players.battingOrder[minigame->turnNumberWithinRound];
        logic->pre_PostMiniGameInd = 1;
        minigame->miniGameTurnCounter = 0;
        minigame->pointsTargetReachedInd = 0;
        if (minigame->multiPlayerInd == 0) {
            minigame->bB_pitchesRemainingInTurn = lbl_3_data_21798[minigame->soloMinigameDifficulty];
        } else {
            minigame->bB_pitchesRemainingInTurn = lbl_3_data_21798[4];
        }
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(minigame->rosterID);
        lbl_803CBC3C.unk_0x2 = 0;
        logic->_125++;
        break;
    case 1:
        if (someAnimationIndFunction()) {
            lbl_3_common_bss_32234.unk1 = 1;
            logic->_125++;
        }
        break;
    default:
        lbl_3_common_bss_32724.unk_B6 = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00131FFC size:0x80 mapped:0x80771090
void fn_3_131FFC(void) {
    g_Scores.highscore++;
    g_Minigame.turnNumberWithinRound = 0;
    if (g_Minigame.multiPlayerInd == 0) {
        fn_3_5A6D4(7);
    } else {
        fn_3_10F550(4, 0);
        if (g_Scores.highscore == 1) {
            fn_3_10AD48();
        }
        fn_3_5A6D4(7);
    }
}

// .text:0x0013207C size:0x40 mapped:0x80771110


void fn_3_13207C(void) {
    // Register setup for sndFXStartEx:
    // r3 = 0x1BD, r5 = 0x3F, r6 = 0
    // r4 is prepared with the address of lbl_800EFBA4, then lbz r4, 6(r4)
    sndFXStartEx(0x1BD, lbl_800EFBA4.volume, 0x3F, 0);

    // After the first call returns, r3 is loaded with 6
    fn_3_5A6D4(6);
}

// .text:0x001320BC size:0x310 mapped:0x80771150
void fn_3_1320BC(void) {
    return;
}

// .text:0x001323CC size:0x11C mapped:0x80771460
static inline void barrelSettle(s32 idx) {
    BB_barrelStruct* b = &g_Minigame.barrels[idx];
    VecXYZ pos;
    f32 desiredY;

    b->currentPos.y += lbl_3_data_21770[1];
    if (b->currentPos.y < (desiredY = b->desiredPos.y)) {
        b->currentPos.y = desiredY;
        if (b->posAtStartOfTurn.y != b->desiredPos.y) {
            pos.x = b->currentPos.x;
            pos.y = b->currentPos.y;
            pos.z = b->currentPos.z;
            pos.y = -pos.y;
            pos.z -= 1.0f;
            if (b->currentPos.y <= 0.0f) {
                fn_8004C108(&pos, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(&pos, 0);
                fn_3_90064(0x2E5);
            }
        }
        b->barrelState = 2;
    }
}

void fn_3_1323CC(void) {
    u32 i;

    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == 1) {
            barrelSettle(i);
        }
    }
}

// .text:0x001324E8 size:0x9F4 mapped:0x8077157C
void fn_3_1324E8(void) {
    return;
}
