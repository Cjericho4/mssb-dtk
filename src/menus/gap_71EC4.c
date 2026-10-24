#include "menus/gap_71EC4.h"
extern void (*lbl_2_data_2A2EC[])(Rep0B08Obj*);

extern void (*lbl_2_data_2A1E8[])(Rep0B08Obj*);
#include "UnknownHeaders.h"
#include "menus/gap_D08.h"
#include "menus/rep_10C0.h"
#include "menus/rep_0438.h"

extern MenusSceneScript lbl_2_data_2DC8C;
extern u8 lbl_2_data_2DC84[];
extern MenusSceneScript lbl_2_data_2B4DC;
extern MenusSceneScript lbl_2_data_2AADC;
extern MenusSceneScript lbl_2_data_2D33C;
extern s32 lbl_2_bss_A840;
#include "menus/gap_8782C.h"
#include "game/rep_3448.h"
#include "static/UnknownHomes_Static.h"
extern void fn_800363D8(DrawingSceneStruct* scene, s32 index, s32 enabled, s32 value, s32 order);

extern void fn_80053FE8(void);
extern u8 lbl_800FE5D4[12];
extern u8 lbl_800FE930[][6];
extern u8 fn_80067B40(u8 side, u8 id, s32 mode);
extern s32 fn_80036214(DrawingSceneStruct* scene, s32 pane, s32 list, s32 index);
extern void fn_80051D00(void);
extern s32 fn_80042DA8(DrawingSceneStruct* scene, s32 index, s32 value);
extern void fn_8004E2EC(void);
extern void fn_8004F964(void);
extern void fn_800625A4(s32, s32);
extern void fn_800626EC(s32);
extern void fn_80062674(s32);
#include "menus/gap_1254.h"

static inline void menuSetTransition(u8 mode) {
    lbl_8034E978.state = mode;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.entries[mode].next;
}

// .text:0x00071EC4 size:0x38
void fn_2_71EC4(Rep0B08Obj* obj) {
    lbl_2_data_2A1E8[obj->state](obj);
}

// .text:0x00071EFC size:0x24
void fn_2_71EFC(Rep0B08Obj* obj) {
    Rep0B08Obj* target = &lbl_2_bss_1A8248->rep0B08Objects[obj->index];
    target->unkC0 = 0;
}

// .text:0x00071F20 size:0x40
void fn_2_71F20(Rep0B08Obj* obj) {
    obj->callback = lbl_2_data_2A2EC[obj->variant];
    obj->callback(obj);
}

