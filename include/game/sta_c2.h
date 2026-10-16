#ifndef __GAME_sta_c2_H_
#define __GAME_sta_c2_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

extern u8 lbl_3_bss_A81C;

// Forward declaration for the dependency
void AnimateActorBones(void* boneData);
void fn_800B4CA0(void* boneData, f32 val);

// Struct at the first level of indirection
typedef struct BoneWrapper {
    void* boneData; // Offset 0x00
} BoneWrapper;

// Main structure passed to fn_3_CFA8C
typedef struct ActorObject {
    u8 _pad0[0x74];
    BoneWrapper* wrapper;       // Offset 0x74
    u8 _pad1[0x90 - 0x78];     // 0x78 to 0x8F
    u8 unk90_bit0 : 1;          // Offset 0x90, bit 7 (MSB = 0x80)
    u8 unk90_rest : 7;
    u8 _pad2[0xa9 - 0x91];     // 0x91 to 0xa8
    u8 field_0xa9;              // Offset 0xa9
    u8 _pad3[0xB0 - 0xAA];     // 0xaa to 0xaf
    u8 state;                   // Offset 0xB0
    u8 _pad4[0xc1 - 0xB1];     // 0xb1 to 0xc0
    u8 field_0xc1;              // Offset 0xc1
    u8 _pad5[0xca - 0xC2];     // 0xc2 to 0xc9
    u8 field_0xca;              // Offset 0xca
} ActorObject;

typedef struct StaC2RangeEntry {
    u8 _pad0[0x20];
    f32 posMin;   /* 0x20 */
    f32 posRange; /* 0x24 */
    f32 negMin;   /* 0x28 */
    f32 negRange; /* 0x2C */
    u8 _pad30[0x4];
} StaC2RangeEntry; /* size: 0x34 */

extern StaC2RangeEntry lbl_3_data_18364[6];

typedef struct StaC2RangeObj {
    u8 _pad0[0x9C];
    u8 entryIdx; /* 0x9C */
    u8 _pad9D[0xD0 - 0x9D];
    s8 dir;      /* 0xD0 */
} StaC2RangeObj;

typedef struct StaC2D24E8Arg {
    u8 _pad0[0xA0];
    Vec field_0xA0;
} StaC2D24E8Arg;

typedef struct StaC2EffectScaleSrc {
    u8 _pad0[0xBC];
    f32 scale; /* 0xBC */
} StaC2EffectScaleSrc;

typedef struct StaC2EffectOwner {
    u8 _pad0[0xA4];
    StaC2EffectScaleSrc* scaleSrc; /* 0xA4 */
} StaC2EffectOwner;

typedef struct StaC2EffectParent {
    u8 _pad0[0x20];
    StaC2EffectOwner* owner; /* 0x20 */
} StaC2EffectParent;

typedef struct StaC2Effect {
    u8 _pad0[0x4];
    Vec pos;           /* 0x04 */
    u8 _pad10[0xC];
    Vec basePos;       /* 0x1C */
    u8 _pad28[0x10];
    f32 scaleX;        /* 0x38 */
    f32 scaleY;        /* 0x3C */
    u8 colorR;         /* 0x40 */
    u8 colorG;         /* 0x41 */
    u8 colorB;         /* 0x42 */
    u8 alpha;          /* 0x43 */
    u8 _pad44[0x4];
    s16 timer;         /* 0x48 */
    s16 duration;      /* 0x4A */
} StaC2Effect;

