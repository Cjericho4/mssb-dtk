#include "game/gap_15C5F4.h"
#include "game/gap_AC9F8.h"
#include "game/rep_16B8.h"

extern void fn_8004D0F0(void);

// .text:0x0015C5F4 size:0x44 mapped:0x8079B688
void fn_3_15C5F4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_7) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0015C638 size:0xAC mapped:0x8079B6CC
void fn_3_15C638(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    fn_80034E20(scene, lbl_3_data_27C54);
    if (lbl_80353A90.unk104 == 2) {
        lbl_80371C30[scene->unkIndex].obj->unk64 = 0xD3;
    } else if (lbl_80353A90.unk104 == 3) {
        lbl_80371C30[scene->unkIndex].obj->unk64 = 0xC0;
    }
    lbl_803CC1B8->unk_00 = fn_3_15C5F4;
}

// .text:0x0015C6E4 size:0xAF4 mapped:0x8079B778
void fn_3_15C6E4(void) {
    return;
}

// .text:0x0015D1D8 size:0x96C mapped:0x8079C26C
void fn_3_15D1D8(void) {
    return;
}

// .text:0x0015DB44 size:0x12E8 mapped:0x8079CBD8
void fn_3_15DB44(void) {
    return;
}

// .text:0x0015EE2C size:0x25C mapped:0x8079DEC0
void fn_3_15EE2C(void) {
    return;
}

// .text:0x0015F088 size:0x198 mapped:0x8079E11C
void fn_3_15F088(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    Entry_80371C30* entries;
    Struct_80371C30_Inner* obj;

    if (g_GameLogic._125 != 10) {
        if ((s8)lbl_3_common_bss_34C90.field_0x1DA == 0) {
            lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 1;
            entries = &lbl_80371C30[2];
            entries[scene->unkIndex].obj->field_0x68 = 4;
            obj = entries[scene->unkIndex].obj;
            if ((obj->field_0x5C >> 16) > 10) {
                obj->field_0x5C = 0xA0000;
            }
        } else {
            entries = &lbl_80371C30[1];
            entries[scene->unkIndex].obj->field_0x68 = 4;
            obj = entries[scene->unkIndex].obj;
            if ((obj->field_0x5C >> 16) > 10) {
                obj->field_0x5C = 0xA0000;
            }
            lbl_80371C30[scene->unkIndex + 2].obj->field_0x68 = 1;
        }
        if (lbl_3_common_bss_32724.unk_CE != 0) {
            lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
            lbl_80371C30[scene->unkIndex + 3].obj->field_0x68 = 4;
            lbl_80371C30[scene->unkIndex + 4].obj->flags &= ~2;
            scene->unk1a_u16++;
            if (scene->unk1a_u16 >= 0x2D) {
                goto remove;
            }
        }
        return;
    }
remove:
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
}

// .text:0x0015F220 size:0x160 mapped:0x8079E2B4
extern s32 lbl_3_data_27420;

void fn_3_15F220(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    fn_80034E20(scene, &lbl_3_data_27420);
    if (!g_d_GameSettings.exhibitionMatchInd) {
        (&lbl_80371C30[scene->unkIndex])[1].obj->unk64 = 0xE;
    }
    if (lbl_80353A90.unk104 == 3) {
        (&lbl_80371C30[scene->unkIndex])[3].obj->unk64 = 0xCC;
        (&lbl_80371C30[scene->unkIndex])[4].obj->unk64 = 0xD0;
    } else if (lbl_80353A90.unk104 == 2) {
        (&lbl_80371C30[scene->unkIndex])[3].obj->unk64 = 0xCD;
        (&lbl_80371C30[scene->unkIndex])[4].obj->unk64 = 0xD1;
    }
    if (!g_d_GameSettings.exhibitionMatchInd && (s8)g_GameLogic.playOverFadeOutStarted >= 0) {
        (&lbl_80371C30[scene->unkIndex])[1].obj->unk64 = 0x10;
    }
    scene->unk1a = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_15F088;
}

// .text:0x0015F380 size:0x44 mapped:0x8079E414
void fn_3_15F380(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_10) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0015F3C4 size:0x4C mapped:0x8079E458

void fn_3_15F3C4(void) {
    fn_80034E20((void (*)()) lbl_803CC1B8, (int *) &lbl_3_data_273E0, (void **) &lbl_803CC1B8);
    lbl_803CC1B8->aFunctionPointer = fn_3_15F380;
}

// .text:0x0015F410 size:0x164 mapped:0x8079E4A4
void fn_3_15F410(void) {
    if (g_GameLogic._125 < TRANSITION_CALCULATION_TYPE_3) {
        return;
    }
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_3) {
        lbl_3_common_bss_32724.unkCF = g_Scores.highscore;
        lbl_3_common_bss_32724.unkD0 = g_Scores.unkAD;
        fn_800B0A5C_insertQueue(fn_3_15F3C4, 2);
    }
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        fn_800B0A5C_insertQueue(fn_3_15C638, 2);
    }
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_7) {
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            if (lbl_3_common_bss_34C90.field_0x1D8 == 0 && g_GameLogic._11A != 0) {
                fn_800B0A5C_insertQueue(fn_3_91FC4, 2);
                fn_800B0A5C_insertQueue(fn_3_15F220, 2);
                g_GameLogic._11A = 0;
            } else if (g_GameLogic._11A != 1) {
                fn_800B0A5C_insertQueue(fn_3_15EE2C, 2);
                g_GameLogic._11A = 1;
            }
        }
    } else if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
    }
}

