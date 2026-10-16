#ifndef __GAME_rep_3880_H_
#define __GAME_rep_3880_H_

#include "mssbTypes.h"
#include "stl/mem.h"
#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"

// Linked list node used by fn_3_14B9F0
typedef struct ListNode_14B9F0 {
    struct ListNode_14B9F0* next;  // 0x00
    Vec offset;                     // 0x04
    union {
        Vec velocity;               // 0x10
        struct {
            u8 _pad10[0x8];
            s16 field_0x18;         // 0x18
            u8 _pad1A[0x2];         // 0x1A
        };
    };
    union {
        VecXYZ pos;                 // 0x1C
        Vec posVec;                 // 0x1C
    };
    u8 _pad28[0x10];                // 0x28
    f32 scaleX;                     // 0x38
    f32 scaleY;                     // 0x3C
    union {
        u8 color[4];                // 0x40
        u32 colorU32;               // 0x40
    };
    u8 field_0x44;                  // 0x44
    u8 field_0x45;                  // 0x45
    u8 _pad46[0x2];                 // 0x46
    s16 field_0x48;                 // 0x48
    s16 field_0x4A;                 // 0x4A
    u8 field_0x4C;                  // 0x4C
    u8 field_0x4D;                  // 0x4D
    u8 field_0x4E;                  // 0x4E
    u8 field_0x4F;                  // 0x4F
} ListNode_14B9F0;

// Draw object passed to fn_3_1480E0 / fn_3_148254
typedef struct {
    u8 _pad0[0x18];
    s8 animIdx;     // 0x18
    u8 _pad19[0x27];
    u32 frontColor; // 0x40
    u32 backColor;  // 0x44
} Rep3880DrawObj;

// Return type from fn_800339F0
struct Struct_800339F0_Result {
    u8 _pad[0x0C];                  // 0x00-0x0B
    ListNode_14B9F0* listHead;      // 0x0C
    s32 field_0x10;                 // 0x10
    u16 flags : 4;                  // 0x14
    u16 count : 12;
    u8 _pad16[0x18 - 0x16];         // 0x16
    Vec* field_0x18;                // 0x18
    u8 _pad1C[0x20 - 0x1C];         // 0x1C
    struct C5CE0Arg* field_0x20;    // 0x20
    s32 field_0x24;                 // 0x24
};

typedef struct {
    f32 x; // 0x0
    f32 y; // 0x4
    f32 z; // 0x8
} Struct_B850_Entry; // size: 0xC

typedef struct Struct_B850_Node {
    struct Struct_B850_Node* next; // 0x00
    Struct_B850_Entry entries[7];  // 0x04
} Struct_B850_Node;

typedef struct {
    u8 _pad[0xC];
    Struct_B850_Node* head; // 0x0C
    u8 _pad10[0x8];
    u8 someFlag; // 0x18
} UnknownStruct_B850;

extern UnknownStruct_B850* lbl_3_bss_B850;

typedef struct UnknownStruct_14CA98 {
    struct UnknownStruct_14CA98* next;
    u8 _pad0[0x40];
    u8 field_0x44;  // 0x44
    u8 field_0x45;  // 0x45
    u8 _pad1[0x4];
    u16 field_0x4A; // 0x4A
    u8 field_0x4C;  // 0x4C
} UnknownStruct_14CA98;

typedef struct {
    u8 _pad[0x4];
    s32 unk4;      // 0x04
    s32 unk8;      // 0x08
    s32 unkC;      // 0x0C
    u8 _pad10[0x4];
    s32 unk14;     // 0x14
    u8 _pad18[0x4];
} Struct_26E24;

extern Struct_26E24 lbl_3_data_26E24;

