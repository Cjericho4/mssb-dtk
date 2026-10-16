#ifndef __GAME_rep_E08_H_
#define __GAME_rep_E08_H_

#include "mssbTypes.h"

typedef struct {
    u8 _pad0[0x02];
    s16 field_0x02; // 0x02
    u16 field_0x04; // 0x04
    u8 _pad1[0x02];
    u8 field_0x08;  // 0x08
    u8 _pad2[0x01];
    u8 field_0x0a;  // 0x0a
    u8 field_0x0B;  // 0x0b
    u8 _pad3[0x04];
} Struct_32220; // size: 0x10

extern Struct_32220 lbl_3_common_bss_32220;

typedef struct {
    u8 unk0; // 0x00
    u8 unk1; // 0x01
    u8 unk2; // 0x02
    u8 unk3; // 0x03
} Struct_32230; // size: 0x04

extern Struct_32230 lbl_3_common_bss_32230;

typedef struct {
    u8 unk0; // 0x00
    u8 unk1; // 0x01
    u8 _pad[0x06];
} Struct_32234; // size: 0x08

extern Struct_32234 lbl_3_common_bss_32234;

typedef struct {
    u8 _pad0[0x28];
    f32 unk28; // Offset 0x28
    u8 _pad2C[0x38 - 0x2C];
    s16 unk38; // Offset 0x38
    s16 unk3A; // Offset 0x3A
    u8 _pad3C[0x40 - 0x3C];
    u8 unk40; // Offset 0x40
    u8 unk41; // Offset 0x41
    u8 _pad42;
    u8 unk43; // Offset 0x43
    u8 _pad44;
    u8 unk45; // Offset 0x45
    u8 _pad46[0x4A - 0x46];
    s16 unk4A; // Offset 0x4A
    u8 unk4C; // Offset 0x4C
    u8 unk4D; // Offset 0x4D
    u8 unk4E; // Offset 0x4E
    u8 unk4F; // Offset 0x4F
    u8 _pad50[0x54 - 0x50]; // Total size 0x54
} AnimationStruct_31EAC;

extern AnimationStruct_31EAC g_UnkAnimation_31EAC[];

void fn_3_60768(void);
void fn_3_60804(s32 index, s32 arg1);
void fn_3_60A98(void);
BOOL fn_3_60D80(s32 index);
void fn_3_60E90(void);
BOOL fn_3_61148(s32 index);
void fn_3_61228(void);
void fn_3_61544(void);
void fn_3_61B64(void);
void fn_3_62904(void);
void fn_3_62B50(void);
void fn_3_62CA8(s32 index);
void fn_3_62D44(s32 index);
void fn_3_62E04(s32 index);
void fn_3_62E28(void);
void fn_3_62E70(void);
void fn_3_631AC(s32 runnerIdx);
void fn_3_63874(s32 runnerIdx);
void fn_3_63A38(void);
void fn_3_63AF8(void);
void fn_3_64BDC(void);
void fn_3_657E4(void);
void fn_3_65FE0(void);
void fn_3_66140(void);
void fn_3_664FC(void);
void fn_3_668BC(void);
void fn_3_67130(void);
void fn_3_6714C(s32 arg0);

#endif // !__GAME_rep_E08_H_
