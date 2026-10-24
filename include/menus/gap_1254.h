#ifndef __MENUS_gap_1254_H_
#define __MENUS_gap_1254_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"
#include "menus/gap_3C03C.h"


typedef struct MenusTeamSelections {
    u8 _pad0[2];
    union {
        struct { s8 first[9]; s8 second[9]; };
        s8 teams[2][9];
    };
    s8 order[2][9];        /* 0x14 */
    u8 selectionFlags[2][9]; /* 0x26 */
    u8 unk38[2][9];        /* 0x38 */
    u8 unk4A[2][9];        /* 0x4A cleared with the slot in fn_2_4970 */
} MenusTeamSelections;
extern MenusTeamSelections lbl_803C6724;
typedef struct MenusAutoFillStrategy {
    u8 _pad0[2];
    u8 current; /* 0x2 random 0..2 */
    u8 previous; /* 0x3 avoid repeating the last strategy */
} MenusAutoFillStrategy;
extern MenusAutoFillStrategy lbl_803CBD24;

typedef struct Menus1254State {
    union {
        s32 states[4];
        struct {
            s32 cursor[2];     /* 0x0 per side: roster slot the cursor is on (0..8) */
            s32 prevCursor[2]; /* 0x8 per side: cursor before the last pick was undone (fn_2_4970) */
        };
    };
    s32 options[4];
    s32 previousGridPick[2]; /* 0x20 cached hovered grid charID per side */
    u8 _pad28[6];
    u8 unk2E;
    s8 teamIndices[2];
    u8 _pad31[5];
    u8 unk36;       /* 0x36 scene-transition timer/mode set to 0x1E when the roster screen is left */
    u8 flags37[4];  /* 0x37 per side: pick in progress (cleared by fn_2_4970) */
    u8 reservedOtherPick[2]; /* 0x3B temporarily reserve other side's hovered char during auto-fill */
    u8 flags3D[2];  /* 0x3D per side */
    u8 unk3F;       /* 0x3F challenge mode: set while the roster is locked (fn_2_DFAC refuses picks with the alert sound) */
    u8 _pad40;
    u8 flags41[2];  /* 0x41 per side: a grid pick is pending, the next A press on the roster confirms it (fn_2_DFAC) */
    u8 flags43[2];  /* 0x43 per side: set by fn_2_DFAC when the "clear team" roster action (cursor 10) ran */
    u8 flags45[2];  /* 0x45 per side: a popup (Z on a slot) is open; fn_2_35D0 consumes it */
    u8 unk47[2];    /* 0x47 per side: popup column (0/1), moved with left/right (fn_2_3624) */
    u8 unk49[2];    /* 0x49 per side: cleared with unk47 */
    u8 unk4B[2];    /* 0x4B per side: set with flags45 when the popup opens */
    u8 _pad4D[2];
    u8 unk4F;
    u8 unk50[2];    /* 0x50 per side: colour cycle (L) found the slot's colour family */
    u8 startAllowed[2]; /* 0x52 */
    u8 startAnimating[2]; /* 0x54 */
    u8 unk56;
    u8 _pad57[2];
    u8 flags59[4];  /* 0x59 per side: this side still takes roster input (fn_2_6608 gates fn_2_3624 on it) */
    u8 _pad5D[2];
    u8 unk5F[2];    /* 0x5F per side: "move" mode, a slot was picked up to swap (A), unk61 holds its cursor */
    s8 unk61[2];    /* 0x61 per side: cursor of the picked-up slot, -1 when none */
    u8 _pad63[2];
    u8 unk65[2];    /* 0x65 per side: set by the ready action */
} Menus1254State;

extern Menus1254State lbl_2_bss_F468;

typedef struct MenusSystemState {
    u8 _pad0[0xCF5F];
    u8 mode;
} MenusSystemState;
extern MenusSystemState lbl_803297E0;

/* DOL character-select helpers used by fn_2_2FC0 (see .agent/character_select.md); same signatures as
   include/Unknown/gap_80064754.h and gap_80067AC8.h, repeated here because those headers' lbl_8034E9A0
   view conflicts with MenusSaveState. */
/* Menus view of the DOL select-grid state lbl_803C6028 (include/Unknown/gap_800506E8.h has the DOL one;
   its lbl_800E8558 view conflicts with MenusLineupChoice). */