// .text:0x00071F60 size:0xD8
void fn_2_71F60(void) {
    s32 i;
    if (lbl_2_bss_1A8248->unk44F2 == 1 || lbl_2_bss_1A8248->unk44F2 == 2 || lbl_2_bss_1A8248->unk44F2 == 3) return;
    for (i = 0; i < 8; i++) {
        Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[i];
        obj->callback = lbl_2_data_2A2EC[obj->variant];
        obj->callback(obj);
    }
    if (lbl_2_bss_1A824C->flag1972BC) {
        lbl_2_bss_1A824C->flag1972BC = 0;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00072038 size:0x1C
void fn_2_72038(s32 index, s16 value) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->unkB4 = value;
}

// .text:0x00072054 size:0x28
void fn_2_72054(s32 index, u8 variant) {
    Rep0B08Obj* obj = &lbl_2_bss_1A8248->rep0B08Objects[index];
    obj->variant = variant;
    obj->state = 0;
}

// .text:0x0007207C size:0x518
void fn_2_7207C(void) {
    return;
}

// .text:0x00072594 size:0x9C
void fn_2_72594(void) {
    DrawingSceneStruct* scene;
    s32 i;
    fn_80034E20(scene = lbl_803CC1B8, &lbl_2_data_2AADC);
    i = 0;
    do {
        fn_800363D8(scene, i + 7, 1, 50, 3 - i);
        i++;
    } while (i < 4);
    fn_800363D8(scene, 2, 1, 53, 0);
    lbl_803CC1B8->unk_00 = fn_2_7207C;
}

// .text:0x00072630 size:0x2C
void fn_2_72630(void) {
    fn_800B0A5C_insertQueue(fn_2_72594, 0x3000);
}

// .text:0x0007265C size:0x1B8
/* Open the select-grid scene. Challenge mode queues its two extra scenes once.
 * The 54-byte flag scan chooses transition 1 (none set) or 2 (some set);
 * challenge always uses transition 0x13. This does not select a texture:
 * fn_80051D00 is the queued DOL grid-scene initializer. */
void fn_2_7265C(void) {
    GameInitVariables* settings;
    s32 i;
    s32 transition;
    s32 any = 0;
    settings = &g_d_GameSettings;
    if (settings->GameModeSelected == 5 && lbl_803C5EA4.rosterSceneQueued == 0) {
        lbl_803C5EA4.rosterSceneQueued = 1;
        fn_800B0A5C_insertQueue(fn_80053FE8, 0x3000);
        fn_800B0A5C_insertQueue(fn_2_82DE8, 0x3000);
    }
    for (i = 0; i < 54; i++) {
        if (lbl_80361B20.characterFlags[i] != 0) {
            any = 1;
            break;
        }
    }
    if (settings->GameModeSelected != 5) {
        if (any) transition = 2;
        else transition = 1;
    } else transition = 0x13;
    lbl_8034E978.state = transition;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.entries[transition].next;
    fn_800B0A5C_insertQueue(fn_80051D00, 0x3000);
}

// .text:0x00072814 size:0xAC
void fn_2_72814(DrawingSceneStruct* scene) {
    s32 first;
    if ((u32)__cntlzw(1 - lbl_803CBBC4.unk3) >> 5) {
        first = !!fn_80042DA8(scene, 0, 0);
        if (first + !!fn_80042DA8(scene, 1, 0) == 2) {
            lbl_803CBBC4.unk3 = 0;
            lbl_803CBBC4.unk2 = 0;
            lbl_803CBBC4.unk0 = 0;
            lbl_803CBBC4.unk4 = 1;
        }
    }
}

// .text:0x000728C0 size:0x7C
void fn_2_728C0(DrawingSceneStruct* scene) {
    if ((u32)__cntlzw(lbl_803CBBC4.unk2) >> 5) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 4;
        lbl_803CBBC4.unk2 = 1;
        lbl_803CBBC4.unk3 = 1;
    }
}

// .text:0x0007293C size:0xA4
void fn_2_7293C(DrawingSceneStruct* scene) {
    s32 first;
    if ((u32)__cntlzw(1 - lbl_803CBBC4.unk3) >> 5) {
        first = !!fn_80042DA8(scene, 0, 25);
        if (first + !!fn_80042DA8(scene, 1, 25) == 2) {
            lbl_803CBBC4.unk3 = 0;
            lbl_803CBBC4.unk2 = 0;
            lbl_803CBBC4.unk0 = 0;
        }
    }
}

// .text:0x000729E0 size:0x78
void fn_2_729E0(DrawingSceneStruct* scene) {
    if ((u32)__cntlzw(lbl_803CBBC4.unk2) >> 5) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 1;
        lbl_803CBBC4.unk2 = 1;
        lbl_803CBBC4.unk3 = 1;
    }
}

// .text:0x00072A58 size:0x30
void fn_2_72A58(void) {
    if ((u32)__cntlzw(1 - lbl_803CBBC4.unk3) >> 5) {
        lbl_803CBBC4.unk3 = 0;
        lbl_803CBBC4.unk2 = 0;
        lbl_803CBBC4.unk0 = 0;
    }
}

// .text:0x00072A88 size:0x22C
void fn_2_72A88(void) {
    return;
}

// .text:0x00072CB4 size:0xAC
void fn_2_72CB4(DrawingSceneStruct* scene) {
    s32 first;
    if ((u32)__cntlzw(1 - lbl_803CBBC4.unk3) >> 5) {
        first = !!fn_80042DA8(scene, 0, 0);
        if (first + !!fn_80042DA8(scene, 1, 0) == 2) {
            lbl_803CBBC4.unk3 = 0;
            lbl_803CBBC4.unk2 = 0;
            lbl_803CBBC4.unk0 = 0;
            lbl_803CBBC4.unk4 = 1;
        }
    }
}

// .text:0x00072D60 size:0x7C
void fn_2_72D60(DrawingSceneStruct* scene) {
    if ((u32)__cntlzw(lbl_803CBBC4.unk2) >> 5) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 4;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x5C = 0x190000;
        lbl_80371C30[scene->unkIndex + 1].obj->field_0x68 = 4;
        lbl_803CBBC4.unk2 = 1;
        lbl_803CBBC4.unk3 = 1;
    }
}

