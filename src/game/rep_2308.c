#include "game/rep_2308.h"
#include "UnknownHeaders.h"
#include "game/rep_1F58.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(void) {
    return;
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
void fn_3_CAE00(void) {
    return;
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void fn_3_CAF9C(void) {
    return;
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

