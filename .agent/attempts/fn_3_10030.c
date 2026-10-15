/* best attempt fn_3_10030: 4 mismatches (add operand pairing: target adds t+half first, then +frame, then +rand*16).
   Needs in gap_FF4C.c: #include "UnknownHeaders.h" and extern u32 lbl_3_data_228; */
void fn_3_10030(void) {
    s32 t;

    t = (lbl_3_data_228 % 10 + 1) * (g_Ball.StaticRandomInt1 * rand());
    g_Ball.StaticRandomInt1 = (rand() * 16 + t + lbl_3_data_228 / 2 + g_d_GameSettings.FrameCountWhileNotAtMainMenu) & 0x7FFF;
    t = (lbl_3_data_228 % 10 + 1) * ((g_Ball.StaticRandomInt2 + 1) * rand());
    g_Ball.StaticRandomInt2 = (rand() * 8 + t + lbl_3_data_228 / 2 + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1)) & 0x7FFF;
}