// .text:0x00072DDC size:0x78
void fn_2_72DDC(DrawingSceneStruct* scene) {
    s32 first;
    if ((u32)__cntlzw(1 - lbl_803CBBC4.unk3) >> 5) {
        first = !!fn_80042DA8(scene, 0, 25);
        if (first == 1) {
            lbl_803CBBC4.unk3 = 0;
            lbl_803CBBC4.unk2 = 0;
            lbl_803CBBC4.unk0 = 0;
        }
    }
}

// .text:0x00072E54 size:0x1D4
void fn_2_72E54(void) {
    return;
}

// .text:0x00073028 size:0x4
void fn_2_73028(void) {
    return;
}

// .text:0x0007302C size:0x60
void fn_2_7302C(void) {
    return;
}

// .text:0x0007308C size:0x6CC
void fn_2_7308C(void) {
    return;
}

// .text:0x00073758 size:0x170
void fn_2_73758(void) {
    return;
}

// .text:0x000738C8 size:0xCC
void fn_2_738C8(void) {
    if (lbl_803CBBCC->previousSelection == 5) fn_800B0A5C_insertQueue(fn_80053FE8, 0);
    if (g_d_GameSettings.GameModeSelected == 5) {
        menuSetTransition(13);
        fn_800B0A5C_insertQueue(fn_8004E2EC, 0x3000);
    } else {
        menuSetTransition(0);
        fn_800B0A5C_insertQueue(fn_8004F964, 0x3000);
    }
}

// .text:0x00073994 size:0x1C0
void fn_2_73994(void) {
    return;
}

// .text:0x00073B54 size:0x40
s32 fn_2_73B54(s32 value) {
    extern s32 lbl_2_bss_A840;
    if (lbl_2_bss_A840 == 0 && value == 6) return 4;
    if (lbl_2_bss_A840 == 6 && value == 0) return 1;
    return 1;
}

// .text:0x00073B94 size:0x5C
s32 fn_2_73B94(s32 value) {
    extern s32 lbl_2_bss_A840;
    if (lbl_2_bss_A840 == 0 && value == 6) return 0x2D;
    if (lbl_2_bss_A840 == 6 && value == 0) return 0xE;
    if (lbl_2_bss_A840 <= value) return 0x1D;
    if (lbl_2_bss_A840 > value) return 0x2C;
}

// .text:0x00073BF0 size:0xCC
void fn_2_73BF0(void) {
    return;
}

// .text:0x00073CBC size:0x240
void fn_2_73CBC(void) {
    return;
}

// .text:0x00073EFC size:0x5CC
void fn_2_73EFC(void) {
    return;
}

// .text:0x000744C8 size:0x50
void fn_2_744C8(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(1 - input->state) >> 5) {
        fn_80062674(0);
        input->state = 2;
    }
}

// .text:0x00074518 size:0x4C
void fn_2_74518(void) {
    MenusInputFlags* input = &lbl_803C66B0;
    if ((u32)__cntlzw(input->state) >> 5) {
        fn_800626EC(0);
        input->state = 1;
    }
}

// .text:0x00074564 size:0xD8
void fn_2_74564(DrawingSceneStruct* scene) {
    s32 i, total, count;
    s32 selected = lbl_2_bss_F410.unk0;
    if ((u32)__cntlzw(1 - lbl_803C66B0.state) >> 5) {
        total = 0;
        count = 0;
        for (i = 0; i < 7; i++) {
            if (selected == i) {
                count++;
                total += fn_80042DA8(scene, i + 3, 14) != 0;
            }
        }
        total += fn_80042DA8(scene, 32, 10) != 0;
        if (total == count + 1) {
            fn_80062674(0);
            lbl_803C66B0.state = 2;
            fn_800625A4(0, 87);
        }
    }
}

// .text:0x0007463C size:0x1C0
void fn_2_7463C(void) {
    return;
}

// .text:0x000747FC size:0x4DC
void fn_2_747FC(void) {
    return;
}

// .text:0x00074CD8 size:0xB4
void fn_2_74CD8(void) {
    DrawingSceneStruct* scene;
    s32 i;
    fn_80034E20(scene = lbl_803CC1B8, &lbl_2_data_2D33C);
    i = 0;
    do {
        fn_800363D8(scene, i + 24, 1, 54, i);
        i++;
    } while (i < 7);
    fn_800363D8(scene, 32, 1, 50, 0);
    lbl_2_bss_A840 = lbl_2_bss_F410.unk0;
    lbl_803CC1B8->unk_00 = fn_2_747FC;
}

