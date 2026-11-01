#include "Unknown/gap_800B508C.h"
#include "math.h"

// .text:0x800B508C size:0xE0
// Relocates a freshly loaded bank in place: every file offset (user data, sequence table, names,
// track arrays, key arrays, key settings and interpolation payloads) becomes a pointer.
void ANIMGet(ANIMBank* bank) {
    ANIMSequences* sequence;
    struct ANIMAnimTrack* track;
    u32 i;
    KeyFrame* keys;

    if (bank->userDataSize != 0 && bank->userData != NULL) {
        bank->userData = (void*)((u32)bank->userData + (u32)bank);
    }
    sequence = (ANIMSequences*)(bank + 1);
    track = (struct ANIMAnimTrack*)(sequence + bank->numSequences);
    keys = (KeyFrame*)(track + bank->numTracks);
    bank->animSequences = (ANIMSequences*)((u32)bank->animSequences + (u32)bank);
    for (i = 0; i < bank->numSequences; i++) {
        sequence[i].sequenceName = (char*)((u32)bank + (u32)sequence[i].sequenceName);
        sequence[i].trackArray = (struct ANIMAnimTrack*)((u32)bank + (u32)sequence[i].trackArray);
    }
    for (i = 0; i < bank->numTracks; i++) {
        track[i].keyFrames = (KeyFrame*)((u32)bank + (u32)track[i].keyFrames);
    }
    for (i = 0; i < bank->numKeyFrames; i++) {
        keys[i].setting = (char*)((u32)bank + (u32)keys[i].setting);
        keys[i].interpolation = (char*)((u32)bank + (u32)keys[i].interpolation);
    }
}

