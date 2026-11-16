#include "Unknown/gap_8000F8F4.h"

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(Gap8000F8F4Range* range) {
    s32 first = range->first;
    s32 i;
    s32 j;
    for (i = 0; i < range->count; i++) {
        if (lbl_80371C30[first + i].object != NULL && (lbl_80371C30[first + i].object->flags & 4)) {
            for (j = 0; j < 30; j++) {
                if (lbl_80366B18.slots[j].object == lbl_80371C30[first + i].object) {
                    lbl_80366B18.slots[j].object = NULL;
                    break;
                }
            }
        }
    }
}

// .text:0x8000F988 size:0x114
void fn_8000F988(void) {
    return;
}

// .text:0x8000FA9C size:0x2B8
void fn_8000FA9C(void) {
    return;
}

// .text:0x8000FD54 size:0x24
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d) {
    lbl_80366B18.entries[index].unk20 = a;
    lbl_80366B18.entries[index].unk22 = b;
    lbl_80366B18.entries[index].unk24 = c;
    lbl_80366B18.entries[index].unk26 = d;
}

// .text:0x8000FD78 size:0x24
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d) {
    lbl_80366B18.entries[index].unk18 = a;
    lbl_80366B18.entries[index].unk1A = b;
    lbl_80366B18.entries[index].unk1C = c;
    lbl_80366B18.entries[index].unk1E = d;
}

// .text:0x8000FD9C size:0x6C
void fn_8000FD9C(s32 index, s32 flag, s32 state) {
    if (flag == 0) {
        lbl_80366B18.entries[index].state = -1;
        lbl_80366B18.entries[index].unk31 = 0;
        lbl_80366B18.entries[index].unk32 = 0;
        return;
    }
    if (state >= 0) {
        lbl_80366B18.entries[index].state = state;
    }
    lbl_80366B18.entries[index].unk31 = flag;
    lbl_80366B18.entries[index].unk32 = 0;
}

// .text:0x8000FE08 size:0x4C
void fn_8000FE08(s32 index, s32 table, s32 value) {
    Gap8000F8F4Entry* entry = &lbl_80366B18.entries[index];
    entry->data = lbl_80366B18.tables[table]->values[value];
    if (entry->state >= 0) {
        entry->state = 0;
        entry->flags34 = 0;
        entry->flags35 = 0;
    }
}

// .text:0x8000FE54 size:0x94
void fn_8000FE54(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].unk2A = 0;
    }
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(s32 index) {
    lbl_80366B18.entries[index].unk2A = 0;
}

// .text:0x8000FF04 size:0x1A0
void fn_8000FF04(void) {
    return;
}

// .text:0x800100A4 size:0x3F4
void fn_800100A4(void) {
    return;
}

// .text:0x80010498 size:0xA94
#pragma dont_inline on
void DrawText(s32 index) {
    return;
}
#pragma dont_inline reset

// .text:0x80010F2C size:0x74
void DrawTextOnCondition(s32 condition) {
    s32 i;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].unk2A == 2 && condition == lbl_80366B18.entries[i].condition) DrawText(i);
    }
}

// .text:0x80010FA0 size:0x60
// Binds the loaded text file (tables[0]): tables[7] points at its word array, four of the
// words are cached in the state, and the u16 list its word 7 points to is copied to
// lbl_80366218 up to the 0x4001 end mark.
void fn_80010FA0(void) {
    /* Non-matching: registers (state base r5 / table r4 swapped) and the copy destination's
       address is formed before the stores in the target. */
    Gap8000F8F4Table* table = lbl_80366B18.tables[0];
    u16* dst;
    u16* src;

    lbl_80366B18.tables[7] = (Gap8000F8F4Table*)table->values;
    lbl_80366B18.unk7EC = table->values[1];
    lbl_80366B18.unk7F0 = table->values[2];
    lbl_80366B18.unk7F8 = table->values[6];
    lbl_80366B18.unk7F4 = table->values[5];
    src = (u16*)lbl_80366B18.tables[7]->values[6];
    dst = lbl_80366218;
    while (1) {
        if (*src == 0x4001) {
            return;
        }
        *dst = *src;
        src++;
        dst++;
    }
}

