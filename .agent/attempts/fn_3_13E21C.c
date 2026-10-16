/* fn_3_13E21C (rep_36D8.c) NONMATCHING best attempt (~19 lines).
 * Remaining diffs are only register allocation of the strength-reduced loop IVs:
 * target list ptr r8, out ptr r7, _18FC ptr r6, g_Runners ptr r5, i r9;
 * ours differ. Tried *out++ vs list[count], init order perms, do/for, u32 i, continue form.
 * Needs fn_3_13E21C.headers.diff (Struct_13E21C_Arg, Data218BC.unk2C, kinoko.h include, extern lbl_3_data_21924).
 */
void fn_3_13E21C(Struct_13E21C_Arg* arg0) {
    s32 list[4];
    s32 count;
    u32 i;
    f32 d;
    s32 pick;
    f32 thresh;

    thresh = lbl_3_data_218BC.unk2C;
    count = 0;
    for (i = 0; i < 4; i++) {
        list[i] = 0;
        if (g_Minigame._18FC[i] >= 0) {
            d = arg0->basePos - g_Runners[i].fractionalBasesRan;
            if (d < 0.0f) {
                d += 4.0f;
            }
            if (d > 2.0f) {
                d = 4.0f - d;
            }
            if (d <= thresh) {
                list[count] = i;
                count++;
            }
        }
    }
    if (count != 0) {
        pick = list[RandomInt_Game(count)];
        g_Minigame.playerIDWithPowerup[0] = pick;
        g_Minigame._1D58 = lbl_3_data_21924[2];
        arg0->active = 0;
        arg0->timer = lbl_3_data_21924[0];
        fn_3_90064(0x2F6);
        fn_3_16C394(pick);
    } else {
        if (g_Minigame._1B19 != 2 && g_Minigame._1B19 != 3) {
            arg0->timer--;
        }
        if (arg0->timer <= 0) {
            arg0->active = 0;
            arg0->timer = lbl_3_data_21924[0];
        }
    }
}
