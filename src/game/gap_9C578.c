#include "game/gap_9C578.h"
#include "UnknownHeaders.h"
#include "game/gap_AC9F8.h"
#include "game/rep_1770.h"
#include "game/rep_16B8.h"

// .text:0x0009C578 size:0x21C
void fn_3_9C578(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724.unk_A5 == 0) {
        lbl_3_common_bss_32724.unk_A5 = 1;
        lbl_3_common_bss_32724.unk_A6 = 0;
        lbl_3_common_bss_32724.unk_A7 = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        fn_800B0A5C_insertQueue(fn_3_9B7F4, 2);
        if (lbl_3_common_bss_32724.unk_A8 == 0) {
            fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
        }
        if (g_Batter.chemLinksOnBase != 0) {
            fn_800B0A5C_insertQueue(fn_3_99CFC, 2);
        }
    }
    if (lbl_3_common_bss_32724.unk_AC == 1 && g_GameLogic.FrameCountOfCurrentPitch == 10) {
        fn_800B0A5C_insertQueue(fn_3_955CC, 2);
        lbl_3_common_bss_32724.unk_AC = 2;
    }
    if (lbl_3_common_bss_32724.unk_A5 != 0 && lbl_3_common_bss_32724.unk_A6 < 0xFF) {
        if (lbl_3_common_bss_32724.unk_A6 < 0xF0) {
            lbl_3_common_bss_32724.unk_A6 += 0x10;
        } else {
            lbl_3_common_bss_32724.unk_A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724.unk_A7 != 0 && lbl_3_common_bss_32724.unk_A7 < 0xFF) {
        if (lbl_3_common_bss_32724.unk_A7 <= 0x10) {
            lbl_3_common_bss_32724.unk_A7 = 0;
            lbl_3_common_bss_32724.unk_A5 = 0;
        } else {
            lbl_3_common_bss_32724.unk_A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724.unk_A5 != 0) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            if (!g_Batter.moonShotInd || g_Ball.framesSinceHit > 1) {
                lbl_3_common_bss_32724.unk_A7 = 0xF0;
            }
        }
        if (lbl_3_common_bss_34C90.field_0x1D5 != 0) {
            lbl_3_common_bss_32724.unk_A7 = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724.unk_A7 = 0;
        lbl_3_common_bss_32724.unk_A5 = 0;
    }
}

// .text:0x0009C794 size:0x35C
void fn_3_9C794(void) {
    return;
}
