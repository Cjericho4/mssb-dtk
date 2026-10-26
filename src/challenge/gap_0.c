#include "challenge/gap_0.h"

// .text:0x00000000 size:0x20
void fn_1_0(ANIMBank* animBank) {
    ANIMGet(animBank);
}

// .text:0x00000020 size:0xC8
void fn_1_20(void) {
    return;
}

// .text:0x000000E8 size:0xC8
void fn_1_E8(void) {
    return;
}

// .text:0x000001B0 size:0x30
void fn_1_1B0(u32* table, s32 count) {
    u32* entry = table;
    s32 i;

    for (i = 0; i < count; i++) {
        if (*entry != 0) {
            *entry += (u32)table;
        }
        entry++;
    }
}

// .text:0x000001E0 size:0x388
void fn_1_1E0(void) {
    return;
}

// .text:0x00000568 size:0x24
void fn_1_568(void) {
    if (lbl_803CC1B8->loadingState == 1) {
        lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
    }
}

// .text:0x0000058C size:0x5C
void fn_1_58C(void) {
    fn_800B0A5C_insertQueue(fn_1_1E0, 0)->unk10 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_568;
    lbl_803CC1B8->loadingState = 0;
}

// .text:0x000005E8 size:0x4
void fn_1_5E8(void) {
    return;
}
