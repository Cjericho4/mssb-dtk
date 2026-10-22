#ifndef __CHALLENGE_rep_02A8_H_
#define __CHALLENGE_rep_02A8_H_

#include "mssbTypes.h"
#include "challenge/challenge.h"
#include "UnknownHeaders.h"
#include "musyx/musyx.h"

void fn_1_A250(void);
void fn_1_A2E4(void);
extern void (*lbl_1_data_1C8C[5])(void);
void fn_1_C2A4(void);
void fn_1_A348(void);
void fn_1_A464(void);
void fn_1_A634(void);
extern u8 lbl_1_bss_2FEE;
void fn_1_9F04(void);
#include "challenge/challenge.h"
void fn_1_A714(void);
BOOL fn_1_A718(void);
s32 fn_1_A77C(void);
typedef struct ChallengeResource ChallengeResource;
typedef struct ChallengeResources {
    u32 unk0;
    ChallengeResource* files[0xE3];
} ChallengeResources;
s32 fn_1_A7B0(void);
extern u8 lbl_1_bss_2FDB;
extern u8 lbl_1_data_1884[8];
extern u8 lbl_1_bss_2FD9;
extern u8 lbl_1_bss_2FDA;
extern u8 lbl_1_data_1CA0;
extern u8 lbl_1_data_17A4[0x20];
s32 fn_1_A7E4(void);
s32 fn_1_A838(void);
s32 fn_1_A880(void);
s32 fn_1_A8B4(void);
s32 fn_1_A908(void);
void fn_1_A95C(void);
typedef struct ChallengeSoundState {
    u8 _pad0[0xE0];
    u8 pending;
} ChallengeSoundState;
extern ChallengeSoundState lbl_1_common_bss_49994;
extern u8 lbl_1_bss_2FE8;
void fn_1_B4A4(void);
void fn_1_B5B8(void);
void fn_1_BA64(void);
void fn_1_BC00(void);
void fn_1_BDD8(void);
void fn_1_BEF4(s16 voiceID);
u8 fn_800211F0(void);
SND_VOICEID fn_1_BF34(u32 fxId);
void fn_1_BFB0(void);
void fn_1_C188(void);

#endif // !__CHALLENGE_rep_02A8_H_
