#ifndef __CHALLENGE_gap_17EFC_H_
#define __CHALLENGE_gap_17EFC_H_

#include "mssbTypes.h"

typedef struct ChallengeSortNode {
    struct ChallengeSortNode* next;
    u8 _pad4[8];
    f32 sortKey;
} ChallengeSortNode;

typedef struct Gap17EFCEntry {
    /* 0x0 */ ChallengeSortNode* node;
    /* 0x4 */ f32 sortKey;
} Gap17EFCEntry;

s32 fn_1_17EFC(Gap17EFCEntry* a, Gap17EFCEntry* b);
ChallengeSortNode* fn_1_17F28(ChallengeSortNode* head, s32 count);
Gap17EFCEntry* _OSAllocFromHeap(s32 alignment, u32 size);
void fn_800246D4(s32 (*compare)(Gap17EFCEntry*, Gap17EFCEntry*), Gap17EFCEntry* first, Gap17EFCEntry* last, s32 size, s32 count);
void fn_800ACFB0(Gap17EFCEntry* allocation);
void fn_1_17FF0(void);
void fn_1_18174(void);

#endif // !__CHALLENGE_gap_17EFC_H_
