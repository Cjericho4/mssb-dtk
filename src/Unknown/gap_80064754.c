#include "Unknown/gap_80064754.h"

// .text:0x80064754 size:0x8C
s32 translateStarPitchHitIndex(u8 id) {
    switch (id) {
    case 0:
        return 6;
    case 1:
        return 7;
    case 2:
        return 10;
    case 3:
        return 11;
    case 4:
        return 14;
    case 5:
        return 15;
    case 6:
        return 16;
    case 7:
        return 17;
    case 8:
        return 12;
    case 9:
        return 13;
    case 10:
        return 8;
    case 11:
        return 9;
    }
    return -1;
}

// .text:0x800647E0 size:0x9C
u8 translateStarPitch(u8 id) {
    switch (id) {
    case 0:
        return 133;
    case 1:
        return 135;
    case 2:
        return 145;
    case 3:
        return 147;
    case 4:
        return 153;
    case 5:
        return 155;
    case 6:
        return 141;
    case 7:
        return 143;
    case 8:
        return 137;
    case 9:
        return 139;
    case 10:
        return 149;
    case 11:
        return 151;
    case 12:
        return 161;
    case 13:
        return 160;
    case 14:
        return 162;
    }
    return id;
}

// .text:0x8006487C size:0x9C
u8 translateStarSwing(u8 id) {
    switch (id) {
    case 0:
        return 132;
    case 1:
        return 134;
    case 2:
        return 144;
    case 3:
        return 146;
    case 4:
        return 152;
    case 5:
        return 154;
    case 6:
        return 140;
    case 7:
        return 142;
    case 8:
        return 136;
    case 9:
        return 138;
    case 10:
        return 148;
    case 11:
        return 150;
    case 12:
        return 157;
    case 13:
        return 158;
    case 14:
        return 159;
    }
    return id;
}

// .text:0x80064918 size:0x54
s32 fn_80064918(s16 id) {
    switch (id) {
    case 0:
    case 1:
        return 4;
    case 4:
    case 5:
    case 11:
    case 14:
        return 1;
    case 3:
    case 28:
    case 33:
    case 34:
    case 35:
    case 36:
    case 39:
    case 47:
        return 2;
    case 12:
    case 16:
    case 32:
    case 40:
    case 44:
    case 45:
    case 46:
    case 48:
    case 51:
        return 5;
    case 6:
    case 7:
    case 8:
    case 13:
    case 15:
    case 18:
    case 20:
    case 24:
    case 25:
    case 26:
    case 29:
    case 30:
    case 31:
    case 41:
    case 43:
        return 3;
    }
    return 0;
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
    u8 stadium;
    if (lbl_80361B20.unkF5 != 0) {
        stadium = randRange_FUN_80042bf0(0, 5);
    } else {
        do {
            stadium = randRange_FUN_80042bf0(0, 5);
        } while (stadium == 1);
    }
    g_d_GameSettings.stadium = stadium;
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
