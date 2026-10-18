#include "Unknown/gap_800B117C.h"

// .text:0x800B117C size:0xC
void fn_800B117C(u8 value) {
    lbl_803CBB34->unk8C = value;
}

// .text:0x800B1188 size:0x11C
void fn_800B1188(void) {
    return;
}

// .text:0x800B12A4 size:0x38
void DrawNullSprite(Gap800B117CVertex* vertices, s32 count) {
    DrawSprite(152, vertices, count, NULL, 0, 0);
}

// .text:0x800B12DC size:0x38
void fn_800B12DC(Gap800B117CVertex* vertices, s32 count) {
    DrawSprite(160, vertices, count, NULL, 0, 0);
}

// .text:0x800B1314 size:0x3C
void fn_800B1314(Gap800B117CVertex* vertices, Gap800B117CTexture* texture, u32 height, u32 width) {
    DrawSprite(0x80, vertices, 4, texture, height, width);
}

// .text:0x800B1350 size:0x38
void DrawSprite_TexObj(Gap800B117CVertex* vertices, Gap800B117CTexture* texture) {
    DrawSprite(0x80, vertices, 4, texture, texture->height, texture->width);
}

// .text:0x800B1388 size:0x38
void fn_800B1388(Gap800B117CVertex* vertices) {
    DrawSprite(0x80, vertices, 4, NULL, 0, 0);
}

// .text:0x800B13C0 size:0xA8
void fn_800B13C0(void) {
    return;
}

// .text:0x800B1468 size:0x98
void fn_800B1468(void) {
    return;
}

// .text:0x800B1500 size:0x9BC
#pragma dont_inline on
void DrawSprite(s32 primitive, Gap800B117CVertex* vertices, s32 count, Gap800B117CTexture* texture, u32 height, u32 width) {
    return;
}

#pragma dont_inline reset

// .text:0x800B1EBC size:0x2A4
void fn_800B1EBC(void) {
    return;
}

// .text:0x800B2160 size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34->unk8A = value;
}

// .text:0x800B216C size:0x3C
void fn_800B216C(void) {
    return;
}

// .text:0x800B21A8 size:0x98
void fn_800B21A8(void) {
    return;
}

// .text:0x800B2240 size:0x294
void fn_800B2240(void) {
    return;
}

// .text:0x800B24D4 size:0x48
void fn_800B24D4(void) {
    return;
}

// .text:0x800B251C size:0x288
void fn_800B251C(void) {
    return;
}

// .text:0x800B27A4 size:0x38
void fn_800B27A4(s32 index) {
    u16 mask;
    if (index < 0) return;
    if (index > 14) return;
    lbl_803CC1C8 = index;
    mask = 1 << index;
    lbl_801115A0.mask6 = lbl_801115A0.mask8 = lbl_801115A0.maskA = lbl_801115A0.maskC = mask;
}

// .text:0x800B27DC size:0x78
void fn_800B27DC(void) {
    return;
}

// .text:0x800B2854 size:0x274
void fn_800B2854(void) {
    return;
}

// .text:0x800B2AC8 size:0x84
void fn_800B2AC8(void) {
    return;
}

// .text:0x800B2B4C size:0x8
void fn_800B2B4C(Gap800B117CObj* obj, f32 value) {
    obj->unk90 = value;
}

// .text:0x800B2B54 size:0x18
void fn_800B2B54(Gap800B117CObj* obj, u16 index, u8 value) {
    obj->entries[index]->unk134 = value;
}

// .text:0x800B2B6C size:0x8
void Set_FUN_800b2b6c(Gap800B117CObj* obj, s32 value) {
    obj->unk88 = value;
}

// .text:0x800B2B74 size:0x34
void fn_800B2B74(Gap800B117CObj* obj, u16 index) {
    DSInsertListObject(&obj->list, obj->list.tail, obj->entries[index]);
}

// .text:0x800B2BA8 size:0x3C
s32 fn_800B2BA8(Gap800B117CObj* obj, u16 index, Gap800B117CObj* other, u16 otherIndex) {
    Gap800B117CObj* entry = obj->entries[index];
    s32 previous = entry->unk14;
    if (other != NULL) entry->unk14 = other->entries[otherIndex]->unk14;
    else entry->unk14 = 0;
    return previous;
}

// .text:0x800B2BE4 size:0x18
void fn_800B2BE4(Gap800B117CObj* obj, u16 index) {
    obj->entries[index]->unk14 = (s32)obj->entries[index]->entries;
}

