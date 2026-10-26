#include "Unknown/gap_800B508C.h"

// .text:0x800B508C size:0xE0
// Relocates a freshly loaded bank in place: every file offset (user data, sequence table, names,
// track arrays, key arrays, key settings and interpolation payloads) becomes a pointer.
void ANIMGet(ANIMBank* bank) {
    ANIMSequences* sequence;
    struct ANIMAnimTrack* track;
    KeyFrame* key;
    u32 i;

    if (bank->userDataSize != 0 && bank->userData != NULL) {
        bank->userData = (u8*)bank + (u32)bank->userData;
    }
    sequence = (ANIMSequences*)(bank + 1);
    track = (struct ANIMAnimTrack*)(sequence + bank->numSequences);
    key = (KeyFrame*)(track + bank->numTracks);
    bank->animSequences = (ANIMSequences*)((u8*)bank + (u32)bank->animSequences);
    for (i = 0; i < bank->numSequences; i++, sequence++) {
        sequence->sequenceName = (char*)bank + (u32)sequence->sequenceName;
        sequence->trackArray = (struct ANIMAnimTrack*)((u8*)bank + (u32)sequence->trackArray);
    }
    for (i = 0; i < bank->numTracks; i++, track++) {
        track->keyFrames = (KeyFrame*)((u8*)bank + (u32)track->keyFrames);
    }
    for (i = 0; i < bank->numKeyFrames; i++, key++) {
        key->setting = (char*)bank + (u32)key->setting;
        key->interpolation = (char*)bank + (u32)key->interpolation;
    }
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

// .text:0x800B7718 size:0x288
// Samples the bound track at pipe->time into the bone control, then steps time by speed
// (forwards or backwards), wrapping at the track duration when looping, clamping otherwise.
void ANIMTick(ANIMPipe* pipe, u8 mode) {
    KeyFrame* current;
    KeyFrame* next;
    struct ANIMAnimTrack* track;
    f32* m;
    f32 scale;

    if (pipe == NULL) return;
    if (pipe->currentTrack == NULL) return;
    ANIMGetKeyFrameFromTrack(pipe->currentTrack, pipe->time, &current, &next, &pipe->keyIndex);
    track = pipe->currentTrack;
    if (track->animType & ANIM_TYPE_MTX) {
        scale = 1.0f / (f32)(1 << (track->quantizeInfo & 0xF));
        m = (f32*)current->setting;
        m[0] *= scale;
        m[1] *= scale;
        m[2] *= scale;
        m[3] *= scale;
        m[4] *= scale;
        m[5] *= scale;
        m[6] *= scale;
        m[7] *= scale;
        m[8] *= scale;
        m[9] *= scale;
        m[10] *= scale;
        m[11] *= scale;
        CTRLSetMatrix(pipe->control, (MtxPtr)current->setting);
        return;
    }
    if (track->animType & ANIM_TYPE_SCALE) {
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

// .text:0x800B79D0 size:0x36C
// Binds `track` to a bone (NULL unbinds). With `blend` the current pose is saved as the blend
// source; channels the track does not animate are copied from the bone's rest-pose control.
void ACTSetBoneTrack(ActBone* bone, struct ANIMAnimTrack* track, s32 blend, f32 time) {
    ANIMPipe* pipe;
    u8 restType;
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    if (track == NULL) {
        if (bone->animPipe != NULL && bone->animPipe->control != NULL) {
            bone->animPipe->control->type = 0;
            bone->animPipe->currentTrack = NULL;
        }
        return;
    }
    if (bone->animPipe == NULL) {
        bone->animPipe = _OSAllocFromHeap(0x20, sizeof(ANIMPipe));
        pipe = bone->animPipe;
        pipe->time = 0.0f;
        pipe->previousTime = 0.0f;
        pipe->speed = 1.0f;
        pipe->currentTrack = NULL;
        pipe->control = NULL;
        pipe->replaceHierarchyCtrl = 0;
        pipe->forward = 1;
        pipe->loop = 1;
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
        CTRLGetTranslation(&bone->orientationCtrl.control, &x, &y, &z);
        CTRLSetTranslation(&bone->animationCtrl.control, x, y, z);
    }
    if ((restType & CTRL_SCALE) && !(track->animType & ANIM_TYPE_SCALE)) {
        CTRLGetScale(&bone->orientationCtrl.control, &x, &y, &z);
        CTRLSetScale(&bone->animationCtrl.control, x, y, z);
        if ((restType & CTRL_SCALE_QUAT) && !(track->animType & ANIM_TYPE_SCALE_QUAT)) {
            CTRL_GetQuatUnk(&bone->orientationCtrl.control, &x, &y, &z, &w);
        } else {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            w = 1.0f;
        }
        CTRL_SetQuatUnk(&bone->animationCtrl.control, x, y, z, w);
    }
    if ((restType & CTRL_ROT_EULER) && !(track->animType & ANIM_TYPE_ROT_EULER)) {
        CTRLGetRotation(&bone->orientationCtrl.control, &x, &y, &z);
        CTRLSetRotation(&bone->animationCtrl.control, x, y, z);
    } else if ((restType & CTRL_ROT_QUAT) && !(track->animType & ANIM_TYPE_ROT_QUAT)) {
        CTRLGetQuat(&bone->orientationCtrl.control, &x, &y, &z, &w);
        CTRLSetQuat(&bone->animationCtrl.control, x, y, z, w);
    }
    if (blend == 0) {
        bone->blendFromCtrl = bone->animationCtrl;
    }
}
