#include "game/rep_21F8.h"
#include "header_rep_data.h"
#include "game/rep_1E08.h"

// .text:0x000C937C size:0x214 mapped:0x80708410
void fn_3_C937C(void) {
    return;
}

// .text:0x000C9590 size:0x1A4 mapped:0x80708624
void fn_3_C9590(Rep21F8Anim* anim, s32 arg1, Mtx m, f32 t) {
    Mtx rot;
    f32 v;

    PSMTXIdentity(m);
    m[0][0] = fn_3_BFDA4(anim->tracks[0], anim->counts[0], arg1, anim->cur[0], &anim->cur[0], t);
    m[1][1] = fn_3_BFDA4(anim->tracks[1], anim->counts[1], arg1, anim->cur[1], &anim->cur[1], t);
    if (anim->tracks[2] != NULL) {
        v = fn_3_BFDA4(anim->tracks[2], anim->counts[2], arg1, anim->cur[2], &anim->cur[2], t);
    } else {
        v = 0.0f;
    }
    m[0][3] = v;
    if (anim->tracks[5] != NULL) {
        v = fn_3_BFDA4(anim->tracks[5], anim->counts[5], arg1, anim->cur[5], &anim->cur[5], t);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(rot, 'Y', v);
        PSMTXConcat(rot, m, m);
    }
    if (anim->tracks[6] != NULL) {
        v = fn_3_BFDA4(anim->tracks[6], anim->counts[6], arg1, anim->cur[6], &anim->cur[6], t);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(rot, 'Z', v);
        PSMTXConcat(rot, m, m);
    }
    fn_3_BFDA4(anim->tracks[7], anim->counts[7], arg1, anim->cur[7], &anim->cur[7], t);
}

// .text:0x000C9734 size:0x10 mapped:0x807087C8
void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}

