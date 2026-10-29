#ifndef __CHALLENGE_rep_00B0_H_
#define __CHALLENGE_rep_00B0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

void fn_1_19AC(void);
typedef struct ChallengeBounds { f32 minX, minY, minZ, maxX, maxY, maxZ; } ChallengeBounds;
void fn_1_1BF8(ChallengeBounds* bounds, s32 index);
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s32 face);
void fn_1_25BC(void);
void fn_1_3E38(Vec* position, u32 index);
void fn_1_4074(Vec* position);
typedef struct ChallengeSegment { Vec start, end; } ChallengeSegment;
void fn_1_4290(ChallengeSegment* segment);
typedef struct ChallengeHit { Vec position, normal; } ChallengeHit;
typedef struct ChallengeCollisionQuery {
    Mtx view;
    u8 _pad30[0x30];
    Vec normal;
    f32 length, nearest;
    u16 hits;
    u8 _pad76[2];
} ChallengeCollisionQuery;
struct ChallengeCollisionMesh;
u16 fn_1_4728(ChallengeSegment* segment, ChallengeHit* hit);
void fn_1_4A24(ChallengeCollisionQuery* query, struct ChallengeCollisionMesh* mesh);

#endif // !__CHALLENGE_rep_00B0_H_
