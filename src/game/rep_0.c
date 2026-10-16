#include "game/rep_0.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    u8 unk0;    /* 0x0 */
    u8 unk1;    /* 0x1 */
    u8 unk2;    /* 0x2 */
    u8 state;   /* 0x3 */
    u8 _pad4[4];
} Rep0Bss10;

typedef struct {
    u8 _pad0[4];
    u16 buttons; /* 0x4 */
    u8 _pad6[0xA];
} PadStatus_803C77B8;

extern Rep0Bss10 lbl_3_bss_10;
extern PadStatus_803C77B8 lbl_803C77B8[];

// .text:0x00000000 size:0x258
void maybeProcessTeamData(void) {
    return;
}

// .text:0x00000258 size:0x20C
void fn_3_258(void) {
    u16 btn;

    if (lbl_3_bss_10.state == 0) {
        btn = lbl_803C77B8[0].buttons;
        if (btn & 8) {
            if (lbl_3_bss_10.unk1 != 0) {
                lbl_3_bss_10.unk1--;
            }
        }
        if (btn & 4) {
            if (lbl_3_bss_10.unk1 < 1) {
                lbl_3_bss_10.unk1++;
            }
        }
        if (btn & 0x100) {
            lbl_3_bss_10.state = 1;
        }
    } else if (lbl_3_bss_10.state == 1 && lbl_3_bss_10.unk1 == 0) {
        btn = lbl_803C77B8[0].buttons;
        if (btn & 8) {
            if (lbl_3_bss_10.unk2 != 0) {
                lbl_3_bss_10.unk2--;
            }
        }
        if (btn & 4) {
            if (lbl_3_bss_10.unk2 < 3) {
                lbl_3_bss_10.unk2++;
            }
        }
        if (btn & 0x100) {
            lbl_3_bss_10.state = 3;
        }
        if (btn & 0x200) {
            lbl_3_bss_10.state = 0;
        }
    } else if (lbl_3_bss_10.state == 1 && lbl_3_bss_10.unk1 == 1) {
        g_d_GameSettings.GameModeSelected = 2;
        lbl_803CC1B8->unk_00 = maybeProcessTeamData;
    } else if (lbl_3_bss_10.state == 2) {
    } else if (lbl_3_bss_10.state == 3) {
        btn = lbl_803C77B8[0].buttons;
        if (btn & 1) {
            if (g_d_GameSettings.StadiumID != 0) {
                g_d_GameSettings.StadiumID--;
            }
        }
        if (btn & 2) {
            if (g_d_GameSettings.StadiumID < 10) {
                g_d_GameSettings.StadiumID++;
            }
        }
        if (btn & 0x100) {
            lbl_3_bss_10.state = 4;
        }
        if (btn & 0x200) {
            lbl_3_bss_10.state = 1;
        }
    } else if (lbl_3_bss_10.state == 4) {
        g_d_GameSettings.GameModeSelected = 0;
        g_d_GameSettings._10 = lbl_3_bss_10.unk2;
        lbl_803CC1B8->unk_00 = maybeProcessTeamData;
    }
}
