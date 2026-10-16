#include "Dolphin/vec.h"
#include "game/rep_36D8.h"
#include "UnknownHeaders.h"
#include "game/rep_1838.h"
#include "game/rep_13B8.h"
#include "game/gap_5985C.h"
#include "game/rep_3880.h"
#include "game/rep_3448.h"
#include "game/rep_F80.h"
#include "musyx/musyx.h"
#include "game/gap_157DB8.h"
#include "game/m_sound.h"

// .text:0x0013C7BC size:0xDBC mapped:0x8077B850
void fn_3_13C7BC(void) {
    return;
}

// .text:0x0013D578 size:0x70 mapped:0x8077C60C
s32 fn_3_13D578(s8 arg0) {
    s8 i = 0;
    do {
        s8 charIdx = g_Minigame.minigameControlStruct[0].characterIndex[i];
        if (charIdx >= 0 && charIdx < 4) {
            if (g_Minigame.miniGameCurrentPoints[i] > g_Minigame.miniGameCurrentPoints[arg0]) {
                return 1;
            }
        }
        i++;
    } while (i < 4);
    return 0;
}

// .text:0x0013D5E8 size:0x30 mapped:0x8077C67C
//Two instructions swapped order
s32 fn_3_13D5E8(unk_13d5e8_struct* a, unk_13d5e8_struct* b) {
    return (s32)((100.0f * a->value) - (100.0f * b->value));
}

// .text:0x0013D618 size:0x408 mapped:0x8077C6AC
void fn_3_13D618(void) {
    return;
}

// .text:0x0013DA20 size:0x30 mapped:0x8077CAB4
// Same issue as fn_3_13D5E8.
s32 fn_3_13DA20(unk_13d5e8_struct* a, unk_13d5e8_struct* b) {
    return (s32)((100.0f * a->value) - (100.0f * b->value));
}

// .text:0x0013DA50 size:0x1F8 mapped:0x8077CAE4
f32 fn_3_13DA50(s8 index, f32 targetPos, s8 *result) {
    f32 zero = 0.0f; // Load f0 early
    f32 wrappedTarget = targetPos; // fmr f3, f1
    InMemRunnerType *runner = &g_Runners[index];
    f32 fractionalBasesRan = runner->fractionalBasesRan; // lfs f4
    f32 wrappedRunner;
    f32 dist1;
    f32 dist2;

    wrappedRunner = fractionalBasesRan; // fmr f2, f4
    if (fractionalBasesRan < zero) {
        wrappedRunner = fractionalBasesRan + 4.0f;
    } else if (fractionalBasesRan >= 4.0f) {
        wrappedRunner = fractionalBasesRan - 4.0f;
    }

    if (targetPos < zero) {
        wrappedTarget = targetPos + 4.0f;
    } else if (targetPos >= 4.0f) {
        wrappedTarget = targetPos - 4.0f;
    }

    if (wrappedRunner > wrappedTarget) {
        dist1 = (4.0f + wrappedTarget) - wrappedRunner;
    } else {
        dist1 = wrappedTarget - wrappedRunner;
    }

    if (runner->runningDirectionCode == 3) {
        dist1 += 0.15f;
    }

    if (fractionalBasesRan < zero) {
        fractionalBasesRan += 4.0f;
    } else if (fractionalBasesRan >= 4.0f) {
        fractionalBasesRan -= 4.0f;
    }

    if (targetPos < zero) {
        targetPos += 4.0f;
    } else if (targetPos >= 4.0f) {
        targetPos -= 4.0f;
    }

    if (fractionalBasesRan < targetPos) {
        dist2 = (4.0f + fractionalBasesRan) - targetPos;
    } else {
        dist2 = fractionalBasesRan - targetPos;
    }

    if (runner->runningDirectionCode == 1) {
        dist2 += 0.15f;
    }

    if (dist1 < dist2) {
        *result = 1;
        return dist1;
    }
    
    if (dist1 > dist2) {
        *result = 3;
        return dist2;
    }

    if (RandomInt_Game(2) == 0) {
        *result = 3;
    } else {
        *result = 1;
    }
    return dist1;
}

