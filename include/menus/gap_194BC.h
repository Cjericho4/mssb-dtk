#ifndef __MENUS_gap_194BC_H_
#define __MENUS_gap_194BC_H_

#include "mssbTypes.h"
#include "menus/rep_0568.h"
#include "UnknownHeaders.h"

typedef struct MenusControllerState {
    u8 _pad0[0x1F];
    u8 unk1F;
} MenusControllerState;

typedef struct MenusRuntimePreferences {
    u8 unk0;
    u8 _pad1[0x24];
    u8 unk25;
} MenusRuntimePreferences;

extern MenusControllerState lbl_80366158;
extern MenusRuntimePreferences lbl_800E8754;

void fn_2_194BC(Rep0568Obj* obj);
void fn_2_194E8(void);
void fn_2_19520(void);
s32 fn_2_19554(void);
void fn_2_195D8(void);
void fn_2_195DC(void);
void fn_2_19778(void);
void fn_2_197AC(void);
void fn_2_19D04(void);
void fn_2_19F2C(void);
void fn_2_1A1B4(void);
void fn_2_1A2AC(void);
void fn_2_1A420(void);

#endif // !__MENUS_gap_194BC_H_