void fn_3_CB8A8(void);
void fn_3_CBA9C(ActorObject* arg0);
void fn_3_CBC18(void);
void fn_3_CBF80(void);
void fn_3_CC1D4(void);
void fn_3_CC438(void);
void fn_3_CC5C4(void);
void fn_3_CC81C(void);
void fn_3_CCC24(void);
void fn_3_CD958(void);
void fn_3_CD968(void);
void fn_3_CDB48(void);
void fn_3_CDD90(void);
void fn_3_CDFA4(void);
void fn_3_CE56C(void *arg0, u8 arg1);
void fn_3_CE8E4(void);
void fn_3_CE954(void);
void fn_3_CEBBC(VecXYZ* pos, s32 idx);
void fn_3_CEC98(void);
void fn_3_CED30(void);
void fn_3_CED34(void);
void fn_3_CED38(void);
void fn_3_CED3C(void);
void fn_3_CEFA8(void);
void fn_3_CF278(void);
void fn_3_CF72C(void);
void fn_3_CF92C(void);
void fn_3_CFA88(void);
void fn_3_CFA8C(ActorObject* actor);
void fn_3_CFAB4(StaC2Effect* effect, StaC2EffectParent* parent);
void fn_3_CFB44(void);
void fn_3_CFD58(void);
void fn_3_D00CC(void);
void fn_3_D00D0(void);
void fn_3_D0280(void);
void fn_3_D0284(void);
void fn_3_D0490(void);
void fn_3_D0528(void);
s32 fn_3_D052C(void);
void fn_3_D0534(void);
f32 fn_3_D0854(StaC2RangeObj* obj);
void fn_3_D0918(void);
void fn_3_D1004(void);
void fn_3_D1110(void);
void fn_3_D127C(void);
void fn_3_D1280(void);
void fn_3_D141C(void);
void fn_3_D173C(void);
void fn_3_D196C(s32 idx);
void fn_80025EEC(struct StadiumActorAnim* anim, s32 arg1, s32 arg2);
void fn_3_D1AC4(ActorObject* arg0);
void fn_3_D1B24(void);
int fn_3_D249C(Struct_800D249C_Arg0 *param_1);
void fn_3_D24E8(StaC2D24E8Arg* arg0, s32 arg1);
typedef struct {
    u8 _pad0[0xA0];
    VecXYZ pos; /* 0xA0 */
} StaC2Object;

VecXYZ* fn_3_D2684(StaC2Object* obj);
void fn_3_D278C(void);
void fn_3_D2A0C(void);
void fn_3_D30D0(void);
void fn_3_D36B0(void);
void fn_3_D3880(void);
void fn_3_D3CDC(void);
void fn_3_D3F54(void);
void fn_3_D4E00(void);
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    Vec unkC[2];
    u8 unk24[0xC];
    u8 unk30[0xC];
    s32 unk3C;
} StaC2D501CEntry; // size: 0x40
typedef struct StaC2ChainParams {
    u8 _pad0[0x18];
    f32 unk18; /* 0x18 */
    f32 unk1C; /* 0x1C */
    u8 _pad20[0x4];
    f32 unk24; /* 0x24 */
} StaC2ChainParams; // size: 0x28

typedef struct StaC2ChainObj {
    u8 _pad0[0xA0];
    Vec pos;                    /* 0xA0 */
    u8 _padAC[0xC0 - 0xAC];
    f32 angle;                  /* 0xC0 */
    StaC2D501CEntry* entries;   /* 0xC4 */
} StaC2ChainObj;

void fn_3_CBAFC(StaC2ChainObj* obj);
void fn_3_D2220(StaC2ChainObj* obj);
InMemBallType* fn_3_D233C(StaC2ChainObj* obj);
s8 fn_3_D255C(StaC2ChainObj* obj);

typedef struct StaC2PlaceEntry {
    Vec pos;        /* 0x00 */
    u8 _padC[0x4];
    Vec rotA;       /* 0x10 */
    Vec rotB;       /* 0x1C */
    u8 _pad28[0x34 - 0x28];
} StaC2PlaceEntry; /* size: 0x34 */

extern StaC2PlaceEntry lbl_3_data_182C8[3];

typedef struct StaC2PlacedObj {
    Control control;            /* 0x00 */
    u8 _pad3C[0x9C - 0x3C];
    u8 idx;                     /* 0x9C */
    u8 _pad9D[0xA0 - 0x9D];
    Vec pos;                    /* 0xA0 */
    u8 _padAC[0xC0 - 0xAC];
    f32 angle;                  /* 0xC0 */
    u8 _padC4[0xCA - 0xC4];
    u8 unkCA;                   /* 0xCA */
} StaC2PlacedObj;

