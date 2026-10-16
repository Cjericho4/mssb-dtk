/* fn_3_B5694 NONMATCHING (3 diff lines): only the position of `lis r3, lbl_3_common_bss_32724@ha`
 * in the tail (target schedules it after the FAC4 addi; mine one slot earlier). Writing the
 * practiceType_2 store before the unk_B9 store fixed the register allocation. Tried chained,
 * temps, inline helpers, (u8) cast, pointer form. Header: carve CommonBss_32724 _padB8 into
 * unk_B9/unk_BB/unk_BD (fn_3_B5694.headers.diff). */
extern u8 lbl_3_data_FAC4[];

void fn_3_B5694(void) {
    InputStruct* input = &g_Controls[g_Practice.homeAway];

    if (lbl_3_common_bss_32724.unk_BB == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            fn_3_B3C94(5);
            sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            fn_3_5B408();
            fn_3_B3C94(7);
            sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
        } else if (input->_08 & 1) {
            if (g_Practice.practiceType != 0) {
                g_Practice.practiceType--;
            } else {
                g_Practice.practiceType = 4;
            }
            lbl_3_common_bss_32724.unk_BD = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        } else if (input->_08 & 2) {
            if (++g_Practice.practiceType >= 5) {
                g_Practice.practiceType = 0;
            }
            lbl_3_common_bss_32724.unk_BD = 2;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        }
    }
    g_Practice.practiceType_2 = lbl_3_data_FAC4[g_Practice.practiceType];
    lbl_3_common_bss_32724.unk_B9 = g_Practice.practiceType;
}
