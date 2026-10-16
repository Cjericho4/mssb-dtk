#include "game/rep_13B8.h"
#include "game/gap_1658F0.h"
#include "game/rep_AC8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/gap_9CD90.h"
#include "game/rep_140.h"
#include "game/rep_18E8.h"
#include "game/rep_1838.h"
#include "game/gap_5985C.h"
#include "game/gap_106DFC.h"

extern f32 lbl_3_rodata_1498;

// .text:0x0007D79C size:0x184 mapped:0x806BC830
void fn_3_7D79C(void) {
    return;
}

extern s16 lbl_3_data_21904[12];

// .text:0x0007D920 size:0xBC mapped:0x806BC9B4
void fn_3_7D920(s32 idx) {
    InMemRunnerType* runner = &g_Runners[idx];
    s8 slot = g_Minigame._18FC[idx];

    if (g_Minigame._1B15[slot] == 2) {
        if (g_Minigame._1B19 == 0) {
            g_Minigame._1B15[slot] = 3;
            runner->runningToDugoutFrameCounter = 0;
        }
        return;
    }
    if (runner->runningToDugoutFrameCounter < lbl_3_data_21904[1]) {
        runner->position.x += runner->velocity.x;
        runner->position.z += runner->velocity.z;
    } else {
        g_Minigame._1B15[slot] = 2;
    }
    if (runner->runningToDugoutFrameCounter < 0x7FFE) {
        runner->runningToDugoutFrameCounter++;
    } else {
        runner->runningToDugoutFrameCounter = 0x7FFF;
    }
}

// .text:0x0007D9DC size:0x154 mapped:0x806BCA70
void fn_3_7D9DC(void) {
    return;
}

// .text:0x0007DB30 size:0x1F4 mapped:0x806BCBC4
void fn_3_7DB30(s32 idx) {
    InMemRunnerType* runner;
    InputStruct* in;

    in = &g_Controls[g_Minigame._18FC[idx]];
    runner = &g_Runners[idx];

    if (fn_3_107DF8(g_Minigame._18FC[idx])) {
        in = &g_Minigame._1D7C[g_Minigame._18FC[idx]];
    }
    if (runner->runningDirectionCode == 3) {
        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 1) {
            if (in->newButtonInput & 0x400) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 3;
                }
            } else if (in->newButtonInput & 0x800) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 1;
                }
            }
        } else if (in->newButtonInput & 0x800) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 2;
            }
        }
    } else if (runner->runningDirectionCode == 1) {
        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 3) {
            if (in->newButtonInput & 0x400) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 3;
                }
            } else if (in->newButtonInput & 0x800) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 1;
                }
            }
        } else if (in->newButtonInput & 0x400) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 2;
            }
        }
    } else if (in->buttonInput & 0x800) {
        if (runner->rosterID >= 0) {
            runner->runningDirectionDesired = 1;
        }
    } else if (in->buttonInput & 0x400) {
        if (runner->rosterID >= 0) {
            runner->runningDirectionDesired = 3;
        }
    }
    if (in->newButtonInput & 0xF00) {
        runner->newButtonThisFrame_forMashPurposes = 1;
    }
}

// .text:0x0007DD24 size:0x48 mapped:0x806BCDB8

void fn_3_7DD24(s32 unk) {
    // The assembly uses lbz r0, 0x11e(r4) where r4 is &g_GameLogic
    // and then lbz r0, 0x190b(r4) where r4 is &g_Minigame
    
    if (g_GameLogic.gameStatus == 2) {
        if (g_Minigame.turnOverStatus == 0) {
            fn_3_7DB30(unk);
        }
    }
}

// .text:0x0007DD6C size:0x550 mapped:0x806BCE00
void fn_3_7DD6C(void) {
    return;
}

// .text:0x0007E2BC size:0x7AC mapped:0x806BD350
void fn_3_7E2BC(void) {
    return;
}

