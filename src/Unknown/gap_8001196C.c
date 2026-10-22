#include "Unknown/gap_8001196C.h"

// .text:0x8001196C size:0xF4
void fn_8001196C(void) {
    return;
}

// .text:0x80011A60 size:0x104
void fn_80011A60(void) {
    return;
}

// .text:0x80011B64 size:0x80
void fn_80011B64(void) {
    return;
}

// .text:0x80011BE4 size:0xC4
void fn_80011BE4(void) {
    return;
}

// .text:0x80011CA8 size:0xA44
void fn_80011CA8(void) {
    return;
}

// .text:0x800126EC size:0x10C
void fn_800126EC(void) {
    return;
}

// .text:0x800127F8 size:0x398
void LoadModel(void) {
    return;
}

#pragma dont_inline on
// .text:0x80012B90 size:0xAF0
u8 fn_80012B90(struct Gap8001196CAnim* anim) {
    return;
}
#pragma dont_inline off

#pragma dont_inline on
// .text:0x80013680 size:0xB84
u8 fn_80013680(struct Gap8001196CAnim* anim) {
    return;
}
#pragma dont_inline off

// .text:0x80014204 size:0x3F4
void fn_80014204(void) {
    return;
}

// .text:0x800145F8 size:0x398
void fn_800145F8(void) {
    return;
}

// .text:0x80014990 size:0x88
void fn_80014990(void) {
    return;
}

// .text:0x80014A18 size:0x334
void fn_80014A18(void) {
    return;
}

// .text:0x80014D4C size:0x104
void fn_80014D4C(void) {
    return;
}

// .text:0x80014E50 size:0xF0
void fn_80014E50(void) {
    return;
}

// .text:0x80014F40 size:0xCC
void fn_80014F40(void) {
    return;
}

// .text:0x8001500C size:0x45C
void fn_8001500C(void) {
    return;
}

// .text:0x80015468 size:0x4E4
void fn_80015468(void) {
    return;
}

// .text:0x8001594C size:0x9F8
void fn_8001594C(void) {
    return;
}

/* ---- fn_80016344 / fn_80016710 helpers (inlined into both in the retail binary) -------------- */

/* Batter slot (12): stream subfile track 17 into g_hugeAnimStruct.batterAnimBank, then ANIMGet. */
static inline BOOL loadBatterAnimBank(s32 slot) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    if (g_hugeAnimStruct.bankLoadStep == 0) {
        g_hugeAnimStruct.bankLoadStep = 1;
        g_hugeAnimStruct.loadedCharID[slot] = anim->charID;
        anim->animBank = g_hugeAnimStruct.batterAnimBank;
        ARAMTransfer(&lbl_803CB790[anim->charID * SUBFILE_TRACKS + 17], anim->animBank, 0, NULL);
    } else if (lbl_803C6CF8.allowLoad == 1) {
        ANIMGet(anim->animBank);
        return TRUE;
    }
    return FALSE;
}

/* Other slots: mode 2 and slots < 9 load the skeleton rig through fn_80021BBC (master 432+charID or
 * track 15) into the shared / per-block buffer; slots >= 9 stream subfile track 16 instead. */
static inline BOOL loadFielderAnimBank(s32 slot) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    if (g_hugeAnimStruct.bankLoadStep == 0) {
        g_hugeAnimStruct.bankLoadStep = 1;
        g_hugeAnimStruct.loadedCharID[slot] = anim->charID;
        if (g_d_GameSettings.mode == 2) {
            anim->animBank = g_hugeAnimStruct.sharedAnimBank;
            fn_80021BBC(anim->charID, anim->animBank);
        } else if (slot >= 9) {
            anim->animBank = g_hugeAnimStruct.sharedAnimBank;
            ARAMTransfer(&lbl_803CB790[anim->charID * SUBFILE_TRACKS + 16], anim->animBank, 0, NULL);
        } else {
            anim->animBank = g_hugeAnimStruct.animBanks[slot].bankE;
            fn_80021BBC(anim->charID, anim->animBank);
        }
    } else if (lbl_803C6CF8.allowLoad == 1) {
        ANIMGet(anim->animBank);
        return TRUE;
    }
    return FALSE;
}

/* Stadium/extra object attached to the character: lbl_800EEB18[charID] (0x800EEB18, s16, -1 = none)
 * is the model id; if the relocated .gpc root header has an extra block (word 0x10) the object is
 * streamed once by fn_80021ADC(modelID, obj->buf) (master descriptor 486 + modelID, guarded by
 * lbl_803CBBFA) and bound with fn_80025FFC.  Returns 1 when done (or nothing to do), 0 to retry. */
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

