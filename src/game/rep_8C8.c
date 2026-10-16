#include "game/rep_8C8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#include "game/gap_9CD90.h"
#include "game/gap_AC9F8.h"

extern f32 lbl_3_data_19CC[4];
extern f32 lbl_3_data_4474[4];
extern u8 lbl_3_data_1AAC[4];
extern u8 lbl_3_data_1AB0[4][3];
extern f32 lbl_3_data_19DC[5][2];
extern f32 lbl_3_data_1A04[2];
extern u8 lbl_3_data_1A24[4];
extern u8 lbl_3_data_1A28[4][5];
extern u8 lbl_3_data_1A3C[4];
extern u8 lbl_3_data_1ABC[2][4][4];

// .text:0x0001E4B8 size:0x26C mapped:0x8065D54C
void fn_3_1E4B8(void) {
    return;
}

// .text:0x0001E724 size:0xD0 mapped:0x8065D7B8
BOOL fn_3_1E724(void) {
    if (g_GameLogic.secondaryGameMode == 13) {
        return fn_3_B0CF4() != 0;
    }
    if (g_AiLogic.batterAIBuntInd != 1) {
        return FALSE;
    }
    if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
        return FALSE;
    }
    if (g_Ball.pitchHangtimeCounter <= 0) {
        return TRUE;
    }
    if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && fn_3_1E7F4() == FALSE) {
        g_AiLogic.aISwingDecisionRelated_noSwingOverride = 1;
        return FALSE;
    }
    return TRUE;
}

// .text:0x0001E7F4 size:0x2B4 mapped:0x8065D888
BOOL fn_3_1E7F4(void) {
    return FALSE;
}

// .text:0x0001EAA8 size:0x53C mapped:0x8065DB3C
void fn_3_1EAA8(void) {
    return;
}

// .text:0x0001EFE4 size:0x1E8 mapped:0x8065E078
void fn_3_1EFE4(void) {
    return;
}

// .text:0x0001F1CC size:0x184 mapped:0x8065E260
void fn_3_1F1CC(void) {
    AIStruct* ai = &g_AiLogic;
    f32 offset;
    f32 x;

    if (ai->batterAIInd10_relatedToBoxPosPrePitch == 3) {
        ai->batterAIDesiredXPosInBox = ai->boxHorizontalPoint;
        return;
    }
    if (g_Batter.characterClass == 2) {
        if (ai->batterAIInd10_relatedToBoxPosPrePitch == 1) {
            return;
        }
        if (ai->batterAIInd10_relatedToBoxPosPrePitch == 2 && ai->_6B != 0) {
            ai->_6B--;
            return;
        }
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[0][0], lbl_3_data_19DC[4][1]);
        offset = RandomF32_Game_Range(lbl_3_data_1A04[1], lbl_3_data_1A04[0] + lbl_3_data_1A04[0]);
        if (RandomInt_Game(2) != 0) {
            g_AiLogic.batterAIDesiredXPosInBox += offset;
        } else {
            g_AiLogic.batterAIDesiredXPosInBox -= offset;
        }
        if (g_AiLogic.batterAIDesiredXPosInBox < -lbl_3_data_1A04[0]) {
            g_AiLogic.batterAIDesiredXPosInBox = -lbl_3_data_1A04[0];
        } else if (g_AiLogic.batterAIDesiredXPosInBox > lbl_3_data_1A04[0]) {
            g_AiLogic.batterAIDesiredXPosInBox = lbl_3_data_1A04[0];
        }
        ai->batterAIInd10_relatedToBoxPosPrePitch = 1;
        g_AiLogic._6B = RandomInt_Game(45) + 15;
    } else if (ai->batterAIInd10_relatedToBoxPosPrePitch == 0) {
        x = RandomF32_Game_Range(lbl_3_data_19DC[ai->batterAIInd9PrincessStarHit + 1][0], lbl_3_data_19DC[ai->batterAIInd9PrincessStarHit + 1][1]);
        ai->batterAIInd10_relatedToBoxPosPrePitch = 1;
        g_AiLogic.batterAIDesiredXPosInBox = x;
    }
}

