#include "challenge/rep_0250.h"

// .text:0x00008CD4 size:0xE8
void fn_1_8CD4(void) {
    ChallengeLayoutPosition* position = fn_80035F20(lbl_1_data_CC8.id, 1, lbl_1_bss_2FAC, (s16)(lbl_1_bss_2FAC + 2));
    lbl_80371C30[lbl_1_bss_2FCC->unkIndex].obj->pos.x = position->x;
    lbl_80371C30[lbl_1_bss_2FCC->unkIndex].obj->pos.y = position->y;
    fn_80035ED0(1);
    lbl_1_bss_2FAC++;
    if (lbl_1_bss_2FAC > 3) lbl_1_bss_2FAC = 0;
}

// .text:0x00008DBC size:0x178
void fn_1_8DBC(void) {
    DrawingSceneStruct* scene;
    ChallengeLayoutState* state = &lbl_1_bss_2FA8;
    (scene = lbl_803CC1B8)->unk18++;
    if (state->mode == 1 || state->mode == 3) {
        if (lbl_8039C3E0.mode == 1) {
            if (state->loaded == 0) {
                fn_800B0A14_removeQueue();
                state->loaded = 1;
                return;
            } else {
                ChallengeLayoutPosition* position = fn_80035F20(lbl_1_data_CC8.id, 1, state->index, (s16)(state->index + 2));
                lbl_80371C30[state->item->unkIndex].obj->pos.x = position->x;
                lbl_80371C30[state->item->unkIndex].obj->pos.y = position->y;
                fn_80035ED0(1);
                state->index++;
                if (state->index > 3) state->index = 0;
            }
        }
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if ((lbl_803C77B8.held & 1) || (lbl_803C77B8.held & 2)) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
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
    DrawingSceneStruct* scene;
    ChallengeLayoutState* state = &lbl_1_bss_2FA8;
    (scene = lbl_803CC1B8)->unk18++;
    if (state->mode == 0) {
        fn_80035EEC(3, 0);
        fn_80035EEC(7, 1);
        fn_80035ED0(2);
    } else if (state->mode == 1) {
        fn_80035EEC(11, 0);
        fn_80035EEC(15, 1);
        fn_80035EEC(19, 2);
    } else {
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if (state->previous != (s8)state->selected) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
    if (lbl_803C77B8.held & 0x200) fn_800B0A14_removeQueue();
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
    DrawingSceneStruct* scene = lbl_803CC1B8;

    fn_80034E20(scene, lbl_1_data_B88);
    lbl_80371C30[scene->unkIndex].obj->field_0x66 = lbl_1_bss_2FAA;
    scene->unk18 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_96D4;
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
