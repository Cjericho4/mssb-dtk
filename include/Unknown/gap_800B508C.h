#ifndef __UNKNOWN_gap_800B508C_H_
#define __UNKNOWN_gap_800B508C_H_

#include "mssbTypes.h"
typedef struct Gap800B508CTrack {
    u8 _pad0[0xF];
    u8 flags;
} Gap800B508CTrack;
typedef struct Gap800B508CAnimation {
    f32 time;
    f32 previousTime;
    u32 unk8;
    Gap800B508CTrack* track;
    u8* data;
    u16 frame;
    u8 flags;
} Gap800B508CAnimation;

void ANIMGet(void);
void Squad(void);
void GetData(void);
void DoTranslationAnimation(void);
void DoScaleAnimation(void);
void DoEulerAnimation(void);
void DoQuatAnimation(void);
void ANIMTick(void);
void ANIMBind(Gap800B508CAnimation* anim, u8* data, Gap800B508CTrack* track, f32 time);
void ACTSetBoneTrack(void);

#endif // !__UNKNOWN_gap_800B508C_H_
