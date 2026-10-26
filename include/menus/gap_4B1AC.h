#ifndef __MENUS_gap_4B1AC_H_
#define __MENUS_gap_4B1AC_H_

#include "mssbTypes.h"
#include "game/rep_1C0.h"

typedef struct MenusResourceLoads {
    u8 _pad0[0x3D4];
    CompressedDiskRead modes[6];
} MenusResourceLoads;
extern MenusResourceLoads lbl_2_data_12EA8;

typedef struct MenusSavedRoster {
    u8 _pad0[0x1606];
    s8 enabled;
    u8 _pad1607[0x2E14];
    u8 alternate; /* 0x441B */
    u8 _pad441C[0xEC];
} MenusSavedRoster;
typedef struct MenusSavedRosters {
    MenusSavedRoster rosters[3];
} MenusSavedRosters;

typedef struct MenusResourceSlot {
    void (*callback)(s32, struct MenusResourceSlot*);
    s16 state; /* 0x04 */
    s16 timer; /* 0x06 */
    s16 unk8;
    s16 unkA;
    s16 bank; /* 0x0C */
    s16 index; /* 0x0E */
    s16 unk10;
    u8 _pad12[6];
} MenusResourceSlot;

typedef struct MenusResourceBank {
    MenusResourceSlot slots[0x360];
} MenusResourceBank;
typedef struct MenusResourceState {
    MenusResourceBank banks[10];
    u8 _pad32A00[4];
    u8 flags[13][10]; /* 0x32A04 */
    u8 pending;
} MenusResourceState;
extern MenusResourceState* lbl_2_bss_1A8230;
struct DrawingSceneStruct;
struct MenusSceneScript;

typedef struct MenusResourceTables {
    u8 _pad0[0x798];
    union {
        u32* tables[3];
        struct MenusSceneArchive* archives[3];
    };
    u8 _pad7A4[4];
    struct MenusSceneArchive* archive;
} MenusResourceTables;
extern MenusResourceTables lbl_80366B18;

typedef struct MenusCompletionState {
    u8 rosterFlags[NUM_CHOOSABLE_CHARACTERS];
    u8 _pad36[0x90];
    u8 completed[5][4];
    u8 _padDA[4];
    u8 counts[6];
    u8 visited[4];
    u8 chosen[12];
    u8 allCompleted;
} MenusCompletionState;
extern MenusCompletionState* lbl_2_bss_1A8244;

typedef struct MenusResourceEntry {
    union {
        u32 resource;
        void (*callback)(s32, MenusResourceSlot*);
    };
    s16 index;
    s16 unk6;
    s16 bank;
    s16 unkA;
    s16 unkC;
    u8 _padE[2];
} MenusResourceEntry;

typedef struct MenusTimeState {
    u32 unk0;
    u32 high;
    u32 low;
} MenusTimeState;

extern MenusTimeState lbl_803C7898;

void fn_2_4B1AC(void);
void fn_2_4B2D0(void);
void fn_2_4C314(void);
void fn_2_4C36C(void);
s16 fn_2_4C3C4(s32 index);
s16 fn_2_4C3D8(s32 index);
void fn_2_4C3EC(void);
void fn_2_4C6A8(void);
void fn_2_4C81C(void);
void fn_2_4C9C4(void);
void fn_2_4CB94(void);
void fn_2_4CD30(void);
void fn_2_4CEE0(void);
void fn_2_4D194(void);
void fn_2_4D378(void);
void fn_2_4D67C(void);
void fn_2_4D960(void);
void fn_2_4DC24(void);
void fn_2_4DEE8(void);
void fn_2_4E1C0(void);
void fn_2_4E7A4(void);
void fn_2_4E7EC(void);
void fn_2_4E824(void);
void fn_2_4E858(struct DrawingSceneStruct* scene);
void fn_2_4E878(struct DrawingSceneStruct* scene, struct MenusSceneScript* script);
void fn_2_4E898(void);
void fn_2_4E8BC(void);
void fn_2_4E8E0(void);
void fn_2_4E904(void);
void fn_2_4E928(void);
void fn_2_4E94C(void);
BOOL fn_2_4E970(void);
BOOL fn_2_4E9A8(void);
BOOL fn_2_4EABC(void);
BOOL fn_2_4EAF4(void);
BOOL fn_2_4EB2C(void);
BOOL fn_2_4EB64(void);
s32 fn_2_4EB9C(void);
void fn_2_50898(s32 value);
void fn_2_509A4(void);
void fn_2_50B0C(void);
void fn_2_50BF4(s16 index);
void fn_2_50CC0(s16 value);
void fn_2_50D40(void);
void fn_2_50DB4(s32 index, s32 id, u16* source);
void fn_2_50E5C(s32 index);
void fn_2_50F20(s32 index, s32 id, u16* source);
void fn_2_50FC8(s32 index);
void fn_2_510A8(void);
void fn_2_5118C(void);
void fn_2_51190(s32 value, s32 mode);
void fn_2_512B4(void);
s32 fn_2_512B8(void);
void fn_2_512C0(void);
void fn_2_51358(void);
void fn_2_5135C(void);
void fn_2_513DC(void);
void fn_2_513E0(u16* text, s32 x, s32 y, s32 zero, s32 extra, s32 a, s32 b, s32 c);
void fn_2_513E4(void);
void fn_2_513E8(void);
void fn_2_5146C(void);
void fn_2_51470(void);
void fn_2_51568(void);
u32 fn_2_5156C(s32 index, u16 selector);
void fn_2_515DC(u8 mode);
void fn_2_5163C(void);
void fn_2_51890(void);
void fn_2_519F0(void);
void fn_2_51A1C(void);
void fn_2_51C58(void);
void fn_2_520A4(void);
void fn_2_52198(void);
void fn_2_52260(void);
void fn_2_52648(s32 priority);
void fn_2_5268C(void);
void fn_2_52690(void);
void fn_2_53408(void);
void fn_2_535B0(void);
void fn_2_5389C(void);
s32 fn_2_53AA4(MenusResourceSlot* slot);
s32 fn_2_53BC8(MenusResourceSlot* slot);
void fn_2_53CEC(struct DrawingSceneStruct* scene);
void fn_2_53DF8(struct DrawingSceneStruct* scene);
void fn_2_53F04(s32 value);
void fn_2_53F88(s32 value);
void fn_2_5400C(void);
void fn_2_54120(void);
void fn_2_54234(MenusResourceEntry* entries, s32 count);
void fn_2_54354(MenusResourceEntry* entries, s32 count);
void fn_2_54474(void);
void fn_2_54844(void);
void fn_2_54848(void);
void fn_2_54874(void);
void fn_2_54890(void);
void fn_2_549B4(void);
void fn_2_54B38(void);
void fn_2_54BAC(void);

#endif // !__MENUS_gap_4B1AC_H_
