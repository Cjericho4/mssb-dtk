#ifndef __UNKNOWN_gap_80039AA8_H_
#define __UNKNOWN_gap_80039AA8_H_

#include "mssbTypes.h"
typedef struct Gap80039AA8Position { f32 x, y; } Gap80039AA8Position;
typedef struct Gap80039AA8State {
    u8 _pad0[0xA00];
    u16 countA00, countA02;
    u8 _padA04[0x2BC];
    u8 flags[13]; /* 0xCC0 */
    u8 _padCCD[3];
    Gap80039AA8Position positions[4]; /* 0xCD0 */
    u8 _padCF0[0x48];
    u8 mode; /* 0xD38 */
} Gap80039AA8State;
extern Gap80039AA8State lbl_802D3D80;
void fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
typedef struct Gap80039AA8Texture Gap80039AA8Texture;
extern Gap80039AA8Texture lbl_8023DD80;
typedef struct Gap80039AA8Table {
    u8 _pad0[0x8];
    /* 0x8 */ u16 height;
    /* 0xA */ u16 width;
    u8 _padC[0x14];
} Gap80039AA8Table;
extern Gap80039AA8Table lbl_800F7A40;
extern u8 lbl_803CB828[3];
typedef struct Gap80039AA8Screen {
    /* 0x0 */ f32 unk0;
    u8 _pad4[0x4];
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u16 unk14;
    u8 _pad16;
    /* 0x17 */ u8 unk17;
    u8 _pad18[2];
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    u8 _pad1E[2];
} Gap80039AA8Screen;
extern Gap80039AA8Screen lbl_803C5090;

extern s32 lbl_803CBCA8;
extern s32 lbl_803CBCB0;

Gap80039AA8Texture* GetUITexture(void);
Gap80039AA8Table* fn_80039AB4(void);
void fn_80039AC0(void);
typedef struct Gap80039AA8RenderMode {
    u8 _pad0[0x18]; u16 width, height;
    u8 _pad1C[9]; u8 flags;
} Gap80039AA8RenderMode;
void fn_80039FF8(Gap80039AA8RenderMode* mode);
void fn_8003A090(void);
void fn_8003A144(void);
typedef struct Gap80039AA8Saved {
    u8 _pad0[8];
    /* 0x08 */ Gap80039AA8Screen screen; /* copy of lbl_803C5090 */
} Gap80039AA8Saved; /* 0x28 */
extern Gap80039AA8Saved lbl_800F7A60[];
extern u8 lbl_803CBBC0; /* index of the entry in use */
void fn_800A7D4C(s32 kind, void* record);
void fn_8003A1D0(void);
void fn_8003A2C0(void);
void fn_8003A2EC(void);
void fn_8003A37C(void);
void fn_8003A4C8(void);
s32 fn_8003A538(void);
void fn_8003A540(s32 value);
void fn_8003A548(s32 value);
void fn_8003A550(void);
void fn_8003A688(s32 index, f32 x, f32 y);
void fn_8003A6B0(void);
void fn_8003A848(u8 a, u8 b, u8 c);
void fn_8003A85C(u8 mode);
void fn_8003A8A0(void);
typedef struct Gap80039AA8Color { u8 r, g, b, a; } Gap80039AA8Color; /* GXColor */
extern u8 lbl_803CBCB4; /* grey level used for the flat material colour */
void GXSetChanMatColor(s32 channel, Gap80039AA8Color color);
void GXSetNumChans(u8 count);
void GXSetChanCtrl(s32 channel, u8 enable, s32 ambSrc, s32 matSrc, u32 lightMask, s32 diffuseFn, s32 attnFn);
void GXSetNumTevStages(u8 count);
void GXSetTevOrder(s32 stage, s32 coord, s32 map, s32 color);
void GXSetTevColorIn(s32 stage, s32 a, s32 b, s32 c, s32 d);
void GXSetTevColorOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 outReg);
void GXSetTevAlphaIn(s32 stage, s32 a, s32 b, s32 c, s32 d);
void GXSetTevAlphaOp(s32 stage, s32 op, s32 bias, s32 scale, u8 clamp, s32 outReg);
void fn_8003AC90(void);
/* Colour-indexed texture description read by fn_8003AD84. */
typedef struct Gap80039AA8TexDesc {
    u8 _pad0[4];
    /* 0x04 */ void* image;
    u8 _pad8[4];
    /* 0x0C */ u16 height;
    /* 0x0E */ u16 width;
    /* 0x10 */ u8 wrapS;
    /* 0x11 */ u8 wrapT;
    /* 0x12 */ u8 minFilter;
    /* 0x13 */ u8 magFilter;
    /* 0x14 */ f32 lodBias;
    u8 _pad18;
    /* 0x19 */ u8 minLod;
    /* 0x1A */ u8 maxLod;
} Gap80039AA8TexDesc;
typedef struct Gap80039AA8TexObj { u32 words[8]; } Gap80039AA8TexObj;   /* GXTexObj */
typedef struct Gap80039AA8TlutObj { u32 words[3]; } Gap80039AA8TlutObj; /* GXTlutObj */
extern Gap80039AA8TexObj lbl_803C50B0;
extern Gap80039AA8TlutObj lbl_803C50DC;
extern u16 lbl_800F7AC0[16]; /* 16-colour palette */
extern u8 lbl_803CBCAC;      /* set once the texture object is built */
void GXInitTexObjCI(Gap80039AA8TexObj* obj, void* image, u16 width, u16 height, s32 format, s32 wrapS, s32 wrapT,
                    u8 mipmap, u32 tlutName);
void GXInitTlutObj(Gap80039AA8TlutObj* obj, void* lut, s32 format, u16 entries);
void GXInitTexObjLOD(Gap80039AA8TexObj* obj, s32 minFilter, s32 magFilter, f32 minLod, f32 maxLod, f32 lodBias,
                     u8 biasClamp, u8 edgeLod, s32 maxAniso);
void fn_8003AD84(Gap80039AA8TexDesc* desc);

u8* memset(u8* memory, s32 value, u32 size);
u8 GetDrawShadows(void);
void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height);
void GXSetTexCopyDst(u16 width, u16 height, s32 format, u8 mipmap);
void GXCopyTex(Gap80039AA8Texture* dest, BOOL clear);
void GXPixModeSync(void);
void fn_800BEB3C(void);
void fn_800BD1E8(void (*callback)(void));
typedef struct Gap80039AA8Thread Gap80039AA8Thread;
Gap80039AA8Thread* OSGetCurrentThread(void);
Gap80039AA8Thread* GXGetCurrentGXThread(void);

#endif // !__UNKNOWN_gap_80039AA8_H_
