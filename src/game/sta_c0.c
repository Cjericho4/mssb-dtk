#include "game/sta_c0.h"
#include "header_rep_data.h"
#include "game/rep_1D58.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXBump.h"

extern GXTexObj lbl_3_bss_9F4C;

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

// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(void) {
    return;
}

// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void fn_3_C9C94(void) {
    return;
}

// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
void fn_3_C9DB4(void) {
    return;
}

