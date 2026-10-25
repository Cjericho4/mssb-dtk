#include "Dolphin/GX/GXPixel.h"
#include "UnknownHeaders.h"
#include "game/sta_c5.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "game/rep_1D58.h"
#include "C3/control.h"
#include "game/sta_c2.h"
#include "game/gap_16C410.h"
#include "game/rep_540.h"
#include "game/rep_AC8.h"
#include "musyx/musyx.h"
#include "Dolphin/GX/GXBump.h"
#include "game/m_sound.h"
#include "game/rep_3880.h"
#include "game/gap_B7EF0.h"

// .text:0x000EDFAC size:0x110
void fn_3_EDFAC(void) {
    StaC5Bss_AEE0* bss = &lbl_3_bss_AEE0;
    u8 status = g_GameLogic.gameStatus;

    if (status == 0x21) {
        return;
    }
    if (status == 0xB) {
        if (bss->emittersPaused == 0) {
            fn_3_8B890(bss->emitter1C);
            fn_3_8B890(bss->emitter18);
            bss->emittersPaused = 1;
        }
    } else if (bss->emittersPaused != 0) {
        GameInitVariables* settings = &g_d_GameSettings;
        bss->emitter1C = fn_3_8BBC4(lbl_3_data_81DC[settings->StadiumID] + 6, NULL, 0, 4);
        bss->emitter18 = fn_3_8BBC4(lbl_3_data_81DC[settings->StadiumID] + 7, NULL, 0, 5);
        bss->emittersPaused = 0;
    } else {
        fn_3_8BA60(bss->emitter1C, NULL, NULL);
        fn_3_8BA60(bss->emitter18, NULL, NULL);
    }
}

// .text:0x000EE100 size:0x288 mapped:0x8072D194
void fn_3_EE100(void) {
    return;
}

// .text:0x000EE388 size:0x2F4 mapped:0x8072D41C
void fn_3_EE388(void) {
    return;
}

// .text:0x000EE67C size:0x2F0 mapped:0x8072D710
void fn_3_EE67C(struct DODisplayObj* dispObj, MtxPtr camera) {
    return;
}

// .text:0x000EE96C size:0x228 mapped:0x8072DA00
void fn_3_EE96C(Vec* pos) {
    return;
}

// .text:0x000EEB94 size:0x160 mapped:0x8072DC28
void fn_3_EEB94(void) {
    return;
}

// .text:0x000EECF4 size:0x148 mapped:0x8072DD88
void fn_3_EECF4(void) {
    return;
}

