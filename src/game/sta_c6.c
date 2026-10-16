#include "game/sta_c6.h"
#include "game/rep_1D58.h"
#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"
#include "stl/mem.h"
#include "header_rep_data.h"

extern long rand(void);
extern u32 lbl_3_data_19018[3];
extern u8 lbl_3_bss_AE80[8];

typedef struct StaC6PlacedObj {
    /* 0x00 */ VecXYZ pos;
    /* 0x0C */ f32 rotY;
    /* 0x10 */ u8 _pad10[0x4];
} StaC6PlacedObj; // size: 0x14

typedef struct StaC6Bss_AEB4 {
    /* 0x00 */ StaC6PlacedObj* objs;
    /* 0x04 */ u8 _pad4[0x28];
} StaC6Bss_AEB4;

extern StaC6Bss_AEB4 lbl_3_bss_AEB4;
extern VecXYZ lbl_3_data_19644[7];
extern f32 lbl_3_data_19698[7];

// .text:0x000E59B4 size:0x68 mapped:0x80724A48
void fn_3_E59B4(ActorObject *arg0) {
    void *boneData = arg0->wrapper->boneData;
    if (lbl_3_rodata_2B90 + fn_800B4C40(boneData) > lbl_3_rodata_2B94) {
        fn_800B4CA0(boneData, lbl_3_rodata_2B98);
    }
    AnimateActorBones(boneData);
}

// .text:0x000E5A1C size:0x68 mapped:0x80724AB0
void fn_3_E5A1C(ActorObject *arg0) {
    void *boneData = arg0->wrapper->boneData;
    if (lbl_3_rodata_2B90 + fn_800B4C40(boneData) > lbl_3_rodata_2B9C) {
        fn_800B4CA0(boneData, lbl_3_rodata_2BA0);
    }
    AnimateActorBones(boneData);
}

// .text:0x000E5A84 size:0x238 mapped:0x80724B18
void fn_3_E5A84(void) {
    return;
}

// .text:0x000E5CBC size:0x158 mapped:0x80724D50
void fn_3_E5CBC(void) {
    return;
}

// .text:0x000E5E14 size:0x5C mapped:0x80724EA8
int fn_3_E5E14(Arg0_E5E14* arg0) {
    u8 nibble = (u8)(arg0->unk4->unk6 >> 4);
    switch (nibble) {
    case 0:
    case 3:
        return 2;
    case 5:
        return 4;
    case 1:
    case 2:
    case 4:
        return 3;
    default:
        return 0;
    }
}

// .text:0x000E5E70 size:0x17C mapped:0x80724F04
void fn_3_E5E70(StaC6Color* out, u32 fmt, StaC6Texel* src) {
    s32 type = (fmt >> 4) & 0xF;

    if (out == NULL || src == NULL) {
        return;
    }
    switch (type) {
    case 0:
        out->r = (src->h >> 8) & 0xF8;
        out->g = (src->h >> 3) & 0xFC;
        out->b = (src->h << 3) & 0xF8;
        out->a = 0xFF;
        break;
    case 3:
        out->r = (src->h >> 12) & 0xF;
        out->g = (src->h >> 8) & 0xF;
        out->b = (src->h >> 4) & 0xF;
        out->a = src->h & 0xF;
        out->r = out->r | (out->r << 4);
        out->g = out->g | (out->g << 4);
        out->b = out->b | (out->b << 4);
        out->a = out->a | (out->a << 4);
        break;
    case 5:
        out->r = src->w >> 24;
        out->g = src->w >> 16;
        out->b = src->w >> 8;
        out->a = src->w;
        break;
    case 1:
    case 2:
        out->r = src->w >> 24;
        out->g = src->w >> 16;
        out->b = src->w >> 8;
        out->a = 0xFF;
        break;
    case 4:
        out->r = (src->h & 0xFC0000) >> 16;
        out->g = (src->h >> 10) & 0xFC;
        out->b = (src->h >> 4) & 0xFC;
        out->a = (src->h << 2) & 0xFC;
        break;
    }
}

// .text:0x000E5FEC size:0x424 mapped:0x80725080
void fn_3_E5FEC(void) {
    return;
}

// .text:0x000E6410 size:0x98 mapped:0x807254A4
void fn_3_E6410(Struct_E6410* arg0) {
    u32* choices[3];
    u32** p = choices;
    u32* q = lbl_3_data_19018;
    int i;

    for (i = 0; i < 3; i++) {
        if (arg0->unkAC != q) {
            *p++ = q;
        }
        q++;
    }
    arg0->unkA8 = choices[rand() % 2];
}

