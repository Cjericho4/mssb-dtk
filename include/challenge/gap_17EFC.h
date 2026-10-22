#ifndef __CHALLENGE_gap_17EFC_H_
#define __CHALLENGE_gap_17EFC_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"

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
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
typedef struct ChallengeRenderCamera {
    Mtx44 projection;
    Mtx view;
    u8 _pad70[0x38];
} ChallengeRenderCamera;
ChallengeRenderCamera* fn_80052768(s32 index);
void fn_1_17FF0(void);
void fn_1_18174(void);

#endif // !__CHALLENGE_gap_17EFC_H_
