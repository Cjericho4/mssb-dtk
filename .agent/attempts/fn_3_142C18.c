// Best attempt (9 sbs lines): initRandomTargets body (memset + setRandomTarget loop). Left: target walker r29 vs aIStrength IV r28 swapped; decl order / assignment placement / index form all keep 9-12.
void fn_3_142C18(void) {
    MinigameRandomTarget* target;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    target = g_Minigame.randomTargets;
    i = 0;
    do {
        setRandomTarget(target, g_Minigame.players.aIStrength[i]);
        target++;
    } while (++i < 4);
}
