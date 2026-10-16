#include "game/gap_6A160.h"
#include "UnknownHeaders.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1E08.h"

// .text:0x0006A160 size:0xF0 mapped:0x806A91F4
void fn_3_6A160(void) {
    s32 type;

    if (g_Ball.framesSinceHit != 0) {
        return;
    }
    if (lbl_3_common_bss_35154.bitfield & 3) {
        return;
    }
    if (g_Batter.captainStarSwingActivated != 0 || g_Batter.didNonCaptainStarSwingConnect != 0) {
        type = 4;
    } else if (g_Batter.hitGeneralType == 3) {
        type = 0;
    } else if (g_Batter.displayContactSprite != 0) {
        type = 3;
    } else if (g_Batter.contactType == 2) {
        type = 2;
    } else {
        type = 1;
    }
    if (g_Batter.batterHand == 0) {
        fn_3_BE174(type, g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
    } else {
        fn_3_BE174(type, -g_Batter.hitContactPos.x, -g_Batter.hitContactPos.y, g_Batter.hitContactPos.z);
    }
}

// .text:0x0006A250 size:0x4 mapped:0x806A92E4
void fn_3_6A250(void) {
    return;
}

// .text:0x0006A254 size:0x4 mapped:0x806A92E8
void fn_3_6A254(void) {
    return;
}

// .text:0x0006A258 size:0x4 mapped:0x806A92EC
void fn_3_6A258(void) {
    return;
}

// .text:0x0006A25C size:0x48 mapped:0x806A92F0
void fn_3_6A25C(void) {
    if (g_hugeAnimStruct.starAnimRelated != NULL) {
        g_hugeAnimStruct.starAnimRelated[17].visible = 0;
        g_hugeAnimStruct.starAnimRelated[18].visible = 0;
        g_hugeAnimStruct.starAnimRelated[19].visible = 0;
        g_hugeAnimStruct.starAnimRelated[20].visible = 0;
    }
    lbl_3_common_bss_32724.someFlag = 0;
}

