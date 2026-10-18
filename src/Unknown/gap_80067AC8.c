#include "Unknown/gap_80067AC8.h"

// .text:0x80067AC8 size:0x78
s16 fn_80067AC8(s16 key, s8 column) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (key == lbl_80108EDC[i][j]) {
                if (column == -1) return key;
                return lbl_80108EDC[i][column];
            }
            if (lbl_80108EDC[i][j] == -1) break;
        }
    }
    return -1;
}

// .text:0x80067B40 size:0x108
void fn_80067B40(void) {
    return;
}

// .text:0x80067C48 size:0x328
void fn_80067C48(void) {
    return;
}

// .text:0x80067F70 size:0x534
void fn_80067F70(void) {
    return;
}

// .text:0x800684A4 size:0x70
void fn_800684A4(void) {
    return;
}

// .text:0x80068514 size:0x118
void fn_80068514(void) {
    return;
}

// .text:0x8006862C size:0xF4
void fn_8006862C(void) {
    return;
}

// .text:0x80068720 size:0x5C
void fn_80068720(u8 index) {
    if (lbl_800EF808.enabled398 != 0) {
        fn_800A86B4(3);
        fn_800A8B78(&lbl_802E4CE8[index]);
    }
}

// .text:0x8006877C size:0xBC
void fn_8006877C(void) {
    return;
}

// .text:0x80068838 size:0xF78
void fn_80068838(void) {
    return;
}

// .text:0x800697B0 size:0xA4
void fn_800697B0(void) {
    return;
}

// .text:0x80069854 size:0xA4
void fn_80069854(void) {
    return;
}

// .text:0x800698F8 size:0x170
void fn_800698F8(void) {
    return;
}

// .text:0x80069A68 size:0x30
void fn_80069A68(void) {
    fn_80021518(0x35, lbl_800EF808.soundC0);
}

// .text:0x80069A98 size:0x3C
void fn_80069A98(void) {
    fn_80034CEC(lbl_803CBD30);
    lbl_803CBD30 = NULL;
    lbl_80366158.state = 2;
}

// .text:0x80069AD4 size:0x34
void fn_80069AD4(void) {
    if (lbl_80366158.state == 2) fn_800B0A14_removeQueue();
}