// .text:0x000E64A8 size:0x80 mapped:0x8072553C
u32* fn_3_E64A8(void) {
    u8 val = rand() % 3;
    
    switch (val) {
        case 0:
            return &lbl_3_data_19018[0];
        case 1:
            return &lbl_3_data_19018[1];
        default:
            return &lbl_3_data_19018[2];
    }
}

// .text:0x000E6528 size:0x50 mapped:0x807255BC
void fn_3_E6528(Struct_E6528* arg0) {
    memcpy(&arg0->unkA4, arg0->unkB4, 4);
    arg0->unkBC = &lbl_3_data_19024 + 0x64;
    arg0->unkC2 = 0;
}

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
void fn_3_E6578(Arg0_E6578* arg0) {
    Material_E6578* mat;
    TargetRef_E6578* ref;

    if (arg0->unk9C != NULL) {
        mat = arg0->unk9C->unk0->unk18[1]->unk14;
        ref = mat->unk8;
        if (mat->unk10->unk4->unk20 != 3) {
            OSPanic("sta_c6.c", 0x713, "参照するディスプレイステートがTEV設定部分じゃないです\n");
        }
        if (arg0->unkC1 == 2) {
            ref->unkC->unkA0 = 1;
        } else if (arg0->unkC1 == 10) {
            ref->unkC->unkA0 = 0;
        } else {
            ref->unkC->unkA0 = 4;
        }
    }
}

// .text:0x000E6638 size:0x4C mapped:0x807256CC
void fn_3_E6638(BaseStruct_E6638* arg0) {
    arg0->field_0x74->field_0x00->array[0]->field_0x14 =
        arg0->field_0x74->field_0x00->array[0]->field_0x18;

    arg0->field_0x74->field_0x00->array[1]->field_0x14 =
        arg0->field_0x74->field_0x00->array[1]->field_0x18;

    arg0->field_0x74->field_0x00->array[2]->field_0x14 =
        arg0->field_0x74->field_0x00->array[2]->field_0x18;
}

// .text:0x000E6684 size:0x98 mapped:0x80725718
void fn_3_E6684(BaseStruct_E6638* arg0) {
    int i;
    InnerStruct_E6638* e;

    for (i = 0; i < 3; i++) {
        e = arg0->field_0x74->field_0x00->array[i];
        if (lbl_3_bss_AE80[i + 1] != 0) {
            e->field_0x14 = e->field_0x18;
        } else {
            e->field_0x14 = 0;
        }
    }
}

// .text:0x000E671C size:0x7C mapped:0x807257B0
void fn_3_E671C(Arg0_E6798* arg0) {
    NodeArray_E6798* nodeArr = arg0->unk74->unk0;
    nodeArr->unk18[0]->unk14 = nodeArr->unk18[0]->unk18;
    nodeArr->unk18[1]->unk14 = nodeArr->unk18[1]->unk18;
    nodeArr->unk18[2]->unk14 = nodeArr->unk18[2]->unk18;
    nodeArr->unk18[3]->unk14 = nodeArr->unk18[3]->unk18;
    nodeArr->unk18[4]->unk14 = nodeArr->unk18[4]->unk18;
    nodeArr->unk18[5]->unk14 = nodeArr->unk18[5]->unk18;
    nodeArr->unk18[6]->unk14 = nodeArr->unk18[6]->unk18;
}

// .text:0x000E6798 size:0x5C mapped:0x8072582C
void fn_3_E6798(Arg0_E6798* arg0) {
    u8* flags = lbl_3_data_196B4;
    int i = 0;
    NodeArray_E6798* nodeArr = arg0->unk74->unk0;
    for (; i < 7; i++) {
        if (*flags != 0) {
            nodeArr->unk18[i]->unk14 = nodeArr->unk18[i]->unk18;
        } else {
            nodeArr->unk18[i]->unk14 = 0;
        }
        flags++;
    }
}

// .text:0x000E67F4 size:0xB4 mapped:0x80725888
static inline void setAnimTime(ActorAnimState* state, f32 time) {
    state->time = time;
    state->setTime = 1;
}

void fn_3_E67F4(void) {
    f32 time = 20.0f;
    u32 i;
    Actor* actor;

    for (i = 0; i < 7; i++) {
        lbl_3_data_196B4[i] = 0;
        actor = g_hugeAnimStruct.animTable->entries[i + 16].anim.actor;
        setAnimTime(&g_hugeAnimStruct.animTable->entries[i + 16].anim, time);
        fn_800B4CA0(actor, g_hugeAnimStruct.animTable->entries[i + 16].anim.time);
        AnimateActorBones(actor);
    }
}

// .text:0x000E68A8 size:0xE4 mapped:0x8072593C
void fn_3_E68A8(void) {
    return;
}

