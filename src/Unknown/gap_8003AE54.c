#include "Unknown/gap_8003AE54.h"

// .text:0x8003AE54 size:0x8
u8 fn_8003AE54(void) {
    return lbl_803CBCB4;
}

// .text:0x8003AE5C size:0x8
void fn_8003AE5C(u8 value) {
    lbl_803CBCB4 = value;
}

// .text:0x8003AE64 size:0xC
void fn_8003AE64(void) {
    lbl_803CBCB8 = 0x0;
}

// .text:0x8003AE70 size:0x5C
u8 fn_8003AE70(s32 arg0) {
    u8 ret = 0;
    switch (arg0) {
    case 0:
        ret = lbl_802D4B00.unk95;
        break;
    case 1:
        ret = lbl_802D4B00.unk94;
        break;
    case 2:
        ret = lbl_802D4B00.unk96;
        break;
    }
    return ret;
}

// .text:0x8003AECC size:0x6E4
void fn_8003AECC(void) {
    return;
}

// .text:0x8003B5B0 size:0x5E0
void fn_8003B5B0(void) {
    return;
}

// .text:0x8003BB90 size:0x3C4
void fn_8003BB90(void) {
    return;
}

// .text:0x8003BF54 size:0xB8
void fn_8003BF54(void) {
    return;
}

// .text:0x8003C00C size:0x28CC
void fn_8003C00C(void) {
    return;
}

// .text:0x8003E8D8 size:0x964
void fn_8003E8D8(void) {
    return;
}

// .text:0x8003F23C size:0x7C
void fn_8003F23C(void) {
    Gap8003AE54Task* task = fn_800B0A5C_insertQueue(fn_8003F2B8, 0x8000);
    task->unk14 = 0;
    task->unk15 = 0;
    task->unk16 = 0;
    task->unk17 = 0;
    task->unk18 = 0;
    task->unk1A = 0;
    task->unk1B = 7;
    task->unk1D = 0;
    task->unk21 = 0;
    lbl_803CC1B8[0]->unk10 = 0;
    lbl_802D4AE0.unkC = 0;
    lbl_802D4AE0.unk8 = 0;
    lbl_802D4AE0.unk4 = 0;
    lbl_802D4AE0.unk0 = 0;
}

// .text:0x8003F2B8 size:0x1284
void fn_8003F2B8(void) {
    return;
}

// .text:0x8004053C size:0x6D8
void fn_8004053C(void) {
    return;
}

// .text:0x80040C14 size:0x3CC
void fn_80040C14(void) {
    return;
}

// .text:0x80040FE0 size:0x94
s32 fn_80040FE0(Gap8003AE54Save* save) {
    u8* data = save->data;
    Gap8003AE54SaveBlock* block;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            save->checksum = fn_800ABB14(data, sizeof(save->data));
        } else {
            block = &save->blocks[i - 1];
            block->checksum = fn_800ABB14(block->data, sizeof(block->data));
        }
    }
    return 17;
}

// .text:0x80041074 size:0xDC
void fn_80041074(void) {
    return;
}

// .text:0x80041150 size:0x1F8
void fn_80041150(void) {
    return;
}
