#ifndef __CHALLENGE_rep_0610_H_
#define __CHALLENGE_rep_0610_H_

#include "mssbTypes.h"

typedef struct Rep0610Slot {
    /* 0x00 */ u8 _pad0[0x44];
    /* 0x44 */ u8 table;
    /* 0x45 */ u8 entry;
    /* 0x46 */ u8 _pad46[2];
} Rep0610Slot;
extern Rep0610Slot lbl_1_bss_6940[];
extern u8 lbl_1_bss_5F73;
extern u32 lbl_1_bss_5F6C;
#include "challenge/challenge.h"

typedef struct Rep0610Items {
    /* 0x0 */ u8 _pad0[4];
    /* 0x4 */ DrawingSceneItem* item4;
    /* 0x8 */ DrawingSceneItem* item8;
} Rep0610Items;

typedef struct Gap8000B9C8Texture Gap8000B9C8Texture;
typedef struct ChallengeState {
    /* 0x0000 */ u8 _pad0[0xC];
    /* 0x000C */ s32 unkC;
    /* 0x0010 */ u8 _pad10;
    /* 0x0011 */ u8 unk11;
    /* 0x0012 */ u8 _pad12[0xE];
    /* 0x0020 */ u8 blink;
    /* 0x0021 */ u8 _pad21[3];
    /* 0x0024 */ u32 unk_0x24;
    /* 0x0028 */ union { s32 selection; Gap8000B9C8Texture* texture; };
    /* 0x002C */ u8 _pad2C[0xC];
    /* 0x0038 */ s32 page;
    /* 0x003C */ u8 _pad3C[0x10];
    /* 0x004C */ s32 queued;
    /* 0x0050 */ u8 _pad50[0x154];
    /* 0x01A4 */ u8 phase;
    /* 0x01A5 */ u8 enabled;
    /* 0x01A6 */ u8 mode;
    /* 0x01A7 */ u8 _pad1A7[0x2D4B];
    /* 0x2EF2 */ u8 channel;
    /* 0x2EF3 */ u8 _pad2EF3[6];
    /* 0x2EF9 */ u8 unk2EF9;
    /* 0x2EFA */ u8 _pad2EFA[2];
    /* 0x2EFC */ u32 selectedBone;
    /* 0x2F00 */ u8 _pad2F00;
    /* 0x2F01 */ u8 unk2F01;
    /* 0x2F02 */ u8 _pad2F02;
    /* 0x2F03 */ u8 modelIndex;
    /* 0x2F04 */ u8 _pad2F04[0x170];
    /* 0x3074 */ Gap8000B9C8Texture* extraTexture;
    /* 0x3078 */ u8 _pad3078[0x6D0];
    /* 0x3748 */ Rep0610Items items;
} ChallengeState;
extern ChallengeState lbl_1_bss_3070;

typedef struct Rep0610Triple {
    /* 0x0 */ s32 values[3];
} Rep0610Triple;
extern s32 lbl_80108B90;
extern u16 lbl_1_data_F17C;
extern s32 lbl_1_data_F2A0;
extern Rep0610Triple lbl_1_data_F0A8;
extern Rep0610Triple lbl_1_data_F0BC;
extern const Vec lbl_1_rodata_7344;
extern const Vec lbl_1_rodata_731C;
extern u16 lbl_1_data_F56C;
extern u16 lbl_1_data_F56E;
void fn_800324EC(u16 arg0, s32 arg1, s32 arg2, s32* arg3);
void fn_80031CA4(Vec* arg0, Rep0610Triple* arg1);
void fn_8002955C(Vec* arg0, s32 arg1, s32* arg2);
#include "challenge/challenge.h"
extern u8 lbl_1_bss_5F71;
#include "UnknownHeaders.h"

typedef struct Rep0610Globals80366158 {
    /* 0x0 */ u8 _pad0[8];
    /* 0x8 */ s32 unk8;
} Rep0610Globals80366158;
extern Rep0610Globals80366158 lbl_80366158;

