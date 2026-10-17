#include "menus/rep_0AB0.h"
#include "menus/gap_1B1BC.h"
#include "menus/gap_71EC4.h"
#include "UnknownHeaders.h"

extern void fn_80053FE8(void);
extern MenusResourceEntry lbl_2_data_268A8[];

#include "menus/gap_4B1AC.h"
extern MenusSceneScript lbl_2_data_20C68;
extern void fn_8000F8F4(DrawingSceneStruct* scene);
extern void fn_8000FE54(void);

// .text:0x0005979C size:0x55C
void fn_2_5979C(void) {
    return;
}

// .text:0x00059CF8 size:0x52C
void fn_2_59CF8(void) {
    return;
}

// .text:0x0005A224 size:0xC30
void fn_2_5A224(void) {
    return;
}

// .text:0x0005AE54 size:0xD0
void fn_2_5AE54(void) {
    DrawingSceneStruct* scene;
    switch ((s32)(scene = lbl_803CC1B8)->eventID) {
    case 0:
        fn_2_4E878(scene, &lbl_2_data_20C68);
        scene->eventID = 1;
        scene->unk18 = 0;
        break;
    case 1: break;
    }
    fn_2_53F88((s32)scene);
    fn_2_54120();
    if (lbl_2_bss_1A8234->panels[1].pending) {
        fn_2_53DF8(scene);
        fn_8000F8F4(scene);
        fn_8000FE54();
        fn_2_4E858(scene);
        fn_800B0A14_removeQueue();
        scene->eventID = 0;
        scene->fielderIndex = 0;
        lbl_2_bss_1A8234->panels[1].pending = 0;
    }
}

// .text:0x0005AF24 size:0x8C
void fn_2_5AF24(void) {
    QueueEntry* task;
    lbl_8034E978.state = 0x53;
    fn_800B0A5C_insertQueue(fn_80053FE8, 0);
    task = fn_800B0A5C_insertQueue(fn_2_5AE54, 0);
    task->unk1C = 0;
    task->unk1E = 0;
    fn_2_54354(lbl_2_data_268A8, 0x2E0);
    lbl_2_bss_1A8234->flag162604 = 1;
    lbl_2_bss_1A8234->flag162605 = 1;
}

// .text:0x0005AFB0 size:0x82C
void fn_2_5AFB0(void) {
    return;
}

// .text:0x0005B7DC size:0xDDC
void fn_2_5B7DC(void) {
    return;
}

// .text:0x0005C5B8 size:0x5A4
void fn_2_5C5B8(void) {
    return;
}

// .text:0x0005CB5C size:0x710
void fn_2_5CB5C(void) {
    return;
}

// .text:0x0005D26C size:0x9F0
void fn_2_5D26C(void) {
    return;
}

// .text:0x0005DC5C size:0x4A8
void fn_2_5DC5C(void) {
    return;
}

// .text:0x0005E104 size:0x748
void fn_2_5E104(void) {
    return;
}
