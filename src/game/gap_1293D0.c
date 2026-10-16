#include "game/gap_1293D0.h"
#include "game/UnknownHomes_Game.h"
#include "stl/mem.h"
#include "UnknownHeaders.h"
#include "game/gap_11D3AC.h"
#include "game/gap_EA340.h"
#include "game/rep_3448.h"
#include "game/gap_97144.h"
#include "game/gap_AC9F8.h"
#include "game/gap_1658F0.h"
#include "game/rep_1770.h"
#include "game/gap_157DB8.h"

extern void fn_8004CC2C(void);
extern void fn_8004D0F0(void);

// .text:0x001293D0 size:0x78 mapped:0x80768468
void fn_3_1293D0(void) {
    if (g_GameLogic._125 == 0) {
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic._125 == 5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
    }
    if (g_GameLogic._125 == 6) {
        fn_8004CC2C();
    }
}

// .text:0x00129458 size:0x104 mapped:0x807684EC
void fn_3_129458(void) {
    if (g_GameLogic.gameStatus == 0xE && g_GameLogic._125 == 1) {
        lbl_3_common_bss_32724.unk_B7 = 0;
        lbl_3_common_bss_32724.unk_B6 = 0;
        if (g_Minigame.GameMode_MiniGame == 1 && g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            fn_800B0A5C_insertQueue(fn_3_11D780, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_EA454, 2);
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic.gameStatus == 0x22 && (lbl_3_common_bss_34C90.field_0x1D2 == 7 || g_GameLogic.framesOfExitingToMenu != 0)) {
        lbl_3_common_bss_32724.unk_B7 = 1;
    }
}

// .text:0x0012955C size:0x4BC mapped:0x807685F0
void fn_3_12955C(void) {
    return;
}

// .text:0x00129A18 size:0x270 mapped:0x80768AAC
void fn_3_129A18(void) {
    return;
}

// .text:0x00129C88 size:0x2C0 mapped:0x80768D1C
void fn_3_129C88(void) {
    return;
}

// .text:0x00129F48 size:0xB0 mapped:0x80768FDC
void fn_3_129F48(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    fn_80034E20(scene, &lbl_3_data_9FB4);
    scene->unk_1C = 0;
    if (lbl_3_common_bss_32724.unk_BF != 0) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x160000;
        scene->unk_1C = 2;
    }
    scene->unk18 = 0;
    scene->unk1a = 0;
    lbl_3_common_bss_32724.unk_BE = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_129C88;
}

// .text:0x00129FF8 size:0x2C0 mapped:0x8076908C
void fn_3_129FF8(void) {
    return;
}

// .text:0x0012A2B8 size:0x138 mapped:0x8076934C
extern s32 lbl_3_data_9ECC;

void fn_3_12A2B8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 level = g_d_GameSettings.miniGameLevels[g_Minigame.GameMode_MiniGame];
    s32 i;

    if (g_Minigame._190A != 0) {
        level = 2;
    }
    fn_80034E20(scene, &lbl_3_data_9ECC);
    for (i = 0; i < 4; i++) {
        if (level >= i) {
            fn_800363D8(scene, i + 2, 1, 0x6B, i);
        } else {
            fn_800363D8(scene, i + 2, 1, 0x6B, 4);
        }
    }
    scene->unk_1C = 0;
    if (lbl_3_common_bss_32724.unk_BF != 0) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x160000;
        scene->unk_1C = 2;
    }
    scene->unk18 = 0;
    scene->unk1a = 0;
    lbl_3_common_bss_32724.unk_BE = 1;
    lbl_803CC1B8->aFunctionPointer = fn_3_129FF8;
}

// .text:0x0012A3F0 size:0x2D4 mapped:0x80769484
void fn_3_12A3F0(void) {
    return;
}

// .text:0x0012A6C4 size:0x24C mapped:0x80769758
void fn_3_12A6C4(void) {
    return;
}

// .text:0x0012A910 size:0xE90 mapped:0x807699A4
void fn_3_12A910(void) {
    return;
}

// .text:0x0012B7A0 size:0x3C4 mapped:0x8076A834
void fn_3_12B7A0(void) {
    return;
}

// .text:0x0012BB64 size:0x484 mapped:0x8076ABF8
void fn_3_12BB64(void) {
    return;
}

// .text:0x0012BFE8 size:0x1C4 mapped:0x8076B07C
void fn_3_12BFE8(void) {
    return;
}

// .text:0x0012C1AC size:0x244 mapped:0x8076B240
void fn_3_12C1AC(void) {
    return;
}

// .text:0x0012C3F0 size:0x124 mapped:0x8076B484
void fn_3_12C3F0(void) {
    return;
}

// .text:0x0012C514 size:0xB8 mapped:0x8076B5A8
void fn_3_12C514(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E364, 2);
        lbl_3_common_bss_32724.unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// .text:0x0012C5CC size:0xB8 mapped:0x8076B660
