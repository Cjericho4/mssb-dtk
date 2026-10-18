#include "Unknown/gap_80039AA8.h"

// .text:0x80039AA8 size:0xC
Gap80039AA8Texture* GetUITexture(void) {
    return &lbl_8023DD80;
}

// .text:0x80039AB4 size:0xC
Gap80039AA8Table* fn_80039AB4(void) {
    return &lbl_800F7A40;
}

// .text:0x80039AC0 size:0x538
void fn_80039AC0(void) {
    return;
}

// .text:0x80039FF8 size:0x98
void fn_80039FF8(void) {
    return;
}

// .text:0x8003A090 size:0xB4
void fn_8003A090(void) {
    return;
}

// .text:0x8003A144 size:0x8C
void fn_8003A144(void) {
    Gap80039AA8Thread* thread = OSGetCurrentThread();
    if (GXGetCurrentGXThread() == thread) {
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 448, 4, 0);
        GXCopyTex(&lbl_8023DD80, 0);
        GXPixModeSync();
        lbl_800F7A40.width = 640;
        lbl_800F7A40.height = 448;
    }
}

// .text:0x8003A1D0 size:0xF0
void fn_8003A1D0(void) {
    return;
}

// .text:0x8003A2C0 size:0x2C
void fn_8003A2C0(void) {
    fn_800B0A5C_insertQueue(fn_8003A1D0, 0x6001);
}

// .text:0x8003A2EC size:0x90
void fn_8003A2EC(void) {
    lbl_803C5090.unk1D = 1;
    lbl_803C5090.unk17 = 0x60;
    lbl_803C5090.unk0 = 30.0f;
    lbl_803C5090.unk8 = 1.0f;
    lbl_803C5090.unkC = 1.0f;
    lbl_803C5090.unk10 = 320;
    lbl_803C5090.unk12 = 224;
    memset((u8*)&lbl_8023DD80, 0, 0x96000);
    lbl_803C5090.unk14 = 448;
    lbl_803C5090.unk1A = 0xFF;
    lbl_803C5090.unk1B = 0xFF;
    lbl_803C5090.unk1C = 0xFF;
}

// .text:0x8003A37C size:0x14C
void fn_8003A37C(void) {
    return;
}

// .text:0x8003A4C8 size:0x70
#pragma dont_inline on
void fn_8003A4C8(void) {
    if (GetDrawShadows()) {
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 448, 4, 0);
        GXCopyTex(GetUITexture(), 1);
        GXPixModeSync();
        fn_800BEB3C();
        fn_800BD1E8(fn_8003A37C);
    }
}
#pragma dont_inline reset

// .text:0x8003A538 size:0x8
s32 fn_8003A538(void) {
    return lbl_803CBCB0;
}

// .text:0x8003A540 size:0x8
void fn_8003A540(s32 value) {
    lbl_803CBCB0 = value;
}

// .text:0x8003A548 size:0x8
void fn_8003A548(s32 value) {
    lbl_803CBCA8 = value;
}

// .text:0x8003A550 size:0x138
void fn_8003A550(void) {
    return;
}

// .text:0x8003A688 size:0x28
void fn_8003A688(s32 index, f32 x, f32 y) {
    f32 half = 0.5f;
    lbl_802D3D80.positions[index].x = x * half;
    lbl_802D3D80.positions[index].y = y * half;
}

// .text:0x8003A6B0 size:0x198
void fn_8003A6B0(void) {
    return;
}

// .text:0x8003A848 size:0x14
void fn_8003A848(u8 a, u8 b, u8 c) {
    lbl_803CB828[0] = a;
    lbl_803CB828[1] = b;
    lbl_803CB828[2] = c;
}

// .text:0x8003A85C size:0x44
void fn_8003A85C(u8 mode) {
    lbl_802D3D80.mode = mode;
    lbl_802D3D80.countA00 = 0;
    lbl_802D3D80.countA02 = 0;
    memset(lbl_802D3D80.flags, 0, 13);
}

// .text:0x8003A8A0 size:0x3F0
void fn_8003A8A0(void) {
    return;
}

// .text:0x8003AC90 size:0xF4
void fn_8003AC90(void) {
    return;
}

// .text:0x8003AD84 size:0xD0
void fn_8003AD84(void) {
    return;
}
