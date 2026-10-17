#include "game/rep_1200.h"
#include "game/rep_1188.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern f32 lbl_3_rodata_1250;
extern void fn_3_5C69C(s32 arg0);
void fn_3_89864(s32 idx, s32 delta);
void fn_3_155288(void);
BOOL fn_3_6F4E8(void);
/* rep_1200 callers test the full r3 (cmplwi, no clrlwi): declared here as u32. */
u32 fn_3_107DB4(s8 arg0);
void fn_3_7CE90(void);
f32 RandomF32_Game_Range(f32 a, f32 b);
extern f32 lbl_3_data_4474[4];
extern f32 lbl_3_data_5EB0[2];
extern f32 lbl_3_data_5F5C[8];
extern f32 lbl_3_data_2138C[4];

// .text:0x0006F6CC size:0x7C mapped:0x806AE760
s32 fn_3_6F6CC(void) {
    f32 limit;
    InMemRunnerType* runner;
    s32 i;

    limit = 0.5f;
    runner = g_Runners;

    for (i = 1; i < 4; i++) {
        if (runner[i].runnerOnFieldOrOutOrScored == 1 && runner[i].percentTowardsNextBase > limit) {
            g_Pitcher.pickOffLoc = 4;
            fn_3_5C69C(0);
            return 1;
        }
    }

    return 0;
}

// .text:0x0006F748 size:0x2E0 mapped:0x806AE7DC
void fn_3_6F748(void) {
    return;
}

// .text:0x0006FA28 size:0x170 mapped:0x806AEABC
void fn_3_6FA28(void) {
    return;
}

// .text:0x0006FB98 size:0x208 mapped:0x806AEC2C
void fn_3_6FB98(void) {
    return;
}

// .text:0x0006FDA0 size:0x224 mapped:0x806AEE34
void fn_3_6FDA0(void) {
    return;
}

// .text:0x0006FFC4 size:0x2BC mapped:0x806AF058
void fn_3_6FFC4(void) {
    return;
}

typedef struct {
    u8 _pad0[2];
    u8 bodyType;     /* 0x2 */
    u8 _pad3[3];
} CharacterBodyInfo; /* size: 0x6 */

typedef struct {
    u8 maxZ; /* 0x0 */
    u8 maxX; /* 0x1 */
    u8 minX; /* 0x2 */
} HitByPitchZone; /* size: 0x3 */

extern CharacterBodyInfo lbl_800E8558[];
extern HitByPitchZone lbl_3_data_76FC[];

// .text:0x00070280 size:0x16C mapped:0x806AF314
void fn_3_70280(void) {
    BOOL hit = FALSE;
    s32 dx;
    s32 dz;
    s32 type;

    if (g_GameLogic.secondaryGameMode == 0xB && g_Practice._1DB == 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 2) {
        return;
    }
    if (g_Batter.framesSinceStartOfSwing > 0) {
        return;
    }
    if (g_Pitcher.calledStrikeInd != 0) {
        return;
    }
    dx = 100.0f * (g_Pitcher.ballCurrentPosition.x - g_Batter.batterPos.x);
    dz = 100.0f * (g_Pitcher.ballCurrentPosition.z - g_Batter.batterPos.z);
    if (g_Batter.batterHand != 0) {
        dx = -dx;
    }
    type = lbl_800E8558[g_Batter.charID].bodyType;
    if (dz <= lbl_3_data_76FC[type].maxZ && (f32)dz >= 0.0f && dx <= lbl_3_data_76FC[type].maxX &&
        dx >= -lbl_3_data_76FC[type].minX) {
        hit = TRUE;
    }
    if (hit) {
        g_Batter.hitByPitch = 1;
    }
}

// .text:0x000703EC size:0x294 mapped:0x806AF480
void fn_3_703EC(void) {
    return;
}

// .text:0x00070680 size:0x38 mapped:0x806AF714



/**
 * @address 00070680
 */
