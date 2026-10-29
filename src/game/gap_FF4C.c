#include "game/gap_FF4C.h"
#include "game/rep_540.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0000FF4C size:0x4C mapped:0x8064EFE0
static inline u32 lcgStep(u32 x, int shift) {
    return ((x * 8) + ((s32)x >> shift) + (x & 0x505)) & 0x7FFF;
}

void fn_3_FF4C(void) {
    g_Ball.StaticRandomInt1 = lcgStep(g_Ball.StaticRandomInt1, 1);
    g_Ball.StaticRandomInt2 = lcgStep(g_Ball.StaticRandomInt2, 2);
}

// .text:0x0000FF98 size:0x98 mapped:0x8064F02C
void fn_3_FF98(void) {
    return;
}

// .text:0x00010030 size:0x11C mapped:0x8064F0C4
void fn_3_10030(void) {
    return;
}

// .text:0x0001014C size:0x17C mapped:0x8064F1E0
// Advance ball-event timers in frames and update ball motion when play permits it.
void ballPhysica(void) {
    if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames != 0) {
        if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.ballOverWallFrames++;
        } else {
            g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 0x7FFF;
        }
    }
    if (g_FieldingLogic._107 != 0) {
        if (g_Ball.framesSincePickOff < 0x7FFE) {
            g_Ball.framesSincePickOff++;
        } else {
            g_Ball.framesSincePickOff = 0x7FFF;
        }
    }
    if (g_Ball.AtBat_ContactResult == -1) {
        if (g_Ball.matchFramesAndBallAngle.framesSinceFoulCalled < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.framesSinceFoulCalled++;
        } else {
            g_Ball.matchFramesAndBallAngle.framesSinceFoulCalled = 0x7FFF;
        }
    }
    if (g_Ball.framesSinceBallHitWall != 0) {
        if (g_Ball.framesSinceBallHitWall < 0x7FFE) {
            g_Ball.framesSinceBallHitWall++;
        } else {
            g_Ball.framesSinceBallHitWall = 0x7FFF;
        }
    }
    if (g_Ball.pauseBallMovementWhenInPlant == 0 && g_Ball.frameCountdownAfterLeavingPlant != 0) {
        g_Ball.frameCountdownAfterLeavingPlant--;
    }
    if ((g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD || g_Minigame.TF_ballDespawnedInd == 0) &&
        g_Ball.groundRuleDoubleInd == 0) {
        if (g_Ball.ballState == 1) {
            fn_3_C9F4();
        } else if (g_Ball.framesSinceHit >= 0) {
            fn_3_A970(0);
        }
    }
    fn_3_E2D4();
}
