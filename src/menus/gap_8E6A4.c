#include "menus/gap_8E6A4.h"
#include "menus/gap_1254.h"
#include "menus/gap_194BC.h"

#include "menus/gap_71EC4.h"
#include "menus/gap_D08.h"
extern void fn_8003F23C(void);
extern void fn_80021228(u8 mode);
extern u32 OSGetSoundMode(void);

extern void fn_8004A0FC(void);

// .text:0x0008E6A4 size:0x200
void fn_2_8E6A4(void) {
    return;
}

// .text:0x0008E8A4 size:0x1DC
void fn_2_8E8A4(void) {
    return;
}

// .text:0x0008EA80 size:0x2CC
void fn_2_8EA80(void) {
    return;
}

// .text:0x0008ED4C size:0x78
void fn_2_8ED4C(void) {
    g_d_GameSettings._10 = 2;
    g_d_GameSettings.home_AwaySetting = 0;
    fn_2_2FC0(9, 0, 1);
    fn_8004A0FC();
    lbl_803C5F04.unk3E = 0;
    fn_8004A0FC();
    lbl_800E8754.unk0 = 3;
    g_d_GameSettings.GameModeSelected = 4;
}

// .text:0x0008EDC4 size:0x104
void fn_2_8EDC4(void) {
    MenusExitTransition* state = &lbl_2_bss_340234;
    switch ((s32)state->step) {
    case 0:
        if (lbl_803C50E8.active == 0) {
            lbl_80366158.unk1F = 1;
            fn_8003F23C();
            state->step++;
            break;
        }
    case 1:
        if (lbl_803C50E8.active == 0) {
            s16 loading = lbl_803CC1B8->loadingState;
            if (loading != 1 && loading != 11) break;
            if (loading != 1) fn_80021228((u8)OSGetSoundMode());
            lbl_803C50E8.active = 1;
            state->step++;
            break;
        }
    case 2:
        state->step = 0;
        lbl_2_bss_340234.state = 0;
        fn_2_11A0(5);
        break;
    }
}

// .text:0x0008EEC8 size:0x22C
void fn_2_8EEC8(void) {
    return;
}
