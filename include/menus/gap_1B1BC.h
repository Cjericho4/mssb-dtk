#ifndef __MENUS_gap_1B1BC_H_
#define __MENUS_gap_1B1BC_H_

#include "mssbTypes.h"
#include "menus/rep_10C0.h"
#include "menus/gap_4B1AC.h"

typedef struct MenusLoadingState {
    u8 _pad0[0x30];
    s16 state;
    u8 _pad32[2];
    u8 unk34;
} MenusLoadingState;
extern MenusLoadingState* lbl_2_bss_1A823C;

typedef struct MenusDisplayPanel {
    u8 visible;
    u8 _pad1[0x1E];
    u8 controls[3];
    u8 _pad22[0x11];
    u8 active;
    u8 _pad34[0x11D];
    u8 pending;
    u8 _pad152[0x98];
} MenusDisplayPanel;

typedef struct MenusDisplayState {
    MenusResourceBank banks[70];
    u8 _pad162600[4];
    u8 flag162604;
    u8 flag162605;
    u8 _pad162606[0x48];
    u8 flag16264E;
    u8 _pad16264F[8];
    MenusDisplayPanel panels[2];
} MenusDisplayState;
extern MenusDisplayState* lbl_2_bss_1A8234;

void fn_2_1B1BC(void);
void fn_2_1B314(void);
void fn_2_1B52C(void);
void fn_2_1B5C0(void);
void fn_2_1B6CC(void);
void fn_2_1B7B4(void);
void fn_2_1BF50(void);
void fn_2_1BFD0(void);
void fn_2_1C0D4(void);
void fn_2_1C21C(void);
void fn_2_1C244(void);
void fn_2_1C33C(void);
void fn_2_1C3A8(void);
void fn_2_1C41C(void);
void fn_2_1C490(void);
void fn_2_1C504(s32 id);
void fn_2_1C5C8(void);
void fn_2_1C714(void);
void fn_2_1C860(void);
void fn_2_1CF94(void);

#endif // !__MENUS_gap_1B1BC_H_
