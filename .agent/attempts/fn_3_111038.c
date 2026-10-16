/* fn_3_111038 NONMATCHING (68 diff lines, all register numbering): logic/instruction
 * sequence matches; target keeps &g_Minigame in r3 and &g_Ball in r4, id*2 in r8, mine
 * swaps them through the volatile regs. Tried decl-order permutations, MiniGameStruct* local.
 * Needs #include "game/gap_1658F0.h" and "game/gap_1293D0.h" in rep_31F0.c. */
typedef struct Data213EC {
    u8 _pad0[0xE];
    s16 kingBombBonus; /* 0x0E */
    s16 streakBonus;   /* 0x10 */
} Data213EC;
extern Data213EC lbl_3_data_213EC;

void fn_3_111038(void) {
    s16 power = g_Ball.Hit_HorizontalPower;
    u8* tracker = g_Minigame.bODCharacterHRStreakTracker;
    f32 pts;
    u8 streak;

    tracker[g_Minigame.rosterID * 2]++;
    if (g_Minigame.bOD_HitPowerOfEachChar[g_Minigame.rosterID] < power) {
        g_Minigame.bOD_HitPowerOfEachChar[g_Minigame.rosterID] = power;
    }
    streak = tracker[g_Minigame.rosterID * 2];
    pts = power;
    if (streak > 1) {
        pts += lbl_3_data_213EC.streakBonus * streak;
    }
    if (g_Minigame.bOD_KingBombInd != 0) {
        pts += lbl_3_data_213EC.kingBombBonus;
    }
    g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] = pts;
    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += (s32)pts;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Minigame.rosterID == lbl_3_common_bss_37400.playerIndex) {
        fn_3_1608F0(0, pts, g_Minigame.bOD_KingBombInd);
    }
}
