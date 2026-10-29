#include "challenge/gap_0.h"

// .text:0x00000000 size:0x20
void fn_1_0(ANIMBank* animBank) {
    ANIMGet(animBank);
}

// .text:0x00000020 size:0xC8
void fn_1_20(void) {
    return;
}

// .text:0x000000E8 size:0xC8
void fn_1_E8(void) {
    return;
}

// .text:0x000001B0 size:0x30
void fn_1_1B0(u32* table, s32 count) {
    u32* entry = table;
    s32 i;

    for (i = 0; i < count; i++) {
        if (*entry != 0) {
            *entry += (u32)table;
        }
        entry++;
    }
}

// .text:0x000001E0 size:0x388
#include "game/rep_1C0.h"
#include "challenge/challenge.h"
typedef struct ChallengeLoadScene {
    void (*callback)(void);
    DrawingSceneStruct* parent;
    u8 _pad8[8];
    s16 state;
    u8 _pad12[2];
    void* data;
    u8 index;
} ChallengeLoadScene;
typedef struct ChallengeAssetBundle {
    u32 texture, layout, geometry, skin, attachment;
} ChallengeAssetBundle;
struct ChallengeFileHandle;
extern struct ChallengeFileHandle lbl_1_bss_4;
extern char lbl_1_data_AC[];
extern CompressedDiskRead lbl_800F1D78[];
void LoadFile(char* name, struct ChallengeFileHandle* handle, s32 a, s32 b, s32 c);
s32 fn_800A8518(s32 mode);
u32 fn_800A88C8(void);
void fn_800A8B78(struct ChallengeFileHandle* handle);
void convertTextureHeader(void* texture);
void LoadActorLayout(void* layout);
void convertGeometryAndSknHeader(void* geometry, void* skin);
void haveActLayoutPointToGeoHeader(void* layout, void* geometry);
void fn_80025DDC(void* attachment);
static inline void relocateChallengeBundle(u32* table, s32 count) {
    u32* entry = table;
    s32 i;
    for (i = 0; i < count; i++) {
        if (*entry) *entry += (u32)table;
        entry++;
    }
}
static inline void loadChallengeBundle(ChallengeAssetBundle* bundle) {
    relocateChallengeBundle((u32*)bundle, 5);
    convertTextureHeader((void*)bundle->texture);
    LoadActorLayout((void*)bundle->layout);
    convertGeometryAndSknHeader((void*)bundle->geometry, (void*)bundle->skin);
    haveActLayoutPointToGeoHeader((void*)bundle->layout, (void*)bundle->geometry);
    if (bundle->attachment) fn_80025DDC((void*)bundle->attachment);
}
/* Load and relocate successive preview assets, then release the file handle. */
void fn_1_1E0(void) {
    ChallengeLoadScene* scene = (ChallengeLoadScene*)lbl_803CC1B8;
    switch (scene->state) {
    case 0:
        LoadFile(lbl_1_data_AC, &lbl_1_bss_4, 0, 0, 1);
        lbl_803CC1B8->loadingState++;
    case 1:
        if (fn_800A8518(1)) lbl_803CC1B8->loadingState++;
        break;
    case 2:
        if (lbl_803C77B8.pressed & 0x100) {
            scene->data = ARAMTransfer(&lbl_800F1D78[scene->index], 0, 0, 0);
            lbl_803CC1B8->loadingState++;
        }
        break;
    case 3:
        if (lbl_803C6CF8.allowLoad == 1) {
            switch (scene->index % 19) {
            case 0: loadChallengeBundle(scene->data); break;
            case 1: loadChallengeBundle(scene->data); break;
            case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
            case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
                ANIMGet(scene->data); break;
            }
            fn_800ACFB0(scene->data);
            if (lbl_803C77B8.buttons & 0x200) lbl_803CC1B8->loadingState++;
            else {
                scene->data = ARAMTransfer(&lbl_800F1D78[++scene->index], 0, 0, 0);
            }
        }
        break;
    case 4:
        if (fn_800A8518(3)) lbl_803CC1B8->loadingState++;
        break;
    case 5:
        if (!fn_800A88C8()) {
            fn_800A8B78(&lbl_1_bss_4);
            lbl_803CC1B8->loadingState++;
        }
        break;
    case 6:
        scene->parent->loadingState = 1;
        fn_800B0A14_removeQueue();
        break;
    }
}

// .text:0x00000568 size:0x24
void fn_1_568(void) {
    if (lbl_803CC1B8->loadingState == 1) {
        lbl_803CC1B8->aFunctionPointer = fn_1_16A0;
    }
}

// .text:0x0000058C size:0x5C
void fn_1_58C(void) {
    fn_800B0A5C_insertQueue(fn_1_1E0, 0)->unk10 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_568;
    lbl_803CC1B8->loadingState = 0;
}

// .text:0x000005E8 size:0x4
void fn_1_5E8(void) {
    return;
}
