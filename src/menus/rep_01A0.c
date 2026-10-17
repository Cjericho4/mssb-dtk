#include "menus/rep_01A0.h"
#include "musyx/musyx.h"

extern f32 lbl_2_bss_18;

// .text:0x00000A70 size:0xC8
void fn_2_A70(void) {
    return;
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
