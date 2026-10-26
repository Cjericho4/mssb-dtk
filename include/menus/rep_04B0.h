#ifndef __MENUS_rep_04B0_H_
#define __MENUS_rep_04B0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct MenusProjectionState {
    union { u8 _pad0[0x30]; Mtx matrix; };
    s16 state;
    s16 step;
    u8 _pad34[4];
    f32 value;
    Vec target;
    Vec position;
    union { s32 flags; f32 unk_0x54; };
} MenusProjectionState;
extern MenusProjectionState lbl_2_bss_1010C;
extern MenusProjectionState lbl_2_bss_1A81D4;

typedef struct MenusLightMatrixState {
    u8 _pad0[0x14];
    Mtx matrix;
} MenusLightMatrixState;
extern MenusLightMatrixState lbl_2_bss_10164;

typedef struct MenusSceneAsset MenusSceneAsset;

void fn_2_14574(void);
void fn_2_14790(void);
void fn_2_14BB8(void);
void fn_2_14CA0(void);
void fn_2_14FB8(s32 index);
void fn_2_150D0(u8 index);
s32 fn_2_15104(s32 previous, s32 current, u8 index, u8 value);
void fn_2_151BC(void);
void fn_2_1560C(void);
void fn_2_15A90(s32* value, u8 index, s32 maximum);
void fn_2_15AFC(void);
void fn_2_15E80(void);
void fn_2_1641C(void);
void fn_2_16460(void);
void fn_2_16664(void);
void fn_2_166CC(void);
void fn_2_16724(void);

#endif // !__MENUS_rep_04B0_H_
