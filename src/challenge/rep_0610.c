#include "challenge/rep_0610.h"

// .text:0x0000C5AC size:0x434
void fn_1_C5AC(void) {
    return;
}

// .text:0x0000C9E0 size:0x1BC
void fn_1_C9E0(void) {
    return;
}

// .text:0x0000CB9C size:0x88
void fn_1_CB9C(s32 reset) {
    if (reset != 0) {
        lbl_1_bss_30BC = 0;
    } else {
        PSMTXCopy(lbl_1_bss_30C0.matrix, lbl_1_data_F4F8[lbl_803CBBC0].matrix);
        fn_800A7D4C(8, &lbl_1_data_F4F8[lbl_803CBBC0]);
    }
}

// .text:0x0000CC24 size:0xA4
void fn_1_CC24(void) {
    DrawingSceneStruct* entry;
    ChallengeState* state = &lbl_1_bss_3070;

    if (state->queued == 0) {
        state->queued = 1;
        entry = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_1_CCC8, (u16)(lbl_803CC1B8->priority + 1));
        if (state->unk2EF9 != 0) {
            Rep0610Items* items = &state->items;
            entry->unk14 = items->item4;
            entry->unk18 = lbl_1_data_F56C;
        } else {
            Rep0610Items* items = &state->items;
            entry->unk14 = items->item8;
            entry->unk18 = lbl_1_data_F56E;
        }
    }
}

// .text:0x0000CCC8 size:0x100
void fn_1_CCC8(void) {
    return;
}

// .text:0x0000CDC8 size:0x374
void fn_1_CDC8(void) {
    return;
}

// .text:0x0000D13C size:0x1B4
void fn_1_D13C(void) {
    return;
}

// .text:0x0000D2F0 size:0x10
void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

// .text:0x0000D300 size:0x1BC
void fn_1_D300(void) {
    return;
}

// .text:0x0000D4BC size:0xD4
void fn_1_D4BC(void) {
    return;
}

// .text:0x0000D590 size:0xA8
void fn_1_D590(s32 a, s32 b, f32 frame) {
    ChallengeState* state = &lbl_1_bss_3070;
    if (state->enabled == 0 || state->mode == 0) return;
    if (state->mode == 2) {
        if ((s32)frame == 0) state->phase += (state->phase != 0);
        if (state->phase == 3) state->phase = 0;
        if (state->phase != 2) return;
    }
    fn_8004B208(a, b, (s8)state->channel < 0 ? 0 : (s8)state->channel);
}

// .text:0x0000D638 size:0x18
u8 fn_1_D638(void) {
    u8 value = lbl_1_bss_3214;
    lbl_1_bss_3214 = 0;
    return value;
}

// .text:0x0000D650 size:0x10
void fn_1_D650(void) {
    lbl_1_bss_3214 = 1;
}

// .text:0x0000D660 size:0x1C
BOOL fn_1_D660(void) {
    return lbl_1_bss_3215 != 0;
}

// .text:0x0000D67C size:0xC
void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

// .text:0x0000D688 size:0x2C
void fn_1_D688(void) {
    if (++lbl_1_bss_3216 == 3) {
        lbl_1_bss_3216 = 0;
    }
}

// .text:0x0000D6B4 size:0x30
void fn_1_D6B4(void) {
    if (lbl_1_bss_3216 == 0) {
        lbl_1_bss_3216 = 3;
    }
    lbl_1_bss_3216--;
}

// .text:0x0000D6E4 size:0x38
s32 fn_1_D6E4(void) {
    switch (lbl_1_bss_3216) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[lbl_1_bss_3216];
    }
    return 0;
}

// .text:0x0000D71C size:0x88
f32 fn_1_D71C(s32 index) {
    s32 count;
    s32 i;
    ChallengeModel* model = (ChallengeModel*)g_hugeAnimStruct.ctrlOrBonePtr[index].unk34;
    count = model->count;
    for (i = 0; i < count; i++) {
        if (model->objects[i]->animation != 0 && model->objects[i]->animation->data != 0) {
            break;
        }
    }
    if (i < count) {
        return model->objects[i]->animation->time;
    }
    return 0.0f;
}

// .text:0x0000D7A4 size:0xFC
void fn_1_D7A4(void) {
    return;
}

// .text:0x0000D8A0 size:0x118
void fn_1_D8A0(void) {
    return;
}

// .text:0x0000D9B8 size:0x464
void fn_1_D9B8(void) {
    return;
}

// .text:0x0000DE1C size:0xF8
void fn_1_DE1C(void) {
    return;
}

// .text:0x0000DF14 size:0x184
void fn_1_DF14(void) {
    return;
}

// .text:0x0000E098 size:0x83C
void fn_1_E098(void) {
    return;
}

// .text:0x0000E8D4 size:0x124
void fn_1_E8D4(void) {
    return;
}

// .text:0x0000E9F8 size:0x28
void fn_1_E9F8(Rep0610Ring* ring, s32 index, s32 steps) {
    s32 i;
    for (i = 0; i < steps; i++) {
        index++;
        if (index == ring->count) {
            index = 0;
        }
    }
}

