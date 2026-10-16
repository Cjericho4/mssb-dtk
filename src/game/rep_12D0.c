#include "game/rep_12D0.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x00077914 size:0xC60 mapped:0x806B69A8
void fn_3_77914(void) {
    return;
}

// .text:0x00078574 size:0x1BC mapped:0x806B7608
void fn_3_78574(void) {
    return;
}

// .text:0x00078730 size:0x394 mapped:0x806B77C4
void fn_3_78730(void) {
    return;
}

// .text:0x00078AC4 size:0x57C mapped:0x806B7B58
void fn_3_78AC4(void) {
    return;
}

// .text:0x00079040 size:0x2F8 mapped:0x806B80D4
void fn_3_79040(void) {
    return;
}

// .text:0x00079338 size:0xDC mapped:0x806B83CC
void fn_3_79338(void) {
    CommonBss32A94* bss;
    s32 i;

    if (g_Strikes.unk_C != 2 && g_Strikes.outs < 3) {
        bss = &lbl_3_common_bss_32A94;
        if (bss->unk24 == 0) {
            if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic.unk113 == 1) {
                if (g_Ball.landingSpotZoneAwayFromHome >= 2) {
                    bss->unk24 = 2;
                }
            }
        } else if (bss->unk24 == 2 && g_Ball.AtBat_ContactResult == 3) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    bss->unk24 = 1;
                }
            }
        }
    }
}

// .text:0x00079414 size:0x194 mapped:0x806B84A8
void fn_3_79414(void) {
    return;
}

// .text:0x000795A8 size:0x1C4 mapped:0x806B863C
void fn_3_795A8(void) {
    CommonBss32A94* bss = &lbl_3_common_bss_32A94;
    u8 cur;
    s32 v;

    if (bss->unk23 > 0) {
        return;
    }
    if (g_Ball.deadBallReason == 1) {
        bss->unk23 = bss->unk22 = 4;
        return;
    }
    if (g_Ball.deadBallReason == 3) {
        bss->unk23 = bss->unk22 = 2;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
        bss->unk23 = bss->unk22 = 4;
        return;
    }
    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0) {
        cur = g_Runners[0].currentBase;
        if (cur == 0) {
            v = 1;
        } else if (g_Runners[0].percentTowardsNextBase < 0.3f) {
            if (g_Runners[0].runnerOnFieldOrOutOrScored == 2 && 0.0f == g_Runners[0].percentTowardsNextBase) {
                v = cur - 1;
            } else {
                v = cur;
            }
        } else {
            v = g_Runners[0].nextBase;
        }
        bss->unk23 = -v;
    }
    if (g_Runners[0].currentBase == -bss->unk23 && bss->unk23 != 0) {
        bss->unk23 *= -1;
        if ((s8)g_Runners[0].baseOfFailedBodyCheck == bss->unk23) {
            bss->unk23--;
        }
        lbl_3_common_bss_32A94.unk22 = bss->unk23;
        return;
    }
    if (g_Runners[0].currentBase - 1 == -bss->unk23 && bss->unk23 != 0) {
        if ((s8)g_Runners[0].baseOfFailedBodyCheck == (1 - bss->unk23) % 4) {
            bss->unk23 *= -1;
            lbl_3_common_bss_32A94.unk22 = bss->unk23;
            return;
        }
    }
    if (g_Runners[0].currentBase != 0) {
        lbl_3_common_bss_32A94.unk22 = g_Runners[0].currentBase;
    }
}

