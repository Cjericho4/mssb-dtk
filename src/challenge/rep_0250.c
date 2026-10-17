#include "challenge/rep_0250.h"

// .text:0x00008CD4 size:0xE8
void fn_1_8CD4(void) {
    return;
}

// .text:0x00008DBC size:0x178
void fn_1_8DBC(void) {
    return;
}

// .text:0x00008F34 size:0x184
void fn_1_8F34(void) {
    return;
}

// .text:0x000090B8 size:0x2C
void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue(fn_1_8F34, 2);
}

// .text:0x000090E4 size:0x1AC
void fn_1_90E4(void) {
    return;
}

// .text:0x00009290 size:0xF0
void fn_1_9290(void) {
    return;
}

// .text:0x00009380 size:0x324
void fn_1_9380(void) {
    return;
}

// .text:0x000096A4 size:0x2C
void fn_1_96A4(void) {
    fn_800B0A5C_insertQueue(fn_1_9380, 2);
}

// .text:0x000096D0 size:0x4
void fn_1_96D0(void) {
    return;
}

// .text:0x000096D4 size:0x68
void fn_1_96D4(void) {
    DrawingSceneStruct* scene;
    (scene = lbl_803CC1B8)->unk18++;
    if ((lbl_803C77B8.held & 1) || (lbl_803C77B8.held & 2)) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
    lbl_1_bss_2FB9 = lbl_1_bss_2FAA;
}

// .text:0x0000973C size:0x7C
void fn_1_973C(void) {
    return;
}

// .text:0x000097B8 size:0x2C
void fn_1_97B8(void) {
    fn_800B0A5C_insertQueue(fn_1_973C, 2);
}

// .text:0x000097E4 size:0x2CC
void fn_1_97E4(void) {
    return;
}

// .text:0x00009AB0 size:0x3F0
void fn_1_9AB0(void) {
    return;
}
