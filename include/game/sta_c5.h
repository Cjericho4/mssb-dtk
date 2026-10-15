#ifndef __GAME_sta_c5_H_
#define __GAME_sta_c5_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "C3/control.h"

typedef struct StaC5PlacedObj {
    /* 0x00 */ Control control;
    /* 0x3C */ u8 _pad3C[0x74 - 0x3C];
    /* 0x74 */ struct ActorAnimState* animState;
    /* 0x78 */ u8 _pad78[0x90 - 0x78];
    /* 0x90 */ u8 flag90_7 : 1;
    /* 0x90 */ u8 flag90_rest : 7;
    /* 0x91 */ u8 _pad91[0xA0 - 0x91];
    /* 0xA0 */ VecXYZ pos;
    /* 0xAC */ u8 _padAC[0xB4 - 0xAC];
    /* 0xB4 */ f32 rotY;
    /* 0xB8 */ u8 _padB8[0xC7 - 0xB8];
    /* 0xC7 */ u8 blinkTimer;
} StaC5PlacedObj;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} EF55C_Arg;

/* Object that drifts toward a target point from lbl_3_data_1B884. */
typedef struct StaC5DriftObj {
    /* 0x00 */ Control control;
    /* 0x3C */ u8 _pad3C[0x9C - 0x3C];
    /* 0x9C */ u8 targetIdx;
    /* 0x9D */ u8 _pad9D[0xA8 - 0x9D];
    /* 0xA8 */ Vec pos;
    /* 0xB4 */ Vec vel;
    /* 0xC0 */ f32 angle;
} StaC5DriftObj;

typedef struct StaC5DriftTarget {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u8 _padC[0x14 - 0xC];
} StaC5DriftTarget; /* size: 0x14 */

extern StaC5DriftTarget lbl_3_data_1B884[];

/* Object placed at an entry of lbl_3_data_1B9A4. */
typedef struct StaC5SpotObj {
    /* 0x00 */ Control control;
    /* 0x3C */ u8 _pad3C[0x9C - 0x3C];
    /* 0x9C */ u8 spotIdx;
    /* 0x9D */ u8 _pad9D[0xA0 - 0x9D];
    /* 0xA0 */ f32 x;
    /* 0xA4 */ f32 y;
    /* 0xA8 */ f32 z;
    /* 0xAC */ f32 rot;
} StaC5SpotObj;

typedef struct StaC5Spot {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 rot;
    /* 0x10 */ u8 _pad10[0x18 - 0x10];
} StaC5Spot; /* size: 0x18 */

extern StaC5Spot lbl_3_data_1B9A4[];

typedef struct {
    u8 _pad0[0x60];
    u8 unk60;       // 0x60
    u8 _pad1[0x43];
    u8 unkA4;       // 0xA4
} ElemStruct_F13F8;

typedef struct {
    u8 _pad0[0x6];
    u16 unk6;       // 0x6 - element count
    u8 _pad1[0x10];
    ElemStruct_F13F8** unk18; // 0x18 - array of element pointers
} DeepStruct_F13F8;

typedef struct {
    DeepStruct_F13F8* unk0; // 0x0
    u8 _pad1[0x54];
    u8 unk58;               // 0x58
} InnerStruct_F13F8;

typedef struct {
    /* 0x00 */ Control control;
    /* 0x3C */ u8 _pad3C[0x74 - 0x3C];
    /* 0x74 */ InnerStruct_F13F8* unk74;
    /* 0x78 */ u8 _pad78[0xC6 - 0x78];
    /* 0xC6 */ u8 unkC6;
    /* 0xC7 */ u8 unkC7;
} OuterStruct_F13F8;

extern u8 lbl_3_bss_AEE8;

