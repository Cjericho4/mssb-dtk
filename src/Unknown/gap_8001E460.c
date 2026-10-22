#include "Unknown/gap_8001E460.h"

// .text:0x8001E460 size:0x14
void fn_8001E460(s32 value) {
    lbl_803CB7AC[lbl_803CBBC0] = value;
}

// .text:0x8001E474 size:0x14
void fn_8001E474(void) {
    lbl_803CB7AC[0] = 0;
    lbl_803CB7AC[1] = 0;
}

// .text:0x8001E488 size:0x2FC
void fn_8001E488(void) {
    return;
}

// .text:0x8001E784 size:0x9E8
void fn_8001E784(void) {
    return;
}

// .text:0x8001F16C size:0xBC
void fn_8001F16C(void) {
    return;
}

// .text:0x8001F228 size:0x298
void fn_8001F228(void) {
    return;
}

// .text:0x8001F4C0 size:0x128
void challengeMapMaybe(void) {
    return;
}

// .text:0x8001F5E8 size:0x2BC
void fn_8001F5E8(void) {
    return;
}

// .text:0x8001F8A4 size:0x3A8
void fn_8001F8A4(void) {
    return;
}

// .text:0x8001FC4C size:0x188
void fn_8001FC4C(void) {
    return;
}

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(Gap8001E460Object* obj) {
    if (obj->fog != 0) {
        fn_800B9AA8(obj->fog);
    }
}

// .text:0x8001FE00 size:0x248
void fn_8001FE00(void) {
    return;
}

// .text:0x80020048 size:0x1D0
void calledWhenStartingMatch(void) {
    return;
}

// .text:0x80020218 size:0x34
BOOL fn_80020218(void) {
    if ((u32)lbl_8037169C.state == 13 || (u32)lbl_8037169C.state == 14 || (u32)lbl_8037169C.state == 15) return 1;
    return 0;
}

// .text:0x8002024C size:0x2C
void fn_8002024C(void) {
    fn_800ACF14(lbl_8037169C.resource);
}

// .text:0x80020278 size:0x110
void fn_80020278(void) {
    return;
}

// .text:0x80020388 size:0x58
BOOL fn_80020388(void) {
    return fn_80035838(&lbl_800EEFD0[lbl_803CB7CC[g_d_GameSettings.unk9] + 0x26], 0xD) != 0;
}

// .text:0x800203E0 size:0xEC
void fn_800203E0(void) {
    return;
}

// .text:0x800204CC size:0xD0
void changeScene(void) {
    return;
}

// .text:0x8002059C size:0x88
void fn_8002059C(void) {
    Gap8001E460QueueNode* task = lbl_803CC1B8;
    if (lbl_8037169C.state == 7 && lbl_80371C30[task->index].stage->status == 2) {
        lbl_8037169C.pending = 1;
        lbl_8037169C.state = 0;
    } else {
        lbl_8037169C.pending = 0;
        return;
    }
    lbl_8037169C.ready = 0;
    fn_80034CEC(task);
    fn_800B0A14_removeQueue();
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    return;
}

// .text:0x800206FC size:0x968
void fn_800206FC(void) {
    return;
}

// .text:0x80021064 size:0x124
void fn_80021064(void) {
    return;
}

// .text:0x80021188 size:0x34
s32 fn_80021188(void) {
    sndMasterVolume(127, 1, 1, 1);
    return 0;
}

// .text:0x800211BC size:0x34
s32 fn_800211BC(void) {
    sndMasterVolume(0, 1, 1, 1);
    return 0;
}

// .text:0x800211F0 size:0x14
u8 fn_800211F0(void) {
    return lbl_800EFBC0.unk18;
}

// .text:0x80021204 size:0x24
void fn_80021204(void) {
    lbl_800E8754.unk23 = lbl_800EF808.unk398;
    lbl_800E8754.unk24 = lbl_800EF808.soundMode;
}

// .text:0x80021228 size:0x64
void fn_80021228(u8 mode) {
    s32 value = 1;

    if (mode) {
        value = mode;
    }
    lbl_800EF808.unk397 = value;
    lbl_800EF808.soundMode = mode;
    sndOutputMode(mode);
    OSSetSoundMode(lbl_800EF808.soundMode != 0);
}

