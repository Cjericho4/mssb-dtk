#ifndef __CHALLENGE_rep_0010_H_
#define __CHALLENGE_rep_0010_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"
#include "Dolphin/GX/GXFrameBuffer.h"

typedef struct Rep0010Globals80366158 {
    /* 0x0 */ u8 _pad0[4];
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Rep0010Globals80366158;
extern Rep0010Globals80366158 lbl_80366158;
extern GXColor lbl_1_data_A8;
void resetAllDrawingStructs(void);
void fn_80009144(void);
void fn_800AD054(s32 arg0, s32 arg1);
void fn_1_16A0(void);

void fn_1_5EC(void);
void fn_1_AF4(void);
void fn_1_F2C(void);
void _epilog(void);
void _unresolved(void);
void _prolog(void);
void fn_1_1148(void);
void fn_1_11D0(void);
void fn_1_1240(void);

#endif // !__CHALLENGE_rep_0010_H_
