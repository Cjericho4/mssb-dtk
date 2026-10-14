#include "game/gap_6C854.h"

// .text:0x0006C854 size:0xE4
void fn_3_6C854(int arg0, int arg1) {
    if (lbl_80366158._00[0x1F] == 0) return;
    if (g_Stats.unk36 != 0) return;

    if (g_d_GameSettings.minigamesEnabled != 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] == arg0) {
                if (g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.minigameControlStruct[0].characterIndex[i]] != 0) {
                    return;
                }
                goto do_call;
            }
        }
    } else {
        arg0 = (s32)g_GameLogic.teams[arg0];
    }
do_call:
    fn_800A97EC(arg0, lbl_3_data_60E4[arg1].a, lbl_3_data_60E4[arg1].b);
}

static inline BOOL isButtonPressed(s32 port, s32 type, s32 mask) {
    s32 i;

    if (g_d_GameSettings.minigamesEnabled != 0) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0
                && g_Minigame.minigameControlStruct[0].characterIndex[i] == port) {
                goto check;
            }
        }
        return FALSE;
    } else {
        if (g_d_GameSettings._10 == 0 && port == 1) {
            return FALSE;
        }
        if (g_d_GameSettings._10 == 3 && port == 0) {
            return FALSE;
        }
    }
check:
    if (type == 0) {
        if (mask & g_Controls[port].buttonInput) {
            return TRUE;
        }
    } else if (type == 1) {
        if (mask & g_Controls[port].newButtonInput) {
            return TRUE;
        }
    } else {
        if (mask & g_Controls[port]._08) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x0006C938 size:0x2F8
s32 fn_3_6C938(s32 arg0, s32 arg1) {
    s32 i;

    if (g_d_GameSettings.GameModeSelected == 4) {
        return 0;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        for (i = 0; i < 4; i++) {
            if (isButtonPressed(i, arg0, arg1)) {
                return i + 1;
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (isButtonPressed(g_GameLogic.teams[i], arg0, arg1)) {
                return i + 1;
            }
        }
    }
    return 0;
}

// .text:0x0006CC30 size:0x158
BOOL fn_3_6CC30(s32 port, s32 type, s32 mask) {
    return isButtonPressed(port, type, mask);
}
