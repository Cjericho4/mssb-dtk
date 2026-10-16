#ifndef __GAME_rep_1C0_H_
#define __GAME_rep_1C0_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct FanObject FanObject;
/* Per-view draw callback, called with the view matrix. */
typedef void (*ViewDrawCallback)(Mtx viewMtx, s32 arg1, s32 arg2);

/* Table of self-relative offsets that are converted to pointers in place. */
typedef struct RelocTable {
    u16 count; /* index of the last entry */
    u8 _pad2[0x2];
    u32 entries[1]; /* 0x4 */
} RelocTable;

typedef struct Fn3_5BCCArg {
    u8 _pad[0x8];
    s32 viewIdx;
} Fn3_5BCCArg;

extern u8 lbl_803CBBC0;
extern f32 lbl_3_rodata_520;
extern f32 lbl_3_rodata_538;
void SetFog(u8 type, u32* color, f32 startZ, f32 endZ, f32 nearScale, f32 farScale);
extern ViewDrawCallback lbl_3_data_A10[2];
extern void fn_80052694(s32 viewIdx);
extern s32 fn_800527BC(void);

typedef struct _CompressedDiskRead {
    u32 OriginalSize_CompressedFlagInTopBits_;
    u32 diskLocation;
    u32 compressedSize;
    u32 padding;
} CompressedDiskRead;

void* ARAMTransfer(CompressedDiskRead *compressedStruct, void *readDestination, u8 loadInfo, void *aramAddress);

struct FanObject* setFanObjPtr(void);
void fn_3_35E4(struct FanObject* arg0);
void fn_3_35F0(void);
void fn_3_64DC(void);
void fn_3_38E8(ViewDrawCallback arg0);
void fn_3_3818(void);
s16 fn_3_6424(RelocTable* table, u32** outEntries);
void fn_3_3904(void);
void fn_3_3BE8(void);
void fn_3_3EE8(void);
void fn_3_42CC(void);
void fn_3_4984(void);
void fn_3_4A38(void);
void fn_3_4F90(void);
void fn_3_53E0(u16* code, s16* x, s16* y, s16* w, s16* h, s16* page);
void fn_3_5518(void);
void fn_3_567C(void);
void fn_3_5BAC(void);
void fn_3_5BCC(struct Fn3_5BCCArg* arg0);
void fn_3_5BF0(void);
void fn_3_5C68(void);
void fn_3_5E60(void);

#endif // !__GAME_rep_1C0_H_
