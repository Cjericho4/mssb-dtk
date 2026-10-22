#include "game/rep_4090.h"
#include "header_rep_data.h"
#include "game/particle_spawn.h"

// .text:0x0016C548 size:0x330 mapped:0x807AB5DC
void fn_3_16C548(void) {
    return;
}

// .text:0x0016C878 size:0x3B4 mapped:0x807AB90C
void fn_3_16C878(void) {
    return;
}

// .text:0x0016CC2C size:0x8AC mapped:0x807ABCC0
void fn_3_16CC2C(void) {
    return;
}

// .text:0x0016D4D8 size:0x10C mapped:0x807AC56C
s32 fn_3_16D4D8(u8 idx, f32 f) {
    VecXYZ v = {0.0f, 0.0f, 0.0f};
    f32 negY;

    if (g_hugeAnimStruct.AnimationStructPtrs[idx]->unk276 & 0x6) {
        return 1;
    }
    fn_8001B728(idx, 0x23, &v);
    negY = -v.y;
    v.x = v.y = v.z = 0.0f;
    fn_8001B728(idx, 0x1F, &v);
    return ((f >= negY) | (f >= -v.y)) != 0;
}

// .text:0x0016D5E4 size:0x22C mapped:0x807AC678
void fn_3_16D5E4(void) {
    return;
}

