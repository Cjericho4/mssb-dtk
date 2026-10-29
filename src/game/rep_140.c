#include "game/rep_140.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

// .text:0x000014A4 size:0xB8 mapped:0x80640538
f32 fn_3_14A4(f32* xs, f32* ys, f32* ds, s32 n, f32 x) {
    s32 lo = 0;
    s32 hi = n - 1;
    s32 mid;
    f32 t;
    f32 h;

    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (xs[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo > 0) {
        lo--;
    }
    t = x - xs[lo];
    h = xs[lo + 1] - xs[lo];
    return ys[lo] + t * (t * (3.0f * ds[lo] + t * (ds[lo + 1] - ds[lo]) / h) + ((ys[lo + 1] - ys[lo]) / h - h * (2.0f * ds[lo] + ds[lo + 1])));
}

// .text:0x0000155C size:0x454 mapped:0x806405F0
void fn_3_155C(void) {
    return;
}

// Evaluate one spline component at the requested time.
/* FAKEMATCH: The two components inline the shared spline evaluation. */
static inline f32 interpolateCurve(f32* xs, f32* ys, f32* ds, s32 n, f32 x) {
    s32 lo = 0;
    s32 hi = n - 1;
    s32 mid;
    f32 t;
    f32 h;

    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (xs[mid] < x) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo > 0) {
        lo--;
    }
    t = x - xs[lo];
    h = xs[lo + 1] - xs[lo];
    return ys[lo] + t * (t * (3.0f * ds[lo] + t * (ds[lo + 1] - ds[lo]) / h) + ((ys[lo + 1] - ys[lo]) / h - h * (2.0f * ds[lo] + ds[lo + 1])));
}

// .text:0x000019B0 size:0x174 mapped:0x80640A44
// Evaluate the X and Z components of a spline using their shared time keys.
void fn_3_19B0(VecXZ* out, f32* valuesX, f32* valuesZ, f32* times, f32* curvesX, f32* curvesZ, s32 count, f32 time) {
    out->x = interpolateCurve(times, valuesX, curvesX, count, time);
    out->z = interpolateCurve(times, valuesZ, curvesZ, count, time);
}

// .text:0x00001B24 size:0xABC mapped:0x80640BB8
void fn_3_1B24(void) {
    return;
}

// .text:0x000025E0 size:0x304 mapped:0x80641674
void running_roundBasePosition(struct _VecXZ* out, struct _VecXZ* points, s32 count, f32 t) {
    return;
}

// .text:0x000028E4 size:0x488 mapped:0x80641978
void fn_3_28E4(void) {
    return;
}

// .text:0x00002D6C size:0x3A0 mapped:0x80641E00
void fn_3_2D6C(void) {
    return;
}

// .text:0x0000310C size:0x4C8 mapped:0x806421A0
void fn_3_310C(void) {
    return;
}

