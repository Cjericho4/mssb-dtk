#ifndef __GAME_rep_21F8_H_
#define __GAME_rep_21F8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

extern u8 lbl_3_bss_9F34;

void fn_3_C937C(void);
typedef struct Rep21F8Key {
    f32 value;      /* 0x0 */
    f32 slope;      /* 0x4 */
    u16 frame;      /* 0x8 */
    u8 _padA[2];
} Rep21F8Key; /* size: 0xC */

typedef struct Rep21F8Anim {
    u8 _pad0[0x14];
    Rep21F8Key* tracks[8];  /* 0x14 */
    u8 counts[8];           /* 0x34 */
    u8 cur[8];              /* 0x3C */
} Rep21F8Anim;

void fn_3_C9590(Rep21F8Anim* anim, s32 arg1, Mtx m, f32 t);
void fn_3_C9734(void);

#endif // !__GAME_rep_21F8_H_
