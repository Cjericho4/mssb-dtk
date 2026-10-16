#include "game/gap_1658F0.h"
#include "UnknownHeaders.h"
#include "game/rep_3310.h"

// .text:0x001658F0 size:0x88 mapped:0x807A4984
void fn_3_1658F0(void) {
    Bss37400Item* p = &lbl_3_common_bss_37400;
    s32 i;

    for (i = 0; i < 9; i++) {
        p->unk12[i].unk1 = 0;
        p->unk12[i].unk0 = 0;
        p->unk12[i].unk2 = 0;
        p->unk12[i].unk3 = 0;
        p->unk12[i].unk4 = 0;
        p->scoutFlags[i].oldFlags = 0;
        p->scoutFlags[i].newFlags = 0;
    }
}

// .text:0x00165978 size:0x14 mapped:0x807A4A0C
void fn_3_165978(void) {
    lbl_3_common_bss_37400.field_0x4A = 0;
}

// .text:0x0016598C size:0x14 mapped:0x807A4A20
void fn_3_16598C(void) {
    lbl_3_common_bss_37400.field_0x4A = 0;
}

// .text:0x001659A0 size:0x384 mapped:0x807A4A34
void fn_3_1659A0(void) {
    return;
}

// .text:0x00165D24 size:0x688 mapped:0x807A4DB8
void fn_3_165D24(void) {
    return;
}

// .text:0x001663AC size:0x9C mapped:0x807A5440
void fn_3_1663AC(void) {
    HugeAnimEntry2D94* entry;
    s32 i;

    if (g_GameLogic.secondaryGameMode == 0xA || g_GameLogic.secondaryGameMode == 0x12) {
        if (g_hugeAnimStruct.field268_0x3078 != 0) {
            for (i = 0; i < g_hugeAnimStruct.field268_0x3078; i++) {
                entry = &g_hugeAnimStruct.entries_2D94[i];
                if (entry != NULL) {
                    entry->unk_26 = 0;
                }
            }
        }
    } else if (g_Practice.practiceLevel == 4) {
        fn_3_11AB2C();
    }
}

