#include "menus/gap_1254.h"
extern s16 lbl_80108EDC[][5];
extern void fn_800506E8(s32 controller, s32 id, s32 enabled);
extern u8 fn_80067B40(u8 side, u8 id, s32 enabled);
extern s16 fn_80067AC8(s16 key, s8 column);
#include "menus/gap_0.h"
#include "game/gap_B3B70.h"
#include "musyx/musyx.h"
#include "menus/rep_0438.h"
#include "game/rep_3448.h"
#include "menus/gap_D08.h"
#include "menus/gap_71EC4.h"
#include "string.h"

extern void sndFXRelated(s32 id);
#include "menus/rep_0568.h"
#include "menus/gap_16870.h"

extern void fn_800AD038(u32 value);
extern void fn_8004EEF4(s32 a, s32 b, s32 c, s32 d, s32 enabled);

extern u8 lbl_2_bss_100B4;

extern u32 lbl_803CB750;
extern void fn_800625A4(s32 index, s32 command);

// .text:0x00001254 size:0x4
void fn_2_1254(void) {
    return;
}

// .text:0x00001258 size:0x48
void fn_2_1258(void) {
    return;
}

// .text:0x000012A0 size:0x2C
void fn_2_12A0(s16* value, s16 amount) {
    if (*value < 0x7FFF - amount) *value += amount;
    else *value = 0x7FFF;
}

// .text:0x000012CC size:0x2C
void fn_2_12CC(u8* value, u16 amount) {
    if (*value + amount > 0xFF) *value = 0xFF;
    else *value += amount;
}

// .text:0x000012F8 size:0x30
void fn_2_12F8(u16* value, u16 amount) {
    if (*value + amount > 0xFFFF) *value = 0xFFFF;
    else *value += amount;
}

// .text:0x00001328 size:0x2C
void fn_2_1328(u32* value, u16 amount) {
    u32 result = *value + amount;
    if (result > 0x7FFFFFFF) *value = 0x7FFFFFFF;
    else *value = result;
}

// .text:0x00001354 size:0x108
void fn_2_1354(MenusSortEntry* entries, s32 count, s32 descending) {
    u32 i;
    u32 j;
    if (count < 2) return;
    if (descending == 0) {
        MenusSortEntry temp;
        for (i = 0; i < (u32)count; i++) {
            j = i;
            while (j >= 1 && entries[j - 1].value > entries[j].value) {
                temp = entries[j - 1];
                entries[j - 1] = entries[j];
                entries[j] = temp;
                j--;
            }
        }
    } else {
        MenusSortEntry temp;
        for (i = 0; i < (u32)count; i++) {
            j = i;
            while (j >= 1 && entries[j - 1].value < entries[j].value) {
                temp = entries[j - 1];
                entries[j - 1] = entries[j];
                entries[j] = temp;
                j--;
            }
        }
    }
}

// .text:0x0000145C size:0x30
void fn_2_145C(void) {
    return;
}

// .text:0x0000148C size:0x6C
s32 fn_2_148C(u16* text) {
    s32 width = 0;
    for (;;) {
        u16 code = *text++;
        if (code & 0x4000) {
            switch (code & 0x3FFF) {
            case 0: goto done;
            case 2: width += 11; break;
            case 3: width += 22; break;
            }
        } else if (code & 0x8000) {
            width += 22;
        } else {
            width += 11;
        }
    }
done:
    return width;
}

// .text:0x000014F8 size:0x5C
s32 fn_2_14F8(s32 first, s32 second) {
    return first;
}

// .text:0x00001554 size:0x24
u32 fn_2_1554(void) {
    return lbl_803CB750 = lbl_803CB750 * 0x5D588B65 + 1;
}

// .text:0x00001578 size:0x288
void fn_2_1578(void) {
    return;
}

// .text:0x00001800 size:0x288
void fn_2_1800(void) {
    return;
}

// .text:0x00001A88 size:0x124
void fn_2_1A88(void) {
    s32 i;
    s32 count = 1;
    lbl_8034E9A0.controllerIndices[0] = 0;
    for (i = 1; i < 4; i++) {
        if (lbl_803C77B8.controllers[i].status != -1) {
            lbl_8034E9A0.controllerIndices[count++] = i;
        }
    }
    while (count < 4) lbl_8034E9A0.controllerIndices[count++] = -1;
}

