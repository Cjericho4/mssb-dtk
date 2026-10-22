// Best attempt (10 diff lines, regalloc only): rand() % 4096 reproduces the slwi/srwi/rotlwi tail. Target inits the 0x28-stride IV with `li r29,0; mr r27,r29` (i=r29, IV=r27, entry=r28); every for/do-while/inline/dual-counter form gives two `li` with i/IV regs swapped.
void fn_3_E1964(void) {
    HugeAnimEntry2D94* entry;
    s32 i;

    i = 0;
    do {
        entry = &g_hugeAnimStruct.entries_2D94[i];
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        entry->vel.y = shortAngleToRad_Capped(rand() % 4096);
    } while (++i < 0x1E);
}
