#include "menus/rep_01A0.h"
#include "musyx/musyx.h"
#include "UnknownHeaders.h"
extern u8 lbl_2_bss_1C;

extern f32 lbl_2_bss_18;

// .text:0x00000A70 size:0xC8
void fn_2_A70(u16 duration) {
    if (lbl_2_bss_1C == 0 && lbl_2_data_134.voice != 0xFFFFFFFF &&
        sndFXCheck(lbl_2_data_134.voice) == lbl_2_data_134.voice) {
        QueueEntry* entry = fn_800B0A5C_insertQueue(fn_2_B38, 0x8000);
        if (duration == 0) duration = 1;
        entry->vec.x = -lbl_2_bss_18 / duration;
        lbl_2_bss_1C = 1;
    }
}

// .text:0x00000B38 size:0xE0
void fn_2_B38(void) {
    return;
}

// .text:0x00000C18 size:0x5C
void fn_2_C18(void) {
    if (lbl_2_data_134.voice != 0xFFFFFFFF) {
        if (sndFXCheck(lbl_2_data_134.voice) == lbl_2_data_134.voice) {
            sndFXKeyOff(lbl_2_data_134.voice);
            lbl_2_data_134.voice = 0xFFFFFFFF;
        }
    }
}

// .text:0x00000C74 size:0x94
void fn_2_C74(u8 value) {
    if (lbl_2_data_134.voice != 0xFFFFFFFF && sndFXCheck(lbl_2_data_134.voice) == lbl_2_data_134.voice) {
        sndFXCtrl(lbl_2_data_134.voice, 7, value);
    } else {
        lbl_2_bss_18 = value;
    }
}