// .text:0x8002128C size:0x7C
void fn_8002128C(u8 mode) {
    s32 value = 1;

    if (mode) {
        value = mode;
    }
    lbl_800EF808.unk397 = value;
    if (OSGetSoundMode() == 0) {
        mode = 0;
    } else if (mode != 2) {
        mode = 1;
    }
    lbl_800EF808.soundMode = mode;
    sndOutputMode(mode);
}

// .text:0x80021308 size:0xEC
void fn_80021308(void) {
    return;
}

// .text:0x800213F4 size:0x4
void fn_800213F4(void) {
    return;
}

// .text:0x800213F8 size:0x18
void fn_800213F8(u32 size) {
    lbl_803CBC40 += (size + 0x1F) & ~0x1F;
}

// .text:0x80021410 size:0x8C
static inline BOOL gap8001E460_popGroup(void) {
    if (sndPopGroup() == 0) {
        return FALSE;
    }
    lbl_800EF808.groupCount--;
    return TRUE;
}

BOOL fn_80021410(void) {
    s8 i;

    for (i = (s8)lbl_800EF808.groupCount - 1; i > 0; i--) {
        if (!gap8001E460_popGroup()) {
            return FALSE;
        }
    }
    return TRUE;
}

// .text:0x8002149C size:0x34
void fn_8002149C(s32 index) {
    fn_800ACFB0(lbl_800EF808.resources[index]);
}

// .text:0x800214D0 size:0x48
BOOL fn_800214D0(void) {
    if (sndPopGroup() == 0) return 0;
    lbl_800EF808.groupCount--;
    return 1;
}

// .text:0x80021518 size:0x74
BOOL fn_80021518(u16 gid, Gap8001E460Resource* res) {
    if (!sndPushGroup(res->project, gid, res->end, res->sdir, res->pool)) {
        return FALSE;
    }
    lbl_800EF808.groups[lbl_800EF808.groupCount++] = gid;
    return TRUE;
}

// .text:0x8002158C size:0x6C
s32 fn_8002158C(void) {
    Gap8001E460Resource* res = lbl_800EF808.resources[0];

    if (sndPushGroup(res->project, 0x1E, res->end, res->sdir, res->pool)) {
        lbl_800EF808.groups[lbl_800EF808.groupCount++] = 0x1E;
    }
    return 0;
}

// .text:0x800215F8 size:0x58
void fn_800215F8(Gap8001E460Load* load) {
    load->sub->unk10 = 0;
    fn_80022CB4(&lbl_800EF508[load->index], 0, 1, 0, fn_80021650, load);
}

// .text:0x80021650 size:0xA8
void fn_80021650(void) {
    return;
}

// .text:0x800216F8 size:0x60
void fn_800216F8(u8 a, s32 b) {
    Gap8001E460Task* task = fn_800B0A5C_insertQueue(fn_80021758, 1);
    task->unk18 = 0;
    task->unk19 = a;
    task->unk14 = b;
    lbl_803CC1B8->unk10 = 0;
}

// .text:0x80021758 size:0x1FC
void fn_80021758(void) {
    return;
}

// .text:0x80021954 size:0x2C
void fn_80021954(Gap8001E460Resource** resource) {
    fn_800ACF78(*resource, (u32)(*resource)->end - (u32)*resource);
}

// .text:0x80021980 size:0x34
void fn_80021980(void) {
    return;
}

// .text:0x800219B4 size:0xEC
void f_initSound(void) {
    return;
}

// .text:0x80021AA0 size:0x20
void fn_80021AA0(void) {
    fn_800ACD44();
}

// .text:0x80021AC0 size:0x4
void fn_80021AC0(void) {
    return;
}

// .text:0x80021AC4 size:0x4
void fn_80021AC4(void) {
    return;
}

// .text:0x80021AC8 size:0x14
void fn_80021AC8(void) {
    lbl_803716B8.unk55C = 0;
}

// .text:0x80021ADC size:0xE0
void fn_80021ADC(void) {
    return;
}

// .text:0x80021BBC size:0xE8
void* fn_80021BBC(s32 charID, void* buf) {
    DiskFileDesc* desc;

    if (charID < 0 || charID >= 54) {
        return NULL;
    }
    if (buf == NULL) {
        desc = &lbl_800EFD38[MASTER_DESC_SKELETON_BASE + charID];
        buf = _OSAllocFromHeap(0x20, desc->sizeFlags & 0x0FFFFFFF);
    }
    if (lbl_803716B8.unk1EA & 2) {
        desc = &lbl_800EFD38[MASTER_DESC_SKELETON_BASE + charID];
        ARAMTransfer(desc, buf, 3, lbl_803716B8.aramAddrs[charID]);
    } else {
        ARAMTransfer(&lbl_800F1D78[charID * SUBFILE_TRACKS + SUBFILE_TRACK_SKELETON], buf, 0, NULL);
    }
    return buf;
}