// .text:0x80011000 size:0x140
void fn_80011000(void) {
    return;
}

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].unk2A = 0;
        lbl_80366B18.slots[i].value = 0;
    }
    lbl_80366B18.flag7FE = 0;
}

// Relocate each resource pointer in a packed menu archive.
// .text:0x800111B4 size:0x24
void fn_800111B4(MenuPointerArchive* archive) {
    s32 count = archive->count;
    u8** entry = archive->entries;
    do {
        *entry = (u8*)((u32)*entry + (u32)archive);
        entry++;
    } while (--count != 0);
}

// .text:0x800111D8 size:0x24
// Address of the model pointer of a slot record's actor block.
Gap8000F8F4Model** fn_800111D8(Gap8000F8F4ActorSlot* slot) {
    return &g_hugeAnimStruct.blocks[slot->blockIndex].model;
}

// .text:0x800111FC size:0x15C
void fn_800111FC(void) {
    return;
}

// .text:0x80011358 size:0x110
// Puts held item `item` (0..3) on bone 36 of the actor in `slotKind`, or takes it off (4, also
// used for any other value): the item is the first bone with an attachment of the model in
// entry 21 + item of the second actor block.
void fn_80011358(s32 slotKind, s32 item) {
    Gap8000F8F4ActorSlot* slot;
    Gap8000F8F4Block* blocks;
    Gap8000F8F4Block* blocks64;
    Gap8000F8F4Model** model;
    Gap8000F8F4Model* other;
    u16 boneIndex;
    s32 i;

    if (slotKind < 0 || slotKind >= 13) {
        return;
    }
    slot = g_hugeAnimStruct.slots[slotKind];
    if (slot == NULL) {
        return;
    }
    if ((blocks = g_hugeAnimStruct.blocks) == NULL || (blocks64 = g_hugeAnimStruct.blocks64) == NULL) {
        return;
    }
    boneIndex = slot->boneIndices[36];
    if (boneIndex == 0xFFFF) {
        return;
    }
    if (item < 0 || item >= 5) {
        item = 4;
    }
    model = &blocks[slot->blockIndex].model;
    if (item == 4) {
        fn_800B2BA8(*model, boneIndex, NULL, 0);
        return;
    }
    other = blocks64[21 + item].model;
    for (i = 0; i < other->totalBones; i++) {
        if (other->boneArray[i]->attachment != 0) {
            fn_800B2BA8(*model, boneIndex, other, i);
            return;
        }
    }
}

// .text:0x80011468 size:0x108
// Per-frame special handling by character over the 13 actor slots: effect / state updates for
// Bowser Jr., the Goombas, Petey, Monty and the Boos, and the model's byte +0x99 for Yoshi,
// Wario, the Koopas and Nokis (set) and the Paratroopas (clear while animation 0x40 plays).
void fn_80011468(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        Gap8000F8F4ActorSlot* anim = g_hugeAnimStruct.slots[i];
        Gap8000F8F4Model** model;

        if (anim == NULL) {
            continue;
        }
        model = &g_hugeAnimStruct.blocks[anim->blockIndex].model;
        switch (anim->charID) {
        case CHAR_ID_BOWSERJR:
            fn_8004B6EC(anim, model);
            break;
        case CHAR_ID_GOOMBA:
        case CHAR_ID_PARAGOOMBA:
            fn_8004B7F4(anim, model);
            break;
        case CHAR_ID_PETEY:
            (*model)->unk99 = 1;
            /* fallthrough */
        case CHAR_ID_MONTY:
            fn_8004BAEC(anim, model);
            break;
        case CHAR_ID_BOO:
        case CHAR_ID_KINGBOO:
            fn_8005240C(anim, model);
            break;
        case CHAR_ID_YOSHI:
        case CHAR_ID_WARIO:
        case CHAR_ID_KOOPA_GREEN:
        case CHAR_ID_NOKI_BLUE:
        case CHAR_ID_NOKI_RED:
        case CHAR_ID_NOKI_GREEN:
        case CHAR_ID_KOOPA_RED:
            (*model)->unk99 = 1;
            break;
        case CHAR_ID_PARATROOPA_RED:
        case CHAR_ID_PARATROOPA_GREEN:
            if (anim->animID == 0x40) {
                (*model)->unk99 = 0;
            } else {
                (*model)->unk99 = 1;
            }
            break;
        }
    }
}

