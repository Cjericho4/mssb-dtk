# DoEulerAnimation

Five attempts exhausted. 88.666664% fuzzy match; 52 feedback entries. Build succeeds; match count stays 4139.

The first 150 instructions (setup, offsets, normalized time, hold and wrapped linear loop) match. Remaining: outgoing-payload address association and load scheduling, Bezier evaluation ordering/registers. Panic arguments and final stack layout match.

Layout caveat contradicting the unconditional setting-order prose in animations.md: Euler skips only the scale vector, not a scale quaternion, even if the scale-quaternion bit is set (0x800B6EC0..CC).

2026-11-01: Five refinements, one compile failure (volatile output argument). Grouping interpolation base with vectorSize before offset improves to 91.219406%; 46 feedback entries remain in Bezier float scheduling/coloring. Full build and preserved-match checks pass.
