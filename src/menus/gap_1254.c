#include "menus/gap_1254.h"
#include "string.h"
#include "musyx/musyx.h"
#include "game/gap_B3B70.h"
#include "game/rep_3448.h"
#include "menus/gap_0.h"
#include "menus/gap_D08.h"
#include "menus/gap_16870.h"
#include "menus/gap_71EC4.h"
#include "menus/gap_8782C.h"
#include "menus/rep_0438.h"
#include "menus/rep_0568.h"

/* DOL functions and data owned by Unknown/gap_8*.h.  Those headers can't be included here yet: each
 * declares its own struct view of shared globals (lbl_803297E0, lbl_80361B20, ...), which clash.
 * Keep these prototypes identical to the owning header until the views are merged. */
extern s16 lbl_80108EDC[][5];                                    /* gap_80067AC8.h */
extern s16 fn_80067AC8(s16 key, s8 column);                      /* gap_80067AC8.h */
extern u8 fn_80067B40(u8 side, u8 id, s32 enabled);              /* header says (s32, s16, u8); its body is unmatched, settle the types when it matches */
extern s32 randRange(s32 low, s32 high);                         /* gap_80041348.h */
extern void sndFXRelated(s32 id);                                /* gap_80041348.h */
extern void fn_8004EEF4(s32 a, s32 b, s32 c, s32 d, s32 enabled); /* gap_8004CA48.h */
extern void fn_80050138(s32 arg0, s32 pick0, s32 pick1, s32 pick2, s32 pick3, s32 arg5); /* gap_8004CA48.h */
extern void fn_800506E8(s32 controller, s32 id, s32 enabled);    /* gap_800506E8.h */
extern void fn_80050FE8(u8 pad0, u8 pad1, u8 pad2, u8 pad3, s32 arg4, s32 arg5); /* gap_800506E8.h */
extern void fn_800625A4(s32 index, s32 command);                 /* gap_80062578.h */
extern u32 fn_800628D4(s32 charID);                              /* gap_80062578.h */
extern void fn_80066EAC(s32 side);                               /* gap_80064754.h */
extern void fn_800AD038(s32 start);                               /* gap_800A97D0.h */

extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_3A8[54]; /* per-charID handedness byte (challenge save): bit 0 stance, bits 1.. arm */
extern u32 lbl_803CB750;

// .text:0x00001254 size:0x4
void fn_2_1254(void) {
    return;
}

// .text:0x00001258 size:0x48
void fn_2_1258(void) {
    return;
}

// .text:0x000012A0 size:0x2C
void satAddS16(s16* value, s16 amount) {
    if (*value < 0x7FFF - amount) *value += amount;
    else *value = 0x7FFF;
}

// .text:0x000012CC size:0x2C
void satAddU8(u8* value, u16 amount) {
    if (*value + amount > 0xFF) *value = 0xFF;
    else *value += amount;
}

// .text:0x000012F8 size:0x30
void satAddU16(u16* value, u16 amount) {
    if (*value + amount > 0xFFFF) *value = 0xFFFF;
    else *value += amount;
}

