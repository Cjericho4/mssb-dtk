#include "Unknown/gap_8002244C.h"

/* inline copy of fn_80022CB4 (defined later in this unit, so -inline auto cannot pick it up) */
static inline BOOL queueLoadInline(Gap8002244CDiskDesc* desc, void* dest, s32 mode, void* aramAddr,
                                   Gap8002244CLoadCallback callback, s32 param) {
    Gap8002244CRecord* rec;
    s8 next = (lbl_803716B8.flag1C8 + 1) % 18;
    if (next == lbl_803716B8.flag1C9 || (dest == NULL && callback == NULL)) {
        return FALSE;
    }
    lbl_803716B8.pending1CA = 1;
    rec = &lbl_803716B8.recs[lbl_803716B8.flag1C8];
    rec->desc = desc;
    rec->dest = dest;
    rec->mode = mode;
    rec->aramAddr = aramAddr;
    rec->callback = callback;
    rec->param = param;
    lbl_803716B8.flag1C8 = next;
    return TRUE;
}

// .text:0x8002244C size:0x100
void fn_8002244C(s32 arg0, Gap8002244CLoadBlock* block, s32 packedID) {
    s32 charID = packedID >> 16;
    u16 itemID = packedID;
    s32 sizeIdx = MASTER_DESC_SUBITEM_BASE + charID;
    Gap8002244CDiskDesc* sizeDesc = &lbl_800EFD38[sizeIdx];
    u32 size = ((sizeDesc->sizeFlags & 0x0FFFFFFF) + 0x1F) & ~0x1F;

    block->size = size;
    block = (Gap8002244CLoadBlock*)(size + (u32)block);
    queueLoadInline(&lbl_800EFD38[MASTER_DESC_SUBITEM_BASE + itemID], block, 3, lbl_803716B8.subItemAramAddrs[itemID],
                    fn_80022620, 0);
}

// .text:0x8002254C size:0xD4
void fn_8002254C(void) {
    return;
}

// .text:0x80022620 size:0x14
void fn_80022620(s32 arg0, Gap8002244CLoadBlock* block, s32 packedID) {
    lbl_803716B8.unk1E8 = 0;
}

// .text:0x80022634 size:0x16C
void fn_80022634(void) {
    return;
}

// .text:0x800227A0 size:0x44
void fn_800227A0(void) {
    u8 flags = lbl_803716B8.flags;
    lbl_803716B8.unk1E9 = 0;
    lbl_803716B8.flags = flags | 1;
    lbl_803716B8.flags |= 2;
    lbl_803716B8.flags |= 4;
    lbl_803716B8.flags |= 8;
}

// .text:0x800227E4 size:0x1E8
void fn_800227E4(void) {
    return;
}

// .text:0x800229CC size:0x58
void fn_800229CC(void) {
    if (lbl_803716B8.pending != 0) {
        fn_800A7568();
    } else if (lbl_803716B8.current != 0) {
        lbl_803716B8.current = 0;
    } else {
        return;
    }
    fn_800A6304();
}

// .text:0x80022A24 size:0xF0
void fn_80022A24(void) {
    return;
}

// .text:0x80022B14 size:0x54
void fn_80022B14(void) {
    s32 complete = lbl_803C6CF8.complete;
    if (complete == 1) {
        if (lbl_803716B8.pending != 0) {
            lbl_803716B8.current = lbl_803716B8.pending;
            lbl_803716B8.pending = 0;
        }
        fn_800B0A14_removeQueue();
    }
}

// .text:0x80022B68 size:0x14C
void fn_80022B68(void) {
    return;
}

