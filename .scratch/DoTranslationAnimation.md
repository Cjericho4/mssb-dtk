# DoTranslationAnimation

Five attempts exhausted. Best 89.06801% fuzzy match. Build passes, match count 4139 unchanged.

Remaining differences: initial type/vectorSize r29/r30 permutation; dynamic payload-add association; Bezier expression scheduling, float-register allocation; Hermite coefficient/register ordering; volatile result scratch forces original stack layout but changes final load scheduling (marked FAKEMATCH). Shared inline helpers retain the documented formulas and quantization. No formula contradiction with animations.md 2.1.

2026-11-01 continuation: Five refinements. Associating the interpolation base with vectorSize before offset improves the fuzzy score to 91.692696%. Remaining: signed-shift codegen, polynomial scheduling/coloring, and output-load scheduling. Separate signed mode webs improved instruction count but scored worse; not retained.
