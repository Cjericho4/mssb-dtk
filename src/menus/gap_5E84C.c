#include "menus/gap_5E84C.h"
#include "game/rep_1C0.h"
#include "menus/rep_0B08.h"
#include "menus/rep_10C0.h"
#include "menus/gap_4B1AC.h"
#include "menus/gap_1B1BC.h"

extern CompressedDiskRead lbl_2_data_20C00;
extern CompressedDiskRead lbl_2_data_20BF0[];
extern s32 fn_80035838(CompressedDiskRead* list, s32 count);
extern void fn_800111B4(struct MenusSceneArchive* archive);

extern void fn_8001F228(void);
extern void fn_80035B50(s32);
#include "game/rep_3448.h"

#include "UnknownHeaders.h"
extern s16 lbl_2_data_2E80[][3];
extern void fn_80062890(s32 value);

// .text:0x0005E84C size:0x32C
void fn_2_5E84C(void) {
    return;
}

// .text:0x0005EB78 size:0x1C4
void fn_2_5EB78(void) {
    return;
}

// .text:0x0005ED3C size:0xF8
void fn_2_5ED3C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        lbl_80366B18.archives[2] = ARAMTransfer(&lbl_2_data_20C00, NULL, 1, NULL);
        scene->field15_0x28 = 1;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.allowLoad == 1) {
            fn_800111B4(lbl_80366B18.archives[2]);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if (fn_80035838(lbl_2_data_20BF0, 10) != 0) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
        break;
    }
}

// .text:0x0005EE34 size:0x88
void fn_2_5EE34(void) {
    lbl_2_bss_1A824C->flag1972BC = 1;
    lbl_2_bss_1A824C->flag1972C0 = 1;
    fn_8001F228();
    fn_80035B50(10);
    if (lbl_80366B18.tables[2] != 0) {
        fn_800ACFB0(lbl_80366B18.tables[2]);
        lbl_80366B18.tables[2] = 0;
    }
    lbl_2_bss_1A823C->unk34 = 0;
}

// .text:0x0005EEBC size:0x1D0
void fn_2_5EEBC(void) {
    return;
}

// .text:0x0005F08C size:0x21C
void fn_2_5F08C(void) {
    return;
}

// .text:0x0005F2A8 size:0x1B0
void fn_2_5F2A8(void) {
    return;
}

// .text:0x0005F458 size:0x96C
void fn_2_5F458(void) {
    return;
}

// .text:0x0005FDC4 size:0x2C0
void fn_2_5FDC4(void) {
    return;
}

// .text:0x00060084 size:0x188
void fn_2_60084(void) {
    return;
}

// .text:0x0006020C size:0x188
void fn_2_6020C(void) {
    return;
}

// .text:0x00060394 size:0x188
void fn_2_60394(void) {
    return;
}

// .text:0x0006051C size:0x2C0
void fn_2_6051C(void) {
    return;
}

// .text:0x000607DC size:0x18C
void fn_2_607DC(void) {
    return;
}

// .text:0x00060968 size:0x188
void fn_2_60968(void) {
    return;
}

// .text:0x00060AF0 size:0x188
void fn_2_60AF0(void) {
    return;
}

// .text:0x00060C78 size:0x17C
void fn_2_60C78(void) {
    return;
}

// .text:0x00060DF4 size:0x188
void fn_2_60DF4(void) {
    return;
}

// .text:0x00060F7C size:0x188
void fn_2_60F7C(void) {
    return;
}

// .text:0x00061104 size:0x1A4
void fn_2_61104(void) {
    return;
}

// .text:0x000612A8 size:0x1C0
void fn_2_612A8(void) {
    return;
}

// .text:0x00061468 size:0x1DC
void fn_2_61468(void) {
    return;
}

