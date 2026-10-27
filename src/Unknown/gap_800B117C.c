#include "Unknown/gap_800B117C.h"
#include "stdarg.h"
#include "Dolphin/GX/GXGeometry.h"

void DOVARender(void* obj, Mtx viewMtx, u8 lightCount, va_list* args);
void DOVARenderSkin(void* obj, Mtx viewMtx, Mtx* skinMatrices, Mtx* inverseMatrices, u8 lightCount, va_list* args);
void DOSetWorldMatrix(void* obj, MtxPtr matrix);

// .text:0x800B117C size:0xC
void fn_800B117C(u8 value) {
    lbl_803CBB34->unk8C = value;
}

// .text:0x800B1188 size:0x11C
void fn_800B1188(void) {
    return;
}

// .text:0x800B12A4 size:0x38
void DrawNullSprite(Gap800B117CVertex* vertices, s32 count) {
    DrawSprite(152, vertices, count, NULL, 0, 0);
}

// .text:0x800B12DC size:0x38
void fn_800B12DC(Gap800B117CVertex* vertices, s32 count) {
    DrawSprite(160, vertices, count, NULL, 0, 0);
}

// .text:0x800B1314 size:0x3C
void fn_800B1314(Gap800B117CVertex* vertices, Gap800B117CTexture* texture, u32 height, u32 width) {
    DrawSprite(0x80, vertices, 4, texture, height, width);
}

// .text:0x800B1350 size:0x38
void DrawSprite_TexObj(Gap800B117CVertex* vertices, Gap800B117CTexture* texture) {
    DrawSprite(0x80, vertices, 4, texture, texture->height, texture->width);
}

// .text:0x800B1388 size:0x38
void fn_800B1388(Gap800B117CVertex* vertices) {
    DrawSprite(0x80, vertices, 4, NULL, 0, 0);
}

// .text:0x800B13C0 size:0xA8
void fn_800B13C0(void) {
    return;
}

// .text:0x800B1468 size:0x98
void fn_800B1468(void) {
    return;
}

// .text:0x800B1500 size:0x9BC
#pragma dont_inline on
void DrawSprite(s32 primitive, Gap800B117CVertex* vertices, s32 count, Gap800B117CTexture* texture, u32 height, u32 width) {
    return;
}

#pragma dont_inline reset

// .text:0x800B1EBC size:0x2A4
void fn_800B1EBC(void) {
    return;
}

// .text:0x800B2160 size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34->unk8A = value;
}

// .text:0x800B216C size:0x3C
BOOL fn_800B216C(u8 a, u32 b, u8 c) {
    u32 mode = a | (b << 1) | (c << 4) | 0x40000000;
    if (lbl_803CBB34->renderMode == mode) return 0;
    lbl_803CBB34->renderMode = mode;
    return 1;
}

// .text:0x800B21A8 size:0x98
void fn_800B21A8(s32 mode) {
    if (mode == 2) {
        u32 old = lbl_803CBB34->renderMode;
        if (fn_800B216C(1, 1, 1)) {
            lbl_803CBB34->savedRenderMode = old;
        }
    } else if (mode != 0) {
        fn_800B216C(1, 3, 1);
    } else {
        fn_800B216C(1, 7, 1);
    }
}

// .text:0x800B2240 size:0x294
void fn_800B2240(void) {
    return;
}

// .text:0x800B24D4 size:0x48
void fn_800B24D4(s32 index) {
    lbl_803CC1D4 = index;
    lbl_803CBB34 = &lbl_802FEBF8.current[index];
    lbl_803CBB38 = &lbl_802FEBF8.previous[index];
    lbl_803CBB40 = &lbl_802FE918[index];
    lbl_803CC1C0 = &lbl_803CC1E4[index];
}

// .text:0x800B251C size:0x288
void fn_800B251C(void) {
    return;
}

// .text:0x800B27A4 size:0x38
void fn_800B27A4(s32 index) {
    u16 mask;
    if (index < 0) return;
    if (index > 14) return;
    lbl_803CC1C8 = index;
    mask = 1 << index;
    lbl_801115A0.mask6 = lbl_801115A0.mask8 = lbl_801115A0.maskA = lbl_801115A0.maskC = mask;
}

// .text:0x800B27DC size:0x78
void fn_800B27DC(void) {
    return;
}

// .text:0x800B2854 size:0x274
void fn_800B2854(void) {
    return;
}

// .text:0x800B2AC8 size:0x84
void fn_800B2AC8(Gap800B117CDisplayAnimation* animation) {
    s32 i;
    Gap800B117CModel* model = animation->model;
    Gap800B117CDisplay* display;
    for (i = 0; i < animation->count; i++) {
        if ((animation->records[i].flags & 0x18) && animation->records[i].index != 0xFFFF) {
            display = model->displays[animation->records[i].index].display;
            fn_800BC824(display, fn_800BF068()->value);
        }
    }
}

