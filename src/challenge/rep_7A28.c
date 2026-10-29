#include "challenge/rep_7A28.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXHardware.h"
typedef struct ChallengeDebugShape {
    u8 _pad0[0x14];
    Rep7978Camera* camera;
    u8 _pad18[8];
    Vec position;
    f32 length;
    f32 scale;
    u16 flags;
    s8 choice;
} ChallengeDebugShape;
extern void (*lbl_1_data_108F0[])(void);
/* Owning headers still expose these as stubs; these are their observed call signatures. */
void fn_8003414C(Rep7978Camera* camera);
void fn_1_AF4(s32 width, s32 height, f32 scale);
void fn_1_F2C(s32 mode, s32 arg1, s32 arg2);
void GXDrawSphere1(u8 subdivisions);

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
/* Draw the debug sphere and its direction line, then invoke the selected overlay. */
void fn_1_27BB8(void) {
    Mtx transform;
    Vec endpoint;
    ChallengeDebugShape* scene = (ChallengeDebugShape*)lbl_803CC1B8;
    fn_8003414C(scene->camera);
    fn_1_272DC(scene->camera, 0);
    fn_1_AF4(20, 20, 1.0f);
    PSMTXScale(transform, scene->scale, scene->scale, scene->scale);
    PSMTXTransApply(transform, transform, scene->position.x, scene->position.y, scene->position.z);
    PSMTXConcat(scene->camera->view, transform, scene->camera->view);
    fn_1_272DC(scene->camera, 0);
    fn_1_F2C(4, 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXDrawSphere1(2);
    PSMTXTrans(transform, scene->position.x, scene->position.y, scene->position.z);
    PSMTXConcat(scene->camera->view, transform, scene->camera->view);
    fn_1_272DC(scene->camera, 0);
    fn_1_F2C(4, 0, 0);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(scene->position.x, scene->position.y, scene->position.z);
    GXColor1u32(0xFF0000FF);
    endpoint.x = 0.0f;
    endpoint.y = 0.0f;
    endpoint.z = scene->length;
    PSVECAdd(&scene->position, &endpoint, &endpoint);
    GXPosition3f32(endpoint.x, endpoint.y, endpoint.z);
    GXColor1u32(0xFF0000FF);
    lbl_1_data_108F0[scene->choice]();
    minigamesGXStuff();
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
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    scene->loadingState = 0;
    fn_800AD038(lbl_80366158.unk8);
    scene->words[0] = (u32)_OSAllocFromHeap(0x20, 0xDC);
    fn_1_273D8((Rep7978Camera*)scene->words[0]);
    scene->words[2] = (u32)_OSAllocFromHeap(0x20, sizeof(ChallengeScript));
    ((ChallengeScript*)scene->words[2])->kind = 0x10;
    ((ChallengeScript*)scene->words[2])->enabled = 1;
    ((Rep7978Camera*)scene->words[0])->up.y *= -1.0f;
    scene->parameters[3] = 0.0f;
    scene->parameters[4] = -1.0f;
    scene->parameters[5] = 0.0f;
    scene->value2C = 1.0f;
    scene->value30 = 1.0f;
    scene->choice = 0;
    scene->cursor = 0;
    scene->flags34 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_28118;
}
