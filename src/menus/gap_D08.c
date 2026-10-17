#include "menus/gap_D08.h"
#include "UnknownHeaders.h"

// .text:0x00000D08 size:0x80
void fn_2_D08(void) {
    return;
}

// .text:0x00000D88 size:0xFC
void fn_2_D88(void) {
    return;
}

// .text:0x00000E84 size:0xE0
void fn_2_E84(void) {
    return;
}

// .text:0x00000F64 size:0xB4
void fn_2_F64(void) {
    return;
}

// .text:0x00001018 size:0x94
void fn_2_1018(void) {
    return;
}

// .text:0x000010AC size:0x50
void fn_2_10AC(void) {
    return;
}

// .text:0x000010FC size:0x34
s32 fn_2_10FC(void) {
    fn_80021518(31, (s32)lbl_800EF808.files[2]);
    return 0;
}

// .text:0x00001130 size:0x34
void fn_2_1130(s16 state) {
    lbl_803CC1B8->currentDrawingItem->loadingState = state;
    fn_800B0A14_removeQueue();
}

// .text:0x00001164 size:0x38
void fn_2_1164(void) {
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x0000119C size:0x4
void fn_2_119C(void) {
    return;
}

// .text:0x000011A0 size:0x38
void fn_2_11A0(void) {
    return;
}

// .text:0x000011D8 size:0x44
void fn_2_11D8(void) {
    return;
}
