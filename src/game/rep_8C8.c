#include "game/rep_8C8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#include "game/gap_9CD90.h"
#include "game/gap_AC9F8.h"

extern u8 lbl_3_data_1AAC[4];
extern u8 lbl_3_data_1AB0[4][3];
extern f32 lbl_3_data_19DC[5][2];
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
    return;
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
    return;
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
