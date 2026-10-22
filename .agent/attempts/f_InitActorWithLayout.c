// Best attempt (93 sbs lines of 207, from a stub). Typed ActLayout/ActGeoPalette/ActDisplayObj/GameActor structs are in include/Unknown/gap_8002244C.h; same-file stubs f_InitBone/fn_80023078/BuildBoneSkinOrientationMatrix need #pragma dont_inline (now in the .c).
// Left: target keeps the running cursor and skinObj as stack memory variables (0xc/0x54(r1)) while also caching cursor in r24, has a 0x110 frame (~0x94 bytes of unexplained locals), adds the allocation sizes as bone+mtx+skinMtx+skinInv+orientInv+ALIGN(bones*0x140)+0xBF, and allocates r31 for &lbl_800E6698 / r23 for layout. Looks like inlined helpers with pointer out-params.
GameActor* f_InitActorWithLayout(ActLayout* layout, ActMemBlock* mem) {
    char* str = lbl_800E6698;
    GameActor* act;
    u32 boneArraySize;
    u32 mtxArraySize;
    u32 skinMtxSize;
    u32 skinInvSize;
    u32 orientInvSize;
    u16 numBones;
    ActMemBlock* cursor;
    Mtx identity;
    ActDisplayObj* skinObj;
    u32 i;
    u32 tmp;
    ActGeoDescriptor* desc;
    ActPositionData* pos;
    u32 normalDelta;
    ActGeoPalette* pal;

    numBones = 0;
    skinMtxSize = 0;
    skinInvSize = 0;
    orientInvSize = 0;
    boneArraySize = (layout->totalBones * 4 + 0x1F) & ~0x1F;
    mtxArraySize = (layout->totalBones * 0x30 + 0x1F) & ~0x1F;
    cursor = mem;
    if (layout->skinFileID != 0xFFFF) {
        pal = layout->geoPalettePtr;
        if (layout->skinFileID >= pal->numDescriptors) {
            OSReport(str, layout->skinFileID, pal->numDescriptors);
            skinObj = NULL;
        } else {
            skinObj = (ActDisplayObj*)mem;
            cursor = mem + 4;
            cursor = fn_80023078(skinObj, pal->descriptorArray[layout->skinFileID].layout, cursor);
        }
        mem = cursor;
        tmp = (layout->totalBones * 0x30 + 0x1F) & ~0x1F;
        skinMtxSize = tmp;
        skinInvSize = tmp;
        if (skinObj->lightingData != NULL) {
            orientInvSize = tmp;
        }
    }
    act = (GameActor*)mem;
    act->boneArray = (ActBone**)(act + 1);
    act->forwardMtxArray = (MtxPtr)((u32)act->boneArray + boneArraySize);
    act->skinObject = skinObj;
    act->skHeader = 0;
    mem = (ActMemBlock*)((u32)mem + ((boneArraySize + mtxArraySize + skinMtxSize + skinInvSize + orientInvSize +
                             ((layout->totalBones * 0x140 + 0x1F) & ~0x1F) + 0xBF) & ~0x1F));
    PSMTXIdentity(identity);
    act->actorID = layout->actorID;
    act->layout = layout;
    act->totalBones = layout->totalBones;
    DSInitTree(&act->hierarchy, NULL, (DSBranchPtr)4);
    DSInitList(&act->drawPriorityList, NULL, (DSLinkPtr)0xFC);
    act->pal = NULL;
    if (layout->geoPalettePtr != NULL) {
        act->pal = layout->geoPalettePtr;
    }
    if (layout->skinFileID != 0xFFFF) {
        DOSetWorldMatrix(act->skinObject, identity);
        act->skinMtxArray = (MtxPtr)((u32)act->forwardMtxArray + mtxArraySize);
        act->skinInvTransposeMtxArray = (MtxPtr)((u32)act->skinMtxArray + skinMtxSize);
        normalDelta = act->skinObject->lightingData->normalArray - act->skinObject->positionData->positionArray;
        pal = layout->geoPalettePtr;
        desc = pal->descriptorArray;
        for (i = 0; i < pal->numDescriptors; i++) {
            pos = desc[i].layout->positionData;
            if (pos->compCount == 6) {
                act->skinObject->positionData->positionArray = pos->positionArray;
                act->skinObject->lightingData->normalArray = pos->positionArray + normalDelta;
                break;
            }
        }
        if (act->skinObject->lightingData != NULL) {
            act->orientationInvMtxArray = (MtxPtr)((u32)act->skinInvTransposeMtxArray + skinInvSize);
        } else {
            act->orientationInvMtxArray = NULL;
        }
    } else {
        act->skinObject = NULL;
        act->skinMtxArray = NULL;
        act->skinInvTransposeMtxArray = NULL;
        act->orientationInvMtxArray = NULL;
    }
    act->worldControl.type = 0;
    if (layout->hierarchyRoot != NULL) {
        f_InitBone(NULL, layout->hierarchyRoot, act, &numBones,
                   (ActMemBlock*)((u32)act->forwardMtxArray + mtxArraySize + skinMtxSize + skinInvSize + orientInvSize), mem);
    }
    if (numBones != act->totalBones) {
        OSPanic(str + 0x3C, 0x209, str + 0x48);
    }
    if (act->skinObject != NULL) {
        BuildBoneSkinOrientationMatrix((ActBone*)act->hierarchy.Root, identity);
    }
    ACTSort(act);
    act->unk80 = 0;
    act->unk82 = 0;
    act->unk84 = 0;
    act->unk88 = 0;
    act->unk8C = 1.0f;
    act->unk90 = 0.0f;
    act->unk99 = 0;
    act->unk98 = 0;
    act->unk94 = 0;
    return act;
}
