#include "game/gap_EA340.h"
#include "game/rep_3448.h"
#include "game/gap_16C410.h"
#include "musyx/musyx.h"
#include "game/gap_157DB8.h"
#include "game/gap_AC9F8.h"
#include "game/gap_1293D0.h"
#include "game/gap_9143C.h"
#include "game/gap_97144.h"
#include "game/rep_16B8.h"
#include "game/sta_c6.h"

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
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (lbl_3_common_bss_32724.someStatusInd == 0) {
        if (g_UnkSound_32718._07 == 0) {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
            if (scene->eventID == 0) {
                if (lbl_800EF808.unk398 == 1) {
                    stadium = g_d_GameSettings.StadiumID;
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        vol = lbl_3_data_84B8[0][27].vol;
                    } else {
                        vol = lbl_3_data_8404[stadium][27].vol;
                    }
                    vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 27, vol, 0x3F, 0);
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        pan = lbl_3_data_84B8[0][27].pan;
                    } else {
                        pan = lbl_3_data_8404[stadium][27].pan;
                    }
                    sndFXCtrl(vid, 0x5B, pan);
                }
                scene->eventID = 1;
            }
        } else {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 0;
        }
        if (lbl_80371C30[scene->unkIndex].obj->field_0x69 != 2) {
            return;
        }
    }
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
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

extern s32 lbl_3_data_8EC4[];

// .text:0x000ED574 size:0x16C mapped:0x8072C608
void fn_3_ED574(void) {
    DrawingSceneStruct* scene;
    s32 turn;

    fn_80034E20(scene = lbl_803CC1B8, lbl_3_data_8EC4);
    fn_800363D8(scene, 1, 6, 0x4A, g_Minigame.toyField_selectedTurns % 10);
    fn_800363D8(scene, 1, 5, 0x4A, g_Minigame.toyField_selectedTurns / 10);
    turn = g_Minigame.toyField_turnNumber;
    if (turn > g_Minigame.toyField_selectedTurns) {
        turn = g_Minigame.toyField_selectedTurns;
    }
    fn_800363D8(scene, 1, 2, 0x4A, turn % 10);
    if (turn >= 10) {
        fn_800363D8(scene, 1, 1, 0x4A, turn / 10);
    } else {
        fn_800363D8(scene, 1, 1, 0x4A, 10);
    }
    lbl_803CC1B8->aFunctionPointer = fn_3_ED4FC;
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
void fn_3_9C28C(void);
void fn_3_9894C(void);
void fn_3_98DE0(void);

void fn_3_ED818(void) {
    CommonBss_32724* a;
    CommonBss_32724* b;
    CommonBss_32724* c;

    if (g_GameLogic.hudElementLoadingInd != 0) {
        c = &lbl_3_common_bss_32724;
        if (c->unk_A5 == 0) {
            c->unk_A5 = 1;
            c->unk_A6 = 0;
            c->unk_A7 = 0xFF;
            fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
            fn_800B0A5C_insertQueue(fn_3_EA8FC, 2)->unk18 = 0;
            fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        }
    }
    if (g_Ball.totalFramesAtPlay == 0xF && g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd == 0 &&
        g_Minigame.toyField_pointMultiplier > 1 && g_Pitcher.nPitchesThisAB == 0) {
        fn_800B0A5C_insertQueue(fn_3_ED490, 2);
    }
    a = &lbl_3_common_bss_32724;
    if (a->unk_A5 != 0 && a->unk_A6 < 0xFF) {
        if (a->unk_A6 < 0xF0) {
            a->unk_A6 += 0x10;
        } else {
            a->unk_A6 = 0xFF;
        }
    }
    b = &lbl_3_common_bss_32724;
    if (b->unk_A7 != 0 && b->unk_A7 < 0xFF) {
        if (b->unk_A7 <= 0x10) {
            b->unk_A7 = 0;
            a->unk_A5 = 0;
        } else {
            b->unk_A7 -= 0x10;
        }
    } else if (a->unk_A5 != 0) {
        if (g_GameLogic.gameStatus == 8) {
            b->unk_A7 = 0;
            a->unk_A5 = 0;
        } else if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 0xB &&
                   g_GameLogic.gameStatus != 0xD) {
            b->unk_A7 = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == 0xB && lbl_3_common_bss_34C90.field_0x1D2 == 1) {
        fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        if (lbl_3_common_bss_32724.unk_AA == 0) {
            fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
        }
    }
}

// .text:0x000EDA3C size:0x2D4 mapped:0x8072CAD0
typedef struct { u8 unk0; u8 _pad1[7]; u8 unk8; u8 unk9; } MenuNumberState_EA340;
typedef struct { u8 _pad0[8]; u16 unk8; u8 _padA[6]; } MenuEntry_EA340;
extern MenuNumberState_EA340 lbl_8034E978;
extern MenuEntry_EA340 lbl_800FEF70[];
extern void fn_80053FE8(void);
extern void fn_80051D00(void);
extern void fn_8004D0F0(void);
extern void fn_80050F78(s32 arg0);
extern void fn_8004CC4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void fn_3_EDA3C(void) {
    if ((g_GameLogic.gameStatus >= 0x1CU) && (g_GameLogic.gameStatus <= 0x20U) && ((u8) lbl_3_common_bss_32724.unkD9 == 0) && ((u8) g_GameLogic.framesOfExitingToMenu == 0)) {
        fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
        fn_800B0A5C_insertQueue(fn_80053FE8, 2);
        lbl_8034E978.unk0 = 0x2E;
        lbl_8034E978.unk9 = (u8) lbl_8034E978.unk8;
        lbl_8034E978.unk8 = (u8) lbl_800FEF70[0x2E].unk8;
    }
    if (g_GameLogic.gameStatus == 30) {
        if (((u8) g_GameLogic._125 == 1) && ((u16) g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0)) {
            if ((u8) lbl_3_common_bss_32724.unkDC == 0) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724.unkDC = 1U;
            }
            if ((u8) lbl_3_common_bss_32724.unkDA != 1) {
                fn_800B0A5C_insertQueue(fn_3_12B7A0, 2);
            }
        }
        if ((u8) g_GameLogic._125 == 2) {
            if (((u8) lbl_3_common_bss_32724.unkDC == 0) && (g_Minigame._19DE != 5) && (g_Minigame._19DE != 8)) {
                fn_800B0A5C_insertQueue(fn_80051D00, 2);
                lbl_3_common_bss_32724.unkDC = 1U;
            }
            if ((g_Minigame._19DE == 1) && ((u16) g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1)) {
                fn_800B0A5C_insertQueue(fn_3_12A6C4, 2);
            }
        }
        if ((u8) g_GameLogic._125 == 7) {
            fn_80050F78(1);
            lbl_3_common_bss_32724.unkDC = 0U;
        }
        if (((u8) g_GameLogic._125 == 3) && ((u16) g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1)) {
            fn_8004CC4C(0, 1, 1, 0, 0x89);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
        }
        if ((u8) g_GameLogic._125 == 5) {
            fn_80050F78(1);
        }
        return;
    }
    if (g_GameLogic.gameStatus == 33) {
        if (((u8) g_GameLogic._125 == 2) && ((u16) g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1)) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
            lbl_8034E978.unk0 = 0x32;
            lbl_8034E978.unk9 = (u8) lbl_8034E978.unk8;
            lbl_8034E978.unk8 = (u8) lbl_800FEF70[0x32].unk8;
            if (((u8) g_d_GameSettings.exhibitionMatchInd == 0) && ((u8) lbl_3_common_bss_32724.unkD9 == 0)) {
                fn_800B0A5C_insertQueue(fn_3_12C3F0, 2);
            }
        }
    }
}


