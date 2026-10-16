/* fn_3_88C24 NONMATCHING (11 lines): register allocation only. Loop counter i gets r9 and the
 * hoisted g_FieldingLogic._108 gets r3 (target: i=r3, _108=r7, landing=r8, ballZone=r9).
 * Tried s32/int/u32 counter, inline helper (ptr or index param), do-while, pointer loops.
 * Note the !(x==0||x==1) form is needed to keep clrlwi in the loop. */
void fn_3_88C24(void) {
    s32 i;

    fn_3_87AE8();
    if (g_GameLogic.secondaryGameMode == 6) {
        fn_3_87CC8();
    } else {
        fn_3_88408();
        fn_3_88B18();
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
                if ((g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) && g_Ball.landingSpotZoneAwayFromHome <= 1) {
                    g_Runners[i].isEligibleToScore = 0;
                } else if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0 && !(g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == 1) &&
                           g_Runners[i].currentBase != 0 && g_Runners[i].currentBase < 3) {
                    g_Runners[i].isEligibleToScore = 0;
                }
            }
        }
        fn_3_87E80();
    }
    fn_3_8781C();
}