/* ---- shared disc-load queue helpers (lbl_803716B8 ring, 18 records) ---------------------------
 * These are inline copies of fn_80022CB4 (push) and the queue kick that gap_8002244C.c owns; the
 * loaders below have them inlined in the retail binary. */
static inline BOOL queueLoadInline(DiskFileDesc* desc, void* dest, s32 mode, void* aramAddr,
                                   Gap8001E460DiskLoadCallback callback, s32 param) {
    Gap8001E460LoadRecord* rec;
    s8 next = (lbl_803716B8.head + 1) % 18;
    if (next == lbl_803716B8.tail || (dest == NULL && callback == NULL)) {
        return FALSE;
    }
    lbl_803716B8.pending = 1;
    rec = &lbl_803716B8.recs[lbl_803716B8.head];
    rec->desc = desc;
    rec->dest = dest;
    rec->mode = mode;
    rec->aramAddr = aramAddr;
    rec->callback = callback;
    rec->param = param;
    lbl_803716B8.head = next;
    return TRUE;
}

/* Run the finished record's callback, then start the next ARAMTransfer (or idle the queue). */
static inline void processLoadQueueInline(void) {
    Gap8001E460LoadRecord* rec;
    if (lbl_803716B8.pending != 0 && lbl_803C6CF8.allowLoad == 1) {
        if (lbl_803716B8.current.callback != NULL) {
            lbl_803716B8.current.callback(lbl_803716B8.current.desc, lbl_803716B8.current.dest, lbl_803716B8.current.param);
        }
        if (lbl_803716B8.tail != lbl_803716B8.head) {
            rec = &lbl_803716B8.recs[lbl_803716B8.tail];
            rec->dest = ARAMTransfer(rec->desc, rec->dest, rec->mode, rec->aramAddr);
            lbl_803716B8.current = *rec;
            lbl_803716B8.tail = (lbl_803716B8.tail + 1) % 18;
        } else {
            lbl_803716B8.current.callback = NULL;
            lbl_803716B8.pending = 0;
        }
    }
}

/* fn_80021CA4 -- queue the load of a character's sub-item model pair (bat/glove/... track).
 *
 * charID   0..53 character slot; itemSlot 0..5 which sub-item pair; buf destination (NULL = allocate
 * from the heap: aligned size of both master descriptors).  Returns buf, or NULL on a bad index.
 *
 * Tables (all relative to lbl_800EFBE8, see Gap8001E460DataBlock):
 *   subItemKind[charID]            0x800F743C  row of subItemPairs used by this character
 *   subItemPairs[kind][itemSlot]   0x800F7424  {k1, k2}: sub-item ids within the character's 7
 *   master[54 + charID*7 + k]      0x800EFD38  master descriptors of the two sub-item files (ARAM path)
 *   subItemFiles[charID][itemSlot] 0x800F5D98  disc descriptor for the pair (disc path)
 *   lbl_803716B8.unk1EA bit 1      sub-items/skeletons resident in ARAM
 *   lbl_803716B8.subItemAramAddrs  per-sub-item ARAM copies
 * ARAM path: queues master[54+item1] with callback fn_8002244C(param = item1 << 16 | item2), which
 * in turn queues item2 behind it.  Disc path: one ARAMTransfer of subItemFiles[charID][itemSlot].
 * Chain position: called by the per-slot loaders after the body model (fn_8002204C).
 * Variant hook: charID is only used to pick subItemKind/bodyItems rows and the 54+charID*7 range,
 * so a (charID, skin) table of alternate sub-item ids/descriptors plugs in right here.
 * Match status: NOT matched (same sub-table addressing issue as fn_8002204C: the retail code forms
 * (lbl_800EFBE8+const)+index and reads sizes with lwzx; this body is semantically identical). */