/* fn_80016344 -- per-slot character load state machine (game side: batter/fielder slots).
 *
 * charID: character; slot: 0..12 (12 = batter); stance: roster batting/fielding byte copied to
 * 0x25A/0x25B; player: roster index forwarded to fn_80017098 when a load must be queued.
 * Returns TRUE when the slot is fully loaded (loadState 6, or state 5 just finished).
 * g_hugeAnimStruct.loadState (0x2D77): 6 done, 1 queued (wait), 2 register slotPtrs[slot] and
 * reset bankLoadStep, 3 animation bank / skeleton (loadBatterAnimBank / loadFielderAnimBank),
 * 4 stadium object (loadStadiumObject with lbl_80118220[0]), 5 fn_80013680(slot) post-processing,
 * anything else -> fn_80017098(0, player, 1, slot, 1, charID) re-queues the load.
 * Tables: lbl_803CB790 runtime subfile table (tracks 16/17), lbl_800EEB18 model map,
 * lbl_80118220 stadium objects, lbl_803C6CF8.allowLoad.
 * Chain position: runs after fn_8001758C/fn_80017814 built the actor; the model files themselves
 * are not touched here.  Variant hook: none for a texture skin; a model-swapping skin only needs
 * the lbl_800EEB18 lookup keyed on (charID, skin).
 * Match status: NOT matched -- only the two state-4 CSE temps (&slots[slot].fileBuffer and
 * slot*0x27c) are allocated r26 after the params here but r30/r29 before them in the target;
 * everything else is identical. */
