#include "game/gap_249E8.h"
#include "game/gap_219CC.h"
#include "game/rep_E08.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"

#include <string.h>

extern Data1F090Entry lbl_3_data_1E434[];
void QueueCharacterAnimation(int character, int animation, u8 arg2, u8 arg3, s16 arg4, u8 flip, int arg6);

// .text:0x000249E8 size:0xF4 mapped:0x80663A7C
void fn_3_249E8(s32 arg0) {
    Fielder *fielder;
    Data1F090Entry *entry;
    f32 temp_f0;
    s32 i;
    u8 r26;

    entry = &lbl_3_data_1F090[arg0];
    fielder = g_Fielders;
    i = 0;
    r26 = entry->unk14;
    do {
        if (r26 == fielder->unk218) {
            lbl_3_common_bss_1323C->unk240[i] = (s16)arg0;
            if (entry->unk19 == 0) {
                memcpy(fielder, entry, 0xC);
            }
            temp_f0 = entry->unkC;
            lbl_3_common_bss_1323C->unk0[i].unkC = temp_f0;
            fielder->unk48 = temp_f0;
            lbl_3_common_bss_1323C->unk261[i] = 1;
            AnimateCharacter(i, entry->unk10, entry->unk16, entry->unk17, entry->unk18, entry->unk12, 0, 0);
        }
        i++;
        fielder++;
    } while (i < 9);
}

// .text:0x00024ADC size:0x2E0 mapped:0x80663B70
void fn_3_24ADC(s32 arg0, s32 arg1) {
    Data1F090Entry* entry;
    s32 idx;
    s32 isQueued;
    AnimationStruct* anim;
    InMemRunnerType* runner;
    f32 angle;
    s32 flip;

    entry = &lbl_3_data_1E434[arg0];
    isQueued = arg1;
    idx = entry->unk14;
    lbl_3_common_bss_1323C->unk240[idx] = arg0;
    if (idx <= 8) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[idx];
        if (entry->unk19 == 0) {
            memcpy(&g_Fielders[idx], entry, 0xC);
            if (anim != NULL) {
                memcpy(&anim->unk34, entry, 0xC);
            }
        }
        angle = entry->unkC;
        lbl_3_common_bss_1323C->unk0[idx].unkC = angle;
        g_Fielders[idx].unk48 = angle;
        if (anim != NULL) {
            anim->unk44 = entry->unkC;
            anim->unk_25D = 1;
        }
        if (entry->unk10 >= 0x69 && entry->unk10 < 0x75) {
            flip = 0;
        } else {
            flip = g_Fielders[idx].unk1C7;
        }
        lbl_3_common_bss_1323C->unk261[idx] = 1;
        lbl_3_common_bss_1323C->unk26E[idx] = 1;
    } else if (idx <= 12) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[idx];
        if (idx == 10) {
            if (anim == NULL) {
                return;
            }
        } else if (idx == 11) {
            if (anim == NULL) {
                return;
            }
        } else if (idx == 12) {
            if (anim == NULL) {
                return;
            }
        }
        runner = &g_Runners[idx - 9];
        if (entry->unk19 == 0) {
            memcpy(runner, entry, 0xC);
            if (anim != NULL) {
                memcpy(&anim->unk34, entry, 0xC);
            }
        }
        angle = entry->unkC;
        lbl_3_common_bss_1323C->unk0[idx].unkC = angle;
        runner->runningAngle = angle;
        if (anim != NULL) {
            anim->unk44 = entry->unkC;
            anim->unk_25D = 1;
        }
        lbl_3_common_bss_1323C->unk261[idx] = 1;
        lbl_3_common_bss_1323C->unk26E[idx] = 1;
        if (idx == 9) {
            if (lbl_3_common_bss_1323C->unk25D == 0 || lbl_3_common_bss_1323C->unk25D == 1) {
                if (g_Batter.batterHand == 1) {
                    flip = 0;
                } else {
                    flip = 1;
                }
            } else {
                flip = 0;
            }
        } else {
            flip = 0;
        }
    }
    if (isQueued == 0) {
        AnimateCharacter(idx, entry->unk10, entry->unk16, entry->unk17, entry->unk18, entry->unk12, flip, 0);
    } else {
        QueueCharacterAnimation(idx, entry->unk10, entry->unk16, entry->unk18, entry->unk12, flip, 0);
    }
}

// .text:0x00024DBC size:0x80 mapped:0x80663E50
void fn_3_24DBC(s32 arg0) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_3_common_bss_1323C->unk240[i] = -1;
        memset(&lbl_3_common_bss_1323C->unk0[i], 0, 0x2C);
        lbl_3_common_bss_1323C->unk261[i] = 0;
    }

    fn_3_6714C(0);

    lbl_3_common_bss_1323C->unk25C = 1;
    lbl_3_common_bss_1323C->unk23C = 0;
    lbl_3_common_bss_1323C->unk27C = 0;
    lbl_3_common_bss_1323C->unk25D = (u8)arg0;
    lbl_3_common_bss_1323C->unk25F = 1;
    lbl_3_common_bss_1323C->unk27D = 0;
    lbl_3_common_bss_1323C->unk27E = 0;
    lbl_3_common_bss_1323C->unk25A = 0;
    lbl_3_common_bss_1323C->unk280 = 1;
}

// .text:0x00024EA0 size:0x80 mapped:0x80663F34
void fn_3_24EA0(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_3_common_bss_1323C->unk240[i] = -1;
        memset(&lbl_3_common_bss_1323C->unk0[i], 0, 0x2C);
        lbl_3_common_bss_1323C->unk261[i] = 0;
    }
}

// .text:0x00024F20 size:0x4 mapped:0x80663FB4
void fn_3_24F20(void) {}

// .text:0x00024F24 size:0x1D8 mapped:0x80663FB8
void fn_3_24F24(void) {
    return;
}

// .text:0x000250FC size:0xE8 mapped:0x80664190
void fn_3_250FC(void) {
    s32 i;
    for (lbl_3_common_bss_1323C->unk25C = (i = 0); i < 0x21; i++) {
        lbl_3_data_2398[i].unk34 = 0;
        lbl_3_data_2398[i].unk38 = 0;
        lbl_3_data_2398[i].unk3C = 0;
    }

    lbl_3_common_bss_1323C->unk27B = 0;
}
