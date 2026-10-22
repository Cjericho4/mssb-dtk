#ifndef __CHALLENGE_rep_7978_H_
#define __CHALLENGE_rep_7978_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"

typedef struct Rep7978Camera {
    /* 0x00 */ Mtx view;
    /* 0x30 */ Mtx44 projection;
    /* 0x70 */ Vec eye;
    /* 0x7C */ Vec direction;
    /* 0x88 */ Vec up;
    /* 0x94 */ u8 _pad94[0x10];
    f32 angleX;
    f32 angleY;
    f32 moveSpeed;
    f32 turnSpeed;
    f32 width;
    f32 height;
    /* 0xBC */ f32 scale;
    /* 0xC0 */ f32 nearZ;
    /* 0xC4 */ f32 farZ;
    /* 0xC8 */ f32 top;
    /* 0xCC */ f32 bottom;
    /* 0xD0 */ f32 left;
    /* 0xD4 */ f32 right;
    u32 flags;
} Rep7978Camera;

#include "challenge/challenge.h"
void fn_1_26D28(Rep7978Camera* camera, u16 buttons, u16 held, u16 pressed, ChallengeAxes* axes);
void fn_1_272DC(Rep7978Camera* camera, u32 mtxId);
void fn_1_27330(Rep7978Camera* camera);
void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void fn_1_273D8(Rep7978Camera* camera);

#endif // !__CHALLENGE_rep_7978_H_
