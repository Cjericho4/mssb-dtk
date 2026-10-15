#include "game/gap_16C410.h"
#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"

// .text:0x0016C410 size:0x138
void fn_3_16C410(u8 arg0) {
    s32 stadium;
    s32 sfx;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;

    if (arg0) {
        if (g_d_GameSettings.StadiumID == 4) {
            sfx = 5;
        } else {
            sfx = 14;
        }
    } else {
        if (g_d_GameSettings.StadiumID == 4) {
            sfx = 4;
        } else {
            sfx = 13;
        }
    }
    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.StadiumID == 4) {
        if (g_d_GameSettings.GameModeSelected == 6) {
            vol = lbl_3_data_84B8[0][sfx].vol;
        } else {
            vol = lbl_3_data_8404[stadium][sfx].vol;
        }
        vid = sndFXStartEx(lbl_3_data_81DC[stadium] + sfx, vol, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            pan = lbl_3_data_84B8[0][sfx].pan;
        } else {
            pan = lbl_3_data_8404[stadium][sfx].pan;
        }
        sndFXCtrl(vid, 0x5B, pan);
    }
}