// .text:0x0001F350 size:0x128 mapped:0x8065E3E4
void fn_3_1F350(void) {
    if (g_Pitcher.windupCountdownUntilBallReleased != lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
        return;
    }
    if (g_AiLogic.lastPitchBallLocZone != 0xFF &&
        RandomInt_Game(100) < lbl_3_data_1A24[g_Batter.characterClass]) {
        g_AiLogic.batterAI_GuessedPitchLocZone = g_AiLogic.lastPitchBallLocZone;
        if (g_AiLogic.batterAI_GuessedPitchLocZone == 0) {
            g_AiLogic.batterAI_GuessedPitchLocZone = 1;
        } else if (g_AiLogic.batterAI_GuessedPitchLocZone == 4) {
            g_AiLogic.batterAI_GuessedPitchLocZone = 3;
        }
    } else {
        g_AiLogic.batterAI_GuessedPitchLocZone = fn_3_9E5A0(lbl_3_data_1A28[g_Batter.characterClass], 5);
    }
    g_AiLogic.batterAIDesiredXPosInBox =
        RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone][0],
                             lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone][1]);
    g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
}

// .text:0x0001F478 size:0x520 mapped:0x8065E50C
void fn_3_1F478(void) {
    return;
}

// .text:0x0001F998 size:0x3F4 mapped:0x8065EA2C
void fn_3_1F998(void) {
    return;
}

// .text:0x0001FD8C size:0x1BC mapped:0x8065EE20
void batterAIControlled(void) {
    return;
}

// .text:0x0001FF48 size:0x11C mapped:0x8065EFDC
void fn_3_1FF48(void) {
    s32 zone;
    f32 step;
    f32 edge;

    if (g_Pitcher.starPitchType != 0) {
        return;
    }
    g_AiLogic.lastPitchFramesUntilPitchGetsToBatter = g_Pitcher.framesUntilPitchGetsToBatter;
    g_AiLogic.lastPitchType = g_Pitcher.TypeOfPitch;
    for (zone = 0; zone < 4; zone++) {
        if (g_Pitcher.pitchXPosition < lbl_3_data_19CC[zone]) {
            break;
        }
    }
    if (g_Batter.batterHand != 0) {
        zone = 4 - zone;
    }
    g_AiLogic.lastPitchBallLocZone = zone;
    step = (lbl_3_data_4474[1] - lbl_3_data_4474[0]) / 5.0f;
    edge = lbl_3_data_4474[0] + step;
    for (zone = 0; zone < 4; zone++) {
        if (g_Pitcher.pitcher.x < edge) {
            break;
        }
        edge += step;
    }
    g_AiLogic.lastPitchMoundZone = zone;
}

