#include "game/gap_FF4C.h"

// .text:0x0000FF4C size:0x4C mapped:0x8064EFE0
static inline u32 lcgStep(u32 x, int shift) {
    return ((x * 8) + ((s32)x >> shift) + (x & 0x505)) & 0x7FFF;
}

void fn_3_FF4C(void) {
    g_Ball.StaticRandomInt1 = lcgStep(g_Ball.StaticRandomInt1, 1);
    g_Ball.StaticRandomInt2 = lcgStep(g_Ball.StaticRandomInt2, 2);
}

// .text:0x0000FF98 size:0x98 mapped:0x8064F02C
void fn_3_FF98(void) {
    return;
}

// .text:0x00010030 size:0x11C mapped:0x8064F0C4
void fn_3_10030(void) {
    return;
}

// .text:0x0001014C size:0x17C mapped:0x8064F1E0
void ballPhysica(void) {
    return;
}

