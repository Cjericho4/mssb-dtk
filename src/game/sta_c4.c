#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTexture.h"
#include "UnknownHeaders.h"
#include "game/rep_1D58.h"
#include "game/sta_c4.h"
#include "header_rep_data.h"
#include "game/m_sound.h"
#include "game/gap_16C410.h"
#include "game/rep_3448.h"
#include "game/sta_c2.h"
#include "C3/unktypes.h"

extern GXTexObj lbl_3_bss_B640;

// .text:0x000F8444 size:0x10 mapped:0x807374D8
void fn_3_F8444(void) {
    lbl_3_bss_B5D4 = TRUE;
}

// .text:0x000F8454 size:0xD0 mapped:0x807374E8
extern s32 lbl_3_bss_B574[];
extern u8 lbl_3_bss_B664;

void fn_3_F8454(void) {
    if (g_GameLogic.gameStatus == 0xB) {
        if (lbl_3_bss_B664 == 0) {
            fn_3_8B890(lbl_3_bss_B574[0]);
            lbl_3_bss_B664 = 1;
        }
    } else if (lbl_3_bss_B664 != 0) {
        lbl_3_bss_B574[0] = fn_3_8BBC4(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 3, NULL, 0, 2);
        lbl_3_bss_B664 = 0;
    } else {
        fn_3_8BA60(lbl_3_bss_B574[0], NULL, NULL);
    }
}

// .text:0x000F8524 size:0x8C mapped:0x807375B8
void fn_3_F8524(StaC4Obj* obj) {
    static const VecXYZ basePos = {0.0f, 0.5f, 60.0f};

    if (obj->unk4F < 42) {
        obj->unk14 = 0.123f;
        obj->pos.x = basePos.x;
        obj->pos.y = basePos.y - 2.0;
        obj->pos.z = basePos.z;
        obj->unk38 = 0.75f;
        obj->unk3C = 4.0f;
    }
    obj->color[2] = 0xFF;
    obj->color[1] = 0xFF;
    obj->color[0] = 0xFF;
    obj->color[3] = 0xFF;
    obj->unk4A = 0x80;
    obj->unk48 = 0;
}

// .text:0x000F85B0 size:0x2C8 mapped:0x80737644
void fn_3_F85B0(void) {
    return;
}

// .text:0x000F8878 size:0x244 mapped:0x8073790C
void fn_3_F8878(void) {
    return;
}

// .text:0x000F8ABC size:0x48 mapped:0x80737B50


void fn_3_F8ABC(void) {
    // 0x000F8ABC: stwu r1, -0x10(r1) - Function Prologue
    // 0x000F8AE4: bl fn_80033A24
    if (fn_80033A24(fn_3_F85B0, 0xF0, 0x0D, 0x2A, 1, 0x7F) != 0) {
        // 0x000F8AF0: bl fn_3_F8878
        fn_3_F8878();
    }
    // 0x000F8B00: blr - Function Epilogue
}

// .text:0x000F8B04 size:0x2C mapped:0x80737B98
// .text:0x000F8B04 size:0x2C mapped:0x80737B98
void fn_3_F8B04(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
}

// .text:0x000F8B30 size:0x4 mapped:0x80737BC4
void fn_3_F8B30(void) {
    return;
}

// .text:0x000F8B34 size:0x74 mapped:0x80737BC8
void fn_3_F8B34(void) {
    fn_3_B9510(0);
    GXLoadTexObj(&lbl_3_bss_B640, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_FALSE, GX_FALSE, GX_ITM_0);
}

// .text:0x000F8BA8 size:0x158 mapped:0x80737C3C
/* Minimal views of the C3 Actor -> sBone -> DODisplayObj chain (C3/geoPalette.h can't be included here). */
typedef struct StaC4DispObj {
    /* 0x00 */ u8 _pad0[0x10];
    /* 0x10 */ DisplayData* displayData;
} StaC4DispObj;

typedef struct StaC4Bone {
    /* 0x00 */ u8 _pad0[0x14];
    /* 0x14 */ StaC4DispObj* dispObj;
} StaC4Bone;

typedef struct StaC4Actor {
    /* 0x00 */ u8 _pad0[0x18];
    /* 0x18 */ StaC4Bone** boneArray;
} StaC4Actor;

