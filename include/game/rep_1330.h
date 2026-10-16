#ifndef __GAME_rep_1330_H_
#define __GAME_rep_1330_H_

#include "mssbTypes.h"

/* One saved game-state snapshot inside g_ReplayCopies. */
typedef struct ReplayCopy {
    /* 0x0000 */ u8 gameLogic[0x158];
    /* 0x0158 */ u8 strikes[0x24];
    /* 0x017C */ u8 scores[0xC8];
    /* 0x0244 */ u8 ball[0x1BF8];
    /* 0x1E3C */ u8 pitcher[0x178];
    /* 0x1FB4 */ u8 batter[0xB0];
    /* 0x2064 */ u8 aiLogic[0xBC];
    /* 0x2120 */ u8 fieldingLogic[0x150];
    /* 0x2270 */ u8 runningLogic[0x20];
    /* 0x2290 */ u8 fielders[0x15A8];
    /* 0x3838 */ u8 runners[0x550];
    /* 0x3D88 */ u8 bss32234[0x6];
    /* 0x3D8E */ u8 bss32230[0x4];
    /* 0x3D92 */ u8 bss32220[0xE];
    /* 0x3DA0 */ u8 throwing31ACC[0x14];
    /* 0x3DB4 */ u8 animation31EAC[0x2F4];
    /* 0x40A8 */ u8 bss321A0[0x80];
    /* 0x4128 */ u8 batterStats[0x2AC];
    /* 0x43D4 */ u8 pitcherStats[0x21C];
} ReplayCopy;
extern ReplayCopy g_ReplayCopies;

void fn_3_7C4E4(void);
void fn_3_7C7AC(void);

#endif // !__GAME_rep_1330_H_
