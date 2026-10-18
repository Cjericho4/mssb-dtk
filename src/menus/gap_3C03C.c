#include "menus/gap_3C03C.h"
extern void fn_80062890(s32 value);
#include "menus/rep_0B08.h"
#include "menus/rep_10C0.h"
#include "string.h"
#include "menus/gap_4B1AC.h"
#include "menus/gap_1B1BC.h"
#include "menus/rep_0788.h"
#include "menus/gap_71EC4.h"
#include "menus/rep_0F60.h"
#include "game/rep_1C0.h"
extern CompressedDiskRead lbl_2_data_12298;
extern void fn_800111B4(struct MenusSceneArchive* archive);

extern MenusMenuBuffer lbl_2_bss_15B8;
extern MenusMenuBuffer* lbl_2_data_12CE8[];
extern MenusMenuBuffer* lbl_2_data_12C0C[];

extern u8 lbl_803CB8F0[];
extern u32 lbl_803CBD0C;
extern MenusEffectState* lbl_2_data_13374[];
extern void fn_80031CA4(Vec* position, MenusEffectState* state);

// .text:0x0003C03C size:0x12C
void fn_2_3C03C(void) {
    return;
}

// .text:0x0003C168 size:0x284
void fn_2_3C168(void) {
    return;
}

// .text:0x0003C3EC size:0x150
void fn_2_3C3EC(void) {
    return;
}

// .text:0x0003C53C size:0x2A0
void fn_2_3C53C(void) {
    return;
}

// .text:0x0003C7DC size:0x558
void fn_2_3C7DC(void) {
    return;
}

// .text:0x0003CD34 size:0x890
void fn_2_3CD34(void) {
    return;
}

// .text:0x0003D5C4 size:0x2B4
void fn_2_3D5C4(void) {
    return;
}

// .text:0x0003D878 size:0x240
void fn_2_3D878(void) {
    return;
}

// .text:0x0003DAB8 size:0x1A8
void fn_2_3DAB8(void) {
    return;
}

// .text:0x0003DC60 size:0x164
void fn_2_3DC60(void) {
    return;
}

// .text:0x0003DDC4 size:0x164
void fn_2_3DDC4(void) {
    return;
}

// .text:0x0003DF28 size:0x130
void fn_2_3DF28(void) {
    return;
}

// .text:0x0003E058 size:0x334
void fn_2_3E058(void) {
    return;
}

// .text:0x0003E38C size:0x460
void fn_2_3E38C(void) {
    return;
}

// .text:0x0003E7EC size:0x12C
void fn_2_3E7EC(void) {
    return;
}

// .text:0x0003E918 size:0x12C
void fn_2_3E918(void) {
    return;
}

// .text:0x0003EA44 size:0x164
void fn_2_3EA44(void) {
    return;
}

// .text:0x0003EBA8 size:0x118
void fn_2_3EBA8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 1;
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) {
            scene->unkIndex = 60;
            fn_2_72054(0, 10);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if ((*(s16*)&scene->unkIndex)-- == 0) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003ECC0 size:0x118
void fn_2_3ECC0(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 1;
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) {
            scene->unkIndex = 60;
            fn_2_72054(0, 10);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if ((*(s16*)&scene->unkIndex)-- == 0) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003EDD8 size:0x118
void fn_2_3EDD8(void) {
    return;
}

// .text:0x0003EEF0 size:0x114
void fn_2_3EEF0(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 1;
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) {
            scene->unkIndex = 60;
            fn_2_72054(0, 11);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0)) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003F004 size:0x184
void fn_2_3F004(void) {
    return;
}

// .text:0x0003F188 size:0x114
void fn_2_3F188(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 1;
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) {
            scene->unkIndex = 60;
            fn_2_72054(0, 9);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0)) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003F29C size:0x1B0
void fn_2_3F29C(void) {
    return;
}

