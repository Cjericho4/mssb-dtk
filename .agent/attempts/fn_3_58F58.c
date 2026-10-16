/* fn_3_58F58 NONMATCHING (4 diff lines): only the final 4554 table lookup has swapped scratch regs
   (target: mulli r6,idx,0x18 / slwi r7,col,3; ours: mulli r7 / slwi r6). Tried: row/elem pointers, flat [12],
   3D f32 array, row struct, col/alt/flag/status types, if/else tail, decl+init order brute force.
   Needs: FieldingLogic.unk11E (u8 @0x11E) carved in UnknownHomes_Game.h; rep_AC8.h prototype
   void fn_3_58F58(s32 idx, f32* x, f32* z); and the extern tables below. */

extern UnknownStructB7 lbl_3_data_450C[9];
extern UnknownStructB7 lbl_3_data_4554[4][3];
extern UnknownStructB7 lbl_3_data_45B4[4];
extern UnknownStructB7 lbl_3_data_45D4[4];

void fn_3_58F58(s32 idx, f32* x, f32* z) {
    s32 flag = 0;
    s32 col;
    s32 alt = (g_Pitcher.pitchTotalTimeCounter <= 0) ? 1 : 2;
    u8 status;

    if (idx <= 1) {
        *x = lbl_3_data_450C[idx].x;
        *z = lbl_3_data_450C[idx].z;
        return;
    }
    if (idx <= 5) {
        status = g_Runners[1].runnerOnFieldOrOutOrScored;
        if (status != 0 && g_Runners[1].furthestBaseForcedToGoToOnWalk != 0 && g_Ball.pitchHangtimeCounter > 0 &&
            g_Pitcher.framesUntilUnhittable < 0xF) {

            if (g_Batter.batterHand == 0 && idx == 3) {
                *x = lbl_3_data_4444[2].x;
                *z = lbl_3_data_4444[2].z;
                return;
            }
            if (g_Batter.batterHand != 0 && idx == 5) {
                *x = lbl_3_data_4444[2].x;
                *z = lbl_3_data_4444[2].z;
                return;
            }
        }
        col = 0;
        if (g_Pitcher.pitchTotalTimeCounter > 30 && (idx == 2 || idx == 4) && g_Batter.buntStatus >= 1 && g_Batter.buntStatus <= 3) {
            flag = 1;
        }
        if ((idx == 2 && status == 1) || (idx == 4 && g_Runners[3].runnerOnFieldOrOutOrScored == 1)) {
            col = alt;
        }
        if (g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
            if (idx == 3 && g_Batter.batterHand == 0) {
                col = alt;
                g_FieldingLogic.unk11E = 0;
            }
            if (idx == 5 && g_Batter.batterHand == 1) {
                col = alt;
                g_FieldingLogic.unk11E = 1;
            }
        }
        if (flag != 0) {
            *x = lbl_3_data_45B4[idx - 2].x;
            *z = lbl_3_data_45B4[idx - 2].z;
            return;
        }
        *x = lbl_3_data_4554[idx - 2][col].x;
        *z = lbl_3_data_4554[idx - 2][col].z;
        return;
    }
    *x = lbl_3_data_45D4[idx - 6].x;
    *z = lbl_3_data_45D4[idx - 6].z;
}
