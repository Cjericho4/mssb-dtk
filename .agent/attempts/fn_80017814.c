// Best attempt (54 sbs lines of ~325, from a stub). Left: (1) the root-header snapshot lands in r3 instead of r7 in the prologue (scheduling of the lwz before the slot mulli), (2) the bone loop's byte-offset induction var is 'li r4,0' instead of 'mr r4,r5', (3) arg evaluation order around the 2nd/3rd fn_800B2B74 calls. Idioms that worked: reuse the 'index' param as the bone-index temp (r28), s32 temp compared with 0xFFFF gives addis+cmplwi, u16 loop local gives plain cmplwi, inline aux ternary as a separate statement.
void fn_80017814(Gap8001196CAnim* anim, s32 index, s32 slotKind, void (*callback)(struct Gap8001E460Object*)) {
    Gap8001196CActorSlot* slot;
    Gap8001196CRootHeader* root = (Gap8001196CRootHeader*)anim->fileBuffer;
    struct Gap8001196CActLayout* layout;
    struct Gap8001196CGeoFile* geo;
    struct Gap8001196CSkin* skn;
    struct Gap8001196CTexArchive* tex;
    u16 numBones;
    u16 boneID;
    s32 i;
    u8* aux;

    slot = &g_hugeAnimStruct.actorEntries[index].slot;
    if (((Gap8001196CRootHeader*)anim->fileBuffer)->texture != 0) {
        ((Gap8001196CRootHeader*)anim->fileBuffer)->texture = (u32)root + root->texture;
        if (((Gap8001196CRootHeader*)anim->fileBuffer)->layout != 0) {
            ((Gap8001196CRootHeader*)anim->fileBuffer)->layout = (u32)root + root->layout;
            if (((Gap8001196CRootHeader*)anim->fileBuffer)->geo != 0) {
                ((Gap8001196CRootHeader*)anim->fileBuffer)->geo = (u32)root + root->geo;
                if (((Gap8001196CRootHeader*)anim->fileBuffer)->skn != 0) {
                    ((Gap8001196CRootHeader*)anim->fileBuffer)->skn = (u32)root + root->skn;
                    if (((Gap8001196CRootHeader*)anim->fileBuffer)->unk10 != 0) {
                        ((Gap8001196CRootHeader*)anim->fileBuffer)->unk10 = (u32)root + root->unk10;
                    }
                }
            }
        }
    }
    tex = (struct Gap8001196CTexArchive*)((Gap8001196CRootHeader*)anim->fileBuffer)->texture;
    convertTextureHeader(tex);
    if (((Gap8001196CRootHeader*)anim->fileBuffer)->layout != 0) {
        layout = (struct Gap8001196CActLayout*)((Gap8001196CRootHeader*)anim->fileBuffer)->layout;
        geo = (struct Gap8001196CGeoFile*)((Gap8001196CRootHeader*)anim->fileBuffer)->geo;
        skn = (struct Gap8001196CSkin*)((Gap8001196CRootHeader*)anim->fileBuffer)->skn;
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, skn);
        haveActLayoutPointToGeoHeader(layout, geo);
        fn_800BD190(geo, tex);
    } else {
        return;
    }
    aux = (slotKind < 9) ? anim->auxFielder : anim->auxBatter;
    fn_8002399C(slot, anim->unk255, index, layout, aux, skn);
    if (((Gap8001196CRootHeader*)anim->fileBuffer)->unk10 != 0) {
        fn_80025DDC((u8*)((Gap8001196CRootHeader*)anim->fileBuffer)->unk10);
        fn_80025C58((u8*)((Gap8001196CRootHeader*)anim->fileBuffer)->unk10, slot);
    }
    numBones = slot->actor->totalBones;
    memset((u8*)anim->boneIndices, 0xFF, sizeof(anim->boneIndices));
    for (i = 0; i < numBones; i++) {
        boneID = slot->actor->boneArray[i]->boneID;
        if (boneID != 0xFFFF) {
            anim->boneIndices[boneID] = i;
        }
    }
    fn_800B2B74(slot->actor, anim->boneIndices[19]);
    fn_800B2B74(slot->actor, anim->boneIndices[25]);
    fn_800B2B74(slot->actor, anim->boneIndices[36]);
    anim->actor = slot->actor;
    if ((s32)anim->boneIndices[3] != 0xFFFF) {
        fn_800B2B54(anim->actor, anim->boneIndices[3], 0xD);
    }
    fn_800BD548(slot, 4, g_hugeAnimStruct.unkAC, g_hugeAnimStruct.unkB0, g_hugeAnimStruct.unkB4, g_hugeAnimStruct.unkB8);
    CTRLSetTranslation(&slot->control, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&slot->control, 0.0f, 0.0f, 0.0f);
    slot->unk54 = 0.5f;
    slot->unk5A = 1;
    index = anim->boneIndices[3];
    if (index != 0xFFFF) {
        fn_800B2BA8(slot->actor, index, NULL, 0);
        slot->actor->boneArray[(u16)index]->unk136 = 1;
    }
    index = anim->boneIndices[2];
    if (index != 0xFFFF) {
        fn_800B2BA8(slot->actor, index, NULL, 0);
        slot->actor->boneArray[(u16)index]->unk136 = 1;
    }
    index = anim->boneIndices[1];
    if (index != 0xFFFF) {
        fn_800B2BA8(slot->actor, index, NULL, 0);
        slot->actor->boneArray[(u16)index]->unk136 = 1;
    }
    if ((s32)anim->boneIndices[36] != 0xFFFF) {
        fn_800B2BA8(slot->actor, anim->boneIndices[36], NULL, 0);
    }
    index = anim->boneIndices[46];
    if (index != 0xFFFF) {
        fn_800B2BA8(slot->actor, index, NULL, 0);
        slot->actor->boneArray[(u16)index]->unk136 = 1;
    }
    fn_800B2C08(slot->actor, anim->boneIndices[4]);
    fn_8001FC4C(anim);
    slot->callback = callback;
    anim->unk60 = -1;
    anim->animID = -1;
    anim->nextAnim = -1;
    anim->unk66 = -1;
    anim->unk68 = -1;
    anim->unk6A = -1;
    anim->unk6C = -1;
    anim->unk6E = -1;
    anim->unk25D = 0;
    anim->unk25E = 0;
    anim->unk25F = 0;
    anim->unk260 = 0;
    anim->unk261 = 0;
    anim->unk262 = 0;
    anim->unk263 = 0;
    anim->unk264 = 0;
    anim->unk265 = 0;
    anim->unk266 = 0;
    anim->unk267 = 0;
    anim->unk268 = 0;
    anim->unk269 = 0;
    anim->unk26A = 0;
    anim->unk26B = 0;
    anim->unk26C = 0;
    anim->unk26D = 0;
    anim->unk26E = 0;
    anim->unk270 = 0;
    anim->unk271 = 0;
    anim->unk272 = 0;
    anim->unk273 = 0;
    anim->unk277 = 0xFF;
    switch (anim->charID) {
    case 2:
        fn_800638B4(anim, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(anim, slot);
        break;
    case 19:
        fn_8004B7B4(anim, slot);
        break;
    case 12:
    case 21:
    case 22:
    case 23:
    case 42:
        slot->actor->unk99 = 1;
        break;
    case 24:
    case 25:
    case 26:
        slot->actor->unk99 = 1;
        break;
    case 20:
    case 43:
        fn_800637BC(anim, slot);
        break;
    case 38:
        slot->actor->unk99 = 1;
        fn_8004BD6C(anim, slot);
        break;
    case 41:
        fn_800637D4(anim, slot);
        fn_8004BD6C(anim, slot);
        break;
    case 14:
    case 37:
        fn_80052634(anim, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(anim, slot);
        break;
    }
}

