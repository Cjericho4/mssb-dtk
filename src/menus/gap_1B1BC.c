#include "menus/gap_1B1BC.h"
#include "menus/rep_0B08.h"
#include "menus/gap_4B1AC.h"
#include "UnknownHeaders.h"

extern void fn_80068720(s32 state);

// .text:0x0001B1BC size:0x158
void fn_2_1B1BC(void) {
    return;
}

// .text:0x0001B314 size:0x218
void fn_2_1B314(void) {
    return;
}

// .text:0x0001B52C size:0x94
void fn_2_1B52C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        if (fn_2_4E970() == 1) scene->field15_0x28 = 1;
        break;
    case 1:
        scene->field15_0x28 = 6;
        break;
    case 6:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x0001B5C0 size:0x10C
void fn_2_1B5C0(void) {
    return;
}

// .text:0x0001B6CC size:0xE8
void fn_2_1B6CC(void) {
    return;
}

// .text:0x0001B7B4 size:0x79C
void fn_2_1B7B4(void) {
    return;
}

// .text:0x0001BF50 size:0x80
void fn_2_1BF50(void) {
    fn_80068720(13);
    lbl_2_bss_1A824C->flag1972BC = 1;
    lbl_2_bss_1A824C->flag1972C0 = 1;
    lbl_2_bss_1A824C->unk1976D6 = 0;
    lbl_2_bss_1A8248->unk44F2 = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C->unk34 = 0;
}

// .text:0x0001BFD0 size:0x104
void fn_2_1BFD0(void) {
    return;
}

// .text:0x0001C0D4 size:0x148
void fn_2_1C0D4(void) {
    return;
}

// .text:0x0001C21C size:0x28
void fn_2_1C21C(void) {
    Vec position;
    fn_2_68DAC(0, &position);
}

// .text:0x0001C244 size:0xF8
void fn_2_1C244(void) {
    return;
}

// .text:0x0001C33C size:0x68
void fn_2_1C33C(void) {
    return;
}

// .text:0x0001C3A4 size:0x4
void fn_2_1C3A4(void) {
    return;
}

// .text:0x0001C3A8 size:0x74
void fn_2_1C3A8(void) {
    if ((s32)lbl_2_bss_1A824C->displayMode == 1) {
        lbl_2_bss_1A8234->panels[0].active = 1;
        lbl_2_bss_1A8234->panels[1].active = 0;
    } else {
        lbl_2_bss_1A8234->panels[1].active = 1;
        lbl_2_bss_1A8234->panels[0].active = 0;
    }
}

// .text:0x0001C41C size:0x74
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234->panels[0].visible = 1;
    lbl_2_bss_1A8234->panels[0].controls[0] = 1;
    lbl_2_bss_1A8234->panels[0].controls[1] = 1;
    lbl_2_bss_1A8234->panels[0].controls[2] = 1;
    lbl_2_bss_1A8234->panels[1].visible = 0;
    lbl_2_bss_1A8234->panels[1].controls[0] = 0;
    lbl_2_bss_1A8234->panels[1].controls[1] = 0;
    lbl_2_bss_1A8234->panels[1].controls[2] = 0;
}

// .text:0x0001C490 size:0x74
void fn_2_1C490(void) {
    lbl_2_bss_1A8234->panels[1].visible = 1;
    lbl_2_bss_1A8234->panels[1].controls[0] = 1;
    lbl_2_bss_1A8234->panels[1].controls[1] = 1;
    lbl_2_bss_1A8234->panels[1].controls[2] = 1;
    lbl_2_bss_1A8234->panels[0].visible = 0;
    lbl_2_bss_1A8234->panels[0].controls[0] = 0;
    lbl_2_bss_1A8234->panels[0].controls[1] = 0;
    lbl_2_bss_1A8234->panels[0].controls[2] = 0;
}

// .text:0x0001C504 size:0xC4
void fn_2_1C504(void) {
    return;
}

// .text:0x0001C5C8 size:0x14C
void fn_2_1C5C8(void) {
    return;
}

// .text:0x0001C714 size:0x14C
void fn_2_1C714(void) {
    return;
}

// .text:0x0001C860 size:0x734
void fn_2_1C860(void) {
    return;
}

// .text:0x0001CF94 size:0x4AC
void fn_2_1CF94(void) {
    return;
}
