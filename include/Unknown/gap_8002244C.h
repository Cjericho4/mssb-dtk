#ifndef __UNKNOWN_gap_8002244C_H_
#define __UNKNOWN_gap_8002244C_H_

#include "mssbTypes.h"
typedef struct Gap8002244CLoad { u8 _pad0[0x715]; u8 complete; } Gap8002244CLoad;
extern Gap8002244CLoad lbl_803C6CF8;
void fn_800B0A14_removeQueue(void);
u8* memset(u8* memory, s32 value, u32 size);
void OSSetProgressiveMode(u32 enable);
void fn_800A7E00(void);
typedef struct Gap8002244CProjParams {
    /* 0x00 */ f32 type;
    /* 0x04 */ f32 m00;
    /* 0x08 */ f32 m0x;
    /* 0x0C */ f32 m11;
    /* 0x10 */ f32 m1x;
    /* 0x14 */ f32 m22;
    /* 0x18 */ f32 m23;
} Gap8002244CProjParams;
typedef struct Gap8002244CStageEntry {
    u8 _pad0[2];
    /* 0x2 */ u8 id;
    u8 _pad3[3];
} Gap8002244CStageEntry;
extern Gap8002244CStageEntry lbl_800E8558[54];
extern u8 lbl_803CB748[8];
typedef struct Gap8002244CGameSettings {
    u8 _pad0[0x1A];
    /* 0x1A */ u8 unlocked[6];
    u8 _pad20[0x38];
} Gap8002244CGameSettings;
extern Gap8002244CGameSettings g_d_GameSettings;
void fn_800A7568(void);
void fn_800A6304(void);
typedef struct Gap8002244CRecord {
    s32 unk0;
    u32 unk4;
    s32 unk8, unkC;
    u32 unk10;
    s32 unk14;
} Gap8002244CRecord;
typedef struct Gap8002244CFlags {
    u8 header[0x18];
    union {
        u8 records[0x1B0];
        Gap8002244CRecord recs[18];
    };
    s8 flag1C8, flag1C9;
    /* 0x1CA */ u8 pending1CA;
    u8 _pad1CB;
    u32 current; /* 0x1CC */
    u32 pending; /* 0x1D0 */
    u8 _pad1D4[0x14];
    /* 0x1E8 */ u8 unk1E8;
    u8 unk1E9;
    u8 flags;
} Gap8002244CFlags;
extern Gap8002244CFlags lbl_803716B8;
typedef struct Gap8002244CVector { f32 x, y, z; } Gap8002244CVector;
typedef struct Gap8002244CObj {
    union { s32 unk0; Gap8002244CVector* vectors; };
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
    /* 0x10 */ s32 unk10;
    volatile s32 current; /* 0x14 */
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
BOOL fn_80022CB4(s32 a, u32 b, s32 c, s32 d, u32 e, s32 f);
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
void fn_80023CF4(BOOL enabled);
s32 fn_80023D3C(void);
void fn_80023D44(s32 value);
BOOL fn_80023D4C(Gap8002244CObj* obj, Gap8002244CVector* out);
void fn_80023D98(void);
BOOL fn_80023DFC(Gap8002244CObj* obj, Gap8002244CVector* out);
void fn_80023E48(void);
void fn_80023EEC(Gap8002244CObj* obj, s32 a, s32 b);
void fn_80023F0C(void);
void gOz_GXSetTexture(void);
void fn_80024390(f32 m[3][4], Gap8002244CProjParams* out, s32 type);
void SetDisplayStateTexture(void);
void fn_800245EC(void);
void fn_800246D4(void);
void fn_800247E4(void);
void challengeStarRelatedInd(void);
void multBottomBits_asFloat(void);
void byteWiseMultiply(void);
void LERPToNewRange_Float(void);
void LinearInterpolateToNewRange(void);
BOOL fn_80024C04(s32 index);
void fn_80024C6C(void);
void fn_80024D2C(void);
void fn_80024DB0(void);
void fn_80024FA4(void);
void fn_80025C58(void);

#endif // !__UNKNOWN_gap_8002244C_H_
