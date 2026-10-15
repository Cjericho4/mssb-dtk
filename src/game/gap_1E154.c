#include "game/gap_1E154.h"
#include "game/gap_AC9F8.h"

// .text:0x0001E154 size:0x24 mapped:0x8065D1E8
void fn_3_1E154(void) {
    fn_3_219A0();
    fn_3_20A60();
}

// .text:0x0001E178 size:0x1B0 mapped:0x8065D20C
void fn_3_1E178(void) {
    return;
}

// .text:0x0001E328 size:0xC4 mapped:0x8065D3BC
void fn_3_1E328(void) {
    g_AiLogic._46 = (s32)(g_GameLogic.AIDifficulty0Special3Weak[0] * 255) / 4;
    g_AiLogic._47 = (s32)(g_GameLogic.AIDifficulty0Special3Weak[1] * 255) / 4;
    fn_3_20AE0();
    lbl_3_common_bss_34C90.field_0x202 = 0;
    lbl_3_common_bss_34C90.field_0x203 = 0;
    lbl_3_common_bss_34C90.field_0x21C = 0;
    lbl_3_common_bss_34C90.field_0x21D = 0;
    if (g_GameLogic._13E[g_GameLogic.homeTeamInd] != 0) {
        g_GameLogic.runnerAIInd[0] = 1;
    }
    if (g_GameLogic._13E[g_GameLogic.homeTeamInd ^ 1] != 0) {
        g_GameLogic.runnerAIInd[1] = 1;
    }
    g_AiLogic.aIPitchDesiredEndingLocIndex = 0xFF;
}

// .text:0x0001E3EC size:0xCC mapped:0x8065D480
void fn_3_1E3EC(void) {
    return;
}

