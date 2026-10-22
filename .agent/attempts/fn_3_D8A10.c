// Best attempt (6 diff lines): the j loop over _1918/_1914 needs the target's IV walker (lbz 0x1919(r3); addi r3,r3,1) after a peeled first iteration via r31; ours recomputes addi r3,r31,k. The named `s16 c = lbl_3_data_18BB8.unk4C` local fixed the r8/lha order in the head.
void fn_3_D8A10(void) {
    MiniGameStruct* mg;
    s32 i;
    s32 j;
    s32 id;
    u8 vol;
    u8 pan;
    SND_VOICEID vid;
    s16* pts;
    s16 c;

    mg = &g_Minigame;
    if (mg->_19CE == 1) {
        pts = mg->miniGameLatestPoints;
        pts[mg->rosterID] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk48;
        pts[(s8)mg->minigamePlayerSelectedOrder] += mg->toyField_pointMultiplier * lbl_3_data_18BB8.unk4A;
        c = lbl_3_data_18BB8.unk4C;
        pts[(s8)mg->minigameControlStruct[1].aIStrength[3]] += mg->toyField_pointMultiplier * c;
        pts[(s8)mg->minigameControlStruct[1]._14] += mg->toyField_pointMultiplier * c;
        for (i = 0; i < 4; i++) {
            if (mg->miniGameLatestPoints[i] != 0) {
                mg->minigamePointsPair[i].current = mg->miniGameCurrentPoints[i];
                mg->minigamePointsPair[i].latest = mg->miniGameLatestPoints[i];
            }
        }
        g_Minigame._19BA = 0;
        mg->_19CE = 2;
        for (j = 0; j < 4; j++) {
            if (mg->_1918[j] != 0) {
                mg->_1914[j] = 0;
            }
        }
        if (lbl_800EF808.unk398 == 1) {
            id = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                vol = lbl_3_data_84B8[0][0x34];
            } else {
                vol = lbl_3_data_8404[id][0x34];
            }
            vid = sndFXStartEx(lbl_3_data_81DC[id] + 0x1A, vol, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                pan = lbl_3_data_84B8[0][0x35];
            } else {
                pan = lbl_3_data_8404[id][0x35];
            }
            sndFXCtrl(vid, 0x5B, pan);
        }
    }
    if (g_Minigame._19BA < 0x7FFE) {
        g_Minigame._19BA++;
    } else {
        g_Minigame._19BA = 0x7FFF;
    }
    if (g_Minigame._19BA > lbl_3_data_18C48[3]) {
        mg->_19CE = 3;
    }
}
