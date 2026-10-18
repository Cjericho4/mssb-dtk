#ifndef __UNKNOWN_gap_80064754_H_
#define __UNKNOWN_gap_80064754_H_

#include "mssbTypes.h"
typedef struct Gap80064754Settings { u8 _pad0[0xE]; u8 side; } Gap80064754Settings;
typedef struct Gap80064754Mode { u8 mode; u8 _pad1[2]; u8 option; u8 _pad4[0x24]; } Gap80064754Mode;
extern Gap80064754Settings g_d_GameSettings;
extern Gap80064754Mode lbl_800E8754;
extern u8 lbl_803CB8D0;
s32 randRange_FUN_80042bf0(s32 low, s32 high);

void translateStarPitchHitIndex(void);
void translateStarPitch(void);
void translateStarSwing(void);
void fn_80064918(void);
void fn_8006496C(void);
void fn_800649BC(void);
void unsure_FillRosterPositions(void);
void characterSelectScreen(void);
void fn_80066EAC(void);
void fn_800670A0(void);
void fn_800671FC(void);
void fn_80067264(void);
void fn_800675C4(void);
void fn_800678CC(void);

#endif // !__UNKNOWN_gap_80064754_H_
