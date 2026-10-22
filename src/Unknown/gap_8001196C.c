#include "Unknown/gap_8001196C.h"

// .text:0x8001196C size:0xF4
void fn_8001196C(void) {
    return;
}

// .text:0x80011A60 size:0x104
void fn_80011A60(void) {
    return;
}

// .text:0x80011B64 size:0x80
void fn_80011B64(void) {
    return;
}

// .text:0x80011BE4 size:0xC4
void fn_80011BE4(void) {
    return;
}

// .text:0x80011CA8 size:0xA44
void fn_80011CA8(void) {
    return;
}

// .text:0x800126EC size:0x10C
void fn_800126EC(void) {
    return;
}

// .text:0x800127F8 size:0x398
void LoadModel(void) {
    return;
}

// .text:0x80012B90 size:0xAF0
void fn_80012B90(void) {
    return;
}

// .text:0x80013680 size:0xB84
void fn_80013680(void) {
    return;
}

// .text:0x80014204 size:0x3F4
void fn_80014204(void) {
    return;
}

// .text:0x800145F8 size:0x398
void fn_800145F8(void) {
    return;
}

// .text:0x80014990 size:0x88
void fn_80014990(void) {
    return;
}

// .text:0x80014A18 size:0x334
void fn_80014A18(void) {
    return;
}

// .text:0x80014D4C size:0x104
void fn_80014D4C(void) {
    return;
}

// .text:0x80014E50 size:0xF0
void fn_80014E50(void) {
    return;
}

// .text:0x80014F40 size:0xCC
void fn_80014F40(void) {
    return;
}

// .text:0x8001500C size:0x45C
void fn_8001500C(void) {
    return;
}

// .text:0x80015468 size:0x4E4
void fn_80015468(void) {
    return;
}

// .text:0x8001594C size:0x9F8
void fn_8001594C(void) {
    return;
}

// .text:0x80016344 size:0x3CC
void fn_80016344(void) {
    return;
}

// .text:0x80016710 size:0x450
void fn_80016710(void) {
    return;
}

// .text:0x80016B60 size:0x41C
void fn_80016B60(void) {
    return;
}

// .text:0x80016F7C size:0x11C
void fn_80016F7C(void) {
    return;
}

// .text:0x80017098 size:0x2A8
void fn_80017098(void) {
    return;
}

// .text:0x80017340 size:0x24C
void fn_80017340(void) {
    return;
}

// .text:0x8001758C size:0x228
BOOL fn_8001758C(u8* state, s32 slot, u8 charID, u8 team, u8 player, u8 arg6, u8 slotKind, u8 variant) {
    Gap8001196CAnim* anim = &g_hugeAnimStruct.slots[slot];
    s32 track;
    Gap8001196CRosterEntry* entry;

    switch (*state) {
    case 0:
        if (lbl_803C6CF8.allowLoad == 1) {
            anim->unk25C = 1;
            anim->team = team;
            anim->player = player;
            anim->slotKind = slotKind;
            anim->charID = charID;
            anim->unk258 = arg6;
            anim->variant = variant;
            track = anim->charID * SUBFILE_TRACKS;
            entry = &inMemRoster[team][player];
            anim->rosterUnk26 = entry->unk26;
            anim->rosterUnk27 = entry->unk27;
            anim->isBatter = slotKind == 9;
            if (variant == 0) {
                track += 1;
            }
            if (anim->isBatter != 0 && variant == 1 && g_hugeAnimStruct.cachedBatterCharID == charID) {
                memcpy(anim->fileBuffer, g_hugeAnimStruct.cachedBatterData, g_hugeAnimStruct.cachedBatterSize);
                goto load;
            }
            if (slotKind >= 10 && slotKind <= 12 && variant == 0 && g_hugeAnimStruct.cachedFielderCharID == charID) {
                memcpy(anim->fileBuffer, g_hugeAnimStruct.cachedFielderData, g_hugeAnimStruct.cachedFielderSize);
                goto load;
            }
            if (variant == 0 || fn_8002204C(anim->charID, anim->fileBuffer) == NULL) {
                ARAMTransfer(&lbl_803CB790[track], anim->fileBuffer, 0, NULL);
            }
            *state = 1;
        }
        break;
    case 1:
        if (lbl_803716B8.loadBusy == 0 && lbl_803C6CF8.allowLoad == 1) {
        load:
            fn_80017814(anim, anim->unk255, slotKind, fn_8001FDD4);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// .text:0x800177B4 size:0x60
void fn_800177B4(void) {
    return;
}

// .text:0x80017814 size:0x514
void fn_80017814(Gap8001196CAnim* anim, s32 arg1, u32 slotKind, void (*callback)(struct Gap8001E460Object*)) {
    return;
}

// .text:0x80017D28 size:0x94
void fn_80017D28(void) {
    return;
}

// .text:0x80017DBC size:0x268
void fn_80017DBC(void) {
    return;
}

// .text:0x80018024 size:0x24C
void fn_80018024(void) {
    return;
}

// .text:0x80018270 size:0x650
void fn_80018270(void) {
    return;
}

// .text:0x800188C0 size:0xF8
void fn_800188C0(void) {
    return;
}

// .text:0x800189B8 size:0x2C
void fn_800189B8(void) {
    return;
}

// .text:0x800189E4 size:0x154
void fn_800189E4(void) {
    return;
}

// .text:0x80018B38 size:0x3C
void fn_80018B38(void) {
    return;
}

// .text:0x80018B74 size:0x278
void fn_80018B74(void) {
    return;
}

// .text:0x80018DEC size:0x8EC
void fn_80018DEC(void) {
    return;
}

// .text:0x800196D8 size:0x388
void fn_800196D8(void) {
    return;
}

// .text:0x80019A60 size:0x1A0
void fn_80019A60(void) {
    return;
}

// .text:0x80019C00 size:0x65C
void fn_80019C00(void) {
    return;
}

// .text:0x8001A25C size:0x1A0
void fn_8001A25C(void) {
    return;
}

// .text:0x8001A3FC size:0x2B4
void fn_8001A3FC(void) {
    return;
}

// .text:0x8001A6B0 size:0x3F4
void challengeMapRelated(void) {
    return;
}

// .text:0x8001AAA4 size:0x4C
void fn_8001AAA4(void) {
    return;
}

// .text:0x8001AAF0 size:0x20
void fn_8001AAF0(void) {
    fn_8003AC90();
}

// .text:0x8001AB10 size:0x488
void fn_8001AB10(void) {
    return;
}

// .text:0x8001AF98 size:0x268
void fn_8001AF98(void) {
    return;
}