// .text:0x00001328 size:0x2C
void satAddS32(u32* value, u16 amount) {
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

/* Button-to-SFX dispatch only: exact button values A=confirm, B=alert,
 * directions=move. This switch does not inspect a character or bind UI art. */
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
    s32 result = 1;
    s32 i;
    for (i = 1; i < 9; i++) {
        if (starMissionCompletionTracker.lineup[0].order == starMissionCompletionTracker.lineup[i].order) result = 0;
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

/* Put charID `id` into roster slot `slot` of `side` (lbl_803C6724.teams). */
static inline void setTeamSlot(u8 side, u8 slot, s32 id) {
    lbl_803C6724.teams[side][slot] = id;
}

/* Close the side's roster popup if one is open (flags45[side]); returns 1 when it did (the button
   press is then consumed).  Body of fn_2_35D0, inlined into fn_2_3624. */
static inline s32 closePopup(u8 index) {
    if (lbl_2_bss_F468.flags45[index]) {
        lbl_2_bss_F468.flags45[index] = 0;
        sndFXRelated(0x200);
        return 1;
    }
    return 0;
}

// .text:0x000035D0 size:0x54
s32 fn_2_35D0(u8 index) {
    return closePopup(index);
}

/*
 * Handle one controller's input while editing the character-select roster. `pad` is the
 * controller-input index; lbl_803C66B0.padSide maps it to a team. A pending flags5D UI command
 * blocks input. Directions follow the roster's 0..8 layout, with 9 = ready and 10 = clear team;
 * a popup uses left/right to choose its column instead of moving the roster cursor.
 *
 * A confirms ready or picks up/swaps batting-order positions; B cancels a move; R closes a
 * popup/cancels editing; L cycles a roster character's colour family; Z opens the slot popup.
 * lbl_2_bss_F468 holds cursors, popup/move state and ready flags. lbl_803C6724 holds charIDs and
 * order[side][slot], which maps physical slots to cursor positions. Colour cycling searches
 * lbl_80108EDC's 9 x 5 family table, rejects a colour already present on either team, writes the
 * new charID and calls markSlotTaken to update charTaken, grid badges and family taken flags.
 *
 * Ready uses lbl_2_bss_100B8.selectionFlags and lbl_803CBBCC->state to advance the scene. In
 * one-pad play it transfers input to team 1 and places that team's grid cursor via fn_80050138
 * (lbl_2_bss_F410.gridPick, lbl_800FDE84 and controllerIndices). Challenge ready copies team 0
 * into inMemRoster, starMissionCompletionTracker.lineup and lbl_80354720 before leaving.
 * Cursor changes request command0xE: menus fn_2_81628 -> fn_2_7DAB8 -> fn_2_74F40
 * refreshes the charID-keyed name/stats. fn_2_776A0 also refreshes hover changes and consumes
 * the L-colour unk50 flag to update the charID-keyed mini image (common sequence0x83).
 * This input handler does not load portrait/name textures. Sound IDs 0x1B7..0x1BF use lbl_800EFBA4's menu volumes.
 *
 * Match-sensitive details: side is s32 and declared last; slot follows the swap temporaries.
 * The challenge copies chain their two destinations to preserve the original load/store order.
 */
// .text:0x00003624 size:0x134C
void fn_2_3624(u8 pad) {
    MenusPlayerInput in;
    u8 handled;
    s32 k;
    s32 i;
    s32 j;
    s32 next;
    s32 t;
    s32 cell;
    s32 b;
    s32 vb;
    s32 a;
    s32 va;
    s8 slot;
    s8 c;
    s8 state;
    s32 n;
    s32 side;
    side = lbl_803C66B0.padSide[pad];
    memset(&in, 0, sizeof(in));
    if (lbl_803C66B0.flags5D[side] != 0) return;
    in.unk0 = lbl_8034E9A0.input[pad].unk0;
    in.unk2 = lbl_8034E9A0.input[pad].unk2;
    in.buttons = lbl_8034E9A0.input[pad].buttons;

    if (in.buttons & 8) {
        if (lbl_2_bss_F468.flags45[side] != 0) return;
        if (lbl_2_bss_F468.cursor[side] == 9) {
            lbl_2_bss_F468.cursor[side] = 2;
            fn_800625A4(side, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        if (lbl_2_bss_F468.cursor[side] == 10) {
            if (lbl_2_bss_F468.flags37[side] != 0) {
                lbl_2_bss_F468.cursor[side] = 9;
                fn_800625A4(side, 0x18);
            } else {
                lbl_2_bss_F468.cursor[side] = 2;
                fn_800625A4(side, 0xE);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        lbl_2_bss_F468.prevCursor[side] = lbl_2_bss_F468.cursor[side];
        switch (lbl_2_bss_F468.cursor[side]) {
        case 0: lbl_2_bss_F468.cursor[side] = 5; break;
        case 1: lbl_2_bss_F468.cursor[side] = 0; break;
        case 2: lbl_2_bss_F468.cursor[side] = 8; break;
        case 3: lbl_2_bss_F468.cursor[side] = 7; break;
        case 4: lbl_2_bss_F468.cursor[side] = 6; break;
        case 5: lbl_2_bss_F468.cursor[side] = 7; break;
        case 6: lbl_2_bss_F468.cursor[side] = 4; break;
        case 8:
            if (lbl_2_bss_F468.flags37[side] != 0 && lbl_2_bss_F468.unk5F[side] == 0) lbl_2_bss_F468.cursor[side] = 9;
            else lbl_2_bss_F468.cursor[side] = 2;
            break;
        case 7: lbl_2_bss_F468.cursor[side] = 1; break;
        }
        if (lbl_2_bss_F468.prevCursor[side] != lbl_2_bss_F468.cursor[side]) fn_800625A4(side, 0xE);
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        return;
    }
    if (in.buttons & 4) {
        if (lbl_2_bss_F468.flags45[side] != 0) return;
        if (lbl_2_bss_F468.cursor[side] == 9) {
            lbl_2_bss_F468.cursor[side] = 8;
            fn_800625A4(side, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        lbl_2_bss_F468.prevCursor[side] = lbl_2_bss_F468.cursor[side];
        switch (lbl_2_bss_F468.cursor[side]) {
        case 0: lbl_2_bss_F468.cursor[side] = 1; break;
        case 2:
            if (lbl_2_bss_F468.flags37[side] != 0 && lbl_2_bss_F468.unk5F[side] == 0) lbl_2_bss_F468.cursor[side] = 9;
            else lbl_2_bss_F468.cursor[side] = 8;
            break;
        case 4: lbl_2_bss_F468.cursor[side] = 6; break;
        case 3: lbl_2_bss_F468.cursor[side] = 0; break;
        case 5: lbl_2_bss_F468.cursor[side] = 0; break;
        case 6: lbl_2_bss_F468.cursor[side] = 5; break;
        case 7: lbl_2_bss_F468.cursor[side] = 4; break;
        case 8: lbl_2_bss_F468.cursor[side] = 2; break;
        case 1: lbl_2_bss_F468.cursor[side] = 7; break;
        }
        if (lbl_2_bss_F468.prevCursor[side] != lbl_2_bss_F468.cursor[side]) fn_800625A4(side, 0xE);
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        return;
    }
    if (in.buttons & 1) {
        if (lbl_2_bss_F468.flags45[side] != 0) {
            if (lbl_2_bss_F468.unk47[side] != 1) return;
            lbl_2_bss_F468.unk47[side] = 0;
            lbl_2_bss_F468.unk49[side] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        if (lbl_2_bss_F468.cursor[side] == 9) {
            lbl_2_bss_F468.cursor[side] = 0;
            fn_800625A4(side, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        lbl_2_bss_F468.prevCursor[side] = lbl_2_bss_F468.cursor[side];
        switch (lbl_2_bss_F468.cursor[side]) {
        case 0: lbl_2_bss_F468.cursor[side] = 4; break;
        case 1:
            if (lbl_2_bss_F468.flags37[side] == 0) return;
            if (lbl_2_bss_F468.unk5F[side] != 0) return;
            lbl_2_bss_F468.cursor[side] = 9;
            break;
        case 2: lbl_2_bss_F468.cursor[side] = 3; break;
        case 3: lbl_2_bss_F468.cursor[side] = 5; break;
        case 7: lbl_2_bss_F468.cursor[side] = 6; break;
        case 8: lbl_2_bss_F468.cursor[side] = 7; break;
        case 4: lbl_2_bss_F468.cursor[side] = 2; break;
        case 10: lbl_2_bss_F468.cursor[side] = 1; break;
        case 5: lbl_2_bss_F468.cursor[side] = 4; break;
        case 6: lbl_2_bss_F468.cursor[side] = 8; break;
        }
        if (lbl_2_bss_F468.prevCursor[side] != lbl_2_bss_F468.cursor[side]) fn_800625A4(side, 0xE);
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        return;
    }
    if (in.buttons & 2) {
        if (lbl_2_bss_F468.flags45[side] != 0) {
            if (lbl_2_bss_F468.unk47[side] != 0) return;
            lbl_2_bss_F468.unk47[side] = 1;
            lbl_2_bss_F468.unk49[side] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        if (lbl_2_bss_F468.cursor[side] == 9) {
            lbl_2_bss_F468.cursor[side] = 0;
            fn_800625A4(side, 0xE);
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
            return;
        }
        lbl_2_bss_F468.prevCursor[side] = lbl_2_bss_F468.cursor[side];
        switch (lbl_2_bss_F468.cursor[side]) {
        case 0:
            if (lbl_2_bss_F468.flags37[side] != 0 && lbl_2_bss_F468.unk5F[side] == 0) {
                lbl_2_bss_F468.cursor[side] = 9;
                fn_800625A4(side, 0x18);
            } else {
                lbl_2_bss_F468.cursor[side] = 2;
                fn_800625A4(side, 0xE);
            }
            break;
        case 1:
            if (lbl_2_bss_F468.flags37[side] == 0) return;
            if (lbl_2_bss_F468.unk5F[side] != 0) return;
            lbl_2_bss_F468.cursor[side] = 9;
            break;
        case 4: lbl_2_bss_F468.cursor[side] = 5; break;
        case 5: lbl_2_bss_F468.cursor[side] = 3; break;
        case 6: lbl_2_bss_F468.cursor[side] = 7; break;
        case 7: lbl_2_bss_F468.cursor[side] = 8; break;
        case 2: lbl_2_bss_F468.cursor[side] = 4; break;
        case 8: lbl_2_bss_F468.cursor[side] = 6; break;
        case 3: lbl_2_bss_F468.cursor[side] = 2; break;
        }
        if (lbl_2_bss_F468.prevCursor[side] != lbl_2_bss_F468.cursor[side]) fn_800625A4(side, 0xE);
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        return;
    }
    if (in.unk2 & 0x100) {
        handled = closePopup(side);
        if (handled) return;
        if (lbl_2_bss_F468.cursor[side] == 9) {
            lbl_2_bss_F468.flags59[side] = cell = 0;
            lbl_2_bss_F468.unk61[side] = -1;
            lbl_2_bss_F468.unk65[side] = 1;
            if (g_d_GameSettings.GameModeSelected == 5) {
                for (n = 0; n < 9; n++) {
                    starMissionCompletionTracker.lineup[n].charID =
                        inMemRoster[0][n].stats.CharID = lbl_803C6724.teams[0][n];
                    starMissionCompletionTracker.lineup[n].slot = n;
                    starMissionCompletionTracker.lineup[n].order =
                        lbl_80354720[0][n].unk2 = lbl_803C6724.order[0][n];
                }
                lbl_2_bss_F468.unk2E = 0;
                lbl_2_bss_100B4 = 1;
                lbl_803CBBCC->state = 8;
            } else if (g_d_GameSettings._10 == 0) {
                if (side != 0) {
                    lbl_2_bss_F468.unk36 = 0x1E;
                    lbl_803CBBCC->state = 3;
                } else {
                    lbl_2_bss_100B8.selectionFlags[0] = 1;
                    lbl_803C66B0.padSide[0] = 1;
                    lbl_2_bss_F468.cursor[lbl_803C66B0.padSide[0]] = 10;
                    lbl_803C5EA4.unkE = 1;
                    if (lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[1]] != 0) {
                        for (; cell < 32; cell++) {
                            if (lbl_8034E9A0.charTaken[lbl_800FDE84[cell]] == 0) {
                                lbl_2_bss_F410.gridPick[1] = lbl_800FDE84[cell];
                                break;
                            }
                        }
                    }
                    switch (lbl_8034E9A0.controllerIndices[1]) {
                    case 0: fn_80050138(1, lbl_2_bss_F410.gridPick[1], -1, -1, -1, 0); break;
                    case 1: fn_80050138(1, -1, lbl_2_bss_F410.gridPick[1], -1, -1, 0); break;
                    case 2: fn_80050138(1, -1, -1, lbl_2_bss_F410.gridPick[1], -1, 0); break;
                    case 3: fn_80050138(1, -1, -1, -1, lbl_2_bss_F410.gridPick[1], 0); break;
                    }
                }
            } else {
                lbl_2_bss_100B8.selectionFlags[side] = 1;
                if (lbl_2_bss_100B8.selectionFlags[0] != 0 && lbl_2_bss_100B8.selectionFlags[1] != 0) {
                    lbl_2_bss_F468.unk4F = 1;
                    lbl_2_bss_F468.unk36 = 0x1E;
                    lbl_803CBBCC->state = 7;
                }
            }
            fn_800625A4(side, 0x1B);
        } else {
            if (lbl_2_bss_F468.unk5F[side] == 0) {
                lbl_2_bss_F468.unk61[side] = lbl_2_bss_F468.cursor[side];
                fn_800625A4(side, 0x1C);
            } else {
                for (k = 0; k < 9; k++) {
                    if (lbl_803C6724.order[side][k] == lbl_2_bss_F468.unk61[side]) {
                        a = k;
                        va = lbl_2_bss_F468.unk61[side];
                    }
                    if (lbl_803C6724.order[side][k] == lbl_2_bss_F468.cursor[side]) {
                        b = k;
                        vb = lbl_2_bss_F468.cursor[side];
                    }
                }
                lbl_803C6724.order[side][a] = vb;
                lbl_803C6724.order[side][b] = va;
                fn_800625A4(side, 0x1C);
            }
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        return;
    }
    if (in.unk2 & 0x200) {
        handled = closePopup(side);
        if (handled) return;
        if (lbl_2_bss_F468.unk5F[side] != 0) fn_800625A4(side, 0x1D);
        sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
        return;
    }
    if (in.unk2 & 0x20) {
        handled = closePopup(side);
        if (handled) return;
        if (lbl_2_bss_F468.unk5F[side] != 0) lbl_2_bss_F468.unk5F[side] = 0;
        fn_800625A4(side, 0x1B);
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        lbl_2_bss_F468.flags59[side] = 0;
        return;
    }
    if (in.unk2 & 0x40) {
        handled = closePopup(side);
        if (handled) return;
        if (g_d_GameSettings.GameModeSelected == 5) return;
        state = lbl_2_bss_F468.cursor[side];
        for (k = 0; k < 9; k++) {
            if (lbl_803C6724.order[side][k] == state) {
                slot = k;
                break;
            }
        }
        c = lbl_803C6724.teams[side][slot];
        if (c == CHAR_ID_NONE || c == NUM_CHOOSABLE_CHARACTERS) {
            sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
            return;
        }
        if (lbl_2_bss_F468.cursor[side] != 9) {
            lbl_2_bss_F468.unk50[side] = i = 0;
            for (; i < 9; i++) {
                for (j = 0; j < 5; j++) {
                    if (c == lbl_80108EDC[i][j]) {
                        lbl_2_bss_F468.unk50[side] = 1;
                        goto found;
                    }
                }
            }
        found:
            if (lbl_2_bss_F468.unk50[side] == 0) return;
            if (lbl_80108EDC[i][j] != -1 && j < 4) {
                next = j + 1;
                if (next == 5 || lbl_80108EDC[i][next] == -1) next = 0;
                for (t = 0; t < 2; t++) {
                    for (k = 0; k < 9; k++) {
                        if (lbl_803C6724.teams[t][k] == lbl_80108EDC[i][next]) goto cycled;
                    }
                }
                setTeamSlot(side, slot, lbl_80108EDC[i][next]);
            } else {
                setTeamSlot(side, slot, lbl_80108EDC[i][0]);
            }
        cycled:
            markSlotTaken(slot, side);
            sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
        } else {
            sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
        }
        return;
    }
    if (in.unk2 & 0x10) {
        handled = closePopup(side);
        if (handled) return;
        for (k = 0; k < 9; k++) {
            if (lbl_803C6724.order[side][k] == lbl_2_bss_F468.cursor[side]) {
                slot = k;
                break;
            }
        }
        if (lbl_2_bss_F468.cursor[side] == 9) return;
        c = lbl_803C6724.teams[side][slot];
        if (c != CHAR_ID_NONE && c != NUM_CHOOSABLE_CHARACTERS) {
            if (lbl_2_bss_F468.flags41[side] == 0) {
                lbl_2_bss_F468.flags45[side] = 1;
                lbl_2_bss_F468.unk4B[side] = 1;
                lbl_2_bss_F468.unk47[side] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4.unk8, 0x3F, 0);
            }
        }
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
            if (c != CHAR_ID_NONE && c != NUM_CHOOSABLE_CHARACTERS) {
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
/* Ready action: persist the challenge lineup, or hand the shared pad over to
 * side 1, or wait for both independent sides. UI commands 0x11/0x13 animate
 * completion; pictures continue to be selected by the scene callbacks. */
void fn_2_5444(u8 side) {
    s32 n;
    s32 cell;
    lbl_2_bss_F468.flags3D[side] = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (n = 0; n < 9; n++) {
            starMissionCompletionTracker.lineup[n].charID = lbl_803C6724.teams[0][n];
            starMissionCompletionTracker.lineup[n].slot = n;
            starMissionCompletionTracker.lineup[n].order = lbl_803C6724.order[0][n];
            inMemRoster[0][n].stats.CharID = lbl_803C6724.teams[0][n];
            lbl_80354720[0][n].unk2 = lbl_803C6724.order[0][n];
        }
        fn_800625A4(0, 0x13);
        fn_800625A4(1, 0x13);
        lbl_2_bss_F468.unk2E = 0;
        lbl_2_bss_100B4 = 1;
        lbl_803CBBCC->state = 8;
        return;
    }
    if (g_d_GameSettings._10 == 0 && lbl_2_bss_100B8.selectionFlags[0] != 0) {
        fn_800625A4(1, 0x11);
        lbl_8034E9A0.unk472A = 0xFF;
        lbl_2_bss_F468.unk36 = 0x1E;
        lbl_803CBBCC->state = 3;
        return;
    }
    if (g_d_GameSettings._10 == 0) {
        lbl_2_bss_100B8.selectionFlags[0] = 1;
        lbl_803C66B0.padSide[0] = 1;
        lbl_2_bss_F468.cursor[lbl_803C66B0.padSide[0]] = 10;
        lbl_803C5EA4.unkE = 1;
        if (lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[1]] != 0) {
            for (cell = 0; cell < 32; cell++) {
                if (lbl_8034E9A0.charTaken[lbl_800FDE84[cell]] == 0) {
                    lbl_2_bss_F410.gridPick[1] = lbl_800FDE84[cell];
                    break;
                }
            }
        }
        switch (lbl_8034E9A0.controllerIndices[1]) {
        case 0: fn_80050138(1, lbl_2_bss_F410.gridPick[1], -1, -1, -1, 0); break;
        case 1: fn_80050138(1, -1, lbl_2_bss_F410.gridPick[1], -1, -1, 0); break;
        case 2: fn_80050138(1, -1, -1, lbl_2_bss_F410.gridPick[1], -1, 0); break;
        case 3: fn_80050138(1, -1, -1, -1, lbl_2_bss_F410.gridPick[1], 0); break;
        }
        fn_800625A4(0, 0x11);
    } else if (g_d_GameSettings._10 == 1) {
        lbl_2_bss_100B8.selectionFlags[side] = 1;
        fn_800625A4(side, 0x11);
        if (lbl_2_bss_100B8.selectionFlags[0] != 0 && lbl_2_bss_100B8.selectionFlags[1] != 0) {
            lbl_2_bss_F468.unk4F = 1;
            lbl_2_bss_F468.unk36 = 0x1E;
            lbl_803CBBCC->state = 7;
        }
    }
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

/*
 * Challenge mode: per charID, recruited characters (starMissionCompletionTracker.missions[c]._31 == 1)
 * are free and un-badged; the others are taken, with the grid cell badged by controller 0 unless the
 * character's colour-family base (fn_80067AC8(c, 0)) is already recruited.
 */
static inline void markChallengeRecruits(void) {
    s32 i;
    s32 base;
    for (i = 0; i < 54; i++) {
        if (starMissionCompletionTracker.missions[i]._31 == 1) {
            lbl_8034E9A0.charTaken[i] = 0;
            fn_800506E8(0, i, 0);
        } else {
            lbl_8034E9A0.charTaken[i] = 1;
            base = fn_80067AC8(i, 0);
            if (base != -1 && starMissionCompletionTracker.missions[base]._31 == 1) fn_800506E8(0, i, 0);
            else fn_800506E8(0, i, 1);
        }
    }
}

/*
 * Open the character-select (roster) screen: reset the select-grid state for both sides.
 * Callers: fn_2_86EC, fn_2_CCBC, fn_2_110B0 (src/menus/gap_1254.c).
 *
 *   1. Outside challenge mode (g_d_GameSettings.GameModeSelected != 5) clear the 54 taken flags
 *      (lbl_8034E9A0.charTaken, charsOnCharacterGridSelected); lbl_8034E9A0.unk48AD = 0;
 *      lbl_803C66B0.unk0 = 2.
 *   2. Pad roles pads[4] (one byte per controller) for fn_80050FE8 (DOL, stub): after the previous
 *      menu 9 pad slot 0 drives side 0 (lbl_803C66B0.padSide = {0, 1}); otherwise padSide[0] =
 *      (g_d_GameSettings._10 == 0 && !challenge) (pad 0 starts on side 1 in one-pad mode).  With
 *      _10 == 0 player 0's pad (lbl_8034E9A0.controllerIndices[0], +0x46F8) gets role 1 and the other
 *      pad (1 if player 0 is on pad 0, else 0) role 2; with _10 != 0 both players' pads get role 1.
 *      fn_80050FE8(pads, 0, !challenge), fn_2_7265C(), lbl_8034E9A0.unk472A = 0xFF.
 *   3. Both cursors (lbl_2_bss_F468.cursor[0..1]) start at 10, or 9 after menu 0xB / in challenge
 *      mode (9/10 are the two non-slot cursor positions, see fn_2_CE44 and fn_2_4970).
 *   4. Taken flags and cell badges:
 *      challenge mode: markChallengeRecruits() (per charID: recruited = free, otherwise taken with the
 *        cell badged by controller 0 unless the family base is recruited), then every charID on team 0
 *        (lbl_803C6724.first[i]) is taken, badged and its whole lbl_80108EDC colour family is taken
 *        (walking the row until -1); lbl_2_bss_F468.flags37[0] = 1;
 *      otherwise: markLockedCharsTaken() (locked uniques, lbl_803CB748), then every charID on both
 *        teams is taken, badged with its owning pad (same rule as markSlotTaken, but written out:
 *        -1 slots are skipped and the charID is re-read for each call) and its family is taken.
 *   5. Per side: lbl_803C6028.unk74[controllerIndices[side]] = (_10 == 0 && side != 0);
 *      lbl_2_bss_F410.gridPick[side] = side ? 9 : 0 (the charID the grid cursor starts on), moved to
 *      the first free exhibition cell lbl_800FDE84[0..31] if that one is taken; then fn_80050138(1,
 *      pick for pad 0..3, 0) (DOL, stub) places the pad's cursor there.
 *   6. fn_800625A4(0/1, 0xA) after menu 9 or in challenge mode (unless coming from menu 0xB), else
 *      (0/1, 9); lbl_803C66B0.unk0 = 2.
 *
 * Nothing here picks portraits or name banners: the grid is keyed by base charID (lbl_800FDE84
 * cells, fn_800506E8 badges by lbl_800E8558[c].baseCharID) and the taken flags by charID.
 *
 * Match notes: the 54-charID recruit loop must be a static inline (its i/base webs then precede the
 * strength-reduced walkers: i r23, walkers r24/r25).  The other three loops are plain code and share
 * ONE variable `i` (team-0 slots, the outer side loop, and the final side loop: r24, r24, r27) with
 * `k` for the inner slot loop (r23); declaring k before i or giving the final loop its own variable
 * permutes r23/r24/r27.  The cursor condition is written `!= 0xB && != 5` with the 10 block first.
 */
// .text:0x00007DDC size:0x910
void fn_2_7DDC(void) {
    u8 pads[4];
    s32 i;
    s32 k;
    s32 cell;
    s32 g;
    s32 j;
    s32 m;

    if (g_d_GameSettings.GameModeSelected != 5) memset(lbl_8034E9A0.charTaken, 0, sizeof(lbl_8034E9A0.charTaken));
    lbl_8034E9A0.unk48AD = 0;
    lbl_803C66B0.unk0 = 2;
    memset(pads, 0xFF, 4);
    if (lbl_803CBBCC->previousSelection == 9) {
        lbl_803C66B0.padSide[0] = 0;
        lbl_803C66B0.padSide[1] = 1;
    } else {
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) lbl_803C66B0.padSide[0] = 1;
        else lbl_803C66B0.padSide[0] = 0;
        lbl_803C66B0.padSide[1] = 1;
    }
    memset(pads, 0, 4);
    if (g_d_GameSettings._10 == 0) {
        pads[lbl_8034E9A0.controllerIndices[0]] = 1;
        if (lbl_8034E9A0.controllerIndices[0] == 0) pads[1] = 2;
        else pads[0] = 2;
    } else {
        pads[lbl_8034E9A0.controllerIndices[1]] = 1;
        pads[lbl_8034E9A0.controllerIndices[0]] = 1;
    }
    if (g_d_GameSettings.GameModeSelected != 5) fn_80050FE8(pads[0], pads[1], pads[2], pads[3], 0, 1);
    else fn_80050FE8(pads[0], pads[1], pads[2], pads[3], 0, 0);
    fn_2_7265C();
    lbl_8034E9A0.unk472A = 0xFF;
    if (lbl_803CBBCC->previousSelection != 0xB && g_d_GameSettings.GameModeSelected != 5) {
        lbl_2_bss_F468.cursor[0] = 10;
        lbl_2_bss_F468.cursor[1] = 10;
    } else {
        lbl_2_bss_F468.cursor[0] = 9;
        lbl_2_bss_F468.cursor[1] = 9;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        markChallengeRecruits();
        for (i = 0; i < 9; i++) {
            lbl_8034E9A0.charTaken[lbl_803C6724.first[i]] = 1;
            fn_800506E8(0, lbl_803C6724.first[i], 1);
            if (fn_80067B40(0, lbl_803C6724.first[i], 2)) {
                for (g = 0; g < 9; g++) {
                    for (j = 0; j < 5; j++) {
                        if (lbl_803C6724.first[i] == lbl_80108EDC[g][j]) {
                            for (m = 0; m < 5; m++) {
                                if (lbl_80108EDC[g][m] == -1) goto next_k;
                                lbl_8034E9A0.charTaken[lbl_80108EDC[g][m]] = 1;
                            }
                        }
                    }
                }
            }
        next_k:;
        }
        lbl_2_bss_F468.flags37[0] = 1;
    } else {
        markLockedCharsTaken();
        for (i = 0; i < 2; i++) {
            for (k = 0; k < 9; k++) {
                if (lbl_803C6724.teams[i][k] == -1) continue;
                lbl_8034E9A0.charTaken[lbl_803C6724.teams[i][k]] = 1;
                if (g_d_GameSettings._10 == 0 && i != 0) {
                    if (lbl_8034E9A0.controllerIndices[0] == 0) fn_800506E8(1, lbl_803C6724.teams[i][k], 1);
                    else fn_800506E8(0, lbl_803C6724.teams[i][k], 1);
                } else {
                    fn_800506E8(lbl_8034E9A0.controllerIndices[i], lbl_803C6724.teams[i][k], 1);
                }
                fn_80067B40(i, lbl_803C6724.teams[i][k], 1);
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (g_d_GameSettings._10 == 0 && i != 0) lbl_803C6028.unk74[lbl_8034E9A0.controllerIndices[i]] = 1;
        else lbl_803C6028.unk74[lbl_8034E9A0.controllerIndices[i]] = 0;
        if (i != 0) lbl_2_bss_F410.gridPick[i] = 9;
        else lbl_2_bss_F410.gridPick[i] = 0;
        if (lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[i]] != 0) {
            for (cell = 0; cell < 32; cell++) {
                if (lbl_8034E9A0.charTaken[lbl_800FDE84[cell]] == 0 && lbl_800FDE84[cell] != 0xFF) {
                    lbl_2_bss_F410.gridPick[i] = lbl_800FDE84[cell];
                    break;
                }
            }
        }
        switch (lbl_8034E9A0.controllerIndices[i]) {
        case 0: fn_80050138(1, lbl_2_bss_F410.gridPick[i], -1, -1, -1, 0); break;
        case 1: fn_80050138(1, -1, lbl_2_bss_F410.gridPick[i], -1, -1, 0); break;
        case 2: fn_80050138(1, -1, -1, lbl_2_bss_F410.gridPick[i], -1, 0); break;
        case 3: fn_80050138(1, -1, -1, -1, lbl_2_bss_F410.gridPick[i], 0); break;
        }
    }
    if (lbl_803CBBCC->previousSelection == 9) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else if (lbl_803CBBCC->previousSelection != 0xB && g_d_GameSettings.GameModeSelected == 5) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else {
        fn_800625A4(0, 9);
        fn_800625A4(1, 9);
    }
    lbl_803C66B0.unk0 = 2;
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

/* Copy one Static_Stats_Tables row into a roster entry, field by field (the same inlined helper is
 * used by every DOL/menus roster copier: fn_2_8CF8, fn_2_9ACC, characterSelectScreen,
 * transferStatsToInMemRoster, fn_800471F4, ...).  Bytes 0x1E/0x1F, 0x72/0x73 and 0x9E/0x9F of the
 * 0xA0 row are never copied: they are structure padding in the original layout.
 * See .agent/roster_flow.md section 3. */
static inline void copyStatsRow(CharacterStats* dst, CharacterStats* src) {
    COPY_STATS_ROW(*dst, *src);
}

/* fn_2_8940 -- build both in-memory rosters from the roster-screen picks (pick order).
 *
 * For side 0..1, slot n 0..8: inMemRoster[side][n] := Static_Stats_Tables[lbl_803C6724.teams[side][n]]
 * (copyStatsRow) and lbl_80354720[side][n].unk2 := lbl_803C6724.order[side][n] (batting order link).
 * Challenge mode (GameModeSelected 5): side 0's fielding arm / batting stance come from the saved
 * per-character handedness byte lbl_2_bss_3A8[lineup[n].charID] (arm = byte / 2, stance = byte % 2).
 * Then lbl_803C5EA4.teamsMirror[2][9] (s16) mirrors the picks and fn_80066EAC(0/1) rebuilds the
 * per-slot chemistry rows.  Called from fn_2_2FC0 (roster finalisation, before characterSelectScreen
 * reorders the entries by fielding position) and fn_2_61A0.
 * Skin hook (phase 3): after copyStatsRow, write the per-slot skin into the entry here
 * (.agent/roster_flow.md section 6.2). */
// .text:0x00008940 size:0x3B8
void fn_2_8940(void) {
    CharacterStats* src;
    s32 team;
    s32 n;
    s32 charID;
    s32 hand;

    for (team = 0; team < 2; team++) {
        for (n = 0; n < 9; n++) {
            charID = lbl_803C6724.teams[team][n];
            src = (CharacterStats*)&lbl_8034E9A0.stats[charID / 9][charID % 9];
            copyStatsRow(&inMemRoster[team][n], src);
            lbl_80354720[team][n].unk2 = lbl_803C6724.order[team][n];
            if (team == 0 && g_d_GameSettings.GameModeSelected == 5) {
                hand = lbl_2_bss_3A8[starMissionCompletionTracker.lineup[n].charID];
                inMemRoster[team][n].stats.FieldingArm = (hand >> 1) & 0xFF;
                inMemRoster[team][n].stats.BattingStance = hand % 2;
            }
        }
    }
    for (team = 0; team < 2; team++) {
        for (n = 0; n < 9; n++) {
            lbl_803C5EA4.teamsMirror[team][n] = lbl_803C6724.teams[team][n];
        }
    }
    fn_80066EAC(0);
    fn_80066EAC(1);
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
void fn_2_ABC0(u8 side) {
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

/* Captain charID of a side (lbl_8034E9A0.players[side], +0x46E0).  The three branches are what the
   binary does: the same load whichever mode or side (presumably different arrays once). */
static inline s32 sideCaptain(u8 side) {
    if (g_d_GameSettings.GameModeSelected != 5) return lbl_8034E9A0.players[side];
    if (side != 0) return lbl_8034E9A0.players[side];
    return lbl_8034E9A0.players[side];
}

/* Roster cursor position 10 ("clear team"): release every non-captain pick of the side. */
static inline void clearSideTeam(u8 side) {
    s32 k;
    lbl_2_bss_F468.flags3D[side] = 0;
    if (g_d_GameSettings.GameModeSelected != 5) {
        if (lbl_2_bss_F468.flags37[side] == 0) {
            fn_2_102C8(side);
            lbl_2_bss_F468.cursor[side] = 9;
        } else {
            for (k = 0; k < 9; k++) {
                if (lbl_8034E9A0.players[side] != lbl_803C6724.teams[side][k]) {
                    lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][k]] = 0;
                    fn_800506E8(lbl_8034E9A0.controllerIndices[side], lbl_803C6724.teams[side][k], 0);
                    fn_80067B40(side, lbl_803C6724.teams[side][k], 0);
                    lbl_803C6724.teams[side][k] = -1;
                    lbl_803C6724.unk4A[side][k] = 0;
                    lbl_803C6724.selectionFlags[side][k] = 0;
                }
            }
            lbl_2_bss_F468.flags37[side] = 0;
            lbl_2_bss_F468.flags43[side] = 1;
            fn_800625A4(side, 0x19);
        }
    }
}

/*
 * Roster screen: the A button of `side` (0 = P1 / team 0, 1 = P2 / team 1).  Caller: fn_2_ED94
 * (the per-pad input dispatcher of the roster screen).  Nothing happens while the side's UI state
 * (lbl_803C66B0.flags5D[0], set by fn_800625A4) is 0xB.
 *
 *   slot  = the roster slot whose pick order lbl_803C6724.order[side][slot] (+0x14) equals the side's
 *           cursor lbl_2_bss_F468.cursor[side] (first match; 0 if none).
 *   captain = lbl_8034E9A0.players[side] (+0x46E0), see sideCaptain().
 *
 * A. No grid pick pending (lbl_2_bss_F468.flags41[side] == 0): the cursor is on the roster.
 *    cursor 9  ("ready"): fn_2_5444(side) commits the lineup (challenge mode: copies team 0 into
 *              starMissionCompletionTracker +0x40B8.. / inMemRoster / lbl_80354720 and advances the
 *              scene; otherwise UI state 0x11 and, with both sides ready, the next scene) + click.
 *    cursor 10 ("clear"/"auto-fill"): refused with the alert sound when challenge mode has the roster
 *              locked (lbl_2_bss_F468.unk3F); otherwise clearSideTeam(side): with no pick in progress
 *              (flags37[side] == 0) fn_2_102C8(side) auto-fills the empty slots (random choice of
 *              fn_2_FCB4 / fn_2_FAA0 / fn_2_F200, then fn_800678CC, unsure_FillRosterPositions, UI
 *              state 0x16) and parks the cursor on 9; with a pick in progress every non-captain slot
 *              is released (charTaken = 0, fn_800506E8(pad, id, 0) un-badges the grid cell,
 *              fn_80067B40(side, id, 0) frees the colour family, teams/unk4A/selectionFlags cleared),
 *              flags37[side] = 0, flags43[side] = 1 and UI state 0x19.  Then the confirm click.
 *    cursor 0..8: picking the captain's own slot, or a locked challenge roster, gives the alert
 *              sound; otherwise flags41[side] = 1 (the next A press confirms a grid pick) and UI
 *              state 0xD (grid cursor shown).
 * B. Grid pick pending (flags41[side] != 0): confirm lbl_2_bss_F410.gridPick[side] (+0x20, the charID
 *    under the pad cursor on the select grid, kept by the DOL fn_80050138/fn_8005xxxx code).
 *    Refused (alert) if that charID is taken (lbl_8034E9A0.charTaken, +0x4757) or -1, silently if
 *    the challenge roster is locked, and with the alert when both pads share one controller
 *    (g_d_GameSettings._10 == 1) and the other side is confirming the same charID.
 *    1. Free the slot's previous character c = teams[side][slot] (not -1 / 0x36): normal modes
 *       un-badge, free its colour family and clear its taken flag; challenge mode first refuses the
 *       swap (alert) when the free characters (charTaken == 0, counted over all 54) are no more than
 *       the slots still to fill (8 - picked non-captain slots), then un-badges/un-takes either the
 *       family base (fn_80067AC8(c, 0)) when c has a colour family (fn_80067B40(..., 2) is the
 *       query form) and no other family member stays on the team, or c itself.
 *    2. teams[side][slot] = gridPick; unk4A[side][slot] = 1 (slot picked by a human this visit);
 *       fn_800628D4(charID) plays the announcer call-out (keyed by unique index via
 *       fn_800698F8); fn_800678CC(side) refreshes the side's captain banner index
 *       (lbl_8034E9A0 + 0x470D + side = captainIdx * 4 + 3 from lbl_80108ED0[12]);
 *       markSlotTaken(slot, side) (taken flag, grid-cell badge by pad, colour family taken).
 *    3. lbl_803C5EA4.unkC[side] = slot, unkA[side] = 1 (tells the scene code which slot changed);
 *       selectionFlags[side][slot] = Static_Stats_Tables[charID].chemistry[captain] (the row is
 *       indexed [charID / 9][charID % 9], 0xA0 bytes each, chemistry at +0x3B); UI state 0xF
 *       (pick landed); and when a pick was in progress (flags37[side]) the pending flag is cleared.
 *
 * Portraits/names are not chosen here: the only keys that leave this function are the charID
 * (teams[], charTaken[], chemistry, announcer) and the base charID's grid cell (fn_800506E8).
 * The visual update is driven by the UI state byte lbl_803C66B0.flags5D[side] that fn_800625A4
 * sets: menus fn_2_81628 dispatches command0xF to fn_2_7F8BC, which sets the mini image
 * charID frame and calls fn_2_74F40 for the charID-keyed name. See character_select.md section8.
 *
 * Match notes: the parameter is an int (its unmasked uses: cursor[side], teams[side], flags41[side]);
 * sideCaptain() and clearSideTeam() take u8 (every use inside them is clrlwi'd), as does
 * markSlotTaken(); `slot` is s8 (extsb before each use, clrlwi for markSlotTaken's u8 index);
 * `state` is the cursor cast to s8 and the slot search breaks on the first match with `state ==
 * order[...]`; `pick` is a local assigned after the release calls (r19); `count` is s32 and
 * `free` s8, compared as `free <= 8 - (s8)count`.
 */
// .text:0x0000DFAC size:0xB34
void fn_2_DFAC(s32 side) {
    s8 slot = 0;
    s8 family = -1;
    s32 captain;
    s32 count = 0;
    s8 free = 0;
    s8 state;
    s32 pick;
    s32 k;
    s32 i;
    s32 j;
    s8 c;
    s32 locked;

    state = lbl_2_bss_F468.cursor[side];
    captain = sideCaptain(side);
    if (lbl_803C66B0.flags5D[0] == 0xB) return;
    for (k = 0; k < 9; k++) {
        if (state == lbl_803C6724.order[side][k]) {
            slot = k;
            break;
        }
    }
    if (lbl_2_bss_F468.flags41[side] == 0) {
        if (lbl_2_bss_F468.cursor[side] == 9) {
            fn_2_5444(side);
            fn_2_1C34(0x100);
            return;
        }
        if (lbl_2_bss_F468.cursor[side] == 10) {
            locked = 0;
            if (g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468.unk3F != 0) locked = 1;
            if (locked) {
                sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
                return;
            }
            clearSideTeam(side);
            fn_2_1C34(0x100);
            return;
        }
        if (lbl_803C6724.teams[side][slot] == lbl_8034E9A0.players[side]) {
            sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
            return;
        }
        locked = 0;
        if (g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468.unk3F != 0) locked = 1;
        if (locked) {
            sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
            return;
        }
        lbl_2_bss_F468.flags41[side] = 1;
        fn_800625A4(side, 0xD);
        fn_2_1C34(0x100);
        return;
    }
    if (lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[side]] != 0 || lbl_2_bss_F410.gridPick[side] == -1) {
        sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
        return;
    }
    locked = 0;
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468.unk3F != 0) locked = 1;
    if (locked) return;
    if (g_d_GameSettings._10 == 1 && lbl_2_bss_F410.gridPick[side] != -1 &&
        lbl_2_bss_F410.gridPick[side] == lbl_2_bss_F410.gridPick[side ^ 1] && lbl_2_bss_F468.flags41[side ^ 1] != 0) {
        sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
        return;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        c = lbl_803C6724.teams[side][slot];
        if (c != CHAR_ID_NONE && c != NUM_CHOOSABLE_CHARACTERS) {
            fn_800506E8(side, c, 0);
            lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
            fn_80067B40(side, lbl_803C6724.teams[side][slot], 0);
        }
    } else {
        for (k = 0; k < 9; k++) {
            if (lbl_803C6724.teams[side][k] != CHAR_ID_NONE && lbl_803C6724.teams[side][k] != NUM_CHOOSABLE_CHARACTERS && lbl_803C6724.teams[side][k] != captain) count++;
        }
        for (i = 0; i < 54; i++) {
            if (lbl_8034E9A0.charTaken[i] == 0) free++;
        }
        if (free <= 8 - (s8)count) {
            if (lbl_803C6724.teams[side][slot] != -1 && lbl_803C6724.teams[side][slot] != NUM_CHOOSABLE_CHARACTERS) {
                sndFXStartEx(0x1BA, lbl_800EFBA4.unk3, 0x3F, 0);
                return;
            }
        }
        c = lbl_803C6724.teams[side][slot];
        if (c != CHAR_ID_NONE && c != NUM_CHOOSABLE_CHARACTERS) {
            if (fn_80067B40(side, c, 2)) {
                for (i = 0; i < 9; i++) {
                    for (j = 0; j < 5; j++) {
                        if (lbl_803C6724.teams[side][slot] == lbl_80108EDC[i][j]) {
                            family = i;
                            goto found_family;
                        }
                    }
                }
            found_family:
                if (family != -1) {
                    for (i = 0; i < 9; i++) {
                        for (j = 0; j < 5; j++) {
                            if (lbl_803C6724.teams[side][i] == lbl_80108EDC[family][j] && i != slot && lbl_80108EDC[family][j] != -1) goto place;
                        }
                    }
                    fn_800506E8(side, fn_80067AC8(lbl_803C6724.teams[side][slot], 0), 0);
                    lbl_8034E9A0.charTaken[fn_80067AC8(lbl_803C6724.teams[side][slot], 0)] = 0;
                }
            } else {
                fn_800506E8(side, lbl_803C6724.teams[side][slot], 0);
                lbl_8034E9A0.charTaken[lbl_803C6724.teams[side][slot]] = 0;
            }
        }
    }
place:
    pick = lbl_2_bss_F410.gridPick[side];
    lbl_803C6724.teams[side][slot] = pick;
    lbl_803C6724.unk4A[side][slot] = 1;
    fn_800628D4(lbl_803C6724.teams[side][slot]);
    fn_800678CC(side);
    markSlotTaken(slot, side);
    lbl_803C5EA4.unkC[side] = slot;
    lbl_803C5EA4.unkA[side] = 1;
    lbl_803C6724.selectionFlags[side][slot] = lbl_8034E9A0.stats[pick / 9][pick % 9].chemistry[captain];
    fn_800625A4(side, 0xF);
    if (lbl_2_bss_F468.flags37[side] != 0) lbl_2_bss_F468.flags41[side] = 0;
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
void fn_2_F200(u8 side) {
    return;
}

// .text:0x0000FAA0 size:0x214
void fn_2_FAA0(u8 side) {
    return;
}

// .text:0x0000FCB4 size:0x614
void fn_2_FCB4(u8 side) {
    return;
}

// .text:0x000102C8 size:0x234
/* Auto-fill, not a picture loader. Temporarily protect the other side's pending
 * grid character, choose a different fill strategy from last time, then rebuild
 * positions and request animation 0x16. A full team instead moves to Ready.
 * The temporary reservation is released after either path. */
void fn_2_102C8(u8 side) {
    s32 other;
    s32 i;
    s32 empty = 0;
    for (i = 0; i < 9; i++) {
        if (lbl_803C6724.teams[side][i] == -1 || lbl_803C6724.teams[side][i] == 54) empty++;
    }
    other = side ^ 1;
    if (lbl_2_bss_F468.flags41[other] != 0) {
        if (lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[other]] == 0) {
            lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[other]] = 1;
            lbl_2_bss_F468.reservedOtherPick[side] = 1;
        }
    }
    if (empty != 0) {
        do {
            lbl_803CBD24.current = randRange(0, 2);
        } while (lbl_803CBD24.previous == lbl_803CBD24.current);
        fn_2_ABC0(side);
        switch (lbl_803CBD24.current) {
        case 0: fn_2_FCB4(side); break;
        case 1: fn_2_FAA0(side); break;
        case 2: fn_2_F200(side); break;
        }
        fn_800678CC(side);
        unsure_FillRosterPositions(side);
        fn_800625A4(side, 0x16);
        lbl_803CBD24.previous = lbl_803CBD24.current;
        lbl_2_bss_F468.flags37[side] = 1;
    } else {
        lbl_2_bss_F468.cursor[side] = 9;
        fn_800625A4(side, 0x11);
    }
    if (lbl_2_bss_F468.reservedOtherPick[side] != 0) {
        lbl_2_bss_F468.reservedOtherPick[side] = 0;
        lbl_8034E9A0.charTaken[lbl_2_bss_F410.gridPick[other]] = 0;
    }
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
    lbl_803C66B0.padSide[1] = 0;
    lbl_803C66B0.padSide[0] = 0;
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
