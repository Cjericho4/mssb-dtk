#include "game/rep_18E8.h"
#include "game/rep_AC8.h"
#include "game/rep_1838.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"

// .text:0x000A009C size:0x1C68 mapped:0x806DF130
void fn_3_A009C(void) {
    return;
}

// .text:0x000A1D04 size:0x9C mapped:0x806E0D98
s32 fn_3_A1D04(void) {
    s32 prev;
    s32 i;
    f32 prevPos;
    f32 pos;

    prevPos = -10.0f;
    for (i = 3; i >= 0; i--) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            pos = g_Runners[i].fractionalBasesRan;
            prevPos = pos - prevPos;
            if (prevPos < 0.0f) {
                prevPos = -prevPos;
            }
            if (prevPos < 0.35f) {
                if (g_Runners[prev].baseStandingOn < 0) {
                    return prev;
                }
                return i;
            }
            prevPos = pos;
            prev = i;
        }
    }
    return -1;
}

// .text:0x000A1DA0 size:0x19C mapped:0x806E0E34
void fn_3_A1DA0(void) {
    return;
}

typedef struct {
    s32 runnerIndex[4]; /* 0x00 */
    u8 _pad10[0x4];
} Bss1808;
extern Bss1808 lbl_3_bss_1808;
extern s32 lbl_3_bss_1858[];
extern u32 lbl_3_bss_1800;
extern s32 lbl_3_bss_181C;
extern s32 lbl_3_bss_1820;
extern u32 lbl_3_bss_1824;

// .text:0x000A1F3C size:0x10C mapped:0x806E0FD0
s32 fn_3_A1F3C(void) {
    s32 i;
    s32 idx;

    if (g_Ball.ballZoneAwayFromHome >= 3) {
        return 0;
    }
    idx = lbl_3_bss_1808.runnerIndex[3];
    if (idx < 0 || idx > 3) {
        return 0;
    }
    if (lbl_3_bss_1858[idx] >= 7) {
        return 0;
    }
    if (g_Runners[idx].tagUpInd != 0) {
        return 0;
    }
    if (idx >= 1) {
        for (i = idx - 1; i >= 0; i--) {
            if (g_Runners[i].percentTowardsNextBase > 0.15f && g_Runners[i].percentTowardsNextBase < 0.85f) {
                return 0;
            }
        }
    }
    if (fn_3_A46A0(idx) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000A2048 size:0x1E4 mapped:0x806E10DC
s32 fn_3_A2048(void) {
    s32 i;
    s32 flags;
    s16 ang;

    flags = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            if (g_Runners[i].fractionalBasesRan < 1.7f) {
                flags |= 0x10;
            } else if (g_Runners[i].fractionalBasesRan < 2.2f) {
                flags |= 0x100;
            } else if (g_Runners[i].fractionalBasesRan <= 3.0f) {
                flags |= 0x1000;
            }
        }
    }
    ang = g_Ball.ballAngleFromHome;
    if (ang > 0x500) {
        if (flags & 0x1000) {
            fn_3_A41E8(3);
            return 1;
        }
        if (flags & 0x100) {
            fn_3_A41E8(3);
            return 1;
        }
        if (flags & 0x10) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    }
    if (ang > 0x400) {
        if (flags & 0x1000) {
            fn_3_A41E8(3);
            return 1;
        }
        if ((flags & 0x100) && !(flags & 0x1000)) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    }
    if (flags & 0x1000) {
        if (!(flags & 0x10) || (flags & 0x100)) {
            fn_3_A41E8(0);
            return 1;
        }
    } else if (flags & 0x100) {
        fn_3_A41E8(3);
        return 1;
    }
    return 0;
}

