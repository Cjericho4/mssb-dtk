#include "menus/rep_0788.h"
#include "menus/gap_4B1AC.h"
#include "menus/rep_10C0.h"
#include "menus/gap_0.h"
#include "UnknownHeaders.h"
#include "game/rep_3448.h"

extern s16 lbl_2_data_2E44[][4];
extern s16 lbl_2_data_3D30[][4];
extern MenusResourceEntry lbl_2_data_1073C[];
extern MenusResourceEntry lbl_2_data_105FC[];
extern MenusResourceEntry lbl_2_data_F0EC[];
extern MenusResourceEntry lbl_2_data_9FC8[];
extern MenusResourceEntry lbl_2_data_104EC[];

#include "menus/gap_71EC4.h"
extern MenusSceneScript lbl_2_data_4C68;
extern MenusSceneScript lbl_2_data_1048C;
extern MenusSceneScript lbl_2_data_1059C;
extern void fn_8000FE54(void);
extern void fn_8000F8F4(DrawingSceneStruct* scene);
extern MenusSceneScript lbl_2_data_1061C;
extern MenusSceneScript lbl_2_data_C96C;
#include "menus/rep_0F60.h"
#include "menus/rep_08E8.h"
#include "menus/rep_0B08.h"
#include "Dolphin/GX/GXPixel.h"
#include "menus/gap_1B1BC.h"

// .text:0x0001D440 size:0x2ACC
void fn_2_1D440(void) {
    return;
}

// .text:0x0001FF0C size:0x4
void fn_2_1FF0C(void) {
    return;
}

// .text:0x0001FF10 size:0x4
void fn_2_1FF10(void) {
    return;
}

// .text:0x0001FF14 size:0xB0
void fn_2_1FF14(void) {
    return;
}

// .text:0x0001FFC4 size:0xB0
void fn_2_1FFC4(void) {
    return;
}

// .text:0x00020074 size:0x70
s32 fn_2_20074(void) {
    u16 buttons = lbl_803C77B8.controllers[lbl_2_bss_1A824C->inputIndex].buttons;
    if (buttons & 8) return 0;
    if (buttons & 4) return 1;
    if (buttons & 1) return 2;
    if (!(buttons & 2)) goto no_input;
    return 3;
no_input:
    return -1;
}

// .text:0x000200E4 size:0x100
s32 fn_2_200E4(void) {
    s32 count;
    if (lbl_2_bss_1A8248->choices[lbl_2_bss_1A8248->rep0B08Objects[0].unkB0].unk6 == 1) return 0;
    if (lbl_2_bss_1A8248->choices[lbl_2_bss_1A8248->rep0B08Objects[0].unkB0].id == 5) return 0;
    count = lbl_2_bss_1A8248->unk442B;
    if (count > 3) count = 3;
    if (lbl_2_data_2E44[lbl_2_bss_1A8248->unk4415][count] >= rand() % 100 && lbl_2_bss_1A8248->unk441C != 5) {
        if (lbl_2_bss_1A8248->unk4422 == 0) return 0;
        if (lbl_2_bss_1A8248->unk442B < 3) lbl_2_bss_1A8248->unk442B++;
        return 1;
    }
    return 0;
}

// .text:0x000201E4 size:0x34
s16 fn_2_201E4(s16 row, s16 column) {
    if (column < 0) return -1;
    return lbl_2_data_3D30[row][column];
}

// .text:0x00020218 size:0x40
void fn_2_20218(void) {
    lbl_2_bss_1A824C->unk19782B = 0;
    lbl_2_bss_1A824C->unk19782C = 0;
    lbl_2_bss_1A824C->unk19782A = 0;
    lbl_2_bss_1A824C->unk197832 = 0;
}

// .text:0x00020258 size:0x4
void fn_2_20258(void) {
    return;
}

