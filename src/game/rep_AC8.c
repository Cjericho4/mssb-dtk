#include "game/rep_AC8.h"
#include "game/rep_1CB8.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "game/rep_1188.h"
#include "game/rep_1838.h"
#include "game/rep_18E8.h"
#include "game/gap_AC9F8.h"

static inline void setFielderReadyAction(s32 idx, s32 action) {
    Fielder* f = &g_Fielders[idx];
    f->unk1D3 = action;
    if (lbl_3_data_3C40.actions[action].unk0 >= 0) {
        g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.actions[action].unk0;
    }
    f->unk1D5 = 0;
    f->unk1D6 = 0;
    f->unk1A4 = 0;
    f->unk1AC = 0;
    f->unk1FF = 0;
}

static inline void setFielderTargetIdx(s32 fielderIdx, f32 x, f32 z) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 dx;
    f32 dz;

    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
    } else {
        f->unk64 = atan2(dz, dx);
        f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    }
    f->unk1D9 = 1;
}

static inline void setFielderTarget(Fielder* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;

    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
    } else {
        f->unk64 = atan2(dz, dx);
        f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    }
    f->unk1D9 = 1;
}

static inline void aimFielderAt(Fielder* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;

    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
        return;
    }
    f->unk64 = atan2(dz, dx);
    f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    f->unk1D9 = 1;
}

static inline s32 fielderFramesToReach(Fielder* f, f32 x, f32 z) {
    f32 dist;
    f32 speed;
    u32 delay;

    if (x == f->pos[0] && z == f->pos[2]) {
        return 1;
    }
    dist = dolsqrtf2((x - f->pos[0]) * (x - f->pos[0]) + (z - f->pos[2]) * (z - f->pos[2]));
    delay = f->unk1D1 / 2;
    speed = f->unk58;
    if (speed == 0.0f) {
        speed = 1.0f;
    }
    return delay + (s32)(dist / speed);
}

static inline void startFielderChase(s32 idx) {
    if (g_FieldingLogic.unk_F8[idx] == 9) {
        return;
    }
    g_Fielders[idx].unk18C = 7;
    if (idx != -1) {
        setFielderReadyAction(idx, 0xE);
    }
    g_Fielders[idx].unk1D6 = 0;
    g_Fielders[idx].unk190 = -1;
}

static inline void sendFielderToHome(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    f->unk18C = 0xE;
    f->unk1D7 = 2;
    if (idx != -1) {
        setFielderReadyAction(idx, 0xE);
    }
    f->unk1D6 = 0xB;
    setFielderTarget(f, lbl_3_data_4444[4].x, lbl_3_data_4444[4].z);
}

static inline void stopFielder(s32 idx) {
    Fielder* g = &g_Fielders[idx];

    g_Fielders[idx].prevPos[0] = g->pos[0];
    g_Fielders[idx].prevPos[1] = g->pos[1];
    g_Fielders[idx].prevPos[2] = g->pos[2];
    g_Fielders[idx].unk30 = 0.0f;
    g_Fielders[idx].unk34 = 0.0f;
    g_Fielders[idx].unk50 = 0.0f;
    g_Fielders[idx].unk68 = 0.0f;
}

static inline void aimPitcherAtBase(void) {
    f32 x;
    f32 z;
    f32 d;

    if (g_Fielders[0].unk18C == 1) {
        x = lbl_3_data_4444[1].x;
        d = x - g_Fielders[0].pos[0];
        if (d > 15.0f) {
            d = 15.0f;
        }
        d /= 3.0f;
        z = lbl_3_data_4444[1].z - d;
    } else if (g_Fielders[0].unk18C == 3) {
        x = lbl_3_data_4444[3].x;
        d = g_Fielders[0].pos[0] - x;
        if (d > 15.0f) {
            d = 15.0f;
        }
        d /= 3.0f;
        z = lbl_3_data_4444[3].z - d;
    } else {
        x = lbl_3_data_4444[g_Fielders[0].unk18C].x;
        z = lbl_3_data_4444[g_Fielders[0].unk18C].z;
    }
    setFielderTargetIdx(0, x, z);
}

// .text:0x000251E4 size:0x1C0 mapped:0x80664278
void fn_3_251E4(void) {
    return;
}

// .text:0x000253A4 size:0x2A4 mapped:0x80664438
void fn_3_253A4(s8 arg0, s32 arg1) {
    return;
}

// .text:0x00025648 size:0x1FC mapped:0x806646DC
void fn_3_25648(void) {
    return;
}

extern s16 lbl_3_data_49DC[44];
// .text:0x00025844 size:0x94 mapped:0x806648D8
void fn_3_25844(s32 fielderIdx, s32 arg1) {
    Fielder* f = &g_Fielders[fielderIdx];

    if (f->unk20F == 0) {
        f->unk1BC = radToShortAngle(f->unk48);
        f->unk20F = 1;
        f->unk1B8 = 0;
        f->unk1BA = lbl_3_data_49DC[arg1 + 29];
        f->unk252 = 0;
        f->unk203 = 0;
        f->unk205 = 0;
        f->unk207 = 0;
        f->unk1EE = 0;
    }
}

// .text:0x000258D8 size:0x190 mapped:0x8066496C
void fn_3_258D8(void) {
    return;
}

// .text:0x00025A68 size:0x1D8 mapped:0x80664AFC
void fn_3_25A68(void) {
    return;
}

// .text:0x00025C40 size:0x5A8 mapped:0x80664CD4
void fn_3_25C40(void) {
    return;
}

// .text:0x000261E8 size:0x47C mapped:0x8066527C
void fn_3_261E8(s32 fielderIdx) {
    return;
}

// .text:0x00026664 size:0x410 mapped:0x806656F8
void fn_3_26664(void) {
    return;
}

// .text:0x00026A74 size:0xBD4 mapped:0x80665B08
void fn_3_26A74(void) {
    return;
}

// .text:0x00027648 size:0xF0 mapped:0x806666DC
void fn_3_27648(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        if (g_Fielders[i].unk252) {
            g_Fielders[i].unk_25B = 1;
            g_Ball.catchAnimationTotalFrames = 0;
        }
    }
}

// .text:0x00027738 size:0x2C mapped:0x806667CC
void fn_3_27738(s32 fielderIndex) {
    // Creating this local pointer anchors the index calculation to r5
    // and the base address calculation to r4/r0.
    Fielder* fielder = &g_Fielders[fielderIndex];
    
    fielder->unk_25B = 1;
    g_Ball.catchAnimationTotalFrames = 0;
}

// .text:0x00027764 size:0xFC mapped:0x806667F8
void fn_3_27764(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (g_d_GameSettings.GameModeSelected != 6 && idx != g_FieldingLogic.unkB0 && idx != -1) {
        f->unk1D3 = 0xC;
        if (lbl_3_data_3C40.unk60 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unk60;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
    f->unk252 = 0;
    f->unk50 = 0.0f;
    f->unk194 = 0;
    f->unk1E9 = 0;
    f->unk1DF = 0;
    f->unk205 = 0;
    f->unk25E = 0;
    if (f->unk1E8 != 0) {
        f->unk1E8 = 2;
    }
    if (g_Ball.fielderWBallIndex >= 0 && g_Ball.catchAnimationTotalFrames != 0) {
        g_Ball.catchAnimationTotalFrames = 0;
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.fielderActionCatchCoords.z;
    }
}

// .text:0x00027860 size:0x508 mapped:0x806668F4
void fn_3_27860(void) {
    return;
}

// .text:0x00027D68 size:0x28C mapped:0x80666DFC
void fn_3_27D68(void) {
    return;
}

// .text:0x00027FF4 size:0x230 mapped:0x80667088
void fn_3_27FF4(void) {
    return;
}

// .text:0x00028224 size:0xA84 mapped:0x806672B8
void fn_3_28224(void) {
    return;
}

// .text:0x00028CA8 size:0x14BC mapped:0x80667D3C
void fn_3_28CA8(void) {
    return;
}

typedef struct Data47D0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Data47D0; // size: 0x14
extern Data47D0 lbl_3_data_47D0[6];

// .text:0x0002A164 size:0x124 mapped:0x806691F8
static inline void startFielderCatch(s32 idx, s32 type, s32 frames, u8 arg3, u8 arg4) {
    Fielder* f = &g_Fielders[idx];

    f->unk24C = frames;
    f->unk24E = 0;
    f->unk252 = type;
    f->unk253 = 0;
    f->unk254 = 0;
    f->unk255 = arg4;
    f->unk_25B = arg3;
    f->unk259 = 0;
    f->unk25C = 0;
    f->unk25D = 0;
    f->unk25E = 0;
    f->unk25F = 0;
    f->unk264 = 0;
    f->unk260 = 0;
    if (type == 7) {
        f->unk260 = 1;
    }
    if (frames < g_Ball.framesUntilBallHitsGround) {
        f->unk264 = 1;
    }
    switch (type) {
    case 3:
        f->unk259 = 2;
        break;
    case 4:
        f->unk259 = 3;
        break;
    }
    g_Ball.catchAnimationTotalFrames = 0;
}

BOOL fn_3_2A164(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (f->unk74 > lbl_3_data_47D0[f->unk1CA].unk8) {
        return FALSE;
    }
    if (g_Ball.AtBat_Contact_BallPos.y < f->unk15C) {
        return FALSE;
    }
    if (g_Ball.AtBat_Contact_BallPos.y > f->unk15C + f->unkF4) {
        return FALSE;
    }
    if (fn_3_B7CDC(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        return FALSE;
    }
    startFielderCatch(idx, 6, 1, 0, 0);
    return TRUE;
}

// .text:0x0002A288 size:0x414 mapped:0x8066931C
void fn_3_2A288(void) {
    return;
}

// .text:0x0002A69C size:0x63C mapped:0x80669730
void fn_3_2A69C(void) {
    return;
}

// .text:0x0002ACD8 size:0x90 mapped:0x80669D6C
BOOL fn_3_2ACD8(s32 fielderIdx, s32 frame) {
    Fielder* f = &g_Fielders[fielderIdx];
    if (frame < 1) {
        return FALSE;
    }
    if (fn_3_2BB04(fielderIdx)) {
        return TRUE;
    }
    f->prevPos[0] = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x;
    f->prevPos[2] = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z;
    f->unk216 = 1;
    return FALSE;
}

// .text:0x0002AD68 size:0x858 mapped:0x80669DFC
void fn_3_2AD68(void) {
    return;
}

// .text:0x0002B5C0 size:0xD4 mapped:0x8066A654
void fn_3_2B5C0(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 a;
    s32 b;
    s16 d;

    f->unk261 = 0;
    a = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x - f->pos[0], g_Ball.AtBat_Contact_BallPos.z - f->pos[2]);
    b = fn_3_9FB8C(f->unk21C - f->pos[0], f->unk224 - f->pos[2]);
    d = fn_3_9FCA4((s16)a, (s16)b);
    if (d < -0x500 || d > 0x500) {
        f->unk261 = 3;
    } else if (d < -0x200) {
        f->unk261 = 1;
    } else if (d > 0x200) {
        f->unk261 = 2;
    }
}

// .text:0x0002B694 size:0x470 mapped:0x8066A728
void fn_3_2B694(void) {
    return;
}

// .text:0x0002BB04 size:0x734 mapped:0x8066AB98
BOOL fn_3_2BB04(s32 fielderIdx) {
    return FALSE;
}

// .text:0x0002C238 size:0xB8 mapped:0x8066B2CC
void fn_3_2C238(s32 idx, s32 type, s32 frames, u8 arg3, u8 arg4) {
    Fielder* f = &g_Fielders[idx];

    f->unk24C = frames;
    f->unk24E = 0;
    f->unk252 = type;
    f->unk253 = 0;
    f->unk254 = 0;
    f->unk255 = arg4;
    f->unk_25B = arg3;
    f->unk259 = 0;
    f->unk25C = 0;
    f->unk25D = 0;
    f->unk25E = 0;
    f->unk25F = 0;
    f->unk264 = 0;
    f->unk260 = 0;
    if (type == 7) {
        f->unk260 = 1;
    }
    if (frames < g_Ball.framesUntilBallHitsGround) {
        f->unk264 = 1;
    }
    switch (type) {
    case 3:
        f->unk259 = 2;
        break;
    case 4:
        f->unk259 = 3;
        break;
    }
    g_Ball.catchAnimationTotalFrames = 0;
}

// .text:0x0002C2F0 size:0x3A8 mapped:0x8066B384
void fn_3_2C2F0(void) {
    return;
}

// .text:0x0002C698 size:0x548 mapped:0x8066B72C
void fn_3_2C698(void) {
    return;
}

// .text:0x0002CBE0 size:0x314 mapped:0x8066BC74
BOOL fn_3_2CBE0(s32 idx) {
    return FALSE;
}

// .text:0x0002CEF4 size:0x18C mapped:0x8066BF88
void fn_3_2CEF4(void) {
    return;
}

// .text:0x0002D080 size:0x288 mapped:0x8066C114
void fn_3_2D080(void) {
    return;
}

// .text:0x0002D308 size:0x174 mapped:0x8066C39C
void fn_3_2D308(void) {
    return;
}

// .text:0x0002D47C size:0x2EC mapped:0x8066C510
void fn_3_2D47C(void) {
    return;
}

// .text:0x0002D768 size:0x1C4 mapped:0x8066C7FC
void fn_3_2D768(void) {
    return;
}

// .text:0x0002D92C size:0x198 mapped:0x8066C9C0
void fn_3_2D92C(void) {
    return;
}

// .text:0x0002DAC4 size:0x230 mapped:0x8066CB58
void fn_3_2DAC4(void) {
    return;
}

// .text:0x0002DCF4 size:0xC0 mapped:0x8066CD88
void fn_3_2DCF4(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (g_Ball.framesSinceHit > 0 && g_Ball.framesSinceHit >= f->unk1D2 && fn_3_53130(idx) == 0) {
        fn_3_447C4(idx);
        if (idx != -1) {
            f->unk1D3 = 0x1B;
            if (lbl_3_data_3C40.unkD8 >= 0) {
                g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unkD8;
            }
            f->unk1D5 = 0;
            f->unk1D6 = 0;
            f->unk1A4 = 0;
            f->unk1AC = 0;
            f->unk1FF = 0;
        }
    }
}

// .text:0x0002DDB4 size:0x668 mapped:0x8066CE48
void fn_3_2DDB4(void) {
    return;
}

// .text:0x0002E41C size:0x460 mapped:0x8066D4B0
void fn_3_2E41C(void) {
    return;
}

// .text:0x0002E87C size:0x1A8 mapped:0x8066D910
void fn_3_2E87C(void) {
    return;
}

// .text:0x0002EA24 size:0x64 mapped:0x8066DAB8
void fn_3_2EA24(void) {
    s32 i = 0;
    do {
        s8 idx = g_Minigame.minigameFielderIndex[i];
        if (idx >= 0) {
            fn_3_55EEC(idx);
        }
        i++;
    } while (i < 4);
    fn_3_2E41C();
    fn_3_313B0();
}

// .text:0x0002EA88 size:0x43C mapped:0x8066DB1C
void fn_3_2EA88(s32 idx) {
    return;
}

// .text:0x0002EEC4 size:0x5C0 mapped:0x8066DF58
void fn_3_2EEC4(s32 idx) {
    return;
}

// .text:0x0002F484 size:0xF0 mapped:0x8066E518
void fn_3_2F484(void) {
    s32 i;

    fn_3_58688();
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameFielderIndex[i] < 0) {
            continue;
        }
        g_FieldingLogic.unk70 = &g_FieldingLogic.entries[i];
        g_FieldingLogic.unk8C = &g_FieldingLogic.targets[i];
        if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame._19BC != 0 &&
            i == (s8)g_Minigame._19C6 && fn_3_2CBE0(i)) {
            continue;
        }
        if (g_Minigame.players.battingHandedness[i] == 0) {
            fn_3_2EEC4(i);
        } else if (g_Minigame.GameMode_MiniGame == 6) {
            fn_3_2EEC4(i);
        } else {
            fn_3_2EA88(i);
        }
    }
}

