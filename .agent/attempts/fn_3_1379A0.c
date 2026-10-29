// 13 floating-register diff entries in the horizontal distance tests; needs headers patch and extern u8 lbl_3_bss_B780.
// .text:0x001379A0 size:0x170 mapped:0x80776A34
// Test whether a non-active Wall Ball fielder overlaps a moving target.
BOOL fn_3_1379A0(s32 fielderIndex) {
    Fielder* fielder = &g_Fielders[fielderIndex];
    u32 player;
    u32 i;
    for (player = 0; player < 4; player++) {
        if (g_Minigame.minigameFielderIndex[player] == fielderIndex) {
            break;
        }
    }
    if (player == (u32)(s8)g_Minigame._1D6D) {
        return FALSE;
    }
    for (i = 0; i < lbl_3_bss_B780; i++) {
        MiniGamePosElement* target = &g_Minigame.unkBB0[i];
        if (target->unk3D == 3 || target->unk3D == 5) {
            f32 height = fielder->unk15C + (fielder->unk_0x0C + fielder->pos[1]);
            f32 tolerance;
            f32 dz;
            f32 dx;
            if (height < target->unk4) {
                tolerance = fielder->unk_0x16C;
            } else {
                tolerance = 12.0f;
            }
            if (!(tolerance < fabs(height - target->unk4))) {
                dz = fabs(target->_08 - (fielder->pos[2] + fielder->unk34));
                dx = fabs(target->_00 - (fielder->pos[0] + fielder->unk30));
                if (dx < 3.5f && dz < 3.125f) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

