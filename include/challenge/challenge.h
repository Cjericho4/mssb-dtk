#ifndef __CHALLENGE_challenge_H_
#define __CHALLENGE_challenge_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct ChallengeInput {
    /* 0x0 */ u8 _pad0[2];
    /* 0x2 */ u16 held;
    /* 0x4 */ u16 pressed;
} ChallengeInput;
extern ChallengeInput lbl_803C77B8;

#endif // !__CHALLENGE_challenge_H_
