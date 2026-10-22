// Best attempt (10 sbs lines, from a stub): logic matches (fn_3_9E5A0 weighted pick, (d1-d0)/5*pick+d0); left: target loads lbl_3_data_4474[1] before [0] and uses f3/f2 temps; all float-temp/association forms tried give the same output. Added extern lbl_3_data_190C[][6] + fn_3_9E5A0 prototype to rep_940.c.
void fn_3_20EEC(void) {
    s32 pick;
    f32 step;

    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aIMoundLocationX = 0.0f;
    } else {
        pick = fn_3_9E5A0(lbl_3_data_190C[g_Pitcher.charClass], 6);
        if (pick != 5) {
            g_AiLogic.aIMoundLocationIndex = pick;
            step = (lbl_3_data_4474[1] - lbl_3_data_4474[0]) / 5.0f;
            g_AiLogic.aIMoundLocationX = step * pick + lbl_3_data_4474[0];
        }
    }
}
