#ifndef __UNKNOWN_gap_80041348_H_
#define __UNKNOWN_gap_80041348_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
typedef struct Gap80041348Allocation Gap80041348Allocation;
extern Gap80041348Allocation* lbl_803CBC48;
extern s32 lbl_803CBC4C;
extern s32 lbl_803CBC50;
Gap80041348Allocation* fn_800ACC6C(s32 heap, u32 size, u32 alignment);
extern u16 lbl_803CBCC0;

/* views used by transferStatsToInMemRoster (other units declare their own views of these objects) */
typedef struct Gap80041348Lineup { u8 _pad0[0xCF46]; /* 0xCF46 */ s8 lineupCursor[2]; } Gap80041348Lineup;
extern Gap80041348Lineup lbl_803297E0;
typedef struct Gap80041348Unlocks { /* 0x0 */ u8 characterFlags[54]; } Gap80041348Unlocks; /* star-player unlock per charID */
extern Gap80041348Unlocks lbl_80361B20;
typedef struct Gap80041348Settings { u8 _pad0[7]; /* 0x7 */ u8 gameMode; u8 _pad8[0x58 - 8]; } Gap80041348Settings; /* 0x58, g_d_GameSettings @0x800E86FC */
extern Gap80041348Settings g_d_GameSettings;
typedef struct Gap80041348SaveState {
    /* 0x0000 */ CharacterStats stats[6][9];   /* Static_Stats_Tables, [charID / 9][charID % 9] */
    u8 _pad21C0[0x4720 - 0x21C0];
    /* 0x4720 */ s32 starToggleCount[2];
    u8 _pad4728[0x489B - 0x4728];
    /* 0x489B */ u8 starFlags[2][9];                   /* [side][slot] star bonus applied */
} Gap80041348SaveState;
extern Gap80041348SaveState lbl_8034E9A0;
extern u8 lbl_802E4B00[2][9];                          /* copy of starFlags for game.rel */
extern u8 lbl_800E86F0[12];                            /* star bonus per ability byte */


void fn_80041348(void);
void fn_8004153C(void);
BOOL fn_8004157C(void);
void fn_800415A0(s16 value);
void fn_800415A8(void);
void capApplicationFunction(void);
void fn_80042598(void);
void transferStatsToInMemRoster(u8 side);
s32 randRange(s32 low, s32 high);
void sndFXRelated(s32 id);

#endif // !__UNKNOWN_gap_80041348_H_
