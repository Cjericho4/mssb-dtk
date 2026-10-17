#include "menus/gap_194BC.h"
#include "menus/gap_1B1BC.h"
#include "menus/rep_10C0.h"
#include "menus/rep_0B08.h"
#include "menus/rep_08E8.h"

extern void fn_80021204(void);
extern s32 fn_8003AE70(s32 index);

// .text:0x000194BC size:0x2C
void fn_2_194BC(Rep0568Obj* obj) {
    if (obj->context != 0) fn_800B9AA8(obj->context);
}

// .text:0x000194E8 size:0x38
void fn_2_194E8(void) {
    fn_80021204();
    lbl_800E8754.unk25 = lbl_80366158.unk1F;
}

// .text:0x00019520 size:0x34
void fn_2_19520(void) {
    return;
}

// .text:0x00019554 size:0x84
s32 fn_2_19554(void) {
    s8 changed = 0;
    if (lbl_800EF808.unk398 != fn_8003AE70(0) || lbl_800EF808.unk397 != fn_8003AE70(1) || lbl_80366158.unk1F != fn_8003AE70(2)) {
        changed = 1;
    }
    return changed;
}

// .text:0x000195D8 size:0x4
void fn_2_195D8(void) {
    return;
}

// .text:0x000195DC size:0x19C
void fn_2_195DC(void) {
    return;
}

// .text:0x00019778 size:0x34
void fn_2_19778(void) {
    return;
}

// .text:0x000197AC size:0x558
void fn_2_197AC(void) {
    return;
}

// .text:0x00019D04 size:0x228
void fn_2_19D04(void) {
    return;
}

// .text:0x00019F2C size:0x288
void fn_2_19F2C(void) {
    return;
}

// .text:0x0001A1B4 size:0xF8
void fn_2_1A1B4(void) {
    return;
}

// .text:0x0001A2AC size:0x174
void fn_2_1A2AC(void) {
    return;
}

// .text:0x0001A420 size:0xA8
BOOL fn_2_1A420(void) {
    s32 ready = 0;
    if (lbl_2_bss_1A823C->state == 3) {
        fn_2_4AB1C();
        if (lbl_2_bss_1A824C->unk197843 == 0) {
            if (lbl_2_bss_1A8248->unk441C == 5) {
                if (fn_2_46D00()) ready = 1;
            } else {
                if (lbl_2_bss_1A8248->unk4426 & 0x20) ready = 1;
            }
        }
    }
    return (u8)(ready != 0);
}