void fn_3_D4780(StaC2PlacedObj* obj);
void fn_3_D4CA4(StaC2PlacedObj* obj);

typedef struct StaC2Particle {
    u8 _pad0[0x4];
    Vec pos;        /* 0x04 */
    Vec vel;        /* 0x10 */
    u8 _pad1C[0x38 - 0x1C];
    f32 unk38;      /* 0x38 */
    f32 unk3C;      /* 0x3C */
    u8 _pad40[0x43 - 0x40];
    u8 unk43;       /* 0x43 */
    u8 _pad44[0x48 - 0x44];
    s16 unk48;      /* 0x48 */
} StaC2Particle;

void fn_8003403C(f32 a, f32 b);
void fn_80033CC8(StaC2Particle* obj, s32 arg1);
void fn_3_CED40(StaC2Particle* obj, s32 arg1);
void fn_3_CEE5C(StaC2Particle* obj, s32 arg1);

typedef struct StaC2CF930Anim {
    u8 _pad0[0xC];
    f32 curFrame;   /* 0x0C */
    f32 speed;      /* 0x10 */
    u8 _pad14[0x24 - 0x14];
    u16 numFrames;  /* 0x24 */
} StaC2CF930Anim;

typedef struct StaC2CF930Link {
    u8 _pad0[0x8];
    void* active;   /* 0x08 */
} StaC2CF930Link;

typedef struct StaC2CF930Obj {
    Control control;            /* 0x00 */
    u8 _pad3C[0x8C - 0x3C];
    StaC2CF930Anim* anim;       /* 0x8C */
    u8 flag90 : 1;              /* 0x90 */
    u8 flag90_rest : 7;
    u8 _pad91;
    u8 alpha;                   /* 0x92 */
    u8 _pad93[0x9C - 0x93];
    u8 posIdx;                  /* 0x9C */
    u8 _pad9D[0xA0 - 0x9D];
    StaC2CF930Link* link;       /* 0xA0 */
} StaC2CF930Obj;

typedef struct StaC2Vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} StaC2Vec4;

extern StaC2Vec4 lbl_3_data_18730[27];

void fn_3_CF930(StaC2CF930Obj* obj);

typedef struct StaC2D1848Wrapper {
    void* boneData;     /* 0x00 */
    u8 _pad4[0x59 - 0x4];
    u8 unk59;           /* 0x59 */
    u8 _pad5A[0x5C - 0x5A];
    f32 unk5C;          /* 0x5C */
} StaC2D1848Wrapper;

typedef struct StaC2D1848Obj {
    u8 _pad0[0x74];
    StaC2D1848Wrapper* wrapper; /* 0x74 */
    u8 _pad78[0x90 - 0x78];
    u8 flag90 : 1;              /* 0x90 */
    u8 flag90_rest : 7;
    u8 _pad91[0x9C - 0x91];
    u8 idx;                     /* 0x9C */
    u8 _pad9D[0xA0 - 0x9D];
    f32 frame;                  /* 0xA0 */
    f32 speed;                  /* 0xA4 */
    u8* trigger;                /* 0xA8 */
    u8 timer;                   /* 0xAC */
} StaC2D1848Obj;

void fn_3_D1848(StaC2D1848Obj* obj);
void fn_3_D1F2C(StaC2ChainParams* params, StaC2D501CEntry* entries, s32 count, Vec* force, StaC2ChainObj* obj);
void fn_3_CC354(StaC2D501CEntry* entries);
void fn_3_D501C(StaC2D501CEntry* entries);
void fn_3_D511C(void);
s32 fn_3_D53C0(u8 arg0);


s32 fn_3_D5444(unknown_tri_compare* a, unknown_tri_compare* b);
s32 fn_3_D5470(f32* a, f32* b);
void fn_3_D5494(Mtx m);
void fn_3_D55EC(void);
void fn_3_D5B6C(void);
void fn_3_D5C8C(void);
void fn_3_D5E80(void);
void fn_3_D60C0(void);
void fn_3_D62F0(void);
void fn_3_D6514(void);
void fn_3_D67CC(void);

// No local headers needed.
#endif // !__GAME_sta_c2_H_