extern u8* lbl_3_bss_B63C;
extern u32 fn_800247E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void fn_3_F8BA8(StaC4AnimObj* obj) {
    DisplayStateList* state = ((StaC4Actor*)obj->animState->actor)->boneArray[0]->dispObj->displayData->displayStateList;
    u32 x;
    u32 y;
    s8 prev;
    s8 cur;
    u32 off;

    if (obj->tickCount != 0 && obj->tickCount % 3 == 0) {
        obj->texFrame++;
        if (obj->texFrame > 25) {
            obj->texFrame = 10;
            obj->tickCount = 0;
        }
        state->setting &= ~0x1FFF;
        state->setting |= obj->texFrame;
        for (x = 0; x < 0x80; x++) {
            for (y = 0; y < 0x80; y++) {
                if (y == 0) {
                    prev = lbl_3_bss_B63C[fn_800247E4(x, 0x7F, 0x80, 2)];
                }
                off = fn_800247E4(x, y, 0x80, 2);
                cur = lbl_3_bss_B63C[off];
                lbl_3_bss_B63C[off] = prev;
                prev = cur;
            }
        }
        DCFlushRange(lbl_3_bss_B63C, 0x8000);
    }
    obj->tickCount++;
}

// .text:0x000F8D00 size:0x120 mapped:0x80737D94
extern char lbl_3_rodata_3030[];
extern char lbl_3_rodata_303C[];

void fn_3_F8D00(void) {
    Mtx23 m;
    u32 y;
    u32 x;
    u32 off;

    m[0][0] = 0.5f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 0.5f;
    m[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    lbl_3_bss_B63C = fn_3_B9534(0x80, 0x80, &lbl_3_bss_B640);
    if (lbl_3_bss_B63C == NULL) {
        OSPanic(lbl_3_rodata_3030, 0x6DF, lbl_3_rodata_303C);
    }
    for (y = 0; y < 0x80; y++) {
        for (x = 0; x < 0x80; x++) {
            off = fn_800247E4(x, y, 0x80, 2);
            lbl_3_bss_B63C[off] = (u8)(rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000F8E20 size:0x268 mapped:0x80737EB4
void fn_3_F8E20(void) {
    return;
}

// .text:0x000F9088 size:0xDC mapped:0x8073811C
extern DrawingSceneStruct* lbl_3_bss_B628;
void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);

void fn_3_F9088(VecXYZ* pos, s32 idx) {
    s16 screenX;
    s16 screenY;

    fn_800528C0(pos->x, pos->y, pos->z, &screenX, &screenY);
    lbl_80371C30[lbl_3_bss_B628->unkIndex + idx].obj->pos.x = screenX;
    lbl_80371C30[lbl_3_bss_B628->unkIndex + idx].obj->pos.y = screenY;
    lbl_80371C30[lbl_3_bss_B628->unkIndex + idx].obj->pos.z = 0.0f;
}

// .text:0x000F9164 size:0x198 mapped:0x807381F8
void fn_3_F9164(void) {
    return;
}

// .text:0x000F92FC size:0x50 mapped:0x80738390
void fn_3_F92FC(void) {
    DrawingSceneStruct *s = lbl_803CC1B8;
    s16 state = s->loadingState;
    s->loadingState = state - 1;
    if (state == 0) {
        s->unk14->b2 = 1;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000F934C size:0x2F0 mapped:0x807383E0
void fn_3_F934C(void) {
    return;
}

// .text:0x000F963C size:0x130 mapped:0x807386D0
void fn_3_F963C(void) {
    return;
}

// .text:0x000F976C size:0x284 mapped:0x80738800
void fn_3_F976C(void) {
    return;
}

// .text:0x000F99F0 size:0x1AC mapped:0x80738A84
void fn_3_F99F0(void) {
    return;
}

// .text:0x000F9B9C size:0x1F8 mapped:0x80738C30
void fn_3_F9B9C(void) {
    return;
}

// .text:0x000F9D94 size:0xE4 mapped:0x80738E28
extern u8 lbl_3_bss_B630[];

void fn_3_F9D94(StaC4AnimObj* obj) {
    ActorAnimState* state = obj->animState;
    s32 i;

    if (obj->animTime >= state->bank->animSequences->trackArray[state->seqNum].animTime) {
        obj->flag90_7 = 0;
        obj->animState = NULL;
        obj->unk78 = 0;
        obj->unk7C = 0;
        obj->unk80 = 0;
        obj->flag90_6 = 0;
        for (i = 0; i < 9; i++) {
            if (lbl_3_bss_B630[i] == obj->slotId) {
                lbl_3_bss_B630[i] = 0xFF;
                return;
            }
        }
    } else {
        AnimateActorBones(state->actor);
        obj->animTime += 1.0f;
    }
}

// .text:0x000F9E78 size:0x548 mapped:0x80738F0C
void fn_3_F9E78(void) {
    return;
}

// .text:0x000FA3C0 size:0x1CC mapped:0x80739454
void fn_3_FA3C0(void) {
    return;
}

// .text:0x000FA58C size:0xE4C mapped:0x80739620
void fn_3_FA58C(void) {
    return;
}

// .text:0x000FB3D8 size:0x7C8 mapped:0x8073A46C
void fn_3_FB3D8(void) {
    return;
}

// .text:0x000FBBA0 size:0x130 mapped:0x8073AC34
void fn_3_FBBA0(void) {
    return;
}
