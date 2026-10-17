#include "challenge/gap_17EFC.h"

// .text:0x00017EFC size:0x2C
s32 fn_1_17EFC(Gap17EFCEntry* a, Gap17EFCEntry* b) {
    if (a->sortKey < b->sortKey) {
        return 1;
    }
    if (a->sortKey > b->sortKey) {
        return -1;
    }
    return 0;
}

// .text:0x00017F28 size:0xC8
void fn_1_17F28(void) {
    return;
}

// .text:0x00017FF0 size:0x184
void fn_1_17FF0(void) {
    return;
}

// .text:0x00018174 size:0x14C
void fn_1_18174(void) {
    return;
}
