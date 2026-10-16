#include "game/gap_7CE90.h"
#include "game/gap_9CD90.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"

// .text:0x0007CE90 size:0xF8 mapped:0x806BBF24
void fn_3_7CE90(void) {
    if (g_Stats.unk37 == 0) {
        return;
    }
    g_Stats.unk37 = 0;
    g_Stats.unk28 = g_Stats.unk24;
    g_Stats.unk2A = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].score;
    g_Stats.unk2C = g_Scores.prevScore;
    g_Stats.unk2E = g_Scores.unkC2;
    g_Stats.unk30 = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].score;
    if (g_Ball.deadBallReason == 1) {
        g_Stats.unk2E = g_RunningLogic.unk12;
        g_Stats.unk2A = g_Scores.prevScore + g_RunningLogic.unk12;
    }
    g_Stats.unk1C = g_Ball.Hit_VerticalAngle;
    g_Stats.unk1E = g_Ball.Hit_HorizontalAngle;
    g_Stats.unk20 = g_Ball.Hit_HorizontalPower;
    g_Stats.unk0 = g_Ball.landingSpotLocation.x;
    g_Stats.unk4 = g_Ball.landingSpotLocation.z;
    g_Stats.unk8 = g_Ball.ballPickedUpCaught.x;
    g_Stats.unkC = g_Ball.ballPickedUpCaught.z;
    g_Stats.unk10 = g_Ball.deadballLastLoc.x;
    g_Stats.unk14 = g_Ball.deadballLastLoc.y;
    g_Stats.unk18 = g_Ball.deadballLastLoc.z;
}

// .text:0x0007CF88 size:0x358 mapped:0x806BC01C
void fn_3_7CF88(void) {
    return;
}

// .text:0x0007D2E0 size:0xBC mapped:0x806BC374
void fn_3_7D2E0(void) {
    InputStruct* in;
    ReplayFrame* frame;

    if ((s32)g_Stats.unk24 >= 1200) {
        g_Stats.unk28 = 1199;
        return;
    }
    in = &g_Controls[g_Stats.unk3F];
    frame = &g_ReplayLogic[g_Stats.unk24];
    frame->inputs[0].controlStickAngle = g_Controls[g_Stats.unk3F].controlStickAngle;
    frame->inputs[0].buttonInput = in->buttonInput & 0xEFFF;
    frame->inputs[0].newButtonInput = in->newButtonInput & 0xEFFF;
    frame->inputs[0].right_left = in->right_left;
    frame->inputs[0].up_down = in->up_down;
    in = &g_Controls[g_Stats.unk40];
    frame->inputs[1].controlStickAngle = g_Controls[g_Stats.unk40].controlStickAngle;
    frame->inputs[1].buttonInput = in->buttonInput & 0xEFFF;
    frame->inputs[1].newButtonInput = in->newButtonInput & 0xEFFF;
    frame->inputs[1].right_left = in->right_left;
    frame->inputs[1].up_down = in->up_down;
    g_Stats.unk24++;
}

// .text:0x0007D39C size:0xBC mapped:0x806BC430
void fn_3_7D39C(void) {
    return;
}

// .text:0x0007D458 size:0x328 mapped:0x806BC4EC
void fn_3_7D458(void) {
    return;
}

// .text:0x0007D780 size:0x1C mapped:0x806BC814
void fn_3_7D780(void) {
    g_Stats.unk36 = 0;
    g_Stats.unk37 = 0;
    g_Stats.unk38 = 0;
}

