#ifndef __CHALLENGE_rep_0610_H_
#define __CHALLENGE_rep_0610_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
extern u8 lbl_1_bss_5F71;
#include "UnknownHeaders.h"

typedef struct Rep0610Globals80366158 {
    /* 0x0 */ u8 _pad0[8];
    /* 0x8 */ s32 unk8;
} Rep0610Globals80366158;
extern Rep0610Globals80366158 lbl_80366158;
extern u8 lbl_1_bss_3216;
extern u8 lbl_1_bss_5F78;
extern f32 lbl_1_bss_5F74;
extern s32 lbl_1_data_F4DC[3];
void fn_800AD038(s32 arg0);
void fn_800B9A9C(u8 enabled, f32 value);
struct TextureHeader;
void SetDisplayStateTexture(struct TextureHeader* tex, s32 texMap, s32 tlutName);

typedef struct Rep0610Linked {
    /* 0x0 */ u8 _pad0[4];
    /* 0x4 */ f32 value;
} Rep0610Linked;

typedef struct Rep0610Obj {
    /* 0x00 */ u8 _pad0[0x54];
    /* 0x54 */ f32 value;
    /* 0x58 */ u8 _pad58[2];
    /* 0x5A */ u8 active;
} Rep0610Obj;

typedef struct Rep0610Ring {
    /* 0x0 */ u8 _pad0[6];
    /* 0x6 */ u16 count;
} Rep0610Ring;

extern u8 lbl_1_bss_30B8;
extern u8 lbl_1_bss_3214;
extern u8 lbl_1_bss_3215;
extern s32 lbl_1_bss_3098;
extern Rep0610Linked* lbl_1_bss_67B8;

void fn_1_C5AC(void);
void fn_1_C9E0(void);
void fn_1_CB9C(void);
void fn_1_CC24(void);
void fn_1_CCC8(void);
void fn_1_CDC8(void);
void fn_1_D13C(void);
void fn_1_D2F0(void);
void fn_1_D300(void);
void fn_1_D4BC(void);
void fn_1_D590(void);
u8 fn_1_D638(void);
void fn_1_D650(void);
BOOL fn_1_D660(void);
void fn_1_D67C(u8 value);
void fn_1_D688(void);
void fn_1_D6B4(void);
s32 fn_1_D6E4(void);
void fn_1_D71C(void);
void fn_1_D7A4(void);
void fn_1_D8A0(void);
void fn_1_D9B8(void);
void fn_1_DE1C(void);
void fn_1_DF14(void);
void fn_1_E098(void);
void fn_1_E8D4(void);
void fn_1_E9F8(Rep0610Ring* ring, s32 index, s32 steps);
void fn_1_EA20(void);
void fn_1_ECF8(void);
void fn_1_F040(void);
void fn_1_F0D0(void);
void fn_1_F1D8(void);
void fn_1_F2F8(void);
void fn_1_F37C(void);
void fn_1_F50C(void);
void fn_1_F6E4(void);
void fn_1_F798(void);
void fn_1_FB98(void);
void fn_1_10044(void);
void fn_1_10458(void);
void fn_1_10560(void);
void fn_1_10670(void);
s32 fn_1_106A4(void);
void fn_1_106B4(void);
void fn_1_106C4(void);
void fn_1_1073C(void);
void fn_1_107B8(void);
void fn_1_10AA4(Rep0610Obj* obj, f32 value);
void fn_1_10ACC(void);
void fn_1_10CEC(void);
void fn_1_10E2C(void);
void fn_1_1125C(void);
void fn_1_116EC(struct TextureHeader* tex);
void fn_1_11714(void);
void fn_1_11C98(void);
void fn_1_11D00(void);
void fn_1_11F08(void);
void fn_1_121D4(void);
void fn_1_126CC(void);
void fn_1_12820(void);
void fn_1_129D0(void);
void fn_1_12F18(void);
void fn_1_12F8C(void);
void fn_1_131E4(void);
void fn_1_1347C(void);
void fn_1_135C0(void);
void fn_1_14710(void);
void fn_1_14888(void);
void fn_1_148CC(void);
void fn_1_14928(void);
void fn_1_1496C(void);
void fn_1_14FB8(void);
void fn_1_15170(void);
void fn_1_151F8(void);
void fn_1_1540C(void);
void fn_1_15760(void);
void fn_1_15CE0(void);
s32 fn_1_160D8(s8 a, s8 b);
void fn_1_160F8(void);
void fn_1_161D0(void);
void fn_1_1620C(void);
void fn_1_163FC(void);
void fn_1_16400(void);
void fn_1_1644C(void);
void fn_1_16558(void);
void fn_1_16590(void);
void fn_1_165E0(void);
void fn_1_168C8(void);
void fn_1_16978(void);
void fn_1_176EC(void);
void fn_1_1770C(void);
void fn_1_17954(void);
void fn_1_179CC(void);
void fn_1_17B5C(void);
void fn_1_17D90(void);

#endif // !__CHALLENGE_rep_0610_H_