// .text:0x0000EA20 size:0x2D8
void fn_1_EA20(void) {
    return;
}

// .text:0x0000ECF8 size:0x348
void fn_1_ECF8(void) {
    return;
}

// .text:0x0000F040 size:0x90
void fn_1_F040(void) {
    ChallengeState* state = &lbl_1_bss_3070;
    Vec pos = lbl_1_rodata_7344;

    if (lbl_803C77B8.pressed & 0x100) {
        lbl_1_data_F2A0 = state->selection;
        fn_8002955C(&pos, 0, &lbl_1_data_F2A0);
    } else if (lbl_803C77B8.pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F0D0 size:0x108
void fn_1_F0D0(void) {
    return;
}

// .text:0x0000F1D8 size:0x120
void fn_1_F1D8(void) {
    return;
}

// .text:0x0000F2F8 size:0x84
void fn_1_F2F8(void) {
    ChallengeState* state = &lbl_1_bss_3070;

    if (lbl_803C77B8.pressed & 0x100) {
        lbl_80108B90 = state->selection;
        fn_800324EC(lbl_1_data_F17C, 0, -1, &lbl_80108B90);
    } else if (lbl_803C77B8.pressed & 0x200) {
        lbl_80108B90 = 0;
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F37C size:0x190
void fn_1_F37C(void) {
    return;
}

// .text:0x0000F50C size:0x1D8
void fn_1_F50C(void) {
    return;
}

// .text:0x0000F6E4 size:0xB4
void fn_1_F6E4(void) {
    Rep0610Triple* dst = &lbl_1_data_F0BC;
    ChallengeState* state = &lbl_1_bss_3070;
    Vec pos = lbl_1_rodata_731C;

    fn_1_F798(dst, &lbl_1_data_F0A8, sizeof(Rep0610Triple));
    if (lbl_803C77B8.pressed & 0x100) {
        dst->values[0] = state->selection;
        fn_80031CA4(&pos, dst);
    } else if (lbl_803C77B8.pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 10;
    }
}

// .text:0x0000F798 size:0x400
void fn_1_F798(Rep0610Triple* dst, Rep0610Triple* src, s32 size) {
    return;
}

// .text:0x0000FB98 size:0x4AC
void fn_1_FB98(void) {
    return;
}

// .text:0x00010044 size:0x414
void fn_1_10044(void) {
    return;
}

// .text:0x00010458 size:0x108
void fn_1_10458(void) {
    return;
}

// .text:0x00010560 size:0x110
void fn_1_10560(void) {
    return;
}

// .text:0x00010670 size:0x34
void fn_1_10670(void) {
    QueueEntry* entry = fn_800B0A5C_insertQueue(fn_1_10560, 0xB);
    entry->unk10 = 0;
}

// .text:0x000106A4 size:0x10
s32 fn_1_106A4(void) {
    return lbl_1_bss_3098;
}

// .text:0x000106B4 size:0x10
void fn_1_106B4(void) {
    lbl_1_bss_3098 = 0;
}

// .text:0x000106C4 size:0x78
void fn_1_106C4(void) {
    u16 pressed = lbl_803C77B8.pressed;
    ChallengeState* state = &lbl_1_bss_3070;

    if (pressed & 8) {
    } else if (pressed & 4) {
    } else if (pressed & 1) {
        state->unk11 ^= 1;
    } else if (pressed & 2) {
        state->unk11 ^= 1;
    } else if (pressed & 0x100) {
    } else if (pressed & 0x200) {
        state->unkC = 0;
        state->unk2F01 = 1;
    }
}

// .text:0x0001073C size:0x7C
void fn_1_1073C(Rep0610Obj1073C* obj) {
    Vec dir;
    dir.x = lbl_1_bss_67E0.pos.x - obj->pos.x;
    dir.y = lbl_1_bss_67E0.pos.y - obj->pos.y;
    dir.z = lbl_1_bss_67E0.pos.z - obj->pos.z;
    fn_80026134(0, &dir);
    fn_80026130(0, &lbl_1_data_ADC4, lbl_1_data_ADC0);
}

// .text:0x000107B8 size:0x2EC
void fn_1_107B8(void) {
    return;
}

// .text:0x00010AA4 size:0x28
void fn_1_10AA4(Rep0610Obj* obj, f32 value) {
    obj->value = value;
    obj->active = 1;
    if (lbl_1_bss_67B8 != NULL) {
        lbl_1_bss_67B8->value = value;
    }
}

// .text:0x00010ACC size:0x220
void fn_1_10ACC(void) {
    return;
}

// .text:0x00010CEC size:0x140
void fn_1_10CEC(void) {
    return;
}

// .text:0x00010E2C size:0x430
void fn_1_10E2C(void) {
    return;
}

// .text:0x0001125C size:0x490
void fn_1_1125C(void) {
    return;
}

// .text:0x000116EC size:0x28
void fn_1_116EC(struct TextureHeader* tex) {
    SetDisplayStateTexture(tex, 0, 0);
}

// .text:0x00011714 size:0x584
void fn_1_11714(void) {
    return;
}

// .text:0x00011C98 size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(g_hugeAnimStruct.menuLights[i], lbl_1_bss_68FC.view);
    }
}

// .text:0x00011D00 size:0x208
void fn_1_11D00(void) {
    return;
}

// .text:0x00011F08 size:0x2CC
void fn_1_11F08(void) {
    return;
}

// .text:0x000121D4 size:0x4F8
void fn_1_121D4(void) {
    return;
}

// .text:0x000126CC size:0x154
void fn_1_126CC(void) {
    return;
}

// .text:0x00012820 size:0x1B0
void fn_1_12820(HugeAnimEntry68* entry, Mtx mtx) {
    return;
}

// .text:0x000129D0 size:0x548
void fn_1_129D0(void) {
    return;
}

// .text:0x00012F18 size:0x74
void fn_1_12F18(Rep0610Obj12F18* obj) {
    fn_1_12820(g_hugeAnimStruct.ctrlOrBonePtr, obj->mtx);
    if (lbl_1_data_A978[lbl_1_bss_68FC.unk40] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C.obj, (s32)obj->mtx);
    }
}

// .text:0x00012F8C size:0x258
void fn_1_12F8C(void) {
    return;
}

// .text:0x000131E4 size:0x298
void fn_1_131E4(void) {
    return;
}

// .text:0x0001347C size:0x144
void fn_1_1347C(void) {
    return;
}

// .text:0x000135C0 size:0x1150
void fn_1_135C0(void) {
    return;
}

// .text:0x00014710 size:0x178
void fn_1_14710(void) {
    return;
}

// .text:0x00014888 size:0x44
void fn_1_14888(Rep0610Obj* obj) {
    if (lbl_1_bss_67E0.useContext != 0) {
        fn_800B9AA8((u32)&lbl_1_bss_67E0.context);
    } else {
        fn_800B9AA8(obj->context);
    }
}

// .text:0x000148CC size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(lbl_80366158.unk8);
    lbl_803CC1B8->loadingState = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// .text:0x00014928 size:0x44
void fn_1_14928(void) {
    fn_800AD038(lbl_80366158.unk8);
    lbl_803CC1B8->currentDrawingItem->loadingState = 1;
}

// .text:0x0001496C size:0x64C
void fn_1_1496C(void) {
    return;
}

// .text:0x00014FB8 size:0x1B8
void fn_1_14FB8(void) {
    return;
}

// .text:0x00015170 size:0x88
void fn_1_15170(void) {
    if (lbl_803C77B8.pressed & 0x200) {
        fn_800AD038(lbl_80366158.unk8);
        lbl_803CC1B8->loadingState = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_176EC;
        lbl_1_bss_30B8 = 1;
    } else if (lbl_803C77B8.pressed & 0x100) {
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x000151F8 size:0x214
void fn_1_151F8(void) {
    return;
}

// .text:0x0001540C size:0x354
void fn_1_1540C(void) {
    return;
}

// .text:0x00015760 size:0x580
void fn_1_15760(void) {
    return;
}

// .text:0x00015CE0 size:0x3F8
void fn_1_15CE0(void) {
    return;
}

// .text:0x000160D8 size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) {
        return 0xFF0F;
    }
    return 0xFFFF;
}

// .text:0x000160F8 size:0xD8
void fn_1_160F8(void) {
    return;
}

// .text:0x000161D0 size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x0001620C size:0x1F0
void fn_1_1620C(void) {
    return;
}

// .text:0x000163FC size:0x4
void fn_1_163FC(void) {
    return;
}

// .text:0x00016400 size:0x4C
void fn_1_16400(s8 delta) {
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].ring->count + delta) %
                     g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].ring->count;
}

