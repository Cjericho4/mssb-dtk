#include "Unknown/gap_800B508C.h"

// .text:0x800B508C size:0xE0
void ANIMGet(void) {
    return;
}

// .text:0x800B516C size:0x4A0
void Squad(void) {
    return;
}

// .text:0x800B560C size:0x79C
void GetData(void) {
    return;
}

// .text:0x800B5DA8 size:0x634
void DoTranslationAnimation(void) {
    return;
}

// .text:0x800B63DC size:0xA30
void DoScaleAnimation(void) {
    return;
}

// .text:0x800B6E0C size:0x3B4
void DoEulerAnimation(void) {
    return;
}

// .text:0x800B71C0 size:0x558
void DoQuatAnimation(void) {
    return;
}

// .text:0x800B7718 size:0x288
void ANIMTick(void) {
    return;
}

// .text:0x800B79A0 size:0x30
void ANIMBind(Gap800B508CAnimation* anim, u8* data, Gap800B508CTrack* track, f32 time) {
    if (track == NULL) return;
    *data = 0;
    anim->data = data;
    anim->track = track;
    anim->time = time;
    anim->previousTime = time;
    anim->flags = track->flags;
    anim->frame = 0;
}

// .text:0x800B79D0 size:0x36C
void ACTSetBoneTrack(void) {
    return;
}
