/* fn_3_C2AA0 (src/game/rep_1FD8.c) NONMATCHING, ~11 diff lines.
 * Needs: #include "Dolphin/mtxext.h" in rep_1FD8.c; header prototype
 *   BOOL fn_3_C2AA0(Vec* pos, f32 width, f32 height);  (see fn_3_C2AA0.headers.diff)
 * Matches: GPR alloc, stack layout, mfcr flag building (statement-split flags |=),
 *   corner store order (chained assignments), cmplwi via (u32) casts.
 * Remaining: float register allocation in the corner setup block only
 *   (target: z f4, x f2, 0.5 f1, y f0, hw f5, hh f6, width f29/height f31;
 *   ours swaps 0.5/y regs and computes hh before hw). Brute-forced statement
 *   order and f32 local declaration order (720 perms) with no improvement. */
BOOL fn_3_C2AA0(Vec* pos, f32 width, f32 height) {
    Vec corners[4];
    Vec out;
    CameraView* view;
    u32 i;
    u8 acc;
    u8 flags;
    f32 x;
    f32 y;
    f32 z;
    f32 hw;
    f32 hh;
    f32 half;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;

    acc = 0;
    view = fn_80052734(fn_8005268C());
    PSMTXMultVec(view->viewMtx, pos, pos);
    if (pos->z > -1.0f || pos->z < -512.0f) {
        return FALSE;
    }
    half = 0.5f;
    hh = height * half;
    hw = width * half;
    x = pos->x;
    y = pos->y;
    z = pos->z;
    x0 = x - hw;
    y0 = y - hh;
    x1 = x + hw;
    y1 = y + hh;
    corners[0].z = corners[1].z = corners[2].z = corners[3].z = z;
    corners[0].x = corners[3].x = x0;
    corners[1].x = corners[2].x = x1;
    corners[0].y = corners[1].y = y0;
    corners[3].y = corners[2].y = y1;
    for (i = 0; i < 4; i++) {
        PSMTX44MultVec(view->projMtx, &corners[i], &out);
        flags = (out.x < -1.0f) | ((out.x > 1.0f) << 1);
        flags |= (out.y < -1.0f) << 2;
        flags |= (out.y > 1.0f) << 3;
        if (flags == 0) {
            return TRUE;
        }
        acc &= flags;
    }
    if ((u32)(acc & 3) == 1 || (u32)(acc & 3) == 2) {
        return FALSE;
    }
    if ((u32)(acc & 0xC) == 4 || (u32)(acc & 0xC) == 8) {
        return FALSE;
    }
    return TRUE;
}
