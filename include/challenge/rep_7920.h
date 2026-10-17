#ifndef __CHALLENGE_rep_7920_H_
#define __CHALLENGE_rep_7920_H_

#include "mssbTypes.h"

typedef struct Rep7920Source {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u8 data[4];
} Rep7920Source;

typedef struct Rep7920Entry {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ u8* data;
} Rep7920Entry;
extern Rep7920Entry lbl_1_common_bss_4C6F8[];

typedef struct Rep7920Anim {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 flag80 : 1;
    /* 0x11 */ u8 mode60 : 2;
    /* 0x11 */ u8 mode18 : 2;
    /* 0x11 */ u8 _bits : 3;
    /* 0x12 */ u8 _pad12[2];
    /* 0x14 */ s32 unk14;
} Rep7920Anim;
void fn_1_26B7C(Rep7920Anim* anim);
Rep7920Entry* fn_1_26BFC(Rep7920Source* src, s32 index);
void fn_1_26C2C(void);

#endif // !__CHALLENGE_rep_7920_H_
