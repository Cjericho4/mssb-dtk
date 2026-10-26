#include "menus/gap_4B1AC.h"
#include "menus/rep_0438.h"
#include "menus/rep_0B08.h"
#include "menus/rep_08E8.h"
#include "menus/gap_1B1BC.h"
#include "string.h"
#include "Dolphin/GX/GXPixel.h"
#include "menus/rep_10C0.h"
#include "UnknownHeaders.h"
#include "game/rep_1C0.h"
#include "game/rep_3448.h"

#include "menus/gap_8E6A4.h"
extern CompressedDiskRead lbl_2_data_1FF94;
extern CompressedDiskRead lbl_2_data_1FF84;
extern void fn_800111B4(struct MenusSceneArchive* archive);
extern s32 fn_800627C4(void);
extern void fn_800216F8(s32 mode, s32 (*callback)(void));
extern CompressedDiskRead lbl_2_data_132DC[];
extern CompressedDiskRead lbl_2_data_1326C[];
extern CompressedDiskRead lbl_2_data_1325C[];
extern CompressedDiskRead lbl_2_data_1324C[];
extern CompressedDiskRead lbl_2_data_1323C[];
extern s32 fn_80035838(CompressedDiskRead* list, s32 count);
#include "menus/gap_8782C.h"

extern void fn_80035B50(s32 arg0);
extern void starMissionRelated2(void);
#include "menus/gap_71EC4.h"
#include "menus/gap_D08.h"
extern void fn_80053FE8(void);
extern void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_800AD054(u32 high, u32 low);
extern s16 lbl_2_data_373C[CHALLENGE_PURCHASE_COUNT];
extern s16 lbl_2_data_3ED4[];
extern s16 lbl_2_data_3EC8[];

extern MenusMenuBuffer lbl_2_bss_5600;
extern MenusMenuBuffer* lbl_2_data_1E99C[];
extern s16 lbl_2_bss_9E08;
extern u16 lbl_2_bss_9600[2];
extern u16 lbl_2_bss_9604[2];
extern u16 lbl_2_bss_9A08[2][256];
extern u16 lbl_2_bss_9608[2][256];

static inline u32* menuStringTable(void) {
    return &lbl_80366B18.tables[lbl_2_bss_1A824C->panel.mode][1];
}

static inline u16* resolveMenuString(u32* table, s32 id, u16* source) {
    if (id == -1) return source;
    return (u16*)table[id];
}

// .text:0x0004B1AC size:0x124
void fn_2_4B1AC(void) {
    s32 delta;
    fn_2_4B2D0();
    if (lbl_2_bss_1A824C->unk197843 == 0) {
        lbl_2_bss_1A824C->unk197778 = 0;
        lbl_2_bss_1A824C->unk197798 = 0;
    } else if (lbl_2_bss_1A824C->unk197843 == 1) {
        if (lbl_2_bss_1A8248->counter == 1) delta = -1;
        else delta = -lbl_2_bss_1A8248->counter / 2;
        lbl_2_bss_1A8248->previousCounter = lbl_2_bss_1A8248->counter;
        lbl_2_bss_1A8248->counter += delta;
        if (lbl_2_bss_1A8248->counter > 999) lbl_2_bss_1A8248->counter = 999;
        if (lbl_2_bss_1A8248->counter < 0) lbl_2_bss_1A8248->counter = 0;
        lbl_2_bss_1A824C->unk19777A = delta;
        lbl_2_bss_1A824C->unk197798 = delta;
    } else if (lbl_2_bss_1A824C->unk197843 == 2) {
        lbl_2_bss_1A824C->unk197796 = 0;
        lbl_2_bss_1A824C->unk197798 = 0;
    }
    starMissionRelated2();
}

// .text:0x0004B2D0 size:0x1044
void fn_2_4B2D0(void) {
    return;
}

// .text:0x0004C314 size:0x58
void fn_2_4C314(void) {
    MenusCompletionState* state = lbl_2_bss_1A8244;
    s32 all = 1;
    s32 i;
    s32 j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            if (state->completed[i][j] == 0) all = 0;
        }
    }
    state->allCompleted = all;
}

// .text:0x0004C36C size:0x58
void fn_2_4C36C(void) {
    MenusSceneState* scene;
    lbl_2_bss_1A8248->unk4424 = 1;
    lbl_2_bss_1A8248->unk4425 = 1;
    lbl_2_bss_1A8248->unk441B = 0;
    scene = lbl_2_bss_1A8248;
    lbl_2_bss_1A8244->completed[scene->unk441C][scene->unk4415] = 1;
    lbl_2_bss_1A8248->unk1606 = 1;
}

