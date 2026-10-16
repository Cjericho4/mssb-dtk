#include "game/rep_720.h"
#include "UnknownHeaders.h"
#include "game/rep_3090.h"
#include "header_rep_data.h"
#include "stl/math.h"

// .text:0x00014BB4 size:0x268 mapped:0x80653C48
void fn_3_14BB4(void) {
    return;
}

// .text:0x00014E1C size:0x34 mapped:0x80653EB0
void fn_3_14E1C(void) {
    // 1. lis r3, lbl_3_bss_44@ha
    // 2. addi r4, r3, lbl_3_bss_44@l
    // Anchoring the pointer to bssPtr ensures r4 is prepared.
    s32 *bssPtr = &lbl_3_bss_44;
    
    // 3. li r0, 0
    // 4. stw r0, 0(r4)
    *bssPtr = 0;

    // 5. li r3, 0 (passing NULL)
    // Overwrites r3 with 0, matching the assembly.
    fn_800528AC(NULL);

}

// .text:0x00014E50 size:0x34 mapped:0x80653EE4
// One register is STWU instead of STW
void fn_3_14E50(void) {
    void (*callback)(void) = fn_3_14BB4; // Anchors to r3
    s32 *bssPtr = &lbl_3_bss_44;        // Anchors to r4

    // stw r0, lbl_3_bss_44@l(r4)
    *bssPtr = 5;

    // Call using r3. r4 remains loaded with bssPtr from the store.
    fn_800528AC(callback); 
}

// .text:0x00014E84 size:0x3C mapped:0x80653F18

void fn_3_14E84(void) {
    /* lbz r0, 0x133(r3) -> cmplwi r0, 2 -> bnelr */
    if (g_FieldingLogic.unk133 != 2) {
        return;
    }

    /* lwz r4, g_pCamera(r3) -> lha r0, 0xaa4(r4) -> cmpwi r0, 0 -> bnelr */
    if (g_pCamera->unkAA4 != 0) {
        return;
    }

    /* lwz r0, 0x24(r3) -> sth r0, 0xaa4(r4) */
    /* Note: sth uses the lower 16 bits of the word loaded from g_Stats */
    g_pCamera->unkAA4 = g_Stats.unk24;
}

// .text:0x00014EC0 size:0x28 mapped:0x80653F54
void fn_3_14EC0(void) {
    if (g_pCamera->unk_A50 == -1) {
        g_pCamera->unk_A50 = g_Strikes.unk_C;
    }
}

// .text:0x00014EE8 size:0x3C mapped:0x80653F7C

/**
 * @address 00014EE8
 */
void fn_3_14EE8(void) {
    /* lbz r0, 0x91(r3) -> cmplwi r0, 0x1 -> bnelr */
    if (g_Batter.contactMadeInd != 1) {
        return;
    }

    /* lwz r4, g_pCamera@l(r3) -> lha r0, 0xaa6(r4) -> cmpwi r0, -1 -> bnelr */
    if (g_pCamera->unkAA6 != -1) {
        return;
    }

    /* lis r3, g_Ball@ha -> addi r3, r3, g_Ball@l -> lha r0, 0x1b9c(r3) */
    /* sth r0, 0xaa6(r4) */
    g_pCamera->unkAA6 = g_Ball.Hit_HorizontalAngle;
}

// .text:0x00014F24 size:0x44 mapped:0x80653FB8

void fn_3_14F24(void) {
    // lha r0, 0x2(r3) -> cmpwi r0, 0x24 -> bltlr
    if (lbl_3_common_bss_32A94.unk2 < 0x24) {
        return;
    }

    // cmpwi r0, 0x26 -> bgtlr
    if (lbl_3_common_bss_32A94.unk2 > 0x26) {
        return;
    }

    // lwz r4, g_pCamera@l(r3) -> lha r0, 0xa9c(r4) -> cmpwi r0, 0 -> bnelr
    if (g_pCamera->unkA9C != 0) {
        return;
    }

    // lwz r0, 0x24(r3) -> sth r0, 0xa9c(r4)
    g_pCamera->unkA9C = (s16)g_Stats.unk24;
}

