// In tree at 99.8% fuzzy. Only remaining diff (2 lines) is the guard
//     if (frames < f->unk1D2 && fielderIdx == 0) return;
// target: "cmpwi r29,0; bne CONT; b RET" vs ours "beq RET".
// Tried: nested ifs, negated ||, empty-then/else-return, goto, condition order swap,
// wrapping the rest in if (frames >= d || idx != 0), inline bool helpers (worse).
