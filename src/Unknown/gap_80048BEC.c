#include "Unknown/gap_80048BEC.h"

// .text:0x80048BEC size:0x28
void fn_80048BEC(Gap80048BECTiming* timing) {
    s32 count = timing->limit;
    if (timing->requested < count) count = timing->requested;
    while (count > 0) count--;
}

// .text:0x80048C14 size:0x8
void fn_80048C14(s32 value) {
    lbl_803CBCE8 = value;
}

// .text:0x80048C1C size:0xC
void fn_80048C1C(void) {
    return;
}

// .text:0x80048C28 size:0x124
void fn_80048C28(void) {
    return;
}

// .text:0x80048D4C size:0xB4
void fn_80048D4C(void) {
    if (lbl_803CBCE8 != 0) {
        GXSetGPMetric(lbl_800FB4C8[lbl_803CB83C[0]], lbl_800FB554[lbl_803CB83C[1]]);
        GXClearGPMetric();
        if (lbl_800FB4C8[lbl_803CB83C[0]] == 0x22) {
            GXReadGP0Metric();
        }
        if (lbl_800FB554[lbl_803CB83C[1]] == 0x15) {
            GXReadGP1Metric();
        }
        GXSetVCacheMetric(0xF);
        GXClearVCacheMetric();
        GXClearPixMetric();
    }
}

// .text:0x80048E00 size:0xA8
s32 fn_80048E00(s32 which, s32 value) {
    s32 max = 0x23;
    if (which != 0) max = 0x17;
    if (value >= max) {
        value = 0;
    } else if (value < 0) {
        value = max - 1;
    }
    if (value != lbl_803CB83C[which]) {
        lbl_803CB83C[which] = value;
        memset(lbl_802E4B28.unk58, 0, 0x2C);
        memset(lbl_802E4B28.unk2C, 0xFF, 0x2C);
        lbl_803CB838 = 300;
    }
    return value;
}

// .text:0x80048EA8 size:0x10
s32 fn_80048EA8(s32 index) {
    return lbl_803CB83C[index];
}

// .text:0x80048EB8 size:0x368
void startGameRelated(void) {
    return;
}

// .text:0x80049220 size:0x2AC
void fn_80049220(void) {
    return;
}

// .text:0x800494CC size:0x3AC
void fn_800494CC(void) {
    return;
}

// .text:0x80049878 size:0x408
void possiblyTransferDataBetweenDifferentRels(void) {
    return;
}

// .text:0x80049C80 size:0xBC
void fn_80049C80(void) {
    return;
}

// .text:0x80049D3C size:0x50
void fn_80049D3C(void) {
    s32 i;
    u8 mode = g_d_GameSettings.mode;
    if (mode == 6) return;
    if (lbl_803C5F04.enabled == 0) return;
    for (i = 0; i < (mode == 6 ? 4 : 2); i++) {
    }
}

// .text:0x80049D8C size:0x370
void fn_80049D8C(void) {
    return;
}

// .text:0x8004A0FC size:0xC0
void fn_8004A0FC(void) {
    s32 i;
    lbl_803C5F04.groupA[0] = 0;
    lbl_803C5F04.groupB[0] = 0;
    lbl_803C5F04.groupA[1] = 1;
    lbl_803C5F04.groupA[2] = 1;
    lbl_803C5F04.groupA[3] = 2;
    lbl_803C5F04.groupA[4] = 0;
    lbl_803C5F04.groupB[1] = 1;
    lbl_803C5F04.groupB[2] = 1;
    lbl_803C5F04.groupB[3] = 2;
    lbl_803C5F04.groupB[4] = 0;
    for (i = 0; i < 4; i++) {
        lbl_803C5F04.quadsA[i].a = 0;
        lbl_803C5F04.quadsA[i].b = 0;
        lbl_803C5F04.quadsA[i].c = 0;
        lbl_803C5F04.quadsA[i].d = 1;
        lbl_803C5F04.quadsB[i].a = 0;
        lbl_803C5F04.quadsB[i].b = 0;
        lbl_803C5F04.quadsB[i].c = 0;
        lbl_803C5F04.quadsB[i].d = 1;
    }
}

// .text:0x8004A1BC size:0x100
void fn_8004A1BC(void) {
    return;
}

// .text:0x8004A2BC size:0x6C
void fn_8004A2BC(void) {
    switch (lbl_803CBBCC->step) {
    case 0:
        fn_800B0A5C_insertQueue(fn_8004A1BC, 0x2000);
        lbl_803C5F04.unk2C = 0;
        lbl_803CBBCC->step++;
        break;
    case 1:
        break;
    }
}