// .text:0x00061644 size:0x150
void fn_2_61644(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
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

// .text:0x00061794 size:0x1B4
void fn_2_61794(void) {
    return;
}

// .text:0x00061948 size:0x224
void fn_2_61948(void) {
    return;
}

// .text:0x00061B6C size:0x224
void fn_2_61B6C(void) {
    return;
}

// .text:0x00061D90 size:0x1CC
void fn_2_61D90(void) {
    return;
}

// .text:0x00061F5C size:0x1B4
void fn_2_61F5C(void) {
    return;
}

// .text:0x00062110 size:0x29C
void fn_2_62110(void) {
    return;
}

// .text:0x000623AC size:0x204
void fn_2_623AC(void) {
    return;
}

// .text:0x000625B0 size:0x244
void fn_2_625B0(void) {
    return;
}

// .text:0x000627F4 size:0x244
void fn_2_627F4(void) {
    return;
}

// .text:0x00062A38 size:0x2E0
void fn_2_62A38(void) {
    return;
}

// .text:0x00062D18 size:0x858
void fn_2_62D18(void) {
    return;
}

// .text:0x00063570 size:0x134
void fn_2_63570(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
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
    case 5: slot->timer = 26; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x000636A4 size:0x1D0
void fn_2_636A4(void) {
    return;
}

// .text:0x00063874 size:0x1F0
void fn_2_63874(void) {
    return;
}

// .text:0x00063A64 size:0x188
void fn_2_63A64(void) {
    return;
}

// .text:0x00063BEC size:0x1D0
void fn_2_63BEC(void) {
    return;
}

// .text:0x00063DBC size:0x19C
void fn_2_63DBC(void) {
    return;
}

// .text:0x00063F58 size:0x1D0
void fn_2_63F58(void) {
    return;
}

// .text:0x00064128 size:0x1D0
void fn_2_64128(void) {
    return;
}

// .text:0x000642F8 size:0x234
void fn_2_642F8(void) {
    return;
}

// .text:0x0006452C size:0x1D0
void fn_2_6452C(void) {
    return;
}

// .text:0x000646FC size:0x1D0
void fn_2_646FC(void) {
    return;
}

// .text:0x000648CC size:0x384
void fn_2_648CC(void) {
    return;
}

// .text:0x00064C50 size:0x1D0
void fn_2_64C50(void) {
    return;
}

// .text:0x00064E20 size:0x284
void fn_2_64E20(void) {
    return;
}

// .text:0x000650A4 size:0x1B4
void fn_2_650A4(void) {
    return;
}

// .text:0x00065258 size:0x17C
void fn_2_65258(void) {
    return;
}

// .text:0x000653D4 size:0x274
void fn_2_653D4(void) {
    return;
}

// .text:0x00065648 size:0x208
void fn_2_65648(void) {
    return;
}

// .text:0x00065850 size:0x1B0
void fn_2_65850(void) {
    return;
}

// .text:0x00065A00 size:0x284
void fn_2_65A00(void) {
    return;
}

// .text:0x00065C84 size:0x1CC
void fn_2_65C84(void) {
    return;
}

// .text:0x00065E50 size:0x1E8
void fn_2_65E50(void) {
    return;
}

// .text:0x00066038 size:0x150
void fn_2_66038(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
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

// .text:0x00066188 size:0x1B4
void fn_2_66188(void) {
    return;
}

// .text:0x0006633C size:0x284
void fn_2_6633C(void) {
    return;
}

// .text:0x000665C0 size:0x19C
void fn_2_665C0(void) {
    return;
}

// .text:0x0006675C size:0x128
void fn_2_6675C(DrawingSceneStruct* scene, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0:
        lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        slot->state = 0x26;
        break;
    case 1: break;
    case 2: slot->state = 0x25; break;
    case 5: slot->timer = 40; slot->state = 6; break;
    case 6:
        if (slot->timer-- <= 0) {
            lbl_80371C30[scene->unkIndex + slot->index].obj->flags &= ~2;
        }
        break;
    case 0x25: break;
    }
}

// .text:0x00066884 size:0x268
void fn_2_66884(void) {
    return;
}

// .text:0x00066AEC size:0x1D8
void fn_2_66AEC(void) {
    return;
}

// .text:0x00066CC4 size:0x150
void fn_2_66CC4(void) {
    return;
}

// .text:0x00066E14 size:0x1B4
void fn_2_66E14(void) {
    return;
}

// .text:0x00066FC8 size:0x214
void fn_2_66FC8(void) {
    return;
}

// .text:0x000671DC size:0x1B4
void fn_2_671DC(void) {
    return;
}

// .text:0x00067390 size:0x1F8
void fn_2_67390(void) {
    return;
}

// .text:0x00067588 size:0x1F8
void fn_2_67588(void) {
    return;
}

// .text:0x00067780 size:0x414
void fn_2_67780(void) {
    return;
}

// .text:0x00067B94 size:0x1B4
void fn_2_67B94(void) {
    return;
}

// .text:0x00067D48 size:0x2A4
void fn_2_67D48(void) {
    return;
}

// .text:0x00067FEC size:0x1B4
void fn_2_67FEC(void) {
    return;
}

// .text:0x000681A0 size:0x94
void fn_2_681A0(s32 unused, MenusResourceSlot* slot) {
    s32 result = fn_2_53BC8(slot);
    if ((s16)result != -1) slot->state = result;
    switch (slot->state) {
    case 0: slot->state = 0x26; break;
    case 1: break;
    case 2: slot->state = 0x25; break;
    case 5: break;
    case 0x25: break;
    }
}

// .text:0x00068234 size:0x2C
void fn_2_68234(DrawingSceneStruct* scene, Rep0788Item* item) {
    lbl_80371C30[scene->unkIndex + item->index].obj->flags &= ~2;
}

// .text:0x00068260 size:0xA8
void fn_2_68260(Rep0B08Obj* obj) {
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

// .text:0x00068308 size:0x24
void fn_2_68308(void) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[1];
    obj->variant = 0;
    obj->state = 0;
    lbl_2_bss_1A8248->unk442F = 0;
}
