#ifndef __GAME_gap_15C5F4_H_
#define __GAME_gap_15C5F4_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "UnknownHeaders.h"

#include "game/rep_3448.h"

extern s32 lbl_3_data_273E0;
extern u8 lbl_3_data_27C54[];

typedef struct {
    u8 _pad0[0x104];
    u8 unk104;          // 0x104
    u8 _pad105[0x108 - 0x105];
} SomeScoreStruct; // size: 0x108
extern SomeScoreStruct lbl_80353A90;

void fn_3_15C5F4(void);
void fn_3_15C638(void);
void fn_3_15C6E4(void);
void fn_3_15D1D8(void);
void fn_3_15DB44(void);
void fn_3_15EE2C(void);
void fn_3_15F088(void);
void fn_3_15F220(void);
void fn_3_15F380(void);
void fn_3_15F3C4(void);
void fn_3_15F410(void);

#endif // !__GAME_gap_15C5F4_H_
