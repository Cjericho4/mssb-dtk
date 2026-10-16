/* fn_3_F8878 NONMATCHING (2 diff lines): the only difference is `stfs f23,0x14(r30)` (obj->unk14 = 0.123f)
   being placed after the if/else instead of in the loop header block (target: clrlwi.; stfs; bne).
   Putting the store first in the loop body instead flips the FP allocation (0.123 -> f31, prev -> f30,
   everything else shifted down by one). Tried: store at every position, odd-branch-first if, 0.123 local,
   extern lbl_3_rodata_2FC4 (much worse), register prev, block-local angle/rad, prev = 0.0f init,
   rad/prev order swap, static inline angle helper, i*3 instead of j.
   Sibling edits this attempt depends on (both stay matched):
     - `static const VecXYZ basePos` moved from inside fn_3_F8524 to file scope (just above fn_3_F8524).
     - fn_3_F8ABC: `StaC4Emitter* em = (StaC4Emitter*)fn_80033A24(...); if (em != NULL) fn_3_F8878(em);`
   Header changes in fn_3_F8878.headers.diff (StaC4Obj tag + next/unk10/unk18/unk4D/unk4E carves,
   new StaC4Emitter, prototype fn_3_F8878(StaC4Emitter* em)). */

extern u32 lbl_3_bss_B660;

void fn_3_F8878(StaC4Emitter* em) {
    s32 j;
    StaC4Obj* obj = em->head;
    u32 i;
    f32 prev;
    f32 angle;
    f32 rad;

    em->unk10 = lbl_3_bss_B660;
    i = 0;
    j = 0;
    for (; obj != NULL; obj = obj->next) {
        if ((i & 1) == 0) {
            angle = (f32)((i % 6) * 60);
            if ((i / 6) % 2 == 1) {
                angle += 30.0f;
            }
        } else {
            angle = 180.0f + prev;
        }
        prev = angle;
        obj->unk14 = 0.123f;
        rad = 0.017453292f * angle;
        obj->unk10 = 0.05 * (f32)cos(rad);
        obj->unk18 = 0.05 * (f32)sin(rad);
        obj->unk48 = j;
        j += 3;
        obj->unk4F = i;
        i++;
        obj->pos.x = basePos.x;
        obj->pos.y = basePos.y - 2.0;
        obj->pos.z = basePos.z;
        obj->unk38 = 0.75f;
        obj->unk3C = 4.0f;
        obj->color[2] = 0xFF;
        obj->color[1] = 0xFF;
        obj->color[0] = 0xFF;
        obj->color[3] = 0xFF;
        obj->unk4A = 0x80;
        obj->unk4D = 0x1B;
        obj->unk4E = 0;
    }
}
