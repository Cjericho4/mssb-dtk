#ifndef __MENUS_rep_04B0_H_
#define __MENUS_rep_04B0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

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
void fn_2_14FB8(void);
void fn_2_150D0(u8 index);
void fn_2_15104(void);
void fn_2_151BC(void);
void fn_2_1560C(void);
void fn_2_15A90(void);
void fn_2_15AFC(void);
void fn_2_15E80(void);
void fn_2_1641C(void);
void fn_2_16460(void);
void fn_2_16664(void);
void fn_2_166CC(void);
void fn_2_16724(void);

#endif // !__MENUS_rep_04B0_H_
