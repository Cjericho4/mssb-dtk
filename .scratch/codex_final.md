Squad: 97.01% — `6098820a`
DoQuatAnimation: 99.72% — `5a9e9299`
DoTranslationAnimation: 89.07% — `2a43ffb2`
DoEulerAnimation: 88.67% — `83c38def`
DoScaleAnimation: 95.95% — `a77f14b0`
fn_8001C234: MATCH! — `2ffae170`

Build passes; matches increased 4,139 → 4,140, with none lost. Remaining differences documented in `.scratch/<fn>.md`.

`animations.md` corrections: Euler skips only the scale vector; clarified scale-quaternion interpolation and dispatch arguments — `c6df9db7`. No interpolation-formula contradictions found. Nothing pushed.

## 2026-11-01 continuation

DoQuatAnimation: 99.82%

Squad: 97.01%

DoScaleAnimation: 96.00%

DoTranslationAnimation: 91.69%

DoEulerAnimation: 91.22%

fn_80016710: 98.70%

fn_80012B90: 98.85%

fn_80013680: 98.66%

f_InitActorWithLayout: 94.95%

fn_80017814: 93.77%

fn_80018024: 76.17%

fn_800145F8: 98.21%

fn_800227E4: MATCH

Full ninja passes; exact matches 4140 -> 4141, none lost. Pointer-arithmetic checks pass for both changed units. All remaining nonmatches reached the five-refinement limit. fn_800227E4 matched on refinement four. The unchanged near-miss commits contain notes only; DoScaleAnimation improved via the shared slerp declaration change in 3cc7e94e. Model sizing, retail maxima, ARAM allocator limits and separate actor workspace are recorded in model_limits.md. Nothing pushed.
