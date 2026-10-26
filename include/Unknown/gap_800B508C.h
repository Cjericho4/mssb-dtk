#ifndef __UNKNOWN_gap_800B508C_H_
#define __UNKNOWN_gap_800B508C_H_

#include "mssbTypes.h"
#include "C3/anim.h"
#include "C3/unktypes.h"
#include "C3/actor.h"

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
