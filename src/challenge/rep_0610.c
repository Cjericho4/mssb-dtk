#include <string.h>
#include "challenge/rep_0610.h"
/* Light owning header conflicts with the allocator declaration in this unit. */
void LITAlloc(struct MenusLight** light);
void LITInitAttn(struct MenusLight* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void LITInitPos(struct MenusLight* light, f32 x, f32 y, f32 z);
void LITInitDir(struct MenusLight* light, f32 x, f32 y, f32 z);
void LITInitColor(struct MenusLight* light, GXColor* color);
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXFifo.h"
extern f32 lbl_1_data_F570;
void fn_1_F2C(s32 mode, s32 arg1, s32 arg2);
#include "game/rep_1C0.h"
#include "Dolphin/OS/OSUtil.h"
typedef struct ChallengeMovingEffect {
    u8 _pad0[0x14];
    VecXYZ position;
    Vec velocity;
    Vec acceleration;
    s32 effect;
    u16 lifetime;
    u8 initialize;
    u8 paired;
} ChallengeMovingEffect;
extern ChallengeCopyValues lbl_1_data_F10C;
extern s32 lbl_1_data_F174;
/* Effect owning header still exposes stub or incompatible vector signatures. */
void fn_8002F258(VecXYZ* position, s32 effect, s32 mode);
s32 fn_8002F1AC(VecXYZ* position, s32 effect);
extern s32 lbl_1_bss_3084;
/* Partial view of the animation auxiliary data referenced by AnimationStruct. */
struct MenusAnimationAux { u8 _pad0[0x10]; u32 unk_0x10; };
/* rep_0138.h declares a conflicting light view; keep its projection API here. */
void fn_800B806C(s32 index, f32 t, f32 b, f32 l, f32 r, f32 nearZ, f32 farZ, f32 scale);
/* Texture owning header has conflicting actor views with this unit. */
void convertTextureHeader(Gap8000B9C8Texture* texture);
extern CompressedDiskRead lbl_1_data_ADE0;
extern CompressedDiskRead lbl_1_data_A940;


// .text:0x0000C5AC size:0x434
void fn_1_C5AC(void) {
    return;
}

// .text:0x0000C9E0 size:0x1BC
/* Render the challenge camera endpoints and its direction and normal vectors. */
void fn_1_C9E0(ChallengeView* view) {
    Mtx transform;
    Vec endpoint;
    fn_1_F2C(4, 0, 0);
    PSMTXConcat(lbl_1_bss_68FC.view, view->matrix, transform);
    GXLoadPosMtxImm(transform, 0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXBegin(GX_LINES, GX_VTXFMT0, 6);
    GXWGFifo.f32 = lbl_1_bss_30C0.target.x;
    GXWGFifo.f32 = lbl_1_bss_30C0.target.y;
    GXWGFifo.f32 = lbl_1_bss_30C0.target.z;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = lbl_1_bss_30C0.origin.x;
    GXWGFifo.f32 = lbl_1_bss_30C0.origin.y;
    GXWGFifo.f32 = lbl_1_bss_30C0.origin.z;
    GXWGFifo.u32 = 0x00FF00FF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0xFF;
    PSVECScale(&lbl_1_bss_30C0.direction, lbl_1_data_F570, &endpoint);
    GXWGFifo.f32 = endpoint.x;
    GXWGFifo.f32 = endpoint.y;
    GXWGFifo.f32 = endpoint.z;
    GXWGFifo.u32 = 0xFF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0xFFFFFFFF;
    PSVECScale(&lbl_1_bss_30C0.normal, lbl_1_data_F570, &endpoint);
    GXWGFifo.f32 = endpoint.x;
    GXWGFifo.f32 = endpoint.y;
    GXWGFifo.f32 = endpoint.z;
    GXWGFifo.u32 = 0xFFFFFFFF;
}

// .text:0x0000CB9C size:0x88
void fn_1_CB9C(s32 reset) {
    if (reset != 0) {
        lbl_1_bss_30BC = 0;
    } else {
        PSMTXCopy(lbl_1_bss_30C0.matrix, lbl_1_data_F4F8[lbl_803CBBC0].matrix);
        fn_800A7D4C(8, &lbl_1_data_F4F8[lbl_803CBBC0]);
    }
}

// .text:0x0000CC24 size:0xA4
void fn_1_CC24(void) {
    DrawingSceneStruct* entry;
    ChallengeState* state = &lbl_1_bss_3070;

    if (state->queued == 0) {
        state->queued = 1;
        entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_CCC8, (u16)(lbl_803CC1B8->priority + 1));
        if (state->unk2EF9 != 0) {
            Rep0610Items* items = &state->items;
            entry->unk14 = items->item4;
            entry->unk18 = lbl_1_data_F56C;
        } else {
            Rep0610Items* items = &state->items;
            entry->unk14 = items->item8;
            entry->unk18 = lbl_1_data_F56E;
        }
    }
}

// .text:0x0000CCC8 size:0x100
void fn_1_CCC8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    ChallengeTiming* timing = (ChallengeTiming*)scene->unk14;
    if (timing != 0 && timing->time < timing->end) {
        if (lbl_1_bss_5F69 != 0) {
            fn_800385F0(&lbl_1_bss_30C0, 1.0f, 0.5f, 0.1f, 1.0f);
        } else {
            fn_800385F0(&lbl_1_bss_30C0, -1.0f, 0.5f, 0.1f, 1.0f);
        }
        lbl_1_bss_30C0.angle = lbl_1_data_F568;
        fn_80037AA0(&lbl_1_bss_30C0, 0, fn_1_CB9C, scene->unk18, (ChallengeTiming*)scene->unk14);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0000CDC8 size:0x374
void fn_1_CDC8(void) {
    return;
}

// .text:0x0000D13C size:0x1B4
void fn_1_D13C(void) {
    return;
}

// .text:0x0000D2F0 size:0x10
void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

// .text:0x0000D300 size:0x1BC
void fn_1_D300(void) {
    return;
}

// .text:0x0000D4BC size:0xD4
void fn_1_D4BC(void) {
    hugeAnimStruct* animations = &g_hugeAnimStruct;
    AnimationStruct* animation = &animations->fielderStructs[0];
    VecXYZ position;
    if (animation != 0) {
        animation->unk276 >>= 1;
        animation->unk276 = (animation->unk276 & 0x1F) << 3;
        getAnimRelatedCoordinates(0, 0x1E, &position);
        if (animation->unk34.y - position.y < 0.3f) animation->unk276 |= 2;
        getAnimRelatedCoordinates(0, 0x22, &position);
        if (animation->unk34.y - position.y < 0.3f) animation->unk276 |= 4;
    }
    animations->AnimationStructPtrs[0]->unk276 |= 1;
}

// .text:0x0000D590 size:0xA8
void fn_1_D590(s32 a, s32 b, f32 frame) {
    ChallengeState* state = &lbl_1_bss_3070;
    if (state->enabled == 0 || state->mode == 0) return;
    if (state->mode == 2) {
        if ((s32)frame == 0) state->phase += (state->phase != 0);
        if (state->phase == 3) state->phase = 0;
        if (state->phase != 2) return;
    }
    fn_8004B208(a, b, (s8)state->channel < 0 ? 0 : (s8)state->channel);
}

// .text:0x0000D638 size:0x18
u8 fn_1_D638(void) {
    u8 value = lbl_1_bss_3214;
    lbl_1_bss_3214 = 0;
    return value;
}

// .text:0x0000D650 size:0x10
void fn_1_D650(void) {
    lbl_1_bss_3214 = 1;
}

// .text:0x0000D660 size:0x1C
BOOL fn_1_D660(void) {
    return lbl_1_bss_3215 != 0;
}

// .text:0x0000D67C size:0xC
void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

// .text:0x0000D688 size:0x2C
void fn_1_D688(void) {
    if (++lbl_1_bss_3216 == 3) {
        lbl_1_bss_3216 = 0;
    }
}

// .text:0x0000D6B4 size:0x30
void fn_1_D6B4(void) {
    if (lbl_1_bss_3216 == 0) {
        lbl_1_bss_3216 = 3;
    }
    lbl_1_bss_3216--;
}

// .text:0x0000D6E4 size:0x38
s32 fn_1_D6E4(void) {
    switch (lbl_1_bss_3216) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[lbl_1_bss_3216];
    }
    return 0;
}

// .text:0x0000D71C size:0x88
f32 fn_1_D71C(s32 index) {
    s32 count;
    s32 i;
    ChallengeModel* model = (ChallengeModel*)g_hugeAnimStruct.ctrlOrBonePtr[index].unk34;
    count = model->count;
    for (i = 0; i < count; i++) {
        if (model->objects[i]->animation != 0 && model->objects[i]->animation->data != 0) {
            break;
        }
    }
    if (i < count) {
        return model->objects[i]->animation->time;
    }
    return 0.0f;
}

// .text:0x0000D7A4 size:0xFC
void fn_1_D7A4(void) {
    return;
}

// .text:0x0000D8A0 size:0x118
void fn_1_D8A0(void) {
    return;
}

// .text:0x0000D9B8 size:0x464
void fn_1_D9B8(void) {
    return;
}

// .text:0x0000DE1C size:0xF8
void fn_1_DE1C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch (scene->flag14) {
    case 0:
        if ((s8)scene->flag15 == 0) {
            scene->aFunctionPointer = fn_1_D9B8;
        } else {
            while ((s8)scene->flag15-- != 0) {
                if (lbl_1_bss_3218[(s8)scene->flag15].table >= 0) {
                    DrawingSceneStruct* entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_DF14, (u16)(lbl_803CC1B8->priority + 1));
                    entry->loadingState = 0;
                    entry->flag14 = scene->flag15;
                    scene->loadingState = 0;
                    scene->flag14++;
                    break;
                }
            }
        }
        break;
    case 1:
        if (scene->loadingState != 0) scene->flag14 = 0;
        break;
    }
    fn_1_D8A0();
}