typedef struct {
    u8 _pad0[0x4];    // 0x00
    s32 unk_04;        // 0x04
    s32 unk_08;        // 0x08
    u8 _padC[0x4];    // 0x0C
    s32 unk_10;        // 0x10
    u8 _pad14[0x4];   // 0x14
    s32 unk_18;        // 0x18
    s32 unk_1C;        // 0x1C
    u8 _pad20[0x4];   // 0x20
    s32 unk_24;        // 0x24
    u8 _pad2[0x30];   // 0x28
} Struct_26C3C;

extern Struct_26C3C lbl_3_data_26C3C;

void pitchingMachinePitching(s32 param);
void fn_80033794(ListNode_14B9F0* list);

void fn_3_14737C(void);
struct Rep3880Source;
void fn_3_147778(struct Struct_800339F0_Result* obj, struct Rep3880Source* src);
void fn_3_147C00(struct Rep3880Source* src);
void fn_3_147CFC(struct Rep3880Source* src);
void fn_3_147DFC(void);
void fn_3_147E20(void);
void fn_3_147F94(void);
void fn_3_1480E0(Rep3880DrawObj* obj);
void fn_3_148254(Rep3880DrawObj* obj, ListNode_14B9F0* node);
bool fn_3_1483D4(void);
void fn_3_14841C(void);
typedef struct Struct_148EF0_Arg {
    u8 _pad0[0x10];
    Vec unk10; // 0x10
} Struct_148EF0_Arg;
void fn_3_148EF0(Struct_148EF0_Arg* arg0, f32 angle);
void fn_3_148FD0(void);
void fn_3_149340(void);
void fn_3_14975C(void);
void fn_3_149BA8(void);
void fn_3_14A070(s32* arr, s32 count);
void fn_3_14A164(void);
s32 fn_3_14A188(struct Struct_14C79C_Arg* arg);
void fn_3_14A37C(void);
void fn_3_14A62C(void);
void fn_3_14A90C(void);
void fn_3_14AC1C(void);
void fn_3_14AC40(void);
typedef struct {
    u8 _pad0[0x24];
    Vec pos; // 0x24
} Struct_14B248_Arg;
void fn_3_14B248(Struct_14B248_Arg* arg0, ListNode_14B9F0* node);
void fn_3_14B3F4(void);
void fn_3_14B53C(void* arg0, void* arg1, void* arg2);
void fn_3_14B92C(void* arg0, void* arg1);
void fn_3_14B9A0(void* arg0, void* arg1);
void fn_3_14B9F0(void);
void fn_3_14BA40(void);
void fn_3_14BCB0(void);
void fn_3_14BECC(void* arg0, void* arg1);
void fn_3_14C348(void* arg0, void* arg1);
void fn_3_14C398(void);
void fn_3_14C3BC(ListNode_14B9F0* node);
void fn_3_14C4C8(void);
typedef struct Struct_14C79C_Arg {
    u8 _pad0[0xC];
    ListNode_14B9F0* node;          // 0x0C
    s32 unk10;                      // 0x10
} Struct_14C79C_Arg;
void fn_3_14C79C(Struct_14C79C_Arg* arg0);
void fn_3_14C830(void);
void fn_3_14C904(void);
void fn_3_14CA00(void);
void fn_3_14CA98(UnknownStruct_14CA98* obj);
void fn_3_14CAB4(s8 arg0);
void fn_3_14CB28(s8 arg0);
void fn_3_14CBB4(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node);
void fn_3_14CD40(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node);
void fn_3_14CECC(void);
void fn_3_14D2C0(void);
void fn_3_14D318(ListNode_14B9F0* node);
void fn_3_14D44C(void);
void fn_3_14D6D4(Struct_14D6D4_Input* in);
void fn_3_14D710(void);
void fn_3_14DC80(s32 arg);
void fn_3_14DCE0(void);
void fn_3_14DD04(void);
void fn_3_14DF6C(void);
void fn_3_14E234(void);
void fn_3_14E7C0(void* arg0);
void fn_3_14E810(void);
void fn_3_14E894(void);
void fn_3_14E920(s8 arg0);
void fn_3_14E988(s8 arg0);
void fn_3_14E9F0(ListNode_14B9F0* node);
void fn_3_14EAF4(ListNode_14B9F0* node);
void fn_3_14ED24(void);
void fn_3_14F3CC(ListNode_14B9F0* node);
typedef struct {
    u8 _pad0[0x38];
    f32 field_0x38;
    f32 field_0x3C;
    u8 _pad1[0x3];
    u8 field_0x43;
    u8 _pad2[0x6];
    s16 field_0x4A;
} Struct_14F544_Arg;