// .text:0x00074D8C size:0x2C
void fn_2_74D8C(void) {
    fn_800B0A5C_insertQueue(fn_2_74CD8, 0x1000);
}

// .text:0x00074DB8 size:0x5C
s32 fn_2_74DB8(s32 value) {
    switch (value) {
    case 13:
    case 16:
    case 20:
    case 22:
    case 25:
    case 34:
    case 42:
    case 50:
    case 52:
        return 1;
    case 21:
    case 24:
    case 29:
    case 33:
    case 44:
    case 51:
    case 53:
        return 2;
    case 23:
    case 30:
    case 36:
    case 45:
        return 3;
    case 12:
    case 26:
    case 27:
    case 31:
    case 35:
    case 43:
    case 46:
    case 49:
        return 4;
    case 32:
        return 5;
    case 47:
        return 6;
    default: return 0;
    }
}

// .text:0x00074E14 size:0x12C
void fn_2_74E14(void) {
    return;
}

// .text:0x00074F40 size:0xC18
/* Refresh the roster/captain stat panel. Pane 0xB0+side is a charID-keyed
 * name animation (resource slot 8, layout 0x82); 0xAE+side is a hard-coded
 * colour label. Neither lookup uses uniqueIdx. Stat bars use the displayed
 * ratings at CharacterStats +0x37..0x3A, not the gameplay simulation values.
 * The roster cursor is an order value, so search order[] before reading teams[].
 * Retail assumes every ordinary cursor has an order[] entry. */
void fn_2_74F40(DrawingSceneStruct* scene, s32 index) {
    s32 charID;
    s32 i;
    s32 rating[4];
    s32 pane[4];
    s32 colour;
    u32 texture;
    MenusCharacterStats* stats;
    if (lbl_803CBBCC->selection == 9 || lbl_803C66B0.flags5D[index] == 0xB) {
        if (g_d_GameSettings.GameModeSelected != 5)
            charID = lbl_800FE5D4[lbl_2_bss_F410.selections[index]];
        else
            charID = lbl_800FE930[lbl_80361B20.challengeCaptainPage][lbl_2_bss_F410.selections[0]];
        stats = &lbl_8034E9A0.stats[charID / 9][charID % 9];
        rating[0] = stats->pitchingDisplay;
        rating[1] = stats->runningDisplay;
        rating[2] = stats->battingDisplay;
        rating[3] = stats->fieldingDisplay;
        goto bars;
    }
    if (lbl_2_bss_F468.flags41[index]) {
        charID = lbl_2_bss_F410.gridPick[index];
        lbl_80371C30[scene->unkIndex + index + 0xB2].obj->flags &= ~2;
    } else if (lbl_2_bss_F468.cursor[index] != 9 && lbl_2_bss_F468.cursor[index] != 10) {
        for (i = 0; i < 9; i++) {
            if (lbl_803C6724.order[index][i] == (s8)lbl_2_bss_F468.cursor[index])
                charID = lbl_803C6724.teams[index][i];
        }
    } else charID = -1;
    if (charID != -1 && fn_80067B40(0, (u8)charID, 2) && g_d_GameSettings.GameModeSelected != 5) {
        lbl_80371C30[scene->unkIndex + index + 0xB2].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + index + 0xB2].obj->field_0x5C = 0;
        lbl_80371C30[scene->unkIndex + index + 0xB2].obj->field_0x68 = 1;
        switch (charID) {
        case 13: case 16: case 20: case 22: case 25: case 34: case 42: case 50: case 52: colour = 1; break;
        case 21: case 24: case 29: case 33: case 44: case 51: case 53: colour = 2; break;
        case 23: case 30: case 36: case 45: colour = 3; break;
        case 12: case 26: case 27: case 31: case 35: case 43: case 46: case 49: colour = 4; break;
        case 32: colour = 5; break;
        case 47: colour = 6; break;
        default: colour = 0; break;
        }
        lbl_80371C30[scene->unkIndex + index + 0xAE].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + index + 0xAE].obj->field_0x5C = colour << 16;
    } else {
        lbl_80371C30[scene->unkIndex + index + 0xB2].obj->flags &= ~2;
        if (lbl_2_bss_F468.cursor[index] != 9 && lbl_2_bss_F468.cursor[index] != 10) {
            lbl_80371C30[scene->unkIndex + index + 0xAE].obj->flags |= 2;
            lbl_80371C30[scene->unkIndex + index + 0xAE].obj->field_0x5C = 0;
        }
    }
    lbl_80371C30[scene->unkIndex + index + 0xAC].obj->flags |= 2;
    if (charID >= 0 && charID < 54) {
        stats = &lbl_8034E9A0.stats[charID / 9][charID % 9];
        rating[0] = stats->pitchingDisplay;
        rating[1] = stats->runningDisplay;
        rating[2] = stats->battingDisplay;
        rating[3] = stats->fieldingDisplay;
        lbl_80371C30[scene->unkIndex + index + 0xB0].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + index + 0xB0].obj->field_0x5C = charID << 16;
        lbl_80371C30[scene->unkIndex + index + 0xAC].obj->field_0x5C = 0;
        lbl_80371C30[scene->unkIndex + index + 0xAC].obj->field_0x68 = 1;
    } else {
        lbl_80371C30[scene->unkIndex + index + 0xB0].obj->flags &= ~2;
        lbl_80371C30[scene->unkIndex + index + 0x97].obj->flags &= ~2;
        return;
    }
