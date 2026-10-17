#include "menus/rep_08E8.h"
#include "game/rep_1E08.h"
#include "math.h"
#include "UnknownHeaders.h"
#include "menus/rep_0B08.h"
#include "menus/rep_10C0.h"
#include "menus/gap_3C03C.h"
#include "menus/gap_4B1AC.h"

extern u32 lbl_803CBD0C;
extern MenusEffectState* lbl_2_data_13374[];
extern void fn_80031CA4(Vec* position, MenusEffectState* state);

extern MenusDisplayConfig lbl_2_data_13228[];
extern u16 lbl_2_data_13238[];
extern void LITXForm(MenusLight* light, Mtx matrix);

// .text:0x00046C88 size:0x78
void fn_2_46C88(s32 index) {
    Vec position;
    fn_2_68690(0);
    fn_2_68DAC(index, &position);
    PSVECScale(&position, 2.0f, &position);
    lbl_2_data_13374[0]->type = lbl_803CBD0C;
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// .text:0x00046D00 size:0x34
BOOL fn_2_46D00(void) {
    if (lbl_2_bss_1A8248->unk441C == 5 && lbl_2_bss_1A8248->unk4422 >= 6) return TRUE;
    return FALSE;
}

// .text:0x00046D34 size:0x60
void fn_2_46D34(s32 amount) {
    lbl_2_bss_1A8248->previousCounter = lbl_2_bss_1A8248->counter;
    lbl_2_bss_1A8248->counter += amount;
    if (lbl_2_bss_1A8248->counter > 999) lbl_2_bss_1A8248->counter = 999;
    if (lbl_2_bss_1A8248->counter < 0) lbl_2_bss_1A8248->counter = 0;
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
    AnimationStruct* anim = &g_hugeAnimStruct.fielderStructs[lbl_2_bss_1A824C->animationIndex];
    anim->unk34.x = 0.0f;
    anim->unk34.y = 0.0f;
    anim->unk34.z = 0.0f;
    anim->unk40.x = 0.0f;
    anim->unk40.y = 0.0f;
    anim->unk40.z = 0.0f;
}

// .text:0x00048D54 size:0x60
void fn_2_48D54(void) {
    s32 i = 0;
    do {
        Fn52768Result* camera = fn_80052768(0);
        LITXForm(g_hugeAnimStruct.menuLights[i], camera->mtx);
        i++;
    } while (i < 4);
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
void fn_2_4917C(u16* text, s32 value, s32 flags, s32 mode, s32 extra) {
    return;
}

// .text:0x00049DB8 size:0xA4
void fn_2_49DB8(s32 x, s32 y, s32 value, s32 flags, s32 z, s32 mode, s32 extra, s32 a, s32 b, s32 c) {
    u16* text = _OSAllocFromHeap(16, 64);
    fn_2_4917C(text, value, flags, mode, extra);
    fn_2_513E0(text, x, y, z, extra, a, b, c);
    if (text != 0) fn_800ACFB0(text);
}

// .text:0x00049E5C size:0xA0
void fn_2_49E5C(s32 x, s32 y, s32 value, s32 flags, s32 mode, s32 extra, s32 a, s32 b, s32 c) {
    u16* text = _OSAllocFromHeap(16, 64);
    fn_2_4917C(text, value, flags, mode, extra);
    fn_2_513E0(text, x, y, 0, extra, a, b, c);
    if (text != 0) fn_800ACFB0(text);
}

// .text:0x00049EFC size:0x80
s32 fn_2_49EFC(u16* text, u16 font) {
    s32 width = 0;
    while (*text != 0x4000) {
        u16 code = *text;
        if (code == 0x4003) width += lbl_2_data_13238[font];
        else if (code == 0x4002) width += (u32)lbl_2_data_13238[font] >> 1;
        else if (!(code & 0x4000)) {
            if (code & 0x8000) width += lbl_2_data_13238[font];
            else width += (u32)lbl_2_data_13238[font] >> 1;
        }
        text++;
    }
    return width;
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
f32 fn_2_4A18C(f32 angle) {
    if (angle >= 3.1415927f) {
        while (angle >= 3.1415927f) angle -= 6.2831855f;
    }
    if (angle < -3.1415927f) {
        while (angle < -3.1415927f) angle = 6.2831855f + angle;
    }
    return angle;
}

// .text:0x0004A1E8 size:0x4C
f32 fn_2_4A1E8(f32 x, f32 y) {
    if (x == 0.0f && y == 0.0f) return 0.0f;
    return (f32)atan2(y, x);
}

// .text:0x0004A234 size:0x90
s32 fn_2_4A234(f32 x, f32 y) {
    s32 angle;
    if (0.0f == x) {
        if (y >= 0.0f) return 0x400;
        return 0xC00;
    }
    angle = (s32)((2048.0f * (f32)atan2(y, x)) / 3.1415927f);
    if ((s16)angle < 0) return (s16)(angle + 0x1000);
    return angle;
}

// .text:0x0004A2C4 size:0x4C
s32 fn_2_4A2C4(f32 angle) {
    if (angle < 0.0f) angle = 6.2831855f + angle;
    return (s32)((2048.0f * angle) / 3.1415927f);
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
