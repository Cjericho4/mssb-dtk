#ifndef __GAME_gap_1658F0_H_
#define __GAME_gap_1658F0_H_

#include "mssbTypes.h"

typedef struct {
    s8 oldFlags;
    s8 newFlags;
} ScoutFlagPair;

typedef struct {
    ScoutFlagPair scoutFlags[9]; /* 0x00 */
    u8 _pad12[0x40 - 0x12];
    s16 playerIndex;   /* 0x40 */
    s16 unk42;         /* 0x42 */
    u8 _pad44[0x2];
    u8 unk46;          /* 0x46 */
    u8 unk47;          /* 0x47 */
    u8 unk48;          /* 0x48 */
    u8 _pad49;
    u8 field_0x4A;
} Bss37400Item;

extern Bss37400Item lbl_3_common_bss_37400;

void fn_3_1658F0(void);
void fn_3_165978(void);
void fn_3_16598C(void);
void fn_3_1659A0(void);
void fn_3_165D24(void);
void fn_3_1663AC(void);

#endif // !__GAME_gap_1658F0_H_
