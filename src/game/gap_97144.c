#include "game/gap_97144.h"
#include "game/rep_16B8.h"
#include "UnknownHeaders.h"
#include "game/gap_AC9F8.h"
#include "game/rep_3448.h"
#include "stl/mem.h"

void fn_80069A98(void);

// .text:0x00097144 size:0x15C mapped:0x806D61D8
void fn_3_97144(void) {
    return;
}

// .text:0x000972A0 size:0x28 mapped:0x806D6334
void fn_3_972A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    fn_8003649C(arg0, arg1, arg2, 0x28, arg3);
}

// .text:0x000972C8 size:0x124 mapped:0x806D635C
void fn_3_972C8(void) {
    GameInitVariables* settings;

    lbl_3_common_bss_32724.someStatusInd = 1;
    settings = &g_d_GameSettings;
    if (settings->GameModeSelected == 4) {
        fn_80069A98();
        fn_80035CA4(0x16);
    }
    if (settings->GameModeSelected == 0 || settings->GameModeSelected == 5 || settings->GameModeSelected == 4) {
        fn_80035CA4(0x10);
        fn_80035CA4(0xF);
    }
    fn_80035CA4(2);
    fn_80035CA4(5);
    fn_80035CA4(4);
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_80035CA4(0x14);
        if (settings->GameModeSelected == 6) {
            fn_80035CA4(0xE);
        }
        fn_80035CA4(3);
        fn_80035CA4(9);
        fn_80035CA4(0xD);
        fn_80035CA4(0x11);
    } else if (settings->GameModeSelected == 2) {
        fn_80035CA4(0xB);
        fn_80035CA4(9);
    }
    if (lbl_3_common_bss_32724.unkD1 != 0) {
        fn_80035CA4(0xC);
    }
}

// .text:0x000973EC size:0x414 mapped:0x806D6480
void fn_3_973EC(void) {
    return;
}

// .text:0x00097800 size:0xDC mapped:0x806D6894
void fn_3_97800(void) {
    lbl_3_common_bss_32724.someStatusInd = 0;
    lbl_3_common_bss_32724.unk_A5 = 0;
    lbl_3_common_bss_32724._pad3a[0] = 0;
    lbl_3_common_bss_32724.unk_A8 = 0;
    lbl_3_common_bss_32724._pad3a[1] = 0;
    lbl_3_common_bss_32724._pad3a[2] = 0;
    lbl_3_common_bss_32724.unkD1 = 0;
    lbl_3_common_bss_32724._padAD[0] = 0;
    lbl_3_common_bss_32724._padAD[1] = 0;
    lbl_3_common_bss_32724.unk_B0 = 0;
    lbl_3_common_bss_32724.unk_B1 = 0;
    lbl_3_common_bss_32724.unk_B2 = 0;
    lbl_3_common_bss_32724.unk_C7 = 0;
    lbl_3_common_bss_32724._padD6[0] = 0;
    lbl_3_common_bss_32724.unk_B6 = 0;
    lbl_3_common_bss_32724.unkD9 = 0;
    lbl_3_common_bss_32724.unkDA = 0;
    lbl_3_common_bss_32724.unk_BC = 0;
    lbl_3_common_bss_32724.unk_C0 = 0;
    lbl_3_common_bss_32724._padC1[0] = 0;
    lbl_3_common_bss_32724._padC1[1] = 0;
    lbl_3_common_bss_32724.unk_C6 = 0;
    lbl_3_common_bss_32724.unk_AA = 0;
    lbl_3_common_bss_32724._padAB = 0;
    lbl_3_common_bss_32724.unk_C3 = 0;
    lbl_3_common_bss_32724._padC4 = 0;
    lbl_3_common_bss_32724.unk_BE = 0;
    lbl_3_common_bss_32724.unk_BF = 0;
    lbl_3_common_bss_32724.unk_B3 = 0;
    lbl_3_common_bss_32724.unk_B4 = 0;
    lbl_3_common_bss_32724.unk_B5 = 0;
    lbl_3_common_bss_32724.unk_C5 = 0;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        fn_800B0A5C_insertQueue(fn_3_95970, 2);
    }
    fn_800B0A5C_insertQueue(fn_3_91A60, 2);
}

// .text:0x000978DC size:0x410 mapped:0x806D6970
void fn_3_978DC(void) {
    return;
}

// .text:0x00097CEC size:0x33C mapped:0x806D6D80
void fn_3_97CEC(void) {
    return;
}

// .text:0x00098028 size:0x390 mapped:0x806D70BC
void fn_3_98028(void) {
    return;
}

// .text:0x000983B8 size:0x7C mapped:0x806D744C
void fn_3_983B8(void) {
    DrawingSceneStruct* scene;

    scene = lbl_803CC1B8;
    fn_80034E20(scene, lbl_3_data_D9E4);
    lbl_3_common_bss_32724.unk_C3 = 0;
    scene->unk_1C = 0;
    scene->unk_1E = lbl_3_common_bss_34C90.unk_221;
    scene->unk_20 = 0;
    lbl_803CC1B8->unk_00 = fn_3_98028;
}

// .text:0x00098434 size:0x518 mapped:0x806D74C8
void fn_3_98434(void) {
    return;
}

// .text:0x0009894C size:0x2D4 mapped:0x806D79E0
void fn_3_9894C(void) {
    return;
}

