#include "menus/gap_5597C.h"
#include "menus/rep_10C0.h"
#include "menus/gap_4B1AC.h"
#include "menus/gap_1B1BC.h"
#include "UnknownHeaders.h"

extern s16 lbl_2_data_1FD84[];
extern void fn_8001F228(void);
extern void fn_80021410(void);
extern void fn_80035B50(s32);
#include "game/rep_3448.h"

// .text:0x0005597C size:0xC4
s32 fn_2_5597C(void) {
    s32 value = lbl_2_bss_1A824C->unk1976FE + lbl_2_bss_1A824C->unk1976FA;
    s32 result;
    if (value < 26) result = 0;
    else if (value < 52) result = 1;
    else if (value < 106) result = 2;
    else if (value < 140) result = 3;
    else if (value < 145) result = 4;
    else if (value < 193) result = 5;
    else if (value < 195) result = 6;
    else if (value < 196) result = 7;
    else if (value < 210) result = 8;
    else if (value < 213) result = 9;
    else result = 10;
    return result;
}

// .text:0x00055A40 size:0x94
void fn_2_55A40(void) {
    lbl_2_bss_1A824C->flag1972BC = 1;
    fn_2_4E7EC();
    fn_8001F228();
    fn_80021410();
    fn_800ACFB0(lbl_800EF808.files[4]);
    fn_80035B50(10);
    if (lbl_80366B18.tables[2] != 0) {
        fn_800ACFB0(lbl_80366B18.tables[2]);
        lbl_80366B18.tables[2] = 0;
    }
    lbl_2_bss_1A823C->unk34 = 0;
}

// .text:0x00055AD4 size:0x188
void fn_2_55AD4(void) {
    return;
}

// .text:0x00055C5C size:0x17C
/* Show the selected menu entry label when it has multiple choices, then hide it on command. */
void fn_2_55C5C(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2: case 8: case 0x11: {
        s32 value = lbl_2_data_1FD84[lbl_2_bss_1A824C->unk1976FA + lbl_2_bss_1A824C->unk1976FE];
        if (value > 1) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
            lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x5C = (value - 1) << 16;
        }
        slot->state = 0x25;
        break;
    }
    case 5:
        slot->timer = 10;
        slot->state = 6;
        break;
    case 6:
        if (slot->timer-- <= 0) lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00055DD8 size:0x200
void fn_2_55DD8(void) {
    return;
}

// .text:0x00055FD8 size:0x188
void fn_2_55FD8(void) {
    return;
}

// .text:0x00056160 size:0x260
void fn_2_56160(void) {
    return;
}

// .text:0x000563C0 size:0x2C8
void fn_2_563C0(void) {
    return;
}

// .text:0x00056688 size:0x314
void fn_2_56688(void) {
    return;
}

// .text:0x0005699C size:0x298
void fn_2_5699C(void) {
    return;
}

// .text:0x00056C34 size:0x258
void fn_2_56C34(void) {
    return;
}

// .text:0x00056E8C size:0x258
void fn_2_56E8C(void) {
    return;
}

// .text:0x000570E4 size:0x1B0
void fn_2_570E4(void) {
    return;
}

// .text:0x00057294 size:0x2B8
void fn_2_57294(void) {
    return;
}

// .text:0x0005754C size:0x1D8
void fn_2_5754C(void) {
    return;
}

// .text:0x00057724 size:0x148
void fn_2_57724(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x0005786C size:0x148
void fn_2_5786C(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x000579B4 size:0x244
void fn_2_579B4(void) {
    return;
}

// .text:0x00057BF8 size:0x358
void fn_2_57BF8(void) {
    return;
}

// .text:0x00057F50 size:0x148
void fn_2_57F50(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00058098 size:0x148
void fn_2_58098(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x000581E0 size:0x148
void fn_2_581E0(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00058328 size:0x148
void fn_2_58328(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 4;
        item->state = 0x26;
        break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00058470 size:0xA0
void fn_2_58470(s32 unused, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0: slot->state = 0x26; break;
    case 1: break;
    case 2: slot->state = 0x25; break;
    case 5: break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00058510 size:0x2C
void fn_2_58510(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x0005853C size:0x2BC
void fn_2_5853C(void) {
    return;
}

// .text:0x000587F8 size:0xFA4
void fn_2_587F8(void) {
    return;
}
