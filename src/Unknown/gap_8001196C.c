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

// .text:0x80016344 size:0x3CC
BOOL fn_80016344(u8 charID, s32 slot, u8 stance, s32 player) {
    return;
}

// .text:0x80016710 size:0x450
BOOL fn_80016710(u8 charID, s32 slot) {
    return;
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
void fn_80017814(Gap8001196CAnim* anim, s32 index, s32 slotKind, void (*callback)(struct Gap8001E460Object*)) {
    return;
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
