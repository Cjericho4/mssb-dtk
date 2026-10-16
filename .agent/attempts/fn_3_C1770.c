/*
 * fn_3_C1770 (src/game/rep_1F58.c) NONMATCHING - not attempted beyond one check.
 * Hits the known-unfixable "same-file static data off one base register" pattern
 * (same as fn_3_C11CC): target keeps &lbl_3_data_17248 in r31 and reaches the slot
 * table (17260) as r31+0x18, plus r31+0x64 / r31+0xA4 (later .data objects in the
 * same TU). With extern symbols MWCC re-materialises lis/addi per object.
 * Logic sketch: if (AnimationStructPtrs[idx] != NULL) { find free slot j in 1..0 of
 * lbl_3_data_17260 (charIndex == -1); store idx, copy anim->unk34/unk3C, compute
 * -(f32)table[anim->unk252].x / K; memcpy 12 bytes; clear +2; sfx 0x18/0x17 via
 * fn_80027918(sfx, 0.0f); GXInitTexObj(&lbl_3_bss_9D20, &lbl_3_bss_9D40, 4,4,6,0,0,0);
 * GXInitTexObjLOD(...); lbl_3_common_bss_35154.<0x477 + j> = 0; }
 */
