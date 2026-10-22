#include "challenge/gap_85A8.h"

// .text:0x000085A8 size:0x7C
void fn_1_85A8(void) {
    if (lbl_803C77B8.pressed & 1) {
        if (--lbl_1_common_bss_472B4.cursor < -1) {
            lbl_1_common_bss_472B4.cursor = lbl_1_common_bss_472B4.count - 1;
        }
    } else if (lbl_803C77B8.pressed & 2) {
        if (++lbl_1_common_bss_472B4.cursor >= lbl_1_common_bss_472B4.count) {
            lbl_1_common_bss_472B4.cursor = -1;
        }
    }
}

// .text:0x00008624 size:0x98
void fn_1_8624(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_803C77B8.held & 0x100) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0;
        scene->unk18 = 0;
    }
    if (lbl_1_common_bss_47674.unkF != 0 || lbl_1_common_bss_47674.unkC == 0) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
    scene->unk18++;
}

// .text:0x000086BC size:0x28
void fn_1_86BC(void) {
    lbl_803CC1B8->unk18 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_8624;
}

// .text:0x000086E4 size:0x8C
void fn_1_86E4(void) {
    return;
}

// .text:0x00008770 size:0x15C
void fn_1_8770(void) {
    return;
}

// .text:0x000088CC size:0x4
void fn_1_88CC(void) {
    return;
}

// .text:0x000088D0 size:0x1C0
void fn_1_88D0(void) {
    return;
}

// .text:0x00008A90 size:0xFC
void fn_1_8A90(void) {
    return;
}

// .text:0x00008B8C size:0x4
void fn_1_8B8C(void) {
    return;
}

// .text:0x00008B90 size:0x10C
void fn_1_8B90(void) {
    return;
}

// .text:0x00008C9C size:0x38
void fn_1_8C9C(void) {
    s32 i;
    lbl_1_common_bss_47698.count = 0;
    i = 10;
    do {
        lbl_1_common_bss_47698.flags[i] = 0;
    } while (--i != 0);
    lbl_1_common_bss_47698.active = 0;
}
