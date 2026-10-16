/* fn_3_1559E4 NONMATCHING (rep_3880.c). All instructions and registers match; the only diff is the
 * stack frame: target frame is 0xC0 with the three int->double conversion slots at 0x98/0xA0/0xA8,
 * ours is 0xB0 with them at 0x90/0x98/0xA0 (target has 8 extra bytes between ctrl (0x50) and the
 * conversion temps). Tried: reordering local decls, a dead/duplicated (f32) conversion (gets the
 * frame to 0xC0 but the slot lands after, not before), s32 rand temps.
 * Header change: include/game/rep_3880.h prototype
 *   void fn_3_1559E4(ListNode_14B9F0* node, Vec* pos, Vec* rot);
 * ListNode_14B9F0 fields used: offset(0x4), scaleX/Y(0x38/0x3C), color[3](0x43), field_0x4A.
 */
typedef struct {
    u8 _pad0[0x8];
    s32 scale;        // 0x08
    u8 _padC[0x4];
    s32 alpha;        // 0x10
    u8 _pad14[0x4];
    s32 field_0x18;   // 0x18
} Struct_26BC0;
extern Vec lbl_3_data_26BB4;
extern Struct_26BC0 lbl_3_data_26BC0;

// .text:0x001559E4 size:0x244 mapped:0x80794A78
void fn_3_1559E4(ListNode_14B9F0* node, Vec* pos, Vec* rot) {
    Control ctrl;
    Mtx m;
    Vec v;
    Vec base;
    f64 ay;

    node->field_0x4A = lbl_3_data_26BC0.field_0x18;
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, rot->x, rot->y, rot->z);
    CTRLBuildMatrix(&ctrl, m);
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        base = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, 1.5f, &base);
    }
    v.x = base.x + 1.5 * ((rand() % 40 - 20) / 100.0);
    v.y = base.y;
    v.z = base.z + 1.5 * ((rand() % 40 - 20) / 100.0);
    PSMTXMultVec(m, &v, &v);
    v.x += pos->x;
    ay = __fabs(pos->y);
    v.y = v.y - ay;
    v.z += pos->z;
    node->offset.x = v.x;
    node->offset.y = v.y;
    node->offset.z = v.z;
    node->scaleY = node->scaleX = (f32)lbl_3_data_26BC0.scale;
    node->color[3] = lbl_3_data_26BC0.alpha;
}
