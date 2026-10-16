/* fn_3_CB538 (rep_2390.c) NONMATCHING best attempt.
 * ~31 lines differ, all register allocation: target has arg0 in r28 and idx/loop counter in r29 (mine swapped), and lbl_3_data_18180[idx].unk0 store is add+stw 0 instead of stwx. Decl-order brute force, ternary/if forms, separate loop counter did not help.
 * Needs the file-scope declarations below (in rep_2390.c) plus fn_3_CB538.headers.diff
 * (UnknownHeaders.h: AnimationStruct.unk25A, CommonBss_35154.unk_44C; rep_2390.h/rep_1E08.c: fn_3_CB538(s32)).
 */

#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1E08.h"
#include "Dolphin/mtx.h"

typedef struct {
    s32 unk0; /* 0x00 */
    s32 unk4; /* 0x04 */
    u8 _pad8[0x48];
} Rep2390Seg; /* size 0x50 */

typedef struct {
    s32 unk0; /* 0x00 */
    u8 _pad4[0x40];
} Rep2390Seg44; /* size 0x44 */

/* lbl_3_data_17DC0 overlay; 0x3C0 onwards is also labelled lbl_3_data_18180 */
typedef struct {
    Rep2390Seg segs[12];     /* 0x000 */
    Rep2390Seg44 extra[3];   /* 0x3C0 */
    Vec v48C;                /* 0x48C */
    Vec v498;                /* 0x498 */
} Rep2390Data;

typedef struct {
    u16 a;
    u16 b;
} Rep2390Pair;

extern Rep2390Data lbl_3_data_17DC0;
extern Rep2390Seg44 lbl_3_data_18180[];
extern Rep2390Pair lbl_3_data_6660[];
void fn_80030D88(Vec* a, Vec* b, Rep2390Seg* seg, s32 n);
void fn_80030470(Vec* a, Vec* b, Vec* c, Rep2390Seg* seg, s32 n);
void fn_8002F5F4(Vec* a, Vec* b);


void fn_3_CB538(s32 arg0) {
    Vec d;
    Vec d2;
    Rep2390Seg* e;
    Rep2390Seg44* x;
    s32 idx;
    s32 i;
    s32 val;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        idx = 2;
    } else {
        idx = g_Ball.framesSinceHit > 0;
    }
    PSVECSubtract(&lbl_3_common_bss_35154.unk_44C, (Vec*)&lbl_3_common_bss_35154.unk_440, &d);
    if (!PSVECMag(&d)) {
        return;
    }
    e = &lbl_3_data_17DC0.segs[idx * 3];
    x = &lbl_3_data_18180[idx];
    val = lbl_3_common_bss_35154.unk4;
    e[2].unk0 = val;
    e[1].unk0 = val;
    x->unk0 = val;
    e[0].unk0 = val;
    if (arg0 == 2) {
        e[0].unk4 = 0x1B;
        e[1].unk4 = 0x1C;
    } else {
        e[0].unk4 = 0x15;
        e[1].unk4 = 7;
    }
    fn_8002F5F4((Vec*)&lbl_3_common_bss_35154.unk_440, &d);
    if (lbl_80366158._28 != 0) {
        return;
    }
    for (idx = 1; idx < 3; idx++) {
        fn_80030D88((Vec*)&lbl_3_common_bss_35154.unk_440, &d, &e[idx], 5);
    }
    PSVECNormalize(&d, &d);
    PSVECSubtract((Vec*)&lbl_3_common_bss_35154.unk_440, &lbl_3_common_bss_35154.unk_44C, &d2);
    fn_80030470((Vec*)&lbl_3_common_bss_35154.unk_440, &d, &d2, e, 5);
}