s32 fn_3_70680(f32 value) {
    /* * Target: lfs f0, 0x7c(r3) -> g_Pitcher.strikeZoneLeft
     * fcmpo cr0, f1, f0 -> value vs left
     * cror eq, gt, eq   -> implements >=
     * bne .L_FAIL       -> if !(value >= left) return 0
     */
    if (value >= g_Pitcher.strikeZoneLeft) {
        /* * Target: lfs f0, 0x80(r3) -> g_Pitcher.strikeZoneRight
         * fcmpo cr0, f1, f0 -> value vs right
         * cror eq, lt, eq   -> implements <=
         * bne .L_FAIL       -> if !(value <= right) return 0
         */
        if (value <= g_Pitcher.strikeZoneRight) {
            /* li r3, 1 -> blr */
            return 1;
        }
    }
    
    /* .L_FAIL: li r3, 0 -> blr */
    return 0;
}

// .text:0x000706B8 size:0xB0 mapped:0x806AF74C
void fn_3_706B8(s32 idx) {
    f32 t;
    f32 x;
    BOOL inZone;

    if (g_Minigame.GameMode_MiniGame == 2) {
        return;
    }
    t = (g_Pitcher.strikeCheckZ[idx] - g_Pitcher.ballCurrentPosition.z) / (g_Pitcher.ballLastPosition.z - g_Pitcher.ballCurrentPosition.z);
    x = t * (g_Pitcher.ballLastPosition.x - g_Pitcher.ballCurrentPosition.x) + g_Pitcher.ballCurrentPosition.x;
    g_Pitcher.estimatedEndingPos.x = x;
    g_Pitcher.estimatedEndingPos.z = t * (g_Pitcher.ballLastPosition.y - g_Pitcher.ballCurrentPosition.y) + g_Pitcher.ballCurrentPosition.y;
    if (x >= g_Pitcher.strikeZoneLeft && x <= g_Pitcher.strikeZoneRight) {
        inZone = TRUE;
    } else {
        inZone = FALSE;
    }
    if (inZone) {
        g_Pitcher.calledStrikeInd = 1;
        g_Pitcher.strikeInd = 1;
    }
}

// .text:0x00070768 size:0xD0 mapped:0x806AF7FC
s32 fn_3_70768(f32* outX, BOOL curve, f32 targetZ) {
    f32 z = g_Pitcher.ballCurrentPosition.z;
    f32 x = g_Pitcher.ballCurrentPosition.x;
    f32 vx = g_Pitcher.ballVelocity.x;
    f32 vy = g_Pitcher.ballVelocity.y;
    f32 vz = g_Pitcher.ballVelocity.z;
    f32 curveV = g_Pitcher.pitchCurveVeloV1;
    f32 prevX;
    f32 prevZ;
    f32 airStart;
    f32 adj;
    f32 decel;
    f32 newVz;
    f32 dx;
    f32 dz;
    f32 t;
    s32 frames = 0;

    if (z < targetZ) {
        return 0;
    }
    airStart = g_Pitcher.pitchZ_whenAirResistanceStarts;
    adj = g_Pitcher.airResistance_veloAdj;
    decel = g_Pitcher.decelerationFactor;
    do {
        prevX = x;
        prevZ = z;
        frames++;
        if (z <= airStart) {
            newVz = vz - vz * adj;
            if (newVz < -0.05f) {
                vz = newVz;
                vx = vx - vx * adj;
                vy = vy - vy * adj;
            }
        }
        vx *= decel;
        vz *= decel;
        vy *= decel;
        x += vx;
        z += vz;
        if (curve) {
            x += curveV;
        }
    } while (!(z < targetZ));
    dz = z;
    dz -= prevZ;
    t = 1.0f - (z - targetZ) / dz;
    dx = (x - prevX) * t;
    *outX = prevX + dx;
    return frames;
}

// .text:0x00070838 size:0x17C mapped:0x806AF8CC
void fn_3_70838(void) {
    return;
}

// .text:0x000709B4 size:0x138 mapped:0x806AFA48
void fn_3_709B4(void) {
    return;
}

