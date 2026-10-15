#ifndef __GAME_gap_BA150_H_
#define __GAME_gap_BA150_H_

#include "mssbTypes.h"
#include "game/rep_1E08.h"

typedef struct BA150Node {
    struct BA150Node* next; // 0x00
    u8 _pad4[0x8];
    f32 sortKey;            // 0x0C
} BA150Node;

typedef struct {
    BA150Node* node; // 0x00
    f32 sortKey;     // 0x04
} BA150SortItem;

void fn_3_BA150(void);
s32 fn_3_BA174(BA150SortItem* a, BA150SortItem* b);
BA150Node* fn_3_BA1A0(BA150Node* list, u32 count);
void fn_3_BA268(void);
void fn_3_BA3EC(void);

#endif // !__GAME_gap_BA150_H_
