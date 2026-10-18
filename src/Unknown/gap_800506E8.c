#include "Unknown/gap_800506E8.h"

// .text:0x800506E8 size:0x78
void fn_800506E8(void) {
    return;
}

// .text:0x80050760 size:0x818
void fn_80050760(void) {
    return;
}

// .text:0x80050F78 size:0x70
void fn_80050F78(void) {
    return;
}

// .text:0x80050FE8 size:0x3A4
void fn_80050FE8(void) {
    return;
}

// .text:0x8005138C size:0x974
void fn_8005138C(void) {
    return;
}

// .text:0x80051D00 size:0x488
void fn_80051D00(void) {
    return;
}

// .text:0x80052188 size:0x28
void fn_80052188(void) {
    lbl_803C6028.unk8E = 0;
    lbl_803C6028.unk8F = 0;
    lbl_803C6028.unk90 = 0;
    lbl_803C6028.unk7C = 0;
    lbl_803C6028.unk7D = 0;
    lbl_803C6028.unk7E = 0;
}

// .text:0x800521B0 size:0x25C
void fn_800521B0(void) {
    return;
}

// .text:0x8005240C size:0x228
void fn_8005240C(void) {
    return;
}

// .text:0x80052634 size:0x58
void fn_80052634(void) {
    return;
}

// .text:0x8005268C size:0x8
s32 fn_8005268C(void) {
    return lbl_803CBD14;
}

// .text:0x80052694 size:0xA0
void fn_80052694(void) {
    return;
}

// .text:0x80052734 size:0x34
Gap800506E8Camera* fn_80052734(s32 index) {
    if (index < 0) index = 0;
    else if (index >= 2) index = 1;
    return &lbl_803C639C.alternate[index];
}

// .text:0x80052768 size:0x30
Gap800506E8Camera* fn_80052768(s32 index) {
    if (index < 0) index = 0;
    else if (index >= 2) index = 1;
    return &lbl_803C639C.slots[index];
}

// .text:0x80052798 size:0x24
void fn_80052798(s32 value) {
    if (value < 1) {
        value = 1;
    } else if (value > 2) {
        value = 2;
    }
    lbl_803CB880 = value;
}

// .text:0x800527BC size:0x8
s32 fn_800527BC(void) {
    return lbl_803CB880;
}

// .text:0x800527C4 size:0xE8
void fn_800527C4(void) {
    return;
}