// .text:0x80011570 size:0x8
s32 fn_80011570(void) {
    return lbl_803CBC18;
}

// .text:0x80011578 size:0x50
/* Clears the callback of actor slot `id` (0..12) if it is live. */
static inline void clearSlotCallback(s8 id) {
    if (id < 0) {
        return;
    }
    if (id >= 13) {
        return;
    }
    if (g_hugeAnimStruct.slots[id] == NULL) {
        return;
    }
    g_hugeAnimStruct.slots[id]->callback = NULL;
}

// Clears the callback of every live actor slot.
void fn_80011578(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        clearSlotCallback(i);
    }
}

// .text:0x800115C8 size:0x3C
// Clears the callback of actor slot `id` (0..12) if it is live.
void fn_800115C8(s8 id) {
    clearSlotCallback(id);
}

// .text:0x80011604 size:0x3C
// Sets the callback of actor slot `id` (0..12) if it is live.
void fn_80011604(s8 id, void* callback) {
    Gap8000F8F4ActorSlot* slot;

    if (id < 0) {
        return;
    }
    if (id >= 13) {
        return;
    }
    slot = g_hugeAnimStruct.slots[id];
    if (slot != NULL) {
        slot->callback = callback;
    }
}

// .text:0x80011640 size:0x9C
void fn_80011640(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* dst) {
    Gap8000F8F4Mtx mtx = lbl_800E6630;

    PSMTXConcat(&mtx, src, dst);
}

// .text:0x800116DC size:0xF0
// Billboards one bone: replaces the bone's matrix with the inverse rotation of `view` (stretched
// by lbl_800E6600) at the bone's current translation.
void fn_800116DC(Gap8000F8F4Model** model, Gap8000F8F4Mtx* view, u16 boneIndex) {
    Gap8000F8F4Mtx result;
    Gap8000F8F4Mtx mtx = lbl_800E6600;
    Gap8000F8F4Mtx* boneMatrix;

    PSMTXConcat(&mtx, view, &result);
    result.m[0][3] = 0.0f;
    result.m[1][3] = 0.0f;
    result.m[2][3] = 0.0f;
    PSMTXInverse(&result, &result);
    boneMatrix = (*model)->boneArray[boneIndex]->matrix;
    result.m[0][3] = boneMatrix->m[0][3];
    result.m[1][3] = boneMatrix->m[1][3];
    result.m[2][3] = boneMatrix->m[2][3];
    PSMTXCopy(&result, boneMatrix);
}

// .text:0x800117CC size:0xE0
// Billboard matrix: the inverse rotation of `view` (with the 1.0714 vertical stretch of
// lbl_800E6600) placed at the translation of `position`.
void fn_800117CC(Gap8000F8F4Mtx* position, Gap8000F8F4Mtx* view, Gap8000F8F4Mtx* out) {
    Gap8000F8F4Mtx result;
    Gap8000F8F4Mtx mtx = lbl_800E6600;

    PSMTXConcat(&mtx, view, &result);
    result.m[0][3] = 0.0f;
    result.m[1][3] = 0.0f;
    result.m[2][3] = 0.0f;
    PSMTXInverse(&result, &result);
    result.m[0][3] = position->m[0][3];
    result.m[1][3] = position->m[1][3];
    result.m[2][3] = position->m[2][3];
    PSMTXCopy(&result, out);
}

// .text:0x800118AC size:0xC0
Gap8000F8F4Mtx* fn_800118AC(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* dst) {
    Gap8000F8F4Mtx mtx = lbl_800E6600;

    PSMTXConcat(&mtx, src, dst);
    dst->m[0][3] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[2][3] = 0.0f;
    PSMTXInverse(dst, dst);
    return dst;
}