// .text:0x0004C3C4 size:0x14
s16 fn_2_4C3C4(s32 index) {
    return lbl_2_data_3ED4[index];
}

// .text:0x0004C3D8 size:0x14
s16 fn_2_4C3D8(s32 index) {
    return lbl_2_data_3EC8[index];
}

// .text:0x0004C3EC size:0x2BC
void fn_2_4C3EC(void) {
    return;
}

// .text:0x0004C6A8 size:0x174
/* Rebuild challenge purchase flags from the menu's saved and current selections. */
void fn_2_4C6A8(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    s32 i;
    for (i = 0; i < CHALLENGE_PURCHASE_COUNT; i++) settings->challengePurchaseFlags[i] = 0;
    for (i = 0; i < CHALLENGE_PURCHASE_COUNT; i++) {
        if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248->copiedFlags[i] != 0) {
            settings->challengePurchaseFlags[i] = 1;
        }
    }
    if (lbl_2_bss_1A8248->unk_0x444B != -1) {
        settings->challengePurchaseFlags[lbl_2_bss_1A8248->unk_0x444B] = 1;
    }
}

// .text:0x0004C81C size:0x1A8
void fn_2_4C81C(void) {
    return;
}

// .text:0x0004C9C4 size:0x1D0
void fn_2_4C9C4(void) {
    return;
}

// .text:0x0004CB94 size:0x19C
void fn_2_4CB94(void) {
    return;
}

// .text:0x0004CD30 size:0x1B0
void fn_2_4CD30(void) {
    return;
}

// .text:0x0004CEE0 size:0x2B4
void fn_2_4CEE0(void) {
    return;
}

// .text:0x0004D194 size:0x1E4
void fn_2_4D194(void) {
    return;
}

// .text:0x0004D378 size:0x304
void fn_2_4D378(void) {
    return;
}

// .text:0x0004D67C size:0x2E4
void fn_2_4D67C(void) {
    return;
}

// .text:0x0004D960 size:0x2C4
void fn_2_4D960(void) {
    return;
}

// .text:0x0004DC24 size:0x2C4
void fn_2_4DC24(void) {
    return;
}

// .text:0x0004DEE8 size:0x2D8
void fn_2_4DEE8(void) {
    return;
}

// .text:0x0004E1C0 size:0x5E4
void fn_2_4E1C0(void) {
    return;
}

// .text:0x0004E7A4 size:0x48
void fn_2_4E7A4(void) {
    fn_8003BF54(0, 0, 0, 1, 1, 4, 1, 3, 0);
}

// .text:0x0004E7EC size:0x38
void fn_2_4E7EC(void) {
    Rep10C0State* state = lbl_2_bss_1A824C;
    fn_800AD054(state->timeHigh, state->timeLow);
}

// .text:0x0004E824 size:0x34
void fn_2_4E824(void) {
    lbl_2_bss_1A824C->timeHigh = lbl_803C7898.high;
    lbl_2_bss_1A824C->timeLow = lbl_803C7898.low;
}

// .text:0x0004E858 size:0x20
void fn_2_4E858(DrawingSceneStruct* scene) {
    fn_80034CEC((u32)scene);
}

// .text:0x0004E878 size:0x20
void fn_2_4E878(DrawingSceneStruct* scene, struct MenusSceneScript* script) {
    fn_80034E20(scene, script);
}

// .text:0x0004E898 size:0x24
void fn_2_4E898(void) {
    fn_80035B50(23);
}

// .text:0x0004E8BC size:0x24
void fn_2_4E8BC(void) {
    fn_80035B50(24);
}

// .text:0x0004E8E0 size:0x24
void fn_2_4E8E0(void) {
    fn_80035B50(23);
}

// .text:0x0004E904 size:0x24
void fn_2_4E904(void) {
    fn_80035B50(12);
}

// .text:0x0004E928 size:0x24
void fn_2_4E928(void) {
    fn_80035B50(21);
}

// .text:0x0004E94C size:0x24
void fn_2_4E94C(void) {
    fn_80035B50(8);
}

// .text:0x0004E970 size:0x38
BOOL fn_2_4E970(void) {
    return fn_80035838(lbl_2_data_132DC, 23) != 0;
}

