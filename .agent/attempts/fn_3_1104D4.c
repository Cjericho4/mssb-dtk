// 15 diff entries: missing duplicate extsb and byte-load register; remaining branch-index differences follow that instruction.
// .text:0x001104D4 size:0x160 mapped:0x8074F568
// Generate the active minigame player's swing input during windup and ball flight.
void fn_3_1104D4(void) {
    s8 i;
    s8 player;
    u8 character;
    MiniGameStruct* minigame = &g_Minigame;
    i = 0;
    do {
        g_Minigame._1DBC[i] = 0;
        i++;
    } while (i < 4);
    player = 0;
    do {
        character = g_Minigame.minigameControlStruct[0].characterIndexBytes[player];
        if ((s8)character >= 0 && (s8)character < 4 && player == (s8)g_Minigame.rosterID &&
            g_Minigame.minigameControlStruct[0].battingHandedness[player] != 0) {
            g_Minigame._1DBC[(s8)character] = 1;
            memset(&g_Minigame._1D7C[(s8)character], 0, sizeof(InputStruct));
            switch (g_Pitcher.pitcherActionState) {
            case PITCHER_ACTION_STATE_WINDUP:
                if (minigame->targetSpawns[0].initialized == 0) {
                    fn_3_110634();
                    minigame->targetSpawns[0].initialized = 1;
                }
                if (g_Pitcher.windupCountdownUntilBallReleased <= minigame->targetSpawns[0].value) {
                    g_Minigame._1D7C[(s8)character].buttonInput |= PAD_BUTTON_A;
                }
                break;
            case PITCHER_ACTION_STATE_IN_AIR:
                if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - minigame->targetSpawns[0].unk_0x02) {
                    g_Minigame._1D7C[(s8)character].buttonInput |= PAD_BUTTON_A;
                }
                break;
            }
        }
        player++;
    } while (player < 4);
}
