/* fn_3_90DD8 NONMATCHING (5 diff lines): everything matches except scheduling of the
 * 2-arg fn_800216F8 call setup (target: lis r4 cb; addi r0,r3,5; addi r4; clrlwi r3 — mine
 * does addi r0 before lis). Tried s32/u8 temps, inline helper, operand order, &fn.
 * Needs include/game/gap_90754.h: `s32 fn_3_90DD8(void);` (was void; gap_DEB90.c already uses s32).
 * Note the loop must use g_Minigame.players._18D0[i] (global) inside `if (idx != 0)`. */
typedef struct {
    u8 _pad0;
    u8 unk1;        /* 0x1 */
    u8 _pad2[4];
} CharBodyInfo_90754; /* size: 0x6 */
extern CharBodyInfo_90754 lbl_800E8558[];

s32 fn_3_90DD8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 idx = lbl_3_common_bss_34C58._2C / 2;
    MiniGameStruct* mg;
    s32 body;
    s32 i;

    if (lbl_3_common_bss_34C58._2C == 0 || lbl_3_common_bss_34C58._2C == 2 || lbl_3_common_bss_34C58._2C == 4 ||
        lbl_3_common_bss_34C58._2C == 6) {
        mg = &g_Minigame;
        if (mg->players.characterIndex[idx] < 0) {
            lbl_3_common_bss_34C58._2C += 2;
            return 0;
        }
        body = lbl_800E8558[mg->players._18D0[idx]].unk1;
        if (idx != 0) {
            for (i = 0; i < idx; i++) {
                if (body == lbl_800E8558[g_Minigame.players._18D0[i]].unk1) {
                    if ((lbl_3_common_bss_34C58._2C += 2) >= 8) {
                        g_Minigame._19AB = 1;
                        return 1;
                    }
                    return 0;
                }
            }
        }
        fn_800216F8((u8)(fn_800698F8(body) + 5), fn_3_90F48);
        lbl_3_common_bss_34C58._2C++;
    } else if (scene->loadingState != 0) {
        if (++lbl_3_common_bss_34C58._2C >= 8) {
            g_Minigame._19AB = 1;
            return 1;
        }
    }
    return 0;
}
