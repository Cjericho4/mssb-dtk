#include "game/rep_1610.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "game/rep_3448.h"
#include "game/gap_97144.h"
#include "game/gap_90754.h"

extern s32 lbl_3_data_D5B8[];

static inline void fn_3_910F4_inline(s32 scene) {
    s32 i;
    s32 count;
    s32 state;

    count = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        count = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 2; i++) {
        state = 3;
        if (((DrawingSceneStruct*)scene)->eventID != count) {
            if (count >= i + 1) {
                state = 2;
            }
            fn_8003649C(scene, i + 1, i + 1, 0x107, state);
        }
    }
    ((DrawingSceneStruct*)scene)->eventID = count;
}

// .text:0x000912B4 size:0x188 mapped:0x806D0348
void fn_3_912B4(void) {
    DrawingSceneStruct* scene;
    s32 i;

    fn_80034E20(scene = lbl_803CC1B8, lbl_3_data_D5B8);
    scene->eventID = 9;
    lbl_80371C30[(s32)(scene->unkIndex + 1)].obj->field_0x5C = 0;
    lbl_80371C30[(s32)(scene->unkIndex + 2)].obj->field_0x5C = 0x10000;
    fn_3_910F4_inline((s32)scene);
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 3; i++) {
            lbl_80371C30[scene->unkIndex + i].obj->pos.y = 56.0f;
        }
    }
    scene->unk18 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_911A8;
}

