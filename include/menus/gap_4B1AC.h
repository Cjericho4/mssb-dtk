#ifndef __MENUS_gap_4B1AC_H_
#define __MENUS_gap_4B1AC_H_

#include "mssbTypes.h"

typedef struct MenusResourceEntry {
    u32 resource;
    s16 index;
    s16 unk6;
    s16 bank;
    s16 unkA;
    s16 unkC;
    u8 _padE[2];
} MenusResourceEntry;

typedef struct MenusTimeState {
    u32 unk0;
    u32 high;
    u32 low;
} MenusTimeState;

extern MenusTimeState lbl_803C7898;

void fn_2_4B1AC(void);
void fn_2_4B2D0(void);
void fn_2_4C314(void);
void fn_2_4C36C(void);
s16 fn_2_4C3C4(s32 index);
s16 fn_2_4C3D8(s32 index);
void fn_2_4C3EC(void);
void fn_2_4C6A8(void);
void fn_2_4C81C(void);
void fn_2_4C9C4(void);
void fn_2_4CB94(void);
void fn_2_4CD30(void);
void fn_2_4CEE0(void);
void fn_2_4D194(void);
void fn_2_4D378(void);
void fn_2_4D67C(void);
void fn_2_4D960(void);
void fn_2_4DC24(void);
void fn_2_4DEE8(void);
void fn_2_4E1C0(void);
void fn_2_4E7A4(void);
void fn_2_4E7EC(void);
void fn_2_4E824(void);
void fn_2_4E858(u32 arg);
void fn_2_4E878(u32 arg0, u32 arg1);
void fn_2_4E898(void);
void fn_2_4E8BC(void);
void fn_2_4E8E0(void);
void fn_2_4E904(void);
void fn_2_4E928(void);
void fn_2_4E94C(void);
BOOL fn_2_4E970(void);
void fn_2_4E9A8(void);
BOOL fn_2_4EABC(void);
BOOL fn_2_4EAF4(void);
BOOL fn_2_4EB2C(void);
BOOL fn_2_4EB64(void);
void fn_2_4EB9C(void);
void fn_2_50898(void);
void fn_2_509A4(void);
void fn_2_50B0C(void);
void fn_2_50BF4(void);
void fn_2_50CC0(void);
void fn_2_50D40(void);
void fn_2_50DB4(void);
void fn_2_50E5C(void);
void fn_2_50F20(void);
void fn_2_50FC8(void);
void fn_2_510A8(void);
void fn_2_5118C(void);
void fn_2_51190(void);
void fn_2_512B4(void);
s32 fn_2_512B8(void);
void fn_2_512C0(void);
void fn_2_51358(void);
void fn_2_5135C(void);
void fn_2_513DC(void);
void fn_2_513E0(void);
void fn_2_513E4(void);
void fn_2_513E8(void);
void fn_2_5146C(void);
void fn_2_51470(void);
void fn_2_51568(void);
void fn_2_5156C(void);
void fn_2_515DC(void);
void fn_2_5163C(void);
void fn_2_51890(void);
void fn_2_519F0(void);
void fn_2_51A1C(void);
void fn_2_51C58(void);
void fn_2_520A4(void);
void fn_2_52198(void);
void fn_2_52260(void);
void fn_2_52648(s32 priority);
void fn_2_5268C(void);
void fn_2_52690(void);
void fn_2_53408(void);
void fn_2_535B0(void);
void fn_2_5389C(void);
void fn_2_53AA4(void);
void fn_2_53BC8(void);
void fn_2_53CEC(void);
void fn_2_53DF8(void);
void fn_2_53F04(void);
void fn_2_53F88(void);
void fn_2_5400C(void);
void fn_2_54120(void);
void fn_2_54234(MenusResourceEntry* entries, s32 count);
void fn_2_54354(MenusResourceEntry* entries, s32 count);
void fn_2_54474(void);
void fn_2_54844(void);
void fn_2_54848(void);
void fn_2_54874(void);
void fn_2_54890(void);
void fn_2_549B4(void);
void fn_2_54B38(void);
void fn_2_54BAC(void);

#endif // !__MENUS_gap_4B1AC_H_
