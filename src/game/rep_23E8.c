#include "game/rep_23E8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"

// .text:0x000CB738 size:0x9C mapped:0x8070A7CC
void fn_3_CB738(void) {
    CommonBss_35154* b = &lbl_3_common_bss_35154;
    if (g_d_GameSettings._55 != 0 || b->unk_479 != 0 || b->someHalfword-- == 0) {
        b->unk_40a = 0;
        fn_800B0A14_removeQueue();
    } else {
        fn_3_BD8D8();
        b->transRot.transY += -0.03125f;
        b->transRot.rotY += 0.15707964f;
    }
}

// .text:0x000CB7D4 size:0x14 mapped:0x8070A868
void fn_3_CB7D4(void) {
    lbl_3_common_bss_35154.someHalfword = 0;
}

// .text:0x000CB7E8 size:0xC0 mapped:0x8070A87C
void fn_3_CB7E8(void) {
    return;
}

