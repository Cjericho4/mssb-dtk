#include "game/rep_3448.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/gap_AC9F8.h"
#include "musyx/musyx.h"
#include "game/m_sound.h"
#include "game/gap_157DB8.h"

// .text:0x0011EC28 size:0x404 mapped:0x8075DCBC
void fn_3_11EC28(void) {
    return;
}

// .text:0x0011F02C size:0x454 mapped:0x8075E0C0
void fn_3_11F02C(void) {
    return;
}

// .text:0x0011F480 size:0x34 mapped:0x8075E514

#include "game/UnknownHomes_Game.h"

/**
 * @address 0011F480
 */

#include "game/UnknownHomes_Game.h"

/**
 * @address 0011F480
 */
void fn_3_11F480(void) {
    MiniGameStruct* mini = &g_Minigame;

    /* Establishing r3 and checking condition */
    if (mini->GameMode_MiniGame == 4) {
        /* To force 'li r4, 0' to stay after the bnelr:
           We initialize it here. If it still hoists, we use a dummy 
           inline block or a volatile-like approach. */
        u32 i = 0; 
        
        do {
            /* lha r0, 0x1890(r3) */
            s16 points = *(s16*)((u8*)mini + 0x1890);
            
            /* The increment and compare are interleaved to match 
               Target scheduling: addi r4, r4, 1 -> cmplwi r4, 4 */
            i++;
            
            /* sth r0, 0x1df4(r3) */
            *(s16*)((u8*)mini + 0x1df4) = points;

            /* addi r3, r3, 2 */
            mini = (MiniGameStruct*)((u8*)mini + 2);

        } while (i < 4);
    }
}

// .text:0x0011F4B4 size:0x54 mapped:0x8075E548
void fn_3_11F4B4(s32 arg1, s32 arg2) {
    s32 step;
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_CHAINCHOMP_SPRINT)
        return;
    step = (arg2 != 0) ? 2 : 0;
    g_Minigame.targetPointsArray[arg1] += lbl_3_data_21884[step].unk1;
}

// .text:0x0011F508 size:0x270 mapped:0x8075E59C
void fn_3_11F508(void) {
    return;
}

// .text:0x0011F778 size:0x2E0 mapped:0x8075E80C
void fn_3_11F778(void) {
    return;
}

// .text:0x0011FA58 size:0x358 mapped:0x8075EAEC
void fn_3_11FA58(void) {
    return;
}

// .text:0x0011FDB0 size:0x4BC mapped:0x8075EE44
void fn_3_11FDB0(void) {
    return;
}

// .text:0x0012026C size:0x630 mapped:0x8075F300
void fn_3_12026C(void) {
    return;
}

// .text:0x0012089C size:0x6C0 mapped:0x8075F930
void fn_3_12089C(void) {
    return;
}

extern s16 lbl_3_data_21654[12];
extern s16 lbl_3_data_21672;
// .text:0x00120F5C size:0x9C mapped:0x8075FFF0
s32 fn_3_120F5C(void) {
    s16 mult = 1;

    if ((g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0 || g_Minigame.soloMinigameDifficulty != 3) &&
        g_Scores.highscore == g_Scores.threshold) {
        mult = lbl_3_data_21672;
    }
    if (g_Minigame.wallBall_hitNoteBlock == 1) {
        return lbl_3_data_21654[10] * mult;
    }
    return g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] * mult;
}

// .text:0x00120FF8 size:0x30C mapped:0x8076008C
void fn_3_120FF8(void) {
    return;
}

// .text:0x00121304 size:0x604 mapped:0x80760398
void fn_3_121304(void) {
    return;
}

// .text:0x00121908 size:0xA2C mapped:0x8076099C
void fn_3_121908(void) {
    return;
}

// .text:0x00122334 size:0x3A0 mapped:0x807613C8
void fn_3_122334(void) {
    return;
}

// .text:0x001226D4 size:0x650 mapped:0x80761768
void fn_3_1226D4(void) {
    return;
}

// .text:0x00122D24 size:0x4B0 mapped:0x80761DB8
void fn_3_122D24(void) {
    return;
}

// .text:0x001231D4 size:0x3E4 mapped:0x80762268
void fn_3_1231D4(void) {
    return;
}

// .text:0x001235B8 size:0x3D8 mapped:0x8076264C
void fn_3_1235B8(void) {
    return;
}

