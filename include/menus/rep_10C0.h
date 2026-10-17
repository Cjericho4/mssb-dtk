#ifndef __MENUS_rep_10C0_H_
#define __MENUS_rep_10C0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct MenusCameraConfig {
    Vec position;
    Vec target;
} MenusCameraConfig;

typedef struct MenusMenuBuffer {
    u8 data[0x4000];
} MenusMenuBuffer;

typedef struct MenusPanelState {
    u8 _pad0[0x1B9E];
    s16 unk1B9E;
    s16 unk1BA0;
    u8 _pad1BA2[8];
    s16 unk1BAA;
    u8 _pad1BAC[0x2C4];
    s16 unk1E70;
    s16 unk1E72;
    u8 _pad1E74[0x18];
    u8 mode;
    u8 _pad1E8D[3];
} MenusPanelState;

typedef struct Rep10C0State {
    u8 _pad0[0x195424];
    u32 timeHigh;
    u32 timeLow;
    MenusPanelState panel;
    u8 flag1972BC;
    u8 _pad1972BD[3];
    u8 flag1972C0;
    u8 _pad1972C1[0x3A7];
    MenusCameraConfig camera; /* 0x197668 */
    u8 _pad197680[4];
    MenusMenuBuffer* buffer; /* 0x197684 */
    u8 _pad197688[4];
    u32 unk19768C;
    u32 unk197690;
    u32 unk197694;
    u8 _pad197698[4];
    s32 animationIndex; /* 0x19769C */
    u8 _pad1976A0[0x36];
    s16 unk1976D6;
    u8 _pad1976D8[0xC];
    s16 unk1976E4;
    u8 _pad1976E6[0x60];
    s16 objectCount; /* 0x197746 */
    u8 _pad197748[2];
    s16 unk19774A;
    u8 _pad19774C[6];
    s16 unk197752;
    s16 unk197754;
    s16 animations[4]; /* 0x197756; extent unknown */
    u8 _pad19775E[0xCC];
    u8 unk19782A;
    u8 unk19782B;
    u8 unk19782C;
    u8 _pad19782D[5];
    u8 unk197832;
    u8 _pad197833[0x10];
    s8 unk197843;
    u8 _pad197844[5];
    u8 unk197849;
    u8 _pad19784A[0xB];
    u8 cameraEnabled; /* 0x197855 */
    u8 unk197856;
    u8 _pad197857[0xC];
    s8 inputIndex; /* 0x197863 */
    u8 _pad197864[0x97];
    u8 displayMode; /* 0x1978FB */
} Rep10C0State;

extern Rep10C0State* lbl_2_bss_1A824C;

void fn_2_927C8(void);
void fn_2_92A34(void);
void fn_2_92CB0(void);
void fn_2_92F2C(void);
void fn_2_932DC(void);
void fn_2_93BF8(void);
void fn_2_93C64(void);
void fn_2_94604(u8 value);
void fn_2_9461C(s16 value);
void fn_2_94634(s32 index);
void fn_2_946DC(void);

#endif // !__MENUS_rep_10C0_H_
