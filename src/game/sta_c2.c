#include "Dolphin/vec.h"
#include <string.h>
#include <math.h>
#include "game/sta_c2.h"
#include "game/rep_1838.h"
#include "game/rep_AC8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/rep_3448.h"
#include "game/gap_B7EF0.h"
#include "game/gap_6C854.h"
#include "game/m_sound.h"
#include "game/rep_540.h"
#include "game/rep_1D58.h"
#include "game/gap_16C410.h"
void fn_3_CB7E8(f32 x, f32 y, f32 z);
#include "musyx/musyx.h"
#include "Dolphin/gx.h"

extern f32 lbl_3_rodata_2664;
extern u8 lbl_800E8754[];
void fn_80033620(void);
void fn_8004C094(Vec* pos);
extern s32 lbl_3_data_182C4;
extern u8 lbl_3_bss_A02C;
extern u8 lbl_3_bss_A02D;
extern StadiumActorAnim lbl_3_bss_A034[];
extern char lbl_3_rodata_286C[];
extern char lbl_3_rodata_2878[];
extern u8 lbl_3_bss_A898[];
extern VecXYZ lbl_3_bss_A820[10];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_bss_A020;
extern DrawingSceneStruct* lbl_3_bss_A8A4;
extern f32 lbl_3_data_188E0;
extern Vec lbl_3_rodata_24E8[];
extern StaC2ChainParams lbl_3_bss_A8A8;
extern StaC2D501CEntry lbl_3_bss_A8D0[4];
extern const Vec lbl_3_rodata_25F8;

static inline void staC2PlaceTrio(void) {
    Mtx m;
    Vec v;
    f32 ang;
    StadiumObjectElem* e;
    u32 i;
    u32 j;
    ActorAnimState* state;

    ang = shortAngleToRad(g_Minigame._1AF8);
    PSMTXRotRad(m, 'Y', 0.017453292f * -ang);
    v.x = 4.5f;
    v.y = 9.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, &v, &v);
    for (i = 0; i < lbl_3_common_bss_350E4[0].memcpyCount; i++) {
        if (lbl_3_common_bss_350E4[0].src[i].unk9D == 1) {
            break;
        }
    }
    for (j = i; j < i + 3; j++) {
        e = &lbl_3_common_bss_350E4[0].src[j];
        CTRLSetTranslation(&e->control, g_Minigame._1AE0 + v.x, g_Minigame._1AE4 - v.y, g_Minigame._1AE8 + v.z);
        state = (ActorAnimState*)e->unk74;
        e->unkAC_u8 = (j % 3) * 30;
        e->unkA0 = 0.0f;
        state->time = e->unkA0;
        state->setTime = 1;
        fn_800B4CA0(state->actor, state->time);
    }
}

// .text:0x000CB8A8 size:0x1F4 mapped:0x8070A93C
void fn_3_CB8A8(StadiumObjectElem* e) {
    switch (e->unkCA) {
    case 0:
        fn_80025EEC(e->unk8C, 0, 2);
        staC2PlaceTrio();
        break;
    case 3:
        fn_80025EEC(e->unk8C, 0, 4);
        break;
    case 1:
        fn_80025EEC(e->unk8C, 0, 3);
        break;
    default:
        fn_80025EEC(e->unk8C, 0, 1);
        break;
    }
}

// .text:0x000CBA9C size:0x60 mapped:0x8070AB30
void fn_3_CBA9C(ActorObject* arg0) {
    hugeAnimStruct* has = (hugeAnimStruct*)arg0->wrapper->boneData;
    u8 byte_ca = arg0->field_0xca;
    AnimLevel1* level1 = has->entries_18->field_0x0;
    AnimLevel2* level2 = level1->ptr14;
    AnimLevel4* level4 = level2->ptr10;
    AnimObject* obj = level4->ptr04;

    if (byte_ca == 0) {
        obj->field_0x74 &= ~0x1FFF;
        obj->field_0x74 |= 0x3;
    } else {
        obj->field_0x74 &= ~0x1FFF;
        obj->field_0x74 |= 0x2;
    }
}

// .text:0x000CBAFC size:0x11C mapped:0x8070AB90
void fn_3_CBAFC(StaC2ChainObj* obj) {
    StaC2D501CEntry* entries = obj->entries;
    Mtx m;
    Vec axis = {0.0f, 1.0f, 0.0f};
    Vec zero = {0.0f, 0.0f, 0.0f};
    Vec v;

    PSMTXRotAxisRad(m, &axis, 0.017453292f * obj->angle);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y += 4.5;
    entries[3].unkC[0] = v;
    entries[3].unkC[1] = entries[3].unkC[0];
    fn_3_D1F2C(&lbl_3_bss_A8A8, obj->entries, 4, &zero, obj);
}

// .text:0x000CBC18 size:0x368 mapped:0x8070ACAC
void fn_3_CBC18(void) {
    return;
}

// .text:0x000CBF80 size:0x254 mapped:0x8070B014
void fn_3_CBF80(struct StaC2ChainObj* obj) {
    return;
}

// .text:0x000CC1D4 size:0x180 mapped:0x8070B268
void fn_3_CC1D4(void) {
    Mtx m;
    Vec v;
    f32 ang;
    StadiumObjectElem* e;
    u32 i;
    u32 j;
    ActorAnimState* state;

    ang = shortAngleToRad(g_Minigame._1AF8);
    PSMTXRotRad(m, 'Y', 0.017453292f * -ang);
    v.x = 4.5f;
    v.y = 9.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, &v, &v);
    for (i = 0; i < lbl_3_common_bss_350E4[0].memcpyCount; i++) {
        if (lbl_3_common_bss_350E4[0].src[i].unk9D == 1) {
            break;
        }
    }
    for (j = i; j < i + 3; j++) {
        e = &lbl_3_common_bss_350E4[0].src[j];
        CTRLSetTranslation(&e->control, g_Minigame._1AE0 + v.x, g_Minigame._1AE4 - v.y, g_Minigame._1AE8 + v.z);
        state = (ActorAnimState*)e->unk74;
        e->unkAC_u8 = (j % 3) * 30;
        e->unkA0 = 0.0f;
        state->time = e->unkA0;
        state->setTime = 1;
        fn_800B4CA0(state->actor, state->time);
    }
}