// .text:0x00070AEC size:0xA8 mapped:0x806AFB80
void fn_3_70AEC(void) {
    f32 t;

    if (g_Pitcher.cancelParabolicAdjustmentInd != 0) {
        g_Pitcher.pitchX_parabolicAdjustment = 0.0f;
        return;
    }
    t = (f32)g_Ball.pitchHangtimeCounter - (f32)g_Pitcher.frameWhenUnhittable * lbl_3_rodata_1250;
    g_Pitcher.pitchX_parabolicAdjustment = g_Pitcher.horizontalOffsetParabolaMidpoint - (t * (g_Pitcher.horizontalGlobalParabolicVelo * t)) / 10000.0f;
}

// .text:0x00070B94 size:0x360 mapped:0x806AFC28
void fn_3_70B94(void) {
    return;
}

// .text:0x00070EF4 size:0x354 mapped:0x806AFF88
void fn_3_70EF4(void) {
    return;
}

// .text:0x00071248 size:0x1520 mapped:0x806B02DC
void fn_3_71248(void) {
    return;
}

// .text:0x00072768 size:0x540 mapped:0x806B17FC
void fn_3_72768(void) {
    return;
}

// .text:0x00072CA8 size:0x464 mapped:0x806B1D3C
void fn_3_72CA8(void) {
    return;
}

// .text:0x0007310C size:0x49C mapped:0x806B21A0
void fn_3_7310C(void) {
    return;
}

// .text:0x000735A8 size:0x124 mapped:0x806B263C
void fn_3_735A8(void) {
    s32 i;
    s32 found = 0;

    if (g_Pitcher.strikeOutOrWalk == 3) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (found == 0) {
                    r->currentBase = i;
                    fn_3_89864(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                found = 1;
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 5) {
                break;
            }
            if (i == r->currentBase) {
                fn_3_89864(i, 1);
            }
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x000736CC size:0x4C mapped:0x806B2760

void fn_3_736CC(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.unk_18[i] == -1) {
            g_Strikes.unk_18[i] = 0;
            return;
        }
    }
}

// .text:0x00073718 size:0x14 mapped:0x806B27AC
void fn_3_73718(void) {
    g_Ball.postPitchResultCounter = -1;
}

// .text:0x0007372C size:0x124 mapped:0x806B27C0
void fn_3_7372C(void) {
    s32 i;
    s32 found = 0;

    if (g_Pitcher.strikeOutOrWalk == 3) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (found == 0) {
                    r->currentBase = i;
                    fn_3_89864(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                found = 1;
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 5) {
                break;
            }
            if (i == r->currentBase) {
                fn_3_89864(i, 1);
            }
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x00073850 size:0x58 mapped:0x806B28E4
void fn_3_73850(void) {
    s32 i;

    g_Strikes.outs++;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.unk_18[i] == -1) {
            g_Strikes.unk_18[i] = 0;
            return;
        }
    }
}

// .text:0x000738A8 size:0x540 mapped:0x806B293C
void fn_3_738A8(void) {
    return;
}

// .text:0x00073DE8 size:0x144 mapped:0x806B2E7C
void fn_3_73DE8(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Ball.postPitchResultCounter < 0x7FFE) {
        g_Ball.postPitchResultCounter++;
    } else {
        g_Ball.postPitchResultCounter = 0x7FFF;
    }
    if (g_d_GameSettings.GameModeSelected == 7 &&
        (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 2 || g_Minigame.GameMode_MiniGame == 3)) {
        g_Pitcher.miniGameRelated = 1;
        if (g_Minigame.GameMode_MiniGame == 1) {
            fn_3_155288();
        }
    } else if (g_Pitcher.miniGameRelated == 0) {
        fn_3_703EC();
        return;
    }
    if (fn_3_6F4E8() == 0) {
        if ((g_d_GameSettings.GameModeSelected != 2 || g_Practice.guidedPracticeCompletionRelated == 0) &&
            g_Pitcher.currentStateFrameCounter > 0x4B) {
            g_GameLogic.playBatterWalkupAnimation = 0;
            fn_3_5A6D4(0);
        }
        fn_3_7CE90();
    }
}

// .text:0x00073F2C size:0x80 mapped:0x806B2FC0
void fn_3_73F2C(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }

    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter++;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }

    g_Pitcher.warioWaluStarAnimationStage = 0;
    fn_3_71248();
}

