#include "Unknown/gap_80042D38.h"

// .text:0x80042D38 size:0x30
void fn_80042D38(u16 state) {
    lbl_803CBBCC->previous = lbl_803CBBCC->current;
    lbl_803CBBCC->previousTimer = lbl_803CBBCC->timer;
    lbl_803CBBCC->current = state;
    lbl_803CBBCC->timer = 0;
}

// .text:0x80042D68 size:0x40
BOOL fn_80042D68(Gap80042D38Task* task, s32 index, s32 time) {
    Gap80042D38Entry* entry = lbl_80371C30[task->baseIndex + index].entry;
    if ((s32)(entry->time >> 16) >= time) {
        entry->active = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DA8 size:0x40
BOOL fn_80042DA8(Gap80042D38Task* task, s32 index, s32 time) {
    Gap80042D38Entry* entry = lbl_80371C30[task->baseIndex + index].entry;
    if ((s32)(entry->time >> 16) == time) {
        entry->active = 0;
        return 1;
    }
    return 0;
}

// .text:0x80042DE8 size:0x5A4
void challengeStarMenu(void) {
    return;
}

// .text:0x8004338C size:0x4F4
void starMenuCursor(void) {
    return;
}

// .text:0x80043880 size:0x1418
void fn_80043880(void) {
    return;
}

// .text:0x80044C98 size:0x14E4
void fn_80044C98(void) {
    return;
}

// .text:0x8004617C size:0x1078
void fn_8004617C(void) {
    return;
}

// .text:0x800471F4 size:0xAEC
void fn_800471F4(void) {
    return;
}

// .text:0x80047CE0 size:0x304
void fn_80047CE0(void) {
    return;
}

// .text:0x80047FE4 size:0x6FC
void pauseMenuSelection(void) {
    return;
}

// .text:0x800486E0 size:0x84
void fn_800486E0(void) {
    return;
}

// .text:0x80048764 size:0xBC
void fn_80048764(void) {
    return;
}

// .text:0x80048820 size:0x3CC
void fn_80048820(void) {
    return;
}
