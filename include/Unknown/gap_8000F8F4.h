#ifndef __UNKNOWN_gap_8000F8F4_H_
#define __UNKNOWN_gap_8000F8F4_H_

#include "mssbTypes.h"
typedef struct Gap8000F8F4Entry {
    u8 _pad0[0x18];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    u8 _pad28[0x2];
    /* 0x2A */ u8 unk2A;
    u8 _pad2B[0xD];
} Gap8000F8F4Entry;
extern Gap8000F8F4Entry lbl_80366B18[];

extern s32 lbl_803CBC18;

void fn_8000F8F4(void);
void fn_8000F988(void);
void fn_8000FA9C(void);
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD9C(void);
void fn_8000FE08(void);
void fn_8000FE54(void);
void fn_8000FEE8(s32 index);
void fn_8000FF04(void);
void fn_800100A4(void);
void DrawText(void);
void DrawTextOnCondition(void);
void fn_80010FA0(void);
void fn_80011000(void);
void fn_80011140(void);
void fn_800111B4(void);
void fn_800111D8(void);
void fn_800111FC(void);
void fn_80011358(void);
void fn_80011468(void);
s32 fn_80011570(void);
void fn_80011578(void);
void fn_800115C8(void);
void fn_80011604(void);
void fn_80011640(void);
void fn_800116DC(void);
void fn_800117CC(void);
void fn_800118AC(void);

#endif // !__UNKNOWN_gap_8000F8F4_H_