// .text:0x00123990 size:0x52C mapped:0x80762A24
void fn_3_123990(void) {
    return;
}

// .text:0x00123EBC size:0x4E8 mapped:0x80762F50
void fn_3_123EBC(void) {
    return;
}

// .text:0x001243A4 size:0x394 mapped:0x80763438
void fn_3_1243A4(void) {
    return;
}

// .text:0x00124738 size:0x5A8 mapped:0x807637CC
void fn_3_124738(void) {
    return;
}

// .text:0x00124CE0 size:0x68C mapped:0x80763D74
void fn_3_124CE0(void) {
    return;
}

// .text:0x0012536C size:0xB8 mapped:0x80764400
BOOL fn_3_12536C(void) {
    u8 status;

    if (lbl_3_common_bss_32724.someStatusInd != 0 || lbl_3_common_bss_32724.unk_B7 != 0) {
        return TRUE;
    }
    status = g_GameLogic.gameStatus;
    if (status == 0xF) {
        return TRUE;
    }
    if (g_Minigame.pauseInd != 0) {
        if (lbl_3_common_bss_34C90.field_0x1D2 == 7 || lbl_3_common_bss_34C90.field_0x1D2 == 9) {
            return TRUE;
        }
        if (lbl_3_common_bss_34C90.field_0x1D2 == 0xD) {
            return TRUE;
        }
    }
    if (status == 0xE && g_GameLogic.FrameCountOfCurrentPitch == 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00125424 size:0x5C mapped:0x807644B8
BOOL fn_3_125424(Struct_125424_Arg* arg0, u32 arg1, u32 arg2) {
    Struct_80371C30_Inner* obj = lbl_80371C30[arg0->field_0x14 + arg1].obj;
    u32 val = obj->field_0x58 >> 16;
    if (val < arg2) {
        obj->field_0x68 = 1;
        return FALSE;
    }
    if (val > arg2) {
        obj->field_0x68 = 4;
        return FALSE;
    }
    obj->field_0x68 = 0;
    return TRUE;
}

// .text:0x00125480 size:0x78 mapped:0x80764514
BOOL fn_3_125480(Struct_125424_Arg* arg0) {
    Struct_80371C30_Inner* obj;
    u32 i;

    for (i = 0; i < arg0->field_0x16; i++) {
        obj = lbl_80371C30[arg0->field_0x14 + i].obj;

        if (obj->field_0x68 == 1) {
            if (obj->field_0x69 != 2) {
                return TRUE;
            }
        } else if (obj->field_0x68 == 4) {
            if ((obj->field_0x5C >> 16) != 0) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern u8 lbl_3_data_23894[];
extern u16 lbl_3_data_238F4[];

// .text:0x001254F8 size:0x10C mapped:0x8076458C
void fn_3_1254F8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (g_GameLogic.gameStatus != 5) {
        g_Minigame._1DFC[6] = 0;
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
        return;
    }
    switch (scene->eventID) {
    case 0:
        g_Minigame._1DFC[6] = 1;
        fn_80034E20(scene, lbl_3_data_23894);
        lbl_80371C30[scene->unkIndex].obj->unk64 = lbl_3_data_238F4[g_Minigame.GameMode_MiniGame];
        if (g_Minigame._1A3C != 0 && g_Minigame.field_1E26[4] >= 6) {
            lbl_80371C30[scene->unkIndex + 1].obj->flags |= 2;
        }
        scene->eventID = 1;
        break;
    case 1:
        break;
    }
}

extern u16 lbl_3_data_91FC[];
void fn_800362F0(DrawingSceneStruct* scene, s32 arg1);

// .text:0x00125604 size:0x24C mapped:0x80764698
void fn_3_125604(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (g_Minigame._1A40 == 0) {
        if (scene->unk18 < 0xFFFE) {
            scene->unk18++;
        } else {
            scene->unk18 = 0xFFFF;
        }
        if (scene->eventID == 0) {
            if (g_Minigame._1A41 != 0) {
                if (--g_Minigame.someGraphicFrameCountdown <= 0) {
                    lbl_80371C30[scene->unkIndex].obj->unk64 = lbl_3_data_91FC[g_Minigame._1A41];
                    lbl_80371C30[scene->unkIndex].obj->flags |= 2;
                    lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
                    lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0;
                    if (g_Minigame._1A41 == 4) {
                        fn_800363D8(scene, 0, 1, 0x13C, g_Scores.highscore - 1);
                        fn_3_90064(0x2F8);
                    }
                    scene->eventID = g_Minigame._1A41;
                    scene->unk18 = 0;
                    g_Minigame.bODRelated = 1;
                    g_Minigame._1A41 = 0;
                }
            }
        } else {
            if (lbl_80371C30[scene->unkIndex].obj->field_0x69 == 2) {
                if (scene->eventID == 4) {
                    fn_800362F0(scene, 0);
                }
                lbl_80371C30[scene->unkIndex].obj->flags &= ~2;
                g_Minigame.bODRelated = 0;
                g_Minigame._1A41 = 0;
                scene->eventID = 0;
            }
            if (scene->eventID == 2) {
                if (scene->unk18 == 0x46) {
                    sndFXStartEx(0x1BD, lbl_800EFBA4.volume, 0x3F, 0);
                }
            } else if (scene->eventID == 1) {
                if (scene->unk18 == 1 && lbl_800EF808.unk398 == 1) {
                    fn_3_90064(0x2EE);
                }
            }
        }
    } else {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00125850 size:0x70 mapped:0x807648E4
void fn_3_125850(void) {
    extern int lbl_3_data_91BC;
    DrawingSceneStruct *temp_r31 = lbl_803CC1B8;
    fn_80034E20((void (*)(void))temp_r31, (int*)&lbl_3_data_91BC, NULL);
    g_Minigame.bODRelated = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk1a = 0;
    temp_r31->eventID = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_125604;
}

// .text:0x001258C0 size:0xD44 mapped:0x80764954
void fn_3_1258C0(void) {
    return;
}

// .text:0x00126604 size:0xEB0 mapped:0x80765698
void fn_3_126604(void) {
    return;
}

// .text:0x001274B4 size:0x6B4 mapped:0x80766548
void fn_3_1274B4(void) {
    return;
}

// .text:0x00127B68 size:0xED0 mapped:0x80766BFC
void fn_3_127B68(void) {
    return;
}

// .text:0x00128A38 size:0x158 mapped:0x80767ACC
void fn_3_128A38(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd == 0) {
        if (scene->eventID == 1) {
            if ((lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16) >= 10) {
                lbl_80371C30[scene->unkIndex].obj->field_0x68 = 0;
                scene->eventID++;
            }
            return;
        } else if (scene->eventID == 2) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (lbl_3_common_bss_34C90.field_0x1D2 == 5) {
                    lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
                    scene->eventID++;
                }
            } else if (lbl_3_common_bss_34C90.field_0x1D4 == 5) {
                lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
                scene->eventID++;
            }
            return;
        } else if (scene->eventID != 3 || (lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16) < 20) {
            return;
        }
    }
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
}

typedef struct {
    u16 first;
    u16 second;
} Rep3448U16Pair;

extern u16 lbl_3_data_B0E0[];
extern Rep3448U16Pair lbl_3_data_B140[];

// .text:0x00128B90 size:0x88 mapped:0x80767C24
void fn_3_128B90(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    lbl_3_data_B0E0[1] = lbl_3_data_B140[g_Minigame.GameMode_MiniGame].first;
    lbl_3_data_B0E0[17] = lbl_3_data_B140[g_Minigame.GameMode_MiniGame].second;
    fn_80034E20(scene, lbl_3_data_B0E0);
    scene->eventID = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_128A38;
}

// .text:0x00128C18 size:0x758 mapped:0x80767CAC
void fn_3_128C18(void) {
    return;
}

// .text:0x00129370 size:0x60 mapped:0x80768404
void fn_3_129370(void) {
    // NONMATCHING: target assembly shows 2-arg call (no r5 setup), but fn_80034E20 is
    // declared with 3 args globally; local redeclaration is rejected by CW
    fn_80034E20((void (*)(void))lbl_803CC1B8, (int*)&lbl_3_data_A9F8, (void**)&lbl_803CC1B8);
    lbl_803CC1B8->unk18 = 0;
    lbl_803CC1B8->unk1a = 0;
    lbl_803CC1B8->aFunctionPointer = (void*)fn_3_128C18;
}