// .text:0x0004E9A8 size:0x114
BOOL fn_2_4E9A8(void) {
    MenusResourceLoads* loads = &lbl_2_data_12EA8;
    switch ((s32)lbl_2_bss_1A8248->unk441C) {
    case 0:
        if (fn_80035838(&loads->modes[0], 24) == 0) return FALSE;
        break;
    case 1:
        if (fn_80035838(&loads->modes[1], 24) == 0) return FALSE;
        break;
    case 2:
        if (fn_80035838(&loads->modes[2], 24) == 0) return FALSE;
        break;
    case 3:
        if (fn_80035838(&loads->modes[3], 24) == 0) return FALSE;
        break;
    case 4:
        if (fn_80035838(&loads->modes[4], 24) == 0) return FALSE;
        break;
    case 5:
        if (fn_80035838(&loads->modes[5], 24) == 0) return FALSE;
        break;
    }
    return TRUE;
}

// .text:0x0004EABC size:0x38
BOOL fn_2_4EABC(void) {
    return fn_80035838(lbl_2_data_1326C, 23) != 0;
}

// .text:0x0004EAF4 size:0x38
BOOL fn_2_4EAF4(void) {
    return fn_80035838(lbl_2_data_1325C, 12) != 0;
}

// .text:0x0004EB2C size:0x38
BOOL fn_2_4EB2C(void) {
    return fn_80035838(lbl_2_data_1324C, 21) != 0;
}

// .text:0x0004EB64 size:0x38
BOOL fn_2_4EB64(void) {
    return fn_80035838(lbl_2_data_1323C, 8) != 0;
}

// .text:0x0004EB9C size:0x1CFC
s32 fn_2_4EB9C(void) {
    return 0;
}

// .text:0x00050898 size:0x10C
void fn_2_50898(s32 value) {
    s32 i;
    lbl_2_bss_1A824C->panel.unk1B8C = value;
    lbl_2_bss_1A824C->panel.unk1BB4 = 1;
    lbl_2_bss_1A824C->panel.unk1BB8 = 1;
    for (i = 0; i < 168; i++) lbl_2_bss_1A824C->panel.values[i] = 0;
    lbl_2_bss_1A824C->panel.unk1BA6 = 1;
    lbl_2_bss_1A824C->panel.unk1B04 = 1;
    lbl_2_bss_1A824C->panel.commandCounters[2] = 0;
}

// .text:0x000509A4 size:0x168
/* Copy the selected menu text page and run its queued panel interaction. */
void fn_2_509A4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    s32 result;
    switch ((s8)scene->field15_0x28) {
    case 0:
        lbl_2_bss_1A824C->panel.unk1BA8 = 0;
        lbl_2_bss_1A824C->panel.unk1BA6 = 0;
        memcpy(&lbl_2_bss_5600, lbl_2_data_1E99C[lbl_2_bss_1A824C->panel.unk1BAA], sizeof(MenusMenuBuffer));
        lbl_2_bss_1A824C->panel.textBuffer = &lbl_2_bss_5600;
        scene->field15_0x28++;
    case 1:
        result = fn_2_4EB9C();
        if ((s16)result != 0) {
            switch ((s16)result) {
            case 1:
                lbl_803CC1B8->currentDrawingItem->loadingState = 1;
                fn_800B0A14_removeQueue();
                break;
            default:
                lbl_803CC1B8->currentDrawingItem->loadingState = 1;
                fn_800B0A14_removeQueue();
                break;
            }
            scene->field15_0x28 = 0;
        }
        break;
    case 2: break;
    }
    if (lbl_2_bss_1A824C->unk19783F == 1) {
        lbl_803CC1B8->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
        scene->field15_0x28 = 0;
    }
}

// .text:0x00050B0C size:0xE8
void fn_2_50B0C(void) {
    return;
}

// .text:0x00050BF4 size:0xCC
void fn_2_50BF4(s16 index) {
    lbl_2_bss_1A824C->panel.unk1BA8 = 0;
    lbl_2_bss_1A824C->panel.unk1BA6 = 0;
    lbl_2_bss_1A824C->panel.unk1BAA = index;
    lbl_2_bss_1A824C->panel.unk1BA0 = 0;
    lbl_2_bss_1A824C->panel.unk1B9E = 0;
    lbl_2_bss_1A824C->panel.unk1E72 = 0;
    lbl_2_bss_1A824C->panel.unk1E70 = 0;
    memcpy(&lbl_2_bss_5600, lbl_2_data_1E99C[lbl_2_bss_1A824C->panel.unk1BAA], sizeof(MenusMenuBuffer));
    lbl_2_bss_1A824C->panel.textBuffer = &lbl_2_bss_5600;
    fn_2_4EB9C();
}