// .text:0x000EEE3C size:0xE8 mapped:0x8072DED0
void fn_3_EEE3C(void) {
    StaC5Actor* actor = lbl_3_bss_B55C->actor;
    StaC5Bone* bone;
    Vec pos;

    lbl_803C5090.unk1D = 1;
    fn_8003A144();
    SetDisplayStateTexture(fn_80039AB4(), 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    bone = actor->drawList;
    while (bone != NULL) {
        pos.x = bone->worldMtx[0][3];
        pos.y = bone->worldMtx[1][3];
        pos.z = bone->worldMtx[2][3];
        fn_3_EE96C(&pos);
        if (bone->dispObj != NULL) {
            DOSetWorldMatrix(bone->dispObj, bone->worldMtx);
            fn_3_EE67C(bone->dispObj, fn_80052734(fn_8005268C())->viewMtx);
        }
        bone = bone->next;
        GXSetTevDirect(GX_TEVSTAGE0);
    }
}

// .text:0x000EEF24 size:0x80 mapped:0x8072DFB8
void fn_3_EEF24(void) {
    if (g_hugeAnimStruct.displayObjects == 0) {
        fn_800B0A14_removeQueue();
    } else if (g_hugeAnimStruct.renderStadiumFlag != 0) {
        fn_800BDA24(lbl_3_bss_B55C);
        fn_3_EE388();
        fn_3_EEB94();
        fn_800A7D4C(1, &lbl_3_data_1BA5C[lbl_803CBBC0 * 8]);
    }
}

// .text:0x000EEFA4 size:0x2C mapped:0x8072E038
// .text:0x000EEFA4 size:0x2C mapped:0x8072E038
void fn_3_EEFA4(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
}

// .text:0x000EEFD0 size:0x4 mapped:0x8072E064
void fn_3_EEFD0(void) {
    return;
}

// .text:0x000EEFD4 size:0x244 mapped:0x8072E068
void fn_3_EEFD4(void) {
    return;
}

// .text:0x000EF218 size:0x4 mapped:0x8072E2AC
void fn_3_EF218(void) {
    return;
}

/* lbl_3_data_1B820 overlay (data addressed off this one base). */
typedef struct StaC5Data1B820 {
    /* 0x000 */ s32 emitter0;
    /* 0x004 */ u8 _pad4[0x154 - 0x4];
    /* 0x154 */ s32 emitPeriod[3];
    /* 0x160 */ f32 emitScale[3];
    /* 0x16C */ u8 _pad16C[0x174 - 0x16C];
    /* 0x174 */ f32 emitArg174;
} StaC5Data1B820;
extern StaC5Data1B820 lbl_3_data_1B820;
u8 fn_800527C4(Vec* pos);
void fn_80064430(Vec* pos, s32 type, f32 a, f32 b);

// .text:0x000EF21C size:0x1B8 mapped:0x8072E2B0
void fn_3_EF21C(StaC5SpotObj* obj) {
    StaC5Data1B820* d = &lbl_3_data_1B820;
    s32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (g_GameLogic.gameStatus != 2) {
        return;
    }
    if (!fn_800527C4((Vec*)&obj->x)) {
        return;
    }
    switch (obj->unkC6) {
    case 0:
        if (obj->unkC7 % d->emitPeriod[0] == 0) {
            fn_80064430((Vec*)&obj->x, 0, d->emitScale[0], 0.0f);
        }
        break;
    case 1:
        if (obj->unkC7 % d->emitPeriod[1] == 0) {
            fn_80064430((Vec*)&obj->x, 0, d->emitScale[1], 0.0f);
        }
        break;
    case 2:
        if (obj->unkC7 % d->emitPeriod[2] == 0) {
            fn_80064430((Vec*)&obj->x, 1, d->emitScale[2], d->emitArg174);
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0][8].vol;
            } else {
                vol = lbl_3_data_8404[stadium][8].vol;
            }
            vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 8, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                pan = lbl_3_data_84B8[0][8].pan;
            } else {
                pan = lbl_3_data_8404[stadium][8].pan;
            }
            sndFXCtrl(vid, 0x5B, pan);
        }
        break;
    }
}

// .text:0x000EF3D4 size:0x34 mapped:0x8072E468



void fn_3_EF3D4(UnknownStruct_EF3D4* arg0, u32 index) {
    /* * clrlslwi r0, r4, 24, 2 
     * This instruction clears the top 24 bits of r4 and shifts left by 2.
     * This is the compiler's way of doing (u8)index * 4.
     */
    u8 scaledIndex = (u8)index;
    
    /* * lwz r3, 0x74(r3)
     * lwzx r4, r4, r0 (where r4 is base of lbl_3_bss_B154)
     * bl fn_3_B97DC
     */
    fn_3_B97DC(arg0->unk74, lbl_3_bss_B154[scaledIndex]);
}

// .text:0x000EF408 size:0x154 mapped:0x8072E49C
void fn_3_EF408(StaC5SpotObj* obj) {
    Vec toSpot;
    Vec facing;
    Vec cross;
    f32 ang;
    f32 dot;

    toSpot.x = lbl_3_data_1B9A4[obj->spotIdx].x - obj->x;
    toSpot.y = 0.0f;
    toSpot.z = lbl_3_data_1B9A4[obj->spotIdx].z - obj->z;
    PSVECNormalize(&toSpot, &toSpot);
    ang = -(0.017453292f * obj->rot);
    facing.x = cos(ang);
    facing.y = 0.0f;
    facing.z = sin(ang);
    PSVECNormalize(&facing, &facing);
    dot = PSVECDotProduct(&toSpot, &facing);
    if (dot < -1.0) {
        dot = -1.0f;
    }
    obj->turnAngle = 57.29578f * (f32)acos(dot);
    PSVECCrossProduct(&toSpot, &facing, &cross);
    if (cross.y < 0.0f) {
        obj->turnDir = 1;
    } else {
        obj->turnDir = -1;
    }
    obj->unkC6 = 0;
}

// .text:0x000EF55C size:0x258 mapped:0x8072E5F0
u8 fn_3_EF55C(EF55C_Arg arg0, u8 arg1) {
    return 0;
}

// .text:0x000EF7B4 size:0x4C mapped:0x8072E848
// Forwards a by-value position and an index to fn_3_EF55C and returns whether it succeeded.
s32 fn_3_EF7B4(EF55C_Arg arg0, u8 arg1) {
    return fn_3_EF55C(arg0, arg1) != 0;
}

