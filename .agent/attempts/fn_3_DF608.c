// Best attempt (10 sbs lines): loop form (player/strength ptr) + numParticipants store first; left: prologue li r0,0 before the player lbz, lis order (same family as fn_3_DF6D4).
void fn_3_DF608(void) {
    s32 player;
    u8* strength;
    s32 i;

    player = g_d_GameSettings._35;
    strength = lbl_3_data_18980;
    g_Minigame._19DA[player] = 0;
    for (i = 0; i < 4; i++) {
        if (player != i) {
            g_Minigame.minigameControlStruct[0].aIStrength[i] = *strength;
            strength++;
        }
    }
    g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame._1907 = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Scores.threshold = 1;
}
