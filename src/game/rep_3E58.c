#include "game/rep_3E58.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "stl/mem.h"
#include "game/particle_spawn.h"
#include "game/gap_167CC4.h"

extern u8 lbl_3_data_28558[23];

// .text:0x001666B0 size:0x1EC mapped:0x807A5744
void fn_3_1666B0(void) {
    return;
}

// .text:0x0016689C size:0xD0 mapped:0x807A5930
void fn_3_16689C(void) {
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_GameLogic.gameStatus != 2 || g_GameLogic.framesOfExitingToMenu != 0 || g_Ball.fielderWBallIndex < 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame.TF_ballDespawnedInd) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_Ball.ballState != 1) {
        fn_800B0A14_removeQueue();
        return;
    }
    fn_3_16699C();
}

// .text:0x0016696C size:0x30 mapped:0x807A5A00
// .text:0x0016696C size:0x30 mapped:0x807A5A00
void fn_3_16696C(void) {
    // Calling the queue insertion with the local function and priority -6.
    // The constant -6 (0xFFFA) matches the lis/subi sequence.
    fn_800B0A5C_insertQueue(fn_3_16689C, 0xFFFA);
}

// .text:0x0016699C size:0x294 mapped:0x807A5A30
void fn_3_16699C(void) {
    return;
}


// .text:0x00166C30 size:0x110 mapped:0x807A5CC4
void fn_3_166C30(struct AnimationStruct* anim, s8 type) {
    spawnCharacterParticles(anim, type);
}

// .text:0x00166D40 size:0xC4 mapped:0x807A5DD4
void fn_3_166D40(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_GameLogic.gameStatus != 2) {
        fn_800B0A14_removeQueue();
        return;
    }
    if ((scene->unk14->unk62 == 0x1B || scene->unk14->unk62 == 0x1A) && g_Ball.ballState == 0) {
        fn_3_16699C();
        scene->unk1b = 1;
        return;
    }
    if (scene->unk1b != 0) {
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00166E04 size:0x1C8 mapped:0x807A5E98
void fn_3_166E04(void) {
    return;
}

// .text:0x00166FCC size:0x1AC mapped:0x807A6060
void fn_3_166FCC(void) {
    EffectTask* task = (EffectTask*)lbl_803CC1B8;
    s8 type;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.unk_479 != 0) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_GameLogic.gameStatus != 2) {
        fn_800B0A14_removeQueue();
        return;
    }
    if (task->owner->animID == 0x26 || task->owner->animID == 0x27) {
        type = lbl_3_data_28558[(u32)rand() % 23];
        spawnCharacterParticles(task->owner, type);
        return;
    }
    fn_800B0A14_removeQueue();
}

// .text:0x00167178 size:0x358 mapped:0x807A620C
void fn_3_167178(void) {
    return;
}

// .text:0x001674D0 size:0x3D8 mapped:0x807A6564
void fn_3_1674D0(void) {
    return;
}

// .text:0x001678A8 size:0x41C mapped:0x807A693C
void fn_3_1678A8(void) {
    return;
}
