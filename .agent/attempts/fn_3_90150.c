/* extracted from a full-file attempt (m_sound_90150_attempt.c); needs that file's helper types */
u32 fn_3_90150(s32 arg0, s32 arg1) {
    SoundGroupTable* groups = &lbl_3_data_8148.groups;
    VoiceMixTable* vm = &lbl_3_data_8148.voiceMix;
    s32 vol = vm->volume[arg1] * vm->scale;
    s32 pan = vm->pan[arg1] * vm->scale;
    SND_VOICEID vid = sndFXStartEx(arg1 + groups->baseID[arg0], vol, 0x3F, 0);

    sndFXCtrl(vid, 0x5B, pan);
    return vid;
}