// .text:0x00001BAC size:0x88
void fn_2_1BAC(void) {
    memset(lbl_803C66B0.resetData, 0, sizeof(lbl_803C66B0.resetData));
    lbl_803C66B0.unk56 = 0;
    lbl_803C66B0.unk55 = 0;
    memset(&lbl_803C5EA4, 0, sizeof(MenusSceneFlags));
    memset(lbl_8034E9A0.resetData, 0, sizeof(lbl_8034E9A0.resetData));
    memset(&lbl_8034E978, 0, sizeof(MenusSceneTransition));
}

// .text:0x00001C34 size:0xF4
void fn_2_1C34(u16 buttons) {
    switch (buttons) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        break;
    case 3: break;
    case 0x20: break;
    case 0x40: break;
    case 0x400: break;
    case 0x800: break;
    }
}

// .text:0x00001D28 size:0x2C
void fn_2_1D28(void) {
    lbl_8034E9A0.unk472A = 0xFF;
    lbl_8034E9A0.unk4756 = 0;
    lbl_8034E9A0.unk4754 = 0;
    lbl_8034E9A0.unk4755 = 3;
    lbl_8034E9A0.unk48B3 = 0;
}

// .text:0x00001D54 size:0x70
void fn_2_1D54(s32* value, u8 index, s32 count) {
    u16 buttons = lbl_8034E9A0.input[index].buttons;
    if (buttons & 8) {
        --*value;
        if (*value < 0) *value = count - 1;
    } else if (buttons & 4) {
        ++*value;
        if (*value == count) *value = 0;
    }
}

// .text:0x00001DC4 size:0x4
void fn_2_1DC4(void) {
    return;
}

// .text:0x00001DC8 size:0x168
void fn_2_1DC8(void) {
    return;
}

// .text:0x00001F30 size:0x8B0
void fn_2_1F30(void) {
    return;
}

// .text:0x000027E0 size:0x3D8
void fn_2_27E0(void) {
    return;
}

// .text:0x00002BB8 size:0x164
void fn_2_2BB8(void) {
    return;
}

// .text:0x00002D1C size:0x2A4
void fn_2_2D1C(void) {
    return;
}

/*
 * Locked-character pass of the roster rebuild (inlined into fn_2_2FC0 below).
 *
 * lbl_803CB748[6] holds the unique indices (0..31) of the six characters that need an unlock;
 * g_d_GameSettings.charUnlocked[i] (0x1A..0x1F) is the matching unlock flag.  Every charID whose
 * lbl_800E8558[charID].uniqueIdx (0x2 of each 6-byte characterStaticIndexes row) is a still-locked
 * unique gets its charsOnCharacterGridSelected flag (lbl_8034E9A0 + 0x4757) set, so the colour walk
 * treats it as taken; unlocked ones get it cleared (0 after the memset anyway).
 *
 * Must stay a separate static inline: inlining puts the helper's i/j/locked webs ahead of the
 * strength-reduced walkers (i=r7, j=r6, lk=r4, walkers r9..r12), and the compiler then promotes
 * the hoisted lbl_803CB748[i] load to r8 with a write-back store (stb r8,0(r12)) after the inner
 * loop.  Written inline in fn_2_2FC0 the same code colours the walkers first (r6..r9) and never
 * matches.  The inner loop runs 54 (all charIDs) and is unrolled 9x6 by the compiler.
 */
static inline void markLockedCharsTaken(void) {
    s32 i;
    s32 j;
    s32 locked;
    for (i = 0; i < 6; i++) {
        locked = !g_d_GameSettings.charUnlocked[i];
        for (j = 0; j < 54; j++) {
            if (lbl_803CB748[i] == lbl_800E8558[j].uniqueIdx) lbl_8034E9A0.charTaken[j] = locked;
        }
    }
}

