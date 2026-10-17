#include "challenge/gap_26AF8.h"

// .text:0x00026AF8 size:0x84
void fn_1_26AF8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    scene->byte1E = 0;
    scene->byte20 = 0;
    scene->byte21 = 0;
    scene->byte1F = 0;
    scene->byte22 = 0;
    while (lbl_1_data_FB98[scene->byte1F].data != NULL) {
        scene->byte1F++;
    }
    fn_80035A00();
    lbl_803CC1B8->aFunctionPointer = fn_1_26928;
}
