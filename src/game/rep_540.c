#include "game/rep_540.h"
#include "stl/math.h"
#include "game/gap_9CD90.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include <math.h>
#include "game/rep_1CB8.h"
#include "game/rep_13B8.h"
#include "game/gap_5985C.h"


extern f32 lbl_3_rodata_590;
extern f32 lbl_3_rodata_59C;
extern f32 lbl_3_rodata_5F8;
extern f64 lbl_3_rodata_600;

// .text:0x00006530 size:0x78 mapped:0x806455C4
void fn_3_6530(void) {
    g_Ball.someCollisionInd = 1;

    if (g_Ball.ballState == 2) {
        g_Ball.ballState = 1;
    }

    g_Ball.someCollisionInd = 1;
    g_Ball.currentStarSwing = 0;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_590;
    fn_3_27648();
}

// .text:0x000065A8 size:0x20 mapped:0x8064563C
void fn_3_65A8(void) {
    if (g_Ball.ballState == 2) {
        g_Ball.ballState = 1;
    }
}



// .text:0x000065C8 size:0x2C mapped:0x8064565C
void fn_3_65C8(void) {
    if (g_Ball.matchFramesAndBallAngle.framesInsidePlant < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant++;
    } else {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0x7FFF;
    }
}

// .text:0x000065F4 size:0x2C mapped:0x80645688
void fn_3_65F4(void) {
    // Ordering is critical to match the interleaving of r5 and r3 stores
    g_Ball.pauseBallMovementWhenInPlant = 0;
    g_FieldingLogic.unk_13B = 1;
    g_Ball.frameCountdownAfterLeavingPlant = 3;
}

// .text:0x00006620 size:0x74 mapped:0x806456B4
void fn_3_6620(void) {
    if (g_Ball.pauseBallMovementWhenInPlant == 0) {
        g_Ball.pauseBallMovementWhenInPlant = 1;
        g_Ball.ballCughtByPlantInd = 1;
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0;
        g_Ball.someCollisionVariable = 0;
        g_Ball.currentStarSwing = 0;
        g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
        g_Ball.someCollisionInd = 1;
        g_Ball.warioWaluGarlicIsActive = 0;
        g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
        g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_590;
        g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_590;
        g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_590;
        fn_3_27648();
    }
}

// .text:0x00006694 size:0x5A4 mapped:0x80645728
void fn_3_6694(void) {
    return;
}

// .text:0x00006C38 size:0x20B8 mapped:0x80645CCC
void fn_3_6C38(void) {
    return;
}

// .text:0x00008CF0 size:0x35C mapped:0x80647D84
void fn_3_8CF0(void) {
    return;
}

extern const f32 lbl_3_rodata_5B0;

// .text:0x0000904C size:0x214 mapped:0x806480E0
void fn_3_904C(void) {
    f32 scaledX = lbl_3_rodata_5B0;
    scaledX *= g_Ball.physicsSubstruct.velocity.x;
    g_Ball.physicsSubstruct.velocity.x = scaledX;
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_5B0 * g_Ball.physicsSubstruct.velocity.y;
    g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_5B0 * g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.deadBallReason == 1) {
        g_Ball.homeRunInd = 1;
        return;
    }
    if (g_Ball.AtBat_ContactResult != -1) {
        if (g_Ball.AtBat_ContactResult == 0 || g_Ball.deadBallReason == 1 ||
            (g_Ball.numberOfThrowsDuringPlay == 0 &&
             g_Ball.numFieldersWhoHandledBallDuringPlay != 0 &&
             g_Ball.framesOnGroundUntilPickedUp == 0)) {
            if (g_Ball.deadBallReason == 0) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 1;
                g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
                g_Ball.AtBat_ContactResult = 1;
                g_Ball.ballInitialHitDoneInd = 1;
                if (g_d_GameSettings.GameModeSelected != 6) {
                    fn_3_59918(0xF, 0);
                }
            }
            g_Ball.homeRunInd = 1;
            return;
        }
        if (g_Ball.deadBallReason == 0) {
            if (g_FieldingLogic._107 != 0) {
                if (g_Ball.deadBallReason != 4) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 4;
                    if (g_RunningLogic.unk0 != 0) {
                        fn_3_59918(0x14, 0);
                    }
                }
            } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 &&
                       g_Ball.numberOfThrowsDuringPlay != 0) {
                if (g_Ball.deadBallReason != 4) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 4;
                    if (g_RunningLogic.unk0 != 0) {
                        fn_3_59918(0x14, 0);
                    }
                }
            } else {
                g_Ball.deadBallReason = 3;
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                fn_3_59918(7, 0);
            }
        }
    }
}