/*
 * Character-select roster rebuild, driven by the menu mode (lbl_803297E0.mode, 0xCF5F).
 *
 *   mode 9  : fn_800684A4() first (DOL, still a stub; touches lbl_8034E9A0), then if `rebuild` the full rebuild below.
 *   mode 10 : full rebuild.
 *   mode 12 : only the tail (fn_800671FC, and fn_800649BC if `finish`).
 *   other   : nothing.
 *
 * Full rebuild (modes 9/10):
 *   1. clear the 54 per-charID taken flags charsOnCharacterGridSelected (lbl_8034E9A0 + 0x4757);
 *   2. mark both players' current picks (lbl_8034E9A0 + 0x46E0 / 0x46E4) as taken;
 *   3. mark every colour variant of a still-locked character as taken (markLockedCharsTaken);
 *   4. fn_80067F70(0/1): DOL auto-pick of a free colour per player (marks the pick and its whole
 *      lbl_80108EDC colour family taken);
 *   5. fn_2_8940, fn_800678CC(0/1), unsure_FillRosterPositions(0/1), characterSelectScreen(0/1),
 *      fn_80069854: rebuild the two rosters / select-screen state from the picks;
 *   6. if `rebuild`, fall into the mode-12 tail.
 *
 * Callers: fn_2_3204 -> fn_2_2FC0(lbl_803297E0.mode, 1, 1); gap_8E6A4.c -> fn_2_2FC0(9, 0, 1).
 */
// .text:0x00002FC0 size:0x244
void fn_2_2FC0(u8 mode, s32 finish, s32 rebuild) {
    switch (mode) {
    case 9:
        fn_800684A4();
        if (rebuild == 0) return;
        /* fallthrough */
    case 10:
        memset(lbl_8034E9A0.charTaken, 0, sizeof(lbl_8034E9A0.charTaken));
        lbl_8034E9A0.charTaken[lbl_8034E9A0.players[0]] = 1;
        lbl_8034E9A0.charTaken[lbl_8034E9A0.players[1]] = 1;
        markLockedCharsTaken();
        fn_80067F70(0);
        fn_80067F70(1);
        fn_2_8940();
        fn_800678CC(0);
        fn_800678CC(1);
        unsure_FillRosterPositions(0);
        unsure_FillRosterPositions(1);
        characterSelectScreen(0);
        characterSelectScreen(1);
        fn_80069854();
        if (rebuild == 0) return;
        /* fallthrough */
    case 12:
        fn_800671FC();
        if (finish != 0) fn_800649BC();
        break;
    }
}

// .text:0x00003204 size:0x38
void fn_2_3204(void) {
    fn_2_2FC0(lbl_803297E0.mode, 1, 1);
}

// .text:0x0000323C size:0x180
void fn_2_323C(void) {
    return;
}

// .text:0x000033BC size:0xD0
s32 fn_2_33BC(void) {
    MenusLineupView* view = (MenusLineupView*)&starMissionCompletionTracker;
    s32 result = 1;
    s32 i;
    for (i = 1; i < 9; i++) {
        if (view->lineup[0].value == view->lineup[i].value) result = 0;
    }
    return result;
}

/*
 * Standalone copy of markLockedCharsTaken (the locked-character pass of the roster rebuild).
 *
 * For each of the six unlockable unique indices lbl_803CB748[i] (0..31; sdata), every charID whose
 * lbl_800E8558[charID].uniqueIdx matches gets its charsOnCharacterGridSelected flag
 * (lbl_8034E9A0.charTaken, +0x4757) set to 1 while g_d_GameSettings.charUnlocked[i] (+0x1A..0x1F)
 * is still 0, and cleared once unlocked.  So a locked character and all its colour variants are
 * excluded from the colour walk exactly like an already-picked one.  No `bl` to it exists in
 * menus.rel; fn_2_2FC0 uses the inlined helper instead.
 *
 * Match notes: as a standalone function the plain nested loop colours uq r6, walkers r7..r10,
 * i r11, locked r12; `locked = (x == 0)` keeps locked in its own register (the `!x` form of the
 * inlined helper would coalesce it into the load temp).
 */
// .text:0x0000348C size:0x144
void fn_2_348C(void) {
    s32 i;
    s32 j;
    s32 locked;
    for (i = 0; i < 6; i++) {
        locked = (g_d_GameSettings.charUnlocked[i] == 0);
        for (j = 0; j < 54; j++) {
            if (lbl_803CB748[i] == lbl_800E8558[j].uniqueIdx) lbl_8034E9A0.charTaken[j] = locked;
        }
    }
}

// .text:0x000035D0 size:0x54
s32 fn_2_35D0(u8 index) {
    if (lbl_2_bss_F468.flags45[index]) {
        lbl_2_bss_F468.flags45[index] = 0;
        sndFXRelated(0x200);
        return 1;
    }
    return 0;
}

// .text:0x00003624 size:0x134C
void fn_2_3624(void) {
    return;
}

