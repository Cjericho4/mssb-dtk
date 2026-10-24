#ifndef __UNKNOWN_gap_80064754_H_
#define __UNKNOWN_gap_80064754_H_

#include "mssbTypes.h"
typedef struct Gap80064754Stats { u8 _pad0[0x46F8]; u8 option0, option1; } Gap80064754Stats;
extern Gap80064754Stats lbl_8034E9A0;
typedef struct Gap80064754Settings { u8 _pad0[0x9]; /* 0x9 */ u8 stadium; u8 _padA[4]; u8 side; u8 _padF; u8 mode; u8 _pad11[0x3F]; u8 option50, option51; } Gap80064754Settings;
typedef struct Gap80064754Mode { u8 mode; u8 _pad1[2]; u8 option; u8 _pad4[0x24]; } Gap80064754Mode;
extern Gap80064754Settings g_d_GameSettings;
extern Gap80064754Mode lbl_800E8754;
extern u8 lbl_803CB8D0;
typedef struct Gap80064754Unlocks { u8 _pad0[0xF5]; /* 0xF5 */ u8 unkF5; } Gap80064754Unlocks;
extern Gap80064754Unlocks lbl_80361B20;

s32 translateStarPitchHitIndex(u8 id);
u8 translateStarPitch(u8 id);
u8 translateStarSwing(u8 id);
s32 fn_80064918(s16 id);
void fn_8006496C(void);
void fn_800649BC(void);
void unsure_FillRosterPositions(s32 player);
void characterSelectScreen(s32 player);
s32 randRange(s32 low, s32 high); /* gap_80041348.c; that header clashes here (lbl_80361B20 view) */
void fn_80066EAC(s32 side);
void fn_800670A0(void);
void fn_800671FC(void);
void fn_80067264(void);
void fn_800675C4(void);
void fn_800678CC(s32 player);

#endif // !__UNKNOWN_gap_80064754_H_