// .text:0x0003F44C size:0x110
void fn_2_3F44C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 40;
        if (lbl_2_bss_1A8248->unk4418 != 0) {
            fn_80062890(8);
            scene->field15_0x28 = 1;
        } else scene->field15_0x28 = 2;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) scene->field15_0x28 = 2;
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003F55C size:0x110
void fn_2_3F55C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 40;
        if (lbl_2_bss_1A8248->unk4418 < 5) {
            fn_80062890(7);
            scene->field15_0x28 = 1;
        } else scene->field15_0x28 = 2;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) scene->field15_0x28 = 2;
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x0003F66C size:0x3A8
void fn_2_3F66C(void) {
    return;
}

// .text:0x0003FA14 size:0x3CC
void fn_2_3FA14(void) {
    return;
}

// .text:0x0003FDE0 size:0x63C
void fn_2_3FDE0(void) {
    return;
}

// .text:0x0004041C size:0x198
void fn_2_4041C(void) {
    return;
}

// .text:0x000405B4 size:0x1D8
void fn_2_405B4(void) {
    return;
}

// .text:0x0004078C size:0x130
void fn_2_4078C(void) {
    return;
}

// .text:0x000408BC size:0x110
void fn_2_408BC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        scene->unkIndex = 60;
        lbl_2_bss_1A824C->unk19782C = 1;
        fn_2_72054(1, 13);
        fn_80062890(9);
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((*(s16*)&scene->unkIndex)-- == 0) scene->field15_0x28 = 2;
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x000409CC size:0xD0
void fn_2_409CC(void) {
    DrawingSceneStruct* scene;
    switch ((s8)(scene = lbl_803CC1B8)->field15_0x28) {
    case 0:
        lbl_80366B18.archive = ARAMTransfer(&lbl_2_data_12298, 0, 1, 0);
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.allowLoad == 1) {
            fn_800111B4(lbl_80366B18.archive);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x00040A9C size:0xF4
void fn_2_40A9C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        lbl_2_bss_1A824C->unk1978F3 = 0;
        scene->field15_0x28 = 1;
        break;
    case 1:
        g_hugeAnimStruct.field269_0x307a = 0;
        fn_2_20218();
        lbl_2_bss_1A8234->panels[1].pending = 1;
        lbl_2_bss_1A8230->pending = 1;
        scene->field15_0x28 = 2;
        break;
    case 2:
        fn_2_1BF50();
        scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x00040B90 size:0x128
void fn_2_40B90(void) {
    return;
}

// .text:0x00040CB8 size:0x15B8
s32 fn_2_40CB8(void) {
    return 0;
}

// .text:0x00042270 size:0x8C
void fn_2_42270(s32 index) {
    lbl_2_bss_1A824C->unk197694 = 0;
    lbl_2_bss_1A824C->unk19768C = 0;
    lbl_2_bss_1A824C->unk197690 = 0;
    memcpy(&lbl_2_bss_15B8, lbl_2_data_12CE8[index], sizeof(MenusMenuBuffer));
    lbl_2_bss_1A824C->buffer = &lbl_2_bss_15B8;
}

// .text:0x000422FC size:0x8C
void fn_2_422FC(s32 index) {
    lbl_2_bss_1A824C->unk197694 = 0;
    lbl_2_bss_1A824C->unk19768C = 0;
    lbl_2_bss_1A824C->unk197690 = 0;
    memcpy(&lbl_2_bss_15B8, lbl_2_data_12C0C[index], sizeof(MenusMenuBuffer));
    lbl_2_bss_1A824C->buffer = &lbl_2_bss_15B8;
}

// .text:0x00042388 size:0xEC
void fn_2_42388(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        lbl_2_bss_1A824C->unk1976E4 = 120;
        scene->field15_0x28 = 1;
        break;
    case 1:
        if (fn_2_40CB8() != 0) scene->field15_0x28 = 2;
        break;
    case 2:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x00042474 size:0x1C
void fn_2_42474(void) {
    lbl_2_bss_1A824C->unk1976E4 = 120;
}

// .text:0x00042490 size:0x1A8
void fn_2_42490(void) {
    return;
}

// .text:0x00042638 size:0xD0
void fn_2_42638(void) {
    s32 i;
    for (i = 0; i < 20; i++) lbl_2_bss_1A824C->copiedFlags[i] = lbl_2_bss_1A8248->copiedFlags[i];
}

// .text:0x00042708 size:0x4E0
void fn_2_42708(void) {
    return;
}

// .text:0x00042BE8 size:0x2C8
void fn_2_42BE8(void) {
    return;
}

// .text:0x00042EB0 size:0x118
void fn_2_42EB0(void) {
    return;
}

// .text:0x00042FC8 size:0x12C
void fn_2_42FC8(void) {
    return;
}

// .text:0x000430F4 size:0x1F8
void fn_2_430F4(void) {
    return;
}

// .text:0x000432EC size:0x118
void fn_2_432EC(void) {
    return;
}

// .text:0x00043404 size:0x188
void fn_2_43404(void) {
    return;
}

// .text:0x0004358C size:0x444
void fn_2_4358C(void) {
    return;
}

// .text:0x000439D0 size:0x4BC
void fn_2_439D0(void) {
    return;
}

// .text:0x00043E8C size:0x188
void fn_2_43E8C(void) {
    return;
}

// .text:0x00044014 size:0x170
void fn_2_44014(void) {
    return;
}

// .text:0x00044184 size:0xB4
void fn_2_44184(void) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 9; i++) {
        if (lbl_2_bss_1A8248->choiceGrid[i][0] == 12) count++;
    }
    if (count == 0) lbl_2_bss_1A8248->unk44F7 = 1;
}

// .text:0x00044238 size:0xB0
BOOL fn_2_44238(s32 value) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 9; i++) {
        if (lbl_2_bss_1A8248->choiceGrid[i][0] == value) count++;
    }
    return count != 0;
}

