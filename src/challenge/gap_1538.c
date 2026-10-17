#include "challenge/gap_1538.h"

// .text:0x00001538 size:0x94
void fn_1_1538(void) {
    return;
}

// .text:0x000015CC size:0x68
void fn_1_15CC(void) {
    return;
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if (lbl_803C6CF8.allowLoad == 1) {
        lbl_803CC1B8->unk14 = ARAMTransfer(&lbl_1_data_0[3], 0, 0, 0);
        lbl_803CC1B8->aFunctionPointer = fn_1_15CC;
    }
}

// .text:0x000016A0 size:0x2A8
void fn_1_16A0(void) {
    return;
}

// .text:0x00001948 size:0x24
void fn_1_1948(void) {
    if (lbl_803CC1B8->loadingState != 0) {
        lbl_803CC1B8->aFunctionPointer = fn_1_11D0;
    }
}

// .text:0x0000196C size:0x40
void fn_1_196C(void) {
    fn_800A7D4C(0, &lbl_1_data_298[lbl_803CBBC0]);
}
