#include "challenge/rep_7A28.h"

// .text:0x00027560 size:0x34
void fn_1_27560(s32 value) {
    lbl_1_data_10908[2].value = value;
    lbl_1_data_10908[1].value = value;
    lbl_1_data_10908[0].value = value;
    lbl_1_data_10908[0].mode = 7;
    lbl_1_data_10908[1].mode = 7;
    lbl_1_data_10908[2].mode = 4;
    lbl_1_data_109F8 = value;
}

// .text:0x00027594 size:0x138
void fn_1_27594(void) {
    return;
}

// .text:0x000276CC size:0x404
void fn_1_276CC(void) {
    return;
}

// .text:0x00027AD0 size:0x4
void fn_1_27AD0(void) {
    return;
}

// .text:0x00027AD4 size:0xE4
void fn_1_27AD4(void) {
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    if (lbl_803C77B8.pressed & 8) {
        scene->cursor = ((s8)scene->cursor + 1) % 2;
    } else if (lbl_803C77B8.pressed & 4) {
        scene->cursor = ((s8)scene->cursor + 1) % 2;
    } else if (lbl_803C77B8.held & 0x100) {
        scene->choice = scene->cursor + 1;
        scene->cursor = 0;
    } else if (lbl_803C77B8.held & 0x200) {
        fn_800AD038(lbl_80366158.unk8);
        ((ChallengeScene*)lbl_803CC1B8)->parent->loadingState = 1;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00027BB8 size:0x1B4
void fn_1_27BB8(void) {
    return;
}

// .text:0x00027D6C size:0xE4
void fn_1_27D6C(void) {
    if (((ChallengeScene*)lbl_803CC1B8)->flags34 & 1) {
        lbl_1_data_108E8[(s8)((ChallengeScene*)lbl_803CC1B8)->choice]();
    } else {
        ChallengeAxes axes;
        memcpy(&axes, &lbl_803C77B8.axes, sizeof(axes));
        axes.bytes[0] = -axes.bytes[0];
        axes.bytes[4] = lbl_803C77B8.axes.bytes[5];
        axes.bytes[5] = lbl_803C77B8.axes.bytes[4];
        fn_1_26D28((Rep7978Camera*)((ChallengeScene*)lbl_803CC1B8)->arg14, lbl_803C77B8.buttons, lbl_803C77B8.held, lbl_803C77B8.pressed, &axes);
    }
    if (lbl_803C77B8.held & 0x1000) ((ChallengeScene*)lbl_803CC1B8)->flags34 ^= 1;
}

// .text:0x00027E50 size:0x48
void fn_1_27E50(void) {
    fn_800AD038(lbl_80366158.unk8);
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x00027E98 size:0x280
void fn_1_27E98(void) {
    return;
}

// .text:0x00028118 size:0xE8
void fn_1_28118(void) {
    return;
}

// .text:0x00028200 size:0xF4
void fn_1_28200(void) {
    return;
}
