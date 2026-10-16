#include "game/rep_1B70.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"

// .text:0x000B3A4C size:0x124 mapped:0x806F2AE0
void fn_3_B3A4C(void) {
    s32 i;

    g_GameLogic.hudElementLoadingInd = 1;
    g_Practice.instructionNumber = -1;
    g_Practice._1C7 = 0;
    g_Practice.guidedPracticeCompletionRelated = 0;
    g_Practice.guidedPracticeCounter = 0;
    g_Practice._186 = 0;
    g_Practice.frames_sinceMovedToFromMenu = 0;
    g_Practice.practiceState = 0;
    g_Practice.tutorialState = 3;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
    for (i = 0; i < 2; i++) {
        g_GameLogic._13E[i] = 0;
        g_GameLogic._140[i] = 0;
        g_GameLogic.batterHandedness[i] = 0;
        g_GameLogic.teamAIInd[i] = 0;
        g_GameLogic.autoFielding[i] = 0;
        g_GameLogic.battingAIInd[i] = 0;
    }
    switch (g_Practice.practiceType_2) {
    case 1:
        g_Practice.aIEnabled = 1;
        g_GameLogic._140[1] = 1;
        g_GameLogic._140[0] = 1;
        break;
    case 2:
        g_Practice.aIEnabled = 1;
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic._140[1] = 1;
        g_GameLogic._140[0] = 1;
        g_GameLogic.batterHandedness[1] = 1;
        g_GameLogic.batterHandedness[0] = 1;
        g_GameLogic.battingAIInd[1] = 1;
        g_GameLogic.battingAIInd[0] = 1;
        break;
    case 4:
        if (g_Practice.practiceLevel == 4) {
            g_Practice.aIEnabled = 1;
            g_Practice.practiceBatterHandedness = 0;
            g_Practice.aIEnabled = 1;
            g_GameLogic._140[1] = 1;
            g_GameLogic._140[0] = 1;
        } else if (g_Practice.practiceLevel == 5) {
            g_Practice.aIEnabled = 0;
            g_Practice.practiceBatterHandedness = 1;
        }
        break;
    }
    g_Pitcher.pitcher.x = 0.0f;
}

