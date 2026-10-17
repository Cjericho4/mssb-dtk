#ifndef __MENUS_gap_3C03C_H_
#define __MENUS_gap_3C03C_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct Gap3C03CObj {
    u8 _pad0[5];
    s8 unk5;
    u8 _pad6[0x2B];
    s8 unk31;
    u8 _pad32[2];
} Gap3C03CObj;

typedef struct MenusEffectState {
    u32 type;
} MenusEffectState;

typedef struct MenusChoiceRecord {
    u8 _pad0[3];
    u8 choice;
    u8 _pad4[6];
} MenusChoiceRecord;

void fn_2_3C03C(void);
void fn_2_3C168(void);
void fn_2_3C3EC(void);
void fn_2_3C53C(void);
void fn_2_3C7DC(void);
void fn_2_3CD34(void);
void fn_2_3D5C4(void);
void fn_2_3D878(void);
void fn_2_3DAB8(void);
void fn_2_3DC60(void);
void fn_2_3DDC4(void);
void fn_2_3DF28(void);
void fn_2_3E058(void);
void fn_2_3E38C(void);
void fn_2_3E7EC(void);
void fn_2_3E918(void);
void fn_2_3EA44(void);
void fn_2_3EBA8(void);
void fn_2_3ECC0(void);
void fn_2_3EDD8(void);
void fn_2_3EEF0(void);
void fn_2_3F004(void);
void fn_2_3F188(void);
void fn_2_3F29C(void);
void fn_2_3F44C(void);
void fn_2_3F55C(void);
void fn_2_3F66C(void);
void fn_2_3FA14(void);
void fn_2_3FDE0(void);
void fn_2_4041C(void);
void fn_2_405B4(void);
void fn_2_4078C(void);
void fn_2_408BC(void);
void fn_2_409CC(void);
void fn_2_40A9C(void);
void fn_2_40B90(void);
void fn_2_40CB8(void);
void fn_2_42270(void);
void fn_2_422FC(void);
void fn_2_42388(void);
void fn_2_42474(void);
void fn_2_42490(void);
void fn_2_42638(void);
void fn_2_42708(void);
void fn_2_42BE8(void);
void fn_2_42EB0(void);
void fn_2_42FC8(void);
void fn_2_430F4(void);
void fn_2_432EC(void);
void fn_2_43404(void);
void fn_2_4358C(void);
void fn_2_439D0(void);
void fn_2_43E8C(void);
void fn_2_44014(void);
void fn_2_44184(void);
void fn_2_44238(void);
void fn_2_442E8(void);
void fn_2_44368(void);
void fn_2_44414(void);
void fn_2_44504(void);
void fn_2_44E2C(void);
s32 fn_2_44F14(s32 index);
BOOL fn_2_44F34(s32 index);
void fn_2_44F64(void);
void fn_2_450E4(void);
void fn_2_45204(void);
void fn_2_45354(void);
void fn_2_454E8(void);
void fn_2_45810(void);
BOOL fn_2_45938(s32 index);
void fn_2_45978(void);
void fn_2_45A84(void);
void fn_2_45BA4(void);
void fn_2_45D38(void);
void fn_2_45E48(void);
void fn_2_45FDC(void);
void fn_2_460EC(void);
void fn_2_460F0(void);
void fn_2_460F4(void);
void fn_2_460F8(void);
void fn_2_46418(void);
void fn_2_4668C(s32 index);
void fn_2_466AC(void);
void fn_2_467FC(void);
void fn_2_468DC(void);
void fn_2_46ADC(void);
s32 fn_2_46C24(void);
void fn_2_46C2C(s32 unused, Vec* position);

#endif // !__MENUS_gap_3C03C_H_