static inline void staC2InitEntries4(StaC2D501CEntry* entries) {
    StaC2D501CEntry* entry;
    u32 i;

    if (entries == NULL) {
        return;
    }
    entry = entries;
    for (i = 0; i < 4; i++, entry++) {
        if (i == 3) {
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
            entry->unk3C = 1;
        } else {
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
        }
        entry->unk4 = 1.0f / entry->unk0;
        memset(entry->unkC, 0, 0x18);
        memset(entry->unk24, 0, 0xC);
        memset(entry->unk30, 0, 0xC);
    }
}

static inline void staC2InitChainParams(StaC2ChainParams* p, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, s32 n) {
    p->unk0 = a;
    p->unk4 = b;
    p->unk8 = c;
    p->unkC = d;
    p->unk10 = e;
    p->unk14 = f;
    p->unk20 = n;
    p->unk18 = 1.0f / p->unk20 / 60.0f;
    p->unk1C = p->unk18 * p->unk18;
    p->unk24 = 1.0f / (2.0f * p->unk18);
}

// .text:0x000CC354 size:0xE4 mapped:0x8070B3E8
void fn_3_CC354(StaC2D501CEntry* entries) {
    StaC2D501CEntry* entry;
    u32 i;

    if (entries == NULL) {
        return;
    }
    entry = entries;
    for (i = 0; i < 4; i++, entry++) {
        if (i == 3) {
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
            entry->unk3C = 1;
        } else {
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
        }
        entry->unk4 = 1.0f / entry->unk0;
        memset(entry->unkC, 0, 0x18);
        memset(entry->unk24, 0, 0xC);
        memset(entry->unk30, 0, 0xC);
    }
}

// .text:0x000CC438 size:0x18C mapped:0x8070B4CC
void fn_3_CC438(void) {
    staC2InitChainParams(&lbl_3_bss_A8A8, 1.755f, 0.5f, 300.0f, 20.0f, 1.5f, 0.001f, 8);
    staC2InitEntries4(lbl_3_bss_A8D0);
}

// .text:0x000CC5C4 size:0x258 mapped:0x8070B658
void fn_3_CC5C4(StaC2ChainObj* obj) {
    obj->unkCA = g_Minigame._1B19;
    fn_80025EEC(obj->anim, 0, 2);
    obj->unkCB = obj->unkCA;
    obj->flag90 = 1;
    obj->control.type = 0;
    CTRLSetScale(&obj->control, 0.75f, 0.75f, 0.75f);
    obj->pos.x = g_Minigame._1AE0;
    obj->pos.y = g_Minigame._1AE4;
    obj->pos.z = g_Minigame._1AE8;
    obj->angle = shortAngleToRad(g_Minigame._1AF8);
    CTRLSetRotation(&obj->control, 0.0f, obj->angle, 0.0f);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    staC2InitChainParams(&lbl_3_bss_A8A8, 1.755f, 0.5f, 300.0f, 20.0f, 1.5f, 0.001f, 8);
    staC2InitEntries4(lbl_3_bss_A8D0);
    fn_3_CBF80(obj);
}

// .text:0x000CC81C size:0x408 mapped:0x8070B8B0
void fn_3_CC81C(void) {
    return;
}

// .text:0x000CCC24 size:0xD34 mapped:0x8070BCB8
void fn_3_CCC24(void) {
    return;
}

// .text:0x000CD958 size:0x10 mapped:0x8070C9EC
void fn_3_CD958(void) {
    lbl_3_bss_A81C = TRUE;
}

// .text:0x000CD968 size:0x1E0 mapped:0x8070C9FC
void fn_3_CD968(void) {
    return;
}

// .text:0x000CDB48 size:0x248 mapped:0x8070CBDC
void fn_3_CDB48(StaC2Particle* p, StaC2CDB48Src* src) {
    f32 ang;
    s32 n;

    ang = 0.017453292f * (rand() % 360);
    p->vel.x = 0.01 * (f32)cos(ang);
    p->vel.z = 0.01 * (f32)sin(ang);
    p->vel.y = 0.12f;
    p->unk1C = 0.5f;
    p->unk1C += ((u32)rand() % 2500) / 1000.0;
    p->unk38 = 2.0 * p->unk1C;
    p->unk3C = 6.0 * p->unk1C;
    p->unk20 = (rand() % 101) / 100.0;
    n = rand() % 24 + 72;
    p->unk4A = n;
    p->unk4F = n;
    p->pos.x = src->pos.x;
    p->pos.y = src->pos.y;
    p->pos.z = src->pos.z;
    p->unk43 = p->unk24 = 255.0f;
    p->unk4A = p->unk4F;
    p->unk48 = 0;
}

// .text:0x000CDD90 size:0x214 mapped:0x8070CE24
void fn_3_CDD90(void) {
    return;
}

// .text:0x000CDFA4 size:0x5C8 mapped:0x8070D038
void fn_3_CDFA4(void) {
    return;
}

// .text:0x000CE56C size:0x378 mapped:0x8070D600
void fn_3_CE56C(void *arg0, u8 arg1) {
    return;
}