// .text:0x0007EA68 size:0x16C mapped:0x806BDAFC
void fn_3_7EA68(void) {
    return;
}

// .text:0x0007EBD4 size:0x128 mapped:0x806BDC68
void fn_3_7EBD4(s32 runnerIdx) {
    return;
}

// .text:0x0007ECFC size:0x5DC mapped:0x806BDD90
void fn_3_7ECFC(s32 runnerIdx) {
    return;
}

// .text:0x0007F2D8 size:0x1BC mapped:0x806BE36C
void fn_3_7F2D8(void) {
    return;
}

// .text:0x0007F494 size:0x530 mapped:0x806BE528
s32 fn_3_7F494(s32 runnerIdx) {
    return 0;
}

// .text:0x0007F9C4 size:0xB4 mapped:0x806BEA58
void fn_3_7F9C4(s32 runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->runningToDugoutInd != 0) {
        runner->baseRoundingState = 0;
        runner->actionCode = 0;
        return;
    }
    fn_3_7ECFC(runnerIdx);
    fn_3_7F494(runnerIdx);
    if (g_GameLogic.secondaryGameMode == 6) {
        return;
    }
    if (runnerIdx == 0 && runner->nextBase == 1) {
        fn_3_7F2D8();
    } else if (runner->baseRoundingState == 1) {
        runner->baseRoundingState = 0;
    }
    fn_3_7EBD4(runnerIdx);
}

// .text:0x0007FA78 size:0x318 mapped:0x806BEB0C
void fn_3_7FA78(void) {
    return;
}

// .text:0x0007FD90 size:0x118 mapped:0x806BEE24
void fn_3_7FD90(void) {
    return;
}

// .text:0x0007FEA8 size:0x2C mapped:0x806BEF3C
void fn_3_7FEA8(s32 runnerIdx, s32 direction) {
    // Defines the pointer here to steer the compiler to use mulli/add
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    // Signed comparison: if (rosterID < 0) return;
    if (runner->rosterID < 0) {
        return;
    }

    // if (direction == 0) return;
    if (direction == 0) {
        return;
    }

    runner->runningDirectionDesired = direction;
}

// .text:0x0007FED4 size:0xFC mapped:0x806BEF68
extern VecXZ lbl_3_data_4A54[2][13];

void fn_3_7FED4(VecXYZ* out, f32 dist, f32 t) {
    VecXZ res;
    s32 start;
    s32 count;

    if (dist < 1.0f) {
        start = 0;
        count = 4;
    } else if (dist < 2.0f) {
        start = 3;
        count = 4;
    } else if (dist < 3.0f) {
        start = 6;
        count = 4;
    } else if (g_GameLogic.secondaryGameMode == 6) {
        start = 9;
        count = 4;
    } else {
        start = 9;
        count = 3;
    }
    running_roundBasePosition(&res, &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == 6][start], count, t);
    out->x = res.x;
    out->z = res.z;
    out->y = 0.0f;
}

// .text:0x0007FFD0 size:0x58 mapped:0x806BF064
void fn_3_7FFD0(void) {
    return;
}

// .text:0x00080028 size:0x109C mapped:0x806BF0BC
void fn_3_80028(void) {
    return;
}

extern VecXZ lbl_3_data_4A34[4];
extern VecXYZ lbl_3_data_4B58[4];

// .text:0x000810C4 size:0xCC mapped:0x806C0158
void fn_3_810C4(s32 runner, s32 base) {
    InMemRunnerType* r = &g_Runners[runner];
    s32 next = (base + 1) & 3;

    if (g_GameLogic.secondaryGameMode == 6) {
        r->runningAngle = lbl_3_data_4B58[base].z;
        r->percentTowardsNextBase = 0.0f;
    } else {
        r->percentTowardsNextBase = r->slidingAdjustment_backwards;
    }
    r->fractionalBasesRan = r->percentTowardsNextBase + base;
    r->baseStandingOn = base;
    r->currentBaseCoordinates.x = lbl_3_data_4A34[base].x;
    r->currentBaseCoordinates.z = lbl_3_data_4A34[base].z;
    r->nextBaseCoordinates.x = lbl_3_data_4A34[next].x;
    r->nextBaseCoordinates.z = lbl_3_data_4A34[next].z;
}

