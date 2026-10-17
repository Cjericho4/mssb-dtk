#include "game/gap_157DB8.h"
#include "game/rep_3448.h"
#include "game/gap_AC9F8.h"
#include "game/rep_16B8.h"
#include "game/rep_540.h"
#include "game/gap_5985C.h"

// .text:0x00157DB8 size:0x70 mapped:0x80796E4C
void fn_3_157DB8(s32 arg0) {
    extern void fn_3_157AC4(void);
    Fn157DB8Struct *temp_r3 = (Fn157DB8Struct *)fn_80033A24(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (temp_r3 != 0) {
        temp_r3->unk18 = 0;
        temp_r3->unk1C = arg0;
        temp_r3->unkC->unk4D = 0;
        temp_r3->unkC->unk40 = -1;
    }
}

// .text:0x00157E28 size:0x284 mapped:0x80796EBC
void fn_3_157E28(void) {
    return;
}

// .text:0x001580AC size:0x60 mapped:0x80797140
extern int lbl_3_data_BD90;

void fn_3_1580AC(void) {
    DrawingSceneStruct* p = lbl_803CC1B8;
    fn_80034E20(p, &lbl_3_data_BD90);
    p->eventID = 0;
    p->fielderIndex = 0;
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_157E28;
}

// .text:0x0015810C size:0xF0 mapped:0x807971A0
void fn_3_15810C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 limit;

    if (lbl_3_common_bss_32724.someStatusInd == 0) {
        limit = 0x96;
        if (g_Practice.practiceType_2 == 0) {
            limit = 0x5A;
        }
        if (g_Practice._186 < limit - 20) {
            if ((lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16) >= 0x21) {
                lbl_80371C30[scene->unkIndex].obj->field_0x68 = 0;
            }
        } else {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        }
        if (!g_Practice._1C7 || lbl_3_common_bss_34C90.field_0x1D2 != 0) {
            return;
        }
    }
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
}

// .text:0x001581FC size:0x68 mapped:0x80797290
void fn_3_1581FC(void) {
    fn_80034E20((void(*)(void))lbl_803CC1B8, (int*)&lbl_3_data_BD50, (void**)&lbl_803CC1B8);
    if ((u8)lbl_800EF808.unk398 == 1) {
        playSoundEffect(0x1AD);
    }
    lbl_803CC1B8->aFunctionPointer = fn_3_15810C;
}

extern u8 lbl_3_data_FAF4[][4];

// .text:0x00158264 size:0x148 mapped:0x807972F8
void fn_3_158264(DrawingSceneStruct* scene) {
    s32 v;

    v = lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel];
    fn_800363D8(scene, 1, 3, 0x32, v);
    fn_800363D8(scene, 1, 4, 0x32, v);
    v = g_Practice.guidedPracticeCounter;
    fn_800363D8(scene, 1, 1, 0x32, v);
    fn_800363D8(scene, 1, 2, 0x32, v);
    if (v != scene->unk1a_u16) {
        if ((lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C >> 16) <= 9) {
            lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0xA0000;
            lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 1;
        }
        if ((lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C >> 16) >= 0x13) {
            lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0x90000;
            lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 0;
            scene->unk1a_u16 = v;
        }
    }
}

// .text:0x001583AC size:0x304 mapped:0x80797440
void fn_3_1583AC(void) {
    return;
}

// .text:0x001586B0 size:0x314 mapped:0x80797744
void fn_3_1586B0(void) {
    return;
}

// .text:0x001589C4 size:0x1A0 mapped:0x80797A58
void fn_3_1589C4(void) {
    CommonBss_32724* b;

    if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            b = &lbl_3_common_bss_32724;
            if (b->unk_C6 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                b->unk_C6 = 1;
            }
            if (g_Practice.practiceType_2 == 2 && g_Ball.totalFramesAtPlay == 1) {
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice.practiceType_2 == 2) {
                if (g_Practice._186 == 0x3C) {
                    fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
                }
            } else if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    } else if (g_Practice.practiceType_2 == 3 && g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
        if (lbl_3_common_bss_32724.unk_C7 == 0) {
            fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
            fn_800B0A5C_insertQueue(fn_3_9669C, 2);
        }
        if (g_Practice._186 == 1) {
            fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
        }
    }
}

