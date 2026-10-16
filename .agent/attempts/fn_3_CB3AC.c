/* fn_3_CB3AC (rep_2390.c) NONMATCHING best attempt.
 * ~48 lines differ: target keeps an extra "segs" base reg (addi r29,r31,0 then mr/addi to make &segs[9..11]) and the 6660 pair search uses a separate i*4 byte-offset induction (lhzx) plus pointer p; MWCC folds these into r31 offsets / lhzu in every form tried (do/for, pointer+index, s2 += 11).
 * Needs the file-scope declarations below (in rep_2390.c) plus fn_3_CB3AC.headers.diff
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


void fn_3_CB3AC(void) {
    Rep2390Data* d;
    Rep2390Seg* s1;
    Rep2390Seg* s2;
    Rep2390Seg* s0;
    AnimationStruct* anim;
    VecXYZ pos;
    Rep2390Seg* segs;
    u16 code;
    s32 val;
    u32 i;

    anim = g_hugeAnimStruct.AnimationStructPtrs[0];
    d = &lbl_3_data_17DC0;
    if (PSVECMag(&d->v48C) != 0.0f && anim != NULL) {
        segs = d->segs;
        s1 = &segs[10];
        s0 = &segs[9];
        s2 = &segs[11];
        val = lbl_3_common_bss_35154.unk4;
        s2->unk0 = val;
        s1->unk0 = val;
        s0->unk0 = val;
        s0->unk4 = 0x15;
        s1->unk4 = 7;
        code = 0x1A;
        if (anim->unk25A != 0) {
            i = 0;
            do {
                if (lbl_3_data_6660[i].a == 0x1A) {
                    code = lbl_3_data_6660[i].b;
                    break;
                }
                if (lbl_3_data_6660[i].b == 0x1A) {
                    code = lbl_3_data_6660[i].a;
                    break;
                }
                i++;
            } while (lbl_3_data_6660[i].a != 0xFFFF);
        }
        getAnimRelatedCoordinates(0, code, &pos);
        PSVECAdd((Vec*)&pos, &d->v498, (Vec*)&pos);
        if (lbl_80366158._28 == 0) {
            fn_80030D88((Vec*)&pos, &d->v48C, s1, 5);
            fn_80030D88((Vec*)&pos, &d->v48C, s2, 5);
            fn_80030470((Vec*)&pos, &d->v48C, &d->v48C, s0, 5);
        }
    }
}