// .text:0x000EF800 size:0x90 mapped:0x8072E894
void fn_3_EF800(StaC5PlacedObj* obj) {
    if (obj->blinkTimer == 0) {
        CTRLSetTranslation(&obj->control, obj->pos.x, 100.0f, obj->pos.z);
    } else {
        if (obj->blinkTimer % 6 == 0) {
            obj->flag90_7 = 0;
        } else {
            obj->flag90_7 = 1;
        }
        obj->blinkTimer--;
    }
}

// .text:0x000EF890 size:0xA0 mapped:0x8072E924
static inline void fn_3_EF890_resetElems(OuterStruct_F13F8* arg0) {
    InnerStruct_F13F8* p = arg0->unk74;
    DeepStruct_F13F8* q = p->unk0;
    u32 i;

    for (i = 0; i < (u32)q->unk6; i++) {
        ElemStruct_F13F8* elem = q->unk18[i];
        elem->unk60 = 0;
        elem->unkA4 = 0;
    }
    arg0->unk74->unk58 = 0;
}

void fn_3_EF890(OuterStruct_F13F8* arg0) {
    fn_3_EF890_resetElems(arg0);
    CTRLSetScale(&arg0->control, 2.0f, 0.1f, 2.0f);
    arg0->unkC6 = 6;
    arg0->unkC7 = 0x4B;
}

// .text:0x000EF930 size:0x224 mapped:0x8072E9C4
void fn_3_EF930(StaC5PlacedObj* obj) {
    Quaternion q2;
    Quaternion q1;
    Vec cross;
    Vec delta;
    Vec dir;
    Vec axis = {0.0f, -1.0f, 0.0f};
    f32 ang;

    delta.x = 0.3 * (f32)cos(obj->unkB8);
    delta.y = obj->unkBC;
    delta.z = 0.3 * (f32)sin(obj->unkB8);
    PSVECAdd((Vec*)&obj->pos, &delta, (Vec*)&obj->pos);
    if (obj->unkBC < 0.0f && obj->pos.y - 1.0f < 0.0f) {
        obj->pos.x -= delta.x;
        obj->pos.y = 1.0f;
        obj->pos.z -= delta.z;
        obj->unkC6 = 6;
        obj->blinkTimer = 0x4B;
    } else {
        obj->unkBC -= 0.044;
    }
    C_QUATRotAxisRad(&q1, &axis, -(0.017453292f * obj->homeX));
    delta.y = -delta.y;
    dir.x = -delta.x;
    dir.y = -0.5f;
    dir.z = -delta.z;
    PSVECNormalize(&delta, &delta);
    PSVECNormalize(&dir, &dir);
    PSVECCrossProduct(&dir, &delta, &cross);
    ang = acos(PSVECDotProduct(&delta, &dir));
    if (ang != 1.0f && ang != -1.0f) {
        C_QUATRotAxisRad(&q2, &cross, ang);
        PSQUATMultiply(&q2, &q1, &q2);
        PSQUATNormalize(&q2, &q2);
        CTRLSetQuat(&obj->control, q2.x, q2.y, q2.z, q2.w);
    }
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
}

// .text:0x000EFB54 size:0x630 mapped:0x8072EBE8
void fn_3_EFB54(StadiumObjectElem* obj) {
    return;
}

// .text:0x000F0184 size:0xA0 mapped:0x8072F218
void fn_3_F0184(void) {
    u32 i;
    StadiumObjectElem* obj;

    if (lbl_3_bss_AEE0.unk8 != 0) {
        fn_800B0A14_removeQueue();
        lbl_3_bss_AEE0.unk8 = 0;
    } else {
        for (i = 0; i < lbl_3_bss_AEE0.unk33C; i++) {
            obj = &lbl_3_common_bss_350E4[0].src[i + lbl_3_bss_AEE0.unk33B];
            if (obj != NULL && obj->unkC6 == 3) {
                fn_3_EFB54(obj);
            }
        }
    }
}

// .text:0x000F0224 size:0x608 mapped:0x8072F2B8
void fn_3_F0224(void) {
    return;
}

// .text:0x000F082C size:0x778 mapped:0x8072F8C0
void fn_3_F082C(void) {
    return;
}

// .text:0x000F0FA4 size:0x454 mapped:0x80730038
void fn_3_F0FA4(void) {
    return;
}

