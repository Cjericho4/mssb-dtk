#ifndef __UNKNOWN_gap_80048BEC_H_
#define __UNKNOWN_gap_80048BEC_H_

#include "mssbTypes.h"
extern void (*lbl_800FBE64[])(s32 a, s32 b, s32 c);
struct Gap80048BECActor;
typedef struct Gap80048BECMenu {
    u8 _pad0[0x16];
    u16 id;
} Gap80048BECMenu;
extern Gap80048BECMenu lbl_803C5F74;
void fn_8000FE08(u16 id, s32 a, s32 b);
typedef struct Gap80048BECTiming {
    s32 unk0;
    s32 requested;
    s32 limit;
} Gap80048BECTiming;
extern s32 lbl_803CB874;
extern s32 lbl_803CB878;
extern s32 lbl_803CB83C[2];
extern s32 lbl_803CBD00;
extern s32 lbl_803CBD04;
extern s32 lbl_803CBD08;
extern s32 lbl_803CBD0C;
typedef struct Gap80048BECObj {
    u8 _pad0[0x3E];
    /* 0x3E */ u8 state;
    u8 _pad3F[0x1BB];
    u16 actorIndex; /* 0x1FA */
} Gap80048BECObj;

extern s32 lbl_803CB848;
extern s32 lbl_803CBCE8;
extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD0C;

void fn_80048BEC(Gap80048BECTiming* timing);
void fn_80048C14(s32 value);
void fn_80048C1C(void);
void fn_80048C28(void);
void fn_80048D4C(void);
void fn_80048E00(void);
s32 fn_80048EA8(s32 index);
void startGameRelated(void);
void fn_80049220(void);
void fn_800494CC(void);
void possiblyTransferDataBetweenDifferentRels(void);
void fn_80049C80(void);
void fn_80049D3C(void);
void fn_80049D8C(void);
void fn_8004A0FC(void);
void fn_8004A1BC(void);
void fn_8004A2BC(void);
BOOL fn_8004A328(Gap80048BECObj* obj);
void fn_8004A34C(void);
void fn_8004A5B8(void);
void fn_8004A7D0(void);
void fn_8004A9E0(void);
void Set_803cb848(s32 value);
s32 fn_8004ABE0(void);
s32 fn_8004ABE8(BOOL clear);
void fn_8004AC00(void);
s32 fn_8004ACC4(BOOL clear);
s32 fn_8004ACDC(BOOL clear);
void fn_8004ACF4(void);
void fn_8004AD54(void);
void fn_8004AE18(void);
void fn_8004AFA8(void);
void fn_8004B1B8(s32 value);
void fn_8004B1C0(s32 index, s32 a, s32 b, s32 c);
void fn_8004B208(void);
void fn_8004B270(void);
void fn_8004B284(void);
void fn_8004B6EC(void);
s32 fn_8004B7B4(Gap80048BECObj* obj, struct Gap80048BECActor** actor);
void fn_8004B7F4(void);
void fn_8004BAEC(void);
void fn_8004BD6C(void);
void fn_8004BEB0(void);
void fn_8004C094(void);
void fn_8004C108(void);
void fn_8004C19C(void);
void fn_8004C510(void);
void fn_8004C5F8(void);
void fn_8004C9FC(void);
void fn_8004CA08(s32 value);
void fn_8004CA14(s32 a, s32 b);

typedef struct Gap80048BECActor Gap80048BECActor;
s32 fn_800B2BA8(Gap80048BECActor* actor, u16 index, Gap80048BECActor* other, u16 otherIndex);

#endif // !__UNKNOWN_gap_80048BEC_H_
