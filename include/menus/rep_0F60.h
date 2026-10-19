#ifndef __MENUS_rep_0F60_H_
#define __MENUS_rep_0F60_H_

#include "mssbTypes.h"
#include "menus/rep_0568.h"

typedef struct MenusAnimationResource {
    u32 resource;
    u32 size;
    u8 _pad8[8];
} MenusAnimationResource;
extern MenusAnimationResource lbl_2_data_2F990[];

void fn_2_8ACE0(void);
void fn_2_8AEE0(void);
void fn_2_8B118(f32 value);
void fn_2_8B158(void);
void fn_2_8B2C0(void);
void fn_2_8B418(void);
void fn_2_8C724(void);
void fn_2_8C80C(s32 resource, s32 start, s32 count, s32 mode, s32 flags);
void fn_2_8C910(void);
BOOL fn_2_8CC88(s32 index);
void fn_2_8CCAC(s32 index, u8 value);
void fn_2_8CCCC(s32 index, s32 animation, u8 flag, u8 mode, u8 value263, s16 value6C, u8 value266, s32 value26A);
void fn_2_8CD58(s32 index, s32 animation, u8 flag, u8 mode, s16 time, u8 value266, u8 duration);
void fn_2_8D024(void);
void fn_2_8D24C(Rep0568Obj* obj);
void fn_2_8D270(u8 index);
void fn_2_8D9DC(s32 mode);
void fn_2_8DB14(void);
void fn_2_8DC00(void);
void fn_2_8DCD8(void);
void fn_2_8DFB0(void);
void fn_2_8E478(void);

#endif // !__MENUS_rep_0F60_H_
