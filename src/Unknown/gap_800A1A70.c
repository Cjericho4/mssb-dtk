#include "Unknown/gap_800A1A70.h"

/* GD display-list writers (the SDK's GDWrite_u8 / GDWrite_u32 with their overflow checks). */
static inline void gdPutU8(u8 value) {
    *lbl_803CC0F0->cur++ = value;
}

static inline void gdWriteU8(u8 value) {
    if (lbl_803CC0F0->cur + 1 > lbl_803CC0F0->end) {
        fn_800A1B80();
    }
    gdPutU8(value);
}

static inline void gdWriteU32(u32 value) {
    if (lbl_803CC0F0->cur + 4 > lbl_803CC0F0->end) {
        fn_800A1B80();
    }
    gdPutU8(value >> 24);
    gdPutU8(value >> 16);
    gdPutU8(value >> 8);
    gdPutU8(value);
}

// .text:0x800A1A70 size:0x18
void fn_800A1A70(Gap800A1A70Range* range, u8* start, u32 length) {
    range->start = start;
    range->cur = start;
    range->end = start + length;
    range->length = length;
}

// .text:0x800A1A88 size:0xF8
// GDPadCurr32: pads the current display list with zero bytes up to a 32-byte boundary.
void fn_800A1A88(void) {
    u32 offset = (u32)lbl_803CC0F0->cur & 31;

    if (offset != 0) {
        for (; offset < 32; offset++) {
            gdPutU8(0);
        }
    }
}

// .text:0x800A1B80 size:0x30
extern void (*lbl_803CC0F4)(void);
/* FAKEMATCH: the writers below call this out of line (it is a separate SDK file, GDBase.c). */
#pragma dont_inline on
void fn_800A1B80(void) {
    if (lbl_803CC0F4) lbl_803CC0F4();
}
#pragma dont_inline reset

// .text:0x800A1BB0 size:0x28C
void fn_800A1BB0(void) {
    return;
}

// .text:0x800A1E3C size:0x104
// GDSetAlphaCompare: writes the BP alpha-test command (two compares with their reference
// values, combined by `op`).
void fn_800A1E3C(u32 comp0, u8 ref0, u32 op, u32 comp1, u8 ref1) {
    gdWriteU8(0x61);
    gdWriteU32(ref0 | (ref1 << 8) | (comp0 << 16) | (comp1 << 19) | (op << 22) | 0xF3000000);
}

// .text:0x800A1F40 size:0x254
void fn_800A1F40(void) {
    return;
}

// .text:0x800A2194 size:0x100
// GDSetTexImgAttr: writes the BP command with a texture map's width, height and format.
void fn_800A2194(u32 texMap, u16 width, u16 height, u32 format) {
    u32 command = (width - 1) | ((height - 1) << 10) | (format << 20) | (lbl_803CBAA8[texMap] << 24);

    gdWriteU8(0x61);
    gdWriteU32(command);
}

// .text:0x800A2294 size:0xE8
// GDSetTexImgPtr: writes the BP command that points texture map `texMap` at an image (its
// physical address in 32-byte units).
void fn_800A2294(u32 texMap, u32 imageAddress) {
    u32 command = ((imageAddress + 0x80000000) >> 5) | (lbl_803CBAB0[texMap] << 24);

    gdWriteU8(0x61);
    gdWriteU32(command);
}

// .text:0x800A237C size:0xF0
// GDSetTexTlut: writes the BP command that selects a texture map's TLUT (its TMEM address
// above 0x80000, in 512-byte units) and format.
void fn_800A237C(u32 texMap, u32 tlutAddress, u32 format) {
    u32 command = ((tlutAddress - 0x80000) >> 9) | (format << 10) | (lbl_803CBAB8[texMap] << 24);

    gdWriteU8(0x61);
    gdWriteU32(command);
}

// .text:0x800A246C size:0x290
void fn_800A246C(void) {
    return;
}

// .text:0x800A26FC size:0x460
void fn_800A26FC(void) {
    return;
}