// .text:0x000EDD10 size:0x29C mapped:0x8072CDA4
void fn_3_EDD10(void) {
    if ((g_GameLogic.gameStatus == 0x1C) || ((u8) (g_GameLogic.gameStatus - 0x1D) <= 3U) || (g_GameLogic.gameStatus == 0x21)) {
        fn_3_EDA3C();
        return;
    }
    lbl_3_common_bss_32724.unkDA = 0;
    fn_3_97144();
    fn_3_96914();
    fn_3_ED818();
    fn_3_9143C();
    if ((s16) g_Minigame.framesSincePanelHit == 1) {
        fn_800B0A5C_insertQueue(fn_3_ED784, 2);
    }
    if (((u8) g_Minigame.panelHitInd != 0) && ((u8) lbl_3_common_bss_32724._padD6[0] == 0) && (g_GameLogic.gameStatus == 2)) {
        fn_800B0A5C_insertQueue(fn_3_EA8FC, 2)->unk18 = 1;
        fn_800B0A5C_insertQueue(fn_3_EAEF4, 2);
    }
    if (((u8) g_Minigame._19CE != 0) && ((s16) g_Minigame._19BA == 1)) {
        fn_800B0A5C_insertQueue(fn_3_ED2A8, 2);
    }
    if ((g_GameLogic.gameStatus == 0xE) || (g_GameLogic.gameStatus == 0x22)) {
        fn_3_129458();
    }
    if (g_GameLogic.gameStatus == 5) {
        if (g_Minigame._1DFC[6] == 0) {
            fn_800B0A5C_insertQueue(fn_3_1254F8, 2);
        }
        return;
    } else if (g_GameLogic.gameStatus == 34) {
        if (lbl_3_common_bss_34C90.field_0x1D2 == 1) {
            fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        }
        return;
    } else if (g_GameLogic.gameStatus == 3) {
        if (g_GameLogic._125 == 0 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            fn_800B0A5C_insertQueue(fn_3_E911C, 2)->unk18 = 0;
        }
        return;
    } else if (g_GameLogic.gameStatus == 36) {
        if (g_GameLogic._125 == 5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            fn_800B0A5C_insertQueue(fn_3_1274B4, 2);
        }
        return;
    } else if (g_GameLogic.gameStatus == 9) {
        return;
    } else if (g_GameLogic.gameStatus == 13) {
        if (lbl_3_common_bss_34C90.field_0x1D2 == 2) {
            fn_800B0A5C_insertQueue(fn_3_128B90, 2);
        }
        return;
    } else if (g_GameLogic.gameStatus == 11) {
        if (lbl_3_common_bss_34C90.field_0x1D2 == 8 && lbl_3_common_bss_34C90.field_0x1D4 == 2) {
            fn_800B0A5C_insertQueue(fn_3_126604, 2);
        }
    }
}
