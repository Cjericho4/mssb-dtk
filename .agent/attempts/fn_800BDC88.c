/* best attempt fn_800BDC88: 25 lines, all from one missing copy. Target keeps a second pointer to the row
   (mr r3,r30 before the bank test, bank stores via r3), so the zero constant lands in r4; MWCC copy-propagates
   every copy tried (plain copy, entry/state pointer, inline helper with/without the if). Saved regs r26-r31 and the
   single clrlwi match with s32 slot + (u16) casts. The final onDraw store re-indexes table (add r26,r31) in target.
   Needs header prototype: void fn_800BDC88(struct StadiumAnimTable*, s32 slot, u16 index, struct Gap800B117CRequest*,
   struct ANIMBank*, s32 actorValue); plus fn_800B4048/fn_800B4724 prototypes (see codex/d1). */
void fn_800BDC88(StadiumAnimTable* table, s32 slot, u16 index, struct Gap800B117CRequest* request, ANIMBank* bank, s32 actorValue) {
    StadiumAnimTable* row;
    StadiumAnimTable* p;

    fn_800B4048(&table->entries[(u16)slot].anim.actor, request, (u16)slot);
    row = (StadiumAnimTable*)((StadiumAnimEntry*)table + (u16)slot);
    fn_800B4724(row->entries[0].anim.actor, actorValue);
    row->entries[0].anim.seqNum = 0;
    row->entries[0].anim.speed = 1.0f;
    row->entries[0].anim.unk64 = 0;
    row->entries[0].anim.unk66 = 0;
    row->entries[0].anim.unk68 = 0;
    row->entries[0].lightCount = 0;
    row->entries[0].lights[0] = NULL;
    row->entries[0].lights[1] = NULL;
    row->entries[0].lights[2] = NULL;
    row->entries[0].lights[3] = NULL;
    row->entries[0].lights[4] = NULL;
    row->entries[0].lights[5] = NULL;
    row->entries[0].lights[6] = NULL;
    row->entries[0].lights[7] = NULL;
    row->entries[0].anim.index = index;
    row->entries[0].enabled = 1;
    p = row;
    if (bank != NULL) {
        p->entries[0].anim.bank = bank;
        p->entries[0].anim.playAnim = 1;
        p->entries[0].anim.setSpeed = 1;
        p->entries[0].anim.setTime = 1;
        p->entries[0].anim.startTime = 0.0f;
        if (row->entries[0].anim.actor != NULL) {
            row->entries[0].anim.actor->unk99 = 0;
        }
    }
    table->entries[(u16)slot].anim.onDraw = NULL;
}
