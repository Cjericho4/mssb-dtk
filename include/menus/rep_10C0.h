#ifndef __MENUS_rep_10C0_H_
#define __MENUS_rep_10C0_H_

#include "mssbTypes.h"

typedef struct Rep10C0State {
    u8 _pad0[0x195424];
    u32 timeHigh;
    u32 timeLow;
    u8 _pad19542C[0x2270];
    s32 animationIndex; /* 0x19769C */
    u8 _pad1976A0[0x44];
    s16 unk1976E4;
    u8 _pad1976E6[0x64];
    s16 unk19774A;
    u8 _pad19774C[6];
    s16 unk197752;
    s16 unk197754;
    u8 _pad197756[0xD4];
    u8 unk19782A;
    u8 unk19782B;
    u8 unk19782C;
    u8 _pad19782D[5];
    u8 unk197832;
    u8 _pad197833[0x16];
    u8 unk197849;
    u8 _pad19784A[0xC];
    u8 unk197856;
} Rep10C0State;

extern Rep10C0State* lbl_2_bss_1A824C;

void fn_2_927C8(void);
void fn_2_92A34(void);
void fn_2_92CB0(void);
void fn_2_92F2C(void);
void fn_2_932DC(void);
void fn_2_93BF8(void);
void fn_2_93C64(void);
void fn_2_94604(u8 value);
void fn_2_9461C(s16 value);
void fn_2_94634(void);
void fn_2_946DC(void);

#endif // !__MENUS_rep_10C0_H_
