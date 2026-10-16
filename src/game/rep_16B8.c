#include "game/rep_16B8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/rep_3448.h"
#include "game/gap_EA340.h"
#include "game/rep_720.h"
#include "game/gap_1658F0.h"

extern int lbl_3_data_EC1C;
extern int lbl_3_data_E75C;
extern int lbl_3_data_F224;
extern u16 lbl_3_data_F344[6];
void fn_800363D8(DrawingSceneStruct* scene, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 lbl_3_data_F430[12][2];
extern u8 lbl_3_data_F200[0x24];

typedef struct {
    /* 0x00 */ u8 _pad0[0x26];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 _pad27[0x28 - 0x27];
} Lbl8034E978; /* size: 0x28 */
extern Lbl8034E978 lbl_8034E978;

// .text:0x00091520 size:0x540 mapped:0x806D05B4
void fn_3_91520(void) {
    return;
}

// .text:0x00091A60 size:0x68 mapped:0x806D0AF4
void fn_3_91A60(void) {
    DrawingSceneStruct* p = lbl_803CC1B8;
    fn_80034E20(p, &lbl_3_data_BF6C);
    p->unk18 = 0;
    p->eventID = 0;
    p->fielderIndex = 0;
    p->unk20 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_91520;
}

// .text:0x00091AC8 size:0x88 mapped:0x806D0B5C
void fn_3_91AC8(void) {
    u8 status = lbl_3_common_bss_32724.someStatusInd;
    DrawingSceneStruct* drawingItem = lbl_803CC1B8;

    if (status == 0 && g_Stats.unk36 == 0) {
        u8 gs = g_GameLogic.gameStatus;
        if (gs == 2 || gs == 1) {
            return;
        }
    }
    fn_80034CEC((u32)drawingItem);
    fn_800B0A14_removeQueue();
    lbl_3_common_bss_32724.unk_B2 = 0;
}

// .text:0x00091B50 size:0x4C mapped:0x806D0BE4
void fn_3_91B50(void) {
    fn_80034E20((void*)lbl_803CC1B8, (int*)&lbl_3_data_F350, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_91AC8;
}

// .text:0x00091B9C size:0xD4 mapped:0x806D0C30
void fn_3_91B9C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd == 0) {
        if ((lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16) >= 0x4B) {
            (&lbl_80371C30[scene->unkIndex])[1].obj->flags |= 2;
        }
        if ((g_Stats.unk36 != 0 || g_Stats.unk39 != 0) && g_GameLogic.gameStatus != 3 &&
            g_GameLogic.gameStatus != 0xB && g_GameLogic.gameStatus != 0xE) {
            return;
        }
    }
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
    lbl_3_common_bss_32724.unk_B0 = 0;
    lbl_3_common_bss_32724.unk_B1 = 0;
}

// .text:0x00091C70 size:0x5C mapped:0x806D0D04
void fn_3_91C70(void) {
    fn_80034E20((void*)lbl_803CC1B8, (int*)&lbl_3_data_F390, (void**)&lbl_803CC1B8);
    lbl_3_common_bss_32724.unk_B0 = 1;
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_91B9C;
}

// .text:0x00091CCC size:0x50 mapped:0x806D0D60

void fn_3_91CCC(void) {
    void *drawingItem = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 || lbl_3_common_bss_32724.transitionToMenuAnimation != 0) {
        fn_80034CEC((u32)drawingItem);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00091D1C size:0x130 mapped:0x806D0DB0
void fn_3_91D1C(void) {
    DrawingSceneStruct* scene;
    s32 i;
    s32 idx;

    fn_80034E20(scene = lbl_803CC1B8, &lbl_3_data_F224);
    lbl_80371C30[scene->unkIndex + 3].obj->unk64 = lbl_3_data_F344[g_d_GameSettings.StadiumID];
    for (i = 0; i < 3; i++) {
        idx = g_GameLogic.currentBatterPerTeam[g_GameLogic.awayTeamBattingInd_battingTeam] + i;
        if (idx > 9) {
            idx -= 9;
        }
        lbl_80371C30[i + (scene->unkIndex + 5)].obj->field_0x5C =
            inMemRoster[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][idx][0]].stats.CharID << 16;
    }
    fn_800363D8(scene, 1, 4, 7, g_d_GameSettings.StadiumID);
    lbl_803CC1B8->aFunctionPointer = fn_3_91CCC;
}