/*
 * Register the character sitting in roster slot `index` of `side` (lbl_803C6724.teams[side][index])
 * as taken on the select grid.  This is the body of fn_2_C698 and is inlined into fn_2_4970,
 * fn_2_7DDC, fn_2_C7DC and fn_2_CA60 (RELs build with -inline noauto, so it has to be an explicit
 * static inline).
 *
 *   1. lbl_8034E9A0.charTaken[id] = 1 (charsOnCharacterGridSelected, +0x4757);
 *   2. fn_800506E8(owner, id, 1): write `owner` into lbl_803C6028.slots[cell] for the grid cell
 *      (lbl_800FDE84) that holds id's base character, i.e. the "picked by Pn" badge on the cell.
 *      owner = lbl_8034E9A0.controllerIndices[side] (+0x46F8), except when g_d_GameSettings._10 == 0
 *      and side != 0 (two players on one side / second team driven by the other pad): the pad that
 *      is not player 0's;
 *   3. fn_80067B40(side, id, 1): set the taken flag of every colour variant in id's family
 *      (lbl_80108EDC row) so the next pick of that character steps to the next free colour.
 * GameModeSelected == 5 (challenge mode): only team 0 exists (lbl_803C6724.first) and the badge is
 * always controller 0.
 */
static inline void markSlotTaken(u8 index, u8 side) {
    s32 id;
    if (g_d_GameSettings.GameModeSelected != 5) {
        id = lbl_803C6724.teams[side][index];
        lbl_8034E9A0.charTaken[id] = 1;
        if (g_d_GameSettings._10 == 0 && side != 0) {
            if (lbl_8034E9A0.controllerIndices[0] == 0) fn_800506E8(1, id, 1);
            else fn_800506E8(0, id, 1);
        } else fn_800506E8(lbl_8034E9A0.controllerIndices[side], id, 1);
        fn_80067B40(side, (u8)id, 1);
    } else {
        id = lbl_803C6724.first[index];
        fn_800506E8(0, id, 1);
        lbl_8034E9A0.charTaken[id] = 1;
        fn_80067B40(side, (u8)id, 1);
    }
}

static inline void releaseSlot(u8 side, s32 slot) {
    u8 found = 0;
    s8 family = 0;
    s32 i;
    s32 j;
    if (g_d_GameSettings.GameModeSelected != 5) {
        fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
        fn_80067B40(side, lbl_803C6724.teams[side][slot], 0);
        lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
    } else if (fn_80067B40(side, lbl_803C6724.teams[side][slot], 2)) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 5; j++) {
                if (lbl_803C6724.teams[side][slot] == lbl_80108EDC[i][j]) {
                    family = i;
                    goto found_family;
                }
            }
        }
    found_family:
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 5; j++) {
                if (lbl_803C6724.teams[side][i] == lbl_80108EDC[family][j] && lbl_80108EDC[family][j] != -1 &&
                    lbl_803C6724.teams[side][i] != lbl_803C6724.teams[side][slot]) {
                    found = 1;
                }
            }
        }
        if (!found) {
            fn_800506E8(side, fn_80067AC8(lbl_803C6724.teams[side][slot], 0), 0);
            lbl_8034E9A0.charTaken[fn_80067AC8(lbl_803C6724.teams[side][slot], 0)] = 0;
        }
    } else {
        fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
        lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
    }
}

/*
 * Undo the latest pick of `side` on the roster screen (B button path of fn_2_CE44, which passes
 * lbl_8034E9A0.players[side] (+0x46E0) as captainID).
 *
 *   slot = the roster slot whose pick order lbl_803C6724.order[side][slot] (+0x14) equals the
 *          side's cursor lbl_2_bss_F468.cursor[side] (states[0..1]).
 *   If that slot holds the captain: just step the cursor back (wrap 0 -> 8); nothing is freed.
 *   Otherwise, if no pick is pending for the side (lbl_2_bss_F468.flags37/flags3D[side] both 0):
 *     remember the cursor in prevCursor[side] (+0x8), step it back, and if the slot holds a real
 *     character (not -1 / 0x36 = empty) release it; if a pick is pending: release the slot's
 *     character without moving the cursor and clear flags3D[side].
 *   Release = markSlotTaken() (re-register, so the family walk below starts from a consistent
 *   state) then:
 *     normal modes: fn_800506E8(side, id, 0) (clear the cell badge), fn_80067B40(side, id, 0)
 *       (clear the taken flag of the whole colour family), charTaken[id] = 0;
 *     challenge mode (GameModeSelected == 5): if id has a colour family (fn_80067B40(..., 2) is
 *       the query form) find its row in lbl_80108EDC and, unless another member of that family is
 *       still on the team, un-badge and un-take the family's base character (fn_80067AC8(id, 0));
 *       if it has no family un-badge/un-take id itself;
 *   then clear the slot: selectionFlags[side][slot] = 0, teams[side][slot] = -1,
 *   unk4A[side][slot] = 0.  Finally flags37[side] = 0 and fn_800625A4(side, 0x10) (DOL, stub:
 *   per-side UI command 0x10, "pick undone").
 *
 * Match notes: `state` (cursor) and `c` (slot character, s8) must be named locals in that order
 * (r7/r8); `found` is declared before `family` (r25/r24); the pending branch's `flags3D[side] = 0`
 * is written between the selectionFlags and teams stores: the scheduler hoists the stbx over it,
 * and any other placement changes the tail's register colouring.
 */
