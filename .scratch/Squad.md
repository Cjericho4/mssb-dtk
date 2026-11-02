# Squad

Five attempts exhausted. Best version: 97.01013% objdiff fuzzy match. Build succeeds; match count 4139 (baseline 4139).

Instruction count, branches, and formulas agree; remaining differences are float-register colouring and load/operation scheduling. Flat named scalar form beats the shared inline slerp version. Original dont_inline scope must remain: removing it inlines empty decoder stubs into ANIMTick and loses that match. No contradiction with animations.md section 2.1.

2026-11-01 continuation: Five new declaration/parameter-web refinements; none improved 97.01013%. Prior body retained. Remaining differences are float coloring and load scheduling (108 feedback entries).
