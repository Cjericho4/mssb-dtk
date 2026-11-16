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
/* FAKEMATCH: kept out of line while it is an empty stub, so its callers still call it. */
#pragma dont_inline on
void fn_80039AC0(void) {
    return;
}
#pragma dont_inline reset

// .text:0x80039FF8 size:0x98
void fn_80039FF8(Gap80039AA8RenderMode* mode) {
    u32 width;
    u32 height;
    if (mode->flags & 1) {
        height = mode->height;
        width = mode->width;
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(width, height, 4, width != 640);
        GXCopyTex(&lbl_8023DD80, 0);
        GXPixModeSync();
        lbl_800F7A40.width = width;
        lbl_800F7A40.height = height;
    }
}

// .text:0x8003A090 size:0xB4
// On the GX thread, when screen flag 0x01 or 0x10 is set: copies the 640x448 frame buffer into
// lbl_8023DD80 at the screen's capture size (unk10 x unk12) and records that size.
void fn_8003A090(void) {
    u32 width;
    u32 height;

    if (GXGetCurrentGXThread() == OSGetCurrentThread() && (lbl_803C5090.unk1D & 0x11)) {
        height = lbl_803C5090.unk12;
        width = lbl_803C5090.unk10;
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(width, height, 4, width != 640);
        GXCopyTex(&lbl_8023DD80, 0);
        GXPixModeSync();
        lbl_800F7A40.width = width;
        lbl_800F7A40.height = height;
    }
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
// Queue task (runs once): sets the capture size to 320x224 when screen flag 2 is set, else
// 640x448; when flag 1 is set without 0x10 it also saves the screen settings into the current
// lbl_800F7A60 record and registers it with fn_800A7D4C(8); then runs fn_80039AC0.
void fn_8003A1D0(void) {
    if (lbl_803C5090.unk1D & 2) {
        lbl_803C5090.unk10 = 320;
        lbl_803C5090.unk12 = 224;
        lbl_800F7A40.width = 320;
        lbl_800F7A40.height = 224;
    } else {
        lbl_803C5090.unk10 = 640;
        lbl_803C5090.unk12 = 448;
        lbl_800F7A40.width = 640;
        lbl_800F7A40.height = 448;
    }
    if ((lbl_803C5090.unk1D & 0x11) == 1) {
        lbl_800F7A60[lbl_803CBBC0].screen = lbl_803C5090;
        fn_800A7D4C(8, &lbl_800F7A60[lbl_803CBBC0]);
    }
    fn_80039AC0();
    fn_800B0A14_removeQueue();
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
// Sets up untextured drawing in one flat grey (level lbl_803CBCB4, opaque): one colour channel
// with lighting off and one TEV stage that passes the rasterised colour and alpha through.
void fn_8003AC90(void) {
    Gap80039AA8Color color;

    color.a = 0xFF;
    color.b = lbl_803CBCB4;
    color.g = lbl_803CBCB4;
    color.r = lbl_803CBCB4;
    GXSetChanMatColor(4, color);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevColorIn(0, 10, 15, 15, 15);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 5, 7, 7, 7);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
}

// .text:0x8003AD84 size:0xD0
// Builds the shared colour-indexed texture object (CI4, 16-colour palette lbl_800F7AC0, TLUT
// slot 0) from a texture description, with its filter and LOD settings.
void fn_8003AD84(Gap80039AA8TexDesc* desc) {
    GXInitTexObjCI(&lbl_803C50B0, desc->image, desc->width, desc->height, 8, desc->wrapS, desc->wrapT, 0, 0);
    GXInitTlutObj(&lbl_803C50DC, lbl_800F7AC0, 0, 16);
    GXInitTexObjLOD(&lbl_803C50B0, desc->minFilter, desc->magFilter, desc->minLod, desc->maxLod, desc->lodBias, 0, 0,
                    0);
    lbl_803CBCAC = 1;
}
