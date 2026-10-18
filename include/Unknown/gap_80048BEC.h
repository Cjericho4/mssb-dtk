#ifndef __UNKNOWN_gap_80048BEC_H_
#define __UNKNOWN_gap_80048BEC_H_

#include "mssbTypes.h"
struct Gap80048BECObj;
typedef union Gap80048BECCallback {
    void (*integer)(s32 a, s32 b, s32 c);
    void (*actor)(struct Gap80048BECObj* obj, f32 value, s32 b, s32 c);
} Gap80048BECCallback;
extern Gap80048BECCallback lbl_800FBE64[];
struct Gap80048BECActor;
typedef struct Gap80048BECMenu {
    u8 _pad0[0x16];
    u16 id;
} Gap80048BECMenu;
extern Gap80048BECMenu lbl_803C5F74;
void fn_8000FE08(u16 id, s32 a, s32 b);
typedef struct Gap80048BECTiming {
    s32 unk0;
    s32 requested;
    s32 limit;
} Gap80048BECTiming;
extern s32 lbl_803CB874;
extern s32 lbl_803CB878;
extern s32 lbl_803CB83C[2];
extern s32 lbl_803CBD00;
extern s32 lbl_803CBD04;
extern s32 lbl_803CBD08;
extern s32 lbl_803CBD0C;
typedef struct Gap80048BECObj {
    u8 _pad0[0x3E];
    /* 0x3E */ u8 state;
    u8 _pad3F[0x1BB];
    u16 actorIndex; /* 0x1FA */
    u8 _pad1FC[0x56];
    s8 id; /* 0x252 */
} Gap80048BECObj;

extern s32 lbl_803CB848;
extern u32 lbl_803CBCE8;
extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD0C;

void fn_80048BEC(Gap80048BECTiming* timing);
void fn_80048C14(s32 value);
void fn_80048C1C(void);
void fn_80048C28(void);
extern s32 lbl_800FB4C8[35];
extern s32 lbl_800FB554[23];
void GXSetGPMetric(s32 perf0, s32 perf1);
void GXClearGPMetric(void);
u32 GXReadGP0Metric(void);
u32 GXReadGP1Metric(void);
void GXSetVCacheMetric(s32 attr);
void GXClearVCacheMetric(void);
void GXClearPixMetric(void);
void fn_80048D4C(void);
typedef struct Gap80048BECSelection {
    u8 unk0[0x2C];
    /* 0x2C */ u8 unk2C[0x2C];
    /* 0x58 */ u8 unk58[0x2C];
    u8 _pad84[0x4];
} Gap80048BECSelection;
extern Gap80048BECSelection lbl_802E4B28;
extern s32 lbl_803CB838;
void* memset(void* dst, int value, unsigned long count);
s32 fn_80048E00(s32 which, s32 value);
s32 fn_80048EA8(s32 index);
void startGameRelated(void);
void fn_80049220(void);
void fn_800494CC(void);
void possiblyTransferDataBetweenDifferentRels(void);
void fn_80049C80(void);
typedef struct Gap80048BECSettings {
    u8 _pad0[0x7];
    /* 0x07 */ u8 mode;
    u8 _pad8[0x50];
} Gap80048BECSettings;
extern Gap80048BECSettings g_d_GameSettings;
typedef struct Gap80048BECQuad {
    u8 a;
    u8 b;
    u8 c;
    u8 d;
} Gap80048BECQuad;
typedef struct Gap80048BECState {
    u8 _pad0[0x2C];
    /* 0x2C */ u16 unk2C;
    u8 _pad2E[0x8];
    /* 0x36 */ u8 enabled;
    u8 _pad37[0x4];
    /* 0x3B */ u8 groupA[5];
    /* 0x40 */ u8 groupB[5];
    /* 0x45 */ Gap80048BECQuad quadsA[4];
    /* 0x55 */ Gap80048BECQuad quadsB[4];
    u8 _pad65[0xB];
} Gap80048BECState;
extern Gap80048BECState lbl_803C5F04;
void fn_80049D3C(void);
void fn_80049D8C(void);
void fn_8004A0FC(void);
void fn_8004A1BC(void);
typedef struct Gap80048BECScene {
    u8 _pad0[0x4];
    /* 0x4 */ u16 step;
} Gap80048BECScene;
extern Gap80048BECScene* lbl_803CBBCC;
void fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
void fn_8004A2BC(void);
BOOL fn_8004A328(Gap80048BECObj* obj);
void fn_8004A34C(void);
void fn_8004A5B8(void);
void fn_8004A7D0(void);
void fn_8004A9E0(void);
void Set_803cb848(s32 value);
s32 fn_8004ABE0(void);
s32 fn_8004ABE8(BOOL clear);
void fn_8004AC00(void);
s32 fn_8004ACC4(BOOL clear);
s32 fn_8004ACDC(BOOL clear);
void fn_8004ACF4(Gap80048BECObj* obj, f32 value, s32 b, s32 c);
void fn_8004AD54(void);
void fn_8004AE18(void);
void fn_8004AFA8(void);
void fn_8004B1B8(s32 value);
void fn_8004B1C0(s32 index, s32 a, s32 b, s32 c);
extern s8 lbl_800FBDEC[0x78];
void fn_8004B208(s32 a, s32 index, s32 c);
void fn_8004B270(void);
void fn_8004B284(void);
void fn_8004B6EC(void);
s32 fn_8004B7B4(Gap80048BECObj* obj, struct Gap80048BECActor** actor);
void fn_8004B7F4(void);
void fn_8004BAEC(void);
void fn_8004BD6C(void);
void fn_8004BEB0(void);
typedef struct Gap80048BECEffectParams {
    /* 0x00 */ s32 unk0;
    u8 _pad4[0x8];
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    u8 _pad14[0x2C];
    /* 0x40 */ u32 color;
    u8 _pad44[0xC];
} Gap80048BECEffectParams;
typedef struct Gap80048BECRGB {
    u8 r;
    u8 g;
    u8 b;
} Gap80048BECRGB;
extern Gap80048BECRGB lbl_803CB864[4];
typedef struct Gap80048BECEffectTarget Gap80048BECEffectTarget;
extern Gap80048BECEffectParams* lbl_803CB860;
void* memcpy(void* dst, const void* src, unsigned long n);
void fn_80031CA4(Gap80048BECEffectTarget* target, Gap80048BECEffectParams* params);
void fn_8004C094(Gap80048BECEffectTarget* target);
void fn_8004C108(Gap80048BECEffectTarget* target, u8 index);
void fn_8004C19C(void);
void fn_8004C510(void);
void fn_8004C5F8(void);
void fn_8004C9FC(void);
void fn_8004CA08(s32 value);
void fn_8004CA14(s32 a, s32 b);

typedef struct Gap80048BECActor Gap80048BECActor;
s32 fn_800B2BA8(Gap80048BECActor* actor, u16 index, Gap80048BECActor* other, u16 otherIndex);

#endif // !__UNKNOWN_gap_80048BEC_H_