// .text:0x00091E4C size:0x178 mapped:0x806D0EE0
void fn_3_91E4C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;
    Entry_80371C30* next;
    s32 val;
    s32 slot;

    if (lbl_3_common_bss_32724.transitionToMenuAnimation == 0) {
        if (lbl_3_common_bss_32724.unk_CE != 0) {
            next = &lbl_80371C30[1];
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
            next[scene->unkIndex].obj->field_0x68 = 4;
            val = next[scene->unkIndex].obj->field_0x5C >> 16;
            for (i = 0; i < 11; i++) {
                if (val <= lbl_3_data_F200[i]) {
                    if (i == 0) {
                        lbl_80371C30[scene->unkIndex + 2].obj->field_0x68 = 4;
                        lbl_80371C30[scene->unkIndex + 3].obj->field_0x68 = 4;
                    }
                    lbl_80371C30[i + (scene->unkIndex + 6)].obj->field_0x68 = 4;
                    lbl_80371C30[i + (scene->unkIndex + 0x11)].obj->field_0x68 = 4;
                }
            }
            scene->unk1a_u16++;
            if (scene->unk1a_u16 >= 0x2D) {
                goto remove;
            }
        }
        return;
    }
remove:
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
    if (g_GameLogic.gameStatus == 3) {
        lbl_8034E978.unk26 = 1;
    }
}

// .text:0x00091FC4 size:0xD14 mapped:0x806D1058
void fn_3_91FC4(void) {
    return;
}

// .text:0x00092CD8 size:0x6F4 mapped:0x806D1D6C
void fn_3_92CD8(DrawingSceneStruct* scene) {
    return;
}

// .text:0x000933CC size:0x178 mapped:0x806D2460
void fn_3_933CC(void) {
    return;
}

// .text:0x00093544 size:0x144 mapped:0x806D25D8
void fn_3_93544(void) {
    DrawingSceneStruct* scene;

    fn_80034E20(scene = lbl_803CC1B8, &lbl_3_data_EC1C);
    lbl_80371C30[scene->unkIndex + 1].obj->unk64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    lbl_80371C30[scene->unkIndex + 2].obj->unk64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = g_GameLogic.logo[0].variationID << 16;
    lbl_80371C30[scene->unkIndex + 2].obj->field_0x5C = g_GameLogic.logo[1].variationID << 16;
    if (g_GameLogic.homeTeamBattingInd_fieldingTeam == 0) {
        scene->unk_1C = g_Scores.prevScore;
        scene->unk_1E = g_Scores.team[1].score;
    } else {
        scene->unk_1C = g_Scores.team[0].score;
        scene->unk_1E = g_Scores.prevScore;
    }
    scene->unk_20 = scene->eventID;
    scene->drawingState = scene->fielderIndex;
    fn_3_92CD8(scene);
    scene->unk18 = 0;
    scene->unk1a = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_933CC;
}

// .text:0x00093688 size:0x2D8 mapped:0x806D271C
void fn_3_93688(void) {
    return;
}

// .text:0x00093960 size:0x3FC mapped:0x806D29F4
void fn_3_93960(void) {
    return;
}

// .text:0x00093D5C size:0x3E0 mapped:0x806D2DF0
void fn_3_93D5C(void) {
    return;
}

