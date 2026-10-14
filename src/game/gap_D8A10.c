#include "game/gap_D8A10.h"

#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "game/gap_106DFC.h"

int fn_3_9EE24(int max);

typedef struct {
    u8 _pad[0x48];
    s16 unk48;
    s16 unk4A;
    s16 unk4C;
} Data18BB8;
extern Data18BB8 lbl_3_data_18BB8;
extern s16 lbl_3_data_18C48[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[][0x1E];
extern u8 lbl_3_data_84B8[][0x1E];

// .text:0x000D8A10 size:0x2C0
void fn_3_D8A10(void) {
    MiniGameStruct* mg;
    s32 i;
    s32 j;
    s32 id;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;
    s16* pts;

    mg = &g_Minigame;
    if (mg->_19CE == 1) {
        pts = mg->miniGameLatestPoints;
        pts[mg->rosterID] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk48;
        pts[(s8)mg->minigamePlayerSelectedOrder] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk4A;
        pts[(s8)mg->minigameControlStruct[1].aIStrength[3]] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk4C;
        pts[(s8)mg->minigameControlStruct[1]._14] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk4C;
        for (i = 0; i < 4; i++) {
            if (mg->miniGameLatestPoints[i] != 0) {
                mg->minigamePointsPair[i].current = mg->miniGameCurrentPoints[i];
                mg->minigamePointsPair[i].latest = mg->miniGameLatestPoints[i];
            }
        }
        g_Minigame._19BA = 0;
        mg->_19CE = 2;
        for (j = 0; j < 4; j++) {
            if (mg->_1918[j] != 0) {
                mg->_1914[j] = 0;
            }
        }
        if (lbl_800EF808.unk398 == 1) {
            id = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0][0x34];
            } else {
                vol = lbl_3_data_8404[id][0x34];
            }
            vid = sndFXStartEx(lbl_3_data_81DC[id] + 0x1A, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                pan = lbl_3_data_84B8[0][0x35];
            } else {
                pan = lbl_3_data_8404[id][0x35];
            }
            sndFXCtrl(vid, 0x5B, pan);
        }
    }
    if (g_Minigame._19BA < 0x7FFE) {
        g_Minigame._19BA++;
    } else {
        g_Minigame._19BA = 0x7FFF;
    }
    if (g_Minigame._19BA > lbl_3_data_18C48[3]) {
        mg->_19CE = 3;
    }
}

// .text:0x000D8CD0 size:0xB98
void fn_3_D8CD0(void) {
    return;
}

// .text:0x000D9868 size:0x1C8
void fn_3_D9868(void) {
    MinigameStanding standings[4];
    u32 i;
    u32 j;
    u32 active;
    u32 count;
    u8 pick;

    fn_3_1079C8(standings, 0);
    active = 0;
    i = 0;
    do {
        if (standings[i].eliminated == 0) {
            active++;
        }
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    switch (g_Minigame.fieldingOrderMode) {
    case 0:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        j = 1;
        i = 0;
        do {
            if (i != g_Minigame.rosterID) {
                g_Minigame.fieldOrder[j++] = i;
            }
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 3:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        do {
            pick = fn_3_9EE24(g_Minigame.miniGameNumberOfParticipants);
            g_Minigame.fieldOrder[1] = pick;
        } while ((s8)pick == (s8)g_Minigame.fieldOrder[0]);
        break;
    case 1:
    case 2:
    case 4:
    case 5:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        if (active == 1 && standings[0].id == g_Minigame.rosterID) {
            count = 0;
            i = 0;
            do {
                if (standings[i].eliminated == 1) {
                    count++;
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            g_Minigame.fieldOrder[1] = standings[fn_3_9EE24(count) + 1].id;
        } else {
            do {
                pick = standings[fn_3_9EE24(active)].id;
                g_Minigame.fieldOrder[1] = pick;
            } while ((s8)pick == (s8)g_Minigame.fieldOrder[0]);
        }
        break;
    }
}

// .text:0x000D9A30 size:0x470
void fn_3_D9A30(void) {
    return;
}
