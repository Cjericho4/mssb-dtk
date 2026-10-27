/* best attempt fn_8001DB74 (applies queued speed/time/loop/remap to each active character, then per-view visibility):
   12 register-only differences, no missing/extra instructions (Codex best2; key fix: slot byte +0x255 is signed).
   NOT a drop-in: this unit file includes UnknownHeaders.h with #define renames and replaces the matched
   fn_8001C920 with a stub. To integrate, move fn_8001DB74 only, and reconcile its types (AnimationStruct,
   g_hugeAnimStruct.AnimationStructPtrs/ctrlOrBonePtr, StadiumAnimTable) with gap_8001196C.h first; drop the
   casts ((s8)_rest255[0], ctrlOrBonePtr, StadiumAnimEntry*). Header used: fn_8001DB74_header.h. */
void fn_8001DB74(StadiumAnimTable* slots) {
    ActorAnimState* entry;
    u16 i;
    u16 viewIndex;
    AnimationStruct* anim;
    GameActor* actor;
    CameraView* view;
    Mtx transform;
    u8 visibility;
    s32 shift;
    f32 (*viewMtx)[4];
    u8 clearMask;
    u8 loopFlags;

    for (i = 0; i < slots->count; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (anim == NULL || anim->unk_25D == 0) continue;
        entry = &((StadiumAnimTable*)g_hugeAnimStruct.ctrlOrBonePtr)->entries[(s8)anim->_rest255[0]].anim;
        actor = entry->actor;
        if (actor == NULL) continue;
        if (entry->playAnim) {
            ACTSetAnimation(actor, entry->bank, NULL, entry->seqNum, 0.0f, entry->startTime);
        }
        if (entry->setTime) fn_800B4CA0(entry->actor, entry->time);
        if (entry->setSpeed) fn_800B4C04(entry->actor, entry->speed);
        loopFlags = entry->loopFlags;
        if (loopFlags & 2) {
            u8 loop = loopFlags & 1;
            fn_800B4AFC(entry->actor, loop);
        }
        Set_FUN_800b2b6c(entry->actor, entry->unk68);
        if (((StadiumAnimEntry*)entry)->enabled) fn_800BDA24(entry);
        for (viewIndex = 0; viewIndex < fn_800527BC(); viewIndex++) {
            view = fn_80052734(viewIndex);
            shift = viewIndex;
            shift *= 3;
            clearMask = ~(3 << shift);
            viewMtx = view->viewMtx;
            if (g_hugeAnimStruct.field269_0x307a == 5) {
                entry->actor->unk98 = 1;
            } else {
                PSMTXTrans(transform, anim->unk34.x, anim->unk34.y, anim->unk34.z);
                PSMTXConcat(viewMtx, transform, transform);
                actor = entry->actor;
                visibility = fn_800B3C04(viewIndex, actor, transform);
                actor->unk98 = (actor->unk98 & clearMask) | (visibility << shift);
            }
        }
        entry->playAnim = 0;
        entry->setTime = 0;
        entry->setSpeed = 0;
        entry->loopFlags &= 1;
    }
}