// .text:0x0002F574 size:0x260 mapped:0x8066E608
void fn_3_2F574(s32 fielderIdx) {
    return;
}

// .text:0x0002F7D4 size:0x150 mapped:0x8066E868
void fn_3_2F7D4(void) {
    return;
}

// .text:0x0002F924 size:0x278 mapped:0x8066E9B8
void fn_3_2F924(void) {
    return;
}

// .text:0x0002FB9C size:0x390 mapped:0x8066EC30
void fn_3_2FB9C(void) {
    return;
}

// .text:0x0002FF2C size:0x18C mapped:0x8066EFC0
void fn_3_2FF2C(void) {
    return;
}

// .text:0x000300B8 size:0x15C mapped:0x8066F14C
void fn_3_300B8(void) {
    return;
}

// .text:0x00030214 size:0x350 mapped:0x8066F2A8
void fn_3_30214(void) {
    return;
}

extern f32 lbl_3_data_4930[43];
// .text:0x00030564 size:0xB8 mapped:0x8066F5F8
BOOL fn_3_30564(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (f->unk25E == 3) {
        f->unk150 *= lbl_3_data_4930[14];
        f->unk158 *= lbl_3_data_4930[14];
        f->pos[0] += f->unk150;
        f->pos[2] += f->unk158;
        f->prevPos[0] = f->pos[0];
        f->prevPos[2] = f->pos[2];
        f->unk1F0 = 1;
    } else if (f->unk25E == 4) {
        f->unk50 = 0.0f;
        f->unk25F--;
        if (f->unk25F == 0) {
            f->unk25E = 0;
        }
    }
    return TRUE;
}

// .text:0x0003061C size:0x29C mapped:0x8066F6B0
void fn_3_3061C(void) {
    return;
}

// .text:0x000308B8 size:0x1A0 mapped:0x8066F94C
void fn_3_308B8(s32 fielderIdx, f32 x, f32 z) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 dx;
    f32 dz;

    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
        return;
    }
    f->unk64 = atan2(dz, dx);
    f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    f->unk1D9 = 1;
}

// .text:0x00030A58 size:0x31C mapped:0x8066FAEC

void fn_3_30A58(void) {
    Fielder* f;
    s32 i;
    f32 x;
    f32 z;

    for (i = 2, f = &g_Fielders[2]; i < 9; i++, f++) {
        fn_3_58F58(i, &x, &z);
        if (dolsqrtf2((f->pos[0] - x) * (f->pos[0] - x) + (f->pos[2] - z) * (f->pos[2] - z)) < 0.1f) {
            x = f->pos[0];
            z = f->pos[2];
        }
        aimFielderAt(f, x, z);
    }
}

// .text:0x00030D74 size:0x63C mapped:0x8066FE08
void fn_3_30D74(void) {
    s32 i;
    Fielder* f;
    Fielder* g;
    s32 j;
    f32 z;
    f32 x;
    s32 moving;
    s16 t;

    if (lbl_3_common_bss_34C90.field_0x1D5 != 0) {
        return;
    }
    g = &g_Fielders[2];
    for (i = 2, f = g; i < 9; i++, f++) {
        fn_3_58F58(i, &x, &z);
        if (dolsqrtf2((f->pos[0] - x) * (f->pos[0] - x) + (f->pos[2] - z) * (f->pos[2] - z)) < 0.1f) {
            x = f->pos[0];
            z = f->pos[2];
        }
        aimFielderAt(f, x, z);
    }
    for (j = 2; j < 9; j++, g++) {
        moving = 0;
        if (g->unk68 > 0.2f) {
            moving = 1;
        } else if (g->unk50 >= 0.1f && g->unk68 > 0.05f) {
            moving = 1;
        }
        if (moving) {
            t = g_Pitcher.pitchTotalTimeCounter;
            if (t <= 0) {
                g->unk50 = 0.1f;
            } else if (g_Batter.buntStatus >= 1 && g_Batter.buntStatus <= 3 && (j == 2 || j == 4)) {
                g->unk50 += g->unk5C;
                if (g->unk50 > g->unk58) {
                    g->unk50 = g->unk58;
                }
            } else if (((j == 3 && g_Batter.batterHand == 0) || (j == 5 && g_Batter.batterHand != 0)) &&
                       g_Runners[1].runnerOnFieldOrOutOrScored != 0 && g_Runners[1].furthestBaseForcedToGoToOnWalk != 0) {
                g->unk50 += g->unk5C;
                if (g->unk50 > g->unk58) {
                    g->unk50 = g->unk58;
                }
            } else if (t < 60) {
                g->unk17E = 60 - t;
                g->unk50 = g->unk68 / g->unk17E;
            } else {
                g->unk17E = 0;
                g->unk50 = 0.0f;
            }
            g->unk68 -= g->unk50;
            if (g->unk50 <= 0.0f) {
                g->unk50 = 0.0f;
                g->unk17E = -1;
            } else if (g->unk68 < 0.0f) {
                g->unk30 = g->prevPos[0] - g->pos[0];
                g->unk34 = g->prevPos[2] - g->pos[2];
                g->pos[0] = g->prevPos[0];
                g->pos[2] = g->prevPos[2];
                g->unk68 = 0.0f;
                g->unk17E = 0;
            } else {
                g->unk30 = g->unk50 * (f32)cos(g->unk64);
                g->unk34 = g->unk50 * (f32)sin(g->unk64);
                g->pos[0] += g->unk30;
                g->pos[2] += g->unk34;
                g->unk17E = g->unk68 / g->unk50;
            }
            g->unk1E3 = 0;
        } else {
            g->unk30 = g->prevPos[0] - g->pos[0];
            g->unk34 = g->prevPos[2] - g->pos[2];
            g->pos[0] = g->prevPos[0];
            g->pos[2] = g->prevPos[2];
            g->unk68 = 0.0f;
            g->unk50 = 0.0f;
            g->unk1E3 = 1;
            g->unk17E = -1;
        }
    }
    g_Fielders[0].pos[0] = g_Pitcher.pitcher.x;
    g_Fielders[0].pos[2] = g_Pitcher.pitcher.z;
}

// .text:0x000313B0 size:0x1E4 mapped:0x80670444
void fn_3_313B0(void) {
    return;
}

// .text:0x00031594 size:0xE4 mapped:0x80670628
void fn_3_31594(void) {
    InputStruct* inputs;
    s32 i;

    inputs = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    for (i = 19; i > 0; i--) {
        lbl_3_bss_170[i] = lbl_3_bss_170[i - 1];
    }
    if (ACTIVE_TUTORIAL) {
        inputs = &g_Practice.inputs[g_GameLogic.teamFielding];
    }
    g_FieldingLogic.unk148 = inputs->buttonInput;
    g_FieldingLogic.unk14A = inputs->newButtonInput;
    g_FieldingLogic.unk14C = inputs->_08;
    for (i = 0; i < 9; i++) {
        fn_3_55EEC(i);
    }
    fn_3_30D74();
    fn_3_313B0();
}

// .text:0x00031678 size:0x3C4 mapped:0x8067070C
void fn_3_31678(void) {
    return;
}

// .text:0x00031A3C size:0x214 mapped:0x80670AD0
void fn_3_31A3C(void) {
    return;
}

// .text:0x00031C50 size:0x440 mapped:0x80670CE4
void fn_3_31C50(void) {
    return;
}

// .text:0x00032090 size:0x314 mapped:0x80671124
void fn_3_32090(void) {
    return;
}

// .text:0x000323A4 size:0x450 mapped:0x80671438
void fn_3_323A4(void) {
    return;
}

// .text:0x000327F4 size:0x1C mapped:0x80671888
BOOL fn_3_327F4(void) {
    return g_Ball.hitClassification2 == 1;
}

// .text:0x00032810 size:0x194 mapped:0x806718A4
void fn_3_32810(void) {
    return;
}

// .text:0x000329A4 size:0x6E4 mapped:0x80671A38
void fn_3_329A4(void) {
    return;
}

// .text:0x00033088 size:0x3D0 mapped:0x8067211C
void fn_3_33088(void) {
    return;
}