// .text:0x8004A328 size:0x24
BOOL fn_8004A328(Gap80048BECObj* obj) {
    if (obj->state != 0) {
        return FALSE;
    }
    obj->state = 2;
    return TRUE;
}

// .text:0x8004A34C size:0x26C
void fn_8004A34C(void) {
    return;
}

// .text:0x8004A5B8 size:0x218
void fn_8004A5B8(void) {
    return;
}

// .text:0x8004A7D0 size:0x210
void fn_8004A7D0(void) {
    return;
}

// .text:0x8004A9E0 size:0x1F8
void fn_8004A9E0(void) {
    return;
}

// .text:0x8004ABD8 size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// .text:0x8004ABE0 size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// .text:0x8004ABE8 size:0x18
s32 fn_8004ABE8(BOOL clear) {
    s32 value = lbl_803CBD00;
    if (clear) {
        lbl_803CBD00 = 0;
    }
    return value;
}

// .text:0x8004AC00 size:0xC4
void fn_8004AC00(void) {
    return;
}

// .text:0x8004ACC4 size:0x18
s32 fn_8004ACC4(BOOL clear) {
    s32 value = lbl_803CBD04;
    if (clear) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// .text:0x8004ACDC size:0x18
s32 fn_8004ACDC(BOOL clear) {
    s32 value = lbl_803CBD08;
    if (clear) {
        lbl_803CBD08 = 0;
    }
    return value;
}

// .text:0x8004ACF4 size:0x60
void fn_8004ACF4(Gap80048BECObj* obj, f32 value, s32 b, s32 c) {
    switch (obj->id) {
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
        if (value < 0.5f) lbl_803CBD04 = 1;
        break;
    }
    lbl_800FBE64[2].actor(obj, value, b, c);
}

// .text:0x8004AD54 size:0xC4
void fn_8004AD54(void) {
    return;
}

// .text:0x8004AE18 size:0x190
void fn_8004AE18(void) {
    return;
}

// .text:0x8004AFA8 size:0x210
void fn_8004AFA8(void) {
    return;
}

// .text:0x8004B1B8 size:0x8
void fn_8004B1B8(s32 value) {
    lbl_803CBD0C = value;
}

// .text:0x8004B1C0 size:0x48
void fn_8004B1C0(s32 index, s32 a, s32 b, s32 c) {
    if (index != 11) lbl_800FBE64[index].integer(a, b, c);
}

// .text:0x8004B208 size:0x68
void fn_8004B208(s32 a, s32 index, s32 c) {
    s32 slot;
    if (lbl_803CB848 != 0 && index >= 0 && index < 0x75) {
        slot = lbl_800FBDEC[index];
        if (slot != 11) lbl_800FBE64[slot].integer(a, index, c);
    }
}

// .text:0x8004B270 size:0x14
void fn_8004B270(void) {
    lbl_803CBD0C = 0;
    lbl_803CBD08 = 0;
    lbl_803CBD04 = 0;
}

// .text:0x8004B284 size:0x468
void fn_8004B284(void) {
    return;
}

// .text:0x8004B6EC size:0xC8
// Bowser Jr.'s per-frame slot update (from fn_80011468): shows one of the two bones 75 / 76 and
// hides the other, chosen by bit 28 of the slot-7 key animation's state (bone 75 shown when the
// bit is clear or there is no animation).
void fn_8004B6EC(Gap80048BECObj* obj, Gap80048BECActor** actor) {
    BOOL clear;

    if (obj == NULL || obj->slotTable7 == NULL) {
        clear = TRUE;
    } else {
        clear = ((fn_80024D2C((Gap80048BECKeyAnimation*)obj->slotTable7->animation) >> 28) & 1) ^ 1;
    }
    if (clear) {
        if (obj->boneIndex75 != 0xFFFF) {
            fn_800B2BE4(*actor, obj->boneIndex75);
        }
        if (obj->actorIndex != 0xFFFF) {
            fn_800B2BA8(*actor, obj->actorIndex, NULL, 0);
        }
    } else {
        if (obj->boneIndex75 != 0xFFFF) {
            fn_800B2BA8(*actor, obj->boneIndex75, NULL, 0);
        }
        if (obj->actorIndex != 0xFFFF) {
            fn_800B2BE4(*actor, obj->actorIndex);
        }
    }
}

// .text:0x8004B7B4 size:0x40
s32 fn_8004B7B4(Gap80048BECObj* obj, Gap80048BECActor** actor) {
    if (obj->actorIndex != 0xFFFF) fn_800B2BA8(*actor, obj->actorIndex, NULL, 0);
    return 0;
}

// .text:0x8004B7F4 size:0x2F8
void fn_8004B7F4(void) {
    return;
}

// .text:0x8004BAEC size:0x280
void fn_8004BAEC(void) {
    return;
}

// .text:0x8004BD6C size:0x144
void fn_8004BD6C(void) {
    return;
}

// .text:0x8004BEB0 size:0x1E4
// Animation event handler (animation 0x10, fielder on fire): while the frame is inside the
// character's window, emits the three effects of lbl_800FC488 from bone 4 plus the character's
// offset, aimed along the actor's facing.
void fn_8004BEB0(Gap80048BECObj* obj, f32 frame) {
    ControlExt control;
    Mtx matrix;
    Vec position;
    Vec direction;

    if (lbl_80366158.mode == 1) {
        return;
    }
    if (frame < (f32)lbl_800FBCA8[obj->id] || frame > (f32)lbl_800FBD14[obj->id]) {
        return;
    }
    position.x = (f32)lbl_800FC494[obj->id].x / 100000.0f;
    position.y = (f32)lbl_800FC494[obj->id].y / 100000.0f;
    position.z = (f32)lbl_800FC494[obj->id].z / 100000.0f;
    fn_8001B728(obj->slotKind, 4, (Gap80048BECVec*)&position);
    control.control.type = 0;
    CTRLSetRotation(&control.control, obj->rotation.x, obj->rotation.y, obj->rotation.z);
    CTRLBuildMatrix(&control.control, matrix);
    direction.x = 0.0f;
    direction.y = 0.0f;
    direction.z = 1.0f;
    PSMTXMultVec(matrix, &direction, &direction);
    lbl_800FC488[0]->unk0 = lbl_800FC488[1]->unk0 = lbl_800FC488[2]->unk0 = lbl_803CBD0C;
    fn_80030D88(&position, &direction, lbl_800FC488[0], 5);
    fn_80030D88(&position, &direction, lbl_800FC488[1], 5);
    fn_80030D88(&position, &direction, lbl_800FC488[2], 5);
}

// .text:0x8004C094 size:0x74
void fn_8004C094(Gap80048BECEffectTarget* target) {
    Gap80048BECEffectParams params;
    Gap80048BECEffectParams* p = &params;
    if (target != NULL) {
        memcpy(p, lbl_803CB860, sizeof(Gap80048BECEffectParams));
        p->unk0 = lbl_803CBD0C;
        p->unkC = 120000;
        p->unk10 = 60000;
        fn_80031CA4(target, p);
    }
}

// .text:0x8004C108 size:0x94
void fn_8004C108(Gap80048BECEffectTarget* target, u8 index) {
    Gap80048BECEffectParams params;
    Gap80048BECEffectParams* p = &params;
    if (target != NULL) {
        memcpy(p, lbl_803CB860, sizeof(params));
        p->unk0 = lbl_803CBD0C;
        p->color = (lbl_803CB864[index].r << 24) | (((u32)lbl_803CB864[index].g << 24) >> 8) | (lbl_803CB864[index].b << 8);
        fn_80031CA4(target, p);
    }
}

// .text:0x8004C19C size:0x374
void fn_8004C19C(void) {
    return;
}

// .text:0x8004C510 size:0xE8
// Animation event handler: on frame 0 hands over to fn_80062D94; on the character's event
// frame (lbl_800FBD80[charID]) spawns the shared effect at the actor's bone-4 position on
// the ground (y = 0) in colour lbl_800FC0FC[colorIndex].
void fn_8004C510(Gap80048BECObj* obj, s32 unused, s32 colorIndex, f32 frame) {
    Gap80048BECVec pos;

    if (frame == 0.0f) {
        fn_80062D94();
        return;
    }
    if (frame == (f32)lbl_800FBD80[obj->id]) {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
        fn_8001B728(obj->slotKind, 4, &pos);
        pos.y = 0.0f;
        lbl_803CB860->unk0 = lbl_803CBD0C;
        lbl_803CB860->color = (lbl_800FC0FC[colorIndex].r << 24) | (((u32)lbl_800FC0FC[colorIndex].g << 24) >> 8) |
                              (lbl_800FC0FC[colorIndex].b << 8);
        fn_80031CA4((Gap80048BECEffectTarget*)&pos, lbl_803CB860);
    }
}

// .text:0x8004C5F8 size:0x404
void fn_8004C5F8(void) {
    return;
}

// .text:0x8004C9FC size:0xC
void fn_8004C9FC(void) {
    lbl_803CB874 = lbl_803CB878;
}

// .text:0x8004CA08 size:0xC
void fn_8004CA08(s32 value) {
    lbl_803CB878 = value;
    lbl_803CB874 = value;
}

// .text:0x8004CA14 size:0x34
void fn_8004CA14(s32 a, s32 b) {
    fn_8000FE08(lbl_803C5F74.id, a, b);
}
