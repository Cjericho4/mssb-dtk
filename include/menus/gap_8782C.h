#ifndef __MENUS_gap_8782C_H_
#define __MENUS_gap_8782C_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct MenusVisibilityState {
    u8 _pad0[0x50];
    u8 visible[1]; /* extent unknown */
} MenusVisibilityState;
extern hugeAnimStruct* lbl_2_bss_340140;
extern MenusVisibilityState* lbl_2_bss_3401BC;

void fn_2_8782C(void);
void fn_2_87998(void);
void fn_2_87FB0(void);
void fn_2_88250(void);
void fn_2_883C8(void);
void fn_2_887F8(void);
void fn_2_88D90(void);
void fn_2_89038(void);
void fn_2_895F8(void);
void fn_2_8975C(void);
void fn_2_89F70(void);
void fn_2_8A008(void);
void fn_2_8A824(void);
void fn_2_8ABFC(void);
void fn_2_8AC84(s32 index, u8 visible);
void fn_2_8ACB0(s32 index, u8 visible);
void fn_2_8ACDC(void);

#endif // !__MENUS_gap_8782C_H_
