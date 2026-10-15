#include "game/rep_3090.h"
#include "UnknownHeaders.h"
#include "header_rep_data.h"
#include "stl/mem.h"

// .text:0x000FC448 size:0x4F0 mapped:0x8073B4DC
void fn_3_FC448(void) {
    return;
}

// .text:0x000FC938 size:0x500 mapped:0x8073B9CC
void fn_3_FC938(void) {
    return;
}

// .text:0x000FCE38 size:0x74 mapped:0x8073BECC
s32 fn_3_FCE38(s32 arg0, f32 arg1) {
    Struct_DE94_Inner* p = lbl_3_common_bss_DE94;
    s32 offset = arg0 << 6;
    s32 backOffset;
    s32 count = p->unk3C;

    goto check_forward;

forward_loop:
    offset += 0x40;
    arg0++;

check_forward:
    if (arg0 >= count) {
        goto reset_offset;
    }
    if (arg1 > *(f32*)((u8*)p->unk34 + offset + 0x3C)) {
        goto forward_loop;
    }
    goto check_backward;

backward_loop:
    backOffset -= 0x40;
    arg0--;

check_backward:
    if (arg0 <= 0) {
        return arg0;
    }
    if (arg1 <= *(f32*)((u8*)p->unk34 + backOffset - 4)) {
        goto backward_loop;
    }

    return arg0;

reset_offset:
    backOffset = arg0 << 6;
    goto check_backward;
}

// .text:0x000FCEAC size:0x4 mapped:0x8073BF40
void fn_3_FCEAC(void) {
    return;
}

// .text:0x000FCEB0 size:0x70 mapped:0x8073BF44
extern f64 lbl_3_rodata_3100;
extern s16 lbl_3_bss_B67A[15];

s32 fn_3_FCEB0(f32 arg0) {
    s32 i = 0;
    Struct_DE94_Inner *p = lbl_3_common_bss_DE94;
    if (arg0 < lbl_3_rodata_3100) {
        return -1;
    }
    for (; i < p->unk3C && arg0 > ((DE94ArrayElement *)p->unk34)[i].value; i++) {}
    if (i < p->unk3C) {
        return i;
    }
    return -1;
}

// .text:0x000FCF20 size:0x4 mapped:0x8073BFB4
void fn_3_FCF20(void) {
    return;
}

// .text:0x000FCF24 size:0x4E4 mapped:0x8073BFB8
void fn_3_FCF24(void) {
    return;
}

// .text:0x000FD408 size:0xD4 mapped:0x8073C49C
void fn_3_FD408(u32 idx, VecXYZ* outPos, f32* outVals) {
    Struct_DE94_Inner* p = lbl_3_common_bss_DE94;

    if (p->unk3C > idx) {
        memcpy(outPos, &p->unk34[idx].pos, sizeof(VecXYZ));
        outVals[0] = p->unk34[idx].unkC;
        outVals[1] = p->unk34[idx].unk10;
    } else {
        memcpy(outPos, &p->unk34[p->unk3C - 1].pos, sizeof(VecXYZ));
        outVals[0] = p->unk34[p->unk3C - 1].unkC;
        outVals[1] = p->unk34[p->unk3C - 1].unk10;
    }
}

// .text:0x000FD4DC size:0x40 mapped:0x8073C570

void fn_3_FD4DC(void) {
    // 1. Load the global pointer into r3 once. 
    // This anchors the base address and prevents reloads.
    Struct_DE94_Inner* inner = lbl_3_common_bss_DE94;

    // 2. srwi. r0, r0, 16 triggers the bne .L_000FD508.
    // In MWCC, (u16)(val >> 16) or (val >> 16) in an if condition 
    // usually triggers the dot-record shift.
    if (!(inner->field_0x118 >> 16)) {
        // 3. stw r0, 0x20(r3) <- lwz r0, 0x124(r3)
        inner->field_0x20 = inner->field_0x124;
    }

    // 4. bl fn_3_FCF24
    fn_3_FCF24();
}

