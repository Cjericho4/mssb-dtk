#include "menus/rep_08E8.h"
#include "game/rep_1E08.h"
#include "UnknownHeaders.h"
#include "menus/rep_0B08.h"

extern MenusDisplayConfig lbl_2_data_13228[];

// .text:0x00046C88 size:0x78
void fn_2_46C88(void) {
    return;
}

// .text:0x00046D00 size:0x34
BOOL fn_2_46D00(void) {
    if (lbl_2_bss_1A8248->unk441C == 5 && lbl_2_bss_1A8248->unk4422 >= 6) return TRUE;
    return FALSE;
}

// .text:0x00046D34 size:0x60
void fn_2_46D34(void) {
    return;
}

// .text:0x00046D94 size:0x530
void fn_2_46D94(void) {
    return;
}

// .text:0x000472C4 size:0x234
void fn_2_472C4(void) {
    return;
}

// .text:0x000474F8 size:0x4
void fn_2_474F8(void) {
    return;
}

// .text:0x000474FC size:0x44
void fn_2_474FC(void) {
    hugeAnimStruct* anim = &g_hugeAnimStruct;
    if (anim->animBankPtr != NULL) {
        fn_800ACFB0(anim->animBankPtr);
        anim->animBankPtr = NULL;
    }
}

// .text:0x00047540 size:0x23C
void fn_2_47540(void) {
    return;
}

// .text:0x0004777C size:0x44
void fn_2_4777C(void) {
    hugeAnimStruct* anim = &g_hugeAnimStruct;
    if (anim->modelDataPtr != NULL) {
        fn_800ACFB0(anim->modelDataPtr);
        anim->modelDataPtr = NULL;
    }
}

// .text:0x000477C0 size:0x134
void fn_2_477C0(void) {
    return;
}

// .text:0x000478F4 size:0x208
void fn_2_478F4(void) {
    return;
}

// .text:0x00047AFC size:0x28
void fn_2_47AFC(void) {
    s32 i;
    for (i = 0; i < 13; i++) {}
}

// .text:0x00047B24 size:0x1D8
void fn_2_47B24(void) {
    return;
}

// .text:0x00047CFC size:0x2FC
void fn_2_47CFC(void) {
    return;
}

// .text:0x00047FF8 size:0x1C0
void fn_2_47FF8(void) {
    return;
}

// .text:0x000481B8 size:0x3C
void fn_2_481B8(void) {
    Fn52768Result* camera = fn_80052768(0);
    fn_800BD670((HugeAnimCtrlObj*)g_hugeAnimStruct.ctrlOrBonePtr, (s32)camera->mtx);
}

// .text:0x000481F4 size:0x5AC
void fn_2_481F4(void) {
    return;
}

// .text:0x000487A0 size:0x23C
void fn_2_487A0(void) {
    return;
}

// .text:0x000489DC size:0x40
void fn_2_489DC(void) {
    fn_800A7D4C(12, (BdcArrayElement*)&lbl_2_data_13228[lbl_803CBBC0]);
}

// .text:0x00048A1C size:0x1C4
void fn_2_48A1C(void) {
    return;
}

// .text:0x00048BE0 size:0x128
void fn_2_48BE0(void) {
    return;
}

// .text:0x00048D08 size:0x4C
void fn_2_48D08(void) {
    return;
}

// .text:0x00048D54 size:0x60
void fn_2_48D54(void) {
    return;
}

// .text:0x00048DB4 size:0x2B8
void fn_2_48DB4(void) {
    return;
}

// .text:0x0004906C size:0x110
void fn_2_4906C(void) {
    return;
}

// .text:0x0004917C size:0xC3C
void fn_2_4917C(void) {
    return;
}

// .text:0x00049DB8 size:0xA4
void fn_2_49DB8(void) {
    return;
}

// .text:0x00049E5C size:0xA0
void fn_2_49E5C(void) {
    return;
}

// .text:0x00049EFC size:0x80
void fn_2_49EFC(void) {
    return;
}

// .text:0x00049F7C size:0xE8
void fn_2_49F7C(void) {
    return;
}

// .text:0x0004A064 size:0x4
void fn_2_4A064(void) {
    return;
}

// .text:0x0004A068 size:0x2C
s32 fn_2_4A068(u16* text) {
    u16* end = text;
    while (*end != 0x4000) end++;
    return end - text;
}

// .text:0x0004A094 size:0x30
u16* fn_2_4A094(u16* dst, u16* src) {
    u16* start = dst;
    while (*src != 0x4000) *dst++ = *src++;
    *dst = *src;
    return start;
}

// .text:0x0004A0C4 size:0x8C
void fn_2_4A0C4(void) {
    return;
}

// .text:0x0004A150 size:0x3C
s16 fn_2_4A150(s16 angle) {
    if (angle < 0) {
        while (angle < 0) angle += 0x1000;
    }
    if (angle >= 0x1000) {
        while (angle >= 0x1000) angle -= 0x1000;
    }
    return angle;
}

// .text:0x0004A18C size:0x5C
void fn_2_4A18C(void) {
    return;
}

// .text:0x0004A1E8 size:0x4C
void fn_2_4A1E8(void) {
    return;
}

// .text:0x0004A234 size:0x90
void fn_2_4A234(void) {
    return;
}

// .text:0x0004A2C4 size:0x4C
void fn_2_4A2C4(void) {
    return;
}

// .text:0x0004A310 size:0x30
s16 fn_2_4A310(s16 a, s16 b) {
    s16 result = __abs(a - b);
    if (result > 0x800) result = 0x1000 - result;
    return result;
}

// .text:0x0004A340 size:0x3A8
void fn_2_4A340(void) {
    return;
}

// .text:0x0004A6E8 size:0x434
void fn_2_4A6E8(void) {
    return;
}

// .text:0x0004AB1C size:0x1DC
void fn_2_4AB1C(void) {
    return;
}

// .text:0x0004ACF8 size:0x1EC
void fn_2_4ACF8(void) {
    return;
}

// .text:0x0004AEE4 size:0x2C8
void fn_2_4AEE4(void) {
    return;
}
