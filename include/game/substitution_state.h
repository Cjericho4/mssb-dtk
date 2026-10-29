#ifndef GAME_SUBSTITUTION_STATE_H
#define GAME_SUBSTITUTION_STATE_H

#include "mssbTypes.h"

typedef struct {
    s32 field_0x00;      /* 0x00 */
    s16 field_0x04;      /* 0x04 */
    u16 field_0x06;      /* 0x06 */
    u16 field_0x08;      /* 0x08 */
    u8 _pad1[0x02];      /* 0x0A */
    s16 field_0x0C;      /* 0x0C */
    s16 field_0x0E;      /* 0x0E */
    s16 field_0x10;      /* 0x10 */
    s16 field_0x12;      /* 0x12 */
    struct {
        s16 cur;
        s16 orig;
    } battingOrder[2][10][2]; /* 0x14 */
    u8 _pad2[0x1D0 - 0xB4]; /* 0xB4 */
    u8 field_0x1D0;      /* 0x1D0 */
    u8 field_0x1D1;      /* 0x1D1 */
    u8 field_0x1D2;      /* 0x1D2 */
    u8 field_0x1D3;      /* 0x1D3 */
    u8 field_0x1D4;      /* 0x1D4 */
    u8 field_0x1D5;      /* 0x1D5 */
    u8 field_0x1D6;      /* 0x1D6 */
    u8 field_0x1D7;      /* 0x1D7 */
    u8 field_0x1D8;      /* 0x1D8 */
    u8 field_0x1D9;      /* 0x1D9 */
    union { u8 field_0x1DA; s8 field_0x1DA_s8; }; /* 0x1DA */
    u8 _pad5[0x26]; /* 0x1DB-0x200 */
    u8 menuFlag; /* 0x201 */
    union {
        struct {
            u8 field_0x202;      /* 0x202 */
            u8 field_0x203;      /* 0x203 */
        };
        u8 field_0x202_team[2];  /* 0x202 */
    };
    u8 menuTeamFlag[2]; /* 0x204 */
    s8 field_0x206;      /* 0x206 */
    u8 _pad207[0x15];    /* 0x207 */
    u8 field_0x21C;      /* 0x21C */
    u8 field_0x21D;      /* 0x21D */
    u8 _pad21E[0x3];     /* 0x21E */
    u8 unk_221;          /* 0x221 */
    u8 field_0x222;      /* 0x222 */
    u8 _pad223[0x1C];    /* 0x223 */
    u8 field_0x23F[2];   /* 0x23F */
    u8 _pad241;          /* 0x241 */
    s16 field_0x242[9];  /* 0x242 */
    s16 unk254;          /* 0x254 */
    s16 unk256;          /* 0x256 */
    s16 unk258;          /* 0x258 */
    s16 unk25A;          /* 0x25A */
    s16 unk25C;          /* 0x25C */
    s16 unk25E;          /* 0x25E */
    u8 field_0x260;      /* 0x260 */
    u8 _pad261[0x3];     /* 0x261 */
} Bss34C90Item; // size: 0x264

extern Bss34C90Item lbl_3_common_bss_34C90;
STATIC_ASSERT(sizeof(Bss34C90Item) == 0x264);

#endif