// .text:0x00014F68 size:0x60 mapped:0x80653FFC
void fn_3_14F68(void) {
    if (g_FieldingLogic.unk133 != 2) return;
    if (g_pCamera->unkAC4 != 0) return;
    g_pCamera->unkAC4 = g_FieldingLogic.unk114;
    g_pCamera->unkA9A = g_Ball.fielderWBallIndex;
    g_pCamera->unkA98 = (s16)g_Stats.unk24;
}

// .text:0x00014FC8 size:0x3C mapped:0x8065405C

/**
 * @address 00014FC8
 */
void fn_3_14FC8(void) {
    /* lis r3, lbl@ha -> addi r3, r3, lbl@l -> lha r0, 0x4(r3) */
    /* cmpwi r0, 0xe -> bnelr */
    if (lbl_3_common_bss_32A94.unk4 != 0xE) {
        return;
    }

    /* lis r3, g_pCamera@ha -> lwz r4, g_pCamera@l(r3) -> lha r0, 0xa96(r4) */
    /* cmpwi r0, 0 -> bnelr */
    if (g_pCamera->unkA96 != 0) {
        return;
    }

    /* lis r3, g_Stats@ha -> addi r3, r3, g_Stats@l -> lwz r0, 0x24(r3) */
    /* sth r0, 0xa96(r4) */
    g_pCamera->unkA96 = (s16)g_Stats.unk24;
}

// .text:0x00015004 size:0xBC mapped:0x80654098
void fn_3_15004(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 3 && g_pCamera->unkAC0[i] == 0) {
            g_pCamera->unkABF = i;
            g_pCamera->unkAC0[i] = 1;
            g_pCamera->unkA94 = g_Stats.unk24;
        }
    }
}

// .text:0x000150C0 size:0x84 mapped:0x80654154
void fn_3_150C0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].baseStandingOn == 3) {
            g_pCamera->unkA8C[i] = g_Stats.unk24;
        }
    }
}

// .text:0x00015144 size:0xDC mapped:0x806541D8
void fn_3_15144(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != 1 && g_Runners[i].runnerOnFieldOrOutOrScored != 2 &&
            g_Runners[i].runnerOnFieldOrOutOrScored != 4) {
            return;
        }
        if (g_Runners[i].groundVelocity[0] > 0.0f &&
            (s32)g_Runners[i].fractionalBasesRan > (s32)g_Runners[i].fractionalBasesRan_stored) {
            if (arg0 == 0) {
                g_pCamera->unkABB[i] = 1;
            } else if (g_pCamera->unkABB[i] == 0) {
                g_pCamera->unkA84[i] = g_Stats.unk24;
            }
        }
    }
}

// .text:0x00015220 size:0x5C mapped:0x806542B4
void fn_3_15220(s32 arg0) {
    if (g_FieldingLogic._pad3[3] == 0) {
        return;
    }
    if (arg0 == 0) {
        g_pCamera->unkABA = 1;
        return;
    }
    if (g_pCamera->unkA82 != 0) {
        return;
    }
    g_pCamera->unkA82 = g_Stats.unk24;
}

// .text:0x0001527C size:0x6C mapped:0x80654310
void fn_3_1527C(s32 arg0) {
    if (g_Ball.ballState != 1) {
        return;
    }
    if (arg0 == 0) {
        g_pCamera->unkAB9 = 1;
        return;
    }
    if (g_pCamera->unkA80 == 0) {
        g_pCamera->unkA9A = g_Ball.fielderWBallIndex;
        g_pCamera->unkA80 = g_Stats.unk24;
    }
}

