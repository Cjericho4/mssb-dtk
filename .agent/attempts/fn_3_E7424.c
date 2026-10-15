/* extracted from a full-file attempt (best_sta_c6.c); needs that file's helper types */
void fn_3_E7424(void) {
    StaC6Bss_AE50* bss = &lbl_3_bss_AE50;
    u8 status = g_GameLogic.gameStatus;
    s32 i;
    u8* flags;

    if (status == 1 || status == 0) {
        bss->unk38++;
        flags = bss->activeFlags;
        for (i = 0; i < 4; i++) {
            flags[i] = g_Minigame._1914[i] != 0;
        }
        lbl_3_data_1963F = -1;
        lbl_3_data_19640 = -1;
    }
    bss->prevBallResult = bss->ballResult;
    bss->ballResult = g_Minigame.toyFieldBallStateResult;
    bss->unk34 += (lbl_80366158._28 == 0);
    if (bss->prevBallResult != bss->ballResult) {
        bss->unk34 = 0;
    }
    bss->unk1 = 0;
}
