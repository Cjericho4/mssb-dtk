#ifndef __MENUS_rep_0B08_H_
#define __MENUS_rep_0B08_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "menus/rep_1028.h"
#include "menus/gap_3C03C.h"

typedef struct Rep0B08AnimationConfig {
    s16 animation;
    s16 time;
    u8 flag;
    u8 _pad5;
} Rep0B08AnimationConfig;

typedef struct Rep0B08Obj {
    /* 0x00 */ Vec position;
    Vec previousPosition; /* 0x0C */
    Vec velocity; /* 0x18 */
    u8 _pad24[0x14];
    f32 unk38;
    f32 unk3C;
    u8 _pad40[0xC];
    f32 angle; /* 0x4C */
    f32 unk50;
    u8 _pad54[0x18];
    f32 unk6C;
    f32 unk70;
    u8 _pad74[0xC];
    s32 index;
    u8 _pad84[8];
    f32 unk8C;
    u8 _pad90[4];
    /* 0x94 */ s16 state;
    /* 0x96 */ u8 _pad96[0xA];
    s16 unkA0;
    /* 0xA2 */ s16 countdown;
    u8 _padA4[0x10];
    s16 unkB4;
    u8 _padB6[4];
    u8 unkBA;
    u8 unkBB;
    u8 _padBC[4];
    u8 unkC0;
    u8 _padC1[2];
    u8 variant; /* 0xC3 */
    u8 unkC4;
    u8 _padC5[5];
    u8 unkCA;
    s8 unkCB;
    s8 unkCC;
    s8 unkCD;
    u8 unkCE;
    u8 unkCF;
    u8 unkD0;
    u8 _padD1[3];
    void (*callback)(struct Rep0B08Obj*); /* 0xD4 */
} Rep0B08Obj;

typedef struct MenusSceneState {
    Gap3C03CObj gap3C03CObjects[1]; /* extent unknown */
    u8 _pad34[0x15D2];
    u8 unk1606;
    u8 _pad1607[9];
    Rep0B08Obj rep0B08Objects[14];
    Rep1028Obj rep1028Objects[29]; /* 0x21E0 */
    u8 _pad372C[0x98C];
    s16 choiceGrid[9][3]; /* 0x40B8 */
    u8 _pad40EE[2];
    MenusChoiceRecord choices[1]; /* 0x40F0; extent unknown */
    u8 _pad40FA[0x2C2];
    s16 counter; /* 0x43BC */
    s16 previousCounter;
    u8 _pad43C0[0x55];
    u8 unk4415;
    u8 unk4416;
    u8 _pad4417[4];
    u8 unk441B;
    u8 unk441C;
    u8 _pad441D[3];
    u8 unk4420;
    u8 _pad4421;
    u8 unk4422;
    u8 _pad4423;
    u8 unk4424;
    u8 unk4425;
    u8 unk4426;
    u8 _pad4427[8];
    u8 unk442F;
    u8 _pad4430[0xC2];
    u8 unk44F2;
} MenusSceneState;

extern MenusSceneState* lbl_2_bss_1A8248;