// .text:0x000FD51C size:0x8C mapped:0x8073C5B0
void fn_3_FD51C(void) {
    return;
}

// .text:0x000FD5A8 size:0xC8 mapped:0x8073C63C
void fn_3_FD5A8(void) {
    return;
}

// .text:0x000FD670 size:0x38C mapped:0x8073C704
void fn_3_FD670(void) {
    return;
}

// .text:0x000FD9FC size:0x20 mapped:0x8073CA90
u32 fn_3_FD9FC(void) {
    return lbl_3_common_bss_DE94->field_0x18 == 1;
}

// .text:0x000FDA1C size:0x114 mapped:0x8073CAB0
void fn_3_FDA1C(void) {
    return;
}

// .text:0x000FDB30 size:0x24E8 mapped:0x8073CBC4
void fn_3_FDB30(void) {
    return;
}

// .text:0x00100018 size:0x20 mapped:0x8073F0AC
BOOL fn_3_100018(void) {
    return (s32)lbl_3_common_bss_DE94->field_0x9B6 == 1;
}

// .text:0x00100038 size:0x44 mapped:0x8073F0CC
//Simple Register Swap
void fn_3_100038(void) {
    if (lbl_3_common_bss_DE94->field_0x118 > lbl_3_common_bss_DE94->field_0x11C) {
        if (lbl_3_common_bss_DE94->field_0x9B1 == 0) {
            lbl_3_common_bss_DE94->field_0x118 = lbl_3_common_bss_DE94->field_0x11C;
        } else {
            lbl_3_common_bss_DE94->field_0x118 = 0;
        }
    } else {
        lbl_3_common_bss_DE94->field_0x118 += 0x10000;
    }
}

// .text:0x0010007C size:0x5C mapped:0x8073F110
BOOL fn_3_10007C(void) {
    Struct_DE94_Inner* ptr = lbl_3_common_bss_DE94;
    if (ptr->field_0x9AB == 1) {
        if (ptr->field_0x14 != 0) {
            lbl_80366158._28 = 1;
            return FALSE;
        }
        lbl_80366158._28 = 0;
        return TRUE;
    }
    return TRUE;
}

// .text:0x001000D8 size:0x1BEC mapped:0x8073F16C
void fn_3_1000D8(void) {
    return;
}

// .text:0x00101CC4 size:0x1F6C mapped:0x80740D58
void fn_3_101CC4(void) {
    return;
}

// .text:0x00103C30 size:0x24C mapped:0x80742CC4
void fn_3_103C30(void) {
    return;
}

// .text:0x00103E7C size:0x25C mapped:0x80742F10
void fn_3_103E7C(void) {
    return;
}

// .text:0x001040D8 size:0x260 mapped:0x8074316C
void fn_3_1040D8(void) {
    return;
}

// .text:0x00104338 size:0x270 mapped:0x807433CC
void fn_3_104338(void) {
    return;
}

// .text:0x001045A8 size:0x198 mapped:0x8074363C
void fn_3_1045A8(void) {
    return;
}

// .text:0x00104740 size:0x1A0 mapped:0x807437D4
void fn_3_104740(void) {
    return;
}

// .text:0x001048E0 size:0x15C mapped:0x80743974
void fn_3_1048E0(void) {
    return;
}

// .text:0x00104A3C size:0x4C mapped:0x80743AD0

/* --- The Function --- */

/* --- The Function --- */
void fn_3_104A3C(Vec *dst, const Mtx44 mtx) {
    // 0x00104A3C: stwu r1, -0x10(r1)
    // 0x00104A54: mr r31, r3  (dst pointer saved to r31)
    // 0x00104A58: mr r3, r4   (mtx moved to r3)
    
    register Vec *reg_dst = dst;
    
    // 0x00104A4C: addi r0, r5, lbl_3_data_21004@l
    // 0x00104A5C: mr r4, r0   (src vector moved to r4)
    // 0x00104A60: mr r5, r31  (dst vector moved to r5)
    PSMTX44MultVec(mtx, &lbl_3_data_21004, reg_dst);
    
    // 0x00104A68: mr r3, r31
    // 0x00104A6C: mr r4, r31
    PSVECNormalize(reg_dst, reg_dst);
    
    // 0x00104A84: blr
}