void fn_2_4970(u8 side, s32 captainID) {
    s32 slot;
    s32 k;
    u8 found = 0;
    s8 family = 0;
    s32 i;
    s32 j;
    s32 state = lbl_2_bss_F468.states[side];
    s8 c;

    for (k = 0; k < 9; k++) {
        if (lbl_803C6724.order[side][k] == state) slot = k;
    }
    c = lbl_803C6724.teams[side][slot];
    if (c == captainID) {
        lbl_2_bss_F468.states[side]--;
        if (lbl_2_bss_F468.states[side] < 0) lbl_2_bss_F468.states[side] = 8;
    } else {
        if (lbl_2_bss_F468.flags37[side] == 0 && lbl_2_bss_F468.flags3D[side] == 0) {
            lbl_2_bss_F468.prevCursor[side] = state;
            lbl_2_bss_F468.states[side]--;
            if (lbl_2_bss_F468.states[side] < 0) lbl_2_bss_F468.states[side] = 8;
            if (c != -1 && c != 0x36) {
                markSlotTaken(slot, side);
                if (g_d_GameSettings.GameModeSelected != 5) {
                    fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
                    fn_80067B40(side, lbl_803C6724.teams[side][slot], 0);
                    lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
                } else if (fn_80067B40(side, lbl_803C6724.teams[side][slot], 2)) {
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 5; j++) {
                            if (lbl_803C6724.teams[side][slot] == lbl_80108EDC[i][j]) {
                                family = i;
                                goto found_family;
                            }
                        }
                    }
                found_family:
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 5; j++) {
                            if (lbl_803C6724.teams[side][i] == lbl_80108EDC[family][j] && lbl_80108EDC[family][j] != -1 &&
                                lbl_803C6724.teams[side][i] != lbl_803C6724.teams[side][slot]) {
                                found = 1;
                            }
                        }
                    }
                    if (!found) {
                        fn_800506E8(side, fn_80067AC8(lbl_803C6724.teams[side][slot], 0), 0);
                        lbl_8034E9A0.charTaken[fn_80067AC8(lbl_803C6724.teams[side][slot], 0)] = 0;
                    }
                } else {
                    fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
                    lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
                }
                lbl_803C6724.selectionFlags[side][slot] = 0;
                lbl_803C6724.teams[side][slot] = -1;
                lbl_803C6724.unk4A[side][slot] = 0;
            }
        } else {
            markSlotTaken(slot, side);
            if (g_d_GameSettings.GameModeSelected != 5) {
                fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
                fn_80067B40(side, lbl_803C6724.teams[side][slot], 0);
                lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
            } else if (fn_80067B40(side, lbl_803C6724.teams[side][slot], 2)) {
                for (i = 0; i < 9; i++) {
                    for (j = 0; j < 5; j++) {
                        if (lbl_803C6724.teams[side][slot] == lbl_80108EDC[i][j]) {
                            family = i;
                            goto found_family2;
                        }
                    }
                }
            found_family2:
                for (i = 0; i < 9; i++) {
                    for (j = 0; j < 5; j++) {
                        if (lbl_803C6724.teams[side][i] == lbl_80108EDC[family][j] && lbl_80108EDC[family][j] != -1 &&
                            lbl_803C6724.teams[side][i] != lbl_803C6724.teams[side][slot]) {
                            found = 1;
                        }
                    }
                }
                if (!found) {
                    fn_800506E8(side, fn_80067AC8(lbl_803C6724.teams[side][slot], 0), 0);
                    lbl_8034E9A0.charTaken[fn_80067AC8(lbl_803C6724.teams[side][slot], 0)] = 0;
                }
            } else {
                fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
                lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
            }
            lbl_803C6724.selectionFlags[side][slot] = 0;
            lbl_2_bss_F468.flags3D[side] = 0;
            lbl_803C6724.teams[side][slot] = -1;
            lbl_803C6724.unk4A[side][slot] = 0;
        }
        lbl_2_bss_F468.flags37[side] = 0;
    }
    fn_800625A4(side, 0x10);
}