// .text:0x000152E8 size:0x94 mapped:0x8065437C
void fn_3_152E8(s32 arg0) {
    if (g_Ball.deadBallReason != 0) {
        g_pCamera->unkAB8 = 1;
        g_pCamera->unkAC6 = g_Ball.deadBallReason;
    }
    if (g_Ball.deadBallReason != 1) {
        return;
    }
    if (arg0 == 0) {
        g_pCamera->unkAB8 = 1;
        g_pCamera->unkAC6 = g_Ball.deadBallReason;
        return;
    }
    if (g_pCamera->unkA7E == 0) {
        g_pCamera->unkA7E = g_Stats.unk24;
    }
}

// .text:0x0001537C size:0x74 mapped:0x80654410
void fn_3_1537C(s32 arg0) {
    s16* temp_r4;

    if (g_Batter.hitTrajectory != 0) {
        temp_r4 = &g_pCamera->unkA7C;
        *temp_r4 = *temp_r4 + 1;
    }
    temp_r4 = &g_pCamera->unkA7C;
    if (*temp_r4 <= 0x28) {
        return;
    }
    if (arg0 == 0) {
        g_pCamera->unkAB7 = 1;
        return;
    }
    temp_r4 = &g_pCamera->unkA7A;
    if (*temp_r4 == 0) {
        *temp_r4 = g_Stats.unk24;
    }
}

// .text:0x000153F0 size:0x68 mapped:0x80654484
void fn_3_153F0(s32 arg0) {
    if ((u8)g_Batter.swingInd == 0) return;
    if ((u8)g_Batter.contactMadeInd != 1) return;
    if (arg0 == 0) {
        g_pCamera->unkAB6 = 1;
        return;
    }
    if (g_pCamera->unkA78 == 0) {
        g_pCamera->unkA78 = (s16)g_Stats.unk24;
    }
}

// .text:0x00015458 size:0x6C mapped:0x806544EC
void fn_3_15458(s32 arg0) {
    if (g_Batter.swingInd == 0) {
        return;
    }
    if (g_Batter.framesSinceStartOfSwing != 1) {
        return;
    }
    if (arg0 == 0) {
        g_pCamera->unkAB5 = 1;
        return;
    }
    if (g_Stats.unk36 == 0) {
        g_pCamera->unkA76 = g_Stats.unk24;
    }
}

// .text:0x000154C4 size:0x60 mapped:0x80654558
void fn_3_154C4(s32 arg) {
    if (g_Pitcher.windupCountdownUntilBallReleased != 1) return;
    if (arg == 0) {
        g_pCamera->unkAB4 = 1;
        return;
    }
    if (g_Stats.unk36 != 0) return;
    g_pCamera->unkA74 = (s16)g_Stats.unk24;
}

// .text:0x00015524 size:0x574 mapped:0x806545B8
void fn_3_15524(void) {
    return;
}

// .text:0x00015A98 size:0x290 mapped:0x80654B2C
void fn_3_15A98(void) {
    return;
}

// .text:0x00015D28 size:0x3C mapped:0x80654DBC

void fn_3_15D28(void) {
    /* * Target Sequence:
     * lis r3, g_pCamera@ha -> addi r3, r3, g_pCamera@l
     * lwz r3, 0(r3)        -> Load pointer
     * lbz r0, 0xad8(r3)    -> Load cameraFlag2
     * cmplwi r0, 1         -> Check if flag is 1
     * bne .L_00015D50      -> Skip next call if not 1
     */
    if (g_pCamera->cameraFlag2 == 1) {
        /* bl fn_3_FBE24 */
        fn_3_FBE24();
    }

    /* .L_00015D50:
     * bl fn_3_FD670
     */
    fn_3_FD670();
}

// .text:0x00015D64 size:0x18 mapped:0x80654DF8
void fn_3_15D64(void) {
    g_pCamera->cameraFlag2 = TRUE;
}

// .text:0x00015D7C size:0x14 mapped:0x80654E10
void fn_3_15D7C(u8 value) {
    g_pCamera->cameraFlag = value;
}

