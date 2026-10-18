#ifndef __UNKNOWN_gap_800B993C_H_
#define __UNKNOWN_gap_800B993C_H_

#include "mssbTypes.h"
extern s32 lbl_803CC21C;
extern f32 lbl_803CC218;
extern f32 lbl_803CC1F8;
extern f32 lbl_803CC1FC;
typedef union Gap800B993CColor {
    struct { u8 r, g, b, a; };
    u32 word;
} Gap800B993CColor;
extern u8 lbl_803CC220;
extern Gap800B993CColor lbl_803CC224;
typedef struct Gap800B993CObj {
    u8 _pad0[0x18];
    /* 0x18 */ f32 worldMatrix[3][4];
    u8 _pad48[0x8];
    /* 0x50 */ s32 unk50;
} Gap800B993CObj;

extern s32 lbl_803CC1F0;
extern s32 lbl_803CC1F4;
extern s32 lbl_803CC200;
extern s32 lbl_803CC20C;

void fn_800B993C(void);
void fn_800B9948(s32 value);
void fn_800B9950(u32 flags, f32 a, f32 b);
void fn_800B996C(s32 value);
void SetFogNone(void);
void SetFog(void);
void SetFogNoneAgain(void);
void fn_800B9A9C(s32 a, f32 b);
void fn_800B9AA8(s32 value);
void fn_800B9AB0(void);
void fn_800B9EA8(void);
void fn_800BA44C(void);
void Custom_SetState(void);
void SetState(void);
void GetColorFromQuant(void);
void DOVARender(void);
void DOVARenderSkin(void);
void fn_800BC824(Gap800B993CObj* obj, s32 value);
void DOSetWorldMatrix(Gap800B993CObj* obj, f32 matrix[3][4]);
void InitDisplayObjWithLayout(void);
void DOGet(void);
void LoadGeoPalette(void);
void convertGeometryAndSknHeader(void);
void fn_800BCDBC(void);
void fn_800BCE38(void);
void fn_800BCEF8(void);
void fn_800BD190(void);
void fn_800BD1E8(s32 value);
void __MTGQR5(void);
void __MTGQR6(void);
void __MTGQR7(void);
void GQRSetup7(void);
void GQRSetup6(void);
void GQRSetup5(void);
u8 fn_800BD2B0(Gap800B993CColor* out);
void fn_800BD2CC(u8 enable, Gap800B993CColor* color);
void fn_800BD2DC(void);
void LITXForm(void);

void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

#endif // !__UNKNOWN_gap_800B993C_H_
