#ifndef __UNKNOWN_gap_800A1A70_H_
#define __UNKNOWN_gap_800A1A70_H_

#include "mssbTypes.h"
typedef struct Gap800A1A70Range {
    /* 0x0 */ s32 start;
    /* 0x4 */ s32 length;
    /* 0x8 */ s32 cur;
    /* 0xC */ s32 end;
} Gap800A1A70Range;

void fn_800A1A70(Gap800A1A70Range* range, s32 start, s32 length);
void fn_800A1A88(void);
void fn_800A1B80(void);
void fn_800A1BB0(void);
void fn_800A1E3C(void);
void fn_800A1F40(void);
void fn_800A2194(void);
void fn_800A2294(void);
void fn_800A237C(void);
void fn_800A246C(void);
void fn_800A26FC(void);

#endif // !__UNKNOWN_gap_800A1A70_H_