// .text:0x000CE8E4 size:0x70 mapped:0x8070D978
void fn_3_CE8E4(void) {
    u32 i = 0;
    do {
        void *obj = (void *)fn_80033A24(fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (obj != 0) {
            fn_3_CE56C(obj, (u8)i);
        }
        i++;
    } while (i < 4);
}

// .text:0x000CE954 size:0x268 mapped:0x8070D9E8
void fn_3_CE954(void) {
    return;
}

// .text:0x000CEBBC size:0xDC mapped:0x8070DC50
void fn_3_CEBBC(VecXYZ* pos, s32 idx) {
    s16 x;
    s16 y;

    fn_800528C0(pos->x, pos->y, pos->z, &x, &y);
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.x = x;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.y = y;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.z = 0.0f;
}

// .text:0x000CEC98 size:0x98 mapped:0x8070DD2C
void fn_3_CEC98(void) {
    s32 idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 8;

    lbl_3_bss_A898[idx] = 1;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000CED30 size:0x4 mapped:0x8070DDC4
void fn_3_CED30(void) {
    return;
}

// .text:0x000CED34 size:0x4 mapped:0x8070DDC8
void fn_3_CED34(void) {
    return;
}

// .text:0x000CED38 size:0x4 mapped:0x8070DDCC
void fn_3_CED38(void) {
    return;
}

// .text:0x000CED3C size:0x4 mapped:0x8070DDD0
void fn_3_CED3C(void) {
    return;
}

// .text:0x000CED40 size:0x11C mapped:0x8070DDD4
void fn_3_CED40(StaC2Particle* obj, s32 arg1) {
    fn_8003403C(obj->unk38, obj->unk3C);
    fn_80033CC8(obj, arg1);
    if (lbl_80366158._28) {
        return;
    }
    if (-obj->unk48 < 5) {
        obj->unk38 += 0.38;
        obj->unk3C += 0.38;
        obj->unk43 += 34.0;
    } else {
        obj->unk43 -= 4;
    }
    obj->pos.x += obj->vel.x;
    obj->pos.y += obj->vel.y;
    obj->pos.z += obj->vel.z;
}

// .text:0x000CEE5C size:0x14C mapped:0x8070DEF0
void fn_3_CEE5C(StaC2Particle* obj, s32 arg1) {
    fn_8003403C(obj->unk38, obj->unk3C);
    fn_80033CC8(obj, arg1);
    if (lbl_80366158._28) {
        return;
    }
    if (-obj->unk48 < 5) {
        obj->unk38 += 0.38;
        obj->unk3C += 0.38;
        obj->unk43 += 34.0;
    } else {
        obj->unk43 += -6.8;
    }
    obj->pos.x += obj->vel.x;
    obj->pos.y += obj->vel.y;
    obj->pos.z += obj->vel.z;
}

// .text:0x000CEFA8 size:0x2D0 mapped:0x8070E03C
void fn_3_CEFA8(void) {
    return;
}

// .text:0x000CF278 size:0x4B4 mapped:0x8070E30C
void fn_3_CF278(StadiumObjectElem* e, Vec pos) {
    return;
}

// .text:0x000CF72C size:0x200 mapped:0x8070E7C0
void fn_3_CF72C(s32 idx) {
    StadiumObjectElem* e = &lbl_3_common_bss_350E4[0].src[idx];
    Vec pos;
    Vec ballPos;
    s32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (g_Ball.AtBat_ContactResult < 2 && e->unkA4 != 1) {
        if (lbl_800E8754[4] != 0) {
            CTRLGetTranslation(&e->control, &pos.x, &pos.y, &pos.z);
            fn_3_CB7E8(pos.x, pos.y - 5.0f, pos.z);
            e->unkA4 = 1;
        }
        if (e->handleA0 != 0) {
            fn_80033964(e->handleA0);
            e->handleA0 = 0;
        }
        e->handleA0 = fn_80033A24(fn_3_CEFA8, 0x80, 0, 0x1E, 1, 0);
        if (e->handleA0 != 0) {
            ballPos.x = g_Ball.AtBat_Contact_BallPos.x;
            ballPos.y = g_Ball.AtBat_Contact_BallPos.y;
            ballPos.z = g_Ball.AtBat_Contact_BallPos.z;
            fn_3_CF278(e, ballPos);
        }
        e->unk8C = &lbl_3_bss_A034[e->unk9C];
        fn_80025EEC(e->unk8C, 0, 0);
        e->unk8C->unk1A = 1;
        e->unk8C->unk58 = -1;
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0][0].vol;
        } else {
            vol = lbl_3_data_8404[stadium][0].vol;
        }
        vid = sndFXStartEx(lbl_3_data_81DC[stadium], vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            pan = lbl_3_data_84B8[0][0].pan;
        } else {
            pan = lbl_3_data_8404[stadium][0].pan;
        }
        sndFXCtrl(vid, 0x5B, pan);
    }
}

// .text:0x000CF92C size:0x4 mapped:0x8070E9C0
void fn_3_CF92C(void) {
    return;
}

// .text:0x000CF930 size:0x158 mapped:0x8070E9C4
void fn_3_CF930(StaC2CF930Obj* obj) {
    StaC2CF930Anim* anim = obj->anim;
    if (anim != NULL) {
        u16 numFrames = anim->numFrames;
        f32 speed = anim->speed;
        f32 step;
        if (anim->curFrame == numFrames) {
            CTRLSetTranslation(&obj->control, lbl_3_data_18730[obj->posIdx].x, 5.0f, lbl_3_data_18730[obj->posIdx].z);
            obj->anim = NULL;
            obj->flag90 = 0;
        }
        step = 255.0f / (numFrames / speed);
        if (obj->alpha <= step) { obj->alpha = 0; } else { obj->alpha -= step; }
    }
    if (obj->link != NULL && obj->link->active == NULL) {
        obj->link = NULL;
    }
}

// .text:0x000CFA88 size:0x4 mapped:0x8070EB1C
void fn_3_CFA88(void) {
    return;
}

// .text:0x000CFA8C size:0x28 mapped:0x8070EB20
void fn_3_CFA8C(ActorObject* actor) {
    AnimateActorBones(actor->wrapper->boneData);
}

// .text:0x000CFAB4 size:0x90 mapped:0x8070EB48
void fn_3_CFAB4(StaC2Effect* effect, StaC2EffectParent* parent) {
    StaC2EffectScaleSrc* src = parent->owner->scaleSrc;

    effect->pos.x = effect->basePos.x;
    effect->pos.y = effect->basePos.y;
    effect->pos.z = effect->basePos.z;
    effect->scaleX = effect->scaleY = 3.0 * src->scale;
    effect->colorR = effect->colorG = effect->colorB = 0xFF;
    effect->alpha = 255.0 * src->scale;
    effect->duration = 30;
    effect->timer = 0;
}

