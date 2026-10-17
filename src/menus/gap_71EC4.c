#include "menus/gap_71EC4.h"
extern void (*lbl_2_data_2A2EC[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A1E8[])(Rep0B08Obj*);
#include "UnknownHeaders.h"
#include "menus/gap_D08.h"

extern void fn_800625A4(s32, s32);
extern void fn_800626EC(s32);
extern void fn_80062674(s32);
#include "menus/gap_1254.h"

// .text:0x00071EC4 size:0x38
void fn_2_71EC4(Rep0B08Obj* obj) {
    lbl_2_data_2A1E8[obj->state](obj);
}

// .text:0x00071EFC size:0x24
void fn_2_71EFC(Rep0B08Obj* obj) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[obj->index];
    target->unkC0 = 0;
}

// .text:0x00071F20 size:0x40
void fn_2_71F20(Rep0B08Obj* obj) {
    obj->callback = lbl_2_data_2A2EC[obj->variant];
    obj->callback(obj);
}

// .text:0x00071F60 size:0xD8
void fn_2_71F60(void) {
    return;
}

// .text:0x00072038 size:0x1C
void fn_2_72038(s32 index, s16 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkB4 = value;
}

// .text:0x00072054 size:0x28
void fn_2_72054(s32 index, u8 variant) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->variant = variant;
    obj->state = 0;
}

// .text:0x0007207C size:0x518
void fn_2_7207C(void) {
    return;
}

// .text:0x00072594 size:0x9C
void fn_2_72594(void) {
    return;
}

// .text:0x00072630 size:0x2C
void fn_2_72630(void) {
    fn_800B0A5C_insertQueue(fn_2_72594, 0x3000);
}

// .text:0x0007265C size:0x1B8
void fn_2_7265C(void) {
    return;
}

// .text:0x00072814 size:0xAC
void fn_2_72814(void) {
    return;
}

// .text:0x000728C0 size:0x7C
void fn_2_728C0(void) {
    return;
}

// .text:0x0007293C size:0xA4
void fn_2_7293C(void) {
    return;
}

// .text:0x000729E0 size:0x78
void fn_2_729E0(void) {
    return;
}

// .text:0x00072A58 size:0x30
void fn_2_72A58(void) {
    return;
}

// .text:0x00072A88 size:0x22C
void fn_2_72A88(void) {
    return;
}

// .text:0x00072CB4 size:0xAC
void fn_2_72CB4(void) {
    return;
}

// .text:0x00072D60 size:0x7C
void fn_2_72D60(void) {
    return;
}

// .text:0x00072DDC size:0x78
void fn_2_72DDC(void) {
    return;
}

// .text:0x00072E54 size:0x1D4
void fn_2_72E54(void) {
    return;
}

// .text:0x00073028 size:0x4
void fn_2_73028(void) {
    return;
}

// .text:0x0007302C size:0x60
void fn_2_7302C(void) {
    return;
}

// .text:0x0007308C size:0x6CC
void fn_2_7308C(void) {
    return;
}

// .text:0x00073758 size:0x170
void fn_2_73758(void) {
    return;
}

// .text:0x000738C8 size:0xCC
void fn_2_738C8(void) {
    return;
}

// .text:0x00073994 size:0x1C0
void fn_2_73994(void) {
    return;
}

// .text:0x00073B54 size:0x40
s32 fn_2_73B54(s32 value) {
    extern s32 lbl_2_bss_A840;
    if (lbl_2_bss_A840 == 0 && value == 6) return 4;
    if (lbl_2_bss_A840 == 6 && value == 0) return 1;
    return 1;
}

// .text:0x00073B94 size:0x5C
s32 fn_2_73B94(s32 value) {
    extern s32 lbl_2_bss_A840;
    if (lbl_2_bss_A840 == 0 && value == 6) return 0x2D;
    if (lbl_2_bss_A840 == 6 && value == 0) return 0xE;
    if (lbl_2_bss_A840 <= value) return 0x1D;
    if (lbl_2_bss_A840 > value) return 0x2C;
}

// .text:0x00073BF0 size:0xCC
void fn_2_73BF0(void) {
    return;
}

// .text:0x00073CBC size:0x240
void fn_2_73CBC(void) {
    return;
}

// .text:0x00073EFC size:0x5CC
void fn_2_73EFC(void) {
    return;
}

// .text:0x000744C8 size:0x50
void fn_2_744C8(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(1 - input->state) >> 5) {
        fn_80062674(0);
        input->state = 2;
    }
}

// .text:0x00074518 size:0x4C
void fn_2_74518(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(input->state) >> 5) {
        fn_800626EC(0);
        input->state = 1;
    }
}

// .text:0x00074564 size:0xD8
void fn_2_74564(void) {
    return;
}

