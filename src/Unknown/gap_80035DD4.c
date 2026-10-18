#include "Unknown/gap_80035DD4.h"

// .text:0x80035DD4 size:0xFC
void fn_80035DD4(void) {
    return;
}

// .text:0x80035ED0 size:0x1C
void fn_80035ED0(s32 index) {
    lbl_8039C3E0[index].unk54 = 0;
}

// .text:0x80035EEC size:0x34
void fn_80035EEC(s32 value, s32 index) {
    if (lbl_8039C3E0[index].unk5C > (u32)(value << 16)) {
        lbl_8039C3E0[index].unk5C = value << 16;
        lbl_8039C3E0[index].unk68 = 0;
    }
}

// .text:0x80035F20 size:0x214
void fn_80035F20(void) {
    return;
}

// .text:0x80036134 size:0xE0
void fn_80036134(void) {
    return;
}

// .text:0x80036214 size:0x5C
void fn_80036214(void) {
    return;
}

// .text:0x80036270 size:0x80
void fn_80036270(void) {
    return;
}

// .text:0x800362F0 size:0xE8
void fn_800362F0(void) {
    return;
}

// .text:0x800363D8 size:0xC4
void fn_800363D8(void) {
    return;
}

// .text:0x8003649C size:0xD0
void fn_8003649C(void) {
    return;
}

// .text:0x8003656C size:0xE0
void fn_8003656C(void) {
    return;
}

// .text:0x8003664C size:0x1D8
void fn_8003664C(void) {
    return;
}

// .text:0x80036824 size:0x1B8
void fn_80036824(void) {
    return;
}

// .text:0x800369DC size:0x60
void fn_800369DC(f32 zoom) {
    f32 scale;
    if (0.0f != zoom) {
        scale = 1.0f / zoom;
        C_MTXFrustum(lbl_801F8640, -0.175f * scale, 0.175f * scale, 0.25f * scale, -0.25f * scale, 1.0f, 512.0f);
    }
}

// .text:0x80036A3C size:0x24C
void fn_80036A3C(void) {
    return;
}

// .text:0x80036C88 size:0x3CC
void fn_80036C88(void) {
    return;
}

// .text:0x80037054 size:0x2C8
void fn_80037054(void) {
    return;
}

// .text:0x8003731C size:0x44C
void fn_8003731C(void) {
    return;
}

// .text:0x80037768 size:0x1FC
void fn_80037768(void) {
    return;
}

// .text:0x80037964 size:0x20
void fn_80037964(void) {
    fn_800B0A14_removeQueue();
}

// .text:0x80037984 size:0x11C
void fn_80037984(void) {
    return;
}

// .text:0x80037AA0 size:0x78
void fn_80037AA0(void) {
    return;
}

// .text:0x80037B18 size:0x94
void fn_80037B18(void) {
    return;
}

// .text:0x80037BAC size:0x5F0
void fn_80037BAC(void) {
    return;
}

// .text:0x8003819C size:0x220
void fn_8003819C(void) {
    return;
}

// .text:0x800383BC size:0x5C
f32 (*fn_800383BC(Gap80035DD4Xform* xf))[4] {
    PSMTXQuat(xf->rot, &xf->quat);
    PSMTXInverse(xf->rot, xf->inv);
    PSMTXTransApply(xf->rot, xf->result, xf->x, xf->y, xf->z);
    return xf->result;
}

// .text:0x80038418 size:0x1D8
void fn_80038418(void) {
    return;
}

// .text:0x800385F0 size:0x1C0
void fn_800385F0(void) {
    return;
}

// .text:0x800387B0 size:0x398
void fn_800387B0(void) {
    return;
}

// .text:0x80038B48 size:0x188
void fn_80038B48(void) {
    return;
}

// .text:0x80038CD0 size:0x15C
void fn_80038CD0(void) {
    return;
}

// .text:0x80038E2C size:0x98
void fn_80038E2C(Gap80035DD4Physics* phys) {
    phys->unk0 = 0.8f;
    phys->unk4 = 0.5f;
    phys->unk8 = 100.0f;
    phys->unkC = 5.0f;
    phys->unk10 = 1.5f;
    phys->unk14 = 0.001f;
    phys->steps = 8;
    phys->dt = (1.0f / phys->steps) / 60.0f;
    phys->dtSq = phys->dt * phys->dt;
    phys->unk24 = 1.0f / (2.0f * phys->dt);
}

// .text:0x80038EC4 size:0x44
void fn_80038EC4(Gap80035DD4Request* request, Gap80035DD4Actor** actor, u8 count) {
    if (lbl_800F79B8.index < 0) lbl_800F79B8.index = 0;
    fn_80038F08(request, *actor, count);
}

// .text:0x80038F08 size:0x408
#pragma dont_inline on
void fn_80038F08(Gap80035DD4Request* request, Gap80035DD4Actor* actor, u32 count) {
    return;
}

#pragma dont_inline reset

// .text:0x80039310 size:0x73C
void fn_80039310(void) {
    return;
}

// .text:0x80039A4C size:0x5C
void fn_80039A4C(void) {
    lbl_800F79B8.index = -1;
    lbl_803CBCA2[0] = 0;
    memset(lbl_800F79A0.bytes, 0, 0xC);
    lbl_803CB818 = -1;
    lbl_803CB820 = -1;
    lbl_803CBCA1 = 0;
}
