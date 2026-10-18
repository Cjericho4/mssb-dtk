#ifndef __MENUS_gap_1254_H_
#define __MENUS_gap_1254_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"
#include "menus/gap_3C03C.h"

/* Menus view of the challenge save data: the 9-slot lineup of s8 values starting at 0x40BB. */
typedef struct MenusLineupEntry {
    s8 value;
    u8 _pad1[5];
} MenusLineupEntry;

typedef struct MenusLineupView {
    u8 _pad0[0x40BB];
    MenusLineupEntry lineup[9]; /* 0x40BB */
} MenusLineupView;

typedef struct MenusTeamSelections {
    u8 _pad0[2];
    s8 first[9];
    s8 second[9];
} MenusTeamSelections;
extern MenusTeamSelections lbl_803C6724;

typedef struct Menus1254State {
    s32 states[4];
    s32 options[4];
    u8 _pad20[0xE];
    u8 unk2E;
    s8 teamIndices[2];
    u8 _pad31[0x10];
    u8 flags41[4];
    u8 flags45[4];
    u8 _pad49[6];
    u8 unk4F;
    u8 _pad50[6];
    u8 unk56;
    u8 _pad57[2];
    u8 flags59[4];
} Menus1254State;

extern Menus1254State lbl_2_bss_F468;

typedef struct MenusSystemState {
    u8 _pad0[0xCF5F];
    u8 mode;
} MenusSystemState;
extern MenusSystemState lbl_803297E0;

void fn_2_1254(void);
void fn_2_1258(void);
void fn_2_12A0(s16* value, s16 amount);
void fn_2_12CC(u8* value, u16 amount);
void fn_2_12F8(u16* value, u16 amount);
void fn_2_1328(u32* value, u16 amount);
void fn_2_1354(MenusSortEntry* entries, s32 count, s32 descending);
void fn_2_145C(void);
s32 fn_2_148C(u16* text);
s32 fn_2_14F8(s32 first, s32 second);
u32 fn_2_1554(void);
void fn_2_1578(void);
void fn_2_1800(void);
void fn_2_1A88(void);
void fn_2_1BAC(void);
void fn_2_1C34(u16 buttons);
void fn_2_1D28(void);
void fn_2_1D54(s32* value, u8 index, s32 count);
void fn_2_1DC4(void);
void fn_2_1DC8(void);
void fn_2_1F30(void);
void fn_2_27E0(void);
void fn_2_2BB8(void);
void fn_2_2D1C(void);
void fn_2_2FC0(u8 mode, s32 update, s32 reset);
void fn_2_3204(void);
void fn_2_323C(void);
s32 fn_2_33BC(void);
void fn_2_348C(void);
s32 fn_2_35D0(u8 index);
void fn_2_3624(void);
void fn_2_4970(void);
void fn_2_5184(void);
void fn_2_52CC(void);
void fn_2_5444(void);
s32 fn_2_57E8(s32 arg0, s32 arg1);
void fn_2_57F0(void);
void fn_2_5F80(void);
void fn_2_6098(u8 index);
s32 fn_2_60D4(u8 index);
void fn_2_6138(void);
void fn_2_61A0(void);
void fn_2_6484(void);
void fn_2_6608(void);
void fn_2_6784(void);
void fn_2_6884(void);
void fn_2_6AF4(void);
void fn_2_6D3C(void);
void fn_2_7504(void);
void fn_2_7D44(void);
void fn_2_7DDC(void);
void fn_2_86EC(void);
s32 fn_2_8780(s32 mode);
s32 fn_2_8794(s32 mode, s32 index);
void fn_2_87A8(void);
void fn_2_893C(void);
void fn_2_8940(void);
void fn_2_8CF8(void);
void fn_2_95D8(void);
void fn_2_9ACC(void);
s32 fn_2_9F70(s8 side);
void fn_2_A040(void);
void fn_2_A1A0(void);
void fn_2_A288(void);
void fn_2_A50C(void);
BOOL fn_2_A62C(void);
void fn_2_A6E0(void);
void fn_2_ABC0(void);
void fn_2_AEE8(void);
void fn_2_B324(void);
void fn_2_B508(void);
void fn_2_B66C(void);
void fn_2_B920(void);
void fn_2_BF90(void);
void fn_2_C324(void);
void fn_2_C484(void);
void fn_2_C698(void);
void fn_2_C7DC(void);
void fn_2_CA60(void);
void fn_2_CCBC(void);
void fn_2_CCE0(void);
void fn_2_CE44(void);
void fn_2_DFAC(void);
void fn_2_EAE0(void);
void fn_2_EC34(void);
void fn_2_EC54(void);
void fn_2_ED94(void);
void fn_2_F200(void);
void fn_2_FAA0(void);
void fn_2_FCB4(void);
void fn_2_102C8(void);
void fn_2_104FC(void);
void fn_2_110B0(void);
BOOL fn_2_112F4(DrawingSceneStruct* scene, s32 offset, s32 index, u16* ids, u16 value);
void fn_2_11340(void);
void fn_2_11698(void);
void fn_2_11EA8(void);
void fn_2_120D0(void);
void fn_2_1216C(void);

#endif // !__MENUS_gap_1254_H_
