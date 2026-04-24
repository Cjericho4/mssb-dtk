#ifndef __GAME_gap_6C854_H_
#define __GAME_gap_6C854_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_720.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    u8 a;
    u8 b;
} DataPair_60E4;

extern DataPair_60E4 lbl_3_data_60E4[6];
extern void fn_800A97EC(s32 arg0, u8 arg1, u8 arg2);

extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

// fn_3_6C854 declared in UnknownHomes_Game.h
s32 fn_3_6C938(s32 arg0, s32 arg1);
void fn_3_6CC30(void);

#endif // !__GAME_gap_6C854_H_
