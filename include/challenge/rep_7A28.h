#ifndef __CHALLENGE_rep_7A28_H_
#define __CHALLENGE_rep_7A28_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"
#include "challenge/challenge.h"

typedef struct Rep7A28Slot {
    /* 0x00 */ s32 value;
    /* 0x04 */ s32 mode;
    /* 0x08 */ u8 _pad8[0x48];
} Rep7A28Slot;
extern Rep7A28Slot lbl_1_data_10908[3];
extern s32 lbl_1_data_109F8;
typedef struct Rep7A28Globals80366158 {
    /* 0x0 */ u8 _pad0[8];
    /* 0x8 */ s32 unk8;
} Rep7A28Globals80366158;
extern Rep7A28Globals80366158 lbl_80366158;
void fn_800AD038(s32 arg0);

void fn_1_27560(s32 value);
void fn_1_27594(void);
void fn_1_276CC(void);
void fn_1_27AD0(void);
void fn_1_27AD4(void);
void fn_1_27BB8(void);
#include "challenge/rep_7978.h"
#include "stl/string.h"
extern void (*lbl_1_data_108E8[])(void);
void fn_1_27D6C(void);
void fn_1_27E50(void);
void fn_1_27E98(void);
void fn_1_28118(void);
void fn_1_28200(void);

#endif // !__CHALLENGE_rep_7A28_H_
