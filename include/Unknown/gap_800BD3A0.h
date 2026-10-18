#ifndef __UNKNOWN_gap_800BD3A0_H_
#define __UNKNOWN_gap_800BD3A0_H_

#include "mssbTypes.h"
typedef struct Gap800BD3A0Color {
    u8 r, g, b, a;
} Gap800BD3A0Color;
typedef struct Gap800BD3A0Light {
    u8 _pad0[0x40];
    /* 0x40 */ f32 posX;
    /* 0x44 */ f32 posY;
    /* 0x48 */ f32 posZ;
    u8 _pad4C[0xC];
    /* 0x58 */ f32 dirX;
    /* 0x5C */ f32 dirY;
    /* 0x60 */ f32 dirZ;
    u8 _pad64[0xC];
    /* 0x70 */ Gap800BD3A0Color color;
} Gap800BD3A0Light;
typedef struct Gap800BD3A0Entry {
    u8 _pad0[0xB0];
    /* 0xB0 */ u8 unkB0;
    u8 _padB1[0x2F];
} Gap800BD3A0Entry;
typedef struct Gap800BD3A0State {
    /* 0x0 */ u8 drawShadows;
    u8 _pad1[0x13];
    /* 0x14 */ Gap800BD3A0Entry* entries;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    u8 _pad24[0x28];
    /* 0x4C */ u8 unk4C;
} Gap800BD3A0State;
extern Gap800BD3A0State lbl_803009F8;

void LITInitColor(Gap800BD3A0Light* light, Gap800BD3A0Color* color);
void LITInitDir(Gap800BD3A0Light* light, f32 x, f32 y, f32 z);
void LITInitPos(Gap800BD3A0Light* light, f32 x, f32 y, f32 z);
void LITInitAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void LITAlloc(void);
void fn_800BD478(void);
void fn_800BD548(void);
void fn_800BD670(void);
void fn_800BD8C4(void);
void fn_800BDA24(void);
void fn_800BDA94(void);
void fn_800BDC88(void);
void ActorObjectInitTable(void);
void fn_800BDE8C(u8 value);
void fn_800BDEA0(void);
void fn_800BDF70(void);
void fn_800BDFE0(void);
void fn_800BE09C(void);
void fn_800BE158(void);
void fn_800BE498(void);
void fn_800BEA04(void);
void fn_800BEB3C(void);
u8* fn_800BEB80(u8 index);
u8 fn_800BEBA0(void);
u8 GetDrawShadows(void);
void DrawShadows(u8 enable);
void fn_800BEBCC(void);
void fn_800BEC00(void);
void fn_800BEC30(void);
void fn_800BF008(void);
void fn_800BF038(s32 value);
void fn_800BF048(s32 value);
void fn_800BF058(s32 value);
Gap800BD3A0State* fn_800BF068(void);
void SKNLoadFile(void);
void SKNFlushByIndex1(void);
void SKNFlushByIndex2(void);
void SKNBzero32B(void);
void SKNInit(void);
void fn_800BF2A8(void);
void SKNIt(void);
void SKN1Vecs16Norms16(void);
void fn_800BFF9C(void);
void SKN2Vecs16Norms16NoTouch(void);
void fn_800C02C8(void);
void SKNAccVecs16Norms16Iu161(void);
void SKNAccVecs16Norms16Iu162(void);
void convertTextureHeader(void);
void fn_800C07BC(void);

void GXInitLightAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);

#endif // !__UNKNOWN_gap_800BD3A0_H_