// .text:0x00081190 size:0x928 mapped:0x806C0224
void fn_3_81190(void) {
    return;
}

// .text:0x00081AB8 size:0x34 mapped:0x806C0B4C


void fn_3_81AB8(s32 index) {
    /* Anchoring r4: The compiler generates mulli and add to calculate the array 
       offset based on the struct size 0x154. Defining the pointer exactly where 
       it's first used ensures the address calculation matches the register flow. */
    InMemRunnerType *runner = &g_Runners[index];

    /* Byte assignments: r0 is loaded with 2 and stored at offsets 0x137 and 0x136. */
    runner->runningDirectionCode = 2;
    runner->nextDirectionBeingProcessed = 2;

    /* Float assignments: f0 is loaded once from rodata and stored in multiple fields. */
    runner->groundVelocity[0] = lbl_3_rodata_1414;
    runner->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
    runner->roundingStrengthPercent = lbl_3_rodata_1414;
}

// .text:0x00081AEC size:0xDC mapped:0x806C0B80
void fn_3_81AEC(s32 idx) {
    InMemRunnerType* r = &g_Runners[idx];
    f32 step;

    if (r->leadoffDurationFrames < 0x7FFE) {
        r->leadoffDurationFrames++;
    } else {
        r->leadoffDurationFrames = 0x7FFF;
    }
    if (r->leadOffTotalFrameCountDown <= 0) {
        r->leadOffStatus = 2;
        r->percentRanPerFrame_slideAdj = 0.0f;
        return;
    }
    step = r->leadoffDistancePercent + r->slidingAdjustment_backwards - r->percentTowardsNextBase;
    step /= r->leadOffTotalFrameCountDown;
    r->percentRanPerFrame_slideAdj = step;
    r->percentTowardsNextBase += step;
    r->fractionalBasesRan = r->startingBase_baseAchieved + r->percentTowardsNextBase;
    r->leadOffTotalFrameCountDown--;
}

// .text:0x00081BC8 size:0x2E4 mapped:0x806C0C5C
void fn_3_81BC8(void) {
    return;
}

// .text:0x00081EAC size:0x508 mapped:0x806C0F40
void fn_3_81EAC(void) {
    return;
}

// .text:0x000823B4 size:0x2BC mapped:0x806C1448
void fn_3_823B4(void) {
    return;
}

// .text:0x00082670 size:0x910 mapped:0x806C1704
void fn_3_82670(void) {
    return;
}

// .text:0x00082F80 size:0xFC mapped:0x806C2014
void fn_3_82F80(s32 idx, s16* outBack, s16* outFwd) {
    InMemRunnerType* r = &g_Runners[idx];
    f32 max;
    f32 dist;
    f32 v;
    f32 start;
    s32 frames;
    f32 max2;
    f32 dist2;
    f32 v2;
    s32 frames2;

    frames = 0;
    dist = r->percentTowardsNextBase_slideAdj;
    if (dist > 0.0f) {
        start = r->percentRanPerFrame_slideAdj;
        max = r->velocityPercent_stamAdj;
        if (start < max) {
            v = start;
            do {
                v += r->accelerationPercent_stamAdj;
                frames++;
                if (v > max) {
                    dist -= max;
                    break;
                }
                dist -= v;
            } while (!(dist < 0.0f));
        }
        frames = (s32)(dist / max) + 1 + frames;
    }
    *outFwd = frames;

    frames2 = 0;
    dist2 = r->percentFromCurrentBase_slideAdj;
    if (dist2 > 0.0f) {
        max2 = r->velocityPercent_stamAdj;
        if ((v2 = r->percentRanPerFrame_slideAdj) > -max2) {
            do {
                v2 -= r->accelerationPercent_stamAdj;
                frames2++;
                if (v2 < -max2) {
                    dist2 -= max2;
                    break;
                }
                dist2 -= v2;
            } while (!(dist2 < 0.0f));
        }
        frames2 = (s32)(dist2 / max2) + 1 + frames2;
    }
    *outBack = frames2;
}

