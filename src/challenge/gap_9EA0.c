#include "challenge/gap_9EA0.h"

// .text:0x00009EA0 size:0x64
void fn_1_9EA0(u8 value, s32 arg) {
    ChallengeScene* entry = (ChallengeScene*)fn_800B0A5C_insertQueue(fn_1_9F04, 1);

    entry->byte18 = 0;
    entry->byte19 = value;
    entry->arg14 = arg;
    lbl_803CC1B8->loadingState = 0;
}

// .text:0x00009F04 size:0x120
void fn_1_9F04(void) {
    return;
}

// .text:0x0000A024 size:0x160
void fn_1_A024(Gap9EA0TextList* list, s32 action) {
    s32 start = list->start;
    s32 count = list->count;
    s32 total = list->total;
    s32 selected = list->unk4;
    s32 relative = selected - start;
    s32 visible;
    if (start + count < total) visible = count;
    else if (total < count) visible = total;
    else visible = total - start;
    switch (action) {
    case 0:
        if (relative != 0) list->unk4--;
        else if (start != 0) { list->start--; list->unk4--; }
        break;
    case 1:
        if (relative + 1 == visible) {
            if (selected + 1 < total) { list->start++; list->unk4++; }
        } else list->unk4++;
        break;
    case 2:
        if (start < count) { list->start = 0; list->unk4 = 0; }
        else { list->start -= count; list->unk4 -= list->count; }
        break;
    case 3:
        if (selected + visible >= total) { list->start = total - visible; list->unk4 = list->total - 1; }
        else { list->start += count; list->unk4 += list->count; }
        break;
    }
}

// .text:0x0000A184 size:0x70
void fn_1_A184(Gap9EA0TextList* list) {
    char* s;
    s32 n;
    s32 i;
    Gap9EA0TextEntry* entry;

    if (list->start + list->count < list->total) {
        n = list->count;
    } else if (list->total < list->count) {
        n = list->total;
    } else {
        n = list->total - list->start;
    }
    entry = &list->entries[list->start];
    for (i = 0; i < n; i++, entry++) {
        if ((s = entry->text) != NULL) {
            while (*s++ != 0) {
            }
        }
    }
}

// .text:0x0000A1F4 size:0x1C
void fn_1_A1F4(Gap9EA0Obj* obj, s32 arg1, s32 arg2, s32 arg3) {
    obj->unk0 = arg1;
    obj->unk10 = arg2;
    obj->unkC = arg3;
    obj->unk8 = 0;
    obj->unk4 = 0;
}

// .text:0x0000A210 size:0x40
char* fn_1_A210(char* path) {
    char c;
    char* last = path;

    if (path == NULL) {
        return NULL;
    }
    while ((c = *path++) != 0) {
        if (c == '/') {
            last = path;
        }
    }
    return last;
}

// .text:0x0000A250 size:0x94
void fn_1_A250(void) {
    s32 i;

    for (i = 0; i < 11; i++) {
        lbl_1_common_bss_49A78.slots[i] = -1;
    }
    lbl_1_common_bss_49A78.unkC = -1;
    lbl_803CC1B8->aFunctionPointer = fn_1_A348;
}
