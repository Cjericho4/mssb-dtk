#ifndef __CHALLENGE_rep_74A0_H_
#define __CHALLENGE_rep_74A0_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"

typedef struct Rep74A0State {
    /* 0x00 */ u8 _pad0[0x10];
    Mtx lightMatrix;
    /* 0x40 */ u8 flags[0x18];
} Rep74A0State;
extern Rep74A0State lbl_1_bss_69FC;

typedef struct Rep74A0Obj {
    /* 0x00 */ u8 _pad0[0x70];
    /* 0x70 */ u32 context;
} Rep74A0Obj;
void fn_800B9AA8(u32 context);

void fn_1_182C0(void);
void fn_1_1857C(void);
typedef struct ChallengeOrbit {
    u32 header;
    Vec origin;
    Vec position;
    Vec rotation;
    Vec angularVelocity;
    u8 _pad34[12];
    GXColor colors[2];
    u16 _pad48;
    s16 index;
} ChallengeOrbit;
typedef struct ChallengeOrbitConfig {
    s32 unk0;
    s32 radius;
    s32 angularSpeed;
    u8 _padC[8];
    s32 colorMinimum;
} ChallengeOrbitConfig;
extern ChallengeOrbitConfig lbl_1_data_FB24;
void fn_1_18E04(ChallengeOrbit* orbit, f32 angle);
void fn_1_18EE4(ChallengeOrbit* orbit);
void fn_1_191DC(void);
void fn_1_1957C(void);
void fn_1_1994C(void);
s32 fn_1_19D1C(u32 flags);
typedef struct ChallengeRenderModel ChallengeRenderModel;
typedef struct ChallengeRenderObject {
    u8 _pad0[0x14];
    ChallengeRenderModel* model;
    u8 _pad18[0x5C];
    struct ChallengeRenderObject* children;
    u8 _pad78[0x74];
    MtxPtr world;
    u8 _padF0[0x10];
    struct ChallengeRenderObject* next;
} ChallengeRenderObject;
typedef struct ChallengeRenderTask {
    ChallengeRenderObject* object;
    u32 unk4;
    void (*callback)(struct ChallengeRenderTask* task);
} ChallengeRenderTask;
void fn_800B2D5C(ChallengeRenderObject* object);
void GXInvalidateVtxCache(void);
void DOSetWorldMatrix(ChallengeRenderModel* model, MtxPtr world);
void fn_1_19D60(ChallengeRenderModel* model, s32 mode);
void fn_1_1A1EC(ChallengeRenderTask* task, s32 mode);
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
void fn_1_1A290(HugeAnimEntry68* entries, s32 mode);
void fn_1_1A3B4(void);
typedef struct ChallengeModelGroup {
    u8 _pad0[6];
    u16 count;
} ChallengeModelGroup;
typedef struct ChallengeSelection {
    u16 selected;
    u8 group;
    u8 _pad3[0x189];
    Mtx matrix;
} ChallengeSelection;
extern ChallengeSelection lbl_1_bss_69F0;
void fn_800B2C88(ChallengeModelGroup* model, u16 index, Mtx matrix);
void fn_1_1A774(void);
void fn_1_1A850(Mtx matrix, Mtx view, s32 r, s32 g, s32 b, s32 a);
void fn_1_1ADA4(void);
void fn_1_1B038(void);
void fn_1_1B0FC(void);
void fn_1_1B2C8(void);
void fn_1_1B424(void);
void fn_1_1B6BC(void);
void fn_1_1B7DC(void);
void fn_1_1C3CC(void);
void fn_1_1C8C0(void);
void fn_1_1CBE4(void);
void fn_1_1D0E8(Rep74A0Obj* obj);
void fn_1_1D10C(void);
void fn_1_1D110(void);
void fn_1_1D450(void);
void fn_1_1D470(void);
void fn_1_1D514(void);

#endif // !__CHALLENGE_rep_74A0_H_
