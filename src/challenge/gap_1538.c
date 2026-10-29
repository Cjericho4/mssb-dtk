#include "challenge/gap_1538.h"
#include "challenge/challenge.h"

/* gap_8000B9C8.h declares fn_800A7D4C with a conflicting table view.
   Keep the texture conversion signature identical to its owning header. */
typedef struct Gap8000B9C8Texture Gap8000B9C8Texture;
void convertTextureHeader(Gap8000B9C8Texture* texture);
typedef struct ChallengeTextureFile {
    u32 textureOffset;
} ChallengeTextureFile;
/* Partial scene view for the loading callback's file and texture fields. */
typedef struct ChallengeTextureScene {
    void (*callback)(void);
    u8 _pad4[0x10];
    ChallengeTextureFile* file;
    Gap8000B9C8Texture* texture;
} ChallengeTextureScene;


// .text:0x00001538 size:0x94
void fn_1_1538(void) {
    return;
}

// .text:0x000015CC size:0x68
// Relocate the loaded challenge texture and advance its scene callback.
void fn_1_15CC(void) {
    ChallengeTextureScene* scene = (ChallengeTextureScene*)lbl_803CC1B8;
    if (lbl_803C6CF8.allowLoad == 1) {
        scene->texture = (Gap8000B9C8Texture*)((u8*)scene->file + scene->file->textureOffset);
        convertTextureHeader(scene->texture);
        ((ChallengeTextureScene*)lbl_803CC1B8)->callback = fn_1_1538;
    }
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if (lbl_803C6CF8.allowLoad == 1) {
        lbl_803CC1B8->unk14 = ARAMTransfer(&lbl_1_data_0[3], 0, 0, 0);
        lbl_803CC1B8->aFunctionPointer = fn_1_15CC;
    }
}

// .text:0x000016A0 size:0x2A8
void fn_1_66C4(void);
void fn_1_8B90(void);
void fn_1_17D90(void);
void fn_1_28200(void);
void fn_1_1D514(void);
void fn_1_26AF8(void);
void fn_1_A2E4(void);
void fn_1_24778(void);
void fn_1_2852C(void);
void fn_1_29A9C(void);
void fn_1_58C(void);
typedef struct ChallengePreviewMenu {
    void (*callback)(void);
    u8 _pad4[8];
    DrawingSceneStruct* drawing;
    u8 _pad10[6];
    s16 selection;
} ChallengePreviewMenu;
static inline void launchPreview(void (*callback)(void)) {
    fn_800B0A5C_insertQueue(callback, 10);
    lbl_803CC1B8->aFunctionPointer = fn_1_1948;
}
/* Navigate the preview menu and dispatch the selected modding/debug scene. */
void fn_1_16A0(void) {
    ChallengePreviewMenu* scene = (ChallengePreviewMenu*)lbl_803CC1B8;
    if (lbl_803C77B8.pressed == 8) {
        if (--scene->selection < 0) scene->selection = 9;
    } else if (lbl_803C77B8.pressed == 4) {
        if (++scene->selection >= 10) scene->selection = 0;
    } else if (lbl_803C77B8.held == 0x100) {
        switch ((u8)scene->selection) {
        case 0: launchPreview(fn_1_66C4); break;
        case 1: launchPreview(fn_1_8B90); break;
        case 2: launchPreview(fn_1_17D90); break;
        case 3: launchPreview(fn_1_28200); break;
        case 4: launchPreview(fn_1_1D514); break;
        case 5: launchPreview(fn_1_26AF8); break;
        case 6: launchPreview(fn_1_A2E4); break;
        case 7: launchPreview(fn_1_24778); break;
        case 8: launchPreview(fn_1_2852C); break;
        case 9: launchPreview(fn_1_29A9C); break;
        case 10: case 11: case 12: case 13: break;
        }
    } else if (lbl_803C77B8.held == 0x1000) {
        scene->drawing->loadingState = 1;
    } else if ((lbl_803C77B8.buttons & 0xA00) == 0xA00) {
        scene->callback = fn_1_58C;
    }
}

// .text:0x00001948 size:0x24
void fn_1_1948(void) {
    if (lbl_803CC1B8->loadingState != 0) {
        lbl_803CC1B8->aFunctionPointer = fn_1_11D0;
    }
}

// .text:0x0000196C size:0x40
void fn_1_196C(void) {
    fn_800A7D4C(0, &lbl_1_data_298[lbl_803CBBC0]);
}
