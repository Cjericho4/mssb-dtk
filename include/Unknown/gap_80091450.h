#ifndef __UNKNOWN_gap_80091450_H_
#define __UNKNOWN_gap_80091450_H_

#include "mssbTypes.h"
typedef struct Gap80091450Entry {
    /* 0x0 */ s32 unk0;
    u8 _pad4[0x4];
} Gap80091450Entry;
typedef struct Gap80091450Tex {
    u8 _pad0[0x8];
    /* 0x8 */ Gap80091450Entry* entries;
} Gap80091450Tex;
typedef struct Gap80091450Tree {
    /* 0x0 */ s32 size;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} Gap80091450Tree;

Gap80091450Entry* TEXGet(Gap80091450Tex* tex, s32 index);
void DSInitList(Gap80091450Tree* list, s32 start, s32 end);
void DSInsertListObject(void);
void Strcmp(void);
void DSInitTree(Gap80091450Tree* tree, s32 start, s32 end);
void DSInsertBranchBelow(void);

#endif // !__UNKNOWN_gap_80091450_H_
