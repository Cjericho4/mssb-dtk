/* fn_3_16D5E4 (src/game/rep_4090.c) NONMATCHING (register allocation only).
 * rep_4090.c also needs: #include "UnknownHeaders.h", "game/particle_spawn.h", "stl/mem.h";
 * u8 fn_800527C4(Vec* pos); fn_3_16CC2C(Vec* pos, s32 idx).
 * Logic, float regs, branch layout match. Remaining: GPR assignment - target keeps
 * idx param in r30, (u8)(idx-1) in r29, fielder ptr in r31; ours idx r31, slot r30,
 * fielder r29 (and scratch regs in the VecXYZ {0,0,0} initializer copy). Brute-forced
 * local declaration order and the slot/anim/fielder statement order without effect.
 * Header changes needed: see fn_3_16D5E4.headers.diff (rep_4090.h prototypes, Ball
 * union for 0x1B48 as s32). */
void fn_3_16D5E4(s32 idx) {
    f32 y0;
    f32 thresh;
    Vec out;
    Fielder* fielder;
    u8 slot;
    AnimationStruct* anim;
    u8 visible;
    f32 mag;

    if (g_d_GameSettings.StadiumID == 4) {
        thresh = 1.5f;
    } else {
        thresh = 0.07f;
    }
    if ((u8)idx != 0) {
        VecXYZ pos = {0.0f, 0.0f, 0.0f};

        slot = (u8)idx - 1;
        anim = g_hugeAnimStruct.AnimationStructPtrs[slot];
        fielder = &g_Fielders[(u8)idx - 1];
        if (anim->unk276 & 6) {
            visible = TRUE;
        } else {
            fn_8001B728(slot, 0x23, &pos);
            y0 = -pos.y;
            pos.x = pos.y = pos.z = 0.0f;
            fn_8001B728(slot, 0x1F, &pos);
            if ((thresh >= y0) | (thresh >= -pos.y)) {
                visible = TRUE;
            } else {
                visible = FALSE;
            }
        }
        if (!visible || fielder->unk50 < 0.1f) {
            return;
        }
        memcpy(&out, fielder->pos, sizeof(Vec));
        out.y = thresh;
    } else {
        mag = PSVECMag((Vec*)&g_Ball.physicsSubstruct.velocity);
        if (!(g_Ball.AtBat_Contact_BallPos.y <= thresh)) {
            return;
        }
        if ((g_Ball.maybeCollisionRelated_s32 & 0x7F) == 9 && !(g_Ball.pastCoordinates[0].y > thresh)) {
            return;
        }
        if (mag >= 0.05) {
            memcpy(&out, &g_Ball.AtBat_Contact_BallPos, sizeof(Vec));
            goto check;
        }
        return;
    }
check:
    if (fn_800527C4(&out)) {
        fn_3_16CC2C(&out, idx);
    }
}
