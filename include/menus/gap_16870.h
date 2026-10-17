#ifndef __MENUS_gap_16870_H_
#define __MENUS_gap_16870_H_

#include "mssbTypes.h"

typedef struct Menus16870State {
    u8 _pad0[0x14];
    u8 active[8];
    u8 counters[8];
    u8 _pad24[0x22];
    u8 values[4];
    u8 _pad4A[0xA];
} Menus16870State;

extern Menus16870State lbl_2_bss_100B8;

void fn_2_16870(void);
u8 fn_2_16A34(s32 index);
void fn_2_16A48(s32 index, u8 value);
u8 fn_2_16A5C(s32 index);
void fn_2_16A74(s32 index, s32 value);

#endif // !__MENUS_gap_16870_H_