// .text:0x0008307C size:0x370 mapped:0x806C2110
void fn_3_8307C(void) {
    return;
}

// .text:0x000833EC size:0x1C4 mapped:0x806C2480
void fn_3_833EC(void) {
    return;
}

typedef struct AiMashEntry {
    /* 0x0 */ s16 minFrames;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 delay;
    /* 0x6 */ s16 chance;
} AiMashEntry; /* size: 0x8 */

extern AiMashEntry lbl_3_data_1C58[];

// .text:0x000835B0 size:0x164 mapped:0x806C2644
void fn_3_835B0(void) {
    if (g_GameLogic._13E[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
        InputStruct* in = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];
        if (in->newButtonInput & 0xF00) {
            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
        }
    } else if (g_AiLogic._44 > 0 &&
               g_Ball.framesSinceHit >= lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]].minFrames) {
        if (g_AiLogic._77 != 0) {
            g_AiLogic._77--;
            return;
        }
        if (RandomInt_Game(100) < lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]].chance) {
            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
            g_AiLogic._44--;
        }
        g_AiLogic._77 = lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]].delay;
    }
}

// .text:0x00083714 size:0xAAC mapped:0x806C27A8
void fn_3_83714(void) {
    return;
}

extern s16 lbl_3_data_1C88[];

