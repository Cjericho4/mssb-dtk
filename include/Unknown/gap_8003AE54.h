#ifndef __UNKNOWN_gap_8003AE54_H_
#define __UNKNOWN_gap_8003AE54_H_

#include "mssbTypes.h"

extern u8 lbl_803CBCB4;
extern s32 lbl_803CBCB8;

typedef struct Gap8003AE54Buffer {
    u8 _pad0[0x94];
    /* 0x94 */ u8 unk94;
    /* 0x95 */ u8 unk95;
    /* 0x96 */ u8 unk96;
} Gap8003AE54Buffer;
extern Gap8003AE54Buffer lbl_802D4B00;

typedef struct Gap8003AE54Task {
    u8 _pad0[0x14];
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    u8 _pad19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    u8 _pad1C;
    /* 0x1D */ u8 unk1D;
    u8 _pad1E[3];
    /* 0x21 */ u8 unk21;
} Gap8003AE54Task;
Gap8003AE54Task* fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
typedef struct Gap8003AE54Counter {
    u8 _pad0[0x10];
    /* 0x10 */ s16 unk10;
} Gap8003AE54Counter;
extern Gap8003AE54Counter* lbl_803CC1B8[2];
typedef struct Gap8003AE54Words {
    s32 unk0, unk4, unk8, unkC;
    u8 _pad10[0x10];
} Gap8003AE54Words;
extern Gap8003AE54Words lbl_802D4AE0;

u8 fn_8003AE54(void);
void fn_8003AE5C(u8 value);
void fn_8003AE64(void);
u8 fn_8003AE70(s32 arg0);
void fn_8003AECC(void);
void fn_8003B5B0(void);
void fn_8003BB90(void);
void fn_8003BF54(void);
void fn_8003C00C(void);
void fn_8003E8D8(void);
void fn_8003F23C(void);
void fn_8003F2B8(void);
void fn_8004053C(void);
void fn_80040C14(void);
void fn_80040FE0(void);
void fn_80041074(void);
void fn_80041150(void);

#endif // !__UNKNOWN_gap_8003AE54_H_