// .text:0x80021CA4 size:0x3A8
u8* fn_80021CA4(s32 charID, s32 itemSlot, u8* buf) {
    Gap8001E460DataBlock* data = &lbl_800EFBE8;
    s32 kind;
    s32 item1;
    s32 item2;
    u32 size1;
    u32 size2;

    if (charID < 0 || charID >= 54) {
        return NULL;
    }
    if (itemSlot < 0 || itemSlot >= 6) {
        return NULL;
    }
    {
        s8 (*pairRows)[6][2] = data->subItemPairs;
        kind = data->subItemKind[charID];
        item1 = charID * SUBITEMS_PER_CHAR + pairRows[kind][itemSlot][0];
        item2 = charID * SUBITEMS_PER_CHAR + pairRows[kind][itemSlot][1];
    }
    if (buf == NULL) {
        size1 = ((data->master[MASTER_DESC_SUBITEM_BASE + item1].sizeFlags & 0x0FFFFFFF) + 0x1F) & ~0x1F;
        size2 = ((data->master[MASTER_DESC_SUBITEM_BASE + item2].sizeFlags & 0x0FFFFFFF) + 0x1F) & ~0x1F;
        buf = _OSAllocFromHeap(0x20, size1 + size2);
    }
    if (lbl_803716B8.unk1EA & 2) {
        queueLoadInline(&data->master[MASTER_DESC_SUBITEM_BASE + item1], buf, 3, lbl_803716B8.subItemAramAddrs[item1],
                        fn_8002244C, (item1 << 16) | item2);
    } else {
        queueLoadInline(&data->subItemFiles[charID][itemSlot], buf, 0, NULL, fn_80022620, 0);
    }
    lbl_803716B8.unk1E8 = 1;
    fn_800B0A5C_insertQueue(fn_80022634, 0);
    processLoadQueueInline();
    return buf;
}

/* fn_8002204C -- queue the load of a character's body model (the track-0 .gpc / master body file).
 *
 * charID 0..53; buf destination (NULL = allocate aligned master[charID] size).  Returns buf or NULL.
 * Tables: master[charID] (body descriptor, size), bodyItems[charID] = {master index to stream,
 *   sub-item id or -1} at 0x800F73B8 (ARAM path, lbl_803716B8.unk1EA bit 0), subfiles[charID][0]
 *   (disc path), lbl_803716B8.bodyAramAddrs[master index].
 * ARAM path: queues master[bodyItems[c][0]]; if bodyItems[c][1] != -1 the completion callback is
 * fn_8002254C with that sub-item id (it chains the sub-item load), else fn_80022620.
 * Chain position: fn_8001758C(variant != 0) -> fn_8002204C -> load queue -> fn_80017814 once the
 * file is in memory (lbl_803716B8.unk1E8 cleared by fn_80022620).
 * Variant hook: every charID use here (bodyItems row, master size, subfiles row) is cosmetic, so a
 * skin table that maps (charID, skin) -> {bodyItems pair, body descriptor, subfile row} is the
 * natural place to redirect a clone's model without touching stats.
 * Match status: NOT matched -- the retail code keeps &lbl_800EFBE8 in r31 and forms each table
 * address as (r31 + table offset) + index (size read via lwzx); MWCC folds those constants for every
 * struct/array form tried.  Semantics are identical. */
// .text:0x8002204C size:0x400
u8* fn_8002204C(s32 charID, u8* buf) {
    Gap8001E460DataBlock* data = &lbl_800EFBE8;
    s32 bodyIndex;
    s32 subItem;

    if (charID < 0 || charID >= 54) {
        return NULL;
    }
    if (buf == NULL) {
        buf = _OSAllocFromHeap(0x20, data->master[charID].sizeFlags & 0x0FFFFFFF);
    }
    if (lbl_803716B8.unk1EA & 1) {
        bodyIndex = data->bodyItems[charID][0];
        subItem = data->bodyItems[charID][1];
        if (subItem == -1) {
            queueLoadInline(&data->master[bodyIndex], buf, 3, lbl_803716B8.bodyAramAddrs[bodyIndex], fn_80022620, 0);
        } else {
            queueLoadInline(&data->master[bodyIndex], buf, 3, lbl_803716B8.bodyAramAddrs[bodyIndex], fn_8002254C, subItem);
        }
    } else {
        queueLoadInline(&data->subfiles[charID][0], buf, 0, NULL, fn_80022620, 0);
    }
    lbl_803716B8.unk1E8 = 1;
    fn_800B0A5C_insertQueue(fn_80022634, 0);
    processLoadQueueInline();
    return buf;
}
