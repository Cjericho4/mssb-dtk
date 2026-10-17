#ifndef __MENUS_rep_1028_H_
#define __MENUS_rep_1028_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct Rep1028Config {
    Vec position;
    f32 value;
    u8 _pad10[4];
} Rep1028Config;

typedef struct Rep1028Obj {
    /* 0x00 */ Vec position;
    u8 _padC[0x1C];
    f32 unk28;
    u8 _pad2C[4];
    f32 unk30;
    u8 _pad34[4];
    f32 unk38;
    f32 unk3C;
    u8 _pad40[0x38];
    s32 index;
    s32 unk7C;
    f32 unk80;
    f32 unk84;
    u8 _pad88[4];
    f32 unk8C;
    /* 0x90 */ s16 state;
    s16 unk92;
    s16 unk94;
    u8 _pad96[6];
    s16 countdown;
    u8 _pad9E[2];
    s16 unkA0;
    u8 _padA2[4];
    s16 unkA6;
    u8 unkA8;
    u8 _padA9;
    u8 unkAA;
    u8 variant; /* 0xAB */
    u8 unkAC;
    u8 unkAD;
    s8 unkAE;
    u8 _padAF[3];
    u8 unkB2;
    u8 _padB3;
    u8 unkB4;
    u8 _padB5[3];
    void (*callback)(struct Rep1028Obj*); /* 0xB8 */
} Rep1028Obj;

void fn_2_8F0F4(void);
void fn_2_8F27C(void);
void fn_2_8F3D4(void);
void fn_2_8F528(void);
void fn_2_8F640(void);
void fn_2_8F688(void);
void fn_2_8F6D0(s32 index, s32 action);
u8 fn_2_8F720(s32 index);
void fn_2_8F73C(s32 index, u8 value);
void fn_2_8F758(s32 index, u8 value);
f32 fn_2_8F774(s32 index);
void fn_2_8F7B0(s32 index, s16 id);
void fn_2_8F838(s32 index, s16 id);
void fn_2_8F8C0(s32 index, s16 id);
void fn_2_8F948(s32 index, s16 id);
void fn_2_8F9D0(s32 index, s16 id);
void fn_2_8FA58(s32 index, s16 id);
void fn_2_8FAE0(s32 index, s16 id);
void fn_2_8FB68(s32 index, s16 id);
void fn_2_8FBF8(s32 index, s16 id);
void fn_2_8FC88(s32 index);
void fn_2_8FD14(void);
void fn_2_8FDB0(void);
void fn_2_8FE9C(void);
void fn_2_9007C(void);
void fn_2_9033C(s32 index, Vec* position, f32 value);
void fn_2_903A8(s32 index);
void fn_2_90428(s32 index);
void fn_2_904A8(void);
void fn_2_90538(void);
void fn_2_9061C(Rep1028Obj* obj);
void fn_2_90628(Rep1028Obj* obj);
void fn_2_90698(Rep1028Obj* obj);
void fn_2_90718(Rep1028Obj* obj);
void fn_2_907F4(Rep1028Obj* obj);
void fn_2_9082C(Rep1028Obj* obj);
void fn_2_90838(Rep1028Obj* obj);
void fn_2_90888(Rep1028Obj* obj);
void fn_2_908FC(Rep1028Obj* obj);
void fn_2_90934(Rep1028Obj* obj);
void fn_2_90940(Rep1028Obj* obj);
void fn_2_9094C(Rep1028Obj* obj);
void fn_2_909F4(Rep1028Obj* obj);
void fn_2_90A2C(Rep1028Obj* obj);
void fn_2_90AB0(Rep1028Obj* obj);
void fn_2_90ABC(void);
void fn_2_90BD0(Rep1028Obj* obj);
void fn_2_90C08(Rep1028Obj* obj);
void fn_2_90C14(Rep1028Obj* obj);
void fn_2_90C4C(Rep1028Obj* obj);
void fn_2_90CD0(Rep1028Obj* obj);
void fn_2_90DAC(Rep1028Obj* obj);
void fn_2_90DE4(void);
void fn_2_90E98(Rep1028Obj* obj);
void fn_2_90EC4(void);
void fn_2_91058(void);
void fn_2_911E0(Rep1028Obj* obj);
void fn_2_91218(Rep1028Obj* obj);
void fn_2_9129C(Rep1028Obj* obj);
void fn_2_912A8(void);
void fn_2_91450(Rep1028Obj* obj);
void fn_2_91488(Rep1028Obj* obj);
void fn_2_9150C(Rep1028Obj* obj);
void fn_2_91518(void);
void fn_2_916C0(Rep1028Obj* obj);
void fn_2_916F8(Rep1028Obj* obj);
void fn_2_9177C(Rep1028Obj* obj);
void fn_2_91788(void);
void fn_2_918A4(Rep1028Obj* obj);
void fn_2_918DC(Rep1028Obj* obj);
void fn_2_918E8(Rep1028Obj* obj);
void fn_2_918F4(Rep1028Obj* obj);
void fn_2_9197C(Rep1028Obj* obj);
void fn_2_919B4(Rep1028Obj* obj);
void fn_2_919C0(Rep1028Obj* obj);
void fn_2_919CC(void);
void fn_2_91AE4(Rep1028Obj* obj);
void fn_2_91B1C(Rep1028Obj* obj);
void fn_2_91B28(void);
void fn_2_91B2C(Rep1028Obj* obj);
void fn_2_91B38(Rep1028Obj* obj);
void fn_2_91B70(Rep1028Obj* obj);
void fn_2_91B7C(void);
void fn_2_91B80(Rep1028Obj* obj);
void fn_2_91C08(Rep1028Obj* obj);
void fn_2_91C40(Rep1028Obj* obj);
void fn_2_91C4C(void);
void fn_2_91D74(void);

#endif // !__MENUS_rep_1028_H_
