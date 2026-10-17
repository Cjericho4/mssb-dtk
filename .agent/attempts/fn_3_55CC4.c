void fn_3_55CC4(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    u8 currentBase;
    u8 nextBase;
    InMemRunnerType* runner;
    s16 runnerIdx;
    s16 trackedIdx;
    f32 progress;

    if (f->unk1E8 == 2 && g_Ball.fielderWBallIndex != fielderIdx) {
        f->unk1E8 = 0;
    }

    if (f->unk50 <= 0.0f) {
        f->unk19A = -1;
        f->unk1A0 = 0;
    } else {
        f->unk19A = radToShortAngle(f->unk64);
        if (f->unk1A0 < 0x7FFE) {
            f->unk1A0 = f->unk1A0 + 1;
        } else {
            f->unk1A0 = 0x7FFF;
        }
    }

    runnerIdx = g_FieldingLogic.unkDE;
    if (runnerIdx >= 0 && f->unk1C6 == 0 &&
        g_Runners[runnerIdx].runnerOnFieldOrOutOrScored != 1) {
        g_FieldingLogic.unkDE = -1;
    }

    if (g_Ball.ballState == 1 || g_Ball.ballState == 2) {
        if (g_FieldingLogic.unkDC >= 0 && g_FieldingLogic.unkCC == 9) {
            runnerIdx = g_FieldingLogic.unkDE;
            if (runnerIdx >= 0) {
                progress = g_Runners[runnerIdx].percentTowardsNextBase;
                if (progress >= 0.3f && progress <= 0.65f) {
                    g_FieldingLogic.unkF4 = runnerIdx;
                }
            }
        }

        trackedIdx = g_FieldingLogic.unkF4;
        if (trackedIdx >= 0) {
            runner = &g_Runners[trackedIdx];
            if (runner->runnerOnFieldOrOutOrScored != 1 ||
                runner->baseStandingOn >= 0) {
                g_FieldingLogic.unkF4 = -1;
                return;
            }

            currentBase = runner->currentBase;
            nextBase = runner->nextBase;
            if (g_FieldingLogic.unkC4 != -1 &&
                g_FieldingLogic.unkC4 != currentBase &&
                g_FieldingLogic.unkC4 != nextBase) {
                g_FieldingLogic.unkF4 = -1;
            }

            if (g_FieldingLogic.unkCC != -1 &&
                g_FieldingLogic.unkCC != 9 &&
                g_FieldingLogic.unkCC != currentBase &&
                g_FieldingLogic.unkCC != nextBase) {
                g_FieldingLogic.unkF4 = -1;
            }
        }
    }
}
