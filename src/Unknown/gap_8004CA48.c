#include "Unknown/gap_8004CA48.h"

// .text:0x8004CA48 size:0x24
void fn_8004CA48(s16 a, s16 b, s16 c, s16 d) {
    lbl_803C5F74.active = 1;
    lbl_803C5F74.unkE = a;
    lbl_803C5F74.unk10 = b;
    lbl_803C5F74.unk12 = c;
    lbl_803C5F74.unk14 = d;
}

// .text:0x8004CA6C size:0x1AC
s32 fn_8004CA6C(s32 buttons) {
    return 0;
}

// .text:0x8004CC18 size:0x14
void fn_8004CC18(void) {
    lbl_803C5F74.mode = 4;
}

// .text:0x8004CC2C size:0x20
void fn_8004CC2C(void) {
    if (lbl_803C5F74.mode != 4) {
        lbl_803C5F74.mode = 3;
    }
}

// .text:0x8004CC4C size:0x74
void fn_8004CC4C(u8 a, u8 b, u8 c, s32 d, s16 e) {
    if (lbl_803C5F74.unk0 != 0) {
        return;
    }
    lbl_803C5F74.unk1 = a;
    lbl_803C5F74.unk2 = c;
    lbl_803C5F74.mode = 0;
    lbl_803C5F74.unk4 = b;
    lbl_803C5F74.unk1E = 0;
    lbl_803C5F74.unk6 = 0;
    lbl_803C5F74.unkE = -1;
    lbl_803C5F74.unk8 = 0;
    lbl_803C5F74.unk10 = -1;
    lbl_803C5F74.unkA = 0;
    lbl_803C5F74.unk12 = -1;
    lbl_803C5F74.unkC = 0;
    lbl_803C5F74.unk14 = -1;
    lbl_803C5F74.unk1B = 0;
    lbl_803C5F74.active = 0;
    if (d >= 0) {
        lbl_803C5F74.unk1A = d;
        lbl_803C5F74.unk18 = e;
    } else {
        lbl_803C5F74.unk1A = -1;
    }
}

// .text:0x8004CCC0 size:0x430
void fn_8004CCC0(void) {
    return;
}

// .text:0x8004D0F0 size:0x370
void fn_8004D0F0(void) {
    return;
}

// .text:0x8004D460 size:0x90
void fn_8004D460(s32 convert, s32 value) {
    s32 values[4];
    s32 i;
    s32 v;
    s32 key;
    s32 j;

    values[0] = value;
    for (i = 0; i < 1; i++) {
        if (lbl_803C6028.indices[i] >= 0 && (v = values[i]) >= 0) {
            if (convert == 0) {
                lbl_803C6028.indices[i] = v;
            } else {
                key = lbl_800E8558[v].id;
                for (j = 0; j < 36; j++) {
                    if (key == lbl_800FE930[lbl_803C6028.unk8C][j]) {
                        lbl_803C6028.indices[i] = j;
                        break;
                    }
                }
            }
        }
    }
}

// .text:0x8004D4F0 size:0x8C
void fn_8004D4F0(s8 value, s32 charIndex, s32 enable) {
    s32 j;
    s32 key = lbl_800E8558[charIndex].id;

    for (j = 0; j < 36; j++) {
        if (lbl_800FE930[lbl_803C6028.unk8C][j] == key) {
            if (enable) {
                lbl_803C6028.picks[j] = value;
            } else {
                lbl_803C6028.picks[j] = -1;
            }
            return;
        }
    }
}

// .text:0x8004D57C size:0x3C0
void fn_8004D57C(void) {
    return;
}

// .text:0x8004D93C size:0x54
BOOL fn_8004D93C(BOOL special) {
    if (lbl_803C6028.transition == 0) {
        if (special) lbl_803C6028.transition = 3;
        else lbl_803C6028.transition = 1;
    }
    if (lbl_803C6028.transition == 2) {
        lbl_803C6028.transition = 0;
        return 1;
    }
    return 0;
}

// .text:0x8004D990 size:0x200
void fn_8004D990(void) {
    return;
}

// .text:0x8004DB90 size:0x75C
void fn_8004DB90(void) {
    return;
}

// .text:0x8004E2EC size:0x218
void fn_8004E2EC(void) {
    return;
}

// .text:0x8004E504 size:0xB0
void fn_8004E504(s32 convert, s32 a, s32 b, s32 c, s32 d) {
    s32 values[4];
    s32 i;
    s32 value;
    s32 key;
    s32 j;

    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
    for (i = 0; i < 4; i++) {
        if (lbl_803C6028.indices[i] >= 0 && (value = values[i]) >= 0) {
            if (convert == 0) {
                lbl_803C6028.indices[i] = value;
            } else {
                key = lbl_800E8558[value].id;
                for (j = 0; j < 36; j++) {
                    if (key == lbl_800FE5D4[j]) {
                        lbl_803C6028.indices[i] = j;
                        break;
                    }
                }
            }
        }
    }
}

// .text:0x8004E5B4 size:0x78
void fn_8004E5B4(s8 value, s32 charIndex, s32 enable) {
    s32 j;
    s32 key = lbl_800E8558[charIndex].id;

    for (j = 0; j < 36; j++) {
        if (lbl_800FE5D4[j] == key) {
            if (enable) {
                lbl_803C6028.picks[j] = value;
            } else {
                lbl_803C6028.picks[j] = -1;
            }
            return;
        }
    }
}

// .text:0x8004E62C size:0x858
void fn_8004E62C(void) {
    return;
}

// .text:0x8004EE84 size:0x70
BOOL fn_8004EE84(s32 kind) {
    if (lbl_803C6028.unk7D == 0) {
        if (kind == 2) {
            lbl_803C6028.unk7D = 4;
            lbl_803C6028.unk8F = 1;
        } else if (kind != 0) {
            lbl_803C6028.unk7D = 3;
        } else {
            lbl_803C6028.unk7D = 1;
        }
    }
    if (lbl_803C6028.unk7D == 2) {
        lbl_803C6028.unk7D = 0;
        return TRUE;
    }
    return FALSE;
}

// .text:0x8004EEF4 size:0x218
void fn_8004EEF4(s32 a, s32 b, s32 c, s32 d, s32 enabled) {
    return;
}

// .text:0x8004F10C size:0x858
void fn_8004F10C(void) {
    return;
}

// .text:0x8004F964 size:0x400
void fn_8004F964(void) {
    return;
}

// .text:0x8004FD64 size:0x3C
s32 fn_8004FD64(s32 index) {
    s32 selected = lbl_803C6028.indices[index];
    if (lbl_803C6028.busy[selected] != 0) return -1;
    return lbl_800FDE84[selected];
}

// .text:0x8004FDA0 size:0x48
void fn_8004FDA0(s32 value) {
    s32 i;
    for (i = 0; i < 36; i++) {
        if (lbl_800FDE84[i] == value) {
            lbl_803C6028.busy[i] = 1;
            return;
        }
    }
}

// .text:0x8004FDE8 size:0x350
void fn_8004FDE8(void) {
    return;
}

// .text:0x80050138 size:0x5B0
void fn_80050138(s32 arg0, s32 pick0, s32 pick1, s32 pick2, s32 pick3, s32 arg5) {
    return;
}