// .text:0x00098C20 size:0x1C0 mapped:0x806D7CB4
void fn_3_98C20(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (lbl_3_common_bss_32724.someStatusInd != 0) {
        goto remove;
    }
    if (scene->eventID == 0) {
        scene->eventID = 1;
        return;
    }
    if (scene->eventID == 1) {
        if (g_d_GameSettings.GameModeSelected == 2) {
            if (g_Practice._19F == 0) {
                goto remove;
            }
            if (lbl_3_common_bss_34C90.field_0x1D2 == 4) {
                scene->eventID = 2;
            }
            return;
        }
        if (g_d_GameSettings.minigamesEnabled) {
            if (g_GameLogic.gameStatus == 0xB && lbl_3_common_bss_34C90.field_0x1D2 == 4) {
                scene->eventID = 2;
            }
            if (g_d_GameSettings.GameModeSelected == 7) {
                if (lbl_3_common_bss_34C90.field_0x1D2 == 4) {
                    scene->eventID = 2;
                }
                if (lbl_3_common_bss_34C90.field_0x1D2 == 7 || lbl_3_common_bss_34C90.field_0x1D2 == 0xD) {
                    goto remove;
                }
            }
            return;
        }
        if ((lbl_3_common_bss_34C90.field_0x1D1 == 2 || lbl_3_common_bss_34C90.field_0x1D1 == 9) &&
            lbl_3_common_bss_34C90.field_0x1D2 == 4) {
            goto remove;
        }
        if (lbl_3_common_bss_34C90.field_0x1D9 == 2) {
            goto remove;
        }
        return;
    }
    if (scene->eventID == 2) {
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
        if ((lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16) == 0) {
            goto remove;
        }
    }
    return;
remove:
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
    lbl_3_common_bss_32724.unk_AA = 0;
}

// .text:0x00098DE0 size:0xC8 mapped:0x806D7E74
extern int lbl_3_data_D7A8;

void fn_3_98DE0(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_80034E20(scene, &lbl_3_data_D7A8);
    if (g_d_GameSettings.minigamesEnabled) {
        lbl_80371C30[scene->unkIndex].obj->field_0x67 = 5;
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        lbl_80371C30[scene->unkIndex].obj->field_0x67 = 6;
    }
    lbl_3_common_bss_32724.unk_AA = 1;
    scene->eventID = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_98C20;
}

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 _pad1[0x8 - 0x1];
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ u8 _padA[0x26 - 0xA];
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 _pad27[0x28 - 0x27];
} MenuNumberState; /* size: 0x28 */
extern MenuNumberState lbl_8034E978;

typedef struct {
    /* 0x0 */ u8 _pad0[0x8];
    /* 0x8 */ u16 unk8;
    /* 0xA */ u8 _padA[0x10 - 0xA];
} MenuEntry_800FEF70; /* size: 0x10 */
extern MenuEntry_800FEF70 lbl_800FEF70[];

typedef struct {
    /* 0x0000 */ u8 _pad0[0xCFA2];
    /* 0xCFA2 */ u8 unkCFA2[2];
} Lbl803297E0;
extern Lbl803297E0 lbl_803297E0;

void fn_80053FE8(void);
void fn_800486E0(s32 arg0, s8 arg1, u8 arg2);

// .text:0x00098EA8 size:0x1BC mapped:0x806D7F3C
void fn_3_98EA8(void) {
    if (lbl_3_common_bss_34C90.field_0x1D2 == 2) {
        fn_800B0A5C_insertQueue(fn_80053FE8, 2);
        memset(&lbl_8034E978, 0, sizeof(MenuNumberState));
        switch (lbl_803297E0.unkCFA2[lbl_3_common_bss_34C90.field_0x00]) {
        case 0:
            lbl_8034E978.unk0 = g_d_GameSettings.GameModeSelected == 5 ? 0x1C : 8;
            lbl_8034E978.unk9 = lbl_8034E978.unk8;
            lbl_8034E978.unk8 = lbl_800FEF70[g_d_GameSettings.GameModeSelected == 5 ? 0x1C : 8].unk8;
            break;
        case 1:
            lbl_8034E978.unk0 = 0xA;
            lbl_8034E978.unk9 = lbl_8034E978.unk8;
            lbl_8034E978.unk8 = lbl_800FEF70[0xA].unk8;
            break;
        case 2:
            lbl_8034E978.unk0 = 0x1E;
            lbl_8034E978.unk9 = lbl_8034E978.unk8;
            lbl_8034E978.unk8 = lbl_800FEF70[0x1E].unk8;
            break;
        case 3:
            lbl_8034E978.unk0 = 0x1F;
            lbl_8034E978.unk9 = lbl_8034E978.unk8;
            lbl_8034E978.unk8 = lbl_800FEF70[0x1F].unk8;
            break;
        }
        fn_800486E0(0, g_GameLogic.teams[lbl_3_common_bss_34C90.field_0x00], lbl_3_common_bss_34C90.field_0x00);
    }
    if (lbl_3_common_bss_34C90.field_0x1D2 == 5) {
        lbl_8034E978.unk26 = 1;
    }
}

// .text:0x00099064 size:0x344 mapped:0x806D80F8
void fn_3_99064(void) {
    return;
}