// .text:0x00033458 size:0x94 mapped:0x806724EC
void fn_3_33458(void) {
    Fielder* f;
    s32 idx;

    fn_3_334EC(1);
    fn_3_33088();
    idx = g_FieldingLogic.unkB2;
    f = &g_Fielders[idx];
    if (idx != -1) {
        f->unk1D3 = 0x16;
        if (lbl_3_data_3C40.unkB0 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unkB0;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x000334EC size:0x8B0 mapped:0x80672580
void fn_3_334EC(s32 arg0) {
    return;
}

// .text:0x00033D9C size:0x34 mapped:0x80672E30

void fn_3_33D9C(void) {
    fn_3_49F40(6,7);
    fn_3_49F40(8,6);
}

// .text:0x00033DD0 size:0x418 mapped:0x80672E64
void fn_3_33DD0(void) {
    return;
}

// .text:0x000341E8 size:0x268 mapped:0x8067327C
void fn_3_341E8(void) {
    return;
}

// .text:0x00034450 size:0x5F0 mapped:0x806734E4
void fn_3_34450(void) {
    return;
}

// .text:0x00034A40 size:0x12E8 mapped:0x80673AD4
void fn_3_34A40(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    f32 dist;
    f32 t;
    f32 a;
    f32 x;
    f32 z;
    s32 frames;
    s32 n;
    s32 i;

    if (g_Ball.fielderWBallIndex >= 0 && g_Ball.fielderWBallIndex != idx) {
        if (f->unk50 == 0.0f) {
            f->unk68 = 0.0f;
            f->prevPos[0] = f->pos[0];
            f->prevPos[1] = f->pos[1];
            f->prevPos[2] = f->pos[2];
            f->unk30 = 0.0f;
            f->unk34 = 0.0f;
        }
        goto tail;
    }
    f->unk1D6 = 0;
    f->unk1EB = 0;
    f->unk1A4 = 0;
    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        if (g_Ball.AtBat_ContactResult != 0 || g_Ball.hitClassification1 != 2) {
            goto chase;
        }
        dist = dolsqrtf2((g_Ball.ballWillHitBallPos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x) *
                             (g_Ball.ballWillHitBallPos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x) +
                         (g_Ball.ballWillHitBallPos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z) *
                             (g_Ball.ballWillHitBallPos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z));
        if (g_Ball.ballVelocity > 0.0f || dist > 20.0f) {
            if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 3.0f) {
                if (f->unk70 < 15.0f) {
                    setFielderTarget(f, f->pos[0], f->pos[2]);
                } else {
                    x = 15.0f * (f->pos[0] / f->unk70);
                    z = 15.0f * (f->pos[2] / f->unk70);
                    setFielderTargetIdx(idx, x, z);
                }
            } else {
                x = 15.0f * (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x /
                             g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) +
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                z = 15.0f * (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z /
                             g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) +
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
                setFielderTargetIdx(idx, x, z);
            }
        } else {
            setFielderTargetIdx(idx, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        }
        if (f->unk68 < 10.0f) {
            f->unk1D6 = 8;
        }
        goto tail;
    }
    if (g_Ball.AtBat_ContactResult != 0) {
        goto chase;
    }
    frames = fielderFramesToReach(f, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                  g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    if (g_Ball.framesUntilBallHitsGround - frames > 10) {
        setFielderTargetIdx(idx, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                            g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    } else {
        for (i = 10; i < 70; i += 10) {
            if (i == 60) {
                setFielderTargetIdx(idx,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilBallHitsGround + i].pos.x,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[g_Ball.framesUntilBallHitsGround + i].pos.z);
                break;
            }
            n = g_Ball.framesUntilBallHitsGround + i;
            if (n - fielderFramesToReach(f, g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x,
                                         g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z) > 5) {
                setFielderTargetIdx(idx, g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z);
                break;
            }
        }
    }
    if (idx <= 5) {
        if (f->unk80 < 10.0f) {
            f->unk1D6 = 8;
        }
    } else if (g_FieldingLogic.unkB0 <= 5 &&
               g_Ball.ballDistanceFromHome < g_Fielders[g_FieldingLogic.unkB0].unk70) {
        if (f->unk80 < 5.0f) {
            f->unk1D6 = 8;
        }
    } else if (f->unk80 < 10.0f) {
        f->unk1D6 = 8;
    }
    goto tail;

chase:
    a = f->unk7C;
    t = 1.0f + ((a - 15.0f) / 100.0f + (g_Ball.ballVelocity - 0.6f));
    x = t * (f->unk74 * g_Ball.ballVelocityPercent.x) + g_Ball.AtBat_Contact_BallPos.x;
    z = t * (f->unk74 * g_Ball.ballVelocityPercent.z) + g_Ball.AtBat_Contact_BallPos.z;
    if (idx >= 6 && f->unk70 < 50.0f) {
        x = f->pos[0];
        z = f->pos[2];
    }
    setFielderTarget(f, x, z);
    if (f->unk74 < 20.0f && a < 5.0f) {
        if (lbl_3_bss_170[0] >= 0) {
            if (__abs(lbl_3_bss_170[0] - radToShortAngle(atan2(g_Ball.AtBat_Contact_BallPos.z - f->pos[2],
                                                                g_Ball.AtBat_Contact_BallPos.x - f->pos[0]))) > 0x80) {
                f->unk1D6 = 8;
            }
        } else {
            f->unk1D6 = 8;
        }
    }

tail:
    if (f->unk50 < 0.01f && f->unk1D6 == 8) {
        f->unk68 = 0.0f;
        f->unk50 = 0.0f;
        f->prevPos[0] = f->pos[0];
        f->prevPos[2] = f->pos[2];
        f->unk1A0 = 0;
        f->unk1D6 = 0;
    }
    fn_3_526DC(idx);
    if (f->unk50 != 0.0f) {
        f->unk17E = f->unk68 / f->unk50;
    }
}

// .text:0x00035D28 size:0xF4 mapped:0x80674DBC
void fn_3_35D28(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (fn_3_53130(idx) != 0) {
        return;
    }
    fn_3_34A40(idx);
    fn_3_4207C(idx);
    if (g_Ball.ballState == 0) {
        return;
    }
    if (g_Ball.ballState == 3) {
        return;
    }
    if (idx != -1) {
        f->unk1D3 = 0xC;
        if (lbl_3_data_3C40.unk60 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unk60;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
    if (idx <= 5) {
        f->unk1D5 = 3;
    } else {
        f->unk1D5 = 2;
    }
}

// .text:0x00035E1C size:0x3BC mapped:0x80674EB0
void fn_3_35E1C(void) {
    return;
}

// .text:0x000361D8 size:0x3F8 mapped:0x8067526C
void fn_3_361D8(void) {
    return;
}

// .text:0x000365D0 size:0xA8 mapped:0x80675664
s32 fn_3_365D0(s32 arg0, s32 arg1, s32 arg2, f32 x, f32 z) {
    s32 result = fn_3_36678(arg1, arg2, 1, x, z);
    if (result == -1) {
        return arg0;
    }
    if (g_FieldingLogic.unkB0 < 0) {
        return fn_3_36678(arg0, result, 1, x, z);
    }
    return fn_3_36678(arg0, result, 0, x, z);
}

// .text:0x00036678 size:0xA9C mapped:0x8067570C
s32 fn_3_36678(s32 arg0, s32 arg1, s32 arg2, f32 x, f32 z) {
    return 0;
}

// .text:0x00037114 size:0x2F8 mapped:0x806761A8
void fn_3_37114(void) {
    return;
}

// .text:0x0003740C size:0x17C mapped:0x806764A0
void fn_3_3740C(void) {
    s16 ang;
    f32 maxV = 0.0f;
    s32 minDiff = 0x1000;
    s32 best = -1;
    s32 i;
    s32 diff;

    if (g_Ball.ballState == 0 && g_FieldingLogic.unkB0 <= 5) {
        for (i = 0; i < 6; i++) {
            if (g_Fielders[i].unk70 > maxV) {
                maxV = g_Fielders[i].unk70;
            }
        }
        if (5.0f + maxV < g_Ball.ballDistanceFromHome) {
            ang = g_Ball.ballAngleFromHome;
            for (i = 6; i < 9; i++) {
                diff = __abs(ang - g_Fielders[i].unk180);
                if (minDiff > diff) {
                    minDiff = diff;
                    best = i;
                }
            }
            g_Ball.ballAngleFromHome = ang;
            if (i >= 0) {
                fn_3_38790(best, 0);
            }
        }
    }
}

// .text:0x00037588 size:0x88 mapped:0x8067661C
void fn_3_37588(void) {
    if (g_Ball.ballVelocity > 0.17f) {
        fn_3_38790(fn_3_378B4(), 0);
    } else if (g_Ball.AtBat_ContactResult == 0 && g_Ball.hitClassification1 != 0) {
        fn_3_37610(g_Ball.framesUntilBallHitsGround);
    } else if (g_Ball.AtBat_ContactResult == 0) {
        fn_3_37610(30);
    } else {
        fn_3_37610(30);
    }
}

// .text:0x00037610 size:0x2A4 mapped:0x806766A4
void fn_3_37610(s32 arg0) {
    return;
}

// .text:0x000378B4 size:0x74C mapped:0x80676948
s32 fn_3_378B4(void) {
    return 0;
}

// .text:0x00038000 size:0x234 mapped:0x80677094
void fn_3_38000(void) {
    return;
}

// .text:0x00038234 size:0xD0 mapped:0x806772C8
void fn_3_38234(void) {
    if (g_Ball.hitClassification2 <= 4 || g_Ball.hitClassification2 == 7) {
        fn_3_38000();
    } else if (g_Ball.maxYOfHit > 7.0f) {
        fn_3_38304();
    } else if (g_Ball.maxYOfHit < 4.0f) {
        fn_3_38000();
    } else if (g_Ball.someYCoord > 5.0f) {
        fn_3_38304();
    } else if (g_Ball.ballDistanceFromHome < 60.0f) {
        if (lbl_3_bss_170[0] >= 0x900 && lbl_3_bss_170[0] < 0xF00) {
            fn_3_38304();
        } else {
            fn_3_38000();
        }
    } else {
        fn_3_38304();
    }
}

// .text:0x00038304 size:0x48C mapped:0x80677398
void fn_3_38304(void) {
    return;
}

// .text:0x00038790 size:0x580 mapped:0x80677824
void fn_3_38790(s32 arg0, s32 arg1) {
    return;
}

// .text:0x00038D10 size:0x2E8 mapped:0x80677DA4
void fn_3_38D10(void) {
    return;
}

// .text:0x00038FF8 size:0x3B8 mapped:0x8067808C
void fn_3_38FF8(void) {
    return;
}

// .text:0x000393B0 size:0x4A8 mapped:0x80678444
void fn_3_393B0(void) {
    return;
}

// .text:0x00039858 size:0x56C mapped:0x806788EC
void fn_3_39858(void) {
    return;
}

// .text:0x00039DC4 size:0xEC mapped:0x80678E58
static inline void clearFielderAction(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (idx != -1) {
        f->unk1D3 = 0;
        if (lbl_3_data_3C40.unk0 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unk0;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
}

void fn_3_39DC4(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        g_FieldingLogic.unk_F8[i] = 0;
        clearFielderAction(i);
        g_Fielders[i].unk20 = 10000.0f;
        g_Fielders[i].unk24 = 0.0f;
    }
    g_FieldingLogic.unkB0 = -1;
    g_FieldingLogic.unkB2 = -1;
    g_FieldingLogic.unkB4 = -1;
    g_FieldingLogic.unkBE = -1;
    g_FieldingLogic.unk139 = 0;
    for (i = 0; i < 4; i++) {
        g_FieldingLogic.unkD0[i] = -1;
        g_FieldingLogic.unk101[i] = 0;
    }
    fn_3_37610(120);
}

// .text:0x00039EB0 size:0x34C mapped:0x80678F44
void fn_3_39EB0(void) {
    return;
}

// .text:0x0003A1FC size:0x38 mapped:0x80679290

#include "game/UnknownHomes_Game.h"

void fn_3_3A1FC(s32 index) {
    /* mulli r4, r3, 0x268 triggers from indexing the global array */
    Fielder *fielder = &g_Fielders[index];

    /* lha r0, 0x1b6(r4) loads a signed halfword */
    if (fielder->unk1B6 != 0) {
        /* Branch taken: copy unk54 to unk50 and exit */
        fielder->unk50 = fielder->unk54;
        return;
    }

    /* Branch not taken: load from rodata and exit */
    fielder->unk50 = lbl_3_rodata_B20;
}

// .text:0x0003A234 size:0x350 mapped:0x806792C8
void fn_3_3A234(void) {
    return;
}

// .text:0x0003A584 size:0x574 mapped:0x80679618
void fn_3_3A584(void) {
    return;
}

// .text:0x0003AAF8 size:0xF8 mapped:0x80679B8C
void fn_3_3AAF8(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 v = lbl_3_bss_170[0];

    if (g_FieldingLogic.unk10E) {
        v = -1;
    }
    f->unk19E = v;
    if (!g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] && v >= 0 && f->unk1A0 > 10) {
        g_FieldingLogic.unkCC = -1;
    }
    if (v < 0) {
        return;
    }
    if (g_FieldingLogic.unk70->unk1A == 3) {
        return;
    }
    if (g_FieldingLogic.unk70->unk1A == 4) {
        return;
    }
    if (g_FieldingLogic.unk14A & 0x200) {
        g_FieldingLogic.unk70->unkC = 0;
    }
    if (ACTIVE_TUTORIAL && g_Practice.practice_fielding_enableSprinting) {
        g_FieldingLogic.unk70->unkC = 0;
    }
}

typedef struct Data484C {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Data484C;
extern Data484C lbl_3_data_484C;

// .text:0x0003ABF0 size:0xD0 mapped:0x80679C84
void fn_3_3ABF0(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    Fielder* other = &g_Fielders[g_FieldingLogic.unkB0];

    if (g_Ball.framesSinceHit < lbl_3_data_484C.unk0) {
        return;
    }
    if (g_FieldingLogic.unk139 != 0) {
        return;
    }
    if ((other->unk256 == 1 && f->unk84[g_FieldingLogic.unkB0] < 15.0f) || (other->unk252 != 0 && other->unk_25B == 0)) {
        g_Fielders[idx].prevPos[0] = f->pos[0];
        g_Fielders[idx].prevPos[1] = f->pos[1];
        g_Fielders[idx].prevPos[2] = f->pos[2];
        g_Fielders[idx].unk30 = 0.0f;
        g_Fielders[idx].unk34 = 0.0f;
        g_Fielders[idx].unk50 = 0.0f;
        g_Fielders[idx].unk68 = 0.0f;
    }
}

// .text:0x0003ACC0 size:0x174 mapped:0x80679D54
extern s16 lbl_3_bss_16C;

void fn_3_3ACC0(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (g_Ball.fielderWithBallIndexStored >= 0) {
        goto set;
    }
    if (idx != g_FieldingLogic.unkB0) {
        return;
    }
    if (g_FieldingLogic.unk139 != 0) {
        return;
    }
    if (g_Ball.framesSinceHit < lbl_3_data_484C.unk0) {
        return;
    }
    if (g_Ball.framesSinceHit >= lbl_3_data_484C.unk2) {
        goto set;
    }
    if (lbl_3_bss_170[0] >= 0 && (g_FieldingLogic.unk148 & 0x200)) {
        goto set;
    }
    if (ACTIVE_TUTORIAL && g_Practice.practice_fielding_enableSprinting != 0) {
        goto set;
    }
    if (f->unk201 != 0 && idx >= 6 && idx <= 8 && g_Ball.ballZoneAwayFromHome == 0) {
        return;
    }
    if (lbl_3_bss_16C < 0) {
        return;
    }
    if (f->unk19A < 0) {
        if (g_Ball.framesSinceHit > f->unk1D2 + 3) {
            goto set;
        }
    } else {
        if (fn_3_9FCF8(lbl_3_bss_16C, f->unk19A) < lbl_3_data_484C.unk4) {
            goto set;
        }
    }
    return;
set:
    f->unk1FF = 2;
    f->unk201 = 0;
}

// .text:0x0003AE34 size:0x53C mapped:0x80679EC8
void fn_3_3AE34(void) {
    return;
}

// .text:0x0003B370 size:0x3F4 mapped:0x8067A404
void fn_3_3B370(void) {
    return;
}

// .text:0x0003B764 size:0x238 mapped:0x8067A7F8
void fn_3_3B764(void) {
    return;
}

// .text:0x0003B99C size:0x48 mapped:0x8067AA30

void fn_3_3B99C(void) {
    // Check MiniGame Mode (lbz r0, 0x1a2a(r3))
    if (g_Minigame.GameMode_MiniGame == 5) {
        return;
    }

    // Check Fielding Flags (lhz r0, 0x14a(r5))
    // rlwinm. r0, r0, 0, 23, 23 checks bit 0x100
    if (!(g_FieldingLogic.unk14A & 0x100)) {
        return;
    }

    // Update target values
    g_FieldingLogic.unk8C->unk2 = 2;
    g_FieldingLogic.unk8C->unk0 = lbl_3_bss_170[0];
}

// .text:0x0003B9E4 size:0x46C mapped:0x8067AA78
void fn_3_3B9E4(void) {
    return;
}

// .text:0x0003BE50 size:0x358 mapped:0x8067AEE4
void fn_3_3BE50(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 t;
    f32 x;
    f32 z;

    if (f->unk1EC != 0) {
        return;
    }
    if (g_Ball.framesSinceThrowStarted == 5 && g_Ball.ballVelocity != 0.0f) {
        t = f->unk74 / g_Ball.ballVelocity;
        x = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
        z = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        if (dolsqrtf2((f->pos[0] - x) * (f->pos[0] - x) + (f->pos[2] - z) * (f->pos[2] - z)) > f->unkE8) {
            f->unk1E9 = 1;
            setFielderTarget(f, x, z);
        }
    }
    fn_3_526DC(fielderIdx);
    if (f->unk1E9 != 0 && f->unk50 == 0.0f) {
        f->unk1E9 = 0;
    }
    if (g_Ball.fielderBeingThrownTo == fielderIdx) {
        fn_3_4E638();
    }
}

// .text:0x0003C1A8 size:0x78 mapped:0x8067B23C
void fn_3_3C1A8(s32 index) {
    Fielder* fielder = &g_Fielders[index];

    if (fielder->unk1EC != 0) {
        return;
    }
    if (fn_3_53130(index) != 0) {
        return;
    }

    fielder->unk50 = lbl_3_rodata_B20;
    fielder->unk1E3 = 1;
    fielder->unk1D5 = 0;
    fielder->prevPos[0] = fielder->pos[0];
    fielder->prevPos[2] = fielder->pos[2];
}

// .text:0x0003C220 size:0x50 mapped:0x8067B2B4


void fn_3_3C220(s32 index) {
    // 1. Force mulli r5, r3, 0x268 by calculating the offset first
    s32 offset = index * 0x268; 
    
    // 2. Define r31 as the base address + the pre-calculated offset
    // This anchors r31 and forces the lis r4 / addi r0 sequence for g_Fielders
    Fielder* fielder = (Fielder*)((u8*)g_Fielders + offset);
    
    // fn_3_53130 returns an int in r3, which is then used by cmpwi
    if (fn_3_53130(index) == 0) {
        // Use a local to ensure a single lfs f0 is used for both stores
        f32 val = lbl_3_rodata_B20;
        fielder->unk50 = val;
        fielder->unk68 = val;
    }
}




// .text:0x0003C270 size:0x214 mapped:0x8067B304
s32 fn_3_3C270(s32 idx) {
    sendFielderToHome(idx);
    return 1;
}

// .text:0x0003C484 size:0x110 mapped:0x8067B518
void fn_3_3C484(void) {
    return;
}

// .text:0x0003C594 size:0x5F8 mapped:0x8067B628
s32 fn_3_3C594(s32 fielderIdx) {
    return 0;
}

// .text:0x0003CB8C size:0x124 mapped:0x8067BC20
BOOL fn_3_3CB8C(s32 idx) {
    Fielder* f;

    if (g_Ball.AtBat_ContactResult > 1) {
        return FALSE;
    }
    if (g_Ball.hitWallInd != 0) {
        return FALSE;
    }
    if (g_FieldingLogic.unkBC >= 0) {
        return FALSE;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        if (g_Ball.landingSpotZoneAwayFromHome >= 1 && idx >= 6) {
            if (g_Ball.landingSpotAngle < 0x380 && idx == 6) {
                return FALSE;
            }
            if (g_Ball.landingSpotAngle > 0x480 && idx == 8) {
                return FALSE;
            }
            goto set;
        }
    } else if (idx >= 6 && idx == g_FieldingLogic.unkB8) {
        goto set;
    }
    return FALSE;
set:
    f = &g_Fielders[idx];
    if (idx != -1) {
        f->unk1D3 = 0x18;
        if (lbl_3_data_3C40.actions[0x18].unk0 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.actions[0x18].unk0;
        }
        g_FieldingLogic.unkBC = idx;
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
    g_FieldingLogic.unkBC = idx;
    return TRUE;
}

// .text:0x0003CCB0 size:0x654 mapped:0x8067BD44
static inline s32 tryCoverNearBase(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];

    if (f->unkA8[0] < 5.0f) {
        f->unk18C = 9;
    } else if (f->unkA8[1] < 5.0f) {
        f->unk18C = fn_3_3D7D4(fielderIdx);
    } else if (f->unkA8[2] < 5.0f) {
        f->unk18C = fn_3_3D7D4(fielderIdx);
    } else if (f->unkA8[3] < 5.0f) {
        f->unk18C = fn_3_3D7D4(fielderIdx);
    } else {
        return 0;
    }
    f->unk1D7 = 2;
    if (fielderIdx != -1) {
        setFielderReadyAction(fielderIdx, 0xE);
    }
    f->unk1D6 = 0xB;
    return 1;
}

static inline s32 tryOutfieldBackup(s32 fielderIdx) {
    if (g_Ball.AtBat_ContactResult > 1) {
        return 0;
    }
    if (g_Ball.hitWallInd != 0) {
        return 0;
    }
    if (g_FieldingLogic.unkBC >= 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        if (g_Ball.landingSpotZoneAwayFromHome >= 1 && fielderIdx >= 6) {
            if (g_Ball.landingSpotAngle < 0x380 && fielderIdx == 6) {
                return 0;
            }
            if (g_Ball.landingSpotAngle > 0x480 && fielderIdx == 8) {
                return 0;
            }
            goto backup;
        }
    } else if (fielderIdx >= 6 && fielderIdx == g_FieldingLogic.unkB8) {
        goto backup;
    }
    return 0;
backup:
    if (fielderIdx != -1) {
        setFielderReadyAction(fielderIdx, 0x18);
        g_FieldingLogic.unkBC = fielderIdx;
    }
    g_FieldingLogic.unkBC = fielderIdx;
    return 1;
}

void fn_3_3CCB0(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 i;

    if (f->unk1EC != 0) {
        return;
    }
    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_FieldingLogic.unkC4 == 5 && f->unk18C == 5) {
        fn_3_3BE50(fielderIdx);
        return;
    }
    if (fielderIdx <= 5) {
        if (fn_3_3C594(fielderIdx) != 0) {
            return;
        }
        if (tryCoverNearBase(fielderIdx) != 0) {
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (fielderIdx == g_FieldingLogic.unkD0[i]) {
            f->unk18C = i;
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 1);
            }
            return;
        }
    }
    if (fielderIdx >= 6) {
        if (tryOutfieldBackup(fielderIdx) != 0) {
            return;
        }
        if (f->unk18C != 7) {
            startFielderChase(fielderIdx);
            return;
        }
    } else if (f->unk70 > 45.0f) {
        f->unk18C = fn_3_3D7D4(fielderIdx);
        f->unk1D7 = 2;
        if (fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0xE);
        }
        f->unk1D6 = 0xB;
        return;
    }
    if (f->unk1DE != 0) {
        sendFielderToHome(fielderIdx);
    } else {
        f->unk30 = 0.0f;
        f->unk34 = 0.0f;
        f->unk50 = 0.0f;
    }
}

// .text:0x0003D304 size:0x3A8 mapped:0x8067C398
void fn_3_3D304(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 x;
    f32 z;
    f32 offX;
    f32 offZ;

    if (f->unk20F != 0) {
        g_FieldingLogic.unk111 = 0;
        return;
    }
    if (f->unk210 != 0) {
        fn_3_251E4();
        f->unk1EE = 0;
        return;
    }
    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (f->unk211 != 0) {
        fn_3_A96FC(fielderIdx);
        return;
    }
    if (f->unk1EE != 0) {
        fn_3_A9984(fielderIdx);
        return;
    }
    if (f->unk1EF != 0) {
        return;
    }
    if (f->unk203 != 0) {
        fn_3_2F574(fielderIdx);
        return;
    }
    if (g_Ball.fielderWBallIndex == fielderIdx && f->unk1EC == 0) {
        g_Ball.fielderWBallIndex = -1;
    }
    x = lbl_3_data_4290[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam].x;
    z = lbl_3_data_4290[g_d_GameSettings.StadiumID][g_GameLogic.awayTeamBattingInd_battingTeam].z;
    if (f->unk178 != g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding]) {
        fn_3_9F79C(lbl_3_data_4348[g_d_GameSettings.StadiumID][g_GameLogic.teamFielding], lbl_3_data_4300[fielderIdx].x,
                   lbl_3_data_4300[fielderIdx].z, &offX, &offZ);
        x += offX;
        z += offZ;
    }
    f->unk1D6 = 0xD;
    setFielderTarget(f, x, z);
    fn_3_526DC(fielderIdx);
    if (f->unk68 <= 0.5f) {
        if (fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0);
        }
        f->unk1FA = 1;
    }
    if (fielderIdx == g_Ball.fielderWBallIndex) {
        g_FieldingLogic.unkC4 = -1;
    }
}

// .text:0x0003D6AC size:0x128 mapped:0x8067C740
void fn_3_3D6AC(s32 idx) {
    Fielder *temp_r31;
    s32 temp_r30;

    temp_r30 = idx;
    temp_r31 = &g_Fielders[temp_r30];
    if ((fn_3_53130(idx) == 0) && ((u8) temp_r31->unk1EC == 0)) {
        temp_r31->unk50 = 0.0f;
        temp_r31->unk1E3 = 1;
        temp_r31->unk1D5 = 0;
        temp_r31->prevPos[0] = temp_r31->pos[0];
        temp_r31->prevPos[2] = temp_r31->pos[2];
        if (g_Ball.ballState == 0) {
            if (temp_r30 == 6) {
                if (g_Ball.ballAngleFromHome < 0x400) goto finish;
                if (g_Ball.ballAngleFromHome < 0xC00) goto action;
                goto finish;
            }
            if (temp_r30 == 8) {
                if (g_Ball.ballAngleFromHome < 0x400) goto action;
                if (g_Ball.ballAngleFromHome < 0xC00) goto finish;
            }
        }
        {
        action:
            if (temp_r30 != -1) {
                temp_r31->unk1D3 = 9;
                if ((s32) lbl_3_data_3C40.actions[9].unk0 >= 0) {
                    g_FieldingLogic.unk_F8[temp_r30] = (s8) lbl_3_data_3C40.actions[9].unk0;
                }
                temp_r31->unk1D5 = 0;
                temp_r31->unk1D6 = 0;
                temp_r31->unk1A4 = 0;
                temp_r31->unk1AC = 0;
                temp_r31->unk1FF = 0;
            }
        }
finish:
        temp_r31->unk1F0 = 1;
    }
}

// .text:0x0003D7D4 size:0x3A4 mapped:0x8067C868
s16 fn_3_3D7D4(s32 idx) {
    return 0;
}

// .text:0x0003DB78 size:0x7D4 mapped:0x8067CC0C

void fn_3_3DB78(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s16 state;
    f32 ox;
    f32 oz;

    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (g_Ball.homeRunClassification != 0 && fielderIdx <= 1) {
        return;
    }
    state = f->unk18C;
    if (state == 5) {
        if (g_FieldingLogic.unkC4 == 5) {
            fn_3_3BE50(fielderIdx);
            fn_3_A7C88();
            if (g_Ball.fielderBeingThrownTo == fielderIdx) {
                fn_3_4E638();
            }
            return;
        }
        ox = oz = 2.0f;
        if (f->pos[0] < 0.0f) {
            ox = -2.0f;
        }
        if (f->pos[2] < lbl_3_data_4444[4].z) {
            oz = -2.0f;
        }
        if (g_FieldingLogic.unk105 != 0 && f->unk50 <= 0.03f) {
            stopFielder(fielderIdx);
            return;
        }
        setFielderTarget(f, lbl_3_data_4444[4].x + ox, lbl_3_data_4444[4].z + oz);
        fn_3_526DC(fielderIdx);
        if (f->unk68 < 3.0f) {
            g_FieldingLogic.unk105 = 1;
            f->unk68 = 0.0f;
            f->unk1D6 = 8;
        } else {
            g_FieldingLogic.unk105 = 0;
            f->unk1D6 = 0xB;
        }
    } else if (state == 7) {
        setFielderTargetIdx(fielderIdx, lbl_3_data_44B4[fielderIdx + 2].x, lbl_3_data_44B4[fielderIdx + 2].z);
        fn_3_526DC(fielderIdx);
        if (f->unk68 == 0.0f && fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0);
        }
    } else if (state >= 8 && state <= 13) {
        setFielderTargetIdx(fielderIdx, lbl_3_data_4484[state - 8].x, lbl_3_data_4484[state - 8].z);
        fn_3_526DC(fielderIdx);
        if (f->unk68 == 0.0f && fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0);
        }
    } else if (state == 14) {
        if (f->unk1DE == 0) {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0);
            }
            f->unk18C = -1;
        } else {
            fn_3_526DC(fielderIdx);
        }
    } else if (state == 15) {
        fn_3_526DC(fielderIdx);
        if (f->unk68 == 0.0f && fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0);
        }
    }
}

