#include "challenge/rep_74A0.h"

// .text:0x000182C0 size:0x2BC
void fn_1_182C0(void) {
    return;
}

// .text:0x0001857C size:0x888
void fn_1_1857C(void) {
    return;
}

// .text:0x00018E04 size:0xE0
void fn_1_18E04(ChallengeOrbit* orbit, f32 angle) {
    f32 sine;
    f32 cosine;
    f32 radians = 0.017453292f * angle;
    sine = (f32)sin(radians);
    cosine = (f32)cos(radians);
    orbit->position.x = (sine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.y = (cosine * lbl_1_data_FB24.radius) / 100000.0f;
    orbit->position.z = 0.0f;
}

// .text:0x00018EE4 size:0x2F8
void fn_1_18EE4(void) {
    return;
}

// .text:0x000191DC size:0x3A0
void fn_1_191DC(void) {
    return;
}

// .text:0x0001957C size:0x3D0
void fn_1_1957C(void) {
    return;
}

// .text:0x0001994C size:0x3D0
void fn_1_1994C(void) {
    return;
}

// .text:0x00019D1C size:0x44
s32 fn_1_19D1C(u32 flags) {
    switch ((flags >> 4) & 0xF) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

// .text:0x00019D60 size:0x48C
void fn_1_19D60(ChallengeRenderModel* model, s32 mode) {
    return;
}

// .text:0x0001A1EC size:0xA4
void fn_1_1A1EC(ChallengeRenderTask* task, s32 mode) {
    ChallengeRenderObject* object = task->object;
    if (task->callback != 0) {
        task->callback(task);
    }
    if (object->model != 0) {
        fn_800B2D5C(object);
        GXInvalidateVtxCache();
        fn_1_19D60(object->model, mode);
    } else {
        for (object = object->children; object != 0; object = object->next) {
            if (object->model != 0) {
                DOSetWorldMatrix(object->model, object->world);
            }
            fn_1_19D60(object->model, mode);
        }
    }
}

// .text:0x0001A290 size:0x124
static inline void drawChallengeTask(HugeAnimEntry68* entry, s32 mode) {
    ChallengeRenderTask* task = (ChallengeRenderTask*)&entry->unk34;
    ChallengeRenderObject* object = task->object;
    if (object != 0 && entry[1].unk10 != 0) {
    if (task->callback != 0) {
        task->callback(task);
    }
    if (object->model != 0) {
        fn_800B2D5C(object);
        GXInvalidateVtxCache();
        fn_1_19D60(object->model, mode);
    } else {
        for (object = object->children; object != 0; object = object->next) {
            if (object->model != 0) {
                DOSetWorldMatrix(object->model, object->world);
            }
            fn_1_19D60(object->model, mode);
        }
    }
    }
}

void fn_1_1A290(HugeAnimEntry68* entries, s32 mode) {
    u16 i;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < entries->count; i++) {
        drawChallengeTask(&entries[i], mode);
    }
}

// .text:0x0001A3B4 size:0x3C0
void fn_1_1A3B4(void) {
    return;
}

// .text:0x0001A774 size:0xDC
void fn_1_1A774(void) {
    s32 i;
    s32 r, g, b, a;
    ChallengeSelection* selection = &lbl_1_bss_69F0;
    hugeAnimStruct* animations = &g_hugeAnimStruct;
    Mtx matrix;
    ChallengeModelGroup* model = (ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34;
    if (selection->selected < model->count) {
        for (i = 0; i < ((ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34)->count; i++) {
            if (i == selection->selected) {
                r = 0; g = 255; b = 255; a = 255;
            } else {
                r = 0; g = 128; b = 128; a = 64;
            }
            fn_800B2C88((ChallengeModelGroup*)animations->ctrlOrBonePtr[selection->group].unk34, i, matrix);
            fn_1_1A850(matrix, selection->matrix, r, g, b, a);
        }
    }
}

// .text:0x0001A850 size:0x554
void fn_1_1A850(Mtx matrix, Mtx view, s32 r, s32 g, s32 b, s32 a) {
    return;
}

// .text:0x0001ADA4 size:0x294
void fn_1_1ADA4(void) {
    return;
}

// .text:0x0001B038 size:0xC4
void fn_1_1B038(void) {
    return;
}

// .text:0x0001B0FC size:0x1CC
void fn_1_1B0FC(void) {
    return;
}

// .text:0x0001B2C8 size:0x15C
void fn_1_1B2C8(void) {
    return;
}

// .text:0x0001B424 size:0x298
void fn_1_1B424(void) {
    return;
}

// .text:0x0001B6BC size:0x120
void fn_1_1B6BC(void) {
    return;
}

// .text:0x0001B7DC size:0xBF0
void fn_1_1B7DC(void) {
    return;
}

// .text:0x0001C3CC size:0x4F4
void fn_1_1C3CC(void) {
    return;
}

// .text:0x0001C8C0 size:0x324
void fn_1_1C8C0(void) {
    return;
}

// .text:0x0001CBE4 size:0x504
void fn_1_1CBE4(void) {
    return;
}

// .text:0x0001D0E8 size:0x24
void fn_1_1D0E8(Rep74A0Obj* obj) {
    fn_800B9AA8(obj->context);
}

// .text:0x0001D10C size:0x4
void fn_1_1D10C(void) {
    return;
}

// .text:0x0001D110 size:0x340
void fn_1_1D110(void) {
    return;
}

// .text:0x0001D450 size:0x20
void fn_1_1D450(void) {
    fn_1_1CBE4();
}

// .text:0x0001D470 size:0xA4
void fn_1_1D470(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;

    for (i = 0; i < 0x18; i++) {
        lbl_1_bss_69FC.flags[i] = 0;
    }
    scene->flag15 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_1D450;
}

// .text:0x0001D514 size:0x7C
void fn_1_1D514(void) {
    return;
}