// .text:0x00015D90 size:0x188 mapped:0x80654E24
void fn_3_15D90(void) {
    s32 i;
    g_pCamera->unkAC8 = 0;
    g_pCamera->unkA74 = 0;
    g_pCamera->unkA76 = 0;
    g_pCamera->unkA78 = 0;
    g_pCamera->unkA7A = 0;
    g_pCamera->unkA7C = 0;
    g_pCamera->unkA7E = 0;
    g_pCamera->unkA80 = 0;
    g_pCamera->unkA82 = 0;
    for (i = 0; i < 4; i++) {
        g_pCamera->unkA84[i] = 0;
    }
    g_pCamera->unkAA6 = -1;
    g_pCamera->unk_A50 = -1;
    g_pCamera->unkAB5 = 0;
    g_pCamera->unkAB6 = 0;
    g_pCamera->unkAB7 = 0;
    g_pCamera->unkAB8 = 0;
    g_pCamera->unkAC6 = 0;
    g_pCamera->unkAB9 = 0;
    g_pCamera->unkABA = 0;
    g_pCamera->unkAC4 = 0;
    g_pCamera->unkACA = 0;
    for (i = 0; i < 4; i++) {
        g_pCamera->unkABB[i] = 0;
        g_pCamera->unkA8C[i] = 0;
        g_pCamera->unkAC0[i] = 0;
    }
    g_pCamera->unkA9E = -1;
    g_pCamera->unkAA0 = -1;
    g_pCamera->unkAA2 = -1;
    g_pCamera->cameraFlag2 = 0;
    g_pCamera->unkA94 = 0;
    g_pCamera->unkABF = 0;
    g_pCamera->unkA96 = 0;
    g_pCamera->unkA98 = 0;
    g_pCamera->unkA9C = 0;
    g_pCamera->unkAA4 = 0;
    g_pCamera->unkA9A = -1;
}

// .text:0x00015F18 size:0x20 mapped:0x80654FAC
void fn_3_15F18(void) {
    fn_3_FD670();
}

// .text:0x00015F38 size:0x3C mapped:0x80654FCC



void fn_3_15F38(void) {
    if ((u8) g_pCamera->cameraFlag2 == 1) {
        fn_3_FBE24();
    }
    fn_3_FD670();
}

// .text:0x00015F74 size:0x20 mapped:0x80655008
void fn_3_15F74(void) {
    fn_3_FD670();
}

// .text:0x00015F94 size:0x3C mapped:0x80655028

/**
 * @address 00015F94
 */
void fn_3_15F94(void) {
    u32 result;

    /* li r3, 0 -> bl fn_3_9EE24 */
    result = fn_3_9EE24(0);

    /* To match the assembly:
     * 1. result stays in r3.
     * 2. g_d_GameSettings address is loaded into r4.
     * 3. StadiumID is loaded into r0.
     * 4. result (r3) = result (r3) + StadiumID (r0).
     * 5. result (r3) = result (r3) + 0x1D.
     */
    
    result += g_d_GameSettings.StadiumID;
    fn_3_FBDAC(result + 0x1D);
}

// .text:0x00015FD0 size:0x20 mapped:0x80655064
void fn_3_15FD0(void) {
    fn_3_FD670();
}

// .text:0x00015FF0 size:0x24 mapped:0x80655084
void fn_3_15FF0(void) {
    fn_3_FBDAC(0x69);
}

// .text:0x00016014 size:0x20 mapped:0x806550A8
void fn_3_16014(void) {
    fn_3_FD670();
}

// .text:0x00016034 size:0x24 mapped:0x806550C8
void fn_3_16034(void) {
    fn_3_FBDAC(0x68);
}

static inline s32 miniGameIdx_16058(void) {
    switch ((u8)g_Minigame.GameMode_MiniGame) {
        case 0: return 6;
        case 1: return 0;
        case 2: return 4;
        case 3: return 5;
        case 4: return 2;
        case 5: return 3;
        case 6: return 1;
    }
}

