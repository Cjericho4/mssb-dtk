#include "Unknown/gap_800A6870.h"

// .text:0x800A6870 size:0x20
s32 fn_800A6870(u8 flag, s32 value) {
    s32 old;

    lbl_803C6CF8.unk6D8 = flag;
    old = lbl_803C6CF8.unk6D0;
    if (flag) {
        lbl_803C6CF8.unk6D0 = value;
    }
    return old;
}

// .text:0x800A6890 size:0x44
void fn_800A6890(void) {
    if (lbl_803C6CF8.running == 0) lbl_803C6CF8.state = 3;
    else OSSignalSemaphore(&lbl_803C6CF8.semaphore);
}

// .text:0x800A68D4 size:0x2C
void fn_800A68D4(void) {
    OSResumeThread(&lbl_803C6CF8.thread);
}

// .text:0x800A6900 size:0x380
void fn_800A6900(void) {
    return;
}

// .text:0x800A6C80 size:0x90
typedef void (*CancelCallback)(s32 result, Gap800A6870CommandBlock* block);
static inline CancelCallback cancelCallback(u8 state) {
    if (state == 0 || state == 3) return fn_800A75EC;
    return fn_800A7670;
}
void fn_800A6C80(void) {
    lbl_803C6CF8.stateBytes[0] = 0;
    lbl_803C6CF8.unk722 = 0;
    if ((s32)lbl_803C6CF8.stateBytes[1] != 1) {
        DVDCancelAsync(lbl_803C6CF8.block, cancelCallback(lbl_803C6CF8.state3));
        ARQRemoveOwnerRequest(2000);
    }
    lbl_803C6CF8.running = 0;
    lbl_803C6CF8.unk710 = 0;
}

// .text:0x800A6D10 size:0x114
void fn_800A6D10(void) {
    return;
}

// .text:0x800A6E24 size:0x170
void fn_800A6E24(void) {
    return;
}

// .text:0x800A6F94 size:0x148
void fn_800A6F94(void) {
    return;
}

// .text:0x800A70DC size:0x430
void ARAMTransfer(void) {
    return;
}

// .text:0x800A750C size:0x38
BOOL fn_800A750C(s32 unused, Gap800A6870DVDFile* file) {
    return DVDFastOpen(lbl_803C6CF8.entryNumber, file) != 0;
}

// .text:0x800A7544 size:0x24
s32 ConvertPathToEntryNum(Gap800A6870File* file) {
    return DVDConvertPathToEntrynum(file->path);
}

// .text:0x800A7568 size:0x84
void fn_800A7568(void) {
    void (*callback)(s32 result, struct Gap800A6870CommandBlock* block);
    lbl_803C6CF8.stateBytes[0] = 0;
    lbl_803C6CF8.unk722 = 0;
    switch (lbl_803C6CF8.stateBytes[1]) {
    case 1:
        break;
    default:
        if (lbl_803C6CF8.state3 == 0 || lbl_803C6CF8.state3 == 3) {
            callback = fn_800A75EC;
        } else {
            callback = fn_800A7670;
        }
        DVDCancelAsync(lbl_803C6CF8.block, callback);
        ARQRemoveOwnerRequest(2000);
        break;
    }
}

// .text:0x800A75EC size:0x84
void fn_800A75EC(s32 result, struct Gap800A6870CommandBlock* block) {
    Gap800A6870Decompressor* dec;
    Gap800A6870Load* load;
    OSCancelThread(&gDataDecompressorValues.thread);
    StartThreadForReadingFromDisk();
    dec = &gDataDecompressorValues;
    lbl_803C6CF8.stateWord = 1;
    if (dec->buffer != NULL) {
        fn_800ACF14(dec->buffer);
        dec->buffer = NULL;
    }
    load = &lbl_803C6CF8;
    if (load->memory != NULL) {
        fn_800ACF14(load->memory);
        load->memory = NULL;
    }
}

// .text:0x800A7670 size:0x4C
void fn_800A7670(s32 result, struct Gap800A6870CommandBlock* block) {
    Gap800A6870Load* load = &lbl_803C6CF8;
    load->stateWord = 1;
    if (load->memory != NULL) {
        fn_800ACF14(load->memory);
        load->memory = NULL;
    }
}

// .text:0x800A76BC size:0xE4
void fn_800A76BC(void) {
    return;
}

// .text:0x800A77A0 size:0x2E0
void fn_800A77A0(void) {
    return;
}

