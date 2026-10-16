/* fn_3_1412BC NONMATCHING (src/game/rep_36D8.c, uses setTargetSpawn inline helper already in file).
   Structure/instructions identical; only saved-register permutation remains: target wants loop counter i in r26
   (below the hoisted table bases r27-r29) and the strength-byte pointer in r30 / spawn ptr in r31; MWCC gives i r29.
   Tried: decl orders, explicit strength pointer (all perms), for vs do-while, &spawns[i] form (adds mr), no-local form. */
void fn_3_1412BC(void) {
    MinigameTargetSpawn* target = g_Minigame.targetSpawns;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    i = 0;
    do {
        setTargetSpawn(target, g_Minigame.players.aIStrength[i]);
        target++;
    } while (++i < 4);
    changeScene(1, 6);
    fn_3_5A6D4(2);
}
