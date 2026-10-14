#include "game/gap_759BC.h"

#include "game/UnknownHomes_Game.h"
#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"
#include "game/gap_1658F0.h"

void fn_3_161588(s32 event, s16 rosterID);

typedef struct {
    u8 _pad[0xa0];
    s8 charIDs[0x32];
    u8 _pad2[0x36];
} Lbl80353A90Struct; // size: 0x108

extern Lbl80353A90Struct lbl_80353A90;

// .text:0x000759BC size:0x7B8
void fn_3_759BC(void) {
    return;
}

// .text:0x00076174 size:0x3E4
void fn_3_76174(void) {
    return;
}

// .text:0x00076558 size:0x544
void fn_3_76558(void) {
    return;
}

// .text:0x00076A9C size:0x1DC
void fn_3_76A9C(void) {
    InMemRunnerType* runner;
    u8* stat;
    s32 runs;
    s32 i;

    runner = &g_Runners[1];
    for (i = 1; i < 4; i++, runner++) {
        if ((runner->runnerOnFieldOrOutOrScored == 1 || runner->runnerOnFieldOrOutOrScored == 3)
            && i != runner->currentBase
            && (g_FieldingLogic._107 != 3 || runner->furthestBaseForcedToGoToOnWalk != 0)
            && runner->forceOutCd <= 0) {
            stat = &lbl_803537E4[g_GameLogic.teamBatting][runner->rosterID].basesStolen;
            if (*stat < 0xFE) {
                (*stat)++;
            } else {
                *stat = 0xFF;
            }
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.playerIndex == g_GameLogic.teamBatting) {
                fn_3_161588(10, runner->rosterID);
            }
        }
    }
    runs = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score - g_Scores.prevScore;
    runner = &g_Runners[3];
    for (i = 3; i >= 0; i--, runner--) {
        if (runs <= 0) {
            break;
        }
        if (runner->runnerOnFieldOrOutOrScored == 3) {
            stat = &lbl_803537E4[g_GameLogic.teamBatting][runner->rosterID].runsScored;
            if (*stat < 0xFE) {
                (*stat)++;
            } else {
                *stat = 0xFF;
            }
            runs--;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.teamBatting == lbl_3_common_bss_37400.playerIndex) {
                fn_3_161588(11, runner->rosterID);
            }
        }
    }
}

// .text:0x00076C78 size:0x90
void fn_3_76C78(void) {
    s32 i;
    for (i = 0; i < 0x32; i++) {
        if (lbl_80353A90.charIDs[i] == -1) {
            if (g_GameLogic.teamBatting == 0) {
                lbl_80353A90.charIDs[i] = g_Batter.rosterID;
                return;
            }
            lbl_80353A90.charIDs[i] = (s8)g_Batter.rosterID + 9;
            return;
        }
    }
}

// .text:0x00076D08 size:0xC0C
void fn_3_76D08(void) {
    return;
}
