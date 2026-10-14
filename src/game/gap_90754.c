#include "game/gap_90754.h"
#include "game/gap_97144.h"

// .text:0x00090754 size:0x10 mapped:0x806CF7E8
void fn_3_90754(Gap90754Struct* arg0, u8 arg1, u8 arg2) {
    arg0->field_0x11820 = arg1;
    arg0->field_0x11821 = arg2;
}

// .text:0x00090764 size:0x34 mapped:0x806CF7F8
s32 fn_3_90764(void) {
    fn_80021518(0x33, lbl_800EF808.unkBC);
    return 0;
}

// .text:0x00090798 size:0x84 mapped:0x806CF82C
void fn_3_90798(void) {
    return;
}

// .text:0x0009081C size:0x44 mapped:0x806CF8B0
void fn_3_9081C(void) {
    fn_800214D0();
    fn_800214D0();
    fn_800ACFB0(lbl_800EF808.unk8);
    lbl_800EF808.unk8 = NULL;
}

// .text:0x00090860 size:0x88 mapped:0x806CF8F4
void fn_3_90860(void) {
    return;
}

// .text:0x000908E8 size:0x40 mapped:0x806CF97C
void fn_3_908E8(void) {
    fn_800214D0();
    fn_800ACFB0(lbl_800EF808.unk98);
    lbl_800EF808.unk98 = 0;
}

// .text:0x00090928 size:0x88 mapped:0x806CF9BC
void fn_3_90928(void) {
    return;
}

// .text:0x000909B0 size:0x68 mapped:0x806CFA44
void fn_3_909B0(void) {
    s32 stadiumID;
    void **ptr;

    fn_800214D0();
    stadiumID = 6;
    if (g_d_GameSettings.StadiumID != 6) {
        stadiumID = g_d_GameSettings.StadiumID;
    }
    ptr = &lbl_800EF808.ptrArray[stadiumID];
    fn_800ACFB0(ptr[1]);
    ptr[1] = NULL;
}

// .text:0x00090A18 size:0x98 mapped:0x806CFAAC
void fn_3_90A18(void) {
    return;
}

// .text:0x00090AB0 size:0x64 mapped:0x806CFB44
void fn_3_90AB0(s32 charID) {
    // NONMATCHING: r0/r4 register swap in base+offset computation, and lwz vs lwzu
    void **entry;
    void *ptr;
    if (charID < 0) return;
    entry = (void**)&lbl_800EF808 + (fn_800698F8(charID) + 5);
    ptr = entry[1];
    if (ptr != NULL) {
        fn_800214D0();
        fn_800ACFB0(entry[1]);
        entry[1] = NULL;
    }
}

// .text:0x00090B14 size:0x100 mapped:0x806CFBA8
s32 fn_3_90B14(u8 charID, s32 altCharID) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 index;

    if (lbl_3_common_bss_34C58._2C == 0) {
        lbl_3_common_bss_34C58._2C = 1;
    }
    if (lbl_3_common_bss_34C58._2C == 1 || lbl_3_common_bss_34C58._2C == 3) {
        if (lbl_3_common_bss_34C58._2C == 1) {
            lbl_3_common_bss_34C58._2D = charID;
        } else {
            if (altCharID < 0) {
                return 1;
            }
            lbl_3_common_bss_34C58._2D = altCharID;
        }
        index = fn_800698F8(lbl_3_common_bss_34C58._2D);
        scene->loadingState = 0;
        fn_800216F8(index + 5, fn_3_90F48, 0);
        lbl_3_common_bss_34C58._2C++;
    } else if (scene->loadingState != 0) {
        if (++lbl_3_common_bss_34C58._2C == 5) {
            return 1;
        }
    }
    return 0;
}

// .text:0x00090C14 size:0x9C mapped:0x806CFCA8
void fn_3_90C14(void) {
    return;
}

// .text:0x00090CB0 size:0x128 mapped:0x806CFD44
void fn_3_90CB0(void) {
    return;
}

// .text:0x00090DD8 size:0x170 mapped:0x806CFE6C
void fn_3_90DD8(void) {
    return;
}

// .text:0x00090F48 size:0x11C mapped:0x806CFFDC
void fn_3_90F48(void) {
    return;
}

// .text:0x00091064 size:0x48 mapped:0x806D00F8
s32 fn_3_91064(void) {
    fn_80021518(0x1C, lbl_800EF808.unk10);
    fn_80021518(0x36, lbl_800EF808.unk10);
    return 0;
}

// .text:0x000910AC size:0x48 mapped:0x806D0140
s32 fn_3_910AC(void) {
    fn_80021518(0x1C, (s32)lbl_800EF808.unk8);
    fn_80021518(0x1D, (s32)lbl_800EF808.unk8);
    return 0;
}

// .text:0x000910F4 size:0xB4 mapped:0x806D0188
void fn_3_910F4(void) {
    return;
}

// .text:0x000911A8 size:0x10C mapped:0x806D023C
void fn_3_911A8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 count;
    s32 i;
    s32 state;

    if (lbl_3_common_bss_32724.someStatusInd != 0 || g_GameLogic.gameStatus != 2) {
        lbl_3_common_bss_32724._pad3a[0] = 0;
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
        return;
    }
    scene->unk18++;
    count = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == 6) {
        count = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 2; i++) {
        state = 3;
        if (scene->eventID != count) {
            if (count >= i + 1) {
                state = 2;
            }
            fn_8003649C((s32)scene, i + 1, i + 1, 0x107, state);
        }
    }
    scene->eventID = count;
}

