#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "game/rep_3880.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/rep_1838.h"
#include "Dolphin/mtx.h"
#include "game/rep_1E08.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/gx.h"
#include "C3/control.h"
#include "game/rep_1D58.h"
#include "game/rep_3310.h"

extern f32 lbl_3_data_21770[6];
extern Vec lbl_3_bss_B860[4];

typedef struct {
    u8 _pad0[0x8];
    s32 unk8;
    u8 _padC[0x24];
    s32 unk30;
    u8 _pad34[0x30];
} Struct_26E9C;
extern Struct_26E9C lbl_3_data_26E9C;
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Struct_26BDC;
extern Struct_26BDC lbl_3_data_26BDC;
extern Struct_26BDC lbl_3_data_26BEC;
extern Struct_26BDC lbl_3_data_26BFC;
f32 fn_3_119854(u32 index);
extern u8 lbl_3_data_26CB8[23];
s32 fn_8001B728(s32 index, u8 type, VecXYZ* out);
struct Struct_800339F0_Result* fn_800337CC(u8* buf, s32 size, s32 arg2);


// .text:0x0014737C size:0x3FC mapped:0x80786410
void fn_3_14737C(void) {
    return;
}

// .text:0x00147778 size:0x488 mapped:0x8078680C
void fn_3_147778(struct Struct_800339F0_Result* obj, struct Rep3880Source* src) {
    return;
}

// .text:0x00147C00 size:0xFC mapped:0x80786C94
void fn_3_147C00(struct Rep3880Source* src) {
    struct Struct_800339F0_Result* existing;
    struct Struct_800339F0_Result* created;
    ListNode_14B9F0* node;
    u8 buf[0x60];

    existing = fn_800339F0(0, 0x26);
    if (existing != NULL) {
        created = fn_800337CC(buf, lbl_3_data_26E9C.unk8 + lbl_3_data_26E9C.unk30, 1);
        if (created == NULL) {
            return;
        }
        fn_3_147778(created, src);
        for (node = existing->listHead; node->next != NULL; node = node->next) {
        }
        node->next = created->listHead;
        existing->count += created->count;
    } else {
        created = (struct Struct_800339F0_Result*)fn_80033A24(fn_3_14737C, 0x80, 0, lbl_3_data_26E9C.unk8 + lbl_3_data_26E9C.unk30, 1, 0x26);
        if (created != NULL) {
            fn_3_147778(created, src);
        }
    }
}

// .text:0x00147CFC size:0x100 mapped:0x80786D90
void fn_3_147CFC(struct Rep3880Source* src) {
    struct Struct_800339F0_Result* existing;
    struct Struct_800339F0_Result* created;
    ListNode_14B9F0* node;
    u8 buf[0x60];

    if (src == NULL) {
        return;
    }
    existing = fn_800339F0(0, 0x26);
    if (existing != NULL) {
        created = fn_800337CC(buf, lbl_3_data_26E9C.unk8 + lbl_3_data_26E9C.unk30, 1);
        if (created == NULL) {
            return;
        }
        fn_3_147778(created, src);
        for (node = existing->listHead; node->next != NULL; node = node->next) {
        }
        node->next = created->listHead;
        existing->count += created->count;
    } else {
        created = (struct Struct_800339F0_Result*)fn_80033A24(fn_3_14737C, 0x80, 0, lbl_3_data_26E9C.unk8 + lbl_3_data_26E9C.unk30, 1, 0x26);
        if (created != NULL) {
            fn_3_147778(created, src);
        }
    }
}

// .text:0x00147DFC size:0x24 mapped:0x80786E90
void fn_3_147DFC(void) {
    pitchingMachinePitching(0x25);
}

// .text:0x00147E20 size:0x174 mapped:0x80786EB4
void fn_3_147E20(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768(0)->mtx, 0);
    GXSetCurrentMtx(0);
}

// .text:0x00147F94 size:0x14C mapped:0x80787028
void fn_3_147F94(void) {
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

// .text:0x001480E0 size:0x174 mapped:0x80787174
void fn_3_1480E0(Rep3880DrawObj* obj) {
    s32 i;

    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(lbl_3_bss_B860[i].x, lbl_3_bss_B860[i].y, lbl_3_bss_B860[i].z);
        GXColor1u32(obj->frontColor);
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(lbl_3_bss_B860[i].x, lbl_3_bss_B860[i].y, lbl_3_bss_B860[i].z);
        GXColor1u32(obj->backColor);
    }
}

// .text:0x00148254 size:0x180 mapped:0x807872E8
void fn_3_148254(Rep3880DrawObj* obj, ListNode_14B9F0* node) {
    Control ctrl;
    Mtx m;
    Vec v;
    f32 w;
    f32 h;
    f32 half;
    AnimationStruct* anim;

    half = 0.5f;
    w = node->scaleX * half;
    h = node->scaleY * half;
    anim = g_hugeAnimStruct.AnimationStructPtrs[obj->animIdx];
    lbl_3_bss_B860[0].x = -w;
    lbl_3_bss_B860[0].y = -h;
    lbl_3_bss_B860[1].x = w;
    lbl_3_bss_B860[1].y = -h;
    lbl_3_bss_B860[2].x = w;
    lbl_3_bss_B860[2].y = h;
    lbl_3_bss_B860[3].x = -w;
    lbl_3_bss_B860[3].y = h;
    PSMTXInverse(fn_80052768(0)->mtx, m);
    m[0][1] = m[1][0] = m[1][2] = m[2][1] = 0.0f;
    m[1][1] = 1.0f;
    v.x = node->offset.x;
    v.y = node->offset.y;
    v.z = node->offset.z;
    PSMTXMultVecSR(m, &v, &v);
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, node->pos.x, node->pos.y, node->pos.z);
    CTRLSetTranslation(&ctrl, anim->unk34.x + v.x, -anim->unk34.y + v.y, anim->unk34.z + v.z);
    CTRLBuildMatrix(&ctrl, m);
    PSMTXConcat(fn_80052768(0)->mtx, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
}

// .text:0x001483D4 size:0x48 mapped:0x80787468

bool fn_3_1483D4(void) {
    // 1. Call rand() and get the result in r3.
    // 2. Perform modulo 5. 
    // 3. Compare the result to 0.
    // 4. Normalize the boolean (val == 0) to an integer 0 or 1.
    
  return !(rand() % 5);
}

// .text:0x0014841C size:0xAD4 mapped:0x807874B0
void fn_3_14841C(void) {
    return;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 _pad8[0x18];
} Struct_26E7C;
extern Struct_26E7C lbl_3_data_26E7C;

// .text:0x00148EF0 size:0xE0 mapped:0x80787F84
void fn_3_148EF0(Struct_148EF0_Arg* arg0, f32 angle) {
    f32 s;
    f32 c;
    f32 rad;

    rad = 0.017453292f * angle;
    s = (f32)sin(rad);
    c = (f32)cos(rad);
    arg0->unk10.x = (s * (f32)lbl_3_data_26E7C.unk4) / 100000.0f;
    arg0->unk10.y = (c * (f32)lbl_3_data_26E7C.unk4) / 100000.0f;
    arg0->unk10.z = 0.0f;
}

// .text:0x00148FD0 size:0x370 mapped:0x80788064
void fn_3_148FD0(void) {
    return;
}

// .text:0x00149340 size:0x41C mapped:0x807883D4
void fn_3_149340(void) {
    return;
}

// .text:0x0014975C size:0x44C mapped:0x807887F0
void fn_3_14975C(void) {
    return;
}

