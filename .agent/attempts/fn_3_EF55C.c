/* fn_3_EF55C NONMATCHING (sta_c5.c) - best ~38 differing lines of 150 (sbs '*' count, excluding rodata names).
 * Structure, stack layout (edgesA@0xc, edgesB@0x8, cross@0x10, b@0x1c, a@0x28), calls and
 * constants all match. Remaining diffs:
 *  - r27/r28 swapped between the edges pointer and the strength-reduced (s8)(i*2-1) sign counter
 *    (both loops).
 *  - Scheduling of the a/b component loads/fsubs/stores: target loads both edge bytes first, then
 *    all of p0.x,p1.x,pos.z,p0.z,p1.z, does 4 fsubs (ax,bx,az,bz) and stores b.y,a.x,a.z,b.x,b.z,a.y.
 *    Tried all 720 statement orders, s32/u32/u8 index temps, flat f32 index (e*2, e*2+1),
 *    f32 scalar temps, and an inline helper (inline grows frame to 0xA0). None fixed it.
 * Also needs fn_3_EF7B4 to pass idx (r4) through: target `fn_3_EF7B4(Vec*, u8)`; with this
 * signature EF7B4 still differs only by load/store scheduling of the 12-byte struct copy.
 * Header change (include/game/sta_c5.h): prototypes become
 *   u8 fn_3_EF55C(Vec* pos, u8 idx);  s32 fn_3_EF7B4(Vec* pos, u8 idx);
 */
/* Corner points (x, z) of the 3 boundary quads. */
extern f32 lbl_3_data_1B824[3][4][2];

u8 fn_3_EF55C(Vec* pos, u8 idx) {
    u8 edgesA[2][2] = {{1, 3}, {0, 2}};
    u8 edgesB[2][2] = {{0, 1}, {2, 3}};
    Vec a;
    Vec b;
    Vec cross;
    f32 (*pts)[2];
    u32 i;
    

    if (pos->y > 0.0f) {
        return 1;
    }
    pts = lbl_3_data_1B824[idx];
    for (i = 0; i < 2; i++) {
        a.z = pos->z - pts[edgesA[i][0]][1];
        b.y = 0.0f;
        a.y = 0.0f;
        b.x = pts[edgesA[i][1]][0] - pts[edgesA[i][0]][0];
        b.z = pts[edgesA[i][1]][1] - pts[edgesA[i][0]][1];
        a.x = pos->x - pts[edgesA[i][0]][0];
        PSVECNormalize(&a, &a);
        PSVECNormalize(&b, &b);
        PSVECCrossProduct(&b, &a, &cross);
        if (cross.y * (s8)(i * 2 - 1) < 0.0f) {
            return 1;
        }
    }
    for (i = 0; i < 2; i++) {
        a.z = pos->z - pts[edgesB[i][0]][1];
        b.y = 0.0f;
        a.y = 0.0f;
        b.x = pts[edgesB[i][1]][0] - pts[edgesB[i][0]][0];
        b.z = pts[edgesB[i][1]][1] - pts[edgesB[i][0]][1];
        a.x = pos->x - pts[edgesB[i][0]][0];
        PSVECNormalize(&a, &a);
        PSVECNormalize(&b, &b);
        PSVECCrossProduct(&b, &a, &cross);
        if (cross.y * (s8)(i * 2 - 1) < 0.0f) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000EF7B4 size:0x4C mapped:0x8072E848
s32 fn_3_EF7B4(Vec* pos, u8 idx) {
    Vec local = *pos;
    return fn_3_EF55C(&local, idx) != 0;
}
