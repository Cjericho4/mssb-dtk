#include "menus/rep_0568.h"
#include "UnknownHeaders.h"
#include "string.h"

// .text:0x00016A98 size:0x248
void fn_2_16A98(void) {
    return;
}

// .text:0x00016CE0 size:0x58
void fn_2_16CE0(void) {
    AnimationStruct* anim;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (anim != 0 && anim->animID == 0x6B) lbl_2_bss_100B8.flags[i] = 1;
    }
}

// .text:0x00016D38 size:0x70
void fn_2_16D38(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        memset(g_hugeAnimStruct.fielderStructs[i].aux, 0, 0x5C);
    }
}

// .text:0x00016DA8 size:0x164
void fn_2_16DA8(void) {
    return;
}

// .text:0x00016F0C size:0x6C
void fn_2_16F0C(void) {
    return;
}

// .text:0x00016F78 size:0x6D0
void fn_2_16F78(void) {
    return;
}

// .text:0x00017648 size:0x470
void fn_2_17648(void) {
    return;
}

// .text:0x00017AB8 size:0x1D0
void fn_2_17AB8(void) {
    return;
}

// .text:0x00017C88 size:0x250
void fn_2_17C88(void) {
    return;
}

// .text:0x00017ED8 size:0x270
void fn_2_17ED8(void) {
    return;
}

// .text:0x00018148 size:0x250
void fn_2_18148(void) {
    return;
}

// .text:0x00018398 size:0x2B8
void fn_2_18398(void) {
    return;
}

// .text:0x00018650 size:0xF8
s32 fn_2_18650(s32 index) {
    s32 next = (lbl_2_bss_100B8.writeIndex + 1) % 10;
    if (next != lbl_2_bss_100B8.readIndex) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = (MenusAnimationTask*)fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224->current = 0;
                lbl_2_bss_1224->state = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8.commands[lbl_2_bss_100B8.writeIndex] = index;
        lbl_2_bss_100B8.writeIndex = next;
        lbl_2_bss_100B8.flags[index + 2] = 1;
        return 1;
    }
    return 0;
}

// .text:0x00018748 size:0x1A4
void fn_2_18748(void) {
    return;
}

// .text:0x000188EC size:0x6D0
void fn_2_188EC(void) {
    return;
}

// .text:0x00018FBC size:0xFC
void fn_2_18FBC(void) {
    return;
}

// .text:0x000190B8 size:0x24
void fn_2_190B8(Rep0568Obj* obj) {
    fn_800B9AA8(obj->context);
}

// .text:0x000190DC size:0x148
void fn_2_190DC(HugeAnimEntry68* entries, Mtx matrix) {
    return;
}

// .text:0x00019224 size:0x158
void fn_2_19224(void) {
    return;
}

// .text:0x0001937C size:0x140
void fn_2_1937C(void) {
    return;
}