// .text:0x80016344 size:0x3CC
BOOL fn_80016344(u8 charID, s32 slot, u8 stance, s32 player) {
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
        g_hugeAnimStruct.bankLoadStep = 0;
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
        if (!loadStadiumObject(charID, slot, &lbl_80118220[0])) {
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
    fn_80017098(0, player, 1, slot, 1, charID);
    return FALSE;
}

/* fn_80016710 -- per-slot character load state machine (menu / non-batter variant of fn_80016344).
 *
 * Same states as fn_80016344 without the stance copy and batter path: state 3 uses
 * loadFielderAnimBank, state 4 uses stadium object lbl_80118220[0] in mode 2 and
 * lbl_80118220[slot] otherwise (13 objects of 0x64 bytes), state 5 runs fn_80013680 (mode 2) or
 * fn_80012B90 and returns TRUE without clearing loadState; other states queue
 * fn_80017098(0, 0, 0, slot, 1, charID).  Returns TRUE when loaded.
 * Variant hook / tables: as fn_80016344.
 * Match status: NOT matched -- same two CSE temps as fn_80016344, swapped (r29/r30) inside each
 * inlined loadStadiumObject copy; everything else identical. */
// .text:0x80016710 size:0x450
BOOL fn_80016710(u8 charID, s32 slot) {
    if (g_hugeAnimStruct.loadState == 6) {
        return TRUE;
    }
    if (g_hugeAnimStruct.loadState == 1) {
        return FALSE;
    }
    if (g_hugeAnimStruct.loadState == 2) {
        g_hugeAnimStruct.slotPtrs[slot] = &g_hugeAnimStruct.slots[slot];
        g_hugeAnimStruct.bankLoadStep = 0;
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
    fn_80017098(0, 0, 0, slot, 1, charID);
    return FALSE;
}

#pragma dont_inline on
// .text:0x80016B60 size:0x41C
/* fn_80016B60 -- stream a slot's five animation banks, one step per call.
 *
 * anim: the slot record (Gap8001196CAnim).  Returns TRUE once all banks are loaded and ANIMGet'd.
 * Step counter: g_hugeAnimStruct.bankLoadStep (0x2D8D).  Odd steps queue an ARAMTransfer from the
 * runtime subfile table lbl_803CB790[anim->charID*19 + track] into the per-block buffer
 * g_hugeAnimStruct.animBanks[anim->blockIndex] (0x2CEC + blockIndex*0x14), even steps wait for
 * lbl_803C6CF8.allowLoad == 1 and call ANIMGet on the buffer.  Track selection depends on
 * g_d_GameSettings.mode (0x800E86FC+7) and settings.unk11:
 *   step 1/2  animBankA (0x18) <- track 4  (13 in mode 7)
 *   step 3/4  animBankB (0x14) <- track 12 (11 in mode 2, 14 in mode 6)
 *   step 5/6  animBankC (0x1C) <- track 5  (18 when unk11 != 0 or mode 2); step 6 also sets
 *             animBankD = animBanks[0].bankD and jumps to step 9 (steps 7/8, track 2/9/10, are dead)
 *   step 9/10 animBank  (0x24) <- track 16
 * Chain position: driven by fn_80016F7C for slots 0..3 after the models are in; the banks are
 * what fn_8002399C/fn_80017814 hand to the actor as "aux".
 * Variant hook: none needed for a cosmetic skin (animations stay on charID); a clone slot must
 * alias the source's tracks 2..18 so these lookups keep working.
 * Match status: MATCH. */
BOOL fn_80016B60(Gap8001196CAnim* anim) {
    Gap8001196CSlotBanks* banks;
    s32 track;

    if (g_hugeAnimStruct.bankLoadStep == 0) {
        g_hugeAnimStruct.bankLoadStep = 1;
    }
    if (g_hugeAnimStruct.bankLoadStep == 1) {
        anim->animBankA = g_hugeAnimStruct.animBanks[anim->blockIndex].bankA;
        if (g_d_GameSettings.mode == 7) {
            track = anim->charID * SUBFILE_TRACKS + 13;
        } else {
            track = anim->charID * SUBFILE_TRACKS + 4;
        }
        ARAMTransfer(&lbl_803CB790[track], anim->animBankA, 0, NULL);
        g_hugeAnimStruct.bankLoadStep = 2;
    } else if (g_hugeAnimStruct.bankLoadStep == 2) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(anim->animBankA);
            g_hugeAnimStruct.bankLoadStep = 3;
        }
    } else if (g_hugeAnimStruct.bankLoadStep == 3) {
        anim->animBankB = g_hugeAnimStruct.animBanks[anim->blockIndex].bankB;
        if (g_d_GameSettings.mode == 2) {
            track = anim->charID * SUBFILE_TRACKS + 11;
        } else if (g_d_GameSettings.mode == 6) {
            track = anim->charID * SUBFILE_TRACKS + 14;
        } else {
            track = anim->charID * SUBFILE_TRACKS + 12;
        }
        ARAMTransfer(&lbl_803CB790[track], anim->animBankB, 0, NULL);
        g_hugeAnimStruct.bankLoadStep = 4;
    } else if (g_hugeAnimStruct.bankLoadStep == 4) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(anim->animBankB);
            g_hugeAnimStruct.bankLoadStep = 5;
        }
    } else if (g_hugeAnimStruct.bankLoadStep == 5) {
        anim->animBankC = g_hugeAnimStruct.animBanks[anim->blockIndex].bankC;
        if (g_d_GameSettings.unk11 != 0 || g_d_GameSettings.mode == 2) {
            track = anim->charID * SUBFILE_TRACKS + 18;
        } else {
            track = anim->charID * SUBFILE_TRACKS + 5;
        }
        ARAMTransfer(&lbl_803CB790[track], anim->animBankC, 0, NULL);
        g_hugeAnimStruct.bankLoadStep = 6;
    } else if (g_hugeAnimStruct.bankLoadStep == 6) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(anim->animBankC);
            anim->animBankD = g_hugeAnimStruct.animBanks[0].bankD;
            g_hugeAnimStruct.bankLoadStep = 9;
        }
    } else if (g_hugeAnimStruct.bankLoadStep == 7) {
        anim->animBankD = g_hugeAnimStruct.animBanks[anim->blockIndex].bankD;
        if (g_d_GameSettings.mode == 7) {
            track = anim->charID * SUBFILE_TRACKS + 9;
        } else if (g_d_GameSettings.mode == 2) {
            track = anim->charID * SUBFILE_TRACKS + 10;
        } else {
            track = anim->charID * SUBFILE_TRACKS + 2;
        }
        ARAMTransfer(&lbl_803CB790[track], anim->animBankD, 0, NULL);
        g_hugeAnimStruct.bankLoadStep = 8;
    } else if (g_hugeAnimStruct.bankLoadStep == 8) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(anim->animBankD);
            g_hugeAnimStruct.bankLoadStep = 9;
        }
    } else if (g_hugeAnimStruct.bankLoadStep == 9) {
        anim->animBank = g_hugeAnimStruct.animBanks[anim->blockIndex].bankE;
        ARAMTransfer(&lbl_803CB790[anim->charID * SUBFILE_TRACKS + 16], anim->animBank, 0, NULL);
        g_hugeAnimStruct.bankLoadStep = 10;
    } else if (g_hugeAnimStruct.bankLoadStep == 10) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(anim->animBank);
            g_hugeAnimStruct.bankLoadStep = 0;
            return TRUE;
        }
    }
    return FALSE;
}
#pragma dont_inline off

