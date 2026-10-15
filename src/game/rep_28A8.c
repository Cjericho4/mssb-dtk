#include "game/rep_28A8.h"
#include "game/gap_AC9F8.h"
#include "game/rep_AC8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1188.h"
#include "game/rep_540.h"
#include "game/rep_1200.h"
#include "game/game_batter.h"
#include "game/rep_868.h"

extern void Set_803cb848(s32 arg0);
extern void fn_3_BF158(void);
extern void fn_3_BF1AC(void);

extern u8 lbl_803CBC3C;

// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
void fn_3_D9EA0(void) {
    return;
}

// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
void fn_3_DA640(void) {
    return;
}

// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
void fn_3_DA834(void) {
    return;
}

// .text:0x000DC240 size:0x140 mapped:0x8071B2D4
void fn_3_DC240(void) {
    return;
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void fn_3_DC380(void) {
    return;
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_DC5A4(void) {
    return;
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    return;
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    return;
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void fn_3_DCC80(void) {
    return;
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void fn_3_DCED0(void) {
    if (lbl_3_common_bss_34C90.field_0x0C < 0x7FFE) {
        lbl_3_common_bss_34C90.field_0x0C++;
    } else {
        lbl_3_common_bss_34C90.field_0x0C = 0x7FFF;
    }

    lbl_803CBC3C = 1;
    if (lbl_3_common_bss_34C90.field_0x0C > 0x3C) {
        fn_3_AFD80(1);
        fn_3_5A6D4(0xB);
        return;
    }

    fn_3_2EA24();
}

// .text:0x000DCF44 size:0xBC mapped:0x8071BFD8
void fn_3_DCF44(void) {
    s32 i;

    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (g_Minigame.players.characterIndex[i] >= 0 && g_Minigame.players.battingHandedness[i] == 0 &&
            (g_Controls[g_Minigame.players.characterIndex[i]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90.field_0x1D5 = 1;
            lbl_3_common_bss_34C90.field_0x00 = g_Minigame.players.characterIndex[i];
            fn_3_AFD80(0);
            fn_3_59918(0xE, 0);
            break;
        }
    }
}

// .text:0x000DD000 size:0x1A8 mapped:0x8071C094
void fn_3_DD000(void) {
    return;
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
void fn_3_DD1A8(void) {
    return;
}

// .text:0x000DD37C size:0x80 mapped:0x8071C410
void fn_3_DD37C(void) {
    if (g_Minigame._19CE != 0) {
        fn_3_FBD70();
        fn_3_FBD58();
    }
    
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    
    fn_3_1DD48();
    
    if (g_Minigame.pointsTargetReachedInd == 0) {
        fn_3_2E87C();
        fn_3_5A6D4(0);
    } else {
        fn_3_5A6D4(8);
    }
}

// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
void fn_3_DD3FC(void) {
    return;
}

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void fn_3_DD9A4(void) {
    return;
}

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void fn_3_DDD60(void) {
    return;
}

// .text:0x000DDF1C size:0x84 mapped:0x8071CFB0
void fn_3_DDF1C(void) {
    fn_3_6EBB4(g_Minigame.minigamePlayerSelectedOrder);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_58870();
    fn_3_1DEB8();
    fn_3_BF1AC();
    Set_803cb848(1);
    fn_3_BF158();
    g_FieldingLogic.unkAE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    g_UnkSimulation_31AC0.unk5 = 0;
    g_UnkSimulation_31AC0.unk6 = 4;
}

// .text:0x000DDFA0 size:0x368 mapped:0x8071D034
void fn_3_DDFA0(void) {
    return;
}

// .text:0x000DE308 size:0x1F4 mapped:0x8071D39C
void fn_3_DE308(void) {
    return;
}

// .text:0x000DE4FC size:0x114 mapped:0x8071D590
void fn_3_DE4FC(void) {
    return;
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4
void fn_3_DE610(void) {
    return;
}

// .text:0x000DE744 size:0x44C mapped:0x8071D7D8
void fn_3_DE744(void) {
    return;
}
