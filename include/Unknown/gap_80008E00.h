#ifndef __UNKNOWN_gap_80008E00_H_
#define __UNKNOWN_gap_80008E00_H_

#include "mssbTypes.h"
extern u8 lbl_803CBBC2[2];
BOOL OSGetResetButtonState(void);
void fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
extern s32 lbl_803CBBBC;
typedef struct Gap80008E00State {
    u8 _pad0[0x88];
    /* 0x88 */ s32 unk88;
} Gap80008E00State;
extern Gap80008E00State lbl_80366188;
void fn_80035168(void);

extern s32 lbl_803CBBAC;
extern s32 lbl_803CBBB8;
extern s32 lbl_803CBBA0;
extern u8 lbl_803CBBA4;
typedef struct Gap80008E00Load {
    u8 _pad0[0x722];
    /* 0x722 */ s8 unk722;
} Gap80008E00Load;
extern Gap80008E00Load lbl_803C6CF8;

void fn_80008E00(s32 value);
void fn_80008E08(void);
void PostRetraceCallback(void);
void fn_8000900C(void);
s32 fn_80009018(s32 value);
u8 fn_80009028(void);
void fn_8001D2D4(void);
void fn_80009094(void);
void fn_800090B4(void);
void fn_80009144(void);
void main(void);
void PrepFilesToBeLoaded(void);
void fn_800097A0(void);
void interpolatePointsUnknown(void);
void BezierInterpolate(void);
s32 fn_8000A094(s32 value);
void fn_8000A0AC(void);
void interpolatePointsBezier_Vec2s(void);
void fn_8000A3EC(void);
void fn_8000AF1C(void);

#endif // !__UNKNOWN_gap_80008E00_H_
