// Best attempt (29 sbs lines of ~290, from a stub). Everything matches except the two CSE temps inside each inlined loadStadiumObject copy (slot*0x27c and &slots[slot].fileBuffer) come out r30/r29 swapped relative to the target (target: fieldptr allocated before the mulli temp); putting the NULL branch after the main path does not change it and breaks the block layout.
static inline BOOL loadFielderAnimBank(s32 slot) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    if (g_hugeAnimStruct.unk2D8D == 0) {
        g_hugeAnimStruct.unk2D8D = 1;
        g_hugeAnimStruct.loadedCharID[slot] = anim->charID;
        if (g_d_GameSettings.mode == 2) {
            anim->animBank = g_hugeAnimStruct.sharedAnimBank;
            fn_80021BBC(anim->charID, anim->animBank);
        } else if (slot >= 9) {
            anim->animBank = g_hugeAnimStruct.sharedAnimBank;
            ARAMTransfer(&lbl_803CB790[anim->charID * SUBFILE_TRACKS + 16], anim->animBank, 0, NULL);
        } else {
            anim->animBank = g_hugeAnimStruct.slotBanks[slot].animBank;
            fn_80021BBC(anim->charID, anim->animBank);
        }
    } else if (lbl_803C6CF8.allowLoad == 1) {
        ANIMGet(anim->animBank);
        return TRUE;
    }
    return FALSE;
}

static inline u8 loadStadiumObject(u8 charID, s32 slot, Gap8001196CStadiumObj* obj) {
    s16 modelID = lbl_800EEB18[charID];
    if (modelID == -1 || ((Gap8001196CModelFile*)g_hugeAnimStruct.slots[slot].fileBuffer)->unk10 == NULL) {
        g_hugeAnimStruct.slots[slot].stadiumObj = NULL;
        return 1;
    }
    if (lbl_803CBBFA == 0) {
        fn_80021ADC(modelID, obj->buf);
        lbl_803CBBFA = 1;
    }
    if (lbl_803C6CF8.allowLoad == 1) {
        obj->charID = charID;
        obj->slot = slot;
        obj->unk4 = obj->buf;
        fn_80025FFC(((Gap8001196CModelFile*)g_hugeAnimStruct.slots[slot].fileBuffer)->unk10, &obj->unk4, obj);
        lbl_803CBBFA = 0;
        g_hugeAnimStruct.slots[slot].stadiumObj = obj;
        return 1;
    }
    return 0;
}

BOOL fn_80016710(u8 charID, s32 slot) {
    if (g_hugeAnimStruct.loadState == 6) {
        return TRUE;
    }
    if (g_hugeAnimStruct.loadState == 1) {
        return FALSE;
    }
    if (g_hugeAnimStruct.loadState == 2) {
        g_hugeAnimStruct.slotPtrs[slot] = &g_hugeAnimStruct.slots[slot];
        g_hugeAnimStruct.unk2D8D = 0;
        g_hugeAnimStruct.loadState = 3;
    }
    if (g_hugeAnimStruct.loadState == 3) {
        if (!loadFielderAnimBank(slot)) {
            return FALSE;
        }
        g_hugeAnimStruct.loadState = 4;
    }
    if (g_hugeAnimStruct.loadState == 4) {
        if (g_d_GameSettings.mode == 2) {
            if (!loadStadiumObject(charID, slot, &lbl_80118220[0])) {
                return FALSE;
            }
        } else {
            if (!loadStadiumObject(charID, slot, &lbl_80118220[slot])) {
                return FALSE;
            }
        }
        g_hugeAnimStruct.loadState = 5;
    }
    if (g_hugeAnimStruct.loadState == 5) {
        if (g_d_GameSettings.mode == 2) {
            if (!fn_80013680(&g_hugeAnimStruct.slots[slot])) {
                return FALSE;
            }
        } else {
            if (!fn_80012B90(&g_hugeAnimStruct.slots[slot])) {
                return FALSE;
            }
        }
        return TRUE;
    }
    fn_80017098(0, NULL, 0, slot, 1, charID);
    return FALSE;
}

#pragma dont_inline on