// .text:0x00104A88 size:0x4C mapped:0x80743B1C

void fn_3_104A88(Vec *dst, Mtx44 mtx) {
    // Register Steering: Assigning r3 to a local here forces the use of r31
    Vec *v = dst; 

    // Assembly shows:
    // mr r3, r4 (mtx)
    // mr r4, r0 (global vec)
    // mr r5, r31 (dst)
    PSMTX44MultVec(mtx, &lbl_3_data_20FF8, v);

    // PSVECNormalize(v, v);
    // Assembly shows:
    // mr r3, r31
    // mr r4, r31
    PSVECNormalize(v, v);
}

// .text:0x00104AD4 size:0x4C mapped:0x80743B68



void fn_3_104AD4(Vec *dst, Mtx44 mtx) {
    // Register Steering: Assigning the input r3 to a local forces r31 usage
    Vec *v = dst;

    // Call results in: 
    // r3 = mtx, r4 = &global, r5 = v (r31)
    PSMTX44MultVec(mtx, &lbl_3_data_20FEC, v);

    // Call results in:
    // r3 = v (r31), r4 = v (r31)
    PSVECNormalize(v, v);
}

// .text:0x00104B20 size:0x1C mapped:0x80743BB4
void fn_3_104B20(VecXYZ* dst, SourceObj_104B20* src) {
    f32 z = src->pos.z;
    f32 y = src->pos.y;
    f32 x = src->pos.x;
    dst->z = z;
    dst->y = y;
    dst->x = x;
}

// .text:0x00104B3C size:0x990 mapped:0x80743BD0
void fn_3_104B3C(void) {
    return;
}

// .text:0x001054CC size:0x4 mapped:0x80744560
void fn_3_1054CC(void) {
    return;
}

// .text:0x001054D0 size:0x540 mapped:0x80744564
void fn_3_1054D0(void) {
    return;
}

// .text:0x00105A10 size:0xBC mapped:0x80744AA4
void fn_3_105A10(VecXYZ* out, VecXYZ* a, VecXYZ* b, f32 t) {
    VecXYZW result;
    VecXYZW va;
    VecXYZW vb;

    memcpy(&va, a, sizeof(VecXYZ));
    memcpy(&vb, b, sizeof(VecXYZ));
    result.x = va.x * t + vb.x * (lbl_3_rodata_30FC - t);
    result.y = va.y * t + vb.y * (lbl_3_rodata_30FC - t);
    result.z = va.z * t + vb.z * (lbl_3_rodata_30FC - t);
    memcpy(out, &result, sizeof(VecXYZ));
}

// .text:0x00105ACC size:0x10C mapped:0x80744B60
void fn_3_105ACC(Quaternion* q, Mtx out) {
    Mtx44 m;
    f32 xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

    xs = q->x + q->x;
    ys = q->y + q->y;
    zs = q->z + q->z;
    wx = q->w * xs;
    wy = q->w * ys;
    wz = q->w * zs;
    xx = q->x * xs;
    xy = q->x * ys;
    xz = q->x * zs;
    yy = q->y * ys;
    yz = q->y * zs;
    zz = q->z * zs;

    m[0][0] = 1.0f - (yy + zz);
    m[0][1] = xy + wz;
    m[0][2] = xz - wy;
    m[0][3] = 0.0f;
    m[1][0] = xy - wz;
    m[1][1] = 1.0f - (xx + zz);
    m[1][2] = yz + wx;
    m[1][3] = 0.0f;
    m[2][0] = xz + wy;
    m[2][1] = yz - wx;
    m[2][2] = 1.0f - (xx + yy);
    m[2][3] = 0.0f;
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 0.0f;
    m[3][3] = 1.0f;
    memcpy(out, m, sizeof(Mtx));
}