// .text:0x00005184 size:0x148
void fn_2_5184(void) {
    return;
}

// .text:0x000052CC size:0x178
void fn_2_52CC(void) {
    return;
}

// .text:0x00005444 size:0x3A4
void fn_2_5444(void) {
    return;
}

// .text:0x000057E8 size:0x8
s32 fn_2_57E8(s32 arg0, s32 arg1) {
    return (s8)arg1;
}

// .text:0x000057F0 size:0x790
void fn_2_57F0(void) {
    return;
}

// .text:0x00005F80 size:0x118
void fn_2_5F80(void) {
    s32 team;
    s32 i;
    s32 j;
    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                if (lbl_80354720[team][i].unk2 == lbl_80354720[team][j].unk2) {
                    lbl_803C6724.teams[team][i] = inMemRoster[team][j].stats.CharID;
                }
            }
            lbl_803C6724.order[team][i] = i;
        }
    }
}

// .text:0x00006098 size:0x3C
void fn_2_6098(u8 index) {
    lbl_2_bss_F468.states[index] = 9;
    fn_800625A4(index, 0x17);
}

// .text:0x000060D4 size:0x64
s32 fn_2_60D4(u8 index) {
    if (g_d_GameSettings.GameModeSelected != 5) return lbl_8034E9A0.players[index];
    if (index != 0) return lbl_8034E9A0.players[index];
    return lbl_8034E9A0.players[index];
}

// .text:0x00006138 size:0x68
void fn_2_6138(void) {
    fn_800625A4(0, 0x13);
    fn_800625A4(1, 0x13);
    lbl_2_bss_F468.unk4F = 0;
    lbl_2_bss_F468.unk2E = 0;
    lbl_2_bss_100B4 = 1;
    lbl_803CBBCC->state = 8;
}

// .text:0x000061A0 size:0x2E4
void fn_2_61A0(void) {
    return;
}

// .text:0x00006484 size:0x184
void fn_2_6484(void) {
    return;
}

// .text:0x00006608 size:0x17C
void fn_2_6608(void) {
    return;
}

// .text:0x00006784 size:0x100
void fn_2_6784(void) {
    return;
}

// .text:0x00006884 size:0x270
void fn_2_6884(void) {
    return;
}

// .text:0x00006AF4 size:0x248
void fn_2_6AF4(void) {
    return;
}

// .text:0x00006D3C size:0x7C8
void fn_2_6D3C(void) {
    return;
}

// .text:0x00007504 size:0x840
void fn_2_7504(void) {
    return;
}

