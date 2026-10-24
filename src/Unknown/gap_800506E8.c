#include "Unknown/gap_800506E8.h"

// .text:0x800506E8 size:0x78
void fn_800506E8(s8 value, s32 index, BOOL set) {
    s32 i;
    s32 id = lbl_800E8558[index].id;
    for (i = 0; i < 0x24; i++) {
        if (lbl_800FDE84[i] == id) {
            if (set) {
                lbl_803C6028.slots[i] = value;
            } else {
                lbl_803C6028.slots[i] = -1;
            }
            return;
        }
    }
}

// .text:0x80050760 size:0x818
void fn_80050760(void) {
    return;
}

// .text:0x80050F78 size:0x70
BOOL fn_80050F78(s32 mode) {
    if (lbl_803C6028.unk7C == 0) {
        if (mode == 2) {
            lbl_803C6028.unk7C = 4;
            lbl_803C6028.unk90 = 1;
        } else if (mode != 0) {
            lbl_803C6028.unk7C = 3;
        } else {
            lbl_803C6028.unk7C = 1;
        }
    }
    if (lbl_803C6028.unk7C == 2) {
        lbl_803C6028.unk7C = 0;
        return TRUE;
    }
    return FALSE;
}

// .text:0x80050FE8 size:0x3A4
void fn_80050FE8(void) {
    return;
}

// .text:0x8005138C size:0x974
void fn_8005138C(void) {
    return;
}

// .text:0x80051D00 size:0x488
/* Open the DOL select grid. Its texture lookup sequence 0x19 (resource 9)
 * supplies textures by GRID charID; taken cells show frame25
 * and controller badges, while unavailable cells substitute charID54.
 * lbl_800FDE60 is the per-cell draw order, FDE84 the base-character grid.
 * No unique-index or family conversion occurs at this texture binding. */