// .text:0x0002025C size:0xCC
void fn_2_2025C(void) {
    MenusSceneState* scene = lbl_2_bss_1A8248;
    if (scene->unk44F2 == 2) g_hugeAnimStruct.field269_0x307a = 0;
    else if (lbl_2_bss_1A824C->unk1978F3 != 0) g_hugeAnimStruct.field269_0x307a = 4;
    if (g_hugeAnimStruct.field269_0x307a == 4 && scene->unk44F2 != 3) {
        if (scene->unk44F2 != 4) fn_2_68E68();
        fn_2_8FD14();
        fn_2_8AEE0();
        fn_2_47FF8();
        if (lbl_2_bss_1A8248->unk44F2 != 4) fn_2_47CFC();
    }
    GXSetZCompLoc(0);
}

// .text:0x00020328 size:0x4D4
void fn_2_20328(void) {
    return;
}

// .text:0x000207FC size:0x4B4
void fn_2_207FC(void) {
    return;
}

// .text:0x00020CB0 size:0x58
s32 fn_2_20CB0(u32 value) {
    s32 result = 0;
    switch (value) {
    case 0: result = 0; break;
    case 4: result = 1; break;
    case 10: result = 2; break;
    case 2: result = 3; break;
    case 6: result = 4; break;
    case 9: result = 5; break;
    }
    return result;
}

// .text:0x00020D08 size:0x3464
void fn_2_20D08(void) {
    return;
}

// .text:0x0002416C size:0xCC
void fn_2_2416C(void) {
    DrawingSceneStruct* scene;
    switch ((s32)(scene = lbl_803CC1B8)->eventID) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_1061C);
        scene->eventID = 1;
        scene->unk18 = 0;
        break;
    case 1: break;
    }
    fn_2_53F88((s32)scene);
    fn_2_54120();
    if (lbl_2_bss_1A8234->panels[1].pending) {
        fn_8000FE54();
        fn_2_53DF8(scene);
        fn_8000F8F4(scene);
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->eventID = 0;
        lbl_2_bss_1A8234->panels[1].pending = 0;
    }
}

// .text:0x00024238 size:0xC4
void fn_2_24238(void) {
    DrawingSceneStruct* scene;
    switch ((s32)(scene = lbl_803CC1B8)->eventID) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_1059C);
        scene->eventID = 1;
        scene->unk18 = 0;
        break;
    case 1: break;
    }
    fn_2_53F88((s32)scene);
    fn_2_54120();
    if (lbl_2_bss_1A8234->panels[1].pending) {
        fn_8000FE54();
        fn_2_53DF8(scene);
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->eventID = 0;
        lbl_2_bss_1A8234->panels[1].pending = 0;
    }
}

// .text:0x000242FC size:0xC0
void fn_2_242FC(void) {
    DrawingSceneStruct* scene;
    switch ((s32)(scene = lbl_803CC1B8)->fielderIndex) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_1048C);
        scene->fielderIndex = 1;
        scene->unk1a = 0;
        break;
    case 1: break;
    }
    fn_2_53F04((s32)scene);
    fn_2_5400C();
    if (lbl_2_bss_1A8230->pending) {
        fn_2_53CEC(scene);
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->fielderIndex = 0;
        lbl_2_bss_1A8230->pending = 0;
    }
}

// .text:0x000243BC size:0xCC
void fn_2_243BC(void) {
    DrawingSceneStruct* scene;
    switch ((s32)(scene = lbl_803CC1B8)->eventID) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_C96C);
        scene->eventID = 1;
        scene->unk18 = 0;
        break;
    case 1: break;
    }
    fn_2_53F88((s32)scene);
    fn_2_54120();
    if (lbl_2_bss_1A8234->panels[1].pending) {
        fn_8000FE54();
        fn_2_53DF8(scene);
        fn_8000F8F4(scene);
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->eventID = 0;
        lbl_2_bss_1A8234->panels[1].pending = 0;
    }
}

