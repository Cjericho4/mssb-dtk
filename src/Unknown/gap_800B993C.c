#include "Unknown/gap_800B993C.h"

// .text:0x800B993C size:0xC
void fn_800B993C(void) {
    lbl_803CC200 = 0x0;
}

// .text:0x800B9948 size:0x8
void fn_800B9948(s32 value) {
    lbl_803CC200 = value;
}

// .text:0x800B9950 size:0x1C
void fn_800B9950(u32 flags, f32 a, f32 b) {
    if (flags & 1) {
        lbl_803CC1F8 = a;
    }
    if (flags & 2) {
        lbl_803CC1FC = b;
    }
}

// .text:0x800B996C size:0x8
void fn_800B996C(s32 value) {
    lbl_803CC1F4 = value;
}

// .text:0x800B9974 size:0x50
void SetFogNone(void) {
    Gap800B993CColor color;
    color.r = color.g = color.b = 0;
    GXSetFog(0, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

// .text:0x800B99C4 size:0x6C
void SetFog(void) {
    return;
}

// .text:0x800B9A30 size:0x6C
void SetFogNoneAgain(void) {
    return;
}

// .text:0x800B9A9C size:0xC
void fn_800B9A9C(s32 a, f32 b) {
    lbl_803CC21C = a;
    lbl_803CC218 = b;
}

// .text:0x800B9AA8 size:0x8
void fn_800B9AA8(s32 value) {
    lbl_803CC1F0 = value;
}

// .text:0x800B9AB0 size:0x3F8
void fn_800B9AB0(void) {
    return;
}

// .text:0x800B9EA8 size:0x5A4
void fn_800B9EA8(void) {
    return;
}

// .text:0x800BA44C size:0x3FC
void fn_800BA44C(void) {
    return;
}

// .text:0x800BA848 size:0x12E4
void Custom_SetState(void) {
    return;
}

// .text:0x800BBB2C size:0x430
void SetState(void) {
    return;
}

// .text:0x800BBF5C size:0x168
void GetColorFromQuant(void) {
    return;
}

// .text:0x800BC0C4 size:0x724
#pragma dont_inline on
void DOVARender(Gap800B993CObj* obj, f32 matrix[3][4], u32 a, u32 b) {
    return;
}

#pragma dont_inline reset

// .text:0x800BC7E8 size:0x3C
void DOVARenderSkin(Gap800B993CObj* obj, f32 matrix[3][4], f32 skinMatrices[][3][4], u16* indices, u32 a, u32 b) {
    lbl_803CC204 = skinMatrices;
    lbl_803CC208 = indices;
    DOVARender(obj, matrix, a, b);
    lbl_803CC204 = NULL;
    lbl_803CC208 = NULL;
}

// .text:0x800BC824 size:0x10
void fn_800BC824(Gap800B993CObj* obj, s32 value) {
    if (obj != NULL) {
        obj->unk50 = value;
    }
}

// .text:0x800BC834 size:0x2C
void DOSetWorldMatrix(Gap800B993CObj* obj, f32 matrix[3][4]) {
    PSMTXCopy(matrix, obj->worldMatrix);
}

// .text:0x800BC860 size:0x258
void InitDisplayObjWithLayout(void) {
    return;
}

// .text:0x800BCAB8 size:0x8C
void DOGet(void) {
    return;
}

// .text:0x800BCB44 size:0x21C
void LoadGeoPalette(void) {
    return;
}

// .text:0x800BCD60 size:0x5C
void convertGeometryAndSknHeader(void) {
    return;
}

// .text:0x800BCDBC size:0x7C
void fn_800BCDBC(void) {
    return;
}

// .text:0x800BCE38 size:0xC0
void fn_800BCE38(void) {
    return;
}

// .text:0x800BCEF8 size:0x298
void fn_800BCEF8(void) {
    return;
}

// .text:0x800BD190 size:0x58
void fn_800BD190(void) {
    return;
}

// .text:0x800BD1E8 size:0x8
void fn_800BD1E8(s32 value) {
    lbl_803CC20C = value;
}

// .text:0x800BD1F0 size:0x8
void __MTGQR5(void) {
    return;
}

// .text:0x800BD1F8 size:0x8
void __MTGQR6(void) {
    return;
}

// .text:0x800BD200 size:0x8
void __MTGQR7(void) {
    return;
}

// .text:0x800BD208 size:0x38
void GQRSetup7(void) {
    return;
}

// .text:0x800BD240 size:0x38
void GQRSetup6(void) {
    return;
}

// .text:0x800BD278 size:0x38
void GQRSetup5(void) {
    return;
}

// .text:0x800BD2B0 size:0x1C
u8 fn_800BD2B0(Gap800B993CColor* out) {
    if (lbl_803CC220 != 0) {
        *out = lbl_803CC224;
    }
    return lbl_803CC220;
}

// .text:0x800BD2CC size:0x10
void fn_800BD2CC(u8 enable, Gap800B993CColor* color) {
    u32 value = color->word;
    lbl_803CC220 = enable;
    lbl_803CC224.word = value;
}

// .text:0x800BD2DC size:0x24
void fn_800BD2DC(void) {
    lbl_803CC220 = 0;
    lbl_803CC224.r = 0;
    lbl_803CC224.b = 0;
    lbl_803CC224.g = 0;
    lbl_803CC224.a = 0xFF;
}

// .text:0x800BD300 size:0xA0
void LITXForm(void) {
    return;
}
