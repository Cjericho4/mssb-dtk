/* fn_3_215AC (rep_940.c) NONMATCHING best attempt (~32 diff lines, float register numbering only).
 * Logic/branches match. Remaining: freg allocation in the mound-X lerp (target: [1]->f0, [0]->f3, step f2) and
 * in the pitcher.x approach block (target: tgt f3, cur f2, d f1, limit f4). Tried expression orders,
 * inline helper, step local, tgt/cur locals with all decl orders.
 * Needs in rep_940.c: extern f32 lbl_3_data_4474[4]; extern u8 lbl_3_data_190C[][6];
 * #include "game/gap_9CD90.h", "game/rep_1200.h", "game/rep_720.h".
 */
void fn_3_215AC(void) {
    s32 idx;
    f32 d;
    f32 tgt;
    f32 cur;

    if (g_Pitcher.currentStateFrameCounter == 1) {
        if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
            g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
        } else {
            idx = fn_3_9E5A0(lbl_3_data_190C[g_Pitcher.charClass], 6);
            if (idx != 5) {
                g_AiLogic.aIMoundLocationIndex = idx;
                d = (lbl_3_data_4474[1] - lbl_3_data_4474[0]) / 5.0f;
                g_AiLogic.aIMoundLocationX = d * idx + lbl_3_data_4474[0];
            }
        }
    }
    if (g_Pitcher.currentStateFrameCounter >= 30) {
        tgt = g_AiLogic.aIMoundLocationX;
        cur = g_Pitcher.pitcher.x;
        if (tgt != cur) {
            d = tgt - cur;
            if (d > lbl_3_rodata_990) {
                if (d <= lbl_3_data_4474[2]) {
                    g_Pitcher.pitcher.x = tgt;
                } else {
                    g_Pitcher.pitcher.x = cur + lbl_3_data_4474[2];
                }
            } else {
                if (d >= -lbl_3_data_4474[2]) {
                    g_Pitcher.pitcher.x = tgt;
                } else {
                    g_Pitcher.pitcher.x = cur - lbl_3_data_4474[2];
                }
            }
        }
    }
    if (g_Pitcher.currentStateFrameCounter >= g_AiLogic.AIFrameToBeginPitch && g_Batter.beginningOfABAnimationOccuring == 0) {
        fn_3_212A0();
        fn_3_20FB0();
        fn_3_750C4(2);
        g_Stats.unk38 = 1;
    }
}
