#include "menus/rep_0DE0.h"
#include "UnknownHeaders.h"
#include "menus/rep_08E8.h"
#include "game/rep_1E08.h"

extern void fn_800BDA94(AnimLevel1** anim, Mtx matrix);
#include "menus/rep_0568.h"
#include "Dolphin/GX/GXTransform.h"
extern Mtx lbl_2_bss_1A81D4;
extern MenusDisplayConfig lbl_2_data_2E9B4[];
extern void C_MTXFrustum(Mtx44 matrix, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);

extern void LITXForm(MenusLight* light, Mtx matrix);

#include "string.h"
extern Vec lbl_2_data_2E9D0;
extern Vec lbl_2_data_2E9C4;
extern f32 lbl_2_bss_B29C;

extern hugeAnimStruct* lbl_2_bss_340140;
extern f32 lbl_2_rodata_E88;

// .text:0x0008563C size:0x268
void fn_2_8563C(void) {
    return;
}

// .text:0x000858A4 size:0x21C
void fn_2_858A4(void) {
    return;
}

// .text:0x00085AC0 size:0x2AC
void fn_2_85AC0(void) {
    return;
}

// .text:0x00085D6C size:0x704
void fn_2_85D6C(Mtx matrix) {
    return;
}

// .text:0x00086470 size:0x458
void fn_2_86470(void) {
    return;
}

// .text:0x000868C8 size:0xEC
void fn_2_868C8(void) {
    HugeAnimEntry2D94* entry = lbl_2_bss_340140->entries_2D94;
    Vec position;
    Vec delta;
    memcpy(&position, &entry->pos, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_2E9D0, &delta);
    delta.x *= -1.0f;
    delta.z *= -1.0f;
    if (delta.x != 0.0f || delta.z != 0.0f) {
        lbl_2_bss_B29C = fn_2_4A1E8(delta.z, delta.x);
    }
    memcpy(&lbl_2_data_2E9D0, &entry->pos, sizeof(Vec));
    entry->pos.x = position.x;
    entry->pos.y = position.y;
    entry->pos.z = position.z;
    entry->vel.x = lbl_2_data_2E9C4.x;
    entry->vel.y = lbl_2_bss_B29C;
    entry->vel.z = lbl_2_data_2E9C4.z;
}

// .text:0x000869B4 size:0x58
void fn_2_869B4(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_340140->field268_0x3078; i++) {
        HugeAnimEntry2D94* entry = &lbl_2_bss_340140->entries_2D94[i];
        entry->pos.x = 0.0f;
        entry->pos.y = 0.0f;
        entry->pos.z = 0.0f;
        entry->vel.x = 0.0f;
        entry->vel.y = 0.0f;
        entry->vel.z = 0.0f;
    }
}

// .text:0x00086A0C size:0x74
void fn_2_86A0C(void) {
    s32 i = 0;
    do {
        Fn52768Result* camera = fn_80052768(0);
        LITXForm(lbl_2_bss_340140->menuLights[i], camera->mtx);
        i++;
    } while (i < 3);
}

// .text:0x00086A80 size:0x34C
void fn_2_86A80(void) {
    return;
}

// .text:0x00086DCC size:0x174
void fn_2_86DCC(void) {
    return;
}

// .text:0x00086F40 size:0xAC
void fn_2_86F40(void) {
    AnimLevel1** anim;
    s32 i;
    for (i = 0; i < g_hugeAnimStruct.entries_68->count; i++) {
        anim = &g_hugeAnimStruct.entries_68[i].unk34;
        if (*anim && g_hugeAnimStruct.entries_68[i + 1].unk10) {
            if (g_hugeAnimStruct.entries_2D94[i].callback) g_hugeAnimStruct.entries_2D94[i].callback(i);
            fn_800BDA94(anim, fn_80052768(0)->mtx);
        }
    }
}

// .text:0x00086FEC size:0xE8
void fn_2_86FEC(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_2_48D54();
    fn_2_86470();
    fn_2_85D6C(lbl_2_bss_1A81D4);
    PSMTXCopy(lbl_2_bss_1A81D4, fn_80052768(0)->mtx);
    fn_800A7D4C(0, (BdcArrayElement*)&lbl_2_data_2E9B4[lbl_803CBBC0]);
    fn_2_190DC(lbl_2_bss_340140->entries_68, fn_80052768(0)->mtx);
}

// .text:0x000870D4 size:0x40
void fn_2_870D4(f32 value) {
    if (value != lbl_2_rodata_E88) lbl_2_bss_340140->field269_0x307a = 3;
    else lbl_2_bss_340140->field269_0x307a = 0;
}

// .text:0x00087114 size:0x4
void fn_2_87114(void) {
    return;
}

// .text:0x00087118 size:0x238
void fn_2_87118(void) {
    return;
}

// .text:0x00087350 size:0x304
void fn_2_87350(void) {
    return;
}

// .text:0x00087654 size:0x1D8
void fn_2_87654(void) {
    return;
}