// .text:0x0003E34C size:0x11C mapped:0x8067D3E0
void fn_3_3E34C(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (f->unk19C >= 1) {
        if (f->unk1C5 != 0) {
            if (idx != -1) {
                f->unk1D3 = 0x12;
                if (lbl_3_data_3C40.unk90 >= 0) {
                    g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unk90;
                }
                f->unk1D5 = 0;
                f->unk1D6 = 0;
                f->unk1A4 = 0;
                f->unk1AC = 0;
                f->unk1FF = 0;
            }
        } else {
            clearFielderAction(idx);
        }
    } else if (g_FieldingLogic.unk11C != 0) {
        clearFielderAction(idx);
    }
}

// .text:0x0003E468 size:0x228 mapped:0x8067D4FC
void fn_3_3E468(void) {
    return;
}

// .text:0x0003E690 size:0x4DC mapped:0x8067D724
void fn_3_3E690(void) {
    return;
}

// .text:0x0003EB6C size:0x4C8 mapped:0x8067DC00
void fn_3_3EB6C(void) {
    return;
}

// .text:0x0003F034 size:0xF0 mapped:0x8067E0C8
void fn_3_3F034(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        g_FieldingLogic.unk_F8[i] = 0;
        clearFielderAction(i);
    }
    for (i = 0; i < 4; i++) {
        g_FieldingLogic.unkD0[i] = -1;
        g_FieldingLogic.unk101[i] = 0;
    }
    g_FieldingLogic.unkBC = -1;
    g_FieldingLogic.unkBE = -1;
    g_FieldingLogic.unkC2 = -1;
    if (g_Ball.AtBat_ContactResult == 0 && g_Ball.hangtimeOfHit > 45) {
        fn_3_3EB6C();
    } else {
        fn_3_3E690();
    }
}

