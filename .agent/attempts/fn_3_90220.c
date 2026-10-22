// Best attempt (14 sbs lines): target computes &pan[arg1] early (add r7) and loads it last before the call, volume via lbzx into r0 then mr r4; every local/pointer ordering tried keeps 14-17 lines.
u32 fn_3_90220(s32 arg0, s32 arg1) {
    u8* panp = &lbl_3_data_8530.pan[arg1];
    u8 pan = *panp;
    SND_VOICEID vid = sndFXStartEx(arg1 + lbl_3_data_8168[arg0], lbl_3_data_8530.volume[arg1], 0x3F, 0);

    sndFXCtrl(vid, 0x5B, pan);
    return vid;
}
