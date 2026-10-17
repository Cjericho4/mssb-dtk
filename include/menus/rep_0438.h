#ifndef __MENUS_rep_0438_H_
#define __MENUS_rep_0438_H_

#include "mssbTypes.h"

typedef struct MenusPlayerInput {
    u16 unk0;
    u16 unk2;
    u16 buttons;
} MenusPlayerInput;

typedef struct MenusSaveState {
    u8 _pad0[0x46E0];
    s32 players[2];
    u32 timeHigh;
    u32 timeLow;
    u32 alternateTimeHigh;
    u32 alternateTimeLow;
    u8 _pad46F8[4];
    u8 unk46FC;
    s8 unk46FD;
    s8 unk46FE;
    s8 unk46FF;
    u8 _pad4700[0x29];
    u8 unk4729;
    u8 unk472A;
    u8 unk472B;
    MenusPlayerInput input[2];
    u8 _pad4738[0x10];
    struct DrawingSceneStruct* scene; /* 0x4748 */
    u8 _pad474C[8];
    u8 unk4754;
    u8 unk4755;
    u8 unk4756;
    u8 _pad4757[0x158];
    u8 unk48AF;
    u8 _pad48B0[3];
    u8 unk48B3;
} MenusSaveState;

extern MenusSaveState lbl_8034E9A0;

void fn_2_12238(void);
void fn_2_123CC(void);
void fn_2_12988(void);
void fn_2_129AC(void);
void fn_2_129D0(void);
void fn_2_12A70(void);
void fn_2_12B60(void);
void fn_2_12C34(void);
void fn_2_12CD8(void);
void fn_2_12F88(void);

#endif // !__MENUS_rep_0438_H_
