#include "game/gap_97144.h"
#include "UnknownHeaders.h"
#include "game/gap_AC9F8.h"
#include "game/rep_3448.h"

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
    return;
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
    return;
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

// .text:0x00098EA8 size:0x1BC mapped:0x806D7F3C
void fn_3_98EA8(void) {
    return;
}

// .text:0x00099064 size:0x344 mapped:0x806D80F8
void fn_3_99064(void) {
    return;
}

