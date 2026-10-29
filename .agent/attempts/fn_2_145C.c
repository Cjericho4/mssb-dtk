// 5 diff lines: r0/r5 swap and relocation on loop branch to the function entry.
#include "mssbTypes.h"
BOOL fn_2_145C(const u16* first, const u16* second) {
    u32 code;
    do {
        code = *first++;
        if (code != *second++) return FALSE;
    } while (code != 0x4000);
    return TRUE;
}