// .text:0x00050CC0 size:0x80
void fn_2_50CC0(s16 value) {
    QueueEntry* task;
    lbl_2_bss_1A824C->panel.unk1BAA = value;
    lbl_2_bss_1A824C->panel.unk1BA0 = 0;
    lbl_2_bss_1A824C->panel.unk1B9E = 0;
    lbl_2_bss_1A824C->panel.unk1E72 = 0;
    lbl_2_bss_1A824C->panel.unk1E70 = 0;
    task = fn_800B0A5C_insertQueue(fn_2_509A4, 4);
    task->unk28 = 0;
}

// .text:0x00050D40 size:0x74
void fn_2_50D40(void) {
    return;
}

// .text:0x00050DB4 size:0xA8
void fn_2_50DB4(s32 index, s32 id, u16* source) {
    u32* table = menuStringTable();
    u16* output;
    u16 code;
    s32 old;
    if (lbl_2_bss_9600[index] != 0) lbl_2_bss_9600[index]--;
    source = resolveMenuString(table, id, source);
    output = lbl_2_bss_9608[index];
    do {
        code = *source++;
        old = lbl_2_bss_9600[index];
        lbl_2_bss_9600[index] = old + 1;
        output[old] = code;
        if (lbl_2_bss_9600[index] == 256) return;
    } while (!(code & 0x4000) || (code & 0x3FFF));
}

// .text:0x00050E5C size:0xC4
void fn_2_50E5C(s32 index) {
    s32 i;
    lbl_2_bss_9600[index] = 0;
    for (i = 0; i < 256; i++) lbl_2_bss_9608[index][i] = 0;
}

// .text:0x00050F20 size:0xA8
void fn_2_50F20(s32 index, s32 id, u16* source) {
    u32* table = menuStringTable();
    u16* output;
    u16 code;
    s32 old;
    if (lbl_2_bss_9604[index] != 0) lbl_2_bss_9604[index]--;
    source = resolveMenuString(table, id, source);
    output = lbl_2_bss_9A08[index];
    do {
        code = *source++;
        old = lbl_2_bss_9604[index];
        lbl_2_bss_9604[index] = old + 1;
        output[old] = code;
        if (lbl_2_bss_9604[index] == 256) return;
    } while (!(code & 0x4000) || (code & 0x3FFF));
}

// .text:0x00050FC8 size:0xE0
void fn_2_50FC8(s32 index) {
    s32 i = 0;
    lbl_2_bss_9604[index] = 0;
    lbl_2_bss_1A824C->panel.bufferFlags[index] = 1;
    for (; i < 256; i++) lbl_2_bss_9A08[index][i] = 0;
}

// .text:0x000510A8 size:0xE4
void fn_2_510A8(void) {
    s32 i = 0;
    lbl_2_bss_9604[1] = 0;
    lbl_2_bss_9604[0] = 0;
    lbl_2_bss_1A824C->panel.bufferFlags[1] = 1;
    lbl_2_bss_1A824C->panel.bufferFlags[0] = 1;
    for (; i < 256; i++) {
        lbl_2_bss_9A08[0][i] = 0;
        lbl_2_bss_9A08[1][i] = 0;
    }
}

// .text:0x0005118C size:0x4
void fn_2_5118C(void) {
    return;
}

// .text:0x00051190 size:0x124
void fn_2_51190(s32 value, s32 mode) {
    s32 i;
    lbl_2_bss_1A824C->panel.unk1BB4 = 1;
    lbl_2_bss_1A824C->panel.unk1BB8 = 1;
    for (i = 0; i < 168; i++) lbl_2_bss_1A824C->panel.values[i] = 0;
    lbl_2_bss_1A824C->panel.unk1B8C = value;
    lbl_2_bss_1A824C->panel.unk1B04 = mode;
    lbl_2_bss_1A824C->panel.unk1B9E = 0;
    lbl_2_bss_1A824C->panel.commandCounters[2] = 0;
    lbl_2_bss_1A824C->panel.unk1E70 = 0;
}

// .text:0x000512B4 size:0x4
void fn_2_512B4(void) {
    return;
}