// .text:0x00009260 size:0x2A8 mapped:0x806482F4
void fn_3_9260(void) {
    return;
}

// .text:0x00009508 size:0x300 mapped:0x8064859C
void fn_3_9508(void) {
    return;
}

// .text:0x00009808 size:0x36C mapped:0x8064889C
void fn_3_9808(void) {
    return;
}

extern f32 lbl_3_rodata_5E4;
extern f32 lbl_3_rodata_5F0;
extern f32 lbl_3_rodata_5F4;

// .text:0x00009B74 size:0x16C mapped:0x80648C08
void fn_3_9B74(void) {
    f32 temp_f1;
    f32 var_f1;
    f32 var_f2;

    if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x > 0.0f) {
        var_f1 = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    } else {
        var_f1 = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    }
    if (var_f1 < -20.0f) {
        g_Ball.howFoulTheBallWillBe = 3;
    } else if (var_f1 < lbl_3_rodata_5F0) {
        g_Ball.howFoulTheBallWillBe = 2;
    } else if (var_f1 < lbl_3_rodata_5E4) {
        g_Ball.howFoulTheBallWillBe = 1;
    } else {
        g_Ball.howFoulTheBallWillBe = 0;
    }
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_5F4) {
        var_f2 = g_Ball.ballWillHitBallPos.x;
        if (var_f2 < 0.0f) {
            var_f2 = -var_f2;
        }
        temp_f1 = g_Ball.ballWillHitBallPos.z - var_f2;
        if (temp_f1 < -20.0f) {
            g_Ball.howFoulTheBallWillBe = 3;
        } else if (temp_f1 < lbl_3_rodata_5F0) {
            g_Ball.howFoulTheBallWillBe = 2;
        } else if (temp_f1 < lbl_3_rodata_5E4) {
            g_Ball.howFoulTheBallWillBe = 1;
        } else {
            g_Ball.howFoulTheBallWillBe = 0;
        }
    }
    if ((u8) g_Ball.deadBallReason == 1) {
        g_Ball.howFoulTheBallWillBe = 0;
    }
}

// .text:0x00009CE0 size:0x138 mapped:0x80648D74
f32 fn_3_9CE0(f32 x, f32 z) {
    f32 dx;
    f32 dz;
    f32 projection;
    f32 distanceSquared;
    dz = z - g_Ball.AtBat_Contact_BallPos.z;
    dx = x - g_Ball.AtBat_Contact_BallPos.x;
    projection = g_Ball.ballVelocityPercent.x * dx + g_Ball.ballVelocityPercent.z * dz;
    distanceSquared = -(projection * projection - (dx * dx + dz * dz));
    if (distanceSquared < 0.0f) return 0.0f;
    return dolsqrtf2(distanceSquared);
}

// .text:0x00009E18 size:0x6C mapped:0x80648EAC
void fn_3_9E18(void) {
    if (g_Ball.deadBallReason != 4) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.deadBallReason = 4;
        if (g_RunningLogic.unk0 != 0) {
            fn_3_59918(0x14, 0);
        }
    }
}

// .text:0x00009E84 size:0x120 mapped:0x80648F18
void fn_3_9E84(void) {
    if (g_Ball.deadBallReason == 0) {
        if (g_FieldingLogic._107 != 0) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic.unk0 != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else if ((g_Ball.numFieldersWhoHandledBallDuringPlay != 0) && (g_Ball.numberOfThrowsDuringPlay != 0)) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic.unk0 != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else {
            g_Ball.deadBallReason = 3;
            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
            fn_3_59918(7, 0);
        }
    }
}

