/* fn_3_A295C NONMATCHING (src/game/rep_18E8.c). Known-unfixable lbl_3_bss_17F8 file-static block pattern:
   target keeps a sub-base pointer addi r30,r31,0x10 (&x1808) and loads runnerIndex[2] as 0x8(r30); MWCC copy-propagates
   the local pointer and folds it to 0x18(r31) (frame also shrinks since r30 is not needed). Logic/control flow otherwise
   believed correct (inlines fn_3_A3768 body). Header change: rep_18E8.h prototype -> s32 fn_3_A295C(void).
   fn_3_A2DDC and fn_3_A2FD8 use the same 17F8 base + addi r3,r31,0x10 sub-bases and were skipped for this reason. */
/* File-local bss block starting at 0x17F8 (accessed via a single base). */
typedef struct Bss17F8 {
    /* 0x00 */ u8 _pad0[0x8];
    /* 0x08 */ u32 x1800;
    /* 0x0C */ u8 _padC[0x4];
    /* 0x10 */ Bss1808 x1808;
    /* 0x24 */ s32 x181C;
    /* 0x28 */ s32 x1820;
    /* 0x2C */ u32 x1824;
    /* 0x30 */ s32 x1828[4];
    /* 0x40 */ s32 x1838[8];
    /* 0x60 */ s32 x1858[4];
} Bss17F8;
extern Bss17F8 lbl_3_bss_17F8;

static inline s32 fn_3_A3768_inl(void) {
    if (g_Ball.ballAngleFromHome >= 0x380
        && g_Ball.ballAngleFromHome < 0x640
        && g_Ball.ballZoneAwayFromHome <= 1
        && g_Ball.AtBat_Contact_BallPos.z > (lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x)) {
        return 1;
    }
    return 0;
}

// .text:0x000A295C size:0x210 mapped:0x806E19F0
s32 fn_3_A295C(void) {
    Bss17F8* bss = &lbl_3_bss_17F8;
    Bss1808* rb = &bss->x1808;
    InMemRunnerType* r = &g_Runners[rb->runnerIndex[2]];

    if (r->percentTowardsNextBase > 0.2f && bss->x1858[rb->runnerIndex[2]] < 3 && g_Ball.ballZoneAwayFromHome <= 1 &&
        r->percentTowardsNextBase <= 0.25f) {
        if (!(r->percentTowardsNextBase >= 0.25f) || r->runningDirectionCode != 1) {
            if ((bss->x1824 & 1) && g_Ball.ballAngleFromHome > 0x1C0 && g_Ball.ballAngleFromHome < 0x300 &&
                r->percentTowardsNextBase <= 0.3f && bss->x1858[bss->x1808.runnerIndex[0]] <= 3 &&
                fn_3_A46A0(bss->x1808.runnerIndex[0]) != 0) {
                return 1;
            }
        }
    }
    if (fn_3_A3768_inl()) {
        if (bss->x1858[rb->runnerIndex[2]] <= 4 && g_Strikes.outs == g_Strikes.unk_C) {
            if (r->percentTowardsNextBase > 0.2f && fn_3_A46A0(rb->runnerIndex[2]) != 0) {
                return 1;
            }
            if ((bss->x1800 & 0x10) && r->percentTowardsNextBase > 0.15f && fn_3_A46A0(rb->runnerIndex[2]) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
