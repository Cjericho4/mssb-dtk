#include "game/gap_15F874.h"
#include "static/UnknownHomes_Static.h"

extern s32 lbl_3_data_27F10[];

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void fn_3_15F874(void) {
    return;
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void fn_3_15F998(void) {
    lbl_3_common_bss_35154.unk_470 = 0;
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void fn_3_15F9AC(void) {
    lbl_3_common_bss_35154.unk_471 = 1;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void fn_3_15F9C0(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    lbl_803CC1B8->loadingState--;
    lbl_3_common_bss_35154.unk_468 = lbl_3_data_27F10[0] * (lbl_3_data_27F10[1] - lbl_803CC1B8->loadingState) / lbl_3_data_27F10[1];
    if (lbl_803CC1B8->loadingState == 0) {
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void fn_3_15FA58(void) {
    return;
}

