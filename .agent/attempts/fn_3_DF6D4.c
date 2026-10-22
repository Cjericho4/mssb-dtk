// Best attempt (21 sbs diff lines): `strength = lbl_3_data_18980;` before the `_19DA[player] = 0` store (21 vs 31). Left: target shares one `li r0,0` between the unrolled i==0 compare and the store; post-loop block regalloc (li r5,1 / g_Minigame in r7 / table in r6).
void fn_3_DF6D4(void) {
    s32 player;
    u8* strength;
    s32 i;

    switch (g_GameLogic._125) {
    case 0:
        player = g_d_GameSettings._35;
        strength = lbl_3_data_18980;
        g_Minigame._19DA[player] = 0;
        for (i = 0; i < 4; i++) {
            if (player != i) {
                g_Minigame.players.aIStrength[i] = *strength;
                strength++;
            }
        }
        g_Minigame._1907 = 1;
        g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
        g_Minigame.multiPlayerInd = 1;
        g_Scores.threshold = 1;
        g_GameLogic._125++;
        break;
    }
    g_Minigame._190A = 1;
    g_Minigame._19DA[g_d_GameSettings._35] = g_d_GameSettings._35;
    lbl_3_common_bss_37400.playerIndex = g_d_GameSettings._35;
    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame._19DF = 0x1E;
    fn_3_5A6D4(0x1B);
}
