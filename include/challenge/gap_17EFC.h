#ifndef __CHALLENGE_gap_17EFC_H_
#define __CHALLENGE_gap_17EFC_H_

#include "mssbTypes.h"

typedef struct Gap17EFCEntry {
    /* 0x0 */ u8 _pad0[4];
    /* 0x4 */ f32 sortKey;
} Gap17EFCEntry;

s32 fn_1_17EFC(Gap17EFCEntry* a, Gap17EFCEntry* b);
void fn_1_17F28(void);
void fn_1_17FF0(void);
void fn_1_18174(void);

#endif // !__CHALLENGE_gap_17EFC_H_
