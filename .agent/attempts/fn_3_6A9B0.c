void fn_3_6A9B0(void) {
    s32 charIdx;
    CommonBss_32724* bss;

    if (g_d_GameSettings.minigamesEnabled) {
        charIdx = g_Minigame.players.characterIndex[g_Minigame.rosterID];
    } else {
        charIdx = 9;
    }
    if (g_Batter.chargeStatus == 1) {
        if (g_Batter.chargeFrames == 1) {
            fn_3_C1770(charIdx);
            lbl_3_common_bss_32724.field_0xC9 = 1;
        } else {
            f32 down = 100.0f * g_Batter.chargeDown;
            f32 up = 100.0f * g_Batter.chargeUp;
            fn_3_C1344(charIdx, up >= 100.0f, up, down);
        }
    } else {
        bss = &lbl_3_common_bss_32724;
        if (bss->field_0xC9 != 0) {
            fn_3_C11CC(charIdx, 1);
            bss->field_0xC9 = 0;
        }
    }
}
