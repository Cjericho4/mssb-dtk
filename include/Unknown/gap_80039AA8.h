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
void fn_80039FF8(void);
void fn_8003A090(void);
void fn_8003A144(void);
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
void fn_8003AC90(void);
void fn_8003AD84(void);

u8* memset(u8* memory, s32 value, u32 size);
u8 GetDrawShadows(void);
void GXSetTexCopySrc(u16 left, u16 top, u16 width, u16 height);
void GXSetTexCopyDst(u16 width, u16 height, s32 format, BOOL mipmap);
void GXCopyTex(Gap80039AA8Texture* dest, BOOL clear);
void GXPixModeSync(void);
void fn_800BEB3C(void);
void fn_800BD1E8(void (*callback)(void));
typedef struct Gap80039AA8Thread Gap80039AA8Thread;
Gap80039AA8Thread* OSGetCurrentThread(void);
Gap80039AA8Thread* GXGetCurrentGXThread(void);

#endif // !__UNKNOWN_gap_80039AA8_H_