// .text:0x0007463C size:0x1C0
void fn_2_7463C(void) {
    return;
}

// .text:0x000747FC size:0x4DC
void fn_2_747FC(void) {
    return;
}

// .text:0x00074CD8 size:0xB4
void fn_2_74CD8(void) {
    return;
}

// .text:0x00074D8C size:0x2C
void fn_2_74D8C(void) {
    fn_800B0A5C_insertQueue(fn_2_74CD8, 0x1000);
}

// .text:0x00074DB8 size:0x5C
s32 fn_2_74DB8(s32 value) {
    switch (value) {
    case 13:
    case 16:
    case 20:
    case 22:
    case 25:
    case 34:
    case 42:
    case 50:
    case 52:
        return 1;
    case 21:
    case 24:
    case 29:
    case 33:
    case 44:
    case 51:
    case 53:
        return 2;
    case 23:
    case 30:
    case 36:
    case 45:
        return 3;
    case 12:
    case 26:
    case 27:
    case 31:
    case 35:
    case 43:
    case 46:
    case 49:
        return 4;
    case 32:
        return 5;
    case 47:
        return 6;
    default: return 0;
    }
}

// .text:0x00074E14 size:0x12C
void fn_2_74E14(void) {
    return;
}

// .text:0x00074F40 size:0xC18
void fn_2_74F40(void) {
    return;
}

// .text:0x00075B58 size:0x8C
void fn_2_75B58(void) {
    return;
}

// .text:0x00075BE4 size:0x4B4
void fn_2_75BE4(void) {
    return;
}

// .text:0x00076098 size:0x4
void fn_2_76098(void) {
    return;
}

// .text:0x0007609C size:0x30
void fn_2_7609C(s32 unused, u8 mode, u8 flag) {
    if (flag == 0) fn_2_8794(mode, 0);
}

// .text:0x000760CC size:0x240
void fn_2_760CC(void) {
    return;
}

// .text:0x0007630C size:0x340
void fn_2_7630C(void) {
    return;
}

// .text:0x0007664C size:0x4
void fn_2_7664C(void) {
    return;
}

// .text:0x00076650 size:0x224
void fn_2_76650(void) {
    return;
}

// .text:0x00076874 size:0x57C
void fn_2_76874(void) {
    return;
}

// .text:0x00076DF0 size:0x8B0
void fn_2_76DF0(void) {
    return;
}

// .text:0x000776A0 size:0x994
void fn_2_776A0(void) {
    return;
}

// .text:0x00078034 size:0x28
void fn_2_78034(s32 unused, s32 index) {
    u8* flag = &lbl_803C66B0.flags[index];
    if ((u32)__cntlzw(*flag) >> 5) {
        *flag = 1;
    }
}

// .text:0x0007805C size:0x310
void fn_2_7805C(void) {
    return;
}

// .text:0x0007836C size:0x754
void fn_2_7836C(void) {
    return;
}

// .text:0x00078AC0 size:0x4B8
void fn_2_78AC0(void) {
    return;
}

// .text:0x00078F78 size:0x1B4
void fn_2_78F78(void) {
    return;
}

// .text:0x0007912C size:0x268
void fn_2_7912C(void) {
    return;
}

// .text:0x00079394 size:0x2A0
void fn_2_79394(void) {
    return;
}

// .text:0x00079634 size:0x54
void fn_2_79634(void) {
    return;
}

// .text:0x00079688 size:0xDC
void fn_2_79688(void) {
    return;
}

// .text:0x00079764 size:0x1CC
void fn_2_79764(void) {
    return;
}

// .text:0x00079930 size:0x1F4
void fn_2_79930(void) {
    return;
}

// .text:0x00079B24 size:0x1D4
void fn_2_79B24(void) {
    return;
}

// .text:0x00079CF8 size:0x2B4
void fn_2_79CF8(void) {
    return;
}

// .text:0x00079FAC size:0x1E8
void fn_2_79FAC(void) {
    return;
}

// .text:0x0007A194 size:0x2CC
void fn_2_7A194(void) {
    return;
}

// .text:0x0007A460 size:0x158
void fn_2_7A460(void) {
    return;
}

// .text:0x0007A5B8 size:0x190
void fn_2_7A5B8(void) {
    return;
}

// .text:0x0007A748 size:0x290
void fn_2_7A748(void) {
    return;
}

// .text:0x0007A9D8 size:0x28C
void fn_2_7A9D8(void) {
    return;
}

// .text:0x0007AC64 size:0x1D8
void fn_2_7AC64(void) {
    return;
}

// .text:0x0007AE3C size:0x11BC
void fn_2_7AE3C(void) {
    return;
}

// .text:0x0007BFF8 size:0x1864
void fn_2_7BFF8(void) {
    return;
}

