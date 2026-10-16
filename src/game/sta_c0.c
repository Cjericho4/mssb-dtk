#include "game/sta_c0.h"
#include "header_rep_data.h"
#include "game/rep_1D58.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXBump.h"
#include "game/m_sound.h"
#include "Dolphin/os.h"
#include "game/gap_16C410.h"

extern GXTexObj lbl_3_bss_9F4C;

// File-local .bss block, addressed off a common base.
typedef struct {
    /* 0x00 */ u8 _0[8];
    /* 0x08 */ s32 crowdEmitter;
    /* 0x0C */ s32 ambientEmitter;
    /* 0x10 */ u8 _10[0x34 - 0x10];
    /* 0x34 */ u8 paused;
} StaC0Bss_9F38;
extern StaC0Bss_9F38 lbl_3_bss_9F38;
extern u32 lbl_3_bss_9F3C;
extern s8* lbl_3_bss_9F48;
extern u32 fn_800247E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

// .text:0x000C9744 size:0x134 mapped:0x807087D8
void fn_3_C9744(void) {
    StaC0Bss_9F38* bss = &lbl_3_bss_9F38;
    GameInitVariables* gs = &g_d_GameSettings;

    if (gs->GameModeSelected == 2) {
        return;
    }
    if (g_GameLogic.gameStatus == 0x21) {
        return;
    }
    if (g_GameLogic.gameStatus == 0xB) {
        if (bss->paused == 0) {
            fn_3_8B890(bss->crowdEmitter);
            if (gs->GameModeSelected != 7) {
                fn_3_8B890(bss->ambientEmitter);
            }
            bss->paused = 1;
        }
    } else if (bss->paused != 0) {
        bss->crowdEmitter = fn_3_8BBC4(lbl_3_data_81DC[gs->StadiumID] + 1, NULL, 0, 1);
        if (gs->GameModeSelected != 7) {
            bss->ambientEmitter = fn_3_B7FC8(lbl_3_data_81DC[gs->StadiumID], 0);
        }
        bss->paused = 0;
    } else {
        fn_3_8BA60(bss->crowdEmitter, NULL, NULL);
        if (gs->GameModeSelected != 7) {
            fn_3_8BA60(bss->ambientEmitter, NULL, NULL);
        }
    }
}

// .text:0x000C9878 size:0x180 mapped:0x8070890C
void fn_3_C9878(void) {
    return;
}

// .text:0x000C99F8 size:0x68 mapped:0x80708A8C
void fn_3_C99F8(ActorObject *arg0) {
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        arg0->unk90_bit0 = 0;
    } else {
        arg0->unk90_bit0 = 1;
        AnimateActorBones(arg0->wrapper->boneData);
    }
}

// .text:0x000C9A60 size:0x68 mapped:0x80708AF4
void fn_3_C9A60(ActorObject *arg0) {
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        arg0->unk90_bit0 = 0;
    } else {
        arg0->unk90_bit0 = 1;
        AnimateActorBones(arg0->wrapper->boneData);
    }
}

// .text:0x000C9AC8 size:0x94 mapped:0x80708B5C
void fn_3_C9AC8(void) {
    fn_3_B9510(0);
    fn_3_B9510(1);
    GXLoadTexObj(&lbl_3_bss_9F4C, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_FALSE, GX_FALSE, GX_ITM_0);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_IND_TEX_STAGE_0, GX_FALSE, GX_FALSE, GX_ITM_0);
}

static inline s8 getTexel(u32 x, u32 y) {
    return lbl_3_bss_9F48[fn_800247E4(x, y, 0x80, 2)];
}

// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(ActorObject* arg0) {
    u32 x;
    u32 y;
    s32 prev;
    u32 idx;
    s32 tmp;

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        arg0->unk90_bit0 = 0;
        return;
    }
    arg0->unk90_bit0 = 1;
    if (lbl_3_bss_9F3C < 3) {
        lbl_3_bss_9F3C++;
        return;
    }
    for (x = 0; x < 0x80; x++) {
        for (y = 0; y < 0x40; y++) {
            if (y == 0) {
                prev = getTexel(x, 0x3F);
            }
            idx = fn_800247E4(x, y, 0x80, 2);
            tmp = lbl_3_bss_9F48[idx];
            lbl_3_bss_9F48[idx] = prev;
            prev = tmp;
        }
    }
    lbl_3_bss_9F3C = 0;
    DCFlushRange(lbl_3_bss_9F48, 0x4000);
}

// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void fn_3_C9C94(void) {
    Mtx23 mtx;
    u32 y;
    u32 x;
    u32 idx;

    mtx[0][0] = 0.5f;
    mtx[0][1] = 0.0f;
    mtx[0][2] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][1] = 0.0f;
    mtx[1][2] = 0.0f;

    GXSetIndTexMtx(GX_ITM_0, mtx, 2);
    lbl_3_bss_9F48 = (s8*)fn_3_B9534(0x80, 0x40, &lbl_3_bss_9F4C);
    if (lbl_3_bss_9F48 == NULL) {
        OSPanic("sta_c0.c", 0x29F, "error\n");
    }
    for (y = 0; y < 0x40; y++) {
        for (x = 0; x < 0x80; x++) {
            idx = fn_800247E4(x, y, 0x80, 2);
            lbl_3_bss_9F48[idx] = (u8)(rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
void fn_3_C9DB4(void) {
    return;
}

