#include "Unknown/gap_80041348.h"
#include "string.h"

// .text:0x80041348 size:0x1F4
void fn_80041348(void) {
    return;
}

// .text:0x8004153C size:0x40
void fn_8004153C(void) {
    lbl_803CBC50 = 0x2380;
    lbl_803CBC4C = 0xE60;
    lbl_803CBC48 = fn_800ACC6C(1, 0x2380, 0x10000);
}

// .text:0x8004157C size:0x24
BOOL fn_8004157C(void) {
    if (lbl_803CBCC0 != 0) {
        lbl_803CBCC0--;
        return TRUE;
    }
    return FALSE;
}

// .text:0x800415A0 size:0x8
void fn_800415A0(s16 value) {
    lbl_803CBCC0 = value;
}

// .text:0x800415A8 size:0xAD4
void fn_800415A8(void) {
    return;
}

// .text:0x8004207C size:0x51C
void capApplicationFunction(void) {
    return;
}

// .text:0x80042598 size:0x144
void fn_80042598(void) {
    return;
}

/* transferStatsToInMemRoster -- toggle the "star player" bonus of one roster slot (pre-game lineup
 * screen startGameRelated, star menu fn_8005A350).  Not in challenge mode.
 *
 * side: 0/1; the slot is lbl_803297E0.lineupCursor[side] (1-based) - 1.  Requires the character's
 * star flag lbl_80361B20.characterFlags[CharID].  Bumps the side's toggle counter (mod 2), flips
 * lbl_8034E9A0.starFlags[side*9 + slot] and copies the side's nine flags to lbl_802E4B00 (read by
 * game.rel).  Flag set: add lbl_800E86F0[k] to the twelve ability bytes and +2 to each stat bar
 * (capped at 10) in place.  Flag clear: re-copy the whole row from Static_Stats_Tables[CharID]
 * (COPY_STATS_ROW), which resets bytes 0x00..0x1D of the entry (a phase-3 skin byte must be
 * saved around it; see .agent/roster_flow.md section 6.2).
 * Match status: NOT matched (26 diff lines): the target keeps the lbl_8034E9A0 base in r7 from the
 * star-flag read to the static-row address and numbers the saved registers differently; the
 * instruction sequence is otherwise identical. */
/* transferStatsToInMemRoster -- toggle the "star player" bonus of one roster slot (pre-game lineup
 * screen startGameRelated, star menu fn_8005A350).  Not in challenge mode.
 *
 * side: 0/1; the slot is lbl_803297E0.lineupCursor[side] (1-based) - 1.  Requires the character's
 * star flag lbl_80361B20.characterFlags[CharID].  Bumps the side's toggle counter (mod 2), flips
 * lbl_8034E9A0.starFlags[side][slot] and copies the side's nine flags to lbl_802E4B00 (read by
 * game.rel).  Flag set: add lbl_800E86F0[k] to the twelve ability bytes and +2 to each stat bar
 * (capped at 10) in place.  Flag clear: re-copy the whole row from Static_Stats_Tables[CharID]
 * (COPY_STATS_ROW), which resets bytes 0x00..0x1D of the entry (a phase-3 skin byte must be
 * saved around it; see .agent/roster_flow.md section 6.2).
 * Match status: NOT matched (26 diff lines): the target keeps the lbl_8034E9A0 base in r7 from the
 * star-flag read to the static-row address and numbers the saved registers differently; the
 * instruction sequence is otherwise identical. */
// .text:0x800426DC size:0x514
void transferStatsToInMemRoster(u8 side) {
    s32 slot;
    s32 charID;
    u8 row;
    u8 col;

    if (g_d_GameSettings.gameMode == 5) {
        return;
    }
    slot = lbl_803297E0.lineupCursor[side] - 1;
    if (lbl_80361B20.characterFlags[inMemRoster[side][slot].stats.CharID] == 0) {
        return;
    }
    lbl_8034E9A0.starToggleCount[side]++;
    if (lbl_8034E9A0.starToggleCount[side] == 2) {
        lbl_8034E9A0.starToggleCount[side] = 0;
    }
    if (g_d_GameSettings.gameMode != 5) {
        lbl_8034E9A0.starFlags[side][slot] ^= 1;
        memcpy(lbl_802E4B00[side], lbl_8034E9A0.starFlags[side], 9);
    } else {
        lbl_8034E9A0.starFlags[0][slot] = 1;
    }
    if (lbl_8034E9A0.starFlags[side][slot] != 0) {
        inMemRoster[side][slot].stats.SlapContactSize += lbl_800E86F0[0];
        inMemRoster[side][slot].stats.ChargeContactSize += lbl_800E86F0[1];
        inMemRoster[side][slot].stats.SlapHitPower += lbl_800E86F0[2];
        inMemRoster[side][slot].stats.ChargeHitPower += lbl_800E86F0[3];
        inMemRoster[side][slot].stats.Speed += lbl_800E86F0[5];
        inMemRoster[side][slot].stats.ThrowingArm += lbl_800E86F0[6];
        inMemRoster[side][slot].stats.BuntingContactSize += lbl_800E86F0[4];
        inMemRoster[side][slot].stats.CurveBallSpeed += lbl_800E86F0[7];
        inMemRoster[side][slot].stats.FastBallSpeed += lbl_800E86F0[8];
        inMemRoster[side][slot].stats.cursedBall += lbl_800E86F0[9];
        inMemRoster[side][slot].stats.Curve += lbl_800E86F0[10];
        inMemRoster[side][slot].stats.curveControl += lbl_800E86F0[11];
        inMemRoster[side][slot].stats.BattingStatBar += 2;
        if (inMemRoster[side][slot].stats.BattingStatBar > 10) {
            inMemRoster[side][slot].stats.BattingStatBar = 10;
        }
        inMemRoster[side][slot].stats.PitchingStatBar += 2;
        if (inMemRoster[side][slot].stats.PitchingStatBar > 10) {
            inMemRoster[side][slot].stats.PitchingStatBar = 10;
        }
        inMemRoster[side][slot].stats.RunningStatBar += 2;
        if (inMemRoster[side][slot].stats.RunningStatBar > 10) {
            inMemRoster[side][slot].stats.RunningStatBar = 10;
        }
        inMemRoster[side][slot].stats.FieldingStatBar += 2;
        if (inMemRoster[side][slot].stats.FieldingStatBar > 10) {
            inMemRoster[side][slot].stats.FieldingStatBar = 10;
        }
        return;
    }
    charID = inMemRoster[side][slot].stats.CharID;
    row = charID / 9;
    col = charID % 9;
    COPY_STATS_ROW(inMemRoster[side][slot], lbl_8034E9A0.stats[row][col]);
}

// .text:0x80042BF0 size:0x54
void randRange_FUN_80042bf0(void) {
    return;
}

// .text:0x80042C44 size:0xF4
void sndFXRelated(void) {
    return;
}