// .text:0x00149BA8 size:0x4C8 mapped:0x80788C3C
void fn_3_149BA8(void) {
    return;
}

extern s8 lbl_3_bss_B85C[4];

// .text:0x0014A070 size:0xF4 mapped:0x80789104
void fn_3_14A070(s32* arr, s32 count) {
    u32 i;
    lbl_3_bss_B85C[0] = -1;
    lbl_3_bss_B85C[1] = -1;
    lbl_3_bss_B85C[2] = -1;
    lbl_3_bss_B85C[3] = -1;
    if (count > 4 || count == 0 || arr == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        lbl_3_bss_B85C[i] = arr[i];
    }
}

// .text:0x0014A164 size:0x24 mapped:0x807891F8
void fn_3_14A164(void) {
    pitchingMachinePitching(0x24);
}

typedef struct {
    u8 _pad0[0x8];
    s32 unk8;   // 0x08
    u8 _padC[0x4];
    s32 unk10;  // 0x10
    s32 unk14;  // 0x14
    u8 _pad18[0x8];
    s32 unk20;  // 0x20
    s32 unk24;  // 0x24
    s32 unk28;  // 0x28
    s32 unk2C;  // 0x2C
    u8 _pad30[0xC];
} Struct_26E40;
extern Struct_26E40 lbl_3_data_26E40;
void fn_80033620(struct Struct_14C79C_Arg* arg);
void fn_80033F64(f32 a, f32 b, f32 c);
void fn_80033CC8(ListNode_14B9F0* node, s32 arg1);

// .text:0x0014A188 size:0x1F4 mapped:0x8078921C
s32 fn_3_14A188(Struct_14C79C_Arg* arg) {
    ListNode_14B9F0* node;
    s32 alpha;
    s32 count;
    s32 da;
    f32 ds;

    count = 0;
    if (lbl_80366158._28 != 0) {
        return 0;
    }
    fn_80033620(arg);
    node = arg->node;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (node->field_0x4A != 0) {
            alpha = node->color[3];
            fn_80033F64(node->scaleX, node->scaleY, node->velocity.x);
            fn_80033CC8(node, arg->unk10);
            if (lbl_3_data_26E40.unk8 - node->field_0x4A < lbl_3_data_26E40.unk10) {
                ds = (node->velocity.z - (f32)lbl_3_data_26E40.unk14 / 100000.0f) / (f32)lbl_3_data_26E40.unk10;
                da = (lbl_3_data_26E40.unk28 - lbl_3_data_26E40.unk24) / lbl_3_data_26E40.unk10;
            } else {
                ds = ((f32)lbl_3_data_26E40.unk20 / 100000.0f + node->velocity.z) / (f32)(lbl_3_data_26E40.unk8 - lbl_3_data_26E40.unk10);
                da = (lbl_3_data_26E40.unk2C - lbl_3_data_26E40.unk28) / (lbl_3_data_26E40.unk8 - lbl_3_data_26E40.unk10);
            }
            alpha += da;
            if (alpha < 0) {
                alpha = 0;
            }
            if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            node->color[3] = alpha;
            node->scaleX += ds;
            node->scaleY = node->scaleX;
            node->velocity.x += node->velocity.y;
            if (--node->field_0x4A != 0) {
                count++;
            }
        }
        node = node->next;
    } while (node != NULL);
    return count == 0;
}

// .text:0x0014A37C size:0x2B0 mapped:0x80789410
void fn_3_14A37C(void) {
    return;
}

// .text:0x0014A62C size:0x2E0 mapped:0x807896C0
void fn_3_14A62C(void) {
    return;
}

// .text:0x0014A90C size:0x310 mapped:0x807899A0
void fn_3_14A90C(void) {
    return;
}

// .text:0x0014AC1C size:0x24 mapped:0x80789CB0
void fn_3_14AC1C(void) {
    pitchingMachinePitching(0x23);
}

// .text:0x0014AC40 size:0x608 mapped:0x80789CD4
void fn_3_14AC40(void) {
    return;
}

// .text:0x0014B248 size:0x1AC mapped:0x8078A2DC
void fn_3_14B248(Struct_14B248_Arg* arg0, ListNode_14B9F0* node) {
    f32 c;
    f32 angle;
    f32 dist;
    f32 s;
    f32 vx;
    f32 vy;
    f32 vz;

    node->scaleX = node->scaleY = (f32)lbl_3_data_26E24.unkC / 100000.0f;
    node->color[3] = lbl_3_data_26E24.unk14;
    angle = 0.017453292f * (f32)(rand() % 360);
    dist = ((u32)rand() % 200) / 1000.0;
    c = (f32)cos(angle);
    s = (f32)sin(angle);
    vx = dist * c;
    vy = dist * s;
    vz = 0.0f;
    node->offset.x = arg0->pos.x + vx;
    node->offset.y = arg0->pos.y + vy;
    node->offset.z = arg0->pos.z + vz;
    node->field_0x4A = lbl_3_data_26E24.unk4;
}

// .text:0x0014B3F4 size:0x148 mapped:0x8078A488
extern VecXYZ lbl_3_data_26E00[3];
void fn_3_14B3F4(PositionEffect* effect) {
    VecXYZ* start;
    VecXYZ* end;
    f32 progress;
    f32 amplitude;
    f32 inverse;
    s32 elapsed = effect->totalFrames - effect->remainingFrames;
    if ((f32)elapsed < effect->phaseFrames) {
        start = &lbl_3_data_26E00[0];
        end = &lbl_3_data_26E00[1];
        progress = (f32)elapsed / effect->phaseFrames;
    } else {
        start = &lbl_3_data_26E00[1];
        end = &lbl_3_data_26E00[2];
        progress = (f32)elapsed / ((f32)effect->totalFrames - effect->phaseFrames);
    }
    amplitude = fn_3_119D28();
    effect->pos.x = amplitude * (start->x * (1.0f - progress) + end->x * progress) + effect->origin.x;
    effect->pos.y = amplitude * (start->y * (1.0f - progress) + end->y * progress) + effect->origin.y;
    effect->pos.z = amplitude * (start->z * (1.0f - progress) + end->z * progress) + effect->origin.z;
}

// .text:0x0014B53C size:0x3F0 mapped:0x8078A5D0
void fn_3_14B53C(void* arg0, void* arg1, void* arg2) {
    return;
}

// .text:0x0014B92C size:0x74 mapped:0x8078A9C0
void fn_3_14B92C(void* arg0, void* arg1) {
    void* temp_r3;

    temp_r3 = (void*)fn_80033A24(fn_3_14AC40, 0x80, 0, lbl_3_data_26E24.unk8, 1, 0x23);
    if (temp_r3 != NULL) {
        fn_3_14B53C(temp_r3, arg0, arg1);
    }
}

// .text:0x0014B9A0 size:0x50 mapped:0x8078AA34
void fn_3_14B9A0(void* arg0, void* arg1) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        g_Minigame.GameMode_MiniGame == 3 &&
        arg1 != NULL) {
        fn_3_14B92C(arg0, arg1);
    }
}

// .text:0x0014B9F0 size:0x50 mapped:0x8078AA84
void fn_3_14B9F0(void) {
    struct Struct_800339F0_Result* result;
    ListNode_14B9F0* node;

    result = fn_800339F0(0, 0x22);
    if (result != NULL) {
        node = result->listHead;
        do {
            node->field_0x4A = 0;
            node = node->next;
        } while (node != NULL);
    }
    pitchingMachinePitching(0x22);
}

// .text:0x0014BA40 size:0x270 mapped:0x8078AAD4
void fn_3_14BA40(void) {
    return;
}

