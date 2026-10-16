/* fn_3_EE96C NONMATCHING (src/game/sta_c5.c). Everything matches up to PSMTXCopy (incl. f30/f31 alloc, stack slots).
   Remaining: tail scheduling. Target stores indMtx[1][1] through a separate pointer (addi r3,r31,0x23c; stfs 0x10(r3))
   while [0][0] is stored as 0x23c(r31); MWCC folds both (tried row pointer local, no temp, extern 0.5f, static inline Mtx23 setter for [1][1]). Also target
   loads 0.2f and 1.0 via addi+lfs 0(rX) form (likely a consequence of the same scheduling).
   Needs includes Dolphin/GX/GXTexture.h + Dolphin/OS/OSCache.h and header carve in .scratch/fn_3_EE96C.headers.diff. */
CameraView* fn_80052768(s32 arg0);

void fn_3_EE96C(Vec* pos) {
    StaC5Bss_AEE0* bss = &lbl_3_bss_AEE0;
    Mtx m;
    Vec dir;
    Vec ref = {0.0f, -1.0f, 0.0f};
    CameraView* cam;
    f32 clamped;
    f32 dist;
    f32 scale;
    f32 t;
    s32 sScale;
    s32 tScale;

    cam = fn_80052768(fn_8005268C());
    PSVECSubtract(&cam->pos, &cam->target, &dir);
    if (PSVECMag(&dir)) {
        PSVECNormalize(&dir, &dir);
    } else {
        dir.y = 0.0f;
        dir.x = 0.0f;
        dir.z = 1.0f;
    }
    acos(PSVECDotProduct(&dir, &ref));
    PSVECSubtract(&cam->pos, pos, &dir);
    clamped = PSVECMag(&dir);
    dist = clamped;
    if (clamped < 20.0f) {
        clamped = 20.0f;
    }
    PSMTXCopy(cam->viewMtx, m);
    scale = 0.2f / clamped;
    bss->indMtx[0][0] = scale;
    bss->indMtx[1][1] = scale * (f32)(1.0 - fabs(0.5f * (ref.y * m[1][1])));
    if (dist < 35.0f) {
        sScale = 4;
        tScale = 4;
    } else if (dist < 55.0f) {
        sScale = 3;
        tScale = 3;
    } else {
        sScale = 2;
        tScale = 2;
    }
    bss->unk14 = 0;
    DCFlushRange(bss->unk238, 0x200);
    GXSetIndTexMtx(GX_ITM_0, bss->indMtx, 2);
    GXLoadTexObj(&bss->texObj, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, sScale, tScale);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_TRUE, GX_FALSE, GX_ITM_0);
}
