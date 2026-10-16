/* fn_3_8A618 NONMATCHING: control flow/structure matches with per-iteration runner ptr; only register
 * coloring in the unrolled runner loop differs (target ptr=r5,_107=r4,tmp=r3,0=r6,1=r0; ours r6/r5/r4/r0/r3).
 * Tried pointer loop, index loop, inline helper (ptr/index). Needs RunningLogicStruct.unk14 (headers diff). */
void fn_3_8A618(void) {
    s32 i;

    if (g_GameLogic.gameStatus == 2 && g_GameLogic.FrameCountOfCurrentPitch < g_RunningLogic.unk14 &&
        g_GameLogic.secondaryGameMode != 0xE && g_FieldingLogic._107 == 0) {
        return;
    }
    if (g_FieldingLogic.unk10E != 0) {
        return;
    }
    if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
        fn_3_7E2BC();
    } else {
        fn_3_83714();
    }
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored != 0) {
            if (g_FieldingLogic._107 == 1 && r->stealingStatus != 0 && r->rosterID >= 0) {
                r->runningDirectionDesired = 1;
            }
            r->stealingStatus = 0;
        }
    }
}
