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
void fn_80067B40(void);
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
void fn_8006877C(void);
void fn_80068838(void);
void fn_800697B0(void);
void fn_80069854(void);
void fn_800698F8(void);
void fn_80069A68(void);
void fn_80069A98(void);
void fn_80069AD4(void);

#endif // !__UNKNOWN_gap_80067AC8_H_
