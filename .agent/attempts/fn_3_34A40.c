// In tree, ~99.9% fuzzy. Only diff: the __abs(lbl_3_bss_170[0] - radToShortAngle(...)) temp lands in r0
// (target r3). Tried: s16/s32 angle local, reusing an int local for the difference.