// .text:0x800B2B4C size:0x8
void fn_800B2B4C(Gap800B117CObj* obj, f32 value) {
    obj->unk90 = value;
}

// .text:0x800B2B54 size:0x18
void fn_800B2B54(Gap800B117CObj* obj, u16 index, u8 value) {
    obj->entries[index]->unk134 = value;
}

// .text:0x800B2B6C size:0x8
void Set_FUN_800b2b6c(Gap800B117CObj* obj, s32 value) {
    obj->unk88 = value;
}

// .text:0x800B2B74 size:0x34
void fn_800B2B74(Gap800B117CObj* obj, u16 index) {
    DSInsertListObject(&obj->list, obj->list.Tail, (Ptr)obj->entries[index]);
}

// .text:0x800B2BA8 size:0x3C
s32 fn_800B2BA8(Gap800B117CObj* obj, u16 index, Gap800B117CObj* other, u16 otherIndex) {
    Gap800B117CObj* entry = obj->entries[index];
    s32 previous = entry->unk14;
    if (other != NULL) entry->unk14 = other->entries[otherIndex]->unk14;
    else entry->unk14 = 0;
    return previous;
}

// .text:0x800B2BE4 size:0x18
void fn_800B2BE4(Gap800B117CObj* obj, u16 index) {
    obj->entries[index]->unk14 = (s32)obj->entries[index]->entries;
}

// .text:0x800B2BFC size:0xC
void fn_800B2BFC(Gap800B117CObj* obj, s16 a, s16 b) {
    obj->unk80 = a;
    obj->unk82 = b;
}

// .text:0x800B2C08 size:0x8
void fn_800B2C08(Gap800B117CObj* obj, s16 value) {
    obj->unk84 = value;
}

// .text:0x800B2C10 size:0x34
void fn_800B2C10(Gap800B117CObj* obj, u16 index, Vec* vec) {
    PSMTXMultVec(obj->matrices[index], vec, vec);
}

// .text:0x800B2C44 size:0x44
void fn_800B2C44(Gap800B117CObj* obj, u16 index, Vec* vec) {
    vec->x = 0.0f;
    vec->y = 0.0f;
    vec->z = 0.0f;
    PSMTXMultVec(obj->matrices[index], vec, vec);
}

// .text:0x800B2C88 size:0x34
void fn_800B2C88(Gap800B117CObj* obj, u16 index, f32 matrix[3][4]) {
    PSMTXCopy(obj->matrices[index], matrix);
}

// .text:0x800B2CBC size:0xA0
// Rebuilds the actor's draw list: bones with geometry, ordered by ascending drawing priority.
void ACTSort(GameActor* actor) {
    u16 i;
    ActBone* cursor;
    actor->drawPriorityList.Head = NULL;
    actor->drawPriorityList.Tail = NULL;
    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->dispObj != NULL) {
            cursor = (ActBone*)actor->drawPriorityList.Head;
            while (cursor != NULL) {
                if (cursor->drawingPriority > actor->boneArray[i]->drawingPriority) {
                    break;
                }
                cursor = (ActBone*)cursor->drawPriorityLink.Next;
            }
            DSInsertListObject(&actor->drawPriorityList, (Ptr)cursor, (Ptr)actor->boneArray[i]);
        }
    }
}

// .text:0x800B2D5C size:0x74
void fn_800B2D5C(Gap800B117CObj* obj) {
    Gap800B117CSkinHeader* skin;
    GQRSetup5(8, 4, 8, 4);
    skin = obj->skinHeaders[0];
    if (skin->format == 0x40) {
        SKNIt(obj->entries, obj->skinOutput, skin->data);
    } else {
        fn_800BF2A8(obj->entries, obj->skinOutput, skin->data);
    }
}

// .text:0x800B2DD0 size:0x36C
void fn_800B2DD0(void) {
    return;
}

// .text:0x800B313C size:0x378
void fn_800B313C(void) {
    return;
}

// .text:0x800B34B4 size:0x2F0
void fn_800B34B4(void) {
    return;
}

// .text:0x800B37A4 size:0x2D4
void f_BuildBoneSkinOrientationMatrix(void) {
    return;
}