// .text:0x0003F124 size:0x128 mapped:0x8067E1B8
void fn_3_3F124(void) {
    setFielderReadyAction(0, 0x14);
    if ((g_Fielders[3].unk182 + g_Fielders[5].unk182) / 2 > g_Ball.Hit_HorizontalAngle) {
        setFielderReadyAction(3, 3);
    } else {
        setFielderReadyAction(5, 3);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x0003F24C size:0x514 mapped:0x8067E2E0
void fn_3_3F24C(void) {
    return;
}

// .text:0x0003F760 size:0x590 mapped:0x8067E7F4
void fn_3_3F760(void) {
    return;
}

// .text:0x0003FCF0 size:0x5B8 mapped:0x8067ED84
void fn_3_3FCF0(void) {
    return;
}

// .text:0x000402A8 size:0x95C mapped:0x8067F33C
void fn_3_402A8(void) {
    return;
}

// .text:0x00040C04 size:0x150 mapped:0x8067FC98
void fn_3_40C04(void) {
    return;
}

// .text:0x00040D54 size:0x34 mapped:0x8067FDE8

void fn_3_40D54(void) {
    fn_3_49F40(6, 7);
    fn_3_49F40(8, 6);
}

// .text:0x00040D88 size:0x424 mapped:0x8067FE1C
void fn_3_40D88(void) {
    return;
}

// .text:0x000411AC size:0x628 mapped:0x80680240
void fn_3_411AC(void) {
    return;
}

// .text:0x000417D4 size:0x1A8 mapped:0x80680868
void fn_3_417D4(void) {
    return;
}

// .text:0x0004197C size:0x3FC mapped:0x80680A10
void fn_3_4197C(void) {
    return;
}

// .text:0x00041D78 size:0x304 mapped:0x80680E0C
void fn_3_41D78(void) {
    return;
}

// .text:0x0004207C size:0x7D4 mapped:0x80681110
void fn_3_4207C(s32 idx) {
    return;
}

// .text:0x00042850 size:0x1B0 mapped:0x806818E4
void fn_3_42850(s32 fielderIdx) {
    setFielderTargetIdx(fielderIdx, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);
}

// .text:0x00042A00 size:0x1D0 mapped:0x80681A94

void fn_3_42A00(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;

    x = g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x;
    z = g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z;
    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
    } else {
        f->unk64 = atan2(dz, dx);
        f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    }
    f->unk1D9 = 1;
    if (f->unk184 <= 1) {
        f->unk1DC = 5;
    }
}

// .text:0x00042BD0 size:0x10C mapped:0x80681C64
void fn_3_42BD0(s32 fielderIndex) {
    Fielder* self = &g_Fielders[fielderIndex];
    s32 i;

    if (fielderIndex >= 6 && g_Ball.ballState == 0) {
        if (self->unk70 < g_Ball.ballDistanceFromHome) {
            fn_3_43038(fielderIndex);
            return;
        }
        for (i = 6; i < 9; i++) {
            if (i != fielderIndex && g_Fielders[i].unk1DC == 3 && g_Fielders[i].unk17E <= self->unk17E && g_Fielders[i].unk17E < 90) {
                fn_3_43038(fielderIndex);
                return;
            }
        }
    }
}

// .text:0x00042CDC size:0x35C mapped:0x80681D70
void fn_3_42CDC(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 x;
    f32 z;

    f->unk28 = 5.0f * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
    f->unk2C = 5.0f * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
    if (f->unk18A != 0) {
        fn_3_50DD8(fielderIdx, &x, &z, 1);
        setFielderTarget(f, x, z);
        f->unk20 = x;
        f->unk24 = z;
    } else {
        setFielderTargetIdx(fielderIdx, f->unk28, f->unk2C);
    }
}

// .text:0x00043038 size:0x3A8 mapped:0x806820CC

void fn_3_43038(s32 fielderIndex) {
    Fielder* f = &g_Fielders[fielderIndex];
    s32 frames;
    s32 i;

    f->unk1DC = 4;
    frames = 0;
    i = 5;
    while (i <= 120) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y > 2.5f) {
            i++;
            continue;
        }
        frames = fielderFramesToReach(f, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x,
                                      g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z);
        if (frames < i) {
            f->unk184 = i;
            goto found;
        }
        i += 5;
    }
    f->unk184 = 120;
found:
    setFielderTarget(f, g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x,
                     g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z);
    if (f->unk184 >= 120) {
        f->unk17E = 120;
    } else {
        f->unk17E = frames;
    }
}

// .text:0x000433E0 size:0x13E4 mapped:0x80682474
static inline void aimAtBallFuture(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    setFielderTargetIdx(idx, g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x,
                        g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z);
    if (f->unk184 <= 1) {
        f->unk1DC = 5;
    }
}

static inline void aimAtBall(s32 idx) {
    setFielderTargetIdx(idx, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);
}

void fn_3_433E0(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 x;
    f32 z;
    f32 dist;
    f32 step;
    f32 v;

    if (g_Ball.ballBounceState == 3) {
        fn_3_43038(fielderIdx);
    }
    v = g_Ball.ballVelocity;
    if (v < 0.05f && g_Ball.ballState != 0 && g_Ball.ballState != 1) {
        if (g_Ball.AtBat_ContactResult != 0) {
            f->unk1DC = 5;
        }
    } else if (v < 0.1f && g_Ball.ballZoneAwayFromHome >= 3 && g_Ball.AtBat_ContactResult >= 1 &&
               g_Ball.AtBat_ContactResult <= 3 && f->unk1DC != 4 && f->unk1DC != 5) {
        fn_3_43038(fielderIdx);
    } else if (g_FieldingLogic._107 == 3 && g_Ball.framesSinceHit <= 180 && fielderIdx == 1 && f->unk1DC != 4) {
        fn_3_43038(fielderIdx);
    }
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        x = g_Ball.AtBat_Contact_BallPos.x - f->pos[0];
        z = g_Ball.AtBat_Contact_BallPos.z - f->pos[2];
        dist = dolsqrtf2(x * x + z * z);
        if (dist < lbl_3_data_4930[36]) {
            setFielderTarget(f, f->pos[0], f->pos[2]);
        } else {
            step = lbl_3_data_4930[36] - 1.0f;
            x = step * (x / dist) + f->pos[0];
            z = step * (z / dist) + f->pos[2];
            setFielderTargetIdx(fielderIdx, x, z);
        }
    } else if (g_FieldingLogic.unk123 != 0) {
        if (f->unk184 <= 1) {
            goto end;
        }
        dist = dolsqrtf2(g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x *
                             g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x +
                         g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z *
                             g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z);
        x = 0.5f * (g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x / dist) +
            g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x;
        z = 0.5f * (g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z / dist) +
            g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z;
        if (x < 0.0f) {
            x += 10.0f;
        } else {
            x -= 10.0f;
        }
        z += 8.0f;
        setFielderTargetIdx(fielderIdx, x, z);
    } else if (f->unk1DC == 0) {
        if (f->unk184 > 1) {
            if (f->unk18A != 0) {
                fn_3_50DD8(fielderIdx, &x, &z, 1);
                f->unk20 = x;
                f->unk24 = z;
            } else {
                dist = dolsqrtf2(g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x *
                                     g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x +
                                 g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z *
                                     g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z);
                x = 0.5f * (g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x / dist) +
                    g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.x;
                z = 0.5f * (g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z / dist) +
                    g_Ball.physicsSubstruct.futureCoordsAndDist[f->unk184].pos.z;
                if (g_Ball.warioWaluGarlicIsActive != 0) {
                    if (g_AiLogic._79[0] != 0) {
                        x = g_Ball.peachDaisyStarHitFielderLoc.x;
                        z = g_Ball.peachDaisyStarHitFielderLoc.z;
                    } else {
                        x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                        z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
                    }
                } else if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
                    x = g_Ball.peachDaisyStarHitFielderLoc.x;
                    z = g_Ball.peachDaisyStarHitFielderLoc.z;
                }
            }
            setFielderTargetIdx(fielderIdx, x, z);
        } else {
            f->unk1DC = 5;
        }
        if (fielderIdx >= 6 && g_Ball.ballState == 0 && f->unk184 < -5) {
            fn_3_43038(fielderIdx);
        }
    } else if (f->unk1DC == 1) {
        f->unk28 = g_Ball.ballWillHitBallPos.x;
        f->unk2C = g_Ball.ballWillHitBallPos.z;
        if (f->unk18A != 0) {
            fn_3_50DD8(fielderIdx, &x, &z, 1);
            setFielderTargetIdx(fielderIdx, x, z);
            f->unk20 = x;
            f->unk24 = z;
        } else {
            setFielderTargetIdx(fielderIdx, f->unk28, f->unk2C);
        }
    } else if (f->unk1DC == 2) {
        fn_3_42CDC(fielderIdx);
    } else if (f->unk1DC == 3) {
        fn_3_42BD0(fielderIdx);
    } else if (f->unk1DC == 4) {
        aimAtBallFuture(fielderIdx);
    } else if (f->unk1DC == 5) {
        aimAtBall(fielderIdx);
    }
end:
    f->unk184--;
    fn_3_526DC(fielderIdx);
    if (f->unk50 != 0.0f) {
        f->unk17E = f->unk68 / f->unk50;
    }
    if ((f->unk1DC == 1 || f->unk1DC == 2 || f->unk1DC == 3) && g_Ball.AtBat_ContactResult == 0) {
        if (g_Ball.framesUntilBallHitsGround >
            fielderFramesToReach(f, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                 g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z)) {
            f->unk1DC = 0;
            f->unk184 = g_Ball.framesUntilBallHitsGround - 2;
        }
    }
}

// .text:0x000447C4 size:0xBD0 mapped:0x80683858
void fn_3_447C4(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    s32 frame;
    s32 minigame;
    f32 x;
    f32 z;
    f32 r;
    f32 w;
    f32 d;
    f32 k;
    f32 tx;
    f32 tz;

    frame = f->unk186 - g_Ball.framesSinceHit + 1;
    minigame = 0;
    if (frame < 0) {
        frame *= -1;
    }
    if (frame >= 360) {
        frame = 359;
    }
    x = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x;
    z = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z;
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        if (g_AiLogic._79[0] != 0) {
            x = g_Ball.peachDaisyStarHitFielderLoc.x;
            z = g_Ball.peachDaisyStarHitFielderLoc.z;
        } else {
            x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    } else if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
        x = g_Ball.peachDaisyStarHitFielderLoc.x;
        z = g_Ball.peachDaisyStarHitFielderLoc.z;
    }
    if (g_d_GameSettings.minigamesEnabled && idx >= 2) {
        minigame = 1;
    }
    if (idx >= 6 || minigame != 0) {
        r = dolsqrtf2(x * x + z * z);
        if (g_Ball._1BC0 != 0 && g_Ball.someCollisionInd == 0) {
            w = dolsqrtf2(g_Ball.ballWillHitBallPos.x * g_Ball.ballWillHitBallPos.x +
                          g_Ball.ballWillHitBallPos.z * g_Ball.ballWillHitBallPos.z);
            if (g_Ball.someCollisionVariable >= 2) {
                tx = f->pos[0] - g_Ball.ballWillHitBallPos.x;
                tz = f->pos[2] - g_Ball.ballWillHitBallPos.z;
                d = dolsqrtf2(tx * tx + tz * tz);
                k = 5.0f / d;
                tx = tx * k + g_Ball.ballWillHitBallPos.x;
                tz = tz * k + g_Ball.ballWillHitBallPos.z;
                f->unk28 = tx;
                f->unk2C = tz;
                fn_3_50C20(idx, &tx, &tz);
                f->unk1DC = 2;
                goto end;
            }
            if (r > w) {
                if (f->unk1DD != 1 || (f->unk1C5 != 0 && f->unk1C4 >= 3)) {
                    tx = 5.0f * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
                    tz = 5.0f * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
                    f->unk28 = tx;
                    f->unk2C = tz;
                    fn_3_50C20(idx, &tx, &tz);
                    f->unk1DC = 2;
                } else {
                    tx = g_Ball.ballWillHitBallPos.x;
                    tz = g_Ball.ballWillHitBallPos.z;
                    f->unk28 = tx;
                    f->unk2C = tz;
                    fn_3_50C20(idx, &tx, &tz);
                    f->unk1DC = 1;
                }
                setFielderTarget(f, tx, tz);
                goto end;
            }
        }
        if (f->unk1DD == 3 || f->unk1DD == 4) {
            if (fn_3_B7E44(r, g_Ball.ballAngleFromHome) != 0) {
                tx = 5.0f * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
                tz = 5.0f * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;
                f->unk28 = tx;
                f->unk2C = tz;
                fn_3_50C20(idx, &tx, &tz);
                f->unk1DC = 2;
            } else {
                tx = g_Ball.physicsSubstruct.futureCoordsAndDist[frame + 30].pos.x;
                tz = g_Ball.physicsSubstruct.futureCoordsAndDist[frame + 30].pos.z;
                f->unk28 = tx;
                f->unk2C = tz;
                fn_3_50C20(idx, &tx, &tz);
                f->unk1DC = 3;
            }
            setFielderTargetIdx(idx, tx, tz);
            goto end;
        }
    }
    d = dolsqrtf2(x * x + z * z);
    if (d <= 0.1f) {
        tx = x;
        tz = z;
    } else {
        tx = 0.5f * (x / d) + x;
        tz = 0.5f * (z / d) + z;
    }
    if (g_Ball.warioWaluGarlicIsActive == 0 && g_Ball.currentStarSwing != 9 && g_Ball.currentStarSwing != 10 &&
        g_Ball.someCollisionInd == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
        fn_3_50DD8(idx, &tx, &tz, 0);
    }
    setFielderTargetIdx(idx, tx, tz);
    f->unk1DC = 0;
end:
    f->unk20 = f->prevPos[0];
    f->unk24 = f->prevPos[2];
    fn_3_526DC(idx);
    f->unk184 = frame;
}

// .text:0x00045394 size:0x220 mapped:0x80684428
void fn_3_45394(s32 idx) {
    return;
}

// .text:0x000455B4 size:0x2AC mapped:0x80684648
void fn_3_455B4(void) {
    return;
}

