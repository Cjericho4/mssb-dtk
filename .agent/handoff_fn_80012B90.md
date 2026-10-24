# fn_80012B90 continuation

2026-10-24, load-chain. Five refinement attempts exhausted; explicit continuation required.
Best retained: 183 feedback lines (baseline 330). Build succeeds; not MATCH.

Changes: readiness branch in caller, texture captured before queuing, root base reloaded for each
relocation (retaining repeated typed casts), actor-slot address before selected header loads,
arm selection computed once in an inline loadAlternatingSubItem helper. Corrected fn_800238E0
from three arguments to four: target caller passes index in r4 and r5, layout in r6; callee
uses r4 to select actor storage, stores r5 as a halfword, and consumes layout from r6.
Both declarations and its stub signature agree. Shared helper adaptation also improves fn_80013680.

Attempts (feedback lines):
1. Readiness split, relocation reloads, four-argument call, caller load order and single arm pointer: 283.
2. Texture declaration first, quotient split, actor-slot calculation before headers: 223.
3. Texture initialized at function entry and s8 slotKind: 266, reverted.
4. Alternating-hand case body in static inline helper: 183, retained.
5. Final case in completeSubItemSet inline helper: 188, reverted; helper removed.

Remaining: slotKind uses r31 instead of r29; subsequent cases allocate texture/object/actor-slot
registers differently. Initialization quotient scratch registers differ, queue argument scheduling
and busy branches differ, and one case shares the switch exit rather than its local continuation.
Do not repeat replacing the obj->buf casts with root-> (known regression).

Verification before commit: ninja, feedback_diff.py (183 lines), report generation, 3967 matches;
all function fuzzy scores compared against the session baseline, no decreases.
