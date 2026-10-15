#ifndef __GAME_rep_EA0_H_
#define __GAME_rep_EA0_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct {
    u8 _pad0[0xC];          // 0x00-0x0B
    s32 unkC;               // 0x0C
    u8 _padC[0x14A4 - 0x10]; // 0x10-0x14A3
    f32 unk14A4;            // 0x14A4
    f32 unk14A8;            // 0x14A8
} Bss200Struct;
extern Bss200Struct lbl_3_bss_200;

extern f32 lbl_3_rodata_F20;

typedef struct Elem6750CSub {
    u8 _pad0[0x1C];
} Elem6750CSub;

typedef struct Elem6750C {
    u8 _pad0[0x4];
    Elem6750CSub sub; /* 0x04 */
} Elem6750C; /* size 0x20 */

typedef struct Data6880Entry {
    union {
        s32 index;
        Elem6750CSub* ptr;
    };                 /* 0x00 */
    f32 unk4;          /* 0x04 */
    f32 unk8;          /* 0x08 */
    s32 unkC;          /* 0x0C */
} Data6880Entry; /* size 0x10 */

extern Data6880Entry lbl_3_data_6880[12];
extern s32 lbl_3_bss_169C;

void fn_3_6750C(Elem6750C* elems);
void fn_3_675B8(u16 arg0);
void fn_3_67620(void);
void fn_3_678B8(void);
void fn_3_67A48(void);
void fn_3_67C34(void);
void fn_3_67EF0(void);
void fn_3_685F0(void);
void fn_3_68BB4(void);
void fn_3_690FC(void);
void fn_3_6916C(void);
void fn_3_69184(void);
void fn_3_692E0(void);
void fn_3_695F8(void);
void fn_3_697CC(void);

#endif // !__GAME_rep_EA0_H_
