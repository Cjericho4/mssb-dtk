// Five register-only differences in previous-runner selection; header needs BOOL(s32*, s32*).
// .text:0x000A8478 size:0x150 mapped:0x806E750C
// Select the forced runner or tagging runner and estimate frames to the threatened base.
BOOL fn_3_A8478(s32* runnerIndex, s32* frames) {
    s32 target = g_FieldingLogic.unkC4;
    InMemRunnerType* runner;
    if (target >= 4 || (s16)target < 0) {
        return FALSE;
    }
    if (g_Ball.AtBat_ContactResult == 3 &&
        (runner = &g_Runners[target])->runnerOnFieldOrOutOrScored == 1 && runner->tagUpInd == 2) {
        *runnerIndex = target;
    } else {
        s32 previous = 3;
        if (target != 0) {
            previous = target - 1;
        }
        runner = &g_Runners[previous];
        if (runner->runnerOnFieldOrOutOrScored == 1 && runner->forceOutCd == 1) {
            *runnerIndex = previous;
            goto forced;
        }
        return FALSE;
    }
    if (runner->currentBase == target) {
        u8 direction = runner->runningDirectionCode;
        if (direction == 3 || direction == 2) {
            *frames = runner->framesToPreviousBase;
        } else if ((direction == 1 && runner->nextDirectionBeingProcessed == 3) ||
                   (direction == 3 && runner->nextDirectionBeingProcessed == 1)) {
            *frames = runner->framesToPreviousBase + 20;
        } else {
            *frames = runner->framesToPreviousBase + 50;
        }
    } else {
        s32 next = runner->framesToNextBase;
        s32 prev = runner->framesToPreviousBase;
        next = prev + next;
        *frames = prev + next;
    }
    return TRUE;
forced:
    *frames = runner->framesToNextBase;
    return TRUE;
}

