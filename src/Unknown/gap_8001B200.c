#include "Unknown/gap_8001B200.h"
#include "Unknown/gap_8001196C.h"

typedef struct PitchBankLoadState {
    u8 reset;
    u8 pitching;
} PitchBankLoadState;
extern PitchBankLoadState lbl_803CBC3C;

enum {
    ANIMATION_SLOT_COUNT = 13,
    ANIMATION_TIMER_LIMIT = 600,
    ANIMATION_NONE = -1,
    ANIMATION_SWITCH_IMMEDIATE = 1,
    ANIMATION_SWITCH_ON_END = 2,
    ANIMATION_DISPATCH_ALTERNATE = 2
};

/* Partial view: the flag at +0x28 gates animation frame counting. */
typedef struct AnimationDispatchGameState {
    u8 _pad0[0x28];
    u8 unk_0x28;
} AnimationDispatchGameState;
extern AnimationDispatchGameState lbl_80366158;

/* gap_800B117C.h cannot be included alongside gap_8001196C.h: their ANIMGet
 * bank-buffer declarations disagree. Use its GameActor query signatures here;
 * the legacy Gap8001196CActor view still needs reconciling with GameActor.
 * gap_80048BEC.h also has a conflicting settings view and its event dispatcher
 * lacks the f1 frame argument forwarded unchanged to the callback in retail. */
struct GameActor;
f32 fn_800B4A44(struct GameActor* actor, u16 index);
f32 fn_800B4C40(struct GameActor* actor);
s32 fn_8004AD54(u32 mode, u32 character);
void fn_8004B208(Gap8001196CAnim* anim, s32 animation, s32 channel, f32 frame);

// .text:0x8001B200 size:0x14
void fn_8001B200(void) {
    return;
}

// .text:0x8001B214 size:0x10
void fn_8001B214(void) {
    return;
}

// .text:0x8001B224 size:0xAC
void fn_8001B224(void) {
    return;
}

// .text:0x8001B2D0 size:0x38
void fn_8001B2D0(void) {
    return;
}

// .text:0x8001B308 size:0x54
void fn_8001B308(void) {
    return;
}

// .text:0x8001B35C size:0x17C
void fn_8001B35C(void) {
    return;
}

// .text:0x8001B4D8 size:0x114
void fn_8001B4D8(void) {
    return;
}

// .text:0x8001B5EC size:0x13C
void fn_8001B5EC(void) {
    return;
}

// .text:0x8001B728 size:0xE4
void fn_8001B728(void) {
    return;
}

// .text:0x8001B80C size:0x10C
void getAnimRelatedCoordinates(void) {
    return;
}

// .text:0x8001B918 size:0x78
void QueueCharacterAnimation(void) {
    return;
}

// .text:0x8001B990 size:0xB4
void AnimateCharacter(void) {
    return;
}

// .text:0x8001BA44 size:0x40C
/* FAKEMATCH: retain calls to the still-unimplemented animation installers. */
#pragma dont_inline on
void fn_8001BA44(s32 slot, s32 animation, s32 flags260, s32 flags263, s32 frames, s32 flags266, s32 flags26A) {
    return;
}

// .text:0x8001BE50 size:0x3E4
void fn_8001BE50(s32 slot, s32 animation, s32 flags260, s32 flags263, s32 frames, s32 flags266, s32 flags26A) {
    return;
}