// .text:0x000442E8 size:0x80
BOOL fn_2_442E8(void) {
    s32 i;
    s32 count = 0;
    for (i = 0; i < 9; i++) {
        s32 value = lbl_2_bss_1A8248->choiceGrid[i][0];
        if (value == 0 || value == 1) count++;
    }
    return count == 2;
}

// .text:0x00044368 size:0xAC
BOOL fn_2_44368(void) {
    s32 count = 0;
    s32 i;
    for (i = 0; i < 9; i++) {
        s32 value = lbl_2_bss_1A8248->choiceGrid[i][0];
        if (value == 13 || (u32)(value - 29) <= 2 || value == 32) count++;
    }
    return count >= 5;
}

// .text:0x00044414 size:0xF0
void fn_2_44414(MenusSortEntry* entries) {
    s32 i;
    s32 j;
    MenusSortEntry temp;
    for (i = 1; i < 55; i++) {
        temp = entries[i];
        entries[0] = temp;
        j = i - 1;
        while (temp.key < entries[j].key) {
            entries[j + 1] = entries[j];
            j--;
        }
        entries[j + 1] = temp;
    }
}

// .text:0x00044504 size:0x928
void fn_2_44504(void) {
    return;
}

// .text:0x00044E2C size:0xE8
s32 fn_2_44E2C(s32 index) {
    MenusLineupChoice* choice = &lbl_800E8558[index];
    if (choice->enabled == 1) {
        u8 team;
        u8* teamField = &choice->team;
        MenusLineupSlot* slot;
        s32 count = 0;
        s32 i;
        team = *teamField;
        slot = lbl_80109AE8[team];
        for (i = 0; i < 10; i++, slot++) {
            if (slot->id != -1) count++;
        }
        *teamField = team;
        return count;
    }
    return 0;
}

// .text:0x00044F14 size:0x20
s32 fn_2_44F14(s32 index) {
    Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[index];
    return obj->unk5;
}

