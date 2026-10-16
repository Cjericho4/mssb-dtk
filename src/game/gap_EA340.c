#include "game/gap_EA340.h"
#include "game/rep_3448.h"
#include "game/gap_16C410.h"
#include "musyx/musyx.h"

// .text:0x000EA340 size:0x114 mapped:0x807293D4
void fn_3_EA340(void) {
    return;
}

// .text:0x000EA454 size:0x4A8 mapped:0x807294E8
void fn_3_EA454(void) {
    return;
}

// .text:0x000EA8FC size:0x5F8 mapped:0x80729990
void fn_3_EA8FC(void) {
    return;
}

// .text:0x000EAEF4 size:0x790 mapped:0x80729F88
void fn_3_EAEF4(void) {
    return;
}

// .text:0x000EB684 size:0x5C mapped:0x8072A718

s32 fn_3_EB684(void) {
    if (lbl_3_common_bss_32724.someStatusInd != 0 || lbl_3_common_bss_32724.unk_B7 != 0) {
        return 1;
    }
    if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 0xB) {
        return 1;
    }
    return 0;
}

// .text:0x000EB6E0 size:0x8F4 mapped:0x8072A774
void fn_3_EB6E0(void) {
    return;
}

// .text:0x000EBFD4 size:0x40 mapped:0x8072B068
s32 fn_3_EBFD4(void) {
    if (lbl_3_common_bss_32724.someStatusInd == 0
        && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL
        && g_GameLogic.gameStatus != GAME_STATUS_TRANSITION)
        return 0;
    return 1;
}

// .text:0x000EC014 size:0x7F0 mapped:0x8072B0A8
void fn_3_EC014(void) {
    return;
}

// .text:0x000EC804 size:0x3AC mapped:0x8072B898
void fn_3_EC804(void) {
    return;
}

// .text:0x000ECBB0 size:0x198 mapped:0x8072BC44
void fn_3_ECBB0(void) {
    return;
}

// .text:0x000ECD48 size:0x310 mapped:0x8072BDDC
void fn_3_ECD48(void) {
    return;
}

// .text:0x000ED058 size:0x9C mapped:0x8072C0EC
void fn_3_ED058(void) {
    return;
}

extern s32 lbl_3_data_8F64;
extern u16 lbl_3_data_8FC4[];

// .text:0x000ED0F4 size:0x150 mapped:0x8072C188
void fn_3_ED0F4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    fn_80034E20(scene, &lbl_3_data_8F64);
    lbl_80371C30[scene->unkIndex + 1].obj->unk64 = lbl_3_data_8FC4[g_Minigame._1921 - 1];
    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0][28].vol;
    } else {
        vol = lbl_3_data_8404[stadium][28].vol;
    }
    vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 28, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        pan = lbl_3_data_84B8[0][28].pan;
    } else {
        pan = lbl_3_data_8404[stadium][28].pan;
    }
    sndFXCtrl(vid, 0x5B, pan);
    scene->timer18 = 0;
    g_Minigame._19CD = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_ED058;
}

// .text:0x000ED244 size:0x64 mapped:0x8072C2D8
void fn_3_ED244(void) {
    DrawingSceneStruct *scene = lbl_803CC1B8;
    if (lbl_3_common_bss_32724.someStatusInd != 0 ||
        lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000ED2A8 size:0x4C mapped:0x8072C33C
void fn_3_ED2A8(void) {
    fn_80034E20((void(*)(void))lbl_803CC1B8, (int*)&lbl_3_data_8FCC, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = fn_3_ED244;
}

// .text:0x000ED2F4 size:0x19C mapped:0x8072C388
void fn_3_ED2F4(void) {
    return;
}

// .text:0x000ED490 size:0x6C mapped:0x8072C524
void fn_3_ED490(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_8F24);
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 1;
    scene->eventID = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_ED2F4;
}

// .text:0x000ED4FC size:0x78 mapped:0x8072C590
void fn_3_ED4FC(void) {
    DrawingSceneStruct *scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd != 0 ||
        g_GameLogic.hudLoadingRelated != 0 ||
        g_GameLogic.gameStatus == 3 ||
        g_GameLogic.gameStatus == 0xE ||
        g_GameLogic.secondaryGameMode == 0xA) {

        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000ED574 size:0x16C mapped:0x8072C608
void fn_3_ED574(void) {
    return;
}

// .text:0x000ED6E0 size:0xA4 mapped:0x8072C774
void fn_3_ED6E0(void) {
    DrawingSceneStruct *scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd != 0 ||
        lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2 ||
        g_GameLogic.gameStatus == 8) {
        if (g_Minigame._1921 != 0) {
            fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
        }
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000ED784 size:0x94 mapped:0x8072C818
void fn_3_ED784(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    u8 result = g_Minigame.toyFieldBallStateResult2;
    s32 script;

    if (result == 11) {
        scene->aFunctionPointer = fn_3_EC014;
        return;
    }
    script = lbl_3_data_8EA8[result];
    if (script < 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    lbl_3_data_8E68[1] = script;
    fn_80034E20(scene, lbl_3_data_8E68);
    lbl_803CC1B8->aFunctionPointer = fn_3_ED6E0;
}

// .text:0x000ED818 size:0x224 mapped:0x8072C8AC
void fn_3_ED818(void) {
    return;
}

// .text:0x000EDA3C size:0x2D4 mapped:0x8072CAD0
void fn_3_EDA3C(void) {
    return;
}

// .text:0x000EDD10 size:0x29C mapped:0x8072CDA4
void fn_3_EDD10(void) {
    return;
}
