#ifndef __UNKNOWN_gap_80069B08_H_
#define __UNKNOWN_gap_80069B08_H_

#include "mssbTypes.h"
typedef struct Gap80069B08Queue {
    u8 _pad0[0x12];
    u16 priority;
    u8 _pad14[0x27];
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

extern s32 lbl_803CBD38;
extern s32 lbl_803CBD3C;

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
void fn_8006C088(void);
void fn_8006C0D0(void);
void fn_8006C100(void);
void fn_8006C13C(void);
void fn_8006C268(void);
void fn_8006C2B4(void);
void fn_8006C398(void);
void fn_8006C3F0(s32 value);
void fn_8006C3F8(void);
void fn_8006C43C(s32 value);
void fn_8006C444(void);
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