bars:
    pane[0] = 0x9C; pane[1] = 0x9E; pane[2] = 0x9B; pane[3] = 0x9D;
    for (i = 0; i < 4; i++) {
        lbl_80371C30[scene->unkIndex + index + 0x97].obj->flags |= 2;
        lbl_80371C30[scene->unkIndex + index + 0x97].obj->field_0x5C = 0;
        lbl_80371C30[scene->unkIndex + index + 0x97].obj->field_0x68 = 1;
        lbl_80371C30[scene->unkIndex + index * 4 + pane[i]].obj->field_0x5C = (rating[i] - 1) << 16;
        texture = fn_80036214(scene, 0xAB, 0, (rating[i] + 1) / 2 - 1);
        lbl_80371C30[scene->unkIndex + index * 4 + pane[i] + 8].obj->field_0x5C = (rating[i] - 1) << 16;
        lbl_80371C30[scene->unkIndex + index * 4 + pane[i] + 8].obj->field_0x58 = texture;
    }
    if (lbl_803CBBCC->selection == 9 || lbl_803C66B0.flags5D[index] == 0xB)
        lbl_80371C30[scene->unkIndex + index + 0xAE].obj->flags &= ~2;
}

// .text:0x00075B58 size:0x8C
void fn_2_75B58(void) {
    return;
}

// .text:0x00075BE4 size:0x4B4
void fn_2_75BE4(void) {
    return;
}

// .text:0x00076098 size:0x4
void fn_2_76098(void) {
    return;
}

// .text:0x0007609C size:0x30
void fn_2_7609C(s32 unused, u8 mode, u8 flag) {
    if (flag == 0) fn_2_8794(mode, 0);
}

// .text:0x000760CC size:0x240
void fn_2_760CC(void) {
    return;
}

// .text:0x0007630C size:0x340
void fn_2_7630C(void) {
    return;
}

// .text:0x0007664C size:0x4
void fn_2_7664C(void) {
    return;
}

// .text:0x00076650 size:0x224
void fn_2_76650(void) {
    return;
}

// .text:0x00076874 size:0x57C
void fn_2_76874(void) {
    return;
}

// .text:0x00076DF0 size:0x8B0
void fn_2_76DF0(void) {
    return;
}

// .text:0x000776A0 size:0x994
void fn_2_776A0(void) {
    return;
}

// .text:0x00078034 size:0x28
void fn_2_78034(s32 unused, s32 index) {
    u8* flag = &lbl_803C66B0.flags[index];
    if ((u32)__cntlzw(*flag) >> 5) {
        *flag = 1;
    }
}

// .text:0x0007805C size:0x310
void fn_2_7805C(void) {
    return;
}

// .text:0x0007836C size:0x754
void fn_2_7836C(void) {
    return;
}

// .text:0x00078AC0 size:0x4B8
void fn_2_78AC0(void) {
    return;
}

// .text:0x00078F78 size:0x1B4
void fn_2_78F78(void) {
    return;
}

// .text:0x0007912C size:0x268
void fn_2_7912C(void) {
    return;
}

// .text:0x00079394 size:0x2A0
void fn_2_79394(void) {
    return;
}

