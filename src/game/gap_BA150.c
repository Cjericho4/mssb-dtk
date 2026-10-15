#include "game/gap_BA150.h"
#include "UnknownHeaders.h"

extern void fn_800246D4(s32 (*compareFn)(BA150SortItem*, BA150SortItem*), BA150SortItem* out, BA150SortItem* in, u32 elemSize, u32 count);

// .text:0x000BA150 size:0x24 mapped:0x806F91E4
void fn_3_BA150(void) {
    pitchingMachinePitching(0x19);
}

// .text:0x000BA174 size:0x2C mapped:0x806F9208
s32 fn_3_BA174(BA150SortItem* a, BA150SortItem* b) {
    if (a->sortKey < b->sortKey) {
        return 1;
    }
    if (a->sortKey > b->sortKey) {
        return -1;
    }
    return 0;
}

// .text:0x000BA1A0 size:0xC8 mapped:0x806F9234
BA150Node* fn_3_BA1A0(BA150Node* list, u32 count) {
    BA150SortItem* items = _OSAllocFromHeap(0x20, count * 8);
    BA150SortItem* p = items;
    BA150Node* n;

    for (n = list; n != NULL; n = n->next) {
        p->node = n;
        p->sortKey = n->sortKey;
        p++;
    }
    fn_800246D4(fn_3_BA174, items, items, 8, count);
    list = items->node;
    p = items;
    while (--count != 0) {
        p->node->next = p[1].node;
        p++;
    }
    p->node->next = NULL;
    fn_800ACFB0(items);
    return list;
}

// .text:0x000BA268 size:0x184 mapped:0x806F92FC
void fn_3_BA268(void) {
    return;
}

// .text:0x000BA3EC size:0x14C mapped:0x806F9480
void fn_3_BA3EC(void) {
    return;
}

