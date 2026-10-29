#include "challenge/rep_0010.h"
#include "challenge/challenge.h"

/* gap_800AD780.h has incompatible queue-node and OSGetTime declarations with
   this unit; retain its exact callback prototype until those views are unified. */
void fn_800B0C80(void (*callback)(void));

// .text:0x000005EC size:0x508
void fn_1_5EC(void) {
    return;
}

// .text:0x00000AF4 size:0x438
void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2) {
    return;
}

// .text:0x00000F2C size:0x1D8
void fn_1_F2C(void) {
    return;
}

// .text:0x00001104 size:0x4
void _epilog(void) {
    return;
}

// .text:0x00001108 size:0x4
void _unresolved(void) {
    return;
}

// .text:0x0000110C size:0x3C
// Register the challenge scene and initialize its display buffers.
void _prolog(void) {
    fn_800B0C80(fn_1_1148);
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
}

// .text:0x00001148 size:0x88
void fn_1_1148(void) {
    ChallengeScene* scene = (ChallengeScene*)lbl_803CC1B8;
    scene->state16 = 0;
    scene->state14 = 0;
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
}

// .text:0x000011D0 size:0x70
void fn_1_11D0(void) {
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.unk8, lbl_80366158.unk4);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
}

// .text:0x00001240 size:0x2F8
void fn_1_1240(void) {
    return;
}
