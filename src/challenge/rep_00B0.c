#include "challenge/rep_00B0.h"
/* Bind the SDK display-list helpers to this game's unresolved symbol names. */
#define __GDCurrentDL lbl_803CC0F0
#define GDOverflowed fn_800A1B80
#include "Dolphin/gd.h"
#include "Dolphin/mtx.h"
extern Vec lbl_1_bss_60[8];

// .text:0x000019AC size:0x24C
void fn_1_19AC(void) {
    return;
}

// .text:0x00001BF8 size:0x1C4
/* Expand a bounding box into eight vertices and emit its six quad faces. */
void fn_1_1BF8(ChallengeBounds* bounds, s32 index) {
    ChallengeBounds* box = &bounds[index];
    lbl_1_bss_60[0].x = box->minX;
    lbl_1_bss_60[0].y = box->minY;
    lbl_1_bss_60[0].z = box->maxZ;
    lbl_1_bss_60[1].x = box->maxX;
    lbl_1_bss_60[1].y = box->minY;
    lbl_1_bss_60[1].z = box->maxZ;
    lbl_1_bss_60[2].x = box->maxX;
    lbl_1_bss_60[2].y = box->minY;
    lbl_1_bss_60[2].z = box->minZ;
    lbl_1_bss_60[3].x = box->minX;
    lbl_1_bss_60[3].y = box->minY;
    lbl_1_bss_60[3].z = box->minZ;
    lbl_1_bss_60[4].x = box->minX;
    lbl_1_bss_60[4].y = box->maxY;
    lbl_1_bss_60[4].z = box->maxZ;
    lbl_1_bss_60[5].x = box->maxX;
    lbl_1_bss_60[5].y = box->maxY;
    lbl_1_bss_60[5].z = box->maxZ;
    lbl_1_bss_60[6].x = box->maxX;
    lbl_1_bss_60[6].y = box->maxY;
    lbl_1_bss_60[6].z = box->minZ;
    lbl_1_bss_60[7].x = box->minX;
    lbl_1_bss_60[7].y = box->maxY;
    lbl_1_bss_60[7].z = box->minZ;
    __GDCheckOverflowed(1);
    __GDWriteU8(0x80);
    __GDCheckOverflowed(2);
    __GDWriteU16(24);
    fn_1_1DBC(7, 6, 2, 3, 12);
    fn_1_1DBC(5, 4, 0, 1, 13);
    fn_1_1DBC(3, 2, 1, 0, 14);
    fn_1_1DBC(4, 5, 6, 7, 15);
    fn_1_1DBC(4, 7, 3, 0, 16);
    fn_1_1DBC(6, 5, 1, 2, 17);
}

// .text:0x00001DBC size:0x800
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s32 face) {
    return;
}

// .text:0x000025BC size:0x187C
void fn_1_25BC(void) {
    return;
}

// .text:0x00003E38 size:0x23C
void fn_1_3E38(void) {
    return;
}

// .text:0x00004074 size:0x21C
void fn_1_4074(void) {
    return;
}

// .text:0x00004290 size:0x498
void fn_1_4290(void) {
    return;
}

// .text:0x00004728 size:0x2FC
void fn_1_4728(void) {
    return;
}

// .text:0x00004A24 size:0x3B4
void fn_1_4A24(void) {
    return;
}
