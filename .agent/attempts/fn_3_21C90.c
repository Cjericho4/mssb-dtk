/* fn_3_21C90 NONMATCHING: only diff is a dead 'b end' after the switch dispatch (cmpwi 1; beq; bge; cmpwi 0; bge; b; b).
 * Tried default:break/return (first & last), case reorder, returns, local switch var. Same dead-b pattern in 22 unmatched fns, none matched.
 * Needs: header carves in .scratch/fn_3_21C90.headers.diff (Camera unkAA8/AAA/AAC/AAE, Lbl803C5090 unk0/14/17-1C,
 * DrawingSceneStruct u16 unk20_u16 alias), plus in rep_A00.c: #include "game/sta_c5.h", extern s32 lbl_3_bss_A0; */
void fn_3_21C90(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;

    switch (lbl_3_bss_A0) {
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
        lbl_803C5090.unk17 = scene->unk20_u16;
        lbl_3_bss_A0++;
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
        lbl_803C5090.unk17 = scene->unk20_u16;
        scene->fielderIndex++;
        if (g_pCamera->unkAAC <= scene->fielderIndex) {
            g_pCamera->unkAA8 = 0;
            fn_800B0A14_removeQueue();
            lbl_3_bss_A0 = 0;
        } else {
            scene->unk_20 = 0xFF - (scene->fielderIndex * 0xFF) / g_pCamera->unkAAC;
        }
        break;
    }
}
