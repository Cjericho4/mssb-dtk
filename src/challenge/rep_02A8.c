#include "challenge/rep_02A8.h"

// .text:0x0000A2E4 size:0x64
void fn_1_A2E4(void) {
    switch (lbl_1_bss_2FDA) {
    case 0:
        lbl_1_bss_2FDA++;
        break;
    case 1:
        lbl_1_bss_2FDA++;
        break;
    case 2:
        lbl_803CC1B8->aFunctionPointer = fn_1_A250;
        break;
    }
}

// .text:0x0000A348 size:0x11C
void fn_1_A348(void) {
    u16 pressed = lbl_803C77B8.pressed;
    u16 held = lbl_803C77B8.held;
    if (pressed & 8) {
        lbl_1_common_bss_49A78.selection = ((s8)lbl_1_common_bss_49A78.selection + 4) % 5;
    } else if (pressed & 4) {
        lbl_1_common_bss_49A78.selection = ((s8)lbl_1_common_bss_49A78.selection + 6) % 5;
    } else if (held & 0x100) {
        lbl_803CC1B8->aFunctionPointer = lbl_1_data_1C8C[(s8)lbl_1_common_bss_49A78.selection];
        lbl_1_common_bss_49A78.pending = 0;
    } else if (held & 0x1200) {
        lbl_1_bss_2FDA = 0;
        lbl_1_bss_2FD9 = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_C2A4;
    }
}

// .text:0x0000A464 size:0x1D0
void fn_1_A464(void) {
    return;
}

// .text:0x0000A634 size:0xE0
void fn_1_A634(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch (lbl_1_bss_2FEE) {
    case 0: {
        ChallengeScene* entry;
        scene->loadingState = 0;
        entry = (ChallengeScene*)fn_800B0A5C_insertQueue(fn_1_9F04, 1);
        entry->byte18 = 0;
        entry->byte19 = 3;
        entry->arg14 = (s32)fn_1_A838;
        lbl_803CC1B8->loadingState = 0;
        lbl_1_bss_2FEE++;
        break;
    }
    case 1:
        if (scene->loadingState != 0) {
            scene->loadingState = 0;
            lbl_1_bss_2FEE++;
        }
        break;
    case 2:
        scene->aFunctionPointer = fn_1_A464;
        lbl_1_bss_2FEE = 0;
        break;
    }
}

// .text:0x0000A714 size:0x4
void fn_1_A714(void) {
    return;
}

// .text:0x0000A718 size:0x64
BOOL fn_1_A718(void) {
    s8 i;

    for (i = (s8)lbl_800EF808.unk390 - 1; i > 0; i--) {
        if (fn_800214D0() == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

// .text:0x0000A77C size:0x34
s32 fn_1_A77C(void) {
    fn_80021518(0x31, (s32)lbl_800EF808.files[0x29]);
    return 0;
}

// .text:0x0000A7B0 size:0x34
s32 fn_1_A7B0(void) {
    fn_80021518(0x33, (s32)((ChallengeResources*)&lbl_800EF808)->files[0x31]);
    return 0;
}

// .text:0x0000A7E4 size:0x54
s32 fn_1_A7E4(void) {
    s32 file = lbl_1_bss_2FDB + 0x2A;
    fn_80021518(lbl_1_data_1884[lbl_1_bss_2FDB], (s32)lbl_800EF808.files[file]);
    return 0;
}

// .text:0x0000A838 size:0x48
s32 fn_1_A838(void) {
    fn_80021518(0x1C, (s32)lbl_800EF808.files[3]);
    fn_80021518(0x36, (s32)lbl_800EF808.files[3]);
    return 0;
}

// .text:0x0000A880 size:0x34
s32 fn_1_A880(void) {
    fn_80021518(0x1C, (s32)lbl_800EF808.files[1]);
    return 0;
}

// .text:0x0000A8B4 size:0x54
s32 fn_1_A8B4(void) {
    s32 file = lbl_1_data_1CA0 + 5;
    fn_80021518(lbl_1_data_17A4[lbl_1_data_1CA0], (s32)lbl_800EF808.files[file]);
    return 0;
}

// .text:0x0000A908 size:0x54
s32 fn_1_A908(void) {
    s32 file = lbl_1_bss_2FD9 + 5;
    fn_80021518(lbl_1_data_17A4[lbl_1_bss_2FD9], (s32)lbl_800EF808.files[file]);
    return 0;
}

// .text:0x0000A95C size:0xB48
void fn_1_A95C(void) {
    return;
}

// .text:0x0000B4A4 size:0x114
void fn_1_B4A4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch (lbl_1_bss_2FE8) {
    case 0: {
        ChallengeScene* entry;
        scene->loadingState = 0;
        entry = (ChallengeScene*)fn_800B0A5C_insertQueue(fn_1_9F04, 1);
        entry->byte18 = 0;
        entry->byte19 = 0x2A;
        entry->arg14 = (s32)fn_1_A7E4;
        lbl_803CC1B8->loadingState = 0;
        lbl_1_bss_2FE8++;
        break;
    }
    case 1:
        if (scene->loadingState != 0) {
            lbl_800EF808.soundMode = 2;
            sndOutputMode(2);
            scene->loadingState = 0;
            lbl_1_bss_2FE8++;
        }
        break;
    case 2:
        scene->aFunctionPointer = fn_1_A95C;
        lbl_1_common_bss_49994.pending = 0;
        lbl_1_bss_2FE8 = 0;
        break;
    }
}

// .text:0x0000B5B8 size:0x4AC
void fn_1_B5B8(void) {
    return;
}

// .text:0x0000BA64 size:0x19C
void fn_1_BA64(void) {
    return;
}

// .text:0x0000BC00 size:0x1D8
void fn_1_BC00(void) {
    return;
}

// .text:0x0000BDD8 size:0x11C
void fn_1_BDD8(void) {
    return;
}

// .text:0x0000BEF4 size:0x40
void fn_1_BEF4(s16 voiceID) {
    sndFXKeyOff(voiceID);
    sndFXCtrl(voiceID, 7, 0);
}

// .text:0x0000BF34 size:0x7C
SND_VOICEID fn_1_BF34(u32 fxId) {
    SND_VOICEID voice = sndFXStartEx(fxId, 0x7F, 0x3F, 0);
    OSReport("sndFXReverb was %s.\n", sndFXCtrl(voice, 0x5B, fn_800211F0()) ? "succeed" : "failed");
    return voice;
}

// .text:0x0000BFB0 size:0x1D8
void fn_1_BFB0(void) {
    return;
}

// .text:0x0000C188 size:0x11C
void fn_1_C188(void) {
    return;
}