// .text:0x000841C0 size:0x124 mapped:0x806C3254
s32 fn_3_841C0(s32 runnerIdx, s32 frames) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    s32 t;

    if (runner->forceOutCd == 1) {
        return 1;
    }
    t = frames + fn_3_A6810(g_Ball.physicsSubstruct.futureCoordsAndDist[frames].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[frames].pos.z,
                            lbl_3_data_4444[runner->nextBase].x, lbl_3_data_4444[runner->nextBase].z);
    t += 45;
    if ((s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        t -= 30;
    } else {
        t += lbl_3_data_1C88[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_Ball.ballZoneAwayFromHome <= 1) {
        if (t - 20 > runner->framesToNextBase) {
            return 1;
        }
    } else if (t > runner->framesToNextBase) {
        return 1;
    }
    return -1;
}

// .text:0x000842E4 size:0x3E4 mapped:0x806C3378
void fn_3_842E4(void) {
    return;
}

// .text:0x000846C8 size:0x408 mapped:0x806C375C
void fn_3_846C8(void) {
    return;
}

// .text:0x00084AD0 size:0x5A4 mapped:0x806C3B64
void fn_3_84AD0(void) {
    return;
}

// .text:0x00085074 size:0x6D0 mapped:0x806C4108
void fn_3_85074(void) {
    return;
}

// .text:0x00085744 size:0xFC mapped:0x806C47D8
void fn_3_85744(s32 idx) {
    InMemRunnerType* r = &g_Runners[idx];

    if (r->fractionalBasesRan > 0.2) {
        return;
    }
    if (r->distanceFromBall < 20.0f && g_Ball.ballState == 3) {
        r->relatedToRunnerPos = 0;
    }
    if (g_FieldingLogic.unkC4 == 5 || g_FieldingLogic.unkC4 == 6 || g_FieldingLogic.unkC4 == r->currentBase) {
        if (r->percentTowardsNextBase >= 0.125f && r->runningDirectionCode == 1 && g_Ball.ballZoneAwayFromHome <= 3) {
            r->relatedToRunnerPos = 0;
        }
    }
    if (r->baseStandingOn >= 0 && r->baseRoundingState == 2) {
        r->relatedToRunnerPos = 1;
        if (0.0f == r->groundVelocity[0]) {
            r->relatedToRunnerPos = 0;
        }
    }
}

// .text:0x00085840 size:0x230 mapped:0x806C48D4
void fn_3_85840(void) {
    return;
}

// .text:0x00085A70 size:0x1D4 mapped:0x806C4B04
void fn_3_85A70(void) {
    return;
}

// .text:0x00085C44 size:0x6C mapped:0x806C4CD8
void fn_3_85C44(s32 runnerIdx, s32 arg1) {
    InMemRunnerType *runner = &g_Runners[runnerIdx];
    if (runner->baseRoundingState == 1 && runner->overRun1BStage >= 2) {
        if (arg1 != 1) {
            return;
        }
    }
    if (arg1 == -1) {
        if (runner->startingBase_baseAchieved == runner->baseStandingOn) {
            arg1 = 0;
        }
    }
    fn_3_85EF4(runnerIdx, arg1);
}

// .text:0x00085CB0 size:0x244 mapped:0x806C4D44
void fn_3_85CB0(void) {
    return;
}

// .text:0x00085EF4 size:0x158 mapped:0x806C4F88
void fn_3_85EF4(s32 runnerIdx, s32 arg1) {
    return;
}

// .text:0x0008604C size:0xCC mapped:0x806C50E0
s32 fn_3_8604C(s32* outFielder) {
    s32 i;
    s32 frames;
    s32 best = 9999;
    s32 j;

    for (i = 0; i < 9; i++) {
        if (g_FieldingLogic.unk_F8[i] == 1 || g_FieldingLogic.unk_F8[i] == 10 || g_FieldingLogic.unk_F8[i] == 11) {
            for (j = 1; j < 120; j += 5) {
                frames = fn_3_52560(i, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.x,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.z);
                if (frames < j + 15) {
                    break;
                }
            }
            if (j >= 120) {
                if (best >= 120) {
                    best = 120;
                }
            } else if (best > frames) {
                best = frames;
                *outFielder = i;
            }
        }
    }
    return best;
}

// .text:0x00086118 size:0x684 mapped:0x806C51AC
void fn_3_86118(void) {
    return;
}

// .text:0x0008679C size:0x660 mapped:0x806C5830
void fn_3_8679C(void) {
    return;
}

// .text:0x00086DFC size:0xFC mapped:0x806C5E90
void fn_3_86DFC(void) {
    InMemRunnerType* runner;
    s32 i;

    runner = g_Runners;
    for (i = 0; i < 4; i++) {
        if (runner->runnerOnFieldOrOutOrScored != 0) {
            if (g_FieldingLogic._107 == 1 && runner->stealingStatus != 0 && runner->rosterID >= 0) {
                runner->runningDirectionDesired = 1;
            }
            runner->stealingStatus = 0;
        }
        runner++;
    }
}

// .text:0x00086EF8 size:0x1B4 mapped:0x806C5F8C
void fn_3_86EF8(void) {
    return;
}

void fn_3_161588(s32 event, s16 rosterID);

// .text:0x000870AC size:0x110 mapped:0x806C6140
void fn_3_870AC(void) {
    InMemRunnerType* r;
    s32 i;

    for (i = 0; i < 4; i++) {
        g_Runners[i].tagType = 0;
    }
    if ((g_FieldingLogic.unk111 == 2 || g_FieldingLogic.unk111 == 4) && g_FieldingLogic.unkE8 >= 0) {
        r = &g_Runners[g_FieldingLogic.unkE8];
        if (r->runnerOnFieldOrOutOrScored == 1) {
            r->tagType = 1;
        }
        if (g_FieldingLogic.unkEC < 5 && r->actionCode != 0) {
            r->tagType = 2;
        }
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.playerIndex == g_GameLogic.teamFielding) {
            fn_3_161588(6, g_Fielders[g_Ball.fielderWBallIndex].unk178);
        }
    }
}

extern f32 lbl_3_data_4C44[4];
extern s16 lbl_3_data_4C54[12];