#pragma dont_inline on
// .text:0x800B516C size:0x4A0
// Spherical cubic blend: slerp(q0,q1,t) and slerp(a,b,t) are slerped again by 2t(1-t) into out.
void Squad(Quaternion *q0, Quaternion *a, Quaternion *b, Quaternion *q1, Quaternion *out, f32 t) {
    f32 dotEnds;
    f32 dotControls;
    f32 dotBlend;
    f32 antipodalSecondBlend;
    f32 angleEnds;
    f32 reciprocalEnds;
    f32 antipodalStepEnds;
    f32 controlZ;
    f32 angleControls;
    f32 reciprocalControls;
    f32 angleBlend;
    f32 antipodalFirstBlend;
    f32 stepEnds;
    f32 controlW;
    f32 stepControls;
    f32 reciprocalBlend;
    f32 antipodalStepBlend;
    f32 antipodalStepControls;
    f32 stepBlend;
    f32 endY;
    f32 controlY;
    f32 endX;
    f32 controlX;
    f32 endW;
    f32 endZ;
    f32 antipodalFirstEnds;
    f32 antipodalFirstControls;
    f32 sineEnds;
    f32 sineControls;
    f32 sineBlend;
    f32 perpendicularZ;
    f32 blend;
    f32 antipodalSecondEnds;
    f32 antipodalSecondControls;
    f32 firstWeightBlend;
    f32 firstWeightControls;
    f32 controlsZ;
    f32 controlsY;
    f32 endsW;
    f32 endsZ;
    f32 endsY;
    f32 endsX;
    f32 firstWeightEnds;
    f32 controlsW;
    f32 controlsX;
    f32 secondWeightBlend;
    f32 secondWeightEnds;
    f32 secondWeightControls;

    endY = q1->y;
    firstWeightControls = 1.0f - t;
    endX = q1->x;
    endZ = q1->z;
    endW = q1->w;
    dotEnds = (q0->w * endW) + ((q0->z * endZ) + ((q0->x * endX) + (q0->y * endY)));
    blend = 2.0f * firstWeightControls * t;
    if ((1.0f + dotEnds) > 0.000001f) {
        if ((1.0f - dotEnds) > 0.000001f) {
            angleEnds = (f32) acos(dotEnds);
            stepEnds = t * angleEnds;
            sineEnds = (f32) sin(angleEnds);
            reciprocalEnds = 1.0f / sineEnds;
            firstWeightEnds = reciprocalEnds * (f32) sin(angleEnds - stepEnds);
            secondWeightEnds = reciprocalEnds * (f32) sin(stepEnds);
        } else {
            firstWeightEnds = firstWeightControls;
            secondWeightEnds = t;
        }
        endsX = (firstWeightEnds * q0->x) + (secondWeightEnds * q1->x);
        endsY = (firstWeightEnds * q0->y) + (secondWeightEnds * q1->y);
        endsZ = (firstWeightEnds * q0->z) + (secondWeightEnds * q1->z);
        endsW = (firstWeightEnds * q0->w) + (secondWeightEnds * q1->w);
    } else {
        antipodalStepEnds = 1.5707963705062866f * t;
        antipodalFirstEnds = (f32) sin(1.5707963705062866f - antipodalStepEnds);
        antipodalSecondEnds = (f32) sin(antipodalStepEnds);
        endsX = (antipodalFirstEnds * q0->x) + (antipodalSecondEnds * -endY);
        endsY = (antipodalFirstEnds * q0->y) + (antipodalSecondEnds * endX);
        endsZ = (antipodalFirstEnds * q0->z) + (antipodalSecondEnds * -endW);
        endsW = (antipodalFirstEnds * q0->w) + (antipodalSecondEnds * endZ);
    }
    controlY = b->y;
    controlX = b->x;
    controlZ = b->z;
    controlW = b->w;
    dotControls = (a->w * controlW) + ((a->z * controlZ) + ((a->x * controlX) + (a->y * controlY)));
    if ((1.0f + dotControls) > 0.000001f) {
        if ((1.0f - dotControls) > 0.000001f) {
            angleControls = (f32) acos(dotControls);
            stepControls = t * angleControls;
            sineControls = (f32) sin(angleControls);
            reciprocalControls = 1.0f / sineControls;
            firstWeightControls = reciprocalControls * (f32) sin(angleControls - stepControls);
            secondWeightControls = reciprocalControls * (f32) sin(stepControls);
        } else {
            secondWeightControls = t;
        }
        controlsX = (firstWeightControls * a->x) + (secondWeightControls * b->x);
        controlsY = (firstWeightControls * a->y) + (secondWeightControls * b->y);
        controlsZ = (firstWeightControls * a->z) + (secondWeightControls * b->z);
        controlsW = (firstWeightControls * a->w) + (secondWeightControls * b->w);
    } else {
        antipodalStepControls = 1.5707963705062866f * t;
        antipodalFirstControls = (f32) sin(1.5707963705062866f - antipodalStepControls);
        antipodalSecondControls = (f32) sin(antipodalStepControls);
        controlsX = (antipodalFirstControls * a->x) + (antipodalSecondControls * -controlY);
        controlsY = (antipodalFirstControls * a->y) + (antipodalSecondControls * controlX);
        controlsZ = (antipodalFirstControls * a->z) + (antipodalSecondControls * -controlW);
        controlsW = (antipodalFirstControls * a->w) + (antipodalSecondControls * controlZ);
    }
    dotBlend = (endsW * controlsW) + ((endsZ * controlsZ) + ((endsX * controlsX) + (endsY * controlsY)));
    if ((1.0f + dotBlend) > 0.000001f) {
        if ((1.0f - dotBlend) > 0.000001f) {
            angleBlend = (f32) acos(dotBlend);
            stepBlend = blend * angleBlend;
            sineBlend = (f32) sin(angleBlend);
            reciprocalBlend = 1.0f / sineBlend;
            firstWeightBlend = reciprocalBlend * (f32) sin(angleBlend - stepBlend);
            secondWeightBlend = reciprocalBlend * (f32) sin(stepBlend);
        } else {
            firstWeightBlend = 1.0f - blend;
            secondWeightBlend = blend;
        }
        out->x = (firstWeightBlend * endsX) + (secondWeightBlend * controlsX);
        out->y = (firstWeightBlend * endsY) + (secondWeightBlend * controlsY);
        out->z = (firstWeightBlend * endsZ) + (secondWeightBlend * controlsZ);
        out->w = (firstWeightBlend * endsW) + (secondWeightBlend * controlsW);
        return;
    }
    perpendicularZ = -controlsW;
    antipodalStepBlend = 1.5707963705062866f * blend;
    out->x = -controlsY;
    out->y = controlsX;
    out->z = perpendicularZ;
    out->w = controlsZ;
    antipodalFirstBlend = (f32) sin(1.5707963705062866f - antipodalStepBlend);
    antipodalSecondBlend = (f32) sin(antipodalStepBlend);
    out->x = (antipodalFirstBlend * endsX) + (antipodalSecondBlend * out->x);
    out->y = (antipodalFirstBlend * endsY) + (antipodalSecondBlend * out->y);
    out->z = (antipodalFirstBlend * endsZ) + (antipodalSecondBlend * out->z);
    out->w = (antipodalFirstBlend * endsW) + (antipodalSecondBlend * out->w);
}

