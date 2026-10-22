#ifndef __CHALLENGE_rep_7BF0_H_
#define __CHALLENGE_rep_7BF0_H_

#include "mssbTypes.h"
#include "challenge/rep_7978.h"
#include "UnknownHeaders.h"

typedef struct Rep7BF0Globals80366158 {
    /* 0x0 */ u8 _pad0[8];
    /* 0x8 */ s32 unk8;
} Rep7BF0Globals80366158;
extern Rep7BF0Globals80366158 lbl_80366158;
void fn_800AD038(s32 arg0);
void fn_800A97D0(s32 arg0, s32 arg1);
void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2);

typedef struct Rep7BF0Unk471BC {
    /* 0x00 */ u8 _pad0[0x1C];
} Rep7BF0Unk471BC;
extern Rep7BF0Unk471BC lbl_1_bss_471BC;
typedef struct Rep7BF0View471D8 {
    /* 0x00 */ Rep7978Camera camera;
} Rep7BF0View471D8;
extern Rep7BF0View471D8 lbl_1_bss_471D8;
void fn_80048BEC(Rep7BF0Unk471BC* arg0, s32 arg1, s32 arg2);

void fn_1_2858C(void);
void fn_1_289C0(void);
void fn_1_289E0(void);
void fn_1_28AE0(void);
void fn_1_28C34(void);
void fn_1_28CE8(DrawingSceneStruct* scene);
void fn_1_2905C(void);
void fn_1_2935C(void);
void fn_1_29414(DrawingSceneStruct* scene);
void fn_1_2948C(void);
void fn_1_295E8(void);
void fn_1_29A48(void);
void fn_1_29A9C(void);

#endif // !__CHALLENGE_rep_7BF0_H_
