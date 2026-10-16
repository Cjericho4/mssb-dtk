/* fn_3_ECBB0 (gap_EA340.c) NONMATCHING best attempt.
 * Remaining diffs: (1) known-unfixable dead extra "b end" after the 2-case switch dispatch;
 * (2) operand order of the two "add r4,r4,r0" (unkIndex + fieldOrder[n]) is swapped.
 * Needs in gap_EA340.c: extern s32 lbl_3_data_19830[];
 * Note 0x1DF4 is declared s16 targetPointsArray[4] but is written as bytes here.
 */
void fn_3_ECBB0(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    u8* hit = (u8*)g_Minigame.targetPointsArray;
    u32 i;

    if (lbl_3_common_bss_32724.someStatusInd != 0) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
        return;
    }
    if (g_GameLogic.gameStatus == 8) {
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
        return;
    }
    switch (scene->eventID) {
    case 0:
        fn_80034E20(scene, lbl_3_data_19830);
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0xA0000;
        i = 0;
        do {
            lbl_80371C30[i + (scene->unkIndex + 2)].obj->flags &= ~2;
            i++;
        } while (i < 4);
        lbl_80371C30[scene->unkIndex + ((s8)g_Minigame.fieldOrder[0] + 2)].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + ((s8)g_Minigame.fieldOrder[1] + 2)].obj->flags |= 2;
        hit[(s8)g_Minigame.fieldOrder[0]] = 1;
        hit[(s8)g_Minigame.fieldOrder[1]] = 1;
        scene->eventID = 1;
        break;
    case 1:
        g_Minigame._1934 = 2;
        scene->eventID = 2;
        break;
    }
}