// .text:0x800B560C size:0x79C
// Decodes `count` quantized values (type: 0 u8, 1 s8, 2 u16, 3 s16, 4 f32) into floats, times `scale`.
void GetData(u8 type, void* src, f32* dst, u8 count, f32 scale) {
    return;
}

// .text:0x800B5DA8 size:0x634
void DoTranslationAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    return;
}

// .text:0x800B63DC size:0xA30
void DoScaleAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next, u8 mode) {
    return;
}

// .text:0x800B6E0C size:0x3B4
void DoEulerAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    return;
}

// .text:0x800B71C0 size:0x558
void DoQuatAnimation(ANIMPipe* pipe, KeyFrame* current, KeyFrame* next) {
    return;
}
#pragma dont_inline off

// .text:0x800B7718 size:0x288
// Samples the bound track at pipe->time into the bone control, then steps time by speed
// (forwards or backwards), wrapping at the track duration when looping, clamping otherwise.
void ANIMTick(ANIMPipe* pipe, u8 mode) {
    KeyFrame* current;
    KeyFrame* next;
    KeyFrame* key;
    u8 type;
    f32 scale;

    if (pipe == NULL || pipe->currentTrack == NULL) return;
    ANIMGetKeyFrameFromTrack(pipe->currentTrack, pipe->time, &current, &next, &pipe->keyIndex);
    type = pipe->currentTrack->animType;
    if (type & ANIM_TYPE_MTX) {
        scale = 1.0f / (f32)(1 << (pipe->currentTrack->quantizeInfo & 0xF));
        key = current;
        ((f32*)key->setting)[0] *= scale;
        ((f32*)key->setting)[1] *= scale;
        ((f32*)key->setting)[2] *= scale;
        ((f32*)key->setting)[3] *= scale;
        ((f32*)key->setting)[4] *= scale;
        ((f32*)key->setting)[5] *= scale;
        ((f32*)key->setting)[6] *= scale;
        ((f32*)key->setting)[7] *= scale;
        ((f32*)key->setting)[8] *= scale;
        ((f32*)key->setting)[9] *= scale;
        ((f32*)key->setting)[10] *= scale;
        ((f32*)key->setting)[11] *= scale;
        CTRLSetMatrix(pipe->control, (MtxPtr)key->setting);
        return;
    }
    if (type & ANIM_TYPE_SCALE) {
        DoScaleAnimation(pipe, current, next, mode);
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_ROT_QUAT) {
        DoQuatAnimation(pipe, current, next);
    } else if (pipe->currentTrack->animType & ANIM_TYPE_ROT_EULER) {
        DoEulerAnimation(pipe, current, next);
    }
    if (pipe->currentTrack->animType & ANIM_TYPE_TRANS) {
        DoTranslationAnimation(pipe, current, next);
    }
    pipe->previousTime = pipe->time;
    if (pipe->forward == 1) {
        pipe->time += pipe->speed;
        if (pipe->time > pipe->currentTrack->animTime) {
            if (pipe->loop) {
                pipe->time -= pipe->currentTrack->animTime;
            } else {
                pipe->time = pipe->currentTrack->animTime;
            }
        }
    } else {
        pipe->time -= pipe->speed;
        if (pipe->time < 0.0f) {
            if (pipe->loop) {
                pipe->time += pipe->currentTrack->animTime;
            } else {
                pipe->time = 0.0f;
            }
        }
    }
}

