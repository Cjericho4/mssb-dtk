#include "Unknown/gap_800B508C.h"

// .text:0x800B508C size:0xE0
// Relocates a freshly loaded bank in place: every file offset (user data, sequence table, names,
// track arrays, key arrays, key settings and interpolation payloads) becomes a pointer.
void ANIMGet(ANIMBank* bank) {
    u32 i;
    ANIMSequences* sequence;
    struct ANIMAnimTrack* track;
    KeyFrame* keys;
    KeyFrame* key;

    if (bank->userDataSize != 0 && bank->userData != NULL) {
        bank->userData = (void*)((u32)bank->userData + (u32)bank);
    }
    sequence = (ANIMSequences*)(bank + 1);
    track = (struct ANIMAnimTrack*)(sequence + bank->numSequences);
    keys = (KeyFrame*)(track + bank->numTracks);
    bank->animSequences = (ANIMSequences*)((u32)bank->animSequences + (u32)bank);
    for (i = 0; i < bank->numSequences; i++, sequence++) {
        sequence->sequenceName = (char*)((u32)bank + (u32)sequence->sequenceName);
        sequence->trackArray = (struct ANIMAnimTrack*)((u32)bank + (u32)sequence->trackArray);
    }
    for (i = 0; i < bank->numTracks; i++, track++) {
        track->keyFrames = (KeyFrame*)((u32)bank + (u32)track->keyFrames);
    }
    key = keys;
    for (i = 0; i < bank->numKeyFrames; i++, key++) {
        key->setting = (char*)((u32)bank + (u32)key->setting);
        key->interpolation = (char*)((u32)bank + (u32)key->interpolation);
    }
}

#pragma dont_inline on
// .text:0x800B516C size:0x4A0
// Spherical cubic blend: slerp(q0,q1,t) and slerp(a,b,t) are slerped again by 2t(1-t) into out.
void Squad(Quaternion* q0, Quaternion* a, Quaternion* b, Quaternion* q1, Quaternion* out, f32 t) {
    return;
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