void fn_3_12C5CC(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E7C4, 2);
        lbl_3_common_bss_32724.unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// .text:0x0012C684 size:0xC8 mapped:0x8076B718
void fn_3_12C684(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_11EC28, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11F02C, 2);
        lbl_3_common_bss_32724.unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// .text:0x0012C74C size:0x11C mapped:0x8076B7E0
void fn_3_12C74C(void) {
    CommonBss_32724* state = &lbl_3_common_bss_32724;
    MiniGameStruct* mg;

    if (state->unk_B6 != 0) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        mg = &g_Minigame;
        if (mg->multiPlayerInd == 0) {
            fn_800B0A5C_insertQueue(fn_3_11F508, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_11F778, 2);
        fn_800B0A5C_insertQueue(fn_3_11FA58, 2);
        fn_800B0A5C_insertQueue(fn_3_11FDB0, 2);
        if (mg->multiPlayerInd != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        state->unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// .text:0x0012C868 size:0x11C mapped:0x8076B8FC
void fn_3_12C868(void) {
    if (g_GameLogic.gameStatus == 0x1A) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_12026C, 2);
        fn_800B0A5C_insertQueue(fn_3_12089C, 2);
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            fn_800B0A5C_insertQueue(fn_3_120FF8, 2);
        } else {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
            fn_800B0A5C_insertQueue(fn_3_123990, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_121304, 2);
        lbl_3_common_bss_32724.unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
        fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
    }
}

// .text:0x0012C984 size:0x10C mapped:0x8076BA18
void fn_3_12C984(void) {
    CommonBss_32724* state = &lbl_3_common_bss_32724;

    if (state->unk_B6 != 0) {
        memset(g_Minigame.targetPointsArray, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_121908, 2);
        if (g_Minigame.multiPlayerInd != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_1226D4, 2);
        fn_800B0A5C_insertQueue(fn_3_122334, 2);
        fn_800B0A5C_insertQueue(fn_3_1235B8, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        state->unk_B6 = lbl_3_common_bss_32724.unk_B7 = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
    fn_3_97144();
}

// .text:0x0012CA90 size:0x764 mapped:0x8076BB24
void fn_3_12CA90(void) {
    return;
}

// .text:0x0012D1F4 size:0x960 mapped:0x8076C288
void fn_3_12D1F4(void) {
    return;
}

// .text:0x0012DB54 size:0x2C mapped:0x8076CBE8
// .text:0x0012DB54 size:0x2C mapped:0x8076CBAC
void fn_3_12DB54(void) {
    s8 i = 0;
    do {
        g_Minigame._1DBC[i] = 0;
        i++;
    } while (i < 4);
}

// .text:0x0012DB80 size:0x208 mapped:0x8076CC14
void fn_3_12DB80(void) {
    return;
}

// .text:0x0012DD88 size:0x44 mapped:0x8076CE1C
s32 fn_3_12DD88(void) {
    u32 count = 0;
    do {
        if (g_Minigame.barrels[count].barrelState != 2) break;
        count++;
    } while (count < 15);
    return count >= 15;
}

// .text:0x0012DDCC size:0x2B8 mapped:0x8076CE60
void fn_3_12DDCC(void) {
    return;
}

// .text:0x0012E084 size:0xF8 mapped:0x8076D118
s32 fn_3_12E084(MinigameRankEntry* a, MinigameRankEntry* b) {
    MiniGameStruct* mg = &g_Minigame;
    s8 ra;
    s8 rb;

    if (a->score != b->score) {
        return b->score - a->score;
    }
    if (a->rank != b->rank) {
        if ((s8)mg->randomTargets[1]._2 != 0) {
            return a->rank - b->rank;
        }
        return b->rank - a->rank;
    }
    ra = __abs(2 - a->id / 3);
    rb = __abs(2 - b->id / 3);
    if (ra != rb) {
        return ra - rb;
    }
    ra = __abs(1 - a->id % 3);
    rb = __abs(1 - b->id % 3);
    return ra - rb;
}

// .text:0x0012E17C size:0x208 mapped:0x8076D210
void fn_3_12E17C(void) {
    return;
}

// .text:0x0012E384 size:0x484 mapped:0x8076D418
void fn_3_12E384(void) {
    return;
}

// .text:0x0012E808 size:0x34 mapped:0x8076D89C
void fn_3_12E808(void) {
    memset(g_Minigame._1D7C, 0, 0x78);
}

// .text:0x0012E83C size:0xC0 mapped:0x8076D8D0
void fn_3_12E83C(void) {
    u8 hits = g_Minigame.barrelBatter_barrelsHit;
    s32 points;

    if (hits <= 1) {
        points = lbl_3_data_217A4[5] * hits;
    } else {
        points = hits * ((hits - 1) * lbl_3_data_217A4[5]);
    }
    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += points;
    g_Minigame.targetPointsArray[0] = points;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Minigame.rosterID == lbl_3_common_bss_37400.playerIndex) {
        fn_3_1608F0(2, points, g_Minigame.barrelBatter_barrelsHit);
    }
}

