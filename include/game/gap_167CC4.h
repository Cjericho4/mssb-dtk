#ifndef GAME_GAP_167CC4_H
#define GAME_GAP_167CC4_H

#include "mssbTypes.h"

void fn_3_167CC4(void);
void fn_3_167D4C(void);
void fn_3_167F14(void);
void fn_3_1680D4(void);
struct AnimationStruct;

/* Queue task spawned for a character effect. */
typedef struct EffectTask {
    u8 _pad0[0x14];
    struct AnimationStruct* owner; /* 0x14 */
    u16 timer;                     /* 0x18 */
    u8 type;                       /* 0x1A */
    u8 state;                      /* 0x1B */
} EffectTask;

EffectTask* fn_3_1682AC(struct AnimationStruct* owner, s8 type);

#endif // GAME_GAP_167CC4_H
