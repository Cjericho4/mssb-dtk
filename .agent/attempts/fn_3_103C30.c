/* fn_3_103C30 NONMATCHING (rep_3090.c) - camera-follow smoothing; ~75 of 150 lines differ.
 * Logic, calls, constants and the f28-f31 math match exactly. Remaining diffs are stack layout:
 * target = [dir 0x8][scaled 0x14][diff 0x20][inline 36-byte by-value param copy 0x2c][dead memcpy
 * of pos 0x50][CamFollowVecs temp 0x5c..0x7c][result 0x80]; ours puts result/prev below the param
 * copy and caches the param-copy addresses in r27/r28/r31 (stmw r28) instead of re-materializing
 * them with addi, and the camPos/camTarget float copies load x,y,z in order in the target
 * (set-helper inline loads z,y,x; plain field copies interleave lfs/stfs).
 * Tried: local decl order (top-level and in-block), out-pointer instead of struct return,
 * 3 separate VecXYZ by-value params with a memcpy-returning inline.
 * Header changes (include/game/rep_3090.h, padding carved in Struct_DE94_Inner): camPos (0xC4,
 * VecXYZ), camTarget (0xD0), followGain/followDamp/followDist (0x10C/0x110/0x114),
 * field_0x9B4 (u8); prototype void fn_3_103C30(VecXYZ* pos). See fn_3_103C30.headers.diff.
 */
typedef struct CamFollowVecs {
    VecXYZ cur;
    VecXYZ pos;
    VecXYZ target;
} CamFollowVecs;

static inline void fn_3_103C30_set(VecXYZ* v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline VecXYZ fn_3_103C30_follow(CamFollowVecs v, f32 gain, f32 damp, f32 dist) {
    VecXYZ dir;
    VecXYZ scaled;
    VecXYZ diff;
    f32 len;
    f32 amt;

    PSVECSubtract((Vec*)&v.target, (Vec*)&v.pos, (Vec*)&dir);
    len = PSVECDistance((Vec*)&v.target, (Vec*)&v.pos);
    PSVECSubtract((Vec*)&v.cur, (Vec*)&v.pos, (Vec*)&diff);
    PSVECScale((Vec*)&diff, 0.01f, (Vec*)&scaled);
    amt = gain * (dist - len) + damp * (PSVECDotProduct((Vec*)&scaled, (Vec*)&dir) / len);
    PSVECNormalize((Vec*)&dir, (Vec*)&dir);
    PSVECScale((Vec*)&dir, amt * 0.01f, (Vec*)&dir);
    PSVECAdd((Vec*)&v.target, (Vec*)&dir, (Vec*)&v.target);
    return v.target;
}

void fn_3_103C30(VecXYZ* pos) {
    VecXYZ prev;
    CamFollowVecs v;
    VecXYZ result;

    if (lbl_3_common_bss_DE94->field_0x9B4 != 0) {
        memcpy(&prev, pos, sizeof(VecXYZ));
        fn_3_103C30_set(&v.target, lbl_3_common_bss_DE94->camTarget.x, lbl_3_common_bss_DE94->camTarget.y,
                        lbl_3_common_bss_DE94->camTarget.z);
        memcpy(&v.pos, pos, sizeof(VecXYZ));
        fn_3_103C30_set(&v.cur, lbl_3_common_bss_DE94->camPos.x, lbl_3_common_bss_DE94->camPos.y,
                        lbl_3_common_bss_DE94->camPos.z);
        result = fn_3_103C30_follow(v, lbl_3_common_bss_DE94->followGain, lbl_3_common_bss_DE94->followDamp,
                                    lbl_3_common_bss_DE94->followDist);
        lbl_3_common_bss_DE94->camPos.x = pos->x;
        lbl_3_common_bss_DE94->camPos.y = pos->y;
        lbl_3_common_bss_DE94->camPos.z = pos->z;
        lbl_3_common_bss_DE94->camTarget.x = result.x;
        lbl_3_common_bss_DE94->camTarget.y = result.y;
        lbl_3_common_bss_DE94->camTarget.z = result.z;
        pos->x = result.x;
        pos->y = result.y;
        pos->z = result.z;
    }
}

