/*
 * fn_3_79414 (src/game/rep_12D0.c) NONMATCHING - register swap only (11 lines).
 * Target keeps the runner pointer (&g_Runners[1]) in r5 and the cached
 * runnerOnFieldOrOutOrScored byte in r6; this build swaps them (r6/r5).
 * Everything else (unrolled forceOutCd count loop with CSE'd &g_Runners[1],
 * ctr main loop, early returns) matches.
 * Tried: decl-order brute force (incl. extra ball/q pointer locals), init
 * order, count-loop forms (index, pointer, manual unroll), main-loop forms
 * (for/while/countdown, per-iteration pointer, status local).
 * Needs: #include "game/gap_9CD90.h" in rep_12D0.c (g_RunningLogic) and the
 * FieldingLogic.unkE8 carve in fn_3_79414.headers.diff.
 */
void fn_3_79414(void) {
    s32 i;
    InMemRunnerType* r;
    s32 notForced;
    s32 forced;

    if (g_Ball.maybebuntOn2Strikes != 0) {
        lbl_3_common_bss_32A94.unk24 = 0xE;
        return;
    }
    if (g_Strikes.unk_C >= 2) {
        return;
    }
    if (g_RunningLogic.unk12 <= 1) {
        return;
    }
    if (lbl_3_common_bss_32A94.unk24 == 0 &&
        (g_Ball.ballState == 1 || g_Ball.ballState == 2 || g_FieldingLogic.unkCC >= 0 || g_FieldingLogic.unkE8 >= 0)) {
        lbl_3_common_bss_32A94.unk24 = 0xC;
    }
    if (lbl_3_common_bss_32A94.unk24 != 0xC && lbl_3_common_bss_32A94.unk24 != 0xF) {
        return;
    }
    notForced = 0;
    forced = 0;
    r = &g_Runners[1];
    for (i = 0; i < 3; i++) {
        if (r[i].forceOutCd != 0) {
            forced++;
        }
    }
    for (i = 0; i < 3; i++, r++) {
        if (r->currentBase > r->startingBase_baseAchieved || r->runnerOnFieldOrOutOrScored == 3) {
            if (r->currentBase == 4 && r->startingBase_baseAchieved == 3 && r->runnerOnFieldOrOutOrScored == 2) {
                lbl_3_common_bss_32A94.unk24 = 0xD;
                break;
            }
            if (r->forceOutCd == 0) {
                notForced++;
            }
        } else if (r->runnerOnFieldOrOutOrScored == 2) {
            lbl_3_common_bss_32A94.unk24 = 0xD;
            break;
        }
    }
    if (notForced != 0 && forced == 0) {
        lbl_3_common_bss_32A94.unk24 = 0xB;
    }
}
