#include "game/rep_E08.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"

static inline void repE08_resetEntry(HugeAnimEntry68* entry, s32 val, s16 arg) {
    entry->unk38 = val;
    entry->unk42 = arg;
    (entry + 1)->unk0 = 0.0f;
    entry->unk8C = 1;
    entry->unk8D = (val != 0);
    entry->unk8E = (val != 0);
    (entry + 1)->unk4 = 0.0f;
}

// .text:0x00060768 size:0x9C mapped:0x8069F7FC
void fn_3_60768(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        repE08_resetEntry(&g_hugeAnimStruct.ctrlOrBonePtr[i], 0, 0);
    }
}

// .text:0x00060804 size:0x294 mapped:0x8069F898
void fn_3_60804(void) {
    return;
}

// .text:0x00060A98 size:0x2E8 mapped:0x8069FB2C
void fn_3_60A98(void) {
    return;
}

// .text:0x00060D80 size:0x110 mapped:0x8069FE14
void fn_3_60D80(void) {
    return;
}

// .text:0x00060E90 size:0x2B8 mapped:0x8069FF24
void fn_3_60E90(void) {
    return;
}

// .text:0x00061148 size:0xE0 mapped:0x806A01DC
void fn_3_61148(void) {
    return;
}

// .text:0x00061228 size:0x31C mapped:0x806A02BC
void fn_3_61228(void) {
    return;
}

// .text:0x00061544 size:0x620 mapped:0x806A05D8
void fn_3_61544(void) {
    return;
}

// .text:0x00061B64 size:0xDA0 mapped:0x806A0BF8
void fn_3_61B64(void) {
    return;
}

// .text:0x00062904 size:0x24C mapped:0x806A1998
void fn_3_62904(void) {
    return;
}

// .text:0x00062B50 size:0x158 mapped:0x806A1BE4
void fn_3_62B50(void) {
    return;
}

// .text:0x00062CA8 size:0x9C mapped:0x806A1D3C
void fn_3_62CA8(s32 index) {
    AnimationStruct_31EAC* anim = &g_UnkAnimation_31EAC[index];
    Fielder* fielder = &g_Fielders[index];
    AnimationStruct* animStruct = g_hugeAnimStruct.AnimationStructPtrs[index];
    u8 type;

    if (anim->unk4C == 0) {
        type = fielder->unk252;
        anim->unk4C = type;
        anim->unk4A = fielder->unk24C;
        if (fielder->unk252 == 1 || fielder->unk252 == 2) {
            anim->unk4E = fielder->unk253;
        }
        if (anim->unk4C != 0) {
            anim->unk4D = anim->unk4C;
        }
    }
    if (animStruct != NULL && animStruct->animID == 0x24) {
        anim->unk4C = 0;
        anim->unk4F = 0;
    }
}

// .text:0x00062D44 size:0xC0 mapped:0x806A1DD8
void fn_3_62D44(s32 index) {
    Fielder* fielder = &g_Fielders[index];
    AnimationStruct_31EAC* anim = &g_UnkAnimation_31EAC[index];

    anim->unk41 = 0;
    if (fielder->unk1E5 == 2) {
        anim->unk41 = 1;
    } else if (fielder->unk1E5 == 3) {
        anim->unk41 = 2;
    }
    if (fielder->unk256 != 0 && g_Ball.AtBat_ContactResult == 0 && fielder->unk248 < fielder->unkE8 &&
        g_Ball.framesUntilBallHitsGround < 120 && g_Ball.maxYOfHit > 5.0f && g_FieldingLogic.unk144 != 0) {
        anim->unk45 = 1;
    }
}

// .text:0x00062E04 size:0x24 mapped:0x806A1E98
void fn_3_62E04(s32 index) {
    // This specific order matches the load/store pattern in the assembly
    g_UnkAnimation_31EAC[index].unk3A = g_UnkAnimation_31EAC[index].unk38;
    g_UnkAnimation_31EAC[index].unk38 = 0;
}

// .text:0x00062E28 size:0x48 mapped:0x806A1EBC

void fn_3_62E28(void) {
    AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[1].unk1C7, 0);
}

// .text:0x00062E70 size:0x33C mapped:0x806A1F04
void fn_3_62E70(void) {
    return;
}

// .text:0x000631AC size:0x6C8 mapped:0x806A2240
void fn_3_631AC(s32 runnerIdx) {
    return;
}

// .text:0x00063874 size:0x1C4 mapped:0x806A2908
void fn_3_63874(s32 runnerIdx) {
    return;
}

// .text:0x00063A38 size:0xC0 mapped:0x806A2ACC
typedef struct {
    f32 groundVelocity; // 0x00
    u8 _pad04[0x17];
    u8 state;           // 0x1B
    u8 prevState;       // 0x1C
    u8 directionCode;   // 0x1D
    u8 _pad1E[0x2];
} RunnerTrackEntry; // size: 0x20

extern RunnerTrackEntry lbl_3_common_bss_321A0[4];

void fn_3_63A38(void) {
    s32 i;
    InMemRunnerType* runner;
    RunnerTrackEntry* entry;

    for (i = 0; i < 4; i++) {
        runner = &g_Runners[i];
        entry = &lbl_3_common_bss_321A0[i];
        entry->prevState = entry->state;
        if (g_d_GameSettings.minigamesEnabled && g_Minigame._18FC[i] < 0) {
            continue;
        }
        if (runner->runnerOnFieldOrOutOrScored == 0) {
            entry->state = 0;
        } else {
            entry->state = 3;
            entry->groundVelocity = runner->groundVelocity[0];
            entry->directionCode = runner->runningDirectionCode;
            fn_3_63874(i);
            fn_3_631AC(i);
        }
    }
}

// .text:0x00063AF8 size:0x10E4 mapped:0x806A2B8C
void fn_3_63AF8(void) {
    return;
}

// .text:0x00064BDC size:0xC08 mapped:0x806A3C70
void fn_3_64BDC(void) {
    return;
}

// .text:0x000657E4 size:0x7FC mapped:0x806A4878
void fn_3_657E4(void) {
    return;
}

// .text:0x00065FE0 size:0x160 mapped:0x806A5074
void fn_3_65FE0(void) {
    return;
}

// .text:0x00066140 size:0x3BC mapped:0x806A51D4
void fn_3_66140(void) {
    return;
}

// .text:0x000664FC size:0x3C0 mapped:0x806A5590
void fn_3_664FC(void) {
    return;
}

// .text:0x000668BC size:0x874 mapped:0x806A5950
void fn_3_668BC(void) {
    return;
}

// .text:0x00067130 size:0x1C mapped:0x806A61C4
void fn_3_67130(void) {
    lbl_3_common_bss_32220.field_0x08 = 0;
    lbl_3_common_bss_32220.field_0x0B = 0;
    lbl_3_common_bss_32220.field_0x04 = 0;
}

// .text:0x0006714C size:0x394 mapped:0x806A61E0
void fn_3_6714C(s32 arg0) {
    return;
}
