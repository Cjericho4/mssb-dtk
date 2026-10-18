#include "menus/rep_0F60.h"
#include "UnknownHeaders.h"
#include "menus/rep_0568.h"
#include "menus/rep_10C0.h"

extern hugeAnimStruct* lbl_2_bss_340140;
extern f32 lbl_2_rodata_FB4;

// .text:0x0008ACE0 size:0x200
void fn_2_8ACE0(void) {
    return;
}

// .text:0x0008AEE0 size:0x238
void fn_2_8AEE0(void) {
    return;
}

// .text:0x0008B118 size:0x40
void fn_2_8B118(f32 value) {
    if (value != lbl_2_rodata_FB4) lbl_2_bss_340140->field269_0x307a = 3;
    else lbl_2_bss_340140->field269_0x307a = 0;
}

// .text:0x0008B158 size:0x168
void fn_2_8B158(void) {
    return;
}

// .text:0x0008B2C0 size:0x158
void fn_2_8B2C0(void) {
    return;
}

// .text:0x0008B418 size:0x130C
void fn_2_8B418(void) {
    return;
}

// .text:0x0008C724 size:0xE8
void fn_2_8C724(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_340140->field268_0x3078; i++) {
        lbl_2_bss_340140->entries_2D94[i].pos.x = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].pos.y = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].pos.z = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].vel.x = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].vel.y = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].vel.z = 0.0f;
        lbl_2_bss_340140->entries_2D94[i].unk_26 = 0;
        lbl_2_bss_340140->entries_2D94[i].callback = NULL;
        lbl_2_bss_340140->entries_68[i + 1].unk10 = 0;
    }
}

// .text:0x0008C80C size:0x104
void fn_2_8C80C(void) {
    return;
}

// .text:0x0008C910 size:0x378
void fn_2_8C910(void) {
    return;
}

// .text:0x0008CC88 size:0x24
BOOL fn_2_8CC88(s32 index) {
    return g_hugeAnimStruct.AnimationStructPtrs[index]->unk68 == 0;
}

// .text:0x0008CCAC size:0x20
void fn_2_8CCAC(s32 index, u8 value) {
    AnimationStruct* obj = &lbl_2_bss_340140->fielderStructs[index];
    if (obj != NULL) obj->unk_25D = value;
}

// .text:0x0008CCCC size:0x8C
void fn_2_8CCCC(s32 index, s32 animation, u8 flag, u8 mode, u8 value263, s16 value6C, u8 value266, s32 value26A) {
    AnimationStruct* anim = lbl_2_bss_340140->AnimationStructPtrs[index];
    if (anim == 0) return;
    if (mode == 1 && anim->animID == animation) return;
    if (mode == 3) mode = 1;
    anim->nextAnim = animation;
    anim->unk6C = value6C;
    anim->unk260 = flag;
    anim->unk25E = mode;
    anim->unk263 = value263;
    anim->unk266 = value266;
    anim->unk26D = 0;
    if (value26A == -1) anim->unk26A = 5;
    else anim->unk26A = value26A;
    anim->unk66 = -1;
}

// .text:0x0008CD58 size:0x2CC
void fn_2_8CD58(s32 index, s32 animation, u8 flag, u8 mode, s16 time, u8 value266, u8 duration) {
    return;
}

// .text:0x0008D024 size:0x228
void fn_2_8D024(void) {
    return;
}

// .text:0x0008D24C size:0x24
void fn_2_8D24C(Rep0568Obj* obj) {
    fn_800B9AA8(obj->context);
}

// .text:0x0008D270 size:0x76C
void fn_2_8D270(void) {
    return;
}

// .text:0x0008D9DC size:0x138
void fn_2_8D9DC(void) {
    return;
}

// .text:0x0008DB14 size:0xEC
void fn_2_8DB14(void) {
    u32 maxSize = 0;
    s32 i;
    for (i = 0; i < lbl_2_bss_1A824C->objectCount; i++) {
        u32 size = lbl_2_data_2F990[i].size & 0x0FFFFFFF;
        if (maxSize < size) maxSize = size;
    }
    maxSize = (maxSize + 31) & ~31;
    lbl_2_bss_340140->field112_0x2c90 = maxSize;
    lbl_2_bss_340140->animBankPtr = _OSAllocFromHeap(0x20, maxSize * lbl_2_bss_1A824C->objectCount);
    for (i = 0; i < lbl_2_bss_1A824C->objectCount; i++) {
        lbl_2_bss_340140->fielderStructs[i].slots[0] = NULL;
    }
}

// .text:0x0008DC00 size:0xD8
void fn_2_8DC00(void) {
    return;
}

// .text:0x0008DCD8 size:0x2D8
void fn_2_8DCD8(void) {
    return;
}

// .text:0x0008DFB0 size:0x4C8
void fn_2_8DFB0(void) {
    return;
}

// .text:0x0008E478 size:0x22C
void fn_2_8E478(void) {
    return;
}