/* Draw an actor's skin and visible bone objects using the supplied lights. */
// .text:0x800B3A78 size:0x18C
void fn_800B3A78(GameActor* actor, Mtx viewMtx, u8 lightCount, ...) {
    va_list args;
    ActBone* bone;
    Gap800B117CObj* skinView = (Gap800B117CObj*)actor;
    Gap800B117CSkinHeader* skin;
    if ((actor->unk98 & 9) != 0) { /* draw flags bits 0 and 3 (meaning not yet named) */
        if (actor->skinObject != NULL) {
            GQRSetup5(8, 4, 8, 4);
            skin = skinView->skinHeaders[0];
            if (skin->format == 0x40) { /* SKNIt layout; others take fn_800BF2A8 */
                SKNIt(skinView->entries, skinView->skinOutput, skin->data);
            } else {
                fn_800BF2A8(skinView->entries, skinView->skinOutput, skin->data);
            }
            GXInvalidateVtxCache();
            va_start(args, lightCount);
            if (actor->skHeader != 0) {
                DOVARender((struct DODisplayObj*)actor->skinObject, viewMtx, lightCount, &args);
            } else {
                DOVARenderSkin((struct DODisplayObj*)actor->skinObject, viewMtx,
                               actor->skinMtxArray, actor->skinInvTransposeMtxArray,
                               lightCount, &args);
            }
        }
        bone = (ActBone*)actor->drawPriorityList.Head;
        while (bone != NULL) {
            if (bone->dispObj != NULL) {
                DOSetWorldMatrix((struct DODisplayObj*)bone->dispObj, bone->forwardMtx);
            }
            va_start(args, lightCount);
            DOVARender((struct DODisplayObj*)bone->dispObj, viewMtx, lightCount, &args);
            bone = (ActBone*)bone->drawPriorityLink.Next;
        }
    }
    va_end(args);
}

// .text:0x800B3C04 size:0x31C
void fn_800B3C04(void) {
    return;
}

// .text:0x800B3F20 size:0x128
void fn_800B3F20(void) {
    return;
}

// .text:0x800B4048 size:0x3C
BOOL fn_800B4048(u32* result, Gap800B117CRequest* request, u16 type) {
    request->type = type;
    *result = fn_800B43A0(request);
    return 1;
}

// .text:0x800B4084 size:0x1F4
void fn_800B4084(void) {
    return;
}

// .text:0x800B4278 size:0x128
void fn_800B4278(void) {
    return;
}

// .text:0x800B43A0 size:0x384
#pragma dont_inline on
u32 fn_800B43A0(Gap800B117CRequest* request) {
}

#pragma dont_inline reset

// .text:0x800B4724 size:0x8
void fn_800B4724(Gap800B117CObj* obj, s32 value) {
    obj->unk7C = value;
}

// .text:0x800B472C size:0x1DC
void fn_800B472C(void) {
    return;
}

// .text:0x800B4908 size:0x8
void haveActLayoutPointToGeoHeader(Gap800B117CObj* obj, s32 value) {
    obj->unk10 = value;
}

// .text:0x800B4910 size:0xD4
void LoadActorLayout(void) {
    return;
}

// .text:0x800B49E4 size:0x60
void fn_800B49E4(void) {
    return;
}

static inline f32 getAnimationTime(ANIMPipe* pipe) {
    if (pipe != NULL) {
        if (pipe->forward == 0) return pipe->time;
        if (pipe->currentTrack != NULL) return pipe->currentTrack->animTime - pipe->time;
    }
    return 0.0f;
}

// .text:0x800B4A44 size:0x50
f32 fn_800B4A44(GameActor* actor, u16 index) {
    return getAnimationTime(actor->boneArray[index]->animPipe);
}

// .text:0x800B4A94 size:0x68
f32 fn_800B4A94(GameActor* actor) {
    u32 i;
    ANIMPipe* pipe;
    struct ANIMAnimTrack* track;
    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) {
            if (pipe->forward == 0) {
                return pipe->time;
            }
            track = pipe->currentTrack;
            if (track != NULL) {
                return track->animTime - pipe->time;
            }
        }
    }
    return 0.0f;
}

// .text:0x800B4AFC size:0x3C
void fn_800B4AFC(GameActor* actor, u8 loop) {
    u32 i;
    for (i = 0; i < actor->totalBones; i++) {
        ANIMPipe* pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) pipe->loop = loop;
    }
}

// .text:0x800B4B38 size:0x90
// Advances the actor's blend weight by its step (clamped to 1) and ticks every bone's pipe.
void AnimateActorBones(GameActor* actor) {
    u32 i;
    actor->unk8C += actor->unk90;
    if (actor->unk8C > 1.0f) actor->unk8C = 1.0f;
    for (i = 0; i < actor->totalBones; i++) {
        ANIMTick(actor->boneArray[i]->animPipe, actor->unk99);
    }
}

// .text:0x800B4BC8 size:0x3C
void fn_800B4BC8(GameActor* actor, u8 forward) {
    u32 i;
    for (i = 0; i < actor->totalBones; i++) {
        ANIMPipe* pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) pipe->forward = forward;
    }
}

