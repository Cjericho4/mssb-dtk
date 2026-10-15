#include "game/rep_1D58.h"
#include "game/UnknownHomes_Game.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "stl/math.h"
#include "game/m_sound.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXPixel.h"

extern f32 lbl_3_data_11178[5];



static struct StadiumObject* lbl_3_bss_190C;
static u8 lbl_3_bss_1902;
static u8 lbl_3_bss_1940[0x8000];
static struct StadiumObject* lbl_3_bss_9940;

// .text:0x000B7FC8 size:0x108 mapped:0x806F705C
void fn_3_B7FC8(s32 soundID, s32 arg1) {
    VecXYZ pos = {0.0f, 0.0f, 37.0f};
    f32 angle;

    angle = 0.017453292f * lbl_3_data_11178[rand() % 5];
    pos.x += 100.0f * (f32)cos(angle);
    pos.y += -30.0f;
    pos.z += 100.0f * (f32)sin(angle);
    fn_3_8BBC4(soundID, &pos, 0, arg1);
}

// .text:0x000B80D0 size:0xB4 mapped:0x806F7164
void fn_3_B80D0(void) {
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

// .text:0x000B8184 size:0xF8 mapped:0x806F7218
void fn_3_B8184(C2310Holder* holder, MtxPtr camera) {
    Mtx viewMtx;
    Mtx ctrlMtx;
    C2310Actor* actor;
    C2310Bone* bone;

    CTRLBuildMatrix(&lbl_3_bss_190C->control, ctrlMtx);
    if (ctrlMtx[1][3] > 0.0f && g_d_GameSettings.StadiumID == 1) {
        return;
    }
    PSMTXConcat(camera, ctrlMtx, viewMtx);
    actor = holder->actor;
    bone = actor->drawList;
    if (actor->skinObject != NULL) {
        if (actor->unk7C != 0) {
            fn_8003A8A0(actor->skinObject, viewMtx, 1);
        } else {
            DOVARenderSkin(actor->skinObject, viewMtx, actor->skinMtxArray, actor->skinInvTransposeMtxArray, 0, NULL);
        }
    }
    while (bone != NULL) {
        if (bone->dispObj != NULL) {
            DOSetWorldMatrix(bone->dispObj, bone->worldMtx);
            fn_8003A8A0(bone->dispObj, viewMtx, 0);
        }
        bone = bone->next;
    }
}

// .text:0x000B827C size:0x10 mapped:0x806F7310
struct StadiumObject* fn_3_B827C(void) {
    return lbl_3_bss_190C;
}

// .text:0x000B828C size:0xC mapped:0x806F7320
void fn_3_B828C(struct StadiumObject* arg0) {
    lbl_3_bss_190C = arg0;
}

// .text:0x000B8298 size:0x17C mapped:0x806F732C
void fn_3_B8298(void) {
    return;
}

// .text:0x000B8414 size:0x50 mapped:0x806F74A8
void fn_3_B8414(f32* arg0, f32* arg1) {
    memcpy(arg0, &lbl_3_bss_1910.unk0, 0xC);
    memcpy(arg1, &lbl_3_bss_1910.unkC, 0xC);
}

// .text:0x000B8464 size:0x110 mapped:0x806F74F8
void fn_3_B8464(Mtx m, struct StadiumModel* model) {
    return;
}

// .text:0x000B8574 size:0x34 mapped:0x806F7608
//register Swaps

void fn_3_B8574(void) {
    lbl_3_bss_1910.unk0 = 10000.0f;
    lbl_3_bss_1910.unk4 = 10000.0f;
    lbl_3_bss_1910.unk8 = 10000.0f;
    lbl_3_bss_1910.unkC = -10000.0f;
    lbl_3_bss_1910.unk10 = -10000.0f;
    lbl_3_bss_1910.unk14 = -10000.0f;
}

// .text:0x000B85A8 size:0x34 mapped:0x806F763C

/**
 * @address 000B85A8
 */

/**
 * @address 000B85A8
 */

/**
 * @address 000B85A8
 */
u32 fn_3_B85A8(s32 index, u32* outPtr) {
    /* Anchoring: slwi for index happens before the addi for the global base. 
       We use element 0 of the global array. */
    UnknownStruct_350E4* bss = &lbl_3_common_bss_350E4[0];

    /* * Matches:
     * lwz r3, 0x40(r7)   -> Load pointer unk40
     * lwz r6, 0x44(r7)   -> Load pointer unk44
     * lhzx r3, r3, r5    -> Load u16 from unk40[index]
     * slwi r3, r3, 2     -> Multiply loaded u16 by 4
     * add r3, r6, r3     -> Offset unk44 by that value
     */
    *outPtr = (u32)&bss->unk44[bss->unk40[index]];

    /* * Matches:
     * lwz r3, 0x3c(r7)   -> Load pointer unk3C
     * lwzx r3, r3, r0    -> Load u32 from unk3C[index]
     */
    return bss->unk3C[index];
}

// .text:0x000B85DC size:0x7C mapped:0x806F7670

void fn_3_B85DC(s32 index, void* dest, void* src2, void* src) {
    UnknownStruct_350E4* base = &lbl_3_common_bss_350E4[0];
    u32 offset1 = index * 0x18;
    u32 offset2 = (index << 1) + 1;
    offset2 *= 0x0C;
    
    memcpy(dest, (u8*)base->unk48 + offset1, 0x0C);
    memcpy(src2, (u8*)base->unk48 + offset2, 0x0C);
}

// .text:0x000B8658 size:0x24 mapped:0x806F76EC
s32 fn_3_B8658(f32* a, f32* b) {
    f32 fa = *a;
    f32 fb = *b;
    if (fa < fb) {
        return -1;
    }
    return fa > fb;
}

// .text:0x000B867C size:0x1AC mapped:0x806F7710
void fn_3_B867C(void) {
    return;
}

// .text:0x000B8828 size:0x3E0 mapped:0x806F78BC
void fn_3_B8828(void) {
    return;
}

// .text:0x000B8C08 size:0x424 mapped:0x806F7C9C
void fn_3_B8C08(void) {
    return;
}

// .text:0x000B902C size:0x60 mapped:0x806F80C0

void fn_3_B902C(void) {
    if (lbl_3_bss_1904 != NULL) {
        memcpy(lbl_3_common_bss_350E4[0].src, lbl_3_bss_1904, lbl_3_common_bss_350E4[0].memcpyCount * 0xe8);
        fn_800ACFB0(lbl_3_bss_1904);
        lbl_3_bss_1904 = NULL;
    }
}

// .text:0x000B908C size:0x98 mapped:0x806F8120
void fn_3_B908C(void) {
    if (lbl_3_bss_1904 == NULL) {
        UnknownStruct_350E4* bss = &lbl_3_common_bss_350E4[0];
        lbl_3_bss_1904 = _OSAllocFromHeap(0x20, bss->memcpyCount * 0xE8);
        memcpy(lbl_3_bss_1904, lbl_3_common_bss_350E4[0].src, bss->memcpyCount * 0xE8);
    }
    memcpy(lbl_3_common_bss_350E4[0].src, lbl_3_common_bss_350E4[0].dest, lbl_3_common_bss_350E4[0].memcpyCount * 0xE8);
    lbl_3_common_bss_350E4[0].unk66 = lbl_3_common_bss_350E4[0].unk68;
}

// .text:0x000B9124 size:0x48 mapped:0x806F81B8

void fn_3_B9124(void) {
    // 1. Calculate size and copy data
    // Assembly: mulli r5, r0, 0xe8 -> (count * 232)
    memcpy(lbl_3_common_bss_350E4->dest, 
           lbl_3_common_bss_350E4->src, 
           lbl_3_common_bss_350E4->memcpyCount * 0xE8);

    // 2. Perform the halfword copy
    // Assembly: lha r0, 0x66(r3); sth r0, 0x68(r3);
    lbl_3_common_bss_350E4->unk68 = lbl_3_common_bss_350E4->unk66;
}

// .text:0x000B916C size:0x5C mapped:0x806F8200
BALL_COLLISION_TYPE processStadiumObjectFunction(s32, s32 index, BALL_COLLISION_TYPE ret, CollisionStruct* outCollision) {
    if (index < (s32)lbl_3_common_bss_350E4[0].memcpyCount) {
        if (lbl_3_common_bss_350E4[0].src[index].fnPtr != NULL) {
            lbl_3_common_bss_350E4[0].src[index].fnPtr(index, ret, outCollision);
        }
    }
}

// .text:0x000B91C8 size:0x1D4 mapped:0x806F825C
void fn_3_B91C8(void) {
    return;
}

// .text:0x000B939C size:0x28 mapped:0x806F8430
void fn_3_B939C(void) {
    // Evaluation of (x == 2) triggers the subfic/cntlzw/extrwi pattern
    lbl_3_common_bss_350E4[0].unk6C = (g_GameLogic.gameStatus == 2);
}

// .text:0x000B93C4 size:0x4 mapped:0x806F8458
void fn_3_B93C4(void) {
    return;
}

// .text:0x000B93C8 size:0x4 mapped:0x806F845C
void fn_3_B93C8(s32) {
    return;
}

// .text:0x000B93CC size:0x140 mapped:0x806F8460
void fn_3_B93CC(void) {
    return;
}

// .text:0x000B950C size:0x4 mapped:0x806F85A0
void fn_3_B950C(void) {
    return;
}

// .text:0x000B9510 size:0x14 mapped:0x806F85A4
void fn_3_B9510(int idx) {
    lbl_3_data_11168[idx] = 1;
}

// .text:0x000B9524 size:0x10 mapped:0x806F85B8
void fn_3_B9524(void) {
    lbl_3_bss_1902 = 0;
}

// .text:0x000B9534 size:0xB8 mapped:0x806F85C8
u8* fn_3_B9534(s32 width, s32 height, GXTexObj* texObj) {
    if (lbl_3_bss_1902 != 0 || texObj == NULL) {
        return NULL;
    }
    lbl_3_bss_1902 = 1;
    GXInitTexObj(texObj, lbl_3_bss_1940, width, height, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    return lbl_3_bss_1940;
}

// .text:0x000B95EC size:0x1DC mapped:0x806F8680
void fn_3_B95EC(void) {
    return;
}

// .text:0x000B97C8 size:0x14 mapped:0x806F885C
void fn_3_B97C8(struct StadiumObject* arg0) {
    if (arg0 != NULL) {
        lbl_3_bss_9940 = arg0;
    }
}

// .text:0x000B97DC size:0x10C mapped:0x806F8870
void fn_3_B97DC(ActorAnimState* state, ANIMBank* bank) {
    s32 loop;

    if (state == NULL || bank == NULL) {
        return;
    }
    state->bank = bank;
    state->seqNum = 0;
    state->time = 0.0f;
    state->playAnim = 1;
    state->setTime = (bank != NULL);
    state->setSpeed = (bank != NULL);
    state->startTime = 0.0f;
    state->loopFlags = 3;
    state->time = 0.0f;
    state->setTime = 1;
    state->speed = 1.0f;
    state->setSpeed = 1;
    state->unk68 = 0;
    state->playAnim = 1;
    if (state->playAnim) {
        ACTSetAnimation(state->actor, state->bank, NULL, state->seqNum, state->startTime);
        fn_800B4BC8(state->actor, 1);
    }
    if (state->setTime) {
        fn_800B4CA0(state->actor, state->time);
    }
    if (state->setSpeed) {
        fn_800B4C04(state->actor, state->speed);
    }
    loop = state->loopFlags & 1;
    if (loop) {
        fn_800B4AFC(state->actor, loop);
    }
}

// .text:0x000B98E8 size:0xFC mapped:0x806F897C
void fn_3_B98E8(C2310Holder* holder) {
    u32 i;
    C2310Bone* bone;

    for (i = 0; i < holder->actor->totalBones; i++) {
        bone = holder->actor->boneArray[i];
        bone->info = _OSAllocFromHeap(0x20, sizeof(B98E8BoneInfo));
        bone->info->unk0 = 0.0f;
        bone->info->unk4 = 0.0f;
        bone->info->unk8 = 1.0f;
        bone->info->unkC = 0;
        bone->info->unk10 = 0;
        bone->info->unk16 = 0;
        bone->info->unk17 = 1;
        bone->info->unk18 = 1;
        bone->info->unk14 = 0;
    }
}

// .text:0x000B99E4 size:0x1D0 mapped:0x806F8A78
void fn_3_B99E4(void) {
    return;
}

// .text:0x000B9BB4 size:0x1B4 mapped:0x806F8C48
void fn_3_B9BB4(void) {
    return;
}

// .text:0x000B9D68 size:0x250 mapped:0x806F8DFC
void fn_3_B9D68(void) {
    return;
}

// .text:0x000B9FB8 size:0x198 mapped:0x806F904C
void fn_3_B9FB8(void) {
    return;
}