// .text:0x00045860 size:0x11C mapped:0x806848F4
void fn_3_45860(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    if (g_Ball.framesSinceHit < f->unk1D2) {
        return;
    }
    if (fn_3_53130(idx) != 0) {
        return;
    }
    fn_3_447C4(idx);
    fn_3_45394(idx);
    if (f->unk1C5 != 0) {
        if (idx != -1) {
            f->unk1D3 = 2;
            if (lbl_3_data_3C40.actions[2].unk0 >= 0) {
                g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.actions[2].unk0;
            }
            f->unk1D5 = 0;
            f->unk1D6 = 0;
            f->unk1A4 = 0;
            f->unk1AC = 0;
            f->unk1FF = 0;
        }
    } else if (idx != -1) {
        f->unk1D3 = 0x10;
        if (lbl_3_data_3C40.actions[0x10].unk0 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.actions[0x10].unk0;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
}

// .text:0x0004597C size:0x20C mapped:0x80684A10
void fn_3_4597C(s32 fielderIdx) {
    VecXZ out;
    VecXZ path[2];
    VecXZ perp[2];
    Fielder* f = &g_Fielders[fielderIdx];
    f32 nx;
    f32 nz;

    path[0].x = g_Ball.AtBat_Contact_BallPos.x;
    path[0].z = g_Ball.AtBat_Contact_BallPos.z;
    path[1].x = g_Ball.throwTarget.x;
    path[1].z = g_Ball.throwTarget.z;
    nx = -(path[1].z - path[0].z);
    nz = path[1].x - path[0].x;
    perp[0].x = f->pos[0];
    perp[0].z = f->pos[2];
    perp[1].x = f->pos[0] + nx;
    perp[1].z = f->pos[2] + nz;
    calculateLineIntersection(&out, path, perp);
    {
        f32 x = out.x;
        f32 z = out.z;
        setFielderTargetIdx(fielderIdx, x, z);
    }
}

// .text:0x00045B88 size:0x310 mapped:0x80684C1C
void fn_3_45B88(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    VecXZ out;
    VecXZ perp[2];
    VecXZ path[2];
    f32 nx;
    f32 nz;

    g_FieldingLogic.unk13C = 0;
    if (f->unk1FF == 0) {
        f->unk1FF = 1;
        f->unk202 = 1;
        g_FieldingLogic.unkB0 = fielderIdx;
        path[0].x = g_Ball.AtBat_Contact_BallPos.x;
        path[0].z = g_Ball.AtBat_Contact_BallPos.z;
        path[1].x = g_Ball.throwTarget.x;
        path[1].z = g_Ball.throwTarget.z;
        nx = -(path[1].z - path[0].z);
        nz = path[1].x - path[0].x;
        perp[0].x = f->pos[0];
        perp[0].z = f->pos[2];
        perp[1].x = f->pos[0] + nx;
        perp[1].z = f->pos[2] + nz;
        calculateLineIntersection(&out, path, perp);
        setFielderTarget(f, out.x, out.z);
    }
    switch (fn_3_53130(fielderIdx)) {
    case 2:
        return;
    default:
        if (f->unk202 != 0) {
            fn_3_526DC(fielderIdx);
            if (g_FieldingLogic.unk14A & 0x100) {
                g_FieldingLogic.unk13C = 1;
            }
        }
    case 1:
        if (g_Ball.ballState != 2) {
            g_FieldingLogic.unkC2 = -1;
            f->unk202 = 0;
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 9);
            }
        }
        break;
    }
}

// .text:0x00045E98 size:0x7F0 mapped:0x80684F2C
void fn_3_45E98(void) {
    return;
}

// .text:0x00046688 size:0x254 mapped:0x8068571C
void fn_3_46688(void) {
    return;
}

// .text:0x000468DC size:0x1E0 mapped:0x80685970
void fn_3_468DC(void) {
    return;
}

// .text:0x00046ABC size:0x34C mapped:0x80685B50
void fn_3_46ABC(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 t;
    f32 x;
    f32 z;

    if (g_Ball.framesSinceThrowStarted == 5 && g_Ball.ballVelocity != 0.0f) {
        t = f->unk74 / g_Ball.ballVelocity;
        x = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
        z = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        if (dolsqrtf2((f->pos[0] - x) * (f->pos[0] - x) + (f->pos[2] - z) * (f->pos[2] - z)) > f->unkE8) {
            f->unk1E9 = 1;
            setFielderTarget(f, x, z);
        }
    }
    fn_3_526DC(fielderIdx);
    if (f->unk1E9 != 0 && f->unk50 == 0.0f) {
        f->unk1E9 = 0;
    }
    if (g_Ball.fielderBeingThrownTo == fielderIdx) {
        fn_3_4E638();
    }
}

// .text:0x00046E08 size:0x820 mapped:0x80685E9C
s32 fn_3_46E08(s32 fielderIdx, f32* x, f32* z) {
    return 0;
}

// .text:0x00047628 size:0x150 mapped:0x806866BC
void fn_3_47628(void) {
    return;
}

// .text:0x00047778 size:0x940 mapped:0x8068680C
void fn_3_47778(void) {
    u8 hit = g_Ball.hitClassification2;
    Fielder* f;

    if (hit != 5 && hit != 6 && hit != 8) {
        return;
    }
    if (g_FieldingLogic.unk_F8[3] == 1 || g_FieldingLogic.unk_F8[3] == 10 || g_FieldingLogic.unk_F8[3] == 11) {
        if (g_Fielders[5].unk18C != -1) {
            g_Fielders[3].unk18C = 6;
            g_Fielders[3].unk1D7 = 2;
        } else {
            g_Fielders[5].unk18C = 6;
            g_Fielders[5].unk1D7 = 2;
            if (g_FieldingLogic.unk_F8[5] == 0) {
                setFielderReadyAction(5, 0xB);
            }
        }
    } else if (g_FieldingLogic.unk_F8[5] == 1 || g_FieldingLogic.unk_F8[5] == 10 ||
               g_FieldingLogic.unk_F8[5] == 11) {
        if (g_Fielders[3].unk18C != -1) {
            g_Fielders[5].unk18C = 6;
            g_Fielders[5].unk1D7 = 2;
        } else {
            g_Fielders[3].unk18C = 6;
            g_Fielders[3].unk1D7 = 2;
            if (g_FieldingLogic.unk_F8[3] == 0) {
                setFielderReadyAction(3, 0xB);
            }
        }
    } else if (g_Ball.Hit_HorizontalAngle < 0x400) {
        if (g_Fielders[3].unk18C == 1 && (g_FieldingLogic.unk_F8[2] == 1 || g_FieldingLogic.unk_F8[2] == 10 ||
                                          g_FieldingLogic.unk_F8[2] == 11)) {
            g_Fielders[2].unk18C = 6;
            g_Fielders[2].unk1D7 = 2;
        } else {
            g_Fielders[3].unk18C = 6;
            g_Fielders[3].unk1D7 = 2;
            if (g_FieldingLogic.unk_F8[3] == 0) {
                setFielderReadyAction(3, 0xB);
            }
        }
    } else {
        if (g_Fielders[5].unk18C == 3 && (g_FieldingLogic.unk_F8[4] == 1 || g_FieldingLogic.unk_F8[4] == 10 ||
                                          g_FieldingLogic.unk_F8[4] == 11)) {
            g_Fielders[4].unk18C = 6;
            g_Fielders[4].unk1D7 = 2;
        } else {
            g_Fielders[5].unk18C = 6;
            g_Fielders[5].unk1D7 = 2;
            if (g_FieldingLogic.unk_F8[5] == 0) {
                setFielderReadyAction(5, 0xB);
            }
        }
    }
    if (g_FieldingLogic.unk_F8[0] == 0) {
        f = &g_Fielders[0];
        f->unk18C = 0xF;
        if (g_Ball.Hit_HorizontalAngle < 0x320) {
            setFielderTarget(f, 6.0f, 16.0f);
        } else if (g_Ball.Hit_HorizontalAngle < 0x400) {
            setFielderTargetIdx(0, 3.0f, 21.0f);
        } else if (g_Ball.Hit_HorizontalAngle < 0x4E0) {
            setFielderTargetIdx(0, -3.0f, 21.0f);
        } else {
            setFielderTargetIdx(0, -6.0f, 16.0f);
        }
        setFielderReadyAction(0, 0xE);
    }
}

// .text:0x000480B8 size:0x314 mapped:0x8068714C
static inline s32 getRunnerChaseBase(s32 i) {
    f32 frac = g_Runners[i].fractionalBasesRan;

    if (frac >= 3.0f) {
        return 0;
    }
    if (g_Runners[i].tagUpInd == 2 && g_Runners[i].percentTowardsNextBase >= 0.7f) {
        return g_Runners[i].startingBase_baseAchieved;
    }
    if (frac >= 2.0f) {
        if (frac >= 2.7f && g_Runners[i].runningDirectionCode == 1) {
            return 0;
        }
        return 3;
    }
    if (frac >= 1.7f && g_Runners[i].runningDirectionCode == 1) {
        return 3;
    }
    return 2;
}

static inline s32 getLeadRunnerChaseBase(void) {
    s32 i;

    for (i = 3; i >= 0; i--) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            if (!(g_Runners[i].fractionalBasesRan >= 3.7f) || g_Runners[i].runningDirectionCode != 1 ||
                g_Runners[i].tagUpInd == 2) {
                return getRunnerChaseBase(i);
            }
        }
    }
    return 4;
}

void fn_3_480B8(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 base;
    f32 x;
    f32 z;

    base = getLeadRunnerChaseBase();
    if (base != -1) {
        f->unk18E = base;
        if (fn_3_46E08(fielderIdx, &x, &z) != 0) {
            setFielderTarget(f, x, z);
        }
    }
}

// .text:0x000483CC size:0xB4 mapped:0x80687460
void fn_3_483CC(s32 idx) {
    Fielder* f = &g_Fielders[idx];

    f->unk18C = fn_3_3D7D4(idx);
    f->unk1D7 = 2;
    if (idx != -1) {
        f->unk1D3 = 0xE;
        if (lbl_3_data_3C40.unk70 >= 0) {
            g_FieldingLogic.unk_F8[idx] = lbl_3_data_3C40.unk70;
        }
        f->unk1D5 = 0;
        f->unk1D6 = 0;
        f->unk1A4 = 0;
        f->unk1AC = 0;
        f->unk1FF = 0;
    }
    f->unk1D6 = 0;
    g_FieldingLogic.unkBE = -1;
}

// .text:0x00048480 size:0x5D4 mapped:0x80687514
void fn_3_48480(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 base;
    f32 z;
    f32 x;
    u8 state;

    switch (fn_3_53130(fielderIdx)) {
    case 2:
        return;
    default:
        if (g_FieldingLogic.unkC4 == 6) {
            fn_3_46ABC(fielderIdx);
            fn_3_A7C88();
        } else if (g_Strikes.outs < 3) {
            base = getLeadRunnerChaseBase();
            if (base != -1) {
                f->unk18E = base;
                if (fn_3_46E08(fielderIdx, &x, &z) != 0) {
                    setFielderTarget(f, x, z);
                }
            }
            fn_3_526DC(fielderIdx);
        }
        if (f->unk50 != 0.0f) {
            f->unk17E = f->unk68 / f->unk50;
        }
    case 1:
        state = g_Ball.ballState;
        if (state != 0 && g_FieldingLogic.unkC4 != 6 && g_Ball.ballZoneAwayFromHome <= 1) {
            f->unk18C = -1;
            f->unk1D7 = 0;
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
            g_FieldingLogic.unkBE = -1;
        } else if (state == 1 && g_Fielders[g_Ball.fielderWBallIndex].unkA8[f->unk18E] < 15.0f &&
                   g_FieldingLogic.unkC4 != 6) {
            f->unk18C = fn_3_3D7D4(fielderIdx);
            f->unk1D7 = 2;
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xE);
            }
            f->unk1D6 = 0;
            g_FieldingLogic.unkBE = -1;
            g_FieldingLogic.unkC0 = 0x5A;
        } else if (state == 2 && g_FieldingLogic.unkC4 != 6) {
            f->unk18C = fn_3_3D7D4(fielderIdx);
            f->unk1D7 = 2;
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xE);
            }
            f->unk1D6 = 0;
            g_FieldingLogic.unkBE = -1;
        }
        if (g_Ball.fielderBeingThrownTo == fielderIdx) {
            fn_3_4E638();
        }
    }
}

// .text:0x00048A54 size:0xAA0 mapped:0x80687AE8
static inline void claimRunnerChase(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    s16 base;

    g_FieldingLogic.unkBE = idx;
    if (idx != -1) {
        setFielderReadyAction(idx, 5);
    }
    fn_3_48480(idx);
    if (g_FieldingLogic.unkD8 != idx && f->unk18C < 0) {
        return;
    }
    base = f->unk18C;
    if (base < 0) {
        return;
    }
    if (base <= 3) {
        if (g_FieldingLogic.unkD0[base] == idx) {
            g_FieldingLogic.unkD0[base] = -1;
            g_FieldingLogic.unk101[base] = 0;
        }
        f->unk18C = -1;
        f->unk1D7 = 0;
        if (f->unk1D3 == 1 && idx != -1) {
            setFielderReadyAction(idx, 0xC);
        }
    } else if (base == 5) {
        f->unk18C = -1;
        f->unk1D7 = 0;
        g_FieldingLogic.unkD8 = -1;
        g_FieldingLogic.unk105 = 0;
        if (f->unk1D3 == 0xE && idx != -1) {
            setFielderReadyAction(idx, 0xC);
        }
    }
}

void fn_3_48A54(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 x;
    f32 z;
    s16 other;
    f32 dist;

    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (f->unk252 != 0) {
        return;
    }
    f->unk18E = getLeadRunnerChaseBase();
    if (g_FieldingLogic.unkBE < 0) {
        if (fn_3_46E08(fielderIdx, &x, &z) == 0) {
            return;
        }
        setFielderTarget(f, x, z);
        claimRunnerChase(fielderIdx);
    } else if (g_FieldingLogic.unkC4 == 6) {
        if (fielderIdx != -1) {
            setFielderReadyAction(fielderIdx, 0xC);
        }
        g_Fielders[fielderIdx].unk1D5 = 4;
    } else {
        if (fn_3_46E08(fielderIdx, &x, &z) == 0) {
            return;
        }
        dist = dolsqrtf2((x - f->pos[0]) * (x - f->pos[0]) + (z - f->pos[2]) * (z - f->pos[2]));
        other = g_FieldingLogic.unkBE;
        if (dist < g_Fielders[g_FieldingLogic.unkBE].unk68) {
            if (g_Ball.fielderWBallIndex != other) {
                if (other != -1) {
                    setFielderReadyAction(other, 0xC);
                }
                g_Fielders[g_FieldingLogic.unkBE].unk1D5 = 4;
            }
            g_Fielders[g_FieldingLogic.unkBE].unk18C = -1;
            g_Fielders[g_FieldingLogic.unkBE].unk1D7 = 0;
            setFielderTargetIdx(fielderIdx, x, z);
            claimRunnerChase(fielderIdx);
        } else {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
            g_Fielders[fielderIdx].unk1D5 = 4;
        }
    }
}

