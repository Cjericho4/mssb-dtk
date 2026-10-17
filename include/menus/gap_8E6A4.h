#ifndef __MENUS_gap_8E6A4_H_
#define __MENUS_gap_8E6A4_H_

#include "mssbTypes.h"

typedef struct MenusExitState {
    u8 _pad0[0x3E];
    u8 unk3E;
} MenusExitState;
extern MenusExitState lbl_803C5F04;

void fn_2_8E6A4(void);
void fn_2_8E8A4(void);
void fn_2_8EA80(void);
void fn_2_8ED4C(void);
void fn_2_8EDC4(void);
void fn_2_8EEC8(void);

#endif // !__MENUS_gap_8E6A4_H_
