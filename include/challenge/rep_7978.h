#ifndef __CHALLENGE_rep_7978_H_
#define __CHALLENGE_rep_7978_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"

typedef struct Rep7978Camera {
    /* 0x00 */ Mtx view;
    /* 0x30 */ Mtx44 projection;
} Rep7978Camera;

void fn_1_26D28(void);
void fn_1_272DC(Rep7978Camera* camera, u32 mtxId);
void fn_1_27330(void);
void fn_1_273D8(void);

#endif // !__CHALLENGE_rep_7978_H_
