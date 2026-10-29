// 18 register-only diff entries: player r8 vs r7 and pause setup temporaries; five attempts.
// .text:0x00108854 size:0x194 mapped:0x807478E8
// Open the minigame pause menu for the first human player pressing Start.
BOOL fn_3_108854(void) {
    s8 controller;
    u32 player;
    if (g_Minigame.turnOverStatus != 0) {
        return FALSE;
    }
    for (player = 0; player < 4; player++) {
        controller = g_Minigame.minigameControlStruct[0].characterIndex[player];
        if (controller >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[player] == 0 &&
            (g_Controls[controller].newButtonInput & PAD_BUTTON_START)) {
            goto openPause;
        }
    }
    return FALSE;
openPause:
    g_Minigame.pauseInd = 1;
    lbl_3_common_bss_34C90.field_0x0A = 0;
    lbl_3_common_bss_34C90.field_0x00 = g_Minigame.minigameControlStruct[0].characterIndex[player];
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        lbl_3_common_bss_34C90.field_0x1D0 = 16;
    } else if (g_Minigame._1A3C != 0) {
        lbl_3_common_bss_34C90.field_0x1D0 = 13;
    } else {
        lbl_3_common_bss_34C90.field_0x1D0 = 9;
    }
    lbl_3_common_bss_34C90.field_0x1D2 = 0;
    lbl_3_common_bss_34C90.field_0x1DA = 0;
    return TRUE;
}

