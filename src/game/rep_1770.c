#include "game/rep_1770.h"
#include "game/rep_3448.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/gap_97144.h"

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    return;
}

// .text:0x0009976C size:0xAC mapped:0x806D8800
extern int lbl_3_data_D378;

void fn_3_9976C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_D378);
    if (g_Batter.batterHand != 0) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0;
    } else {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x10000;
    }
    scene->unk_1C = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_993A8;
}

// .text:0x00099818 size:0x3C4 mapped:0x806D88AC
void fn_3_99818(void) {
    return;
}

// .text:0x00099BDC size:0xAC mapped:0x806D8C70
extern int lbl_3_data_D258;

void fn_3_99BDC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_D258);
    if (g_Minigame.GameMode_MiniGame == 2) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x30000;
    } else {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x20000;
    }
    scene->unk_1C = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_99818;
}

// .text:0x00099C88 size:0x74 mapped:0x806D8D1C
void fn_3_99C88(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd == 0 && lbl_3_common_bss_32724.unk_A7 != 0) {
        Struct_80371C30_Inner* obj = lbl_80371C30[scene->unkIndex].obj;
        obj->field_0x58 = lbl_3_common_bss_32724.unk_A7 | (obj->field_0x58 & ~0xFF);
    } else {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00099CFC size:0x114 mapped:0x806D8D90
extern int lbl_3_data_D4F8;

void fn_3_99CFC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_D4F8);
    if (!(g_Batter.runnersOnBase & 1)) {
        lbl_80371C30[scene->unkIndex + 3].obj->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 2)) {
        lbl_80371C30[scene->unkIndex + 2].obj->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 4)) {
        lbl_80371C30[scene->unkIndex + 1].obj->flags &= ~2;
    }
    if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0) {
        playSoundEffect(0x1AB);
    }
    lbl_803CC1B8->aFunctionPointer = fn_3_99C88;
}

// .text:0x00099E10 size:0xA94 mapped:0x806D8EA4
void fn_3_99E10(void) {
    return;
}

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void fn_3_9A8A4(void) {
    return;
}

// .text:0x0009B108 size:0x218 mapped:0x806DA19C
void fn_3_9B108(s32 arg) {
    if (g_Scores.ScoreTeam0 >= 10) {
        fn_3_972A0(arg, 0xB, 4, g_Scores.ScoreTeam0 % 10);
        fn_3_972A0(arg, 0xC, 3, g_Scores.ScoreTeam0 / 10);
        fn_3_972A0(arg, 0xB, 0xA, g_Scores.ScoreTeam0 % 10);
        fn_3_972A0(arg, 0xC, 9, g_Scores.ScoreTeam0 / 10);
    } else {
        fn_3_972A0(arg, 0xA, 1, g_Scores.ScoreTeam0);
        fn_3_972A0(arg, 0xA, 7, g_Scores.ScoreTeam0);
    }
    if (g_Scores.ScoreTeam1 >= 10) {
        fn_3_972A0(arg, 0xE, 6, g_Scores.ScoreTeam1 % 10);
        fn_3_972A0(arg, 0xF, 5, g_Scores.ScoreTeam1 / 10);
        fn_3_972A0(arg, 0xE, 0xC, g_Scores.ScoreTeam1 % 10);
        fn_3_972A0(arg, 0xF, 0xB, g_Scores.ScoreTeam1 / 10);
    } else {
        fn_3_972A0(arg, 0xD, 2, g_Scores.ScoreTeam1);
        fn_3_972A0(arg, 0xD, 8, g_Scores.ScoreTeam1);
    }
}

// .text:0x0009B320 size:0x4D4 mapped:0x806DA3B4
void fn_3_9B320(void) {
    return;
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void fn_3_9B7F4(void) {
    return;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void fn_3_9BEE0(DrawingSceneStruct* scene) {
    s32 i;
    s32 kind;
    s32 count;

    count = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        count = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 7; i++) {
        kind = 3;
        if (g_d_GameSettings.GameModeSelected == 6 && i >= 5) {
            break;
        }
        if (i < 2) {
            if (scene->eventID == g_Strikes.strikes) {
                continue;
            }
            if (g_Strikes.strikes >= i + 1) {
                kind = 0;
            }
        } else if (i < 5) {
            if (scene->fielderIndex == g_Strikes.balls) {
                continue;
            }
            if (g_Strikes.balls >= i - 1) {
                kind = 1;
            }
        } else {
            if (scene->unk20_u16 == count) {
                continue;
            }
            if (count >= i - 4) {
                kind = 2;
            }
        }
        fn_8003649C((s32)scene, i + 1, i + 1, 0x107, kind);
    }
    scene->eventID = g_Strikes.strikes;
    scene->fielderIndex = g_Strikes.balls;
    scene->unk20_u16 = count;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void fn_3_9C014(void) {
    return;
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void fn_3_9C28C(void) {
    return;
}
