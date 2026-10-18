#include "Unknown/gap_8002244C.h"

// .text:0x8002244C size:0x100
void fn_8002244C(void) {
    return;
}

// .text:0x8002254C size:0xD4
void fn_8002254C(void) {
    return;
}

// .text:0x80022620 size:0x14
void fn_80022620(void) {
    lbl_803716B8.unk1E8 = 0;
}

// .text:0x80022634 size:0x16C
void fn_80022634(void) {
    return;
}

// .text:0x800227A0 size:0x44
void fn_800227A0(void) {
    u8 flags = lbl_803716B8.flags;
    lbl_803716B8.unk1E9 = 0;
    lbl_803716B8.flags = flags | 1;
    lbl_803716B8.flags |= 2;
    lbl_803716B8.flags |= 4;
    lbl_803716B8.flags |= 8;
}

// .text:0x800227E4 size:0x1E8
void fn_800227E4(void) {
    return;
}

// .text:0x800229CC size:0x58
void fn_800229CC(void) {
    return;
}

// .text:0x80022A24 size:0xF0
void fn_80022A24(void) {
    return;
}

// .text:0x80022B14 size:0x54
void fn_80022B14(void) {
    return;
}

// .text:0x80022B68 size:0x14C
void fn_80022B68(void) {
    return;
}

// .text:0x80022CB4 size:0xA4
void fn_80022CB4(void) {
    return;
}

// .text:0x80022D58 size:0x54
void fn_80022D58(void) {
    return;
}

// .text:0x80022DAC size:0x2CC
void f_InitBone(void) {
    return;
}

// .text:0x80023078 size:0x268
void fn_80023078(void) {
    return;
}

// .text:0x800232E0 size:0x32C
void f_InitActorWithLayout(void) {
    return;
}

// .text:0x8002360C size:0x2D4
void BuildBoneSkinOrientationMatrix(void) {
    return;
}

// .text:0x800238E0 size:0xBC
void fn_800238E0(void) {
    return;
}

// .text:0x8002399C size:0x108
void fn_8002399C(void) {
    return;
}

// .text:0x80023AA4 size:0x60
void fn_80023AA4(void) {
    return;
}

// .text:0x80023B04 size:0x8C
void fn_80023B04(void) {
    return;
}

// .text:0x80023B90 size:0x164
void fn_80023B90(void) {
    return;
}

// .text:0x80023CF4 size:0x48
void fn_80023CF4(BOOL enabled) {
    if (enabled) {
        OSSetProgressiveMode(1);
        fn_800A7E00();
    } else {
        OSSetProgressiveMode(0);
    }
    lbl_803CBC60 = enabled;
}

// .text:0x80023D3C size:0x8
s32 fn_80023D3C(void) {
    return lbl_803CBC60;
}

// .text:0x80023D44 size:0x8
void fn_80023D44(s32 value) {
    lbl_803CBC60 = value;
}

// .text:0x80023D4C size:0x4C
BOOL fn_80023D4C(Gap8002244CObj* obj, Gap8002244CVector* out) {
    if (obj->unk8 != 0) {
        obj->current = obj->unk10;
        *out = obj->vectors[obj->current];
        return 1;
    }
    return 0;
}

// .text:0x80023D98 size:0x64
void fn_80023D98(void) {
    return;
}

// .text:0x80023DFC size:0x4C
void fn_80023DFC(void) {
    return;
}

// .text:0x80023E48 size:0xA4
void fn_80023E48(void) {
    return;
}

// .text:0x80023EEC size:0x20
void fn_80023EEC(Gap8002244CObj* obj, s32 a, s32 b) {
    obj->unk0 = a;
    obj->unk4 = b;
    obj->unk8 = 0;
    obj->unkC = 0;
    obj->unk10 = 0;
    obj->unk18 = 0;
}

// .text:0x80023F0C size:0x278
void fn_80023F0C(void) {
    return;
}

// .text:0x80024184 size:0x20C
void gOz_GXSetTexture(void) {
    return;
}

// .text:0x80024390 size:0x74
void fn_80024390(void) {
    return;
}

// .text:0x80024404 size:0x1E8
void SetDisplayStateTexture(void) {
    return;
}

// .text:0x800245EC size:0xE8
void fn_800245EC(void) {
    return;
}

// .text:0x800246D4 size:0x110
void fn_800246D4(void) {
    return;
}

// .text:0x800247E4 size:0x5C
void fn_800247E4(void) {
    return;
}

// .text:0x80024840 size:0x134
void challengeStarRelatedInd(void) {
    return;
}

// .text:0x80024974 size:0x64
void multBottomBits_asFloat(void) {
    return;
}

// .text:0x800249D8 size:0x128
void byteWiseMultiply(void) {
    return;
}

// .text:0x80024B00 size:0xB4
void LERPToNewRange_Float(void) {
    return;
}

// .text:0x80024BB4 size:0x50
void LinearInterpolateToNewRange(void) {
    return;
}

// .text:0x80024C04 size:0x68
void fn_80024C04(void) {
    return;
}

// .text:0x80024C6C size:0xC0
void fn_80024C6C(void) {
    return;
}

// .text:0x80024D2C size:0x84
void fn_80024D2C(void) {
    return;
}

// .text:0x80024DB0 size:0x1F4
void fn_80024DB0(void) {
    return;
}

// .text:0x80024FA4 size:0xCB4
void fn_80024FA4(void) {
    return;
}

// .text:0x80025C58 size:0x184
void fn_80025C58(void) {
    return;
}