// .text:0x000CFB44 size:0x214 mapped:0x8070EBD8
BOOL fn_3_CFB44(StaC2Emitter* em) {
    StaC2Particle* p = em->particles;
    StaC2D00D0Obj* owner = em->owner;
    s32 a;

    fn_80033620();
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    do {
        if (p->unk48 <= 0 && p->unk4A != 0) {
            fn_8003403C(p->unk38, p->unk3C);
            fn_80033CC8(p, em->unk10);
            p->unk38 += 0.1;
            if (p->unk38 < 0.0f) {
                p->unk38 = 0.0f;
            }
            p->unk3C += 0.1;
            if (p->unk3C < 0.0f) {
                p->unk3C = 0.0f;
            }
            a = p->unk43;
            a -= 8;
            if (a < 0) {
                a = 0;
            }
            p->unk43 = a;
            p->pos.x += p->vel.x;
            p->pos.y -= p->vel.y;
            p->pos.z += p->vel.z;
            p->unk4A--;
        }
        p->unk48--;
        if (p->unk4A == 0) {
            StaC2D00D0Src* f = em->owner->followSrc;
            p->pos.x = p->origin.x;
            p->pos.y = p->origin.y;
            p->pos.z = p->origin.z;
            p->unk38 = p->unk3C = 3.0 * f->unkBC;
            p->unk40[0] = p->unk40[1] = p->unk40[2] = 0xFF;
            p->unk43 = 255.0 * f->unkBC;
            p->unk4A = 30;
            p->unk48 = 0;
        }
    } while ((p = p->next) != NULL);
    if (owner->src->state == 0) {
        owner->handle = 0;
        return TRUE;
    }
    return FALSE;
}


// .text:0x000CFD58 size:0x374 mapped:0x8070EDEC
void fn_3_CFD58(StaC2D00D0Obj* obj) {
    return;
}

// .text:0x000D00CC size:0x4 mapped:0x8070F160
void fn_3_D00CC(void) {
    return;
}

// .text:0x000D00D0 size:0x1B0 mapped:0x8070F164
void fn_3_D00D0(Control* ctrl) {
    StaC2D00D0Obj* obj = (StaC2D00D0Obj*)ctrl;
    Vec pos;
    Control* follow = obj->follow;
    u8 state = obj->src->state;

    if (state == 0) {
        if (obj->flag90) {
            obj->flag90 = 0;
        }
        if (obj->alpha != 0xFF) {
            obj->alpha = 0xFF;
        }
        if (obj->handle != 0) {
            fn_80033964(obj->handle);
            obj->handle = 0;
        }
    } else {
        if (!obj->flag90) {
            obj->flag90 = 1;
        }
        if (obj->handle == 0) {
            obj->handle = fn_80033A24((void (*)(void))fn_3_CFB44, 0x80, 0, 0x1E, 0, 1);
            if (obj->handle != 0) {
                fn_3_CFD58(obj);
            }
        }
        CTRLSetRotation(&obj->control, 0.0f, obj->src->rotY, 0.0f);
        if (state == 3) {
            obj->alpha -= 1.7f;
            if (obj->alpha > 253.3f) {
                obj->alpha = 0;
            }
        }
    }
    CTRLGetTranslation(follow, &pos.x, &pos.y, &pos.z);
    CTRLSetTranslation(&obj->control, pos.x, pos.y, pos.z);
}

// .text:0x000D0280 size:0x4 mapped:0x8070F314
void fn_3_D0280(void) {
    return;
}

// .text:0x000D0284 size:0x20C mapped:0x8070F318
void fn_3_D0284(Control* ctrl) {
    StaC2D0284Obj* obj = (StaC2D0284Obj*)ctrl;
    u8 state = obj->src->state;
    f32 ang;
    s32 a;

    if (state == 0) {
        if (obj->flag90) {
            obj->flag90 = 0;
        }
        if (obj->alpha != 0xFF) {
            obj->alpha = 0xFF;
        }
        if (obj->scale != 1.0) {
            obj->scale = 1.0f;
        }
    } else {
        if (!obj->flag90) {
            obj->flag90 = 1;
        }
        CTRLSetRotation(&obj->control, 0.0f, obj->src->rotY, 0.0f);
        ang = 0.017453292f * (rand() % 360);
        obj->offset.x = obj->scale * (f32)cos(ang);
        obj->offset.z = obj->scale * (f32)sin(ang);
        CTRLSetTranslation(&obj->control, obj->base.x + obj->offset.x, 0.0f, obj->base.z + obj->offset.z);
        if (state == 3) {
            a = obj->alpha;
            a -= 1.7f;
            if (a < 0) {
                a = 0;
            }
            obj->alpha = a;
            obj->scale -= 0.006666666666666667;
            if (obj->scale < 0.0f) {
                obj->scale = 0.0f;
            }
        }
    }
}

