#ifndef __CHALLENGE_gap_1538_H_
#define __CHALLENGE_gap_1538_H_

#include "mssbTypes.h"

typedef struct Gap1538Entry {
    /* 0x0 */ u8 _pad0[8];
} Gap1538Entry;
extern Gap1538Entry lbl_1_data_298[];
extern u8 lbl_803CBBC0;
void fn_800A7D4C(s32 arg0, Gap1538Entry* entry);
#include "UnknownHeaders.h"
#include "challenge/rep_0010.h"
#include "game/rep_1C0.h"

extern CompressedDiskRead lbl_1_data_0[];

void fn_1_1538(void);
void fn_1_15CC(void);
void fn_1_1634(void);
void fn_1_16A0(void);
void fn_1_1948(void);
void fn_1_196C(void);

#endif // !__CHALLENGE_gap_1538_H_
