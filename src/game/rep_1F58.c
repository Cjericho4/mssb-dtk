#include "game/rep_1F58.h"
#include "game/rep_1E08.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/gx.h"
#include <string.h>

extern GXTexObj lbl_3_bss_9D20;
extern u8 lbl_3_bss_9D40[0x40];
extern const f32 lbl_3_rodata_1FA8;

typedef struct {
    u8 _pad0[0x14];
    u32 unk14;     /* 0x14 */
    s32 slot;      /* 0x18 */
    s32 charIndex; /* 0x1C */
    u8 active;     /* 0x20 */
} RepC0854Obj;

typedef struct {
    s16 charIndex;
    u8 _pad2[0x1E];
} RepC0854Slot; /* size: 0x20 */

extern RepC0854Obj* lbl_3_data_174A0[2];
extern RepC0854Slot lbl_3_data_17260[18];
void fn_80027918(u8 id, f32 arg1);

typedef struct RepC095CEntry {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ void (*callback)(struct RepC095CEntry* entry);
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ u32 frames;
} RepC095CEntry; /* size: 0x18 */

extern RepC095CEntry lbl_3_data_174A8[2][2];
s32 fn_8005268C(void);
u32 fn_80024DB0(CommonBss32724Timer* timer);
void fn_80024FA4(AnimLevel1** anim, s32 arg1, CommonBss32724Timer* timer, s32 arg3);
void fn_800B4CA0(AnimLevel1* anim, f32 val);
void fn_800B4C04(AnimLevel1* anim, f32 val);
void fn_800BDA24(AnimLevel1** anim);
void fn_800BDA94(AnimLevel1** anim, Mtx mtx);
AnimationStruct* fn_80011570(s32 arg0);

// .text:0x000C0854 size:0x108 mapped:0x806FF8E8
void fn_3_C0854(void) {
    s32 i;
    s32 j;
    s16 id;
    AnimationStruct* anim;
    s32 sfx;

    for (i = 0; i < 2; i++) {
        if (lbl_3_data_174A0[i] != NULL) {
            lbl_3_data_174A0[i]->active = 1;
        }
        id = lbl_3_data_17260[i].charIndex;
        if (id >= 0) {
            j = 1;
            do {
                if (id == lbl_3_data_17260[j].charIndex) {
                    break;
                }
            } while (j-- != 0);
            if (j >= 0) {
                anim = g_hugeAnimStruct.AnimationStructPtrs[id];
                if (anim != NULL) {
                    anim->funcPtr_0x5c = NULL;
                }
                sfx = 0x18;
                lbl_3_data_17260[j].charIndex = -1;
                if (j != 0) {
                    sfx = 0x17;
                }
                fn_80027918(sfx, 0.0f);
            }
        }
    }
}

// .text:0x000C095C size:0x17C mapped:0x806FF9F0
void fn_3_C095C(RepC095CEntry* entry) {
    Mtx m;
    s32 ids[2];
    CommonBss32724Timer* timers[2];
    AnimLevel1** anim;
    s32 i;
    CommonBss32724Timer* t;

    anim = &lbl_3_common_bss_35154.unk10->unk34;
    ids[0] = lbl_3_common_bss_35154.unk40;
    timers[0] = &lbl_3_common_bss_35154.timer20;
    ids[1] = lbl_3_common_bss_35154.unk9C;
    timers[1] = &lbl_3_common_bss_35154.timer7C;
    PSMTXTrans(m, entry->x, entry->y, entry->z);
    PSMTXConcat(fn_80052734(fn_8005268C())->viewMtx, m, m);
    i = 1;
    do {
        t = timers[i];
        t->unk0 = 0.0f;
        t->unkC = 0;
        t->unk4 = entry->frames;
        fn_80024DB0(t);
        fn_80024FA4(anim, ids[i], timers[i], -1);
    } while (i-- != 0);
    (*anim)->unk99 = 1;
    fn_800B4CA0(*anim, entry->frames);
    fn_800B4C04(*anim, 1.0f);
    fn_800BDA24(anim);
    (*anim)->animFlags = 0xFF;
    fn_800BDA94(anim, m);
}

