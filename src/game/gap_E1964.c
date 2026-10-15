#include "game/gap_E1964.h"

#include "UnknownHeaders.h"
#include "game/rep_1838.h"
#include "game/rep_1D58.h"
#include "Dolphin/GX/GXTev.h"
#include "game/rep_3310.h"
#include "game/gap_6A160.h"
#include "game/rep_2940.h"
#include "game/gap_DEB90.h"
#include "game/rep_EA0.h"
#include "game/gap_6B4C8.h"
#include "game/rep_F80.h"
#include "game/gap_EA340.h"
#include "game/gap_1293D0.h"
#include "static/UnknownHomes_Static.h"

extern void fn_8001D0D0();
extern f32 lbl_3_data_18D98[];
extern void fn_800BF058(void (*fn)(void));
extern void fn_8003A548(void (*fn)(void));
extern void fn_800BDF70(void** ptr);

typedef struct {
    void* _0;
    u8 _4[0x94];
    u8 unk98;   /* 0x98 */
} E1D00Inner;

typedef struct {
    u8 _pad[0x10];
    u8 flag;    /* 0x10 */
    u8 _pad2[0x1c - 0x11];
} E1D00Entry;

extern E1D00Entry lbl_3_data_18ED0[];

typedef struct GapE1964Entry {
    u8 _pad0[0x14];
    f32 field_0x14;
} GapE1964Entry;

typedef struct {
    u8 _pad[2];
    s16 unk2;
} Data18BB0Entry;
extern Data18BB0Entry lbl_3_data_18BB0[];
extern f32 lbl_3_data_18DD0;

typedef struct {
    void* unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 _pad18[0xC];
    u8 _pad24[2];
    u8 unk26;
    u8 _pad27;
} GapE19E8Entry;

// .text:0x000E1964 size:0x84
void fn_3_E1964(void) {
    s32 i;
    GapE1964Entry* entry;
    s32 offset;

    i = 0;
    offset = i;
    do {
        entry = (GapE1964Entry*)((u8*)g_hugeAnimStruct.entries_2D94 + offset);
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        {
            u32 r = (u32)rand();
            u32 shifted = r << 20;
            r >>= 31;
            shifted -= r;
            shifted = (shifted << 12) | (shifted >> 20);
            shifted += r;
            entry->field_0x14 = shortAngleToRad_Capped((s16)shifted);
        }
        i++;
        offset += 0x28;
    } while (i < 0x1E);
}

/* Inlined copy of fn_3_E0668. */
static inline void updateWallBallCoins(void) {
    GapE19E8Entry* entry;
    s32 i;

    for (i = 0; i < 0x1E; i++) {
        entry = (GapE19E8Entry*)&g_hugeAnimStruct.entries_2D94[i];
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 0) {
            entry->unk26 = 0;
        } else if (g_Minigame.wallBall_coinsVisibleFrameCounter[0] > lbl_3_data_18BB0[g_Minigame._199E].unk2
                   && (g_Minigame.wallBall_coinsVisibleFrameCounter[0] & 1)) {
            entry->unk26 = 0;
        } else {
            entry->unk26 = 1;
            entry->unk4 = g_Minigame.wallBall_coinCoordinates[i].x;
            entry->unk8 = -g_Minigame.wallBall_coinCoordinates[i].y;
            entry->unkC = g_Minigame.wallBall_coinCoordinates[i].z;
            entry->unk14 = fn_3_9FEA8(entry->unk14 + lbl_3_data_18DD0);
        }
    }
}

// .text:0x000E19E8 size:0x278
void fn_3_E19E8(void) {
    s32 i;
    u8 status;

    g_hugeAnimStruct.field280_0x3087 = 1;
    if (g_GameLogic.gameStatus == 5 && g_GameLogic._125 == 5) {
        fn_3_11D1B0();
    }
    status = g_GameLogic.gameStatus;
    if (status == 0x1B) {
        return;
    }
    if (g_hugeAnimStruct.field269_0x307a == 0) {
        for (i = 0; i < 4; i++) {
            if (g_hugeAnimStruct.AnimationStructPtrs[i] != NULL) {
                g_hugeAnimStruct.AnimationStructPtrs[i]->unk_25D = 0;
            }
        }
        fn_3_6A25C();
        fn_3_6A250();
    } else if ((u8)(status - 0x1C) <= 2 || status == 0x1F) {
        if (status == 0x1E) {
            fn_3_E11E0();
        }
    } else if (status == 0xE || status == 0x22 || status == 0x24 || status == 0x26 || status == 0x27) {
        g_hugeAnimStruct.field280_0x3087 = g_d_GameSettings.GameModeSelected != 6;
        fn_3_E07DC();
        fn_3_116B74();
    } else {
        if (status == 4) {
            return;
        }
        if (status != 5) {
            fn_3_697CC();
            fn_3_685F0();
            fn_3_E1478();
            fn_3_6B674();
            if (g_d_GameSettings.GameModeSelected == 6) {
                updateWallBallCoins();
            } else {
                fn_3_11AC6C();
            }
            fn_3_6AB58();
        }
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_3_EDD10();
    } else {
        fn_3_12D1F4();
    }
}

// .text:0x000E1C60 size:0xA0
void fn_3_E1C60(void) {
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorIn(0, 0xF, 0xF, 7, 0xA);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 7, 7, 4);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
}

// .text:0x000E1D00 size:0xB8
void fn_3_E1D00(void) {
    StadiumObjectElem* obj;
    s32 i;

    fn_800BF058((void (*)(void))fn_3_B8184);
    fn_8003A548(fn_3_E1C60);
    i = 0;
    while (i < (s32)lbl_3_common_bss_350E4[0].memcpyCount) {
        if (lbl_3_data_18ED0[i].flag == 2) break;
        obj = &lbl_3_common_bss_350E4[0].src[i];
        fn_3_B828C((StadiumObject*)obj);
        if (obj->unk74 != NULL) {
            E1D00Inner* inner = (E1D00Inner*)*obj->unk74;
            inner->unk98 = obj->unk93 | 6;
            fn_800BDF70(obj->unk74);
        }
        i++;
    }
    fn_8003A548(NULL);
}
