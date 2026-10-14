#include "game/gap_6B4C8.h"

#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_720.h"
#include "game/gap_9CD90.h"

typedef struct {
    u8 _pad[0xa0];
    s8 charIDs[0x32];
    u8 _pad2[0x31];
    s8 field_0x103;
    u8 _pad3[0x4];
} Lbl80353A90Struct6B; // size: 0x108

extern Lbl80353A90Struct6B lbl_80353A90;
extern s32 fn_80016344(s32, s32, s32, s32);
extern s32 fn_8001500C(s32 team, s32 rosterID, s32 slot);
extern u8 lbl_3_data_FAA8[];

/* Team selection data inside the 0x4C28-byte object at 0x8034E9A0. */
typedef struct {
    u8 _pad0[0x46E0];
    s32 captainCharID[2];   /* 0x46E0 */
    u8 _pad46E8[0x21];
    u8 captainVariant[2];   /* 0x4709 */
} TeamSelectData;
extern TeamSelectData lbl_8034E9A0;
void fn_80011A60(void);
AnimLevel1** fn_800111D8(AnimationStruct* anim);
void fn_800BDE8C(s32 arg0);
void fn_80011BE4(s32 animIndex);
void fn_8001196C(void);
s32 fn_8001594C(s32 team);

typedef struct {
    u8 _pad0[2];
    u8 bodyType;     /* 0x2 */
    u8 _pad3[3];
} CharacterBodyInfo; /* size: 0x6 */
extern CharacterBodyInfo lbl_800E8558[];

// .text:0x0006B4C8 size:0x110
s32 fn_3_6B4C8(void) {
    s32 i;

    if (lbl_3_common_bss_32724.unk9A == 0) {
        fn_80011A60();
        g_hugeAnimStruct.field186_0x2d77 = 0;
        lbl_3_common_bss_32724.unk9A = 1;
    }
    if (fn_80016344(lbl_8034E9A0.captainCharID[g_d_GameSettings.humanTeamNumber], 0xC, 1,
                    lbl_8034E9A0.captainVariant[g_d_GameSettings.humanTeamNumber]) != 0) {
        for (i = 0; i < 9; i++) {
            if (g_hugeAnimStruct.AnimationStructPtrs[i]->unk252 == lbl_8034E9A0.captainCharID[g_d_GameSettings.humanTeamNumber]) {
                g_hugeAnimStruct.AnimationStructPtrs[i] = &g_hugeAnimStruct.fielderStructs[12];
                g_hugeAnimStruct.AnimationStructPtrs[12] = NULL;
                break;
            }
        }
        return 1;
    }
    return 0;
}

// .text:0x0006B5D8 size:0x9C
s32 fn_3_6B5D8(void) {
    switch (lbl_3_common_bss_32724.unk9A) {
    case 0:
        g_hugeAnimStruct.field186_0x2d77 = 0;
        lbl_3_common_bss_34C58._2C = 0;
        lbl_3_common_bss_32724.unk9A = lbl_3_common_bss_32724.unk9A + 1;
        break;
    case 1:
        if (fn_80016344((s8)lbl_80353A90.field_0x103, 9, 0, 0) != 0) {
            return 1;
        }
        break;
    }
    return 0;
}

// .text:0x0006B674 size:0x1FC
void fn_3_6B674(void) {
    AnimationStruct* anim;
    AnimLevel1* model;
    s32 i;
    s32 visible;

    if (g_d_GameSettings.minigamesEnabled == 0 || g_Minigame.GameMode_MiniGame == 0) {
        if (g_GameLogic.sceneID == 1) {
            fn_800BDE8C(2);
        } else {
            fn_800BDE8C(1);
        }
    } else {
        switch (g_Minigame.GameMode_MiniGame) {
        case 1:
        case 3:
            fn_800BDE8C(2);
            break;
        case 2:
        case 4:
        case 5:
        case 6:
            fn_800BDE8C(1);
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (anim == NULL || *fn_800111D8(anim) == NULL) {
            continue;
        }
        visible = 1;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            if ((g_GameLogic.gameStatus == 0x1C || (u8)(g_GameLogic.gameStatus - 0x1D) <= 1 || g_GameLogic.gameStatus == 0x1F)
                && g_GameLogic.gameStatus == 0x1F) {
                visible = 0;
            }
            if (g_d_GameSettings.GameModeSelected == 6 && g_GameLogic.sceneID == 1 && g_Minigame.minigameFielderIndex[i] >= 1) {
                visible = 0;
            }
        } else if (g_GameLogic.secondaryGameMode != 0xE && g_Stats.unk36 == 0 && i != 0 && i != 9 && g_GameLogic.sceneID == 1) {
            visible = 0;
        }
        if (anim->unk_25D == 2) {
            visible = 0;
        }
        model = *fn_800111D8(anim);
        if (visible) {
            model->animFlags |= 4;
        } else {
            model->animFlags &= 0xFB;
        }
    }
}

