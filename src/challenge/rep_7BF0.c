#include "challenge/rep_7BF0.h"

// .text:0x0002858C size:0x434
void fn_1_2858C(void) {
    return;
}

// .text:0x000289C0 size:0x20
void fn_1_289C0(Rep7978Camera* camera) {
    fn_1_273D8(camera);
}

// .text:0x000289E0 size:0x100
void fn_1_289E0(void) {
    return;
}

// .text:0x00028AE0 size:0x154
void fn_1_28AE0(void) {
    return;
}

// .text:0x00028C34 size:0xB4
void fn_1_28C34(void) {
    return;
}

// .text:0x00028CE8 size:0x374
void fn_1_28CE8(DrawingSceneStruct* scene) {
    return;
}

// .text:0x0002905C size:0x300
void fn_1_2905C(void) {
    return;
}

// .text:0x0002935C size:0xB8
void fn_1_2935C(Rep7BF0View471D8* view) {
    fn_80037768(view, 2, lbl_1_data_11300.mode, (f32)lbl_1_data_11300.bounds[0] / 100000.0f, (f32)lbl_1_data_11300.bounds[1] / 100000.0f, (f32)lbl_1_data_11300.bounds[2] / 100000.0f, (f32)lbl_1_data_11300.bounds[3] / 100000.0f);
}

// .text:0x00029414 size:0x78
void fn_1_29414(DrawingSceneStruct* scene) {
    if (scene->flag14 != 0) {
        fn_80048BEC(&lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(&lbl_1_bss_471D8.camera, 0);
    fn_1_AF4(10, 10, 1.0f);
    fn_1_28CE8(scene);
}

// .text:0x0002948C size:0x15C
void fn_1_2948C(void) {
    return;
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    return;
}

// .text:0x00029A48 size:0x54
void fn_1_29A48(void) {
    fn_800AD038(lbl_80366158.unk8);
    fn_800A97D0(0x10, 0x1E);
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    return;
}
