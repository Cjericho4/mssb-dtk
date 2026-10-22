// Best attempt (24 sbs lines, from a stub): saturating counters, pos history copy, vel.y -= gravity, fn_3_DBD0, pos += vel, ground bounce with lbl_3_data_4388[StadiumID] (BounceParams, 0x14 stride: drag@4, bounceFactorFast@C, bounceFactorSlow@10). Left: second g_Ball base r6 vs r7, StadiumID index temp regs, and the 0.5/0.01 constant load scheduling. Needs `#include "game/rep_540.h"`, extern lbl_3_rodata_1254 and the BounceParams typedef/extern in rep_1200.c.
void fn_3_6FA28(void) {
    BounceParams* bp;
    f32 velY;

    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter++;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
    g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
    g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.physicsSubstruct.velocity.y = g_Ball.physicsSubstruct.velocity.y - g_Ball.physicsSubstruct.gravity;
    fn_3_DBD0();
    g_Ball.AtBat_Contact_BallPos.x += g_Ball.physicsSubstruct.velocity.x;
    g_Ball.AtBat_Contact_BallPos.y += g_Ball.physicsSubstruct.velocity.y;
    g_Ball.AtBat_Contact_BallPos.z += g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
        bp = &lbl_3_data_4388[g_d_GameSettings.StadiumID];
        velY = g_Ball.physicsSubstruct.velocity.y;
        g_Ball.physicsSubstruct.velocity.y = velY * (bp->drag - velY * lbl_3_rodata_1250);
        g_Ball.physicsSubstruct.velocity.y = -g_Ball.physicsSubstruct.velocity.y;
        if (g_Ball.physicsSubstruct.velocity.y < 0.01f) {
            g_Ball.physicsSubstruct.velocity.x *= bp->bounceFactorSlow;
            g_Ball.physicsSubstruct.velocity.z *= bp->bounceFactorSlow;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= bp->bounceFactorFast;
            g_Ball.physicsSubstruct.velocity.z *= bp->bounceFactorFast;
        }
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.groundYForBounces;
    }
}
