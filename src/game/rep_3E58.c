#include "game/rep_3E58.h"
#include "header_rep_data.h"
#include "UnknownHeaders.h"
#include "stl/mem.h"

// .text:0x001666B0 size:0x1EC mapped:0x807A5744
void fn_3_1666B0(void) {
    return;
}

// .text:0x0016689C size:0xD0 mapped:0x807A5930
void fn_3_16689C(void) {
    return;
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

typedef struct {
    s32 unk0;
    u8 _pad04[0x3C];
    VecXYZ pos;          /* 0x40 */
    u8 color[3];         /* 0x4C */
    u8 _pad4F;
} ParticleSpawnParams; /* size: 0x50 */
extern ParticleSpawnParams lbl_3_data_28508;
extern s32 lbl_803CBD0C;
void fn_80026998(ParticleSpawnParams* params);
s32 fn_8001B728(s32 index, s32 type, VecXYZ* out);

// .text:0x00166C30 size:0x110 mapped:0x807A5CC4
void fn_3_166C30(struct AnimationStruct* anim, s8 type) {
    VecXYZ pos;
    ParticleSpawnParams params;

    memset(&pos, 0, sizeof(VecXYZ));
    memcpy(&params, &lbl_3_data_28508, sizeof(ParticleSpawnParams));
    params.unk0 = lbl_803CBD0C;
    if (fn_8001B728(anim->unk254, type, &pos) == 0) {
        memset(&pos, 0, sizeof(VecXYZ));
        fn_8001B728(anim->unk254, 4, &pos);
    }
    memcpy(&params.pos, &pos, sizeof(VecXYZ));
    params.color[0] = rand() % 256;
    params.color[1] = rand() % 256;
    params.color[2] = rand() % 256;
    fn_80026998(&params);
}

// .text:0x00166D40 size:0xC4 mapped:0x807A5DD4
void fn_3_166D40(void) {
    return;
}

// .text:0x00166E04 size:0x1C8 mapped:0x807A5E98
void fn_3_166E04(void) {
    return;
}

// .text:0x00166FCC size:0x1AC mapped:0x807A6060
void fn_3_166FCC(void) {
    return;
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