// .text:0x0013DC48 size:0x198 mapped:0x8077CCDC
void fn_3_13DC48(void) {
    return;
}

// .text:0x0013DDE0 size:0xC4 mapped:0x8077CE74
void fn_3_13DDE0(void) {
    return;
}

// .text:0x0013DEA4 size:0x118 mapped:0x8077CF38
typedef struct {
    s16 min;
    s16 max;
} RangeS16_36D8;

typedef struct {
    s8 min;
    s8 max;
} RangeS8_36D8;

extern RangeS8_36D8 lbl_3_data_21944[4];
extern RangeS16_36D8 lbl_3_data_2194C[4];
extern s8 lbl_3_data_2197C[4];
extern s8 lbl_3_data_21980[4];

static inline void setTargetSpawn(MinigameTargetSpawn* target, u8 strength) {
    s8 minVal;

    target->value = RandomInt_Game_Range(lbl_3_data_2194C[strength].min, lbl_3_data_2194C[strength].max);
    if (RandomInt_Game(100) < lbl_3_data_2197C[strength]) {
        minVal = lbl_3_data_21980[strength];
        if (minVal < 8) {
            target->unk6 = RandomInt_Game_Range(minVal, 8);
        } else {
            target->unk6 = 8;
        }
    } else {
        target->unk6 = 0x7F;
    }
    target->unk5 = 2;
    target->unk7 = RandomInt_Game_Range(lbl_3_data_21944[strength].min, lbl_3_data_21944[strength].max);
}

void fn_3_13DEA4(void) {
    MinigameTargetSpawn* spawns = g_Minigame.targetSpawns;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    i = 0;
    do {
        MinigameTargetSpawn* target = &spawns[i];
        setTargetSpawn(target, g_Minigame.players.aIStrength[i]);
    } while (++i < 4);
}

extern f32 lbl_3_bss_B794;
extern s32 lbl_3_bss_B798;
void fn_800528B4(void);

// .text:0x0013DFBC size:0x1B8 mapped:0x8077D050
void fn_3_13DFBC(CameraView* cam) {
    Vec v;
    Mtx m;
    s32 range;

    range = 1000.0f * lbl_3_bss_B794;
    v.x = (rand() % range - range / 2) / 1000.0;
    v.y = (rand() % range - range / 2) / 1000.0;
    v.z = 0.0f;
    PSMTXInverse(cam->viewMtx, m);
    PSMTXMultVecSR(m, &v, &v);
    cam->pos.x += v.x;
    cam->pos.y += v.y;
    cam->pos.z += v.z;
    cam->target.x += v.x;
    cam->target.y += v.y;
    cam->target.z += v.z;
    if (--lbl_3_bss_B798 <= 0) {
        lbl_3_bss_B798 = 0;
        lbl_3_bss_B794 = 0.0f;
        fn_800528B4();
    }
}

// .text:0x0013E174 size:0xA8 mapped:0x8077D208
typedef struct {
    u8 _pad0[0xC];
    f32 unkC;     /* 0x0C */
    f32 unk10;    /* 0x10 */
    u8 _pad14[0x18 - 0x14];
    f32 unk18;    /* 0x18 */
    u8 _pad1C[0x30 - 0x1C];
    f32 unk30[2]; /* 0x30 */
    f32 unk38[2]; /* 0x38 */
    f32 unk40[2]; /* 0x40 */
} Data218BC;
extern Data218BC lbl_3_data_218BC;
extern f32 lbl_3_bss_B794;
extern s32 lbl_3_bss_B798;

void fn_3_13E174(u8 mode) {
    switch (mode) {
    case 0:
        lbl_3_bss_B798 = lbl_3_data_218BC.unk30[0];
        lbl_3_bss_B794 = lbl_3_data_218BC.unk38[0];
        break;
    case 1:
        lbl_3_bss_B798 = lbl_3_data_218BC.unk30[1];
        lbl_3_bss_B794 = lbl_3_data_218BC.unk38[1];
        break;
    default:
        return;
    }
    fn_800528AC((void (*)(void))fn_3_13DFBC);
}

