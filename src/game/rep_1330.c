#include "game/rep_1330.h"
#include "header_rep_data.h"
#include <string.h>
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "game/gap_9CD90.h"
#include "game/rep_E08.h"

extern u8 lbl_3_common_bss_321A0[0x80];

// .text:0x0007C4E4 size:0x2C8 mapped:0x806BB578
void fn_3_7C4E4(void) {
    return;
}


// .text:0x0007C7AC size:0x22C mapped:0x806BB840
void fn_3_7C7AC(void) {
    memcpy(g_ReplayCopies.gameLogic, &g_GameLogic, 0x158);
    memcpy(g_ReplayCopies.strikes, &g_Strikes, 0x24);
    memcpy(g_ReplayCopies.scores, &g_Scores, 0xC8);
    memcpy(g_ReplayCopies.ball, &g_Ball, 0x1BF8);
    memcpy(g_ReplayCopies.pitcher, &g_Pitcher, 0x178);
    memcpy(g_ReplayCopies.batter, &g_Batter, 0xB0);
    memcpy(g_ReplayCopies.aiLogic, &g_AiLogic, 0xBC);
    memcpy(g_ReplayCopies.fieldingLogic, &g_FieldingLogic, 0x150);
    memcpy(g_ReplayCopies.runningLogic, &g_RunningLogic, 0x20);
    memcpy(g_ReplayCopies.fielders, g_Fielders, 0x15A8);
    memcpy(g_ReplayCopies.runners, g_Runners, 0x550);
    memcpy(g_ReplayCopies.batterStats, lbl_803537E4, 0x2AC);
    memcpy(g_ReplayCopies.pitcherStats, lbl_803535C8, 0x21C);
    memcpy(g_ReplayCopies.bss32234, &lbl_3_common_bss_32234, 0x6);
    memcpy(g_ReplayCopies.bss32230, &lbl_3_common_bss_32230, 0x4);
    memcpy(g_ReplayCopies.bss32220, &lbl_3_common_bss_32220, 0xE);
    memcpy(g_ReplayCopies.throwing31ACC, &g_UnkThrowing_31ACC, 0x14);
    memcpy(g_ReplayCopies.animation31EAC, g_UnkAnimation_31EAC, 0x2F4);
    memcpy(g_ReplayCopies.bss321A0, lbl_3_common_bss_321A0, 0x80);
}
