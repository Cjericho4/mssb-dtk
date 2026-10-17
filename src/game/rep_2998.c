#include "game/rep_2998.h"
#include "game/rep_23E8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "C3/control.h"
#include "Dolphin/vec.h"
#include "game/rep_1D58.h"
#include "game/sta_c2.h"
#include "math.h"
#include "game/gap_16C410.h"
#include "musyx/musyx.h"
#include "game/rep_540.h"
#include "game/rep_AC8.h"
#include "game/m_sound.h"
#include "game/gap_B7EF0.h"

// .text:0x000E1DB8 size:0x1F0 mapped:0x80720E4C
void fn_3_E1DB8(void) {
    Rep2998Bss* bss = &lbl_3_bss_AE00;

    if (g_GameLogic.gameStatus == 0x21) {
        return;
    }
    if (g_GameLogic.gameStatus == 0xB) {
        if (bss->active) {
            fn_3_8B890(bss->handle);
            bss->active = 0;
        }
        return;
    }
    if (!bss->active) {
        bss->handle = fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 5, NULL, 0, 6);
        bss->active = 1;
        bss->timerC = rand() % 900 + 100;
        bss->timer8 = rand() % 900 + 100;
    }
    if (bss->timerC <= 0) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 6, 7);
        bss->timerC = rand() % 900 + 100;
    } else {
        bss->timerC--;
    }
    if (bss->timer8 <= 0) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 7, 7);
        bss->timer8 = rand() % 900 + 100;
    } else {
        bss->timer8--;
    }
}

// .text:0x000E1FA8 size:0x8C mapped:0x8072103C
void fn_3_E1FA8(UnknownStruct_EF3D4* obj) {
    ActorAnimState* state = obj->unk74;
    Actor* actor = state->actor;
    if (state->time + state->speed > 900.0f) {
        state->time = 180.0f;
        state->setTime = 1;
        fn_800B4CA0(actor, state->time);
    }
    AnimateActorBones(actor);
    state->time += state->speed;
}

// .text:0x000E2034 size:0xE4 mapped:0x807210C8
void fn_3_E2034(CastleRotObj* obj) {
    Vec diff;
    Vec fwd = {0.0f, 0.0f, -1.0f};
    f32 angle;

    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&obj->pos, &diff);
    diff.y = 0.0f;
    PSVECNormalize(&diff, &diff);
    PSVECNormalize(&fwd, &fwd);
    angle = 57.29578f * (f32)acos(PSVECDotProduct(&diff, &fwd));
    if (diff.x < 0.0f) {
        angle = 360.0f - angle;
    }
    obj->curRotation = -angle;
    CTRLSetRotation(&obj->control, 0.0f, obj->curRotation, 0.0f);
}

// .text:0x000E2118 size:0x18C mapped:0x807211AC
void fn_3_E2118(s32 idx) {
    StadiumObjectElem* obj = &lbl_3_common_bss_350E4[0].src[idx];
    u32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (obj->unkC4 == 0 || obj->unkC4 == 5) {
        return;
    }
    if (obj->unkC8 != 0 && obj->unkC4 != 4) {
        if (g_Ball.AtBat_ContactResult > 1) {
            return;
        }
        obj->unkC9 = 1;
        obj->unkC4 = 4;
        obj->unkAC = lbl_3_bss_AE18[8];
        fn_3_B97DC((ActorAnimState*)obj->unk74, (ANIMBank*)obj->unkAC);
        ((ActorAnimState*)obj->unk74)->loopFlags = 2;
        fn_800B4AFC(((ActorAnimState*)obj->unk74)->actor, ((ActorAnimState*)obj->unk74)->loopFlags & 1);
        obj->unkB8 = ((ActorAnimState*)obj->unk74)->time;
        obj->unkCB = 8;
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0][2].vol;
        } else {
            vol = lbl_3_data_8404[stadium][2].vol;
        }
        vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 2, vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            pan = lbl_3_data_84B8[0][2].pan;
        } else {
            pan = lbl_3_data_8404[stadium][2].pan;
        }
        sndFXCtrl(vid, 0x5B, pan);
    }
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic.unk_13B = 1;
}

// .text:0x000E22A4 size:0x80 mapped:0x80721338
void fn_3_E22A4(Arg_E22A4 *arg0) {
    E22A4_Level6 *ptr = arg0->unk_74->unk_00->unk_10->unk_10->unk_00->unk_10->unk_04;
    u8 val;

    ptr->unk_04 &= ~0x1FFFU;

    if (arg0->unk_C4 == 0) {
        return;
    }

    val = arg0->unk_C8 + 1;

    if (arg0->unk_C4 == 1 || arg0->unk_C4 == 5) {
        if (arg0->unk_C5 % 2 == 0) {
            val = 0;
        }
    }

    ptr->unk_04 |= val;
}

