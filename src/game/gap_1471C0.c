#include "game/gap_1471C0.h"
#include <string.h>

// .text:0x001471C0 size:0x4 mapped:0x80786254
void fn_3_1471C0(void) {
    return;
}

// .text:0x001471C4 size:0x194 mapped:0x80786258
typedef struct RangeS16_21EAC {
    s16 min;
    s16 max;
} RangeS16_21EAC;
extern RangeS16_21EAC lbl_3_data_21EAC[];

void fn_3_146408(void);
void fn_3_146A90(void);
void fn_3_10F550(u8 arg0, s16 arg1);
int RandomInt_Game_Range(int min, int max);

static inline void setRandomTarget_1471C4(MinigameRandomTarget* target, s32 strength) {
    target->active = 1;
    target->value = RandomInt_Game_Range(lbl_3_data_21EAC[(u8)strength].min, lbl_3_data_21EAC[(u8)strength].max);
}

static inline void initRandomTargets_1471C4(void) {
    MinigameRandomTarget* target = g_Minigame.randomTargets;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    i = 0;
    do {
        setRandomTarget_1471C4(target, g_Minigame.players.aIStrength[i]);
        target++;
    } while (++i < 4);
}

void fn_3_1471C4(void) {
    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_146A90();
        break;
    case 26:
        switch (g_GameLogic._125) {
        case 0:
            fn_3_10F550(2, lbl_3_data_21278.unk0);
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 1;
            break;
        case 1:
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278.unk0 + lbl_3_data_21278.unk1) {
                g_GameLogic._125 = 2;
            }
            break;
        case 2:
            fn_3_5A6D4(0);
            break;
        }
        break;
    case 1:
    case 3:
        break;
    case 0:
        initRandomTargets_1471C4();
        changeScene(1, 6);
        fn_3_5A6D4(2);
        break;
    case 2:
        fn_3_146408();
        break;
    }
}

// .text:0x00147358 size:0x24 mapped:0x807863EC
void fn_3_147358(void) {
    pitchingMachinePitching(0x26);
}