// .text:0x80016F7C size:0x11C
BOOL fn_80016F7C(void) {
    Gap8001196CAnim* src;
    Gap8001196CAnim* dst;

    if (g_hugeAnimStruct.loadStarted == 0) {
        g_hugeAnimStruct.loadStarted = 1;
        g_hugeAnimStruct.bankLoadStep = 0;
        g_hugeAnimStruct.loadSlot = 0;
    }
    do {
        if (!fn_80016B60(&g_hugeAnimStruct.slots[g_hugeAnimStruct.loadSlot])) {
            break;
        }
        if (g_d_GameSettings.mode == 6) {
            src = &g_hugeAnimStruct.slots[g_hugeAnimStruct.loadSlot];
            dst = &g_hugeAnimStruct.slots[g_hugeAnimStruct.loadSlot + 4];
            dst->slotTables[0] = src->slotTables[0];
            dst->slotTables[1] = src->slotTables[1];
            dst->slotTables[2] = src->slotTables[2];
            dst->slotTables[3] = src->slotTables[3];
            dst->slotTables[4] = src->slotTables[4];
            dst->slotTables[5] = src->slotTables[5];
            dst->slotTables[6] = src->slotTables[6];
        }
        g_hugeAnimStruct.loadSlot++;
        if (g_hugeAnimStruct.loadSlot >= 4) {
            return TRUE;
        }
    } while (TRUE);
    return FALSE;
}

#pragma dont_inline on
// .text:0x80017098 size:0x2A8
/* fn_80017098 -- request a character load into a slot (or reuse a slot that already has it).
 *
 * team/player: inMemRoster[team][player] (0x5A0/0xA0 strides) supplies the charID when
 * charIDOverride < 0 (roster field 0x24); arg1B and variant (0x259) are copied into the slot;
 * slotKind is which logical slot (0..8 fielders, 9..12 batter/runner kinds) wants the character.
 * Returns TRUE when an already-loaded slot was reused, FALSE when a load task was queued.
 *
 * With charIDOverride >= 0 no search is done: a task is queued with slot = slotKind.  Otherwise the
 * 13 g_hugeAnimStruct.slots are scanned for one with the same charID (0x252), roster bytes
 * (0x25A/0x25B), player (0x257), team (0x256), unk258 (== arg1B) and variant (0x259); on a hit the
 * slot is re-owned (slotOwner[i] = slotKind, slots[i].slotKind = slotKind, slotPtrs[slotKind] =
 * &slots[i], loadState = 0) and no file is read.  On a miss a Gap8001196CLoadTask is queued for
 * fn_800177B4 (fn_800B0A5C_insertQueue), a free slot is picked (slotOwner[i] < 0; kinds >= 9 only
 * look at 9..12, defaulting to 13 = "none"), and loadState = 1 starts fn_80016344/fn_80016710.
 * Chain position: entry point of the charID -> model chain from game/menu code.
 * Variant hook: the per-player skin id would be read from the roster here (next to the charID
 * override) and stored in the task/slot so the loaders can key on (charID, skin); the reuse scan
 * already compares `variant` (0x259), which is the existing per-slot variant byte.
 * Match status: MATCH. */
