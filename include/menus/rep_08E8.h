#ifndef __MENUS_rep_08E8_H_
#define __MENUS_rep_08E8_H_

#include "mssbTypes.h"

typedef struct MenusLight MenusLight;

typedef struct MenusDisplayConfig {
    u32 unk0;
    u32 unk4;
} MenusDisplayConfig;

void fn_2_46C88(s32 index, s32 mode);
BOOL fn_2_46D00(void);
void fn_2_46D34(s32 amount);
void fn_2_46D94(void);
void fn_2_472C4(void);
void fn_2_474F8(void);
void fn_2_474FC(void);
void fn_2_47540(void);
void fn_2_4777C(void);
void fn_2_477C0(void);
void fn_2_478F4(void);
void fn_2_47AFC(void);
void fn_2_47B24(void);
void fn_2_47CFC(void);
void fn_2_47FF8(void);
void fn_2_481B8(void);
void fn_2_481F4(void);
void fn_2_487A0(void);
void fn_2_489DC(void);
void fn_2_48A1C(void);
void fn_2_48BE0(void);
void fn_2_48D08(void);
void fn_2_48D54(void);
void fn_2_48DB4(void);
void fn_2_4906C(void);
void fn_2_4917C(u16* text, s32 value, s32 flags, s32 mode, s32 extra);
void fn_2_49DB8(s32 x, s32 y, s32 value, s32 flags, s32 z, s32 mode, s32 extra, s32 a, s32 b, s32 c);
void fn_2_49E5C(s32 x, s32 y, s32 value, s32 flags, s32 mode, s32 extra, s32 a, s32 b, s32 c);
s32 fn_2_49EFC(u16* text, u16 font);
void fn_2_49F7C(void);
void fn_2_4A064(void);
s32 fn_2_4A068(u16* text);
u16* fn_2_4A094(u16* dst, u16* src);
void fn_2_4A0C4(void);
s16 fn_2_4A150(s16 angle);
f32 fn_2_4A18C(f32 angle);
f32 fn_2_4A1E8(f32 x, f32 y);
s32 fn_2_4A234(f32 x, f32 y);
s32 fn_2_4A2C4(f32 angle);
s16 fn_2_4A310(s16 a, s16 b);
void fn_2_4A340(void);
void fn_2_4A6E8(void);
void fn_2_4AB1C(void);
void fn_2_4ACF8(void);
void fn_2_4AEE4(void);

#endif // !__MENUS_rep_08E8_H_
