#include "game/rep_2940.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "game/gap_6A160.h"

extern VecXYZ lbl_3_data_18DD4[4];

// .text:0x000E11E0 size:0x118 mapped:0x80720274
void fn_3_E11E0(void) {
    AnimationStruct* anim;
    s32 i;
    s8 v;

    g_hugeAnimStruct.characterRelated = -1;
    for (i = 0; i < 4; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (anim == NULL) {
            continue;
        }
        anim->unk_25D = 0;
        if (g_Minigame._1A13[i] != 0) {
            continue;
        }
        if (g_Minigame.teamEntries[i].fieldB < 0) {
            continue;
        }
        if ((s8)g_Minigame.teamEntries[i]._7 == 0) {
            continue;
        }
        v = g_Minigame._19DA[i];
        if (v < 0) {
            continue;
        }
        if (g_d_GameSettings.exhibitionMatchInd == 0) {
            if (v >= 1) {
                continue;
            }
        } else if (g_Minigame._19E6 == 1 && g_d_GameSettings.GameModeSelected != 6 && g_Minigame._1A3C == 0 &&
                   v >= 1) {
            continue;
        }
        anim->unk_25D = 1;
        anim->unk34.x = lbl_3_data_18DD4[i].x;
        anim->unk34.y = -lbl_3_data_18DD4[i].y;
        anim->unk34.z = lbl_3_data_18DD4[i].z;
        anim->unk40.x = 0.0f;
        anim->unk40.y = 0.0f;
        anim->unk40.z = 0.0f;
    }
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void fn_3_E12F8(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (g_hugeAnimStruct.AnimationStructPtrs[i] != NULL) {
            g_hugeAnimStruct.AnimationStructPtrs[i]->unk_25D = 0;
        }
    }
    fn_3_6A25C();
    fn_3_6A250();
}

// .text:0x000E1370 size:0x108 mapped:0x80720404
void fn_3_E1370(s32 arg0) {
    AnimationStruct* anim;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == 3) {
            anim = g_hugeAnimStruct.AnimationStructPtrs[i];
            if (g_d_GameSettings.GameModeSelected == 2) {
                anim = g_hugeAnimStruct.AnimationStructPtrs[9];
                if (i >= 1) {
                    return;
                }
            }
            if (anim != NULL) {
                anim->unk25A = g_Minigame.teamEntries[i]._4 / 2;
                anim->unk25B = g_Minigame.teamEntries[i]._4 % 2;
            }
        }
    }
}

// .text:0x000E1478 size:0x4EC mapped:0x8072050C
void fn_3_E1478(void) {
    return;
}