// .text:0x000512B8 size:0x8
s32 fn_2_512B8(void) {
    return 0;
}

// .text:0x000512C0 size:0x98
void fn_2_512C0(void) {
    return;
}

// .text:0x00051358 size:0x4
void fn_2_51358(void) {
    return;
}

// .text:0x0005135C size:0x80
void fn_2_5135C(void) {
    return;
}

// .text:0x000513DC size:0x4
void fn_2_513DC(void) {
    return;
}

// .text:0x000513E0 size:0x4
void fn_2_513E0(u16* text, s32 x, s32 y, s32 zero, s32 extra, s32 a, s32 b, s32 c) {
    return;
}

// .text:0x000513E4 size:0x4
void fn_2_513E4(void) {
    return;
}

// .text:0x000513E8 size:0x84
void fn_2_513E8(void) {
    return;
}

// .text:0x0005146C size:0x4
void fn_2_5146C(void) {
    return;
}

// .text:0x00051470 size:0xF8
void fn_2_51470(void) {
    return;
}

// .text:0x00051568 size:0x4
void fn_2_51568(void) {
    return;
}

// .text:0x0005156C size:0x70
u32 fn_2_5156C(s32 index, u16 selector) {
    if (selector == 0) {
        return lbl_80366B18.tables[lbl_2_bss_1A824C->panel.mode][index + 1];
    }
    return lbl_80366B18.tables[lbl_2_bss_1A824C->panel.mode][index + 1];
}

// .text:0x000515DC size:0x60
void fn_2_515DC(u8 mode) {
    memset(&lbl_2_bss_1A824C->panel, 0, sizeof(MenusPanelState));
    lbl_2_bss_1A824C->panel.mode = mode;
    fn_2_4906C();
}

// .text:0x0005163C size:0x254
void fn_2_5163C(void) {
    return;
}

// .text:0x00051890 size:0x160
void fn_2_51890(void) {
    MenusRosterState* settings=&lbl_80361B20;
    MenusSavedRosters* data=(MenusSavedRosters*)&lbl_80354768;
    if(data->rosters[settings->mode].enabled) {
        if(data->rosters[lbl_8034E9A0.unk4754].alternate) {
            lbl_2_bss_F410.rosterMode=1;
            lbl_2_bss_33FBCC.mode=3;
            lbl_2_bss_33FBCC.flags[0]=0;
            lbl_2_bss_33FBCC.flags[1]=1;
            lbl_2_bss_33FBCC.flags[2]=1;
            lbl_2_bss_33FBCC.flags[3]=1;
            lbl_2_bss_33FBCC.flags[4]=1;
            lbl_2_bss_33FBCC.flags[5]=1;
        } else {
            lbl_2_bss_F410.rosterMode=2;
            lbl_2_bss_33FBCC.mode=2;
            lbl_2_bss_33FBCC.flags[0]=0;
            lbl_2_bss_33FBCC.flags[1]=0;
            lbl_2_bss_33FBCC.flags[2]=1;
            lbl_2_bss_33FBCC.flags[3]=1;
            lbl_2_bss_33FBCC.flags[4]=1;
            lbl_2_bss_33FBCC.flags[5]=1;
        }
    } else {
        if(data->rosters[lbl_8034E9A0.unk4754].alternate) {
            lbl_2_bss_F410.rosterMode=1;
            lbl_2_bss_33FBCC.mode=1;
            lbl_2_bss_33FBCC.flags[0]=0;
            lbl_2_bss_33FBCC.flags[1]=1;
            lbl_2_bss_33FBCC.flags[2]=0;
            lbl_2_bss_33FBCC.flags[3]=1;
            lbl_2_bss_33FBCC.flags[4]=1;
            lbl_2_bss_33FBCC.flags[5]=1;
        } else {
            lbl_2_bss_F410.rosterMode=0;
            lbl_2_bss_33FBCC.mode=0;
            lbl_2_bss_33FBCC.flags[0]=1;
            lbl_2_bss_33FBCC.flags[1]=0;
            lbl_2_bss_33FBCC.flags[2]=0;
            lbl_2_bss_33FBCC.flags[3]=0;
            lbl_2_bss_33FBCC.flags[4]=0;
            lbl_2_bss_33FBCC.flags[5]=1;
        }
    }
}

// .text:0x000519F0 size:0x2C
void fn_2_519F0(void) {
    fn_800B0A5C_insertQueue(fn_2_89F70, 0x3000);
}

