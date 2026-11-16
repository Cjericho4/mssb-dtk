#ifndef __UNKNOWN_gap_800A1A70_H_
#define __UNKNOWN_gap_800A1A70_H_

#include "mssbTypes.h"
/* The SDK's GDLObj: a display list being written. */
typedef struct Gap800A1A70Range {
    /* 0x0 */ u8* start;
    /* 0x4 */ u32 length;
    /* 0x8 */ u8* cur;
    /* 0xC */ u8* end;
} Gap800A1A70Range;

void fn_800A1A70(Gap800A1A70Range* range, u8* start, u32 length);
void fn_800A1A88(void);
void fn_800A1B80(void);
void fn_800A1BB0(void);
void fn_800A1E3C(void);
void fn_800A1F40(void);
extern u8 lbl_803CBAA8[8]; /* BP register id per texture map for the image attributes */
void fn_800A2194(u32 texMap, u16 width, u16 height, u32 format);
extern Gap800A1A70Range* lbl_803CC0F0; /* current GD display list (GDLObj) */
extern u8 lbl_803CBAB0[8];             /* BP register id per texture map for the image pointer */
void fn_800A2294(u32 texMap, u32 imageAddress);
extern u8 lbl_803CBAB8[8]; /* BP register id per texture map for the TLUT */
void fn_800A237C(u32 texMap, u32 tlutAddress, u32 format);
void fn_800A246C(void);
void fn_800A26FC(void);

#endif // !__UNKNOWN_gap_800A1A70_H_