// .text:0x0001644C size:0x10C
void fn_1_1644C(void) {
    return;
}

// .text:0x00016558 size:0x38
s32 fn_1_16558(s32 table, s32 entry) {
    return g_hugeAnimStruct.fielderStructs[lbl_1_bss_5F73].slots[table]->entries[entry].value;
}

// .text:0x00016590 size:0x50
s32 fn_1_16590(void) {
    u8 index = lbl_1_bss_5F73;
    return g_hugeAnimStruct.fielderStructs[index].slots[lbl_1_bss_6940[index].table]->entries[lbl_1_bss_6940[index].entry].value;
}

// .text:0x000165E0 size:0x2E8
void fn_1_165E0(void) {
    return;
}

// .text:0x000168C8 size:0xB0
void fn_1_168C8(void) {
    return;
}

// .text:0x00016978 size:0xD74
void fn_1_16978(void) {
    return;
}

// .text:0x000176EC size:0x20
void fn_1_176EC(void) {
    fn_1_1496C();
}

// .text:0x0001770C size:0x248
void fn_1_1770C(void) {
    return;
}

// .text:0x00017954 size:0x78
void fn_1_17954(void) {
    Mtx44 proj;
    C_MTXFrustum(proj, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
}

// .text:0x000179CC size:0x190
void fn_1_179CC(void) {
    return;
}

// .text:0x00017B5C size:0x234
void fn_1_17B5C(void) {
    return;
}

// .text:0x00017D90 size:0x16C
void fn_1_17D90(void) {
    return;
}
