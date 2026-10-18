#ifndef __UNKNOWN_gap_80039AA8_H_
#define __UNKNOWN_gap_80039AA8_H_

#include "mssbTypes.h"
typedef struct Gap80039AA8Position { f32 x, y; } Gap80039AA8Position;
typedef struct Gap80039AA8State {
    u8 _pad0[0xCD0];
    Gap80039AA8Position positions[4]; /* 0xCD0 */
} Gap80039AA8State;
extern Gap80039AA8State lbl_802D3D80;
void fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
typedef struct Gap80039AA8Texture Gap80039AA8Texture;
extern Gap80039AA8Texture lbl_8023DD80;
typedef struct Gap80039AA8Table Gap80039AA8Table;
extern Gap80039AA8Table lbl_800F7A40;
extern u8 lbl_803CB828[3];

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
void fn_8003A85C(void);
void fn_8003A8A0(void);
void fn_8003AC90(void);
void fn_8003AD84(void);

#endif // !__UNKNOWN_gap_80039AA8_H_
