#include "game/rep_3F60.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"

/* Queue entry created by the rep_3F60 animation-event callbacks. */
typedef struct Rep3F60QueueObj {
    /* 0x00 */ u8 _pad0[0x14];
    /* 0x14 */ VecXYZ pos;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 animIdx;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
} Rep3F60QueueObj;

extern s32 lbl_3_data_28680[];
extern u8 lbl_3_data_28914[0xA];
extern u16 lbl_3_data_2891E;
extern u16 lbl_3_data_28920;

// .text:0x00168414 size:0x2F0 mapped:0x807A74A8
void fn_3_168414(void) {
    return;
}

// .text:0x00168704 size:0x228 mapped:0x807A7798
void fn_3_168704(void) {
    return;
}

// .text:0x0016892C size:0x140 mapped:0x807A79C0
void fn_3_16892C(AnimationStruct* anim, s16 arg1, f32 frame) {
    Rep3F60QueueObj* q;
    s32 idx = anim->unk254;

    if (frame == lbl_3_data_28680[16] / 100000.0f && !(lbl_3_data_28914[idx] & 1)) {
        lbl_3_data_28914[idx] |= 1;
        if (anim != NULL) {
            q = (Rep3F60QueueObj*)fn_800B0A5C_insertQueue(fn_3_168704, (u16)(lbl_803CC1B8->priority + 1));
            q->animIdx = idx;
            q->unk24 = 0;
            q->unk20 = lbl_3_data_28680[17] / 100000.0f;
            q->unk26 = arg1;
            q->unk2A = 3;
            q->unk28 = 5;
            q->unk2B = 8;
            q->unk2C = 9;
        }
    }
    lbl_3_data_28914[idx] |= 2;
}

// .text:0x00168A6C size:0x26C mapped:0x807A7B00
void fn_3_168A6C(void) {
    return;
}

// .text:0x00168CD8 size:0x124 mapped:0x807A7D6C
void fn_3_168CD8(AnimationStruct* anim, s16 arg1, f32 frame) {
    Rep3F60QueueObj* q;
    s32 idx = anim->unk254;

    if (frame == lbl_3_data_28680[14] / 100000.0f && anim != NULL) {
        q = (Rep3F60QueueObj*)fn_800B0A5C_insertQueue(fn_3_168DFC, (u16)(lbl_803CC1B8->priority + 1));
        q->animIdx = idx;
        q->unk24 = 0;
        q->unk20 = lbl_3_data_28680[15] / 100000.0f;
        getAnimRelatedCoordinates(idx, lbl_3_data_28920, &q->pos);
        q->unk2A = 2;
        q->unk28 = 4;
        q->unk2B = 7;
    }
}

// .text:0x00168DFC size:0x1A4 mapped:0x807A7E90
void fn_3_168DFC(void) {
    return;
}

// .text:0x00168FA0 size:0x120 mapped:0x807A8034
void fn_3_168FA0(void) {
    return;
}

