#include "menus/rep_0B08.h"
#include "menus/rep_10C0.h"
#include "menus/rep_0F60.h"
#include "UnknownHeaders.h"
#include "string.h"

extern Rep0B08AnimationConfig lbl_2_data_3C84[];
extern Vec lbl_2_data_2EA4[];
extern s16 lbl_2_data_3D30[][4];
extern Vec lbl_2_data_3150[];
extern f32 lbl_2_data_3EF4[];
extern f32 lbl_2_data_3F0C[];
extern f32 lbl_2_data_3F5C;
#include "math.h"
#include "menus/rep_08E8.h"
#include "Dolphin/GX/GXTypes.h"

extern GXColor lbl_800F7478[];
extern void fn_800BD2CC(s32 enabled, GXColor color);

extern void (*lbl_2_data_2A1F4[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A200[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A208[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A210[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A220[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A234[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A248[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A250[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A25C[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A268[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A274[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A280[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A28C[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A29C[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A2AC[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A2B8[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A2C4[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A2D4[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A2E0[])(Rep0B08Obj*);

static inline void setMenuObjectActive(s32 index, u8 value) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[index];
    target->unkC0 = value;
}
static inline void setMenuObjectAlpha(s32 index, u8 value) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[index];
    target->unkCA = value;
}

static inline void menuScalePosition(Vec* source, Vec* target, f32 scale) {
    target->x = source->x * scale;
    target->y = source->y * scale;
    target->z = source->z * scale;
}

static inline void menuChangeAnimation(s32 index, s32 animation) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep0B08AnimationConfig* configs = lbl_2_data_3C84;
    if (lbl_2_bss_1A824C->animations[obj->index] != animation) {
        fn_2_8CD58(obj->index, configs[animation].animation, configs[animation].flag, 1, configs[animation].time, 0, 0);
        lbl_2_bss_1A824C->animations[obj->index] = animation;
    }
}

extern s16 lbl_2_data_2E80[][3];
extern void fn_80062890(s32 value);
static inline void menuCheckAnimationEnd(Rep0B08Obj* obj) {
    u32 mode = lbl_2_bss_1A8248->unk441C;
    s32 full = lbl_2_data_2E80[mode][0] * 2;
    s32 end = full - lbl_2_data_2E80[mode][2] * 2;
    s32 start = full - lbl_2_data_2E80[mode][1] * 2;
    if (obj->index == 0) {
        AnimationStruct* anim = &g_hugeAnimStruct.fielderStructs[0];
        if (anim && (anim->unk68 == end || anim->unk68 == start)) {
            if (mode == 5) fn_80062890(1);
            else fn_80062890(0);
        }
    }
}

// .text:0x0006832C size:0xC0
void fn_2_6832C(void) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[1];
    memcpy(&obj->position, &lbl_2_data_2EA4[5], sizeof(Vec));
    obj->previousPosition.x = 0.0f;
    obj->previousPosition.y = 0.0f;
    obj->previousPosition.z = 0.0f;
    obj->velocity.x = 0.0f;
    obj->velocity.y = 0.0f;
    obj->velocity.z = 0.0f;
    obj->unk6C = obj->position.x;
    obj->unk70 = obj->position.z;
    obj->unk38 = 0.0f;
    obj->unkBB = 0;
    obj->unk30 = obj->unk34 = obj->angle;
    lbl_2_bss_1A8248->rep0B08Objects[1].unkB2 = 5;
    {
        Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[1];
        target->variant = 6;
        target->state = 0;
    }
    lbl_2_bss_1A8248->unk442F = 1;
}

// .text:0x000683EC size:0xE4
void fn_2_683EC(void) {
    Rep0B08Obj* obj;
    {
        MenusSceneState* scene = lbl_2_bss_1A8248;
        scene->rep0B08Objects[1].position.x = scene->rep0B08Objects[0].position.x;
        scene->rep0B08Objects[1].position.y = scene->rep0B08Objects[0].position.y;
        scene->rep0B08Objects[1].position.z = scene->rep0B08Objects[0].position.z;
    }
    obj = &lbl_2_bss_1A8248->rep0B08Objects[1];
    memcpy(&obj->position, &lbl_2_data_2EA4[lbl_2_bss_1A8248->rep0B08Objects[0].unkB2], sizeof(Vec));
    obj->previousPosition.x = 0.0f;
    obj->previousPosition.y = 0.0f;
    obj->previousPosition.z = 0.0f;
    obj->velocity.x = 0.0f;
    obj->velocity.y = 0.0f;
    obj->velocity.z = 0.0f;
    obj->unk6C = obj->position.x;
    obj->unk70 = obj->position.z;
    obj->unk38 = 0.0f;
    obj->unkBB = 0;
    obj->unk30 = obj->unk34 = obj->angle;
    lbl_2_bss_1A8248->rep0B08Objects[1].unkB2 = lbl_2_bss_1A8248->rep0B08Objects[0].unkB2;
    {
        Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[1];
        target->variant = 6;
        target->state = 0;
    }
    lbl_2_bss_1A8248->unk442F = 1;
}

// .text:0x000684D0 size:0x168
void fn_2_684D0(void) {
    return;
}

// .text:0x00068638 size:0x1C
void fn_2_68638(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkCE = value;
}

// .text:0x00068654 size:0x1C
void fn_2_68654(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkCD = value;
}

// .text:0x00068670 size:0x20
s32 fn_2_68670(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    return obj->unkCD;
}

// .text:0x00068690 size:0x20
s32 fn_2_68690(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    return obj->unkCC;
}

// .text:0x000686B0 size:0x20
s32 fn_2_686B0(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    return obj->unkCB;
}

// .text:0x000686D0 size:0x1C
void fn_2_686D0(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkCF = value;
}

// .text:0x000686EC size:0xB8
BOOL fn_2_686EC(s32 firstIndex, s32 secondIndex) {
    Rep0B08Obj* first = &lbl_2_bss_1A8248->rep0B08Objects[firstIndex];
    Rep0B08Obj* second = &lbl_2_bss_1A8248->rep0B08Objects[secondIndex];
    f32 dx = second->position.x - first->position.x;
    f32 dz = second->position.z - first->position.z;
    f32 angle = (f32)atan2(-dx, -dz);
    f32 difference = fn_2_4A18C(first->angle) - angle;
    if (difference < 1.2217306f && difference > -1.2217306f) return 1;
    return 0;
}

// .text:0x000687A4 size:0x100
s32 fn_2_687A4(s32 index, s32 otherIndex, s32 positionIndex) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep0B08Obj* other = &lbl_2_bss_1A8248->rep0B08Objects[otherIndex];
    Vec position;
    f32 angle = (f32)atan2(-(other->position.x - obj->position.x), -(other->position.z - obj->position.z));
    memcpy(&position, &lbl_2_data_2EA4[positionIndex], sizeof(Vec));
    angle -= (f32)atan2(-(position.x - obj->position.x), -(position.z - obj->position.z));
    if (angle < 1.2217306f && angle > -1.2217306f) return 1;
    return 0;
}

// .text:0x000688A4 size:0x9C
f32 fn_2_688A4(s32 index, s32 target) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Vec pos;
    f32 x, z, angle;
    memcpy(&pos, &lbl_2_data_2EA4[target], sizeof(Vec));
    x = pos.x - obj->position.x;
    z = pos.z - obj->position.z;
    angle = (f32)atan2(-x, -z);
    return fn_2_4A18C(obj->angle) - angle;
}

// .text:0x00068940 size:0x8C
f32 fn_2_68940(s32 firstIndex, s32 secondIndex) {
    Rep0B08Obj* first = &lbl_2_bss_1A8248->rep0B08Objects[firstIndex];
    Rep0B08Obj* second = &lbl_2_bss_1A8248->rep0B08Objects[secondIndex];
    f32 dx = second->position.x - first->position.x;
    f32 dz = second->position.z - first->position.z;
    f32 angle = (f32)atan2(-dx, -dz);
    return fn_2_4A18C(first->angle) - angle;
}

// .text:0x000689CC size:0xBC
s16 fn_2_689CC(s32 index) {
    Vec position;
    Vec target;
    f32 best = 10000.0f;
    s32 i;
    s32 closest = 0;
    memcpy(&position, &lbl_2_bss_1A8248->rep0B08Objects[index].position, sizeof(Vec));
    for (i = 0; i < 51; i++) {
        f32 distance;
        memcpy(&target, &lbl_2_data_2EA4[i], sizeof(Vec));
        distance = PSVECDistance(&position, &target);
        if (distance < best) {
            best = distance;
            closest = i;
        }
    }
    return closest;
}

// .text:0x00068A88 size:0xCC
BOOL fn_2_68A88(s32 index, s32 targetIndex) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[targetIndex];
    Vec position;
    f32 distance;
    f32 radius;
    menuScalePosition(&target->position, &position, 0.5f);
    distance = PSVECDistance(&obj->position, &position);
    radius = lbl_2_data_3EF4[lbl_2_bss_1A8248->unk441C];
    if (distance < radius + lbl_2_data_3F5C && obj->unkC0) return 1;
    return 0;
}

// .text:0x00068B54 size:0x12C
void fn_2_68B54(void) {
    return;
}

// .text:0x00068C80 size:0x110
BOOL fn_2_68C80(s32 firstIndex, s32 secondIndex) {
    Rep0B08Obj* first = &lbl_2_bss_1A8248->rep0B08Objects[firstIndex];
    Rep0B08Obj* second = &lbl_2_bss_1A8248->rep0B08Objects[secondIndex];
    f32 a;
    f32 b;
    f32 distance = PSVECDistance(&first->position, &second->position);
    if (firstIndex == 0) {
        a = lbl_2_data_3EF4[lbl_2_bss_1A8248->unk441C];
        b = lbl_2_data_3F0C[secondIndex];
    } else {
        a = lbl_2_data_3F0C[firstIndex];
        b = lbl_2_data_3EF4[lbl_2_bss_1A8248->unk441C];
    }
    if (distance < a + b && first->unkC0 != 0 && second->unkC0 != 0) return TRUE;
    return FALSE;
}

// .text:0x00068D90 size:0x1C
void fn_2_68D90(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkCA = value;
}

// .text:0x00068DAC size:0x3C
void fn_2_68DAC(s32 index, Vec* out) {
    memcpy(out, &lbl_2_bss_1A8248->rep0B08Objects[index].position, sizeof(Vec));
}

// .text:0x00068DE8 size:0x80
void fn_2_68DE8(s32 index, Vec* out) {
    if (index != -1) {
        memcpy(out, &lbl_2_bss_1A8248->rep0B08Objects[index].position, sizeof(Vec));
        PSVECScale(out, 2.0f, out);
    } else {
        out->z = 0.0f;
        out->y = 0.0f;
        out->x = 0.0f;
    }
}

// .text:0x00068E68 size:0xA0
void fn_2_68E68(void) {
    Rep0B08Obj* obj;
    AnimationStruct* anim;
    s32 i;
    for (i = 0; i < lbl_2_bss_1A824C->objectCount; i++) {
        anim = &g_hugeAnimStruct.fielderStructs[i];
        obj = &lbl_2_bss_1A8248->rep0B08Objects[i];
        memcpy(&anim->unk34, &obj->position, sizeof(Vec));
        anim->unk40.y = obj->angle;
        anim->unk_25D = obj->unkC0;
        anim->unk277 = obj->unkCA;
    }
}

// .text:0x00068F08 size:0x1C
void fn_2_68F08(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkC0 = value;
}

// .text:0x00068F24 size:0x98
void fn_2_68F24(s32 index, s32 animation) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep0B08AnimationConfig* config = &lbl_2_data_3C84[animation];
    fn_2_8CD58(obj->index, config->animation, config->flag, 1, config->time, 0, 0);
    lbl_2_bss_1A824C->animations[obj->index] = animation;
}

// .text:0x00068FBC size:0xB4
void fn_2_68FBC(s32 index, s32 animation) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep0B08AnimationConfig* config = &lbl_2_data_3C84[animation];
    if (lbl_2_bss_1A824C->animations[obj->index] != animation) {
        fn_2_8CD58(obj->index, config->animation, config->flag, 1, config->time, 0, 0);
        lbl_2_bss_1A824C->animations[obj->index] = animation;
    }
}

// .text:0x00069070 size:0x260
void fn_2_69070(void) {
    return;
}

// .text:0x000692D0 size:0x284
void fn_2_692D0(void) {
    return;
}

// .text:0x00069554 size:0x180
void fn_2_69554(void) {
    return;
}

// .text:0x000696D4 size:0x3C
void fn_2_696D4(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    if (obj->unkA0 != 0) {
        obj->unk38 = obj->unk3C;
    } else {
        obj->unk38 = 0.0f;
    }
}

// .text:0x00069710 size:0x1DC
void fn_2_69710(void) {
    return;
}

// .text:0x000698EC size:0xE8
void fn_2_698EC(void) {
    return;
}

// .text:0x000699D4 size:0x448
void fn_2_699D4(void) {
    return;
}

// .text:0x00069E1C size:0x634
void fn_2_69E1C(s32 index) {
    return;
}

// .text:0x0006A450 size:0x158
void fn_2_6A450(void) {
    return;
}

// .text:0x0006A5A8 size:0x80
void fn_2_6A5A8(s32 index) {
    lbl_2_bss_1A8248->rep0B08Objects[index].previousPosition.x = lbl_2_bss_1A8248->rep0B08Objects[index].position.x;
    lbl_2_bss_1A8248->rep0B08Objects[index].previousPosition.y = lbl_2_bss_1A8248->rep0B08Objects[index].position.y;
    lbl_2_bss_1A8248->rep0B08Objects[index].previousPosition.z = lbl_2_bss_1A8248->rep0B08Objects[index].position.z;
    lbl_2_bss_1A8248->rep0B08Objects[index].velocity.x = 0.0f;
    lbl_2_bss_1A8248->rep0B08Objects[index].velocity.y = 0.0f;
    lbl_2_bss_1A8248->rep0B08Objects[index].velocity.z = 0.0f;
    lbl_2_bss_1A8248->rep0B08Objects[index].unk38 = 0.0f;
    lbl_2_bss_1A8248->rep0B08Objects[index].unk50 = 0.0f;
}

// .text:0x0006A628 size:0xE0
void fn_2_6A628(void) {
    Mtx matrix;
    Vec velocity;
    MenusSceneState* scene = lbl_2_bss_1A8248;
    if (!(scene->rep0B08Objects[0].unk38 <= 0.0f)) {
        PSMTXRotRad(matrix, 'Y', scene->rep0B08Objects[0].angle);
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        velocity.z = -scene->rep0B08Objects[0].unk38;
        PSMTXMultVec(matrix, &velocity, &velocity);
        scene->rep0B08Objects[0].velocity.x = velocity.x;
        scene->rep0B08Objects[0].velocity.z = velocity.z;
        scene->rep0B08Objects[0].position.x += scene->rep0B08Objects[0].velocity.x;
        scene->rep0B08Objects[0].position.z += scene->rep0B08Objects[0].velocity.z;
    }
    scene->rep0B08Objects[0].previousPosition.x = scene->rep0B08Objects[0].position.x;
    scene->rep0B08Objects[0].previousPosition.z = scene->rep0B08Objects[0].position.z;
    if (0.0f == scene->rep0B08Objects[0].unk38) {
        scene->rep0B08Objects[0].acceleration.x = 0.0f;
        scene->rep0B08Objects[0].acceleration.z = 0.0f;
    }
}

// .text:0x0006A708 size:0x174
void fn_2_6A708(void) {
    return;
}

// .text:0x0006A87C size:0x23C
void fn_2_6A87C(void) {
    return;
}

// .text:0x0006AAB8 size:0x4
void fn_2_6AAB8(void) {
    return;
}

// .text:0x0006AABC size:0x80
void fn_2_6AABC(s32 index, Vec* position) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    memcpy(&obj->position, position, sizeof(Vec));
    obj->previousPosition.x = 0.0f;
    obj->previousPosition.y = 0.0f;
    obj->previousPosition.z = 0.0f;
    obj->velocity.x = 0.0f;
    obj->velocity.y = 0.0f;
    obj->velocity.z = 0.0f;
    obj->unk6C = obj->position.x;
    obj->unk70 = obj->position.z;
    obj->unk38 = 0.0f;
    obj->unkBB = 0;
}

// .text:0x0006AB3C size:0xC0
void fn_2_6AB3C(s32 index, Vec* position, f32 angle) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    f32 dx, dz;
    memcpy(&obj->position, position, sizeof(Vec));
    obj->previousPosition.x = 0.0f;
    obj->previousPosition.y = 0.0f;
    obj->previousPosition.z = 0.0f;
    obj->velocity.x = 0.0f;
    obj->velocity.y = 0.0f;
    obj->velocity.z = 0.0f;
    obj->unk30 = angle;
    obj->unk6C = obj->position.x;
    obj->unk70 = obj->position.z;
    obj->unk38 = 0.0f;
    obj->unkBB = 0;
    dx = -obj->position.x;
    dz = -obj->position.z;
    obj->unk30 = obj->unk34 = (f32)atan2(-dx, -dz);
}

// .text:0x0006ABFC size:0xF4
void fn_2_6ABFC(s32 index, s32 position) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    if (index < 2) {
        memcpy(&obj->position, &lbl_2_data_2EA4[position], sizeof(Vec));
    } else if (index >= 2 && index <= 6) {
        memcpy(&obj->position, &lbl_2_data_2EA4[position], sizeof(Vec));
    } else {
        memcpy(&obj->position, &lbl_2_data_3150[index - 7], sizeof(Vec));
    }
    obj->previousPosition.x = 0.0f;
    obj->previousPosition.y = 0.0f;
    obj->previousPosition.z = 0.0f;
    obj->velocity.x = 0.0f;
    obj->velocity.y = 0.0f;
    obj->velocity.z = 0.0f;
    obj->unk6C = obj->position.x;
    obj->unk70 = obj->position.z;
    obj->unk38 = 0.0f;
    obj->unkBB = 0;
    obj->unk30 = obj->unk34 = obj->angle;
}

// .text:0x0006ACF0 size:0x4
void fn_2_6ACF0(void) {
    return;
}

// .text:0x0006ACF4 size:0x114
void fn_2_6ACF4(void) {
    Rep0B08Obj* obj;
    s32 i;
    for (i = 0; i < 8; i++) {
        obj = &lbl_2_bss_1A8248->rep0B08Objects[i];
        obj->index = i;
        obj->animationIndex = i;
        obj->unk8C = 0.0f;
        obj->unkB6 = 10;
        obj->unk40 = 0.0003f * obj->unkB6 + 0.1f;
        obj->unkB8 = 10;
        obj->unkB7 = 15;
        obj->unk44 = obj->unk40 / obj->unkB7;
        obj->unkBB = 0;
        obj->unkC0 = 0;
        obj->unk96 = i;
        obj->unk98 = -1;
        obj->unkBC = 1;
        obj->variant = 0;
        obj->state = 0;
        obj->unkC6 = -1;
        obj->unkC4 = 0;
        obj->unkC5 = 0;
        obj->unk88 = 0.0f;
        obj->unkC1 = 0;
        obj->unkAC = 0;
        obj->unkCA = 255;
        obj->unkCB = -1;
        obj->unkCC = -1;
    }
}

// .text:0x0006AE08 size:0x178
void fn_2_6AE08(void) {
    return;
}

// .text:0x0006AF80 size:0x1C
void fn_2_6AF80(s32 index, u8 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkC4 = value;
}

// .text:0x0006AF9C size:0x38
BOOL fn_2_6AF9C(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    if (obj->unkD0 == 0) {
        obj->unkD0 = 0;
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006AFD4 size:0x50
s32 fn_2_6AFD4(s32 index) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    if (obj->unkC4 == 1) {
        obj->unkC4 = 0;
        return 1;
    }
    if (obj->unkC4 == 2) {
        obj->unkC4 = 0;
        return 2;
    }
    return 0;
}

// .text:0x0006B024 size:0xFC
void fn_2_6B024(void) {
    return;
}

// .text:0x0006B120 size:0x118
void fn_2_6B120(void) {
    return;
}

// .text:0x0006B238 size:0x28C
void fn_2_6B238(void) {
    return;
}

// .text:0x0006B4C4 size:0x38
void fn_2_6B4C4(Rep0B08Obj* obj) {
    lbl_2_data_2A2E0[obj->state](obj);
}

// .text:0x0006B4FC size:0x124
void fn_2_6B4FC(void) {
    return;
}

// .text:0x0006B620 size:0x124
void fn_2_6B620(void) {
    return;
}

// .text:0x0006B744 size:0x2D4
void fn_2_6B744(void) {
    return;
}

// .text:0x0006BA18 size:0x38
void fn_2_6BA18(Rep0B08Obj* obj) {
    lbl_2_data_2A2D4[obj->state](obj);
}

// .text:0x0006BA50 size:0x5C
void fn_2_6BA50(Rep0B08Obj* obj) {
    GXColor color = lbl_800F7478[10];
    color.a = 255;
    fn_800BD2CC(0, color);
    obj->state = 2;
}

// .text:0x0006BAAC size:0x2C
void fn_2_6BAAC(Rep0B08Obj* obj) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[obj->index];
    target->unkCA = 0xFF;
    obj->state = 3;
}

// .text:0x0006BAD8 size:0xA4
void fn_2_6BAD8(Rep0B08Obj* obj) {
    s32 alpha;
    obj->unk8C -= 0.1;
    alpha = 255.0f * obj->unk8C;
    if (alpha > 1) {
        setMenuObjectAlpha(obj->index, alpha);
    } else {
        setMenuObjectAlpha(obj->index, 0);
        setMenuObjectActive(obj->index, 0);
        obj->state = 2;
    }
}

// .text:0x0006BB7C size:0x4C
void fn_2_6BB7C(Rep0B08Obj* obj) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[obj->index];
    target->unkC0 = 1;
    target = &lbl_2_bss_1A8248->rep0B08Objects[obj->index];
    target->unkCA = 255;
    obj->unk8C = 1.0f;
    obj->state = 1;
}

// .text:0x0006BBC8 size:0x38
void fn_2_6BBC8(Rep0B08Obj* obj) {
    lbl_2_data_2A2C4[obj->state](obj);
}

// .text:0x0006BC00 size:0xC
void fn_2_6BC00(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x0006BC0C size:0xA0
void fn_2_6BC0C(Rep0B08Obj* obj) {
    s32 alpha;
    setMenuObjectActive(obj->index, 1);
    obj->unk8C += 0.1;
    alpha = 256.0f * obj->unk8C;
    if (alpha < 255) {
        setMenuObjectAlpha(obj->index, alpha);
    } else {
        setMenuObjectAlpha(obj->index, 255);
        obj->state = 2;
    }
}

// .text:0x0006BCAC size:0xF0
static inline void menuForceAnimation(s32 index, s32 animation) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    Rep0B08AnimationConfig* configs = lbl_2_data_3C84;
    fn_2_8CD58(obj->index, configs[animation].animation, configs[animation].flag, 1, configs[animation].time, 0, 0);
    lbl_2_bss_1A824C->animations[obj->index] = animation;
}
void fn_2_6BCAC(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 0);
    menuForceAnimation(obj->index, 9);
    obj->angle = 0.0f;
    obj->unk34 = 0.0f;
    setMenuObjectAlpha(obj->index, 255);
    obj->unk8C = 0.0f;
    obj->state = 1;
}

// .text:0x0006BD9C size:0x38
void fn_2_6BD9C(Rep0B08Obj* obj) {
    lbl_2_data_2A2B8[obj->state](obj);
}

// .text:0x0006BDD4 size:0xC
void fn_2_6BDD4(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x0006BDE0 size:0xA0
void fn_2_6BDE0(Rep0B08Obj* obj) {
    s32 alpha;
    setMenuObjectActive(obj->index, 1);
    obj->unk8C += 0.1;
    alpha = 256.0f * obj->unk8C;
    if (alpha < 255) {
        setMenuObjectAlpha(obj->index, alpha);
    } else {
        setMenuObjectAlpha(obj->index, 255);
        obj->state = 2;
    }
}

// .text:0x0006BE80 size:0x108
void fn_2_6BE80(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 0);
    menuChangeAnimation(obj->index, 1);
    setMenuObjectAlpha(obj->index, 255);
    obj->unk8C = 0.0f;
    obj->state = 1;
}

// .text:0x0006BF88 size:0x38
void fn_2_6BF88(Rep0B08Obj* obj) {
    lbl_2_data_2A2AC[obj->state](obj);
}

// .text:0x0006BFC0 size:0x60
void fn_2_6BFC0(Rep0B08Obj* obj) {
    if ((f32)fabs(PSVECDistance(&lbl_2_bss_1A8248->rep0B08Objects[0].position, &obj->position)) > 1.6f) {
        obj->state = 1;
    }
}

// .text:0x0006C020 size:0x100
void fn_2_6C020(Rep0B08Obj* obj) {
    f32 difference;
    obj->angle = (f32)atan2(-(lbl_2_bss_1A8248->rep0B08Objects[0].position.x - obj->position.x), -(lbl_2_bss_1A8248->rep0B08Objects[0].position.z - obj->position.z));
    difference = fn_2_4A18C(obj->unk34 - obj->angle);
    if ((difference < 0.02 && difference > 0.0f) || (difference > -0.02 && difference < 0.0f)) {
        obj->state = 3;
    } else if (difference < 0.0f) {
        obj->unk34 += 0.05235988f;
    } else {
        obj->unk34 -= 0.05235988f;
    }
    obj->angle = obj->unk34;
}

// .text:0x0006C120 size:0x70
void fn_2_6C120(Rep0B08Obj* obj) {
    f32 distance = (f32)fabs(PSVECDistance(&lbl_2_bss_1A8248->rep0B08Objects[0].position, &obj->position));
    if (distance < 1.6f && 0.0f != distance) obj->state = 2;
}

// .text:0x0006C190 size:0xFC
void fn_2_6C190(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 1);
    menuChangeAnimation(obj->index, 1);
    obj->unk34 = obj->angle;
    fn_2_46C88(lbl_2_bss_1A8248->unk441E, 0);
    obj->state = 1;
}

// .text:0x0006C28C size:0x38
void fn_2_6C28C(Rep0B08Obj* obj) {
    lbl_2_data_2A29C[obj->state](obj);
}

// .text:0x0006C2C4 size:0x24
void fn_2_6C2C4(void) {
    Rep0B08Obj* obj;
    lbl_2_bss_1A8248->unk442F = 0;
    obj = &lbl_2_bss_1A8248->rep0B08Objects[1];
    obj->variant = 0;
    obj->state = 0;
}

// .text:0x0006C2E8 size:0x60
void fn_2_6C2E8(Rep0B08Obj* obj) {
    fn_2_69E1C(obj->index);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->state = 3;
    }
}

// .text:0x0006C348 size:0x298
void fn_2_6C348(void) {
    return;
}

// .text:0x0006C5E0 size:0x358
void fn_2_6C5E0(void) {
    return;
}

// .text:0x0006C938 size:0x38
void fn_2_6C938(Rep0B08Obj* obj) {
    lbl_2_data_2A28C[obj->state](obj);
}

// .text:0x0006C970 size:0xC
void fn_2_6C970(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x0006C97C size:0xC
void fn_2_6C97C(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x0006C988 size:0x1F0
void fn_2_6C988(void) {
    return;
}

// .text:0x0006CB78 size:0x38
void fn_2_6CB78(Rep0B08Obj* obj) {
    lbl_2_data_2A280[obj->state](obj);
}

// .text:0x0006CBB0 size:0x108
void fn_2_6CBB0(Rep0B08Obj* obj) {
    s32 index = obj->index;
    fn_2_69E1C(index);
    menuCheckAnimationEnd(obj);
    if (obj->unk38 <= 0.0f) {
        Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[index];
        target->variant = 3;
        target->state = 0;
    }
}

// .text:0x0006CCB8 size:0x11C
void fn_2_6CCB8(Rep0B08Obj* obj) {
    s32 i;
    fn_2_69E1C(obj->index);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        for (i = 0; i < 4; i++) {
            if (lbl_2_bss_1A8248->rep0B08Objects[0].unkB0 == lbl_2_data_3D30[lbl_2_bss_1A8248->rep0B08Objects[0].unkB2][i]) lbl_2_bss_1A8248->unk4448 = i;
        }
        lbl_2_bss_1A8248->rep0B08Objects[0].unkB2 = lbl_2_bss_1A8248->rep0B08Objects[0].unkB0;
        obj->state = 2;
    }
}

// .text:0x0006CDD4 size:0x26C
void fn_2_6CDD4(void) {
    return;
}

// .text:0x0006D040 size:0x38
void fn_2_6D040(Rep0B08Obj* obj) {
    lbl_2_data_2A274[obj->state](obj);
}

// .text:0x0006D078 size:0x10
void fn_2_6D078(Rep0B08Obj* obj) {
    obj->countdown--;
}

// .text:0x0006D088 size:0xDC
void fn_2_6D088(Rep0B08Obj* obj) {
    if (fn_2_8CC88(obj->animationIndex)) {
        menuChangeAnimation(obj->index, 7);
        obj->countdown = 30;
        obj->state = 2;
    }
}

// .text:0x0006D164 size:0xEC
void fn_2_6D164(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 1);
    obj->unk34 = 0.0f;
    obj->angle = 0.0f;
    menuChangeAnimation(obj->index, 4);
    obj->state = 1;
}

// .text:0x0006D250 size:0x38
void fn_2_6D250(Rep0B08Obj* obj) {
    lbl_2_data_2A268[obj->state](obj);
}

// .text:0x0006D288 size:0x10
void fn_2_6D288(Rep0B08Obj* obj) {
    obj->countdown--;
}

// .text:0x0006D298 size:0xDC
void fn_2_6D298(Rep0B08Obj* obj) {
    if (fn_2_8CC88(obj->animationIndex)) {
        menuChangeAnimation(obj->index, 6);
        obj->countdown = 30;
        obj->state = 2;
    }
}

// .text:0x0006D374 size:0x13C
void fn_2_6D374(void) {
    return;
}

// .text:0x0006D4B0 size:0x38
void fn_2_6D4B0(Rep0B08Obj* obj) {
    lbl_2_data_2A25C[obj->state](obj);
}

// .text:0x0006D4E8 size:0x10
void fn_2_6D4E8(Rep0B08Obj* obj) {
    obj->countdown--;
}

// .text:0x0006D4F8 size:0xDC
void fn_2_6D4F8(Rep0B08Obj* obj) {
    if (fn_2_8CC88(obj->animationIndex)) {
        menuChangeAnimation(obj->index, 5);
        obj->countdown = 30;
        obj->state = 2;
    }
}

// .text:0x0006D5D4 size:0x13C
void fn_2_6D5D4(void) {
    return;
}

// .text:0x0006D710 size:0x38
void fn_2_6D710(Rep0B08Obj* obj) {
    lbl_2_data_2A250[obj->state](obj);
}

// .text:0x0006D748 size:0xC
void fn_2_6D748(Rep0B08Obj* obj) {
    obj->state = 1;
}

// .text:0x0006D754 size:0xEC
void fn_2_6D754(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 1);
    menuChangeAnimation(obj->index, 1);
    obj->angle = 0.0f;
    obj->unk34 = 0.0f;
    obj->state = 1;
}

// .text:0x0006D840 size:0x38
void fn_2_6D840(Rep0B08Obj* obj) {
    lbl_2_data_2A248[obj->state](obj);
}

// .text:0x0006D878 size:0xF0
void fn_2_6D878(Rep0B08Obj* obj) {
    s32 index = obj->index;
    if (lbl_2_bss_1A8248->rep0B08Objects[0].unkCD == 0) {
        obj->countdown = 120;
        menuChangeAnimation(index, 1);
        obj->unkBA = 9;
        obj->unk50 = 0.0f;
        obj->unk38 = 0.0f;
        obj->state = 2;
    }
}

// .text:0x0006D968 size:0x1C8
void fn_2_6D968(void) {
    return;
}

// .text:0x0006DB30 size:0x324
void fn_2_6DB30(void) {
    return;
}

// .text:0x0006DE54 size:0x37C
void fn_2_6DE54(void) {
    return;
}

// .text:0x0006E1D0 size:0x678
void fn_2_6E1D0(void) {
    return;
}

// .text:0x0006E848 size:0x38
void fn_2_6E848(Rep0B08Obj* obj) {
    lbl_2_data_2A234[obj->state](obj);
}

// .text:0x0006E880 size:0xC
void fn_2_6E880(Rep0B08Obj* obj) {
    obj->state = 4;
}

// .text:0x0006E88C size:0x1E8
void fn_2_6E88C(void) {
    return;
}

// .text:0x0006EA74 size:0x2BC
void fn_2_6EA74(void) {
    return;
}

// .text:0x0006ED30 size:0x3D4
void fn_2_6ED30(void) {
    return;
}

// .text:0x0006F104 size:0x5F0
void fn_2_6F104(void) {
    return;
}

// .text:0x0006F6F4 size:0x38
void fn_2_6F6F4(Rep0B08Obj* obj) {
    lbl_2_data_2A220[obj->state](obj);
}

// .text:0x0006F72C size:0x60
void fn_2_6F72C(Rep0B08Obj* obj) {
    if ((f32)fabs(PSVECDistance(&lbl_2_bss_1A8248->rep0B08Objects[0].position, &obj->position)) > 1.6f) {
        obj->state = 1;
    }
}

// .text:0x0006F78C size:0x100
void fn_2_6F78C(Rep0B08Obj* obj) {
    f32 difference;
    obj->angle = (f32)atan2(-(lbl_2_bss_1A8248->rep0B08Objects[0].position.x - obj->position.x), -(lbl_2_bss_1A8248->rep0B08Objects[0].position.z - obj->position.z));
    difference = fn_2_4A18C(obj->unk34 - obj->angle);
    if ((difference < 0.02 && difference > 0.0f) || (difference > -0.02 && difference < 0.0f)) {
        obj->state = 3;
    } else if (difference < 0.0f) {
        obj->unk34 += 0.05235988f;
    } else {
        obj->unk34 -= 0.05235988f;
    }
    obj->angle = obj->unk34;
}

// .text:0x0006F88C size:0x280
void fn_2_6F88C(void) {
    return;
}

// .text:0x0006FB0C size:0x328
void fn_2_6FB0C(void) {
    return;
}

// .text:0x0006FE34 size:0x38
void fn_2_6FE34(Rep0B08Obj* obj) {
    lbl_2_data_2A210[obj->state](obj);
}

// .text:0x0006FE6C size:0x2A4
void fn_2_6FE6C(void) {
    return;
}

// .text:0x00070110 size:0x34C
void fn_2_70110(void) {
    return;
}

// .text:0x0007045C size:0x38
void fn_2_7045C(Rep0B08Obj* obj) {
    lbl_2_data_2A208[obj->state](obj);
}

// .text:0x00070494 size:0xC
void fn_2_70494(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x000704A0 size:0xC
void fn_2_704A0(Rep0B08Obj* obj) {
    obj->state = 2;
}

// .text:0x000704AC size:0xDC
void fn_2_704AC(Rep0B08Obj* obj) {
    setMenuObjectActive(obj->index, 1);
    menuChangeAnimation(obj->index, 1);
    obj->state = 1;
}

// .text:0x00070588 size:0x38
void fn_2_70588(Rep0B08Obj* obj) {
    lbl_2_data_2A200[obj->state](obj);
}

// .text:0x000705C0 size:0x3E0
void fn_2_705C0(void) {
    return;
}

// .text:0x000709A0 size:0x6F8
void fn_2_709A0(void) {
    return;
}

// .text:0x00071098 size:0x9A0
void fn_2_71098(void) {
    return;
}

// .text:0x00071A38 size:0x38
void fn_2_71A38(Rep0B08Obj* obj) {
    lbl_2_data_2A1F4[obj->state](obj);
}

// .text:0x00071A70 size:0x110
void fn_2_71A70(Rep0B08Obj* obj) {
    s32 index = obj->index;
    fn_2_69E1C(index);
    menuCheckAnimationEnd(obj);
    if (obj->unk38 <= 0.0f) {
        Rep0B08Obj* target;
        obj->unk34 = obj->angle;
        target = &lbl_2_bss_1A8248->rep0B08Objects[index];
        target->variant = 3;
        target->state = 0;
    }
}

// .text:0x00071B80 size:0xEC
void fn_2_71B80(Rep0B08Obj* obj) {
    fn_2_69E1C(obj->index);
    menuCheckAnimationEnd(obj);
    if (obj->unk50 <= 0.0f) {
        obj->unkBA = 4;
        obj->unkC4 = 1;
        obj->state = 2;
    }
}

// .text:0x00071C6C size:0x258
void fn_2_71C6C(void) {
    return;
}
