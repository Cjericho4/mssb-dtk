// 10 diff lines remain: floating-point register allocation after getComponentsFromRad.
#include "game/rep_1200.h"
#include "game/rep_1838.h"
#include "game/UnknownHomes_Game.h"
extern u8 lbl_3_data_5F50[][5];
void fn_3_709B4(void) {
    f32 angle;
    f32 radius;
    f32 sine;
    f32 cosine;
    InMemPitcherType* pitcher = &g_Pitcher;
    pitcher->bulletPitchFrameCounter++;
    if (pitcher->bulletPitchFrameCounter >= pitcher->bulletPitchLoopFrames) {
        pitcher->bulletPitchStageCode = 2;
    } else {
        angle = (f32)g_Pitcher.bulletPitchFrameCounter / (f32)g_Pitcher.bulletPitchLoopFrames;
        angle *= 6.2831855f;
        angle += 3.1415927f;
        getComponentsFromRad(angle, &sine, &cosine);
        radius = 0.01f * lbl_3_data_5F50[g_Pitcher.starPitchType - 7][4];
        g_Pitcher.starPitchPositionAdjustment.x = 0.0f;
        g_Pitcher.bulletPitchLoopAngleRadians = angle;
        g_Pitcher.starPitchPositionAdjustment.y = sine * radius + radius;
        g_Pitcher.starPitchPositionAdjustment.z = cosine * radius;
    }
}