void fn_80051D00(void) {
    MenuGridScene* scene = lbl_803CC1B8;
    s32 cell;
    s32 i;
    u8 charID;
    s8 controller;
    if (lbl_803C6028.unk8E == 1) return;
    fn_80034E20(scene, lbl_800FCA60);
    if (lbl_803C6028.unk8F == 1)
        lbl_80371C30[scene->paneBase + 2].pane->sequence = 0x14;
    lbl_80371C30[scene->paneBase + 1].pane->frame = 0x320000;
    for (cell = 0; cell < 36; cell++) {
        if (lbl_800FDE84[cell] == 0xFF) {
            lbl_80371C30[scene->paneBase + cell + 0x2F].pane->flags &= ~2;
            lbl_80371C30[scene->paneBase + cell + 3].pane->flags &= ~2;
        } else {
            charID = lbl_800FDE84[cell];
            if ((s8)lbl_803C6028.cellUnavailable[cell] != 0) charID = 54;
            fn_800363D8(scene, cell + 0x2F, 1, 0x19, charID);
            lbl_80371C30[scene->paneBase + cell + 0x2F].pane->order = lbl_800FDE60[cell];
            if (lbl_803C6028.unk8F == 1) {
                for (i = 0; i < 12; i++) {
                    if (lbl_800E854C[i] == charID) {
                        lbl_80371C30[scene->paneBase + cell + 0x2F].pane->frame = 0x50000;
                        lbl_80371C30[scene->paneBase + cell + 0x2F].pane->playMode = 0;
                        break;
                    }
                }
            }
            if (charID < 54) {
                if (g_d_GameSettings.exhibitionMatchInd == 0) {
                    if (starMissionCompletionTracker.characterFlags[charID])
                        lbl_80371C30[scene->paneBase + cell + 0x53].pane->flags |= 2;
                } else if (lbl_80361B20.characterFlags[charID])
                    lbl_80371C30[scene->paneBase + cell + 0x53].pane->flags |= 2;
            }
        }
        lbl_80371C30[scene->paneBase + cell + 0x77].pane->flags &= ~2;
        lbl_80371C30[scene->paneBase + cell + 0x77].pane->order = lbl_800FDE60[cell];
        controller = lbl_803C6028.slots[cell];
        if (controller >= 0) {
            lbl_80371C30[scene->paneBase + cell + 0x2F].pane->frame = 0x190000;
            lbl_80371C30[scene->paneBase + cell + 0x2F].pane->playMode = 0;
            lbl_80371C30[scene->paneBase + cell + 3].pane->frame = 0x190000;
            lbl_80371C30[scene->paneBase + cell + 3].pane->playMode = 0;
            lbl_80371C30[scene->paneBase + cell + 0x77].pane->flags |= 2;
            lbl_80371C30[scene->paneBase + cell + 0x77].pane->frame = 0x190000;
            lbl_80371C30[scene->paneBase + cell + 0x77].pane->playMode = 0;
            if (lbl_803C6028.alternateBadge[controller])
                fn_800363D8(scene, cell + 0x77, 1, 0x1A, controller + 4);
            else fn_800363D8(scene, cell + 0x77, 1, 0x1A, controller);
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_80371C30[scene->paneBase + i + 0x2B].pane->frame = i << 16;
        if (lbl_803C6028.alternateBadge[i]) fn_800363D8(scene, i + 0x9B, 1, 0x1A, i + 4);
        else fn_800363D8(scene, i + 0x9B, 1, 0x1A, i);
    }
    lbl_803C6028.unk7C = 0;
    lbl_803C6028.unk92 = 0;
    scene->state = 0;
    lbl_803CC1B8->update = fn_8005138C;
}

// .text:0x80052188 size:0x28
void fn_80052188(void) {
    lbl_803C6028.unk8E = 0;
    lbl_803C6028.unk8F = 0;
    lbl_803C6028.unk90 = 0;
    lbl_803C6028.unk7C = 0;
    lbl_803C6028.unk7D = 0;
    lbl_803C6028.unk7E = 0;
}

// .text:0x800521B0 size:0x25C
void fn_800521B0(void) {
    return;
}

// .text:0x8005240C size:0x228
void fn_8005240C(void) {
    return;
}

// .text:0x80052634 size:0x58
void fn_80052634(Gap800506E8Actor* actor, s32 index) {
    Gap800506E8Task* task = fn_800B0A5C_insertQueue(fn_800521B0, 4);
    task->actor = actor;
    task->index = index;
    task->id = actor->id;
}

// .text:0x8005268C size:0x8
s32 fn_8005268C(void) {
    return lbl_803CBD14;
}

// .text:0x80052694 size:0xA0
void fn_80052694(s32 camera) {
    if (camera < 0) {
        camera = 0;
    } else if (camera >= 2) {
        camera = 1;
    }
    lbl_803CBD14 = camera;
    GXSetProjection(lbl_803C639C.alternate[camera].projection, 0);
    if (lbl_803CB880 == 1) {
        GXSetScissor(0, 0, 640, 448);
    } else if (lbl_803CB880 == 2) {
        GXSetScissor(camera * 320, 0, 320, 448);
    }
}

// .text:0x80052734 size:0x34
Gap800506E8Camera* fn_80052734(s32 index) {
    if (index < 0) index = 0;
    else if (index >= 2) index = 1;
    return &lbl_803C639C.alternate[index];
}

// .text:0x80052768 size:0x30
Gap800506E8Camera* fn_80052768(s32 index) {
    if (index < 0) index = 0;
    else if (index >= 2) index = 1;
    return &lbl_803C639C.slots[index];
}

// .text:0x80052798 size:0x24
void fn_80052798(s32 value) {
    if (value < 1) {
        value = 1;
    } else if (value > 2) {
        value = 2;
    }
    lbl_803CB880 = value;
}

// .text:0x800527BC size:0x8
s32 fn_800527BC(void) {
    return lbl_803CB880;
}

// .text:0x800527C4 size:0xE8
void fn_800527C4(void) {
    return;
}
