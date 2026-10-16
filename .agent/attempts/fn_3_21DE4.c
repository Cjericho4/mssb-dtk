/* fn_3_21DE4 NONMATCHING: same as fn_3_21C90 - only the dead 'b end' after switch dispatch differs.
 * Needs header carves from .scratch/fn_3_21C90.headers.diff, plus #include "game/sta_c5.h", extern s32 lbl_3_bss_9C; in rep_A00.c */
void fn_3_21DE4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    switch (lbl_3_bss_9C) {
    case 0:
        scene->fielderIndex = 0;
        scene->unk_20 = 0xFF;
        lbl_803C5090.unk1D = 9;
        lbl_803C5090.unk0 = 1.0f;
        lbl_803C5090.unk14 = 0x1C0;
        lbl_803C5090.unk19 = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.unk1A = 0xFF;
        lbl_803C5090.unk1B = 0xFF;
        lbl_803C5090.unk1C = 0xFF;
        lbl_803C5090.unk17 = 0xFF;
        lbl_3_bss_9C++;
        break;
    case 1:
        lbl_803C5090.unk1D = 8;
        lbl_803C5090.unk0 = 1.0f;
        lbl_803C5090.unk14 = 0x1C0;
        lbl_803C5090.unk19 = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.unk1A = 0xFF;
        lbl_803C5090.unk1B = 0xFF;
        lbl_803C5090.unk1C = 0xFF;
        lbl_803C5090.unk17 = 0xFF;
        scene->fielderIndex++;
        if (g_pCamera->unkAAE <= scene->fielderIndex) {
            g_pCamera->unkAAA = 0;
            fn_800B0A14_removeQueue();
            lbl_3_bss_9C = 0;
        }
        break;
    }
}
