#ifndef __CHALLENGE_rep_0250_H_
#define __CHALLENGE_rep_0250_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
#include "game/rep_3448.h"
extern s32 lbl_1_data_B88[];
#include "UnknownHeaders.h"
#include "challenge/challenge.h"

extern u8 lbl_1_bss_2FAA;
extern u8 lbl_1_bss_2FB9;

typedef struct ChallengeLayoutPosition {
    u8 _pad0[0x14];
    s16 x;
    s16 y;
} ChallengeLayoutPosition;
typedef struct ChallengeLayoutConfig {
    u8 _pad0[0x14];
    u8 id;
} ChallengeLayoutConfig;
extern u16 lbl_1_bss_2FAC;
extern DrawingSceneStruct* lbl_1_bss_2FCC;
extern ChallengeLayoutConfig lbl_1_data_CC8;
ChallengeLayoutPosition* fn_80035F20(s32 id, s32 mode, s32 index, s16 next);
void fn_80035ED0(s32 mode);
void fn_80035EEC(s32 id, s32 index);
void fn_1_8CD4(void);
void fn_1_8DBC(void);
void fn_1_8F34(void);
void fn_1_90B8(void);
void fn_1_90E4(void);
typedef struct ChallengeLayoutState {
    u8 _pad0[2];
    u8 selected;
    u8 _pad3[4];
    u8 mode;
    u8 _pad8[9];
    u8 previous;
} ChallengeLayoutState;
extern ChallengeLayoutState lbl_1_bss_2FA8;
void fn_1_9290(void);
void fn_1_9380(void);
void fn_1_96A4(void);
void fn_1_96D0(void);
void fn_1_96D4(void);
void fn_1_973C(void);
void fn_1_97B8(void);
void fn_1_97E4(void);
void fn_1_9AB0(void);

#endif // !__CHALLENGE_rep_0250_H_
