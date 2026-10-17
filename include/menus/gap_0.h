#ifndef __MENUS_gap_0_H_
#define __MENUS_gap_0_H_

#include "mssbTypes.h"

typedef struct MenusInputState {
    u8 _pad0[2];
    u16 buttons;
    u8 _pad4[0x1E];
    u16 otherButtons;
} MenusInputState;
extern MenusInputState lbl_803C77B8;

typedef struct MenusCommandQueue {
    u8 _pad0[0x15];
    u8 writeIndex;
    u8 readIndex;
    u8 commands[0x20];
} MenusCommandQueue;

extern MenusCommandQueue* lbl_2_bss_4;

void fn_2_0(void);
void fn_2_3C(void);
void _epilog(void);
void _prolog(void);
void fn_2_110(void);
void fn_2_160(void);
void fn_2_1A8(void);
void fn_2_2D8(void);
void fn_2_2DC(void);
void fn_2_328(void);
void fn_2_374(void);
void fn_2_4C4(void);
u8 fn_2_510(MenusCommandQueue* queue);
void fn_2_554(void);
void fn_2_664(void);
void fn_2_708(void);
void fn_2_794(void);
void fn_2_940(void);
void fn_2_978(void);
void fn_2_A14(void);

#endif // !__MENUS_gap_0_H_