// .text:0x000D0490 size:0x98 mapped:0x8070F524
void fn_3_D0490(void) {
    s32 idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2;

    lbl_3_bss_A898[idx] = 1;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_80371C30[lbl_3_bss_A8A4->unkIndex + idx].obj->pos.z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000D0528 size:0x4 mapped:0x8070F5BC
void fn_3_D0528(void) {
    return;
}

// .text:0x000D052C size:0x8 mapped:0x8070F5C0
s32 fn_3_D052C(void) {
    return 0;
}

// .text:0x000D0534 size:0x320 mapped:0x8070F5C8
void fn_3_D0534(void) {
    return;
}

// .text:0x000D0854 size:0xC4 mapped:0x8070F8E8
f32 fn_3_D0854(StaC2RangeObj* obj) {
    f32 min;
    f32 range;

    if (obj->dir > 0) {
        min = lbl_3_data_18364[obj->entryIdx].posMin;
        range = lbl_3_data_18364[obj->entryIdx].posRange;
    } else {
        min = lbl_3_data_18364[obj->entryIdx].negMin;
        range = lbl_3_data_18364[obj->entryIdx].negRange;
    }
    return min + range * (fn_3_B7F70(1000) / 1000.0);
}

// .text:0x000D0918 size:0x6EC mapped:0x8070F9AC
void fn_3_D0918(void) {
    return;
}

// .text:0x000D1004 size:0x10C mapped:0x80710098
void fn_3_D1004(StaC2SpinObj* obj, f32 x, f32 y, f32 z, f32 rotY, f32 angle) {
    StaC2Bone* bone = ((StaC2Model*)obj->wrapper->boneData)->bones[3];
    Vec axis = {0.0f, 1.0f, 0.0f};
    Quaternion q;

    obj->pos.x = x;
    obj->pos.y = y;
    obj->pos.z = z;
    obj->angle = angle;
    obj->ctrl.type = 0;
    CTRLSetTranslation(&obj->ctrl, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation(&obj->ctrl, 0.0f, rotY, 0.0f);
    C_QUATRotAxisRad(&q, &axis, 0.017453292f * obj->angle);
    PSQUATMultiply(&q, &obj->quat, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat(&bone->ctrl, q.x, q.y, q.z, q.w);
}

// .text:0x000D1110 size:0x16C mapped:0x807101A4
static inline void staC2PlaceSwing(StaC2D00D0Src* obj, StaC2BoneNode* node, f32 x, f32 y, f32 z, f32 rot) {
    Vec axis = lbl_3_rodata_25F8;
    Quaternion q;

    obj->pos.x = x;
    obj->pos.y = y;
    obj->pos.z = z;
    obj->rotY = 0.0f;
    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation(&obj->control, 0.0f, rot, 0.0f);
    C_QUATRotAxisRad(&q, &axis, 0.017453292f * obj->rotY);
    PSQUATMultiply(&q, &obj->quat, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat(&node->control, q.x, q.y, q.z, q.w);
}

void fn_3_D1110(StaC2D00D0Src* obj) {
    u8 idx = obj->idx;
    StaC2BoneNode* node = (*obj->actor)->bones->node;

    staC2PlaceSwing(obj, node, lbl_3_data_18364[idx].pos.x, lbl_3_data_18364[idx].pos.y, lbl_3_data_18364[idx].pos.z, lbl_3_data_18364[idx].rotY);
    obj->unkC8 = lbl_3_data_18364[obj->idx].pos.y;
    obj->unkBC = 0.0f;
    obj->unkC4 = 0.0f;
    obj->state = 0;
}

// .text:0x000D127C size:0x4 mapped:0x80710310
void fn_3_D127C(void) {
    return;
}

// .text:0x000D1280 size:0x19C mapped:0x80710314
void fn_3_D1280(StaC2D1280Obj* obj) {
    Vec mid;
    Vec diff;
    VecXYZ sndPos;
    f32 dist;
    s32 t;

    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0) {
        obj->control.type = 0;
    }
    fn_3_D141C(obj);
    PSVECAdd(&obj->endB->unkC[0], &obj->endA->unkC[0], &mid);
    PSVECScale(&mid, 0.5f, &mid);
    if (g_GameLogic.gameStatus == 2 && g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSVECSubtract(&mid, &obj->pos, &diff);
        dist = PSVECMag(&diff);
        t = obj->timer + 1;
        if (t < 0x100) {
            obj->timer = t;
        }
        if (dist >= 0.3f && obj->timer > 10) {
            memcpy(&sndPos, &obj->pos, sizeof(Vec));
            sndPos.y *= -1.0f;
            fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 6, &sndPos, 0, 14);
            obj->timer = 0;
        }
    }
    PSVECScale(&mid, 1.0f, &obj->pos);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetScale(&obj->control, 0.75f, 0.75f, 0.75f);
}

// .text:0x000D141C size:0x320 mapped:0x807104B0
void fn_3_D141C(StaC2D1280Obj* obj) {
    return;
}

// .text:0x000D173C size:0x10C mapped:0x807107D0
void fn_3_D173C(StaC2SpinObj* obj) {
    return;
}

// .text:0x000D1848 size:0x124 mapped:0x807108DC
void fn_3_D1848(StaC2D1848Obj* obj) {
    StaC2D1848Wrapper* w = obj->wrapper;
    if (*obj->trigger != 0) {
        if (obj->flag90) {
            obj->flag90 = 0;
            obj->timer = (obj->idx % 3) * 30;
            obj->frame = 0.0f;
            w->unk5C = obj->frame;
            w->unk59 = 1;
            fn_800B4CA0(w->boneData, w->unk5C);
        }
    } else if (obj->timer != 0) {
        if (obj->flag90) {
            obj->flag90 = 0;
        }
        obj->timer--;
    } else {
        if (!obj->flag90) {
            obj->flag90 = 1;
        }
        obj->frame += obj->speed;
        if (obj->frame > 100.0f) {
            obj->frame -= 100.0f;
            obj->timer = 90;
        }
        AnimateActorBones(w->boneData);
    }
}

// .text:0x000D196C size:0x158 mapped:0x80710A00
void fn_3_D196C(s32 idx) {
    StadiumObjectElem* e = &lbl_3_common_bss_350E4[0].src[idx];
    VecXYZ pos;
    s32 i;

    if (g_Ball.ballState == 1) {
        return;
    }
    if (e->unkCA == 0) {
        e->unk99 &= 0xFB;
        e->unkCC = 5;
        e->unkCB = e->unkCA;
        e->unkCA = 2;
        e->unkB0 = 0.5f;
        fn_80025EEC(e->unk8C, 0, 3);
    }
    memcpy(&pos, &g_Ball.AtBat_Contact_BallPos, sizeof(VecXYZ));
    pos.y *= -1.0f;
    fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 5, &pos, 0, 13);
    i = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0;
    lbl_3_bss_A898[i] = 1;
    lbl_3_bss_A820[i].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_A820[i].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_A820[i].z = g_Ball.AtBat_Contact_BallPos.z;
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic.unk_13B = 1;
}

// .text:0x000D1AC4 size:0x60 mapped:0x80710B58
void fn_3_D1AC4(ActorObject* arg0) {
    hugeAnimStruct* has = (hugeAnimStruct*)arg0->wrapper->boneData;
    u8 byte_ca = arg0->field_0xca;
    AnimLevel1* level1 = has->entries_18->field_0x0;
    AnimLevel2* level2 = level1->ptr14;
    AnimLevel4* level4 = level2->ptr10;
    AnimObject* obj = level4->ptr04;

    if (byte_ca == 0) {
        obj->field_0x74 &= ~0x1FFF;
        obj->field_0x74 |= 0x3;
    } else {
        obj->field_0x74 &= ~0x1FFF;
        obj->field_0x74 |= 0x2;
    }
}

// .text:0x000D1B24 size:0x408 mapped:0x80710BB8
void fn_3_D1B24(void) {
    return;
}

// .text:0x000D1F2C size:0x2F4 mapped:0x80710FC0
void fn_3_D1F2C(StaC2ChainParams* params, StaC2D501CEntry* entries, s32 count, Vec* force, StaC2ChainObj* obj) {
    return;
}

static inline void staC2UpdateChain8(StaC2ChainObj* obj) {
    StaC2D501CEntry* entries = obj->entries;
    Mtx m;
    Vec axis = {0.0f, 1.0f, 0.0f};
    Vec zero = {0.0f, 0.0f, 0.0f};
    Vec v;

    PSMTXRotAxisRad(m, &axis, 0.017453292f * obj->angle);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y += 4.5;
    entries[7].unkC[0] = v;
    entries[7].unkC[1] = entries[7].unkC[0];
    fn_3_D1F2C(&lbl_3_bss_A8A8, obj->entries, 8, &zero, obj);
}

// .text:0x000D2220 size:0x11C mapped:0x807112B4
void fn_3_D2220(StaC2ChainObj* obj) {
    StaC2D501CEntry* entries = obj->entries;
    Mtx m;
    Vec axis = {0.0f, 1.0f, 0.0f};
    Vec zero = {0.0f, 0.0f, 0.0f};
    Vec v;

    PSMTXRotAxisRad(m, &axis, 0.017453292f * obj->angle);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y += 4.5;
    entries[7].unkC[0] = v;
    entries[7].unkC[1] = entries[7].unkC[0];
    fn_3_D1F2C(&lbl_3_bss_A8A8, obj->entries, 8, &zero, obj);
}

// .text:0x000D233C size:0x160 mapped:0x807113D0
InMemBallType* fn_3_D233C(StaC2ChainObj* obj) {
    Mtx m;
    Vec diff;
    Vec dir;
    Vec fwd = {1.0f, 0.0f, 0.0f};
    Vec axis = {0.0f, 1.0f, 0.0f};
    Vec pos = obj->pos;

    if (g_Ball.AtBat_ContactResult >= 2) {
        return NULL;
    }
    pos.y = 4.5f;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &pos, &diff);
    diff.y = 0.0f;
    if (PSVECMag(&diff) < 23.0f) {
        PSVECNormalize(&diff, &diff);
        PSMTXRotAxisRad(m, &axis, 0.017453292f * obj->angle);
        PSMTXMultVec(m, &fwd, &dir);
        if (57.29578f * (f32)acos(PSVECDotProduct(&diff, &dir)) <= 60.0f) {
            return &g_Ball;
        }
    }
    return NULL;
}

