// Best attempt (16 sbs lines, from a stub): logic matches; only the two double constants (int->double magic and 0.06) load via addi+lfd 0(r) in a different order/registers (scheduler artifact); operand order, s16 temp, extern rodata and f64 local forms are identical.
s32 fn_3_B7E44(f32 x, s16 angle) {
    s32 d;
    f32 t;

    if (angle < 0x1E0 || angle > 0x620) {
        return 0;
    }
    d = angle - 0x400;
    d = ABS(d);
    t = 0.06 * (s16)(0x200 - d);
    if (63.0f + t < x) {
        return 2;
    }
    return 55.0f + t < x;
}
