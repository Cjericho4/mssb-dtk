#include "Unknown/gap_80062578.h"

// .text:0x80062578 size:0x2C
BOOL fn_80062578(void) {
    return lbl_803C66B0.busy[0] == 0 && lbl_803C66B0.busy[1] == 0;
}

// .text:0x800625A4 size:0xD0
// Requests `command` for player `index`: reports if a request is still flagged busy (index 0 is
// used for the flag when g_d_GameSettings.mode is 0), stores the command and clears the
// player's byte in all 14 status rows.
void fn_800625A4(s32 index, s32 command) {
    /* Non-matching: the unrolled loop stores a separate zero register; the target stores the
       loop counter's register (li r4, 0). */
    s32 flagIndex;
    s32 i;

    flagIndex = (g_d_GameSettings.mode == 0) ? 0 : index;
    if (lbl_803C66B0.flags[flagIndex] != 0) {
        OSReport(lbl_800E6970, flagIndex, lbl_803C66B0.busy[flagIndex]);
    }
    lbl_803C66B0.busy[index] = command;
    for (i = 0; i < 14; i++) {
        lbl_803C66B0.rows[i].perIndex[index] = 0;
    }
}

// .text:0x80062674 size:0x78
void fn_80062674(s32 index) {
    lbl_803C663C.values[index]--;
    if (lbl_803C663C.values[index] != 0) {
        return;
    }
    if (g_d_GameSettings.mode == 0) {
        lbl_803C66B0.flags[0] = 0;
    } else {
        lbl_803C66B0.flags[index] = 0;
    }
    lbl_803C66B0.busy[index] = 0;
}

// .text:0x800626EC size:0x58
void fn_800626EC(s32 index) {
    if (g_d_GameSettings.mode == 0) lbl_803C66B0.flags[0] = 1;
    else lbl_803C66B0.flags[index] = 1;
    lbl_803C663C.values[index]++;
}

// .text:0x80062744 size:0x20
void fn_80062744(void) {
    lbl_803C663C.unkC = 0;
    lbl_803C663C.unk8 = 0;
    lbl_803C663C.unk4 = 0;
    lbl_803C663C.unk0 = 0;
}

// .text:0x80062764 size:0x30
void fn_80062764(s32 value) {
    lbl_80108B84.value = value;
    fn_800215F8(&lbl_80108B84);
}

// .text:0x80062794 size:0x30
BOOL fn_80062794(u32 handle) {
    return sndFXCheck(handle) != -1;
}

// .text:0x800627C4 size:0x34
s32 fn_800627C4(void) {
    fn_80021518(0, lbl_800EF808.sound14);
    return 0;
}

// .text:0x800627F8 size:0x34
s32 fn_800627F8(void) {
    fn_80021518(49, lbl_800EF808.sound9C);
    return 0;
}

// .text:0x8006282C size:0x30
void fn_8006282C(void) {
    fn_80021518(0x20, lbl_800EF808.sound98);
}

// .text:0x8006285C size:0x34
s32 fn_8006285C(void) {
    fn_80021518(32, lbl_800EF808.sound98);
    return 0;
}

// .text:0x80062890 size:0x44
u32 fn_80062890(s32 index) {
    return sndFXStartEx(lbl_80108E38[index], lbl_80108B3C[index], 63, 0);
}

// .text:0x800628D4 size:0x74
/* Announcer name call-out for a character: the SFX is keyed by the roster-grid index
 * (fn_800698F8), so colour variants share their base's call-out.  useAltBirdoGrid is set so that
 * Birdo (grid 0x11) uses the alternate entry 0x20 of lbl_80108DF4.  Returns the voice handle. */
u32 fn_800628D4(s32 charID) {
    u32 handle;
    u16 sfx;
    lbl_8034E9A0.useAltBirdoGrid = 1;
    sfx = lbl_80108DF4[fn_800698F8(charID)];
    handle = sndFXStartEx(sfx, lbl_80108B18[0], 63, 0);
    sndFXCtrl(handle, 0x5B, 0);
    return handle;
}

// .text:0x80062948 size:0x14
void fn_80062948(void) {
    lbl_803C6714.unkD = 1;
}

