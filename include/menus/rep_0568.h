#ifndef __MENUS_rep_0568_H_
#define __MENUS_rep_0568_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct MenusAnimationAux MenusAnimationAux;

typedef struct MenusRenderAnimation {
    ActRelatedSub animation;
    f32 time; /* 0x5C */
    f32 blend; /* 0x60 */
    u8 _pad64[4];
    s32 mode; /* 0x68 */
    u8 visible; /* 0x6C */
    u8 _pad6D[0x23];
} MenusRenderAnimation;
typedef struct MenusRenderList {
    u16 count;
    u8 _pad2[0x32];
    MenusRenderAnimation entries[1];
} MenusRenderList;

typedef union MenusAnimationTask {
    QueueEntry queue;
    struct {
        u8 _pad0[0x1C];
        u8 current;
        u8 state;
    };
} MenusAnimationTask;
extern MenusAnimationTask* lbl_2_bss_1224;

typedef struct Rep0568Obj {
    u8 _pad0[0x70];
    u32 context;
} Rep0568Obj;

typedef struct Rep0568State {
    s8 writeIndex;
    s8 readIndex;
    s8 commands[10];
    s32 unkC;
    u8 actionFlags[2]; /* 0x10 */
    u8 pendingActions[2]; /* 0x12 */
    u8 active[8];
    union {
        s8 counters[9];
        u8 holdTimers[9];
        struct {
            u8 _pad1C[4];
            u8 unk20;
        };
    };
    u8 _pad25[2];
    s8 selections[6];
    u8 count;
    u8 selectionFlags[2];
    u8 flags30[2];
    u8 _pad32[0xE];
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
    u8 unk4F;
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
s32 fn_2_18650(s32 index);
void fn_2_18748(void);
void fn_2_188EC(void);
void fn_2_18FBC(void);
void fn_2_190B8(Rep0568Obj* obj);
struct HugeAnimEntry68;
void fn_2_190DC(struct HugeAnimEntry68* entries, f32 matrix[3][4]);
void fn_2_19224(MenusRenderList* list);
void fn_2_1937C(MenusRenderList* list, Mtx matrix);

#endif // !__MENUS_rep_0568_H_
