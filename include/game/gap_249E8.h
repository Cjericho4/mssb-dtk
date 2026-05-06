#ifndef __GAME_gap_249E8_H_
#define __GAME_gap_249E8_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 _pad15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 _pad1A[2];
} Data1F090Entry; // size: 0x1C

typedef struct {
    u8 _pad0[0x34];
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Data2398Entry; // size 0x40

extern Data1F090Entry lbl_3_data_1F090[];
extern Data2398Entry lbl_3_data_2398[];

void fn_3_249E8(s32 arg0);
void fn_3_24ADC(s32 arg0, s32 arg1);
void fn_3_24DBC(s32 arg0);
void fn_3_24EA0(void);
void fn_3_24F20(void);
void fn_3_24F24(void);
void fn_3_250FC(void);

#endif // !__GAME_gap_249E8_H_
