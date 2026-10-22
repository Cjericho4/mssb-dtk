// Best attempt (9 sbs lines, from a stub): logic matches; target keeps the scene pointer in r3 from the first lwz through to `bl fn_80034CEC` (no arg setup), i.e. the original call passes nothing and r3 happens to hold scene; with the prototyped fn_80034CEC(u32) we must pass (u32)scene which loads it into r6 + mr r3.
void fn_3_ED058(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    scene->unk18++;
    if (lbl_3_common_bss_32724.someStatusInd == 0) {
        if (g_GameLogic.gameStatus == 2 || g_GameLogic.gameStatus == 1) {
            if (lbl_80371C30[scene->unkIndex].obj->field_0x69 != 2) {
                return;
            }
        }
    }
    fn_80034CEC((u32)scene);
    fn_800B0A14_removeQueue();
    g_Minigame._19CD = 3;
}
