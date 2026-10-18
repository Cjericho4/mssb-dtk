#include "Unknown/gap_80064754.h"

// .text:0x80064754 size:0x8C
void translateStarPitchHitIndex(void) {
    return;
}

// .text:0x800647E0 size:0x9C
void translateStarPitch(void) {
    return;
}

// .text:0x8006487C size:0x9C
void translateStarSwing(void) {
    return;
}

// .text:0x80064918 size:0x54
void fn_80064918(void) {
    return;
}

// .text:0x8006496C size:0x50
void fn_8006496C(void) {
    g_d_GameSettings.option50 = lbl_8034E9A0.option0;
    if (g_d_GameSettings.mode == 0) {
        if (g_d_GameSettings.option50 == 0) g_d_GameSettings.option51 = 5;
        else g_d_GameSettings.option51 = 4;
    } else {
        g_d_GameSettings.option51 = lbl_8034E9A0.option1;
    }
}

// .text:0x800649BC size:0x48
void fn_800649BC(void) {
    g_d_GameSettings.side = randRange_FUN_80042bf0(0, 1);
    lbl_800E8754.mode = 3;
    lbl_800E8754.option = lbl_803CB8D0;
}

// .text:0x80064A04 size:0x13E8
void unsure_FillRosterPositions(void) {
    return;
}

// .text:0x80065DEC size:0x10C0
void characterSelectScreen(void) {
    return;
}

// .text:0x80066EAC size:0x1F4
void fn_80066EAC(void) {
    return;
}

// .text:0x800670A0 size:0x15C
void fn_800670A0(void) {
    return;
}

// .text:0x800671FC size:0x68
void fn_800671FC(void) {
    return;
}

// .text:0x80067264 size:0x360
void fn_80067264(void) {
    return;
}

// .text:0x800675C4 size:0x308
void fn_800675C4(void) {
    return;
}

// .text:0x800678CC size:0x1FC
void fn_800678CC(void) {
    return;
}
