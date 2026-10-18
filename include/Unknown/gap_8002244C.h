#ifndef __UNKNOWN_gap_8002244C_H_
#define __UNKNOWN_gap_8002244C_H_

#include "mssbTypes.h"
typedef struct Gap8002244CFlags {
    u8 _pad0[0x1E8];
    /* 0x1E8 */ u8 unk1E8;
    u8 unk1E9;
    u8 flags;
} Gap8002244CFlags;
extern Gap8002244CFlags lbl_803716B8;
typedef struct Gap8002244CObj {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
    /* 0x10 */ s32 unk10;
    u8 _pad14[0x4];
    /* 0x18 */ s32 unk18;
} Gap8002244CObj;

extern s32 lbl_803CBC60;

void fn_8002244C(void);
void fn_8002254C(void);
void fn_80022620(void);
void fn_80022634(void);
void fn_800227A0(void);
void fn_800227E4(void);
void fn_800229CC(void);
void fn_80022A24(void);
void fn_80022B14(void);
void fn_80022B68(void);
void fn_80022CB4(void);
void fn_80022D58(void);
void f_InitBone(void);
void fn_80023078(void);
void f_InitActorWithLayout(void);
void BuildBoneSkinOrientationMatrix(void);
void fn_800238E0(void);
void fn_8002399C(void);
void fn_80023AA4(void);
void fn_80023B04(void);
void fn_80023B90(void);
void fn_80023CF4(void);
s32 fn_80023D3C(void);
void fn_80023D44(s32 value);
void fn_80023D4C(void);
void fn_80023D98(void);
void fn_80023DFC(void);
void fn_80023E48(void);
void fn_80023EEC(Gap8002244CObj* obj, s32 a, s32 b);
void fn_80023F0C(void);
void gOz_GXSetTexture(void);
void fn_80024390(void);
void SetDisplayStateTexture(void);
void fn_800245EC(void);
void fn_800246D4(void);
void fn_800247E4(void);
void challengeStarRelatedInd(void);
void multBottomBits_asFloat(void);
void byteWiseMultiply(void);
void LERPToNewRange_Float(void);
void LinearInterpolateToNewRange(void);
void fn_80024C04(void);
void fn_80024C6C(void);
void fn_80024D2C(void);
void fn_80024DB0(void);
void fn_80024FA4(void);
void fn_80025C58(void);

#endif // !__UNKNOWN_gap_8002244C_H_