// .text:0x00044F34 size:0x30
BOOL fn_2_44F34(s32 index) {
    Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[index];
    return obj->unk5 <= 3;
}

// .text:0x00044F64 size:0x180
void fn_2_44F64(void) {
    return;
}

// .text:0x000450E4 size:0x120
void fn_2_450E4(void) {
    return;
}

// .text:0x00045204 size:0x150
void fn_2_45204(void) {
    return;
}

// .text:0x00045354 size:0x194
void fn_2_45354(void) {
    return;
}

// .text:0x000454E8 size:0x328
void fn_2_454E8(void) {
    return;
}

// .text:0x00045810 size:0x128
void fn_2_45810(void) {
    return;
}

// .text:0x00045938 size:0x40
BOOL fn_2_45938(s32 index) {
    MenusSceneState* scene = lbl_2_bss_1A8248;
    Gap3C03CObj* obj = &scene->gap3C03CObjects[lbl_803CB8F0[scene->choices[index].choice]];
    return obj->unk31 == 0;
}

// .text:0x00045978 size:0x10C
void fn_2_45978(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[i];
        obj->previous = obj->current;
        for (j = 0; j < 10; j++) {
            obj->previousValues[j][0] = obj->currentValues[j][0];
            obj->previousValues[j][1] = obj->currentValues[j][1];
        }
        lbl_2_bss_1A8248->resetFlags[0][i] = 0;
        lbl_2_bss_1A8248->resetFlags[1][i] = 0;
        lbl_2_bss_1A8248->resetFlags[2][i] = 0;
    }
}

// .text:0x00045A84 size:0x120
void fn_2_45A84(void) {
    return;
}

// .text:0x00045BA4 size:0x194
void fn_2_45BA4(void) {
    return;
}

// .text:0x00045D38 size:0x110
void fn_2_45D38(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[i];
        obj->current = obj->previous;
    }
}

// .text:0x00045E48 size:0x194
void fn_2_45E48(void) {
    return;
}

// .text:0x00045FDC size:0x110
void fn_2_45FDC(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[i];
        obj->previous = obj->current;
    }
}

// .text:0x000460EC size:0x4
void fn_2_460EC(void) {
    return;
}

// .text:0x000460F0 size:0x4
void fn_2_460F0(void) {
    return;
}

// .text:0x000460F4 size:0x4
void fn_2_460F4(void) {
    return;
}

// .text:0x000460F8 size:0x320
void fn_2_460F8(void) {
    return;
}

// .text:0x00046418 size:0x274
void fn_2_46418(void) {
    return;
}

// .text:0x0004668C size:0x20
void fn_2_4668C(s32 index) {
    Gap3C03CObj* obj = &lbl_2_bss_1A8248->gap3C03CObjects[index];
    obj->unk31 = 1;
}

// .text:0x000466AC size:0x150
void fn_2_466AC(void) {
    return;
}

// .text:0x000467FC size:0xE0
void fn_2_467FC(void) {
    Gap3C03CObj* obj;
    s32 i;
    for (i = 0; i < 54; i++) {
        obj = &lbl_2_bss_1A8248->gap3C03CObjects[i];
        if (obj->unk4 == lbl_2_bss_1A8248->unk441C && obj->unk5 <= 3) obj->unk31 = 1;
        else obj->unk31 = 0;
    }
}

// .text:0x000468DC size:0x200
void fn_2_468DC(void) {
    return;
}

// .text:0x00046ADC size:0x148
void fn_2_46ADC(void) {
    return;
}

// .text:0x00046C24 size:0x8
s32 fn_2_46C24(void) {
    return 0;
}

// .text:0x00046C2C size:0x5C
void fn_2_46C2C(s32 unused, Vec* position) {
    Vec pos;
    pos.x = position->x;
    pos.y = position->y;
    pos.z = position->z;
    lbl_2_data_13374[0]->type = lbl_803CBD0C;
    fn_80031CA4(&pos, lbl_2_data_13374[0]);
}
