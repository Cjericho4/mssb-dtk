#include "menus/rep_0200.h"
#include "Dolphin/OS/OSError.h"

extern char lbl_2_rodata_250[];
extern char lbl_2_rodata_25C[];

// .text:0x0000121C size:0x38
void fn_2_121C(void) {
    OSPanic(lbl_2_rodata_250, 0x4C, lbl_2_rodata_25C);
}