// .text:0x0014BCB0 size:0x21C mapped:0x8078AD44
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 _padC[4];
    s32 unk10;
    u8 _pad14[8];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 _pad2C[0x10];
} EffectConfig26D88;
extern EffectConfig26D88 lbl_3_data_26D88;
extern EffectConfig26D88 lbl_3_data_26DC4;
void fn_3_14BCB0(struct Struct_800339F0_Result* obj, Vec* pos, s32 arg2) {
    EffectConfig26D88* config;
    ListNode_14B9F0* node;
    u32 i;
    f32 angle;
    f32 radius;
    obj->field_0x10 = lbl_3_common_bss_32724.field6C;
    i = 0;
    node = obj->listHead;
    config = (u8)arg2 != 0 ? &lbl_3_data_26DC4 : &lbl_3_data_26D88;
    do {
        if (node->field_0x4A == 0) {
            node->field_0x4D = config->unk0;
            node->field_0x4E = 0;
            node->field_0x4A = config->unk8;
            node->scaleX = node->scaleY = (f32)config->unk10 / 100000.0f;
            node->color[3] = config->unk28;
            node->color[0] = config->unk1C;
            node->color[1] = config->unk20;
            node->color[2] = config->unk24;
            { f32 scale = 2.0f;
            radius = scale * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            }
            angle = 0.017453292f * (f32)((180.0 / config->unk4) * i);
            node->offset.x = radius * (f32)cos(angle) + pos->x;
            node->offset.y = (pos->y - radius * (f32)sin(angle)) - 1.0;
            node->offset.z = pos->z;
            node->field_0x4F = arg2;
            i++;
        }
        node = node->next;
    } while (node != NULL && i < lbl_3_data_26D88.unk4);
}

// .text:0x0014BECC size:0x47C mapped:0x8078AF60
void fn_3_14BECC(void* arg0, void* arg1) {
    return;
}

// .text:0x0014C348 size:0x50 mapped:0x8078B3DC
void fn_3_14C348(void* arg0, void* arg1) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        g_Minigame.GameMode_MiniGame == 2 &&
        arg0 != NULL) {
        fn_3_14BECC(arg0, arg1);
    }
}

// .text:0x0014C398 size:0x24 mapped:0x8078B42C
void fn_3_14C398(void) {
    pitchingMachinePitching(0x21);
}

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    u8 _padC[0x4];
    s32 unk10;
    s32 unk14;
    u8 _pad18[0x4];
    s32 unk1C;
    u8 _pad20[0xC];
} Struct_26D5C;
extern Vec lbl_3_data_26D50;
extern Struct_26D5C lbl_3_data_26D5C;

// .text:0x0014C3BC size:0x10C mapped:0x8078B450
void fn_3_14C3BC(ListNode_14B9F0* node) {
    Mtx m;
    Vec v;
    f32 half;

    PSVECScale(&lbl_3_data_26D50, 0.75f, &v);
    PSMTXRotRad(m, 'Y', shortAngleToRad(g_Minigame._1AF8));
    PSMTXMultVec(m, &v, &v);
    half = 0.5f;
    node->offset.x = (g_Minigame._1AE0 + v.x) + ((f32)lbl_3_data_26D5C.unk14 / 100000.0f) * half;
    node->offset.y = v.y - (g_Minigame._1AE4 + ((f32)lbl_3_data_26D5C.unk14 / 100000.0f) * half);
    node->offset.z = g_Minigame._1AE8 + v.z;
}

// .text:0x0014C4C8 size:0x2D4 mapped:0x8078B55C
void fn_3_14C4C8(void) {
    return;
}

// .text:0x0014C79C size:0x94 mapped:0x8078B830
void fn_3_14C79C(Struct_14C79C_Arg* arg0) {
    ListNode_14B9F0* node;

    arg0->unk10 = lbl_3_common_bss_32724.field6C;
    node = arg0->node;
    node->field_0x4D = lbl_3_data_26D5C.unk00;
    node->field_0x4E = 0;
    node->field_0x4A = lbl_3_data_26D5C.unk08;
    node->scaleX = node->scaleY = (f32)lbl_3_data_26D5C.unk10 / 100000.0f;
    node->color[3] = lbl_3_data_26D5C.unk1C;
    node->color[0] = node->color[1] = node->color[2] = 0xFF;
}

// .text:0x0014C830 size:0xD4 mapped:0x8078B8C4
void fn_3_14C830(void) {
    Struct_14C79C_Arg* obj;
    ListNode_14B9F0* node;

    obj = (Struct_14C79C_Arg*)fn_80033A24(fn_3_14C4C8, 0x80, 0, lbl_3_data_26D5C.unk04, 1, 10);
    if (obj != NULL) {
        obj->unk10 = lbl_3_common_bss_32724.field6C;
        node = obj->node;
        node->field_0x4D = lbl_3_data_26D5C.unk00;
        node->field_0x4E = 0;
        node->field_0x4A = lbl_3_data_26D5C.unk08;
        node->scaleX = node->scaleY = (f32)lbl_3_data_26D5C.unk10 / 100000.0f;
        node->color[3] = lbl_3_data_26D5C.unk1C;
        node->color[0] = node->color[1] = node->color[2] = 0xFF;
    }
}

// .text:0x0014C904 size:0xFC mapped:0x8078B998
void fn_3_14C904(void) {
    Struct_14C79C_Arg* obj;
    ListNode_14B9F0* node;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == 4) {
        obj = (Struct_14C79C_Arg*)fn_80033A24(fn_3_14C4C8, 0x80, 0, lbl_3_data_26D5C.unk04, 1, 10);
        if (obj != NULL) {
            obj->unk10 = lbl_3_common_bss_32724.field6C;
            node = obj->node;
            node->field_0x4D = lbl_3_data_26D5C.unk00;
            node->field_0x4E = 0;
            node->field_0x4A = lbl_3_data_26D5C.unk08;
            node->scaleX = node->scaleY = (f32)lbl_3_data_26D5C.unk10 / 100000.0f;
            node->color[3] = lbl_3_data_26D5C.unk1C;
            node->color[0] = node->color[1] = node->color[2] = 0xFF;
        }
    }
}

// .text:0x0014CA00 size:0x98 mapped:0x8078BA94
void fn_3_14CA00(void) {
    u32 i = 0;
    struct Struct_800339F0_Result* result;
    UnknownStruct_14CA98* node;

    do {
        result = fn_800339F0(0, 0x20);
        if (result != NULL) {
            node = (UnknownStruct_14CA98*)result->listHead;
            do {
                if (node->field_0x45 == (s8)i) {
                    node->field_0x44 = 0;
                    node->field_0x45 = 0xFF;
                    node->field_0x4A = 0;
                    node->field_0x4C = 0;
                }
                node = node->next;
            } while (node != NULL);
        }
        i++;
    } while (i < 15);

    pitchingMachinePitching(0x20);
}

// .text:0x0014CA98 size:0x1C mapped:0x8078BB2C
void fn_3_14CA98(UnknownStruct_14CA98* obj) {
    obj->field_0x44 = 0;
    obj->field_0x45 = 0xFF;
    obj->field_0x4A = 0;
    obj->field_0x4C = 0;
}

// .text:0x0014CAB4 size:0x74 mapped:0x8078BB48
void fn_3_14CAB4(s8 arg0) {
    struct Struct_800339F0_Result* result;
    UnknownStruct_14CA98* node;

    result = fn_800339F0(0, 0x20);
    if (result != NULL) {
        node = (UnknownStruct_14CA98*)result->listHead;
        do {
            if (node->field_0x45 == arg0) {
                node->field_0x44 = 0;
                node->field_0x45 = 0xFF;
                node->field_0x4A = 0;
                node->field_0x4C = 0;
            }
            node = node->next;
        } while (node != NULL);
    }
}

