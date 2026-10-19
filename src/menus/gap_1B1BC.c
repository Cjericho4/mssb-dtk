#include "menus/gap_1B1BC.h"
#include "menus/rep_0B08.h"
#include "menus/gap_4B1AC.h"
#include "UnknownHeaders.h"
#include "menus/gap_3C03C.h"

extern void fn_8001F228(void);
extern void fn_80021410(void);

extern void fn_80068720(s32 state);

// .text:0x0001B1BC size:0x158
void fn_2_1B1BC(void) {
    return;
}

// .text:0x0001B314 size:0x218
void fn_2_1B314(void) {
    return;
}

// .text:0x0001B52C size:0x94
void fn_2_1B52C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        if (fn_2_4E970() == 1) scene->field15_0x28 = 1;
        break;
    case 1:
        scene->field15_0x28 = 6;
        break;
    case 6:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x0001B5C0 size:0x10C
void fn_2_1B5C0(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0: {
        QueueEntry* entry = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        entry->unk28 = 0;
        scene->loadingState = 0;
        scene->field15_0x28 = 1;
        break;
    }
    case 1:
        if (scene->loadingState == 1) scene->field15_0x28 = 2;
        break;
    case 2:
        if (fn_2_4EB64() == 1) scene->field15_0x28 = 3;
        break;
    case 3:
        if (fn_2_4EB2C() == 1) scene->field15_0x28 = 4;
        break;
    case 4:
        if (fn_2_4EAF4() == 1) scene->field15_0x28 = 5;
        break;
    case 5:
        if (fn_2_4E9A8() == 1) scene->field15_0x28 = 6;
        break;
    case 6:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x0001B6CC size:0xE8
void fn_2_1B6CC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0: {
        QueueEntry* entry = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        entry->unk28 = 0;
        scene->loadingState = 0;
        scene->field15_0x28 = 1;
        break;
    }
    case 1:
        if (scene->loadingState == 1) scene->field15_0x28 = 2;
        break;
    case 2:
        if (fn_2_4EB64() == 1) scene->field15_0x28 = 3;
        break;
    case 3:
        if (fn_2_4EB2C() == 1) scene->field15_0x28 = 4;
        break;
    case 4:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x0001B7B4 size:0x79C
void fn_2_1B7B4(void) {
    return;
}

// .text:0x0001BF50 size:0x80
void fn_2_1BF50(void) {
    fn_80068720(13);
    lbl_2_bss_1A824C->flag1972BC = 1;
    lbl_2_bss_1A824C->flag1972C0 = 1;
    lbl_2_bss_1A824C->unk1976D6 = 0;
    lbl_2_bss_1A8248->unk44F2 = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C->unk34 = 0;
}

// .text:0x0001BFD0 size:0x104
void fn_2_1BFD0(void) {
    fn_80068720(10);
    lbl_2_bss_1A824C->flag1972BC = 1;
    lbl_2_bss_1A824C->flag1972C0 = 1;
    lbl_2_bss_1A824C->unk1976D6 = 0;
    lbl_2_bss_1A8248->unk44F2 = 0;
    if (lbl_2_bss_1A824C->unk197864 == 0) fn_2_4E7EC();
    fn_8001F228();
    fn_80021410();
    fn_800ACFB0(lbl_800EF808.ptrArray[0]);
    if (lbl_2_bss_1A8248->unk44F4 != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
    }
    fn_2_4E94C();
    if (lbl_80366B18.archive != NULL) {
        fn_800ACFB0(lbl_80366B18.archive);
        lbl_80366B18.archive = NULL;
    }
    lbl_2_bss_1A823C->unk34 = 0;
}

// .text:0x0001C0D4 size:0x148
void fn_2_1C0D4(void) {
    return;
}

// .text:0x0001C21C size:0x28
void fn_2_1C21C(void) {
    Vec position;
    fn_2_68DAC(0, &position);
}

// .text:0x0001C244 size:0xF8
void fn_2_1C244(void) {
    MenusDisplayState* state = lbl_2_bss_1A8234;
    s32 bank;
    s32 slot;
    for (bank = 0; bank < 70; bank++) {
        for (slot = 0; slot < 864; slot++) {
            if (bank >= 35 && slot >= 100 && state->banks[bank].slots[slot].callback != NULL) return;
        }
    }
}

// .text:0x0001C33C size:0x6C
void fn_2_1C33C(void) {
    MenusSceneState* scene = lbl_2_bss_1A8248;

    if (scene->unk441C >= 6) {
        while (1) {}
    }
    if (scene->unk4415 >= 4) {
        while (1) {}
    }
    if (scene->counter < 0 || scene->counter > 999) {
        while (1) {}
    }
    if (lbl_2_bss_1A823C->state == 5 && scene->unk4420 >= 5) {
        while (1) {}
    }
}

// .text:0x0001C3A8 size:0x74
void fn_2_1C3A8(void) {
    if ((s32)lbl_2_bss_1A824C->displayMode == 1) {
        lbl_2_bss_1A8234->panels[0].active = 1;
        lbl_2_bss_1A8234->panels[1].active = 0;
    } else {
        lbl_2_bss_1A8234->panels[1].active = 1;
        lbl_2_bss_1A8234->panels[0].active = 0;
    }
}

// .text:0x0001C41C size:0x74
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234->panels[0].visible = 1;
    lbl_2_bss_1A8234->panels[0].controls[0] = 1;
    lbl_2_bss_1A8234->panels[0].controls[1] = 1;
    lbl_2_bss_1A8234->panels[0].controls[2] = 1;
    lbl_2_bss_1A8234->panels[1].visible = 0;
    lbl_2_bss_1A8234->panels[1].controls[0] = 0;
    lbl_2_bss_1A8234->panels[1].controls[1] = 0;
    lbl_2_bss_1A8234->panels[1].controls[2] = 0;
}

