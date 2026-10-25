#ifndef __GAME_gap_90754_H_
#define __GAME_gap_90754_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

extern u8 lbl_3_data_81D4[];

typedef struct {
    u8 _pad[0x11820];
    u8 field_0x11820;
    u8 field_0x11821;
} Gap90754Struct;

void fn_3_90754(Gap90754Struct* arg0, u8 arg1, u8 arg2);
s32 fn_3_90764(void);
s32 fn_3_90798(void);
void fn_3_9081C(void);
s32 fn_3_90860(void);
void fn_3_908E8(void);
s32 fn_3_90928(void);
extern s32 fn_8006285C(void);
void fn_3_909B0(void);
s32 fn_3_90A18(void);
void fn_3_90AB0(s32 charID);
extern s32 fn_800698F8(s32 charID);
s32 fn_3_90B14(u8 charID, s32 altCharID);
void fn_800216F8(u8 fileID, s32 (*callback)(void));
s32 fn_3_90C14(s32 charID);
void fn_3_90CB0(void);
void fn_3_90DD8(void);
s32 fn_3_90F48(void);
s32 fn_3_91064(void);
s32 fn_3_910AC(void);
void fn_3_910F4(s32 scene);
void fn_3_911A8(void);

#endif // !__GAME_gap_90754_H_
