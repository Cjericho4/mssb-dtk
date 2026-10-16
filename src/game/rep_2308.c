#include "game/rep_2308.h"
#include <string.h>
#include <math.h>
#include "UnknownHeaders.h"
#include "game/rep_1F58.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"
#include "game/rep_1E08.h"
#include "game/rep_1D58.h"

typedef struct {
    union {
        /* 0x00 */ u32 unk[4];
        /* 0x00 */ Quaternion quat;
    };
} RepCAE00Params; /* size: 0x10 */

typedef struct {
    /* 0x00 */ u8 _pad0[0x14];
    /* 0x14 */ Vec pos;
    /* 0x20 */ RepCAE00Params params;
    /* 0x30 */ u16 frames;
    /* 0x32 */ u8 slot;
    /* 0x33 */ u8 charIndex;
    /* 0x34 */ u8 done;
} RepCAE00Obj;

typedef struct RepCAE00Entry {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ void (*callback)(void);
    /* 0x08 */ Vec pos;
    /* 0x14 */ RepCAE00Params params;
    /* 0x24 */ u32 frames;
} RepCAE00Entry; /* size: 0x28 */

extern RepCAE00Obj* lbl_3_data_17D10[2];
extern RepCAE00Entry lbl_3_data_17D18[2][2];
extern s32 lbl_3_data_17D08[2];
void fn_3_15C024(Vec* pos, Vec* vel, Vec* accel, s32 arg3);
s32 fn_8005268C(void);
u32 fn_80024DB0(CommonBss32724Timer* timer);
void fn_80024FA4(AnimLevel1** anim, s32 arg1, CommonBss32724Timer* timer, s32 arg3);
void fn_800BDA24(AnimLevel1** anim);
void fn_800BDA94(AnimLevel1** anim, Mtx mtx);

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(RepCAE00Entry* entry) {
    Mtx m;
    s32 ids[3];
    CommonBss32724Timer* timers[3];
    ActorAnimState* anim;
    f32 scale;
    s32 i;
    CommonBss32724Timer* t;

    scale = lbl_3_data_17D08[0] / 100000.0f;
    anim = (ActorAnimState*)&lbl_3_common_bss_35154.unk10[1].unk34;
    ids[0] = lbl_3_common_bss_35154.unkF8;
    timers[0] = &lbl_3_common_bss_35154.timerD8;
    ids[1] = lbl_3_common_bss_35154.unk154;
    timers[1] = &lbl_3_common_bss_35154.timer134;
    ids[2] = lbl_3_common_bss_35154.unk1B0;
    timers[2] = &lbl_3_common_bss_35154.timer190;
    PSMTXQuat(m, &entry->params.quat);
    PSMTXScaleApply(m, m, scale, scale, scale);
    PSMTXTransApply(m, m, entry->pos.x, entry->pos.y, entry->pos.z);
    PSMTXConcat(fn_80052734(fn_8005268C())->viewMtx, m, m);
    i = 2;
    do {
        t = timers[i];
        t->unk0 = 0.0f;
        t->unkC = 0;
        t->unk4 = entry->frames;
        fn_80024DB0(t);
        fn_80024FA4((AnimLevel1**)anim, ids[i], timers[i], -1);
    } while (i-- != 0);
    ((AnimLevel1*)anim->actor)->unk99 = 1;
    ACTSetAnimation(anim->actor, anim->bank, NULL, anim->seqNum, 0.0f, anim->startTime);
    fn_800B4CA0(anim->actor, entry->frames);
    fn_800B4C04(anim->actor, 1.0f);
    fn_800BDA24((AnimLevel1**)anim);
    ((AnimLevel1*)anim->actor)->animFlags = 0xFF;
    fn_800BDA94((AnimLevel1**)anim, m);
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
void fn_3_CAE00(void) {
    RepCAE00Obj* obj = (RepCAE00Obj*)lbl_803CC1B8;
    AnimationStruct* anim = g_hugeAnimStruct.AnimationStructPtrs[obj->charIndex];

    if (obj->done == 0 && anim != NULL) {
        fn_800A7D4C(0, (BdcArrayElement*)&lbl_3_data_17D18[obj->slot][lbl_803CBBC0]);
        lbl_3_data_17D18[obj->slot][lbl_803CBBC0].frames = obj->frames;
        lbl_3_data_17D18[obj->slot][lbl_803CBBC0].pos.x = obj->pos.x;
        lbl_3_data_17D18[obj->slot][lbl_803CBBC0].pos.y = obj->pos.y;
        lbl_3_data_17D18[obj->slot][lbl_803CBBC0].pos.z = obj->pos.z;
        lbl_3_data_17D18[obj->slot][lbl_803CBBC0].params = obj->params;
        if (lbl_80366158._28 == 0) {
            obj->frames++;
        }
    } else {
        lbl_3_data_17D10[obj->slot] = NULL;
        fn_800B0A14_removeQueue();
    }
    if (obj->frames >= lbl_3_common_bss_35154.timerD8.unk18) {
        lbl_3_data_17D10[obj->slot] = NULL;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void fn_3_CAF9C(void) {
    RepCAE00Obj* obj = (RepCAE00Obj*)fn_800B0A5C_insertQueue(fn_3_CAE00, 1);
    Vec pos;
    Vec vel;
    Vec accel;
    s32 n;
    s32 i;

    obj->frames = 0;
    obj->charIndex = g_Pitcher.rosterID;
    memcpy(&pos, &g_Pitcher.ballCurrentPosition, sizeof(Vec));
    memcpy(&vel, &g_Pitcher.ballVelocity, sizeof(Vec));
    memcpy(&accel, &g_Pitcher.pitchCurveVeloV1, sizeof(Vec));
    n = lbl_3_data_17D08[1];
    while (n-- != 0) {
        fn_3_15C024(&pos, &vel, &accel, 0);
    }
    obj->pos.x = pos.x;
    obj->pos.y = -pos.y;
    obj->pos.z = pos.z;
    pos.x -= g_Pitcher.ballCurrentPosition.x;
    pos.y -= g_Pitcher.ballCurrentPosition.y;
    pos.z -= g_Pitcher.ballCurrentPosition.z;
    pos.y = -pos.y;
    PSVECNormalize(&pos, &pos);
    vel.x = -1.0f;
    vel.y = 0.0f;
    vel.z = 0.0f;
    PSVECCrossProduct(&vel, &pos, (Vec*)&obj->params.quat);
    obj->params.quat.w = acos(PSVECDotProduct(&vel, &pos)) / 2.0;
    if (PSVECMag((Vec*)&obj->params.quat)) {
        PSVECNormalize((Vec*)&obj->params.quat, (Vec*)&obj->params.quat);
        PSVECScale((Vec*)&obj->params.quat, (f32)sin(obj->params.quat.w), (Vec*)&obj->params.quat);
    }
    obj->params.quat.w = cos(obj->params.quat.w);
    obj->done = i = 0;
    for (; i < 2; i++) {
        if (lbl_3_data_17D10[i] == NULL) {
            lbl_3_data_17D10[i] = obj;
            obj->slot = i;
            break;
        }
    }
}

// .text:0x000CB1B0 size:0x84 mapped:0x8070A244
void fn_3_CB1B0(s32 index, u8 arg1, s32 arg2) {
    u32 mask;
    AnimationStruct* anim;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES ||
        (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        if (arg2 == 0x23) {
            lbl_3_common_bss_35154.unk_467 = arg1;
            anim = g_hugeAnimStruct.AnimationStructPtrs[index];
            mask = lbl_3_common_bss_35154.bitfield;
            mask |= 0x10;
            lbl_3_common_bss_35154.unk_428.x = anim->unk34.x;
            lbl_3_common_bss_35154.unk_428.y = -anim->unk34.y;
            lbl_3_common_bss_35154.unk_428.z = anim->unk34.z;
            lbl_3_common_bss_35154.bitfield = mask;
        }
    }
}

// .text:0x000CB234 size:0x50 mapped:0x8070A2C8
void fn_3_CB234(s32 arg0, s32 arg1) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES ||
        (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        fn_3_C11CC(arg0, arg1);
    }
}

// .text:0x000CB284 size:0xC0 mapped:0x8070A318
void fn_3_CB284(s32 index, s32 arg1, f32 arg2) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES ||
        (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        if ((s8)lbl_3_common_bss_35154.unk_467 != 0 && arg1 == 0x23) {
            lbl_3_common_bss_35154.unk_428.x = g_hugeAnimStruct.AnimationStructPtrs[index]->unk34.x;
            lbl_3_common_bss_35154.unk_428.y = -g_hugeAnimStruct.AnimationStructPtrs[index]->unk34.y;
            lbl_3_common_bss_35154.unk_428.z = g_hugeAnimStruct.AnimationStructPtrs[index]->unk34.z;
            lbl_3_common_bss_35154.bitfield |= 0x10;
        }
        fn_3_C1344(index, arg1 == 30, 100.0f * arg2, 100.0f);
    }
}

