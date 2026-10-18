#ifndef __UNKNOWN_gap_800506E8_H_
#define __UNKNOWN_gap_800506E8_H_

#include "mssbTypes.h"
typedef struct Gap800506E8Camera { u8 _pad0[0xA8]; } Gap800506E8Camera;
extern Gap800506E8Camera lbl_803C639C[2];
extern s32 lbl_803CB880;
typedef struct Gap800506E8State {
    u8 _pad0[0x7C];
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ u8 unk7E;
    u8 _pad7F[0xF];
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F;
    /* 0x90 */ u8 unk90;
} Gap800506E8State;
extern Gap800506E8State lbl_803C6028;

extern s32 lbl_803CB880;
extern s32 lbl_803CBD14;

void fn_800506E8(void);
void fn_80050760(void);
void fn_80050F78(void);
void fn_80050FE8(void);
void fn_8005138C(void);
void fn_80051D00(void);
void fn_80052188(void);
void fn_800521B0(void);
void fn_8005240C(void);
void fn_80052634(void);
s32 fn_8005268C(void);
void fn_80052694(void);
void fn_80052734(void);
Gap800506E8Camera* fn_80052768(s32 index);
void fn_80052798(s32 value);
s32 fn_800527BC(void);
void fn_800527C4(void);

#endif // !__UNKNOWN_gap_800506E8_H_
