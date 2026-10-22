// Best attempt (32 sbs lines of ~250, from a stub): everything matches except MWCC gives the two state-4 CSE temps (&slots[slot].fileBuffer and slot*0x27c) r30/r29 before the params (r26-r28) in the target, while here the field pointer lands in r26 after the params (explicit pointer locals / anim locals make it worse).
// Types: Gap8001196CAnimTable slotPtrs/sharedAnimBank/batterAnimBank/slotBanks/loadState/loadedCharID, Gap8001196CStadiumObj (lbl_80118220), lbl_800EEB18 model map, in include/Unknown/gap_8001196C.h.
static inline BOOL loadBatterAnimBank(s32 slot) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    if (g_hugeAnimStruct.unk2D8D == 0) {
        g_hugeAnimStruct.unk2D8D = 1;
        g_hugeAnimStruct.loadedCharID[slot] = anim->charID;
        anim->animBank = g_hugeAnimStruct.batterAnimBank;
        ARAMTransfer(&lbl_803CB790[anim->charID * SUBFILE_TRACKS + 17], anim->animBank, 0, NULL);
    } else if (lbl_803C6CF8.allowLoad == 1) {
        ANIMGet(anim->animBank);
        return TRUE;
    }
    return FALSE;
}

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

static inline u8 loadStadiumObject(u8 charID, s32 slot) {
    s16 modelID = lbl_800EEB18[charID];
    if (modelID == -1 || ((Gap8001196CModelFile*)g_hugeAnimStruct.slots[slot].fileBuffer)->unk10 == NULL) {
        g_hugeAnimStruct.slots[slot].stadiumObj = NULL;
        return 1;
    }
    if (lbl_803CBBFA == 0) {
        fn_80021ADC(modelID, lbl_80118220.buf);
        lbl_803CBBFA = 1;
    }
    if (lbl_803C6CF8.allowLoad == 1) {
        lbl_80118220.charID = charID;
        lbl_80118220.slot = slot;
        lbl_80118220.unk4 = lbl_80118220.buf;
        fn_80025FFC(((Gap8001196CModelFile*)g_hugeAnimStruct.slots[slot].fileBuffer)->unk10, &lbl_80118220.unk4, &lbl_80118220);
        lbl_803CBBFA = 0;
        g_hugeAnimStruct.slots[slot].stadiumObj = &lbl_80118220;
        return 1;
    }
    return 0;
}

BOOL fn_80016344(u8 charID, s32 slot, u8 stance, struct Gap8001196CLoadArg* arg) {

    if (g_hugeAnimStruct.loadState == 6) {
        return TRUE;
    }
    if (g_hugeAnimStruct.loadState == 1) {
        return FALSE;
    }
    if (g_hugeAnimStruct.loadState == 2) {
        g_hugeAnimStruct.slotPtrs[slot] = &g_hugeAnimStruct.slots[slot];
        g_hugeAnimStruct.slotPtrs[slot]->rosterUnk26 = stance;
        g_hugeAnimStruct.slotPtrs[slot]->rosterUnk27 = stance;
        g_hugeAnimStruct.unk2D8D = 0;
        g_hugeAnimStruct.loadState = 3;
    }
    if (g_hugeAnimStruct.loadState == 3) {
        if (slot == 12) {
            if (!loadBatterAnimBank(slot)) {
                return FALSE;
            }
        } else {
            if (!loadFielderAnimBank(slot)) {
                return FALSE;
            }
        }
        g_hugeAnimStruct.loadState = 4;
    }
    if (g_hugeAnimStruct.loadState == 4) {
        if (!loadStadiumObject(charID, slot)) {
            return FALSE;
        }
        g_hugeAnimStruct.loadState = 5;
    }
    if (g_hugeAnimStruct.loadState == 5) {
        if (!fn_80013680(&g_hugeAnimStruct.slots[slot])) {
            return FALSE;
        }
        g_hugeAnimStruct.loadState = 0;
        return TRUE;
    }
    fn_80017098(0, arg, 1, slot, 1, charID);
    return FALSE;
}

