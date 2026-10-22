// Best attempt (37 sbs lines, from 43): declare `active` before i/j; left: g_Minigame base anchors (r30/r31 vs r31/r29) and loop counter regs.
void fn_3_D9868(void) {
    MinigameStanding standings[4];
    u32 active;
    u32 i;
    u32 j;
    u32 count;
    u8 pick;

    fn_3_1079C8(standings, 0);
    active = 0;
    i = 0;
    do {
        if (standings[i].eliminated == 0) {
            active++;
        }
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    switch (g_Minigame.fieldingOrderMode) {
    case 0:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        j = 1;
        i = 0;
        do {
            if (i != g_Minigame.rosterID) {
                g_Minigame.fieldOrder[j++] = i;
            }
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 3:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        do {
            pick = fn_3_9EE24(g_Minigame.miniGameNumberOfParticipants);
            g_Minigame.fieldOrder[1] = pick;
        } while ((s8)pick == (s8)g_Minigame.fieldOrder[0]);
        break;
    case 1:
    case 2:
    case 4:
    case 5:
        g_Minigame.fieldOrder[0] = g_Minigame.rosterID;
        if (active == 1 && standings[0].id == g_Minigame.rosterID) {
            count = 0;
            i = 0;
            do {
                if (standings[i].eliminated == 1) {
                    count++;
                }
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            g_Minigame.fieldOrder[1] = standings[fn_3_9EE24(count) + 1].id;
        } else {
            do {
                pick = standings[fn_3_9EE24(active)].id;
                g_Minigame.fieldOrder[1] = pick;
            } while ((s8)pick == (s8)g_Minigame.fieldOrder[0]);
        }
        break;
    }
}
