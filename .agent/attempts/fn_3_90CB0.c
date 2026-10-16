/* fn_3_90CB0 NONMATCHING (src/game/gap_90754.c). Best: 41 diff lines. Control flow and all memory ops line up;
   remaining: target strength-reduces both inner loops to byte pointers (mr r8,r31 / addi r8,1 for characterIndex[j];
   r6 = copy of mg kept in r29 for _18D0[k]) and saves r27-r31 via stmw; MWCC here indexes with add/lbzx instead.
   Tried: plain nested loops, local mg2 copy, global vs local base per access, per-match u8* cur, inline helpers
   (isDuplicateBody / findSlot). lbl_800E8558 element type is file-local in gap_6B4C8.c (CharacterBodyInfo, 6 bytes, field +1 needed). */
typedef struct {
    u8 _0;
    u8 unk1;
    u8 _2[4];
} CharBodyInfo_90754; // size: 0x6
extern CharBodyInfo_90754 lbl_800E8558[];
static inline BOOL isDuplicateBody(MiniGameStruct* mg, s32 j) {
    s32 k;
    BOOL found = FALSE;
    for (k = 0; k < j; k++) {
        if (lbl_800E8558[mg->players._18D0[j]].unk1 == lbl_800E8558[mg->players._18D0[k]].unk1) {
            found = TRUE;
            break;
        }
    }
    return found;
}

void fn_3_90CB0(void) {
    MiniGameStruct* mg = &g_Minigame;
    s32 i;
    s32 j;
    s32 slot;
    void** entry;

    if (mg->_19AB == 0) {
        return;
    }
    for (i = 3; i >= 0; i--) {
        for (j = 0; j < 4; j++) {
            if (mg->players.characterIndex[j] == i) {
                if (!isDuplicateBody(mg, j)) {
                    break;
                }
            }
        }
        if (j < 4) {
            slot = fn_800698F8(inMemRoster[0][i].stats.CharID) + 5;
            entry = &lbl_800EF808.files[slot];
            if (*entry != NULL) {
                fn_800214D0();
                fn_800ACFB0(*entry);
                *entry = NULL;
            }
        }
    }
}
