# DoScaleAnimation

Three attempts; best retained: 95.94785% fuzzy match. Build succeeds, baseline 4139 matches preserved. First 153 instructions match. Remaining: scale-axis slerp float-register allocation (dot product caching, angle/step and antipodal step), Bezier scheduling and Hermite coefficient-register permutation. A precomputed-first-weight slerp helper and flat Hermite evaluation were worse. Two refinements remain under the five-attempt cap, but the remaining allocation patterns repeat those already investigated in the earlier decoders.

No formula contradiction with animations.md 2.1; scale-axis quaternion is always held/slerped according to scale mode, using remapped time in mode 3.

2026-11-01 continuation: Five new refinements: explicit polynomial expansion and coefficient declaration changes. None beat the shared slerp declaration improvement (96.00153%). Prior body retained; quaternion component coloring and polynomial scheduling remain.