// .text:0x0000DF14 size:0x184
void fn_1_DF14(void) {
    return;
}

// .text:0x0000E098 size:0x83C
void fn_1_E098(void) {
    return;
}

// .text:0x0000E8D4 size:0x124
void fn_1_E8D4(void) {
    return;
}

// .text:0x0000E9F8 size:0x28
void fn_1_E9F8(Rep0610Ring* ring, s32 index, s32 steps) {
    s32 i;
    for (i = 0; i < steps; i++) {
        index++;
        if (index == ring->count) {
            index = 0;
        }
    }
}

// .text:0x0000EA20 size:0x2D8
void fn_1_EA20(void) {
    return;
}

// .text:0x0000ECF8 size:0x348
void fn_1_ECF8(void) {
    return;
}

// .text:0x0000F040 size:0x90
void fn_1_F040(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    Vec pos = lbl_1_rodata_7344;

    if (lbl_803C77B8.pressed & 0x100) {
        lbl_1_data_F2A0 = state->selection;
        fn_8002955C(&pos, 0, &lbl_1_data_F2A0);
    } else if (lbl_803C77B8.pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F0D0 size:0x108
void fn_1_F0D0(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    fn_1_F798(&lbl_1_data_F278[state->page]->base, &lbl_1_data_F284.base, sizeof(ChallengeCopyValues));
    if (lbl_803C77B8.pressed & 0x1000) {
        state->page = (state->page + 1) % 3;
    } else if (lbl_803C77B8.buttons & 0x100) {
        if (lbl_803C77B8.held & 0x100) {
            ChallengeScene* entry;
            s32 selection = state->selection;
            lbl_1_data_F278[2]->base.values[0] = selection;
            lbl_1_data_F278[1]->base.values[0] = selection;
            lbl_1_data_F278[0]->base.values[0] = selection;
            entry = (ChallengeScene*)fn_800B0A5C_insertQueue(fn_1_F1D8, 0);
            entry->words[3] = 0xF0;
            entry->words[4] = 4;
        }
    } else if (lbl_803C77B8.pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F1D8 size:0x120
void fn_1_F1D8(void) {
    Control control;
    Mtx matrix;
    VecXYZ position;
    Vec direction;
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    AnimationStruct* animation = g_hugeAnimStruct.AnimationStructPtrs[lbl_1_bss_5F73];
    getAnimRelatedCoordinates(0, scene->words[4], &position);
    control.type = 0;
    CTRLSetRotation(&control, animation->unk40.x, animation->unk40.y, animation->unk40.z);
    CTRLBuildMatrix(&control, matrix);
    direction.x = 0.0f;
    direction.y = 0.0f;
    direction.z = 1.0f;
    PSMTXMultVec(matrix, &direction, &direction);
    fn_80030D88(&position, &direction, lbl_1_data_F278[0], 5);
    fn_80030D88(&position, &direction, lbl_1_data_F278[1], 5);
    fn_80030D88(&position, &direction, lbl_1_data_F278[2], 5);
    if (--scene->words[3] == 0) fn_800B0A14_removeQueue();
}

// .text:0x0000F2F8 size:0x84
void fn_1_F2F8(void) {
    ChallengeState* state = &lbl_1_bss_3070;

    if (lbl_803C77B8.pressed & 0x100) {
        lbl_80108B90 = state->selection;
        fn_800324EC(lbl_1_data_F17C, 0, -1, &lbl_80108B90);
    } else if (lbl_803C77B8.pressed & 0x200) {
        lbl_80108B90 = 0;
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F37C size:0x190
void fn_1_F37C(void) {
    return;
}

// .text:0x0000F50C size:0x1D8
/* Advance a moving effect, updating either its position or two projected bone anchors. */
void fn_1_F50C(void) {
    VecXYZ position;
    ChallengeMovingEffect* scene = (ChallengeMovingEffect*)lbl_803CC1B8;
    AnimationStruct* actor = &g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73];
    if (actor != NULL) {
        actor->unk34.x = scene->position.x;
        actor->unk34.y = scene->position.y;
        actor->unk34.z = scene->position.z;
    }
    fn_80030D88(&scene->position, &scene->velocity, &lbl_1_data_F10C, 5);
    if (scene->initialize) {
        scene->initialize = 0;
        if (scene->paired) {
            getAnimRelatedCoordinates(0, 30, &position);
            position.y = 0.0f;
            fn_8002F258(&position, scene->effect, lbl_1_data_F174);
            getAnimRelatedCoordinates(0, 34, &position);
            position.y = 0.0f;
            fn_8002F258(&position, scene->effect + 1, lbl_1_data_F174);
        } else {
            fn_8002F258(&scene->position, scene->effect, lbl_1_data_F174);
        }
    } else {
        if (scene->paired) {
            getAnimRelatedCoordinates(0, 30, &position);
            position.y = 0.0f;
            fn_8002F1AC(&position, scene->effect);
            getAnimRelatedCoordinates(0, 34, &position);
            position.y = 0.0f;
            fn_8002F1AC(&position, scene->effect + 1);
        } else {
            fn_8002F1AC(&scene->position, scene->effect);
        }
    }
    PSVECAdd(&scene->velocity, &scene->acceleration, &scene->velocity);
    PSVECAdd(&scene->velocity, (Vec*)&scene->position, (Vec*)&scene->position);
    scene->lifetime--;
    if (scene->lifetime == 0) fn_800B0A14_removeQueue();
}

// .text:0x0000F6E4 size:0xB4
void fn_1_F6E4(void) {
    Rep0610Triple* dst = &lbl_1_data_F0BC;
    ChallengeState* state = &lbl_1_bss_3070;
    Vec pos = {0.0f, 0.0f, 10.0f};

    fn_1_F798(dst, &lbl_1_data_F0A8, sizeof(Rep0610Triple));
    if (lbl_803C77B8.pressed & 0x100) {
        dst->values[0] = state->selection;
        fn_80031CA4(&pos, dst);
    } else if (lbl_803C77B8.pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F798 size:0x400
void fn_1_F798(Rep0610Triple* dst, Rep0610Triple* src, s32 size) {
    return;
}

// .text:0x0000FB98 size:0x4AC
void fn_1_FB98(void) {
    return;
}

// .text:0x00010044 size:0x414
void fn_1_10044(void) {
    return;
}

// .text:0x00010458 size:0x108
// Handle the seven-item challenge selector and its confirm/cancel controls.
void fn_1_10458(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    if ((u32)state->selection == 0) {
        if (state->unk_0x24 == 0) {
            DrawingSceneStruct* entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_10560, 11);
            entry->loadingState = 0;
        }
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_UP) {
        if (state->unkC != 0) state->unkC--;
        else state->unkC = 6;
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_DOWN) {
        if (++state->unkC == 7) state->unkC = 0;
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_LEFT) {
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_RIGHT) {
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_A) {
        state->unk2F01 += state->unkC + 1;
        state->unkC = 0;
    } else if (lbl_803C77B8.pressed & PAD_BUTTON_B) {
        state->unkC = 0;
        state->unk2F01 = 1;
    }
}

// .text:0x00010560 size:0x110
// Load and relocate the selector's two texture resources over successive frames.
void fn_1_10560(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    switch (lbl_803CC1B8->loadingState) {
    case 0:
        state->unk_0x24 = (u32)ARAMTransfer(&lbl_1_data_ADE0, 0, 0, 0);
        lbl_803CC1B8->loadingState = 1;
        break;
    case 1:
        if (lbl_803C6CF8.allowLoad == 1) {
            u32* file = (u32*)state->unk_0x24;
            state->texture = (Gap8000B9C8Texture*)((u8*)file + file[0]);
            convertTextureHeader(state->texture);
            state->extraTexture = (Gap8000B9C8Texture*)ARAMTransfer(&lbl_1_data_A940, 0, 1, 0);
            lbl_803CC1B8->loadingState = 2;
        }
        break;
    case 2:
        if (lbl_803C6CF8.allowLoad == 1) {
            convertTextureHeader(state->extraTexture);
            fn_800B0A14_removeQueue();
        }
        break;
    }
}

// .text:0x00010670 size:0x34
void fn_1_10670(void) {
    QueueEntry* entry = fn_800B0A5C_insertQueue(fn_1_10560, 0xB);
    entry->unk10 = 0;
}

// .text:0x000106A4 size:0x10
s32 fn_1_106A4(void) {
    return lbl_1_bss_3098;
}

// .text:0x000106B4 size:0x10
void fn_1_106B4(void) {
    lbl_1_bss_3098 = 0;
}

// .text:0x000106C4 size:0x78
void fn_1_106C4(void) {
    u16 pressed = lbl_803C77B8.pressed;
    ChallengeState* state = &lbl_1_bss_3070;

    if (pressed & 8) {
    } else if (pressed & 4) {
    } else if (pressed & 1) {
        state->unk11 ^= 1;
    } else if (pressed & 2) {
        state->unk11 ^= 1;
    } else if (pressed & 0x100) {
    } else if (pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 1;
    }
}

// .text:0x0001073C size:0x7C
void fn_1_1073C(Rep0610Obj1073C* obj) {
    Vec dir;
    dir.x = lbl_1_bss_67E0.pos.x - obj->pos.x;
    dir.y = lbl_1_bss_67E0.pos.y - obj->pos.y;
    dir.z = lbl_1_bss_67E0.pos.z - obj->pos.z;
    fn_80026134(0, &dir);
    fn_80026130(0, &lbl_1_data_ADC4, lbl_1_data_ADC0);
}

// .text:0x000107B8 size:0x2EC
void fn_1_107B8(void) {
    return;
}

// .text:0x00010AA4 size:0x28
void fn_1_10AA4(Rep0610Obj* obj, f32 value) {
    obj->value = value;
    obj->active = 1;
    if (lbl_1_bss_67B8 != NULL) {
        lbl_1_bss_67B8->value = value;
    }
}

// .text:0x00010ACC size:0x220
/* Draw a colored debug line and restore culling and the normal depth test. */
void fn_1_10ACC(Mtx matrix, Vec* position, void* unused, f32 size, GXColor* color) {
    GXCullMode cullMode;
    GXGetCullMode(&cullMode);
    GXLoadPosMtxImm(matrix, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetLineWidth(10, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(position->x, position->y, position->z);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXPosition3f32(position->x + size, position->y + size, position->z + size);
    GXColor4u8(color->r, color->g, color->b, color->a);
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetCullMode(cullMode);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

// .text:0x00010CEC size:0x140
void fn_1_10CEC(Rep0610Obj12F18* object) {
    Mtx bone;
    Mtx view;
    s32 i;
    s32 index;
    u32 x, y, z;
    ChallengeState* state = &lbl_1_bss_3070;
    if (lbl_1_data_ABA8 == 0) {
        PSMTXTrans(view, g_hugeAnimStruct.fielderStructs[state->modelIndex].unk34.x, g_hugeAnimStruct.fielderStructs[state->modelIndex].unk34.y, g_hugeAnimStruct.fielderStructs[state->modelIndex].unk34.z);
        PSMTXConcat(object->mtx, view, view);
        for (i = 0; (index = state->modelIndex), i < ((ChallengeModel*)g_hugeAnimStruct.ctrlOrBonePtr[index].unk34)->count; i++) {
            if ((u32)i != state->selectedBone) {
                x = 0x80008080; y = 0x80800080; z = 0x00808080;
            } else if (state->blink++ & 0x20) {
                x = 0xFF8080FF; y = 0x80FF80FF; z = 0x8080FFFF;
            } else {
                x = 0xFFFFFFFF; y = 0xFFFFFFFF; z = 0xFFFFFFFF;
            }
            fn_800B2C88((ChallengeModel*)g_hugeAnimStruct.ctrlOrBonePtr[index].unk34, i, bone);
            fn_1_10E2C(bone, view, x, y, z);
        }
    }
}

// .text:0x00010E2C size:0x430
void fn_1_10E2C(Mtx matrix, Mtx view, u32 x, u32 y, u32 z) {
    return;
}

// .text:0x0001125C size:0x490
void fn_1_1125C(void) {
    return;
}

// .text:0x000116EC size:0x28
void fn_1_116EC(struct TextureHeader* tex) {
    SetDisplayStateTexture(tex, 0, 0);
}

// .text:0x00011714 size:0x584
void fn_1_11714(void) {
    return;
}

// .text:0x00011C98 size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(g_hugeAnimStruct.menuLights[i], lbl_1_bss_68FC.view);
    }
}

// .text:0x00011D00 size:0x208
void fn_1_11D00(void) {
    return;
}

// .text:0x00011F08 size:0x2CC
typedef struct ChallengeCameraOutput {
    u8 _pad0[0x70];
    Vec eye;
    Vec target;
} ChallengeCameraOutput;
/* Camera owning header contains incompatible scene declarations. */
ChallengeCameraOutput* fn_80052768(s32 index);
void makeLookAtMatrix(Mtx matrix, Vec* eye, Vec* up, Vec* target);
extern Vec lbl_1_data_AD18;
void fn_1_11F08(Rep0610Unk67E0* camera) {
    Mtx pitch, yaw, rotation;
    Vec angles;
    Vec offset = {0.0f, 0.0f, 100.0f};
    f32 cosine, sine;
    ChallengeCameraOutput* output;
    if (!(lbl_803C77B8.buttons & 0x10)) {
        camera->unk_0xF0 -= (s8)lbl_803C77B8.axes.bytes[3] * 4;
        camera->unk_0xF2 += (s8)lbl_803C77B8.axes.bytes[2] * 4;
        camera->strafe = (s8)lbl_803C77B8.axes.bytes[0] / -256.0f;
        camera->unk_0xF8 = (s8)lbl_803C77B8.axes.bytes[1] / 256.0f;
        camera->pos.y += lbl_803C77B8.axes.bytes[5] / 1024.0f;
        camera->pos.y -= lbl_803C77B8.axes.bytes[4] / 1024.0f;
    }
    angles.x = camera->unk_0xF0;
    angles.y = camera->unk_0xF2;
    angles.z = 0.0f;
    PSVECScale(&angles, 0.0000958738f, &angles);
    PSMTXRotRad(pitch, 'X', angles.x);
    PSMTXRotRad(yaw, 'Y', angles.y);
    sine = yaw[0][2];
    cosine = yaw[0][0];
    PSMTXConcat(yaw, pitch, rotation);
    PSMTXMultVec(rotation, &offset, &camera->target);
    camera->pos.x += camera->unk_0xF8 * sine - camera->strafe * cosine;
    camera->pos.z += camera->unk_0xF8 * cosine + camera->strafe * sine;
    camera->target.x += camera->pos.x;
    camera->target.y += camera->pos.y;
    camera->target.z += camera->pos.z;
    makeLookAtMatrix(camera->view, &camera->pos, &lbl_1_data_AD18, &camera->target);
    output = fn_80052768(0);
    memcpy(&output->eye, &camera->pos, sizeof(Vec));
    memcpy(&output->target, &camera->target, sizeof(Vec));
}

// .text:0x000121D4 size:0x4F8
void fn_1_121D4(void) {
    return;
}

// .text:0x000126CC size:0x154
void fn_1_126CC(void) {
    return;
}

// .text:0x00012820 size:0x1B0
void fn_1_12820(HugeAnimEntry68* entry, Mtx mtx) {
    return;
}

// .text:0x000129D0 size:0x548
void fn_1_129D0(void) {
    return;
}

// .text:0x00012F18 size:0x74
void fn_1_12F18(Rep0610Obj12F18* obj) {
    fn_1_12820(g_hugeAnimStruct.ctrlOrBonePtr, obj->mtx);
    if (lbl_1_data_A978[lbl_1_bss_68FC.unk40] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C.obj, (s32)obj->mtx);
    }
}

// .text:0x00012F8C size:0x258
void fn_1_12F8C(void) {
    return;
}

// .text:0x000131E4 size:0x298
/* Allocate and initialize the four model-preview lights. */
void fn_1_131E4(void) {
    GXColor white = {255, 255, 255, 255};
    LITAlloc(&g_hugeAnimStruct.menuLights[0]);
    LITAlloc(&g_hugeAnimStruct.menuLights[1]);
    LITAlloc(&g_hugeAnimStruct.menuLights[2]);
    LITAlloc(&g_hugeAnimStruct.menuLights[3]);
    LITInitAttn(g_hugeAnimStruct.menuLights[0], 1, 0, 0, 1, 0, 0);
    LITInitPos(g_hugeAnimStruct.menuLights[0], 5, -10, 5);
    LITInitDir(g_hugeAnimStruct.menuLights[0], 0, 0, 0);
    { GXColor color = white; LITInitColor(g_hugeAnimStruct.menuLights[0], &color); }
    LITInitDir(g_hugeAnimStruct.menuLights[0], -5, 0, -5);
    LITInitAttn(g_hugeAnimStruct.menuLights[1], 1, 0, 0, 1, 0, 0);
    LITInitPos(g_hugeAnimStruct.menuLights[1], -5, -10, 0);
    LITInitDir(g_hugeAnimStruct.menuLights[1], 0, 0, 0);
    { GXColor color = white; LITInitColor(g_hugeAnimStruct.menuLights[1], &color); }
    LITInitAttn(g_hugeAnimStruct.menuLights[2], 1, 0, 0, 1, 0, 0);
    LITInitPos(g_hugeAnimStruct.menuLights[2], 0, -10, 5);
    LITInitDir(g_hugeAnimStruct.menuLights[2], 0, 0, 0);
    { GXColor color = white; LITInitColor(g_hugeAnimStruct.menuLights[2], &color); }
    LITInitAttn(g_hugeAnimStruct.menuLights[3], 1, 0, 0, 1, 0, 0);
    LITInitPos(g_hugeAnimStruct.menuLights[3], 0, -10, -5);
    LITInitDir(g_hugeAnimStruct.menuLights[3], 0, 0, 0);
    { GXColor color = white; LITInitColor(g_hugeAnimStruct.menuLights[3], &color); }
}

// .text:0x0001347C size:0x144
/* Initialize the challenge camera, projection volumes, and camera control state. */
void fn_1_1347C(void) {
    Mtx44 projection;
    lbl_1_bss_67E0.pos.x = 0.0f;
    lbl_1_bss_67E0.pos.y = -0.8f;
    lbl_1_bss_67E0.pos.z = 0.0f;
    lbl_1_bss_67E0.target.x = 0.0f;
    lbl_1_bss_67E0.target.y = 0.0f;
    lbl_1_bss_67E0.target.z = 10.0f;
    C_MTXFrustum(projection, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -0.001f, 1280.0f);
    lbl_1_bss_67E0.unk_0x114 = 0;
    lbl_1_bss_67E0.unk_0xF8 = 0.0f;
    lbl_1_bss_67E0.unk_0xF0 = 0;
    lbl_1_bss_67E0.unk_0xF2 = 0;
}

// .text:0x000135C0 size:0x1150
void fn_1_135C0(void) {
    return;
}

// .text:0x00014710 size:0x178
void fn_1_14710(void) {
    return;
}

// .text:0x00014888 size:0x44
void fn_1_14888(Rep0610Obj* obj) {
    if (lbl_1_bss_67E0.useContext != 0) {
        fn_800B9AA8((u32)&lbl_1_bss_67E0.context);
    } else {
        fn_800B9AA8(obj->context);
    }
}

// .text:0x000148CC size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(lbl_80366158.unk8);
    lbl_803CC1B8->loadingState = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// .text:0x00014928 size:0x44
void fn_1_14928(void) {
    fn_800AD038(lbl_80366158.unk8);
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
}

// .text:0x0001496C size:0x64C
void fn_1_1496C(void) {
    return;
}

// .text:0x00014FB8 size:0x1B8
/* Select a challenge animation action, wrapping the cursor over nine entries. */
void fn_1_14FB8(void) {
    u16 pressed = lbl_803C77B8.pressed;
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    if (pressed & 8) {
        if (scene->bytes[12]) scene->bytes[12]--;
        else scene->bytes[12] = 8;
    } else if (pressed & 4) {
        scene->bytes[12]++;
        if (scene->bytes[12] == 9) scene->bytes[12] = 0;
    } else if (lbl_803C77B8.buttons & 0x100) {
        switch (scene->bytes[12]) {
        case 0: if (pressed & 0x100) lbl_1_bss_5F71 = 3; break;
        case 1: if (pressed & 0x100) lbl_1_bss_5F71 = 4; break;
        case 2: if (pressed & 0x100) lbl_1_bss_5F71 = 5; break;
        case 3: if (pressed & 0x100) lbl_1_bss_5F71 = 6; break;
        case 4: if (lbl_803C77B8.held & 0x100) lbl_1_bss_5F71 = 2; break;
        case 5: if (lbl_803C77B8.held & 0x100) lbl_1_bss_5F71 = 8; break;
        case 6: if (lbl_803C77B8.held & 0x100) lbl_1_bss_5F71 = 7; break;
        case 7: if (pressed & 0x100) lbl_1_bss_5F71 = 9; break;
        case 8: if (pressed & 0x100) lbl_1_bss_5F71 = 10; break;
        }
    } else if (lbl_803C77B8.held & 0x200) {
        lbl_1_bss_5F71 = 0;
        minigamesSetSomePointers();
    }
}

// .text:0x00015170 size:0x88
void fn_1_15170(void) {
    if (lbl_803C77B8.pressed & 0x200) {
        fn_800AD038(lbl_80366158.unk8);
        lbl_803CC1B8->loadingState = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_176EC;
        lbl_1_bss_30B8 = 1;
    } else if (lbl_803C77B8.pressed & 0x100) {
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x000151F8 size:0x214
/* FAKEMATCH: inline direction retains the original positive multiplication. */
static inline void adjustChallengeBlend(ChallengeState* state, f32 direction) {
    f32 step = 0.01f;
    if (lbl_803C77B8.buttons & 0x400) step *= 10.0f;
    step *= direction;
    state->blend += step;
    if (state->blend > 1.0f) state->blend = 0.0f;
    if (state->blend < 0.0f) state->blend = 1.0f;
    fn_800B9A9C(state->blendEnabled, state->blend);
}
/* Adjust the preview blend toggle/value and wrap its two-row selector. */
void fn_1_151F8(void) {
    u16 pressed = lbl_803C77B8.pressed;
    ChallengeState* state = &lbl_1_bss_3070;
    if (pressed & 8) {
        if (--state->unkC < 0) state->unkC = 1;
    } else if (pressed & 4) {
        if (++state->unkC >= 2) state->unkC = 0;
    } else if (pressed & 1) {
        switch (state->unkC) {
        case 0:
            state->blendEnabled ^= 1;
            fn_800B9A9C(state->blendEnabled, state->blend);
            break;
        case 1:
            {
                f32 step = 0.01f;
                if (lbl_803C77B8.buttons & 0x400) step *= 10.0f;
                step *= -1.0f;
                state->blend += step;
                if (state->blend > 1.0f) state->blend = 0.0f;
                if (state->blend < 0.0f) state->blend = 1.0f;
                fn_800B9A9C(state->blendEnabled, state->blend);
            }
            break;
        }
    } else if (pressed & 2) {
        switch (state->unkC) {
        case 0:
            state->blendEnabled ^= 1;
            fn_800B9A9C(state->blendEnabled, state->blend);
            break;
        case 1:
            {
                adjustChallengeBlend(state, 1.0f);
            }
            break;
        }
    } else if (pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 1;
    }
}

// .text:0x0001540C size:0x354
void fn_1_1540C(void) {
    return;
}

// .text:0x00015760 size:0x580
void fn_1_15760(void) {
    return;
}

// .text:0x00015CE0 size:0x3F8
void fn_1_15CE0(void) {
    return;
}

// .text:0x000160D8 size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) {
        return 0xFF0F;
    }
    return 0xFFFF;
}

// .text:0x000160F8 size:0xD8
void fn_1_160F8(s32 delta) {
    f32 step = 0.01f;
    if (lbl_803C77B8.buttons & 0x400) step *= 10.0f;
    step *= delta;
    lbl_1_bss_5F74 += step;
    if (lbl_1_bss_5F74 > 1.0f) lbl_1_bss_5F74 = 0.0f;
    if (lbl_1_bss_5F74 < 0.0f) lbl_1_bss_5F74 = 1.0f;
    fn_800B9A9C(lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x000161D0 size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x0001620C size:0x1F0
/* Reset the preview actor and establish its camera and overlay projections. */
void fn_1_1620C(void) {
    Mtx44 projection;
    s32 i = 0;
    do {
        g_hugeAnimStruct.fielderStructs[i].unk34.x = 0.0f;
        g_hugeAnimStruct.fielderStructs[i].unk34.y = 0.0f;
        g_hugeAnimStruct.fielderStructs[i].unk34.z = 10.0f;
        g_hugeAnimStruct.fielderStructs[i].unk40.x = 0.0f;
        g_hugeAnimStruct.fielderStructs[i].unk40.y = 0.0f;
        g_hugeAnimStruct.fielderStructs[i].unk40.z = 0.0f;
        CTRLSetTranslation(&((HugeAnimCtrlEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&((HugeAnimCtrlEntry*)g_hugeAnimStruct.ctrlOrBonePtr)[i].ctrl, 0.0f, 0.0f, 0.0f);
    } while (++i < 1);
    lbl_1_bss_67E0.pos.x = 0.0f;
    lbl_1_bss_67E0.pos.y = -0.8f;
    lbl_1_bss_67E0.pos.z = 0.0f;
    lbl_1_bss_67E0.target.x = 0.0f;
    lbl_1_bss_67E0.target.y = 0.0f;
    lbl_1_bss_67E0.target.z = 10.0f;
    C_MTXFrustum(projection, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -0.001f, 1280.0f);
    lbl_1_bss_67E0.unk_0x114 = 0;
    lbl_1_bss_67E0.unk_0xF8 = 0.0f;
    lbl_1_bss_67E0.unk_0xF0 = 0;
    lbl_1_bss_67E0.unk_0xF2 = 0;
}

// .text:0x000163FC size:0x4
void fn_1_163FC(void) {
    return;
}

// .text:0x00016400 size:0x4C
void fn_1_16400(s8 delta) {
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].ring->count + delta) %
                     g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].ring->count;
}

// .text:0x0001644C size:0x10C
void fn_1_1644C(void) {
    return;
}

// .text:0x00016558 size:0x38
s32 fn_1_16558(s32 table, s32 entry) {
    return g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].slots[table]->entries[entry].value;
}

// .text:0x00016590 size:0x50
s32 fn_1_16590(void) {
    u8 index = lbl_1_bss_5F73;
    return g_hugeAnimStruct.fielderStructs[index].slots[lbl_1_bss_6940[index].table]->entries[lbl_1_bss_6940[index].entry].value;
}

// .text:0x000165E0 size:0x2E8
/* Light header has incompatible allocator declarations in this unit. */
struct MenusLight {
    u8 _pad0[0x40];
    Vec position;
    u8 _pad4C[12];
    Vec direction;
    u8 _pad64[12];
    GXColor color;
};
void fn_1_165E0(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    struct MenusLight* light = g_hugeAnimStruct.menuLights[(s8)state->lightIndex];
    s16 step = 0;
    if (lbl_803C77B8.pressed & 1) step = -1;
    else if (lbl_803C77B8.pressed & 2) step = 1;
    else if (lbl_803C77B8.pressed & 8) {
        if (--state->unkC < 0) state->unkC = 9;
    } else if (lbl_803C77B8.pressed & 4) {
        if (++state->unkC >= 10) state->unkC = 0;
    } else if (lbl_803C77B8.held & 0x200) {
        state->lightIndex = 0;
        state->unkC = 0;
        state->unk2F01 = 1;
    }
    if (lbl_803C77B8.buttons & 0x400) step *= 10;
    switch (state->unkC) {
    case 0:
        if ((s8)(state->lightIndex += step) < 0) state->lightIndex = 2;
        else if ((s8)state->lightIndex >= 3) state->lightIndex = 0;
        break;
    case 1:
        light->color.r += step;
        if (light->color.r > 255) light->color.r = 0;
        break;
    case 2:
        light->color.g += step;
        if (light->color.g > 255) light->color.g = 0;
        break;
    case 3:
        light->color.b += step;
        if (light->color.b > 255) light->color.b = 0;
        break;
    case 4: light->position.x += step; break;
    case 5: light->position.y += step; break;
    case 6: light->position.z += step; break;
    case 7: light->direction.x += step; break;
    case 8: light->direction.y += step; break;
    case 9: light->direction.z += step; break;
    }
}

// .text:0x000168C8 size:0xB0
/* Time one challenge update, then advance the scene on the following tick. */
void fn_1_168C8(void) {
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    if (lbl_1_bss_3084 == 0) {
        lbl_1_bss_3084 = 1;
        scene->words[2] = OSGetTick();
        fn_1_135C0();
        scene->words[2] = OSGetTick() - scene->words[2];
    } else {
        lbl_1_bss_3084 = 0;
        scene->loadingState = 0;
        /* FAKEMATCH: retain the original auxiliary-data branch despite identical callbacks. */
        if (g_hugeAnimStruct.fielderStructs[0].aux->unk_0x10 != 0) {
            lbl_803CC1B8->aFunctionPointer = fn_1_1770C;
        } else {
            lbl_803CC1B8->aFunctionPointer = fn_1_1770C;
        }
    }
}

// .text:0x00016978 size:0xD74
void fn_1_16978(void) {
    return;
}

// .text:0x000176EC size:0x20
void fn_1_176EC(void) {
    fn_1_1496C();
}

// .text:0x0001770C size:0x248
void fn_1_1770C(void) {
    return;
}

// .text:0x00017954 size:0x78
void fn_1_17954(void) {
    Mtx44 proj;
    C_MTXFrustum(proj, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
}

// .text:0x000179CC size:0x190
void fn_1_179CC(void) {
    return;
}

// .text:0x00017B5C size:0x234
void fn_1_17B5C(void) {
    return;
}

// .text:0x00017D90 size:0x16C
void fn_1_17D90(void) {
    return;
}