// .text:0x000E698C size:0xBC mapped:0x80725A20
static inline f32 getBoneFrame(ActorObject* actor, void** outBoneData) {
    void* boneData = actor->wrapper->boneData;
    *outBoneData = boneData;
    return fn_800B4C40(boneData);
}

void fn_3_E698C(ActorObject* arg0) {
    void* boneData;
    f32 frame;
    u8 idx;

    frame = getBoneFrame(arg0, &boneData);
    idx = arg0->field_0xc1 - 0x10;

    if (lbl_3_data_196B4[idx] == 0) {
        fn_800B4CA0(boneData, lbl_3_rodata_2BA4);
        AnimateActorBones(boneData);
    }
    if (lbl_3_data_196B4[idx] != 0 && frame <= lbl_3_rodata_2BA0) {
        AnimateActorBones(boneData);
    }
}

// .text:0x000E6A48 size:0x348 mapped:0x80725ADC
void fn_3_E6A48(void) {
    return;
}

// .text:0x000E6D90 size:0x5C0 mapped:0x80725E24
void fn_3_E6D90(void) {
    return;
}

// .text:0x000E7350 size:0x14 mapped:0x807263E4
void fn_3_E7350(void) {
    lbl_3_data_1963F = lbl_3_data_19640;
}

// .text:0x000E7364 size:0x24 mapped:0x807263F8
void fn_3_E7364(s32 index) {
    StadiumObjectElem* obj = &lbl_3_common_bss_350E4[0].src[index];
    lbl_3_data_19640 = obj->unkC0;
}

// .text:0x000E7388 size:0x9C mapped:0x8072641C
void fn_3_E7388(void) {
    return;
}

// .text:0x000E7424 size:0xF8 mapped:0x807264B8
void fn_3_E7424(void) {
    return;
}

// .text:0x000E751C size:0x120 mapped:0x807265B0
struct StadiumModel* fn_3_E751C(s32 idx, Mtx m) {
    Control ctrl;
    StadiumObjectElem* elem;

    ctrl.type = 0;
    elem = &lbl_3_common_bss_350E4->src[idx];
    if (elem->unkC1 <= 7) {
        CTRLSetTranslation(&ctrl, lbl_3_bss_AEB4.objs[idx].pos.x, -0.04f, lbl_3_bss_AEB4.objs[idx].pos.z);
        CTRLSetRotation(&ctrl, 0.0f, lbl_3_bss_AEB4.objs[idx].rotY, 0.0f);
    } else {
        CTRLSetTranslation(&ctrl, lbl_3_data_19644[elem->unkC3].x, -0.04f, lbl_3_data_19644[elem->unkC3].z);
        CTRLSetRotation(&ctrl, 0.0f, lbl_3_data_19698[elem->unkC3], 0.0f);
    }
    CTRLBuildMatrix(&ctrl, m);
    return elem->unk_78;
}

// .text:0x000E763C size:0x3F0 mapped:0x807266D0
void fn_3_E763C(void) {
    return;
}

// .text:0x000E7A2C size:0xF4 mapped:0x80726AC0
void fn_3_E7A2C(StaC6SetupObj* obj) {
    obj->fn7C = NULL;
    obj->fn80 = NULL;
    obj->fn84 = NULL;
    obj->fn88 = NULL;
    switch (obj->kind) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
    case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
        obj->fn80 = fn_3_E7364;
        obj->fn84 = fn_3_E6D90;
        lbl_3_bss_AEAC++;
        break;
    case 16: case 17: case 18: case 19: case 20: case 21: case 22:
        obj->fn7C = fn_3_E698C;
        obj->fn84 = fn_3_E68A8;
        break;
    case 23:
        obj->fn84 = fn_3_E6798;
        obj->fn88 = fn_3_E671C;
        break;
    case 24:
        obj->fn84 = fn_3_E6684;
        obj->fn88 = fn_3_E6638;
        break;
    case 26:
        obj->fn7C = fn_3_E59B4;
        break;
    case 25:
        obj->fn7C = fn_3_E5A1C;
        break;
    }
}

// .text:0x000E7B20 size:0xFA8 mapped:0x80726BB4
u8 fn_3_E7B20(u32 arg0, u32 arg1) {
    return 0;
}

// .text:0x000E8AC8 size:0x5C mapped:0x80727B5C
int fn_3_E8AC8(void) {
    if (g_d_GameSettings.StadiumID != 6) {
        return 0;
    }
    return (u8)fn_3_E7B20(lbl_3_common_bss_350E4[0].unk38, lbl_3_common_bss_350E4[0].unk34) != 0;
}

// .text:0x000E8B24 size:0x5F8 mapped:0x80727BB8
void fn_3_E8B24(void) {
    return;
}
