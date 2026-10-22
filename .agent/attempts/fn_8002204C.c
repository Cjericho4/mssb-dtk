// Best attempt (82 sbs lines of ~250, from a stub). Types: Gap8001E460DataBlock (lbl_800EFBE8 block: master words @0x150, subfiles @0x2190, bodyItems pairs @0x77D0), Gap8001E460LoadRecord/Flags ring in include/Unknown/gap_8001E460.h.
// Left: the target forms every sub-table address as (r31+const) THEN adds the index ('addi r4,r31,0x150; slwi; add'), and reads the size with lwzx (index = charID*16+4); MWCC folds the constants into the displacement for every struct/array/cast form tried (direct, block-local pointer, u8 byte offsets, 2D arrays, inline accessor). A block-local pointer with two uses reproduces the pairs table exactly, so the original probably used pointer locals per table that were rematerialized; the inlined push (fn_80022CB4) and the queue kick (processLoadQueueInline) otherwise match.
/* inline copies of fn_80022CB4 / the queue kick in gap_8002244C.c */
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

// .text:0x8002204C size:0x400
u8* fn_8002204C(s32 charID, u8* buf) {
    Gap8001E460DataBlock* data = &lbl_800EFBE8;
    s32 item;
    s32 subItem;

    if (charID < 0 || charID >= 54) {
        return NULL;
    }
    if (buf == NULL) {
        buf = _OSAllocFromHeap(0x20, ((DiskFileDesc*)data->master)[charID].sizeFlags & 0x0FFFFFFF);
    }
    if (lbl_803716B8.unk1EA & 1) {
        s8 (*pairs)[2] = data->bodyItems;
        item = pairs[charID][0];
        subItem = pairs[charID][1];
        if (subItem == -1) {
            queueLoadInline((DiskFileDesc*)data->master + item, buf, 3, lbl_803716B8.bodyAramAddrs[item], fn_80022620, 0);
        } else {
            queueLoadInline((DiskFileDesc*)data->master + item, buf, 3, lbl_803716B8.bodyAramAddrs[item], fn_8002254C, subItem);
        }
    } else {
        queueLoadInline((DiskFileDesc*)data->subfiles + charID * 19, buf, 0, NULL, fn_80022620, 0);
    }
    lbl_803716B8.unk1E8 = 1;
    fn_800B0A5C_insertQueue(fn_80022634, 0);
    processLoadQueueInline();
    return buf;
}
