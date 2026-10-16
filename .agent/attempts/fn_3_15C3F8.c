/* fn_3_15C3F8 (rep_3B70.c) NONMATCHING best attempt (whole file body below; ~80 diff lines).
 * Logic complete. Remaining: (1) target materialises &counters (addi rX,r31,0x0) and the quads base
 * (addi r4,r31,0x4) separately and adds (cnt*0x110 + slot*0x88) to it, storing q->counter at 0x84(q);
 * MWCC folds the +4 here (stw 0x88). Tried pointer locals, nested counter struct, p+=forms.
 * (2) size = (f32)d->sizeXXX / 100000.0f * 0.5f: rodata/freg order differs (target: 100000 in f1, 0.5 in f0).
 * Replace src/game/rep_3B70.c contents with the below (needs rep_1E08.h/UnknownHeaders.h includes).
 */
typedef struct Rep3B70Quad {
    u8 _pad0[8];
    Mtx mtx;            /* 0x08 */
    u8 unk38[0x54 - 0x38]; /* 0x38 */
    Vec corners[4];     /* 0x54 */
    u8* counter;        /* 0x84 */
} Rep3B70Quad; /* size: 0x88 */

/* Overlay of the file-static data block at lbl_3_data_271A8. */
typedef struct Rep3B70Data {
    u8 counters[4];             /* 0x000 */
    Rep3B70Quad quads[2][2];    /* 0x004 */
    s32 size224;                /* 0x224 */
    u8 _pad228[4];
    s32 size22C;                /* 0x22C */
} Rep3B70Data;

extern Rep3B70Data lbl_3_data_271A8;
extern u8 lbl_803CBBC0;
void fn_80024390(CameraView* cam, u8* arg1, s32 arg2);
void fn_800340F4(Mtx m);

// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void fn_3_15C3F8(void) {
    Rep3B70Data* d = &lbl_3_data_271A8;
    Rep3B70Quad* q;
    u8* cnt;
    Mtx m;
    s32 mode;
    f32 size;
    s32 i;

    cnt = &d->counters[lbl_803CBBC0];
    q = &d->quads[(*cnt)++][lbl_803CBBC0];
    q->counter = cnt;
    fn_80024390(fn_80052734(0), q->unk38, 0);
    PSMTXTrans(q->mtx, lbl_3_common_bss_35154.unk_440, lbl_3_common_bss_35154.unk_444, lbl_3_common_bss_35154.unk_448);
    PSMTXConcat(fn_80052734(0)->viewMtx, q->mtx, q->mtx);
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        mode = 2;
    } else {
        mode = g_Ball.framesSinceHit > 0;
    }
    if (mode == 2) {
        size = d->size22C / 100000.0f * 0.5f;
    } else {
        size = d->size224 / 100000.0f * 0.5f;
    }
    fn_800340F4(m);
    q->corners[0].x = q->corners[0].y = q->corners[1].y = q->corners[3].x = -size;
    q->corners[2].x = q->corners[2].y = q->corners[3].y = q->corners[1].x = size;
    q->corners[0].z = q->corners[1].z = q->corners[2].z = q->corners[3].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(m, &q->corners[i], &q->corners[i]);
    }
    fn_800A7D4C(11, (BdcArrayElement*)q);
}