// .text:0x0013E21C size:0x188 mapped:0x8077D2B0
void fn_3_13E21C(f32* arg0) {
    return;
}

// .text:0x0013E3A4 size:0x2CC mapped:0x8077D438
void fn_3_13E3A4(f32* arg0) {
    return;
}

// .text:0x0013E670 size:0x64 mapped:0x8077D704
void fn_3_13E670(void) {
    if ((u8)g_Minigame.turnOverStatus != 0) {
        g_Minigame.playerIDWithPowerup[0] = -1;
        g_Minigame._CCE[0] = 0;
        return;
    }
    if ((u8)g_Minigame._CCE[0] != 0) {
        fn_3_13E21C(&g_Minigame._CB0);
        return;
    }
    fn_3_13E3A4(&g_Minigame._CB0);
}

typedef struct {
    u8 _pad0[0x10];
    f32 gravity;     /* 0x10 */
    f32 bounceDamp;  /* 0x14 */
    f32 bounceRest;  /* 0x18 */
} WallBallCoinPhysics;
extern WallBallCoinPhysics lbl_3_data_2188C;
extern s16 lbl_3_data_218A8;

// .text:0x0013E6D4 size:0x100 mapped:0x8077D768
void fn_3_13E6D4(void) {
    u32 i;

    for (i = 15; i < 35; i++) {
        if (g_Minigame.wallBall_coinsVisibleInd) {
            PSVECAdd((Vec*)&g_Minigame.wallBall_coinCoordinates[i], (Vec*)&g_Minigame.wallBall_coinVelocity[i], (Vec*)&g_Minigame.wallBall_coinCoordinates[i]);
            g_Minigame.wallBall_coinVelocity[i].y += lbl_3_data_2188C.gravity;
            if (g_Minigame.wallBall_coinCoordinates[i].y < 0.01) {
                g_Minigame.wallBall_coinCoordinates[i].y = 0.01f;
                g_Minigame.wallBall_coinVelocity[i].x *= lbl_3_data_2188C.bounceDamp;
                g_Minigame.wallBall_coinVelocity[i].z *= lbl_3_data_2188C.bounceDamp;
                g_Minigame.wallBall_coinVelocity[i].y *= -lbl_3_data_2188C.bounceRest;
            }
            if (++g_Minigame.wallBall_coinsVisibleFrameCounter[i] >= lbl_3_data_218A8) {
                g_Minigame.wallBall_coinsVisibleInd[i] = 0;
            }
        }
    }
}

// .text:0x0013E7D4 size:0x25C mapped:0x8077D868
void fn_3_13E7D4(void) {
    return;
}

// .text:0x0013EA30 size:0x214 mapped:0x8077DAC4
void fn_3_13EA30(void) {
    return;
}

// .text:0x0013EC44 size:0x840 mapped:0x8077DCD8
void fn_3_13EC44(void) {
    return;
}

// .text:0x0013F484 size:0x244 mapped:0x8077E518
void fn_3_13F484(void) {
    return;
}

// .text:0x0013F6C8 size:0x11C mapped:0x8077E75C
void fn_3_13F6C8(void) {
    return;
}

// .text:0x0013F7E4 size:0xE0 mapped:0x8077E878
void fn_3_13F7E4(void) {
    return;
}

// .text:0x0013F8C4 size:0x360 mapped:0x8077E958
void fn_3_13F8C4(void) {
    return;
}

// .text:0x0013FC24 size:0x660 mapped:0x8077ECB8
void fn_3_13FC24(void) {
    return;
}

// .text:0x00140284 size:0x200 mapped:0x8077F318
void fn_3_140284(void) {
    return;
}

// .text:0x00140484 size:0x154 mapped:0x8077F518
extern void fn_8004C094(f32* arg0);
extern s16 lbl_3_data_21904[];

