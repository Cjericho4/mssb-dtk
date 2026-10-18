#include "menus/gap_D08.h"
#include "UnknownHeaders.h"
#include "musyx/seq.h"

extern u32 sndSeqGetValid(u32 sequence);
extern u32 lbl_2_bss_D974[];
extern s16 lbl_2_bss_D958[];
extern void (*lbl_2_data_138[])(void);

// .text:0x00000D08 size:0x80
void fn_2_D08(u16 index, u16 time, u8 mode) {
    if (lbl_2_bss_D974[index] != 0xFFFFFFFF && sndSeqGetValid(lbl_2_bss_D974[index]) != 0) {
        sndSeqVolume(0, time, lbl_2_bss_D974[index], mode);
    }
}

// .text:0x00000D88 size:0xFC
void fn_2_D88(void) {
    return;
}

// .text:0x00000E84 size:0xE0
void fn_2_E84(u16 index, s16 sound) {
    MenusSequenceConfig* config = &lbl_2_data_128[sound];
    if (lbl_2_bss_D974[index] != 0xFFFFFFFF) {
        if (sndSeqGetValid(lbl_2_bss_D974[index]) != 0) {
            sndSeqVolume(0, 0, lbl_2_bss_D974[index], 1);
            sndSeqStop(lbl_2_bss_D974[index]);
        }
        lbl_2_bss_D974[index] = -1;
        lbl_2_bss_D958[index] = -1;
    }
    lbl_2_bss_D974[index] = sndSeqPlayEx(config->group, config->song, lbl_2_bss_D984[config->resource], 0, 0);
    lbl_2_bss_D958[index] = sound;
}

// .text:0x00000F64 size:0xB4
void fn_2_F64(void) {
    u16 i;
    for (i = 0; i < 4; i++) {
        if (lbl_2_bss_D974[i] != 0xFFFFFFFF) {
            if (sndSeqGetValid(lbl_2_bss_D974[i]) != 0) {
                sndSeqVolume(0, 0, lbl_2_bss_D974[i], 1);
                sndSeqStop(lbl_2_bss_D974[i]);
            }
            lbl_2_bss_D974[i] = -1;
            lbl_2_bss_D958[i] = -1;
        }
    }
}

// .text:0x00001018 size:0x94
void fn_2_1018(u16 index) {
    if (lbl_2_bss_D974[index] != 0xFFFFFFFF) {
        if (sndSeqGetValid(lbl_2_bss_D974[index]) != 0) {
            sndSeqVolume(0, 0, lbl_2_bss_D974[index], 1);
            sndSeqStop(lbl_2_bss_D974[index]);
        }
        lbl_2_bss_D974[index] = 0xFFFFFFFF;
        lbl_2_bss_D958[index] = -1;
    }
}

// .text:0x000010AC size:0x50
void fn_2_10AC(void) {
    return;
}

// .text:0x000010FC size:0x34
s32 fn_2_10FC(void) {
    fn_80021518(31, (s32)lbl_800EF808.files[2]);
    return 0;
}

// .text:0x00001130 size:0x34
void fn_2_1130(s16 state) {
    lbl_803CC1B8->currentDrawingItem->loadingState = state;
    fn_800B0A14_removeQueue();
}

// .text:0x00001164 size:0x38
void fn_2_1164(void) {
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x0000119C size:0x4
void fn_2_119C(void) {
    return;
}

// .text:0x000011A0 size:0x38
void fn_2_11A0(u16 selection) {
    lbl_803CBBCC->previousSelection = lbl_803CBBCC->selection;
    lbl_803CBBCC->previousState = lbl_803CBBCC->state;
    lbl_803CBBCC->selection = selection;
    lbl_803CBBCC->state = 0;
}

// .text:0x000011D8 size:0x44
void fn_2_11D8(void) {
    lbl_2_data_138[lbl_803CBBCC->selection]();
}