static inline void unloadEmptyBaseRunners(void) {
    s32 i;

    for (i = 1; i < 4; i++) {
        if (g_RunningLogic.runnerOnBase[i] == -1) {
            fn_80011BE4(i + 9);
        }
    }
}

// .text:0x0006B870 size:0x1F4
void fn_3_6B870(void) {
    s32 i;

    if (g_Strikes.outs >= 3) {
        for (i = 0; i < 4; i++) {
            if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF || i != 0) {
                fn_80011BE4(i + 9);
            }
        }
    } else if (g_GameLogic.gameStatus == 0xA) {
        unloadEmptyBaseRunners();
    } else {
        unloadEmptyBaseRunners();
        if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF) {
            fn_80011BE4(9);
        }
    }
    for (i = 9; i < 13; i++) {
        if (g_d_GameSettings.GameModeSelected != 2 || g_GameLogic.secondaryGameMode != 0xF || i != 9) {
            g_hugeAnimStruct.AnimationStructPtrs[i] = NULL;
        }
    }
}

// .text:0x0006BA64 size:0x308
s32 fn_3_6BA64(void) {
    s32 runner;
    s32 next;
    u8 mode;

    if (lbl_3_common_bss_32724.unk9A == 0) {
        g_hugeAnimStruct.field189_0x2d7a = 0;
        g_hugeAnimStruct.field186_0x2d77 = 0;
        lbl_3_common_bss_32724.unk9A = 1;
    }
    do {
        runner = 3 - g_hugeAnimStruct.field189_0x2d7a;
        if (g_Runners[runner].rosterID >= 0) {
            if (fn_8001500C(g_GameLogic.teamBatting, g_Runners[runner].rosterID, runner + 9) == 0) {
                return 0;
            }
        }
        g_hugeAnimStruct.field189_0x2d7a++;
    } while (g_hugeAnimStruct.field189_0x2d7a < 4);

    mode = g_d_GameSettings.GameModeSelected;
    if (mode == 0 || (u8)(mode - 4) <= 1 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        lbl_3_common_bss_32724.unk9E = g_Runners[0].charID;
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        lbl_3_common_bss_32724.unk9E = lbl_3_data_FAA8[g_Practice.rosterID];
    }
    if (mode == 0 || (u8)(mode - 4) <= 1 || (mode == 2 && g_GameLogic.secondaryGameMode == 0x10)) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
        if (next > 9) {
            next = 1;
        }
        lbl_3_common_bss_32724.unkA0 = inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]].stats.CharID;
    } else if (mode == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        lbl_3_common_bss_32724.unkA0 = inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]].stats.CharID;
    }
    if (mode == 0 || mode == 5 || mode == 4) {
        next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
        if (next > 9) {
            next = 1;
        }
        lbl_3_common_bss_32724.unkA2 = inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]].stats.CharID;
    }
    return 1;
}

// .text:0x0006BD6C size:0x138
s32 fn_3_6BD6C(void) {
    s32 team;
    s32 i;

    if (lbl_3_common_bss_32724.unk9B == 0) {
        fn_8001196C();
        lbl_3_common_bss_32724.unk9B = 1;
        g_hugeAnimStruct.field186_0x2d77 = 0;
        g_hugeAnimStruct.field190_0x2d7b = 0;
        g_hugeAnimStruct.field191_0x2d7c = 0;
        if (g_GameLogic.gameStatus == 9) {
            g_hugeAnimStruct.field191_0x2d7c = 1;
            for (team = 0; team < 2; team++) {
                for (i = 0; i < 9; i++) {
                    if (lbl_800E8558[inMemRoster[team][i].stats.CharID].bodyType == 0x19) {
                        inMemRoster[team][i].stats.FieldingArm = 0;
                        inMemRoster[team][i].stats.BattingStance = 1;
                    }
                }
            }
        }
    }
    return fn_8001594C(g_GameLogic.teamFielding) != 0;
}
