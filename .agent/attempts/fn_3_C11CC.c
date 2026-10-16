/*
 * fn_3_C11CC (src/game/rep_1F58.c) NONMATCHING
 * Known-unfixable pattern: "same-file static data off one base register".
 * Target keeps &lbl_3_data_17248 in r30 for the whole function and reaches
 * lbl_3_data_17260 (slots) as r30+0x18, alpha[] as r30+0x0, speed[] as r30+0x4
 * (explicit addi with 0 offset) -> the original defined this unit's .data
 * statically in the TU. With an extern overlay struct MWCC re-materialises
 * lis/addi per use and folds the 0x18 into displacements; also float-constant
 * load order around sin() differs (0.5 / u8->double magic scheduling).
 * Types needed (local to rep_1F58.c):
 */
typedef struct {
    s16 charIndex;
    u8 _pad2[0x1C - 0x2];
    f32 unk1C; /* 0x1C */
} RepC0854Slot; /* size: 0x20 */

/* Overlay on the start of this unit's .data (lbl_3_data_17248..lbl_3_data_17260) */
typedef struct {
    /* 0x00 */ u8 alpha[2];
    /* 0x02 */ u8 _pad2[2];
    /* 0x04 */ f32 speed[3];
    /* 0x10 */ u8 _pad10[0x18 - 0x10];
    /* 0x18 */ RepC0854Slot slots[18];
} Rep1F58Data; /* lbl_3_data_17260 == slots */

typedef struct {
    /* 0x00 */ u8 _pad0[0x14];
    /* 0x14 */ u8 charIndex;
    /* 0x15 */ u8 alpha;
    /* 0x16 */ u8 timer;
} RepC1004Obj;

extern Rep1F58Data lbl_3_data_17248;

void fn_3_C11CC(s32 idx, s32 arg1) {
    s32 j;
    AnimationStruct* anim;
    s32 sfx;
    RepC1004Obj* obj;
    RepC0854Slot* slots = lbl_3_data_17248.slots;

    j = 1;
    do {
        if (idx == slots[j].charIndex) {
            break;
        }
    } while (j-- != 0);
    if (j < 0) {
        return;
    }
    if (arg1 != 0) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[idx];
        if (anim != NULL) {
            anim->funcPtr_0x5c = NULL;
        }
        sfx = 0x18;
        lbl_3_data_17248.slots[j].charIndex = -1;
        if (j != 0) {
            sfx = 0x17;
        }
        fn_80027918(sfx, 0.0f);
    } else {
        obj = (RepC1004Obj*)fn_800B0A5C_insertQueue(fn_3_C1004, lbl_803CC1B8->priority);
        obj->charIndex = idx;
        obj->alpha = lbl_3_data_17248.alpha[j] * (0.5 + 0.5 * sin(lbl_3_data_17248.speed[j] * lbl_3_data_17248.slots[j].unk1C / 100.0f));
        obj->timer = 10;
    }
}