// .text:0x00007D44 size:0x98
void fn_2_7D44(void) {
    if (lbl_803CBBCC->previousSelection == 9) {
        memset(&lbl_2_bss_100B8, 0, sizeof(Rep0568State));
    }
    lbl_8034E9A0.unk4755 = 1;
    lbl_2_bss_100B8.count = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// .text:0x00007DDC size:0x910
void fn_2_7DDC(void) {
    return;
}

// .text:0x000086EC size:0x94
void fn_2_86EC(void) {
    return;
}

// .text:0x00008780 size:0x14
s32 fn_2_8780(s32 mode) {
    s32 result = 9;
    if (mode != 0) result = 19;
    return result;
}

// .text:0x00008794 size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// .text:0x000087A8 size:0x194
void fn_2_87A8(void) {
    return;
}

// .text:0x0000893C size:0x4
void fn_2_893C(void) {
    return;
}

// .text:0x00008940 size:0x3B8
void fn_2_8940(void) {
    return;
}

// .text:0x00008CF8 size:0x8E0
void fn_2_8CF8(void) {
    return;
}

// .text:0x000095D8 size:0x4F4
void fn_2_95D8(void) {
    return;
}

// .text:0x00009ACC size:0x4A4
void fn_2_9ACC(void) {
    return;
}

// .text:0x00009F70 size:0xD0
s32 fn_2_9F70(s8 side) {
    s32 result;
    s8 other = lbl_2_bss_F468.teamIndices[(s8)side ^ 1];
    s32 own = lbl_2_bss_F468.teamIndices[(s8)side];
    s32 i, j;
    switch (lbl_2_bss_F468.options[own]) {
    case 1: result = 2; break;
    case 2: result = 1; break;
    case 3: result = 1; break;
    }
restart:
    for (i = 0; i < 9; i++) {
        u8 character = inMemRoster[other][i].stats.CharID;
        for (j = 0; j < 9; j++) {
            if (character == 0) {
                if (result == 1 || result == 2) return 3;
                result = 2;
                goto restart;
            }
        }
    }
    return result;
}

// .text:0x0000A040 size:0x160
void fn_2_A040(s32 group, s32 choice, u8 team, u8 slot) {
    s32 i,j;
    if(lbl_80108EDC[group][choice]!=-1 && choice<4) {
        choice++;
        if(choice==5 || lbl_80108EDC[group][choice]==-1) choice=0;
        for(i=0;i<2;i++) {
            for(j=0;j<9;j++) {
                if(lbl_803C6724.teams[i][j]==lbl_80108EDC[group][choice]) return;
            }
        }
        lbl_803C6724.teams[team][slot]=lbl_80108EDC[group][choice];
    } else lbl_803C6724.teams[team][slot]=lbl_80108EDC[group][0];
}

// .text:0x0000A1A0 size:0xE8
void fn_2_A1A0(void) {
    return;
}

// .text:0x0000A288 size:0x284
void fn_2_A288(void) {
    return;
}

// .text:0x0000A50C size:0x120
BOOL fn_2_A50C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        s32 value = lbl_803C6724.first[i];
        for (j = 0; j < 9; j++) {
            if (value == lbl_803C6724.second[j]) return TRUE;
        }
    }
    return FALSE;
}

// .text:0x0000A62C size:0xB4
BOOL fn_2_A62C(void) {
    s32 i, j;
    for (i = 0; i < 9; i++) {
        s32 value = lbl_803C6724.first[i];
        for (j = 0; j < 9; j++) {
            if (value == lbl_803C6724.second[j] && value != 255) return 1;
        }
    }
    return 0;
}

// .text:0x0000A6E0 size:0x4E0
void fn_2_A6E0(void) {
    return;
}

// .text:0x0000ABC0 size:0x328
void fn_2_ABC0(void) {
    return;
}

// .text:0x0000AEE8 size:0x43C
void fn_2_AEE8(void) {
    return;
}

// .text:0x0000B324 size:0x1E4
void fn_2_B324(void) {
    return;
}

// .text:0x0000B508 size:0x164
void fn_2_B508(void) {
    return;
}

// .text:0x0000B66C size:0x2B4
void fn_2_B66C(void) {
    return;
}

// .text:0x0000B920 size:0x670
void fn_2_B920(void) {
    return;
}

// .text:0x0000BF90 size:0x394
void fn_2_BF90(void) {
    return;
}

// .text:0x0000C324 size:0x160
s8 fn_2_C324(s32 character) {
    s32 found=-1;
    s32 i,j;
    for(i=0;i<9;i++) {
        for(j=0;j<5;j++) {
            if(character==lbl_80108EDC[i][j]) {found=i;goto done;}
        }
    }
done:
    if(found==-1) return found;
    for(i=0;i<9;i++) {
        s32 current=inMemRoster[0][i].stats.CharID;
        for(j=0;j<5;j++) {
            if(current==lbl_80108EDC[found][j] && current!=character) return found;
        }
    }
    return -1;
}

// .text:0x0000C484 size:0x214
void fn_2_C484(void) {
    return;
}

// .text:0x0000C698 size:0x144
/* Standalone markSlotTaken (see above fn_2_4970). */
void fn_2_C698(u8 index, u8 side) {
    markSlotTaken(index, side);
}

// .text:0x0000C7DC size:0x284
void fn_2_C7DC(void) {
    return;
}

// .text:0x0000CA60 size:0x25C
void fn_2_CA60(void) {
    return;
}

