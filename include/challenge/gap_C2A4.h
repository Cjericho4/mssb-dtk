#ifndef __CHALLENGE_gap_C2A4_H_
#define __CHALLENGE_gap_C2A4_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

void fn_1_C2A4(void);
typedef struct ChallengeTreeNode {
    u8 _pad0[8];
    struct ChallengeTreeNode* sibling;
    u8 _padC[4];
    struct ChallengeTreeNode* child;
} ChallengeTreeNode;
s32 fn_1_C2DC(ChallengeTreeNode* node, char* prefix, s32 depth, s32 mode, s32 result, s32* remaining, s32* skip, s32* count);
void fn_1_C5A8(void);

#endif // !__CHALLENGE_gap_C2A4_H_
