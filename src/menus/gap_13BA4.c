#include "menus/gap_13BA4.h"
#include "menus/rep_0568.h"
#include "menus/gap_8782C.h"

// .text:0x00013BA4 size:0xFC
void fn_2_13BA4(void) {
    return;
}

// .text:0x00013CA0 size:0xD0
void fn_2_13CA0(MenusPlayerInput* input) {
    if (input->buttons & 8) {
        lbl_2_bss_100B8.unk4E--;
        if ((s8)lbl_2_bss_100B8.unk4E < 0) lbl_2_bss_100B8.unk4E = 5;
    } else if (input->buttons & 4) {
        lbl_2_bss_100B8.unk4E++;
        if ((s8)lbl_2_bss_100B8.unk4E == 6) lbl_2_bss_100B8.unk4E = 0;
    } else if (input->buttons & 1) {
        lbl_80361B20.unkF5 ^= 1;
    } else if (input->buttons & 2) {
        lbl_80361B20.unkF5 ^= 1;
    } else if (input->unk2 & 0x200) {
        lbl_2_bss_100B8.unk50 = 0;
    }
}

// .text:0x00013D70 size:0x2FC
void fn_2_13D70(void) {
    return;
}

// .text:0x0001406C size:0xF8
void fn_2_1406C(MenusPlayerInput* input) {
    if (input->buttons & 8) {
        lbl_2_bss_100B8.unk4C--;
        if ((s8)lbl_2_bss_100B8.unk4C < 0) lbl_2_bss_100B8.unk4C = 5;
    } else if (input->buttons & 4) {
        lbl_2_bss_100B8.unk4C++;
        if ((s8)lbl_2_bss_100B8.unk4C == 6) lbl_2_bss_100B8.unk4C = 0;
    } else if (input->buttons & 1) {
        g_d_GameSettings.miniGameLevels[(s8)lbl_2_bss_100B8.unk4C + 7] ^= 1;
    } else if (input->buttons & 2) {
        g_d_GameSettings.miniGameLevels[(s8)lbl_2_bss_100B8.unk4C + 7] ^= 1;
    } else if (input->unk2 & 0x200) {
        lbl_2_bss_100B8.unk50 = 0;
    }
}

// .text:0x00014164 size:0xBC
void fn_2_14164(MenusPlayerInput* input) {
    if (input->buttons & 8) {
        lbl_2_bss_100B8.unk51--;
        if ((s8)lbl_2_bss_100B8.unk51 == 0) lbl_2_bss_100B8.unk51 = 4;
    } else if (input->buttons & 4) {
        lbl_2_bss_100B8.unk51++;
        if ((s8)lbl_2_bss_100B8.unk51 == 5) lbl_2_bss_100B8.unk51 = 1;
    } else if (input->unk2 & 0x100) {
        lbl_2_bss_100B8.unk50 = lbl_2_bss_100B8.unk51;
    } else if (input->unk2 & 0x200) {
        lbl_2_bss_100B8.unk4C = 0;
        lbl_2_bss_100B8.unk50 = 0;
        lbl_2_bss_100B8.unk51 = 1;
        lbl_2_bss_100B8.unk4B = 0;
    }
}

// .text:0x00014220 size:0x354
void fn_2_14220(void) {
    return;
}