// .text:0x000F13F8 size:0x50 mapped:0x8073048C
void fn_3_F13F8(OuterStruct_F13F8* arg0) {
    InnerStruct_F13F8* p = arg0->unk74;
    DeepStruct_F13F8* q = p->unk0;
    u32 i;

    for (i = 0; i < (u32)q->unk6; i++) {
        ElemStruct_F13F8* elem = q->unk18[i];
        elem->unk60 = 0;
        elem->unkA4 = 0;
    }
    arg0->unk74->unk58 = 0;
}

// .text:0x000F1448 size:0xD0 mapped:0x807304DC
void fn_3_F1448(StaC5SpotObj* obj) {
    obj->x = lbl_3_data_1B9A4[obj->spotIdx].x;
    obj->y = lbl_3_data_1B9A4[obj->spotIdx].y;
    obj->z = lbl_3_data_1B9A4[obj->spotIdx].z;
    obj->rot = -lbl_3_data_1B9A4[obj->spotIdx].rot;
    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, obj->x, -obj->y, obj->z);
    CTRLSetRotation(&obj->control, 0.0f, obj->rot, 0.0f);
    CTRLSetScale(&obj->control, 1.0f, 1.0f, 1.0f);
}

// .text:0x000F1518 size:0x15C mapped:0x807305AC
void fn_3_F1518(StaC5SpotObj* obj) {
    obj->unkC5 = lbl_3_data_1B9A4[obj->spotIdx].unk14;
    obj->unkC6 = 1;
    obj->unkC7 = 0;
    obj->unkC1 = -1;
    if (!obj->flag90_7) {
        obj->flag90_7 = 1;
    }
    obj->unk99 = 1;
    obj->unkB0 = 0.0f;
    obj->x = lbl_3_data_1B9A4[obj->spotIdx].x;
    obj->y = lbl_3_data_1B9A4[obj->spotIdx].y;
    obj->z = lbl_3_data_1B9A4[obj->spotIdx].z;
    obj->rot = -lbl_3_data_1B9A4[obj->spotIdx].rot;
    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, obj->x, -obj->y, obj->z);
    CTRLSetRotation(&obj->control, 0.0f, obj->rot, 0.0f);
    CTRLSetScale(&obj->control, 1.0f, 1.0f, 1.0f);
    fn_3_B97DC(obj->animState, lbl_3_bss_B154[0]);
    obj->animState->playAnim = 1;
    obj->unkC0 = 0;
}

// .text:0x000F1674 size:0xDC mapped:0x80730708
void fn_3_F1674(void) {
    s32 stadium = g_d_GameSettings.StadiumID;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0][5].vol;
    } else {
        vol = lbl_3_data_8404[stadium][5].vol;
    }
    vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 5, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        pan = lbl_3_data_84B8[0][5].pan;
    } else {
        pan = lbl_3_data_8404[stadium][5].pan;
    }
    sndFXCtrl(vid, 0x5B, pan);
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic.unk_13B = 1;
}

// .text:0x000F1750 size:0x154 mapped:0x807307E4
extern u8 lbl_3_bss_B219;

static inline void fn_3_F3A5C_inline(StaC5PlacedObj* obj, f32 x, f32 y, f32 z, f32 rotY) {
    obj->pos.x = x;
    obj->pos.y = y;
    obj->pos.z = z;
    obj->rotY = rotY;
    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation(&obj->control, 0.0f, rotY, 0.0f);
}

static inline void fn_3_F3AE0_inline(StaC5PlacedObj* obj) {
    obj->homeX = lbl_3_data_1B884[obj->targetIdx].pos.x;
    obj->homeZ = lbl_3_data_1B884[obj->targetIdx].pos.z;
    fn_3_F3A5C_inline(obj, obj->homeX, 10.0f, obj->homeZ, -lbl_3_data_1B884[obj->targetIdx].rot);
}

static inline void fn_3_F3BB0_inline(StaC5PlacedObj* obj) {
    fn_3_F3AE0_inline(obj);
    obj->unkC1 = 0;
    obj->flag90_7 = 1;
    obj->animState = &g_hugeAnimStruct.animTable->entries[lbl_3_bss_B219 + obj->targetIdx].anim;
    obj->unkC4 = 0;
    obj->unk99 = 1;
}

