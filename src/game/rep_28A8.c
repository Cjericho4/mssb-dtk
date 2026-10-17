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
#include "musyx/musyx.h"
#include "game/gap_E587C.h"

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
    g_Minigame.toyFieldBallStateResult2 = g_Minigame.toyFieldBallStateResult;
    if (fn_3_E5924() != 0) {
        if (g_Minigame._19CF == 0) {
            g_Minigame.toyFieldBallStateResult2 = 0xC;
        }
        if (g_Minigame._19CF > 0x3CU) {
            g_Minigame._19CE = 1;
            return;
        }
        if (g_Minigame._19CF < 0xFEU) {
            g_Minigame._19CF += 1;
            return;
        }
        g_Minigame._19CF = 0xFF;
        return;
    }
    if ((g_Minigame.toyFieldBallStateResult2 == 2) || (g_Ball.maybebuntOn2Strikes != 0)) {
        if (g_Ball.maybebuntOn2Strikes == 0) {
            fn_3_59918(1, 0);
        }
        g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
        if ((s16) g_Ball.fielderWBallIndex >= 0) {
            g_Minigame._19C6 = g_Fielders[g_Ball.fielderWBallIndex].unk20D;
        }
    } else {
        if (g_Minigame.toyFieldBallStateResult2 == 1) {
            fn_3_A0F0();
        } else if (g_Minigame.toyFieldBallStateResult2 == 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void fn_3_DC380(void) {
    return;
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_5B408(void);
s32 fn_3_6C938(s32 arg0, s32 arg1);

void fn_3_DC5A4(void) {
    s32 ret;

    if ((ret = fn_3_6C938(1, 0x100)) != 0) {
        lbl_3_common_bss_34C90.field_0x00 = ret - 1;
        if ((s32)lbl_3_common_bss_34C90.field_0x1DA == 2) {
            fn_3_5B408();
            lbl_3_common_bss_34C90.field_0x1D2 = 9;
        } else {
            lbl_3_common_bss_34C90.field_0x1D2 = 4;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
    } else if (fn_3_6C938(1, 8) != 0) {
        if ((s8)lbl_3_common_bss_34C90.field_0x1DA != 0) {
            lbl_3_common_bss_34C90.field_0x1DA--;
        } else {
            lbl_3_common_bss_34C90.field_0x1DA = 2;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    } else if (fn_3_6C938(1, 4) != 0) {
        lbl_3_common_bss_34C90.field_0x1DA++;
        if ((s8)lbl_3_common_bss_34C90.field_0x1DA >= 3) {
            lbl_3_common_bss_34C90.field_0x1DA = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    }
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    return;
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    Bss34C90Item* b = &lbl_3_common_bss_34C90;

    if (b->field_0x06 & 0x1000) {
        b->field_0x1D2 = 4;
        sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
    } else if (b->field_0x06 & 0x100) {
        if (b->field_0x1DA_s8 == 0) {
            b->field_0x1D2 = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        } else if (b->field_0x1DA_s8 == 1) {
            b->field_0x1D2 = 8;
            b->field_0x1D4 = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        } else if (b->field_0x1DA_s8 == 2) {
            b->field_0x1D2 = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        } else if (b->field_0x1DA_s8 == 3) {
            fn_3_5B408();
            lbl_3_common_bss_34C90.field_0x1D2 = 9;
            sndFXStartEx(0x1B8, lbl_800EFBA4.confirmVolume, 0x3F, 0);
        }
    } else if (b->field_0x06 & 0x200) {
        if ((s8)b->field_0x1DA != 0) {
            b->field_0x1DA = 0;
        } else {
            b->field_0x1D2 = 4;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4.alertVolume, 0x3F, 0);
    } else if (b->field_0x08 & 8) {
        if ((s8)b->field_0x1DA > 0) {
            b->field_0x1DA--;
        } else {
            b->field_0x1DA = 3;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    } else if (b->field_0x08 & 4) {
        b->field_0x1DA++;
        if ((s8)b->field_0x1DA >= 4) {
            b->field_0x1DA = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4.menuVolume, 0x3F, 0);
    }
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
    GameControlsStruct* gl = &g_GameLogic;

    switch (gl->_125) {
    case 0:
        changeScene(1, 6);
        gl->_125 = 1;
        break;
    case 1:
        if (gl->FrameCountOfCurrentPitch > 1800) {
            gl->_125 = 2;
            gl->FrameCountOfCurrentAtBat_Copy = 0;
        } else if (gl->FrameCountOfCurrentPitch > 300 && fn_3_6C938(1, 0x1100) != 0) {
            gl->_125 = 2;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 2:
        if (gl->FrameCountOfCurrentAtBat_Copy > 30) {
            if (g_Minigame._190A != 0) {
                gl->_125 = 4;
            } else {
                gl->_125 = 3;
            }
        }
        break;
    case 3:
        lbl_3_common_bss_34C90.field_0x1D1 = 0;
        lbl_3_common_bss_34C90.field_0x1D2 = 0;
        fn_3_5A6D4(0x22);
        break;
    case 4:
        changeScene(4, 6);
        if (lbl_8037169C._13 != 0) {
            gl->_125 = 10;
        }
        break;
    case 5:
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            g_d_GameSettings._38 = 0;
        } else {
            g_d_GameSettings._38 = g_Minigame.players._18E8[g_d_GameSettings._35];
        }
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
int fn_3_9EE24(int max);
extern s16 lbl_3_data_18C48[];

static inline BOOL fn_3_DD1A8_done(GameControlsStruct* gl) {
    BOOL done = FALSE;
    if (gl->FrameCountOfCurrentPitch >= lbl_3_data_18C48[2]) {
        done = TRUE;
    } else if (gl->FrameCountOfCurrentAtBat_Copy >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100)) {
        done = TRUE;
    }
    return done;
}

void fn_3_DD1A8(void) {
    GameControlsStruct* gl = &g_GameLogic;
    s32 i;

    switch (gl->_125) {
    case 0:
        if (g_Minigame.toyField_turnNumber == 0) {
            if (fn_3_9EE24(100) < lbl_3_data_18C48[7] || g_Minigame._1907 == 4) {
                i = 0;
                do {
                    g_Minigame.rosterID = fn_3_9EE24(4);
                    i++;
                    if (i >= 100) {
                        break;
                    }
                } while (g_Minigame.players.battingHandedness[g_Minigame.rosterID] != 0);
            } else {
                i = 0;
                do {
                    g_Minigame.rosterID = fn_3_9EE24(4);
                    i++;
                    if (i >= 100) {
                        break;
                    }
                } while (g_Minigame.players.battingHandedness[g_Minigame.rosterID] == 0);
            }
        }
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 1;
        break;
    case 1:
        if (fn_3_DD1A8_done(gl)) {
            gl->_125 = 2;
            changeScene(3, 6);
        }
        break;
    case 2:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(7);
        }
        break;
    }
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

typedef struct {
    s16 initialCountdown;
    s16 minimumCountdown;
    s16 _4;
    s16 _6;
} ToyFieldCountdownParams;
extern ToyFieldCountdownParams lbl_3_data_1899C;

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void fn_3_DDD60(void) {
    s16 selectedTurns;
    s16 turnNumber;

    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C.initialCountdown;
    }
    g_GameLogic.CountdownUntilFade--;
    if (g_Minigame._19A0 != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C.minimumCountdown) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C.minimumCountdown;
    }
    if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C.minimumCountdown - 10) {
        turnNumber = g_Minigame.toyField_turnNumber;
        selectedTurns = g_Minigame.toyField_selectedTurns;
        if (turnNumber >= selectedTurns &&
            g_Minigame.players._18E8[(s8)g_Minigame.rosterID] == 1) {
            fn_3_59918(0xD, 0);
        } else if ((u8)g_Minigame.rosterID != (s8)g_Minigame._19C6) {
            if (turnNumber >= selectedTurns) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
    }
    if (g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
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
            return;
        }
        fn_3_5A6D4(8);
    }
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
    s32 i;
    s32 j;
    s16 score;
    s32 rank;

    for (i = 0; i < 4; i++) {
        g_Minigame.players._18E8[i] = 0;
        g_Minigame.players._18EC[i] = 0;
    }
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        score = g_Minigame.miniGameCurrentPoints[i];
        rank = 1;
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.miniGameCurrentPoints[j] > score) {
                rank++;
            }
        }
        g_Minigame.players._18E8[i] = rank;
        g_Minigame.players._18EC[i] = rank;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.players._18E8[i] > 1) {
            break;
        }
    }
    if (i >= 4 && g_Minigame.miniGameNumberOfParticipants > 1) {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = 1;
    } else {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = 0;
    }
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4
void fn_3_DE610(void) {
    g_Minigame.panelHitInd = 0;
    if (g_Minigame._19A6 != 0) {
        g_Minigame._19A6--;
        if (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) {
            g_Minigame._19A6 = 3;
        }
    }
    g_Strikes.outs = 0;
    g_Strikes.unk_C = 0;
    g_Minigame._19A5 = 1;
    if ((((s8) (u8) g_Minigame.rosterID != (s8) g_Minigame._19C6) || ((u8) g_Minigame.players._18E8[(s8)g_Minigame.rosterID] == 1)) && ((s16) g_Minigame.toyField_turnNumber >= (s16) g_Minigame.toyField_selectedTurns)) {
        lbl_3_common_bss_34C90.field_0x1D2 = 0;
        fn_3_5A6D4(0xEU);
        return;
    }
    if (((s16) g_Minigame.toyField_turnNumber < (s16) g_Minigame.toyField_selectedTurns) && ((g_Minigame.toyField_turnNumber % 10) == 0)) {
        fn_3_5A6D4(3U);
        return;
    }
    fn_3_5A6D4(7U);
}

// .text:0x000DE744 size:0x44C mapped:0x8071D7D8
void fn_3_DE744(void) {
    return;
}