// .text:0x00105BD8 size:0x50 mapped:0x80744C6C
void fn_3_105BD8(Struct_105BD8* arg0) {
    f32 val;
    memset(arg0, 0, 0x88);
    val = lbl_3_rodata_30FC;
    arg0->field_0x3C = val;
    arg0->field_0x28 = val;
    arg0->field_0x14 = val;
    arg0->field_0x00 = val;
    arg0->field_0x40 = val;
}

// .text:0x00105C28 size:0x5C mapped:0x80744CBC
u32 fn_3_105C28(Struct_105C28* arg0, u32 arg1) {
    LookupTable_105C28* tbl = arg0->table;
    u16 lo = (u16)arg1;
    u16 hi = (u16)(arg1 >> 16);
    u16 found = 0;
    u16 count = tbl->count;
    LookupEntry_105C28* entry = tbl->entries;
    LookupEntry_105C28* last;
    do {
        last = entry;
        if (entry->key == hi && lo == 0) {
            found = entry->val;
        }
        if ((++entry)->key > hi) break;
        count--;
    } while ((u16)count != 0);
    return found | ((u32)last->val << 16);
}

// .text:0x00105C84 size:0x58 mapped:0x80744D18
void fn_3_105C84(Fixup_105C84* arg0) {
    u32* table = &arg0->unk8;
    u32* ptr = table;
    s16 i;

    *table += (u32)arg0;
    for (i = 0; i < arg0->unk6; i++) {
        *++ptr += (u32)arg0;
    }
    lbl_3_common_bss_DE94->field_0x11C = (u32)arg0->unk4 << 16;
}

// .text:0x00105CDC size:0x124 mapped:0x80744D70
void fn_3_105CDC(void) {
    return;
}

// .text:0x00105E00 size:0x214 mapped:0x80744E94
void fn_3_105E00(void) {
    return;
}

// .text:0x00106014 size:0xC4 mapped:0x807450A8
void fn_3_106014(f32 x, f32 y, f32 z) {
    VecXYZ* p = lbl_3_common_bss_DE94->field_0x98;

    if (lbl_3_bss_B67A[0] == 0) {
        p[lbl_3_bss_B67A[0]].x = x;
        p[lbl_3_bss_B67A[0]].y = y;
        p[lbl_3_bss_B67A[0]].z = z;
        lbl_3_bss_B67A[0]++;
    } else if (x != p[lbl_3_bss_B67A[0] - 1].x && y != p[lbl_3_bss_B67A[0] - 1].y &&
               z != p[lbl_3_bss_B67A[0] - 1].z) {
        p[lbl_3_bss_B67A[0]].x = x;
        p[lbl_3_bss_B67A[0]].y = y;
        p[lbl_3_bss_B67A[0]].z = z;
        if (lbl_3_bss_B67A[0] < 1000) {
            lbl_3_bss_B67A[0]++;
        }
    }
}

// .text:0x001060D8 size:0xA4 mapped:0x8074516C
void fn_3_1060D8(void) {
    s32 i;
    VecXYZ* p;

    p = lbl_3_common_bss_DE94->field_0x98;
    lbl_3_bss_B67A[0] = 0;
    for (i = 0; i < 1000; i++) {
        p->x = p->y = p->z = -1000.0f;
        p++;
    }
}

// .text:0x0010617C size:0xF4 mapped:0x80745210
void fn_3_10617C(void) {
    return;
}

// .text:0x00106270 size:0x71C mapped:0x80745304
void fn_3_106270(void) {
    return;
}

// .text:0x0010698C size:0x24 mapped:0x80745A20
u32 fn_3_10698C(u32* list) {
    u32 count = 0;
    while (*list != 0) {
        list++;
        count++;
    }
    return count;
}

// .text:0x001069B0 size:0x10 mapped:0x80745A44
void* fn_3_1069B0(void* base, s32 index) {
    s32* offsetTable = (s32*)base;
    return (u8*)base + offsetTable[index];
}

// .text:0x001069C0 size:0x1E0 mapped:0x80745A54
void fn_3_1069C0(void) {
    return;
}

// .text:0x00106BA0 size:0x25C mapped:0x80745C34
void fn_3_106BA0(void) {
    return;
}
