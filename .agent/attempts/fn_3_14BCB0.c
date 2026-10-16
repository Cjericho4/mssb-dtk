/* fn_3_14BCB0 NONMATCHING (12 diff lines): only float-constant load scheduling differs:
 * target loads 0.5 (addi r7) before the 2.0f (lis r5); ours issues 2.0f first. The 2.0f must be a float
 * variable (lfs + double fmul) — literal 2.0f folds into the 2.0 double. Inline helpers/statement reorders worse.
 * Header: rep_3880.h prototype -> void fn_3_14BCB0(struct Struct_800339F0_Result* obj, Vec* center, u8 flag); */
typedef struct {
    s32 unk0;   // 0x00
    s32 unk4;   // 0x04
    s32 unk8;   // 0x08
    u8 _padC[0x4];
    s32 unk10;  // 0x10
    u8 _pad14[0x8];
    s32 unk1C;  // 0x1C
    s32 unk20;  // 0x20
    s32 unk24;  // 0x24
    s32 unk28;  // 0x28
    u8 _pad2C[0x10];
} Struct_26D88;
extern Struct_26D88 lbl_3_data_26D88;
extern Struct_26D88 lbl_3_data_26DC4;

static inline f32 rep3880_randUnit(void) { return (f32)rand() / 32767.0f; }

// .text:0x0014BCB0 size:0x21C mapped:0x8078AD44
void fn_3_14BCB0(struct Struct_800339F0_Result* obj, Vec* center, u8 flag) {
    Struct_26D88* table;
    ListNode_14B9F0* node;
    u32 count;
    f32 angle;
    f32 radius;
    f32 two = 2.0f;

    obj->field_0x10 = lbl_3_common_bss_32724.field6C;
    count = 0;
    node = obj->listHead;
    if (flag) {
        table = &lbl_3_data_26DC4;
    } else {
        table = &lbl_3_data_26D88;
    }
    do {
        if (node->field_0x4A == 0) {
            node->field_0x4D = table->unk0;
            node->field_0x4E = 0;
            node->field_0x4A = table->unk8;
            node->scaleX = node->scaleY = (f32)table->unk10 / 100000.0f;
            node->color[3] = table->unk28;
            node->color[0] = table->unk1C;
            node->color[1] = table->unk20;
            node->color[2] = table->unk24;
            radius = two * (2.0 * (rep3880_randUnit() - 0.5));
            angle = 0.017453292f * (f32)(180.0 / table->unk4 * count);
            node->offset.x = center->x + radius * (f32)cos(angle);
            node->offset.y = center->y - radius * (f32)sin(angle) - 1.0;
            count++;
            node->offset.z = center->z;
            node->field_0x4F = flag;
        }
        node = node->next;
    } while (node != NULL && count < lbl_3_data_26D88.unk4);
}
