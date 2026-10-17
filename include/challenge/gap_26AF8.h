#ifndef __CHALLENGE_gap_26AF8_H_
#define __CHALLENGE_gap_26AF8_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
#include "challenge/rep_7730.h"

typedef struct Gap26AF8Entry {
    /* 0x0 */ void* data;
    /* 0x4 */ u8 _pad4[0xC];
} Gap26AF8Entry;
extern Gap26AF8Entry lbl_1_data_FB98[];
void fn_80035A00(void);

void fn_1_26AF8(void);

#endif // !__CHALLENGE_gap_26AF8_H_
