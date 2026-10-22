// Best attempt (2 diff lines): only `addi r4, r30, 0x1c4` is scheduled before `slwi r0, r28, 1` instead of after. Keys: song = tables->songs; song += songIndex; (unfolded 0x798 base), setting = tables->songSettings; setting += songIndex; (lbzx), and no seq local (store the call result to state->_08 and pass state->_08).
s32 fn_3_9056C(s32 songIndex) {
    SoundTables* tables = &lbl_3_data_8148;
    SongEntry* song;
    Struct34C58* state;
    u8 volume;
    SongSettings* setting;

    if (g_d_GameSettings.GameModeSelected != 2) {
        song = tables->songs;
        song += songIndex;
    } else {
        song = tables->practiceSongs;
        song += songIndex;
    }
    state = &lbl_3_common_bss_34C58;
    if (sndSeqGetValid(state->_08) != 0) {
        sndSeqVolume(0, 0, state->_08, 1);
        return 0;
    }
    state->_08 = sndSeqPlayEx(song->seqID, song->groupID, lbl_3_bss_1774[songIndex], 0, 0);
    setting = tables->songSettings;
    setting += songIndex;
    volume = setting->volume;
    lbl_800EF808.musicVolume = volume;
    sndSeqVolume(volume, 0, state->_08, 0);
    return 1;
}
