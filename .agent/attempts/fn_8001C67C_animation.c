/* best attempt fn_8001C67C_animation (batting bank loader): 9 lines, register swap in the bone-reset loop only:
   target keeps the context in r28 and the 4-byte bone offset in r27; this build swaps them. All 120 orders of the
   five locals tried (no change). Needs the typed context struct and ACTSetBoneTrack prototype from the patch
   (Codex .scratch/fn_8001C67C_near_match.patch). Next idea: the reset loop as an inline helper taking the actor. */
s32 fn_8001C67C_animation(s32 charID, s32 slot) {
    Gap8001196CBattingResetContext* context;
    GameActor* actor;
    Gap8001196CAnim* anim;
    s32 track;
    s32 boneIndex;

    if (lbl_803CBC3C.batting == 0) {
        if (lbl_803C6CF8.allowLoad != 1) return 0;
        context = g_hugeAnimStruct.battingResetContext;
        actor = context->actor;
        if (actor->boneArray[0]->animPipe != NULL &&
            actor->boneArray[0]->animPipe->currentTrack != NULL) {
            for (boneIndex = 0; boneIndex < actor->totalBones; boneIndex++) {
                ACTSetBoneTrack(actor->boneArray[boneIndex], NULL, 0.0f,
                                actor->unk8C < 1.0f);
            }
            context->pendingA = 0;
            context->pendingB = 0;
            context->pendingC = 0;
            context->blendTime = 0.0f;
        }
        lbl_803CBC3C.batting = 1;
    }

    if (lbl_803CBC3C.batting == 1) {
        if (g_d_GameSettings.unk11 != 0) {
            if (g_d_GameSettings.mode == 7) {
                track = charID * SUBFILE_TRACKS + 9;
            } else {
                track = charID * SUBFILE_TRACKS + 2;
            }
            ARAMTransfer(&lbl_803CB790[track], g_hugeAnimStruct.alternateBatterAnimBank, 0, NULL);
        } else {
            if (charID == g_hugeAnimStruct.cachedBatterSourceCharID) {
                memcpy(g_hugeAnimStruct.sharedAnimBank, g_hugeAnimStruct.cachedBatterSource,
                       g_hugeAnimStruct.cachedBatterCopySize);
                goto installShared;
            }
            if (g_d_GameSettings.mode == 2) {
                track = charID * SUBFILE_TRACKS + 10;
            } else {
                track = charID * SUBFILE_TRACKS + 2;
            }
            ARAMTransfer(&lbl_803CB790[track], g_hugeAnimStruct.sharedAnimBank, 0, NULL);
        }
        lbl_803CBC3C.batting = 2;
    } else if (lbl_803CBC3C.batting == 2) {
        if (lbl_803C6CF8.allowLoad != 1) goto notReady;
        if (g_d_GameSettings.unk11 != 0) {
            ANIMGet(g_hugeAnimStruct.alternateBatterAnimBank);
            anim = g_hugeAnimStruct.slotPtrs[slot];
            if (anim->animBankD == NULL) {
                anim->animBankD = g_hugeAnimStruct.alternateBatterAnimBank;
            }
            goto done;
        }
installShared:
        ANIMGet(g_hugeAnimStruct.sharedAnimBank);
        anim = g_hugeAnimStruct.slotPtrs[slot];
        if (anim->animBankD == NULL) {
            anim->animBankD = g_hugeAnimStruct.sharedAnimBank;
        }
done:
        g_hugeAnimStruct.activeBatterCharID = charID;
        return 1;
    }
notReady:
    lbl_803CBC3C.reset = 0;
    return 0;
 }
 
 // .text:0x8001C920 size:0x120
