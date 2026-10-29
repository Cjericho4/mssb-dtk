#include "challenge/rep_00B0.h"
/* Bind the SDK display-list helpers to this game's unresolved symbol names. */
#define __GDCurrentDL lbl_803CC0F0
#define GDOverflowed fn_800A1B80
#include "Dolphin/gd.h"
#include "Dolphin/mtx.h"
extern Vec lbl_1_bss_60[8];

// .text:0x000019AC size:0x24C
void fn_1_19AC(void) {
    return;
}

// .text:0x00001BF8 size:0x1C4
/* Expand a bounding box into eight vertices and emit its six quad faces. */
void fn_1_1BF8(ChallengeBounds* bounds, s32 index) {
    ChallengeBounds* box = &bounds[index];
    lbl_1_bss_60[0].x = box->minX;
    lbl_1_bss_60[0].y = box->minY;
    lbl_1_bss_60[0].z = box->maxZ;
    lbl_1_bss_60[1].x = box->maxX;
    lbl_1_bss_60[1].y = box->minY;
    lbl_1_bss_60[1].z = box->maxZ;
    lbl_1_bss_60[2].x = box->maxX;
    lbl_1_bss_60[2].y = box->minY;
    lbl_1_bss_60[2].z = box->minZ;
    lbl_1_bss_60[3].x = box->minX;
    lbl_1_bss_60[3].y = box->minY;
    lbl_1_bss_60[3].z = box->minZ;
    lbl_1_bss_60[4].x = box->minX;
    lbl_1_bss_60[4].y = box->maxY;
    lbl_1_bss_60[4].z = box->maxZ;
    lbl_1_bss_60[5].x = box->maxX;
    lbl_1_bss_60[5].y = box->maxY;
    lbl_1_bss_60[5].z = box->maxZ;
    lbl_1_bss_60[6].x = box->maxX;
    lbl_1_bss_60[6].y = box->maxY;
    lbl_1_bss_60[6].z = box->minZ;
    lbl_1_bss_60[7].x = box->minX;
    lbl_1_bss_60[7].y = box->maxY;
    lbl_1_bss_60[7].z = box->minZ;
    __GDCheckOverflowed(1);
    __GDWriteU8(0x80);
    __GDCheckOverflowed(2);
    __GDWriteU16(24);
    fn_1_1DBC(7, 6, 2, 3, 12);
    fn_1_1DBC(5, 4, 0, 1, 13);
    fn_1_1DBC(3, 2, 1, 0, 14);
    fn_1_1DBC(4, 5, 6, 7, 15);
    fn_1_1DBC(4, 7, 3, 0, 16);
    fn_1_1DBC(6, 5, 1, 2, 17);
}

// .text:0x00001DBC size:0x800
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s32 face) {
    return;
}

// .text:0x000025BC size:0x187C
void fn_1_25BC(void) {
    return;
}

static inline void writeChallengeFloat(f32 value) {
    union { f32 value; u32 bits; } encoded;
    encoded.value = value;
    __GDCheckOverflowed(4);
    __GDWriteU32(encoded.bits);
}
static inline void writeChallengePosition(f32 x, f32 y, f32 z) {
    writeChallengeFloat(x);
    writeChallengeFloat(y);
    writeChallengeFloat(z);
}
// .text:0x00003E38 size:0x23C
/* Emit a position and decode the packed display-list attribute index. */
void fn_1_3E38(Vec* position, u32 index) {
    writeChallengePosition(position->x, position->y, position->z);
    __GDCheckOverflowed(1);
    __GDWriteU8((index >> 7) + ((index & 0x7F) - 1) * 2);
}

// .text:0x00004074 size:0x21C
/* Emit a floating-point position and its display-list attribute index. */
void fn_1_4074(Vec* position) {
    writeChallengePosition(position->x, position->y, position->z);
    __GDCheckOverflowed(1);
    __GDWriteU8(18);
}

// .text:0x00004290 size:0x498
void fn_1_4290(void) {
    return;
}

// .text:0x00004728 size:0x2FC
#include <string.h>
#include <math.h>
typedef struct ChallengeCollisionArchive {
    ChallengeSegment* bounds;
    struct ChallengeCollisionMesh* meshes[1];
} ChallengeCollisionArchive;
typedef struct ChallengeCollisionState {
    u8 _pad0[0x224];
    ChallengeCollisionArchive* archive;
    s16 count;
} ChallengeCollisionState;
extern ChallengeCollisionState lbl_1_common_bss_472B4;
extern Vec lbl_1_data_218, lbl_1_data_224;
void makeLookAtMatrix(Mtx matrix, Vec* eye, Vec* up, Vec* target);
typedef union ChallengeVectorBits { Vec vector; u32 bits[3]; } ChallengeVectorBits;
u16 fn_1_4728(ChallengeSegment* segment, ChallengeHit* hit) {
    u8 rejected[256];
    ChallengeCollisionQuery query;
    ChallengeVectorBits delta[4];
    Mtx inverse;
    ChallengeCollisionState* state = &lbl_1_common_bss_472B4;
    s32 count;
    u32 noCandidates;
    ChallengeSegment* bounds = state->archive->bounds;
    u8* flag;
    memset(rejected, 1, state->count);
    count = state->count;
    flag = rejected;
    noCandidates = 1;
    do {
        PSVECSubtract(&segment->start, &bounds->start, &delta[0].vector);
        PSVECSubtract(&bounds->end, &segment->start, &delta[1].vector);
        PSVECSubtract(&segment->end, &bounds->start, &delta[2].vector);
        PSVECSubtract(&bounds->end, &segment->end, &delta[3].vector);
        if (!(((delta[0].bits[0] & delta[2].bits[0]) | (delta[1].bits[0] & delta[3].bits[0])) & 0x80000000) &&
            !(((delta[0].bits[1] & delta[2].bits[1]) | (delta[1].bits[1] & delta[3].bits[1])) & 0x80000000) &&
            !(((delta[0].bits[2] & delta[2].bits[2]) | (delta[1].bits[2] & delta[3].bits[2])) & 0x80000000)) {
            *flag = 0;
            noCandidates = 0;
        }
        bounds++;
        flag++;
    } while (--count);
    if (noCandidates) return 0;
    makeLookAtMatrix(query.view, &segment->start, &lbl_1_data_218, &segment->end);
    query.nearest = query.length = dolsqrtf2(PSVECSquareDistance(&segment->end, &segment->start));
    query.hits = 0;
    {
        u8* meshFlag;
        s32 meshCount;
        struct ChallengeCollisionMesh** mesh;
        mesh = state->archive->meshes;
        meshCount = state->count;
        meshFlag = rejected;
        do {
            if (*meshFlag++ == 0) fn_1_4A24(&query, *mesh);
            mesh++;
        } while (--meshCount);
    }
    if (query.hits) {
        PSMTXInverse(query.view, inverse);
        lbl_1_data_224.z = -query.nearest;
        PSMTXMultVec(inverse, &lbl_1_data_224, &hit->position);
        PSMTXTranspose(query.view, inverse);
        PSMTXMultVec(inverse, &query.normal, &hit->normal);
        PSVECNormalize(&hit->normal, &hit->normal);
        return query.hits;
    }
    return 0;
}

// .text:0x00004A24 size:0x3B4
void fn_1_4A24(ChallengeCollisionQuery* query, struct ChallengeCollisionMesh* mesh) {
    return;
}
