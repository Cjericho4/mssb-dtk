#ifndef __CHALLENGE_gap_85A8_H_
#define __CHALLENGE_gap_85A8_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
#include "game/rep_3448.h"

typedef struct Gap85A8State {
    /* 0x00 */ u8 _pad0[8];
    /* 0x08 */ s32 mode;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 pending;
    /* 0x0E */ u8 _padE;
    /* 0x0F */ u8 unkF;
    /* 0x10 */ u8 previous;
} Gap85A8State;
extern Gap85A8State lbl_1_common_bss_47674;
typedef struct Gap85A8Cursor {
    /* 0x000 */ u8 _pad0[0x22A];
    /* 0x22A */ s16 count;
    /* 0x22C */ u8 _pad22C[2];
    /* 0x22E */ s16 cursor;
    /* 0x230 */ u8 _pad230[0x190];
} Gap85A8Cursor;
extern Gap85A8Cursor lbl_1_common_bss_472B4;
#include "UnknownHeaders.h"

void fn_1_85A8(void);
void fn_1_8624(void);
void fn_1_86BC(void);
void fn_1_86E4(void);
void fn_1_8770(void);
void fn_1_88CC(void);
void fn_1_88D0(void);
void fn_1_8A90(void);
void fn_1_8B8C(void);
void fn_1_8B90(void);
typedef struct ChallengeResetFlags {
    u16 count;
    union {
        u8 flags[11];
        struct {
            u8 _pad2[10];
            u8 active;
        };
    };
} ChallengeResetFlags;
extern ChallengeResetFlags lbl_1_common_bss_47698;
void fn_1_8C9C(void);

#endif // !__CHALLENGE_gap_85A8_H_