#pragma dont_inline on
// .text:0x800B79A0 size:0x30
// Attaches a track to a pipe: clears the target control, rewinds to `time` and resets the key cache.
void ANIMBind(ANIMPipe* pipe, Control* control, struct ANIMAnimTrack* track, f32 time) {
    if (track == NULL) return;
    control->type = 0;
    pipe->control = control;
    pipe->currentTrack = track;
    pipe->time = time;
    pipe->previousTime = time;
    pipe->replaceHierarchyCtrl = track->replaceHierarchyCtrl;
    pipe->keyIndex = 0;
}
#pragma dont_inline off

// .text:0x800B79D0 size:0x36C
// Binds `track` to a bone (NULL unbinds). With `blend` the current pose is saved as the blend
// source; channels the track does not animate are copied from the bone's rest-pose control.
void ACTSetBoneTrack(ActBone* bone, struct ANIMAnimTrack* track, f32 time, s32 blend) {
    u8 restType;
    f32 rest[4]; /* x, y, z, w of the rest-pose channel being copied */

    if (track == NULL) {
        if (bone->animPipe != NULL && bone->animPipe->control != NULL) {
            bone->animPipe->control->type = 0;
            bone->animPipe->currentTrack = NULL;
        }
        return;
    }
    if (bone->animPipe == NULL) {
        bone->animPipe = _OSAllocFromHeap(0x20, sizeof(ANIMPipe));
        bone->animPipe->time = 0.0f;
        bone->animPipe->previousTime = 0.0f;
        bone->animPipe->speed = 1.0f;
        bone->animPipe->currentTrack = NULL;
        bone->animPipe->control = NULL;
        bone->animPipe->replaceHierarchyCtrl = 0;
        bone->animPipe->forward = 1;
        bone->animPipe->loop = 1;
    }
    bone->animPipe->keyIndex = 0;
    if (blend != 0) {
        if (bone->animPipe->control != NULL) {
            if (bone->animPipe->control->type != 0) {
                bone->blendFromCtrl = bone->animationCtrl;
            } else {
                bone->blendFromCtrl = bone->orientationCtrl;
            }
        } else {
            bone->blendFromCtrl = bone->animationCtrl;
        }
    }
    ANIMBind(bone->animPipe, &bone->animationCtrl.control, track, time);
    if (bone->holdTranslation != 0) {
        bone->animPipe->currentTrack->interpolationType &= ~3;
    }
    restType = bone->orientationCtrl.control.type;
    if ((restType & CTRL_TRANS) && !(track->animType & ANIM_TYPE_TRANS)) {
        CTRLGetTranslation(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetTranslation(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
    }
    if ((restType & CTRL_SCALE) && !(track->animType & ANIM_TYPE_SCALE)) {
        CTRLGetScale(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetScale(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
        if ((restType & CTRL_SCALE_QUAT) && !(track->animType & ANIM_TYPE_SCALE_QUAT)) {
            CTRL_GetQuatUnk(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2], &rest[3]);
        } else {
            rest[0] = 0.0f;
            rest[1] = 0.0f;
            rest[2] = 0.0f;
            rest[3] = 1.0f;
        }
        CTRL_SetQuatUnk(&bone->animationCtrl.control, rest[0], rest[1], rest[2], rest[3]);
    }
    if ((restType & CTRL_ROT_EULER) && !(track->animType & ANIM_TYPE_ROT_EULER)) {
        CTRLGetRotation(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2]);
        CTRLSetRotation(&bone->animationCtrl.control, rest[0], rest[1], rest[2]);
    } else if ((restType & CTRL_ROT_QUAT) && !(track->animType & ANIM_TYPE_ROT_QUAT)) {
        CTRLGetQuat(&bone->orientationCtrl.control, &rest[0], &rest[1], &rest[2], &rest[3]);
        CTRLSetQuat(&bone->animationCtrl.control, rest[0], rest[1], rest[2], rest[3]);
    }
    if (blend == 0) {
        bone->blendFromCtrl = bone->animationCtrl;
    }
}