// .text:0x00073FAC size:0x124 mapped:0x806B3040
void fn_3_73FAC(void) {
    g_Pitcher.eggBallBounceYHeight = g_Batter.batPosition2.y;
    g_Pitcher.pitchStartingPosition_AIMaxCurve = LinearInterpolateToNewRange(g_Pitcher.pitcher.x, lbl_3_data_4474[0], lbl_3_data_4474[1], lbl_3_data_5EB0[0], lbl_3_data_5EB0[1]);
    if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = 0.0f;
    } else if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 10) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-lbl_3_data_5F5C[3], lbl_3_data_5F5C[3]);
        g_Pitcher.eggBallBounceYHeight = lbl_3_data_5F5C[0];
        g_Pitcher.frontOfPlateZ = RandomF32_Game_Range(lbl_3_data_5F5C[1], lbl_3_data_5F5C[2]);
    }
    if (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 3) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-lbl_3_data_2138C[g_Minigame.soloMinigameDifficulty], lbl_3_data_2138C[g_Minigame.soloMinigameDifficulty]);
    }
}

// .text:0x000740D0 size:0x58 mapped:0x806B3164
void fn_3_740D0(void) {
    g_Pitcher.nonCaptainStarPitchTriggeredType = g_Pitcher.nonCaptainStarPitch;
    switch (g_Pitcher.nonCaptainStarPitch) {
        case 1:
            g_Pitcher.specialPitchTypeCode = 0x10;
            break;
        case 2:
            g_Pitcher.specialPitchTypeCode = 0x11;
            break;
        case 3:
            g_Pitcher.specialPitchTypeCode = 0x12;
            break;
    }
}

// .text:0x00074128 size:0x99C mapped:0x806B31BC
void fn_3_74128(void) {
    return;
}