// .text:0x00079634 size:0x54
void fn_2_79634(s32 unused, s32 index) {
    if ((u32)__cntlzw(1 - lbl_803C66B0.flags[index]) >> 5) {
        fn_80062674(index);
        lbl_803C66B0.flags[index] = 2;
    }
}

// .text:0x00079688 size:0xDC
void fn_2_79688(void) {
    return;
}

// .text:0x00079764 size:0x1CC
void fn_2_79764(void) {
    return;
}

// .text:0x00079930 size:0x1F4
void fn_2_79930(void) {
    return;
}

// .text:0x00079B24 size:0x1D4
void fn_2_79B24(void) {
    return;
}

// .text:0x00079CF8 size:0x2B4
void fn_2_79CF8(void) {
    return;
}

// .text:0x00079FAC size:0x1E8
void fn_2_79FAC(void) {
    return;
}

// .text:0x0007A194 size:0x2CC
void fn_2_7A194(void) {
    return;
}

// .text:0x0007A460 size:0x158
void fn_2_7A460(DrawingSceneStruct* scene, s32 index) {
    s32 total;
    if ((u32)__cntlzw(1 - lbl_803C66B0.flags[index]) >> 5) {
        total=!!fn_80042DA8(scene,index,40);
        total+=!!fn_80042DA8(scene,index+2,40);
        total+=!!fn_80042DA8(scene,index+0x85,30);
        total+=!!fn_80042DA8(scene,index+0x1C,30);
        total+=!!fn_80042DA8(scene,index+0x6A,50);
        if(total==5) {
            lbl_80371C30[12+scene->unkIndex+index].obj->flags &=~2;
            lbl_80371C30[18+scene->unkIndex+index].obj->flags &=~2;
            fn_80062674(index);
            lbl_803C66B0.flags[index]=2;
        }
    }
}

// .text:0x0007A5B8 size:0x190
void fn_2_7A5B8(void) {
    return;
}

// .text:0x0007A748 size:0x290
void fn_2_7A748(void) {
    return;
}

// .text:0x0007A9D8 size:0x28C
void fn_2_7A9D8(void) {
    return;
}

// .text:0x0007AC64 size:0x1D8
void fn_2_7AC64(void) {
    return;
}

// .text:0x0007AE3C size:0x11BC
void fn_2_7AE3C(void) {
    return;
}

// .text:0x0007BFF8 size:0x1864
void fn_2_7BFF8(void) {
    return;
}

// .text:0x0007D85C size:0x25C
void fn_2_7D85C(void) {
    return;
}

// .text:0x0007DAB8 size:0x6DC
void fn_2_7DAB8(void) {
    return;
}

// .text:0x0007E194 size:0x1EC
void fn_2_7E194(void) {
    return;
}

// .text:0x0007E380 size:0x4E0
void fn_2_7E380(void) {
    return;
}

// .text:0x0007E860 size:0x114
void fn_2_7E860(DrawingSceneStruct* scene, s32 index) {
    s32 count;
    if ((u32)__cntlzw(1 - lbl_803C66B0.flags[index]) >> 5) {
        count = !!fn_80042DA8(scene, index + 12, 10);
        count += !!fn_80042DA8(scene, index + 14, 14);
        count += !!fn_80042DA8(scene, index + 18, 10);
        count += !!fn_80042DA8(scene, index + 28, 20);
        count += !!fn_80042DA8(scene, index + 106, 30);
        if (count == 5) {
            fn_80062674(index);
            lbl_803C66B0.flags[index] = 2;
        }
    }
}

// .text:0x0007E974 size:0x508
void fn_2_7E974(void) {
    return;
}

// .text:0x0007EE7C size:0xEC
void fn_2_7EE7C(DrawingSceneStruct* scene, s32 index) {
    s32 value = lbl_2_bss_F468.states[index];
    if (lbl_2_bss_F468.flags41[index] != 0) {
        s32 slot = scene->unkIndex + value;
        slot += index * 9;
        slot += 0x22;
        lbl_80371C30[slot].obj->flags &= ~2;
    } else {
        s32 slot = scene->unkIndex + value;
        slot += index * 9;
        slot += 0x22;
        lbl_80371C30[slot].obj->flags |= 2;
    }
    fn_2_74F40(scene, index);
    {
        u8 flag = lbl_2_bss_F468.flags59[index];
        lbl_803C66B0.flags5D[index] = 0;
        if (flag != 0) fn_800625A4(index, 0x1A);
    }
}

