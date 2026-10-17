#include "menus/gap_94854.h"
#include "UnknownHeaders.h"
#include "menus/gap_71EC4.h"
#include "game/rep_3448.h"

extern MenusSceneScript lbl_2_data_311E4;

extern void fn_80062674(s32);
extern void fn_800626EC(s32);
extern void fn_80053FE8(void);

static inline BOOL menusCanStart(void) {
    return lbl_803C66B0.state4F == 0;
}

// .text:0x00094854 size:0x18
void fn_2_94854(u8 value) {
    lbl_2_bss_1A824C->unk197849 = value;
}

// .text:0x0009486C size:0x4C
void fn_2_9486C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_2_bss_1033C.pending != 0) {
        lbl_2_bss_1033C.pending = 0;
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000948B8 size:0x84
void fn_2_948B8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    lbl_2_bss_1033C.pending = 0;
    fn_80034E20(scene, &lbl_2_data_311E4);
    lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x280000;
    lbl_803CC1B8->unk_00 = fn_2_9486C;
}

// .text:0x0009493C size:0x150
void fn_2_9493C(void) {
    return;
}

// .text:0x00094A8C size:0xB78
void fn_2_94A8C(void) {
    return;
}

// .text:0x00095604 size:0x50
void fn_2_95604(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(1 - input->state4F) >> 5) {
        fn_80062674(0);
        input->state4F = 2;
    }
}

// .text:0x00095654 size:0x4D4
void fn_2_95654(void) {
    return;
}

// .text:0x00095B28 size:0x50
void fn_2_95B28(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(1 - input->state4F) >> 5) {
        fn_80062674(0);
        input->state4F = 2;
    }
}

// .text:0x00095B78 size:0x308
void fn_2_95B78(void) {
    return;
}

// .text:0x00095E80 size:0xBC
void fn_2_95E80(void) {
    return;
}

// .text:0x00095F3C size:0xA4
void fn_2_95F3C(DrawingSceneStruct* scene) {
    BOOL ready = menusCanStart();
    if (ready) {
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
        (&lbl_80371C30[scene->unkIndex])[1].obj->field_0x68 = 4;
        (&lbl_80371C30[scene->unkIndex])[3].obj->field_0x68 = 4;
        (&lbl_80371C30[scene->unkIndex])[4].obj->field_0x68 = 4;
        fn_800626EC(0);
        lbl_803C66B0.state4F = 1;
    }
}

// .text:0x00095FE0 size:0x138
void fn_2_95FE0(void) {
    return;
}

// .text:0x00096118 size:0x580
void fn_2_96118(void) {
    return;
}

// .text:0x00096698 size:0x43C
void fn_2_96698(void) {
    return;
}

// .text:0x00096AD4 size:0x24C
void fn_2_96AD4(void) {
    return;
}

// .text:0x00096D20 size:0x74
void fn_2_96D20(void) {
    fn_800B0A5C_insertQueue(fn_80053FE8, 0x3000);
    lbl_8034E978.state = 0x5B;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.next5B8;
    fn_800B0A5C_insertQueue(fn_2_948B8, 0x3000);
    fn_800B0A5C_insertQueue(fn_2_96AD4, 0x3000);
}