// .text:0x000871BC size:0x110 mapped:0x806C6250
void fn_3_871BC(void) {
    s32 i;
    s32 drain;
    f32 t;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            drain = 0;
            if (g_Runners[i].groundVelocity[0] >= 0.1f) {
                drain = lbl_3_data_4C54[10];
            }
            if (g_Runners[i].turnaroundCode != 0) {
                drain += lbl_3_data_4C54[11];
            }
            if (drain != 0) {
                g_Runners[i].stamina -= drain;
                if (g_Runners[i].stamina < 0) {
                    g_Runners[i].stamina = 0;
                }
            }
            t = 1.0f - (f32)g_Runners[i].stamina / (f32)lbl_3_data_4C54[9];
            g_Runners[i].staminaMult = 1.0f - lbl_3_data_4C44[1] * t;
            g_Runners[i].accelerationStaminaEffect = 1.0f - lbl_3_data_4C44[2] * t;
            g_Runners[i].accelerationStaminaEffectWhileChangingDirection = 1.0f - lbl_3_data_4C44[3] * t;
        }
    }
}

// .text:0x000872CC size:0x158 mapped:0x806C6360
void fn_3_872CC(void) {
    return;
}

// .text:0x00087424 size:0x3F8 mapped:0x806C64B8
void fn_3_87424(void) {
    return;
}

// .text:0x0008781C size:0x2CC mapped:0x806C68B0
void fn_3_8781C(void) {
    return;
}

// .text:0x00087AE8 size:0x1E0 mapped:0x806C6B7C
void fn_3_87AE8(void) {
    return;
}

// .text:0x00087CC8 size:0x1B8 mapped:0x806C6D5C
void fn_3_87CC8(void) {
    return;
}

// .text:0x00087E80 size:0x3A8 mapped:0x806C6F14
void fn_3_87E80(void) {
    return;
}

// .text:0x00088228 size:0x1E0 mapped:0x806C72BC
void fn_3_88228(void) {
    return;
}

// .text:0x00088408 size:0x5F4 mapped:0x806C749C
void fn_3_88408(void) {
    return;
}

// .text:0x000889FC size:0x11C mapped:0x806C7A90
void fn_3_889FC(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            if ((g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) &&
                g_Ball.landingSpotZoneAwayFromHome <= 1) {
                g_Runners[i].isEligibleToScore = 0;
            } else if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0 &&
                       !(g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == 1) && g_Runners[i].currentBase != 0 &&
                       g_Runners[i].currentBase < 3) {
                g_Runners[i].isEligibleToScore = 0;
            }
        }
    }
}

// .text:0x00088B18 size:0x10C mapped:0x806C7BAC
void fn_3_88B18(void) {
    s32 state;
    s32 i;
    InMemRunnerType* runner;
    s16 standing;

    state = 0;
    if (g_FieldingLogic._107 != 0 && g_FieldingLogic._107 != 4) {
        state = 1;
    }
    runner = g_Runners;
    for (i = 0; i < 4; i++, runner++) {
        if (runner->forceOutCd == 2) {
            state = 2;
            continue;
        }
        runner->forceOutCd = 0;
        if (g_Ball.AtBat_ContactResult < 0 || g_FieldingLogic._108 != 0) {
            continue;
        }
        if (state != 0) {
            if (runner->runnerOnFieldOrOutOrScored == 0) {
                state = 1;
            }
            if (state == 2 && runner->startingBase_baseAchieved == runner->currentBase) {
                runner->forceOutCd = -1;
            }
        } else if (runner->runnerOnFieldOrOutOrScored == 1) {
            standing = runner->baseStandingOn;
            if ((standing < 0 || standing != ((runner->startingBase_baseAchieved + 1) & 3))
                && runner->startingBase_baseAchieved == runner->currentBase) {
                runner->forceOutCd = 1;
            }
        } else {
            state = 1;
        }
    }
}

// .text:0x00088C24 size:0x164 mapped:0x806C7CB8
void fn_3_88C24(void) {
    return;
}

