#ifndef __UNKNOWN_gap_800A97D0_H_
#define __UNKNOWN_gap_800A97D0_H_

#include "mssbTypes.h"
typedef struct Gap800A97D0Pad {
    u8 _pad0[9];
    u8 pending;
    u8 command;
    u8 value;
    u8 _padC[0x14];
} Gap800A97D0Pad;
extern Gap800A97D0Pad lbl_803C77B8[4];
extern u16 lbl_800E7800[256];
typedef struct Gap800A97D0Flags {
    u8 _pad0[0x55];
    /* 0x55 */ u8 unk55;
} Gap800A97D0Flags;
extern Gap800A97D0Flags lbl_803C7838;
typedef struct Gap800A97D0Pan {
    u8 _pad0[6];
    u8 disabledPads;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ s8 unk8;
    /* 0x9 */ s8 unk9;
} Gap800A97D0Pan;
extern Gap800A97D0Pan lbl_80110080;
typedef struct Gap800A97D0Heap {
    /* 0x0 */ s32 size;
    /* 0x4 */ s32 start;
    /* 0x8 */ s32 end;
} Gap800A97D0Heap;
extern Gap800A97D0Heap lbl_803C7898;
typedef struct Gap800A97D0Block {
    /* 0x0 */ s32 addr;
    /* 0x4 */ s32 size;
} Gap800A97D0Block;
void CARDInit(void);
void PADInit(void);
void SISetSamplingRate(u32 msec);

void fn_800A97D0(u8 a, s8 b);
void fn_800A97EC(s32 index, u32 command, u8 value);
void fn_800A983C(void);
void fn_800A9864(void);
void fn_800A98FC(void);
void fn_800A9CF8(void);
void fn_800A9E34(void);
void fn_800A9ECC(void);
void fn_800AA34C(void);
void fn_800AA44C(void);
void fn_800AA930(void);
void fn_800AAA70(void);
void fn_800AAEE4(void);
void fn_800AAFEC(void);
void fn_800AB474(void);
void fn_800AB534(void);
u16 fn_800ABB14(u8* data, s32 count);
void fn_800ABB60(void);
void fn_800ABBD0(void);
void fn_800ABF44(void);
void fn_800AC508(void);
void fn_800ACC6C(void);
void fn_800ACCD4(void);
void fn_800ACCE8(void);
void fn_800ACD44(void);
void fn_800ACD64(void);
void fn_800ACF14(Gap800A97D0Block* block);
void fn_800ACF34(void);
void fn_800ACF78(void);
void fn_800ACFB0(Gap800A97D0Block* block);
void _OSAllocFromHeap(void);
void fn_800AD01C(s32 end);
void fn_800AD038(s32 start);
void fn_800AD054(s32 start, s32 end);
void fn_800AD070(void);
void fn_800AD490(void);
void fn_800AD500(void);
void fn_800AD6BC(void);

#endif // !__UNKNOWN_gap_800A97D0_H_
