#include "game/gap_7976C.h"
#include "game/gap_15C5F4.h"

s32 fn_3_6C938(s32, s32);

typedef struct Bss32A38Entry {
    u8 unk0;
    u8 unk1;
    u8 _pad2[3];
} Bss32A38Entry; // size: 0x5

extern Bss32A38Entry lbl_3_common_bss_32A38[2][9];

// .text:0x0007976C size:0x294 mapped:0x806B8800
void fn_3_7976C(void) {
    return;
}

// .text:0x00079A00 size:0xCC mapped:0x806B8A94
void fn_3_79A00(void) {
    if (lbl_3_common_bss_32A94.unk25 == -1) {
        return;
    }
    if (lbl_3_common_bss_32A94.unk25 == 0 && g_Strikes.unk_18[0] >= 0) {
        if (g_Runners[g_Strikes.unk_18[0]].forceOutCd == 2) {
            lbl_3_common_bss_32A94.unk25 = 1;
        } else {
            lbl_3_common_bss_32A94.unk25 = -1;
        }
    }
    if (lbl_3_common_bss_32A94.unk25 == 1 && g_Strikes.unk_18[1] >= 0) {
        if (g_Runners[g_Strikes.unk_18[1]].forceOutCd == 2) {
            lbl_3_common_bss_32A94.unk25 = 2;
        } else if (g_Runners[g_Strikes.unk_18[1]].forceOutCd == -1) {
            lbl_3_common_bss_32A94.unk25 = 3;
        } else {
            lbl_3_common_bss_32A94.unk25 = -1;
        }
    }
}

// .text:0x00079ACC size:0x308 mapped:0x806B8B60
void fn_3_79ACC(void) {
    return;
}

// .text:0x00079DD4 size:0x120 mapped:0x806B8E68
void fn_3_79DD4(void) {
    s32 diff;
    s32 n;
    s32 slot;
    s32 i;

    diff = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score - g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score;
    g_Scores.unkB7[g_GameLogic.awayTeamBattingInd_battingTeam] = -1;
    if (diff <= 0) {
        return;
    }
    if (g_Scores.highscore + 2 >= g_Scores.threshold && (g_Scores.highscore + 2 != g_Scores.threshold || g_Strikes.outs != 0) &&
        (diff > 3 || (g_Scores.highscore >= g_Scores.threshold && (g_Scores.highscore < g_Scores.threshold || g_Strikes.outs != 0)))) {
        n = 0;
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
                n++;
            }
        }
        if (diff > n + 2) {
            return;
        }
    }
    slot = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    g_Scores.unkB7[g_GameLogic.awayTeamBattingInd_battingTeam] = slot;
    lbl_3_common_bss_32A38[g_GameLogic.teamFielding][slot].unk1 = 1;
}

// .text:0x00079EF4 size:0x260 mapped:0x806B8F88
void fn_3_79EF4(void) {
    return;
}

// .text:0x0007A154 size:0x9E0 mapped:0x806B91E8
void fn_3_7A154(void) {
    return;
}

// .text:0x0007AB34 size:0x44 mapped:0x806B9BC8
void fn_3_7AB34(void) {
    StatTableEntry* entry = &lbl_803535C8[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]];
    entry->unkE++;
}

// .text:0x0007AB78 size:0x1F0 mapped:0x806B9C0C
void fn_3_7AB78(s32 arg0) {
    s32 i;
    s32 team;
    s32 pitcher;
    s32 catcher;

    if (arg0 != 0) {
        if (g_Scores.unkBB[g_GameLogic.awayTeamBattingInd_battingTeam] < 0xFE) {
            g_Scores.unkBB[g_GameLogic.awayTeamBattingInd_battingTeam]++;
        } else {
            g_Scores.unkBB[g_GameLogic.awayTeamBattingInd_battingTeam] = 0xFF;
        }
    }
    team = g_GameLogic.awayTeamBattingInd_battingTeam;
    pitcher = g_GameLogic.battingOrderAndPositionMapping[team][0][0];
    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[team][i][1] == 1) {
            catcher = g_GameLogic.battingOrderAndPositionMapping[team][i][0];
            break;
        }
    }
    if (lbl_80353A90.pitchers[g_GameLogic.teamFielding][0].id == -1) {
        lbl_80353A90.pitchers[g_GameLogic.teamFielding][0].id = pitcher;
        lbl_80353A90.pitchers[g_GameLogic.teamFielding][0].inning = 1;
        lbl_80353A90.catchers[g_GameLogic.teamFielding][0] = catcher;
        return;
    }
    for (i = 1; i < 10; i++) {
        if (lbl_80353A90.pitchers[g_GameLogic.teamFielding][i].id == -1) {
            if (lbl_80353A90.pitchers[g_GameLogic.teamFielding][i - 1].id != pitcher) {
                lbl_80353A90.pitchers[g_GameLogic.teamFielding][i].id = pitcher;
                lbl_80353A90.pitchers[g_GameLogic.teamFielding][i].inning = g_Scores.highscore;
                if (lbl_3_common_bss_32A94.unk4C[team] < 0x7FFE) {
                    lbl_3_common_bss_32A94.unk4C[team]++;
                } else {
                    lbl_3_common_bss_32A94.unk4C[team] = 0x7FFF;
                }
            }
            break;
        }
    }
    if (arg0 != 0) {
        return;
    }
    for (i = 1; i < 5; i++) {
        if (lbl_80353A90.catchers[g_GameLogic.teamFielding][i] == -1) {
            if (lbl_80353A90.catchers[g_GameLogic.teamFielding][i - 1] != catcher) {
                lbl_80353A90.catchers[g_GameLogic.teamFielding][i] = catcher;
            }
            return;
        }
    }
}

