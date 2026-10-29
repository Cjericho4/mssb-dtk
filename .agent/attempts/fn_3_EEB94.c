// Two diff entries: addi r6,r26,1 scheduled four instructions late; needs accompanying support patch.
// .text:0x000EEB94 size:0x160 mapped:0x8072DC28
// Animate the two channels of the stadium's 16-by-16 distortion texture.
void fn_3_EEB94(void) {
    u32 y;
    s8* direction;
    s8* secondDirection;
    u32 x;
    s32 first;
    s32 second;
    s32 offset;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            offset = fn_800247E4(x, y, 16, 2);
            first = lbl_3_bss_B118[offset];
            second = lbl_3_bss_B118[offset + 1];
            first += (rand() % 14 + 8) * (direction = &lbl_3_bss_AF18[offset])[0];
            second += (rand() % 14 + 8) * direction[1];
            secondDirection = &direction[1];
            if (first >= 227) {
                first--;
                direction[0] = -1;
            } else if (first <= 27) {
                first++;
                direction[0] = 1;
            }
            if (second >= 227) {
                second--;
                *secondDirection = -1;
            } else if (second <= 27) {
                second++;
                *secondDirection = 1;
            }
            lbl_3_bss_B118[offset] = first;
            lbl_3_bss_B118[offset + 1] = second;
        }
    }
}