// .text:0x80022CB4 size:0xA4
BOOL fn_80022CB4(Gap8002244CDiskDesc* desc, void* dest, s32 mode, void* aramAddr, Gap8002244CLoadCallback callback,
                 s32 param) {
    Gap8002244CRecord* rec;
    s8 next = (lbl_803716B8.flag1C8 + 1) % 18;
    if (next == lbl_803716B8.flag1C9 || (dest == NULL && callback == NULL)) {
        return FALSE;
    }
    lbl_803716B8.pending1CA = 1;
    rec = &lbl_803716B8.recs[lbl_803716B8.flag1C8];
    rec->desc = desc;
    rec->dest = dest;
    rec->mode = mode;
    rec->aramAddr = aramAddr;
    rec->callback = callback;
    rec->param = param;
    lbl_803716B8.flag1C8 = next;
    return TRUE;
}

// .text:0x80022D58 size:0x54
void fn_80022D58(void) {
    lbl_803716B8.flag1C8 = lbl_803716B8.flag1C9 = 0;
    memset(lbl_803716B8.header, 0, 0x18);
    memset(lbl_803716B8.records, 0, 0x1B0);
}

#pragma dont_inline on
// .text:0x80022DAC size:0x2CC
void f_InitBone(ActBone* parent, ActBoneLayout* layout, GameActor* actor, u16* numBones, ActMemBlock* mtxMem, ActMemBlock* boneMem) {
    return;
}
#pragma dont_inline off

#pragma dont_inline on
// .text:0x80023078 size:0x268
ActMemBlock* fn_80023078(ActDisplayObj* obj, ActDOLayout* layout, ActMemBlock* mem) {
    return;
}
#pragma dont_inline off

// .text:0x800232E0 size:0x32C
GameActor* f_InitActorWithLayout(ActLayout* layout, ActMemBlock* mem) {
    return;
}

#pragma dont_inline on
// .text:0x8002360C size:0x2D4
void BuildBoneSkinOrientationMatrix(ActBone* root, Mtx m) {
    return;
}
#pragma dont_inline off

// .text:0x800238E0 size:0xBC
void fn_800238E0(void) {
    return;
}

// .text:0x8002399C size:0x108
void fn_8002399C(void) {
    return;
}

// .text:0x80023AA4 size:0x60
void fn_80023AA4(void) {
    u32 i;
    lbl_8017EB40[0] = _OSAllocFromHeap(32, 28 * sizeof(Gap8002244CActor));
    i = 1;
    do {
        lbl_8017EB40[i] = lbl_8017EB40[i - 1] + 1;
    } while (++i < 28);
    ActorObjectInitTable(28);
}

// .text:0x80023B04 size:0x8C
void fn_80023B04(void) {
    return;
}

// .text:0x80023B90 size:0x164
void fn_80023B90(void) {
    return;
}

// .text:0x80023CF4 size:0x48
void fn_80023CF4(BOOL enabled) {
    if (enabled) {
        OSSetProgressiveMode(1);
        fn_800A7E00();
    } else {
        OSSetProgressiveMode(0);
    }
    lbl_803CBC60 = enabled;
}

// .text:0x80023D3C size:0x8
s32 fn_80023D3C(void) {
    return lbl_803CBC60;
}

// .text:0x80023D44 size:0x8
void fn_80023D44(s32 value) {
    lbl_803CBC60 = value;
}

// .text:0x80023D4C size:0x4C
BOOL fn_80023D4C(Gap8002244CObj* obj, Gap8002244CVector* out) {
    if (obj->unk8 != 0) {
        obj->current = obj->unk10;
        *out = obj->vectors[obj->current];
        return 1;
    }
    return 0;
}

// .text:0x80023D98 size:0x64
static inline s32 previousSlot(s32 count) { return count - 1; }
BOOL fn_80023D98(Gap8002244CObj* obj, Gap8002244CVector* out) {
    s32 current = obj->current;
    if (current == obj->unk10) return 0;
    obj->current = (current + previousSlot(obj->unk4)) % obj->unk4;
    *out = obj->vectors[obj->current];
    return 1;
}

// .text:0x80023DFC size:0x4C
BOOL fn_80023DFC(Gap8002244CObj* obj, Gap8002244CVector* out) {
    if (obj->unk8 != 0) {
        obj->current = obj->unkC;
        *out = obj->vectors[obj->current];
        return 1;
    }
    return 0;
}

