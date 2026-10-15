#ifndef __GAME_sta_c4_H_
#define __GAME_sta_c4_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

extern u8 lbl_3_bss_B5D4;

void fn_3_F8444(void);
typedef struct {
    u8 _pad0[0x4];
    VecXYZ pos;         // 0x04
    u8 _pad10[0x14 - 0x10];
    f32 unk14;          // 0x14
    u8 _pad18[0x38 - 0x18];
    f32 unk38;          // 0x38
    f32 unk3C;          // 0x3C
    u8 color[4];        // 0x40
    u8 _pad44[0x48 - 0x44];
    s16 unk48;          // 0x48
    s16 unk4A;          // 0x4A
    u8 _pad4C[0x4F - 0x4C];
    u8 unk4F;           // 0x4F
} StaC4Obj;

void fn_3_F8524(StaC4Obj* obj);
void fn_3_F85B0(void);
void fn_3_F8878(void);
void fn_3_F8ABC(void);
void fn_3_F8B04(void);
void fn_3_F8B30(void);
void fn_3_F8B34(void);
void fn_3_F8BA8(void);
void fn_3_F8D00(void);
void fn_3_F8E20(void);
void fn_3_F9088(void);
void fn_3_F9164(void);
void fn_3_F92FC(void);
void fn_3_F934C(void);
void fn_3_F963C(void);
void fn_3_F976C(void);
void fn_3_F99F0(void);
void fn_3_F9B9C(void);
void fn_3_F9D94(void);
void fn_3_F9E78(void);
void fn_3_FA3C0(void);
void fn_3_FA58C(void);
void fn_3_FB3D8(void);
void fn_3_FBBA0(void);

// No local headers needed.
#endif // !__GAME_sta_c4_H_
