#include "game/rep_FE0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_E08.h"
#include "game/rep_1838.h"

// .text:0x0006AF9C size:0x1A8 mapped:0x806AA030
f32 fn_3_6AF9C(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    AnimationStruct_31EAC* anim = &g_UnkAnimation_31EAC[idx];
    f32 ang = fn_3_9FEA8(-f->unk48 - 1.5707964f);
    s32 cur;
    s32 target;
    s32 diff;

    if (f->unk1FC != 0) {
        return ang;
    }
    cur = radToShortAngle(ang);
    target = radToShortAngle(anim->unk28);
    diff = fn_3_9FCA4(target, cur);
    if (diff > 0x800) {
        diff -= 0x1000;
    } else if (diff <= -0x800) {
        diff += 0x1000;
    }
    if (diff > 0x600) {
        if (f->unk1C7 == 0) {
            target -= 0x280;
        } else {
            target += 0x280;
        }
    } else if (diff < -0x600) {
        if (f->unk1C7 == 0) {
            target -= 0x280;
        } else {
            target += 0x280;
        }
    } else if (diff > 0x200) {
        target -= 0x180;
    } else if (diff < -0x200) {
        target += 0x180;
    } else if (diff > 0x180) {
        target -= 0x100;
    } else if (diff < -0x180) {
        target += 0x100;
    } else if (diff > 0xC0) {
        target -= 0x80;
    } else if (diff < -0xC0) {
        target += 0x80;
    } else if (diff > 0x60) {
        target -= 0x40;
    } else if (diff < -0x60) {
        target += 0x40;
    } else {
        return ang;
    }
    return shortAngleToRad(target);
}

// .text:0x0006B144 size:0x384 mapped:0x806AA1D8
void fn_3_6B144(void) {
    return;
}

