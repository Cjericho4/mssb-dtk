#ifndef __UNKNOWN_gap_80032038_H_
#define __UNKNOWN_gap_80032038_H_

#include "mssbTypes.h"
extern f32 lbl_8017ED68[];
typedef struct Gap80032038SortEntry {
    u32 unk0;
    f32 key;
} Gap80032038SortEntry;
extern f32 lbl_8017FF78[3][4];
extern f32 lbl_8017FFE0[3][4];
void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

s32 fn_80032038(Gap80032038SortEntry* a, Gap80032038SortEntry* b);
void fn_80032064(void);
void fn_80032284(void);
void fn_800324EC(void);
void fn_800328E0(void);
void fn_800330CC(void);
void fn_800332B8(void);
f32 fn_800335BC(s32 angle);
void fn_800335EC(void);
void fn_80033620(void);
void fn_80033794(void);
void fn_800337CC(void);
void pitchingMachinePitching(void);
void fn_80033928(void);
void fn_80033964(void);
void fn_800339F0(void);
void fn_80033A24(void);
void fn_80033B58(void);
void fn_80033CC8(void);
void fn_80033F64(void);
void fn_8003403C(void);
void fn_800340F4(f32 matrix[3][4]);
void fn_80034120(f32 matrix[3][4]);
void fn_8003414C(void);
void minigamesSetSomePointers(void);
void minigamesGXStuff(void);
void minigamesSetSomePointers2(void);
void fn_80034BCC(void);
void fn_80034CEC(void);
void fn_80034E20(void);
void fn_80034F50(void);
void fn_80035168(void);
void fn_800356B8(void);
void fn_80035750(void);
void fn_80035838(void);
void fn_80035A00(void);
void fn_80035B50(void);
void fn_80035CA4(void);

#endif // !__UNKNOWN_gap_80032038_H_
