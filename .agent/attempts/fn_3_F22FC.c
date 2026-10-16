/* fn_3_F22FC NONMATCHING (sta_c5.c): only r29/r30 swap between the s8 idx and the &g_Fielders[idx] CSE temp.
 * Header changes needed: see .scratch/fn_3_F22FC.headers.diff (StadiumObjectElem unkAC/B8/BC, Fielder unk217, proto s32). */
extern u8 lbl_3_bss_B21B;
extern u8 lbl_3_bss_B21C;
void fn_800527C4(VecXYZ* pos);

void fn_3_F22FC(StaC5PlacedObj* obj, s32 fielderIdx) {
    Vec dir;
    StadiumObjectElem* elem;
    u32 i;
    s8 idx;

    idx = fielderIdx;
    PSVECSubtract((Vec*)g_Fielders[idx].pos, (Vec*)&obj->pos, &dir);
    dir.y = 0.0f;
    PSVECNormalize(&dir, &dir);
    fn_3_253A4(idx, fn_3_9FB8C(dir.x, dir.z));
    fn_800527C4(&obj->pos);
    for (i = 0; i < lbl_3_bss_B21C; i++) {
        elem = &lbl_3_common_bss_350E4[0].src[lbl_3_bss_B21B + i];
        if (elem->unkC6 == 3 && (s8)elem->unkC1 == (s8)fielderIdx) {
            elem->unkB8 = 0.017453292f * (-elem->unkAC - 180.0f);
            elem->unkC6 = 4;
            elem->unkBC = 0.5f;
            g_Fielders[idx].unk217--;
        }
    }
}
