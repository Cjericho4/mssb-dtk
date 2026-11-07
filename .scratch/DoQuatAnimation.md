# DoQuatAnimation

Five attempts exhausted. Best: 99.72222% fuzzy match, 17 feedback entries, all register permutations in slerp (to.x/y/z in f4/f5/f7; angle/step f29/f30 and antipodal step). All offsets, branches, arithmetic and stack layout agree. Build passes; 4139 matches preserved. No contradiction with animations.md 2.1.

2026-11-01 continuation: five refinements (one failed to compile). Swapping the
angle/step declarations in the shared slerp inline removes five register differences;
12 remain, in destination-component coloring and the antipodal step. Retained this
small improvement. Explicit scalar caching increased register pressure; direct
expansion disturbed the outer easedTime web. Full ninja passes, 4140 matches preserved.
