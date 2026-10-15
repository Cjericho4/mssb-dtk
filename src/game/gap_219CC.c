#include "game/gap_219CC.h"
#include "UnknownHeaders.h"

// .text:0x000219CC size:0xDC mapped:0x80660A60
void fn_3_219CC(void) {
    return;
}

// .text:0x00021AA8 size:0x134 mapped:0x80660B3C
void fn_3_21AA8(void) {
    return;
}

// .text:0x00021BDC size:0xA0 mapped:0x80660C70
void fn_3_21BDC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    switch (scene->drawingState) {
    case 0:
        scene->drawingState = 1;
        scene->timer18 = 0x5A;
        break;
    case 1:
        if (scene->timer18-- == 0) {
            scene->drawingState = 2;
        }
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->drawingState = 0;
        break;
    }
}

// .text:0x00021C7C size:0x14 mapped:0x80660D10

void fn_3_21C7C(s32 arg0, u8 arg1) {
    u8* base = (u8*)lbl_3_common_bss_1323C;
    *(base + arg0 + 0x261) = arg1;
}