typedef struct {
    u32 field_0x0;   // 0x0
    u8 _pad0[0x4];
    s32 field_0x8;
    u8 _pad1[0x8];
    u32 field_0x14;
    u8 _pad2[0x4];
    u32 field_0x1C;
    u8 _pad3[0x4];
} Struct_26C94;
extern Struct_26C94 lbl_3_data_26C94;
extern f32 lbl_3_rodata_3930;

void fn_3_14F544(Struct_14F544_Arg* arg);
void fn_3_14F5A4(void);
void fn_3_14F8D0(struct Struct_800339F0_Result* arg);
void fn_3_14F930(void);
void fn_3_150010(s32 arg);
void fn_3_150070(void);
void fn_3_1500C8(void);
void fn_3_150120(void);
void fn_3_1504EC(void);
void fn_3_150940(void);
void fn_3_150D84(void);
struct C2310Holder;
typedef struct {
    u8 _pad0[0x18];
    struct C2310Holder* holder; // 0x18
} Struct_151068_Arg;
void fn_3_151068(Struct_151068_Arg* obj, ListNode_14B9F0* node);
void fn_3_151204(void* obj, void* arg1, void* arg2);
void fn_3_151694(void* arg0, void* arg1);
void fn_3_151710(void* arg0, void* arg1);
void fn_3_151760(void);
void fn_3_151798(void);
void fn_3_1517D0(ListNode_14B9F0* node, Struct_14C79C_Arg* arg1);
void fn_3_1519F8(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node);
void fn_3_151BAC(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node);
void fn_3_151D6C(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node);
void fn_3_151F2C(void);
void fn_3_1524E8(void);
void fn_3_152794(void);
void fn_3_152AB4(void);
void fn_3_1531A4(void);
void fn_3_1534C0(ListNode_14B9F0* node);
void fn_3_1536A8(void);
void fn_3_153E8C(ListNode_14B9F0* node, VecXYZ* pos, u8 arg2, u8 arg3, u8 arg4);
void fn_3_153F8C(struct Struct_800339F0_Result* obj, s32 arg1, s32 arg2, Vec* arg3);
void fn_3_1540E4(s32 arg0, s32 arg1, Vec* arg2);
void fn_3_1541C4(s32 arg0, s32 arg1, Vec* arg2);
void fn_3_154214(void);
void fn_3_154238(s16 arg0);
void fn_3_1542F4(void);
void fn_3_1549F0(void);
void fn_3_154C7C(u32 unknown);
void fn_3_15521C(u32 unused, u32 param_2, u32 param_3);
void fn_3_155264(void);
void fn_3_155288(void);
void fn_3_1552AC(void);
void fn_3_1559E4(void);
void fn_3_155C28(void);
void fn_3_155F08(void);
void fn_3_156218(void);
void fn_3_156548(void);
void fn_3_156970(void);
void fn_3_156D04(void);
void fn_3_15730C(u32 index, f32 x, f32 y, f32 z);
void fn_3_1573AC(void);
void fn_3_157570(void);
void fn_3_157588(s32 arg);
Struct_B850_Entry* fn_3_1575F0(u32 index);
void fn_3_15767C(void);
void fn_3_1578F8(void);
void fn_3_15791C(void);
void fn_3_157AC4(void);

// No local headers needed.
#endif // !__GAME_rep_3880_H_
