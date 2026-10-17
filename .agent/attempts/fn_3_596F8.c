// In tree (~96%). Remaining: GameLogic/lbl_3_data_470C address regs swapped (r4/r5) in the second loop and fmuls dest f1 vs f0.
// Tried: loop as inline helper (helped), decl orders, increment order, float temp, operand orders.
