#include "menus/gap_92394.h"
#include "menus/rep_0B08.h"
#include "menus/gap_8782C.h"
#include "menus/rep_10C0.h"
#include "Dolphin/GX/GXTypes.h"

extern GXColor lbl_800F7478[];
extern void (*lbl_2_data_30900[])(s32);
extern void fn_800BD2CC(s32 enabled, GXColor color);
extern void (*lbl_2_data_308B4[])(Rep1028Obj*);

extern void (*lbl_2_data_307F0[])(Rep1028Obj*);

extern void (*lbl_2_data_307F8[])(Rep1028Obj*);

extern void (*lbl_2_data_30804[])(Rep1028Obj*);

// .text:0x00092394 size:0x38
void fn_2_92394(Rep1028Obj* obj) {
    lbl_2_data_30804[obj->state](obj);
}

// .text:0x000923CC size:0xC
void fn_2_923CC(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000923D8 size:0xC
void fn_2_923D8(Rep1028Obj* obj) {
    obj->state = 2;
}

// .text:0x000923E4 size:0x88
void fn_2_923E4(Rep1028Obj* obj) {
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

// .text:0x0009246C size:0x38
void fn_2_9246C(Rep1028Obj* obj) {
    lbl_2_data_307F8[obj->state](obj);
}

// .text:0x000924A4 size:0xC
void fn_2_924A4(Rep1028Obj* obj) {
    obj->state = 1;
}

// .text:0x000924B0 size:0x54
void fn_2_924B0(Rep1028Obj* obj) {
    GXColor color = lbl_800F7478[10];
    fn_2_8AC84(obj->index, 0);
    color.a = 255;
    fn_800BD2CC(0, color);
}

// .text:0x00092504 size:0x38
void fn_2_92504(Rep1028Obj* obj) {
    lbl_2_data_307F0[obj->state](obj);
}

// .text:0x0009253C size:0x40
void fn_2_9253C(Rep1028Obj* obj) {
    obj->callback = lbl_2_data_308B4[obj->variant];
    obj->callback(obj);
}

// .text:0x0009257C size:0xD8
void fn_2_9257C(void) {
    s32 i;
    if (lbl_2_bss_1A8248->unk44F2 == 1 || lbl_2_bss_1A8248->unk44F2 == 2 || lbl_2_bss_1A8248->unk44F2 == 3) return;
    for (i = 0; i < 29; i++) {
        Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[i];
        obj->callback = lbl_2_data_308B4[obj->variant];
        obj->callback(obj);
    }
    if (lbl_2_bss_1A824C->flag1972C0) {
        lbl_2_bss_1A824C->flag1972C0 = 0;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00092654 size:0x28
void fn_2_92654(s32 index, u8 variant) {
    Rep1028Obj* obj = &lbl_2_bss_1A8248->rep1028Objects[index];
    obj->variant = variant;
    obj->state = 0;
}

// .text:0x0009267C size:0x14C
void fn_2_9267C(void) {
    return;
}
