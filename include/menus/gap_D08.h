#ifndef __MENUS_gap_D08_H_
#define __MENUS_gap_D08_H_

#include "mssbTypes.h"

typedef struct MenusD08State {
    u16 unk0;
    u16 selection;
    u16 state;
    u16 previousSelection;
    u16 previousState;
    u8 _padA[2];
    u16 input[2];
    u8 flags;
} MenusD08State;

extern MenusD08State* lbl_803CBBCC;

void fn_2_D08(u16 index, u16 time, u8 mode);
void fn_2_D88(void);
void fn_2_E84(void);
void fn_2_F64(void);
void fn_2_1018(u16 index);
void fn_2_10AC(void);
s32 fn_2_10FC(void);
void fn_2_1130(s16 state);
void fn_2_1164(void);
void fn_2_119C(void);
void fn_2_11A0(u16 selection);
void fn_2_11D8(void);

#endif // !__MENUS_gap_D08_H_