// .text:0x00024488 size:0x140
void fn_2_24488(void) {
    DrawingSceneStruct* scene;
    switch ((s32)*(u16*)&(scene = lbl_803CC1B8)->unk_1C) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_4C68);
        scene->unk_1C = 1;
        scene->unk18 = 0;
        break;
    case 1:
        if ((s32)lbl_2_bss_1A824C->displayMode == 1) {
            lbl_2_bss_1A8234->flags[1][64] = 1;
            lbl_2_bss_1A8234->flags[8][64] = 0;
        } else {
            lbl_2_bss_1A8234->flags[8][64] = 1;
            lbl_2_bss_1A8234->flags[1][64] = 0;
        }
        break;
    }
    fn_2_53F88((s32)scene);
    fn_2_54120();
    if (lbl_2_bss_1A8234->panels[1].pending != 0) {
        fn_8000FE54();
        fn_2_53DF8(scene);
        fn_8000F8F4(scene);
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->unk_1C = 0;
        lbl_2_bss_1A8234->panels[1].pending = 0;
    }
}

// .text:0x000245C8 size:0x44
void fn_2_245C8(void) {
    QueueEntry* task = fn_800B0A5C_insertQueue(fn_2_2416C, 2);
    task->unk1C = 0;
    fn_2_54354(lbl_2_data_1073C, 8);
}

// .text:0x0002460C size:0x44
void fn_2_2460C(void) {
    QueueEntry* task = fn_800B0A5C_insertQueue(fn_2_24238, 2);
    task->unk1C = 0;
    fn_2_54354(lbl_2_data_105FC, 2);
}

// .text:0x00024650 size:0x4C
void fn_2_24650(void) {
    QueueEntry* task = fn_800B0A5C_insertQueue(fn_2_242FC, 2);
    task->unk1C = 0;
    task->unk1E = 0;
    fn_2_54234(lbl_2_data_104EC, 2);
}

// .text:0x0002469C size:0x44
void fn_2_2469C(void) {
    QueueEntry* task = fn_800B0A5C_insertQueue(fn_2_243BC, 2);
    task->unk1C = 0;
    fn_2_54354(lbl_2_data_F0EC, 314);
}

// .text:0x000246E0 size:0x44
void fn_2_246E0(void) {
    QueueEntry* task = fn_800B0A5C_insertQueue(fn_2_24488, 2);
    task->unk1C = 0;
    fn_2_54354(lbl_2_data_9FC8, 659);
}

// .text:0x00024724 size:0x4
void fn_2_24724(void) {
    return;
}

// .text:0x00024728 size:0xD8
BOOL fn_2_24728(s32 side) {
    MenusSceneState* scene = lbl_2_bss_1A8248;
    s32 i;
    for (i = 0; i < 51; i++) {
        if (scene->choices[i].state == 0 && scene->choices[i].flag == 1 && scene->choices[i].side == side && scene->readyFlags[side] == 1) return 1;
    }
    return 0;
}

// .text:0x00024800 size:0x69C
void fn_2_24800(void) {
    return;
}

// .text:0x00024E9C size:0x14
s16 fn_2_24E9C(void) {
    return lbl_803CC1B8->loadingState;
}

// .text:0x00024EB0 size:0x14
void fn_2_24EB0(s16 state) {
    lbl_803CC1B8->loadingState = state;
}

// .text:0x00024EC4 size:0x18C
void fn_2_24EC4(void) {
    return;
}

// .text:0x00025050 size:0x1B0
void fn_2_25050(void) {
    return;
}

// .text:0x00025200 size:0x1B0
void fn_2_25200(void) {
    return;
}

// .text:0x000253B0 size:0x174
void fn_2_253B0(void) {
    return;
}

// .text:0x00025524 size:0x258
void fn_2_25524(void) {
    return;
}

// .text:0x0002577C size:0xD4
void fn_2_2577C(DrawingSceneStruct* scene, Rep0788Item* item) {
    s32 result = fn_2_53BC8(item);
    if ((s16)result != -1) item->state = result;
    switch (item->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1: break;
    case 2: item->state = 0x25; break;
    case 5: break;
    case 8: break;
    case 0x24: break;
    case 0x25: break;
    }
}

