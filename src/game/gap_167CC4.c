#include "game/gap_167CC4.h"

#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_3E58.h"

// .text:0x00167CC4 size:0x88
void fn_3_167CC4(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_GameLogic.gameStatus != 2) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_Ball.ballState == 2) {
        fn_3_16699C();
        return;
    }
    fn_800B0A14_removeQueue();
}

// .text:0x00167D4C size:0x1C8
void fn_3_167D4C(void) {
    return;
}

// .text:0x00167F14 size:0x1C0
void fn_3_167F14(void) {
    return;
}

// .text:0x001680D4 size:0x1D8
void fn_3_1680D4(void) {
    return;
}

// .text:0x001682AC size:0x168
EffectTask* fn_3_1682AC(struct AnimationStruct* owner, s8 type) {
    EffectTask* task = NULL;

    if (owner != NULL) {
        switch (type) {
        case 1:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_1680D4, 0xFFFA);
            break;
        case 2:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_167F14, 0xFFFA);
            break;
        case 4:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_167CC4, 0xFFFA);
            break;
        case 3:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_167D4C, 0xFFFA);
            break;
        case 10:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_1678A8, 0xFFFA);
            break;
        case 8:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_1674D0, 0xFFFA);
            break;
        case 6:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_166FCC, 0xFFFA);
            break;
        case 12:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_167178, 0xFFFA);
            break;
        case 11:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_166E04, 0xFFFA);
            break;
        case 7:
            task = (EffectTask*)fn_800B0A5C_insertQueue(fn_3_166D40, 0xFFFA);
            break;
        }
        if (task != NULL) {
            task->owner = owner;
            task->timer = 0;
            task->type = type;
            task->state = 0;
        }
    }
    return task;
}
