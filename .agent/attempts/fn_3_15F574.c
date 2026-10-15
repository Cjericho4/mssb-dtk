#include "game/rep_3C28.h"
#include "header_rep_data.h"
#include "game/gap_6C854.h"
#include "Dolphin/vec.h"

// .text:0x0015F574 size:0xD4 mapped:0x8079E608
void fn_3_15F574(void) {
    s32 idx;
    Vec dir;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        idx = 2;
    } else {
        idx = g_Ball.framesSinceHit > 0;
    }
    PSVECSubtract(&lbl_3_common_bss_35154.vec_44C, &lbl_3_common_bss_35154.vec_440, &dir);
    if (PSVECMag(&dir)) {
        lbl_3_data_27C98[idx].unk0 = lbl_3_common_bss_35154.unk4;
        if (!lbl_80366158._28) {
            fn_8002C2D0(&lbl_3_common_bss_35154.vec_440, &dir);
        }
    }
}