// .text:0x00025850 size:0x2C
void fn_2_25850(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x0002587C size:0x1A0
void fn_2_2587C(void) {
    return;
}

// .text:0x00025A1C size:0x2C
void fn_2_25A1C(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x00025A48 size:0x324
void fn_2_25A48(void) {
    return;
}

// .text:0x00025D6C size:0x2C
void fn_2_25D6C(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x00025D98 size:0x118
void fn_2_25D98(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x5C = lbl_2_bss_1A8248->unk441C << 16;
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00025EB0 size:0x160
void fn_2_25EB0(void) {
    return;
}

// .text:0x00026010 size:0x160
void fn_2_26010(void) {
    return;
}

// .text:0x00026170 size:0x160
void fn_2_26170(void) {
    return;
}

// .text:0x000262D0 size:0x3B4
void fn_2_262D0(void) {
    return;
}

// .text:0x00026684 size:0xF0
void fn_2_26684(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00026774 size:0xF0
void fn_2_26774(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00026864 size:0x290
void fn_2_26864(void) {
    return;
}

// .text:0x00026AF4 size:0x17C
void fn_2_26AF4(void) {
    return;
}

// .text:0x00026C70 size:0x310
void fn_2_26C70(void) {
    return;
}

// .text:0x00026F80 size:0x138
void fn_2_26F80(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x5C = lbl_2_bss_1A8248->unk441C << 16;
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x68 = 0;
        slot->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x000270B8 size:0x204
void fn_2_270B8(void) {
    return;
}

// .text:0x000272BC size:0x2C
void fn_2_272BC(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x000272E8 size:0x1B4
void fn_2_272E8(void) {
    return;
}

// .text:0x0002749C size:0x1C4
void fn_2_2749C(void) {
    return;
}

// .text:0x00027660 size:0x1C4
void fn_2_27660(void) {
    return;
}

// .text:0x00027824 size:0x1D0
void fn_2_27824(void) {
    return;
}

// .text:0x000279F4 size:0x188
void fn_2_279F4(void) {
    return;
}

// .text:0x00027B7C size:0x210
void fn_2_27B7C(void) {
    return;
}

// .text:0x00027D8C size:0x150
void fn_2_27D8C(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 5: slot->timer = 3; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x00027EDC size:0x1B4
void fn_2_27EDC(void) {
    return;
}

// .text:0x00028090 size:0x194
void fn_2_28090(void) {
    return;
}

// .text:0x00028224 size:0x138
void fn_2_28224(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x5C = 0;
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        break;
    case 0x25: break;
    }
}

// .text:0x0002835C size:0x154
void fn_2_2835C(void) {
    return;
}

// .text:0x000284B0 size:0x2E4
void fn_2_284B0(void) {
    return;
}

// .text:0x00028794 size:0x1B4
void fn_2_28794(void) {
    return;
}

// .text:0x00028948 size:0x3DC
void fn_2_28948(void) {
    return;
}

// .text:0x00028D24 size:0x17C
void fn_2_28D24(void) {
    return;
}

// .text:0x00028EA0 size:0x3CC
void fn_2_28EA0(void) {
    return;
}

// .text:0x0002926C size:0x618
void fn_2_2926C(void) {
    return;
}

// .text:0x00029884 size:0x694
void fn_2_29884(void) {
    return;
}

// .text:0x00029F18 size:0x150
void fn_2_29F18(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 5: slot->timer = 40; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x0002A068 size:0x1B4
void fn_2_2A068(void) {
    return;
}

// .text:0x0002A21C size:0x11C
void fn_2_2A21C(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        break;
    case 0x25: break;
    }
}

// .text:0x0002A338 size:0x444
void fn_2_2A338(void) {
    return;
}

// .text:0x0002A77C size:0x310
void fn_2_2A77C(void) {
    return;
}

// .text:0x0002AA8C size:0x2A4
void fn_2_2AA8C(void) {
    return;
}

// .text:0x0002AD30 size:0x1AC
void fn_2_2AD30(void) {
    return;
}

// .text:0x0002AEDC size:0x188
void fn_2_2AEDC(void) {
    return;
}

// .text:0x0002B064 size:0x1EC
void fn_2_2B064(void) {
    return;
}

// .text:0x0002B250 size:0x1EC
void fn_2_2B250(void) {
    return;
}

// .text:0x0002B43C size:0x218
void fn_2_2B43C(void) {
    return;
}

// .text:0x0002B654 size:0x230
void fn_2_2B654(void) {
    return;
}

// .text:0x0002B884 size:0x2B0
void fn_2_2B884(void) {
    return;
}

// .text:0x0002BB34 size:0x270
void fn_2_2BB34(void) {
    return;
}

// .text:0x0002BDA4 size:0x17C
void fn_2_2BDA4(void) {
    return;
}

// .text:0x0002BF20 size:0x288
void fn_2_2BF20(void) {
    return;
}

// .text:0x0002C1A8 size:0x1D0
void fn_2_2C1A8(void) {
    return;
}

// .text:0x0002C378 size:0x16C
void fn_2_2C378(void) {
    return;
}

// .text:0x0002C4E4 size:0x1B4
void fn_2_2C4E4(void) {
    return;
}

// .text:0x0002C698 size:0x1C8
void fn_2_2C698(void) {
    return;
}

// .text:0x0002C860 size:0x1D0
void fn_2_2C860(void) {
    return;
}

// .text:0x0002CA30 size:0x19C
void fn_2_2CA30(void) {
    return;
}

// .text:0x0002CBCC size:0x1D8
void fn_2_2CBCC(void) {
    return;
}

// .text:0x0002CDA4 size:0x1B4
void fn_2_2CDA4(void) {
    return;
}

// .text:0x0002CF58 size:0x17C
void fn_2_2CF58(void) {
    return;
}

// .text:0x0002D0D4 size:0x434
void fn_2_2D0D4(void) {
    return;
}

// .text:0x0002D508 size:0x138
void fn_2_2D508(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x68 = 1;
        slot->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        break;
    case 0x25: break;
    }
}

// .text:0x0002D640 size:0x284
void fn_2_2D640(void) {
    return;
}

// .text:0x0002D8C4 size:0x1E4
void fn_2_2D8C4(void) {
    return;
}

// .text:0x0002DAA8 size:0x200
void fn_2_2DAA8(void) {
    return;
}

// .text:0x0002DCA8 size:0x1D0
void fn_2_2DCA8(void) {
    return;
}

// .text:0x0002DE78 size:0x150
void fn_2_2DE78(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 5: slot->timer = 40; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x0002DFC8 size:0x1B4
void fn_2_2DFC8(void) {
    return;
}

// .text:0x0002E17C size:0x11C
void fn_2_2E17C(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
        break;
    case 0x25: break;
    }
}

// .text:0x0002E298 size:0x1B4
void fn_2_2E298(void) {
    return;
}

// .text:0x0002E44C size:0x17C
void fn_2_2E44C(void) {
    return;
}

// .text:0x0002E5C8 size:0x208
void fn_2_2E5C8(void) {
    return;
}

// .text:0x0002E7D0 size:0x414
void fn_2_2E7D0(void) {
    return;
}

// .text:0x0002EBE4 size:0x3E8
void fn_2_2EBE4(void) {
    return;
}

// .text:0x0002EFCC size:0x578
void fn_2_2EFCC(void) {
    return;
}

// .text:0x0002F544 size:0x1CC
void fn_2_2F544(void) {
    return;
}

// .text:0x0002F710 size:0x194
void fn_2_2F710(void) {
    return;
}

// .text:0x0002F8A4 size:0x1D8
void fn_2_2F8A4(void) {
    return;
}

// .text:0x0002FA7C size:0x150
void fn_2_2FA7C(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x68 = 1;
        slot->state = 0x25;
        break;
    case 0x11: slot->state = 0x25; break;
    case 5: slot->timer = 25; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x0002FBCC size:0x134
void fn_2_2FBCC(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 0x11: slot->state = 0x25; break;
    case 5: slot->timer = 25; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x0002FD00 size:0x150
void fn_2_2FD00(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + slot->index].obj->field_0x68 = 1;
        slot->state = 0x25;
        break;
    case 0x11: slot->state = 0x25; break;
    case 5: slot->timer = 14; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x0002FE50 size:0x26C
void fn_2_2FE50(void) {
    return;
}

// .text:0x000300BC size:0x2E0
void fn_2_300BC(void) {
    return;
}

// .text:0x0003039C size:0x33C
void fn_2_3039C(void) {
    return;
}

// .text:0x000306D8 size:0x1BC
void fn_2_306D8(void) {
    return;
}

// .text:0x00030894 size:0x3B8
void fn_2_30894(void) {
    return;
}

// .text:0x00030C4C size:0x134
void fn_2_30C4C(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 0x11: slot->state = 0x25; break;
    case 5: slot->timer = 14; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x00030D80 size:0x178
void fn_2_30D80(void) {
    return;
}

// .text:0x00030EF8 size:0x1A4
void fn_2_30EF8(void) {
    return;
}

// .text:0x0003109C size:0x1B4
void fn_2_3109C(void) {
    return;
}

// .text:0x00031250 size:0x134
void fn_2_31250(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 0x11: slot->state = 0x25; break;
    case 5: slot->timer = 14; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x00031384 size:0x1B4
void fn_2_31384(void) {
    return;
}

// .text:0x00031538 size:0x1C0
void fn_2_31538(void) {
    return;
}

// .text:0x000316F8 size:0x188
void fn_2_316F8(void) {
    return;
}

// .text:0x00031880 size:0x210
void fn_2_31880(void) {
    return;
}

// .text:0x00031A90 size:0x150
void fn_2_31A90(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags |= 2;
        slot->state = 0x25;
        break;
    case 5: slot->timer = 3; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x00031BE0 size:0x1B4
void fn_2_31BE0(void) {
    return;
}

// .text:0x00031D94 size:0x1BC
void fn_2_31D94(void) {
    return;
}

// .text:0x00031F50 size:0x188
void fn_2_31F50(void) {
    return;
}

// .text:0x000320D8 size:0x20C
void fn_2_320D8(void) {
    return;
}

// .text:0x000322E4 size:0x150
void fn_2_322E4(void) {
    return;
}

// .text:0x00032434 size:0x1B4
void fn_2_32434(void) {
    return;
}

// .text:0x000325E8 size:0x1EC
void fn_2_325E8(void) {
    return;
}

// .text:0x000327D4 size:0xF0
void fn_2_327D4(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x000328C4 size:0x1B4
void fn_2_328C4(void) {
    return;
}

// .text:0x00032A78 size:0x1EC
void fn_2_32A78(void) {
    return;
}

// .text:0x00032C64 size:0xF0
void fn_2_32C64(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00032D54 size:0x1B4
void fn_2_32D54(void) {
    return;
}

// .text:0x00032F08 size:0x2C0
void fn_2_32F08(void) {
    return;
}

// .text:0x000331C8 size:0x44C
void fn_2_331C8(void) {
    return;
}

// .text:0x00033614 size:0x10C
void fn_2_33614(DrawingSceneStruct* scene, Rep0788Item* item) {
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
        lbl_80371C30[scene->unkIndex + item->index].obj->field_0x68 = 0;
        item->state = 0x25;
        break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00033720 size:0x1B4
void fn_2_33720(void) {
    return;
}

// .text:0x000338D4 size:0x59C
void fn_2_338D4(void) {
    return;
}
