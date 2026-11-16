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
typedef struct Gap80069B08Script Gap80069B08Script;
Gap80069B08Queue* fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
typedef struct Gap80069B08ScoutFlags {
    u8 _pad0[0x4];
    /* 0x04 */ s8 flags[4][6]; /* [difficulty][challengeCaptain] */
} Gap80069B08ScoutFlags;
/* Local view of ChallengeTrackingStruct / ChallengeSaveData (UnknownHomes_Game.h). The two
   headers declare starMissionCompletionTracker with different types, so this unit cannot
   include the owning one yet; missions[335] spans the 54 per-character records and the
   0x0AF8..0x440C area in one array. */
typedef struct Gap80069B08Mission {
    /* 0x00 */ Gap80069B08ScoutFlags* scoutFlags;
    /* 0x04 */ u8 challengeCaptain;
    /* 0x05 */ s8 variantClassification;
    /* 0x06 */ u8 scoutFlagsAchieved;
    u8 _pad7[0x31 - 0x7];
    /* 0x31 */ s8 state; /* 1 = recruited */
    u8 _pad32[0x2];
} Gap80069B08Mission;
typedef struct Gap80069B08Tracker {
    Gap80069B08Mission missions[335];
    u8 _pad440C[9];
    u8 row; /* 0x4415 challenge difficulty */
    u8 _pad4416[0x6];
    /* 0x441C */ u8 challengeCaptain;
    u8 _pad441D;
    /* 0x441E */ u8 opponentCaptain;
    /* 0x441F */ u8 opponentCaptainCharID;
    u8 _pad4420[0x2];
    u8 column; /* 0x4422 */
    u8 _pad4423[0x444D - 0x4423];
    /* 0x444D */ u8 newlyRecruited[NUM_CHOOSABLE_CHARACTERS]; /* set with state = 1 by fn_8006C9D8 */
    u8 _pad4483[0x4508 - 0x4483];
} Gap80069B08Tracker;
STATIC_ASSERT(sizeof(Gap80069B08Tracker) == 0x4508);
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
extern char lbl_801092E8[0x10];
extern Gap80069B08Script lbl_80109378;
extern Gap80069B08Queue* lbl_803CBD30;
BOOL fn_80035838(char* name, s32 id);
void fn_80034E20(Gap80069B08Queue* scene, Gap80069B08Script* script);
BOOL fn_80069B68(void);
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
/* View of lbl_800E8558 (characterStaticIndexes, character_select.md section 1). */
typedef struct Gap80069B08CharIndex {
    u8 family;
    u8 baseCharID;
    u8 uniqueIdx;
    /* 0x3 */ u8 isBase;
    u8 isCaptain;
    u8 colourIdx;
} Gap80069B08CharIndex;
extern Gap80069B08CharIndex lbl_800E8558[NUM_CHOOSABLE_CHARACTERS];
extern s16 lbl_8010B444[][11]; /* [variant classification][stars earned 0..10] */
BOOL challengeStarRelatedInd(s32 charID, s32 mission);
s32 challengeRelated(s32 charID);
void determineIfMissionDescriptionIsShown(void);
void fn_8006CDC0(void);
typedef struct Gap80069B08Audio {
    u8 _pad0[0xCF69];
    /* 0xCF69 */ u8 unkCF69;
    /* 0xCF6A */ u8 unkCF6A;
    /* 0xCF6B */ u8 pending;
    /* 0xCF6C */ u8 handles[4];
    u8 _padCF70[0x17D28];
} Gap80069B08Audio;
extern Gap80069B08Audio lbl_803297E0;
void fn_8000FEE8(u8 handle);
void fn_8000F8F4(Gap80069B08Queue* queue);
void fn_80034CEC(Gap80069B08Queue* queue);
void fn_8006CEBC(void);
typedef struct Gap80069B08Sound {
    u8 _pad0[0x2F];
    /* 0x2F */ u8 active;
    u8 _pad30[0x8];
} Gap80069B08Sound;
extern Gap80069B08Sound lbl_80366B18[];
extern Gap80069B08Script lbl_801075A8;
u8 fn_8000F988(Gap80069B08Queue* queue, s32 id, s32 a, s32 b, s32 sound, s32 c);
void fn_8006CF6C(void);

#endif // !__UNKNOWN_gap_80069B08_H_
