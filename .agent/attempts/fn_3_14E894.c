// Best attempt (9 sbs lines): u32 loop + s8 idx + do-while over res->listHead. Left: target copies the stored 0 from i (`mr r31,r30`) and keeps node in r3 / idx+1 in r4 (ours r4/r3).
void fn_3_14E894(void) {
    u32 i;
    struct Struct_800339F0_Result* res;
    ListNode_14B9F0* node;

    for (i = 0; i < 4; i++) {
        s8 idx = i;
        res = fn_800339F0(0, 0x1E);
        if (res != NULL) {
            node = res->listHead;
            do {
                if (node->field_0x4C == idx + 1) {
                    node->field_0x4A = 0;
                }
                node = node->next;
            } while (node != NULL);
        }
    }
    pitchingMachinePitching(0x1E);
}