// .text:0x000E2324 size:0x2AC mapped:0x807213B8
void fn_3_E2324(void) {
    return;
}

// .text:0x000E25D0 size:0x9C mapped:0x80721664
static inline void fn_3_E25D0_inline(castleThwompObj* arg, u32 idx) {
    arg->unkAC = lbl_3_bss_AE18[idx];
    fn_3_B97DC((ActorAnimState*)arg->actPtr, (ANIMBank*)arg->unkAC);
    if (idx != 0 && idx != 2 && idx != 3) {
        ((ActorAnimState*)arg->actPtr)->loopFlags = 2;
        fn_800B4AFC(((ActorAnimState*)arg->actPtr)->actor, ((ActorAnimState*)arg->actPtr)->loopFlags & 1);
    }
    arg->rotation.y = arg->actPtr->unk5C;
    arg->field37_0xcb = idx;
}

void fn_3_E25D0(castleThwompObj* arg, u32 idx) {
    fn_3_E25D0_inline(arg, idx);
}

// .text:0x000E266C size:0x270 mapped:0x80721700
void fn_3_E266C(void) {
    return;
}

// .text:0x000E28DC size:0xD8 mapped:0x80721970
BOOL fn_3_E28DC(castleThwompObj* obj) {
    VecXYZ pos;
    Vec diff;

    pos = obj->position;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&pos, &diff);
    diff.y = 0.0f;
    if (2.5 >= PSVECMag(&diff)) {
        fn_3_E25D0_inline(obj, 6);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000E29B4 size:0x1BC mapped:0x80721A48
BOOL fn_3_E29B4(castleThwompObj* obj) {
    static const f32 sSpeeds[3] = {0.8f, 1.0f, 1.2f};
    VecXYZ pos;
    Vec diff;

    pos = obj->position;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&pos, &diff);
    diff.y = 0.0f;
    if (5.5 * obj->rotation.x > PSVECMag(&diff)) {
        if (g_Ball.AtBat_Contact_BallPos.y >= 1.5 * obj->rotation.x && g_Ball.AtBat_Contact_BallPos.y <= 8.5 * obj->rotation.x) {
            if (g_Ball.AtBat_Contact_BallPos.y < 5.0 * obj->rotation.x) {
                fn_3_E25D0_inline(obj, 4);
            } else {
                fn_3_E25D0_inline(obj, 5);
            }
            {
                s16 i = fn_3_B7F70(3);
                ActorAnimState* st = (ActorAnimState*)obj->actPtr;
                st->speed = sSpeeds[i];
                st->setSpeed = 1;
            }
            fn_800B4C04(((ActorAnimState*)obj->actPtr)->actor, ((ActorAnimState*)obj->actPtr)->speed);
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000E2B70 size:0x308 mapped:0x80721C04
u8 fn_3_E2B70(CastleRotObj* obj) {
    return 0;
}

// .text:0x000E2E78 size:0xD4 mapped:0x80721F0C
void fn_3_E2E78(CastleRotObj* obj) {
    if (obj->shrinkTimer == 0) {
        obj->unkC8 = 0;
        obj->unkC4 = 0;
    } else {
        obj->scale -= 1.0857142857142859 / obj->shrinkFrames;
        obj->pos.y = -(1.2 * obj->scale);
        CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
        CTRLSetScale(&obj->control, obj->scale, obj->scale, obj->scale);
        obj->shrinkTimer--;
    }
}

extern u8 lbl_800E8754[];

// .text:0x000E2F4C size:0xF8 mapped:0x80721FE0
void fn_3_E2F4C(CastleRotObj* obj) {
    f32 angle;
    f32 x;

    f32 time = obj->animTime;
    f32 speed = obj->anim->speed;

    if (time >= 20.0 && time - speed < 20.0 && lbl_800E8754[4] != 0) {
        angle = -obj->curRotation;
        angle = 0.017453292f * angle;
        x = obj->scale * (5.0 * sinf_kludge(angle)) + obj->pos.x;
        fn_3_CB7E8(x, -2.0 * obj->scale, obj->scale * (-5.0 * cosf_kludge(angle)) + obj->pos.z);
    }
}

// .text:0x000E3044 size:0x240 mapped:0x807220D8
void fn_3_E3044(void) {
    return;
}

// .text:0x000E3284 size:0x3E4 mapped:0x80722318
u8 fn_3_E3284(CastleRotObj* obj) {
    return 0;
}

// .text:0x000E3668 size:0xFC mapped:0x807226FC
void fn_3_E3668(CastleRotObj* obj) {
    if (fn_3_E2B70(obj)) {
        fn_3_E3284(obj);
    } else {
        Vec fwd = {0.0f, 0.0f, -1.0f};
        Vec diff;
        f32 angle;

        PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&obj->pos, &diff);
        diff.y = 0.0f;
        PSVECNormalize(&diff, &diff);
        PSVECNormalize(&fwd, &fwd);
        angle = 57.29578f * (f32)acos(PSVECDotProduct(&diff, &fwd));
        if (diff.x < 0.0f) {
            angle = 360.0f - angle;
        }
        obj->curRotation = -angle;
        CTRLSetRotation(&obj->control, 0.0f, obj->curRotation, 0.0f);
    }
}

// .text:0x000E3764 size:0x1B0 mapped:0x807227F8
void fn_3_E3764(CastleRotObj* obj) {
    obj->shrinkTimer++;
    obj->scale += 1.0857142857142859 / obj->shrinkFrames;
    CTRLSetScale(&obj->control, obj->scale, obj->scale, obj->scale);
    obj->pos.y = -(1.2 * obj->scale);
    CTRLSetTranslation(&obj->control, obj->pos.x, -obj->pos.y, obj->pos.z);
    if (fn_3_E2B70(obj)) {
        if (fn_3_E3284(obj)) {
            return;
        }
    } else {
        Vec fwd = {0.0f, 0.0f, -1.0f};
        Vec diff;
        f32 angle;

        PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&obj->pos, &diff);
        diff.y = 0.0f;
        PSVECNormalize(&diff, &diff);
        PSVECNormalize(&fwd, &fwd);
        angle = 57.29578f * (f32)acos(PSVECDotProduct(&diff, &fwd));
        if (diff.x < 0.0f) {
            angle = 360.0f - angle;
        }
        obj->curRotation = -angle;
        CTRLSetRotation(&obj->control, 0.0f, obj->curRotation, 0.0f);
    }
    if (obj->shrinkTimer >= obj->shrinkFrames) {
        obj->unkC4 = 2;
    }
}

// .text:0x000E3914 size:0x274 mapped:0x807229A8
void fn_3_E3914(void) {
    return;
}

// .text:0x000E3B88 size:0x9CC mapped:0x80722C1C
void fn_3_E3B88(void) {
    return;
}

// .text:0x000E4554 size:0x54 mapped:0x807235E8
void fn_3_E4554(castleThwompObj *arg) {
    arg->unkAC = lbl_3_bss_AE18[0];
    fn_3_B97DC((ActorAnimState*)arg->actPtr, (ANIMBank*)arg->unkAC);
    arg->rotation.y = arg->actPtr->unk5C;
    arg->field37_0xcb = 0;
}

// .text:0x000E45A8 size:0x48 mapped:0x8072363C
void fn_3_E45A8(castleThwompObj *param) {
    CTRLSetScale(&param->control, 0.2f, 0.2f, 0.2f);
    param->rotation.x = 0.2f;
}

// .text:0x000E45F0 size:0x68 mapped:0x80723684
void fn_3_E45F0(CastleRotObj *arg0) {
    RotTableEntry *entries = lbl_3_data_18ED0.entries;
    CTRLSetRotation((Control*)arg0, 0.0f,
                    entries[arg0->rotIdx].rotValues[0], 0.0f);
    arg0->curRotation = entries[arg0->rotIdx].rotValues[0];
}

// .text:0x000E4658 size:0x108 mapped:0x807236EC
void fn_3_E4658(CastleRotObj* obj) {
    RotTableEntry* entries;

    obj->control.type = 0;
    CTRLSetTranslation(&obj->control, lbl_3_data_18ED0.defs[obj->rotIdx].pos.x, 0.24f + lbl_3_data_18ED0.defs[obj->rotIdx].pos.y, lbl_3_data_18ED0.defs[obj->rotIdx].pos.z);
    PSVECScale((Vec*)&lbl_3_data_18ED0.defs[obj->rotIdx].pos, 1.0f, (Vec*)&obj->pos);
    obj->pos.y -= 0.24f;
    entries = lbl_3_data_18ED0.entries;
    CTRLSetRotation(&obj->control, 0.0f, entries[obj->rotIdx].rotValues[0], 0.0f);
    obj->curRotation = entries[obj->rotIdx].rotValues[0];
    CTRLSetScale(&obj->control, 0.2f, 0.2f, 0.2f);
    obj->scale = 0.2f;
}

// .text:0x000E4760 size:0x170 mapped:0x807237F4
void fn_3_E4760(void) {
    return;
}

// .text:0x000E48D0 size:0x168 mapped:0x80723964
void fn_3_E48D0(void) {
    return;
}

// .text:0x000E4A38 size:0x1B0 mapped:0x80723ACC
void fn_3_E4A38(MtxPtr mtx, E4A38Model* model) {
    Vec v;
    Vec center;
    s32 n;
    u8* p;
    f32 minX;
    f32 minY;
    f32 minZ;
    f32 maxX;
    f32 maxY;
    f32 maxZ;
    s32 t;
    u16 count;

    minX = 10000.0f;
    maxX = -10000.0f;
    maxY = maxX;
    minY = minX;
    minZ = minX;
    maxZ = maxX;
    p = model->data;
    while (1) {
        count = ((E4A38PrimHdr*)p)->count;
        if (count == 0) {
            break;
        }
        t = count * 3;
        if (((E4A38PrimHdr*)p)->unk1 != 0) {
            t = count + 2;
        }
        n = t;
        p += sizeof(E4A38PrimHdr);
        do {
            if (lbl_3_bss_AE01 == 0) {
                PSMTXMultVec(mtx, &((E4A38Vtx*)p)->pos, &v);
            } else {
                PSVECScale(&((E4A38Vtx*)p)->pos, 1.0f, &v);
            }
            p += sizeof(E4A38Vtx);
            if (minX > v.x) minX = v.x;
            if (minY > v.y) minY = v.y;
            if (minZ > v.z) minZ = v.z;
            if (maxX < v.x) maxX = v.x;
            if (maxY < v.y) maxY = v.y;
            if (maxZ < v.z) maxZ = v.z;
        } while (--n != 0);
    }
    PSVECScale((Vec*)&g_Ball, 1.0f, &center);
}

// .text:0x000E4BE8 size:0xC8 mapped:0x80723C7C
typedef struct E4BE8Actor {
    u8 _pad0[0x18];
    AnimObjMtxHolder** boneArray; /* 0x18 */
} E4BE8Actor;

static inline StadiumObjectElem* getStadiumObj(s32 index) {
    return &lbl_3_common_bss_350E4[0].src[index];
}

struct StadiumModel* fn_3_E4BE8(s32 index, MtxPtr m) {
    Mtx boneMtx;
    StadiumObjectElem* obj = getStadiumObj(index);

    CTRLBuildMatrix(&obj->control, m);
    if (obj->unk9D == 0) {
        if (obj->unkC8 == 0 || obj->unkC4 == 0 || obj->unkC4 == 5 || obj->unkC4 == 4) {
            return NULL;
        }
        PSMTXCopy(((E4BE8Actor*)*obj->unk74)->boneArray[16]->mtxEC, boneMtx);
        PSMTXConcat(m, boneMtx, m);
    }
    return lbl_3_common_bss_350E4[0].src[index].unk_78;
}

// .text:0x000E4CB0 size:0x244 mapped:0x80723D44
void fn_3_E4CB0(s32* arg0, s32* arg1) {
    return;
}

// .text:0x000E4EF4 size:0xD0 mapped:0x80723F88
void fn_3_E4EF4(void) {
    UnknownStruct_350E4* p = lbl_3_common_bss_350E4;
    u32 n = p->memcpyCount;
    u32 size = n * sizeof(u16) + n * sizeof(u32) + n * sizeof(u32) + n * sizeof(VecXYZ) * 2;
    s32 a;
    s32 b;

    if (p->unk48 == NULL) {
        p->unk48 = _OSAllocFromHeap(4, size);
        lbl_3_common_bss_350E4[0].unk3C = (u32*)&p->unk48[p->memcpyCount * 2];
        lbl_3_common_bss_350E4[0].unk44 = lbl_3_common_bss_350E4[0].unk3C + p->memcpyCount;
        lbl_3_common_bss_350E4[0].unk40 = (u16*)(lbl_3_common_bss_350E4[0].unk44 + p->memcpyCount);
    }
    memset(p->unk48, 0, size);
    a = 0;
    b = 0;
    fn_3_E4CB0(&a, &b);
    lbl_3_common_bss_350E4[0].unk64 = a;
}

// .text:0x000E4FC4 size:0x8B8 mapped:0x80724058
void fn_3_E4FC4(void) {
    return;
}
