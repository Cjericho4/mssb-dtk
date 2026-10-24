#ifndef __UNKNOWN_gap_80067AC8_H_
#define __UNKNOWN_gap_80067AC8_H_

#include "mssbTypes.h"
typedef struct Gap80067AC8Object Gap80067AC8Object;
extern Gap80067AC8Object* lbl_803CBD30;
void fn_80034CEC(Gap80067AC8Object* obj);
typedef struct Gap80067AC8Status {
    u8 _pad0[0x2A];
    u8 state;
} Gap80067AC8Status;
extern Gap80067AC8Status lbl_80366158;
void fn_800B0A14_removeQueue(void);
typedef struct Gap80067AC8Sound {
    u8 _pad0[0xC0];
    u32 soundC0;
    u8 _padC4[0x2D4];
    /* 0x398 */ u8 enabled398;
    u8 _pad399[0x3];
} Gap80067AC8Sound;
extern Gap80067AC8Sound lbl_800EF808;
void fn_80021518(s32 id, u32 sound);

extern s16 lbl_80108EDC[][5];
s16 fn_80067AC8(s16 key, s8 column);
u8 fn_80067B40(s32 arg0, s16 charID, u8 value);
void fn_80067C48(void);
void fn_80067F70(void);
void fn_800684A4(void);
void fn_80068514(void);
void fn_8006862C(void);
typedef struct Gap80067AC8Voice {
    u8 _pad0[0x50];
} Gap80067AC8Voice;
extern Gap80067AC8Voice lbl_802E4CE8[16];
void fn_800A86B4(s32 mode);
void fn_800A8B78(Gap80067AC8Voice* voice);
void fn_80068720(u8 index);
typedef struct Gap80067AC8TrackPair {
    u8 track;
    u8 unk1;
} Gap80067AC8TrackPair;
extern Gap80067AC8TrackPair lbl_800E88A4[16];
typedef struct Gap80067AC8TrackName {
    char name[0x10];
} Gap80067AC8TrackName;
extern Gap80067AC8TrackName lbl_800E87B4[15];
extern Gap80067AC8Voice lbl_8034E478[16];
void fn_800A8878(s32 a, s32 b);
void fn_800A8AB0(s32 mode);
void fn_800A8E30(Gap80067AC8TrackName* name, Gap80067AC8Voice* voice, s32 a, s32 b);
void fn_8006877C(u8 index);
void fn_80068838(void);
extern u16 lbl_803CBD24;
extern char lbl_80109044[0x10];
typedef struct Gap80067AC8Loader {
    u8 _pad0[0x79C];
    /* 0x79C */ u32 aramAddr;
    u8 _pad7A0[0x60];
} Gap80067AC8Loader;
extern Gap80067AC8Loader lbl_80366B18;
typedef struct Gap80067AC8LoadStatus {
    u8 _pad0[0x715];
    /* 0x715 */ u8 done;
} Gap80067AC8LoadStatus;
extern Gap80067AC8LoadStatus lbl_803C6CF8;
u32 ARAMTransfer(char* name, s32 a, s32 b, s32 c);
void fn_800111B4(u32 aramAddr);
BOOL fn_800697B0(void);
typedef struct Gap80067AC8Stats {
    u8 _pad0[0x46E0]; s32 selected[2];
    u8 _pad46E8[0x21]; u8 indices[2];
    u8 _pad470B[0x4757 - 0x470B];
    /* 0x4757 */ u8 charsOnCharacterGridSelected[54]; /* per-charID "taken" flag on the roster grid */
    /* 0x478D */ u8 rankedByChemistry[5][54];          /* fn_80067C48: ids sorted by chemistry per selected player */
    u8 _pad489B[0x48AE - 0x489B];
    /* 0x48AE */ u8 useAltBirdoGrid;                   /* fn_800698F8: Birdo (grid 0x11) reports grid 0x20 once */
} Gap80067AC8Stats;
typedef struct Gap80067AC8RosterEntry { u8 _pad0[0x24]; s16 id; u8 _pad26[0x7A]; } Gap80067AC8RosterEntry;
extern Gap80067AC8Stats lbl_8034E9A0;
extern Gap80067AC8RosterEntry inMemRoster[2][9];
void fn_80069854(void);
typedef struct Gap80067AC8PanicStrings {
    char file[0x10];     /* "mb_subfunc.c" */
    char notFound[0x1C]; /* 0x10 */
    char badIndex[0x1C]; /* 0x2C */
} Gap80067AC8PanicStrings;
extern Gap80067AC8PanicStrings lbl_800E69B8;
extern u8 lbl_80108DB8[33]; /* mainCharArray: grid index -> base charID */
extern u8 lbl_80108DDC[22]; /* secondaryCharacterArray: colour-variant charIDs */
void OSPanic(char* file, s32 line, char* msg, ...);
s32 fn_800698F8(s32 charID);
void fn_80069A68(void);
void fn_80069A98(void);
void fn_80069AD4(void);

#endif // !__UNKNOWN_gap_80067AC8_H_
