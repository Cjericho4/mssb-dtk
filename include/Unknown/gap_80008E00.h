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
/* Local views of globals owned by other units. */
typedef struct Gap80008E00Time {
    u32 hi;
    u32 lo;
} Gap80008E00Time;
typedef struct Gap80008E00Clock {
    u8 _pad0[0x50];
    /* 0x50 */ Gap80008E00Time unk50;
} Gap80008E00Clock;
extern Gap80008E00Clock lbl_803C7420;
typedef struct Gap80008E00GameState {
    /* 0x00 */ Gap80008E00Time unk0; /* copy of lbl_803C7420.unk50 taken at boot */
    u8 _pad8[0x1D - 0x8];
    /* 0x1D */ u8 unk1D;
} Gap80008E00GameState;
extern Gap80008E00GameState lbl_80366158;
typedef struct Gap80008E00Task {
    /* 0x00 */ void (*callback)(void);
    u8 _pad4[0x14];
    /* 0x18 */ u16 unk18;
} Gap80008E00Task;
extern Gap80008E00Task* lbl_803CC1B8;
typedef struct Gap80008E00FileName {
    char* path;
    u8 _pad4[0xC];
} Gap80008E00FileName;
extern Gap80008E00FileName lbl_800E8EE8; /* program data file */
extern Gap80008E00FileName lbl_800E8EF8; /* game data file */
s32 ConvertPathToEntryNum(Gap80008E00FileName* name);
extern s32 lbl_803CBBD4; /* entry number of lbl_800E8EE8 */
extern s32 lbl_803CBBD0; /* entry number of lbl_800E8EF8 */
extern char lbl_800E6568[]; /* "s32ProgId=%d\n" */
extern char lbl_800E6578[]; /* "s32DataId=%d\n" */
void OSReport(const char* message, ...);
typedef struct Gap80008E00Config {
    u8 _pad0[5];
    /* 0x5 */ u8 unk5;
    u8 _pad6[0xA];
} Gap80008E00Config; /* at least 0x10 bytes, so not small data */
extern Gap80008E00Config lbl_80110080;
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