// .text:0x0007EF68 size:0xC8
void fn_2_7EF68(void) {
    return;
}

// .text:0x0007F030 size:0x28C
void fn_2_7F030(void) {
    return;
}

// .text:0x0007F2BC size:0x458
void fn_2_7F2BC(void) {
    return;
}

// .text:0x0007F714 size:0x1A8
void fn_2_7F714(void) {
    return;
}

// .text:0x0007F8BC size:0x240
void fn_2_7F8BC(void) {
    return;
}

// .text:0x0007FAFC size:0x5B4
void fn_2_7FAFC(void) {
    return;
}

// .text:0x000800B0 size:0x23C
void fn_2_800B0(void) {
    return;
}

// .text:0x000802EC size:0x214
void fn_2_802EC(void) {
    return;
}

// .text:0x00080500 size:0xDC
void fn_2_80500(DrawingSceneStruct* scene, s32 index) {
    u8 singlePlayer;
    if ((u32)__cntlzw(lbl_803C66B0.flags[index]) >> 5) {
        singlePlayer = (u32)__cntlzw(lbl_8034E9A0.controllerIndices[0]) >> 5;
        lbl_80371C30[scene->unkIndex + 0x7B].obj->field_0x5C = singlePlayer << 16;
        lbl_80371C30[scene->unkIndex + 0x19].obj->field_0x5C = (singlePlayer + 4) << 16;
        fn_800626EC(index);
        lbl_803C66B0.flags[index] = 1;
    }
    if (lbl_803C66B0.flags[index] == 1) {
        fn_80062674(index);
        lbl_803C66B0.flags[index] = 2;
        g_d_GameSettings._10 = 0;
    }
}

// .text:0x000805DC size:0x250
void fn_2_805DC(void) {
    return;
}

// .text:0x0008082C size:0xAC
void fn_2_8082C(DrawingSceneStruct* scene, s32 index) {
    s32 first;
    if ((u32)__cntlzw(1 - lbl_803C66B0.flags[index]) >> 5) {
        first = !!fn_80042DA8(scene, index + 0x89, 5);
        if (first + !!fn_80042DA8(scene, index + 0x8B, 10) == 2) {
            fn_80062674(index);
            lbl_803C66B0.flags[index] = 2;
        }
    }
}

// .text:0x000808D8 size:0x284
void fn_2_808D8(void) {
    return;
}

// .text:0x00080B5C size:0xD0
void fn_2_80B5C(DrawingSceneStruct* scene, s32 index) {
    s32 count;
    if ((u32)__cntlzw(1 - lbl_803C66B0.flags[index]) >> 5) {
        count = !!fn_80042DA8(scene, index, 0);
        count += !!fn_80042DA8(scene, index + 2, 0);
        count += !!fn_80042DA8(scene, index + 0x89, 10);
        if (count == 3) {
            fn_80062674(index);
            lbl_803C66B0.flags[index] = 2;
        }
    }
}

// .text:0x00080C2C size:0x1E0
void fn_2_80C2C(void) {
    return;
}

// .text:0x00080E0C size:0x150
void fn_2_80E0C(void) {
    return;
}

// .text:0x00080F5C size:0x6CC
void fn_2_80F5C(void) {
    return;
}

// .text:0x00081628 size:0x1174
void fn_2_81628(void) {
    return;
}

// .text:0x0008279C size:0x554
void fn_2_8279C(void) {
    return;
}

