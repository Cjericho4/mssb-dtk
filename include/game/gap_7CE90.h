#ifndef __GAME_gap_7CE90_H_
#define __GAME_gap_7CE90_H_

#include "mssbTypes.h"
#include "game/rep_720.h"

typedef struct ReplayInput {
    /* 0x0 */ s16 controlStickAngle;
    /* 0x2 */ u16 buttonInput;
    /* 0x4 */ u16 newButtonInput;
    /* 0x6 */ s8 right_left;
    /* 0x7 */ s8 up_down;
} ReplayInput; // size: 0x8

typedef struct ReplayFrame {
    ReplayInput inputs[2];
} ReplayFrame; // size: 0x10

extern ReplayFrame g_ReplayLogic[1200];

void fn_3_7CE90(void);
void fn_3_7CF88(void);
void fn_3_7D2E0(void);
void fn_3_7D39C(void);
void fn_3_7D458(void);
void fn_3_7D780(void);

#endif // !__GAME_gap_7CE90_H_
