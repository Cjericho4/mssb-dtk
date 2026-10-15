#include "game/gap_6F4E8.h"
#include "game/gap_9CD90.h"

extern void fn_3_5C69C(s32 arg0);

// .text:0x0006F4E8 size:0x1E4
BOOL fn_3_6F4E8(void) {
    BOOL found = FALSE;
    int i;
    InMemRunnerType* runner;

    if (g_Strikes.outs >= 3) {
        return FALSE;
    }
    if (g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1) {
        return FALSE;
    }
    if (g_Pitcher.strikeOutOrWalk == 2) {
        if (g_RunningLogic.unk12 == 4) {
            return FALSE;
        }
        for (i = 1; i < 4; i++) {
            if ((g_Runners[i].runnerOnFieldOrOutOrScored == 1 || g_Runners[i].runnerOnFieldOrOutOrScored == 3) &&
                g_Runners[i].furthestBaseForcedToGoToOnWalk == 1) {
                found = TRUE;
            }
        }
        if (!found) {
            return FALSE;
        }
    }
    runner = &g_Runners[1];
    for (i = 1; i < 4; i++) {
        if (runner->runnerOnFieldOrOutOrScored == 1 && runner->furthestBaseForcedToGoToOnWalk != 0) {
            g_Pitcher.pickOffLoc = 5;
            fn_3_5C69C(1);
            if (g_Pitcher.strikeOutOrWalk == 1) {
                g_Strikes.outs++;
                for (i = 0; i < 3; i++) {
                    if (g_Strikes.unk_18[i] == -1) {
                        g_Strikes.unk_18[i] = 0;
                        break;
                    }
                }
            }
            return TRUE;
        }
        runner++;
    }
    return FALSE;
}