// .text:0x00051A1C size:0x23C
void fn_2_51A1C(void) {
    return;
}

// .text:0x00051C58 size:0x44C
void fn_2_51C58(void) {
    return;
}

// .text:0x000520A4 size:0xF4
void fn_2_520A4(void) {
    MenusRosterTransition* state = &lbl_2_bss_33FBCC;
    switch ((s32)state->state) {
    case 0:
        fn_2_51890();
        fn_800B0A5C_insertQueue(fn_2_89F70, 0x3000);
        lbl_2_bss_33FBCC.command = 0x51;
        state->state = 1;
        break;
    case 1:
        if (state->command != 0x51) fn_2_51C58();
        break;
    case 2:
        state->command = 0x52;
        state->pending = 1;
        state->state = 0;
        lbl_2_bss_9E08 = 10;
        break;
    case 3:
        state->command = 0x52;
        lbl_2_bss_9E08 = 5;
        state->pending = 1;
        state->state = 0;
        break;
    case 4:
        fn_2_51A1C();
        break;
    }
}

// .text:0x00052198 size:0xC8
void fn_2_52198(void) {
    s32 mode;
    if (lbl_803CBBCC->previousSelection == 5 || lbl_803CBBCC->previousSelection == 16) {
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        fn_800B0A5C_insertQueue(fn_2_82DE8, 0x3000);
    }
    if (lbl_8034E9A0.unk4756 == 0) mode = 11;
    else {
        lbl_8034E978.unk3 = lbl_8034E9A0.unk4711;
        mode = 16;
    }
    lbl_8034E978.state = mode;
    lbl_8034E978.previous = lbl_8034E978.current;
    lbl_8034E978.current = lbl_800FEF70.entries[mode].next;
    fn_800B0A5C_insertQueue(fn_2_8ABFC, 0x3000);
}

// .text:0x00052260 size:0x3E8
void fn_2_52260(void) {
    return;
}

// .text:0x00052648 size:0x44
void fn_2_52648(s32 priority) {
    fn_800B0A5C_insertQueue(fn_2_52690, priority);
    lbl_8034E9A0.unk472B = g_d_GameSettings._06;
}

// .text:0x0005268C size:0x4
void fn_2_5268C(void) {
    return;
}

// .text:0x00052690 size:0xD78
void fn_2_52690(void) {
    return;
}

// .text:0x00053408 size:0x1A8
void fn_2_53408(void) {
    return;
}

// .text:0x000535B0 size:0x2EC
void fn_2_535B0(void) {
    return;
}

// .text:0x0005389C size:0x208
void fn_2_5389C(void) {
    return;
}

// .text:0x00053AA4 size:0x124
s32 fn_2_53AA4(MenusResourceSlot* slot) {
    s16 bank = slot->bank;
    s16 result = -1;
    if (lbl_2_bss_1A8230->flags[0][bank] != 0) result = 0;
    else if (lbl_2_bss_1A8230->flags[1][bank] != 0) result = 2;
    else if (lbl_2_bss_1A8230->flags[8][bank] != 0) result = 5;
    else if (lbl_2_bss_1A8230->flags[2][bank] != 0) result = 23;
    else if (lbl_2_bss_1A8230->flags[3][bank] != 0) result = 8;
    else if (lbl_2_bss_1A8230->flags[4][bank] != 0) result = 11;
    else if (lbl_2_bss_1A8230->flags[5][bank] != 0) result = 14;
    else if (lbl_2_bss_1A8230->flags[6][bank] != 0) result = 17;
    else if (lbl_2_bss_1A8230->flags[7][bank] != 0) result = 20;
    else if (lbl_2_bss_1A8230->flags[9][bank] != 0) result = 24;
    else if (lbl_2_bss_1A8230->flags[10][bank] != 0) result = 27;
    else if (lbl_2_bss_1A8230->flags[11][bank] != 0) result = 30;
    else if (lbl_2_bss_1A8230->flags[12][bank] != 0) result = 33;
    return result;
}

