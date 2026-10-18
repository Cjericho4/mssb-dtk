#include "Unknown/gap_800A97D0.h"

// .text:0x800A97D0 size:0x1C
void fn_800A97D0(u8 a, s8 b) {
    lbl_80110080.unk7 = a;
    lbl_80110080.unk8 = -b;
    lbl_80110080.unk9 = b;
}

// .text:0x800A97EC size:0x50
void fn_800A97EC(s32 index, u32 command, u8 value) {
    Gap800A97D0Pad* pad = &lbl_803C77B8[index];
    if (lbl_80110080.disabledPads & (1 << index)) return;
    pad->command = command;
    pad->value = 0;
    if (command != 0) pad->value = value;
    pad->pending = 1;
}

// .text:0x800A983C size:0x28
void fn_800A983C(void) {
    PADInit();
    SISetSamplingRate(0);
}

// .text:0x800A9864 size:0x98
void fn_800A9864(void) {
    return;
}

// .text:0x800A98FC size:0x3FC
void fn_800A98FC(void) {
    return;
}

// .text:0x800A9CF8 size:0x13C
void fn_800A9CF8(void) {
    return;
}

// .text:0x800A9E34 size:0x98
void fn_800A9E34(void) {
    return;
}

// .text:0x800A9ECC size:0x480
void fn_800A9ECC(void) {
    return;
}

// .text:0x800AA34C size:0x100
void fn_800AA34C(void) {
    return;
}

// .text:0x800AA44C size:0x4E4
void fn_800AA44C(void) {
    return;
}

// .text:0x800AA930 size:0x140
void fn_800AA930(void) {
    return;
}

// .text:0x800AAA70 size:0x474
void fn_800AAA70(void) {
    return;
}

// .text:0x800AAEE4 size:0x108
void fn_800AAEE4(void) {
    return;
}

// .text:0x800AAFEC size:0x488
void fn_800AAFEC(void) {
    return;
}

// .text:0x800AB474 size:0xC0
void fn_800AB474(void) {
    return;
}

// .text:0x800AB534 size:0x5E0
void fn_800AB534(void) {
    return;
}

// .text:0x800ABB14 size:0x4C
u16 fn_800ABB14(u8* data, s32 count) {
    u16 crc = 0xFFFF;
    while (--count >= 0) {
        crc = (crc << 8) ^ lbl_800E7800[(crc >> 8) ^ *data++];
    }
    return ~crc;
}

// .text:0x800ABB60 size:0x70
void fn_800ABB60(void) {
    return;
}

// .text:0x800ABBD0 size:0x374
void fn_800ABBD0(void) {
    return;
}

// .text:0x800ABF44 size:0x5C4
void fn_800ABF44(void) {
    return;
}

// .text:0x800AC508 size:0x764
void fn_800AC508(void) {
    return;
}

// .text:0x800ACC6C size:0x68
void fn_800ACC6C(void) {
    return;
}

// .text:0x800ACCD4 size:0x14
void fn_800ACCD4(void) {
    lbl_803C7838.unk55 = 7;
}

// .text:0x800ACCE8 size:0x5C
void fn_800ACCE8(void) {
    return;
}

// .text:0x800ACD44 size:0x20
void fn_800ACD44(void) {
    CARDInit();
}

// .text:0x800ACD64 size:0x1B0
void fn_800ACD64(void) {
    return;
}

// .text:0x800ACF14 size:0x20
void fn_800ACF14(void) {
    return;
}

// .text:0x800ACF34 size:0x44
void fn_800ACF34(void) {
    return;
}

// .text:0x800ACF78 size:0x38
void fn_800ACF78(void) {
    return;
}

// .text:0x800ACFB0 size:0x20
void fn_800ACFB0(void) {
    return;
}

// .text:0x800ACFD0 size:0x4C
void _OSAllocFromHeap(void) {
    return;
}

// .text:0x800AD01C size:0x1C
void fn_800AD01C(s32 end) {
    lbl_803C7898.end = end;
    lbl_803C7898.size = end - lbl_803C7898.start;
}

// .text:0x800AD038 size:0x1C
void fn_800AD038(s32 start) {
    lbl_803C7898.start = start;
    lbl_803C7898.size = lbl_803C7898.end - start;
}

// .text:0x800AD054 size:0x1C
void fn_800AD054(s32 start, s32 end) {
    lbl_803C7898.start = start;
    lbl_803C7898.end = end;
    lbl_803C7898.size = end - start;
}

// .text:0x800AD070 size:0x420
void fn_800AD070(void) {
    return;
}

// .text:0x800AD490 size:0x70
void fn_800AD490(void) {
    return;
}

// .text:0x800AD500 size:0x1BC
void fn_800AD500(void) {
    return;
}

// .text:0x800AD6BC size:0xC4
void fn_800AD6BC(void) {
    return;
}