// .text:0x0014CB28 size:0x8C mapped:0x8078BBBC
static inline void fn_3_14CB28_inline(s8 arg0) {
    struct Struct_800339F0_Result* result;
    UnknownStruct_14CA98* node;

    result = fn_800339F0(0, 0x20);
    if (result != NULL) {
        node = (UnknownStruct_14CA98*)result->listHead;
        do {
            if (node->field_0x45 == arg0) {
                node->field_0x44 = 0;
                node->field_0x45 = 0xFF;
                node->field_0x4A = 0;
                node->field_0x4C = 0;
            }
            node = node->next;
        } while (node != NULL);
    }
}
void fn_3_14CB28(s8 arg0) {
    if (arg0 >= 15 || arg0 < 0) {
        return;
    }
    fn_3_14CB28_inline(arg0);
}

typedef struct {
    u8 _pad0[0xC];
    s32 unkC;  // 0x0C
    u8 _pad10[0x4];
    s32 unk14; // 0x14
    s32 unk18; // 0x18
    u8 _pad1C[0x4];
    s32 unk20; // 0x20
    s32 unk24; // 0x24
    s32 unk28; // 0x28
    u8 _pad2C[0x4];
    s32 unk30; // 0x30
    s32 unk34; // 0x34
    u8 _pad38[0x4];
    s32 unk3C; // 0x3C
    s32 unk40; // 0x40
    s32 unk44; // 0x44
    s32 unk48; // 0x48
    u8 _pad4C[0x4];
} Struct_26D00;
extern Struct_26D00 lbl_3_data_26D00;
void fn_8003403C(f32 a, f32 b);
void fn_80033CC8(ListNode_14B9F0* node, s32 arg1);

// .text:0x0014CBB4 size:0x18C mapped:0x8078BC48
void fn_3_14CBB4(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node) {
    s32 da;
    s32 alpha;
    f32 ds;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    fn_8003403C(node->scaleX, node->scaleY);
    fn_80033CC8(node, arg0->unk10);
    alpha = node->color[3];
    if (-node->field_0x48 < lbl_3_data_26D00.unk28) {
        ds = ((f32)lbl_3_data_26D00.unk30 / 100000.0f) / (f32)lbl_3_data_26D00.unk28;
        da = lbl_3_data_26D00.unk3C / lbl_3_data_26D00.unk28;
    } else {
        ds = ((f32)(lbl_3_data_26D00.unk34 - lbl_3_data_26D00.unk30) / 100000.0f) / (f32)(lbl_3_data_26D00.unk48 - lbl_3_data_26D00.unk28);
        da = (lbl_3_data_26D00.unk40 - lbl_3_data_26D00.unk3C) / (lbl_3_data_26D00.unk48 - lbl_3_data_26D00.unk28);
    }
    alpha += da;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    node->color[3] = alpha;
    node->color[0] = node->color[1] = node->color[2] = node->color[3];
    node->scaleX += ds;
    node->scaleY = node->scaleX;
}

// .text:0x0014CD40 size:0x18C mapped:0x8078BDD4
void fn_3_14CD40(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node) {
    s32 da;
    s32 alpha;
    f32 ds;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    fn_8003403C(node->scaleX, node->scaleY);
    fn_80033CC8(node, arg0->unk10);
    alpha = node->color[3];
    if (-node->field_0x48 < lbl_3_data_26D00.unkC) {
        ds = ((f32)lbl_3_data_26D00.unk14 / 100000.0f) / (f32)lbl_3_data_26D00.unkC;
        da = lbl_3_data_26D00.unk20 / lbl_3_data_26D00.unkC;
    } else {
        ds = ((f32)(lbl_3_data_26D00.unk18 - lbl_3_data_26D00.unk14) / 100000.0f) / (f32)(lbl_3_data_26D00.unk44 - lbl_3_data_26D00.unkC);
        da = (lbl_3_data_26D00.unk24 - lbl_3_data_26D00.unk20) / (lbl_3_data_26D00.unk44 - lbl_3_data_26D00.unkC);
    }
    alpha += da;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    node->color[3] = alpha;
    node->color[0] = node->color[1] = node->color[2] = node->color[3];
    node->scaleX += ds;
    node->scaleY = node->scaleX;
}

// .text:0x0014CECC size:0x3F4 mapped:0x8078BF60
void fn_3_14CECC(void) {
    return;
}

// .text:0x0014D2C0 size:0x58 mapped:0x8078C354
void fn_3_14D2C0(void) {
    return;
}

// .text:0x0014D318 size:0x134 mapped:0x8078C3AC
void fn_3_14D318(ListNode_14B9F0* node) {
    u8 idx;
    BB_barrelStruct* barrel;
    f32 half = 0.5f;

    idx = node->field_0x45;
    barrel = &g_Minigame.barrels[idx];

    node->offset.x = barrel->currentPos.x;
    node->offset.y = -(lbl_3_data_21770[3] * half + barrel->currentPos.y);
    node->offset.z = barrel->currentPos.z;
    node->offset.x += (rand() % 100 - 50) / 100.0;
    node->offset.y += (rand() % 100 - 50) / 100.0;
}

// .text:0x0014D44C size:0x288 mapped:0x8078C4E0
void fn_3_14D44C(void) {
    return;
}

// .text:0x0014D6D4 size:0x3C mapped:0x8078C768


void fn_3_14D6D4(Struct_14D6D4_Input* in) {
    Struct_14D6D4_Node* node;

    in->field10 = lbl_3_common_bss_32724.field6C;
    node = in->listHead;

    do {
        node->unk46 = 0;
        node->unk45 = 0;
        node->unk44 = 0;
        node->unk4A = 0;
        node->unk4E = 0;
        node = node->next;
    } while (node != NULL);
}

// .text:0x0014D710 size:0x570 mapped:0x8078C7A4
void fn_3_14D710(void) {
    return;
}

// .text:0x0014DC80 size:0x60 mapped:0x8078CD14
void fn_3_14DC80(s32 arg) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) return;
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER) return;
    if ((s8)arg >= 15 || (s8)arg < 0) return;
    fn_3_14D710();
}

// .text:0x0014DCE0 size:0x24 mapped:0x8078CD74
void fn_3_14DCE0(void) {
    pitchingMachinePitching(0x1F);
}