// .text:0x0007D85C size:0x25C
void fn_2_7D85C(void) {
    return;
}

// .text:0x0007DAB8 size:0x6DC
void fn_2_7DAB8(void) {
    return;
}

// .text:0x0007E194 size:0x1EC
void fn_2_7E194(void) {
    return;
}

// .text:0x0007E380 size:0x4E0
void fn_2_7E380(void) {
    return;
}

// .text:0x0007E860 size:0x114
void fn_2_7E860(void) {
    return;
}

// .text:0x0007E974 size:0x508
void fn_2_7E974(void) {
    return;
}

// .text:0x0007EE7C size:0xEC
void fn_2_7EE7C(void) {
    return;
}

// .text:0x0007EF68 size:0xC8
void fn_2_7EF68(void) {
    return;
}

// .text:0x0007F030 size:0x28C
void fn_2_7F030(void) {
    return;
}

// .text:0x0007F2BC size:0x458
void fn_2_7F2BC(void) {
    return;
}

// .text:0x0007F714 size:0x1A8
void fn_2_7F714(void) {
    return;
}

// .text:0x0007F8BC size:0x240
void fn_2_7F8BC(void) {
    return;
}

// .text:0x0007FAFC size:0x5B4
void fn_2_7FAFC(void) {
    return;
}

// .text:0x000800B0 size:0x23C
void fn_2_800B0(void) {
    return;
}

// .text:0x000802EC size:0x214
void fn_2_802EC(void) {
    return;
}

// .text:0x00080500 size:0xDC
void fn_2_80500(void) {
    return;
}

// .text:0x000805DC size:0x250
void fn_2_805DC(void) {
    return;
}

// .text:0x0008082C size:0xAC
void fn_2_8082C(void) {
    return;
}

// .text:0x000808D8 size:0x284
void fn_2_808D8(void) {
    return;
}

// .text:0x00080B5C size:0xD0
void fn_2_80B5C(void) {
    return;
}

// .text:0x00080C2C size:0x1E0
void fn_2_80C2C(void) {
    return;
}

// .text:0x00080E0C size:0x150
void fn_2_80E0C(void) {
    return;
}

// .text:0x00080F5C size:0x6CC
void fn_2_80F5C(void) {
    return;
}

// .text:0x00081628 size:0x1174
void fn_2_81628(void) {
    return;
}

// .text:0x0008279C size:0x554
void fn_2_8279C(void) {
    return;
}

// .text:0x00082CF0 size:0xF8
void fn_2_82CF0(void) {
    return;
}

// .text:0x00082DE8 size:0x70
void fn_2_82DE8(void) {
    return;
}

// .text:0x00082E58 size:0x68
void fn_2_82E58(void) {
    if (lbl_803CBBCC->previousSelection != 11 && g_d_GameSettings.GameModeSelected != 5) {
        fn_800B0A5C_insertQueue(fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue(fn_2_8279C, 0x3000);
}

// .text:0x00082EC0 size:0x630
void fn_2_82EC0(void) {
    return;
}

// .text:0x000834F0 size:0x1B4
void fn_2_834F0(void) {
    return;
}

// .text:0x000836A4 size:0xA0
void fn_2_836A4(void) {
    return;
}

// .text:0x00083744 size:0x94
void fn_2_83744(void) {
    return;
}

// .text:0x000837D8 size:0x19C
void fn_2_837D8(void) {
    return;
}

// .text:0x00083974 size:0x1C0
void fn_2_83974(void) {
    return;
}

// .text:0x00083B34 size:0x660
void fn_2_83B34(void) {
    return;
}

// .text:0x00084194 size:0x1F4
void fn_2_84194(void) {
    return;
}

// .text:0x00084388 size:0x220
void fn_2_84388(void) {
    return;
}

// .text:0x000845A8 size:0xA00
void fn_2_845A8(void) {
    return;
}

// .text:0x00084FA8 size:0x160
void fn_2_84FA8(void) {
    return;
}

// .text:0x00085108 size:0x54
void fn_2_85108(void) {
    lbl_8034E978.state = 5;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.next;
    fn_800B0A5C_insertQueue(fn_2_84FA8, 0x3000);
}

// .text:0x0008515C size:0x4
void fn_2_8515C(void) {
    return;
}

// .text:0x00085160 size:0x48
void fn_2_85160(void) {
    if (--lbl_803CC1B8->loadingState == 0) {
        fn_800625A4(0, 4);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000851A8 size:0x168
void fn_2_851A8(void) {
    return;
}

// .text:0x00085310 size:0x1A0
void fn_2_85310(void) {
    return;
}

// .text:0x000854B0 size:0x18C
void fn_2_854B0(void) {
    return;
}