// .text:0x00016058 size:0x168 mapped:0x806550EC
void fn_3_16058(void) {
    s32 idx;
    u32 result;
    if (g_GameLogic.FrameCountOfCurrentPitch <= 1) {
        if (g_d_GameSettings.GameModeSelected == 7) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x32);
        } else if (g_d_GameSettings.GameModeSelected == 6) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x32);
        } else {
            result = fn_3_9EE24(0);
            result += g_d_GameSettings.StadiumID;
            fn_3_FBDAC(result + 0x16);
        }
    }
    fn_3_FD670();
}

// .text:0x000161C0 size:0x168 mapped:0x80655254
void fn_3_161C0(void) {
    s32 idx;
    u32 result;
    if (g_GameLogic.FrameCountOfCurrentPitch == 0) {
        if (g_d_GameSettings.GameModeSelected == 7) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x2B);
        } else if (g_d_GameSettings.GameModeSelected == 6) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x2B);
        } else {
            result = fn_3_9EE24(0);
            result += g_d_GameSettings.StadiumID;
            fn_3_FBDAC(result + 0xF);
        }
    }
    fn_3_FD670();
}

// .text:0x00016328 size:0x180 mapped:0x806553BC
void fn_3_16328(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    s32 idx;
    u32 result;
    if (g_GameLogic.FrameCountOfCurrentPitch <= 1) {
        if (settings->GameModeSelected == 5) {
            fn_3_FBDAC(settings->StadiumID + 0x39);
        } else if (settings->GameModeSelected == 7) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x24);
        } else if (settings->GameModeSelected == 6) {
            idx = miniGameIdx_16058();
            result = fn_3_9EE24(0);
            result += idx;
            fn_3_FBDAC(result + 0x24);
        } else {
            result = fn_3_9EE24(0);
            result += settings->StadiumID;
            fn_3_FBDAC(result + 0x8);
        }
    }
    fn_3_FD670();
}

// .text:0x000164A8 size:0x64 mapped:0x8065553C
s32 fn_3_164A8(void) {
    switch ((u8)g_Minigame.GameMode_MiniGame) {
        case 0: return 6;
        case 1: return 0;
        case 2: return 4;
        case 3: return 5;
        case 4: return 2;
        case 5: return 3;
        case 6: return 1;
    }
}

// .text:0x0001650C size:0x1E8 mapped:0x806555A0
void fn_3_1650C(s32* outX, s32* outY, s32 mode, f32 x, f32 y) {
    return;
}

// .text:0x000166F4 size:0x20C mapped:0x80655788
void fn_3_166F4(void) {
    return;
}

// .text:0x00016900 size:0x2A0 mapped:0x80655994
void fn_3_16900(void) {
    return;
}

// .text:0x00016BA0 size:0x1CC mapped:0x80655C34
void fn_3_16BA0(void) {
    return;
}

// .text:0x00016D6C size:0x198 mapped:0x80655E00
void fn_3_16D6C(void) {
    return;
}

// .text:0x00016F04 size:0x20C mapped:0x80655F98
void fn_3_16F04(void) {
    return;
}

// .text:0x00017110 size:0x20C mapped:0x806561A4
void fn_3_17110(void) {
    return;
}

// .text:0x0001731C size:0x444 mapped:0x806563B0
void fn_3_1731C(void) {
    return;
}

// .text:0x00017760 size:0xA4 mapped:0x806567F4
void fn_3_17760(void) {
    return;
}

// .text:0x00017804 size:0x58 mapped:0x80656898
void fn_3_17804(void) {
    g_pCamera->unk2840 = 0.0f;
    g_pCamera->unk2844 = 0.0f;
    g_pCamera->unk2848 = 0.0f;
    g_pCamera->unk284C = 0.0f;
    g_pCamera->unk2850 = 0.0f;
    g_pCamera->unk2854 = 1.0f;
    g_pCamera->unk2878 = 1.0f;
}

// .text:0x0001785C size:0x294 mapped:0x806568F0
void fn_3_1785C(void) {
    return;
}

// .text:0x00017AF0 size:0x3C mapped:0x80656B84



