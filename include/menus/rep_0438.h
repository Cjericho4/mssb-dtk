#ifndef __MENUS_rep_0438_H_
#define __MENUS_rep_0438_H_

#include "mssbTypes.h"

typedef struct MenusPlayerInput {
    u16 unk0;
    u16 unk2;
    u16 buttons;
} MenusPlayerInput;

/* Menus view of one Static_Stats_Tables row (0xA0 bytes, = game/UnknownHomes_Game.h's CharacterStats with the
   chemistry row as an array). */
typedef struct MenusCharacterStats {
    u8 _pad0[0x37];
    u8 battingDisplay; /* 0x37 menu ratings, 1..10 */
    u8 pitchingDisplay; /* 0x38 */
    u8 runningDisplay; /* 0x39 */
    u8 fieldingDisplay; /* 0x3A */      /* 0x00 StatTable (game/UnknownHomes_Game.h) */
    u8 chemistry[54];    /* 0x3B per-charID chemistry with this character */
    u8 _pad71[0x2F];
} MenusCharacterStats;

typedef struct MenusSaveState {
    MenusCharacterStats stats[6][9]; /* 0x0 Static_Stats_Tables, 54 rows indexed [charID / 9][charID % 9] (fn_2_DFAC) */
    u8 _pad21C0[0x46E0 - 0x21C0];
    s32 players[2];
    u32 timeHigh;
    u32 timeLow;
    u32 alternateTimeHigh;
    u32 alternateTimeLow;
    s8 controllerIndices[4];
    u8 unk46FC;
    s8 unk46FD;
    s8 unk46FE;
    s8 unk46FF;
    u8 _pad4700;
    u8 unk4701;
    u8 _pad4702[0xB];
    u8 captainBanner[2]; /* 0x470D */
    s8 chemistryStars[2]; /* 0x470F average nonzero chemistry excluding captain, quantized 0..5 */
    u8 unk4711;
    u8 _pad4712[0x17];
    u8 unk4729;
    u8 unk472A;
    u8 unk472B;
    MenusPlayerInput input[4];
    u8 _pad4744[4];
    struct DrawingSceneStruct* scene; /* 0x4748 */
    u8 _pad474C[8];
    u8 unk4754;
    u8 unk4755;
    u8 unk4756;
    u8 charTaken[54]; /* 0x4757 charsOnCharacterGridSelected: per-charID taken/unavailable flag on the select grid */
    u8 _pad478D[0x10E];
    u8 resetData[0x12]; /* 0x489B */
    u8 unk48AD;
    u8 _pad48AE;
    u8 unk48AF;
    u8 _pad48B0;
    u8 unk48B1;
    u8 _pad48B2;
    u8 unk48B3;
} MenusSaveState;

extern MenusSaveState lbl_8034E9A0;

void fn_2_12238(void);
void fn_2_123CC(void);
void fn_2_12988(void);
void fn_2_129AC(void);
void fn_2_129D0(void);
void fn_2_12A70(void);
void fn_2_12B60(void);
void fn_2_12C34(void);
void fn_2_12CD8(void);
void fn_2_12F88(void);

#endif // !__MENUS_rep_0438_H_
