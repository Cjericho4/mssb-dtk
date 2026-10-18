#include "Unknown/gap_800BD3A0.h"

// .text:0x800BD3A0 size:0xC
void LITInitColor(Gap800BD3A0Light* light, Gap800BD3A0Color* color) {
    light->color = *color;
}

// .text:0x800BD3AC size:0x10
void LITInitDir(Gap800BD3A0Light* light, f32 x, f32 y, f32 z) {
    light->dirX = x;
    light->dirY = y;
    light->dirZ = z;
}

// .text:0x800BD3BC size:0x10
void LITInitPos(Gap800BD3A0Light* light, f32 x, f32 y, f32 z) {
    light->posX = x;
    light->posY = y;
    light->posZ = z;
}

// .text:0x800BD3CC size:0x20
void LITInitAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(light, a0, a1, a2, k0, k1, k2);
}

// .text:0x800BD3EC size:0x8C
void LITAlloc(void) {
    return;
}

// .text:0x800BD478 size:0xD0
void fn_800BD478(void) {
    return;
}

// .text:0x800BD548 size:0x128
void fn_800BD548(void) {
    return;
}

// .text:0x800BD670 size:0x254
void fn_800BD670(void) {
    return;
}

// .text:0x800BD8C4 size:0x160
void fn_800BD8C4(void) {
    return;
}

// .text:0x800BDA24 size:0x70
void fn_800BDA24(Gap800BD3A0Instance* inst) {
    Gap800BD3A0ActorObj* obj = inst->obj;
    memcpy(&inst->obj->transform, &inst->transform, sizeof(Gap800BD3A0Transform));
    fn_800B2BFC(inst->obj, inst->unk64, inst->unk66);
    AnimateActorBones(obj);
    fn_800B3F20(obj);
    fn_800B313C(obj);
}

// .text:0x800BDA94 size:0x1F4
void fn_800BDA94(void) {
    return;
}

// .text:0x800BDC88 size:0xEC
void fn_800BDC88(void) {
    return;
}

// .text:0x800BDD74 size:0x118
void ActorObjectInitTable(void) {
    return;
}

// .text:0x800BDE8C size:0x14
void fn_800BDE8C(u8 value) {
    lbl_803009F8.unk4C = (value & 7) << 5;
}

// .text:0x800BDEA0 size:0xD0
void fn_800BDEA0(void) {
    return;
}

// .text:0x800BDF70 size:0x70
void fn_800BDF70(Gap800BD3A0Model* model) {
    if (lbl_803009F8.drawShadows && lbl_803009F8.callback != NULL && model->unk6C) {
        u8 flags = model->actor->flags98;
        if ((flags & 0x24) && (flags & 0x12)) {
            lbl_803009F8.callback(model, &lbl_803009F8.entries->data);
        }
    }
}

// .text:0x800BDFE0 size:0xBC
void fn_800BDFE0(void) {
    return;
}

// .text:0x800BE09C size:0xBC
void fn_800BE09C(void) {
    return;
}

// .text:0x800BE158 size:0x340
void fn_800BE158(void) {
    return;
}

// .text:0x800BE498 size:0x56C
void fn_800BE498(void) {
    return;
}

// .text:0x800BEA04 size:0x138
void fn_800BEA04(void) {
    return;
}

// .text:0x800BEB3C size:0x44
void fn_800BEB3C(void) {
    lbl_803009F8.boundCount = 0;
    lbl_803009F8.minX = lbl_803009F8.minY = lbl_803009F8.minZ = 100000000.0f;
    lbl_803009F8.maxX = lbl_803009F8.maxY = lbl_803009F8.maxZ = -100000000.0f;
    lbl_803009F8.x = lbl_803009F8.y = lbl_803009F8.z = 0.0f;
}

// .text:0x800BEB80 size:0x20
u8* fn_800BEB80(u8 index) {
    return &lbl_803009F8.entries[index].unkB0;
}

// .text:0x800BEBA0 size:0x10
u8 fn_800BEBA0(void) {
    return lbl_803009F8.drawShadows;
}

// .text:0x800BEBB0 size:0x10
u8 GetDrawShadows(void) {
    return lbl_803009F8.drawShadows;
}

// .text:0x800BEBC0 size:0xC
void DrawShadows(u8 enable) {
    lbl_803009F8.drawShadows = enable;
}

// .text:0x800BEBCC size:0x34
void fn_800BEBCC(void) {
    return;
}

// .text:0x800BEC00 size:0x30
void fn_800BEC00(BOOL enable) {
    if (enable) lbl_803009F8.unk4D = -1;
    else lbl_803009F8.unk4D = 1;
}

// .text:0x800BEC30 size:0x3D8
void fn_800BEC30(void) {
    return;
}

// .text:0x800BF008 size:0x30
void fn_800BF008(void) {
    GXLoadTlut(lbl_803009F8.tlut, 15);
}

// .text:0x800BF038 size:0x10
void fn_800BF038(s32 value) {
    lbl_803009F8.unk20 = value;
}

// .text:0x800BF048 size:0x10
void fn_800BF048(s32 value) {
    lbl_803009F8.unk18 = value;
}

// .text:0x800BF058 size:0x10
void fn_800BF058(Gap800BD3A0Callback value) {
    lbl_803009F8.callback = value;
}

// .text:0x800BF068 size:0xC
Gap800BD3A0State* fn_800BF068(void) {
    return &lbl_803009F8;
}

// .text:0x800BF074 size:0x130
void SKNLoadFile(void) {
    return;
}

// .text:0x800BF1A4 size:0x1C
void SKNFlushByIndex1(void) {
    return;
}

// .text:0x800BF1C0 size:0x28
void SKNFlushByIndex2(void) {
    return;
}

// .text:0x800BF1E8 size:0x1C
void SKNBzero32B(void) {
    return;
}

// .text:0x800BF204 size:0xA4
void SKNInit(void) {
    return;
}

// .text:0x800BF2A8 size:0x5F4
void fn_800BF2A8(void) {
    return;
}

// .text:0x800BF89C size:0x5F4
void SKNIt(void) {
    return;
}

// .text:0x800BFE90 size:0x10C
void SKN1Vecs16Norms16(void) {
    return;
}

// .text:0x800BFF9C size:0x10C
void fn_800BFF9C(void) {
    return;
}

// .text:0x800C00A8 size:0x220
void SKN2Vecs16Norms16NoTouch(void) {
    return;
}

// .text:0x800C02C8 size:0x220
void fn_800C02C8(void) {
    return;
}

// .text:0x800C04E8 size:0x148
void SKNAccVecs16Norms16Iu161(void) {
    return;
}

// .text:0x800C0630 size:0x140
void SKNAccVecs16Norms16Iu162(void) {
    return;
}

// .text:0x800C0770 size:0x4C
void convertTextureHeader(void) {
    return;
}

// .text:0x800C07BC size:0x2D0
void fn_800C07BC(void) {
    return;
}