// .text:0x000494F4 size:0x4D0 mapped:0x80688588
void fn_3_494F4(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 dz;
    f32 dx;
    f32 dist;
    f32 step;

    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        dz = g_Ball.AtBat_Contact_BallPos.z - f->pos[2];
        dx = g_Ball.AtBat_Contact_BallPos.x - f->pos[0];
        dist = dolsqrtf2(dx * dx + dz * dz);
        if (dist < lbl_3_data_4930[37]) {
            goto stop;
        }
        {
            f32 x = (lbl_3_data_4930[36] - 1.0f) * (dx / dist) + f->pos[0];
            f32 z = (lbl_3_data_4930[36] - 1.0f) * (dz / dist) + f->pos[2];
            setFielderTarget(f, x, z);
        }
    }
    if (g_Ball.hitWallInd != 0) {
        if (f->unk74 < lbl_3_data_4930[1]) {
            goto stop;
        }
    } else if (dolsqrtf2((g_Ball.AtBat_Contact_BallPos.x - g_Ball.ballWillHitBallPos.x) *
                             (g_Ball.AtBat_Contact_BallPos.x - g_Ball.ballWillHitBallPos.x) +
                         (g_Ball.AtBat_Contact_BallPos.z - g_Ball.ballWillHitBallPos.z) *
                             (g_Ball.AtBat_Contact_BallPos.z - g_Ball.ballWillHitBallPos.z)) < lbl_3_data_4930[2] &&
               f->unk7C < lbl_3_data_4930[3]) {
        goto stop;
    }
    if (g_Ball.hitClassification1 == 2 && f->unk7C < lbl_3_data_4930[3]) {
        goto stop;
    }
    return;

stop:
    stopFielder(fielderIdx);
}

// .text:0x000499C4 size:0x254 mapped:0x80688A58
void fn_3_499C4(s32 fielderIdx, VecXYZ* out) {
    return;
}

// .text:0x00049C18 size:0x290 mapped:0x80688CAC
void fn_3_49C18(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    VecXYZ target;

    switch (fn_3_53130(fielderIdx)) {
    case 2:
        return;
    default:
        if (f->unk1FF == 0) {
            fn_3_499C4(fielderIdx, &target);
            {
                f32 x = target.x;
                f32 z = target.z;
                setFielderTargetIdx(fielderIdx, x, z);
            }
            f->unk1FF = 1;
        }
        if (f->unk1FF == 1) {
            fn_3_526DC(fielderIdx);
            fn_3_494F4(fielderIdx);
        }
    case 1:
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
            if (fielderIdx <= 5) {
                f->unk1D6 = 7;
            } else {
                f->unk1D6 = 6;
            }
        }
        break;
    }
}

// .text:0x00049EA8 size:0x94 mapped:0x80688F3C
void fn_3_49EA8(s32 idx) {
    startFielderChase(idx);
}

// .text:0x00049F3C size:0x4 mapped:0x80688FD0
void fn_3_49F3C(void) {
    return;
}

// .text:0x00049F40 size:0x1E4 mapped:0x80688FD4
void fn_3_49F40(s32 arg0, s32 arg1) {
    return;
}

// .text:0x0004A124 size:0x2E4 mapped:0x806891B8
void fn_3_4A124(void) {
    return;
}

// .text:0x0004A408 size:0x5A4 mapped:0x8068949C
void fn_3_4A408(s32 fielderIdx, f32* x, f32* z) {
    return;
}

// .text:0x0004A9AC size:0x77C mapped:0x80689A40
void fn_3_4A9AC(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s32 target = g_Ball.fielderAboutToGetBall_hasBall;
    f32 x;
    f32 z;
    s32 i;
    s32 r;

    switch (fn_3_53130(fielderIdx)) {
    case 2:
        return;
    default:
        if (f->unk1C5 == 0) {
            fn_3_4A408(fielderIdx, &x, &z);
        } else if (target == -1) {
            x = f->pos[0];
            z = f->pos[2];
        } else if (f->unk74 < 5.0f) {
            x = f->pos[0];
            z = f->pos[2];
        } else if (g_Ball.ballState == 3) {
            x = 10.0f * g_Ball.ballVelocityPercent.x + g_Ball.AtBat_Contact_BallPos.x;
            z = 10.0f * g_Ball.ballVelocityPercent.z + g_Ball.AtBat_Contact_BallPos.z;
        } else if (f->unk50 == 0.0f && f->unk84[target] < 15.0f) {
            x = f->pos[0];
            z = f->pos[2];
        } else {
            x = 10.0f * g_Ball.ballVelocityPercent.x + g_Fielders[target].prevPos[0];
            z = 10.0f * g_Ball.ballVelocityPercent.z + g_Fielders[target].prevPos[2];
        }
        setFielderTarget(f, x, z);
        if (fielderIdx >= 6) {
            if (target >= 6 && f->unk68 < 20.0f) {
                f->unk1D6 = 5;
            }
            if (f->unk68 < 15.0f) {
                f->unk1D6 = 7;
            } else if (f->unk68 < 20.0f) {
                f->unk1D6 = 6;
            }
            r = fn_3_B7E44(f->unk70, f->unk180);
            if (r == 2) {
                f->unk1D6 = 8;
            }
            if (r == 1) {
                f->unk1D6 = 5;
            }
        } else if (target <= 5 && f->unk68 < 10.0f) {
            f->unk1D6 = 7;
        }
        for (i = 0; i < 9; i++) {
            if (i != fielderIdx && f->unk84[i] < 3.0f) {
                f->unk1D6 = 9;
                break;
            }
        }
        fn_3_526DC(fielderIdx);
    case 1:
        if (g_Ball.ballState != 0 && g_Ball.ballState != 3) {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
            if (fielderIdx <= 5) {
                f->unk1D6 = 7;
            } else {
                f->unk1D6 = 6;
            }
        }
        if (g_Ball.AtBat_ContactResult != 0 && f->unk84[target] > 5.0f + f->unk74) {
            if (dolsqrtf2((g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.x - f->pos[0]) *
                              (g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.x - f->pos[0]) +
                          (g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.z - f->pos[2]) *
                              (g_Ball.physicsSubstruct.futureCoordsAndDist[5].pos.z - f->pos[2])) < f->unk74 &&
                f->unk1C5 != 0) {
                fn_3_43038(fielderIdx);
                if (fielderIdx != -1) {
                    setFielderReadyAction(fielderIdx, 0x12);
                }
                g_Ball.fielderAboutToGetBall_hasBall = -1;
            }
        }
    }
}

// .text:0x0004B128 size:0x3EC mapped:0x8068A1BC
void fn_3_4B128(s32 fielderIdx) {
    s16 base;
    s32 ang;
    f32 dx;
    f32 dz;
    f32 x;
    f32 z;

    switch (fn_3_53130(fielderIdx)) {
    case 2:
        return;
    default:
        base = g_FieldingLogic.unkC4;
        if (base >= 1 && base <= 3 && g_FieldingLogic.unkE6 == 1 && (base == 2 || fielderIdx != 7)) {
            ang = fn_3_9FB8C(g_Ball.throwDestination.x - g_Ball.AtBat_Contact_BallPos.x,
                             g_Ball.throwDestination.z - g_Ball.AtBat_Contact_BallPos.z);
            fn_3_9F9C8(ang, &dx, &dz);
            x = 20.0f * dx + lbl_3_data_4444[g_FieldingLogic.unkC4].x;
            z = 20.0f * dz + lbl_3_data_4444[g_FieldingLogic.unkC4].z;
            ang = fn_3_9FB8C(x, z);
            if (ang <= 0x800 &&
                ((ang < 0x300 && fielderIdx == 8) || (ang > 0x500 && fielderIdx == 6) ||
                 (ang < 0x400 && (fielderIdx == 7 || fielderIdx == 8)) ||
                 (ang >= 0x400 && (fielderIdx == 7 || fielderIdx == 6)))) {
                if (z < lbl_3_data_4444[1].z) {
                    if (x < 0.0f) {
                        x = -35.0f;
                    } else {
                        x = 35.0f;
                    }
                    z = 30.0f;
                }
                setFielderTargetIdx(fielderIdx, x, z);
            }
        }
        fn_3_526DC(fielderIdx);
        if (g_Fielders[fielderIdx].unk68 < 5.0f) {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
        } else if (g_Ball.numberOfThrowsDuringPlay >= 2) {
            if (fielderIdx != -1) {
                setFielderReadyAction(fielderIdx, 0xC);
            }
        }
        break;
    case 1:
        break;
    }
}

// .text:0x0004B514 size:0x3BC mapped:0x8068A5A8
void fn_3_4B514(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 off = 0.0f;

    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (f->unk1D4 >= 2) {
        setFielderTarget(f, lbl_3_data_44B4[f->unk1D4].x, lbl_3_data_44B4[f->unk1D4].z);
    } else {
        if (fielderIdx == 6) {
            off = 10.0f;
        }
        if (fielderIdx == 8) {
            off = -10.0f;
        }
        setFielderTargetIdx(fielderIdx, f->pos[0] + off, f->pos[2] - 20.0f);
    }
    if (fielderIdx != -1) {
        setFielderReadyAction(fielderIdx, 6);
    }
}

// .text:0x0004B8D0 size:0x13C mapped:0x8068A964
void fn_3_4B8D0(void) {
    return;
}

// .text:0x0004BA0C size:0xFBC mapped:0x8068AAA0
void fn_3_4BA0C(void) {
    return;
}

// .text:0x0004C9C8 size:0x5E8 mapped:0x8068BA5C
void fn_3_4C9C8(void) {
    return;
}

// .text:0x0004CFB0 size:0x25C mapped:0x8068C044
void fn_3_4CFB0(void) {
    aimPitcherAtBase();
}

// .text:0x0004D20C size:0x978 mapped:0x8068C2A0

void fn_3_4D20C(s32 fielderIdx) {
    Fielder* f = &g_Fielders[fielderIdx];
    s16 frames;
    s16 base;
    u8 state;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 step;

    if (g_Ball.homeRunClassification != 0 && fielderIdx <= 1) {
        return;
    }
    frames = g_Ball.framesSinceHit;
    if (frames < 15) {
        return;
    }
    if (fielderIdx == 1 && g_FieldingLogic.unk118 != 0) {
        return;
    }
    if (frames < f->unk1D2 - 15 && fielderIdx != 0) {
        return;
    }
    if (frames < f->unk1D2 && fielderIdx == 0) {
        return;
    }
    if (fn_3_53130(fielderIdx) != 0) {
        return;
    }
    if (g_FieldingLogic.unkC4 == f->unk18C) {
        fn_3_A7C88();
    }
    if (f->unk1D7 == 1) {
        if (f->unk216 != 0) {
            dz = f->prevPos[2] - f->pos[2];
            dx = f->prevPos[0] - f->pos[0];
            dist = dolsqrtf2(dx * dx + dz * dz);
            if (dist < f->unk58) {
                step = dist;
            } else {
                step = f->unk58;
            }
            f->unk30 = dx * step;
            f->unk34 = dz * step;
            f->unk50 = step;
            f->pos[0] += f->unk30;
            f->pos[2] += f->unk34;
            f->unk68 = dist - step;
        } else if (f->unk252 != 0) {
            fn_3_261E8(fielderIdx);
            f->unk1A2 = 0;
        } else {
            base = f->unk18C;
            state = g_FieldingLogic.unk101[base];
            if (state == 0) {
                if (f->unk1D8 == 1) {
                    aimPitcherAtBase();
                } else {
                    setFielderTarget(f, lbl_3_data_4444[base].x, lbl_3_data_4444[base].z);
                }
                fn_3_526DC(fielderIdx);
            } else if (state == 1) {
                if (f->unkA8[base] > lbl_3_data_4780[f->unk1C9]) {
                    dx = lbl_3_data_4444[base].x - f->pos[0];
                    dz = lbl_3_data_4444[base].z - f->pos[2];
                    f->prevPos[0] = lbl_3_data_4444[base].x;
                    f->prevPos[2] = lbl_3_data_4444[f->unk18C].z;
                    f->unk30 = 0.03f * dx / f->unkA8[f->unk18C];
                    f->unk34 = 0.03f * dz / f->unkA8[f->unk18C];
                    f->unk50 = 0.03f;
                    f->unk68 = f->unkA8[f->unk18C];
                    f->pos[0] += f->unk30;
                    f->pos[2] += f->unk34;
                } else {
                    f32 ex;
                    f32 ez;

                    ex = lbl_3_data_4444[base].x - f->pos[0];
                    ez = lbl_3_data_4444[base].z - f->pos[2];
                    dist = dolsqrtf2(ex * ex + ez * ez);
                    if (dist < 0.1f) {
                        f->pos[0] = lbl_3_data_4444[f->unk18C].x;
                        f->pos[2] = lbl_3_data_4444[f->unk18C].z;
                        stopFielder(fielderIdx);
                    } else {
                        f->unk30 = ex / 5.0f;
                        f->unk34 = ez / 5.0f;
                        f->pos[0] += f->unk30;
                        f->pos[2] += f->unk34;
                    }
                }
                f->unk30 = 0.0f;
                f->unk34 = 0.0f;
                f->unk50 = 0.0f;
            }
        }
    }
    if (f->unk1D7 == 1 && f->unk50 != 0.0f) {
        f->unk17E = f->unk68 / f->unk58;
    }
    fn_3_5372C(fielderIdx);
    if (g_Ball.fielderBeingThrownTo == fielderIdx) {
        fn_3_4E638();
    }
}

