#include "Unknown/gap_8001E460.h"

// .text:0x8001E460 size:0x14
void fn_8001E460(s32 value) {
    lbl_803CB7AC[lbl_803CBBC0] = value;
}

// .text:0x8001E474 size:0x14
void fn_8001E474(void) {
    lbl_803CB7AC[0] = 0;
    lbl_803CB7AC[1] = 0;
}

// .text:0x8001E488 size:0x2FC
void fn_8001E488(void) {
    return;
}

// .text:0x8001E784 size:0x9E8
void fn_8001E784(void) {
    return;
}

// .text:0x8001F16C size:0xBC
void fn_8001F16C(void) {
    return;
}

// .text:0x8001F228 size:0x298
void fn_8001F228(void) {
    return;
}

// .text:0x8001F4C0 size:0x128
void challengeMapMaybe(void) {
    return;
}

// .text:0x8001F5E8 size:0x2BC
void fn_8001F5E8(void) {
    return;
}

// .text:0x8001F8A4 size:0x3A8
void fn_8001F8A4(void) {
    return;
}

// .text:0x8001FC4C size:0x188
void fn_8001FC4C(void) {
    return;
}

// .text:0x8001FDD4 size:0x2C
void fn_8001FDD4(Gap8001E460Object* obj) {
    if (obj->fog != 0) {
        fn_800B9AA8(obj->fog);
    }
}

// .text:0x8001FE00 size:0x248
void fn_8001FE00(void) {
    return;
}

// .text:0x80020048 size:0x1D0
void calledWhenStartingMatch(void) {
    return;
}

// .text:0x80020218 size:0x34
BOOL fn_80020218(void) {
    if ((u32)lbl_8037169C.state == 13 || (u32)lbl_8037169C.state == 14 || (u32)lbl_8037169C.state == 15) return 1;
    return 0;
}

// .text:0x8002024C size:0x2C
void fn_8002024C(void) {
    fn_800ACF14(lbl_8037169C.resource);
}

// .text:0x80020278 size:0x110
void fn_80020278(void) {
    return;
}

// .text:0x80020388 size:0x58
void fn_80020388(void) {
    return;
}

// .text:0x800203E0 size:0xEC
void fn_800203E0(void) {
    return;
}

// .text:0x800204CC size:0xD0
void changeScene(void) {
    return;
}

// .text:0x8002059C size:0x88
void fn_8002059C(void) {
    return;
}

// .text:0x80020624 size:0xD8
void fn_80020624(void) {
    return;
}

// .text:0x800206FC size:0x968
void fn_800206FC(void) {
    return;
}

// .text:0x80021064 size:0x124
void fn_80021064(void) {
    return;
}

// .text:0x80021188 size:0x34
s32 fn_80021188(void) {
    sndMasterVolume(127, 1, 1, 1);
    return 0;
}

// .text:0x800211BC size:0x34
s32 fn_800211BC(void) {
    sndMasterVolume(0, 1, 1, 1);
    return 0;
}

// .text:0x800211F0 size:0x14
u8 fn_800211F0(void) {
    return lbl_800EFBC0.unk18;
}

// .text:0x80021204 size:0x24
void fn_80021204(void) {
    lbl_800E8754.unk23 = lbl_800EF808.unk398;
    lbl_800E8754.unk24 = lbl_800EF808.soundMode;
}

// .text:0x80021228 size:0x64
void fn_80021228(void) {
    return;
}

// .text:0x8002128C size:0x7C
void fn_8002128C(void) {
    return;
}

// .text:0x80021308 size:0xEC
void fn_80021308(void) {
    return;
}

// .text:0x800213F4 size:0x4
void fn_800213F4(void) {
    return;
}

// .text:0x800213F8 size:0x18
void fn_800213F8(u32 size) {
    lbl_803CBC40 += (size + 0x1F) & ~0x1F;
}

// .text:0x80021410 size:0x8C
void fn_80021410(void) {
    return;
}

// .text:0x8002149C size:0x34
void fn_8002149C(s32 index) {
    fn_800ACFB0(lbl_800EF808.resources[index]);
}

// .text:0x800214D0 size:0x48
void fn_800214D0(void) {
    return;
}

// .text:0x80021518 size:0x74
void fn_80021518(void) {
    return;
}

// .text:0x8002158C size:0x6C
void fn_8002158C(void) {
    return;
}

// .text:0x800215F8 size:0x58
void fn_800215F8(void) {
    return;
}

// .text:0x80021650 size:0xA8
void fn_80021650(void) {
    return;
}

// .text:0x800216F8 size:0x60
void fn_800216F8(void) {
    return;
}

// .text:0x80021758 size:0x1FC
void fn_80021758(void) {
    return;
}

// .text:0x80021954 size:0x2C
void fn_80021954(void) {
    return;
}

// .text:0x80021980 size:0x34
void fn_80021980(void) {
    return;
}

// .text:0x800219B4 size:0xEC
void f_initSound(void) {
    return;
}

// .text:0x80021AA0 size:0x20
void fn_80021AA0(void) {
    fn_800ACD44();
}

// .text:0x80021AC0 size:0x4
void fn_80021AC0(void) {
    return;
}

// .text:0x80021AC4 size:0x4
void fn_80021AC4(void) {
    return;
}

// .text:0x80021AC8 size:0x14
void fn_80021AC8(void) {
    lbl_803716B8.unk55C = 0;
}

// .text:0x80021ADC size:0xE0
void fn_80021ADC(void) {
    return;
}

// .text:0x80021BBC size:0xE8
void fn_80021BBC(void) {
    return;
}

// .text:0x80021CA4 size:0x3A8
void fn_80021CA4(void) {
    return;
}

// .text:0x8002204C size:0x400
void fn_8002204C(void) {
    return;
}
