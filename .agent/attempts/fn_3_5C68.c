/* fn_3_5C68 NONMATCHING (src/game/rep_1C0.c). Instruction stream matches except saved-register assignment:
   target obj=r29, j=r28, i=r27, count=r26 (count reuses the param reg); ours i=r29, obj=r28, count=r27, j=r26.
   Declaration-order brute force (all 48 perms incl. dx/dy order) has no effect; static inline helper for the inner loop made it worse.
   Needs header types in .scratch/fn_3_5C68.headers.diff (AnimTileSet/AnimTileObj/... + fn_80023F0C proto in rep_1C0.h). */
void fn_3_5C68(AnimTileSet* set) {
    s32 i;
    AnimTileObj* obj;
    s32 count;
    s32 j;
    u8* tile;
    s32 frame;
    s32 sx;
    s32 sy;
    s32 dx;
    s32 dy;

    GXSetCullMode(GX_CULL_BACK);
    {
        u32 color[1] = {0};
        SetFog(0, color, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    i = 2;
    while (i-- != 0) {
        obj = set->objs[i];
        if (obj == NULL) {
            continue;
        }
        count = 0;
        for (j = 0; j < obj->count; j++) {
            if (obj->entries[j].timer-- != 0) {
                continue;
            }
            obj->entries[j].frame = (obj->entries[j].frame + 1) % obj->numFrames;
            dx = (j % 8) << 5;
            dy = (j / 8) << 6;
            frame = obj->frames[obj->entries[j].frame];
            if (i != 0) {
                tile = obj->tiles + (obj->entries[j].row * 4 + frame * 2);
                sx = tile[0] << 5;
                sy = tile[1] << 6;
            } else {
                tile = obj->tiles + (obj->entries[j].row * 8 + frame * 2);
                sx = tile[0] << 5;
                sy = tile[1] << 6;
            }
            fn_80023F0C(obj->dst, obj->tex, sx, sy, 0x20, 0x40, dx, dy);
            obj->entries[j].timer = obj->delay;
            count++;
        }
        if (count != 0) {
            DCStoreRange(obj->tex->data, obj->tex->height * obj->tex->width);
        }
    }
    if (lbl_3_bss_18[0] != NULL) {
        ((void (*)(void))lbl_3_bss_18[0])();
    }
    GXSetZCompLoc(GX_FALSE);
}