// .text:0x000D249C size:0x4C mapped:0x80711530


int fn_3_D249C(Struct_800D249C_Arg0 *param_1) {
    Vec vStack_08; // Local vector at r1 + 0x8
    Struct_800D249C_C4 *temp_r4;

    // 0x000D24AC: lwz r4, 0xc4(r3)
    temp_r4 = param_1->ptr_0xC4;

    // 0x000D24B0: addi r3, r4, 0x1cc
    // 0x000D24B4: addi r4, r4, 0x0c
    // 0x000D24A8: addi r5, r1, 0x8
    PSVECSubtract(&temp_r4->field_0x1CC, &temp_r4->field_0x0C, &vStack_08);

    // 0x000D24BC: addi r3, r1, 0x8
    // 0x000D24C0: bl PSVECMag (result in f1)
    // We compare directly to avoid 'frsp' rounding instructions.
    return (f64)PSVECMag(&vStack_08) > lbl_3_rodata_2800;
}

// .text:0x000D24E8 size:0x74 mapped:0x8071157C
void fn_3_D24E8(StaC2D24E8Arg* arg0, s32 arg1) {
    Vec sp8;
    s8 fielderIndex;

    fielderIndex = arg1;
    PSVECSubtract((Vec*)((u8*)g_Fielders + (fielderIndex * sizeof(Fielder))), &arg0->field_0xA0, &sp8);
    sp8.y = lbl_3_rodata_2664;
    PSVECNormalize(&sp8, &sp8);
    fn_3_253A4(fielderIndex, (s16)fn_3_9FB8C(sp8.x, sp8.z));
}

