#ifndef __UNKNOWN_gap_80062578_H_
#define __UNKNOWN_gap_80062578_H_

#include "mssbTypes.h"
typedef struct Gap80062578Flags {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    u8 _pad6[0x7];
    /* 0xD */ u8 unkD;
} Gap80062578Flags;
extern Gap80062578Flags lbl_803C6714;
typedef struct Gap80062578Words {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
} Gap80062578Words;
extern Gap80062578Words lbl_803C663C;
typedef struct Gap80062578Stats {
    u8 _pad0[0x48B3];
    /* 0x48B3 */ u8 unk48B3;
} Gap80062578Stats;
extern Gap80062578Stats lbl_8034E9A0;
typedef struct Gap80062578Scene {
    u8 _pad0[0x94];
    void (*callback)(void); /* 0x94 */
} Gap80062578Scene;

void fn_80062578(void);
void fn_800625A4(void);
void fn_80062674(void);
void fn_800626EC(void);
void fn_80062744(void);
void fn_80062764(void);
void fn_80062794(void);
void fn_800627C4(void);
void fn_800627F8(void);
void fn_8006282C(void);
void fn_8006285C(void);
void fn_80062890(void);
void fn_800628D4(void);
void fn_80062948(void);
void fn_8006295C(void);
void initializeUnknown(void);
void fn_80062A74(void);
void fn_80062A94(void);
void fn_80062BE4(void);
void fn_80062C24(void);
void fn_80062C60(void);
void fn_80062D94(void);
void fn_80062E6C(void);
void fn_80062ED4(void);
void fn_80062F38(void);
s32 fn_80063010(s32 arg0, Gap80062578Scene** scene);
void fn_80063028(void);
void fn_800633AC(void);
void fn_80063718(void);
s32 fn_800637BC(s32 arg0, Gap80062578Scene** scene);
s32 fn_800637D4(void);
void fn_800637DC(void);
s32 fn_800638B4(s32 arg0, Gap80062578Scene** scene);
void fn_800638CC(void);
void fn_80063958(void);
void fn_800639BC(void);
void fn_80064344(void);
void fn_80064430(void);
void fn_80064534(void);

#endif // !__UNKNOWN_gap_80062578_H_