void fn_3_17AF0(void) {
    if ((u8) g_GameLogic.sceneID == 4) {
        fn_3_197E8();
        return;
    }
    fn_3_1C1B0();
}

// .text:0x00017B2C size:0x274 mapped:0x80656BC0
void fn_3_17B2C(void) {
    return;
}

// .text:0x00017DA0 size:0x76C mapped:0x80656E34
void fn_3_17DA0(void) {
    return;
}

// .text:0x0001850C size:0xAEC mapped:0x806575A0
void fn_3_1850C(void) {
    return;
}

// .text:0x00018FF8 size:0x3F0 mapped:0x8065808C
void fn_3_18FF8(void) {
    return;
}

// .text:0x000193E8 size:0x1D4 mapped:0x8065847C
void fn_3_193E8(void) {
    return;
}

// .text:0x000195BC size:0x1B4 mapped:0x80658650
void fn_3_195BC(void) {
    return;
}

// .text:0x00019770 size:0x78 mapped:0x80658804
void fn_3_19770(void) {
    Data1348Entry* entry;
    Camera* cam;
    cam = g_pCamera;
    entry = &lbl_3_data_1348[cam->unk11C];
    cam->unkE4 = entry->unk00;
    cam->unkF0 = entry->unk0C;
    cam->unk108 = 0.0f;
    cam->unkE8 = entry->unk04;
    cam->unkF4 = entry->unk10;
    cam->unk10C = 0.0f;
    cam->unkEC = entry->unk08;
    cam->unkF8 = entry->unk14;
    cam->unk110 = 0.0f;
    cam->unk114 = entry->unk18;
    cam->unk11A = 1;
}

// .text:0x000197E8 size:0x354 mapped:0x8065887C
void fn_3_197E8(void) {
    return;
}

// .text:0x00019B3C size:0x174 mapped:0x80658BD0
void fn_3_19B3C(void) {
    return;
}

// .text:0x00019CB0 size:0x2F4 mapped:0x80658D44
void fn_3_19CB0(void) {
    return;
}

// .text:0x00019FA4 size:0xEA0 mapped:0x80659038
void fn_3_19FA4(void) {
    return;
}

// .text:0x0001AE44 size:0x74 mapped:0x80659ED8
void fn_3_1AE44(u8 arg0, s16 arg1, f32 arg2, f32 arg3, f32 arg4) {
    if (g_Stats.unk36 != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        return;
    }
    g_pCamera->unk2828 = arg2;
    g_pCamera->unk282C = arg3;
    g_pCamera->unk2830 = arg4;
    g_pCamera->unk2838 = 0;
    g_pCamera->unk283C = arg1;
    g_pCamera->unk283E = 1;
    g_pCamera->unk283F = arg0;
}

// .text:0x0001AEB8 size:0x2C4 mapped:0x80659F4C
void fn_3_1AEB8(void) {
    return;
}

// .text:0x0001B17C size:0x1F4 mapped:0x8065A210
void fn_3_1B17C(void) {
    return;
}

// .text:0x0001B370 size:0x6A8 mapped:0x8065A404
void fn_3_1B370(void) {
    return;
}

// .text:0x0001BA18 size:0x698 mapped:0x8065AAAC
void fn_3_1BA18(void) {
    return;
}

// .text:0x0001C0B0 size:0x80 mapped:0x8065B144
void fn_3_1C0B0(void) {
    f32 f1 = 0.0f;
    f32 f0;


    g_pCamera->unk_30 = f1;
            f0 = 1.0f;

    g_pCamera->unk_34 = f1;
    g_pCamera->unk_38 = f1;
    g_pCamera->unk_C0 = f1;
    g_pCamera->unk_D0 = f0;
    
    g_pCamera->unk_E2 = 0;
    g_pCamera->unk_E0 = -1;
    g_pCamera->unk_D4 = f1;
    g_pCamera->unk_D8 = f1;
    g_pCamera->unk_DC = f1;
    g_pCamera->unk_E3 = 0;
}

