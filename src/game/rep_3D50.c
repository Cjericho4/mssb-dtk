#include "game/rep_3D50.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"

extern QueueEntry* lbl_3_bss_B9B8;
extern s32 lbl_3_data_283F0[2][4];
extern s32 lbl_3_data_28410[2];

// .text:0x00160578 size:0x29C mapped:0x8079F60C
void fn_3_160578(void) {
    return;
}


// .text:0x00160814 size:0xDC mapped:0x8079F8A8
void fn_3_160814(s32 type) {
    s32 idx;

    if (lbl_3_common_bss_35154.unk_464 != 0) {
        return;
    }
    lbl_3_bss_B9B8 = fn_800B0A5C_insertQueue(fn_3_160578, (u16)(lbl_803CC1B8->priority + 1));
    lbl_3_bss_B9B8->unk14 = (type == 4);
    idx = lbl_3_bss_B9B8->unk14;
    lbl_3_bss_B9B8->unk15 = 0;
    lbl_3_bss_B9B8->unk16 = lbl_3_data_283F0[idx][0];
    lbl_3_bss_B9B8->unk17 = 0;
    lbl_3_common_bss_35154.unk_47A[lbl_3_bss_B9B8->unk14 != 0] = lbl_3_data_28410[lbl_3_bss_B9B8->unk14];
}