// .text:0x800B2BFC size:0xC
void fn_800B2BFC(Gap800B117CObj* obj, s16 a, s16 b) {
    obj->unk80 = a;
    obj->unk82 = b;
}

// .text:0x800B2C08 size:0x8
void fn_800B2C08(Gap800B117CObj* obj, s16 value) {
    obj->unk84 = value;
}

// .text:0x800B2C10 size:0x34
void fn_800B2C10(Gap800B117CObj* obj, u16 index, Gap800B117CVec* vec) {
    PSMTXMultVec(obj->matrices[index], vec, vec);
}

// .text:0x800B2C44 size:0x44
void fn_800B2C44(void) {
    return;
}

// .text:0x800B2C88 size:0x34
void fn_800B2C88(Gap800B117CObj* obj, u16 index, f32 matrix[3][4]) {
    PSMTXCopy(obj->matrices[index], matrix);
}

// .text:0x800B2CBC size:0xA0
void ACTSort(void) {
    return;
}

// .text:0x800B2D5C size:0x74
void fn_800B2D5C(void) {
    return;
}

// .text:0x800B2DD0 size:0x36C
void fn_800B2DD0(void) {
    return;
}

// .text:0x800B313C size:0x378
void fn_800B313C(void) {
    return;
}

// .text:0x800B34B4 size:0x2F0
void fn_800B34B4(void) {
    return;
}

// .text:0x800B37A4 size:0x2D4
void f_BuildBoneSkinOrientationMatrix(void) {
    return;
}

// .text:0x800B3A78 size:0x18C
void fn_800B3A78(void) {
    return;
}

// .text:0x800B3C04 size:0x31C
void fn_800B3C04(void) {
    return;
}

// .text:0x800B3F20 size:0x128
void fn_800B3F20(void) {
    return;
}

// .text:0x800B4048 size:0x3C
void fn_800B4048(void) {
    return;
}

// .text:0x800B4084 size:0x1F4
void fn_800B4084(void) {
    return;
}

// .text:0x800B4278 size:0x128
void fn_800B4278(void) {
    return;
}

// .text:0x800B43A0 size:0x384
void fn_800B43A0(void) {
    return;
}

// .text:0x800B4724 size:0x8
void fn_800B4724(Gap800B117CObj* obj, s32 value) {
    obj->unk7C = value;
}

// .text:0x800B472C size:0x1DC
void fn_800B472C(void) {
    return;
}

// .text:0x800B4908 size:0x8
void haveActLayoutPointToGeoHeader(Gap800B117CObj* obj, s32 value) {
    obj->unk10 = value;
}

// .text:0x800B4910 size:0xD4
void LoadActorLayout(void) {
    return;
}

// .text:0x800B49E4 size:0x60
void fn_800B49E4(void) {
    return;
}

// .text:0x800B4A44 size:0x50
void fn_800B4A44(void) {
    return;
}

// .text:0x800B4A94 size:0x68
void fn_800B4A94(void) {
    return;
}

// .text:0x800B4AFC size:0x3C
void fn_800B4AFC(Gap800B117CObj* obj, u8 value) {
    u32 i;
    for (i = 0; i < obj->count; i++) {
        Gap800B117CAnimation* animation = obj->entries[i]->animation;
        if (animation != NULL) animation->flags18 = value;
    }
}

// .text:0x800B4B38 size:0x90
void AnimateActorBones(void) {
    return;
}

// .text:0x800B4BC8 size:0x3C
void fn_800B4BC8(void) {
    return;
}

// .text:0x800B4C04 size:0x3C
void fn_800B4C04(void) {
    return;
}

// .text:0x800B4C40 size:0x60
void fn_800B4C40(void) {
    return;
}

// .text:0x800B4CA0 size:0x3C
void fn_800B4CA0(void) {
    return;
}

// .text:0x800B4CDC size:0x88
void fn_800B4CDC(void) {
    return;
}

// .text:0x800B4D64 size:0x138
void ACTSetAnimation(void) {
    return;
}

// .text:0x800B4E9C size:0x100
void ANIMGetKeyFrameFromTrack(void) {
    return;
}

// .text:0x800B4F9C size:0x50
void ANIMGetTrackFromSequence(void) {
    return;
}

// .text:0x800B4FEC size:0xA0
void ANIMGetSequence(void) {
    return;
}
