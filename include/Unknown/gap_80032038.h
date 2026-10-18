#ifndef __UNKNOWN_gap_80032038_H_
#define __UNKNOWN_gap_80032038_H_

#include "mssbTypes.h"
typedef struct Gap80032038Chain { struct Gap80032038Chain* next; } Gap80032038Chain;
extern Gap80032038Chain* lbl_803CBC74;
typedef struct Gap80032038Obj {
    /* 0x00 */ struct Gap80032038Obj* prev;
    /* 0x04 */ struct Gap80032038Obj* next;
    /* 0x08 */ u32 active;
    /* 0x0C */ Gap80032038Chain* chain;
    /* 0x10 */ u8 _pad10[0x4];
    /* 0x14 */ u16 unk14 : 4;
    /* 0x14 */ u16 count : 12;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 flag : 1;
    /* 0x17 */ u8 id : 7;
} Gap80032038Obj;
typedef struct Gap80032038ObjList {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ Gap80032038Obj* next;
} Gap80032038ObjList;
extern Gap80032038ObjList lbl_803CBC84;
extern Gap80032038Obj* lbl_803CBC80;
extern f32 lbl_8017ED68[];
typedef struct Gap80032038SortEntry {
    u32 unk0;
    f32 key;
} Gap80032038SortEntry;
extern f32 lbl_8017FF78[3][4];
extern f32 lbl_8017FFE0[3][4];
void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);
typedef struct Gap80032038Vec { f32 x, y, z; } Gap80032038Vec;
extern Gap80032038Vec lbl_80180010[4];
void PSMTXMultVec(f32 m[3][4], Gap80032038Vec* src, Gap80032038Vec* dst);

s32 fn_80032038(Gap80032038SortEntry* a, Gap80032038SortEntry* b);
void fn_80032064(void);
void fn_80032284(void);
void fn_800324EC(void);
void fn_800328E0(void);
void fn_800330CC(void);
void fn_800332B8(void);
f32 fn_800335BC(s32 angle);
f32 fn_800335EC(s32 angle);
void fn_80033620(void);
void fn_80033794(Gap80032038Chain* head);
Gap80032038Obj* fn_800337CC(Gap80032038Obj* obj, s32 count, BOOL exact);
void pitchingMachinePitching(void);
BOOL fn_80033928(u8 id);
void fn_80033964(Gap80032038Obj* obj);
Gap80032038Obj* fn_800339F0(Gap80032038Obj* obj, u8 id);
void fn_80033A24(void);
void fn_80033B58(void);
void fn_80033CC8(void);
void fn_80033F64(void);
void fn_8003403C(f32 width, f32 height);
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
typedef struct Gap80032038Actor {
    u32 unk0, unk4, unk8;
    f32 matrix[3][4];
    u8 _pad3C[0x18];
    u32 flags;
    u8 _pad58[0x68];
} Gap80032038Actor;
typedef struct Gap80032038ActorRef { Gap80032038Actor* actor; u32 unk4; } Gap80032038ActorRef;
extern Gap80032038Actor lbl_8039C3E0[864];
extern Gap80032038ActorRef lbl_80371C30[864];
extern u8 lbl_803C5F74[0xB4];
void PSMTXIdentity(f32 matrix[3][4]);
void fn_80011140(void);
void fn_800356B8(void);
void fn_80035750(void);
void fn_80035838(void);
void fn_80035A00(void);
void fn_80035B50(void);
void fn_80035CA4(void);

#endif // !__UNKNOWN_gap_80032038_H_
