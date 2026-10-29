#include "challenge/gap_C2A4.h"

// .text:0x0000C2A4 size:0x38
void fn_1_C2A4(void) {
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
    fn_800B0A14_removeQueue();
}

// .text:0x0000C2DC size:0x2CC
static inline s32 visitChallengeTree(ChallengeTreeNode* node, char* prefix, s32 depth, s32 mode, s32 result, s32* remaining, s32* skip, s32* count) {
    if (*skip == 0) {
        prefix[depth] = '+';
        prefix[depth + 1] = 0;
        --*count;
        if (*count == 0) return result;
    } else {
        --*skip;
    }
    --*remaining;
    if (node->child != NULL) {
        if (node->sibling != NULL) prefix[depth] = '|';
        else prefix[depth] = ' ';
        result = fn_1_C2DC(node->child, prefix, depth + 1, mode, result, remaining, skip, count);
        if (*count == 0) return result;
    }
    if (node->sibling != NULL) {
        result = fn_1_C2DC(node->sibling, prefix, depth, mode, result, remaining, skip, count);
        if (*count == 0) return result;
    }
    return result;
}

s32 fn_1_C2DC(ChallengeTreeNode* node, char* prefix, s32 depth, s32 mode, s32 result, s32* remaining, s32* skip, s32* count) {
    if (*skip == 0) {
        prefix[depth] = '+';
        prefix[depth + 1] = 0;
        --*count;
        if (*count == 0) return result;
    } else {
        --*skip;
    }
    --*remaining;
    if (node->child != NULL) {
        if (node->sibling != NULL) prefix[depth] = '|';
        else prefix[depth] = ' ';
        result = visitChallengeTree(node->child, prefix, depth + 1, mode, result, remaining, skip, count);
        if (*count == 0) return result;
    }
    if (node->sibling != NULL) {
        result = visitChallengeTree(node->sibling, prefix, depth, mode, result, remaining, skip, count);
        if (*count == 0) return result;
    }
    return result;
}

// .text:0x0000C5A8 size:0x4
void fn_1_C5A8(void) {
    return;
}
