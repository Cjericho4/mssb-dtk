#ifndef __UNKNOWN_gap_80042D38_H_
#define __UNKNOWN_gap_80042D38_H_

#include "mssbTypes.h"
typedef struct Gap80042D38State {
    u16 unk0;
    u16 current;
    u16 timer;
    u16 previous;
    u16 previousTimer;
} Gap80042D38State;
extern Gap80042D38State* lbl_803CBBCC;

void fn_80042D38(u16 state);
void fn_80042D68(void);
void fn_80042DA8(void);
void challengeStarMenu(void);
void starMenuCursor(void);
void fn_80043880(void);
void fn_80044C98(void);
void fn_8004617C(void);
void fn_800471F4(void);
void fn_80047CE0(void);
void pauseMenuSelection(void);
void fn_800486E0(void);
void fn_80048764(void);
void fn_80048820(void);

#endif // !__UNKNOWN_gap_80042D38_H_
