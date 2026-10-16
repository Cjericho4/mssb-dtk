/* fn_3_F9164 NONMATCHING: only diff is the clrlslwi (1 line). */
/*
 * Needs in src/game/sta_c4.c: #include "musyx/musyx.h",
 *   extern VecXYZ lbl_3_bss_B5D8[6]; extern u8 lbl_3_bss_B620[8];
 * plus header changes in the .headers.diff (StadiumObjectElem.unkA2 carve,
 * prototype changes in sta_c4.h).
 * Shared blocker with fn_3_F9164/fn_3_F99F0: `lbl_3_data_81DC[stadium]` emits
 * `clrlslwi r0,rS,24,1` where target has plain `slwi` (u8 stadium). Making
 * stadium s32/u32 (or casting the index) removes the mask but MWCC then
 * schedules the 81DC lookup before the vol if/else -> big reorder.
 * Tried: ternary vs explicit vol/pan locals (u8/s32), decl-order brute force,
 * swapped/u16-cast fid, index casts, static inline shared body (changes
 * saved-reg count). Store order flag-first was needed for the tail.
 */
void fn_3_F9164(StadiumObjectElem* elem) {
    u8 stadium;
    s32 slot;
    s32 sfx;
    GameInitVariables* settings;
    SND_VOICEID voice;

    switch (elem->unkA2) {
    case 0:
        sfx = 2;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy;
        break;
    case 1:
        sfx = 1;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 2;
        break;
    case 2:
        sfx = 0;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 4;
        break;
    }
    settings = &g_d_GameSettings;
    stadium = settings->StadiumID;
    voice = sndFXStartEx(sfx + lbl_3_data_81DC[stadium],
                         settings->GameModeSelected == 6 ? lbl_3_data_84B8[0][sfx].vol : lbl_3_data_8404[stadium][sfx].vol,
                         0x3F, 0);
    sndFXCtrl(voice, 0x5B, settings->GameModeSelected == 6 ? lbl_3_data_84B8[0][sfx].pan : lbl_3_data_8404[stadium][sfx].pan);
    lbl_3_bss_B620[slot] = 1;
    lbl_3_bss_B5D8[slot].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_B5D8[slot].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_B5D8[slot].z = g_Ball.AtBat_Contact_BallPos.z;
}
