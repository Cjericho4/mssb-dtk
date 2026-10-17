#include "menus/gap_8782C.h"
#include "menus/gap_71EC4.h"
#include "menus/rep_0438.h"

extern MenusSceneScript lbl_2_data_2ECE4;

// .text:0x0008782C size:0x16C
void fn_2_8782C(void) {
    return;
}

// .text:0x00087998 size:0x618
void fn_2_87998(void) {
    return;
}

// .text:0x00087FB0 size:0x2A0
void fn_2_87FB0(void) {
    return;
}

// .text:0x00088250 size:0x178
void fn_2_88250(void) {
    return;
}

// .text:0x000883C8 size:0x430
void fn_2_883C8(void) {
    return;
}

// .text:0x000887F8 size:0x598
void fn_2_887F8(void) {
    return;
}

// .text:0x00088D90 size:0x2A8
void fn_2_88D90(void) {
    return;
}

// .text:0x00089038 size:0x5C0
void fn_2_89038(void) {
    return;
}

// .text:0x000895F8 size:0x164
void fn_2_895F8(void) {
    return;
}

// .text:0x0008975C size:0x814
void fn_2_8975C(void) {
    return;
}

// .text:0x00089F70 size:0x98
void fn_2_89F70(void) {
    u8* script;
    s32 mode = lbl_2_bss_33FBCC.mode;
    DrawingSceneStruct* scene;
    MenusRosterScripts* scripts = &lbl_2_data_2E9F8;
    scene = lbl_803CC1B8;
    switch (mode) {
    case 0: script = scripts->mode0; break;
    case 1:
    case 2: script = scripts->mode12; break;
    case 3: script = scripts->mode3; break;
    }
    fn_80034E20(scene, (MenusSceneScript*)script);
    lbl_2_bss_33FBCC.pending = 0;
    lbl_803CC1B8->unk_00 = fn_2_8975C;
}

// .text:0x0008A008 size:0x81C
void fn_2_8A008(DrawingSceneStruct* scene) {
    return;
}

// .text:0x0008A824 size:0x3D8
void fn_2_8A824(void) {
    return;
}

// .text:0x0008ABFC size:0x88
void fn_2_8ABFC(void) {
    DrawingSceneStruct* scene;
    fn_80034E20(scene = lbl_803CC1B8, &lbl_2_data_2ECE4);
    fn_2_8A008(scene);
    if (lbl_8034E9A0.unk4756 == 1) lbl_2_bss_F410.selection = lbl_80361B20.mode;
    lbl_803CC1B8->unk_00 = fn_2_8A824;
}

// .text:0x0008AC84 size:0x2C
void fn_2_8AC84(s32 index, u8 visible) {
    if (lbl_2_bss_340140->entries_2D94 != 0) {
        lbl_2_bss_3401BC->visible[index] = visible;
    }
}

// .text:0x0008ACB0 size:0x2C
void fn_2_8ACB0(s32 index, u8 visible) {
    HugeAnimEntry2D94* entries = lbl_2_bss_340140->entries_2D94;
    HugeAnimEntry2D94* entry;
    if (entries != 0) return;
    entry = &entries[index];
    if (entry != 0) entry->unk_26 = visible;
}

// .text:0x0008ACDC size:0x4
void fn_2_8ACDC(void) {
    return;
}