typedef struct MenusGridState {
    u8 _pad0[0x28];
    s8 slots[0x24];  /* 0x28 per grid cell (lbl_800FDE84): controller index that picked it, or -1 (fn_800506E8) */
    u8 _pad4C[0x28];
    u8 unk74[4];     /* 0x74 per controller index: 1 for the second side's pad when one pad drives both sides */
} MenusGridState;
extern MenusGridState lbl_803C6028;
extern u8 lbl_800FDE84[36]; /* exhibition select-grid cells: base charID per cell, 0xFF = empty */
extern u8 lbl_803CB748[6]; /* unique indices that need an unlock; g_d_GameSettings.charUnlocked[i] is their flag */
void fn_800684A4(void);
void fn_80067F70(s32 player);               /* auto-pick a free colour for player's selection */
void fn_800678CC(s32 player);
void unsure_FillRosterPositions(u8 player);
void characterSelectScreen(s32 player);
void fn_80069854(void);
void fn_800671FC(void);
void fn_800649BC(void);

void fn_2_1254(void);
void fn_2_1258(void);
void fn_2_12A0(s16* value, s16 amount);
void fn_2_12CC(u8* value, u16 amount);
void fn_2_12F8(u16* value, u16 amount);
void fn_2_1328(u32* value, u16 amount);
void fn_2_1354(MenusSortEntry* entries, s32 count, s32 descending);
void fn_2_145C(void);
s32 fn_2_148C(u16* text);
s32 fn_2_14F8(s32 first, s32 second);
u32 fn_2_1554(void);
void fn_2_1578(void);
void fn_2_1800(void);
void fn_2_1A88(void);
void fn_2_1BAC(void);
void fn_2_1C34(u16 buttons);
void fn_2_1D28(void);
void fn_2_1D54(s32* value, u8 index, s32 count);
void fn_2_1DC4(void);
void fn_2_1DC8(void);
void fn_2_1F30(void);
void fn_2_27E0(void);
void fn_2_2BB8(void);
void fn_2_2D1C(void);
void fn_2_2FC0(u8 mode, s32 finish, s32 rebuild);
void fn_2_3204(void);
void fn_2_323C(void);
s32 fn_2_33BC(void);
void fn_2_348C(void);
s32 fn_2_35D0(u8 index);
void fn_2_3624(u8 pad);
void fn_2_4970(u8 side, s32 captainID);
void fn_2_5184(void);
void fn_2_52CC(void);
void fn_2_5444(u8 side);
s32 fn_2_57E8(s32 arg0, s32 arg1);
void fn_2_57F0(void);
void fn_2_5F80(void);
void fn_2_6098(u8 index);
s32 fn_2_60D4(u8 index);
void fn_2_6138(void);
void fn_2_61A0(void);
void fn_2_6484(void);
void fn_2_6608(void);
void fn_2_6784(void);
void fn_2_6884(void);
void fn_2_6AF4(void);
void fn_2_6D3C(void);
void fn_2_7504(void);
void fn_2_7D44(void);
void fn_2_7DDC(void);
void fn_2_86EC(void);
s32 fn_2_8780(s32 mode);
s32 fn_2_8794(s32 mode, s32 index);
void fn_2_87A8(void);
void fn_2_893C(void);
void fn_2_8940(void);
void fn_2_8CF8(void);
void fn_2_95D8(void);
void fn_2_9ACC(void);
s32 fn_2_9F70(s8 side);
void fn_2_A040(s32 group, s32 choice, u8 team, u8 slot);
void fn_2_A1A0(void);
void fn_2_A288(void);
BOOL fn_2_A50C(void);
BOOL fn_2_A62C(void);
void fn_2_A6E0(void);
void fn_2_ABC0(u8 side);
void fn_2_AEE8(void);
void fn_2_B324(void);
void fn_2_B508(void);
void fn_2_B66C(void);
void fn_2_B920(void);
void fn_2_BF90(void);
s8 fn_2_C324(s32 character);
void fn_2_C484(void);
void fn_2_C698(u8 index, u8 side);
void fn_2_C7DC(void);
void fn_2_CA60(void);
void fn_2_CCBC(void);
void fn_2_CCE0(void);
void fn_2_CE44(void);
void fn_2_DFAC(s32 side);
void fn_2_EAE0(void);
void fn_2_EC34(void);
void fn_2_EC54(s32 side);
void fn_2_ED94(void);
void fn_2_F200(u8 side);
void fn_2_FAA0(u8 side);
void fn_2_FCB4(u8 side);
void fn_2_102C8(u8 side);
void fn_2_104FC(void);
void fn_2_110B0(void);
BOOL fn_2_112F4(DrawingSceneStruct* scene, s32 offset, s32 index, u16* ids, u16 value);
void fn_2_11340(void);
void fn_2_11698(void);
void fn_2_11EA8(void);
void fn_2_120D0(void);
void fn_2_1216C(void);

#endif // !__MENUS_gap_1254_H_