// .text:0x000C0AD8 size:0x174 mapped:0x806FFB6C
void fn_3_C0AD8(void) {
    RepC0854Obj* obj = (RepC0854Obj*)lbl_803CC1B8;
    AnimationStruct* anim = g_hugeAnimStruct.AnimationStructPtrs[obj->charIndex];

    if (obj->active == 0 && anim != NULL) {
        fn_800A7D4C(0, (BdcArrayElement*)&lbl_3_data_174A8[obj->slot][lbl_803CBBC0]);
        lbl_3_data_174A8[obj->slot][lbl_803CBBC0].frames = obj->unk14;
        lbl_3_data_174A8[obj->slot][lbl_803CBBC0].x = anim->unk34.x;
        lbl_3_data_174A8[obj->slot][lbl_803CBBC0].y = anim->unk34.y;
        lbl_3_data_174A8[obj->slot][lbl_803CBBC0].z = anim->unk34.z;
        if (lbl_80366158._28 == 0) {
            obj->unk14++;
        }
    } else {
        lbl_3_data_174A0[obj->slot] = NULL;
        fn_800B0A14_removeQueue();
    }
    if (obj->unk14 >= lbl_3_common_bss_35154.timer20.unk18) {
        lbl_3_data_174A0[obj->slot] = NULL;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000C0C4C size:0x9C mapped:0x806FFCE0
void fn_3_C0C4C(s32 idx) {
    RepC0854Obj* obj = (RepC0854Obj*)fn_800B0A5C_insertQueue(fn_3_C0AD8, 1);

    obj->unk14 = 0;
    obj->charIndex = lbl_3_data_17260[idx].charIndex;
    obj->active = 0;
    for (idx = 0; idx < 2; idx++) {
        if (lbl_3_data_174A0[idx] == NULL) {
            lbl_3_data_174A0[idx] = obj;
            obj->slot = idx;
            break;
        }
    }
}

// .text:0x000C0CE8 size:0x28 mapped:0x806FFD7C
void fn_3_C0CE8(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    u32 temp_mask = lbl_3_common_bss_35154.bitfield;
    
    lbl_3_common_bss_35154.unk_434 = arg0;
    temp_mask |= 0x100;
    lbl_3_common_bss_35154.unk_438 = arg1;
    lbl_3_common_bss_35154.unk_43C = arg2;
    lbl_3_common_bss_35154.unk_467 = arg3;
    lbl_3_common_bss_35154.bitfield = temp_mask;
}

// .text:0x000C0D10 size:0xC8 mapped:0x806FFDA4
void fn_3_C0D10(void) {
    return;
}

// .text:0x000C0DD8 size:0x1B4 mapped:0x806FFE6C
void fn_3_C0DD8(s32 arg0, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, u8* arg4, u8* arg5) {
    s32 j;
    s32 id;
    Mtx m;

    id = fn_80011570(arg0)->unk254;
    j = 1;
    do {
        if (id == lbl_3_data_17260[j].charIndex) {
            break;
        }
    } while (j-- != 0);
    if (j < 0) {
        return;
    }
    GXLoadTexObj(&lbl_3_bss_9D20, *map);
    memset(m, 0, sizeof(Mtx));
    m[0][3] = 0.0f;
    m[1][3] = j;
    GXLoadTexMtxImm(m, *map * 3 + GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, GX_TG_TEX0, *map * 3 + GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(*stage, *coord, *map, GX_COLOR0A0);
    GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    (*stage)++;
    (*map)++;
    (*arg5)++;
    (*arg4)++;
}

// .text:0x000C0F8C size:0x78 mapped:0x80700020
void fn_3_C0F8C(void) {
    GXInitTexObj(&lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
    GXInitTexObjLOD(&lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
}

// .text:0x000C1004 size:0x1C8 mapped:0x80700098
void fn_3_C1004(void) {
    return;
}

// .text:0x000C11CC size:0x178 mapped:0x80700260
void fn_3_C11CC(s32 arg0, s32 arg1) {
    return;
}

// .text:0x000C1344 size:0x42C mapped:0x807003D8
void fn_3_C1344(s32 arg0, BOOL arg1, f32 arg2, f32 arg3) {
    return;
}

// .text:0x000C1770 size:0x1C0 mapped:0x80700804
void fn_3_C1770(int arg0) {
    return;
}
