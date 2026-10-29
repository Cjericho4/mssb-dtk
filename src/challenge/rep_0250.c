#include "challenge/rep_0250.h"
extern ChallengeLayoutConfig lbl_1_data_BC8;
/* The owning gap_80035DD4.h still declares a void stub; this call takes four arguments. */
void fn_8003664C(u8 id, s32 slot, u16 glyph, s32 position);

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
    DrawingSceneStruct* scene;
    ChallengeLayoutState* state = &lbl_1_bss_2FA8;
    scene = lbl_803CC1B8;
    if (lbl_803C77B8.held & 0x200) {
        fn_80034CEC((u32)state->item);
        fn_800B0A14_removeQueue();
        return;
    }
    state->item = scene;
    fn_80034E20(scene, &lbl_1_data_CC8);
    if (state->mode == 1 || state->mode == 3) {
        ChallengeLayoutPosition* position = fn_80035F20(lbl_1_data_CC8.id, 1, state->index, (s16)(state->index + 2));
        lbl_80371C30[scene->unkIndex].obj->pos.x = position->x;
        lbl_80371C30[scene->unkIndex].obj->pos.y = position->y;
        fn_80035ED0(1);
        state->index++;
        if (state->index > 3) state->index = 0;
    } else {
        lbl_80371C30[scene->unkIndex].obj->unk64 = 7;
        fn_80035ED0(1);
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    lbl_803CC1B8->aFunctionPointer = fn_1_8DBC;
}

// .text:0x000090B8 size:0x2C
void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue(fn_1_8F34, 2);
}

// .text:0x000090E4 size:0x1AC
/* Display the thousands, hundreds, and tens digits in the challenge numeric layout. */
void fn_1_90E4(s32 value) {
    fn_80034CEC((u32)lbl_1_bss_2FCC);
    fn_80034E20(lbl_1_bss_2FCC, &lbl_1_data_BC8);
    lbl_80371C30[lbl_1_bss_2FCC->unkIndex].obj->field_0x5C = 0x80000;
    fn_8003664C(lbl_1_data_BC8.id, 0, value / 1000 + 10, 4);
    value %= 1000;
    lbl_80371C30[lbl_1_bss_2FCC->unkIndex + 1].obj->field_0x5C = 0xC0000;
    fn_8003664C(lbl_1_data_BC8.id, 1, value / 100 + 10, 5);
    value %= 100;
    lbl_80371C30[lbl_1_bss_2FCC->unkIndex + 2].obj->field_0x5C = 0x100000;
    fn_8003664C(lbl_1_data_BC8.id, 2, value / 10 + 10, 6);
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
extern u8 lbl_1_data_FBC;
extern u32 lbl_1_data_B80;
typedef struct ChallengeLayoutGlobal { u8 _pad0[8]; s32 queue; } ChallengeLayoutGlobal;
extern ChallengeLayoutGlobal lbl_80366158;
void fn_80035A00(void);
void fn_800AD038(s32 queue);
void fn_1_97E4(void) {
    DrawingSceneStruct* scene;
    ChallengeLayoutState* state = &lbl_1_bss_2FA8;
    scene = lbl_803CC1B8;
    switch (lbl_803C77B8.pressed) {
    case 0x100:
        state->field8 = 0;
        state->field9 = 0;
        state->field28 = 0;
        if (++state->mode == 3) state->mode = 0;
        switch (state->selected) {
        case 11: break;
        default: fn_80034CEC((u32)state->item); break;
        }
        state->loaded = 0;
        break;
    case 0x200:
        fn_80034CEC((u32)state->item);
        fn_80035A00();
        fn_800AD038(lbl_80366158.queue);
        scene->currentDrawingItem->loadingState = 1;
        break;
    case 0x800: lbl_1_data_FBC = 1; break;
    case 0x400: lbl_1_data_FBC = 0; break;
    case 0x20: lbl_1_data_B80 = 0; break;
    case 0x1000: lbl_1_data_B80 = 0x10000; break;
    case 8:
        if (scene->unk1a_hi != 0) scene->unk1a_hi--;
        else scene->unk1a_hi = 1;
        break;
    case 4:
        scene->unk1a_hi++;
        if (scene->unk1a_hi == 2) scene->unk1a_hi = 0;
        break;
    case 1:
        switch (scene->unk1a_hi) {
        case 0:
            state->field10 = 0;
            state->selected++;
            if ((s8)state->selected >= 12) state->selected = 0;
            break;
        case 1:
            lbl_1_data_B80 += 1000;
            if (lbl_1_data_B80 > 0x70000) lbl_1_data_B80 = 0x70000;
            break;
        }
        state->field28 = 0;
        break;
    case 2:
        switch (scene->unk1a_hi) {
        case 0:
            state->field10 = 0;
            state->selected--;
            if ((s8)state->selected < 0) state->selected = 11;
            break;
        case 1:
            lbl_1_data_B80 -= 1000;
            if (lbl_1_data_B80 >= (u32)-1000) lbl_1_data_B80 = 0;
            break;
        }
        state->field28 = 0;
        break;
    case 3:
    case 0x10:
    case 0x40:
        break;
    }
}

// .text:0x00009AB0 size:0x3F0
void fn_1_9AB0(void) {
    return;
}
