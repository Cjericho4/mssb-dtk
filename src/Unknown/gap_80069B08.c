#include "Unknown/gap_80069B08.h"

// .text:0x80069B08 size:0x60
void fn_80069B08(void) {
    Gap80069B08Queue* queue = lbl_803CC1B8;
    if (lbl_80366158.unk2A != 0) {
        lbl_80371C30[queue->slot].obj->unk5C = 0;
        lbl_80371C30[queue->slot].obj->flags |= 2;
        lbl_803CC1B8->callback = fn_80069AD4;
    }
}

// .text:0x80069B68 size:0x74
void fn_80069B68(void) {
    return;
}

// .text:0x80069BDC size:0x5B8
void fn_80069BDC(void) {
    return;
}

// .text:0x8006A194 size:0x36C
void fn_8006A194(void) {
    return;
}

// .text:0x8006A500 size:0x324
void fn_8006A500(void) {
    return;
}

// .text:0x8006A824 size:0x400
void fn_8006A824(void) {
    return;
}

// .text:0x8006AC24 size:0x348
void fn_8006AC24(void) {
    return;
}

// .text:0x8006AF6C size:0x30
void fn_8006AF6C(void) {
    if (lbl_803CC1B8->active == 0) fn_800B0A14_removeQueue();
}

// .text:0x8006AF9C size:0x294
void fn_8006AF9C(void) {
    return;
}

// .text:0x8006B230 size:0x438
void fn_8006B230(void) {
    return;
}

// .text:0x8006B668 size:0x124
void fn_8006B668(void) {
    return;
}

// .text:0x8006B78C size:0x3D4
void fn_8006B78C(void) {
    return;
}

// .text:0x8006BB60 size:0x2A0
void fn_8006BB60(void) {
    return;
}

// .text:0x8006BE00 size:0x288
void fn_8006BE00(void) {
    return;
}

// .text:0x8006C088 size:0x48
void fn_8006C088(BOOL alternate) {
    Gap80069B08RenderMode* mode;
    mode = alternate ? &lbl_8010928C : &lbl_80109250;
    lbl_803CBD34 = mode;
    VIConfigure(mode);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

// .text:0x8006C0D0 size:0x30
void fn_8006C0D0(void) {
    fn_800B0A5C_insertQueue(fn_8006BE00, lbl_803CC1B8->priority);
}

// .text:0x8006C100 size:0x3C
u8 fn_8006C100(s16 value) {
    u32 i;
    i = 0;
    do {
        if (value >= lbl_80109400[i]) return i;
        i++;
    } while (i < 7);
    return 6;
}

// .text:0x8006C13C size:0x12C
void fn_8006C13C(void) {
    return;
}

// .text:0x8006C268 size:0x4C
s16 fn_8006C268(s16* values) {
    s16 total = 0;
    s16* entry = values;
    u32 i = 0;
    do {
        ++i;
        total += *entry++;
    } while (i < 6);
    total += values[6];
    total += values[7];
    if (total > 9999) total = 9999;
    return total;
}

// .text:0x8006C2B4 size:0xE4
void fn_8006C2B4(void) {
    return;
}

// .text:0x8006C398 size:0x58
void fn_8006C398(Gap80069B08Lineup* lineup) {
    u32 i;
    memset(lineup, 0, sizeof(Gap80069B08Lineup));
    i = 0;
    do {
        lineup->order[i] = i + 1;
        i++;
    } while (i < 6);
    lineup->unk12 = 3;
}

// .text:0x8006C3F0 size:0x8
void fn_8006C3F0(Gap80069B08Callback value) {
    lbl_803CBD38 = value;
}

// .text:0x8006C3F8 size:0x44
void fn_8006C3F8(s32 a, s32 b, s32 c) {
    if (lbl_80366158.mode != 1 && lbl_803CBD38 != NULL) lbl_803CBD38(a, b, c);
}

// .text:0x8006C43C size:0x8
void fn_8006C43C(Gap80069B08Callback value) {
    lbl_803CBD3C = value;
}

// .text:0x8006C444 size:0x44
void fn_8006C444(s32 a, s32 b, s32 c) {
    if (lbl_80366158.mode != 1 && lbl_803CBD3C != NULL) lbl_803CBD3C(a, b, c);
}

// .text:0x8006C488 size:0x4
void fn_8006C488(void) {
    return;
}

// .text:0x8006C48C size:0x140
void challengeDrawStarsOnMissionMenu(void) {
    return;
}

// .text:0x8006C5CC size:0xF8
void fn_8006C5CC(void) {
    return;
}

// .text:0x8006C6C4 size:0xD8
void fn_8006C6C4(void) {
    return;
}

// .text:0x8006C79C size:0x28
BOOL fn_8006C79C(s32 index) {
    Gap80069B08Mission* mission = &starMissionCompletionTracker.missions[index];
    return mission->state == 1;
}

// .text:0x8006C7C4 size:0x214
void starMissionRelated2(void) {
    return;
}

// .text:0x8006C9D8 size:0xC4
void fn_8006C9D8(void) {
    return;
}

// .text:0x8006CA9C size:0x2C
f32 fn_8006CA9C(void) {
    return lbl_8010B590[starMissionCompletionTracker.row][starMissionCompletionTracker.column];
}

// .text:0x8006CAC8 size:0x11C
void starMissionMenu(void) {
    return;
}

// .text:0x8006CBE4 size:0xC0
void challengeRelated(void) {
    return;
}

// .text:0x8006CCA4 size:0x11C
void determineIfMissionDescriptionIsShown(void) {
    return;
}

// .text:0x8006CDC0 size:0xFC
void fn_8006CDC0(void) {
    return;
}

// .text:0x8006CEBC size:0xB0
void fn_8006CEBC(void) {
    return;
}

// .text:0x8006CF6C size:0xB8
void fn_8006CF6C(void) {
    return;
}