// .text:0x00020064 size:0x124 mapped:0x8065F0F8
void fn_3_20064(void) {
    u8 pitchType;

    g_AiLogic.batterAITrackBallPoorlyOffset = 0.0f;
    if (g_Pitcher.starPitchType != 0) {
        return;
    }
    pitchType = g_Pitcher.TypeOfPitch;
    if (pitchType == 0) {
        g_AiLogic.batterAISwingEarly1OrLate2 = 0;
    } else if (g_AiLogic.batterAIPitchGuessed != pitchType) {
        if (pitchType == 1) {
            if (RandomInt_Game(100) < lbl_3_data_1ABC[0][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAISwingEarly1OrLate2 = 0;
            } else {
                g_AiLogic.batterAISwingEarly1OrLate2 = 1;
            }
        } else {
            if (RandomInt_Game(100) < lbl_3_data_1ABC[1][g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAISwingEarly1OrLate2 = 0;
            } else {
                g_AiLogic.batterAISwingEarly1OrLate2 = 2;
            }
        }
    } else {
        g_AiLogic.batterAISwingEarly1OrLate2 = 0;
    }
}

// .text:0x00020188 size:0x9C mapped:0x8065F21C
void fn_3_20188(void) {
    if (g_AiLogic.lastPitchType != 0xFF &&
        RandomInt_Game(100) < lbl_3_data_1AAC[g_AiLogic.aIBatterDifficulty]) {
        g_AiLogic.batterAIPitchGuessed = g_AiLogic.lastPitchType;
    } else {
        g_AiLogic.batterAIPitchGuessed = fn_3_9E5A0(lbl_3_data_1AB0[g_Pitcher.charClass], 3);
    }
}

// .text:0x00020224 size:0x83C mapped:0x8065F2B8
void fn_3_20224(void) {
    return;
}

// .text:0x00020A60 size:0x50 mapped:0x8065FAF4
void fn_3_20A60(void) {
    g_AiLogic.boxHorizontalPoint = g_Batter.batPosition2.x;
    g_AiLogic.boxVerticalPoint = g_Batter.batPosition2.z;
    g_AiLogic.batterAIDesiredZPosInBox = maybeInitialBatPos.z;
    g_AiLogic.batterAIABStrat = -1;
    g_AiLogic._67 = 0;
    g_AiLogic.batterAIBuntPossibility = 1;
    g_AiLogic.batterAIBuntInd = 0;
}

// .text:0x00020AB0 size:0x30 mapped:0x8065FB44
void fn_3_20AB0(void) {
    g_AiLogic.lastPitchFramesUntilPitchGetsToBatter = 0;
    g_AiLogic.lastPitchType = 0xFF;
    g_AiLogic.starRelated[0] = 0;
    g_AiLogic.starRelated[1] = 0;
    g_AiLogic.lastPitchBallLocZone = 0xFF;
    g_AiLogic.lastPitchMoundZone = 0xFF;
    g_AiLogic.batterAIStealIndicator = 0;
}

// .text:0x00020AE0 size:0x50 mapped:0x8065FB74
void fn_3_20AE0(void) {
    f32 x = 0.0f;
    f32 z = maybeInitialBatPos.z;
    f32 a = 30.0f;
    f32 b = 40.0f;

    g_AiLogic.batterAIDesiredXPosInBox = x;
    g_AiLogic.batterAIDesiredZPosInBox = z;
    g_AiLogic._10 = a;
    g_AiLogic._14 = b;
    g_AiLogic._18 = a;
    g_AiLogic._1C = b;
    g_AiLogic.batterAIDesiredXPosInBox = x;
    g_AiLogic.batterAIDesiredZPosInBox = z;
}

// .text:0x00020B30 size:0x104 mapped:0x8065FBC4
s32 fn_3_20B30(void) {
    if (g_AiLogic.aIPitcherPickOffInd == 0) {
        return 0;
    }
    if (g_Pitcher.currentStateFrameCounter > g_AiLogic.AIFrameToBeginPitch - 10) {
        if (g_RunningLogic.basesOccupied == 0x1011) {
            if (RandomInt_Game(3) == 0) {
                g_Pitcher.pickOffLoc = 3;
            } else {
                g_Pitcher.pickOffLoc = 1;
            }
        } else if (g_RunningLogic.basesOccupied == 0x1101) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic.basesOccupied == 0x111) {
            g_Pitcher.pickOffLoc = 2;
        } else if (g_RunningLogic.basesOccupied == 0x1001) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic.basesOccupied == 0x101) {
            g_Pitcher.pickOffLoc = 2;
        } else {
            g_Pitcher.pickOffLoc = 1;
        }
        return 1;
    }
    return 0;
}

// .text:0x00020C34 size:0xB8 mapped:0x8065FCC8
extern u8 lbl_3_data_1924[4][4];

void fn_3_20C34(void) {
    s32 chance;
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        return;
    }
    g_AiLogic.aIPitcherPickOffInd = 0;
    if (g_RunningLogic.basesOccupied == 1 || g_RunningLogic.basesOccupied == 0x1111) {
        return;
    }
    if (g_AiLogic.always0_AIPickoffRelated != 0) {
        chance = 5;
    } else {
        chance = lbl_3_data_1924[g_Pitcher.charClass][g_AiLogic._49];
    }
    if (RandomInt_Game(100) < chance) {
        g_AiLogic.aIPitcherPickOffInd = 1;
    }
}