// .text:0x80023E48 size:0xA4
void fn_80023E48(Gap8002244CObj* obj, Gap8002244CVector* v) {
    obj->unkC = (obj->unkC + obj->unk18) % obj->unk4;
    if (obj->unk10 == obj->unkC) {
        obj->unk10 = (obj->unk10 + obj->unk18) % obj->unk4;
    }
    obj->unk18 = 1;
    obj->vectors[obj->unkC] = *v;
    obj->unk8 += (obj->unk8 < obj->unk4);
}

// .text:0x80023EEC size:0x20
void fn_80023EEC(Gap8002244CObj* obj, s32 a, s32 b) {
    obj->unk0 = a;
    obj->unk4 = b;
    obj->unk8 = 0;
    obj->unkC = 0;
    obj->unk10 = 0;
    obj->unk18 = 0;
}

// .text:0x80023F0C size:0x278
void fn_80023F0C(void) {
    return;
}

// .text:0x80024184 size:0x20C
void gOz_GXSetTexture(void) {
    return;
}

// .text:0x80024390 size:0x74
void fn_80024390(f32 m[3][4], Gap8002244CProjParams* out, s32 type) {
    s32 col = (type == 0) ? 2 : 3;
    out->type = type;
    out->m00 = m[0][0];
    out->m0x = m[0][col];
    out->m11 = m[1][1];
    out->m1x = m[1][col];
    out->m22 = m[2][2];
    out->m23 = m[2][3];
}

// .text:0x80024404 size:0x1E8
void SetDisplayStateTexture(void) {
    return;
}

// .text:0x800245EC size:0xE8
void fn_800245EC(void) {
    return;
}

// .text:0x800246D4 size:0x110
void fn_800246D4(void) {
    return;
}

// .text:0x800247E4 size:0x5C
void fn_800247E4(void) {
    return;
}

// .text:0x80024840 size:0x134
void challengeStarRelatedInd(void) {
    return;
}

// .text:0x80024974 size:0x64
void multBottomBits_asFloat(void) {
    return;
}

// .text:0x800249D8 size:0x128
void byteWiseMultiply(void) {
    return;
}

// .text:0x80024B00 size:0xB4
void LERPToNewRange_Float(void) {
    return;
}

// .text:0x80024BB4 size:0x50
f32 LinearInterpolateToNewRange(f32 x, f32 inMin, f32 inMax, f32 outMin, f32 outMax) {
    f32 range = inMax - inMin;
    f32 outRange;
    f32 t;
    if (range == 0.0f) {
        t = 1.0f;
    } else {
        t = ((x - inMin) / range > 1.0f) ? 1.0f : (((x - inMin) / range < 0.0f) ? 0.0f : (x - inMin) / range);
    }
    outRange = outMax - outMin;
    return outRange * t + outMin;
}

// .text:0x80024C04 size:0x68
BOOL fn_80024C04(s32 index) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (lbl_803CB748[i] == lbl_800E8558[index].id) {
            if (g_d_GameSettings.unlocked[i] == 0) {
                return FALSE;
            }
            break;
        }
    }
    return TRUE;
}

// .text:0x80024C6C size:0xC0
void fn_80024C6C(void) {
    return;
}

// .text:0x80024D2C size:0x84
u32 fn_80024D2C(Gap8002244CKeyAnimation* animation) {
    Gap8002244CKeyTrack* track = &animation->tracks[animation->trackIndex];
    s32 i = track->count;
    while (i-- != 0) {
        if ((f32)(u32)(track->keys[i].time & 0xFFF) <= animation->time) {
            return track->keys[i].word & 0xF0000000;
        }
    }
    return 0;
}

// .text:0x80024DB0 size:0x1F4
void fn_80024DB0(void) {
    return;
}

// .text:0x80024FA4 size:0xCB4
void fn_80024FA4(void) {
    return;
}

// .text:0x80025C58 size:0x184
void fn_80025C58(void) {
    return;
}