// .text:0x0007AD68 size:0x140 mapped:0x806B9DFC
void fn_3_7AD68(void) {
    return;
}

// .text:0x0007AEA8 size:0x40 mapped:0x806B9F3C
s32 fn_3_7AEA8(void) {
    s32 team = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    s32 bssVal = lbl_3_common_bss_32A94.unk44[team];
    s32 currentBatter = g_GameLogic.currentBatterPerTeam[team];
    return currentBatter + (bssVal - 1) * 9 - 1;
}

// .text:0x0007AEE8 size:0x4 mapped:0x806B9F7C
void fn_3_7AEE8(void) {
    return;
}

// .text:0x0007AEEC size:0x7C mapped:0x806B9F80
void fn_3_7AEEC(void) {
    InMemRunnerType *pRunners = g_Runners;
    CommonBss32A94 *pBss = &lbl_3_common_bss_32A94;
    pBss->_pad6[0x1C] = (u8)-1;
    pBss->_pad6[0x21] = 0;
    if (pRunners[1].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x22] = 1;
    } else {
        pBss->_pad6[0x22] = 0;
    }
    pRunners += 2;
    if (pRunners[0].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x23] = 1;
    } else {
        pBss->_pad6[0x23] = 0;
    }
    if (pRunners[1].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x24] = 1;
    } else {
        pBss->_pad6[0x24] = 0;
    }
}

// .text:0x0007AF68 size:0x7C mapped:0x806B9FFC
void fn_3_7AF68(void) {
    InMemRunnerType *pRunners = g_Runners;
    CommonBss32A94 *pBss = &lbl_3_common_bss_32A94;
    pBss->_pad6[0x1C] = (u8)-1;
    pBss->_pad6[0x21] = 0;
    if (pRunners[1].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x22] = 1;
    } else {
        pBss->_pad6[0x22] = 0;
    }
    pRunners += 2;
    if (pRunners[0].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x23] = 1;
    } else {
        pBss->_pad6[0x23] = 0;
    }
    if (pRunners[1].runnerOnFieldOrOutOrScored != 0) {
        pBss->_pad6[0x24] = 1;
    } else {
        pBss->_pad6[0x24] = 0;
    }
}

// .text:0x0007AFE4 size:0x14C mapped:0x806BA078
void fn_3_7AFE4(void) {
    return;
}

// .text:0x0007B130 size:0x1D8 mapped:0x806BA1C4
void fn_3_7B130(void) {
    return;
}

// .text:0x0007B308 size:0x86C mapped:0x806BA39C
void fn_3_7B308(void) {
    return;
}

// .text:0x0007BB74 size:0x4C mapped:0x806BAC08
BatterStatEntry* fn_3_7BB74(void) {
    s32 fieldingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    s32 batting = g_GameLogic.teamBatting;
    s32 currentBatter = g_GameLogic.currentBatterPerTeam[fieldingTeam];
    s32 rosterSlot = g_GameLogic.battingOrderAndPositionMapping[fieldingTeam][currentBatter][0];
    return &lbl_803537E4[batting][rosterSlot];
}

// .text:0x0007BBC0 size:0x38 mapped:0x806BAC54
StatTableEntry* fn_3_7BBC0(void) {
    s32 awayTeam = g_GameLogic.awayTeamBattingInd_battingTeam;
    s32 teamFielding = g_GameLogic.teamFielding;
    s32 rosterSlot = g_GameLogic.battingOrderAndPositionMapping[awayTeam][0][0];
    return &lbl_803535C8[teamFielding][rosterSlot];
}

// .text:0x0007BBF8 size:0x14 mapped:0x806BAC8C
void fn_3_7BBF8(void) {
    g_Stats.unk39 = 1;
}

// .text:0x0007BC0C size:0x14 mapped:0x806BACA0
void fn_3_7BC0C(void) {
    g_Stats.unk39 = 1;
}

// .text:0x0007BC20 size:0x570 mapped:0x806BACB4
void fn_3_7BC20(void) {
    return;
}

// .text:0x0007C190 size:0x4 mapped:0x806BB224
void fn_3_7C190(void) {
    return;
}

// .text:0x0007C194 size:0x68 mapped:0x806BB228
s32 fn_3_7C194(void) {
    if ((s32)g_Stats.unk24 < 0x5A) {
        return 0;
    }
    if ((s32)g_Stats.unk24 > (s32)(g_Stats.unk28 - 0x3C)) {
        return 0;
    }
    return fn_3_6C938(1, 0x1100) != 0;
}