// .text:0x00158B64 size:0x480 mapped:0x80797BF8
void fn_3_158B64(void) {
    return;
}

// .text:0x00158FE4 size:0xE4 mapped:0x80798078
void fn_3_158FE4(void) {
    DrawingSceneStruct* scene;

    fn_80034E20(scene = lbl_803CC1B8, &lbl_3_data_B85C);
    lbl_80371C30[scene->unkIndex + 8].obj->flags &= ~2;
    fn_800363D8(scene, 0xD, 1, 0xE, g_Practice.practiceLevel);
    fn_800363D8(scene, 0xD, 2, 0xE, g_Practice.practiceLevel);
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.diagramTextChannelIndex = -1;
    scene->unk18 = 0;
    scene->unk1a = 0;
    scene->unk_1C = 0;
    scene->unk_1E = 0;
    scene->unk_20 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_158B64;
}

// .text:0x001590C8 size:0x4C mapped:0x8079815C
void fn_3_1590C8(void) {
    if (g_Practice.tutorialState == 0 && g_Practice.practiceState == 7) {
        fn_800B0A5C_insertQueue(fn_3_158FE4, 2);
    }
}

// .text:0x00159114 size:0x47C mapped:0x807981A8
void fn_3_159114(void) {
    return;
}

// .text:0x00159590 size:0x64 mapped:0x80798624
void fn_3_159590(void) {
    DrawingSceneStruct* dss = lbl_803CC1B8;
    fn_80034E20(dss, &lbl_3_data_B3F4);
    dss->unk18 = 0;
    dss->unk1a = 0;
    dss->eventID = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_159114;
}

// .text:0x001595F4 size:0x3C4 mapped:0x80798688
void fn_3_1595F4(void) {
    return;
}

// .text:0x001599B8 size:0x398 mapped:0x80798A4C
void fn_3_1599B8(void) {
    return;
}

// .text:0x00159D50 size:0x4F4 mapped:0x80798DE4
void fn_3_159D50(void) {
    return;
}

extern s32 lbl_3_data_B1BC;
extern u8 lbl_3_data_FAC4[5];
extern u16 lbl_3_data_B3DC[];
extern u16 lbl_3_data_B3E8[];

// .text:0x0015A244 size:0x204 mapped:0x807992D8
void fn_3_15A244(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;

    fn_80034E20(scene, &lbl_3_data_B1BC);
    for (i = 0; i < 5; i++) {
        lbl_80371C30[scene->unkIndex + i + 6].obj->field_0x5C = lbl_3_data_B3DC[lbl_3_data_FAC4[i]] << 16;
    }
    scene->unk_1C = 1;
    if (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
        g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) {
        lbl_80371C30[scene->unkIndex].obj->unk64 = lbl_3_data_B3E8[g_Practice.practiceType];
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x320000;
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
        lbl_80371C30[1 + scene->unkIndex + g_Practice.practiceType].obj->field_0x5C = 0x690000;
        lbl_80371C30[0xB + scene->unkIndex + g_Practice.practiceType].obj->field_0x5C = 0x690000;
        scene->unk_1C = 5;
    }
    lbl_3_common_bss_32724.unk_C0 = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_159D50;
}

// .text:0x0015A448 size:0x314 mapped:0x807994DC
void fn_3_15A448(void) {
    return;
}

// .text:0x0015A75C size:0x298 mapped:0x807997F0
void fn_3_9976C();                                  /* extern */
void fn_3_99BDC();                                  /* extern */
void fn_3_9A8A4();                                  /* extern */
void fn_3_9C28C();                                  /* extern */

