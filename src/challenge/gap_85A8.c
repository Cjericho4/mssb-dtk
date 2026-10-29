#include "challenge/gap_85A8.h"
extern char lbl_1_data_B70[];
/* Owning resource API header has incompatible actor declarations. */
s32 fn_80035838(char* descriptor, s32 mode);

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
    Gap85A8State* state = &lbl_1_common_bss_47674;
    if (state->pending == 0) return;
    switch (state->mode) {
    case 0:
        if (state->unkF == state->previous) return;
        state->previous = state->unkF;
        state->unkF = 0;
        break;
    case 1:
        state->previous = state->unkF;
        state->unkF = 1;
        break;
    case 2:
        state->previous = state->unkF;
        state->unkF = 2;
        break;
    }
    state->pending = 0;
}

// .text:0x00008770 size:0x15C
static inline void updateChallengeMode(void) {
    Gap85A8State* state = &lbl_1_common_bss_47674;
    if (state->pending == 0) return;
    switch (state->mode) {
    case 0:
        if (state->unkF == state->previous) return;
        state->previous = state->unkF;
        state->unkF = 0;
        break;
    case 1:
        state->previous = state->unkF;
        state->unkF = 1;
        break;
    case 2:
        state->previous = state->unkF;
        state->unkF = 2;
        break;
    }
    state->pending = 0;
}

void fn_1_8770(void) {
    if (lbl_803C77B8.held & 8) {
        if (--lbl_1_common_bss_47674.mode < 0) lbl_1_common_bss_47674.mode = 2;
    } else if (lbl_803C77B8.held & 4) {
        if (++lbl_1_common_bss_47674.mode == 3) lbl_1_common_bss_47674.mode = 0;
    } else if (lbl_803C77B8.held & 0x100) {
        if (lbl_1_common_bss_47674.ready == 0) {
            lbl_1_common_bss_47674.pending = 1;
            lbl_1_common_bss_47674.ready = 1;
        } else {
            lbl_1_common_bss_47674.pending = 2;
        }
        updateChallengeMode();
    } else if (lbl_803C77B8.held & 0x200) {
        lbl_1_common_bss_47674.unkC = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_8B90;
    }
}

// .text:0x000088CC size:0x4
void fn_1_88CC(void) {
    return;
}

// .text:0x000088D0 size:0x1C0
/* Load the mode-selection resource, then handle selection and confirmation. */
void fn_1_88D0(void) {
    Gap85A8State* state = &lbl_1_common_bss_47674;
    switch (state->unkC) {
    case 0:
        if (fn_80035838(lbl_1_data_B70, 6)) {
            lbl_1_common_bss_47674.pending = 0;
            lbl_1_common_bss_47674.previous = 3;
            state->unkC++;
        }
        break;
    case 1:
    if (lbl_803C77B8.held & 8) {
        if (--state->mode < 0) state->mode = 2;
    } else if (lbl_803C77B8.held & 4) {
        if (++state->mode == 3) state->mode = 0;
    } else if (lbl_803C77B8.held & 0x100) {
        if (state->ready == 0) {
            state->pending = 1;
            state->ready = 1;
        } else {
            state->pending = 2;
        }
        updateChallengeMode();
    } else if (lbl_803C77B8.held & 0x200) {
        state->unkC = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_8B90;
    }
        break;
    }
}

// .text:0x00008A90 size:0xFC
void fn_1_8A90(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_803C77B8.held & 8) {
        if (--lbl_1_common_bss_47674.selection < 0) lbl_1_common_bss_47674.selection = 1;
    } else if (lbl_803C77B8.held & 4) {
        if (++lbl_1_common_bss_47674.selection == 2) lbl_1_common_bss_47674.selection = 0;
    } else if (lbl_803C77B8.held & 0x100) {
        if (lbl_1_common_bss_47674.selection == 0) {
            scene->aFunctionPointer = fn_1_9AB0;
        } else {
            scene->aFunctionPointer = fn_1_88D0;
        }
    } else if (lbl_803C77B8.held & 0x200) {
        lbl_1_common_bss_47674.active = 0;
        fn_80035CA4(6);
        scene->currentDrawingItem->loadingState = 1;
    }
}

// .text:0x00008B8C size:0x4
void fn_1_8B8C(void) {
    return;
}

// .text:0x00008B90 size:0x10C
void fn_1_8B90(void) {
    Gap85A8State* state = &lbl_1_common_bss_47674;
    switch (state->active) {
    case 0:
        state->active++;
        break;
    case 1: {
DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_803C77B8.held & 8) {
        if (--state->selection < 0) state->selection = 1;
    } else if (lbl_803C77B8.held & 4) {
        if (++state->selection == 2) state->selection = 0;
    } else if (lbl_803C77B8.held & 0x100) {
        if (state->selection == 0) {
            scene->aFunctionPointer = fn_1_9AB0;
        } else {
            scene->aFunctionPointer = fn_1_88D0;
        }
    } else if (lbl_803C77B8.held & 0x200) {
        state->active = 0;
        fn_80035CA4(6);
        scene->currentDrawingItem->loadingState = 1;
    }
        break;
    }
    }
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
