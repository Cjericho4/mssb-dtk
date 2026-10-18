#ifndef __UNKNOWN_gap_80062578_H_
#define __UNKNOWN_gap_80062578_H_

#include "mssbTypes.h"
typedef struct Gap80062578Settings { u8 _pad0[0x10]; u8 mode; } Gap80062578Settings;
extern Gap80062578Settings g_d_GameSettings;
extern u16 lbl_80108E38[];
extern u8 lbl_80108B3C[];
u32 sndFXStartEx(u16 effect, u8 volume, u8 pan, u32 studio);
typedef struct Gap80062578GameState {
    u8 _pad0[0x28];
    u8 mode;
} Gap80062578GameState;
extern Gap80062578GameState lbl_80366158;
typedef struct Gap80062578Object Gap80062578Object;
void fn_80032284(Gap80062578Object* obj);
typedef struct Gap80062578Setup { s32 value; u32 unk4; u32 unk8; } Gap80062578Setup;
extern Gap80062578Setup lbl_80108B90;
extern s32 lbl_803CBD0C;
void fn_80032064(Gap80062578Object* obj, Gap80062578Setup* setup);
typedef struct Gap80062578Request {
    u32 unk0;
    u32 unk4;
    s32 value; /* 0x8 */
} Gap80062578Request;
extern Gap80062578Request lbl_80108B84;
void fn_800215F8(Gap80062578Request* request);
u32 sndFXCheck(u32 handle);
typedef struct Gap80062578Sound {
    u8 _pad0[0x14];
    u32 sound14;
    u8 _pad18[0x80];
    u32 sound98;
    u32 sound9C;
} Gap80062578Sound;
extern Gap80062578Sound lbl_800EF808;
void fn_80021518(s32 id, u32 sound);
typedef struct Gap80062578Status {
    u8 _pad0[0x55];
    u8 flags[8];
    u8 busy[2]; /* 0x5D */
} Gap80062578Status;
extern Gap80062578Status lbl_803C66B0;
typedef struct Gap80062578Flags {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    u8 _pad6[0x7];
    /* 0xD */ u8 unkD;
} Gap80062578Flags;
extern Gap80062578Flags lbl_803C6714;
typedef union Gap80062578Words {
    struct { s32 unk0, unk4, unk8, unkC; };
    s32 values[4];
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

BOOL fn_80062578(void);
void fn_800625A4(void);
void fn_80062674(s32 index);
void fn_800626EC(s32 index);
void fn_80062744(void);
void fn_80062764(s32 value);
BOOL fn_80062794(u32 handle);
s32 fn_800627C4(void);
s32 fn_800627F8(void);
void fn_8006282C(void);
s32 fn_8006285C(void);
u32 fn_80062890(s32 index);
void fn_800628D4(void);
void fn_80062948(void);
void fn_8006295C(void);
void initializeUnknown(void);
void fn_80062A74(void);
void fn_80062A94(void);
void fn_80062BE4(Gap80062578Object* obj);
void fn_80062C24(Gap80062578Object* obj);
void fn_80062C60(void);
void fn_80062D94(void);
typedef struct Gap80062578Actor {
    u8 _pad0[0x252];
    /* 0x252 */ s8 unk252;
} Gap80062578Actor;
extern s8 lbl_80108BF0[5][0x36];
void fn_8004B1C0(s32 index, Gap80062578Actor* actor, s32 a, s32 b);
void fn_80062E6C(Gap80062578Actor* actor, s32 a, s32 b);
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
typedef struct Gap80062578Slot {
    /* 0x00 */ u8 unk0[0xC];
    /* 0x0C */ u8 unkC[0xC];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 unk1C;
    u8 _pad1D[0x3];
} Gap80062578Slot;
typedef struct Gap80062578SlotTable {
    Gap80062578Slot slots[9];
    u8 _pad120[0x8];
} Gap80062578SlotTable;
extern Gap80062578SlotTable lbl_802E4BC0;
u8* memset(u8* memory, s32 value, u32 size);
void fn_80063958(s8 index);
void fn_800639BC(void);
void fn_80064344(void);
void fn_80064430(void);
void fn_80064534(void);

#endif // !__UNKNOWN_gap_80062578_H_
