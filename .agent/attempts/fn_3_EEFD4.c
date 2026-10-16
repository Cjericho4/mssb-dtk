/* fn_3_EEFD4 NONMATCHING (sta_c5.c). Only diff: acos result frsp is scheduled late and `ang` is
 * allocated to f1 instead of f2 (target: bl acos; frsp f2,f1; lfs f1,dir.z ...). Everything else matches.
 * Needs: helper fn_3_EF890_resetElems moved above this fn, #include "game/game_batter.h" (lbl_800E8754),
 * local prototype of fn_3_CB7E8 (rep_23E8.h conflicts), header changes in fn_3_EEFD4.headers.diff
 * (prototype takes s32 idx; StadiumObjectElem f32 unkBC carved at 0xBC). Full diff: fn_3_EEFD4.src.diff.
 * Tried: (f32) cast or not, ternary, both-branch stores, writing obj->unkB8 directly, inline angle helper,
 * dot temp, ang decl order, store order, double literal f suffix. Key prologue fix: obj declared first. */
void fn_3_EEFD4(s32 idx) {
    StadiumObjectElem* obj = &lbl_3_common_bss_350E4[0].src[idx];
    Vec dir;
    Vec axis = {1.0f, 0.0f, 0.0f};
    Vec pos;
    f32 ang;
    s32 stadium;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (obj->unkC6 >= 3) {
        return;
    }
    dir.x = g_Ball.physicsSubstruct.velocity.x;
    dir.y = 0.0f;
    dir.z = g_Ball.physicsSubstruct.velocity.z;
    PSVECNormalize(&dir, &dir);
    ang = acos(PSVECDotProduct(&axis, &dir));
    if (dir.z < 0.0f) {
        ang = 6.283185258507729 - ang;
    }
    obj->unkB8 = ang;
    obj->unkBC = 0.5f;
    obj->unkC6 = 4;
    fn_3_EF890_resetElems((OuterStruct_F13F8*)obj);
    if (g_Ball.AtBat_ContactResult != 2 && lbl_800E8754[4] != 0) {
        CTRLGetTranslation(&obj->control, &pos.x, &pos.y, &pos.z);
        fn_3_CB7E8(pos.x, pos.y - 5.0f, pos.z);
        obj->unkC8 = 1;
    }
    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[0][9].vol;
    } else {
        vol = lbl_3_data_8404[stadium][9].vol;
    }
    vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 9, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        pan = lbl_3_data_84B8[0][9].pan;
    } else {
        pan = lbl_3_data_8404[stadium][9].pan;
    }
    sndFXCtrl(vid, 0x5B, pan);
    fn_3_27648();
    g_FieldingLogic.unk_13B = 1;
}
