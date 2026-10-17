#include "challenge/rep_7920.h"

// .text:0x00026B7C size:0x80
void fn_1_26B7C(void) {
    return;
}

// .text:0x00026BFC size:0x30
Rep7920Entry* fn_1_26BFC(Rep7920Source* src, s32 index) {
    Rep7920Entry* entry = &lbl_1_common_bss_4C6F8[index];
    entry->unk0 = src->unk0;
    entry->unk2 = src->unk2;
    entry->data = src->data;
    return entry;
}

// .text:0x00026C2C size:0xFC
void fn_1_26C2C(void) {
    return;
}
