#ifndef __UNKNOWN_gap_8000F8F4_H_
#define __UNKNOWN_gap_8000F8F4_H_

#include "mssbTypes.h"
typedef struct Gap8000F8F4Entry {
    u32 unk0;
    u32 data;
    u8 _pad8[0x10];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    s16 state; /* 0x28 */
    /* 0x2A */ u8 unk2A;
    u8 _pad2B[6];
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    u8 _pad33;
    u8 flags34, flags35;
    u8 _pad36[2];
} Gap8000F8F4Entry;
typedef struct Gap8000F8F4Table { u32 unk0; u32 values[256]; } Gap8000F8F4Table;
typedef struct Gap8000F8F4State {
    Gap8000F8F4Entry entries[34];
    u8 _pad770[0x28];
    Gap8000F8F4Table* tables[8];
} Gap8000F8F4State;
extern Gap8000F8F4State lbl_80366B18;

extern s32 lbl_803CBC18;

void fn_8000F8F4(void);
void fn_8000F988(void);
void fn_8000FA9C(void);
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD9C(s32 index, s32 flag, s32 state);
void fn_8000FE08(s32 index, s32 table, s32 value);
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
