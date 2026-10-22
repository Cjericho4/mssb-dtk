#include "challenge/gap_17EFC.h"

// .text:0x00017EFC size:0x2C
s32 fn_1_17EFC(Gap17EFCEntry* a, Gap17EFCEntry* b) {
    if (a->sortKey < b->sortKey) {
        return 1;
    }
    if (a->sortKey > b->sortKey) {
        return -1;
    }
    return 0;
}

// .text:0x00017F28 size:0xC8
ChallengeSortNode* fn_1_17F28(ChallengeSortNode* head, s32 count) {
    Gap17EFCEntry* allocation = _OSAllocFromHeap(0x20, count * sizeof(Gap17EFCEntry));
    Gap17EFCEntry* entry = allocation;
    ChallengeSortNode* node = head;
    while (node != 0) {
        entry->node = node;
        entry->sortKey = node->sortKey;
        entry++;
        node = node->next;
    }
    fn_800246D4(fn_1_17EFC, allocation, allocation, sizeof(Gap17EFCEntry), count);
    head = allocation->node;
    entry = allocation;
    while (--count != 0) {
        entry->node->next = entry[1].node;
        entry++;
    }
    entry->node->next = 0;
    fn_800ACFB0(allocation);
    return head;
}

// .text:0x00017FF0 size:0x184
void fn_1_17FF0(void) {
    return;
}

// .text:0x00018174 size:0x14C
void fn_1_18174(void) {
    return;
}
