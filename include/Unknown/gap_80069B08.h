#ifndef __UNKNOWN_gap_80069B08_H_
#define __UNKNOWN_gap_80069B08_H_

#include "mssbTypes.h"
typedef struct Gap80069B08RenderMode Gap80069B08RenderMode;
extern Gap80069B08RenderMode lbl_80109250;
extern Gap80069B08RenderMode lbl_8010928C;
extern Gap80069B08RenderMode* lbl_803CBD34;
void VIConfigure(Gap80069B08RenderMode* mode);
void VIFlush(void);
void VIWaitForRetrace(void);
typedef void (*Gap80069B08Callback)(s32 a, s32 b, s32 c);
typedef struct Gap80069B08Game { u8 _pad0[0x28]; u8 mode; u8 _pad29; u8 unk2A; } Gap80069B08Game;
extern Gap80069B08Game lbl_80366158;
typedef struct Gap80069B08Queue {
    /* 0x00 */ void (*callback)(void);
    u8 _pad4[0xE];
    /* 0x12 */ u16 priority;
    /* 0x14 */ u16 slot;
    u8 _pad16[0x25];
    u8 active;
} Gap80069B08Queue;
extern Gap80069B08Queue* lbl_803CC1B8;
void fn_800B0A14_removeQueue(void);
void fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
typedef struct Gap80069B08Mission {
    u8 _pad0[0x31];
    /* 0x31 */ s8 state;
    u8 _pad32[0x2];
} Gap80069B08Mission;
typedef struct Gap80069B08Tracker {
    Gap80069B08Mission missions[335];
    u8 _pad440C[9];
    u8 row; /* 0x4415 */
    u8 _pad4416[0xC];
    u8 column; /* 0x4422 */
    u8 _pad4423[0xE5];
} Gap80069B08Tracker;
extern Gap80069B08Tracker starMissionCompletionTracker;
extern f32 lbl_8010B590[][7];

extern Gap80069B08Callback lbl_803CBD38;
extern Gap80069B08Callback lbl_803CBD3C;

typedef struct Gap80069B08SlotObj {
    u8 _pad0[0x54];
    /* 0x54 */ u32 flags;
    u8 _pad58[0x4];
    /* 0x5C */ u32 unk5C;
} Gap80069B08SlotObj;
typedef struct Gap80069B08Slot {
    /* 0x0 */ Gap80069B08SlotObj* obj;
    u8 _pad4[0x4];
} Gap80069B08Slot;
extern Gap80069B08Slot lbl_80371C30[];
void fn_80069AD4(void);
void fn_80069B08(void);
void fn_80069B68(void);
void fn_80069BDC(void);
void fn_8006A194(void);
void fn_8006A500(void);
void fn_8006A824(void);
void fn_8006AC24(void);
void fn_8006AF6C(void);
void fn_8006AF9C(void);
void fn_8006B230(void);
void fn_8006B668(void);
void fn_8006B78C(void);
void fn_8006BB60(void);
void fn_8006BE00(void);
void fn_8006C088(BOOL alternate);
void fn_8006C0D0(void);
extern s16 lbl_80109400[8];
u8 fn_8006C100(s16 value);
void fn_8006C13C(void);
s16 fn_8006C268(s16* values);
void fn_8006C2B4(void);
typedef struct Gap80069B08Lineup {
    u8 _pad0[0xC];
    /* 0x0C */ u8 order[6];
    /* 0x12 */ u8 unk12;
    u8 _pad13[0x3];
} Gap80069B08Lineup;
void* memset(void* dst, int value, unsigned long count);
void fn_8006C398(Gap80069B08Lineup* lineup);
void fn_8006C3F0(Gap80069B08Callback value);
void fn_8006C3F8(s32 a, s32 b, s32 c);
void fn_8006C43C(Gap80069B08Callback value);
void fn_8006C444(s32 a, s32 b, s32 c);
void fn_8006C488(void);
void challengeDrawStarsOnMissionMenu(void);
void fn_8006C5CC(void);
void fn_8006C6C4(void);
BOOL fn_8006C79C(s32 index);
void starMissionRelated2(void);
void fn_8006C9D8(void);
f32 fn_8006CA9C(void);
void starMissionMenu(void);
void challengeRelated(void);
void determineIfMissionDescriptionIsShown(void);
void fn_8006CDC0(void);
void fn_8006CEBC(void);
void fn_8006CF6C(void);

#endif // !__UNKNOWN_gap_80069B08_H_
