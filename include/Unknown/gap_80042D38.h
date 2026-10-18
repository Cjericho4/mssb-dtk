#ifndef __UNKNOWN_gap_80042D38_H_
#define __UNKNOWN_gap_80042D38_H_

#include "mssbTypes.h"
typedef struct Gap80042D38Task {
    u8 _pad0[0x14];
    u16 baseIndex;
} Gap80042D38Task;
typedef struct Gap80042D38Entry {
    u8 _pad0[0x5C];
    u32 time;
    u8 _pad60[8];
    u8 active;
} Gap80042D38Entry;
typedef struct Gap80042D38Slot {
    Gap80042D38Entry* entry;
    u32 unk4;
} Gap80042D38Slot;
extern Gap80042D38Slot lbl_80371C30[];
typedef struct Gap80042D38Pause {
    u8 _pad0[0xCF38];
    /* 0xCF38 */ s16 selection;
    /* 0xCF3A */ s8 team;
    /* 0xCF3B */ u8 player;
    u8 _padCF3C[6];
    /* 0xCF42 */ u8 unkCF42;
} Gap80042D38Pause;
extern Gap80042D38Pause lbl_803297E0;
typedef struct Gap80042D38Settings { u8 _pad0[6]; /* 0x6 */ u8 mode; u8 _pad7[0x51]; } Gap80042D38Settings;
extern Gap80042D38Settings g_d_GameSettings;
void fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
typedef struct Gap80042D38State {
    u16 unk0;
    u16 current;
    u16 timer;
    u16 previous;
    u16 previousTimer;
} Gap80042D38State;
extern Gap80042D38State* lbl_803CBBCC;

void fn_80042D38(u16 state);
BOOL fn_80042D68(Gap80042D38Task* task, s32 index, s32 time);
BOOL fn_80042DA8(Gap80042D38Task* task, s32 index, s32 time);
void challengeStarMenu(void);
void starMenuCursor(void);
void fn_80043880(void);
void fn_80044C98(void);
void fn_8004617C(void);
void fn_800471F4(void);
void fn_80047CE0(void);
void pauseMenuSelection(void);
void fn_800486E0(s32 priority, s8 team, u8 player);
void fn_80048764(void);
void fn_80048820(void);

#endif // !__UNKNOWN_gap_80042D38_H_