// .text:0x00088D88 size:0x210 mapped:0x806C7E1C
void fn_3_88D88(s32 idx) {
    Strikes* strikes = &g_Strikes;
    InMemRunnerType* runner = &g_Runners[idx];
    GameControlsStruct* logic;
    s32 i;

    if (strikes->outs >= 3) {
        return;
    }
    logic = &g_GameLogic;
    if (logic->EventTriggers_EndOfGame != 0) {
        return;
    }
    if (runner->runnerOnFieldOrOutOrScored != 1) {
        return;
    }
    if (logic->freeFieldingPracticeInd == 0) {
        strikes->outs++;
    } else if ((g_Practice.practiceType_2 == 2 && g_Practice.practiceLevel == 1) || g_Practice.practiceLevel == 7 ||
               g_Practice.practiceLevel == 6) {
        strikes->outs++;
    }
    if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
        fn_3_59918(0x16, 0);
    } else if (runner->fractionalBasesRan >= 3.8f && g_Ball.baseBallAndFielderAreOn == 0) {
        fn_3_59918(1, 1);
    } else {
        fn_3_59918(1, 0);
    }
    for (i = 0; i < 3; i++) {
        if (g_Strikes.unk_18[i] == -1) {
            g_Strikes.unk_18[i] = idx;
            break;
        }
    }
    if (strikes->outs == 3) {
        if (runner->forceOutCd == 1) {
            g_Strikes.unk_10 = 1;
        } else {
            fn_3_5C74C(1);
        }
        fn_3_5D094(0);
        if (logic->EventTriggers_EndOfGame != 0) {
            fn_3_59918(0xD, 0);
        } else {
            fn_3_59918(5, 0);
        }
    }
    runner->runnerOnFieldOrOutOrScored = 2;
}

// .text:0x00088F98 size:0x90 mapped:0x806C802C
void fn_3_88F98(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == 0) {
            fn_3_85EF4(i, 1);
        }
        if (i == 0) {
            g_Runners[i].unused_AIRelated = 1;
        } else {
            g_Runners[i].unused_AIRelated = 0;
            if (g_Strikes.unk_C < 2) {
                g_Runners[i].tagUpInd = 1;
            } else {
                g_Runners[i].tagUpInd = 0;
            }
        }
    }
}

// .text:0x00089028 size:0xF4 mapped:0x806C80BC
void fn_3_89028(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_Runners[i].leadOffStatus = 0;
    }
    for (i = 1; i < 4; i++) {
        g_Runners[i].unused_AIRelated = 0;
        g_Runners[i].tagUpInd = 0;
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            fn_3_85EF4(i, 1);
        }
    }
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 5;
    } else if (g_FieldingLogic._107 == 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 1;
        fn_3_85EF4(0, 1);
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = 4;
    }
}

// .text:0x0008911C size:0x20 mapped:0x806C81B0
void fn_3_8911C(void) {
    g_Runners[0].leadOffStatus = 0;
    g_Runners[1].leadOffStatus = 0;
    g_Runners[2].leadOffStatus = 0;
    g_Runners[3].leadOffStatus = 0;
}

// .text:0x0008913C size:0x728 mapped:0x806C81D0
void fn_3_8913C(void) {
    return;
}

// .text:0x00089864 size:0x58 mapped:0x806C88F8
void fn_3_89864(s32 idx, s32 delta) {
    InMemRunnerType* runner = &g_Runners[idx];
    runner->currentBase += delta;
    runner->nextBase = (runner->currentBase + 1) & 3;
    if (runner->currentBase >= 4) {
        runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DURING_PLAY;
        g_Scores.field_0x9C++;
    }
}

// .text:0x000898BC size:0x58 mapped:0x806C8950
void fn_3_898BC(s32 idx, s32 rosterIdx) {
    InMemRunnerType* runner = &g_Runners[idx];
    runner->rosterID = rosterIdx;
    runner->battingHand = inMemRoster[g_GameLogic.teamBatting][rosterIdx].stats.FieldingArm;
    if (runner->battingHand == 2) {
        runner->battingHand = BATTING_HAND_RIGHT;
    }
}