// .text:0x0000CCBC size:0x24
void fn_2_CCBC(void) {
    fn_2_7DDC();
    fn_2_7504();
}

// .text:0x0000CCE0 size:0x164
void fn_2_CCE0(void) {
    return;
}

// .text:0x0000CE44 size:0x1168
void fn_2_CE44(void) {
    return;
}

// .text:0x0000DFAC size:0xB34
void fn_2_DFAC(void) {
    return;
}

// .text:0x0000EAE0 size:0x154
void fn_2_EAE0(void) {
    return;
}

// .text:0x0000EC34 size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468.unk56 == 0) lbl_2_bss_F468.unk56 = 1;
}

// .text:0x0000EC54 size:0x140
void fn_2_EC54(s32 side) {
    s32 i;
    s32 j;
    if (g_d_GameSettings.GameModeSelected != 5) {
        if (g_d_GameSettings._10 == 1) {
            lbl_2_bss_100B8.selectionFlags[1] = 0;
            lbl_2_bss_100B8.selectionFlags[0] = 0;
        } else lbl_2_bss_100B8.selectionFlags[side] = 0;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) lbl_803C6724.selectionFlags[i][j] = 0;
            if (lbl_2_bss_F468.flags45[i] != 0) lbl_2_bss_F468.flags45[i] = 0;
        }
        if (lbl_2_bss_F468.unk56 == 0) lbl_2_bss_F468.unk56 = 1;
        lbl_2_bss_F468.unk2E = 1;
        lbl_2_bss_100B4 = 1;
        lbl_803CBBCC->state = 8;
    }
}

// .text:0x0000ED94 size:0x46C
void fn_2_ED94(void) {
    return;
}

// .text:0x0000F200 size:0x8A0
void fn_2_F200(void) {
    return;
}

// .text:0x0000FAA0 size:0x214
void fn_2_FAA0(void) {
    return;
}

// .text:0x0000FCB4 size:0x614
void fn_2_FCB4(void) {
    return;
}

// .text:0x000102C8 size:0x234
void fn_2_102C8(void) {
    return;
}

// .text:0x000104FC size:0xBB4
void fn_2_104FC(void) {
    return;
}

// .text:0x000110B0 size:0x244
void fn_2_110B0(void) {
    return;
}

// .text:0x000112F4 size:0x4C
BOOL fn_2_112F4(DrawingSceneStruct* scene, s32 offset, s32 index, u16* ids, u16 value) {
    Struct_80371C30_Inner* obj = lbl_80371C30[scene->unkIndex + offset].obj;
    if ((s32)(obj->field_0x5C >> 16) == ids[index + 1] - 1) {
        obj->unk64 = value;
        return TRUE;
    }
    return FALSE;
}

// .text:0x00011340 size:0x358
void fn_2_11340(void) {
    return;
}

// .text:0x00011698 size:0x810
void fn_2_11698(void) {
    return;
}

// .text:0x00011EA8 size:0x228
void fn_2_11EA8(void) {
    return;
}

// .text:0x000120D0 size:0x9C
void fn_2_120D0(void) {
    lbl_8034E9A0.unk48AD = 1;
    lbl_8034E9A0.unk4755 = 3;
    lbl_803C66B0.unk0 = 0;
    lbl_803C66B0.unk5A = 0;
    lbl_803C66B0.unk59 = 0;
    lbl_8034E9A0.unk472A = 0xFF;
    lbl_8034E9A0.unk48AF = 1;
    lbl_8034E9A0.unk48B1 = 1;
    memset(lbl_803C66B0.resetData, 0, 6);
    lbl_8034E978.unk26 = 1;
    fn_800AD038(lbl_8034E9A0.timeHigh);
    g_d_GameSettings._10 = 0;
}

// .text:0x0001216C size:0xCC
void fn_2_1216C(void) {
    s8 modes[4];
    memset(modes, 2, sizeof(modes));
    if (g_d_GameSettings._10 == 0) {
        modes[lbl_8034E9A0.controllerIndices[0]] = 1;
        if (lbl_8034E9A0.controllerIndices[0] == 0) modes[1] = 2;
        else modes[0] = 2;
    } else {
        modes[lbl_8034E9A0.controllerIndices[1]] = 1;
        modes[lbl_8034E9A0.controllerIndices[0]] = 1;
    }
    fn_8004EEF4(modes[0], modes[1], modes[2], modes[3], 1);
}
