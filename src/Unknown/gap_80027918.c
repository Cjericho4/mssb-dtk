#include "Unknown/gap_80027918.h"

// .text:0x80027918 size:0x50
void fn_80027918(void) {
    return;
}

// .text:0x80027968 size:0xBC4
void fn_80027968(void) {
    return;
}

// .text:0x8002852C size:0xFC
void fn_8002852C(void) {
    return;
}

// .text:0x80028628 size:0x920
void fn_80028628(void) {
    return;
}

// .text:0x80028F48 size:0x614
void fn_80028F48(void) {
    return;
}

// .text:0x8002955C size:0x294
void fn_8002955C(void) {
    return;
}

// .text:0x800297F0 size:0x4D8
void fn_800297F0(void) {
    return;
}

// .text:0x80029CC8 size:0x504
void fn_80029CC8(void) {
    return;
}

// .text:0x8002A1CC size:0x690
void fn_8002A1CC(void) {
    return;
}

// .text:0x8002A85C size:0x40C
void fn_8002A85C(void) {
    return;
}

// .text:0x8002AC68 size:0x3AC
void fn_8002AC68(void) {
    return;
}

// .text:0x8002B014 size:0x3EC
void fn_8002B014(void) {
    return;
}

// .text:0x8002B400 size:0x3F8
void fn_8002B400(void) {
    return;
}

// .text:0x8002B7F8 size:0x48C
void fn_8002B7F8(void) {
    return;
}

// .text:0x8002BC84 size:0x64C
void fn_8002BC84(void) {
    return;
}

// .text:0x8002C2D0 size:0x29C
void fn_8002C2D0(void) {
    return;
}

// .text:0x8002C56C size:0x864
void fn_8002C56C(void) {
    return;
}

// .text:0x8002CDD0 size:0x7C
void fn_8002CDD0(Gap80027918Vec* v) {
    Gap80027918Node* node = (Gap80027918Node*)&lbl_803CBC84;

    while ((node = node->next) != NULL) {
        if (node->type == 10) {
            break;
        }
    }
    if (node != NULL && node->unk40 != 0) {
        node->prevPos.x = v->x;
        node->prevPos.y = v->y;
        node->prevPos.z = v->z;
        PSVECSubtract(&node->prevPos, &node->pos, &node->delta);
    }
}

// .text:0x8002CE4C size:0x9E0
void fn_8002CE4C(void) {
    return;
}

// .text:0x8002D82C size:0x43C
void fn_8002D82C(void) {
    return;
}

// .text:0x8002DC68 size:0x7C
void fn_8002DC68(Gap80027918Vec* v) {
    Gap80027918Node* node = (Gap80027918Node*)&lbl_803CBC84;

    while ((node = node->next) != NULL) {
        if (node->type == 9) {
            break;
        }
    }
    if (node != NULL) {
        memcpy(&node->prevPos, &node->pos, sizeof(Gap80027918Vec));
        memcpy(&node->pos, v, sizeof(Gap80027918Vec));
    }
}

// .text:0x8002DCE4 size:0x6F8
void fn_8002DCE4(void) {
    return;
}

// .text:0x8002E3DC size:0x44C
void fn_8002E3DC(void) {
    return;
}

// .text:0x8002E828 size:0x478
void fn_8002E828(void) {
    return;
}

// .text:0x8002ECA0 size:0x50C
void fn_8002ECA0(void) {
    return;
}

// .text:0x8002F1AC size:0xAC
BOOL fn_8002F1AC(Gap80027918Vec* v, s32 id) {
    Gap80027918Node* node = (Gap80027918Node*)&lbl_803CBC84;
    Gap80027918Item* item;

    while ((node = node->next) != NULL) {
        if (node->type == 6) {
            break;
        }
    }
    if (node != NULL && lbl_80366158.mode == 0) {
        for (item = node->items; item != NULL; item = item->next) {
            if (item->id == id) {
                memcpy(&item->pos, v, sizeof(Gap80027918Vec));
                item->count++;
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x8002F258 size:0x39C
void fn_8002F258(void) {
    return;
}

// .text:0x8002F5F4 size:0x408
void fn_8002F5F4(void) {
    return;
}

// .text:0x8002F9FC size:0x3BC
void fn_8002F9FC(void) {
    return;
}

// .text:0x8002FDB8 size:0x6B8
void fn_8002FDB8(void) {
    return;
}

// .text:0x80030470 size:0x2B0
void fn_80030470(void) {
    return;
}

// .text:0x80030720 size:0x668
void fn_80030720(void) {
    return;
}

// .text:0x80030D88 size:0x2AC
void fn_80030D88(void) {
    return;
}

// .text:0x80031034 size:0x790
void fn_80031034(void) {
    return;
}

// .text:0x800317C4 size:0x4E0
void fn_800317C4(void) {
    return;
}

// .text:0x80031CA4 size:0x290
void fn_80031CA4(void) {
    return;
}

// .text:0x80031F34 size:0x104
void fn_80031F34(void) {
    return;
}