#pragma dont_inline off
// .text:0x8001C234 size:0x2F4
// Advances pending gameplay animations and reports changed slots before dispatching frame sound events.
void fn_8001C234(u32* changedSlots) {
    Gap8001196CAnim* anim;
    s32 slot;
    Gap8001196CAnimTable* animations = &g_hugeAnimStruct;
    AnimationDispatchGameState* gameState = &lbl_80366158;
    Gap8001196CGameSettings* settings = &g_d_GameSettings;
    f32 frame;
    f32 duration;
    s32 boneIndex;
    s32 overrideFrame;

    *changedSlots = 0;
    for (slot = 0; slot < ANIMATION_SLOT_COUNT; slot++) {
        anim = animations->slotPtrs[slot];
        if (anim != NULL && anim->unk25D != 0) {
            if (anim->unk6A < ANIMATION_TIMER_LIMIT && gameState->unk_0x28 == 0 && lbl_803CBC3C.reset == 0 && anim->unk_0x26F == 0) {
                anim->unk6A++;
            }
            duration = 1.0f;
            if (animations->slotPtrs[slot] != NULL) boneIndex = (animations->slotPtrs[slot])->boneIndices[4];
            else boneIndex = 0xFFFF;
            if (boneIndex != 0xFFFF) {
                duration = fn_800B4A44((struct GameActor*)animations->actorEntries[anim->blockIndex].slot.actor, boneIndex);
            }
            anim->unk68 = duration / anim->unk4C;
            overrideFrame = anim->unk70;
            if ((s16)overrideFrame >= 0) anim->unk68 = overrideFrame;
            anim->unk70 = ANIMATION_NONE;
            if (anim->unk25E == ANIMATION_SWITCH_IMMEDIATE ||
                (anim->unk25E == ANIMATION_SWITCH_ON_END && anim->unk68 == 0 && anim->unk6A > 1) || anim->animID == ANIMATION_NONE) {
                *changedSlots |= 1 << slot;
                if (anim->nextAnim >= 0) {
                    frame = anim->unk6C;
                    if (settings->unk11 != 0 && settings->unk_0x06 == ANIMATION_DISPATCH_ALTERNATE) {
                        fn_8001BA44(slot, anim->nextAnim, anim->unk260, anim->unk263, anim->unk6C, anim->unk266, anim->unk26A);
                    } else {
                        fn_8001BE50(slot, anim->nextAnim, anim->unk260, anim->unk263, anim->unk6C, anim->unk266, anim->unk26A);
                    }
                    anim->unk60 = anim->animID;
                    anim->animID = anim->nextAnim;
                    anim->nextAnim = ANIMATION_NONE;
                    anim->unk25F = anim->unk260;
                    anim->unk262 = anim->unk263;
                    anim->unk265 = anim->unk266;
                    anim->unk269 = anim->unk26A;
                    anim->unk26C = anim->unk26D;
                    anim->unk6A = 0;
                    if (anim->unk66 >= 0) {
                        anim->nextAnim = anim->unk66;
                        anim->unk6C = anim->unk6E;
                        anim->unk260 = anim->unk261;
                        anim->unk263 = anim->unk264;
                        anim->unk25E = ANIMATION_SWITCH_ON_END;
                        anim->unk266 = anim->unk267;
                        anim->unk26A = anim->unk26B;
                        anim->unk26D = anim->unk26E;
                        anim->unk66 = ANIMATION_NONE;
                        continue;
                    }
                } else {
                    frame = 0.0f;
                }
                anim->unk25E = 0;
            } else {
                frame = fn_800B4C40((struct GameActor*)animations->actorEntries[anim->blockIndex].slot.actor);
            }
            if (lbl_803CBC3C.reset == 0) {
                fn_8004B208(anim, anim->animID, fn_8004AD54(settings->unk_0x09, anim->unk_0x275), frame);
            }
        }
    }
}

// .text:0x8001C528 size:0x60
void fn_8001C528(void) {
    return;
}

// .text:0x8001C588 size:0xF4
s32 fn_8001C588(s16 characterId) {
    return 0;
}

// .text:0x8001C67C size:0x2A4
void fn_8001C67C_animation(void) {
    return;
}

// .text:0x8001C920 size:0x120
/* Loads the pitching animation bank, selecting track 5 or 18 by game mode. */
s32 fn_8001C920(s32 charID) {
    s32 track;
    if (lbl_803CBC3C.pitching == 0) {
        if (lbl_803C6CF8.allowLoad != 1) goto notReady;
        lbl_803CBC3C.pitching = 1;
    }
    if (lbl_803CBC3C.pitching == 1) {
        if (g_d_GameSettings.unk11 || g_d_GameSettings.mode == GAME_TYPE_PRACTICE) {
            track = charID * SUBFILE_TRACKS + 18; /* practice / alternate pitching bank */
        } else {
            track = charID * SUBFILE_TRACKS + 5; /* normal pitching bank */
        }
        ARAMTransfer(&lbl_803CB790[track], g_hugeAnimStruct.pitchingAnimBank, 0, NULL);
        lbl_803CBC3C.pitching = 2;
    } else if (lbl_803CBC3C.pitching == 2) {
        if (lbl_803C6CF8.allowLoad == 1) {
            ANIMGet(g_hugeAnimStruct.pitchingAnimBank);
            if (g_hugeAnimStruct.slotPtrs[0]->animBankC == NULL) {
                g_hugeAnimStruct.slotPtrs[0]->animBankC = g_hugeAnimStruct.pitchingAnimBank;
            }
            return 1;
        }
    }
notReady:
    lbl_803CBC3C.reset = 0;
    return 0;
}

// .text:0x8001CA40 size:0xD0
void fn_8001CA40(void) {
    return;
}

// .text:0x8001CB10 size:0xC4
void fn_8001CB10(void) {
    return;
}

// .text:0x8001CBD4 size:0xF4
void fn_8001CBD4(void) {
    return;
}

// .text:0x8001CCC8 size:0x1AC
void fn_8001CCC8(void) {
    return;
}

// .text:0x8001CE74 size:0x200
void fn_8001CE74(void) {
    return;
}

// .text:0x8001D074 size:0x5C
void fn_8001D074(void) {
    return;
}

// .text:0x8001D0D0 size:0x40
void fn_8001D0D0(void) {
    return;
}

// .text:0x8001D110 size:0x38
void fn_8001D110(void) {
    return;
}

// .text:0x8001D148 size:0x38
void fn_8001D148(void) {
    return;
}

// .text:0x8001D180 size:0x154
void fn_8001D180(void) {
    return;
}

// .text:0x8001D2D4 size:0x8A0
void fn_8001D2D4(void) {
    return;
}

// .text:0x8001DB74 size:0x1E4
void fn_8001DB74(void) {
    return;
}

// .text:0x8001DD58 size:0x14C
void fn_8001DD58(void) {
    return;
}

// .text:0x8001DEA4 size:0x234
void fn_8001DEA4(void) {
    return;
}

// .text:0x8001E0D8 size:0x388
void fn_8001E0D8(void) {
    return;
}
