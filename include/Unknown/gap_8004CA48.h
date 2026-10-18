#ifndef __UNKNOWN_gap_8004CA48_H_
#define __UNKNOWN_gap_8004CA48_H_

#include "mssbTypes.h"
typedef struct Gap8004CA48Selection {
    u8 _pad0[0x18];
    s16 indices[8];
    s8 picks[36]; /* 0x28 */
    s8 busy[36]; /* 0x4C */
    u8 _pad70[0xD];
    /* 0x7D */ u8 unk7D;
    u8 transition; /* 0x7E */
    u8 _pad7F[0xD];
    /* 0x8C */ u8 unk8C;
    u8 _pad8D[0x2];
    /* 0x8F */ u8 unk8F;
} Gap8004CA48Selection;
extern Gap8004CA48Selection lbl_803C6028;
extern u8 lbl_800FDE84[];
typedef struct Gap8004CA48State {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 mode;
    /* 0x4 */ u8 unk4;
    u8 _pad5;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
    /* 0xE */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    u8 _pad16[0x2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 active;
    u8 _pad1D;
    /* 0x1E */ u8 unk1E;
} Gap8004CA48State;
extern Gap8004CA48State lbl_803C5F74;

void fn_8004CA48(s16 a, s16 b, s16 c, s16 d);
void fn_8004CA6C(void);
void fn_8004CC18(void);
void fn_8004CC2C(void);
void fn_8004CC4C(u8 a, u8 b, u8 c, s32 d, s16 e);
void fn_8004CCC0(void);
void fn_8004D0F0(void);
extern u8 lbl_800FE930[][6];
void fn_8004D460(s32 convert, s32 value);
void fn_8004D4F0(void);
void fn_8004D57C(void);
BOOL fn_8004D93C(BOOL special);
void fn_8004D990(void);
void fn_8004DB90(void);
void fn_8004E2EC(void);
typedef struct Gap8004CA48CharInfo {
    u8 unk0;
    /* 0x1 */ u8 id;
    u8 _pad2[0x4];
} Gap8004CA48CharInfo;
extern Gap8004CA48CharInfo lbl_800E8558[54];
extern u8 lbl_800FE5D4[0x350];
void fn_8004E504(s32 convert, s32 a, s32 b, s32 c, s32 d);
void fn_8004E5B4(s8 value, s32 charIndex, s32 enable);
void fn_8004E62C(void);
BOOL fn_8004EE84(s32 kind);
void fn_8004EEF4(void);
void fn_8004F10C(void);
void fn_8004F964(void);
s32 fn_8004FD64(s32 index);
void fn_8004FDA0(s32 value);
void fn_8004FDE8(void);
void fn_80050138(void);

#endif // !__UNKNOWN_gap_8004CA48_H_
