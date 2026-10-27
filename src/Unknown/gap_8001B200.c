#include "Unknown/gap_8001B200.h"
#include "Unknown/gap_8001196C.h"

typedef struct PitchBankLoadState {
    u8 reset;
    u8 pitching;
} PitchBankLoadState;
extern PitchBankLoadState lbl_803CBC3C;

// .text:0x8001B200 size:0x14
void fn_8001B200(void) {
    return;
}

// .text:0x8001B214 size:0x10
void fn_8001B214(void) {
    return;
}

// .text:0x8001B224 size:0xAC
void fn_8001B224(void) {
    return;
}

// .text:0x8001B2D0 size:0x38
void fn_8001B2D0(void) {
    return;
}

// .text:0x8001B308 size:0x54
void fn_8001B308(void) {
    return;
}

// .text:0x8001B35C size:0x17C
void fn_8001B35C(void) {
    return;
}

// .text:0x8001B4D8 size:0x114
void fn_8001B4D8(void) {
    return;
}

// .text:0x8001B5EC size:0x13C
void fn_8001B5EC(void) {
    return;
}

// .text:0x8001B728 size:0xE4
void fn_8001B728(void) {
    return;
}

// .text:0x8001B80C size:0x10C
void getAnimRelatedCoordinates(void) {
    return;
}

// .text:0x8001B918 size:0x78
void QueueCharacterAnimation(void) {
    return;
}

// .text:0x8001B990 size:0xB4
void AnimateCharacter(void) {
    return;
}

// .text:0x8001BA44 size:0x40C
void fn_8001BA44(void) {
    return;
}

// .text:0x8001BE50 size:0x3E4
void fn_8001BE50(void) {
    return;
}

// .text:0x8001C234 size:0x2F4
void fn_8001C234(void) {
    return;
}

// .text:0x8001C528 size:0x60
void fn_8001C528(void) {
    return;
}

// .text:0x8001C588 size:0xF4
void fn_8001C588(void) {
    return;
}

// .text:0x8001C67C size:0x2A4
void fn_8001C67C_animation(void) {
    return;
}

// .text:0x8001C920 size:0x120
/* Loads the pitching animation bank, selecting track 5 or 18 by game mode. */
s32 fn_8001C920(s32 charID) {
    s32 track;
    if (lbl_803CBC3C.pitching == 0) {
        if (lbl_803C6CF8.allowLoad != 1) goto notReady;
        lbl_803CBC3C.pitching = 1;
    }
    if (lbl_803CBC3C.pitching == 1) {
        if (g_d_GameSettings.unk11 || g_d_GameSettings.mode == GAME_TYPE_PRACTICE) {
            track = charID * SUBFILE_TRACKS + 18; /* practice / alternate pitching bank */
        } else {
            track = charID * SUBFILE_TRACKS + 5; /* normal pitching bank */
        }
        ARAMTransfer(&lbl_803CB790[track], g_hugeAnimStruct.pitchingAnimBank, 0, NULL);
        lbl_803CBC3C.pitching = 2;
    } else if (lbl_803CBC3C.pitching == 2) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(g_hugeAnimStruct.pitchingAnimBank);
            if (g_hugeAnimStruct.slotPtrs[0]->animBankC == NULL) {
                g_hugeAnimStruct.slotPtrs[0]->animBankC = g_hugeAnimStruct.pitchingAnimBank;
            }
            return 1;
        }
    }
notReady:
    lbl_803CBC3C.reset = 0;
    return 0;
}

// .text:0x8001CA40 size:0xD0
void fn_8001CA40(void) {
    return;
}

// .text:0x8001CB10 size:0xC4
void fn_8001CB10(void) {
    return;
}

// .text:0x8001CBD4 size:0xF4
void fn_8001CBD4(void) {
    return;
}

// .text:0x8001CCC8 size:0x1AC
void fn_8001CCC8(void) {
    return;
}

// .text:0x8001CE74 size:0x200
void fn_8001CE74(void) {
    return;
}

// .text:0x8001D074 size:0x5C
void fn_8001D074(void) {
    return;
}

// .text:0x8001D0D0 size:0x40
void fn_8001D0D0(void) {
    return;
}

// .text:0x8001D110 size:0x38
void fn_8001D110(void) {
    return;
}

// .text:0x8001D148 size:0x38
void fn_8001D148(void) {
    return;
}

// .text:0x8001D180 size:0x154
void fn_8001D180(void) {
    return;
}

// .text:0x8001D2D4 size:0x8A0
void fn_8001D2D4(void) {
    return;
}

// .text:0x8001DB74 size:0x1E4
void fn_8001DB74(void) {
    return;
}

// .text:0x8001DD58 size:0x14C
void fn_8001DD58(void) {
    return;
}

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(void) {
    return;
}

// .text:0x8001E0D8 size:0x388
void fn_8001E0D8(void) {
    return;
}