// .text:0x000D255C size:0x128 mapped:0x807115F0
s8 fn_3_D255C(StaC2ChainObj* obj) {
    Vec diff;
    u8 orderA[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8 orderB[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u32 i;
    u8* order;

    if (obj->pos.y > 3.0) {
        return -1;
    }
    if (obj->pos.x > 0.0f) {
        order = orderA;
    } else {
        order = orderB;
    }
    for (i = 0; i < 9; i++) {
        Fielder* f = &g_Fielders[order[i]];
        if (f != NULL && f->unk210 == 0) {
            PSVECSubtract(&obj->pos, (Vec*)f->pos, &diff);
            if (PSVECMag(&diff) <= 4.5) {
                return (s8)order[i];
            }
        }
    }
    return -1;
}

// .text:0x000D2684 size:0x108 mapped:0x80711718
VecXYZ* fn_3_D2684(StaC2Object* obj) {
    Vec diff;
    u8 idsA[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8 idsB[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u32 i;
    AnimationStruct* anim;
    u8* list;

    if (obj->pos.x > 0.0f) {
        list = idsA;
    } else {
        list = idsB;
    }
    for (i = 0; i < 4; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[list[i]];
        if (anim != NULL) {
            PSVECSubtract((Vec*)&obj->pos, (Vec*)&anim->unk34, &diff);
            if (PSVECMag(&diff) <= 12.5f) {
                return &anim->unk34;
            }
        }
    }
    return NULL;
}

// .text:0x000D278C size:0x280 mapped:0x80711820
void fn_3_D278C(void) {
    return;
}

// .text:0x000D2A0C size:0x6C4 mapped:0x80711AA0
void fn_3_D2A0C(void) {
    return;
}

// .text:0x000D30D0 size:0x5E0 mapped:0x80712164
void fn_3_D30D0(void) {
    return;
}

// .text:0x000D36B0 size:0x1D0 mapped:0x80712744
void fn_3_D36B0(StaC2ChainObj* obj) {
    obj->pos.y += obj->velY;
    obj->velY -= 0.04f;
    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        if (!(obj->unk99 & 4)) {
            obj->unkCB = obj->unkCA;
            obj->unkCA = 1;
            fn_80025EEC(obj->anim, 0, 1);
        }
        obj->unk99 &= 0xFB;
        fn_8004C094(&obj->pos);
    }
    staC2UpdateChain8(obj);
    CTRLSetRotation(&obj->control, 0.0f, obj->angle, 0.0f);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
}

// .text:0x000D3880 size:0x45C mapped:0x80712914
void fn_3_D3880(void) {
    return;
}

// .text:0x000D3CDC size:0x278 mapped:0x80712D70
void fn_3_D3CDC(void) {
    return;
}

// .text:0x000D3F54 size:0x82C mapped:0x80712FE8
void fn_3_D3F54(void) {
    return;
}

// .text:0x000D4780 size:0x524 mapped:0x80713814
void fn_3_D4780(StaC2PlacedObj* obj) {
    return;
}

static inline void staC2PlaceObj(StaC2PlacedObj* obj) {
    obj->control.type = 0;
    CTRLSetScale(&obj->control, 0.75f, 0.75f, 0.75f);
    if (obj->unkCA == 0) {
        CTRLSetRotation(&obj->control, lbl_3_data_182C8[obj->idx].rotB.x, -lbl_3_data_182C8[obj->idx].rotB.y, lbl_3_data_182C8[obj->idx].rotB.z);
        obj->angle = -lbl_3_data_182C8[obj->idx].rotB.y;
    } else {
        CTRLSetRotation(&obj->control, lbl_3_data_182C8[obj->idx].rotA.x, -lbl_3_data_182C8[obj->idx].rotA.y, lbl_3_data_182C8[obj->idx].rotA.z);
        obj->angle = -lbl_3_data_182C8[obj->idx].rotA.y;
    }
    CTRLSetTranslation(&obj->control, lbl_3_data_182C8[obj->idx].pos.x, lbl_3_data_182C8[obj->idx].pos.y, lbl_3_data_182C8[obj->idx].pos.z);
    obj->pos.x = lbl_3_data_182C8[obj->idx].pos.x;
    obj->pos.y = -lbl_3_data_182C8[obj->idx].pos.y;
    obj->pos.z = lbl_3_data_182C8[obj->idx].pos.z;
    fn_3_D4780(obj);
}

// .text:0x000D4CA4 size:0x15C mapped:0x80713D38
void fn_3_D4CA4(StaC2PlacedObj* obj) {
    obj->control.type = 0;
    CTRLSetScale(&obj->control, 0.75f, 0.75f, 0.75f);
    if (obj->unkCA == 0) {
        CTRLSetRotation(&obj->control, lbl_3_data_182C8[obj->idx].rotB.x, -lbl_3_data_182C8[obj->idx].rotB.y, lbl_3_data_182C8[obj->idx].rotB.z);
        obj->angle = -lbl_3_data_182C8[obj->idx].rotB.y;
    } else {
        CTRLSetRotation(&obj->control, lbl_3_data_182C8[obj->idx].rotA.x, -lbl_3_data_182C8[obj->idx].rotA.y, lbl_3_data_182C8[obj->idx].rotA.z);
        obj->angle = -lbl_3_data_182C8[obj->idx].rotA.y;
    }
    CTRLSetTranslation(&obj->control, lbl_3_data_182C8[obj->idx].pos.x, lbl_3_data_182C8[obj->idx].pos.y, lbl_3_data_182C8[obj->idx].pos.z);
    obj->pos.x = lbl_3_data_182C8[obj->idx].pos.x;
    obj->pos.y = -lbl_3_data_182C8[obj->idx].pos.y;
    obj->pos.z = lbl_3_data_182C8[obj->idx].pos.z;
    fn_3_D4780(obj);
}

// .text:0x000D4E00 size:0x21C mapped:0x80713E94
void fn_3_D4E00(StaC2PlacedObj* obj) {
    obj->unkCA = rand() % 10;
    if (obj->unkCA < 3) {
        obj->unkCA = 0;
        fn_80025EEC(obj->anim, 0, 2);
    } else {
        obj->unkCA = 1;
        fn_80025EEC(obj->anim, 0, 1);
    }
    obj->unkCB = obj->unkCA;
    obj->flag90 = 1;
    staC2PlaceObj(obj);
    obj->unk99 = 0;
    obj->unkC8 = 1;
    if (lbl_3_data_182C4 != -1) {
        fn_3_8B890(lbl_3_data_182C4);
        lbl_3_data_182C4 = -1;
    }
    obj->unkCD = 1;
}

// .text:0x000D501C size:0x100 mapped:0x807140B0
void fn_3_D501C(StaC2D501CEntry* entries) {
    StaC2D501CEntry* entry;
    u32 i;

    if (entries == NULL) {
        return;
    }
    memset(entries, 0, 0x40);
    entry = entries;
    for (i = 0; i < 8; i++, entry++) {
        if (i == 7) {
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
            entry->unk3C = 1;
        } else {
            if (i == 0) {
                entry->unk3C = 1;
            }
            entry->unk0 = lbl_3_data_188E0;
            entry->unk8 = 0.504375f;
        }
        entry->unk4 = 1.0f / entry->unk0;
        memset(entry->unkC, 0, 0x18);
        memset(entry->unk24, 0, 0xC);
        memset(entry->unk30, 0, 0xC);
    }
}

// .text:0x000D511C size:0x2A4 mapped:0x807141B0
void fn_3_D511C(void) {
    return;
}

// .text:0x000D53C0 size:0x84 mapped:0x80714454
s32 fn_3_D53C0(u8 arg0) {
    u32 i;
    for (i = lbl_3_common_bss_350E4[0].memcpyCount; i > 0; i--) {
        if (lbl_3_common_bss_350E4[0].idEntries[i - 1].id == arg0) {
            return i - 1;
        }
    }
    OSPanic(lbl_3_rodata_286C, 0x863, lbl_3_rodata_2878);
    return 0;
}

// .text:0x000D5444 size:0x2C mapped:0x807144D8
s32 fn_3_D5444(unknown_tri_compare* a, unknown_tri_compare* b) {
    u32 valA = a->value;
    u32 valB = b->value;

    if (valA < valB) {
        return -1;
    }
    
    // In Metrowerks, (u32 > u32) generates the sequence:
    // xor -> cntlzw -> slw -> srwi
    return valA > valB;
}

// .text:0x000D5470 size:0x24 mapped:0x80714504
s32 fn_3_D5470(f32* a, f32* b) {
    f32 fa = *a;
    f32 fb = *b;

    if (fa < fb) {
        return -1;
    }
    return fa > fb;
}

// .text:0x000D5494 size:0x158 mapped:0x80714528
void fn_3_D5494(Mtx m) {
    Vec pos;
    StadiumIdEntry* entry;
    u32 i;
    u8 type;
    f32 lim;

    memcpy(&pos, &g_Ball.AtBat_Contact_BallPos, sizeof(Vec));
    PSMTXMultVec(m, &pos, &pos);
    for (i = 0; i < lbl_3_common_bss_350E4[0].memcpyCount; i++) {
        entry = &lbl_3_common_bss_350E4[0].idEntries[i];
        if (lbl_3_common_bss_350E4[0].src[entry->id].flag90_80) {
            type = lbl_3_common_bss_350E4[0].src[entry->id].unk9D;
            if (type == 0 || (u8)(type - 4) <= 1 || (type > 7 && type < 11)) {
                entry->unk0 = 1.0f;
            } else {
                lim = 2.0f + pos.z;
                if (entry->unk0 < lim) {
                    entry->unk0 = 1.0f;
                } else if (entry->unk0 > 10.0f + pos.z) {
                    entry->unk0 = 0.25f;
                } else {
                    entry->unk0 = 1.0 - 0.75f * ((entry->unk0 - lim) / 8.0f);
                }
            }
        }
    }
}

// .text:0x000D55EC size:0x580 mapped:0x80714680
void fn_3_D55EC(void) {
    return;
}

// .text:0x000D5B6C size:0x120 mapped:0x80714C00
void fn_3_D5B6C(s32* count) {
    StaC2ControlExt control;
    Mtx m;
    StadiumObjectElem* obj;
    u16 start;

    start = lbl_3_common_bss_350E4[0].unk40[*count - 1] + lbl_3_common_bss_350E4[0].unk3C[*count - 1];
    lbl_3_common_bss_350E4[0].unk40[*count] = start;
    lbl_3_common_bss_350E4[0].unk44[start] = lbl_3_bss_A020;
    lbl_3_common_bss_350E4[0].unk3C[*count]++;
    obj = &lbl_3_common_bss_350E4[0].src[lbl_3_bss_A020];
    control = *(StaC2ControlExt*)&obj->control;
    CTRLBuildMatrix(&control.control, m);
    fn_3_B8464(m, obj->unk_78);
    fn_3_B8414(&lbl_3_common_bss_350E4[0].unk48[*count * 2].x, &lbl_3_common_bss_350E4[0].unk48[*count * 2 + 1].x);
    (*count)++;
}

// .text:0x000D5C8C size:0x1F4 mapped:0x80714D20
void fn_3_D5C8C(void) {
    return;
}

// .text:0x000D5E80 size:0x240 mapped:0x80714F14
void fn_3_D5E80(void) {
    return;
}

// .text:0x000D60C0 size:0x230 mapped:0x80715154
void fn_3_D60C0(void) {
    return;
}

// .text:0x000D62F0 size:0x224 mapped:0x80715384
void fn_3_D62F0(s32* count) {
    StaC2ControlExt control;
    Mtx m;
    StadiumObjectElem* obj;
    u16 start;
    s32 i;
    s32 idx;

    for (i = 0; i < lbl_3_bss_A02D; i++) {
        start = lbl_3_common_bss_350E4[0].unk40[*count - 1] + lbl_3_common_bss_350E4[0].unk3C[*count - 1];
        lbl_3_common_bss_350E4[0].unk40[*count] = start;
        idx = lbl_3_bss_A02C + i;
        lbl_3_common_bss_350E4[0].unk44[start] = idx;
        lbl_3_common_bss_350E4[0].unk3C[*count]++;
        obj = &lbl_3_common_bss_350E4[0].src[idx];
        control = *(StaC2ControlExt*)&obj->control;
        CTRLBuildMatrix(&control.control, m);
        fn_3_B8464(m, obj->unk_78);
        CTRLSetTranslation(&control.control, 14.250000447034836 + lbl_3_data_182C8[obj->unk9C].pos.x,
                           -(9.375f + lbl_3_data_182C8[obj->unk9C].pos.y),
                           14.250000447034836 + lbl_3_data_182C8[obj->unk9C].pos.z);
        CTRLBuildMatrix(&control.control, m);
        fn_3_B8464(m, obj->unk_78);
        CTRLSetTranslation(&control.control, lbl_3_data_182C8[obj->unk9C].pos.x - 14.250000447034836,
                           -(9.375f + lbl_3_data_182C8[obj->unk9C].pos.y),
                           lbl_3_data_182C8[obj->unk9C].pos.z - 14.250000447034836);
        CTRLBuildMatrix(&control.control, m);
        fn_3_B8464(m, obj->unk_78);
        if (lbl_3_common_bss_350E4[0].unk3C[*count] != 0) {
            fn_3_B8414(&lbl_3_common_bss_350E4[0].unk48[*count * 2].x, &lbl_3_common_bss_350E4[0].unk48[*count * 2 + 1].x);
            (*count)++;
        }
    }
}

// .text:0x000D6514 size:0x2B8 mapped:0x807155A8
void fn_3_D6514(void) {
    return;
}

// .text:0x000D67CC size:0x2244 mapped:0x80715860
void fn_3_D67CC(void) {
    return;
}
