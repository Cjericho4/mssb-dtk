#ifndef __CHALLENGE_rep_7730_H_
#define __CHALLENGE_rep_7730_H_

#include "mssbTypes.h"
#include "challenge/rep_7978.h"
#include "challenge/rep_0010.h"
typedef void (*Rep7730ModeFunc)(s16 arg);
extern Rep7730ModeFunc lbl_1_data_1066C[];
extern Rep7978Camera lbl_1_bss_6D48;
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
extern Mtx44 lbl_1_bss_47010;
void fn_80048C14(s32 arg0);
void fn_80048E00(s32 arg0, s32 arg1);
#include "challenge/challenge.h"
#include "game/rep_1C0.h"
extern CompressedDiskRead lbl_1_data_104F4;
extern CompressedDiskRead lbl_1_data_10674;
#include "UnknownHeaders.h"

typedef struct Rep7730Values {
    /* 0x0 */ f32 value0;
    /* 0x4 */ f32 value4;
    /* 0x8 */ f32 value8;
    /* 0xC */ f32 valueC;
} Rep7730Values;
extern Rep7730Values lbl_1_bss_6BE4;

typedef struct Rep7730Unk6BF4 {
    Vec origin, target;
    u8 _pad18[0x38];
    f32 angle;
    u8 _pad54[4];
    Mtx matrix;
    u8 _pad88[0x60];
    union {
        Vec direction;
        struct { f32 _padE8; f32 time; f32 _padF0; };
    };
    Vec offset;
    u8 _pad100[0x40];
    Vec normal;
    u8 _pad14C[8];
} Rep7730Unk6BF4;
extern Rep7730Unk6BF4 lbl_1_bss_6BF4;
void fn_80037B18(Rep7730Unk6BF4* arg0, Vec* arg1, f32 arg2);

void fn_1_1D694(void);
void fn_1_1D944(void);
void fn_1_1DA54(void);
void fn_1_1DCE4(void);
f32 fn_1_1DD48(u16 buttons, s32 negate, f32 value, f32 stepA, f32 step, f32 stepB, f32 min, f32 max);
void fn_1_1DD94(void);
void fn_1_1DDE4(f32 value);
void fn_1_1DDF4(f32 value);
void fn_1_1DE04(f32 value);
void fn_1_1DE14(f32 value);
f32 fn_1_1DE20(void);
f32 fn_1_1DE30(void);
f32 fn_1_1DE40(void);
f32 fn_1_1DE50(void);
void fn_1_1DE5C(void);
void fn_1_1DE60(void);
void fn_1_1E28C(void);
s16 fn_1_1E290(s16 selected, u16 held, u16 unused, u16 pressed);
void fn_1_1E5D0(Rep7730Unk6BF4* arg0);
void fn_1_1E8C0(s32 arg);
void fn_1_1E90C(void);
void fn_1_1EFF4(void);
void fn_1_1F05C(void);
void fn_800385F0(Rep7730Unk6BF4* camera, f32 a, f32 b, f32 c, f32 d);
void fn_1_1F23C(Rep7730Unk6BF4* camera);
void fn_1_1F2D8(void);
typedef struct ChallengeRenderSettings {
    u8 _pad0[0x1C];
    u32 value;
    u8 mode;
    u8 selection;
    u8 stages;
    u8 textureIndex;
} ChallengeRenderSettings;
void fn_1_1F418(ChallengeRenderSettings* settings);
s32 fn_80048EA8(s32 index);
void fn_1_1F618(void);
void fn_1_1F900(void);
void fn_1_1FD78(ChallengeRenderSettings* settings);
void fn_1_2004C(void);
void fn_80048C1C(void);
void fn_80048D4C(void);
void fn_80048C28(void);
#include "Dolphin/GX/GXFrameBuffer.h"
extern void (*lbl_1_data_10508[])(ChallengeScene*);
extern void (*lbl_1_data_10510[])(ChallengeScene*);
void fn_1_202A4(void);
void fn_1_2040C(void);
#include "Dolphin/GX/GXTexture.h"
#include "game/sta_c4.h"
u8 fn_1_2051C(StaC4TexDesc* desc, GXTexObj* texture, GXTlutObj* palette, u32 paletteName);
typedef struct ChallengeTextureStages {
    u8 _pad0[0x22];
    u8 count;
} ChallengeTextureStages;
void fn_1_20640(ChallengeTextureStages* stages, u32* indices);
void fn_1_207D4(void);
void fn_1_20890(void);
void fn_1_20950(void);
void fn_1_20BD8(void);
void fn_1_20DC8(void);
void fn_1_20E00(void);
void fn_1_20F8C(void);
#include "Dolphin/GX/GXFifo.h"
void fn_1_21040(void);
void fn_1_21180(void);
typedef struct ChallengeLineScene {
    u8 _pad0[0x21];
    u8 count;
    u8 showFlat;
    u8 _pad23;
    u8 showCurve;
} ChallengeLineScene;
void fn_1_21298(ChallengeLineScene* scene);
void fn_1_21408(void);
void fn_1_21CE8(void);
void fn_1_225B8(void);
void fn_1_22644(void);
void fn_1_22874(void);
void fn_1_22DF4(void);
void fn_1_22F4C(void);
void fn_1_23098(void);
void fn_1_23804(s32 unusedA, s32 unusedB, s32 columns, s32 rows);
void fn_1_23AD8(Mtx44 projection, Vec* eye, Vec* target);
void C_MTXFrustum(Mtx44 projection, f32 top, f32 bottom, f32 left, f32 right, f32 nearZ, f32 farZ);
void fn_1_23B54(void);
void fn_1_24410(void);
extern void (*lbl_1_data_104A8[4])(void);
void fn_1_246AC(void);
void fn_1_24778(void);
void fn_1_247A0(void);
void fn_1_248BC(void);
void fn_1_24A8C(void);
typedef struct ChallengeSpringPoint {
    f32 mass, reserved;
    Vec position, previous, velocity, force;
    u32 fixed;
} ChallengeSpringPoint;
void fn_1_24C4C(ChallengeSpringPoint* points, s32 count, Vec* impulse, f32 stiffness, f32 damping, f32 restLength, f32 timeScale);
void fn_1_25064(void);
void fn_1_25C68(void);
void fn_1_25F98(void);
void fn_1_267BC(void);
typedef struct ChallengeSpriteHeader {
    u8 _pad0[8];
    s32* indices;
} ChallengeSpriteHeader;
typedef struct ChallengeSpriteSlot {
    u8 _pad0[0x38];
    ChallengeSpriteHeader* header;
} ChallengeSpriteSlot;
extern ChallengeSpriteSlot lbl_803C4BE0[];
typedef struct ChallengeSpriteResource ChallengeSpriteResource;
typedef struct Gap26AF8Entry {
    ChallengeSpriteResource* data;
    u8 _pad4[0xC];
} Gap26AF8Entry;
extern Gap26AF8Entry lbl_1_data_FB98[];
extern s32 lbl_1_data_10344[];
s32 fn_80035838(Gap26AF8Entry* descriptor, s32 mode);
s32 fn_80035DD4(s32 index);
void fn_1_267F4(void);
void fn_800AD038(s32 heap);
void fn_800B24D4(s32 mode);
void fn_800B1188(void);
void fn_1_26928(void);
void fn_1_26A34(void);

#endif // !__CHALLENGE_rep_7730_H_
