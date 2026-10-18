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