// .text:0x00053BC8 size:0x124
s32 fn_2_53BC8(MenusResourceSlot* slot) {
    s16 bank = slot->bank;
    s16 result = -1;
    if (lbl_2_bss_1A8234->flags[0][bank] != 0) result = 0;
    else if (lbl_2_bss_1A8234->flags[1][bank] != 0) result = 2;
    else if (lbl_2_bss_1A8234->flags[8][bank] != 0) result = 5;
    else if (lbl_2_bss_1A8234->flags[2][bank] != 0) result = 23;
    else if (lbl_2_bss_1A8234->flags[3][bank] != 0) result = 8;
    else if (lbl_2_bss_1A8234->flags[4][bank] != 0) result = 11;
    else if (lbl_2_bss_1A8234->flags[5][bank] != 0) result = 14;
    else if (lbl_2_bss_1A8234->flags[6][bank] != 0) result = 17;
    else if (lbl_2_bss_1A8234->flags[7][bank] != 0) result = 20;
    else if (lbl_2_bss_1A8234->flags[9][bank] != 0) result = 24;
    else if (lbl_2_bss_1A8234->flags[10][bank] != 0) result = 27;
    else if (lbl_2_bss_1A8234->flags[11][bank] != 0) result = 30;
    else if (lbl_2_bss_1A8234->flags[12][bank] != 0) result = 33;
    return result;
}

// .text:0x00053CEC size:0x10C
void fn_2_53CEC(DrawingSceneStruct* scene) {
    MenusResourceSlot* entry;
    s32 bank;
    s32 slot;
    for (bank = 0; bank < 10; bank++) {
        for (slot = 0; slot < 0x360; slot++) {
            entry = &lbl_2_bss_1A8230->banks[bank].slots[slot];
            if (entry->callback != 0) {
                lbl_80371C30[scene->unkIndex + entry->index].obj->field_0x68 = 0;
                lbl_80371C30[scene->unkIndex + entry->index].obj->flags &= ~2;
            }
        }
    }
}

// .text:0x00053DF8 size:0x10C
void fn_2_53DF8(DrawingSceneStruct* scene) {
    MenusResourceSlot* entry;
    s32 bank;
    s32 slot;
    for (bank = 0; bank < 70; bank++) {
        for (slot = 0; slot < 0x360; slot++) {
            entry = &lbl_2_bss_1A8234->banks[bank].slots[slot];
            if (entry->callback != 0) {
                lbl_80371C30[scene->unkIndex + entry->index].obj->field_0x68 = 0;
                lbl_80371C30[scene->unkIndex + entry->index].obj->flags &= ~2;
            }
        }
    }
}

// .text:0x00053F04 size:0x84
void fn_2_53F04(s32 value) {
    s32 bank;
    s32 slot;
    for (bank = 0; bank < 10; bank++) {
        for (slot = 0; slot < 0x360; slot++) {
            MenusResourceSlot* entry = &lbl_2_bss_1A8230->banks[bank].slots[slot];
            if (entry->callback != 0) entry->callback(value, entry);
        }
    }
}

// .text:0x00053F88 size:0x84
void fn_2_53F88(s32 value) {
    s32 bank;
    s32 slot;
    for (bank = 0; bank < 70; bank++) {
        for (slot = 0; slot < 0x360; slot++) {
            MenusResourceSlot* entry = &lbl_2_bss_1A8234->banks[bank].slots[slot];
            if (entry->callback != 0) entry->callback(value, entry);
        }
    }
}

// .text:0x0005400C size:0x114
void fn_2_5400C(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        lbl_2_bss_1A8230->flags[0][i] = 0;
        lbl_2_bss_1A8230->flags[1][i] = 0;
        lbl_2_bss_1A8230->flags[2][i] = 0;
        lbl_2_bss_1A8230->flags[3][i] = 0;
        lbl_2_bss_1A8230->flags[4][i] = 0;
        lbl_2_bss_1A8230->flags[5][i] = 0;
        lbl_2_bss_1A8230->flags[6][i] = 0;
        lbl_2_bss_1A8230->flags[7][i] = 0;
        lbl_2_bss_1A8230->flags[8][i] = 0;
        lbl_2_bss_1A8230->flags[9][i] = 0;
        lbl_2_bss_1A8230->flags[10][i] = 0;
        lbl_2_bss_1A8230->flags[11][i] = 0;
        lbl_2_bss_1A8230->flags[12][i] = 0;
    }
}

