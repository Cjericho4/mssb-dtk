#ifndef __CHALLENGE_rep_0138_H_
#define __CHALLENGE_rep_0138_H_

#include "mssbTypes.h"
void fn_80048C28(void);
void fn_80048C1C(void);
#include "Dolphin/GX/GXGeometry.h"

typedef struct Rep0138Model {
    /* 0x00 */ u8 _pad0[0x68];
    /* 0x68 */ struct Rep0138ModelData* data;
} Rep0138Model;
extern GXCullMode lbl_1_data_8C4;
#include "Dolphin/mtx.h"
typedef struct Rep0138Light Rep0138Light;
extern Rep0138Light* lbl_1_data_848[4];
void LITXForm(Rep0138Light* light, Mtx view);
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/GX/GXTev.h"

typedef struct Rep0138UnkC4 {
    /* 0x000 */ s32 cullNone;
    /* 0x004 */ u8 _pad4[0x218];
} Rep0138UnkC4;
extern Rep0138UnkC4 lbl_1_bss_C4;
extern GXColor lbl_1_data_858;
void SetFogNoneAgain(void);

void fn_1_4E98(void);
void fn_1_54E0(Mtx view);
void fn_1_5540(void);
void fn_1_5544(void);
void fn_1_5698(void);
void fn_1_5924(void);
void fn_1_5AC0(void);
void fn_1_6050(u16* pixels, s32 width, s32 height, f32 scale);
#include "Dolphin/GX/GXTexture.h"
typedef struct ChallengeMipSettings {
    u8 _pad0[0x778];
    u8 levels;
    u8 _pad779[3];
    f32 scales[4];
    f32 bias;
    s32 filter;
} ChallengeMipSettings;
extern ChallengeMipSettings lbl_1_data_2A8;
void fn_1_6578(GXTexObj* texture, u16* pixels, s32 width, s32 height);
typedef struct ChallengeModelPose {
    u32 flags;
    void (*draw)(Rep0138Model*);
    Mtx transform;
    u8 _pad38[0x34];
} ChallengeModelPose;
typedef struct ChallengePreviewState {
    u8 _pad0[0x30];
    u16 flags;
    u8 _pad32[0x1A];
    Vec position;
    u8 _pad58[4];
    ChallengeModelPose poses[4];
    u8 _pad20C[0x10];
    u16* pixels;
    u8 _pad220[0xE];
    s16 selection;
    s8 mode;
    s8 option;
    u8 _pad232[2];
    u8 active;
    u8 _pad235[0xB];
} ChallengePreviewState;
extern ChallengePreviewState lbl_1_common_bss_472B4;
void fn_800B472C(Rep0138Model* model);
typedef struct Rep0138Globals80366158 { u8 _pad0[8]; s32 unk8; } Rep0138Globals80366158;
extern Rep0138Globals80366158 lbl_80366158;
void fn_800AD038(s32 arg);
#include <string.h>
void fn_1_66C4(void);
void fn_1_6848(void);
void fn_1_6E14(void);
void fn_1_717C(void);
void fn_1_7280(void);
void fn_1_73B8(Rep0138Model* model, s32 count, ...);
void fn_1_77EC(Rep0138Model* model);
void fn_1_7848(void);
typedef struct ChallengeFog {
    union {
        GXColor color;
        struct {
            u8 rgb[3];
            u8 type;
        };
    };
    f32 start;
    f32 end;
} ChallengeFog;
extern ChallengeFog* lbl_1_bss_4E0;
void fn_80048D4C(void);
void SetFog(u8 type, GXColor color, f32 start, f32 end, f32 nearScale, f32 farScale);
void fn_1_786C(void);
void fn_1_78E4(void);
void fn_1_7960(void);
void fn_1_7E04(f32 scale);
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_800B806C(s32 index, f32 t, f32 b, f32 l, f32 r, f32 nearZ, f32 farZ, f32 scale);
#include "Dolphin/GX/GXTransform.h"
#include "challenge/challenge.h"
extern u8 lbl_1_bss_C2;
extern u8 lbl_1_data_85C;
s32 fn_80048EA8(s32 index);
void fn_80048E00(s32 index, s32 value);
void fn_80048C14(s32 mode);
void fn_1_7EF8(void);
void fn_1_7FF8(void);
void fn_1_8368(void);

#endif // !__CHALLENGE_rep_0138_H_