// .text:0x0014DD04 size:0x268 mapped:0x8078CD98
typedef struct {
    s32 unk0, unk4, unk8, unkC, unk10, unk14, unk18, unk1C, unk20, unk24, unk28;
} EffectConfig26CD0;
extern EffectConfig26CD0 lbl_3_data_26CD0;
ListNode_14B9F0* fn_80031F34(ListNode_14B9F0* node, s32 count);
s32 fn_3_14DD04(struct Struct_800339F0_Result* obj) {
    ListNode_14B9F0* node;
    ListNode_14B9F0** link;
    ListNode_14B9F0* tail;
    s32 count = 0;
    node = obj->listHead = fn_80031F34(obj->listHead, obj->count);
    link = &obj->listHead;
    tail = NULL;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (node->field_0x4A != 0) {
            s32 alpha;
            s32 da;
            f32 ds;
            fn_8003403C(node->scaleX, node->scaleY);
            fn_80033CC8(node, obj->field_0x10);
            node->offset.y -= node->velocity.y;
            node->velocity.y -= (f32)lbl_3_data_26CD0.unk28 / 100000.0f;
            alpha = node->color[3];
            if (lbl_3_data_26CD0.unk8 / node->field_0x4A < 2) {
                ds = node->pos.x * (((f32)(lbl_3_data_26CD0.unk10 - lbl_3_data_26CD0.unkC) / 100000.0f) / (f32)(lbl_3_data_26CD0.unk8 / 2));
                da = (lbl_3_data_26CD0.unk1C - lbl_3_data_26CD0.unk18) / (lbl_3_data_26CD0.unk8 / 2);
            } else {
                ds = node->pos.x * (((f32)(lbl_3_data_26CD0.unk14 - lbl_3_data_26CD0.unk10) / 100000.0f) / (f32)(lbl_3_data_26CD0.unk8 / 2));
                da = (lbl_3_data_26CD0.unk20 - lbl_3_data_26CD0.unk1C) / (lbl_3_data_26CD0.unk8 / 2);
            }
            alpha += da;
            node->scaleX += ds;
            node->scaleY = node->scaleX;
            if (alpha < 0) alpha = 0;
            else if (alpha > 255) alpha = 255;
            node->color[3] = alpha;
            node->field_0x4A--;
            if (node->field_0x4A == 0) {
                *link = node->next;
                if (tail != NULL) tail->next = node;
                tail = node;
                node->next = NULL;
                obj->count--;
            } else {
                link = &node->next;
                count++;
            }
        }
        node = *link;
    } while (node != NULL);
    return count == 0;
}

// .text:0x0014DF6C size:0x2C8 mapped:0x8078D000
void fn_3_14DF6C(void) {
    return;
}

// .text:0x0014E234 size:0x58C mapped:0x8078D2C8
void fn_3_14E234(void) {
    return;
}

// .text:0x0014E7C0 size:0x50 mapped:0x8078D854
void fn_3_14E7C0(void* arg0) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        g_Minigame.GameMode_MiniGame == 6 &&
        arg0 != NULL) {
        fn_3_14E234();
    }
}

// .text:0x0014E810 size:0x84 mapped:0x8078D8A4
void fn_3_14E810(void) {
    u32 i = 0;
    struct Struct_800339F0_Result* result;
    ListNode_14B9F0* node;
    s32 target_val;

    do {
        result = fn_800339F0(0, 0x1E);
        if (result != NULL) {
            target_val = (s8)i + 1;
            node = result->listHead;
            do {
                if (node->field_0x4C == target_val) {
                    node->field_0x4A = 0;
                }
                node = node->next;
            } while (node != NULL);
        }
        i++;
    } while (i < 4);

    pitchingMachinePitching(0x1E);
}

// .text:0x0014E894 size:0x8C mapped:0x8078D928
void fn_3_14E894(void) {
    return;
}

// .text:0x0014E920 size:0x68 mapped:0x8078D9B4
void fn_3_14E920(s8 arg0) {
    struct Struct_800339F0_Result *result;
    ListNode_14B9F0 *node;
    result = fn_800339F0(0, 0x1E);
    if (result != NULL) {
        node = result->listHead;
        do {
            if (node->field_0x4C == (s8)arg0 + 1) {
                node->field_0x4A = 0;
            }
            node = node->next;
        } while (node != NULL);
    }
}

// .text:0x0014E988 size:0x68 mapped:0x8078DA1C
void fn_3_14E988(s8 arg0) {
    struct Struct_800339F0_Result *result;
    ListNode_14B9F0 *node;
    result = fn_800339F0(0, 0x1E);
    if (result != NULL) {
        node = result->listHead;
        do {
            if (node->field_0x4C == (s8)arg0 + 1) {
                node->field_0x4A = 0;
            }
            node = node->next;
        } while (node != NULL);
    }
}

// .text:0x0014E9F0 size:0x104 mapped:0x8078DA84
void fn_3_14E9F0(ListNode_14B9F0* node) {
    VecXYZ delta;
    s32 r;
    u8 type;

    if (node->field_0x4C < 5) {
        type = lbl_3_data_26CB8[(u32)rand() % 23];
        delta.z = 0.0f;
        delta.y = 0.0f;
        delta.x = 0.0f;
        if (fn_8001B728(node->field_0x4C - 1, type, &delta) == 0) {
            memset(&delta, 0, sizeof(VecXYZ));
            fn_8001B728(node->field_0x4C - 1, 4, &delta);
        }
    } else {
        delta.x = g_Minigame._6E8;
        delta.y = -g_Minigame._6EC;
        delta.z = g_Minigame._6F0;
    }
    node->offset.x += delta.x;
    node->offset.y += delta.y;
    node->offset.z += delta.z;
}

// .text:0x0014EAF4 size:0x230 mapped:0x8078DB88
void fn_3_14EAF4(ListNode_14B9F0* node) {
    Vec v = {0.0f, 0.0f, 0.0f};
    VecXYZ delta;
    u8 type;

    if (node->field_0x4C == 5) {
        v.x += (f32)(rand() % 10000 - 5000) / 10000.0f;
        v.y += (f32)(rand() % 10000 - 5000) / 10000.0f;
        node->offset.x = v.x;
        node->offset.y = v.y - 0.5f;
        node->offset.z = v.z;
    } else {
        node->offset.x = node->offset.y = node->offset.z = 0.0f;
    }
    if (node->field_0x4C < 5) {
        type = lbl_3_data_26CB8[(u32)rand() % 23];
        delta.z = 0.0f;
        delta.y = 0.0f;
        delta.x = 0.0f;
        if (fn_8001B728(node->field_0x4C - 1, type, &delta) == 0) {
            memset(&delta, 0, sizeof(VecXYZ));
            fn_8001B728(node->field_0x4C - 1, 4, &delta);
        }
    } else {
        delta.x = g_Minigame._6E8;
        delta.y = -g_Minigame._6EC;
        delta.z = g_Minigame._6F0;
    }
    node->offset.x += delta.x;
    node->offset.y += delta.y;
    node->offset.z += delta.z;
}

// .text:0x0014ED24 size:0x6A8 mapped:0x8078DDB8
void fn_3_14ED24(void) {
    return;
}

// .text:0x0014F3CC size:0x178 mapped:0x8078E460
void fn_3_14F3CC(ListNode_14B9F0* node) {
    Vec v = {0.0f, 0.0f, 0.0f};
    f32 yOff;
    s16 rangeX;
    s16 rangeY;

    yOff = node->field_0x4C < 5 ? 1.25f : 0.5f;
    rangeX = node->field_0x4C < 5 ? 20000 : 10000;
    rangeY = node->field_0x4C < 5 ? 20000 : 10000;
    v.x += (f32)(rand() % rangeX - rangeX / 2) / 10000.0f;
    v.y += (f32)(rand() % rangeY - rangeY / 2) / 10000.0f;
    node->offset.x = v.x;
    node->offset.y = v.y - yOff;
    node->offset.z = v.z;
}

// .text:0x0014F544 size:0x60 mapped:0x8078E5D8
void fn_3_14F544(Struct_14F544_Arg* arg) {
    // NONMATCHING: lfd f2 (bias double load) scheduled 2 instructions too early
    f32 val;
    arg->field_0x4A = (s16)lbl_3_data_26C94.field_0x1C;
    arg->field_0x43 = (u8)lbl_3_data_26C94.field_0x14;
    val = (f32)lbl_3_data_26C94.field_0x8 / 100000.0f;
    arg->field_0x3C = val;
    arg->field_0x38 = val;
}