// .text:0x8006295C size:0xF4
// Queue task: keeps sound effect 0 playing until a stop is requested (unkD), then keys it off
// and removes itself; if the sound system is not ready it stops at once and reports "sound end".
void fn_8006295C(void) {
    if (lbl_800EF808.unk398 != 0) {
        if (lbl_803C6714.playing == 0) {
            lbl_803C6714.voice = sndFXStartEx(0, lbl_803CB889, 0x3F, 0);
            lbl_803C6714.playing = 1;
            lbl_803C6714.unkD = 0;
        }
        if (lbl_803C6714.unkD != 0) {
            sndFXKeyOff(lbl_803C6714.voice);
            lbl_803C6714.voice = 0;
            lbl_803C6714.unkD = 0;
            lbl_803C6714.playing = 0;
            fn_800B0A14_removeQueue();
        }
    } else {
        sndFXKeyOff(lbl_803C6714.voice);
        lbl_803C6714.voice = 0;
        lbl_803C6714.unkD = 0;
        lbl_803C6714.playing = 0;
        OSReport(lbl_800E69A8);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x80062A50 size:0x24
void initializeUnknown(void) {
    lbl_8034E9A0.unk48B3 = 0;
    lbl_803C6714.unk0 = 0;
    lbl_803C6714.unk5 = 0;
    lbl_803C6714.unk4 = 0;
}

// .text:0x80062A74 size:0x20
void fn_80062A74(void) {
    lbl_803C6714.unk5 = 1;
    lbl_8034E9A0.unk48B3 = 1;
}

// .text:0x80062A94 size:0x150
void fn_80062A94(void) {
    return;
}

// .text:0x80062BE4 size:0x40
void fn_80062BE4(Gap80062578Object* obj) {
    if (lbl_80366158.mode != 1) {
        lbl_80108B90.value = lbl_803CBD0C;
        fn_80032064(obj, &lbl_80108B90);
    }
}

// .text:0x80062C24 size:0x3C
void fn_80062C24(Gap80062578Object* obj) {
    if (lbl_80366158.mode != 1 && obj != NULL) fn_80032284(obj);
}

// .text:0x80062C60 size:0x134
void fn_80062C60(void) {
    return;
}

// .text:0x80062D94 size:0xD8
/* Actor bone index of bone id `id` on the model in slot `slotKind`, 0xFFFF if there is none. */
static inline s32 slotBoneIndex(s32 slotKind, s32 id) {
    Gap80062578Actor* slot = g_hugeAnimStruct.slotPtrs[slotKind];

    if (slot != NULL) {
        return slot->boneIndices[(u16)id];
    }
    return 0xFFFF;
}

// Starts the lbl_80108B90 effect on the first bone of lbl_80108BE0 that the actor's model has
// (none if the list runs out). Nothing in mode 1.
void fn_80062D94(Gap80062578Actor* actor) {
    /* Non-matching: registers only (the list walker and the slot pointer want r7 and r8). */
    s32 i;

    if (lbl_80366158.mode == 1) {
        return;
    }
    for (i = 0; lbl_80108BE0[i] != 0xFFFF && slotBoneIndex(actor->slotKind, lbl_80108BE0[i]) == 0xFFFF; i++) {
    }
    if (lbl_80108BE0[i] != 0xFFFF) {
        lbl_80108B90.value = lbl_803CBD0C;
        fn_800324EC(lbl_80108BE0[i], actor->slotKind, -1, &lbl_80108B90);
    }
}

// .text:0x80062E6C size:0x68
void fn_80062E6C(Gap80062578Actor* actor, s32 a, s32 b) {
    s32 row = a - 0x28;

    if (lbl_80366158.mode != 1) {
        fn_8004B1C0(lbl_80108BF0[row][actor->unk252], actor, a, b);
    }
}

// .text:0x80062ED4 size:0x64
s32 fn_80062ED4(s32 unused, Gap80062578RenderGroup** group) {
    Gap80062578RenderObject* obj;
    Gap80062578RenderGroup* owner = *group;
    s32 i;
    for (i = 0; i < owner->count; i++) {
        obj = owner->objects[i];
        switch (obj->type) {
        case 0x41: case 0x43: case 0x45: case 0x47: case 0x49: case 0x4B:
            obj->state = 2;
            break;
        }
    }
    return 0;
}

BOOL fn_80062F38(Gap80062578RenderObject* obj, Gap80062578Transform* transform, f32 matrix[3][4], f32 weight);

// .text:0x80062F38 size:0xD8
// Bone callback installed by fn_80063010 (the Magikoopas' model setup hook): for bones 0x46,
// 0x4A and 0x4C blends the bone's control toward its target and builds its matrix with the
// flip variant.
BOOL fn_80062F38(Gap80062578RenderObject* obj, Gap80062578Transform* transform, f32 matrix[3][4], f32 weight) {
    switch (obj->type) {
    case 0x46:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        CTRLBuildMatrix_Flip(&transform->current, matrix, 0);
        return 1;
    case 0x4A:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        CTRLBuildMatrix_Flip(&transform->current, matrix, 0);
        return 1;
    case 0x4C:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        CTRLBuildMatrix_Flip(&transform->current, matrix, 0);
        return 1;
    default:
        return 0;
    }
}

// .text:0x80063010 size:0x18
s32 fn_80063010(s32 arg0, Gap80062578Scene** scene) {
    (*scene)->callback = (void (*)(void))fn_80062F38;
    return 0;
}

// .text:0x80063028 size:0x384
#pragma dont_inline on
void fn_80063028(Gap80062578Control* control, f32 matrix[3][4], u32 flags) {
    return;
}
#pragma dont_inline reset

// .text:0x800633AC size:0x36C
#pragma dont_inline on
void fn_800633AC(Gap80062578Control* control, f32 matrix[3][4], u32 flags) {
    return;
}
#pragma dont_inline reset

// .text:0x80063718 size:0xA4
BOOL fn_80063718(Gap80062578RenderObject* obj, Gap80062578Transform* transform, f32 matrix[3][4], f32 weight) {
    switch (obj->type) {
    case 0x4A:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        fn_800633AC(&transform->current, matrix, lbl_803CB890);
        return 1;
    case 0x4B:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        fn_800633AC(&transform->current, matrix, lbl_803CB890);
        return 1;
    default:
        return 0;
    }
}

// .text:0x800637BC size:0x18
s32 fn_800637BC(s32 arg0, Gap80062578Scene** scene) {
    (*scene)->callback = (void (*)(void))fn_80063718;
    return 0;
}

// .text:0x800637D4 size:0x8
s32 fn_800637D4(void) {
    return 0x0;
}

// .text:0x800637DC size:0xD8
// Bone callback installed by fn_800637BC (the Paratroopas' model setup hook): blends the
// control of bones 0x40, 0x41 and 0x47 toward its target and builds the matrix (fn_80063028
// with flags 4 for 0x40, the flip variant with 1 for 0x41 and 0 for 0x47).
BOOL fn_800637DC(Gap80062578RenderObject* obj, Gap80062578Transform* transform, f32 matrix[3][4], f32 weight) {
    switch (obj->type) {
    case 0x47:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        CTRLBuildMatrix_Flip(&transform->current, matrix, 0);
        return 1;
    case 0x40:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        fn_80063028(&transform->current, matrix, 4);
        return 1;
    case 0x41:
        fn_800B84AC(&transform->current, &transform->target, &transform->current, weight);
        CTRLBuildMatrix_Flip(&transform->current, matrix, 1);
        return 1;
    default:
        return 0;
    }
}

// .text:0x800638B4 size:0x18
s32 fn_800638B4(s32 arg0, Gap80062578Scene** scene) {
    (*scene)->callback = (void (*)(void))fn_800637DC;
    return 0;
}

// .text:0x800638CC size:0x8C
void fn_800638CC(void) {
    Gap80062578Slot* slot;
    u32 i;

    for (i = 0; i < 9; i++) {
        slot = &lbl_802E4BC0.slots[(s8)i];
        memset(slot->unk0, 0, 0xC);
        memset(slot->unkC, 0, 0xC);
        slot->unk18 = 0;
        slot->unk1C = 0;
    }
}

// .text:0x80063958 size:0x64
void fn_80063958(s8 index) {
    Gap80062578Slot* slot = &lbl_802E4BC0.slots[index];

    memset(slot->unk0, 0, 0xC);
    memset(slot->unkC, 0, 0xC);
    slot->unk18 = 0;
    slot->unk1C = 0;
}

// .text:0x800639BC size:0x988
void fn_800639BC(void) {
    return;
}

// .text:0x80064344 size:0xEC
/* Starts an emitter at `position` from the lbl_80108D48 template with its three unk54 values
   scaled by scaleA and its unk14 / unk38 values scaled by scaleB. */
static inline void startScaledEmitter(Gap80062578Vec* position, s32 type, f32 scaleA, f32 scaleB) {
    Gap80062578Emitter emitter;

    memcpy(&emitter, &lbl_80108D48, sizeof(emitter));
    emitter.unk0 = lbl_803CBD0C;
    emitter.unk14[0] *= scaleB;
    emitter.unk14[1] *= scaleB;
    emitter.unk14[2] *= scaleB;
    emitter.unk14[3] *= scaleB;
    emitter.unk14[4] *= scaleB;
    emitter.unk14[5] *= scaleB;
    emitter.unk38 *= scaleB;
    emitter.unk54[0] *= scaleA;
    emitter.unk54[1] *= scaleA;
    emitter.unk54[2] *= scaleA;
    fn_8002B7F8(position, &emitter, type);
}

// Starts a type-1 emitter at `position`, scaled by 3.0 times the length of `velocity`.
void fn_80064344(Gap80062578Vec* position, Gap80062578Vec* velocity) {
    f32 scale = 3.0f * PSVECMag(velocity);

    startScaledEmitter(position, 1, scale, scale);
}

// .text:0x80064430 size:0x104
// Starts a scaled emitter of the given type (see startScaledEmitter).
void fn_80064430(Gap80062578Vec* position, s32 type, f32 scaleA, f32 scaleB) {
    startScaledEmitter(position, type, scaleA, scaleB);
}

// .text:0x80064534 size:0x220
void fn_80064534(void) {
    return;
}
