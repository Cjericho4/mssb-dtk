#include "Unknown/gap_800528AC.h"

// .text:0x800528AC size:0x8
void fn_800528AC(s32 value) {
    lbl_803CBD10 = value;
}

// .text:0x800528B4 size:0xC
void fn_800528B4(void) {
    lbl_803CBD10 = 0x0;
}

// .text:0x800528C0 size:0xA8
void fn_800528C0(s16* screenX, s16* screenY, f32 x, f32 y, f32 z) {
    Gap800528ACVec v;
    f32 halfWidth;
    f32 halfHeight;
    v.x = x;
    v.y = y;
    v.z = z;
    PSMTXMultVec(lbl_803C639C[0].view, &v, &v);
    PSMTX44MultVec(lbl_803C639C[0].projection, &v, &v);
    halfWidth = 320.0f;
    halfHeight = 224.0f;
    *screenX = v.x * halfWidth + halfWidth;
    *screenY = -v.y * halfHeight + halfHeight;
}

// .text:0x80052968 size:0x408
void fn_80052968(void) {
    return;
}

// .text:0x80052D70 size:0x228
void fn_80052D70(void) {
    return;
}

// .text:0x80052F98 size:0x238
void possiblyTransitionBlackScreen(void) {
    return;
}

// .text:0x800531D0 size:0x640
void fn_800531D0(void) {
    return;
}

// .text:0x80053810 size:0x7D8
void fn_80053810(void) {
    return;
}

// .text:0x80053FE8 size:0x2DC
void fn_80053FE8(void) {
    return;
}

// .text:0x800542C4 size:0x64C
void fn_800542C4(void) {
    return;
}

// .text:0x80054910 size:0x1F0
void fn_80054910(void) {
    return;
}

// .text:0x80054B00 size:0x874
void fn_80054B00(void) {
    return;
}

// .text:0x80055374 size:0x424
void fn_80055374(void) {
    return;
}

// .text:0x80055798 size:0x254
void fn_80055798(void) {
    return;
}

// .text:0x800559EC size:0x734
void fn_800559EC(void) {
    return;
}

// .text:0x80056120 size:0x8A8
void fn_80056120(void) {
    return;
}

// .text:0x800569C8 size:0x11C
void fn_800569C8(void) {
    return;
}

// .text:0x80056AE4 size:0x48C
void drawStarProgressionMenu(void) {
    return;
}

// .text:0x80056F70 size:0x350
void someChallengeStarFunction(void) {
    return;
}

// .text:0x800572C0 size:0x430
void someChallengeStarFunction2(void) {
    return;
}

// .text:0x800576F0 size:0x518
void challengeCheckStarsMenuLoading(void) {
    return;
}

// .text:0x80057C08 size:0xA4
void starMenu(void) {
    return;
}

// .text:0x80057CAC size:0x3A4
void fn_80057CAC(void) {
    return;
}

// .text:0x80058050 size:0x344
void fn_80058050(void) {
    return;
}

// .text:0x80058394 size:0x2B0
void fn_80058394(void) {
    return;
}

// .text:0x80058644 size:0x4DC
void fn_80058644(void) {
    return;
}

// .text:0x80058B20 size:0x2EC
void fn_80058B20(void) {
    return;
}

// .text:0x80058E0C size:0x64C
void fn_80058E0C(void) {
    return;
}

// .text:0x80059458 size:0x27C
void fn_80059458(void) {
    return;
}

// .text:0x800596D4 size:0x464
void fn_800596D4(void) {
    return;
}

// .text:0x80059B38 size:0x818
void starMissionRelated1(void) {
    return;
}

// .text:0x8005A350 size:0xC18
void fn_8005A350(void) {
    return;
}

// .text:0x8005AF68 size:0x330
void fn_8005AF68(void) {
    return;
}

// .text:0x8005B298 size:0x4C8
void fn_8005B298(void) {
    return;
}

// .text:0x8005B760 size:0x3FC
void fn_8005B760(void) {
    return;
}

// .text:0x8005BB5C size:0x3E4
void fn_8005BB5C(void) {
    return;
}

// .text:0x8005BF40 size:0x370
void fn_8005BF40(void) {
    return;
}

// .text:0x8005C2B0 size:0x314
void fn_8005C2B0(void) {
    return;
}

// .text:0x8005C5C4 size:0x26C
void fn_8005C5C4(void) {
    return;
}

// .text:0x8005C830 size:0x4B4
void fn_8005C830(void) {
    return;
}

// .text:0x8005CCE4 size:0x1130
void fn_8005CCE4(void) {
    return;
}

// .text:0x8005DE14 size:0xBC4
void fn_8005DE14(void) {
    return;
}

// .text:0x8005E9D8 size:0x2B0
void fn_8005E9D8(void) {
    return;
}

// .text:0x8005EC88 size:0x3E0
void fn_8005EC88(void) {
    return;
}

// .text:0x8005F068 size:0x6CC
void fn_8005F068(void) {
    return;
}

// .text:0x8005F734 size:0x29C
void fn_8005F734(void) {
    return;
}

// .text:0x8005F9D0 size:0x2D0
void fn_8005F9D0(void) {
    return;
}

// .text:0x8005FCA0 size:0x4E4
void fn_8005FCA0(void) {
    return;
}

// .text:0x80060184 size:0x1A18
void fn_80060184(void) {
    return;
}

// .text:0x80061B9C size:0x7D0
void fn_80061B9C(void) {
    return;
}

// .text:0x8006236C size:0x20C
void SetMenuNumber(void) {
    return;
}