// .text:0x00074AC4 size:0x248 mapped:0x806B3B58
void fn_3_74AC4(void) {
    InputStruct* in = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    f32 delta = 0.0f;

    if (ACTIVE_TUTORIAL) {
        in = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (fn_3_107DB4(g_Minigame.players.characterIndex[g_Minigame.minigamePlayerSelectedOrder])) {
        in = &g_Minigame._1D7C[g_Minigame.players.characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
    } else if (g_d_GameSettings.minigamesEnabled) {
        in = &g_Controls[g_Minigame.players.characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
    }
    if (in->buttonInput & 0x40) {
        g_Pitcher.pitcherOffCenter = 1;
    }
    if (g_Pitcher.pitcherOffCenter) {
        if (g_Pitcher.pitcher.x >= -lbl_3_data_4474[3] && g_Pitcher.pitcher.x <= lbl_3_data_4474[3]) {
            g_Pitcher.pitcherOffCenter = 0;
            g_Pitcher.pitcher.x = 0.0f;
        } else if (g_Pitcher.pitcher.x < 0.0f) {
            g_Pitcher.pitcher.x += lbl_3_data_4474[3];
        } else {
            g_Pitcher.pitcher.x -= lbl_3_data_4474[3];
        }
    } else {
        if (in->buttonInput & 1) {
            delta = -lbl_3_data_4474[2];
        } else if (in->buttonInput & 2) {
            delta = lbl_3_data_4474[2];
        }
        g_Pitcher.pitcher.x += delta;
        if (g_Pitcher.pitcher.x < lbl_3_data_4474[0]) {
            g_Pitcher.pitcher.x = lbl_3_data_4474[0];
        }
        if (g_Pitcher.pitcher.x > lbl_3_data_4474[1]) {
            g_Pitcher.pitcher.x = lbl_3_data_4474[1];
        }
    }
}

// .text:0x00074D0C size:0x384 mapped:0x806B3DA0
void fn_3_74D0C(void) {
    return;
}

// .text:0x00075090 size:0x34 mapped:0x806B4124


void fn_3_75090(void) {

    g_Pitcher.pitcherActionState = 1;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
}

// .text:0x000750C4 size:0x18 mapped:0x806B4158
void fn_3_750C4(s8 value) {
    g_Pitcher.pitcherActionState = value;
    g_Pitcher.currentStateFrameCounter = 0;
}

// .text:0x000750DC size:0xD8 mapped:0x806B4170
typedef struct {
    u8 highLevelSimulationFlag;
    u8 _1;
} HighLevelSimulation_1200;
extern HighLevelSimulation_1200 lbl_803CBC3C;
BOOL fn_8001C920(s16 charID);

BOOL fn_3_750DC(void) {
    s16 charID = inMemRoster[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]].stats.CharID;

    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceType_2 != 4) {
        charID = g_Pitcher.charID;
    }
    if (lbl_3_common_bss_32724.unk9C == 0) {
        lbl_803CBC3C._1 = 0;
        lbl_3_common_bss_32724.unk9C = 1;
    }
    if (lbl_3_common_bss_32724.unk9C == 1 && fn_8001C920(charID)) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000751B4 size:0x234 mapped:0x806B4248
void fn_3_751B4(void) {
    return;
}

// .text:0x000753E8 size:0x4C mapped:0x806B447C

void fn_3_753E8(s32 param_1) {
    // 0x000753EC: cmpwi r3, 0x0
    // The incoming r3 (param_1) is compared to 0.
    
    // 0x000753F8: stb r0, 0x13e(r3)
    g_Pitcher.pitcherActionState = 0;
    
    // 0x000753FC: sth r0, 0x120(r3)
    g_Pitcher.currentStateFrameCounter = 0;

    // 0x00075400: bne .L_0007540C
    // If param_1 != 0, skip these two assignments.
    if (param_1 == 0) {
        // 0x00075404: stb r0, 0x159(r3)
        g_Pitcher.nPitchesThisAB = 0;
        // 0x00075408: stb r0, 0x15a(r3)
        g_Pitcher.nPickoffAttempts = 0;
    }

    // 0x00075410: lfsu f1, lbl_3_data_446C@l(r4)
    // 0x0007541C: lfs f0, 0x4(r4)
    // 0x00075424: stfs f1, 0x8c(r3)
    // 0x00075428: stfs f0, 0x90(r3)
    g_Pitcher.pitcher.x = lbl_3_data_446C.x;
    g_Pitcher.pitcher.z = lbl_3_data_446C.z;

    // 0x0007542C: stb r0, 0x15e(r3)
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
}

// .text:0x00075434 size:0x84 mapped:0x806B44C8
void fn_3_75434(void) {
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.nPitchesThisAB = 0;
    g_Pitcher.nPickoffAttempts = 0;
    g_Pitcher.pitcher.x = lbl_3_data_446C.x;
    g_Pitcher.pitcher.z = lbl_3_data_446C.z;
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
    if (g_Scores.highscore == 1) {
        g_Pitcher.playStartOfGameAnimation = 1;
    }
}

extern f32 lbl_3_data_5E98[6];
extern f32 lbl_3_data_5F90[12];
// .text:0x000754B8 size:0xA8 mapped:0x806B454C
void fn_3_754B8(void) {
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.pitchSpeedScaler = lbl_3_data_5F90[0];
    g_Pitcher.decelerationFactor = lbl_3_data_5F90[1];
    g_Pitcher.centerOfStrikeZone.x = 0.5f * (lbl_3_data_5E98[0] + lbl_3_data_5E98[1]);
    g_Pitcher.centerOfStrikeZone.z = 0.5f * (lbl_3_data_5E98[2] + lbl_3_data_5E98[3]);
    g_Pitcher.strikeZoneLeft = lbl_3_data_5E98[0];
    g_Pitcher.strikeZoneRight = lbl_3_data_5E98[1];
    g_Pitcher.beginningOfStrikeCheckZ = lbl_3_data_5E98[2];
    g_Pitcher.endingOfStrikeCheckZ = lbl_3_data_5E98[3];
    g_Pitcher.pitcher.x = lbl_3_data_446C.x;
    g_Pitcher.pitcher.z = lbl_3_data_446C.z;
    g_Pitcher.windupCountdownUntilBallReleased = 100;
    g_Pitcher.pitchWindUpCountDown = 100;
    g_Pitcher.curvePitchWindupFrames = 100;
    g_Pitcher.playStartOfGameAnimation = 1;
}

// .text:0x00075560 size:0x45C mapped:0x806B45F4
void fn_3_75560(void) {
    return;
}
