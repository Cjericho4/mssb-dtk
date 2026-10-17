#include "menus/rep_1028.h"
#include "menus/rep_0B08.h"
#include "menus/gap_8782C.h"
#include "Dolphin/GX/GXTypes.h"
#include "string.h"

extern GXColor lbl_800F7478[];
extern Rep1028Config lbl_2_data_369C[];
extern Rep1028Config lbl_2_data_3198[];
extern void (*lbl_2_data_30900[])(s32);
extern void fn_800BD2CC(s32 enabled, GXColor color);

extern void (*lbl_2_data_30810[])(Rep1028Obj*);

extern void (*lbl_2_data_3081C[])(Rep1028Obj*);

extern void (*lbl_2_data_30828[])(Rep1028Obj*);

extern void (*lbl_2_data_30834[])(Rep1028Obj*);

extern void (*lbl_2_data_30840[])(Rep1028Obj*);

extern void (*lbl_2_data_3084C[])(Rep1028Obj*);

extern void (*lbl_2_data_30858[])(Rep1028Obj*);

extern void (*lbl_2_data_30864[])(Rep1028Obj*);

extern void (*lbl_2_data_30870[])(Rep1028Obj*);

extern void (*lbl_2_data_30880[])(Rep1028Obj*);

extern void (*lbl_2_data_3088C[])(Rep1028Obj*);

extern void (*lbl_2_data_30898[])(Rep1028Obj*);

extern void (*lbl_2_data_308A4[])(Rep1028Obj*);

// .text:0x0008F0F4 size:0x188
void fn_2_8F0F4(void) {
    return;
}

// .text:0x0008F27C size:0x158
void fn_2_8F27C(void) {
    return;
}

// .text:0x0008F3D4 size:0x154
void fn_2_8F3D4(void) {
    return;
}

// .text:0x0008F528 size:0x118
void fn_2_8F528(void) {
    return;
}

// .text:0x0008F640 size:0x48
void fn_2_8F640(void) {
    GXColor color = lbl_800F7478[10];
    color.a = 255;
    fn_800BD2CC(1, color);
}

// .text:0x0008F688 size:0x48
void fn_2_8F688(void) {
    GXColor color = lbl_800F7478[10];
    color.a = 255;
    fn_800BD2CC(0, color);
}

// .text:0x0008F6D0 size:0x50
void fn_2_8F6D0(s32 index, s32 action) {
    hugeAnimStruct* render = lbl_2_bss_340140;
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    HugeAnimEntry2D94* entries = render->entries_2D94;
    if (entries != 0) {
        obj->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[action];
    }
}

// .text:0x0008F720 size:0x1C
u8 fn_2_8F720(s32 index) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    return obj->unkB4;
}

// .text:0x0008F73C size:0x1C
void fn_2_8F73C(s32 index, u8 value) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    obj->unkB4 = value;
}

// .text:0x0008F758 size:0x1C
void fn_2_8F758(s32 index, u8 value) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    obj->unkA8 = value;
}

// .text:0x0008F774 size:0x3C
f32 fn_2_8F774(s32 index) {
    HugeAnimEntry68* entry = &lbl_2_bss_340140->entries_68[index];
    return fn_800B4A94(entry->unk34, (hugeAnimStruct*)lbl_2_bss_340140->entries_68);
}

