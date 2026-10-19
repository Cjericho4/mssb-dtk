#ifndef __MENUS_rep_10C0_H_
#define __MENUS_rep_10C0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "UnknownHeaders.h"

typedef struct MenusCameraConfig {
    Vec position;
    Vec target;
} MenusCameraConfig;

typedef struct MenusMenuBuffer {
    u8 data[0x4000];
} MenusMenuBuffer;

typedef struct MenusPanelState {
    u8 _pad0[0x80];
    u16* commands[4]; /* 0x80 */
    u8 _pad90[0x1A60];
    MenusMenuBuffer* textBuffer;
    u8 _pad1AF4[0x10];
    s32 unk1B04;
    u8 _pad1B08[0x84];
    s32 unk1B8C;
    u8 _pad1B90[0xE];
    union {
        struct {
            s16 unk1B9E;
            s16 unk1BA0;
        };
        s16 bufferFlags[2];
    };
    u8 _pad1BA2[4];
    s16 unk1BA6;
    s16 unk1BA8;
    s16 unk1BAA;
    u8 _pad1BAC[8];
    s16 unk1BB4;
    u8 _pad1BB6[2];
    s16 unk1BB8;
    u8 _pad1BBA[2];
    s16 values[168]; /* 0x1BBC */
    u8 _pad1D0C[0x15C];
    s16 commandCounters[4]; /* 0x1E68 */
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
    u8 _pad1976E6[0x14];
    s16 unk1976FA;
    u8 _pad1976FC[2];
    s16 unk1976FE;
    u8 _pad197700[0x46];
    s16 objectCount; /* 0x197746 */
    u8 _pad197748[2];
    s16 unk19774A;
    u8 _pad19774C[6];
    s16 unk197752;
    s16 unk197754;
    s16 animations[4]; /* 0x197756; extent unknown */
    u8 _pad19775E[0x1A];
    s16 unk197778;
    s16 unk19777A;
    u8 _pad19777C[0x1A];
    s16 unk197796;
    s16 unk197798;
    u8 _pad19779A[0x90];
    u8 unk19782A;
    u8 unk19782B;
    u8 unk19782C;
    u8 _pad19782D[5];
    u8 unk197832;
    u8 _pad197833[0xB];
    u8 unk19783E;
    u8 unk19783F;
    u8 _pad197840[3];
    s8 unk197843;
    u8 _pad197844;
    u8 unk197845;
    u8 _pad197846[3];
    u8 unk197849;
    u8 _pad19784A[0xB];
    u8 cameraEnabled; /* 0x197855 */
    u8 unk197856;
    u8 _pad197857[0xC];
    s8 inputIndex; /* 0x197863 */
    u8 unk197864;
    u8 _pad197865[0x62];
    u8 copiedFlags[20]; /* 0x1978C7 */
    u8 _pad1978DB[0x18];
    u8 unk1978F3;
    u8 _pad1978F4[7];
    u8 displayMode; /* 0x1978FB */
} Rep10C0State;

extern Rep10C0State* lbl_2_bss_1A824C;

void fn_2_927C8(void);
void fn_2_92A34(void);
void fn_2_92CB0(void);
void fn_2_92F2C(DrawingSceneStruct* scene);
void fn_2_932DC(DrawingSceneStruct* scene);
void fn_2_93BF8(DrawingSceneStruct* scene);
void fn_2_93C64(void);
void fn_2_94604(u8 value);
void fn_2_9461C(s16 value);
void fn_2_94634(s32 index);
void fn_2_946DC(void);

#endif // !__MENUS_rep_10C0_H_
