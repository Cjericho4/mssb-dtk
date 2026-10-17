#ifndef __MENUS_rep_0568_H_
#define __MENUS_rep_0568_H_

#include "mssbTypes.h"

typedef struct Rep0568Obj {
    u8 _pad0[0x70];
    u32 context;
} Rep0568Obj;

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
void fn_2_190DC(void);
void fn_2_19224(void);
void fn_2_1937C(void);

#endif // !__MENUS_rep_0568_H_
