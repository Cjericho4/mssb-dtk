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
void fn_8004CA6C(void) {
    return;
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
void fn_8004CC4C(void) {
    return;
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
void fn_8004D460(void) {
    return;
}

// .text:0x8004D4F0 size:0x8C
void fn_8004D4F0(void) {
    return;
}

// .text:0x8004D57C size:0x3C0
void fn_8004D57C(void) {
    return;
}

// .text:0x8004D93C size:0x54
void fn_8004D93C(void) {
    return;
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
void fn_8004E504(void) {
    return;
}

// .text:0x8004E5B4 size:0x78
void fn_8004E5B4(void) {
    return;
}

// .text:0x8004E62C size:0x858
void fn_8004E62C(void) {
    return;
}

// .text:0x8004EE84 size:0x70
void fn_8004EE84(void) {
    return;
}

// .text:0x8004EEF4 size:0x218
void fn_8004EEF4(void) {
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
void fn_80050138(void) {
    return;
}
