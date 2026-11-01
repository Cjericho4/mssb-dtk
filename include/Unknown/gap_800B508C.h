#ifndef __UNKNOWN_gap_800B508C_H_
#define __UNKNOWN_gap_800B508C_H_

#include "mssbTypes.h"
#include "C3/anim.h"
#include "C3/unktypes.h"
#include "C3/actor.h"

typedef struct AnimationEase {
    s16 incoming;
    s16 outgoing;
} AnimationEase;
STATIC_ASSERT(sizeof(AnimationEase) == 4);

typedef struct AnimationQuatAux {
    s16 incoming[4];
    s16 outgoing[4];
    AnimationEase ease;
} AnimationQuatAux;
STATIC_ASSERT(sizeof(AnimationQuatAux) == 0x14);

/* Partial view of the animation decoder's read-only diagnostic strings. */
typedef struct AnimationDiagnostics {
    char _pad0[0x30];
    char file[0xC];
    char unsupportedInterpolation[0x48];
    char unsupportedEuler[0x74];
    char unsupportedQuat[1];
} AnimationDiagnostics;
extern AnimationDiagnostics lbl_800E7D58;

extern f32 lbl_803CBB48;
extern f32 lbl_803CBB4C;
extern u8 lbl_803CBB50;
extern u8 lbl_803CBB51;
extern char lbl_800E7D88[];
extern char lbl_800E7D94[];
extern char lbl_800E7E50[];

void Squad(Quaternion* q0, Quaternion* a, Quaternion* b, Quaternion* q1, Quaternion* out, f32 t);
void GetData(u8 type, void* src, f32* dst, u8 count, f32 scale);
void DoTranslationAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next);
void DoScaleAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next, u8 mode);
void DoEulerAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next);
void DoQuatAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next);
void ACTSetBoneTrack(ActBone* bone, struct ANIMAnimTrack* track, f32 time, s32 blend);
void* _OSAllocFromHeap(s32 alignment, u32 size);
void CTRL_SetQuatUnk(Control* control, f32 x, f32 y, f32 z, f32 w);
void CTRL_GetQuatUnk(const Control* control, f32* x, f32* y, f32* z, f32* w);

#endif // !__UNKNOWN_gap_800B508C_H_
