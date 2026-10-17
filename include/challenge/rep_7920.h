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

void fn_1_26B7C(void);
Rep7920Entry* fn_1_26BFC(Rep7920Source* src, s32 index);
void fn_1_26C2C(void);

#endif // !__CHALLENGE_rep_7920_H_
