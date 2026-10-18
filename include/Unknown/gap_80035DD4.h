#ifndef __UNKNOWN_gap_80035DD4_H_
#define __UNKNOWN_gap_80035DD4_H_

#include "mssbTypes.h"
typedef struct Gap80035DD4Request Gap80035DD4Request;
typedef struct Gap80035DD4Actor Gap80035DD4Actor;
typedef struct Gap80035DD4RenderState { u8 _pad0[0x78]; s32 index; } Gap80035DD4RenderState;
extern Gap80035DD4RenderState lbl_800F79B8;
typedef struct Gap80035DD4Entry {
    u8 _pad0[0x54];
    /* 0x54 */ s32 unk54;
    u8 _pad58[0x4];
    /* 0x5C */ u32 unk5C;
    u8 _pad60[0x8];
    /* 0x68 */ u8 unk68;
    u8 _pad69[0x57];
} Gap80035DD4Entry;
extern Gap80035DD4Entry lbl_8039C3E0[];
typedef struct Gap80035DD4Quat { f32 x, y, z, w; } Gap80035DD4Quat;
typedef struct Gap80035DD4Vec { f32 x, y, z; } Gap80035DD4Vec;
typedef struct Gap80035DD4Task { u8 _pad0[0x14]; /* 0x14 */ u16 baseIndex; } Gap80035DD4Task;
typedef struct Gap80035DD4Node {
    u8 _pad0[0x64];
    /* 0x64 */ u16 frame;
    /* 0x66 */ u8 model;
} Gap80035DD4Node;
typedef struct Gap80035DD4Slot {
    Gap80035DD4Node* node;
    u32 unk4;
} Gap80035DD4Slot;
extern Gap80035DD4Slot lbl_80371C30[];
typedef struct Gap80035DD4Model {
    u8 _pad0[0x38];
    /* 0x38 */ s32 data;
} Gap80035DD4Model;
extern Gap80035DD4Model lbl_803C4BE0[20];
typedef struct Gap80035DD4Query {
    u8 _pad0[0x14];
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ u8 _pad18[0x4];
    /* 0x1C */ s32 result;
    u8 _pad20[0x30];
} Gap80035DD4Query;
void fn_8000CEF0(s32 data, s32 frame, s32 a, s32 b, Gap80035DD4Query* out);
typedef struct Gap80035DD4Xform {
    u8 _pad0[0xC];
    /* 0x0C */ Gap80035DD4Vec vel;
    /* 0x18 */ Gap80035DD4Vec accel;
    u8 _pad24[0x34];
    /* 0x58 */ f32 result[3][4];
    /* 0x88 */ f32 rot[3][4];
    /* 0xB8 */ f32 inv[3][4];
    /* 0xE8 */ f32 x, y, z;
    /* 0xF4 */ Gap80035DD4Quat quat;
    u8 _pad104[0xC];
    /* 0x110 */ Gap80035DD4Vec force;
    u8 _pad11C[0x18];
    /* 0x134 */ Gap80035DD4Vec torque;
} Gap80035DD4Xform;
void PSVECScale(Gap80035DD4Vec* src, Gap80035DD4Vec* dst, f32 scale);
void PSVECAdd(Gap80035DD4Vec* a, Gap80035DD4Vec* b, Gap80035DD4Vec* ab);
void PSMTXMultVec(f32 m[3][4], Gap80035DD4Vec* src, Gap80035DD4Vec* dst);
void PSVECCrossProduct(Gap80035DD4Vec* a, Gap80035DD4Vec* b, Gap80035DD4Vec* axb);
void PSMTXQuat(f32 m[3][4], Gap80035DD4Quat* q);
u32 PSMTXInverse(f32 src[3][4], f32 inv[3][4]);
void PSMTXTransApply(f32 src[3][4], f32 dst[3][4], f32 x, f32 y, f32 z);
typedef struct Gap80035DD4Block { u8 bytes[0x18]; } Gap80035DD4Block;
extern Gap80035DD4Block lbl_800F79A0;
extern u8 lbl_803CBCA2[6];
extern u8 lbl_803CBCA1;
extern s16 lbl_803CB818;
extern s32 lbl_803CB820;
u8* memset(u8* memory, s32 value, u32 size);
typedef struct Gap80035DD4Physics {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 dt;
    /* 0x1C */ f32 dtSq;
    /* 0x20 */ s32 steps;
    /* 0x24 */ f32 unk24;
} Gap80035DD4Physics;
extern f32 lbl_801F8640[4][4];
void C_MTXFrustum(f32 m[4][4], f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_800B0A14_removeQueue(void);

void fn_80035DD4(void);
void fn_80035ED0(s32 index);
void fn_80035EEC(s32 value, s32 index);
void fn_80035F20(void);
void fn_80036134(void);
s32 fn_80036214(Gap80035DD4Task* task, s32 index, s32 a, s32 b);
void fn_80036270(Gap80035DD4Task* task, s32 index, s32 a, s32 b, s16* x, s16* y);
void fn_800362F0(void);
void fn_800363D8(void);
void fn_8003649C(void);
void fn_8003656C(void);
void fn_8003664C(void);
void fn_80036824(void);
void fn_800369DC(f32 zoom);
void fn_80036A3C(void);
void fn_80036C88(void);
void fn_80037054(void);
void fn_8003731C(void);
void fn_80037768(void);
void fn_80037964(void);
void fn_80037984(void);
void fn_80037AA0(void);
void fn_80037B18(Gap80035DD4Xform* xf, Gap80035DD4Vec* force);
void fn_80037BAC(void);
void fn_8003819C(void);
f32 (*fn_800383BC(Gap80035DD4Xform* xf))[4];
void fn_80038418(void);
void fn_800385F0(void);
void fn_800387B0(void);
void fn_80038B48(void);
void fn_80038CD0(void);
void fn_80038E2C(Gap80035DD4Physics* phys);
void fn_80038EC4(Gap80035DD4Request* request, Gap80035DD4Actor** actor, u8 count);
void fn_80038F08(Gap80035DD4Request* request, Gap80035DD4Actor* actor, u32 count);
void fn_80039310(void);
void fn_80039A4C(void);

#endif // !__UNKNOWN_gap_80035DD4_H_
