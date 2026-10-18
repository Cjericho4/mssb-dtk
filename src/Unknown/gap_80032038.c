#include "Unknown/gap_80032038.h"

// .text:0x80032038 size:0x2C
s32 fn_80032038(Gap80032038SortEntry* a, Gap80032038SortEntry* b) {
    if (a->key > b->key) return 1;
    if (a->key < b->key) return -1;
    return 0;
}

// .text:0x80032064 size:0x220
void fn_80032064(void) {
    return;
}

// .text:0x80032284 size:0x268
void fn_80032284(void) {
    return;
}

// .text:0x800324EC size:0x3F4
void fn_800324EC(void) {
    return;
}

// .text:0x800328E0 size:0x7EC
void fn_800328E0(void) {
    return;
}

// .text:0x800330CC size:0x1EC
void fn_800330CC(void) {
    return;
}

// .text:0x800332B8 size:0x304
void fn_800332B8(void) {
    return;
}

// .text:0x800335BC size:0x30
f32 fn_800335BC(s32 angle) {
    s32 index = __abs(angle) & 0x7FF;
    if (index >= 0x401) index = 0x800 - index;
    return lbl_8017ED68[index];
}

// .text:0x800335EC size:0x34
f32 fn_800335EC(s32 angle) {
    s32 index = __abs(angle + 0x600) & 0x7FF;
    if (index >= 0x401) index = 0x800 - index;
    return lbl_8017ED68[index];
}

// .text:0x80033620 size:0x174
void fn_80033620(void) {
    return;
}

// .text:0x80033794 size:0x38
void fn_80033794(Gap80032038Chain* head) {
    Gap80032038Chain* tail = head;
    while (tail != NULL && tail->next != NULL) tail = tail->next;
    if (tail != NULL) {
        tail->next = lbl_803CBC74;
        lbl_803CBC74 = head;
    }
}

// .text:0x800337CC size:0x90
void fn_800337CC(void) {
    return;
}

// .text:0x8003385C size:0xCC
void pitchingMachinePitching(void) {
    return;
}

// .text:0x80033928 size:0x3C
BOOL fn_80033928(u8 id) {
    Gap80032038Obj* obj;
    for (obj = lbl_803CBC84.next; obj != NULL; obj = obj->next) {
        if (obj->id == id) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x80033964 size:0x8C
void fn_80033964(void) {
    return;
}

// .text:0x800339F0 size:0x34
Gap80032038Obj* fn_800339F0(Gap80032038Obj* obj, u8 id) {
    if (obj == NULL) {
        obj = (Gap80032038Obj*)&lbl_803CBC84;
    }
    while ((obj = obj->next) != NULL) {
        if (obj->id == id) {
            break;
        }
    }
    return obj;
}

// .text:0x80033A24 size:0x134
void fn_80033A24(void) {
    return;
}

// .text:0x80033B58 size:0x170
void fn_80033B58(void) {
    return;
}

// .text:0x80033CC8 size:0x29C
void fn_80033CC8(void) {
    return;
}

// .text:0x80033F64 size:0xD8
void fn_80033F64(void) {
    return;
}

// .text:0x8003403C size:0xB8
void fn_8003403C(void) {
    return;
}

// .text:0x800340F4 size:0x2C
void fn_800340F4(f32 matrix[3][4]) {
    PSMTXCopy(lbl_8017FF78, matrix);
}

// .text:0x80034120 size:0x2C
void fn_80034120(f32 matrix[3][4]) {
    PSMTXCopy(lbl_8017FFE0, matrix);
}

// .text:0x8003414C size:0xD4
void fn_8003414C(void) {
    return;
}

// .text:0x80034220 size:0x30C
void minigamesSetSomePointers(void) {
    return;
}

// .text:0x8003452C size:0x39C
void minigamesGXStuff(void) {
    return;
}

// .text:0x800348C8 size:0x304
void minigamesSetSomePointers2(void) {
    return;
}

// .text:0x80034BCC size:0x120
void fn_80034BCC(void) {
    return;
}

// .text:0x80034CEC size:0x134
void fn_80034CEC(void) {
    return;
}

// .text:0x80034E20 size:0x130
void fn_80034E20(void) {
    return;
}

// .text:0x80034F50 size:0x218
void fn_80034F50(void) {
    return;
}

// .text:0x80035168 size:0x550
void fn_80035168(void) {
    return;
}

// .text:0x800356B8 size:0x98
void fn_800356B8(void) {
    return;
}

// .text:0x80035750 size:0xE8
void fn_80035750(void) {
    return;
}

// .text:0x80035838 size:0x1C8
void fn_80035838(void) {
    return;
}

// .text:0x80035A00 size:0x150
void fn_80035A00(void) {
    return;
}

// .text:0x80035B50 size:0x154
void fn_80035B50(void) {
    return;
}

// .text:0x80035CA4 size:0x130
void fn_80035CA4(void) {
    return;
}