// .text:0x00089914 size:0xA8 mapped:0x806C89A8
void fn_3_89914(s32 src, s32 dst) {
    InMemRunnerType* from = &g_Runners[src];
    InMemRunnerType* to = &g_Runners[dst];

    if (src >= 0 && src <= 3) {
        if (g_GameLogic.secondaryGameMode == 0xF && src == 0) {
            to->rosterID = g_Practice.rosterID;
        } else {
            to->rosterID = from->rosterID;
            to->battingHand = from->battingHand;
            to->runnerDidntReachOnError = from->runnerDidntReachOnError;
            to->pitcherWhoLetRunnerOnBase = from->pitcherWhoLetRunnerOnBase;
        }
        g_RunningLogic.runnerOnBase[src] = dst;
    } else {
        to->rosterID = -1;
        to->runnerDidntReachOnError = 0;
        to->pitcherWhoLetRunnerOnBase = -1;
    }
}

// .text:0x000899BC size:0x81C mapped:0x806C8A50
void fn_3_899BC(void) {
    return;
}

// .text:0x0008A1D8 size:0x178 mapped:0x806C926C
void fn_3_8A1D8(void) {
    return;
}

// .text:0x0008A350 size:0x178 mapped:0x806C93E4
void fn_3_8A350(void) {
    return;
}

// .text:0x0008A4C8 size:0x1C mapped:0x806C955C
void fn_3_8A4C8(void) {
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.z = g_Batter.batterPos.z;
}

// .text:0x0008A4E4 size:0xC0 mapped:0x806C9578
void fn_3_8A4E4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];

        r->position.x = lbl_3_data_4A34[i].x;
        r->position.z = lbl_3_data_4A34[i].z;
        r->velocity.x = 0.0f;
        r->velocity.y = 0.0f;
        r->velocity.z = 0.0f;
        r->startingBase_baseAchieved = i;
        r->currentBase = i;
        r->nextBase = (i + 1) & 3;
        r->baseStandingOn = i;
        r->baseRunningTowards = 0xFF;
        r->leadOffStatus = 0;
    }
}

// .text:0x0008A5A4 size:0x74 mapped:0x806C9638
void fn_3_8A5A4(void) {
    InMemRunnerType* runners = g_Runners;
    s16 value = -1;

    runners[0].rosterID = value;
    runners[0]._121 = 0xA;
    runners[0].delayBeforeStartingToRun = 0x1E;
    runners[0].leadoffDistancePercent = lbl_3_rodata_1498;
    runners[0].someCollisionCheck = 0;
    runners[1].rosterID = value;
    runners[1]._121 = 0xA;
    runners[1].delayBeforeStartingToRun = 0x1E;
    runners[1].leadoffDistancePercent = lbl_3_rodata_1498;
    runners[1].someCollisionCheck = 0;
    runners[2].rosterID = value;
    runners[2]._121 = 0xA;
    runners[2].delayBeforeStartingToRun = 0x1E;
    runners[2].leadoffDistancePercent = lbl_3_rodata_1498;
    runners[2].someCollisionCheck = 0;
    runners[3].rosterID = value;
    runners[3]._121 = 0xA;
    runners[3].delayBeforeStartingToRun = 0x1E;
    runners[3].leadoffDistancePercent = lbl_3_rodata_1498;
    runners[3].someCollisionCheck = 0;
}

// .text:0x0008A618 size:0x19C mapped:0x806C96AC
void fn_3_8A618(void) {
    return;
}

// .text:0x0008A7B4 size:0x1A4 mapped:0x806C9848
void fn_3_8A7B4(void) {
    return;
}

// .text:0x0008A958 size:0x73C mapped:0x806C99EC
void fn_3_8A958(void) {
    return;
}
