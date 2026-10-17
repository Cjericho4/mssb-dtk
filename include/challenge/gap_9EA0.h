#ifndef __CHALLENGE_gap_9EA0_H_
#define __CHALLENGE_gap_9EA0_H_

#include "mssbTypes.h"

typedef struct Gap9EA0Obj {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} Gap9EA0Obj;

void fn_1_9EA0(void);
void fn_1_9F04(void);
void fn_1_A024(void);
void fn_1_A184(void);
void fn_1_A1F4(Gap9EA0Obj* obj, s32 arg1, s32 arg2, s32 arg3);
void fn_1_A210(void);
void fn_1_A250(void);

#endif // !__CHALLENGE_gap_9EA0_H_
