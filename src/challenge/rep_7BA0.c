#include "challenge/rep_7BA0.h"

// .text:0x000282F4 size:0x1B4
void fn_1_282F4(void) {
    return;
}

// .text:0x000284A8 size:0x84
void fn_1_284A8(void) {
    u16 pressed = lbl_803C77B8.pressed;
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (pressed & 3) {
        scene->flag15 ^= 1;
    } else if (pressed & 0x100) {
        scene->flag14 = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_282F4;
    } else if (pressed & 0x200) {
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0002852C size:0x60
void fn_1_2852C(void) {
    return;
}
