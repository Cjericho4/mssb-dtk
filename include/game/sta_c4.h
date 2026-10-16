#ifndef __GAME_sta_c4_H_
#define __GAME_sta_c4_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

extern u8 lbl_3_bss_B5D4;

void fn_3_F8444(void);
typedef struct {
    u8 _pad0[0x4];
    VecXYZ pos;         // 0x04
    u8 _pad10[0x14 - 0x10];
    f32 unk14;          // 0x14
    u8 _pad18[0x38 - 0x18];
    f32 unk38;          // 0x38
    f32 unk3C;          // 0x3C
    u8 color[4];        // 0x40
    u8 _pad44[0x48 - 0x44];
    s16 unk48;          // 0x48
    s16 unk4A;          // 0x4A
    u8 _pad4C[0x4F - 0x4C];
    u8 unk4F;           // 0x4F
} StaC4Obj;

void fn_3_F8524(StaC4Obj* obj);

struct ActorAnimState;
typedef struct StaC4AnimObj {
    /* 0x00 */ u8 _pad0[0x74];
    /* 0x74 */ struct ActorAnimState* animState;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ u8 _pad84[0x90 - 0x84];
    /* 0x90 */ u8 flag90_7 : 1;
    /* 0x90 */ u8 flag90_6 : 1;
    /* 0x90 */ u8 flag90_rest : 6;
    /* 0x91 */ u8 _pad91[0x9C - 0x91];
    /* 0x9C */ f32 animTime;
    /* 0xA0 */ u8 slotId;
    /* 0xA1 */ u8 _padA1;
    /* 0xA2 */ u8 texFrame;
    /* 0xA3 */ u8 tickCount;
} StaC4AnimObj;
void fn_3_F85B0(void);
void fn_3_F8878(void);
void fn_3_F8ABC(void);
void fn_3_F8B04(void);
void fn_3_F8B30(void);
void fn_3_F8B34(void);
void fn_3_F8BA8(StaC4AnimObj* obj);
void fn_3_F8D00(void);
void fn_3_F8E20(void);
void fn_3_F9088(VecXYZ* pos, s32 idx);
void fn_3_F9164(void);
void fn_3_F92FC(void);
void fn_3_F934C(void);
typedef struct StaC4QueueObj {
    /* 0x00 */ u8 _pad0[0x14];
    /* 0x14 */ Vec vel;
    /* 0x20 */ Vec unk20;
    /* 0x2C */ s32 elemIdx;
    /* 0x30 */ u8 unk30;
} StaC4QueueObj;

typedef struct StaC4LaunchSrc {
    /* 0x00 */ u8 _pad0[0xC];
    /* 0x0C */ Vec vel;
} StaC4LaunchSrc;

void fn_3_F963C(s32 elemIdx, StaC4LaunchSrc* src);
void fn_3_F976C(void);
void fn_3_F99F0(void);
void fn_3_F9B9C(void);
void fn_3_F9D94(StaC4AnimObj* obj);
void fn_3_F9E78(void);
void fn_3_FA3C0(void);
void fn_3_FA58C(void);
void fn_3_FB3D8(void);
typedef struct StaC4TexDesc {
    /* 0x00 */ u8* image;
    /* 0x04 */ u8* tlut;
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 wrapS;
    /* 0x0D */ u8 wrapT;
    /* 0x0E */ u8 minFilter;
    /* 0x0F */ u8 magFilter;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 _pad14;
    /* 0x15 */ u8 minLOD;
    /* 0x16 */ u8 maxLOD;
    /* 0x17 */ u8 format;
    /* 0x18 */ u16 tlutEntries;
    /* 0x1A */ u8 tlutFormat;
} StaC4TexDesc;

void fn_3_FBBA0(StaC4TexDesc* desc);

// No local headers needed.
#endif // !__GAME_sta_c4_H_
