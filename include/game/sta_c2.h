#ifndef __GAME_sta_c2_H_
#define __GAME_sta_c2_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

extern u8 lbl_3_bss_A81C;

// Forward declaration for the dependency
void AnimateActorBones(void* boneData);

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
    u8 _pad4[0xca - 0xB1];     // 0xb1 to 0xc9
    u8 field_0xca;              // Offset 0xca
} ActorObject;

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
void fn_3_CBAFC(void);
void fn_3_CBC18(void);
void fn_3_CBF80(void);
void fn_3_CC1D4(void);
void fn_3_CC354(void);
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
void fn_3_CEBBC(void);
void fn_3_CEC98(void);
void fn_3_CED30(void);
void fn_3_CED34(void);
void fn_3_CED38(void);
void fn_3_CED3C(void);
void fn_3_CED40(void);
void fn_3_CEE5C(void);
void fn_3_CEFA8(void);
void fn_3_CF278(void);
void fn_3_CF72C(void);
void fn_3_CF92C(void);
void fn_3_CF930(void);
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
void fn_3_D0854(void);
void fn_3_D0918(void);
void fn_3_D1004(void);
void fn_3_D1110(void);
void fn_3_D127C(void);
void fn_3_D1280(void);
void fn_3_D141C(void);
void fn_3_D173C(void);
void fn_3_D1848(void);
void fn_3_D196C(void);
void fn_3_D1AC4(ActorObject* arg0);
void fn_3_D1B24(void);
void fn_3_D1F2C(void);
void fn_3_D2220(void);
void fn_3_D233C(void);
int fn_3_D249C(Struct_800D249C_Arg0 *param_1);
void fn_3_D24E8(StaC2D24E8Arg* arg0, s32 arg1);
void fn_3_D255C(void);
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
void fn_3_D4780(void);
void fn_3_D4CA4(void);
void fn_3_D4E00(void);
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC[0x18];
    u8 unk24[0xC];
    u8 unk30[0xC];
    s32 unk3C;
} StaC2D501CEntry; // size: 0x40
void fn_3_D501C(StaC2D501CEntry* entries);
void fn_3_D511C(void);
void fn_3_D53C0(void);


s32 fn_3_D5444(unknown_tri_compare* a, unknown_tri_compare* b);
s32 fn_3_D5470(f32* a, f32* b);
void fn_3_D5494(void);
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
