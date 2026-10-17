#ifndef __CHALLENGE_gap_9EA0_H_
#define __CHALLENGE_gap_9EA0_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
#include "challenge/rep_02A8.h"

typedef struct Gap9EA0State {
    /* 0x00 */ u8 _pad0[0xC];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 _pad10[0x14];
    /* 0x24 */ s32 slots[11];
} Gap9EA0State;
extern Gap9EA0State lbl_1_common_bss_49A78;

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
typedef struct Gap9EA0TextEntry {
    /* 0x00 */ char* text;
    /* 0x04 */ u8 _pad4[0xC];
} Gap9EA0TextEntry;
typedef struct Gap9EA0TextList {
    /* 0x00 */ Gap9EA0TextEntry* entries;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 start;
    /* 0x0C */ s32 count;
    /* 0x10 */ s32 total;
} Gap9EA0TextList;
void fn_1_A184(Gap9EA0TextList* list);
void fn_1_A1F4(Gap9EA0Obj* obj, s32 arg1, s32 arg2, s32 arg3);
char* fn_1_A210(char* path);
void fn_1_A250(void);

#endif // !__CHALLENGE_gap_9EA0_H_
