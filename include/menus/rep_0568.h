#ifndef __MENUS_rep_0568_H_
#define __MENUS_rep_0568_H_

#include "mssbTypes.h"

typedef struct MenusAnimationAux MenusAnimationAux;

typedef struct Rep0568Obj {
    u8 _pad0[0x70];
    u32 context;
} Rep0568Obj;

typedef struct Rep0568State {
    u8 _pad0[0xC];
    s32 unkC;
    u8 _pad10[4];
    u8 active[8];
    union {
        s8 counters[9];
        u8 holdTimers[9];
        struct {
            u8 _pad1C[4];
            u8 unk20;
        };
    };
    u8 _pad25[8];
    u8 count;
    u8 _pad2E[0x12];
    union {
        u8 flags[13];
        struct {
            u8 _pad40[6];
            u8 values[4];
            u8 unk4A;
            u8 unk4B;
            u8 unk4C;
        };
    };
    u8 _pad4D;
    u8 unk4E;
    u8 _pad4F;
    u8 unk50;
    u8 unk51;
    u8 _pad52[2];
} Rep0568State;
extern Rep0568State lbl_2_bss_100B8;

void fn_800B9AA8(u32 context);

void fn_2_16A98(void);
void fn_2_16CE0(void);
void fn_2_16D38(void);
void fn_2_16DA8(void);
void fn_2_16F0C(void);
void fn_2_16F78(void);
void fn_2_17648(void);
void fn_2_17AB8(void);
void fn_2_17C88(void);
void fn_2_17ED8(void);
void fn_2_18148(void);
void fn_2_18398(void);
void fn_2_18650(void);
void fn_2_18748(void);
void fn_2_188EC(void);
void fn_2_18FBC(void);
void fn_2_190B8(Rep0568Obj* obj);
struct HugeAnimEntry68;
void fn_2_190DC(struct HugeAnimEntry68* entries, f32 matrix[3][4]);
void fn_2_19224(void);
void fn_2_1937C(void);

#endif // !__MENUS_rep_0568_H_
