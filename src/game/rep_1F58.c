#include "game/rep_1F58.h"
#include "game/rep_1E08.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXTexture.h"

extern GXTexObj lbl_3_bss_9D20;
extern u8 lbl_3_bss_9D40[0x40];
extern const f32 lbl_3_rodata_1FA8;

typedef struct {
    u8 _pad0[0x20];
    u8 active; /* 0x20 */
} RepC0854Obj;

typedef struct {
    s16 charIndex;
    u8 _pad2[0x1E];
} RepC0854Slot; /* size: 0x20 */

extern RepC0854Obj* lbl_3_data_174A0[2];
extern RepC0854Slot lbl_3_data_17260[18];
void fn_80027918(u8 id, f32 arg1);

// .text:0x000C0854 size:0x108 mapped:0x806FF8E8
void fn_3_C0854(void) {
    s32 i;
    s32 j;
    s16 id;
    AnimationStruct* anim;
    s32 sfx;

    for (i = 0; i < 2; i++) {
        if (lbl_3_data_174A0[i] != NULL) {
            lbl_3_data_174A0[i]->active = 1;
        }
        id = lbl_3_data_17260[i].charIndex;
        if (id >= 0) {
            j = 1;
            do {
                if (id == lbl_3_data_17260[j].charIndex) {
                    break;
                }
            } while (j-- != 0);
            if (j >= 0) {
                anim = g_hugeAnimStruct.AnimationStructPtrs[id];
                if (anim != NULL) {
                    anim->funcPtr_0x5c = NULL;
                }
                sfx = 0x18;
                lbl_3_data_17260[j].charIndex = -1;
                if (j != 0) {
                    sfx = 0x17;
                }
                fn_80027918(sfx, 0.0f);
            }
        }
    }
}

// .text:0x000C095C size:0x17C mapped:0x806FF9F0
void fn_3_C095C(void) {
    return;
}

// .text:0x000C0AD8 size:0x174 mapped:0x806FFB6C
void fn_3_C0AD8(void) {
    return;
}

// .text:0x000C0C4C size:0x9C mapped:0x806FFCE0
void fn_3_C0C4C(void) {
    return;
}

// .text:0x000C0CE8 size:0x28 mapped:0x806FFD7C
void fn_3_C0CE8(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    u32 temp_mask = lbl_3_common_bss_35154.bitfield;
    
    lbl_3_common_bss_35154.unk_434 = arg0;
    temp_mask |= 0x100;
    lbl_3_common_bss_35154.unk_438 = arg1;
    lbl_3_common_bss_35154.unk_43C = arg2;
    lbl_3_common_bss_35154.unk_467 = arg3;
    lbl_3_common_bss_35154.bitfield = temp_mask;
}

// .text:0x000C0D10 size:0xC8 mapped:0x806FFDA4
void fn_3_C0D10(void) {
    return;
}

// .text:0x000C0DD8 size:0x1B4 mapped:0x806FFE6C
void fn_3_C0DD8(void) {
    return;
}

// .text:0x000C0F8C size:0x78 mapped:0x80700020
void fn_3_C0F8C(void) {
    GXInitTexObj(&lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
    GXInitTexObjLOD(&lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
}

// .text:0x000C1004 size:0x1C8 mapped:0x80700098
void fn_3_C1004(void) {
    return;
}

// .text:0x000C11CC size:0x178 mapped:0x80700260
void fn_3_C11CC(s32 arg0, s32 arg1) {
    return;
}

// .text:0x000C1344 size:0x42C mapped:0x807003D8
void fn_3_C1344(s32 arg0, BOOL arg1, f32 arg2, f32 arg3) {
    return;
}

// .text:0x000C1770 size:0x1C0 mapped:0x80700804
void fn_3_C1770(int arg0) {
    return;
}
