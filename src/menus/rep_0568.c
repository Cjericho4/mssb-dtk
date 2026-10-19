#include "menus/rep_0568.h"
#include "menus/rep_0438.h"
#include "UnknownHeaders.h"
#include "string.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXTransform.h"
extern void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
extern void fn_800BDA94(AnimLevel1** anim, Mtx matrix);

extern f32 lbl_2_rodata_5B8;
extern void ACTSetAnimation(AnimLevel1* actor, s32 bank, s32 sequence, u16 number, f32 blend, f32 time);
extern void fn_800B4CA0(AnimLevel1* actor, f32 time);
extern void fn_800B4C04(AnimLevel1* actor, f32 speed);
extern void fn_800B4AFC(AnimLevel1* actor, u8 loop);
extern void Set_FUN_800b2b6c(AnimLevel1* actor, s32 mode);
extern void fn_800BDA24(MenusRenderAnimation* entry);

// .text:0x00016A98 size:0x248
void fn_2_16A98(void) {
    return;
}

// .text:0x00016CE0 size:0x58
void fn_2_16CE0(void) {
    AnimationStruct* anim;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        anim = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (anim != 0 && anim->animID == 0x6B) lbl_2_bss_100B8.flags[i] = 1;
    }
}

// .text:0x00016D38 size:0x70
void fn_2_16D38(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8.count; i++) {
        memset(g_hugeAnimStruct.fielderStructs[i].aux, 0, 0x5C);
    }
}

// .text:0x00016DA8 size:0x164
void fn_2_16DA8(void) {
    return;
}

// .text:0x00016F0C size:0x6C
void fn_2_16F0C(void) {
    return;
}

// .text:0x00016F78 size:0x6D0
void fn_2_16F78(void) {
    return;
}

// .text:0x00017648 size:0x470
void fn_2_17648(void) {
    return;
}

// .text:0x00017AB8 size:0x1D0
void fn_2_17AB8(void) {
    return;
}

// .text:0x00017C88 size:0x250
void fn_2_17C88(void) {
    return;
}

// .text:0x00017ED8 size:0x270
void fn_2_17ED8(void) {
    return;
}

// .text:0x00018148 size:0x250
void fn_2_18148(void) {
    return;
}

// .text:0x00018398 size:0x2B8
void fn_2_18398(void) {
    return;
}

// .text:0x00018650 size:0xF8
s32 fn_2_18650(s32 index) {
    s32 next = (lbl_2_bss_100B8.writeIndex + 1) % 10;
    if (next != lbl_2_bss_100B8.readIndex) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = (MenusAnimationTask*)fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224->current = 0;
                lbl_2_bss_1224->state = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8.commands[lbl_2_bss_100B8.writeIndex] = index;
        lbl_2_bss_100B8.writeIndex = next;
        lbl_2_bss_100B8.flags[index + 2] = 1;
        return 1;
    }
    return 0;
}

// .text:0x00018748 size:0x1A4
void fn_2_18748(void) {
    return;
}

// .text:0x000188EC size:0x6D0
void fn_2_188EC(void) {
    return;
}

// .text:0x00018FBC size:0xFC
void fn_2_18FBC(void) {
    MenusAnimationTask* task = (MenusAnimationTask*)fn_800B0A5C_insertQueue(fn_2_188EC, 0x6000);
    s32 i;
    lbl_2_bss_100B8.active[5] = 0;
    lbl_2_bss_100B8.active[7] = 1;
    if (lbl_8034E9A0.unk4701 == 0) {
        for (i = 0; i < lbl_2_bss_100B8.count; i++) lbl_2_bss_100B8.selections[i] = -1;
        task->current = 0;
    } else {
        for (i = 0; i < lbl_2_bss_100B8.count; i++) lbl_2_bss_100B8.active[i] = 0;
        task->current = 0;
    }
    lbl_2_bss_100B8.writeIndex = 0;
    lbl_2_bss_100B8.readIndex = 0;
    for (i = 0; i < 10; i++) lbl_2_bss_100B8.commands[i] = -1;
}

// .text:0x000190B8 size:0x24
void fn_2_190B8(Rep0568Obj* obj) {
    fn_800B9AA8(obj->context);
}

// .text:0x000190DC size:0x148
void fn_2_190DC(HugeAnimEntry68* entries, Mtx matrix) {
    return;
}

// .text:0x00019224 size:0x158
void fn_2_19224(MenusRenderList* list) {
    u16 i;
    MenusRenderAnimation* entry;
    for (i=0;i<list->count;i++) {
        AnimationStruct* actor=g_hugeAnimStruct.AnimationStructPtrs[i];
        if (actor != NULL && actor->unk_25D != 0) {
            entry=&list->entries[i];
            if(entry->animation.obj != NULL) {
                if(entry->animation.unk8C) ACTSetAnimation(entry->animation.obj,entry->animation.unk38_s32,0,*(u16*)&entry->animation.unk42,lbl_2_rodata_5B8,entry->blend);
                if(entry->animation.flag59) fn_800B4CA0(entry->animation.obj,entry->time);
                if(entry->animation.flag5a) fn_800B4C04(entry->animation.obj,entry->animation.float54);
                if(entry->animation.flag5b&2) fn_800B4AFC(entry->animation.obj,entry->animation.flag5b&1);
                Set_FUN_800b2b6c(entry->animation.obj,entry->mode);
                if(entry->visible) fn_800BDA24(entry);
                entry->animation.obj->animFlags=1;
                entry->animation.unk8C=0;
                entry->animation.flag59=0;
                entry->animation.flag5a=0;
                entry->animation.flag5b &=1;
            }
        }
    }
}

// .text:0x0001937C size:0x140
void fn_2_1937C(MenusRenderList* list, Mtx matrix) {
    Mtx44 projection;
    u16 i;
    MenusRenderAnimation* entry;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < list->count; i++) {
        AnimationStruct* actor = g_hugeAnimStruct.AnimationStructPtrs[i];
        if (actor != NULL) {
            entry = &list->entries[i];
            if (entry->animation.obj != NULL && entry->visible != 0) {
                f32 x = actor->unk34.x / 1280.0f;
                f32 y = actor->unk34.y / 1280.0f;
                C_MTXFrustum(projection, -0.175f + y, 0.175f + y, 0.25f + x, -0.25f + x, 1.0f, 512.0f);
                GXSetProjection(projection, GX_PERSPECTIVE);
                fn_800BDA94(&entry->animation.obj, matrix);
            }
        }
    }
}