// .text:0x00009FA4 size:0x7C mapped:0x80649038
void fn_3_9FA4(void) {
    if (g_Ball.deadBallReason == 0) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;

        g_Ball.deadBallReason = 1;
        g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        g_Ball.AtBat_ContactResult = 1;
        g_Ball.ballInitialHitDoneInd = 1;

        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x0000A020 size:0xD0 mapped:0x806490B4
void fn_3_A020(void) {
    BOOL struckOut;

    if (g_Ball.deadBallReason != 0) {
        return;
    }
    g_Ball.deadBallReason = 2;
    struckOut = FALSE;
    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.AtBat_ContactResult = -1;
    g_Ball.ballInitialHitDoneInd = 1;
    if (g_FieldingLogic.unk110 == 1) {
        return;
    }
    g_FieldingLogic.unk110 = 1;
    if (++g_Strikes.strikes >= 3) {
        if (g_Ball.maybeBuntInd != 0) {
            g_Ball.maybebuntOn2Strikes = 1;
            fn_3_88D88(0);
            struckOut = TRUE;
        } else {
            g_Strikes.strikes = 2;
        }
    }
    if (!struckOut) {
        fn_3_59918(3, 0);
    }
}

// .text:0x0000A0F0 size:0xA8 mapped:0x80649184
void fn_3_A0F0(void) {
    BOOL handled = FALSE;

    g_Ball.AtBat_ContactResult = -1;
    g_Ball.ballInitialHitDoneInd = 1;
    if (g_FieldingLogic.unk110 == 1) {
        return;
    }
    g_FieldingLogic.unk110 = 1;
    if (++g_Strikes.strikes >= 3) {
        if (g_Ball.maybeBuntInd != 0) {
            g_Ball.maybebuntOn2Strikes = 1;
            fn_3_88D88(0);
            handled = TRUE;
        } else {
            g_Strikes.strikes = 2;
        }
    }
    if (!handled) {
        fn_3_59918(3, 0);
    }
}

// .text:0x0000A198 size:0x6A4 mapped:0x8064922C
void fn_3_A198(void) {
    return;
}

// .text:0x0000A83C size:0x134 mapped:0x806498D0
void fn_3_A83C(void) {
    s32 i;
    for (i = 59; i > 0; i--) {
        g_Ball.coordinateHistory[i].x = g_Ball.coordinateHistory[i - 1].x;
        g_Ball.coordinateHistory[i].y = g_Ball.coordinateHistory[i - 1].y;
        g_Ball.coordinateHistory[i].z = g_Ball.coordinateHistory[i - 1].z;
    }
    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.fielderActionOccuring != 0) {
        g_Ball.coordinateHistory[0].x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.coordinateHistory[0].y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.coordinateHistory[0].z = g_Ball.fielderActionCatchCoords.z;
    } else {
        g_Ball.coordinateHistory[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.coordinateHistory[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.coordinateHistory[0].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        for (i = 9; i > 0; i--) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.warioStarHitCoords[i + 2].x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.warioStarHitCoords[i + 2].y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.warioStarHitCoords[i + 2].z;
        }
        g_Ball.warioStarHitCoords[3].x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.warioStarHitCoords[3].y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.warioStarHitCoords[3].z = g_Ball.warioStarHitCoords[0].z;
    }
}

// .text:0x0000A970 size:0xAD0 mapped:0x80649A04
void fn_3_A970(void) {
    return;
}

// .text:0x0000B440 size:0x500 mapped:0x8064A4D4
void fn_3_B440(void) {
    return;
}

// .text:0x0000B940 size:0x27C mapped:0x8064A9D4
void fn_3_B940(void) {
    return;
}

// .text:0x0000BBBC size:0x98 mapped:0x8064AC50
s32 fn_3_BBBC(VecXYZ* out, s32 count, s32 step, f32 x, f32 z) {
    s32 i;
    s32 best = -1;
    f32 minDist = 100000000.0f;
    f32 dist;
    f32 dx;
    f32 dz;

    for (i = 0; i < count; i += step) {
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - z;
        dist = dx * dx + dz * dz;
        if (!(dist < minDist)) {
            break;
        }
        minDist = dist;
        best = i;
    }
    if (best < 0) {
        return -1;
    }
    out->x = g_Ball.physicsSubstruct.futureCoordsAndDist[best].pos.x;
    out->y = g_Ball.physicsSubstruct.futureCoordsAndDist[best].pos.y;
    out->z = g_Ball.physicsSubstruct.futureCoordsAndDist[best].pos.z;
    return best;
}

// .text:0x0000BC54 size:0x124 mapped:0x8064ACE8
void fn_3_BC54(void) {
    f32 var_f1;
    s32 temp_r0;
    s32 var_r7;

    if (fn_3_B7DD8(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) == 0) {
        if (g_Ball.AtBat_Contact_BallPos.x > 0.0f) {
            var_f1 = g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x;
        } else {
            var_f1 = g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x;
        }
        if ((var_f1 < -5.0f) || (g_Ball.ballVelocity < 0.05f)) {
            goto block_6;
        }
    } else {
block_6:
        g_Ball.AtBat_ContactResult = -1;
        var_r7 = 0;
        g_Ball.ballInitialHitDoneInd = 1;
        if ((u8) g_FieldingLogic.unk110 != 1) {
            g_FieldingLogic.unk110 = 1;
            temp_r0 = g_Strikes.strikes + 1;
            g_Strikes.strikes = temp_r0;
            if (temp_r0 >= 3) {
                if ((u8) g_Ball.maybeBuntInd != 0) {
                    g_Ball.maybebuntOn2Strikes = 1;
                    fn_3_88D88(0);
                    var_r7 = 1;
                } else {
                    g_Strikes.strikes = 2;
                }
            }
            if (var_r7 == 0) {
                fn_3_59918(3, 0);
            }
        }
    }
}

// .text:0x0000BD78 size:0x2BC mapped:0x8064AE0C
void fn_3_BD78(void) {
    return;
}

// .text:0x0000C034 size:0x9C0 mapped:0x8064B0C8
void fn_3_C034(void) {
    return;
}

// .text:0x0000C9F4 size:0x434 mapped:0x8064BA88
void fn_3_C9F4(void) {
    return;
}

// .text:0x0000CE28 size:0xBC4 mapped:0x8064BEBC
void estimateAndSetFutureCoords(int) {
    return;
}

extern f32 lbl_3_rodata_5A0;
extern f32 lbl_3_rodata_660;
extern f32 lbl_3_rodata_664;
extern f32 lbl_3_rodata_668;
extern f32 lbl_3_rodata_66C;

// .text:0x0000D9EC size:0x1E4 mapped:0x8064CA80
void fn_3_D9EC(void) {
    f32 speed = dolsqrtf2((g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x) + (g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z));
    f32 checkSpeed = (f32)(double)speed;
    g_Ball.ballVelocity = speed;
    g_Ball.ballStoppingCode1ReallySlow2Stopped = 0;
    if (lbl_3_rodata_590 != checkSpeed) {
        g_Ball.ballVelocityPercent.x = g_Ball.physicsSubstruct.velocity.x / checkSpeed;
        g_Ball.ballVelocityPercent.z = g_Ball.physicsSubstruct.velocity.z / checkSpeed;
    }
    if (g_Ball.ballVelocity <= lbl_3_rodata_660 &&
        g_Ball.AtBat_Contact_BallPos.y <= lbl_3_rodata_664 &&
        g_Ball.physicsSubstruct.velocity.y < lbl_3_rodata_668 &&
        g_Ball.physicsSubstruct.velocity.y > lbl_3_rodata_66C) {
        if (g_Ball.ballVelocity < lbl_3_rodata_5A0) {
            g_Ball.ballStoppingCode1ReallySlow2Stopped = 2;
            g_Ball.physicsSubstruct.velocity.x = 0.0f;
            g_Ball.physicsSubstruct.velocity.z = 0.0f;
            g_Ball.ballVelocity = 0.0f;
            return;
        }
        g_Ball.ballStoppingCode1ReallySlow2Stopped = 1;
    }
}

// .text:0x0000DBD0 size:0x78 mapped:0x8064CC64
void fn_3_DBD0(void) {
    f32 factor;

    factor = lbl_3_rodata_59C - ((f32)g_Ball.airResistance / lbl_3_rodata_5F8);
    g_Ball.physicsSubstruct.velocity.x *= factor;
    g_Ball.physicsSubstruct.velocity.y *= factor;
    g_Ball.physicsSubstruct.velocity.z *= factor;
}

// .text:0x0000DC48 size:0x68C mapped:0x8064CCDC
void fn_3_DC48(void) {
    return;
}

// .text:0x0000E2D4 size:0xB78 mapped:0x8064D368
void fn_3_E2D4(void) {
    return;
}

// .text:0x0000EE4C size:0x390 mapped:0x8064DEE0
void fn_3_EE4C(void) {
    return;
}

// .text:0x0000F1DC size:0x39C mapped:0x8064E270
void fn_3_F1DC(void) {
    return;
}

// .text:0x0000F578 size:0x240 mapped:0x8064E60C
void fn_3_F578(void) {
    return;
}

// .text:0x0000F7B8 size:0x240 mapped:0x8064E84C
void fn_3_F7B8(void) {
    return;
}

extern VecXZ lbl_3_data_450C;

// .text:0x0000F9F8 size:0x1B0 mapped:0x8064EA8C
void fn_3_F9F8(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C.x;
    g_Ball.AtBat_Contact_BallPos.y = lbl_3_rodata_590;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C.z;
    if (g_Minigame.GameMode_MiniGame == 6) {
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.AtBat_Contact_BallPos.y = lbl_3_rodata_59C;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.coordinateHistory[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.coordinateHistory[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.coordinateHistory[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    g_Ball.physicsSubstruct.velocity.x = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_590;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_590;
}

// .text:0x0000FBA8 size:0x3A4 mapped:0x8064EC3C
void fn_3_FBA8(void) {
    return;
}
