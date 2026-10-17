#include "menus/gap_8E6A4.h"
#include "menus/gap_1254.h"
#include "menus/gap_194BC.h"

extern void fn_8004A0FC(void);

// .text:0x0008E6A4 size:0x200
void fn_2_8E6A4(void) {
    return;
}

// .text:0x0008E8A4 size:0x1DC
void fn_2_8E8A4(void) {
    return;
}

// .text:0x0008EA80 size:0x2CC
void fn_2_8EA80(void) {
    return;
}

// .text:0x0008ED4C size:0x78
void fn_2_8ED4C(void) {
    g_d_GameSettings._10 = 2;
    g_d_GameSettings.home_AwaySetting = 0;
    fn_2_2FC0(9, 0, 1);
    fn_8004A0FC();
    lbl_803C5F04.unk3E = 0;
    fn_8004A0FC();
    lbl_800E8754.unk0 = 3;
    g_d_GameSettings.GameModeSelected = 4;
}

// .text:0x0008EDC4 size:0x104
void fn_2_8EDC4(void) {
    return;
}

// .text:0x0008EEC8 size:0x22C
void fn_2_8EEC8(void) {
    return;
}