// .text:0x0001C490 size:0x74
void fn_2_1C490(void) {
    lbl_2_bss_1A8234->panels[1].visible = 1;
    lbl_2_bss_1A8234->panels[1].controls[0] = 1;
    lbl_2_bss_1A8234->panels[1].controls[1] = 1;
    lbl_2_bss_1A8234->panels[1].controls[2] = 1;
    lbl_2_bss_1A8234->panels[0].visible = 0;
    lbl_2_bss_1A8234->panels[0].controls[0] = 0;
    lbl_2_bss_1A8234->panels[0].controls[1] = 0;
    lbl_2_bss_1A8234->panels[0].controls[2] = 0;
}

// .text:0x0001C504 size:0xC4
void fn_2_1C504(s32 id) {
    s32 i;
    for (i = 0; i < 51; i++) {
        if (id == lbl_2_bss_1A8248->choices[i].id &&
            (lbl_2_bss_1A8248->choices[i].state == 1 || lbl_2_bss_1A8248->choices[i].state == 0)) {
            if (lbl_2_bss_1A8248->unk441C == 5) {
                if (lbl_2_bss_1A8248->choices[i].flag == 1) lbl_2_bss_1A8248->choices[i].state = 3;
                else lbl_2_bss_1A8248->choices[i].state = 0;
            } else lbl_2_bss_1A8248->choices[i].state = 0;
        }
    }
    lbl_2_bss_1A8248->choiceFlags[id] = 1;
    if (!(lbl_2_bss_1A8248->choiceMask & (1 << id))) {
        lbl_2_bss_1A8248->unk4423++;
        lbl_2_bss_1A8248->choiceMask |= 1 << id;
    }
}

// .text:0x0001C5C8 size:0x14C
void fn_2_1C5C8(s32 id) {
    u32 i;
    for (i = 0; i < 51; i++) {
        if (id == lbl_2_bss_1A8248->choices[i].id && ((u32)lbl_2_bss_1A8248->choices[i].state == 1 || (u32)lbl_2_bss_1A8248->choices[i].state == 0)) {
            if (lbl_2_bss_1A8248->choices[i].flag == 0 && lbl_2_bss_1A8248->unk441C != id) {
                if (lbl_2_bss_1A8248->unk441C == 5) lbl_2_bss_1A8248->choices[i].state = 3;
                else lbl_2_bss_1A8248->choices[i].state = 2;
            } else lbl_2_bss_1A8248->choices[i].state = 0;
            if (lbl_2_bss_1A8248->choices[i].flag == 2) lbl_2_bss_1A8248->choices[i].state = 0;
        }
        if ((u32)lbl_2_bss_1A8248->choices[i].id == 6 || (u32)lbl_2_bss_1A8248->choices[i].id == 7 || (u32)lbl_2_bss_1A8248->choices[i].id == 8) {
            lbl_2_bss_1A8248->choices[i].state = 0;
            lbl_2_bss_1A8248->choiceFlags[6] = 1;
            lbl_2_bss_1A8248->choiceFlags[7] = 1;
            lbl_2_bss_1A8248->choiceFlags[8] = 1;
        }
    }
    lbl_2_bss_1A8248->choiceFlags[id] = 1;
    if (lbl_2_bss_1A8248->unk441C != id) {
        s32 flag = 1 << id;
        if (!(lbl_2_bss_1A8248->unk4426 & flag)) {
            lbl_2_bss_1A8248->unk4422++;
            lbl_2_bss_1A8248->unk4426 |= flag;
        }
    }
}

// .text:0x0001C714 size:0x14C
void fn_2_1C714(s32 id) {
    u32 i;
    for (i = 0; i < 51; i++) {
        if (id == lbl_2_bss_1A8248->choices[i].id && ((u32)lbl_2_bss_1A8248->choices[i].state == 1 || (u32)lbl_2_bss_1A8248->choices[i].state == 0)) {
            if (lbl_2_bss_1A8248->choices[i].flag == 0 && lbl_2_bss_1A8248->unk441C != id) {
                if (lbl_2_bss_1A8248->unk441C == 5) lbl_2_bss_1A8248->choices[i].state = 3;
                else lbl_2_bss_1A8248->choices[i].state = 0;
            } else lbl_2_bss_1A8248->choices[i].state = 0;
            if (lbl_2_bss_1A8248->choices[i].flag == 2) lbl_2_bss_1A8248->choices[i].state = 0;
        }
        if ((u32)lbl_2_bss_1A8248->choices[i].id == 6 || (u32)lbl_2_bss_1A8248->choices[i].id == 7 || (u32)lbl_2_bss_1A8248->choices[i].id == 8) {
            lbl_2_bss_1A8248->choices[i].state = 0;
            lbl_2_bss_1A8248->choiceFlags[6] = 1;
            lbl_2_bss_1A8248->choiceFlags[7] = 1;
            lbl_2_bss_1A8248->choiceFlags[8] = 1;
        }
    }
    lbl_2_bss_1A8248->choiceFlags[id] = 1;
    if (lbl_2_bss_1A8248->unk441C != id) {
        s32 flag = 1 << id;
        if (!(lbl_2_bss_1A8248->unk4426 & flag)) {
            lbl_2_bss_1A8248->unk4422++;
            lbl_2_bss_1A8248->unk4426 |= flag;
        }
    }
}

// .text:0x0001C860 size:0x734
void fn_2_1C860(void) {
    return;
}

// .text:0x0001CF94 size:0x4AC
void fn_2_1CF94(void) {
    return;
}
