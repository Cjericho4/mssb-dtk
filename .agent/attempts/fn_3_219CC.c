void fn_3_219CC(void) {
    s32 i;
    s32 cap = g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber];
    u8 n = 0;

    for (i = 0; i < 9; i++) {
        if (cap ==
            g_hugeAnimStruct.AnimationStructPtrs[i]->unk257) {
            g_Fielders[i].unk218 = 0;
        } else {
            n++;
            g_Fielders[i].unk218 = n;
        }
    }
}
