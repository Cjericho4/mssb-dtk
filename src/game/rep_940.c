#include "game/rep_940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

static const f32 lbl_3_rodata_990 = 0.0f;

// .text:0x00020CEC size:0x164 mapped:0x8065FD80
s32 fn_3_20CEC(f32 rate) {
    f32 dx;
    s32 frames;

    if (g_Ball.pitchHangtimeCounter <= 1) {
        return 0;
    }
    if (lbl_3_rodata_990 == rate) {
        return 0;
    }
    dx = g_AiLogic.aiPitchCurveEndingX - g_Pitcher.pitchXPosition2;
    if (g_AiLogic.pitchAIDelayCurveStart != 0) {
        frames = g_Pitcher.frameWhenUnhittable - g_Ball.pitchHangtimeCounter;
        if (frames <= 0) {
            return 0;
        }
        rate *= frames / 2 * frames;
        if (dx < lbl_3_rodata_990) {
            if (-dx < rate) {
                return 0;
            }
        } else if (dx < rate) {
            return 0;
        }
        g_AiLogic.pitchAIDelayCurveStart = 0;
    }
    if (dx > 0.03f) {
        if (g_AiLogic.aiPitchDirectionInput == -1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = 1;
        return 1;
    } else if (dx < -0.03f) {
        if (g_AiLogic.aiPitchDirectionInput == 1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = -1;
        return -1;
    }
    return 0;
}

// .text:0x00020E50 size:0x9C mapped:0x8065FEE4
void fn_3_20E50(void) {
    return;
}

// .text:0x00020EEC size:0xC4 mapped:0x8065FF80
void fn_3_20EEC(void) {
    return;
}

// .text:0x00020FB0 size:0x2F0 mapped:0x80660044
void fn_3_20FB0(void) {
    return;
}

// .text:0x000212A0 size:0x30C mapped:0x80660334
void fn_3_212A0(void) {
    return;
}

// .text:0x000215AC size:0x1BC mapped:0x80660640
void fn_3_215AC(void) {
    return;
}

// .text:0x00021768 size:0x238 mapped:0x806607FC
void fn_3_21768(void) {
    return;
}

// .text:0x000219A0 size:0x2C mapped:0x80660A34
void fn_3_219A0(void) {
    // The float reference must come first to trigger the lis r3, rodata@ha
    f32 val = lbl_3_rodata_990;

    g_AiLogic.nStarPitchesThrownThisAB = 0;
    g_AiLogic.aIMoundLocationX = val;
    g_AiLogic.aIMoundLocationIndex = 2;
    g_AiLogic.always0_AIPickoffRelated = 0;
}