void fn_3_15A75C(void) {
    if (((u8) g_GameLogic.hudElementLoadingInd != 0) && (lbl_3_common_bss_32724.unk_A5 == 0) && ((s8) (u8) g_Practice.instructionNumber < 0)) {
        lbl_3_common_bss_32724.unk_A5 = 1;
        lbl_3_common_bss_32724.unk_A6 = 0;
        lbl_3_common_bss_32724.unk_A7 = 0xFF;
        if (g_Practice.practiceLevel == 4) {
            fn_800B0A5C_insertQueue(fn_3_9976C, 2);
        } else if (g_Practice.practiceLevel == 5) {
            fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
        } else {
            if (g_Practice.practiceType_2 == 4) {
                fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
                fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
            } else if (g_Practice.practiceType_2 == 0) {
                if (g_Practice.practiceLevel == 1) {
                    fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
                }
            } else if (g_Practice.practiceType_2 == 1) {
                if (g_Practice.practiceLevel == 1) {
                    fn_800B0A5C_insertQueue(fn_3_9976C, 2);
                }
            }
        }
    }
    if ((lbl_3_common_bss_32724.unk_A5 != 0) && (lbl_3_common_bss_32724.unk_A6 < 0xFFU)) {
        if (lbl_3_common_bss_32724.unk_A6 < 0xF0U) {
            lbl_3_common_bss_32724.unk_A6 += 0x10;
        } else {
            lbl_3_common_bss_32724.unk_A6 = 0xFF;
        }
    }
    if ((lbl_3_common_bss_32724.unk_A7 != 0) && (lbl_3_common_bss_32724.unk_A7 < 0xFFU)) {
        if (lbl_3_common_bss_32724.unk_A7 <= 0x10U) {
            lbl_3_common_bss_32724.unk_A7 = 0;
            lbl_3_common_bss_32724.unk_A5 = 0;
        } else {
            lbl_3_common_bss_32724.unk_A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724.unk_A5 != 0) {
        if ((g_GameLogic.gameStatus != 1) && (g_GameLogic.gameStatus != 0) && (g_GameLogic.gameStatus != 7)) {
            lbl_3_common_bss_32724.unk_A7 = 0xF0;
        }
        if ((u8) lbl_3_common_bss_34C90.field_0x1D5 != 0) {
            lbl_3_common_bss_32724.unk_A7 = 0xF0;
        }
        if (((u8) g_Practice._19F != 0) && ((lbl_3_common_bss_34C90.field_0x1D2 == 7) || (lbl_3_common_bss_34C90.field_0x1D2 == 9) || (lbl_3_common_bss_34C90.field_0x1D2 == 0xB))) {
            lbl_3_common_bss_32724.unk_A7 = 0;
            lbl_3_common_bss_32724.unk_A5 = 0;
        }
        if (((u8) g_Practice._1C7 != 0) && ((lbl_3_common_bss_34C90.field_0x1D2 == 5) || (lbl_3_common_bss_34C90.field_0x1D2 == 0xB) || (lbl_3_common_bss_34C90.field_0x1D2 == 7))) {
            lbl_3_common_bss_32724.unk_A7 = 0;
            lbl_3_common_bss_32724.unk_A5 = 0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724.unk_A7 = 0;
        lbl_3_common_bss_32724.unk_A5 = 0;
    }
}



// .text:0x0015A9F4 size:0x3A0 mapped:0x80799A88
void fn_3_15A9F4(void) {
    return;
}

// .text:0x0015AD94 size:0x40 mapped:0x80799E28
void fn_3_15AD94(void) {
    if (g_Pitcher.currentStateFrameCounter > lbl_3_data_FC1C) {
        fn_3_750C4(2);
    }
}

// .text:0x0015ADD4 size:0x60 mapped:0x80799E68

void fn_3_15ADD4(void) {
    fn_3_6B870();
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    if ((g_GameLogic.secondaryGameMode == 0xF) && (g_Strikes.outs >= 3)) {
        g_Strikes.outs = 0;
    }
    fn_3_5A6D4(7);
}

// .text:0x0015AE34 size:0x144 mapped:0x80799EC8
void fn_3_15AE34(void) {
    s32 ids[4];
    s32 i;
    s32 j;

    if (g_GameLogic.secondaryGameMode == 0xF) {
        for (i = 0; i < 4; i++) {
            ids[i] = i + 1;
        }
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {
                if (g_Runners[j].rosterID == ids[i]) {
                    ids[i] = -1;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (ids[i] >= 0) {
                g_Practice.rosterID = ids[i];
                break;
            }
        }
    }
    if (g_GameLogic.TeamStars[0] == 0) {
        g_GameLogic.TeamStars[0] = 5;
    }
    if (g_GameLogic.TeamStars[1] == 0) {
        g_GameLogic.TeamStars[1] = 5;
    }
    if (g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    g_Practice.guidedPracticeCompletionRelated = 0;
}

// .text:0x0015AF78 size:0x160 mapped:0x8079A00C
void fn_3_15AF78(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_5F154();
        break;
    case 1:
        fn_3_5EFEC();
        break;
    case 2:
        fn_3_5EDD8();
        break;
    case 7:
        fn_3_5F3FC();
        if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
            fn_3_15AE34();
        }
        break;
    case 8:
        fn_3_6B870();
        g_GameLogic._135 = 0;
        g_GameLogic._136 = 0;
        if (g_GameLogic.secondaryGameMode == 0xF && g_Strikes.outs >= 3) {
            g_Strikes.outs = 0;
        }
        fn_3_5A6D4(7);
        break;
    case 10:
        fn_3_5CD24();
        break;
    }
    if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        g_Strikes.outs = 0;
    }
}

// .text:0x0015B0D8 size:0x12C mapped:0x8079A16C
void fn_3_15B0D8(void) {
    g_GameLogic._13E[0] = 0;
    g_GameLogic._140[0] = 0;
    g_GameLogic.teamAIInd[0] = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.batterHandedness[0] = 0;
    g_GameLogic.battingAIInd[0] = 0;
    g_GameLogic._13E[1] = 0;
    g_GameLogic._140[1] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.batterHandedness[1] = 0;
    g_GameLogic.battingAIInd[1] = 0;
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.freePracticeInd_writeOnly = 0;
    g_Practice.__0x1aapadding[0] = 0;
    if ((u8) g_GameLogic.secondaryGameMode == 0xF) {
        g_Practice.aIEnabled = 1;
        g_GameLogic._13E[g_GameLogic.teamFielding] = 1;
        g_Practice.freePracticeInd_writeOnly = 1;
        g_GameLogic._140[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_Practice.rosterID = 1;
        g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
    } else {
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic._13E[g_GameLogic.teamBatting] = 1;
        g_Practice.__0x1aapadding[0] = 1;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
    }
    g_Practice._186 = 0;
    fn_3_5A684();
    fn_3_8A350();
    fn_3_F7B8();
    fn_3_75434();
    fn_3_59338();
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
}

// .text:0x0015B204 size:0x290 mapped:0x8079A298
void fn_3_15B204(void) {
    return;
}

// .text:0x0015B494 size:0x17C mapped:0x8079A528
void fn_3_15B494(void) {
    return;
}

// .text:0x0015B610 size:0x18C mapped:0x8079A6A4
void fn_3_15B610(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_15B494();
        break;
    case 3:
        g_GameLogic.hudElementLoadingInd = 0;
        g_GameLogic.hudLoadingRelated = 0;
        if (g_Ball.totalFramesAtPlay < 0x7FFE) {
            g_Ball.totalFramesAtPlay++;
        } else {
            g_Ball.totalFramesAtPlay = 0x7FFF;
        }
        if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
            g_Practice.frames_sinceMovedToFromMenu++;
        } else {
            g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
        }
        switch (g_GameLogic.gameStatus) {
        case 0:
            fn_3_5F154();
            break;
        case 1:
            fn_3_5EFEC();
            break;
        case 2:
            fn_3_5EDD8();
            break;
        case 7:
            fn_3_5F3FC();
            if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
                fn_3_15AE34();
            }
            break;
        case 8:
            fn_3_6B870();
            g_GameLogic._135 = 0;
            g_GameLogic._136 = 0;
            if (g_GameLogic.secondaryGameMode == 0xF && g_Strikes.outs >= 3) {
                g_Strikes.outs = 0;
            }
            fn_3_5A6D4(7);
            break;
        case 10:
            fn_3_5CD24();
            break;
        }
        if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
            g_Strikes.outs = 0;
        }
        break;
    }
}

