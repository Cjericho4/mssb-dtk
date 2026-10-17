/* fn_2_512C0 (menus/gap_4B1AC.c) -- best attempt, 1 instruction short (Fable, 2026-10-17)
 *
 * Prerequisites (both verified, not committed):
 *  - fn_2_51358 is this function's trailing blr split off by dtk (KB section 8). To match,
 *    set fn_2_512C0 size 0x9C in config/GYQE01/menus/symbols.txt, drop the fn_2_51358 line,
 *    its stub in src/menus/gap_4B1AC.c and its prototype in include/menus/gap_4B1AC.h.
 *  - MenusPanelState.commands[4] (+0x80) and commandCounters[4] (+0x1E68) are in rep_10C0.h.
 *
 * Target tree after `clrlwi r0, r3, 18`:
 *   cmpwi 4; beq L; bge L; cmpwi 0; beqlr; b L; b L; blr; L: inc; b loop; L2: inc; b loop
 * (two identical `counter++; b loop` blocks: L for the switch path, L2 for the non-flag path.)
 *
 * This body produces everything except the second dead `b L`.
 *   case 4: continue; case 5: break;             -> exact tree + layout, but 4 goes to the loop head
 *   case 4: inc; break; case 5: default: break;  -> exact layout + beq L, but 5/default go to the loop head
 * Everything else tried (break/goto/continue bodies, dead statements in case 4, do{}while(0),
 * for(;;inc), labeled null statements, goto into case 4's body) merges cases 4 and 5 into
 * `cmpwi 4; bge L` (no beq): MWCC builds the compare tree after body codegen/DCE and merges
 * adjacent cases whose *resolved* targets coincide. Need a case-4 position distinct from
 * case 5's that still resolves to the after-switch increment.
 */
void fn_2_512C0(s32 index) {
    u16* p = lbl_2_bss_1A824C->panel.commands[index];
    for (;;) {
        u16 code = *p++;
        if (code & 0x4000) {
            switch (code & 0x3FFF) {
            case 0: return;
            case 4: break;
            }
            lbl_2_bss_1A824C->panel.commandCounters[index]++;
        } else {
            lbl_2_bss_1A824C->panel.commandCounters[index]++;
        }
    }
}