void fn_3_F1750(StaC5PlacedObj* obj, struct hugeAnimStruct* anim) {
    ActorAnimState* state = obj->animState;

    if (!fn_800B4A94((AnimLevel1*)state->actor, anim)) {
        fn_3_F3BB0_inline(obj);
    } else {
        AnimateActorBones(state->actor);
    }
}

// .text:0x000F18A4 size:0x98 mapped:0x80730938
extern u8 lbl_3_bss_B218;

void fn_3_F18A4(StaC5PlacedObj* obj) {
    ActorAnimState* state = &g_hugeAnimStruct.animTable->entries[lbl_3_bss_B218].anim;
    obj->animState = state;
    state->time = 0.0f;
    state->setTime = 1;
    fn_800B4CA0(state->actor, state->time);
    obj->rotY += 180.0;
    AnimateActorBones(state->actor);
}

// .text:0x000F193C size:0x4F0 mapped:0x807309D0
void fn_3_F193C(void) {
    return;
}

// .text:0x000F1E2C size:0x4D0 mapped:0x80730EC0
void fn_3_F1E2C(void) {
    return;
}

// .text:0x000F22FC size:0x14C mapped:0x80731390
void fn_3_F22FC(void) {
    return;
}

// .text:0x000F2448 size:0x2DC mapped:0x807314DC
void fn_3_F2448(void) {
    return;
}

// .text:0x000F2724 size:0x214 mapped:0x807317B8
void fn_3_F2724(void) {
    return;
}

// .text:0x000F2938 size:0x6C4 mapped:0x807319CC
void fn_3_F2938(void) {
    return;
}

// .text:0x000F2FFC size:0x1E4 mapped:0x80732090
void fn_3_F2FFC(void) {
    return;
}

// .text:0x000F31E0 size:0x5DC mapped:0x80732274
void fn_3_F31E0(void) {
    return;
}

