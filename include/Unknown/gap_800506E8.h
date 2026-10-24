#ifndef __UNKNOWN_gap_800506E8_H_
#define __UNKNOWN_gap_800506E8_H_

#include "mssbTypes.h"
#include "menus/menu_ui.h"

typedef struct MenuGridScene {
    void (*update)(void);
    u8 _pad4[0x10];
    u16 paneBase;
    u8 _pad16[6];
    s16 state; /* 0x1C */
} MenuGridScene;
typedef struct MenuGridPane {
    u8 _pad0[0x54];
    u32 flags;
    u32 textureOverride;
    u32 frame;
    u8 _pad60[4];
    u16 sequence;
    u8 _pad66[2];
    u8 playMode;
    u8 _pad69[9];
    u16 order;
} MenuGridPane;
typedef struct MenuGridPaneEntry {
    MenuGridPane* pane;
    u32 owner;
} MenuGridPaneEntry;
extern MenuGridPaneEntry lbl_80371C30[];
extern MenuGridScene* lbl_803CC1B8;
extern MenusSceneScript lbl_800FCA60[160];
extern u8 lbl_800FDE60[36];
extern u8 lbl_800E854C[12];
typedef struct MenuGridSettings {
    u8 _pad0[8];
    u8 exhibitionMatchInd;
} MenuGridSettings;
extern MenuGridSettings g_d_GameSettings;
typedef struct MenuGridCharacterFlags { u8 characterFlags[54]; } MenuGridCharacterFlags;
extern MenuGridCharacterFlags lbl_80361B20;
typedef struct MenuGridChallengeFlags {
    u8 _pad0[0x43D6];
    u8 characterFlags[54];
} MenuGridChallengeFlags;
extern MenuGridChallengeFlags starMissionCompletionTracker;
void fn_80034E20(MenuGridScene* scene, MenusSceneScript* script);
void fn_800363D8(MenuGridScene* scene, s32 pane, s32 field, s32 sourcePane, s32 frame);
typedef struct Gap800506E8Actor { u8 _pad0[0x252]; u8 id; } Gap800506E8Actor;
typedef struct Gap800506E8Task {
    u8 _pad0[0x14];
    s32 index;
    Gap800506E8Actor* actor;
    u8 id;
} Gap800506E8Task;
Gap800506E8Task* fn_800B0A5C_insertQueue(void (*callback)(void), u16 priority);
typedef struct Gap800506E8Camera {
    /* 0x00 */ f32 projection[4][4];
    u8 _pad40[0x68];
} Gap800506E8Camera;
typedef struct Gap800506E8Cameras {
    Gap800506E8Camera slots[2];
    Gap800506E8Camera alternate[2];
} Gap800506E8Cameras;
extern Gap800506E8Cameras lbl_803C639C;
extern s32 lbl_803CB880;
typedef struct Gap800506E8State {
    u8 _pad0[0x28];
    /* 0x28 */ s8 slots[0x24];
    u8 cellUnavailable[36]; /* 0x4C hides cell character with placeholder charID 54 */
    u8 _pad70[4];
    u8 alternateBadge[4]; /* 0x74 controller badge bank +4 */
    u8 _pad78[4];
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ u8 unk7E;
    u8 _pad7F[0xF];
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F;
    /* 0x90 */ u8 unk90;
    u8 _pad91;
    u8 unk92;
} Gap800506E8State;
extern Gap800506E8State lbl_803C6028;

extern s32 lbl_803CB880;
extern s32 lbl_803CBD14;

typedef struct Gap800506E8Character {
    u8 unk0;
    /* 0x1 */ u8 id;
    u8 _pad2[0x4];
} Gap800506E8Character;
extern Gap800506E8Character lbl_800E8558[54];
extern u8 lbl_800FDE84[0x744];
void fn_800506E8(s8 value, s32 index, BOOL set);
void fn_80050760(void);
BOOL fn_80050F78(s32 mode);
void fn_80050FE8(void);
void fn_8005138C(void);
void fn_80051D00(void);
void fn_80052188(void);
void fn_800521B0(void);
void fn_8005240C(void);
void fn_80052634(Gap800506E8Actor* actor, s32 index);
s32 fn_8005268C(void);
void GXSetProjection(f32 mtx[4][4], s32 type);
void GXSetScissor(u32 left, u32 top, u32 width, u32 height);
void fn_80052694(s32 camera);
Gap800506E8Camera* fn_80052734(s32 index);
Gap800506E8Camera* fn_80052768(s32 index);
void fn_80052798(s32 value);
s32 fn_800527BC(void);
void fn_800527C4(void);

#endif // !__UNKNOWN_gap_800506E8_H_