// .text:0x800B4C04 size:0x3C
void fn_800B4C04(GameActor* actor, f32 speed) {
    u32 i;
    for (i = 0; i < actor->totalBones; i++) {
        ANIMPipe* pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) pipe->speed = speed;
    }
}

// .text:0x800B4C40 size:0x60
f32 fn_800B4C40(GameActor* actor) {
    u32 i;
    for (i = 0; i < actor->totalBones; i++) {
        if (actor->boneArray[i]->animPipe != NULL && actor->boneArray[i]->animPipe->currentTrack != NULL) {
            return actor->boneArray[i]->animPipe->time;
        }
    }
    return 0.0f;
}

// .text:0x800B4CA0 size:0x3C
void fn_800B4CA0(GameActor* actor, f32 time) {
    u32 i;
    for (i = 0; i < actor->totalBones; i++) {
        ANIMPipe* pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) pipe->time = time;
    }
}

// .text:0x800B4CDC size:0x88
void fn_800B4CDC(GameActor* actor) {
    s32 i;
    for (i = actor->totalBones - 1; i >= 0; i--) {
        if (actor->boneArray[i]->animPipe != NULL) {
            fn_800ACFB0(actor->boneArray[i]->animPipe);
            actor->boneArray[i]->animPipe = NULL;
        }
    }
}

// .text:0x800B4D64 size:0x138
// Binds sequence `seqNum` (or `sequenceName`) of `bank` to every bone of the actor at `time`,
// blending from the current pose when blendStep != 0 (blend weight grows by blendStep per tick).
void ACTSetAnimation(GameActor* actor, ANIMBank* bank, char* sequenceName, u16 seqNum, f32 time, f32 blendStep) {
    u16 i;
    ANIMSequences* sequence = ANIMGetSequence(bank, sequenceName, seqNum);
    struct ANIMAnimTrack* track = NULL;
    ActBone* bone;

    for (i = 0; i < actor->totalBones; i++) {
        if (sequence != NULL) {
            track = ANIMGetTrackFromSequence(sequence, actor->boneArray[i]->boneID);
        }
        bone = actor->boneArray[i];
        ACTSetBoneTrack(bone, track, time, actor->unk8C < 1.0f && bone->animFlags != 0);
        bone = actor->boneArray[i];
        if (bone->animFlags & 0x1C) {
            bone->animFlags |= 0x20;
        } else {
            bone->animFlags &= 0xFFDF;
        }
    }
    actor->unk8C = blendStep ? 0.0f : 1.0f;
    actor->unk90 = blendStep;
}

// .text:0x800B4E9C size:0x100
// Finds the key pair surrounding `time`, starting from the cached *keyIndex (restarting at 0 when
// time moved before that key); after the last key the next key wraps to key 0.
void ANIMGetKeyFrameFromTrack(struct ANIMAnimTrack* track, f32 time, KeyFrame** currentFrame, KeyFrame** nextFrame,
                              u16* keyIndex) {
    u16 i;
    u16 remaining;
    s32 start = *keyIndex;

    if (track->keyFrames[start].time <= time) {
        start = *keyIndex; /* FAKEMATCH: redundant reload keeps the empty-then branch shape */
    } else {
        start = 0;
    }
    i = start;
    remaining = track->totalFrames;
    while (remaining-- != 0) {
        if (track->keyFrames[i].time <= time) {
            if (i < track->totalFrames - 1) {
                if (track->keyFrames[i + 1].time > time) {
                    if (currentFrame != NULL) *currentFrame = &track->keyFrames[i];
                    if (nextFrame != NULL) *nextFrame = &track->keyFrames[i + 1];
                    *keyIndex = i;
                    return;
                }
            } else {
                if (currentFrame != NULL) *currentFrame = &track->keyFrames[i];
                if (nextFrame != NULL) *nextFrame = track->keyFrames;
                *keyIndex = i;
                return;
            }
        }
        i = (i + 1) % track->totalFrames;
    }
}

// .text:0x800B4F9C size:0x50
struct ANIMAnimTrack* ANIMGetTrackFromSequence(ANIMSequences* sequence, u16 id) {
    u32 i;
    for (i = 0; i < sequence->totalTracks; i++) {
        if (id == sequence->trackArray[i].trackID) return &sequence->trackArray[i];
    }
    return NULL;
}

// .text:0x800B4FEC size:0xA0
ANIMSequences* ANIMGetSequence(ANIMBank* bank, char* name, u16 index) {
    u32 i;
    if (name != NULL) {
        for (i = 0; i < bank->numSequences; i++) {
            if (Strcmp(bank->animSequences[i].sequenceName, name) == 0) {
                return &bank->animSequences[i];
            }
        }
    } else if (bank == NULL) {
        return NULL;
    }
    return &bank->animSequences[index];
}