// .text:0x0009413C size:0x58 mapped:0x806D31D0
void fn_3_9413C(void) {
    void* drawingItem;
    u8 status = lbl_3_common_bss_32724.someStatusInd;
    drawingItem = lbl_803CC1B8;
    if (status != 0 || g_GameLogic.gameStatus != 9) {
        fn_80034CEC((u32)drawingItem);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00094194 size:0x574 mapped:0x806D3228
void fn_3_94194(void) {
    return;
}

// .text:0x00094708 size:0x58 mapped:0x806D379C
void fn_3_94708(void) {


     void* drawingItem;
    u8 status = lbl_3_common_bss_32724.someStatusInd;
    drawingItem = lbl_803CC1B8;
    if (status != 0 || g_GameLogic._125 > 9) {
        fn_80034CEC((u32)drawingItem);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00094760 size:0x158 mapped:0x806D37F4
static inline s32 teamThing(s32 t) {
    return g_GameLogic.teams[t] + g_GameLogic._13E[t] * 4;
}

void fn_3_94760(void) {
    DrawingSceneStruct* scene;

    fn_80034E20(scene = lbl_803CC1B8, &lbl_3_data_E75C);
    lbl_80371C30[scene->unkIndex + 3].obj->unk64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][0];
    lbl_80371C30[scene->unkIndex + 4].obj->unk64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][0];
    lbl_80371C30[scene->unkIndex + 3].obj->field_0x5C = g_GameLogic.logo[0].variationID << 16;
    lbl_80371C30[scene->unkIndex + 4].obj->field_0x5C = g_GameLogic.logo[1].variationID << 16;
    fn_800363D8(scene, 5, 1, 0x25, teamThing(g_GameLogic.homeTeamInd));
    fn_800363D8(scene, 6, 1, 0x25, teamThing(g_GameLogic.homeTeamInd ^ 1));
    lbl_803CC1B8->aFunctionPointer = fn_3_94708;
}

// .text:0x000948B8 size:0x78 mapped:0x806D394C
void fn_3_948B8(void) {
    DrawingSceneStruct *scene = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 || g_GameLogic.gameStatus != 0x17 ||
        lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00094930 size:0x4C mapped:0x806D39C4



void fn_3_94930(void) {
    fn_80034E20((void*)lbl_803CC1B8, (int*)&lbl_3_data_F3F0, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_948B8;
}

// .text:0x0009497C size:0x248 mapped:0x806D3A10
void fn_3_9497C(void) {
    return;
}

// .text:0x00094BC4 size:0x2A4 mapped:0x806D3C58
void fn_3_94BC4(void) {
    return;
}

// .text:0x00094E68 size:0x198 mapped:0x806D3EFC
void fn_3_94E68(void) {
    return;
}

// .text:0x00095000 size:0x98 mapped:0x806D4094
void fn_3_95000(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_E2F8);
    lbl_80371C30[scene->unkIndex + 2].obj->field_0x5C = lbl_3_data_E200[lbl_3_common_bss_37400.unk46] << 16;
    scene->unk_1C = lbl_3_common_bss_37400.unk46;
    lbl_803CC1B8->aFunctionPointer = fn_3_94E68;
}

// .text:0x00095098 size:0x8C mapped:0x806D412C
void fn_3_95098(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 ||
        lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        lbl_3_common_bss_32724.unk_B3 = 0;
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00095124 size:0x90 mapped:0x806D41B8
void fn_3_95124(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_E278);
    lbl_80371C30[scene->unkIndex + 2].obj->field_0x5C = lbl_3_data_E200[lbl_3_common_bss_37400.unk46] << 16;
    lbl_803CC1B8->aFunctionPointer = fn_3_95098;
}

// .text:0x000951B4 size:0x128 mapped:0x806D4248
void fn_3_951B4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (g_Ball.deadBallReason == 1) {
        if (g_GameLogic.gameStatus == 0x14) {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        }
        if (g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 0x14) {
            return;
        }
    } else {
        if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == 1) {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        }
        if (lbl_3_common_bss_32724.someStatusInd == 0 && lbl_3_common_bss_37400.unk42 != 0 &&
            (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2)) {
            return;
        }
    }
    lbl_3_common_bss_32724.unk_B4 = 0;
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
}

// .text:0x000952DC size:0xB0 mapped:0x806D4370
void fn_3_952DC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    CommonBss_32724* state = &lbl_3_common_bss_32724;

    if (state->unk_B5 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    fn_80034E20(scene, &lbl_3_data_E21C);
    if (lbl_3_common_bss_37400.unk47 == 1) {
        lbl_80371C30[scene->unkIndex].obj->unk64 = 0x5A;
    }
    state->unk_B5 = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_951B4;
}

// .text:0x0009538C size:0x70 mapped:0x806D4420
void fn_3_9538C(void) {
    DrawingSceneStruct *temp_r31 = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 || g_GameLogic.gameStatus != 0x16) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        fn_80034CEC((u32)temp_r31);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000953FC size:0xC8 mapped:0x806D4490
void fn_3_953FC(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_E160);
    lbl_80371C30[scene->unkIndex + 2].obj->field_0x5C = lbl_3_data_E200[lbl_3_common_bss_37400.unk46] << 16;
    lbl_80371C30[scene->unkIndex + 3].obj->field_0x5C = lbl_3_data_E200[lbl_3_common_bss_37400.unk46] << 16;
    lbl_3_common_bss_32724.unk_B4 = 0;
    lbl_3_common_bss_32724.unk_B3 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_9538C;
}

