# Function categorization summary

Processed **1700** functions from `input.tsv`.

## Counts by category and difficulty

| Category | Easy | Medium | Hard | Total |
|---|---:|---:|---:|---:|
| leaf_setter | 72 | 0 | 16 | 88 |
| state_machine | 0 | 111 | 458 | 569 |
| loop_table | 0 | 105 | 185 | 290 |
| float_math | 0 | 0 | 251 | 251 |
| call_sequence | 0 | 139 | 49 | 188 |
| data_driven | 0 | 16 | 27 | 43 |
| other | 15 | 155 | 101 | 271 |
| **Total** | 87 | 526 | 1087 | 1700 |

## 50 promising easy/medium functions

Ranked by `size_bytes / difficulty_weight` (easy = 1, medium = 2), grouped by source file.

### `src/game/gap_106DFC.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 31 | `fn_3_10EFAC` | 552 | state_machine | medium | 276 | 138 insns, 7 calls |

### `src/game/gap_1293D0.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 8 | `fn_3_12A6C4` | 588 | loop_table | medium | 294 | 147 insns, 1 loop backedge |
| 14 | `fn_3_12C1AC` | 580 | other | medium | 290 | 145 insns, 2 calls |

### `src/game/gap_9CD90.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 20 | `fn_3_9E368` | 568 | other | medium | 284 | 142 insns, 1 call |
| 22 | `fn_3_9E5A0` | 564 | other | medium | 282 | 141 insns, 1 call |

### `src/game/gap_AC9F8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 25 | `fn_3_AFE0C` | 560 | state_machine | medium | 280 | 140 insns, 3 calls |

### `src/game/gap_EA340.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 36 | `fn_3_ED818` | 548 | state_machine | medium | 274 | 137 insns, 6 calls |

### `src/game/m_sound.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 24 | `fn_3_8BBC4` | 560 | loop_table | medium | 280 | 140 insns, 1 loop backedge |
| 46 | `fn_3_8C2DC` | 532 | other | medium | 266 | 133 insns, 2 calls |

### `src/game/rep_1038.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 19 | `fn_3_6C1D8` | 568 | state_machine | medium | 284 | 142 insns, 14 calls |

### `src/game/rep_1200.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 10 | `fn_3_74AC4` | 584 | other | medium | 292 | 146 insns, 1 call |

### `src/game/rep_1330.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 29 | `fn_3_7C7AC` | 556 | call_sequence | medium | 278 | 139 insns, 19 calls |

### `src/game/rep_13B8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 50 | `fn_3_88D88` | 528 | state_machine | medium | 264 | 132 insns, 7 calls |

### `src/game/rep_16B8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 11 | `fn_3_9497C` | 584 | loop_table | medium | 292 | 146 insns, 1 loop backedge |

### `src/game/rep_1770.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 40 | `fn_3_9B108` | 536 | call_sequence | medium | 268 | 134 insns, 12 calls |

### `src/game/rep_1FD8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 5 | `fn_3_C19C8` | 592 | loop_table | medium | 296 | 148 insns, 1 loop backedge |
| 41 | `fn_3_C54D0` | 536 | other | medium | 268 | 134 insns, 29 calls |

### `src/game/rep_21F8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 47 | `fn_3_C937C` | 532 | call_sequence | medium | 266 | 133 insns, 9 calls |

### `src/game/rep_2308.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 48 | `fn_3_CAF9C` | 532 | loop_table | medium | 266 | 133 insns, 2 loop backedges |

### `src/game/rep_28A8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 42 | `fn_3_DCA68` | 536 | state_machine | medium | 268 | 134 insns, 9 calls |

### `src/game/rep_2998.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 18 | `fn_3_E3044` | 576 | state_machine | medium | 288 | 144 insns, 8 calls |

### `src/game/rep_3090.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 6 | `fn_3_103C30` | 588 | call_sequence | medium | 294 | 147 insns, 10 calls |
| 43 | `fn_3_105E00` | 532 | call_sequence | medium | 266 | 133 insns, 21 calls |

### `src/game/rep_3310.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 26 | `fn_3_11CF84` | 556 | state_machine | medium | 278 | 139 insns, 17 calls |

### `src/game/rep_3448.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 7 | `fn_3_125604` | 588 | state_machine | medium | 294 | 147 insns, 7 calls |

### `src/game/rep_3880.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 15 | `fn_3_1559E4` | 580 | call_sequence | medium | 290 | 145 insns, 6 calls |
| 23 | `fn_3_14EAF4` | 560 | call_sequence | medium | 280 | 140 insns, 6 calls |
| 32 | `fn_3_1517D0` | 552 | loop_table | medium | 276 | 138 insns, 1 loop backedge |
| 38 | `fn_3_14BCB0` | 540 | loop_table | medium | 270 | 135 insns, 1 loop backedge |

### `src/game/rep_3C80.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 27 | `fn_3_15F648` | 556 | state_machine | medium | 278 | 139 insns, 9 calls |

### `src/game/rep_3F60.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 33 | `fn_3_168704` | 552 | state_machine | medium | 276 | 138 insns, 5 calls |

### `src/game/rep_4090.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 28 | `fn_3_16D5E4` | 556 | state_machine | medium | 278 | 139 insns, 7 calls |

### `src/game/rep_720.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 44 | `fn_3_1C684` | 532 | call_sequence | medium | 266 | 133 insns, 6 calls |
| 45 | `fn_3_1C8AC` | 532 | call_sequence | medium | 266 | 133 insns, 8 calls |

### `src/game/rep_AC8.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 3 | `fn_3_58F58` | 596 | other | medium | 298 | 149 insns |

### `src/game/rep_E08.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 9 | `fn_3_62904` | 588 | state_machine | medium | 294 | 147 insns, 6 calls |

### `src/game/sta_c2.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 1 | `fn_3_CC5C4` | 600 | loop_table | medium | 300 | 150 insns, 1 loop backedge |
| 4 | `fn_3_CBF80` | 596 | loop_table | medium | 298 | 149 insns, 2 loop backedges |
| 12 | `fn_3_CDB48` | 584 | call_sequence | medium | 292 | 146 insns, 6 calls |
| 35 | `fn_3_D62F0` | 548 | loop_table | medium | 274 | 137 insns, 2 loop backedges |
| 39 | `fn_3_D4E00` | 540 | call_sequence | medium | 270 | 135 insns, 9 calls |
| 49 | `fn_3_CFB44` | 532 | state_machine | medium | 266 | 133 insns, 5 calls |

### `src/game/sta_c4.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 17 | `fn_3_F8878` | 580 | loop_table | medium | 290 | 145 insns, 1 loop backedge |

### `src/game/sta_c5.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 2 | `fn_3_EF55C` | 600 | state_machine | medium | 300 | 150 insns, 6 calls |
| 13 | `fn_3_F5C30` | 584 | call_sequence | medium | 292 | 146 insns, 6 calls |
| 16 | `fn_3_EEFD4` | 580 | state_machine | medium | 290 | 145 insns, 8 calls |
| 30 | `fn_3_F3CD0` | 556 | loop_table | medium | 278 | 139 insns, 1 loop backedge |
| 34 | `fn_3_EE96C` | 552 | call_sequence | medium | 276 | 138 insns, 17 calls |
| 37 | `fn_3_EF930` | 548 | call_sequence | medium | 274 | 137 insns, 14 calls |

### `src/game/sta_c6.c`

| Rank | Function | Size | Category | Difficulty | Value | Notes |
|---:|---|---:|---|---|---:|---|
| 21 | `fn_3_E5A84` | 568 | state_machine | medium | 284 | 142 insns, 18 calls |