// .text:0x000F37BC size:0x118 mapped:0x80732850
static inline u32 binomial(u32 n, u32 k) {
    u32 result = 1;
    u32 i;

    for (i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

u32 fn_3_F37BC(u32 n, u32 k) {
    u32 result = 1;
    u32 i;

    for (i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

// .text:0x000F38D4 size:0x130 mapped:0x80732968
extern u32 lbl_3_bss_B244[7];

void fn_3_F38D4(void) {
    u32 i;

    for (i = 0; i < 7; i++) {
        lbl_3_bss_B244[i] = binomial(6, i);
    }
}

// .text:0x000F3A04 size:0x58 mapped:0x80732A98
void fn_3_F3A04(OuterStruct_F13F8* arg0) {
    u32 i;
    for (i = 0; i < (u32)arg0->unk74->unk0->unk6; i++) {
        // Empty loop
    }
}

// .text:0x000F3A5C size:0x84 mapped:0x80732AF0
void fn_3_F3A5C(StaC5PlacedObj* obj, f32 x, f32 y, f32 z, f32 rotY) {
    fn_3_F3A5C_inline(obj, x, y, z, rotY);
}

// .text:0x000F3AE0 size:0xD0 mapped:0x80732B74
void fn_3_F3AE0(StaC5PlacedObj* obj) {
    fn_3_F3AE0_inline(obj);
}

// .text:0x000F3BB0 size:0x120 mapped:0x80732C44
void fn_3_F3BB0(StaC5PlacedObj* obj) {
    fn_3_F3BB0_inline(obj);
}

// .text:0x000F3CD0 size:0x22C mapped:0x80732D64
void fn_80033620(void);
void fn_80033F64(f32 a, f32 b, f32 c);

BOOL fn_3_F3CD0(struct Struct_800339F0_Result* obj) {
    StaC2Particle* p;
    s32 count;

    count = 0;
    p = (StaC2Particle*)obj->listHead;
    fn_80033620();
    do {
        if (p->unk48 <= 0 && p->unk4A != 0) {
            fn_80033F64(p->unk38, p->unk3C, p->unk20);
            fn_80033CC8(p, obj->field_0x10);
            if (-p->unk48 < 5) {
                p->unk38 = p->unk38 + (p->unk28 - 10.0) / 5.0;
                p->unk3C = p->unk38;
                p->unk43 += 12.0;
            } else {
                p->unk38 = p->unk38 + (p->unk2C - p->unk28) / 495.0f;
                p->unk3C = p->unk38;
                p->unk43 = p->unk43 + -60.0 / (0x1EF - p->unk4F);
                if (p->unk43 >= 0x3C) {
                    p->unk43 = 0;
                }
            }
            p->pos.x += p->vel.x;
            p->pos.y += p->vel.y;
            p->pos.z += p->vel.z;
            p->unk20 = p->unk1C * p->unk24 + p->unk20;
            p->unk4A--;
        }
        p->unk48--;
        if (p->unk4A != 0) {
            count++;
        }
        p = p->next;
    } while (p != NULL);
    return count == 0;
}

// .text:0x000F3EFC size:0x3A4 mapped:0x80732F90
void fn_3_F3EFC(void) {
    return;
}

// .text:0x000F42A0 size:0x3CC mapped:0x80733334
void fn_3_F42A0(void) {
    return;
}

// .text:0x000F466C size:0x30 mapped:0x80733700
// .text:0x000F466C size:0x30 mapped:0x80733700
void fn_3_27648(void);

void fn_3_F466C(void) {
    fn_3_27648();
    g_FieldingLogic.unk_13B = 1;
}

// .text:0x000F469C size:0x4 mapped:0x80733730
void fn_3_F469C(void) {
    return;
}

// .text:0x000F46A0 size:0x500 mapped:0x80733734
void fn_3_F46A0(void) {
    return;
}

// .text:0x000F4BA0 size:0xAC mapped:0x80733C34
void fn_3_F4BA0(StaC5DriftObj* obj) {
    Vec target;
    Vec diff;

    PSVECAdd(&obj->pos, &obj->vel, &obj->pos);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    target.x = lbl_3_data_1B884[obj->targetIdx].pos.x;
    target.y = lbl_3_data_1B884[obj->targetIdx].pos.y;
    target.z = lbl_3_data_1B884[obj->targetIdx].pos.z;
    PSVECSubtract(&target, &obj->pos, &diff);
    obj->vel.x = 0.2f * diff.x;
    obj->vel.z = 0.2f * diff.z;
}

// .text:0x000F4C4C size:0xB4 mapped:0x80733CE0
void fn_3_F4C4C(StaC5DriftObj* obj) {
    f32 rad;
    f32 s;
    f32 c;

    rad = -obj->angle;
    rad = 0.017453292f * rad;
    s = sin(rad);
    obj->vel.x = 3.0f * s;
    obj->vel.y = 0.0f;
    c = cos(rad);
    obj->vel.z = 3.0f * -c;
    PSVECScale(&obj->vel, -1.0f, &obj->vel);
}

// .text:0x000F4D00 size:0xAC mapped:0x80733D94
void fn_3_F4D00(StaC5DriftObj* obj) {
    Vec diff;
    Vec target;

    PSVECAdd(&obj->pos, &obj->vel, &obj->pos);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    target.x = lbl_3_data_1B884[obj->targetIdx].pos.x;
    target.y = lbl_3_data_1B884[obj->targetIdx].pos.y;
    target.z = lbl_3_data_1B884[obj->targetIdx].pos.z;
    PSVECSubtract(&target, &obj->pos, &diff);
    obj->vel.x = 0.2f * diff.x;
    obj->vel.z = 0.2f * diff.z;
}

// .text:0x000F4DAC size:0x210 mapped:0x80733E40
extern u8 lbl_3_bss_B21F;
extern u8 lbl_3_bss_B220;

void fn_3_F4DAC(void) {
    Vec v;
    Vec n;
    Vec ref = {0.0f, 0.0f, 1.0f};
    u8 step = 100 / lbl_3_bss_B220;
    u8 i = 0;
    f32 mag;
    f32 ang;
    f32 t;
    u8 r;
    StadiumObjectElem* obj;

    v.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    v.y = 0.0f;
    v.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    PSVECNormalize(&v, &n);
    mag = PSVECMag(&v);
    ang = 57.29578f * (f32)acos(PSVECDotProduct(&n, &ref));
    if (ang < 18.0f) {
        r = fn_3_B7F70(100);
        while (r / step) {
            step += 100 / lbl_3_bss_B220;
            i++;
        }
        obj = &lbl_3_common_bss_350E4[0].src[i + lbl_3_bss_B21F];
    } else if (n.x < 0.0f) {
        obj = &lbl_3_common_bss_350E4[0].src[lbl_3_bss_B21F];
    } else {
        obj = &lbl_3_common_bss_350E4[0].src[lbl_3_bss_B21F + 1];
    }
    t = ang / 45.0f;
    if (!(mag > 90.0 * (1.0 - t) + 73.0f * t)) {
        if (mag > 52.0f) {
            obj->unkC4 = 1;
        } else {
            obj->unkC4 = 2;
        }
    }
}

// .text:0x000F4FBC size:0x710 mapped:0x80734050
void fn_3_F4FBC(void) {
    return;
}

// .text:0x000F56CC size:0x564 mapped:0x80734760
void fn_3_F56CC(void) {
    return;
}

// .text:0x000F5C30 size:0x248 mapped:0x80734CC4
void fn_3_F5C30(StaC5DriftObj* obj) {
    obj->pos.x = lbl_3_data_1B884[obj->targetIdx].pos.x;
    obj->pos.y = lbl_3_data_1B884[obj->targetIdx].pos.y;
    obj->pos.z = lbl_3_data_1B884[obj->targetIdx].pos.z;
    obj->angle = -lbl_3_data_1B884[obj->targetIdx].rot;
    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation(&obj->control, 0.0f, obj->angle, 0.0f);
    obj->vel.x = obj->vel.y = obj->vel.z = 0.0f;
    if (obj->fx != NULL) {
        if (obj->fx->unk8 != 0) {
            fn_80033964((u32)obj->fx);
            obj->fx = NULL;
        } else {
            obj->fx = NULL;
        }
    }
    if (obj->partner != NULL) {
        fn_3_F3BB0_inline(obj->partner);
    }
    obj->unk99 = 1;
    obj->unkC4 = 0;
    if (lbl_3_data_1B820.emitter0 != -1) {
        fn_3_8B890(lbl_3_data_1B820.emitter0);
        lbl_3_data_1B820.emitter0 = -1;
    }
}

extern char lbl_3_rodata_2DB8[];
extern char lbl_3_rodata_2F10[];

// .text:0x000F5E78 size:0x84 mapped:0x80734F0C
s32 fn_3_F5E78(u8 arg0) {
    u32 i;
    for (i = lbl_3_common_bss_350E4[0].memcpyCount; i != 0; i--) {
        if (lbl_3_common_bss_350E4[0].idEntries[i - 1].id == arg0) {
            return i - 1;
        }
    }
    OSPanic(lbl_3_rodata_2DB8, 0x637, lbl_3_rodata_2F10);
    return 0;
}

// .text:0x000F5EFC size:0x2C mapped:0x80734F90
s32 fn_3_F5EFC(unknown_tri_compare* a, unknown_tri_compare* b) {
    u32 valA = a->value;
    u32 valB = b->value;

    if (valA < valB) {
        return -1;
    }
    return valA > valB;
}

// .text:0x000F5F28 size:0x24 mapped:0x80734FBC
s32 fn_3_F5F28(f32* a, f32* b) {
    f32 fa = *a;
    f32 fb = *b;
    if (fa < fb) {
        return -1;
    }
    return fa > fb;
}

// .text:0x000F5F4C size:0x138 mapped:0x80734FE0
void fn_3_F5F4C(MtxPtr m) {
    Vec ball;
    StadiumIdEntry* entry;
    StadiumObjectElem* elem;
    f32 nearZ;
    u32 i;

    memcpy(&ball, &g_Ball.AtBat_Contact_BallPos, sizeof(ball));
    PSMTXMultVec(m, &ball, &ball);
    for (i = 0; i < lbl_3_common_bss_350E4[0].memcpyCount; i++) {
        entry = &lbl_3_common_bss_350E4[0].idEntries[i];
        elem = &lbl_3_common_bss_350E4[0].src[entry->id];
        if (elem->flag90_80) {
            if (elem->unk9D == 1) {
                entry->unk0 = 1.0f;
            } else if (entry->unk0 < (nearZ = 2.0f + ball.z)) {
                entry->unk0 = 1.0f;
            } else if (entry->unk0 > 10.0f + ball.z) {
                entry->unk0 = 0.25f;
            } else {
                entry->unk0 = 1.0 - 0.75f * ((entry->unk0 - nearZ) / 8.0f);
            }
        }
    }
}

// .text:0x000F6084 size:0x480 mapped:0x80735118
void fn_3_F6084(void) {
    return;
}

// .text:0x000F6504 size:0xC4 mapped:0x80735598
struct StadiumModel* fn_3_F6504(s32 index, Mtx m) {
    StadiumObjectElem* obj = &lbl_3_common_bss_350E4[0].src[index];

    if (obj->unk9D == 2) {
        if (obj->unkC6 < 3 && g_Ball.ballState != 1) {
            CTRLBuildMatrix(&obj->control, m);
        } else {
            return NULL;
        }
    } else if (obj->unk9D == 0) {
        if (obj->unkC1 == 2) {
            return NULL;
        }
        if (g_Ball.AtBat_ContactResult >= 2) {
            return NULL;
        }
        CTRLBuildMatrix(&obj->control, m);
    } else {
        CTRLBuildMatrix(&obj->control, m);
    }
    return lbl_3_common_bss_350E4[0].src[index].unk_78;
}

extern u8 lbl_3_bss_B21A;

/* Local object control; the original local is 0x14 bytes larger than Control. */
typedef struct {
    Control control;
    u8 _pad3C[0x14];
} StaC5ObjControl;

// .text:0x000F65C8 size:0x100 mapped:0x8073565C
void fn_3_F65C8(s32* count) {
    StaC5ObjControl control;
    Mtx m;
    StadiumObjectElem* obj;
    struct StadiumModel* model;
    u16 start;

    obj = &lbl_3_common_bss_350E4[0].src[lbl_3_bss_B21A];
    start = lbl_3_common_bss_350E4[0].unk40[*count - 1] + lbl_3_common_bss_350E4[0].unk3C[*count - 1];
    lbl_3_common_bss_350E4[0].unk40[*count] = start;
    lbl_3_common_bss_350E4[0].unk44[start] = lbl_3_bss_B21A;
    lbl_3_common_bss_350E4[0].unk3C[*count]++;
    model = obj->unk_78;
    control.control.type = 0;
    CTRLBuildMatrix(&control.control, m);
    fn_3_B8464(m, model);
    fn_3_B8414(&lbl_3_common_bss_350E4[0].unk48[*count * 2].x, &lbl_3_common_bss_350E4[0].unk48[*count * 2 + 1].x);
    (*count)++;
}

// .text:0x000F66C8 size:0x270 mapped:0x8073575C
void fn_3_F66C8(void) {
    return;
}

// .text:0x000F6938 size:0x15C mapped:0x807359CC
void fn_3_F6938(void) {
    return;
}

// .text:0x000F6A94 size:0x1CC mapped:0x80735B28
extern u8 lbl_3_bss_B21D;
extern u8 lbl_3_bss_B21E;

void fn_3_F6A94(s32* count) {
    Control control;
    Mtx m;
    struct StadiumModel* model;
    u16 start;
    s32 i;
    s32 j;

    start = lbl_3_common_bss_350E4[0].unk40[*count - 1] + lbl_3_common_bss_350E4[0].unk3C[*count - 1];
    lbl_3_common_bss_350E4[0].unk40[*count] = start;
    j = start;
    for (i = 0; i < lbl_3_bss_B21E; i++) {
        lbl_3_common_bss_350E4[0].unk44[j] = lbl_3_bss_B21D + i;
        j++;
        lbl_3_common_bss_350E4[0].unk3C[*count]++;
    }
    fn_3_B8574();
    model = lbl_3_common_bss_350E4[0].src[lbl_3_bss_B21D].unk_78;
    control.type = 0;
    CTRLSetTranslation(&control, -50.0f, 0.0f, 40.0f);
    CTRLBuildMatrix(&control, m);
    fn_3_B8464(m, model);
    control.type = 0;
    CTRLSetTranslation(&control, 50.0f, -20.0f, 95.0f);
    CTRLBuildMatrix(&control, m);
    fn_3_B8464(m, model);
    if (lbl_3_common_bss_350E4[0].unk3C[*count] != 0) {
        fn_3_B8414(&lbl_3_common_bss_350E4[0].unk48[*count * 2].x, &lbl_3_common_bss_350E4[0].unk48[*count * 2 + 1].x);
        (*count)++;
    }
}

// .text:0x000F6C60 size:0x36C mapped:0x80735CF4
void fn_3_F6C60(void) {
    return;
}

// .text:0x000F6FCC size:0x10 mapped:0x80736060
void fn_3_F6FCC(void) {
    lbl_3_bss_AEE8 = TRUE;
}

// .text:0x000F6FDC size:0x1468 mapped:0x80736070
void fn_3_F6FDC(void) {
    return;
}



s32 fn_3_EE0BC(u32 arg0) {
    s32 val = (arg0 >> 4) & 0xF;
    switch (val) {
        case 0:
        case 1:
            return 1;
        case 2:
        case 3:
            return 2;
        case 4:
            return 4;
        default:
            return 0;
    }
}