BOOL fn_80017098(s32 team, s32 player, s32 arg1B, s32 slotKind, s32 variant, s32 charIDOverride) {
    Gap8001196CLoadTask* task;
    s32 i;
    s32 slot;
    BOOL sameRoster;

    if (charIDOverride >= 0) {
        task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
        slot = slotKind;
    } else {
        for (i = 0; i < 13; i++) {
            sameRoster = FALSE;
            if (g_hugeAnimStruct.slots[i].charID == inMemRoster[team][player].charID &&
                g_hugeAnimStruct.slots[i].rosterUnk26 == inMemRoster[team][player].unk26 &&
                g_hugeAnimStruct.slots[i].rosterUnk27 == inMemRoster[team][player].unk27 &&
                (s8)g_hugeAnimStruct.slots[i].player == (s8)player) {
                sameRoster = TRUE;
            }
            if (g_hugeAnimStruct.slots[i].team == team && sameRoster && g_hugeAnimStruct.slots[i].unk258 == arg1B &&
                g_hugeAnimStruct.slots[i].variant == variant) {
                g_hugeAnimStruct.loadState = 0;
                g_hugeAnimStruct.slotOwner[i] = slotKind;
                g_hugeAnimStruct.currentSlot = i;
                g_hugeAnimStruct.slots[i].slotKind = slotKind;
                for (slot = 0; slot < 13; slot++) {
                    if (g_hugeAnimStruct.slotPtrs[slot] == &g_hugeAnimStruct.slots[i]) {
                        g_hugeAnimStruct.slotPtrs[slot] = NULL;
                        break;
                    }
                }
                g_hugeAnimStruct.slotPtrs[slotKind] = &g_hugeAnimStruct.slots[i];
                return TRUE;
            }
        }
        task = fn_800B0A5C_insertQueue(fn_800177B4, 0);
        if (slotKind >= 9) {
            for (slot = 9; slot < 13; slot++) {
                if (g_hugeAnimStruct.slotOwner[slot] < 0) {
                    break;
                }
            }
        } else {
            for (slot = 0; slot < 13; slot++) {
                if (g_hugeAnimStruct.slotOwner[slot] < 0) {
                    break;
                }
            }
        }
    }
    task->unk14 = 0;
    task->slot = slot;
    task->team = team;
    task->player = player;
    task->unk1B = arg1B;
    task->slotKind = slotKind;
    task->variant = variant;
    if (charIDOverride < 0) {
        task->charID = inMemRoster[team][player].charID;
    } else {
        task->charID = charIDOverride;
    }
    g_hugeAnimStruct.slotOwner[slot] = slotKind;
    g_hugeAnimStruct.loadState = 1;
    g_hugeAnimStruct.currentSlot = slot;
    return FALSE;
}

// .text:0x80017340 size:0x24C
void fn_80017340(void) {
    return;
}

