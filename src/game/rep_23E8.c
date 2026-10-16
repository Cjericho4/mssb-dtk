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
void fn_3_CB7E8(f32 x, f32 y, f32 z) {
    lbl_3_common_bss_35154.transRot.transX = x;
    lbl_3_common_bss_35154.transRot.transY = y;
    lbl_3_common_bss_35154.transRot.transZ = z;
    lbl_3_common_bss_35154.transRot.rotZ = 0.0f;
    lbl_3_common_bss_35154.transRot.rotY = 0.0f;
    lbl_3_common_bss_35154.transRot.rotX = 0.0f;
    lbl_3_common_bss_35154.someHalfword = 0x50;
    lbl_3_common_bss_35154.unk_40a = 1;
    lbl_3_common_bss_35154.bitfield |= 4;
    fn_800B0A5C_insertQueue(fn_3_CB738, (u16)(lbl_803CC1B8->priority + 1));
    playSoundEffect(0x19D);
    if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] < 5) {
        g_GameLogic.TeamStars[g_GameLogic.teamBatting]++;
    }
    g_GameLogic.stadiumStarObtained = 1;
}

