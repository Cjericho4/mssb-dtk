#ifndef __MENUS_gap_94854_H_
#define __MENUS_gap_94854_H_

#include "mssbTypes.h"
#include "menus/rep_10C0.h"

typedef struct MenusPreferences {
    u8 _pad0[0xF];
    u8 pending;
} MenusPreferences;
extern MenusPreferences lbl_2_bss_1033C;

void fn_2_94854(u8 value);
void fn_2_9486C(void);
void fn_2_948B8(void);
void fn_2_9493C(void);
void fn_2_94A8C(void);
void fn_2_95604(void);
void fn_2_95654(void);
void fn_2_95B28(void);
void fn_2_95B78(void);
void fn_2_95E80(void);
void fn_2_95F3C(void);
void fn_2_95FE0(void);
void fn_2_96118(void);
void fn_2_96698(void);
void fn_2_96AD4(void);
void fn_2_96D20(void);

#endif // !__MENUS_gap_94854_H_