// .text:0x800A7A80 size:0x54
void fn_800A7A80(s32 result) {
    if (result == -3) {
        lbl_803C6CF8.running = 0;
        lbl_803C6CF8.pending = 0;
    } else if (result != -1) {
        OSResumeThread(&lbl_803C6CF8.thread);
    }
}

// .text:0x800A7AD4 size:0x4
void fn_800A7AD4(void) {
    return;
}

// .text:0x800A7AD8 size:0xD4
void fn_800A7AD8(void) {
    return;
}

// .text:0x800A7BAC size:0x5C
void fn_800A7BAC(u8 flag) {
    if (flag) {
        lbl_803C7420.unk397 = 2;
    } else {
        lbl_803C7420.unk397 = 0;
    }
    PPCSync();
    OSWakeupThread(&lbl_803C7420.queue380);
}

// .text:0x800A7C08 size:0x144
void fn_800A7C08(void) {
    return;
}

// .text:0x800A7D4C size:0x30
void fn_800A7D4C(s32 index, Gap800A6870PoolNode* node) {
    node->pointer = lbl_803C7420.heads[index] >> 2;
    lbl_803C7420.heads[index] = (u32)node | 1;
}

// .text:0x800A7D7C size:0x34
void fn_800A7D7C(Gap800A6870PoolNode* nodes, u32 count) {
    lbl_803C7420.heads = (u32*)nodes;
    count--;
    do {
        nodes->next = (u32)&nodes[1] | 1;
        nodes++;
    } while (--count != 0);
    nodes->next = 0;
}

// .text:0x800A7DB0 size:0x50
void fn_800A7DB0(void) {
    OSSleepThread(&lbl_803C7420.waiters);
    GXSetColorUpdate(1);
    VIFlush();
    GXDrawDone();
    GXCopyDisp(lbl_803C7420.framebuffer, 1);
}

// .text:0x800A7E00 size:0x110
void fn_800A7E00(void) {
    return;
}

// .text:0x800A7F10 size:0x1D8
void fn_800A7F10(void) {
    return;
}

// .text:0x800A80E8 size:0x3DC
void initRenderMode(void) {
    return;
}

// .text:0x800A84C4 size:0x54
void fn_800A84C4(void) {
    if (lbl_803C7420.paused == 0) {
        if ((s8)--lbl_803C7420.counter < 0) {
            lbl_803C7420.counter = lbl_803C7420.period;
            OSWakeupThread(&lbl_803C7420.waiters);
        }
    }
}

// .text:0x800A8518 size:0x19C
void fn_800A8518(void) {
    return;
}

// .text:0x800A86B4 size:0x1B0
void fn_800A86B4(void) {
    return;
}

// .text:0x800A8864 size:0x14
u16 fn_800A8864(void) {
    return (lbl_803CC135 << 8) | lbl_803CC134;
}

// .text:0x800A8878 size:0x48
void fn_800A8878(u8 left, u8 right) {
    lbl_803CC135 = left;
    lbl_803CC134 = right;
    if ((u32)lbl_803CC148 == 1) {
        AISetStreamVolLeft(left);
        AISetStreamVolRight(right);
    }
}

// .text:0x800A88C0 size:0x8
Gap800A6870Stream* fn_800A88C0(void) {
    return lbl_803CC154;
}

// .text:0x800A88C8 size:0x8
s32 fn_800A88C8(void) {
    return lbl_803CC148;
}

// .text:0x800A88D0 size:0x8
s32 fn_800A88D0(void) {
    return lbl_803CC140;
}

// .text:0x800A88D8 size:0x1D8
#pragma dont_inline on
void fn_800A88D8(u32 value) {
    return;
}

#pragma dont_inline reset

// .text:0x800A8AB0 size:0x8
void fn_800A8AB0(s32 value) {
    lbl_803CC140 = value;
}

// .text:0x800A8AB8 size:0xC0
void fn_800A8AB8(void) {
    return;
}

// .text:0x800A8B78 size:0x144
void fn_800A8B78(void) {
    return;
}

// .text:0x800A8CBC size:0x174
void LoadFile(void) {
    return;
}

// .text:0x800A8E30 size:0x138
void fn_800A8E30(void) {
    return;
}

