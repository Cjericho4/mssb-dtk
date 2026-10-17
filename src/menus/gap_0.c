#include "menus/gap_0.h"
#include "game/rep_1E08.h"

extern BdcArrayElement lbl_2_data_C0;
#include "menus/gap_D08.h"
#include "UnknownHeaders.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"

// .text:0x00000000 size:0x3C
void fn_2_0(void) {
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

// .text:0x0000003C size:0x2C
void fn_2_3C(void) {
    fn_800A7D4C(0, &lbl_2_data_C0);
}

// .text:0x00000068 size:0x20
void _epilog(void) {
    return;
}

// .text:0x00000088 size:0x88
void _prolog(void) {
    return;
}

// .text:0x00000110 size:0x50
void fn_2_110(void) {
    u8 i = 0;
    while (i < 2) {
        if (lbl_803CBBCC->flags & (1 << i)) lbl_803CBBCC->input[i] = 0;
        i++;
    }
}

// .text:0x00000160 size:0x48
void fn_2_160(void) {
    lbl_803CBBCC->input[0] |= lbl_803C77B8.buttons;
    lbl_803CBBCC->input[1] |= lbl_803C77B8.otherButtons;
    lbl_803CBBCC->flags = 0;
}

// .text:0x000001A8 size:0x130
void fn_2_1A8(void) {
    return;
}

// .text:0x000002D8 size:0x4
void fn_2_2D8(void) {
    return;
}

// .text:0x000002DC size:0x4C
void fn_2_2DC(void) {
    MenusCommandQueue* queue = lbl_2_bss_4;
    u8 next = (queue->writeIndex + 1) % 32;
    if (next != queue->readIndex) {
        queue->writeIndex = next;
        queue->commands[queue->writeIndex] = 2;
    }
}

// .text:0x00000328 size:0x4C
void fn_2_328(void) {
    MenusCommandQueue* queue = lbl_2_bss_4;
    u8 next = (queue->writeIndex + 1) % 32;
    if (next != queue->readIndex) {
        queue->writeIndex = next;
        queue->commands[queue->writeIndex] = 1;
    }
}

// .text:0x00000374 size:0x150
void fn_2_374(void) {
    return;
}

// .text:0x000004C4 size:0x4C
BOOL fn_2_4C4(MenusCommandQueue* queue, u8 command) {
    u8 next = (queue->writeIndex + 1) % 32;
    if (next == queue->readIndex) return FALSE;
    queue->writeIndex = next;
    queue->commands[queue->writeIndex] = command;
    return TRUE;
}

// .text:0x00000510 size:0x44
u8 fn_2_510(MenusCommandQueue* queue) {
    if (queue->readIndex == queue->writeIndex) return 0;
    queue->readIndex = (queue->readIndex + 1) % 32;
    return queue->commands[queue->readIndex];
}

// .text:0x00000554 size:0x110
void fn_2_554(void) {
    return;
}

// .text:0x00000664 size:0xA4
void fn_2_664(void) {
    return;
}

// .text:0x00000708 size:0x8C
void fn_2_708(void) {
    return;
}

// .text:0x00000794 size:0x1AC
void fn_2_794(void) {
    return;
}

// .text:0x00000940 size:0x38
void fn_2_940(void) {
    if (lbl_803CBBCC->unk0 == 5) fn_800B0A14_removeQueue();
}

// .text:0x00000978 size:0x9C
void fn_2_978(void) {
    return;
}

// .text:0x00000A14 size:0x5C
void fn_2_A14(void) {
    return;
}