// .text:0x0008F7B0 size:0x88
void fn_2_8F7B0(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[7];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008F838 size:0x88
void fn_2_8F838(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[6];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008F8C0 size:0x88
void fn_2_8F8C0(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[5];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008F948 size:0x88
void fn_2_8F948(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[4];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008F9D0 size:0x88
void fn_2_8F9D0(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[3];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FA58 size:0x88
void fn_2_8FA58(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[2];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FAE0 size:0x88
void fn_2_8FAE0(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->values[1];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FB68 size:0x90
void fn_2_8FB68(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    value = lbl_2_bss_3401BC->assets[index];
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FBF8 size:0x90
void fn_2_8FBF8(s32 index, s16 id) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    value = lbl_2_bss_3401BC->assets[index];
    sub->unk38_s32 = value;
    sub->unk42 = id;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FC88 size:0x8C
void fn_2_8FC88(s32 index) {
    u32 value;
    ActRelatedSub* sub;
    if (lbl_2_bss_3401BC == 0) return;
    value = lbl_2_bss_3401BC->assets[0];
    sub = &((ActRelatedEntry*)lbl_2_bss_340140->entries_68)[index].sub;
    sub->unk38_s32 = value;
    sub->unk42 = 0;
    sub[1].prevFloat = 0.0f;
    sub->unk8C = 1;
    sub->flag59 = value != 0;
    sub->flag5a = value != 0;
    sub[1].unk38_f32 = 0.0f;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
    sub[1].prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->flag5b = 3;
}

// .text:0x0008FD14 size:0x9C
void fn_2_8FD14(void) {
    HugeAnimEntry2D94* entry;
    Rep1028Obj* obj;
    s32 i;
    for (i = 0; i < lbl_2_bss_340140->field268_0x3078; i++) {
        if (lbl_2_bss_340140->entries_2D94 != 0) {
            entry = &lbl_2_bss_340140->entries_2D94[i];
            obj = &lbl_2_bss_1A8248->rep1028Objects[i];
            memcpy(&entry->pos, &obj->position, sizeof(Vec));
            entry->vel.y = obj->unk28;
            entry->unk_26 = obj->unkAA;
        }
    }
}

// .text:0x0008FDB0 size:0xEC
void fn_2_8FDB0(void) {
    return;
}

// .text:0x0008FE9C size:0x1E0
void fn_2_8FE9C(void) {
    return;
}

// .text:0x0009007C size:0x2C0
void fn_2_9007C(void) {
    return;
}

// .text:0x0009033C size:0x6C
void fn_2_9033C(s32 index, Vec* position, f32 value) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    memcpy(&obj->position, position, sizeof(Vec));
    obj->unk28 = value;
    obj->unk30 = 0.0f;
    obj->unk28 = value;
}

// .text:0x000903A8 size:0x80
void fn_2_903A8(s32 index) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    memcpy(&obj->position, &lbl_2_data_369C[index].position, sizeof(Vec));
    obj->unk30 = 0.0f;
    obj->unk28 = lbl_2_data_369C[index].value;
}

// .text:0x00090428 size:0x80
void fn_2_90428(s32 index) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    memcpy(&obj->position, &lbl_2_data_3198[index].position, sizeof(Vec));
    obj->unk30 = 0.0f;
    obj->unk28 = lbl_2_data_3198[index].value;
}

// .text:0x000904A8 size:0x90
void fn_2_904A8(void) {
    Rep1028Obj* obj;
    s32 i;
    for (i = 0; i < 29; i++) {
        obj = &lbl_2_bss_1A8248->rep1028Objects[i];
        obj->index = i;
        obj->unk7C = i;
        obj->unk84 = 0.0f;
        obj->unk38 = 0.0f;
        obj->unk3C = 0.0f;
        obj->unkAA = 0;
        obj->unk92 = i;
        obj->unk94 = -1;
        obj->unkA8 = 0;
        obj->variant = 0;
        obj->state = 0;
        obj->unkAE = -1;
        obj->unkAC = 0;
        obj->unkAD = 0;
        obj->unk80 = 0.0f;
        obj->unkA6 = 0;
        obj->unkB2 = 0xFF;
        obj->unkB4 = 0;
    }
}

// .text:0x00090538 size:0xE4
void fn_2_90538(void) {
    return;
}

// .text:0x0009061C size:0xC
void fn_2_9061C(Rep1028Obj* obj) {
    obj->state = 3;
}

// .text:0x00090628 size:0x70
void fn_2_90628(Rep1028Obj* obj) {
    if (obj->unkA0 == 1) {
        Rep1028Obj* target;
        fn_2_8AC84(obj->index, 0);
        obj->unkA0 = 2;
        target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 0;
        target->state = 0;
    }
}

// .text:0x00090698 size:0x80
void fn_2_90698(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    if (obj->countdown-- != 0) return;
    obj->unk8C = 0.02f;
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries != 0) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[5];
    }
    obj->state = 2;
}

// .text:0x00090718 size:0xDC
void fn_2_90718(void) {
    return;
}

// .text:0x000907F4 size:0x38
void fn_2_907F4(Rep1028Obj* obj) {
    lbl_2_data_308A4[obj->state](obj);
}

// .text:0x0009082C size:0xC
void fn_2_9082C(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00090838 size:0x50
void fn_2_90838(Rep1028Obj* obj) {
    if (obj->unkA0 == 1) {
        fn_2_8AC84(obj->index, 0);
        obj->unkA0 = 2;
    }
    obj->state = 2;
}

// .text:0x00090888 size:0x74
void fn_2_90888(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    obj->unk8C = 0.8f;
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries != 0) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[5];
    }
    obj->unkA0 = 0;
    obj->state = 1;
}

// .text:0x000908FC size:0x38
void fn_2_908FC(Rep1028Obj* obj) {
    lbl_2_data_30898[obj->state](obj);
}

// .text:0x00090934 size:0xC
void fn_2_90934(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00090940 size:0xC
void fn_2_90940(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x0009094C size:0xA8
void fn_2_9094C(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    fn_2_8AC84(obj->index, 0);
    obj->unk8C = 0.08f;
    obj->unkA0 = 0;
    fn_2_8AC84(obj->index, 1);
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[4];
    }
    obj->state = 1;
}

// .text:0x000909F4 size:0x38
void fn_2_909F4(Rep1028Obj* obj) {
    lbl_2_data_3088C[obj->state](obj);
}

// .text:0x00090A2C size:0x84
void fn_2_90A2C(Rep1028Obj* obj) {
    HugeAnimEntry68* entry = &lbl_2_bss_340140->entries_68[obj->index];
    if (0.0f == fn_800B4A94(entry->unk34, (hugeAnimStruct*)lbl_2_bss_340140->entries_68)) {
        Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 2;
        target->state = 0;
    }
}

// .text:0x00090AB0 size:0xC
void fn_2_90AB0(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00090ABC size:0x114
void fn_2_90ABC(void) {
    return;
}

// .text:0x00090BD0 size:0x38
void fn_2_90BD0(Rep1028Obj* obj) {
    lbl_2_data_30880[obj->state](obj);
}

// .text:0x00090C08 size:0xC
void fn_2_90C08(Rep1028Obj* obj) {
    obj->state = 3;
}

// .text:0x00090C14 size:0x38
void fn_2_90C14(Rep1028Obj* obj) {
    if (obj->unkA0 == 1) {
        Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 0;
        target->state = 0;
    }
}

// .text:0x00090C4C size:0x84
void fn_2_90C4C(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    if (obj->countdown-- != 0) return;
    obj->unk8C = 0.06f;
    obj->unkA0 = 0;
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries != 0) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[3];
    }
    obj->state = 2;
}

// .text:0x00090CD0 size:0xDC
void fn_2_90CD0(void) {
    return;
}

// .text:0x00090DAC size:0x38
void fn_2_90DAC(Rep1028Obj* obj) {
    lbl_2_data_30870[obj->state](obj);
}

// .text:0x00090DE4 size:0xB4
void fn_2_90DE4(void) {
    return;
}

// .text:0x00090E98 size:0x2C
void fn_2_90E98(Rep1028Obj* obj) {
    Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
    target->variant = 0;
    target->state = 0;
}

// .text:0x00090EC4 size:0x194
void fn_2_90EC4(void) {
    return;
}

// .text:0x00091058 size:0x188
void fn_2_91058(void) {
    return;
}

// .text:0x000911E0 size:0x38
void fn_2_911E0(Rep1028Obj* obj) {
    lbl_2_data_30864[obj->state](obj);
}

// .text:0x00091218 size:0x84
void fn_2_91218(Rep1028Obj* obj) {
    HugeAnimEntry68* entry = &lbl_2_bss_340140->entries_68[obj->index];
    if (0.0f == fn_800B4A94(entry->unk34, (hugeAnimStruct*)lbl_2_bss_340140->entries_68)) {
        Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 2;
        target->state = 0;
    }
}

// .text:0x0009129C size:0xC
void fn_2_9129C(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000912A8 size:0x1A8
void fn_2_912A8(void) {
    return;
}

// .text:0x00091450 size:0x38
void fn_2_91450(Rep1028Obj* obj) {
    lbl_2_data_30858[obj->state](obj);
}

// .text:0x00091488 size:0x84
void fn_2_91488(Rep1028Obj* obj) {
    HugeAnimEntry68* entry = &lbl_2_bss_340140->entries_68[obj->index];
    if (0.0f == fn_800B4A94(entry->unk34, (hugeAnimStruct*)lbl_2_bss_340140->entries_68)) {
        Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 2;
        target->state = 0;
    }
}

// .text:0x0009150C size:0xC
void fn_2_9150C(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00091518 size:0x1A8
void fn_2_91518(void) {
    return;
}

// .text:0x000916C0 size:0x38
void fn_2_916C0(Rep1028Obj* obj) {
    lbl_2_data_3084C[obj->state](obj);
}

// .text:0x000916F8 size:0x84
void fn_2_916F8(Rep1028Obj* obj) {
    HugeAnimEntry68* entry = &lbl_2_bss_340140->entries_68[obj->index];
    if (0.0f == fn_800B4A94(entry->unk34, (hugeAnimStruct*)lbl_2_bss_340140->entries_68)) {
        Rep1028Obj* target = &lbl_2_bss_1A8248->rep1028Objects[obj->index];
        target->variant = 2;
        target->state = 0;
    }
}

// .text:0x0009177C size:0xC
void fn_2_9177C(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00091788 size:0x11C
void fn_2_91788(void) {
    return;
}

// .text:0x000918A4 size:0x38
void fn_2_918A4(Rep1028Obj* obj) {
    lbl_2_data_30840[obj->state](obj);
}

// .text:0x000918DC size:0xC
void fn_2_918DC(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000918E8 size:0xC
void fn_2_918E8(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000918F4 size:0x88
void fn_2_918F4(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    fn_2_8AC84(obj->index, 1);
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries != 0) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[2];
    }
    obj->state = 1;
}

// .text:0x0009197C size:0x38
void fn_2_9197C(Rep1028Obj* obj) {
    lbl_2_data_30834[obj->state](obj);
}

// .text:0x000919B4 size:0xC
void fn_2_919B4(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000919C0 size:0xC
void fn_2_919C0(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000919CC size:0x118
void fn_2_919CC(void) {
    return;
}

// .text:0x00091AE4 size:0x38
void fn_2_91AE4(Rep1028Obj* obj) {
    lbl_2_data_30828[obj->state](obj);
}

// .text:0x00091B1C size:0xC
void fn_2_91B1C(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00091B28 size:0x4
void fn_2_91B28(void) {
    return;
}

// .text:0x00091B2C size:0xC
void fn_2_91B2C(Rep1028Obj* obj) {
    obj->state = 1;
}

// .text:0x00091B38 size:0x38
void fn_2_91B38(Rep1028Obj* obj) {
    lbl_2_data_3081C[obj->state](obj);
}

// .text:0x00091B70 size:0xC
void fn_2_91B70(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00091B7C size:0x4
void fn_2_91B7C(void) {
    return;
}

// .text:0x00091B80 size:0x88
void fn_2_91B80(Rep1028Obj* obj) {
    s32 index;
    hugeAnimStruct* render;
    Rep1028Obj* target;
    HugeAnimEntry2D94* entries;
    fn_2_8AC84(obj->index, 1);
    index = obj->index;
    render = lbl_2_bss_340140;
    target = &lbl_2_bss_1A8248->rep1028Objects[index];
    entries = render->entries_2D94;
    if (entries != 0) {
        target->unkA6 = 0;
        entries[index].callback = lbl_2_data_30900[0];
    }
    obj->state = 1;
}

// .text:0x00091C08 size:0x38
void fn_2_91C08(Rep1028Obj* obj) {
    lbl_2_data_30810[obj->state](obj);
}

// .text:0x00091C40 size:0xC
void fn_2_91C40(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x00091C4C size:0x128
void fn_2_91C4C(void) {
    return;
}

// .text:0x00091D74 size:0x620
void fn_2_91D74(void) {
    return;
}
