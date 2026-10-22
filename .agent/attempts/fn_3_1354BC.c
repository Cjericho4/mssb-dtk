// Best attempt (5 sbs lines): nested ifs with `ret = 1` + (f32)fabs locals give the target control flow; left: float temps (target d1 f4, d2 f1, |d1| f2, |d2| f3, frsp into f1/f2; ours in-place f1/f2). Two-step webs, f64 temps and decl orders all worse.
s32 fn_3_1354BC(s32 idx, f32 f1, f32 f2) {
    s32 ret = 0;
    f32 d1 = g_Minigame.unkBB0[idx]._00 - f1;
    f32 d2 = g_Minigame.unkBB0[idx]._08 - f2;
    f32 r1 = (f32)fabs(d1);
    f32 r2 = (f32)fabs(d2);

    if (r1 <= lbl_3_rodata_35D8) {
        if (r2 <= lbl_3_rodata_35DC) {
            ret = 1;
        }
    }
    return ret;
}
