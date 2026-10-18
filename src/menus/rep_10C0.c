#include "menus/rep_10C0.h"

extern MenusCameraConfig lbl_2_data_3BB0[];
extern void fn_80011640(DrawingSceneStruct* src, DrawingSceneStruct* dst);

// .text:0x000927C8 size:0x26C
void fn_2_927C8(void) {
    return;
}

// .text:0x00092A34 size:0x27C
void fn_2_92A34(void) {
    return;
}

// .text:0x00092CB0 size:0x27C
void fn_2_92CB0(void) {
    return;
}

// .text:0x00092F2C size:0x3B0
void fn_2_92F2C(DrawingSceneStruct* scene) {
    return;
}

// .text:0x000932DC size:0x91C
void fn_2_932DC(DrawingSceneStruct* scene) {
    return;
}

// .text:0x00093BF8 size:0x6C
void fn_2_93BF8(DrawingSceneStruct* scene) {
    switch (lbl_2_bss_1A824C->unk197845) {
        case 0:
            fn_2_932DC(scene);
            break;
        case 1:
            fn_2_92F2C(scene);
            break;
    }
    fn_80011640(scene, scene);
}

// .text:0x00093C64 size:0x9A0
void fn_2_93C64(void) {
    return;
}

// .text:0x00094604 size:0x18
void fn_2_94604(u8 value) {
    lbl_2_bss_1A824C->unk197856 = value;
}

// .text:0x0009461C size:0x18
void fn_2_9461C(s16 value) {
    lbl_2_bss_1A824C->unk19774A = value;
}

// .text:0x00094634 size:0xA8
void fn_2_94634(s32 index) {
    lbl_2_bss_1A824C->camera.position.x = lbl_2_data_3BB0[index].position.x;
    lbl_2_bss_1A824C->camera.position.y = lbl_2_data_3BB0[index].position.y;
    lbl_2_bss_1A824C->camera.position.z = lbl_2_data_3BB0[index].position.z;
    lbl_2_bss_1A824C->camera.target.x = lbl_2_data_3BB0[index].target.x;
    lbl_2_bss_1A824C->camera.target.y = lbl_2_data_3BB0[index].target.y;
    lbl_2_bss_1A824C->camera.target.z = lbl_2_data_3BB0[index].target.z;
    if (index == 0) lbl_2_bss_1A824C->cameraEnabled = 0;
    else lbl_2_bss_1A824C->cameraEnabled = 1;
}

// .text:0x000946DC size:0x178
void fn_2_946DC(void) {
    return;
}