// .text:0x0001C130 size:0x80 mapped:0x8065B1C4
void fn_3_1C130(void) {
    f32 f1 = 0.0f;
    f32 f0;

    g_pCamera->unk_30 = f1;
    f0 = 1.0f;
    
    g_pCamera->unk_34 = f1;
    g_pCamera->unk_38 = f1;
    g_pCamera->unk_C0 = f1;
    g_pCamera->unk_D0 = f0;
    
    g_pCamera->unk_E2 = 0;
    g_pCamera->unk_E0 = -1;
    g_pCamera->unk_D4 = f1;
    g_pCamera->unk_D8 = f1;
    g_pCamera->unk_DC = f1;
    g_pCamera->unk_E3 = 0;
}

// .text:0x0001C1B0 size:0x4D4 mapped:0x8065B244
void fn_3_1C1B0(void) {
    return;
}

// .text:0x0001C684 size:0x214 mapped:0x8065B718
void fn_3_1C684(void) {
    return;
}

// .text:0x0001C898 size:0x10 mapped:0x8065B92C
u8 getSceneID(void) {
    return g_GameLogic.sceneID;
}

// .text:0x0001C8A8 size:0x4 mapped:0x8065B93C
void fn_3_1C8A8(void) {
    return;
}

// .text:0x0001C8AC size:0x214 mapped:0x8065B940
void fn_3_1C8AC(void) {
    return;
}

typedef struct {
    u8 _pad0[0x40];
    Mtx mtx;         /* 0x40 */
    VecXYZ eye;      /* 0x70 */
    VecXYZ target;   /* 0x7C */
    u8 _pad88[0x1C];
    f32 unkA4;       /* 0xA4 */
} CameraRenderObj;
CameraRenderObj* fn_80052768(s32 arg0);

// .text:0x0001CAC0 size:0x10C mapped:0x8065BB54
void fn_3_1CAC0(void) {
    CameraRenderObj* obj;

    obj = fn_80052768(g_pCamera->unk28A8);
    obj->eye.x = g_pCamera->unk2840;
    obj->eye.y = -g_pCamera->unk2844;
    obj->eye.z = g_pCamera->unk2848;
    obj->target.x = g_pCamera->unk284C;
    obj->target.y = -g_pCamera->unk2850;
    obj->target.z = g_pCamera->unk2854;
    if (lbl_3_common_bss_DE94->field_0x9AC == 0) {
        obj->unkA4 = g_pCamera->unk2878;
    } else {
        obj->unkA4 = ((36.0 / tan((57.29578f * lbl_3_common_bss_DE94->fov) / 114.59155f)) * 0.5) / 74.0;
    }
}

// .text:0x0001CBCC size:0xFC mapped:0x8065BC60
extern s16 lbl_3_data_A38[2];

void fn_3_1CBCC(void) {
    g_GameLogic.sceneID = 1;
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        g_pCamera->unk28A7 = lbl_3_data_A38[1];
    } else {
        g_pCamera->unk28A7 = lbl_3_data_A38[0];
    }
    g_pCamera->unk118 = 0;
    g_pCamera->unk11C = 0;
    g_pCamera->unk_30 = 0.0f;
    g_pCamera->unk_34 = 0.0f;
    g_pCamera->unk_38 = 0.0f;
    g_pCamera->unk_C0 = 0.0f;
    g_pCamera->unk_D0 = 1.0f;
    g_pCamera->unk_E2 = 0;
    g_pCamera->unk_E0 = -1;
    g_pCamera->unk_D4 = 0.0f;
    g_pCamera->unk_D8 = 0.0f;
    g_pCamera->unk_DC = 0.0f;
    g_pCamera->unk_E3 = 0;
}

// .text:0x0001CCC8 size:0x1C8 mapped:0x8065BD5C
void fn_3_1CCC8(void) {
    return;
}

// .text:0x0001CE90 size:0x9DC mapped:0x8065BF24
void fn_3_1CE90(void) {
    return;
}
