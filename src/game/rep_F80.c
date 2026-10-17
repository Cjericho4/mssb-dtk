#include "game/rep_F80.h"
#include "game/rep_1E08.h"
#include "game/rep_E08.h"
#include "header_rep_data.h"
#include "game/rep_2308.h"
#include "game/auto_00_000CB344_text.h"
#include "game/rep_540.h"

// .text:0x0006A2A4 size:0x5C mapped:0x806A9338
void fn_3_6A2A4(s8 arg1) {
    ActRelatedSub *sub = &g_hugeAnimStruct.actRelatedPtr[arg1 - 0x1f].sub;
    lbl_3_common_bss_32724.someFlag = 1;
    sub->flag5b = 2;
    (sub + 1)->prevFloat = 0.0f;
    sub->flag59 = 1;
    sub->float54 = 1.0f;
    sub->flag5a = 1;
}

// .text:0x0006A300 size:0x100 mapped:0x806A9394
void fn_3_6A300(void) {
    AnimationStruct* anim;
    StadiumObjEntry* entry;

    if (lbl_3_common_bss_32724.someFlag == 0) {
        return;
    }
    anim = g_hugeAnimStruct.AnimationStructPtrs[9];
    if (g_d_GameSettings.GameModeSelected == 6) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[g_Minigame.rosterID];
    }
    if (anim->unk252 == 0x30) {
        entry = &g_hugeAnimStruct.starAnimRelated[17];
    } else if (anim->unk252 == 0x31) {
        entry = &g_hugeAnimStruct.starAnimRelated[18];
    } else if (anim->unk252 == 0x32) {
        entry = &g_hugeAnimStruct.starAnimRelated[19];
    } else {
        entry = &g_hugeAnimStruct.starAnimRelated[20];
    }
    entry->visible = 1;
    entry->pos.x = anim->unk34.x;
    entry->pos.y = -anim->unk34.y;
    entry->pos.z = anim->unk34.z;
    entry->rot.x = anim->unk40.x;
    entry->rot.y = -anim->unk40.y;
    entry->rot.z = anim->unk40.z;
}

// .text:0x0006A400 size:0x14 mapped:0x806A9494
void fn_3_6A400(void) {
    lbl_3_common_bss_32724.someFlag = FALSE;
}

// .text:0x0006A414 size:0x428 mapped:0x806A94A8
void fn_3_6A414(void) {
    return;
}

// .text:0x0006A83C size:0x174 mapped:0x806A98D0
void fn_3_6A83C(void) {
    VecXYZ sp8;
    s32 var_r4;
    s32 var_r30;
    s16 pitchTime;
    u8 status;

    var_r30 = 0;
    pitchTime = g_Pitcher.pitchTotalTimeCounter;
    if (pitchTime <= 0) {
        lbl_3_common_bss_32724.field_0xC8 = 0;
        return;
    }
    status = lbl_3_common_bss_32724.field_0xC8;
    if (status < 2U) {
        if ((u8) g_d_GameSettings.minigamesEnabled != 0) {
            var_r30 = g_Minigame.players.characterIndex[(s8) g_Minigame.minigamePlayerSelectedOrder];
        }
        if ((pitchTime >= 0) && (((u8) g_Pitcher.TypeOfPitch != 0) || ((u8) g_Pitcher.ChargePitchType != 0))) {
            if (status == 0) {
                fn_3_CB344(var_r30, g_Pitcher.starPitchType);
                lbl_3_common_bss_32724.field_0xC8 = 1;
            }
            if ((u8) lbl_3_common_bss_32724.field_0xC8 == 1) {
                if (((s16) g_Ball.pitchHangtimeCounter == 1) || ((u8) g_GameLogic.gameStatus != 1)) {
                    fn_3_CB234(var_r30, 1);
                    lbl_3_common_bss_32724.field_0xC8 = 2;
                    return;
                }
                var_r4 = 0x1A;
                if ((u8) g_Pitcher.handedness != 0) {
                    var_r4 = 0x14;
                }
                getAnimRelatedCoordinates(var_r30, var_r4, &sp8);
                fn_3_CB284(var_r30, g_Pitcher.windupCountdownUntilBallReleased, g_Pitcher.pitchChargeUpAnimationProportion);
            }
        }
    }
}



// .text:0x0006A9B0 size:0xE8 mapped:0x806A9A44
void fn_3_6A9B0(void) {
    return;
}

// .text:0x0006AA98 size:0x98 mapped:0x806A9B2C
void fn_3_6AA98(void) {
    u8 state;

    if (g_Batter.charID == 2 || g_Batter.charID == 3 || g_Batter.charID == 6) {
        return;
    }
    state = lbl_3_common_bss_32220.field_0x0a;
    if (state == 0) {
        return;
    }
    if (state == 3 || state == 4) {
        fn_3_C07A0();
    } else if (state == 9) {
        fn_3_C0770();
    } else if (lbl_3_common_bss_32220.field_0x02 == 2 && state == 2) {
        fn_3_C07B0();
    }
}

// .text:0x0006AB30 size:0x28 mapped:0x806A9BC4
void fn_3_6AB30(void) {
    fn_3_BF1AC();
    fn_3_CABB4();
    fn_80011578();
}

// .text:0x0006AB58 size:0x368 mapped:0x806A9BEC
void fn_3_6AB58(void) {
    return;
}
