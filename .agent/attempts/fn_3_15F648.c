/* fn_3_15F648 NONMATCHING: logic believed correct; hits Known Unfixable 'same-file static data off one base register'.
 * Target keeps &lbl_3_data_27D58 in r30 and reaches the thresholds via 'addi r3,r30,0x148; lwz r4,4(r3)' / 8(r3)
 * (thresh[0] folds to 0x148(r30)) - i.e. the thresholds were likely a separate static array addressed off the
 * TU data base. Every s32[3]/struct-array/2D/inline-helper form folds to 0x14c(r30). Remaining: GXColor build
 * (target clrlslwi g<<16 then rlwimi r,b; ours slwi) and data-pointer init 'addi r0; mr r30'.
 * Header: rep_3C80.h needs #include "Dolphin/mtx.h" and void fn_3_15F648(s32 arg0, s32 arg1, Vec* pos, Vec* dir); */
#include "game/rep_3C80.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "Dolphin/gx.h"

typedef struct Rep3C80Effect0 {
    /* 0x00 */ s32 frame;
    /* 0x04 */ u8 _pad4[0x3C];
    /* 0x40 */ u32 color;
    /* 0x44 */ u8 _pad44[0xC];
} Rep3C80Effect0; // size: 0x50

typedef struct Rep3C80Data {
    /* 0x000 */ Rep3C80Effect0 eff0;
    /* 0x050 */ s32 eff50[0x15];
    /* 0x0A4 */ s32 effA4[0x14];
    /* 0x0F4 */ s32 effF4[0x15];
    /* 0x148 */ s32 thresh[3];
    /* 0x154 */ u8 _pad154[0x168 - 0x154];
} Rep3C80Data; // size: 0x168

typedef struct Rep3C80Color {
    u8 r;
    u8 g;
    u8 b;
} Rep3C80Color;

extern Rep3C80Data lbl_3_data_27D58;
extern Rep3C80Color lbl_800FC0FC[];

void fn_80064344(Vec* pos, Vec* dir);
void fn_8002955C(Vec* pos, s32 arg1, s32* eff);
void fn_80030D88(Vec* pos, Vec* dir, s32* eff, s32 arg3);
void fn_80031CA4(Vec* pos, Rep3C80Effect0* eff);
s32 fn_8004AD54(u8 stadium, s32 arg1);

// .text:0x0015F648 size:0x22C mapped:0x8079E6DC
void fn_3_15F648(s32 arg0, s32 arg1, Vec* pos, Vec* dir) {
    Rep3C80Data* d;
    s32 kind;

    d = &lbl_3_data_27D58;
    switch (arg0) {
    case 10:
        fn_80064344(pos, dir);
        break;
    default:
        if (arg1 == 1) {
            if (PSVECMag(dir) >= (f32)d->thresh[1] / 100000.0f) {
                d->effA4[0] = d->eff50[0] = lbl_3_common_bss_35154.unk4;
                fn_8002955C(pos, 0, d->eff50);
                fn_80030D88(pos, dir, d->effA4, 5);
            }
        } else {
            kind = fn_8004AD54(g_d_GameSettings.StadiumID, arg0);
            if (PSVECMag(dir) >= (f32)d->thresh[0] / 100000.0f) {
                d->eff0.frame = lbl_3_common_bss_35154.unk4;
                d->eff0.color = (lbl_800FC0FC[kind].r << 24) | (lbl_800FC0FC[kind].g << 16) | (lbl_800FC0FC[kind].b << 8);
                fn_80031CA4(pos, &d->eff0);
            }
            if (PSVECMag(dir) >= (f32)d->thresh[2] / 100000.0f) {
                switch (kind) {
                case 1:
                case 3:
                case 7:
                    d->effF4[0] = lbl_3_common_bss_35154.unk4;
                    fn_8002955C(pos, 0, d->effF4);
                    break;
                }
            }
        }
        break;
    }
}