/* File-local bss block starting at 0xAEE0 (accessed via a single base). */
typedef struct StaC5Bss_AEE0 {
    /* 0x000 */ u8 _pad0[0x8];
    /* 0x008 */ u8 unk8;
    /* 0x009 */ u8 _pad9[0x33B - 0x9];
    /* 0x33B */ u8 unk33B;
    /* 0x33C */ u8 unk33C;
} StaC5Bss_AEE0;
extern StaC5Bss_AEE0 lbl_3_bss_AEE0;
extern void* lbl_3_bss_B55C;
extern u8 lbl_3_data_1BA5C[];
extern u8 lbl_803CBBC0;

void fn_800BDA24(void* arg0);
void fn_800A7D4C(s32 arg0, void* elem);

void fn_3_EE100(void);
void fn_3_EE388(void);
void fn_3_EE67C(void);
void fn_3_EE96C(void);
void fn_3_EEB94(void);
void fn_3_EECF4(void);
void fn_3_EEE3C(void);
void fn_3_EEF24(void);
void fn_3_EEFA4(void);
void fn_3_EEFD0(void);
void fn_3_EEFD4(void);
void fn_3_EF218(void);
void fn_3_EF21C(void);
void fn_3_EF3D4(UnknownStruct_EF3D4* arg0, u32 index);
void fn_3_EF408(void);
u8 fn_3_EF55C(EF55C_Arg* arg0);
s32 fn_3_EF7B4(EF55C_Arg* arg0);
void fn_3_EF800(StaC5PlacedObj* obj);
void fn_3_EF890(OuterStruct_F13F8* arg0);
void fn_3_EF930(void);
void fn_3_EFB54(StadiumObjectElem* obj);
void fn_3_F0184(void);
void fn_3_F0224(void);
void fn_3_F082C(void);
void fn_3_F0FA4(void);
void fn_3_F13F8(OuterStruct_F13F8* arg0);
void fn_3_F1448(StaC5SpotObj* obj);
void fn_3_F1518(void);
void fn_3_F1674(void);
void fn_3_F1750(void);
void fn_3_F18A4(StaC5PlacedObj* obj);
void fn_3_F193C(void);
void fn_3_F1E2C(void);
void fn_3_F22FC(void);
void fn_3_F2448(void);
void fn_3_F2724(void);
void fn_3_F2938(void);
void fn_3_F2FFC(void);
void fn_3_F31E0(void);
void fn_3_F37BC(void);
void fn_3_F38D4(void);
void fn_3_F3A04(OuterStruct_F13F8* arg0);
void fn_3_F3A5C(StaC5PlacedObj* obj, f32 x, f32 y, f32 z, f32 rotY);
void fn_3_F3AE0(void);
void fn_3_F3BB0(void);
void fn_3_F3CD0(void);
void fn_3_F3EFC(void);
void fn_3_F42A0(void);
void fn_3_F466C(void);
void fn_3_F469C(void);
void fn_3_F46A0(void);
void fn_3_F4BA0(StaC5DriftObj* obj);
void fn_3_F4C4C(StaC5DriftObj* obj);
void fn_3_F4D00(StaC5DriftObj* obj);
void fn_3_F4DAC(void);
void fn_3_F4FBC(void);
void fn_3_F56CC(void);
void fn_3_F5C30(void);
s32 fn_3_F5E78(u8 arg0);
s32 fn_3_F5EFC(unknown_tri_compare* a, unknown_tri_compare* b);
s32 fn_3_F5F28(f32* a, f32* b);
void fn_3_F5F4C(void);
void fn_3_F6084(void);
struct StadiumModel* fn_3_F6504(s32 index, Mtx m);
void fn_3_F65C8(s32* count);
void fn_3_F66C8(void);
void fn_3_F6938(void);
void fn_3_F6A94(void);
void fn_3_F6C60(void);
void fn_3_F6FCC(void);
void fn_3_F6FDC(void);

s32 fn_3_EE0BC(u32 arg0);
// No local headers needed.
#endif // !__GAME_sta_c5_H_
