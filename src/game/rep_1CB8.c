#include "game/rep_1CB8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"

// .text:0x000B79AC size:0x280 mapped:0x806F6A40
void fn_3_B79AC(void) {
    return;
}

// .text:0x000B7C2C size:0xB0 mapped:0x806F6CC0
// Casts a ray between the two points (y flipped) and reports whether it hits a wall-like surface.
BOOL fn_3_B7C2C(Vec* start, Vec* end) {
    VecSrcDst ray;
    CollisionStruct hit;
    u32 t;

    ray.src.x = start->x;
    ray.src.y = -start->y;
    ray.src.z = start->z;
    ray.dst.x = end->x;
    ray.dst.y = -end->y;
    ray.dst.z = end->z;
    t = checkCollision(&ray, &hit, 0, 0) & 0x7F;
    // FAKEMATCH: the negated != chain keeps one compare per value; an == || chain merges 2..5 and 7..8 into range checks.
    if (!(t != BALL_COLLISION_TYPE_WALL && t != BALL_COLLISION_TYPE_STRUCTURE && t != BALL_COLLISION_TYPE_FOUL_LINE &&
          t != BALL_COLLISION_TYPE_UNCLIMBABLE_WALL && t != BALL_COLLISION_TYPE_PIT_WALL && t != BALL_COLLISION_TYPE_PIT &&
          t != BALL_COLLISION_TYPE_CHOMP_HAZARD)) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000B7CDC size:0x90 mapped:0x806F6D70
// Casts a vertical ray at (x, z) and returns FALSE if it lands on grass, dirt, rough terrain, water or type 0x32.
BOOL fn_3_B7CDC(f32 x, f32 z) {
    VecSrcDst ray;
    CollisionStruct hit;
    u32 t;

    ray.src.x = x;
    ray.src.y = -100.0f;
    ray.src.z = z;
    ray.dst.x = x;
    ray.dst.y = 100.0f;
    ray.dst.z = z;
    t = checkCollision(&ray, &hit, 0, 0) & 0x7F;
    // FAKEMATCH: negated != chain, as in fn_3_B7C2C, so 9 and 10 stay separate compares.
    if (!(t != BALL_COLLISION_TYPE_GRASS && t != BALL_COLLISION_TYPE_DIRT && t != BALL_COLLISION_TYPE_ROUGH_TERRAIN &&
          t != BALL_COLLISION_TYPE_WATER && t != 0x32)) {
        return FALSE;
    }
    return TRUE;
}

// .text:0x000B7D6C size:0x6C mapped:0x806F6E00
s32 fn_3_B7D6C(f32 f1, f32 f2) {
    if (f1 > lbl_3_rodata_1D08) {
        if (f2 > f1 - lbl_3_rodata_1D38 && f2 < lbl_3_rodata_1D38 + f1) {
            return 1;
        }
    } else {
        if (f2 > -f1 - lbl_3_rodata_1D38 && f2 < lbl_3_rodata_1D38 - f1) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000B7DD8 size:0x38 mapped:0x806F6E6C


/**
 * @address 000B7DD8
 */
s32 fn_3_B7DD8(f32 f1, f32 f2) {
    /* Target: lfs f3, 0x14(r3) */
    f32 limit = lbl_3_data_4444[2].z;
    
    /* Target: fadds f0, f1, f3 -> fcmpo cr0, f2, f0 -> ble .L_000B7DF8 */
    if (f2 > f1 + limit) {
        /* Target: li r3, 1 -> blr */
        return 1;
    }

    /* Target: fneg f0, f1 
       Target: fadds f0, f0, f3
       Target: fcmpo cr0, f2, f0
       Target: mfcr r0 -> extrwi r3, r0, 1, 1 
       
       Writing it exactly as (-f1 + limit) forces the compiler to negate f1 
       separately before adding, matching the fneg/fadds sequence. */
    return f2 > (-f1 + limit);
}

// .text:0x000B7E10 size:0x34 mapped:0x806F6EA4

/**
 * @address 000B7E10
 */

/**
 * @address 000B7E10
 */
s32 fn_3_B7E10(f32 f1, f32 f2) {
    /* * The first check (f2 < f1 - rodata) triggers a conditional branch.
     * li r3, 1 followed by blr is the standard return for the true case.
     */
    if (f2 < f1 - lbl_3_rodata_1D3C) {
        return 1;
    }

    /* * The second check (f2 < -f1 - rodata) uses branchless logic.
     * fneg f0, f1 -> fsubs f0, f0, f3 -> fcmpo -> mfcr -> srwi.
     * CodeWarrior generates this pattern for boolean normalization 
     * using the Condition Register.
     */
    return f2 < -f1 - lbl_3_rodata_1D3C;
}

// .text:0x000B7E44 size:0xAC mapped:0x806F6ED8
// Classifies a distance against a band whose width falls off linearly with the angle from 0x400 (0 = out of range, 2 = beyond the far edge).
s32 fn_3_B7E44(f32 arg0, s16 arg1) {
    f32 v;
    s32 a;
    if (arg1 < 0x1E0 || arg1 > 0x620) {
        return 0;
    }
    a = __abs(arg1 - 0x400);
    v = 0.06 * (s16)(0x200 - a);
    if (63.0f + v < arg0) {
        return 2;
    }
    return 55.0f + v < arg0;
}
