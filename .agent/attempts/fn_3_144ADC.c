/* fn_3_144ADC (rep_37A8.c) NONMATCHING best attempt (~38 diff lines, scheduling only).
 * Remaining: in both lerp cases the target loads lbl_3_data_21E68[16] (n) before the first xoris/stw of t,
 * and loads lbl_3_data_21D2C[a] before [b]; MWCC here interleaves differently. Tried inline lerp with all
 * parameter orders, f32/s32/s16 params, ratio param, explicit ratio local.
 * Needs: extern s16 lbl_3_data_21E68[]; extern f32 lbl_3_data_21D2C[2]; prototype void fn_3_144ADC(s32 i);
 * and fn_3_144ADC.headers.diff (Fielder: f32 unkC carved at 0x0C).
 */
static inline f32 lerp37A8(f32 a, f32 b, s16 t, s16 n) {
    return b + (a - b) * ((f32)t / (f32)n);
}

// .text:0x00144ADC size:0x1DC mapped:0x80783B70
void fn_3_144ADC(s32 i) {
    InputStruct* in = &g_Controls[g_Minigame.players.characterIndex[i]];
    Fielder* f = &g_Fielders[g_Minigame.minigameFielderIndex[i]];

    if (g_Minigame.players.battingHandedness[i] != 0) {
        in = &g_Minigame._1D7C[g_Minigame.players.characterIndex[i]];
    }
    if ((&g_Minigame._1B34[8])[i] < 0x7FFE) {
        (&g_Minigame._1B34[8])[i]++;
    } else {
        (&g_Minigame._1B34[8])[i] = 0x7FFF;
    }
    switch (g_Minigame._1CA5[i]) {
    case 1:
        f->unkC = lerp37A8(lbl_3_data_21D2C[0], lbl_3_data_21D2C[1], (&g_Minigame._1B34[8])[i], lbl_3_data_21E68[16]);
        if ((&g_Minigame._1B34[8])[i] >= lbl_3_data_21E68[16]) {
            g_Minigame._1CA5[i] = 2;
            (&g_Minigame._1B34[8])[i] = 0;
        }
        break;
    case 2:
        if (!(in->buttonInput & 4)) {
            g_Minigame._1CA5[i] = 3;
            (&g_Minigame._1B34[8])[i] = 0;
        }
        break;
    case 3:
        f->unkC = lerp37A8(lbl_3_data_21D2C[1], lbl_3_data_21D2C[0], (&g_Minigame._1B34[8])[i], lbl_3_data_21E68[16]);
        if ((&g_Minigame._1B34[8])[i] >= lbl_3_data_21E68[16]) {
            g_Minigame._1CA5[i] = 0;
            (&g_Minigame._1B34[8])[i] = 0;
        }
        break;
    }
}
