#include "Unknown/gap_80067AC8.h"

// .text:0x80067AC8 size:0x78
s16 fn_80067AC8(s16 key, s8 column) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (key == lbl_80108EDC[i][j]) {
                if (column == -1) return key;
                return lbl_80108EDC[i][column];
            }
            if (lbl_80108EDC[i][j] == -1) break;
        }
    }
    return -1;
}

// .text:0x80067B40 size:0x108
/* fn_80067B40 -- mark every colour variant of charID's family as taken/free on the roster grid.
 * arg0: unused (passed by callers, not read); charID: the picked character (compared as u8, so
 * -1 never matches: a 0xFF charID returns 0 immediately); value: byte written into
 * lbl_8034E9A0.charsOnCharacterGridSelected[member] for each member of the family row of
 * lbl_80108EDC that contains charID, except value == 2 which only queries.  Returns 1 when charID
 * belongs to a colour family, else 0.  The retail compiler fully unrolls the 5-member loop.
 * Match status: NOT matched -- 8 lines: the u8 key lands in r7 (fresh reg) and the row/column
 * walkers in r6/r4 in retail; here the key stays in r4.  Explicit walkers made it worse. */
u8 fn_80067B40(s32 arg0, s16 charID, u8 value) {
    s32 i;
    s32 j;
    s32 k;
    s16 member;
    s32 id = (u8)charID;
    if (id == -1) {
        return 0;
    }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (id == lbl_80108EDC[i][j]) {
                for (k = 0; k < 5; k++) {
                    member = lbl_80108EDC[i][k];
                    if (member != -1 && value != 2) {
                        lbl_8034E9A0.charsOnCharacterGridSelected[member] = value;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x80067C48 size:0x328
void fn_80067C48(void) {
    return;
}

// .text:0x80067F70 size:0x534
void fn_80067F70(s32 player) {
    return;
}

// .text:0x800684A4 size:0x70
void fn_800684A4(void) {
    return;
}

// .text:0x80068514 size:0x118
void fn_80068514(void) {
    return;
}

// .text:0x8006862C size:0xF4
void fn_8006862C(void) {
    return;
}

// .text:0x80068720 size:0x5C
void fn_80068720(u8 index) {
    if (lbl_800EF808.enabled398 != 0) {
        fn_800A86B4(3);
        fn_800A8B78(&lbl_802E4CE8[index]);
    }
}

// .text:0x8006877C size:0xBC
void fn_8006877C(u8 index) {
    if (lbl_800EF808.enabled398 != 0) {
        u8 track = lbl_800E88A4[index].track;
        fn_800A8878(track, track);
        if (index == 12) {
            fn_800A8AB0(0);
        } else {
            fn_800A8AB0(2);
        }
        fn_800A8E30(&lbl_800E87B4[index], &lbl_8034E478[index], 0, 0);
        fn_800A86B4(4);
        fn_800A86B4(1);
    }
}

// .text:0x80068838 size:0xF78
void fn_80068838(void) {
    return;
}

// .text:0x800697B0 size:0xA4
BOOL fn_800697B0(void) {
    switch (lbl_803CBD24) {
    case 0:
        lbl_80366B18.aramAddr = ARAMTransfer(lbl_80109044, 0, 1, 0);
        lbl_803CBD24++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.done == 1) {
            fn_800111B4(lbl_80366B18.aramAddr);
            lbl_803CBD24 = 0;
            return FALSE;
        }
        break;
    }
    return TRUE;
}

// .text:0x80069854 size:0xA4
void fn_80069854(void) {
    s32 side;
    s32 i;
    for (side = 0; side < 2; side++) {
        for (i = 0; i < 9; i++) {
            if (lbl_8034E9A0.selected[side] == inMemRoster[side][i].id) {
                lbl_8034E9A0.indices[side] = i;
            }
        }
    }
}

// .text:0x800698F8 size:0x170
/* fn_800698F8 -- findCharacterID: charID -> roster-grid index (0..31, or 0x20 for the alternate
 * Birdo cell when lbl_8034E9A0.useAltBirdoGrid is set; the flag is cleared on every call).
 * Base characters are found in lbl_80108DB8 (mainCharArray, 32 scanned); colour variants in
 * lbl_80108DDC map to their family base's grid cell (piantas 0x15, nokis 0x16, toads 0x0D,
 * magikoopas 0x19, koopa 0x0C, paratroopa 0x14, shy guys 0x10, dry bones 0x1F, bros 0x17).
 * A charID in neither table OSPanics ("mb_subfunc.c" lines 0x95/0x99).  Names, portraits and the
 * announcer call-out are keyed by this index, which is why variants share their base's.
 * Match status: NOT matched -- 24 lines: retail hoists &lbl_800E69B8 into r31 in the prologue and
 * the switch's local jump table is named jumptable_801091F4; logic verified against the asm. */
s32 fn_800698F8(s32 charID) {
    s32 i;
    s32 grid;
    for (i = 0; i < 32; i++) {
        if (lbl_80108DB8[i] == charID) {
            if (i == 0x11 && lbl_8034E9A0.useAltBirdoGrid != 0) {
                i = 0x20;
            }
            lbl_8034E9A0.useAltBirdoGrid = 0;
            return i;
        }
    }
    if (i == 0x20) {
        for (i = 0; i < 22; i++) {
            if (lbl_80108DDC[i] == charID) {
                grid = charID;
                switch (i) {
                case 0: case 1: grid = 0x15; break;
                case 2: case 3: grid = 0x16; break;
                case 4: case 5: case 6: case 7: grid = 0x0D; break;
                case 8: case 9: case 10: grid = 0x19; break;
                case 11: grid = 0x0C; break;
                case 12: grid = 0x14; break;
                case 13: case 14: case 15: case 16: grid = 0x10; break;
                case 17: case 18: case 19: grid = 0x1F; break;
                case 20: case 21: grid = 0x17; break;
                }
                lbl_8034E9A0.useAltBirdoGrid = 0;
                return grid;
            }
        }
        if (i == 0x16) {
            OSPanic(lbl_800E69B8.file, 0x95, lbl_800E69B8.notFound);
        }
    }
    OSPanic(lbl_800E69B8.file, 0x99, lbl_800E69B8.badIndex);
    return 0;
}

// .text:0x80069A68 size:0x30
void fn_80069A68(void) {
    fn_80021518(0x35, lbl_800EF808.soundC0);
}

// .text:0x80069A98 size:0x3C
void fn_80069A98(void) {
    fn_80034CEC(lbl_803CBD30);
    lbl_803CBD30 = NULL;
    lbl_80366158.state = 2;
}

// .text:0x80069AD4 size:0x34
void fn_80069AD4(void) {
    if (lbl_80366158.state == 2) fn_800B0A14_removeQueue();
}