// .text:0x000A222C size:0x1D8 mapped:0x806E12C0
s32 fn_3_A222C(void) {
    s32 order[3];
    s32 i;
    s32 idx;

    if (g_Ball.AtBat_ContactResult != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        } else {
            order[0] = 3;
            order[1] = 1;
            order[2] = 2;
        }
    }
    for (i = 0; i < 3; i++) {
        idx = order[i];
        if (g_Runners[idx].runnerOnFieldOrOutOrScored == 1 && g_Runners[idx].tagUpInd == 2 &&
            lbl_3_bss_1858[idx] <= 4 && g_Ball.ballDistanceFromBase[idx] < 45.0f && fn_3_A46A0(idx) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2404 size:0x1C0 mapped:0x806E1498
s32 fn_3_A2404(void) {
    s32 order[3];
    s32 i;
    s32 idx;

    if (g_Ball.AtBat_ContactResult != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        } else {
            order[0] = 3;
            order[1] = 1;
            order[2] = 2;
        }
    }
    for (i = 0; i < 3; i++) {
        idx = order[i];
        if (g_Runners[idx].runnerOnFieldOrOutOrScored == 1 && g_Runners[idx].tagUpInd == 2 &&
            lbl_3_bss_1858[idx] <= 4 && fn_3_A46A0(idx) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A25C4 size:0x398 mapped:0x806E1658
void fn_3_A25C4(void) {
    return;
}

// .text:0x000A295C size:0x210 mapped:0x806E19F0
void fn_3_A295C(void) {
    return;
}

// .text:0x000A2B6C size:0x130 mapped:0x806E1C00
void fn_3_A2B6C(void) {
    return;
}

// .text:0x000A2C9C size:0x140 mapped:0x806E1D30
void fn_3_A2C9C(void) {
    return;
}

// .text:0x000A2DDC size:0x1FC mapped:0x806E1E70
void fn_3_A2DDC(void) {
    return;
}

// .text:0x000A2FD8 size:0x210 mapped:0x806E206C
void fn_3_A2FD8(void) {
    return;
}

// .text:0x000A31E8 size:0xD0 mapped:0x806E227C
void fn_3_A31E8(void) {
    return;
}

// .text:0x000A32B8 size:0xBC mapped:0x806E234C
void fn_3_A32B8(void) {
    return;
}

// .text:0x000A3374 size:0x348 mapped:0x806E2408
void fn_3_A3374(void) {
    return;
}

// .text:0x000A36BC size:0x70 mapped:0x806E2750
s32 fn_3_A36BC(void) {
    if (g_Ball.AtBat_Contact_BallPos.z < 15.0f &&
        g_Ball.AtBat_Contact_BallPos.z > 8.0f &&
        g_Ball.AtBat_Contact_BallPos.z < 1.5f + g_Ball.AtBat_Contact_BallPos.x &&
        g_Ball.AtBat_Contact_BallPos.z > g_Ball.AtBat_Contact_BallPos.x - 1.5f &&
        g_Ball.AtBat_Contact_BallPos.x > g_Runners[0].position.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A372C size:0x3C mapped:0x806E27C0

#include "types.h"
#include "game/UnknownHomes_Game.h"

/**
 * @address 000A372C
 */
s32 fn_3_A372C(void) {
    if (g_Ball.AtBat_Contact_BallPos.z < 40.0f + g_Ball.AtBat_Contact_BallPos.x && g_Ball.AtBat_Contact_BallPos.z < 40.0f - g_Ball.AtBat_Contact_BallPos.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A3768 size:0x54 mapped:0x806E27FC
s32 fn_3_A3768(void) {
    if (g_Ball.ballAngleFromHome >= 0x380
        && g_Ball.ballAngleFromHome < 0x640
        && g_Ball.ballZoneAwayFromHome <= 1
        && g_Ball.AtBat_Contact_BallPos.z > (lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x)) {
        return 1;
    }
    return 0;
}

// .text:0x000A37BC size:0x90 mapped:0x806E2850
BOOL fn_3_A37BC(void) {
    sAng ang = g_Ball.ballAngleFromHome;
    if (ang < 0x398) {
        return FALSE;
    }
    if (g_Ball.ballDistanceFromBase[2] < 5.0f) {
        return TRUE;
    }
    if (ang < 0x400) {
        if (g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x > 40.0f) {
            return TRUE;
        }
    } else {
        if (g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x > 40.0f) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000A384C size:0x2E4 mapped:0x806E28E0
void fn_3_A384C(void) {
    return;
}

// .text:0x000A3B30 size:0xD0 mapped:0x806E2BC4
void fn_3_A3B30(void) {
    s32 diff;
    diff = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score -
           g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score;
    lbl_3_bss_181C = 0;
    if (g_Scores.highscore >= g_Scores.threshold && g_Scores.unkAD != 0 && diff == 0) {
        lbl_3_bss_181C = 3;
    } else if (g_Scores.highscore >= g_Scores.threshold - 1 && diff <= 1 && diff >= -1) {
        lbl_3_bss_181C = 2;
    } else if (g_Scores.highscore >= g_Scores.threshold - 4 && diff <= 1 && diff >= -3) {
        lbl_3_bss_181C = 1;
    }
}

// .text:0x000A3C00 size:0xC0 mapped:0x806E2C94
void fn_3_A3C00(void) {
    s32 i;

    lbl_3_bss_1800 = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_3_bss_1808.runnerIndex[i] >= 0) {
            if (g_Runners[lbl_3_bss_1808.runnerIndex[i]].runningDirectionCode == 1) {
                lbl_3_bss_1800 |= 1 << (i * 4);
            } else if (g_Runners[lbl_3_bss_1808.runnerIndex[i]].runningDirectionCode == 3) {
                lbl_3_bss_1800 |= 2 << (i * 4);
            } else if (g_Runners[lbl_3_bss_1808.runnerIndex[i]].runningDirectionCode == 2) {
                lbl_3_bss_1800 |= 4 << (i * 4);
            }
        }
    }
}

// .text:0x000A3CC0 size:0x498 mapped:0x806E2D54
void fn_3_A3CC0(void) {
    return;
}

// .text:0x000A4158 size:0x90 mapped:0x806E31EC
void fn_3_A4158(s32 runnerIdx) {
    InMemRunnerType* r = &g_Runners[runnerIdx];
    if (r->runningDirectionCode == 2) {
        fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x, r->position.z);
    } else {
        fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x + 2.0f * (r->velocity.x * r->distanceFromBall),
                   r->position.z + 2.0f * (r->velocity.y * r->distanceFromBall));
    }
}

// .text:0x000A41E8 size:0x4B8 mapped:0x806E327C
void fn_3_A41E8(s32 arg0) {
    return;
}

// .text:0x000A46A0 size:0x370 mapped:0x806E3734
s32 fn_3_A46A0(s32 idx) {
    return 0;
}

// .text:0x000A4A10 size:0x540 mapped:0x806E3AA4
void fn_3_A4A10(void) {
    return;
}

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
void fn_3_A4F50(void) {
    return;
}

// .text:0x000A53DC size:0x328 mapped:0x806E4470
void fn_3_A53DC(void) {
    return;
}

// .text:0x000A5704 size:0x448 mapped:0x806E4798
void fn_3_A5704(void) {
    return;
}

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
void fn_3_A5B4C(void) {
    return;
}

// .text:0x000A63E4 size:0x404 mapped:0x806E5478
void fn_3_A63E4(void) {
    return;
}

// .text:0x000A67E8 size:0x28 mapped:0x806E587C
void fn_3_A67E8(s32 index) {
    lbl_3_bss_1838[index] = 9;
    lbl_3_bss_1828[index] = -1;
}

// .text:0x000A6810 size:0x2AC mapped:0x806E58A4
s32 fn_3_A6810(f32 x0, f32 z0, f32 x1, f32 z1) {
    return 0;
}

// .text:0x000A6ABC size:0x28C mapped:0x806E5B50
void fn_3_A6ABC(void) {
    return;
}

// .text:0x000A6D48 size:0x150 mapped:0x806E5DDC
void fn_3_A6D48(void) {
    s32 i;
    s32 base;

    lbl_3_bss_1824 = 0;
    for (i = 0; i < 4; i++) {
        lbl_3_bss_1808.runnerIndex[i] = -1;
    }
    for (i = 3; i >= 0; i--) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            base = g_Runners[i].currentBase;
            lbl_3_bss_1824 |= 1 << ((s32)g_Runners[i].fractionalBasesRan * 4);
            if (lbl_3_bss_1808.runnerIndex[base] < 0 ||
                g_Runners[lbl_3_bss_1808.runnerIndex[base]].baseStandingOn >= 0) {
                lbl_3_bss_1808.runnerIndex[base] = i;
            }
        }
    }
}

// .text:0x000A6E98 size:0x1A8 mapped:0x806E5F2C
void fn_3_A6E98(void) {
    return;
}

// .text:0x000A7040 size:0x674 mapped:0x806E60D4
void fn_3_A7040(void) {
    return;
}

// .text:0x000A76B4 size:0x5D4 mapped:0x806E6748
void fn_3_A76B4(void) {
    return;
}

// .text:0x000A7C88 size:0x270 mapped:0x806E6D1C
void fn_3_A7C88(void) {
    return;
}

// .text:0x000A7EF8 size:0x17C mapped:0x806E6F8C
void fn_3_A7EF8(void) {
    InputStruct* input = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    s16 angle;
    u8 prev;

    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        input = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (g_d_GameSettings.minigamesEnabled != 0) {
        input = &g_Controls[g_Minigame.players.characterIndex[g_Minigame._1922]];
    }
    angle = input->controlStickAngle;
    prev = g_FieldingLogic.unk12E;
    if (angle >= 0xE00) {
        g_FieldingLogic.unk12E = 2;
    } else if (angle >= 0xA00) {
        g_FieldingLogic.unk12E = 3;
    } else if (angle >= 0x600) {
        g_FieldingLogic.unk12E = 4;
    } else if (angle >= 0x200) {
        g_FieldingLogic.unk12E = 1;
    } else if (angle >= 0) {
        g_FieldingLogic.unk12E = 2;
    } else {
        g_FieldingLogic.unk12E = 0;
    }
    if (g_FieldingLogic.unk12E == 0) {
        g_FieldingLogic.unk12F = 0;
    } else if (g_FieldingLogic.unk12E == prev) {
        if (g_FieldingLogic.unk12F < 0xFE) {
            g_FieldingLogic.unk12F++;
        } else {
            g_FieldingLogic.unk12F = 0xFF;
        }
    } else {
        g_FieldingLogic.unk12F = 1;
    }
}

// .text:0x000A8074 size:0x2C4 mapped:0x806E7108
void fn_3_A8074(s32 fielderIdx) {
    return;
}

// .text:0x000A8338 size:0x140 mapped:0x806E73CC
void fn_3_A8338(s32 fielderIdx) {
    FieldingLogic* fl = &g_FieldingLogic;
    Fielder* fielder = &g_Fielders[fielderIdx];
    s16 base = fl->unkCC;
    s16 runner;

    if (base >= 0 && base <= 3 && fielder->unk1F5 == base) {
        fl->unkCC = -1;
        return;
    }
    if (g_FieldingLogic.unkE2 == -1) {
        runner = g_FieldingLogic.unkDE;
        if (runner >= 0 && g_Runners[runner].runnerOnFieldOrOutOrScored != 1) {
            g_FieldingLogic.unkDE = -1;
            fl->unkCC = -1;
            return;
        }
        g_FieldingLogic.unkE2 = base;
        fn_3_A8074(fielderIdx);
    }
    base = fl->unkCC;
    if (base >= 0 && base <= 3) {
        if (g_FieldingLogic.unkDE == -1) {
            fn_3_52F4C(g_Ball.fielderWBallIndex, lbl_3_data_4444[base].x, lbl_3_data_4444[base].z);
        } else {
            fn_3_52F4C(g_Ball.fielderWBallIndex, g_Runners[g_FieldingLogic.unkDE].position.x,
                       g_Runners[g_FieldingLogic.unkDE].position.z);
        }
    }
    fn_3_A3CC0();
}

// .text:0x000A8478 size:0x150 mapped:0x806E750C
void fn_3_A8478(void) {
    return;
}

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
void fn_3_A85C8(void) {
    return;
}

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
void fn_3_A89D4(void) {
    return;
}

// .text:0x000A9354 size:0x3A8 mapped:0x806E83E8
void fn_3_A9354(void) {
    return;
}

// .text:0x000A96FC size:0x288 mapped:0x806E8790
void fn_3_A96FC(s32 fielderIdx) {
    return;
}

// .text:0x000A9984 size:0x2F0 mapped:0x806E8A18
void fn_3_A9984(s32 fielderIdx) {
    return;
}

// .text:0x000A9C74 size:0xAC mapped:0x806E8D08
typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
} FielderThrowEntry;
extern FielderThrowEntry lbl_3_data_4900[];

void fn_3_A9C74(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    BOOL quick = checkFieldingStat(g_GameLogic.teamFielding, f->unk178, FIELDING_ABILITY_QUICK_THROW);
    if (f->unk1F8 >= 3) {
        f->unk215 = lbl_3_data_4900[quick].unk1;
    } else {
        f->unk215 = lbl_3_data_4900[quick].unk0;
    }
    if (quick && g_FieldingLogic.unkC4 >= 0) {
        playSoundEffect(0x1a8);
    }
}

// .text:0x000A9D20 size:0xD1C mapped:0x806E8DB4
void fn_3_A9D20(void) {
    return;
}

// .text:0x000AAA3C size:0x1BC mapped:0x806E9AD0
void fn_3_AAA3C(s32 fielderIdx) {
    FieldingLogic* fl = &g_FieldingLogic;
    Fielder* f = &g_Fielders[fielderIdx];
    s16 a;
    s16 base;
    s16 r;

    a = fl->unkCE;
    if (a < 0) {
        return;
    }
    base = fl->unkC4;
    if (base < 0 || base > 3) {
        return;
    }
    if (f->unkA8[base] > 10.0f && fl->unkDC < 0) {
        return;
    }
    if (base == a) {
        r = g_FieldingLogic.unkE0;
        if (r >= 0 && r <= 3) {
            if (g_FieldingLogic.unkDC == g_Runners[r].nextBase || g_FieldingLogic.unkDC == g_Runners[r].currentBase) {
                g_FieldingLogic.unk119 = 1;
            }
        }
    }
    if (fl->unkCE == 9) {
        r = g_FieldingLogic.unkE0;
        if (r >= 0 && r <= 3 && g_Runners[r].runnerOnFieldOrOutOrScored == 1 &&
            fl->unkC4 == g_Runners[r].baseRunningTowards) {
            g_FieldingLogic.unk119 = 1;
        }
    }
    if (g_FieldingLogic.unk119 != 0) {
        base = fl->unkC4;
        if (base >= 0 && base <= 3) {
            if (fn_3_9FC1C(game_atan2(lbl_3_data_4444[base].x - f->pos[0], lbl_3_data_4444[base].z - f->pos[2]), f->unk48) > 0x40) {
                g_FieldingLogic.unk119 = 0;
            }
        }
    }
}

// .text:0x000AABF8 size:0x8C mapped:0x806E9C8C
BOOL fn_3_AABF8(void) {
    s16 idx = g_FieldingLogic.unkD0[4];
    if (idx == -1) {
        return FALSE;
    }
    if (g_FieldingLogic.unk101[4] != 1) {
        return FALSE;
    }
    if (g_Fielders[idx].unk18C != 5) {
        return FALSE;
    }
    return !(g_Fielders[g_Ball.fielderWBallIndex].unkB8 < 10.0f);
}

// .text:0x000AAC84 size:0x36C mapped:0x806E9D18
void fn_3_AAC84(void) {
    return;
}

// .text:0x000AAFF0 size:0x564 mapped:0x806EA084
void fn_3_AAFF0(void) {
    return;
}

// .text:0x000AB554 size:0x5C mapped:0x806EA5E8
void fn_3_AB554(void) {
    if (g_FieldingLogic.unk10D != 0) {
        s16 t = g_Ball.timeSinceBallPickedUp;
        if (t >= 0 && t < 0x28) {
            if (g_FieldingLogic.unkC4 >= 0) {
                g_FieldingLogic.unk10C = 1;
                g_FieldingLogic.unk10D = 0;
            }
        } else {
            g_FieldingLogic.unk10D = 0;
        }
    }
}

// .text:0x000AB5B0 size:0x820 mapped:0x806EA644
void fn_3_AB5B0(void) {
    return;
}

// .text:0x000ABDD0 size:0xC28 mapped:0x806EAE64
void fn_3_ABDD0(void) {
    return;
}