// .text:0x000954C4 size:0x58 mapped:0x806D4558
void fn_3_954C4(void) {
    void* drawingItem;
    u8 status = lbl_3_common_bss_32724.someStatusInd;
    drawingItem = lbl_803CC1B8;
    if (status != 0 || g_GameLogic.gameStatus != 22) {
        fn_80034CEC((u32)drawingItem);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0009551C size:0x4C mapped:0x806D45B0


void fn_3_9551C(void) {
    fn_80034E20((void*)lbl_803CC1B8, (int*)&lbl_3_data_E120, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_954C4;
}

// .text:0x00095568 size:0x64 mapped:0x806D45FC
void fn_3_95568(void) {
    DrawingSceneStruct *scene = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 ||
        lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000955CC size:0x54 mapped:0x806D4660
void fn_3_955CC(void) {
    fn_80034E20((void (*)(void)) lbl_803CC1B8, (int *) &lbl_3_data_E0E0, (void **) &lbl_803CC1B8);
    playSoundEffect(0x1A9);
    lbl_803CC1B8->aFunctionPointer = (void *) fn_3_95568;
}

// .text:0x00095620 size:0x350 mapped:0x806D46B4
void fn_3_95620(void) {
    return;
}

// .text:0x00095970 size:0x4C mapped:0x806D4A04

void fn_3_95970(void) {
    fn_80034E20((void*)lbl_803CC1B8, (int*)&lbl_3_data_C1EC, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_95620;
}

// .text:0x000959BC size:0xCE0 mapped:0x806D4A50
void fn_3_959BC(void) {
    return;
}

// .text:0x0009669C size:0x278 mapped:0x806D5730
void fn_3_9669C(void) {
    return;
}

// .text:0x00096914 size:0x78 mapped:0x806D59A8
void fn_3_96914(void) {
    if (lbl_3_common_bss_32724.unk_C7 != 0) {
        return;
    }
    if (g_GameLogic.hudElementLoadingInd == 0) {
        return;
    }
    fn_800B0A5C_insertQueue(fn_3_9669C, 2);
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_800B0A5C_insertQueue(fn_3_ED574, 2);
    }
}

// .text:0x0009698C size:0x318 mapped:0x806D5A20
void fn_3_9698C(void) {
    return;
}

// .text:0x00096CA4 size:0x4A0 mapped:0x806D5D38
void fn_3_96CA4(void) {
    return;
}
