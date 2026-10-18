#include "menus/rep_0438.h"
extern void fn_800628D4(s32 player);
extern u8 lbl_2_bss_100B4;
#include "menus/gap_4B1AC.h"
#include "menus/gap_D08.h"
#include "menus/rep_0568.h"
#include "string.h"
#include "menus/gap_71EC4.h"
#include "UnknownHeaders.h"
extern u16 lbl_2_bss_AE0;

// .text:0x00012238 size:0x194
void fn_2_12238(void) {
    return;
}

// .text:0x000123CC size:0x5BC
void fn_2_123CC(void) {
    return;
}

// .text:0x00012988 size:0x24
void fn_2_12988(void) {
    lbl_8034E9A0.alternateTimeHigh = lbl_803C7898.high;
    lbl_8034E9A0.alternateTimeLow = lbl_803C7898.low;
}

// .text:0x000129AC size:0x24
void fn_2_129AC(void) {
    lbl_8034E9A0.timeHigh = lbl_803C7898.high;
    lbl_8034E9A0.timeLow = lbl_803C7898.low;
}

// .text:0x000129D0 size:0xA0
void fn_2_129D0(void) {
    Rep0568State* state = &lbl_2_bss_100B8;
    memset(state->active, 0, state->count);
    memset(lbl_2_bss_100B8.counters, 0, state->count);
    memset(&lbl_2_bss_100B8.counters[7], -1, 2);
    lbl_2_bss_100B8.active[4] = 0;
    lbl_2_bss_100B8.active[5] = 0;
    lbl_2_bss_100B8.active[6] = 0;
    lbl_2_bss_100B8.active[7] = 0;
    lbl_2_bss_100B8.counters[4] = 0;
    lbl_2_bss_100B8.counters[5] = -1;
    lbl_2_bss_100B8.counters[6] = -1;
    lbl_2_bss_100B8.unkC = -1;
    state->count = 0;
}

// .text:0x00012A70 size:0xF0
void fn_2_12A70(void) {
    if (lbl_2_bss_100B8.pendingActions[0] != 0) {
        lbl_2_bss_100B8.pendingActions[0] = 0;
        fn_800628D4(lbl_8034E9A0.players[0]);
    }
    if (lbl_2_bss_100B8.pendingActions[1] != 0) {
        lbl_2_bss_100B8.pendingActions[1] = 0;
        fn_800628D4(lbl_8034E9A0.players[1]);
    }
    if (lbl_2_bss_100B8.actionFlags[0] != 0 && lbl_2_bss_100B8.actionFlags[1] != 0) {
        if (g_d_GameSettings.GameModeSelected != 5) lbl_2_bss_100B4 = 1;
        lbl_803CBBCC->state = 4;
        if (g_d_GameSettings._10 == 0) {
            lbl_2_bss_100B8.actionFlags[1] = 0;
            lbl_2_bss_100B8.pendingActions[1] = 0;
        }
    }
}

// .text:0x00012B60 size:0xD4
void fn_2_12B60(void) {
    return;
}

// .text:0x00012C34 size:0xA4
void fn_2_12C34(void) {
    u8 count;
    s32 i, value;
    if (lbl_2_bss_100B8.unk4A) return;
    if (lbl_2_bss_100B8.unk20 == 1 || !lbl_803C5EA4.unk5) {
        if (lbl_2_bss_AE0 == 60000) lbl_2_bss_AE0 = 0;
        lbl_2_bss_AE0++;
    }
    count = 12;
    value = 4;
    if (g_d_GameSettings.GameModeSelected == 5) count = 6;
    for (i = 0; i < count; i++) {
        value++;
        if (value == 21) value = 5;
    }
}

// .text:0x00012CD8 size:0x2B0
void fn_2_12CD8(void) {
    return;
}

// .text:0x00012F88 size:0xC1C
void fn_2_12F88(void) {
    return;
}