void fn_2_6832C(void);
void fn_2_683EC(void);
void fn_2_684D0(void);
void fn_2_68638(s32 index, u8 value);
void fn_2_68654(s32 index, u8 value);
s32 fn_2_68670(s32 index);
s32 fn_2_68690(s32 index);
s32 fn_2_686B0(s32 index);
void fn_2_686D0(s32 index, u8 value);
void fn_2_686EC(void);
void fn_2_687A4(void);
f32 fn_2_688A4(s32 index, s32 target);
f32 fn_2_68940(s32 firstIndex, s32 secondIndex);
void fn_2_689CC(void);
void fn_2_68A88(void);
void fn_2_68B54(void);
void fn_2_68C80(void);
void fn_2_68D90(s32 index, u8 value);
void fn_2_68DAC(s32 index, Vec* out);
void fn_2_68DE8(s32 index, Vec* out);
void fn_2_68E68(void);
void fn_2_68F08(s32 index, u8 value);
void fn_2_68F24(s32 index, s32 animation);
void fn_2_68FBC(void);
void fn_2_69070(void);
void fn_2_692D0(void);
void fn_2_69554(void);
void fn_2_696D4(s32 index);
void fn_2_69710(void);
void fn_2_698EC(void);
void fn_2_699D4(void);
void fn_2_69E1C(s32 index);
void fn_2_6A450(void);
void fn_2_6A5A8(s32 index);
void fn_2_6A628(void);
void fn_2_6A708(void);
void fn_2_6A87C(void);
void fn_2_6AAB8(void);
void fn_2_6AABC(s32 index, Vec* position);
void fn_2_6AB3C(void);
void fn_2_6ABFC(void);
void fn_2_6ACF0(void);
void fn_2_6ACF4(void);
void fn_2_6AE08(void);
void fn_2_6AF80(s32 index, u8 value);
BOOL fn_2_6AF9C(s32 index);
s32 fn_2_6AFD4(s32 index);
void fn_2_6B024(void);
void fn_2_6B120(void);
void fn_2_6B238(void);
void fn_2_6B4C4(Rep0B08Obj* obj);
void fn_2_6B4FC(void);
void fn_2_6B620(void);
void fn_2_6B744(void);
void fn_2_6BA18(Rep0B08Obj* obj);
void fn_2_6BA50(Rep0B08Obj* obj);
void fn_2_6BAAC(Rep0B08Obj* obj);
void fn_2_6BAD8(Rep0B08Obj* obj);
void fn_2_6BB7C(Rep0B08Obj* obj);
void fn_2_6BBC8(Rep0B08Obj* obj);
void fn_2_6BC00(Rep0B08Obj* obj);
void fn_2_6BC0C(Rep0B08Obj* obj);
void fn_2_6BCAC(void);
void fn_2_6BD9C(Rep0B08Obj* obj);
void fn_2_6BDD4(Rep0B08Obj* obj);
void fn_2_6BDE0(Rep0B08Obj* obj);
void fn_2_6BE80(void);
void fn_2_6BF88(Rep0B08Obj* obj);
void fn_2_6BFC0(Rep0B08Obj* obj);
void fn_2_6C020(void);
void fn_2_6C120(Rep0B08Obj* obj);
void fn_2_6C190(void);
void fn_2_6C28C(Rep0B08Obj* obj);
void fn_2_6C2C4(void);
void fn_2_6C2E8(Rep0B08Obj* obj);
void fn_2_6C348(void);
void fn_2_6C5E0(void);
void fn_2_6C938(Rep0B08Obj* obj);
void fn_2_6C970(Rep0B08Obj* obj);
void fn_2_6C97C(Rep0B08Obj* obj);
void fn_2_6C988(void);
void fn_2_6CB78(Rep0B08Obj* obj);
void fn_2_6CBB0(void);
void fn_2_6CCB8(void);
void fn_2_6CDD4(void);
void fn_2_6D040(Rep0B08Obj* obj);
void fn_2_6D078(Rep0B08Obj* obj);
void fn_2_6D088(void);
void fn_2_6D164(void);
void fn_2_6D250(Rep0B08Obj* obj);
void fn_2_6D288(Rep0B08Obj* obj);
void fn_2_6D298(void);
void fn_2_6D374(void);
void fn_2_6D4B0(Rep0B08Obj* obj);
void fn_2_6D4E8(Rep0B08Obj* obj);
void fn_2_6D4F8(void);
void fn_2_6D5D4(void);
void fn_2_6D710(Rep0B08Obj* obj);
void fn_2_6D748(Rep0B08Obj* obj);
void fn_2_6D754(void);
void fn_2_6D840(Rep0B08Obj* obj);
void fn_2_6D878(void);
void fn_2_6D968(void);
void fn_2_6DB30(void);
void fn_2_6DE54(void);
void fn_2_6E1D0(void);
void fn_2_6E848(Rep0B08Obj* obj);
void fn_2_6E880(Rep0B08Obj* obj);
void fn_2_6E88C(void);
void fn_2_6EA74(void);
void fn_2_6ED30(void);
void fn_2_6F104(void);
void fn_2_6F6F4(Rep0B08Obj* obj);
void fn_2_6F72C(Rep0B08Obj* obj);
void fn_2_6F78C(void);
void fn_2_6F88C(void);
void fn_2_6FB0C(void);
void fn_2_6FE34(Rep0B08Obj* obj);
void fn_2_6FE6C(void);
void fn_2_70110(void);
void fn_2_7045C(Rep0B08Obj* obj);
void fn_2_70494(Rep0B08Obj* obj);
void fn_2_704A0(Rep0B08Obj* obj);
void fn_2_704AC(void);
void fn_2_70588(Rep0B08Obj* obj);
void fn_2_705C0(void);
void fn_2_709A0(void);
void fn_2_71098(void);
void fn_2_71A38(Rep0B08Obj* obj);
void fn_2_71A70(void);
void fn_2_71B80(void);
void fn_2_71C6C(void);

#endif // !__MENUS_rep_0B08_H_
