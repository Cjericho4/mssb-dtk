/* fn_3_105E00 (rep_3090.c) NONMATCHING best attempt.
 * With s32 x/y params (below) the callee only differs in register numbering in the vertex block (r7 vs r5 for 0xCC01,
 * li ordering for the color bytes). With the existing s16 prototype the callee gets extra `extsh` before
 * x+w / y+h, but switching to s32 breaks the matched caller fn_3_105CDC (it then needs `(s16)` casts and its
 * mulhw/addi scheduling shifts by one instruction; tried s16 locals/expression orders in the caller).
 * Likely the real signature is s16 and the vertex writes go through some inline that truncates first.
 * Needs `#include "Dolphin/gx.h"` in rep_3090.c and fn_3_105E00.headers.diff (prototype).
 * The caller line used: fn_3_105E00((s16)(x / 50 + 150), (s16)(-z / 50 + 400), 2, 2);
 */
static inline void rep3090Pos2s16(s16 x, s16 y) {
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
}

// .text:0x00105E00 size:0x214 mapped:0x80744E94
void fn_3_105E00(s32 x, s32 y, s32 w, s32 h) {
    Mtx44 proj;
    Mtx mv;

    C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, -100.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mv);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGBA8, 0);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y;
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXWGFifo.s16 = x + w;
    GXWGFifo.s16 = y;
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXWGFifo.s16 = x + w;
    GXWGFifo.s16 = y + h;
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXWGFifo.s16 = x;
    GXWGFifo.s16 = y + h;
    GXColor4u8(0, 0xFF, 0, 0xC8);
}