// .text:0x00082CF0 size:0xF8
void fn_2_82CF0(void) {
    DrawingSceneStruct* scene = lbl_8034E9A0.scene;
    if (lbl_803C5EA4.unk36 != 0) {
        lbl_80371C30[scene->unkIndex].obj->field_0x5C = 0;
        (&lbl_80371C30[1])[scene->unkIndex].obj->field_0x5C = 0x280000;
        lbl_80371C30[scene->unkIndex + 2].obj->unk64 = lbl_803C5EA4.unk38 + 0x123;
        lbl_80371C30[scene->unkIndex + 3].obj->unk64 = lbl_803C5EA4.unk37 + 0x123;
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
        (&lbl_80371C30[1])[scene->unkIndex].obj->field_0x68 = 4;
        lbl_803C5EA4.unk36 = 0;
    }
    if (lbl_8034E9A0.unk48AF != 0) {
        lbl_8034E9A0.unk48AF = 0;
        fn_80034CEC((u32)scene);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x00082DE8 size:0x70
void fn_2_82DE8(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    lbl_8034E9A0.scene = scene;
    lbl_8034E9A0.unk48AF = 0;
    lbl_803C5EA4.unk37 = 0;
    lbl_803C5EA4.unk38 = 0;
    fn_80034E20(scene, &lbl_2_data_2B4DC);
    lbl_803CC1B8->unk_00 = fn_2_82CF0;
}

// .text:0x00082E58 size:0x68
void fn_2_82E58(void) {
    if (lbl_803CBBCC->previousSelection != 11 && g_d_GameSettings.GameModeSelected != 5) {
        fn_800B0A5C_insertQueue(fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue(fn_2_8279C, 0x3000);
}

// .text:0x00082EC0 size:0x630
void fn_2_82EC0(void) {
    return;
}

// .text:0x000834F0 size:0x1B4
void fn_2_834F0(void) {
    return;
}

// .text:0x000836A4 size:0xA0
void fn_2_836A4(void) {
    if (lbl_803C50E8.pending) fn_800B0A5C_insertQueue(fn_80053FE8, 0);
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.state = 12;
    lbl_8034E978.current = lbl_800FEF70.nextC8;
    if (lbl_803CBBCC->previousSelection != 9) fn_800B0A5C_insertQueue(fn_2_82DE8, 0x3000);
    fn_800B0A5C_insertQueue(fn_2_834F0, 0x3000);
}

// .text:0x00083744 size:0x94
void fn_2_83744(DrawingSceneStruct* scene) {
    if (lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16 == 0x14) {
        lbl_80371C30[scene->unkIndex].obj->field_0x68 = 1;
    }
    if (lbl_80371C30[scene->unkIndex].obj->field_0x5C >> 16 == 0x1E) {
        lbl_803CBCD8.unk4 = 1;
        fn_80062674(0);
        lbl_803C66B0.unk31 = 2;
    }
}

// .text:0x000837D8 size:0x19C
void fn_2_837D8(void) {
    return;
}

// .text:0x00083974 size:0x1C0
void fn_2_83974(void) {
    return;
}

// .text:0x00083B34 size:0x660
void fn_2_83B34(void) {
    return;
}

// .text:0x00084194 size:0x1F4
void fn_2_84194(void) {
    return;
}

// .text:0x00084388 size:0x220
void fn_2_84388(void) {
    return;
}

// .text:0x000845A8 size:0xA00
void fn_2_845A8(void) {
    return;
}

// .text:0x00084FA8 size:0x160
void fn_2_84FA8(void) {
    DrawingSceneStruct* scene;
    s32 i;
    s8 option;
    fn_80034E20(scene=lbl_803CC1B8,&lbl_2_data_2DC8C);
    for(i=0;i<6;i++) {
        if(lbl_80361B20.unkF5==0 && lbl_2_data_2DC84[i]==1) option=6;
        else option=lbl_2_data_2DC84[i];
        fn_800363D8(scene,i+6,2,30,option);
    }
    if(lbl_80361B20.unkF5==0 && lbl_2_data_2DC84[lbl_2_bss_F410.option]==1) option=18;
    else option=lbl_2_data_2DC84[lbl_2_bss_F410.option];
    if(lbl_2_bss_F410.option!=0) fn_800363D8(scene,0,1,32,option);
    lbl_803CBCD8.unk4=0;
    scene->unk18=0;
    lbl_803CC1B8->unk_00=fn_2_845A8;
}

// .text:0x00085108 size:0x54
void fn_2_85108(void) {
    lbl_8034E978.state = 5;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.next;
    fn_800B0A5C_insertQueue(fn_2_84FA8, 0x3000);
}

// .text:0x0008515C size:0x4
void fn_2_8515C(void) {
    return;
}

// .text:0x00085160 size:0x48
void fn_2_85160(void) {
    if (--lbl_803CC1B8->loadingState == 0) {
        fn_800625A4(0, 4);
        fn_800B0A14_removeQueue();
    }
}

// .text:0x000851A8 size:0x168
void fn_2_851A8(void) {
    return;
}

// .text:0x00085310 size:0x1A0
void fn_2_85310(void) {
    return;
}

// .text:0x000854B0 size:0x18C
void fn_2_854B0(void) {
    return;
}
