#include "Unknown/gap_80091450.h"

// .text:0x80091450 size:0x10
Gap80091450Entry* TEXGet(Gap80091450Tex* tex, s32 index) {
    return &tex->entries[index];
}

// .text:0x80091460 size:0x18
void DSInitList(Gap80091450Tree* list, s32 start, s32 end) {
    list->unk4 = 0;
    list->unk8 = 0;
    list->size = end - start;
}

// .text:0x80091478 size:0x94
void DSInsertListObject(void) {
    return;
}

// .text:0x8009150C size:0x50
void Strcmp(void) {
    return;
}

// .text:0x8009155C size:0x14
void DSInitTree(Gap80091450Tree* tree, s32 start, s32 end) {
    tree->unk4 = 0;
    tree->size = end - start;
}

// .text:0x80091570 size:0x98
void DSInsertBranchBelow(void) {
    return;
}
