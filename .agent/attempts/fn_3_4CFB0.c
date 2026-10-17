// In tree: fn_3_4CFB0 calls static inline aimPitcherAtBase() (99.2% fuzzy).
// The same helper inlined inside fn_3_4D20C produces exactly the target code, so the
// helper body is believed correct; standalone fn_3_4CFB0 still differs (~18 lines: x/z float
// register assignment and r3/r4 for lbl_3_data_4444). Likely a different call shape in the original.
