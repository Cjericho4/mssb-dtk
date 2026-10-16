#ifndef __GAME_kinoko_H_
#define __GAME_kinoko_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "Dolphin/vec.h"

typedef struct KinokoState {
    u8 *ptr0;        // 0x00
    u8 *ptr4;        // 0x04
    u8 _unk08[0xD8]; // 0x08
} KinokoState;       // 0xE0 bytes

typedef struct KinokoData {
    u8 _pad0[0x19D4];  // 0x0000
    u32 unk_19D4;      // 0x19D4
    u8 _pad1[0x4];     // 0x19D8
    s8 unk_19DC;       // 0x19DC
    u8 unk_19DD;       // 0x19DD
    u8 _pad2[0x2];     // 0x19DE
} KinokoData;          // 0x19E0 bytes

typedef struct KinokoSegment {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec left;
    /* 0x18 */ Vec right;
    /* 0x24 */ GXColor color;
    /* 0x28 */ u8 _28[2];
    /* 0x2A */ u8 active;
    /* 0x2B */ u8 _2B;
} KinokoSegment; // 0x2C bytes

typedef struct KinokoQuadVert {
    Vec* pos;
    GXColor* color;
} KinokoQuadVert;

typedef struct KinokoQuad {
    /* 0x00 */ KinokoQuadVert verts[4];
    /* 0x20 */ Vec center;
    /* 0x2C */ u8 active;
    /* 0x2D */ u8 _2D[3];
} KinokoQuad; // 0x30 bytes

typedef struct KinokoBss {
    KinokoQuad quads[0x95];
} KinokoBss;            // 0x1BF0 bytes

extern KinokoData lbl_3_data_28928;
extern KinokoBss lbl_3_bss_BAE0;

void fn_3_16917C(void);
void fn_3_1695A4(s8 arg1, u8 arg2);
void fn_3_169600(void);
void fn_3_169804(void);
void fn_3_169984(void);
void fn_3_169D00(KinokoSegment* segs, u32* count);
void fn_3_169E70(void);
void fn_3_16A07C(void);
void fn_3_1695A0(void);
void fn_3_16B488(struct _VecXYZ* out, s8 type);
void fn_3_16B5B4(void);
void fn_3_16B884(void);
void fn_3_16C394(s8 arg0);

#endif // !__GAME_kinoko_H_
