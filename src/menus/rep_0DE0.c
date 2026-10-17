#include "menus/rep_0DE0.h"
#include "UnknownHeaders.h"

extern hugeAnimStruct* lbl_2_bss_340140;
extern f32 lbl_2_rodata_E88;

// .text:0x0008563C size:0x268
void fn_2_8563C(void) {
    return;
}

// .text:0x000858A4 size:0x21C
void fn_2_858A4(void) {
    return;
}

// .text:0x00085AC0 size:0x2AC
void fn_2_85AC0(void) {
    return;
}

// .text:0x00085D6C size:0x704
void fn_2_85D6C(void) {
    return;
}

// .text:0x00086470 size:0x458
void fn_2_86470(void) {
    return;
}

// .text:0x000868C8 size:0xEC
void fn_2_868C8(void) {
    return;
}

// .text:0x000869B4 size:0x58
void fn_2_869B4(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_340140->field268_0x3078; i++) {
        HugeAnimEntry2D94* entry = &lbl_2_bss_340140->entries_2D94[i];
        entry->pos.x = 0.0f;
        entry->pos.y = 0.0f;
        entry->pos.z = 0.0f;
        entry->vel.x = 0.0f;
        entry->vel.y = 0.0f;
        entry->vel.z = 0.0f;
    }
}

// .text:0x00086A0C size:0x74
void fn_2_86A0C(void) {
    return;
}

// .text:0x00086A80 size:0x34C
void fn_2_86A80(void) {
    return;
}

// .text:0x00086DCC size:0x174
void fn_2_86DCC(void) {
    return;
}

// .text:0x00086F40 size:0xAC
void fn_2_86F40(void) {
    return;
}

// .text:0x00086FEC size:0xE8
void fn_2_86FEC(void) {
    return;
}

// .text:0x000870D4 size:0x40
void fn_2_870D4(f32 value) {
    if (value != lbl_2_rodata_E88) lbl_2_bss_340140->field269_0x307a = 3;
    else lbl_2_bss_340140->field269_0x307a = 0;
}

// .text:0x00087114 size:0x4
void fn_2_87114(void) {
    return;
}

// .text:0x00087118 size:0x238
void fn_2_87118(void) {
    return;
}

// .text:0x00087350 size:0x304
void fn_2_87350(void) {
    return;
}

// .text:0x00087654 size:0x1D8
void fn_2_87654(void) {
    return;
}