// .text:0x00054120 size:0x114
void fn_2_54120(void) {
    s32 i;
    for (i = 0; i < 70; i++) {
        lbl_2_bss_1A8234->flags[0][i] = 0;
        lbl_2_bss_1A8234->flags[1][i] = 0;
        lbl_2_bss_1A8234->flags[2][i] = 0;
        lbl_2_bss_1A8234->flags[3][i] = 0;
        lbl_2_bss_1A8234->flags[4][i] = 0;
        lbl_2_bss_1A8234->flags[5][i] = 0;
        lbl_2_bss_1A8234->flags[6][i] = 0;
        lbl_2_bss_1A8234->flags[7][i] = 0;
        lbl_2_bss_1A8234->flags[8][i] = 0;
        lbl_2_bss_1A8234->flags[9][i] = 0;
        lbl_2_bss_1A8234->flags[10][i] = 0;
        lbl_2_bss_1A8234->flags[11][i] = 0;
        lbl_2_bss_1A8234->flags[12][i] = 0;
    }
}

// .text:0x00054234 size:0x120
void fn_2_54234(MenusResourceEntry* entries, s32 count) {
    while (count > 0) {
        MenusResourceSlot* slot = &lbl_2_bss_1A8230->banks[entries->bank].slots[entries->index];
        slot->callback = entries->callback;
        slot->unk8 = entries->index;
        slot->unkA = entries->unk6;
        slot->bank = entries->bank;
        slot->index = entries->unkA;
        slot->unk10 = entries->unkC;
        entries++;
        count--;
    }
}

// .text:0x00054354 size:0x120
void fn_2_54354(MenusResourceEntry* entries, s32 count) {
    while (count > 0) {
        MenusResourceSlot* slot = &lbl_2_bss_1A8234->banks[entries->bank].slots[entries->index];
        slot->callback = entries->callback;
        slot->unk8 = entries->index;
        slot->unkA = entries->unk6;
        slot->bank = entries->bank;
        slot->index = entries->unkA;
        slot->unk10 = entries->unkC;
        entries++;
        count--;
    }
}

// .text:0x00054474 size:0x3D0
void fn_2_54474(void) {
    return;
}

// .text:0x00054844 size:0x4
void fn_2_54844(void) {
    return;
}

// .text:0x00054848 size:0x2C
void fn_2_54848(void) {
    lbl_2_bss_1A824C->unk197754 = 1;
    lbl_2_bss_1A824C->unk197752 = 10;
}

// .text:0x00054874 size:0x1C
void fn_2_54874(void) {
    lbl_2_bss_1A824C->unk197754 = 0;
}

// .text:0x00054890 size:0x124
void fn_2_54890(void) {
    return;
}

// .text:0x000549B4 size:0x184
/* Load the menu archive, prepare its resources, and wait for the queued scene. */
void fn_2_549B4(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch ((s8)scene->field15_0x28) {
    case 0:
        lbl_80366B18.archives[2] = ARAMTransfer(&lbl_2_data_1FF94, NULL, 1, NULL);
        scene->field15_0x28 = 1;
        break;
    case 1:
        if (lbl_803C6CF8.allowLoad == 1) {
            fn_800111B4(lbl_80366B18.archives[2]);
            scene->field15_0x28 = 2;
        }
        break;
    case 2:
        if (fn_80035838(&lbl_2_data_1FF84, 10) != 0) scene->field15_0x28 = 3;
        break;
    case 3:
        scene->loadingState = 0;
        fn_800216F8(4, fn_800627C4);
        scene->field15_0x28 = 4;
        break;
    case 4:
        if (scene->loadingState != 0) {
            scene->loadingState = 0;
            scene->field15_0x28 = 5;
        }
        break;
    case 5: {
        DrawingSceneStruct* child;
        lbl_2_bss_1A824C->objectCount = 1;
        child = (DrawingSceneStruct*)fn_800B0A5C_insertQueue(fn_2_8E8A4, 2);
        child->field15_0x28 = 0;
        child->unkIndex2 = 12;
        scene->loadingState = 0;
        scene->field15_0x28 = 6;
        break;
    }
    case 6:
        if (scene->loadingState == 1) {
            scene->currentDrawingItem->loadingState = 1;
            fn_800B0A14_removeQueue();
            scene->field15_0x28 = 0;
        }
        break;
    }
}

// .text:0x00054B38 size:0x74
void fn_2_54B38(void) {
    if (g_hugeAnimStruct.field269_0x307a == 2) {
        if (lbl_2_bss_1A8248->unk44F2 != 4) fn_2_68E68();
        fn_2_47FF8();
        if (lbl_2_bss_1A8248->unk44F2 != 4) fn_2_47CFC();
    }
    GXSetZCompLoc(GX_FALSE);
}

// .text:0x00054BAC size:0x4
void fn_2_54BAC(void) {
    return;
}
