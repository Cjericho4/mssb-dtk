#include "game/rep_1188.h"
#include "header_rep_data.h"

#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern f32 lbl_3_data_4BC4[10];
extern f32 lbl_3_data_4BEC[22];
extern s16 lbl_3_data_4C54[12];
extern f32 lbl_3_rodata_11D8;
extern f32 lbl_3_rodata_11DC;
extern f32 lbl_3_rodata_11E0;

// .text:0x0006D6D4 size:0x290 mapped:0x806AC768
void fn_3_6D6D4(s32 runnerIndex) {
    InMemRunnerType* runner = &g_Runners[runnerIndex];
    u32 bucket = runner->speed / 10;
    s32 lower = bucket * 10;
    s32 upper = lower + 10;

    runner->maximumBaseVelocity = LinearInterpolateToNewRange(
        (f32)runner->speed, (f32)lower, (f32)upper,
        lbl_3_data_4BEC[(s32)(bucket * 10) / 10], lbl_3_data_4BEC[upper / 10]);
    runner->baseAcceleration = LinearInterpolateToNewRange(
        (f32)runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
        lbl_3_data_4BC4[0], lbl_3_data_4BC4[1]);
    runner->baseAccelerationWhileChaingingDirection = LinearInterpolateToNewRange(
        (f32)runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
        lbl_3_data_4BC4[2], lbl_3_data_4BC4[3]);
    runner->maxMashVeloAdjustment = LinearInterpolateToNewRange(
        (f32)runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
        lbl_3_data_4BC4[4], lbl_3_data_4BC4[5]);
    runner->percentAddedPerMash = lbl_3_rodata_11E0 / LinearInterpolateToNewRange(
        (f32)runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
        lbl_3_data_4BC4[6], lbl_3_data_4BC4[7]);
    runner->stamina_MashPercentTakenAwayPerFrame = lbl_3_rodata_11E0 /
        LinearInterpolateToNewRange((f32)runner->speed, lbl_3_rodata_11D8, lbl_3_rodata_11DC,
                                    lbl_3_data_4BC4[8], lbl_3_data_4BC4[9]);
    runner->FramesUntilNotSprinting = (u8)lbl_3_data_4C54[7];
}

// .text:0x0006D964 size:0x4FC mapped:0x806AC9F8
void fn_3_6D964(s32 rosterIdx, s32 runnerIdx) {
    return;
}

// .text:0x0006DE60 size:0x374 mapped:0x806ACEF4
void setInMemBatterConstants(int rosterID) {
    int battingOrderCounter;
    int index;
    int batterID;

    CharacterStats* char_stats = &inMemRoster[g_GameLogic.teamBatting][rosterID];
    ChallengeTrackingStruct* starMissions = starMissionCompletionTracker.missions;
    g_Batter.easyBatting = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2 ||
            g_Practice.practiceType_2 == 3) {
            char_stats = inMemRoster[g_GameLogic.teamBatting];
        }
    } else if (g_d_GameSettings.minigamesEnabled) {
        rosterID = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
        char_stats = &inMemRoster[0][rosterID];
    } else {
        g_Batter.easyBatting =
            gameInitOptions.controlOptions[g_d_GameSettings.PlayerPorts[g_GameLogic.teamBatting] % 4].easyBatting;
    }

    g_Batter.rosterID = rosterID;
    g_Batter.charID = char_stats->stats.CharID;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapContactSize;
    g_Batter.contactSize_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeContactSize;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_SLAP] = char_stats->stats.SlapHitPower;
    g_Batter.hitPower_raw[BAT_CONTACT_TYPE_CHARGE] = char_stats->stats.ChargeHitPower;
    g_Batter.buntingContactSize = char_stats->stats.BuntingContactSize;
    g_Batter.trajectoryPushPull = char_stats->stats.HitTrajectoryPushPull;
    g_Batter.trajectoryHighLow = char_stats->stats.HitTrajectoryHighLow;
    g_Batter.batterHand = char_stats->stats.BattingStance;
    g_Batter.characterClass = char_stats->stats.CharacterClass;
    g_Batter.trimmedBat = BatterHitbox[g_Batter.charID].TrimmedBat;
    g_Batter.chemLinksOnBase = 0;
    g_Batter.aiLevel = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];

    if (g_d_GameSettings.minigamesEnabled) {
        g_Batter.captainStarHitPitch = 0;
        g_Batter.noncaptainStarSwing = 0;
    } else {
        g_Batter.captainStarHitPitch = (char_stats->stats).CaptainStarHitPitch;
        g_Batter.noncaptainStarSwing = (char_stats->stats).NonCaptainStarSwing;
    }

    if (!g_d_GameSettings.exhibitionMatchInd) {
        g_Batter.charIDForScoutFlagMission = -1;
        for (index = 0; index < 54; index++) {
            if ((g_Batter.charID == index) && (starMissions[index].variantClassification <= 3)) {
                g_Batter.charIDForScoutFlagMission = index;
                break;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 bVar1;
        // This should match target's struct access pattern
        if (g_Minigame.battingHandedness[rosterID] & 1) {
            g_Batter.batterHand = 1;
        } else {
            g_Batter.batterHand = 0;
        }

        bVar1 = g_Minigame.minigameControlStruct[0].characterIndex[rosterID];

        if (g_Minigame.minigameControlStruct[0].battingHandedness[bVar1] != 0) {
            g_Pitcher.aiLevel = aILevel[g_Minigame.minigameControlStruct[0].aIStrength[bVar1]];
        }
    }
}

extern u8 lbl_3_data_4744[24];

// .text:0x0006E1D4 size:0x78 mapped:0x806AD268
u8 fn_3_6E1D4(u8 arg0) {
    s32 val = arg0;
    s32 minVal = (val / 10) * 10;
    s32 maxVal = minVal + 10;
    return LERPToNewRange_Float(val, minVal, maxVal, lbl_3_data_4744[minVal / 10], lbl_3_data_4744[maxVal / 10]);
}

// .text:0x0006E24C size:0x968 mapped:0x806AD2E0
void setFielderValues(s32 rosterID, s32 fielderIndex) {
    return;
}

// .text:0x0006EBB4 size:0x368 mapped:0x806ADC48
void fn_3_6EBB4(s32 arg0) {
    return;
}

// .text:0x0006EF1C size:0x5CC mapped:0x806ADFB0
void fn_3_6EF1C(void) {
    return;
}
