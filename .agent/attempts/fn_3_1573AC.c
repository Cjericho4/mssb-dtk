/* fn_3_1573AC NONMATCHING: hits Known Unfixable 'same-file static data off one base register'.
 * Target keeps &lbl_3_data_266A8 in r31 for the whole function (across calls) and addresses the
 * 0x13C/0x23C/0x254 sub-arrays off it (addi r29,r31,0x23c etc.); every C form (direct global, overlay
 * pointer local, register, inline param) gets the address copy-propagated and rematerialized after calls.
 * Logic is believed correct. Needs: AnimationStruct.unk255 (s8, carved from _rest255 in UnknownHeaders.h),
 * prototype void fn_3_1573AC(struct AnimationStruct* anim) in rep_3880.h. */
typedef struct {
    s32 unk0; // 0x0
    s32 unk4; // 0x4
} Struct_80030D88_Target;

void fn_80030D88(VecXYZ* pos, Vec* dir, Struct_80030D88_Target* target, s32 arg3);

typedef struct {
    s16 unk0; // 0x0
    s16 unk2; // 0x2
} Struct_266A8_13C;

typedef struct {
    s32 x; // 0x0
    s32 y; // 0x4
    s32 z; // 0x8
} Struct_266A8_254;

// Overlay of the file's static data block starting at lbl_3_data_266A8
typedef struct {
    u8 _pad0[0x13C];
    Struct_266A8_13C unk13C[64];         // 0x13C
    Struct_80030D88_Target* unk23C[3];   // 0x23C
    u8 _pad248[0xC];
    Struct_266A8_254 unk254[1];          // 0x254
} Data_266A8;
extern Data_266A8 lbl_3_data_266A8;


void fn_3_1573AC(AnimationStruct* anim) {
    Control ctrl;
    Mtx m;
    VecXYZ pos;
    Vec dir;
    Data_266A8* d;
    Struct_266A8_254* tbl;
    Struct_80030D88_Target** targets;
    s32 val;
    s32 idx;

    d = &lbl_3_data_266A8;
    idx = anim->unk252;
    tbl = d->unk254;
    pos.x = (f32)tbl[idx].x / 100000.0f;
    pos.y = (f32)tbl[idx].y / 100000.0f;
    pos.z = (f32)tbl[idx].z / 100000.0f;
    fn_8001B728(anim->unk255, 4, &pos);
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, anim->unk40.x, anim->unk40.y, anim->unk40.z);
    CTRLBuildMatrix(&ctrl, m);
    dir.z = 1.0f;
    dir.x = dir.y = 0.0f;
    PSMTXMultVec(m, &dir, &dir);
    targets = d->unk23C;
    targets[0]->unk0 = targets[1]->unk0 = targets[2]->unk0 = lbl_3_common_bss_32724.field6C;
    targets[0]->unk4 = targets[1]->unk4 = d->unk13C[anim->unk254].unk2;
    fn_80030D88(&pos, &dir, targets[0], 0x29);
    fn_80030D88(&pos, &dir, targets[1], 0x29);
    fn_80030D88(&pos, &dir, targets[2], 0x29);
}

