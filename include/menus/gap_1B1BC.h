#ifndef __MENUS_gap_1B1BC_H_
#define __MENUS_gap_1B1BC_H_

#include "mssbTypes.h"
#include "menus/rep_10C0.h"

typedef struct MenusDisplayPanel {
    u8 visible;
    u8 _pad1[0x1E];
    u8 controls[3];
    u8 _pad22[0x11];
    u8 active;
    u8 _pad34[0x1B6];
} MenusDisplayPanel;

typedef struct MenusDisplayState {
    u8 _pad0[0x162657];
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
void fn_2_1C3A4(void);
void fn_2_1C3A8(void);
void fn_2_1C41C(void);
void fn_2_1C490(void);
void fn_2_1C504(void);
void fn_2_1C5C8(void);
void fn_2_1C714(void);
void fn_2_1C860(void);
void fn_2_1CF94(void);

#endif // !__MENUS_gap_1B1BC_H_
