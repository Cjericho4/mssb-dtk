#ifndef __UNKNOWN_gap_800528AC_H_
#define __UNKNOWN_gap_800528AC_H_

#include "mssbTypes.h"

extern s32 lbl_803CBD10;

void fn_800528AC(s32 value);
void fn_800528B4(void);
typedef struct Gap800528ACVec {
    f32 x;
    f32 y;
    f32 z;
} Gap800528ACVec;
typedef struct Gap800528ACCamera {
    /* 0x00 */ f32 projection[4][4];
    /* 0x40 */ f32 view[3][4];
    u8 _pad70[0x38];
} Gap800528ACCamera;
extern Gap800528ACCamera lbl_803C639C[4];
void PSMTXMultVec(f32 matrix[3][4], Gap800528ACVec* src, Gap800528ACVec* dst);
void PSMTX44MultVec(f32 matrix[4][4], Gap800528ACVec* src, Gap800528ACVec* dst);
void fn_800528C0(s16* screenX, s16* screenY, f32 x, f32 y, f32 z);
void fn_80052968(void);
void fn_80052D70(void);
void possiblyTransitionBlackScreen(void);
void fn_800531D0(void);
void fn_80053810(void);
void fn_80053FE8(void);
void fn_800542C4(void);
void fn_80054910(void);
void fn_80054B00(void);
void fn_80055374(void);
void fn_80055798(void);
void fn_800559EC(void);
void fn_80056120(void);
void fn_800569C8(void);
void drawStarProgressionMenu(void);
void someChallengeStarFunction(void);
void someChallengeStarFunction2(void);
void challengeCheckStarsMenuLoading(void);
/* Local views: the queue task, the scene object table, the scene script and the in-memory
   roster are owned by other headers this unit does not include. */
typedef struct Gap800528ACTask {
    /* 0x00 */ void (*callback)(void);
    u8 _pad4[0x10];
    /* 0x14 */ u16 index;
} Gap800528ACTask;
extern Gap800528ACTask* lbl_803CC1B8;
typedef struct Gap800528ACObject {
    u8 _pad0[0x5C];
    /* 0x5C */ u32 unk5C;
} Gap800528ACObject;
typedef struct Gap800528ACObjectRef {
    Gap800528ACObject* object;
    u32 unk4;
} Gap800528ACObjectRef;
extern Gap800528ACObjectRef lbl_80371C30[];
typedef struct Gap800528ACScript Gap800528ACScript;
extern Gap800528ACScript lbl_80108048;
typedef struct Gap800528ACRosterEntry {
    u8 _pad0[0x24];
    /* 0x24 */ s16 charID; /* stats.CharID */
    u8 _pad26[0xA0 - 0x26];
} Gap800528ACRosterEntry;
extern Gap800528ACRosterEntry inMemRoster[2][9];
void fn_80034E20(Gap800528ACTask* scene, Gap800528ACScript* script);
/* gap_80035DD4 owns this; arguments from starMenu's call. */
void fn_800363D8(Gap800528ACTask* scene, s32 id, s32 a, s32 b, s32 value);
void starMenu(void);
void fn_80057CAC(void);
void fn_80058050(void);
void fn_80058394(void);
void fn_80058644(void);
void fn_80058B20(void);
void fn_80058E0C(void);
void fn_80059458(void);
void fn_800596D4(void);
void starMissionRelated1(void);
void fn_8005A350(void);
void fn_8005AF68(void);
void fn_8005B298(void);
void fn_8005B760(void);
void fn_8005BB5C(void);
void fn_8005BF40(void);
void fn_8005C2B0(void);
void fn_8005C5C4(void);
void fn_8005C830(void);
void fn_8005CCE4(void);
void fn_8005DE14(void);
void fn_8005E9D8(void);
void fn_8005EC88(void);
void fn_8005F068(void);
void fn_8005F734(void);
void fn_8005F9D0(void);
void fn_8005FCA0(void);
void fn_80060184(void);
void fn_80061B9C(void);
void SetMenuNumber(void);

#endif // !__UNKNOWN_gap_800528AC_H_
