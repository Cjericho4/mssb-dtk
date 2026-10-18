#ifndef __MENUS_gap_8782C_H_
#define __MENUS_gap_8782C_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct MenusRosterTransition {
    u8 _pad0[2];
    u16 state;
    u8 _pad4;
    u8 mode;
    u8 _pad6[8];
    u8 pending;
    u8 _padF[0x13];
    u8 command;
} MenusRosterTransition;
extern MenusRosterTransition lbl_2_bss_33FBCC;

typedef struct MenusRosterScripts {
    u8 _pad0[0xBAC];
    u8 mode3[0x120];
    u8 mode12[0x100];
    u8 mode0[1];
} MenusRosterScripts;
extern MenusRosterScripts lbl_2_data_2E9F8;

typedef struct MenusRosterState {
    u8 _pad0[0xE4];
    u8 options[4];
    u8 _padE8[0xD];
    u8 unkF5;
    u8 mode;
} MenusRosterState;

typedef struct MenusGameChoiceState {
    u32 unk0;
    u8 _pad4[0xC];
    s32 selections[2];
    u8 _pad18[0x38];
    u32 selection;
} MenusGameChoiceState;
extern MenusRosterState lbl_80361B20;
extern MenusGameChoiceState lbl_2_bss_F410;

typedef struct MenusVisibilityState {
    u8 _pad0[0xC];
    u32 assets[9];
    u32 values[8];
    u8 visible[1]; /* extent unknown */
} MenusVisibilityState;
extern hugeAnimStruct* lbl_2_bss_340140;
extern MenusVisibilityState* lbl_2_bss_3401BC;

void fn_2_8782C(void);
void fn_2_87998(void);
void fn_2_87FB0(void);
void fn_2_88250(void);
void fn_2_883C8(void);
void fn_2_887F8(void);
void fn_2_88D90(void);
void fn_2_89038(void);
void fn_2_895F8(void);
void fn_2_8975C(void);
void fn_2_89F70(void);
void fn_2_8A008(DrawingSceneStruct* scene);
void fn_2_8A824(void);
void fn_2_8ABFC(void);
void fn_2_8AC84(s32 index, u8 visible);
void fn_2_8ACB0(s32 index, u8 visible);
void fn_2_8ACDC(void);

#endif // !__MENUS_gap_8782C_H_
