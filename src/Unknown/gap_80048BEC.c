#include "Unknown/gap_80048BEC.h"

// .text:0x80048BEC size:0x28
void fn_80048BEC(Gap80048BECTiming* timing) {
    s32 count = timing->limit;
    if (timing->requested < count) count = timing->requested;
    while (count > 0) count--;
}

// .text:0x80048C14 size:0x8
void fn_80048C14(s32 value) {
    lbl_803CBCE8 = value;
}

// .text:0x80048C1C size:0xC
void fn_80048C1C(void) {
    return;
}

// .text:0x80048C28 size:0x124
void fn_80048C28(void) {
    return;
}

// .text:0x80048D4C size:0xB4
void fn_80048D4C(void) {
    return;
}

// .text:0x80048E00 size:0xA8
void fn_80048E00(void) {
    return;
}

// .text:0x80048EA8 size:0x10
s32 fn_80048EA8(s32 index) {
    return lbl_803CB83C[index];
}

// .text:0x80048EB8 size:0x368
void startGameRelated(void) {
    return;
}

// .text:0x80049220 size:0x2AC
void fn_80049220(void) {
    return;
}

// .text:0x800494CC size:0x3AC
void fn_800494CC(void) {
    return;
}

// .text:0x80049878 size:0x408
void possiblyTransferDataBetweenDifferentRels(void) {
    return;
}

// .text:0x80049C80 size:0xBC
void fn_80049C80(void) {
    return;
}

// .text:0x80049D3C size:0x50
void fn_80049D3C(void) {
    return;
}

// .text:0x80049D8C size:0x370
void fn_80049D8C(void) {
    return;
}

// .text:0x8004A0FC size:0xC0
void fn_8004A0FC(void) {
    return;
}

// .text:0x8004A1BC size:0x100
void fn_8004A1BC(void) {
    return;
}

// .text:0x8004A2BC size:0x6C
void fn_8004A2BC(void) {
    return;
}

// .text:0x8004A328 size:0x24
BOOL fn_8004A328(Gap80048BECObj* obj) {
    if (obj->state != 0) {
        return FALSE;
    }
    obj->state = 2;
    return TRUE;
}

// .text:0x8004A34C size:0x26C
void fn_8004A34C(void) {
    return;
}

// .text:0x8004A5B8 size:0x218
void fn_8004A5B8(void) {
    return;
}

// .text:0x8004A7D0 size:0x210
void fn_8004A7D0(void) {
    return;
}

// .text:0x8004A9E0 size:0x1F8
void fn_8004A9E0(void) {
    return;
}

// .text:0x8004ABD8 size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// .text:0x8004ABE0 size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// .text:0x8004ABE8 size:0x18
s32 fn_8004ABE8(BOOL clear) {
    s32 value = lbl_803CBD00;
    if (clear) {
        lbl_803CBD00 = 0;
    }
    return value;
}

// .text:0x8004AC00 size:0xC4
void fn_8004AC00(void) {
    return;
}

// .text:0x8004ACC4 size:0x18
s32 fn_8004ACC4(BOOL clear) {
    s32 value = lbl_803CBD04;
    if (clear) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// .text:0x8004ACDC size:0x18
s32 fn_8004ACDC(BOOL clear) {
    s32 value = lbl_803CBD08;
    if (clear) {
        lbl_803CBD08 = 0;
    }
    return value;
}

// .text:0x8004ACF4 size:0x60
void fn_8004ACF4(void) {
    return;
}

// .text:0x8004AD54 size:0xC4
void fn_8004AD54(void) {
    return;
}

// .text:0x8004AE18 size:0x190
void fn_8004AE18(void) {
    return;
}

// .text:0x8004AFA8 size:0x210
void fn_8004AFA8(void) {
    return;
}

// .text:0x8004B1B8 size:0x8
void fn_8004B1B8(s32 value) {
    lbl_803CBD0C = value;
}

// .text:0x8004B1C0 size:0x48
void fn_8004B1C0(void) {
    return;
}

// .text:0x8004B208 size:0x68
void fn_8004B208(void) {
    return;
}

// .text:0x8004B270 size:0x14
void fn_8004B270(void) {
    lbl_803CBD0C = 0;
    lbl_803CBD08 = 0;
    lbl_803CBD04 = 0;
}

// .text:0x8004B284 size:0x468
void fn_8004B284(void) {
    return;
}

// .text:0x8004B6EC size:0xC8
void fn_8004B6EC(void) {
    return;
}

// .text:0x8004B7B4 size:0x40
s32 fn_8004B7B4(Gap80048BECObj* obj, Gap80048BECActor** actor) {
    if (obj->actorIndex != 0xFFFF) fn_800B2BA8(*actor, obj->actorIndex, NULL, 0);
    return 0;
}

// .text:0x8004B7F4 size:0x2F8
void fn_8004B7F4(void) {
    return;
}

// .text:0x8004BAEC size:0x280
void fn_8004BAEC(void) {
    return;
}

// .text:0x8004BD6C size:0x144
void fn_8004BD6C(void) {
    return;
}

// .text:0x8004BEB0 size:0x1E4
void fn_8004BEB0(void) {
    return;
}

// .text:0x8004C094 size:0x74
void fn_8004C094(void) {
    return;
}

// .text:0x8004C108 size:0x94
void fn_8004C108(void) {
    return;
}

// .text:0x8004C19C size:0x374
void fn_8004C19C(void) {
    return;
}

// .text:0x8004C510 size:0xE8
void fn_8004C510(void) {
    return;
}

// .text:0x8004C5F8 size:0x404
void fn_8004C5F8(void) {
    return;
}

// .text:0x8004C9FC size:0xC
void fn_8004C9FC(void) {
    lbl_803CB874 = lbl_803CB878;
}

// .text:0x8004CA08 size:0xC
void fn_8004CA08(s32 value) {
    lbl_803CB878 = value;
    lbl_803CB874 = value;
}

// .text:0x8004CA14 size:0x34
void fn_8004CA14(s32 a, s32 b) {
    fn_8000FE08(lbl_803C5F74.id, a, b);
}
