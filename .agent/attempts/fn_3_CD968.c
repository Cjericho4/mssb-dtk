/* fn_3_CD968 (sta_c2.c) NONMATCHING best attempt.
 * Remaining diff: only the corner-setup float block (~20 lines): target loads x into f2, 0.5 into f1, y into f0,
 * computes fmuls f5,f29,f1 (w*0.5 operand order) and z in f4; all four corner values computed before the x/y stores.
 * MWCC here emits fmuls f6,f0,f31 (const first) and interleaves stores. Everything else (bit-code, saved regs) matches.
 * Needs: sta_c2.h prototype `BOOL fn_3_CD968(Vec* pos, f32 w, f32 h);`, `#include "Dolphin/mtxext.h"`,
 * and local `s32 fn_8005268C(void);` in sta_c2.c.
 */
BOOL fn_3_CD968(Vec* pos, f32 w, f32 h) {
    CameraView* cam;
    u8 acc = 0;
    Vec pts[4];
    Vec out;
    u32 i;
    u8 code;
    f32 x;
    f32 y;
    f32 z;
    f32 hw;
    f32 hh;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;

    cam = fn_80052734(fn_8005268C());
    PSMTXMultVec(cam->viewMtx, pos, pos);
    z = pos->z;
    if (z > -1.0f || z < -512.0f) {
        return FALSE;
    }
    x = pos->x;
    y = pos->y;
    hh = h * 0.5f;
    hw = w * 0.5f;
    x0 = x - hw;
    y0 = y - hh;
    x1 = x + hw;
    y1 = y + hh;
    pts[0].z = pts[1].z = pts[2].z = pts[3].z = z;
    pts[0].x = pts[3].x = x0;
    pts[1].x = pts[2].x = x1;
    pts[0].y = pts[1].y = y0;
    pts[3].y = pts[2].y = y1;
    for (i = 0; i < 4; i++) {
        PSMTX44MultVec(cam->projMtx, &pts[i], &out);
        code = out.x < -1.0f;
        code |= (out.x > 1.0f) << 1;
        code |= (out.y < -1.0f) << 2;
        code |= (out.y > 1.0f) << 3;
        if (code == 0) {
            return TRUE;
        }
        acc &= code;
    }
    if ((acc & 3U) == 1 || (acc & 3U) == 2) {
        return FALSE;
    }
    if ((acc & 0xCU) == 4 || (acc & 0xCU) == 8) {
        return FALSE;
    }
    return TRUE;
}