// .text:0x800A8F68 size:0x74
void fn_800A8F68(void) {
    lbl_803CC148 = 0;
    *(volatile s32*)&lbl_803CC140 = 0;
    *(volatile s32*)&lbl_803CC13C = 0;
    *(volatile u32*)&lbl_803CC138 = 12000;
    lbl_803CC135 = 255;
    lbl_803CC154 = NULL;
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC134 = 255;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AIRegisterStreamCallback(fn_800A9168);
    AIResetStreamSampleCount();
    AISetStreamPlayState(0);
}

// .text:0x800A8FDC size:0x58
void fn_800A8FDC(void) {
    BOOL enabled;
    Gap800A6870Stream* stream;
    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    stream = lbl_803CC154;
    if (stream != NULL && stream->previous != NULL) lbl_803CC154 = stream->previous;
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = 0;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A9034 size:0x58
void fn_800A9034(void) {
    BOOL enabled;
    Gap800A6870Stream* stream;
    AISetStreamPlayState(0);
    enabled = OSDisableInterrupts();
    stream = lbl_803CC154;
    if (stream != NULL && stream->next != NULL) lbl_803CC154 = stream->next;
    OSRestoreInterrupts(enabled);
    lbl_803CC148 = 0;
    fn_800A88D8(lbl_803CC144);
}

// .text:0x800A908C size:0x58
void fn_800A908C(void) {
    u32 flags;
    AISetStreamPlayState(0);
    if (lbl_803CC154 != NULL && lbl_803CC154->callback != NULL) {
        if ((flags = lbl_803CC154->flags & 2) != 0) lbl_803CC154->callback(flags);
    }
    lbl_803CC148 = 0;
}

// .text:0x800A90E4 size:0x84
void fn_800A90E4(void) {
    Gap800A6870Stream* stream;
    AISetStreamPlayState(0);
    for (stream = lbl_803CC150; stream != NULL; stream = stream->next) {
        DVDClose(&stream->file);
    }
    lbl_803CC150 = NULL;
    lbl_803CC14C = NULL;
    lbl_803CC154 = NULL;
    lbl_803CC148 = 0;
    if (lbl_803CC128 != NULL) {
        lbl_803CC128();
        lbl_803CC128 = NULL;
    }
    lbl_803CC148 = 0;
    lbl_803CC130 = 0;
}

// .text:0x800A9168 size:0x48
void fn_800A9168(u32 trigger) {
    AISetStreamTrigger(trigger + lbl_803CC138);
    if ((u32)lbl_803CC154 != 0) DVDGetStreamPlayAddrAsync(&lbl_802EF200, fn_800A91B0);
}

// .text:0x800A91B0 size:0x1FC
void fn_800A91B0(void) {
    return;
}

// .text:0x800A93AC size:0x78
void fn_800A93AC(void) {
    Gap800A6870Stream* stream;
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    AISetStreamPlayState(0);
    DVDStopStreamAtEndAsync(&lbl_802EF260, NULL);
    stream = lbl_803CC154;
    lbl_803CC148 = 2;
    if (stream != NULL && stream->callback != NULL && (stream->flags & 0x20)) {
        stream->callback(stream->flags & 0x20);
    }
}

// .text:0x800A9424 size:0x84
void fn_800A9424(void) {
    Gap800A6870Stream* stream;
    AISetStreamVolLeft(lbl_803CC135);
    AISetStreamVolRight(lbl_803CC134);
    AIResetStreamSampleCount();
    AISetStreamTrigger(lbl_803CC138);
    AISetStreamPlayState(1);
    DVDStopStreamAtEndAsync(&lbl_802EF290, NULL);
    stream = lbl_803CC154;
    lbl_803CC148 = 1;
    if (stream != NULL && stream->callback != NULL && (stream->flags & 1)) {
        stream->callback(stream->flags & 1);
    }
}

// .text:0x800A94A8 size:0x1C
void fn_800A94A8(u8 flag) {
    if (!flag) {
        lbl_803CC12C = 1;
        lbl_803CC13C = 0;
    }
}

// .text:0x800A94C4 size:0x5C
void fn_800A94C4(void) {
    u32 mask = 0;
    Gap800A6870Pad* p = lbl_803C77B8;
    s32 i = 0;
    do {
        if (p->err == 0) {
            mask |= 0x80000000 >> i;
        }
        i++;
        p++;
    } while (i < 4);
    PADRecalibrate(mask);
}

// .text:0x800A9520 size:0x2B0
void fn_800A9520(void) {
    return;
}
