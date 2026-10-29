#include "game/gap_464.h"
#include "game/rep_1D58.h"
/* gap_8001B200.h conflicts with the existing getAnimRelatedCoordinates prototype. */
void fn_8001CBD4(void);

void fn_3_5AE9C(void);
void fn_3_C0824(void);

// .text:0x00000464 size:0x38 mapped:0x8063F4F8
void _epilog(void) {
    g_d_GameSettings._55 = 0;
    fn_800BF038(0, &g_d_GameSettings);
    fn_3_BF20C();
}

// .text:0x0000049C size:0x58 mapped:0x8063F530
void _prolog(void) {
    fn_800B0A5C_insertQueue(fn_3_5AE9C, 1);
    fn_3_C0824();
    fn_80036C88(&lbl_3_data_118, &lbl_3_data_118.sub);
    fn_800B0D28(&lbl_3_data_118.sub);
    fn_8004B270();
}

typedef struct StadiumLoadState {
    u8 _pad00[0x10];
    u8 loaded;
    u8 _pad11[3];
} StadiumLoadState;
STATIC_ASSERT(sizeof(StadiumLoadState) == 0x14);
extern StadiumLoadState lbl_3_data_228;
/* gap_8001E460.h has a conflicting ARAMTransfer descriptor view; use rep_1C0.h's interface here. */
extern CompressedDiskRead lbl_800EFBE8[21];
void fn_3_5EC0(StadiumFileHeader* header);

// .text:0x000004F4 size:0x168 mapped:0x8063F588
// Load the stadium file, wait for its objects, and release the loading task.
void manageStadiumLoading(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch (scene->loadingState) {
    case 0:
        fn_8001CBD4();
        g_hugeAnimStruct.stadiumFileHeaderPointer = ARAMTransfer(
            &lbl_800EFBE8[g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3], NULL, 0, NULL);
        scene->loadingState++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8.allowLoad == 1) {
            fn_3_5EC0(g_hugeAnimStruct.stadiumFileHeaderPointer);
            scene->loadingState++;
        }
        break;
    case 2:
        switch (fn_3_B9BB4(g_d_GameSettings.StadiumID)) {
        case 0:
            break;
        case 1:
            scene->loadingState = 3;
            break;
        case -1:
            scene->loadingState = 4;
            break;
        }
        break;
    case 3:
        if (lbl_3_common_bss_350E4[0].unk6A == 0) {
            scene->loadingState++;
        }
        break;
    default:
        scene->currentDrawingItem->loadingState = 1;
        lbl_3_data_228.loaded = 1;
        fn_800B0A14_removeQueue();
        break;
    }
}

