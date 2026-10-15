#ifndef __GAME_gap_1658F0_H_
#define __GAME_gap_1658F0_H_

#include "mssbTypes.h"

typedef struct {
    u8 _pad[0x40];
    s16 playerIndex;   /* 0x40 */
    u8 _pad42[0x4];
    u8 unk46;          /* 0x46 */
    u8 unk47;          /* 0x47 */
    u8 _pad48[0x2];
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
