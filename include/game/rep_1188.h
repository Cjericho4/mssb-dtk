#ifndef __GAME_rep_1188_H_
#define __GAME_rep_1188_H_

#include "mssbTypes.h"

extern u8 aILevel[4];

void fn_3_6D6D4(s32 runnerIndex);
void fn_3_6D964(s32 rosterIdx, s32 runnerIdx);
void setInMemBatterConstants(int rosterID);
u8 fn_3_6E1D4(u8 arg0);
u32 LERPToNewRange_Float(u8 current, s32 minVal, s32 maxVal, u8 minMapped, u8 maxMapped);
void setFielderValues(s32 rosterID, s32 fielderIndex);  //This is important to find character struct
void fn_3_6EBB4(s32 arg0);
void fn_3_6EF1C(void);

#endif // !__GAME_rep_1188_H_
