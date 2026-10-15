void fn_3_EA340(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 i;
    s32 v;
    s32 off;

    fn_80034E20(scene, &lbl_3_data_900C);
    off = 3;
    for (i = 0; i < 3; i++) {
        if (g_Minigame.players.fielderRosterIDs[i] >= 0) {
            v = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.players.fielderRosterIDs[i]] << 16;
            lbl_80371C30[scene->unkIndex + i + off].obj->field_0x5C = v;
            lbl_80371C30[scene->unkIndex + i + off * 2].obj->field_0x5C = v;
            lbl_80371C30[scene->unkIndex + i + off * 3].obj->field_0x5C = inMemRoster[0][g_Minigame.players.fielderRosterIDs[i]].stats.CharID << 16;
        }
    }
    scene->unk18 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_3_E9D30;
}
