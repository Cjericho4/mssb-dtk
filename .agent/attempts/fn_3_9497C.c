/* fn_3_9497C NONMATCHING (rep_16B8.c). Only diff is inside the unrolled j-loop: target computes
 * (scene->unkIndex + J) + E758[i] (lhz r7; lbz r5; addi r0,r7,J; add r0,r5,r0) but MWCC reassociates
 * mine to (E758[i] + J) + unkIndex (lbz first). Explicit unrolled statements give the right load order
 * but add first (unkIndex + E758) + J. Tried: all operand orders, k temp, casts, j types (s32/u32/int/u8/u16/s16),
 * pointer walk over E758, inline helpers (1-arg and 2-arg), j=0..4 with +1. No header changes needed. */
extern u8 lbl_3_data_E758[];

void fn_3_9497C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;
    s32 j;

    if (lbl_3_common_bss_32724.someStatusInd != 0) {
        goto remove;
    }
    if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == 1) {
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + 2].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + 3].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + 4].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + 5].obj->field_0x68 = 1;
    }
    if (scene->eventID == 2) {
        if (lbl_3_common_bss_32724.unk_B4 == 0) {
            goto remove;
        }
    } else if (scene->eventID != 0) {
        if (g_GameLogic.gameStatus != 0x16) {
            goto remove;
        }
    } else {
        if (lbl_3_common_bss_32724.unk_B3 == 0) {
            goto remove;
        }
    }
    if (scene->eventID != 2) {
        for (i = 0; i < scene->unk1a_u16; i++) {
            for (j = 1; j < 6; j++) {
                if ((lbl_80371C30[lbl_3_data_E758[i] + (scene->unkIndex + j)].obj->field_0x5C >> 16) > 0x28) {
                    lbl_80371C30[lbl_3_data_E758[i] + (scene->unkIndex + j)].obj->field_0x5C = 0x3C0000;
                }
            }
        }
    }
    return;
remove:
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
}