void fn_3_140484(void) {
    MiniGameStruct* mg = &g_Minigame;
    s32 i;

    if (mg->turnOverStatus != 0) {
        return;
    }
    mg->_1AE4 += mg->_1AF0;
    if (mg->_1AE4 <= 0.0f && mg->_1AF0 < -lbl_3_data_218BC.unk18) {
        mg->_1AF0 = 0.0f;
        mg->_1AE4 = 0.0f;
        fn_8004C094(&mg->_1AE0);
        fn_3_90064(0x2DF);
        lbl_3_bss_B798 = lbl_3_data_218BC.unk30[0];
        lbl_3_bss_B794 = lbl_3_data_218BC.unk38[0];
        fn_800528AC((void (*)(void))fn_3_13DFBC);
        for (i = 0; i < 4; i++) {
            fn_3_6C854(i, 1);
        }
    } else if (mg->_1AE4 > 0.0f) {
        mg->_1AF0 -= lbl_3_data_218BC.unk18;
    }
    if (g_Minigame._1AFA >= lbl_3_data_21904[9]) {
        g_Minigame._1B19 = 2;
        g_Minigame._1AFA = 0;
        mg->_1AF0 = lbl_3_data_218BC.unk10;
    }
}

// .text:0x001405D8 size:0x11C mapped:0x8077F66C
extern s16 lbl_3_data_21804[][9];

void fn_3_1405D8(void) {
    MiniGameStruct* mg = &g_Minigame;
    u8 idx;
    s16 r;

    if (mg->_1AFA <= 1) {
        if (mg->multiPlayerInd != 0) {
            idx = 4;
        } else {
            idx = mg->soloMinigameDifficulty;
        }
        r = RandomInt_Game_Range(0, 1000);
        g_Minigame._1B06 = 0;
        do {
            r -= lbl_3_data_21804[idx][g_Minigame._1B06++];
        } while (r > 0 && lbl_3_data_21804[idx][g_Minigame._1B06] >= 0);
        g_Minigame._1B06 *= 0x78;
        g_Minigame._1B06 -= 0x30;
        fn_3_157DB8(g_Minigame._1B06);
    } else {
        mg->_1AF8 = 0xE00;
        if (mg->_1AFA >= mg->_1B06) {
            mg->_1B19 = 1;
            mg->_1AFA = 0;
            mg->_1AF0 = lbl_3_data_218BC.unkC;
            fn_3_14C904();
            fn_3_90064(0x2E0);
        }
    }
}

// .text:0x001406F4 size:0x2B8 mapped:0x8077F788
void fn_3_1406F4(void) {
    return;
}

// .text:0x001409AC size:0x220 mapped:0x8077FA40
void fn_3_1409AC(void) {
    return;
}

// .text:0x00140BCC size:0x114 mapped:0x8077FC60

void fn_3_140BCC(void) {
    MiniGameStruct* mg = &g_Minigame;
    GameControlsStruct* gl;

    if (mg->turnOverStatus == 0) {
        if (mg->_17C4 == 0) {
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4.unk7, 0x3F, 0);
            fn_3_151798();
            fn_3_11F480();
            fn_80011578();
            g_Minigame._CCE[0] = 0;
            mg->turnOverStatus = 1;
        }
        return;
    }
    if (mg->turnOverStatus == 1) {
        mg->turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_21904[0];
    }
    if (g_Minigame._1B19 != 3) {
        g_GameLogic.CountdownUntilFade--;
    }
    gl = &g_GameLogic;
    if (gl->CountdownUntilFade == 7) {
        changeScene(3, 6);
        fn_3_1578F8();
    }
    if (gl->CountdownUntilFade <= 0) {
        fn_3_1409AC();
    }
}

// .text:0x00140CE0 size:0x410 mapped:0x8077FD74
void fn_3_140CE0(void) {
    return;
}

// .text:0x001410F0 size:0x1CC mapped:0x80780184
void fn_3_1410F0(void) {
    return;
}

// .text:0x001412BC size:0x128 mapped:0x80780350
void fn_3_1412BC(void) {
    return;
}

// .text:0x001413E4 size:0xC8 mapped:0x80780478
void fn_3_1413E4(void) {
    fn_3_7DD6C();
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278.unk0);
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278.unk0 + lbl_3_data_21278.unk1) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x001414AC size:0x580 mapped:0x80780540
void fn_3_1414AC(void) {
    return;
}
