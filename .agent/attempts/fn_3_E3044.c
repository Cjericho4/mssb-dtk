/* fn_3_E3044 (rep_2998.c) NONMATCHING best attempt (2 diffs).
 * Remaining: (1) target schedules `lbz r0,0xcb(r3)` before `mr r31,r3`; (2) deg->rad load order:
 * target loads launchAngle into f1 then the 0.017453292f const into f0 (fmuls f31,f0,f1); MWCC here
 * gives field f0 / const f1. Tried: operand swap, Control* param, inline deg2rad, switch, s32 local,
 * block-scope ang, extern rodata const, `ang = field; ang *= k`.
 * Needs fn_3_E3044.headers.diff (CastleRotObj: anim@0x74, animTime/launchAngle/rotSpeed@0xB8-0xC0,
 * unkCA/unkCB appended; prototype void fn_3_E3044(struct CastleRotObj*)).
 */
void fn_3_E3044(CastleRotObj* obj) {
    f32 speed = obj->anim->speed;
    f32 ang;
    f32 x;
    f32 z;
    f32 t;
    u32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if ((s32)obj->unkCB == 7) {
        obj->curRotation += obj->rotSpeed;
        CTRLSetRotation(&obj->control, 0.0f, obj->curRotation, 0.0f);
        return;
    }
    if (obj->animTime >= 20.0 && obj->animTime - speed < 20.0) {
        ang = 0.017453292f * obj->launchAngle;
        t = sin(ang);
        x = obj->pos.x + obj->scale * (5.0 * t);
        t = cos(ang);
        z = obj->pos.z + obj->scale * (-5.0 * t);
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = 2.0 * obj->scale;
        g_Ball.AtBat_Contact_BallPos.z = z;
        t = sin(ang);
        g_Ball.physicsSubstruct.velocity.x = 0.1 * t;
        g_Ball.physicsSubstruct.velocity.y = 0.0f;
        t = cos(ang);
        g_Ball.physicsSubstruct.velocity.z = 0.1 * -t;
        fn_3_65F4();
        obj->unkCA = 0;
        stadium = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0][1].vol;
        } else {
            vol = lbl_3_data_8404[stadium][1].vol;
        }
        vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 1, vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            pan = lbl_3_data_84B8[0][1].pan;
        } else {
            pan = lbl_3_data_8404[stadium][1].pan;
        }
        sndFXCtrl(vid, 0x5B, pan);
    }
}