// .text:0x0014F5A4 size:0x32C mapped:0x8078E638
void fn_3_14F5A4(void) {
    return;
}

// .text:0x0014F8D0 size:0x60 mapped:0x8078E964
void fn_3_14F8D0(struct Struct_800339F0_Result* arg) {
    ListNode_14B9F0* node;
    u32 i = 0;
    arg->field_0x10 = lbl_3_common_bss_32724.field6C;
    node = arg->listHead;
    do {
        node->field_0x4F = 0;
        node->field_0x4D = lbl_3_data_26C94.field_0x0;
        node->field_0x4E = 0;
        node->field_0x4C = i / 18 + 1;
        i++;
        node = node->next;
    } while (node != NULL);
}

// .text:0x0014F930 size:0x6E0 mapped:0x8078E9C4
void fn_3_14F930(void) {
    return;
}

// .text:0x00150010 size:0x60 mapped:0x8078F0A4
void fn_3_150010(s32 arg) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) return;
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_STAR_DASH) return;
    if ((s8)arg > 4 || (s8)arg < 0) return;
    fn_3_14F930();
}

// .text:0x00150070 size:0x58 mapped:0x8078F104
void fn_3_150070(void) {
    struct Struct_800339F0_Result* result;
    ListNode_14B9F0* node;

    result = fn_800339F0(0, 0x1D);
    if (result != NULL) {
        node = result->listHead;
        do {
            node->field_0x4A = 0;
            node->field_0x48 = 0;
            node->field_0x4C = 0;
            node = node->next;
        } while (node != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x001500C8 size:0x58 mapped:0x8078F15C
void fn_3_1500C8(void) {
    struct Struct_800339F0_Result* result;
    ListNode_14B9F0* node;

    result = fn_800339F0(0, 0x1D);
    if (result != NULL) {
        node = result->listHead;
        do {
            node->field_0x4A = 0;
            node->field_0x48 = 0;
            node->field_0x4C = 0;
            node = node->next;
        } while (node != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x00150120 size:0x3CC mapped:0x8078F1B4
void fn_3_150120(void) {
    return;
}

// .text:0x001504EC size:0x454 mapped:0x8078F580
void fn_3_1504EC(void) {
    return;
}

// .text:0x00150940 size:0x444 mapped:0x8078F9D4
void fn_3_150940(void) {
    return;
}

// .text:0x00150D84 size:0x2E4 mapped:0x8078FE18
void fn_3_150D84(void) {
    return;
}

// .text:0x00151068 size:0x19C mapped:0x807900FC
void fn_3_151068(Struct_151068_Arg* obj, ListNode_14B9F0* node) {
    Mtx m;
    C2310Bone* bone;
    f32 x;
    f32 y;
    f32 z;

    node->field_0x4A = lbl_3_data_26C3C.unk_18;
    bone = obj->holder->actor->boneArray[lbl_3_data_26C3C.unk_1C];
    PSMTXIdentity(m);
    x = bone->worldMtx[0][3];
    y = bone->worldMtx[1][3];
    z = bone->worldMtx[2][3];
    x += (rand() % 100 - 50) / 100.0;
    y += (rand() % 150 - 75) / 100.0;
    node->offset.x = x;
    node->offset.y = y;
    node->offset.z = z;
    node->scaleY = node->scaleX = (f32)lbl_3_data_26C3C.unk_08;
    node->color[3] = lbl_3_data_26C3C.unk_10;
}

// .text:0x00151204 size:0x490 mapped:0x80790298
void fn_3_151204(void* obj, void* arg1, void* arg2) {
    return;
}

// .text:0x00151694 size:0x7C mapped:0x80790728
void fn_3_151694(void* arg0, void* arg1) {
    void* obj;

    obj = (void*)fn_80033A24(fn_3_150940, 0x80, 0, lbl_3_data_26C3C.unk_04 + lbl_3_data_26C3C.unk_24, 1, 0x1D);
    if (obj != NULL) {
        fn_3_151204(obj, arg0, arg1);
    }
}

// .text:0x00151710 size:0x50 mapped:0x807907A4
void fn_3_151710(void* arg0, void* arg1) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        g_Minigame.GameMode_MiniGame == 2 &&
        arg0 != NULL) {
        fn_3_151694(arg0, arg1);
    }
}

// .text:0x00151760 size:0x38 mapped:0x807907F4

/**
 * @address 00151760
 */
void fn_3_151760(void) {
    /* * Target Sequence:
     * lis r3, lbl@ha -> li r4, 0 -> stw r0, 0x14(r1) -> addi r3, r3, lbl@l
     * li r5, 0xf -> bl memset
     */
    memset(lbl_3_bss_B894, 0, 0xF);

    /* * Target Sequence:
     * li r3, 0x1c -> bl pitchingMachinePitching
     */
    pitchingMachinePitching(0x1C);
}

// .text:0x00151798 size:0x38 mapped:0x8079082C



void fn_3_151798(void) {
    memset(lbl_3_bss_B894, 0, 0xFU);
    pitchingMachinePitching(0x1C);
}

void fn_80033B58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// .text:0x001517D0 size:0x228 mapped:0x80790864
void fn_3_1517D0(ListNode_14B9F0* node, Struct_14C79C_Arg* arg1) {
    f32 half = 0.5f;
    f32 w = node->scaleX * half;
    f32 h = node->scaleY * half;
    Mtx m;
    Mtx44 proj;
    Vec quad[4];
    f32 uv[4][2] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    s32 i;

    quad[0].x = -w;
    quad[0].y = -h;
    quad[1].x = w;
    quad[1].y = -h;
    quad[2].x = w;
    quad[2].y = h;
    quad[3].x = -w;
    quad[3].y = h;
    quad[0].z = quad[1].z = quad[2].z = quad[3].z = 0.0f;
    PSMTXIdentity(m);
    PSMTX44Identity(proj);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_80033B58(arg1->unk10, node->field_0x4D, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(node->offset.x + quad[i].x, node->offset.y + quad[i].y, -1.0f);
        GXColor1u32(node->colorU32);
        GXTexCoord2f32(uv[node->field_0x4E + i][0], uv[node->field_0x4E + i][1]);
    }
    GXLoadPosMtxImm(fn_80052768(0)->mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768(0)->proj, GX_PERSPECTIVE);
}

extern f32 lbl_3_data_26C1C[4][2];
void fn_3_11F4B4(s32 arg1, s32 arg2);

// .text:0x001519F8 size:0x1B4 mapped:0x80790A8C
void fn_3_1519F8(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node) {
    Vec v;
    Vec dir;
    Vec w;
    f32 mag;

    fn_3_1517D0(node, arg0);
    if (lbl_80366158._28 != 0) {
        return;
    }
    PSVECAdd(&node->offset, &node->velocity, &node->offset);
    memcpy(&v, &node->offset, sizeof(Vec));
    v.x = lbl_3_data_26C1C[node->field_0x44][0] - v.x;
    v.y = lbl_3_data_26C1C[node->field_0x44][1] - v.y;
    v.z = 0.0f;
    PSVECNormalize(&v, &dir);
    mag = PSVECMag(&v);
    PSVECScale(&dir, 0.0015f * (1.0f / (mag * mag)), &v);
    PSVECAdd(&node->velocity, &v, &node->velocity);
    w.x = lbl_3_data_26C1C[node->field_0x44][0];
    w.y = lbl_3_data_26C1C[node->field_0x44][1];
    w.z = 0.0f;
    PSVECNormalize(&w, &w);
    if (PSVECDotProduct(&dir, &w) < 0.0f || !mag) {
        node->field_0x4A = 0;
    }
    if (node->field_0x4A == 0 && node->field_0x45 != 0) {
        fn_3_11F4B4(node->field_0x44, node->field_0x4D == 1);
        node->field_0x45 = 0;
    }
}

// .text:0x00151BAC size:0x1C0 mapped:0x80790C40
void fn_3_151BAC(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node) {
    f32 scale;
    s32 alpha;
    s32 da;
    f32 ds;
    s32 half;

    fn_8003403C(node->scaleX, node->scaleY);
    fn_80033CC8(node, arg0->unk10);
    if (node->field_0x4D != 0) {
        scale = fn_3_119854(2);
    } else {
        scale = fn_3_119854(0);
    }
    alpha = node->color[3];
    if (lbl_3_data_26BFC.unkC / node->field_0x4A < 2) {
        half = lbl_3_data_26BFC.unkC / 2;
        da = lbl_3_data_26BDC.unk8 / half;
        ds = ((f32)lbl_3_data_26BFC.unk4 * scale / 100000.0f) / (f32)half;
    } else {
        half = lbl_3_data_26BFC.unkC / 2;
        da = -lbl_3_data_26BDC.unk8 / half;
        ds = -((f32)lbl_3_data_26BFC.unk4 * scale / 100000.0f) / (f32)half;
    }
    alpha += da;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    node->color[3] = alpha;
    node->scaleX += ds;
    node->scaleY = node->scaleX;
    PSVECAdd(&node->offset, &node->velocity, &node->offset);
    node->field_0x4A--;
}

// .text:0x00151D6C size:0x1C0 mapped:0x80790E00
void fn_3_151D6C(Struct_14C79C_Arg* arg0, ListNode_14B9F0* node) {
    f32 scale;
    s32 alpha;
    s32 da;
    f32 ds;
    s32 half;

    fn_8003403C(node->scaleX, node->scaleY);
    fn_80033CC8(node, arg0->unk10);
    if (node->field_0x4D != 0) {
        scale = fn_3_119854(2);
    } else {
        scale = fn_3_119854(0);
    }
    alpha = node->color[3];
    if (lbl_3_data_26BEC.unkC / node->field_0x4A < 2) {
        half = lbl_3_data_26BEC.unkC / 2;
        da = lbl_3_data_26BDC.unk8 / half;
        ds = ((f32)lbl_3_data_26BEC.unk4 * scale / 100000.0f) / (f32)half;
    } else {
        half = lbl_3_data_26BEC.unkC / 2;
        da = -lbl_3_data_26BDC.unk8 / half;
        ds = -((f32)lbl_3_data_26BEC.unk4 * scale / 100000.0f) / (f32)half;
    }
    alpha += da;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    node->color[3] = alpha;
    node->scaleX += ds;
    node->scaleY = node->scaleX;
    PSVECAdd(&node->offset, &node->velocity, &node->offset);
    node->field_0x4A--;
}

// .text:0x00151F2C size:0x5BC mapped:0x80790FC0
void fn_3_151F2C(void) {
    return;
}

// .text:0x001524E8 size:0x2AC mapped:0x8079157C
void fn_3_1524E8(void) {
    return;
}

// .text:0x00152794 size:0x320 mapped:0x80791828
void fn_3_152794(void) {
    return;
}

// .text:0x00152AB4 size:0x6F0 mapped:0x80791B48
void fn_3_152AB4(void) {
    return;
}

// .text:0x001531A4 size:0x31C mapped:0x80792238
void fn_3_1531A4(void) {
    return;
}

s32 fn_8005268C(void);

// .text:0x001534C0 size:0x1E8 mapped:0x80792554
void fn_3_1534C0(ListNode_14B9F0* node) {
    Mtx m;
    CameraView* cam = fn_80052734(fn_8005268C());
    f32 scale = node->field_0x4D != 0 ? fn_3_119854(2) : fn_3_119854(0);
    Vec fwd = {0.0f, 0.0f, -1.0f};
    Vec axis;
    Vec dir;
    Vec off;
    f32 angle;

    off.x = 0.0f;
    off.y = 0.0f;
    off.z = -0.354f * scale;
    PSVECSubtract(&cam->pos, &node->posVec, &dir);
    PSVECNormalize(&dir, &dir);
    angle = acos(PSVECDotProduct(&fwd, &dir));
    PSVECCrossProduct(&fwd, &dir, &axis);
    if (PSVECMag(&axis) == 0.0f) {
        axis.x = 0.0f;
        axis.z = 0.0f;
        axis.y = -1.0f;
    }
    PSMTXRotAxisRad(m, &axis, angle);
    PSMTXMultVec(m, &off, &off);
    node->offset.x = node->pos.x + off.x;
    node->offset.y = node->pos.y + off.y;
    node->offset.z = node->pos.z + off.z;
    node->scaleX = node->scaleY = (f32)lbl_3_data_26BEC.unk0;
    node->field_0x4C = 1;
    node->field_0x4A = lbl_3_data_26BEC.unkC;
    node->velocity.x = node->velocity.z = 0.0f;
    node->velocity.y = (f32)lbl_3_data_26BEC.unk8 / 100000.0f;
}

// .text:0x001536A8 size:0x7E4 mapped:0x8079273C
void fn_3_1536A8(void) {
    return;
}

// .text:0x00153E8C size:0x100 mapped:0x80792F20
void fn_3_153E8C(ListNode_14B9F0* node, VecXYZ* pos, u8 arg2, u8 arg3, u8 arg4) {
    f32 height;

    node->field_0x48 = (arg4 != 0) * lbl_3_data_26BEC.unkC + (arg4 * lbl_3_data_26BDC.unkC) / lbl_3_data_26BDC.unk0;
    node->field_0x4D = (arg3 == 4);
    node->field_0x4E = 0;
    node->field_0x4F = arg2;
    node->color[2] = 0xFF;
    node->color[1] = 0xFF;
    node->color[0] = 0xFF;
    node->color[3] = lbl_3_data_26BDC.unk4;
    node->pos.x = pos->x;
    if (node->field_0x4D) {
        height = fn_3_119854(2);
    } else {
        height = fn_3_119854(0);
    }
    node->pos.y = -pos->y - 0.1435f * height;
    node->pos.z = pos->z;
    node->field_0x45 = 0;
    node->field_0x44 = 0;
}

// .text:0x00153F8C size:0x158 mapped:0x80793020
void fn_3_153F8C(struct Struct_800339F0_Result* obj, s32 arg1, s32 arg2, Vec* arg3) {
    return;
}

// .text:0x001540E4 size:0xE0 mapped:0x80793178
void fn_3_1540E4(s32 arg0, s32 arg1, Vec* arg2) {
    struct Struct_800339F0_Result* obj;
    ListNode_14B9F0* node;

    obj = fn_800339F0(0, 0x1C);
    if (obj != NULL) {
        fn_3_153F8C(obj, arg0, arg1, arg2);
        return;
    }
    obj = (struct Struct_800339F0_Result*)fn_80033A24(fn_3_151F2C, 0x80, 0, lbl_3_data_26BDC.unk0 * 15, 1, 0x1C);
    if (obj != NULL) {
        node = obj->listHead;
        do {
            node->field_0x4A = 0;
            node->field_0x4C = 0;
            node->field_0x4F = 0xFF;
            node = node->next;
        } while (node != NULL);
        fn_3_153F8C(obj, arg0, arg1, arg2);
        memset(lbl_3_bss_B894, 0, 0xF);
    }
}

// .text:0x001541C4 size:0x50 mapped:0x80793258
void fn_3_1541C4(s32 arg0, s32 arg1, Vec* arg2) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        g_Minigame.GameMode_MiniGame == 4 &&
        arg2 != NULL) {
        fn_3_1540E4(arg0, arg1, arg2);
    }
}

// .text:0x00154214 size:0x24 mapped:0x807932A8
void fn_3_154214(void) {
    pitchingMachinePitching(0x27);
}

// .text:0x00154238 size:0xBC mapped:0x807932CC
void fn_3_154238(s16 arg0) {
    struct Struct_800339F0_Result* result;
    ListNode_14B9F0** link;
    ListNode_14B9F0* node;
    ListNode_14B9F0* head;
    ListNode_14B9F0* tail;

    result = fn_800339F0(0, 0x27);
    if (result != NULL) {
        node = result->listHead;
        link = &result->listHead;
        tail = NULL;
        head = NULL;
        do {
            if (node->field_0x18 == arg0) {
                *link = node->next;
                if (tail != NULL) {
                    tail->next = node;
                } else {
                    head = node;
                }
                node->next = NULL;
                tail = node;
                result->count--;
            } else {
                link = &node->next;
            }
            node = *link;
        } while (node != NULL);
        if (head != NULL) {
            fn_80033794(head);
        }
    }
}

// .text:0x001542F4 size:0x6FC mapped:0x80793388
void fn_3_1542F4(void) {
    return;
}

// .text:0x001549F0 size:0x28C mapped:0x80793A84
void fn_3_1549F0(void) {
    return;
}

// .text:0x00154C7C size:0x5A0 mapped:0x80793D10
void fn_3_154C7C(u32 unknown) {
    return;
}

// .text:0x0015521C size:0x48 mapped:0x807942B0



void fn_3_15521C(u32 unused, u32 param_2, u32 param_3) {
    if (g_d_GameSettings.GameModeSelected != 7) {
        return;
    }
    if (param_2 == 0 || param_3 == 0) {
        return;
    }
    fn_3_154C7C(unused);
}

// .text:0x00155264 size:0x24 mapped:0x807942F8
void fn_3_155264(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x00155288 size:0x24 mapped:0x8079431C
void fn_3_155288(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x001552AC size:0x738 mapped:0x80794340
void fn_3_1552AC(void) {
    return;
}

// .text:0x001559E4 size:0x244 mapped:0x80794A78
typedef struct {
    u8 _pad0[0x8];
    s32 scale;        // 0x08
    u8 _padC[0x4];
    s32 alpha;        // 0x10
    u8 _pad14[0x4];
    s32 field_0x18;   // 0x18
} Struct_26BC0;
extern Vec lbl_3_data_26BB4;
extern Struct_26BC0 lbl_3_data_26BC0;

// .text:0x001559E4 size:0x244 mapped:0x80794A78
void fn_3_1559E4(ListNode_14B9F0* node, Vec* pos, Vec* rot) {
    struct { Control ctrl; u8 _pad[8]; } control;
    Mtx m;
    Vec v;
    Vec base;
    f64 ay;

    node->field_0x4A = lbl_3_data_26BC0.field_0x18;
    control.ctrl.type = 0;
    CTRLSetRotation(&control.ctrl, rot->x, rot->y, rot->z);
    CTRLBuildMatrix(&control.ctrl, m);
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        base = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, 1.5f, &base);
    }
    v.x = base.x + 1.5 * ((rand() % 40 - 20) / 100.0);
    v.y = base.y;
    v.z = base.z + 1.5 * ((rand() % 40 - 20) / 100.0);
    PSMTXMultVec(m, &v, &v);
    v.x += pos->x;
    ay = __fabs(pos->y);
    v.y = v.y - ay;
    v.z += pos->z;
    node->offset.x = v.x;
    node->offset.y = v.y;
    node->offset.z = v.z;
    node->scaleY = node->scaleX = (f32)lbl_3_data_26BC0.scale;
    node->color[3] = lbl_3_data_26BC0.alpha;
}

// .text:0x00155C28 size:0x2E0 mapped:0x80794CBC
void fn_3_155C28(void) {
    return;
}

// .text:0x00155F08 size:0x310 mapped:0x80794F9C
void fn_3_155F08(void) {
    return;
}

// .text:0x00156218 size:0x330 mapped:0x807952AC
void fn_3_156218(void) {
    return;
}

// .text:0x00156548 size:0x428 mapped:0x807955DC
void fn_3_156548(void) {
    return;
}

// .text:0x00156970 size:0x394 mapped:0x80795A04
void fn_3_156970(void) {
    return;
}

// .text:0x00156D04 size:0x608 mapped:0x80795D98
void fn_3_156D04(void) {
    return;
}

static inline Struct_B850_Entry* fn_3_1575F0_inline(u32 index) {
    Struct_B850_Node* node;

    if (lbl_3_bss_B850 != NULL) {
        node = lbl_3_bss_B850->head;
        while (index >= 7) {
            node = node->next;
            index -= 7;
        }
        return &node->entries[index];
    }
    return NULL;
}

// .text:0x0015730C size:0xA0 mapped:0x807963A0
void fn_3_15730C(u32 index, f32 x, f32 y, f32 z) {
    Struct_B850_Entry* entry;

    entry = fn_3_1575F0_inline(index);
    if (entry != NULL) {
        entry->x = x;
        entry->y = y;
        entry->z = z;
    }
}

// .text:0x001573AC size:0x1C4 mapped:0x80796440
void fn_3_1573AC(void) {
    return;
}

// .text:0x00157570 size:0x18 mapped:0x80796604
void fn_3_157570(void) {
    lbl_3_bss_B850->someFlag = TRUE;
}

// .text:0x00157588 size:0x68 mapped:0x8079661C
void fn_3_157588(s32 arg) {
    UnknownStruct_B850 *temp_r3;

    temp_r3 = (UnknownStruct_B850 *)fn_80033A24(fn_3_15767C, 0x80, 0, (arg + 6) / 7, 1, 0x28);
    lbl_3_bss_B850 = temp_r3;
    temp_r3->someFlag = 0;
}

// .text:0x001575F0 size:0x8C mapped:0x80796684
Struct_B850_Entry* fn_3_1575F0(u32 index) {
    return fn_3_1575F0_inline(index);
}

// .text:0x0015767C size:0x27C mapped:0x80796710
void fn_3_15767C(void) {
    return;
}

// .text:0x001578F8 size:0x24 mapped:0x8079698C
void fn_3_1578F8(void) {
    pitchingMachinePitching(0x16);
}

// .text:0x0015791C size:0x1A8 mapped:0x807969B0
f32 fn_3_15791C(s32 arg) {
    s32 cycles = (arg + 48) / 120;
    s32 frame = (arg + 48) % 120;
    f32 value;
    f32 half = 0.5f;
    if (frame >= 48) {
        value = (f32)cos(3.1415927f * (1.0f + ((f32)frame - 48.0f) / 72.0f));
    } else {
        value = (f32)cos(3.1415927f * ((f32)frame / 48.0f));
    }
    value = value * half;
    value += half;
    if (cycles != 0 && g_GameLogic.gameStatus != 14 && g_GameLogic.gameStatus != 34 && g_GameLogic.gameStatus != 36 && g_GameLogic.gameStatus != 38) {
        value += (half * ((f32)arg - 72.0f)) / 120.0f;
    }
    return 4.0f * value;
}

// .text:0x00157AC4 size:0x2F4 mapped:0x80796B58
void fn_3_157AC4(void) {
    return;
}
