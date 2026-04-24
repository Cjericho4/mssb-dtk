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

// .text:0x0006C938 size:0x2F8
s32 fn_3_6C938(s32 arg0, s32 arg1) {
    return 0;
}

// .text:0x0006CC30 size:0x158
void fn_3_6CC30(void) {
    return;
}