// .text:0x0004DB84 size:0x90 mapped:0x8068CC18
BOOL fn_3_4DB84(s32 i) {
    Fielder* f = &g_Fielders[i];

    if (g_Ball.ballVelocityPercent.x == 0.0f && g_Ball.ballVelocityPercent.z == 0.0f) {
        return FALSE;
    }
    if (-(g_Ball.ballVelocityPercent.x * g_Ball.AtBat_Contact_BallPos.x) - g_Ball.ballVelocityPercent.z * g_Ball.AtBat_Contact_BallPos.z +
            (g_Ball.ballVelocityPercent.x * f->pos[0] + g_Ball.ballVelocityPercent.z * f->pos[2]) > 0.0f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0004DC14 size:0x5A8 mapped:0x8068CCA8
void fn_3_4DC14(void) {
    return;
}

// .text:0x0004E1BC size:0x47C mapped:0x8068D250
void fn_3_4E1BC(void) {
    return;
}

// .text:0x0004E638 size:0x58C mapped:0x8068D6CC
void fn_3_4E638(void) {
    return;
}

// .text:0x0004EBC4 size:0x404 mapped:0x8068DC58
void fn_3_4EBC4(void) {
    return;
}

// .text:0x0004EFC8 size:0x53C mapped:0x8068E05C
void fn_3_4EFC8(void) {
    return;
}

// .text:0x0004F504 size:0x630 mapped:0x8068E598
void fn_3_4F504(void) {
    return;
}

// .text:0x0004FB34 size:0xD64 mapped:0x8068EBC8
void fn_3_4FB34(void) {
    return;
}

// .text:0x00050898 size:0x388 mapped:0x8068F92C
void fn_3_50898(void) {
    return;
}

// .text:0x00050C20 size:0x1B8 mapped:0x8068FCB4
void fn_3_50C20(s32 fielderIdx, f32* x, f32* z) {
    return;
}

// .text:0x00050DD8 size:0x448 mapped:0x8068FE6C
void fn_3_50DD8(s32 fielderIdx, f32* x, f32* z, s32 arg3) {
    return;
}

// .text:0x00051220 size:0x42C mapped:0x806902B4
void fn_3_51220(void) {
    return;
}

// .text:0x0005164C size:0x14C mapped:0x806906E0
s32 fn_3_5164C(s32 idx, VecXYZ* result) {
    Fielder* f = &g_Fielders[idx];
    f32 x = f->pos[0] + f->unk30;
    f32 z = f->pos[2] + f->unk34;
    f32 limit;
    f32 negativeX;
    f32 delta;
    f32 product;
    s32 status = 0;
    if (x > 0.0f) {
        if (x > z) {
            product = 0.5f * (x - z);
            x = z + product;
            z = x;
            status = 2;
        }
    } else {
        delta = -x;
        if (delta > z) {
            product = 0.5f * (delta - z);
            z += product;
            x = -z;
            status = 2;
        }
    }
    limit = lbl_3_data_4444[2].z;
    delta = z - limit;
    if (!(delta > x)) {
        negativeX = -x;
        if (!(delta > negativeX)) {
            if (x > 0.0f) {
                delta = limit - z;
                product = 0.5f * (x - delta);
                x = delta + product;
                z = -x + limit;
                status = 2;
            } else {
                delta = limit - z;
                product = 0.5f * (negativeX - delta);
                x = -delta - product;
                z = x + limit;
                status = 2;
            }
        }
    }
    if (z <= lbl_3_data_4444[2].x) return 1;
    result->x = x;
    result->z = z;
    return status;
}

// .text:0x00051798 size:0x658 mapped:0x8069082C
void fn_3_51798(void) {
    return;
}

// .text:0x00051DF0 size:0x294 mapped:0x80690E84
void fn_3_51DF0(void) {
    return;
}

// .text:0x00052084 size:0x25C mapped:0x80691118
void fn_3_52084(void) {
    return;
}

// .text:0x000522E0 size:0x280 mapped:0x80691374
void fn_3_522E0(void) {
    return;
}

// .text:0x00052560 size:0x17C mapped:0x806915F4
s32 fn_3_52560(s32 fielderIdx, f32 x, f32 z) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 dist;
    f32 speed;
    u32 delay;

    if (x == f->pos[0] && z == f->pos[2]) {
        return 1;
    }
    dist = dolsqrtf2((x - f->pos[0]) * (x - f->pos[0]) + (z - f->pos[2]) * (z - f->pos[2]));
    delay = f->unk1D1 / 2;
    if (f->unk58 == 0.0f) {
        speed = 1.0f;
    } else {
        speed = f->unk58;
    }
    return delay + (s32)(dist / speed);
}

// .text:0x000526DC size:0x870 mapped:0x80691770
void fn_3_526DC(s32 fielderIdx) {
    return;
}

// .text:0x00052F4C size:0x1A0 mapped:0x80691FE0
void fn_3_52F4C(s32 fielderIdx, f32 x, f32 z) {
    Fielder* f = &g_Fielders[fielderIdx];
    f32 dx;
    f32 dz;

    f->prevPos[0] = x;
    f->prevPos[2] = z;
    dx = x - f->pos[0];
    dz = z - f->pos[2];
    if (dx == 0.0f && dz == 0.0f) {
        f->unk50 = 0.0f;
        f->unk68 = 0.0f;
    } else {
        f->unk64 = atan2(dz, dx);
        f->unk68 = dolsqrtf2(dx * dx + dz * dz);
    }
    f->unk1D9 = 1;
}

// .text:0x000530EC size:0x44 mapped:0x80692180

void fn_3_530EC(int index) {
    // Declaring the pointer but not immediately calculating it.
    Fielder* fielder;
    fielder = &g_Fielders[index];

    fielder->prevPos[0] = fielder->pos[0];
    fielder->prevPos[1] = fielder->pos[1];
    fielder->prevPos[2] = fielder->pos[2];

    // These use f0
    fielder->unk30 = lbl_3_rodata_B20;
    fielder->unk34 = lbl_3_rodata_B20;
    fielder->unk50 = lbl_3_rodata_B20;
    fielder->unk68 = lbl_3_rodata_B20;
}

// .text:0x00053130 size:0x5FC mapped:0x806921C4
int fn_3_53130(s32 temp) {
    return;
}

// .text:0x0005372C size:0x7BC mapped:0x806927C0
void fn_3_5372C(s32 fielderIdx) {
    return;
}

// .text:0x00053EE8 size:0x60 mapped:0x80692F7C
void fn_3_53EE8(s32 idx) {
    Fielder* f = &g_Fielders[idx];
    if (idx == -1) return;
    f->unk1D3 = 0x13;
    if (lbl_3_data_3C40.unk98 >= 0) {
        g_FieldingLogic.unk_F8[idx] = (u8)lbl_3_data_3C40.unk98;
    }
    f->unk1D5 = 0;
    f->unk1D6 = 0;
    f->unk1A4 = 0;
    f->unk1AC = 0;
    f->unk1FF = 0;
}

// .text:0x00053F48 size:0x570 mapped:0x80692FDC
void fn_3_53F48(void) {
    return;
}

// .text:0x000544B8 size:0x448 mapped:0x8069354C
void fn_3_544B8(void) {
    return;
}

// .text:0x00054900 size:0x258 mapped:0x80693994
void fn_3_54900(void) {
    return;
}

// .text:0x00054B58 size:0x818 mapped:0x80693BEC
void fn_3_54B58(void) {
    return;
}

// .text:0x00055370 size:0x23C mapped:0x80694404
void fn_3_55370(void) {
    return;
}

// .text:0x000555AC size:0x164 mapped:0x80694640
void fn_3_555AC(void) {
    return;
}

// .text:0x00055710 size:0x208 mapped:0x806947A4
void fn_3_55710(void) {
    return;
}

// .text:0x00055918 size:0x3AC mapped:0x806949AC
void fn_3_55918(void) {
    return;
}

// .text:0x00055CC4 size:0x228 mapped:0x80694D58
void fn_3_55CC4(void) {
    return;
}

// .text:0x00055EEC size:0x1258 mapped:0x80694F80
void fn_3_55EEC(s32 fielderIdx) {
    return;
}

// .text:0x00057144 size:0x344 mapped:0x806961D8
void fn_3_57144(void) {
    return;
}

// .text:0x00057488 size:0x22C mapped:0x8069651C
void fn_3_57488(void) {
    return;
}

// .text:0x000576B4 size:0x360 mapped:0x80696748
void fn_3_576B4(s16 idx) {
    return;
}

// .text:0x00057A14 size:0x1A0 mapped:0x80696AA8
void fn_3_57A14(void) {
    f32 best;
    f32 second;
    s32 bestIdx;
    s32 secondIdx;
    s32 i;

    if (g_Ball.fielderWBallIndex >= 0) {
        g_FieldingLogic.unkB0 = g_Ball.fielderWBallIndex;
        return;
    }
    if (g_Ball.ballState == 2) {
        g_FieldingLogic.unkB0 = g_Ball.fielderBeingThrownTo;
        return;
    }
    second = 999.9f;
    secondIdx = -1;
    best = second;
    bestIdx = -1;
    for (i = 1; i < 9; i++) {
        if (g_Fielders[i].unk1D3 == 2 || g_Fielders[i].unk1D3 == 3) {
            if (g_Fielders[i].unk7C < second) {
                if (g_Fielders[i].unk7C < best) {
                    second = best;
                    secondIdx = bestIdx;
                    best = g_Fielders[i].unk7C;
                    bestIdx = i;
                } else {
                    second = g_Fielders[i].unk7C;
                    secondIdx = i;
                }
            }
        }
    }
    if (bestIdx >= 0) {
        g_FieldingLogic.unkB0 = bestIdx;
    } else if (g_Fielders[0].unk1D3 == 2 || g_Fielders[0].unk1D3 == 3 || g_Fielders[0].unk1D3 == 4) {
        g_FieldingLogic.unkB0 = 0;
    }
    if (secondIdx >= 0) {
        g_FieldingLogic.unkB2 = secondIdx;
    }
    if (g_FieldingLogic.unkB0 >= 0) {
        fn_3_576B4(g_FieldingLogic.unkB0);
    }
}

// .text:0x00057BB4 size:0x804 mapped:0x80696C48
void fn_3_57BB4(void) {
    Fielder* f;
    s32 idx;
    f32 x;
    f32 z;
    f32 dist;
    f32 step;

    idx = g_FieldingLogic.unkB0;
    if (g_d_GameSettings.minigamesEnabled) {
        idx = g_Minigame.minigameRelatedIndex;
    }
    if (idx < 0) {
        return;
    }
    f = &g_Fielders[idx];
    if (g_Ball.framesSinceHit < f->unk1D2) {
        return;
    }
    fn_3_57488();
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        x = g_Ball.AtBat_Contact_BallPos.x - f->pos[0];
        z = g_Ball.AtBat_Contact_BallPos.z - f->pos[2];
        dist = dolsqrtf2(x * x + z * z);
        if (dist < lbl_3_data_4930[37]) {
            setFielderTarget(f, f->pos[0], f->pos[2]);
        } else {
            step = lbl_3_data_4930[36] - 1.0f;
            x = step * (x / dist) + f->pos[0];
            z = step * (z / dist) + f->pos[2];
            setFielderTargetIdx(idx, x, z);
        }
        f->unk20 = f->prevPos[0];
        f->unk24 = f->prevPos[2];
    } else if (f->unk18A != 0) {
        fn_3_50DD8(idx, &x, &z, 1);
        setFielderTargetIdx(idx, x, z);
        f->unk20 = f->prevPos[0];
        f->unk24 = f->prevPos[2];
    }
    x = f->unk20 - f->pos[0];
    z = f->unk24 - f->pos[2];
    dist = dolsqrtf2(x * x + z * z);
    if (!(dist < 0.5f)) {
        if (f->unk1B6 == 0 && lbl_3_data_49DC[25] * f->unk58 < dist) {
            g_FieldingLogic.unk148 |= 0x200;
        }
        lbl_3_bss_170[0] = fn_3_9FB8C(x, z);
    }
    lbl_3_bss_16C = lbl_3_bss_170[0];
}

// .text:0x000583B8 size:0x2D0 mapped:0x8069744C
void fn_3_583B8(void) {
    return;
}

// .text:0x00058688 size:0x1E8 mapped:0x8069771C
void fn_3_58688(void) {
    return;
}

// .text:0x00058870 size:0x5E0 mapped:0x80697904
void fn_3_58870(void) {
    return;
}

extern u8 lbl_3_data_46F8[][9];

// .text:0x00058E50 size:0x108 mapped:0x80697EE4
void fn_3_58E50(void) {
    s32 i;
    s32 fielderIndex;

    g_GameLogic.rosterLoc_skippingCap = 0;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.players.fielderRosterIDs[i] >= 0) {
            fielderIndex = (g_Minigame.players.fielderRosterIDs[i] == (s8)g_Minigame.minigamePlayerSelectedOrder) ? 0 : i + 2;
            setFielderValues(g_Minigame.players.fielderRosterIDs[i], fielderIndex);
            if (fielderIndex == 0) {
                g_Fielders[fielderIndex].unk1D2 = lbl_3_data_46F8[g_Minigame.players.battingHandedness[i]][0];
            } else {
                g_Fielders[fielderIndex].unk1D2 = lbl_3_data_46F8[g_Minigame.players.battingHandedness[i]][7];
            }
        }
    }
}

// .text:0x00058F58 size:0x254 mapped:0x80697FEC
void fn_3_58F58(s32 fielderIdx, f32* x, f32* z) {
    return;
}

// .text:0x000591AC size:0x18C mapped:0x80698240
void fn_3_591AC(void) {
    return;
}

// .text:0x00059338 size:0x28C mapped:0x806983CC
void fn_3_59338(void) {
    return;
}

// .text:0x000595C4 size:0x134 mapped:0x80698658
void fn_3_595C4(void) {
    return;
}

// .text:0x000596F8 size:0x164 mapped:0x8069878C
void fn_3_596F8(void) {
    return;
}
