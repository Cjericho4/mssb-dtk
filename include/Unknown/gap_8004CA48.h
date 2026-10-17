#ifndef __UNKNOWN_gap_8004CA48_H_
#define __UNKNOWN_gap_8004CA48_H_

#include "mssbTypes.h"
typedef struct Gap8004CA48State {
    u8 _pad0[0x3];
    /* 0x3 */ u8 mode;
    u8 _pad4[0xA];
    /* 0xE */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    u8 _pad16[0x6];
    /* 0x1C */ u8 active;
} Gap8004CA48State;
extern Gap8004CA48State lbl_803C5F74;

void fn_8004CA48(s16 a, s16 b, s16 c, s16 d);
void fn_8004CA6C(void);
void fn_8004CC18(void);
void fn_8004CC2C(void);
void fn_8004CC4C(void);
void fn_8004CCC0(void);
void fn_8004D0F0(void);
void fn_8004D460(void);
void fn_8004D4F0(void);
void fn_8004D57C(void);
void fn_8004D93C(void);
void fn_8004D990(void);
void fn_8004DB90(void);
void fn_8004E2EC(void);
void fn_8004E504(void);
void fn_8004E5B4(void);
void fn_8004E62C(void);
void fn_8004EE84(void);
void fn_8004EEF4(void);
void fn_8004F10C(void);
void fn_8004F964(void);
void fn_8004FD64(void);
void fn_8004FDA0(void);
void fn_8004FDE8(void);
void fn_80050138(void);

#endif // !__UNKNOWN_gap_8004CA48_H_