// .text:0x8001758C size:0x228
BOOL fn_8001758C(u8* state, s32 slot, u8 charID, u8 team, u8 player, u8 arg6, u8 slotKind, u8 variant) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    s32 track;
    Gap8001196CRosterEntry* entry;

    switch (*state) {
    case 0:
        if (lbl_803C6CF8.allowLoad == 1) {
            anim->unk25C = 1;
            anim->team = team;
            anim->player = player;
            anim->slotKind = slotKind;
            anim->charID = charID;
            anim->unk258 = arg6;
            anim->variant = variant;
            track = anim->charID * SUBFILE_TRACKS;
            entry = &inMemRoster[team][player];
            anim->rosterUnk26 = entry->unk26;
            anim->rosterUnk27 = entry->unk27;
            anim->isBatter = slotKind == 9;
            if (variant == 0) {
                track += 1;
            }
            if (anim->isBatter != 0 && variant == 1 && g_hugeAnimStruct.cachedBatterCharID == charID) {
                memcpy(anim->fileBuffer, g_hugeAnimStruct.cachedBatterData, g_hugeAnimStruct.cachedBatterSize);
                goto load;
            }
            if (slotKind >= 10 && slotKind <= 12 && variant == 0 && g_hugeAnimStruct.cachedFielderCharID == charID) {
                memcpy(anim->fileBuffer, g_hugeAnimStruct.cachedFielderData, g_hugeAnimStruct.cachedFielderSize);
                goto load;
            }
            if (variant == 0 || fn_8002204C(anim->charID, anim->fileBuffer) == NULL) {
                ARAMTransfer(&lbl_803CB790[track], anim->fileBuffer, 0, NULL);
            }
            *state = 1;
        }
        break;
    case 1:
        if (lbl_803716B8.loadBusy == 0 && lbl_803C6CF8.allowLoad == 1) {
        load:
            fn_80017814(anim, anim->blockIndex, slotKind, fn_8001FDD4);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// .text:0x800177B4 size:0x60
void fn_800177B4(void) {
    return;
}

// .text:0x80017814 size:0x514
/* fn_80017814 -- turn a loaded character .gpc file into an actor and hook it to its slot.
 *
 * anim: slot record whose fileBuffer (0x08) holds the relocated-in-place .gpc; index: actor id /
 * actor-entry index (g_hugeAnimStruct.actorEntries[index].slot, 0x90 stride, slot at +0x34);
 * slotKind: < 9 fielder (uses animBankA as the actor aux), else batter (animBankB); callback is
 * stored in the actor slot (+0x08, normally fn_8001FDD4).  No return value.
 *
 * Steps: (1) relocate the Gap8001196CRootHeader words 0x00 texture archive, 0x04 actor layout,
 * 0x08 geo palette, 0x0C skin, 0x10 extra (each += base when non-zero; a zero word stops the
 * chain); (2) convertTextureHeader(texture) [0x800C0770]; (3) if a layout exists:
 * LoadActorLayout, convertGeometryAndSknHeader(geo, skn), haveActLayoutPointToGeoHeader,
 * fn_800BD190(geo, texture) binds the texture archive to the geometry -- else return;
 * (4) fn_8002399C(slot, anim->blockIndex, index, layout, aux bank, skn) -> f_InitActorWithLayout;
 * (5) fn_80025DDC/fn_80025C58 for the extra block; (6) anim->boneIndices[boneID] = bone index
 * (120 u16 at 0x162, 0xFFFF = absent) from actor->boneArray[i]->boneID, then fn_800B2B74 for bone
 * ids 19/25/36, anim->actor = slot->actor, fn_800B2B54(actor, bone 3, 0xD), fn_800BD548(slot, 4,
 * g_hugeAnimStruct 0xAC..0xB8), CTRLSetTranslation/Rotation(&slot->control, 0), slot->unk54 = 0.5,
 * slot->unk5A = 1, fn_800B2BA8 + bone->unk136 = 1 for bone ids 3/2/1/46 (36 without the flag),
 * fn_800B2C08(actor, bone 4), fn_8001FC4C(anim); (7) reset anim ids 0x60..0x6E to -1 and the flag
 * bytes 0x25D..0x273 (0x277 = 0xFF); (8) per-charID setup switch (jumptable_800EEC40, 48 entries).
 * Chain position: fn_8001758C state 1 -> here -> fn_8002399C -> f_InitActorWithLayout.
 * Variant hook: the cheapest texture-only skin is to substitute root->texture (the archive handed
 * to convertTextureHeader and fn_800BD190) before step 2; the per-charID switch must be keyed on the
 * source character for a clone slot.
 * Match status: NOT matched -- 54 of ~325 lines differ: the root-header snapshot lands in r3 instead
 * of r7 in the prologue, the bone loop's byte-offset induction variable starts with li instead of
 * mr, and the argument evaluation order of the 2nd/3rd fn_800B2B74 calls; semantics identical. */
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
    aux = (slotKind < 9) ? anim->animBankA : anim->animBankB;
    fn_8002399C(slot, anim->blockIndex, index, layout, aux, skn);
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


// .text:0x80017D28 size:0x94
void fn_80017D28(void) {
    return;
}

// .text:0x80017DBC size:0x268
void fn_80017DBC(void) {
    return;
}

// .text:0x80018024 size:0x24C
void fn_80018024(void) {
    return;
}

// .text:0x80018270 size:0x650
void fn_80018270(void) {
    return;
}

// .text:0x800188C0 size:0xF8
void fn_800188C0(void) {
    return;
}

// .text:0x800189B8 size:0x2C
void fn_800189B8(void) {
    return;
}

// .text:0x800189E4 size:0x154
void fn_800189E4(void) {
    return;
}

// .text:0x80018B38 size:0x3C
void fn_80018B38(void) {
    return;
}

// .text:0x80018B74 size:0x278
void fn_80018B74(void) {
    return;
}

// .text:0x80018DEC size:0x8EC
void fn_80018DEC(void) {
    return;
}

// .text:0x800196D8 size:0x388
void fn_800196D8(void) {
    return;
}

// .text:0x80019A60 size:0x1A0
void fn_80019A60(void) {
    return;
}

// .text:0x80019C00 size:0x65C
void fn_80019C00(void) {
    return;
}

// .text:0x8001A25C size:0x1A0
void fn_8001A25C(void) {
    return;
}

// .text:0x8001A3FC size:0x2B4
void fn_8001A3FC(void) {
    return;
}

// .text:0x8001A6B0 size:0x3F4
void challengeMapRelated(void) {
    return;
}

// .text:0x8001AAA4 size:0x4C
void fn_8001AAA4(void) {
    return;
}

// .text:0x8001AAF0 size:0x20
void fn_8001AAF0(void) {
    fn_8003AC90();
}

// .text:0x8001AB10 size:0x488
void fn_8001AB10(void) {
    return;
}

// .text:0x8001AF98 size:0x268
void fn_8001AF98(void) {
    return;
}
