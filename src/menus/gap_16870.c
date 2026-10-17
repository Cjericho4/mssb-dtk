#include "menus/gap_16870.h"
#include "UnknownHeaders.h"

// .text:0x00016870 size:0x1C4
void fn_2_16870(void) {
    return;
}

// .text:0x00016A34 size:0x14
u8 fn_2_16A34(s32 index) {
    return lbl_2_bss_100B8.values[index];
}

// .text:0x00016A48 size:0x14
void fn_2_16A48(s32 index, u8 value) {
    lbl_2_bss_100B8.values[index] = value;
}

// .text:0x00016A5C size:0x18
u8 fn_2_16A5C(s32 index) {
    return g_hugeAnimStruct.fielderStructs[index].unk_25D;
}

// .text:0x00016A74 size:0x24
void fn_2_16A74(s32 index, s32 value) {
    g_hugeAnimStruct.fielderStructs[index].unk_25D = value != 0;
}