typedef struct Rep0610Camera68FC {
    /* 0x00 */ u8 _pad0[0x10];
    /* 0x10 */ Mtx view;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 _pad41[3];
} Rep0610Camera68FC;
extern Rep0610Camera68FC lbl_1_bss_68FC;
void LITXForm(struct MenusLight* light, Mtx view);
#include "Dolphin/GX/GXTransform.h"
typedef struct Rep0610Unk67E0 {
    /* 0x000 */ u8 _pad0[0x30];
    union {
        /* 0x030 */ u32 context[0x36];
        struct {
            u8 _pad30[0xC0];
            /* 0x0F0 */ s16 unk_0xF0;
            /* 0x0F2 */ s16 unk_0xF2;
            u8 _padF4[4];
            /* 0x0F8 */ f32 unk_0xF8;
            /* 0x0FC */ Vec target;
        };
    };
    /* 0x108 */ Vec pos;
    /* 0x114 */ u32 unk_0x114;
    /* 0x118 */ u8 useContext;
    /* 0x119 */ u8 _pad119[3];
} Rep0610Unk67E0;
extern Rep0610Unk67E0 lbl_1_bss_67E0;
typedef struct Rep0610Obj1073C {
    /* 0x00 */ u8 _pad0[0x34];
    /* 0x34 */ Vec pos;
} Rep0610Obj1073C;
typedef struct Rep0610UnkADC4 {
    /* 0x00 */ u8 _pad0[0x1C];
} Rep0610UnkADC4;
extern f32 lbl_1_data_ADC0;
extern Rep0610UnkADC4 lbl_1_data_ADC4;
void fn_80026134(s32 arg0, Vec* arg1);
void fn_80026130(s32 arg0, Rep0610UnkADC4* arg1, f32 arg2);
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
extern s16 lbl_1_data_A978[0x6E];
typedef struct Rep0610Ctrl5F7C {
    /* 0x000 */ HugeAnimCtrlObj* obj;
    /* 0x004 */ u8 _pad4[0x838];
} Rep0610Ctrl5F7C;
extern Rep0610Ctrl5F7C lbl_1_bss_5F7C;
typedef struct Rep0610Obj12F18 {
    /* 0x00 */ u8 _pad0[8];
    /* 0x08 */ Mtx mtx;
} Rep0610Obj12F18;
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
    /* 0x5B */ u8 _pad5B[0x15];
    /* 0x70 */ u32 context;
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
typedef struct ChallengeView {
    u32 header[2];
    Mtx matrix;
} ChallengeView;
typedef struct ChallengeViewState {
    u8 _pad0[0x50];
    f32 angle;
    u8 _pad54[4];
    Mtx matrix;
} ChallengeViewState;
extern ChallengeView lbl_1_data_F4F8[];
extern ChallengeViewState lbl_1_bss_30C0;
extern s32 lbl_1_bss_30BC;
extern u8 lbl_803CBBC0;
void fn_800A7D4C(s32 mode, ChallengeView* view);
void fn_1_CB9C(s32 reset);
void fn_1_CC24(void);
typedef struct ChallengeTiming {
    f32 time;
    f32 end;
} ChallengeTiming;
extern u8 lbl_1_bss_5F69;
extern f32 lbl_1_data_F568;
void fn_800385F0(ChallengeViewState* state, f32 a, f32 b, f32 c, f32 d);
void fn_80037AA0(ChallengeViewState* state, s32 mode, void (*callback)(s32), u16 id, ChallengeTiming* timing);
void fn_1_CCC8(void);
void fn_1_CDC8(void);
void fn_1_D13C(void);
void fn_1_D2F0(void);
void fn_1_D300(void);
void fn_1_D4BC(void);
void fn_1_D590(s32 a, s32 b, f32 frame);
void fn_8004B208(s32 a, s32 b, s32 channel);
u8 fn_1_D638(void);
void fn_1_D650(void);
BOOL fn_1_D660(void);
void fn_1_D67C(u8 value);
void fn_1_D688(void);
void fn_1_D6B4(void);
s32 fn_1_D6E4(void);
typedef struct ChallengeAnimation {
    f32 time;
    u8 _pad4[8];
    struct ChallengeAnimationData* data;
} ChallengeAnimation;
typedef struct ChallengeModelObject {
    u8 _pad0[0xE8];
    ChallengeAnimation* animation;
} ChallengeModelObject;
typedef struct ChallengeModel {
    u8 _pad0[6];
    u16 count;
    u8 _pad8[0x10];
    ChallengeModelObject** objects;
} ChallengeModel;
f32 fn_1_D71C(s32 index);
void fn_1_D7A4(void);
void fn_1_D8A0(void);
void fn_1_D9B8(void);
typedef struct ChallengeAnimChoice {
    s16 table;
    s16 entry;
    s16 value;
    s16 flags;
} ChallengeAnimChoice;
extern ChallengeAnimChoice lbl_1_bss_3218[9];
void fn_1_DE1C(void);
void fn_1_DF14(void);
void fn_1_E098(void);
void fn_1_E8D4(void);
void fn_1_E9F8(Rep0610Ring* ring, s32 index, s32 steps);
void fn_1_EA20(void);
void fn_1_ECF8(void);
void fn_1_F040(void);
typedef struct ChallengeCopyValues {
    Rep0610Triple base;
    s32 extra;
} ChallengeCopyValues;
extern ChallengeCopyValues* lbl_1_data_F278[3];
extern ChallengeCopyValues lbl_1_data_F284;
void fn_1_F0D0(void);
void fn_80030D88(VecXYZ* position, Vec* direction, ChallengeCopyValues* values, s32 count);
void fn_1_F1D8(void);
void fn_1_F2F8(void);
void fn_1_F37C(void);
void fn_1_F50C(void);
void fn_1_F6E4(void);
void fn_1_F798(Rep0610Triple* dst, Rep0610Triple* src, s32 size);
void fn_1_FB98(void);
void fn_1_10044(void);
void fn_1_10458(void);
void fn_1_10560(void);
void fn_1_10670(void);
s32 fn_1_106A4(void);
void fn_1_106B4(void);
void fn_1_106C4(void);
void fn_1_1073C(Rep0610Obj1073C* obj);
void fn_1_107B8(void);
void fn_1_10AA4(Rep0610Obj* obj, f32 value);
void fn_1_10ACC(void);
extern u8 lbl_1_data_ABA8;
void fn_800B2C88(ChallengeModel* model, u16 index, Mtx matrix);
void fn_1_10CEC(Rep0610Obj12F18* object);
void fn_1_10E2C(Mtx matrix, Mtx view, u32 x, u32 y, u32 z);
void fn_1_1125C(void);
void fn_1_116EC(struct TextureHeader* tex);
void fn_1_11714(void);
void fn_1_11C98(void);
void fn_1_11D00(void);
void fn_1_11F08(void);
void fn_1_121D4(void);
void fn_1_126CC(void);
void fn_1_12820(HugeAnimEntry68* entry, Mtx mtx);
void fn_1_129D0(void);
void fn_1_12F18(Rep0610Obj12F18* obj);
void fn_1_12F8C(void);
void fn_1_131E4(void);
void fn_1_1347C(void);
void fn_1_135C0(void);
void fn_1_14710(void);
void fn_1_14888(Rep0610Obj* obj);
void fn_800B9AA8(u32 context);
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
void fn_1_160F8(s32 delta);
void fn_1_161D0(void);
void fn_1_1620C(void);
void fn_1_163FC(void);
void fn_1_16400(s8 delta);
void fn_1_1644C(void);
s32 fn_1_16558(s32 table, s32 entry);
s32 fn_1_16590(void);
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
