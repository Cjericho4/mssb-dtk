#include "game/gap_1690C0.h"
#include "game/rep_3E58.h"
#include "UnknownHeaders.h"
#include "stl/mem.h"

extern u8 lbl_3_data_28908[0xC];
extern u8 lbl_3_data_28914[0xA];

// .text:0x001690C0 size:0x90 mapped:0x807A8154
void fn_3_1690C0(void) {
    s32 i;

    memset(lbl_3_data_28908, 0, 9);
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    i = 8;
    do {
        lbl_3_data_28914[i] &= 0xFD;
    } while (i-- != 0);
    fn_800B0A14_removeQueue();
}

// .text:0x00169150 size:0x2C mapped:0x807A81E4
void fn_3_169150(void) {
    fn_800B0A5C_insertQueue(fn_3_1690C0, 0);
}

