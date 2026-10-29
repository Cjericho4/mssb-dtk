#ifndef __GAME_sta_c6_H_
#define __GAME_sta_c6_H_

#include "mssbTypes.h"
#include "game/sta_c2.h"

// Structs for fn_3_E6638
typedef struct OuterPtr_E6798 {
    struct NodeArray_E6798* unk0;  // +0x00
} OuterPtr_E6798;

typedef struct ElemNode_E6798 {
    u8 _pad[0x14];
    u32 unk14;  // +0x14
    u32 unk18;  // +0x18
} ElemNode_E6798;

typedef struct NodeArray_E6798 {
    u8 _pad[0x18];
    ElemNode_E6798** unk18;  // +0x18
} NodeArray_E6798;

typedef struct Arg0_E6798 {
    u8 _pad[0x74];
    OuterPtr_E6798* unk74;  // +0x74
} Arg0_E6798;

typedef struct InnerStruct_E6638 {
    u8 _pad[0x14];
    u32 field_0x14;  // 0x14
    u32 field_0x18;  // 0x18
} InnerStruct_E6638;

typedef struct MiddleStruct_E6638 {
    u8 _pad[0x18];
    InnerStruct_E6638** array;  // 0x18 - array of pointers
} MiddleStruct_E6638;

typedef struct OuterStruct_E6638 {
    MiddleStruct_E6638* field_0x00;  // 0x00
} OuterStruct_E6638;

typedef struct BaseStruct_E6638 {
    u8 _pad[0x74];
    OuterStruct_E6638* field_0x74;  // 0x74
} BaseStruct_E6638;

typedef struct {
    u8 _pad0[0x20];
    u8 unk20;       // 0x20: display state kind (3 = TEV setting)
} DispState_E6578;

typedef struct {
    u8 _pad0[0x4];
    DispState_E6578* unk4;  // 0x04
} DispStateRef_E6578;

typedef struct {
    u8 _pad0[0xA0];
    s16 unkA0;      // 0xA0
} Target_E6578;

typedef struct {
    u8 _pad0[0xC];
    Target_E6578* unkC;     // 0x0C
} TargetRef_E6578;

typedef struct {
    u8 _pad0[0x8];
    TargetRef_E6578* unk8;      // 0x08
    u8 _pad1[0x4];
    DispStateRef_E6578* unk10;  // 0x10
} Material_E6578;

typedef struct {
    u8 _pad0[0x14];
    Material_E6578* unk14;  // 0x14
} Node_E6578;

typedef struct {
    u8 _pad0[0x18];
    Node_E6578** unk18;     // 0x18
} NodeList_E6578;

typedef struct {
    NodeList_E6578* unk0;   // 0x00
} Model_E6578;

typedef struct {
    u8 _pad0[0x9C];
    Model_E6578* unk9C;     // 0x9C
    u8 _pad1[0xC1 - 0xA0];
    u8 unkC1;               // 0xC1
} Arg0_E6578;

typedef struct StaC6Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} StaC6Color;

typedef struct {
    u8 _pad0[0xA4];
    StaC6Color color; /* 0xA4 */
    u32* unkA8;     // 0xA8
    u32* unkAC;     // 0xAC
} Struct_E6410;

typedef struct {
    u8 _pad0[0xA4];
    u32 unkA4;      // 0xA4
    u8 _pad1[0xC];  // 0xA8..0xB3
    u8* unkB4;      // 0xB4
    u8 _pad2[0x4];  // 0xB8..0xBB
    u8* unkBC;      // 0xBC
    u8 _pad3[0x2];  // 0xC0..0xC1
    u8 unkC2;       // 0xC2
} Struct_E6528;

typedef struct {
    u8 _pad0[0x6];
    u8 unk6;   // +0x06
} Inner_E5E14;

typedef struct {
    u8 _pad0[0x4];
    Inner_E5E14* unk4;  // +0x04
} Arg0_E5E14;

extern u8 lbl_3_data_196B4[];
extern u8 lbl_3_data_19024;
extern u8 lbl_3_data_1963F;
extern u8 lbl_3_data_19640;
extern f32 lbl_3_rodata_2B90;
extern f32 lbl_3_rodata_2B94;
extern f32 lbl_3_rodata_2B98;
extern f32 lbl_3_rodata_2B9C;
extern f32 lbl_3_rodata_2BA0;
extern f32 lbl_3_rodata_2BA4;
f32 fn_800B4C40(void *boneData);
void fn_800B4CA0(void *boneData, f32 val);
void fn_3_E59B4(ActorObject *arg0);
void fn_3_E5A1C(ActorObject *arg0);
void fn_3_E5A84(ActorObject* actor);
void fn_3_E5CBC(Struct_E6410* object, f32 blend);
int fn_3_E5E14(Arg0_E5E14* arg0);


typedef union StaC6Texel {
    u16 h;
    u32 w;
} StaC6Texel;

void fn_3_E5E70(StaC6Color* out, u32 fmt, StaC6Texel* src);
void fn_3_E5FEC(void);
void fn_3_E6410(Struct_E6410* arg0);
u32* fn_3_E64A8(void);
void fn_3_E6528(Struct_E6528* arg0);
void fn_3_E6578(Arg0_E6578* arg0);
void fn_3_E6638(BaseStruct_E6638* arg0);
void fn_3_E6684(BaseStruct_E6638* arg0);
void fn_3_E671C(Arg0_E6798* arg0);
void fn_3_E6798(Arg0_E6798* arg0);
void fn_3_E67F4(void);
void fn_3_E68A8(void);
void fn_3_E698C(ActorObject* arg0);
void fn_3_E6A48(void);
void fn_3_E6D90(void);
void fn_3_E7350(void);
void fn_3_E7364(s32 index);
void fn_3_E7388(void);
void fn_3_E7424(void);
struct StadiumModel* fn_3_E751C(s32 idx, Mtx m);
void fn_3_E763C(void);
typedef void (*StaC6ObjFn)();
typedef struct StaC6SetupObj {
    u8 _pad0[0x7C];
    StaC6ObjFn fn7C;    // 0x7C
    StaC6ObjFn fn80;    // 0x80
    StaC6ObjFn fn84;    // 0x84
    StaC6ObjFn fn88;    // 0x88
    u8 _pad8C[0xC1 - 0x8C];
    u8 kind;            // 0xC1
} StaC6SetupObj;
extern u8 lbl_3_bss_AEAC;
void fn_3_E7A2C(StaC6SetupObj* obj);
u8 fn_3_E7B20(u32 arg0, u32 arg1);
int fn_3_E8AC8(void);
void fn_3_E8B24(void);
void fn_3_E911C(void);

#endif // !__GAME_sta_c6_H_
