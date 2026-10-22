#ifndef __UNKNOWN_gap_8001196C_H_
#define __UNKNOWN_gap_8001196C_H_

#include "mssbTypes.h"
void fn_8003AC90(void);

void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011B64(void);
void fn_80011BE4(void);
void fn_80011CA8(void);
void fn_800126EC(void);
void LoadModel(void);
void fn_80012B90(void);
void fn_80013680(void);
void fn_80014204(void);
void fn_800145F8(void);
void fn_80014990(void);
void fn_80014A18(void);
void fn_80014D4C(void);
void fn_80014E50(void);
void fn_80014F40(void);
void fn_8001500C(void);
void fn_80015468(void);
void fn_8001594C(void);
void fn_80016344(void);
void fn_80016710(void);
BOOL fn_80016F7C(void);
void fn_80017098(void);
void fn_80017340(void);

/* per-slot animation/actor record (AnimationStruct in UnknownHeaders.h), 0x27C bytes */
typedef struct Gap8001196CAnim {
    u8 _pad0[8];
    /* 0x008 */ u8* fileBuffer;              /* body .gpc / anim bank buffer */
    u8 _padC[4];
    /* 0x010 */ struct Gap8001196CSlotTable* slotTables[9];
    u8 _pad34[0x252 - 0x34];
    /* 0x252 */ s8 charID;
    u8 _pad253;
    /* 0x254 */ u8 slotKind;                 /* 9 = batter */
    /* 0x255 */ s8 unk255;
    /* 0x256 */ u8 team;
    /* 0x257 */ u8 player;
    /* 0x258 */ u8 unk258;
    /* 0x259 */ u8 variant;                  /* 1: use alternate track / cached batter model */
    /* 0x25A */ u8 rosterUnk26;
    /* 0x25B */ u8 rosterUnk27;
    /* 0x25C */ u8 unk25C;
    u8 _pad25D[0x278 - 0x25D];
    /* 0x278 */ u8 isBatter;
    u8 _pad279[0x27C - 0x279];
} Gap8001196CAnim;
/* hugeAnimStruct (UnknownHeaders.h) seen from this unit */
typedef struct Gap8001196CAnimTable {
    u8 _pad0[0xC04];
    /* 0x0C04 */ Gap8001196CAnim slots[13];
    u8 _pad2C50[0x2D3C - 0x2C50];
    /* 0x2D3C */ void* cachedFielderData;
    /* 0x2D40 */ u32 cachedFielderSize;
    /* 0x2D44 */ s16 cachedFielderCharID;
    u8 _pad2D46[0x2D54 - 0x2D46];
    /* 0x2D54 */ void* cachedBatterData;
    /* 0x2D58 */ u32 cachedBatterSize;
    /* 0x2D5C */ s16 cachedBatterCharID;
    u8 _pad2D5E[0x2D88 - 0x2D5E];
    /* 0x2D88 */ s8 loadSlot;                /* fn_80016F7C loop index */
    u8 _pad2D89[4];
    /* 0x2D8D */ u8 unk2D8D;
    /* 0x2D8E */ u8 loadStarted;
} Gap8001196CAnimTable;
typedef struct Gap8001196CGameSettings { u8 _pad0[7]; u8 mode; u8 _pad8[0x50]; } Gap8001196CGameSettings;
extern Gap8001196CGameSettings g_d_GameSettings;
extern Gap8001196CAnimTable g_hugeAnimStruct;
typedef struct Gap8001196CRosterEntry { u8 _pad0[0x26]; u8 unk26; u8 unk27; u8 _pad28[0x78]; } Gap8001196CRosterEntry;
extern Gap8001196CRosterEntry inMemRoster[2][9];
typedef struct Gap8001196CLoadStatus { u8 _pad0[0x715]; s8 allowLoad; } Gap8001196CLoadStatus;
extern Gap8001196CLoadStatus lbl_803C6CF8;
typedef struct Gap8001196CFlags { u8 _pad0[0x1E8]; u8 loadBusy; } Gap8001196CFlags;
extern Gap8001196CFlags lbl_803716B8;
/* disc file descriptor, 16 bytes (DiskFileDesc in gap_8001E460.h) */
typedef struct Gap8001196CDiskDesc { u32 flags; u32 sizeFlags; u32 discOffset; u32 compressedSize; } Gap8001196CDiskDesc;
#define SUBFILE_TRACKS 19
extern Gap8001196CDiskDesc* lbl_803CB790;  /* runtime copy of the per-character subfile table */
struct Gap8001E460Object;
void fn_8001FDD4(struct Gap8001E460Object* obj);
u8* fn_8002204C(s32 charID, u8* buf);
void* ARAMTransfer(Gap8001196CDiskDesc* desc, void* dest, u8 loadInfo, void* aramAddress);
void* memcpy(void* dest, const void* src, u32 n);
BOOL fn_80016B60(Gap8001196CAnim* anim);
BOOL fn_8001758C(u8* state, s32 slot, u8 charID, u8 team, u8 player, u8 arg6, u8 slotKind, u8 variant);
void fn_800177B4(void);
void fn_80017814(Gap8001196CAnim* anim, s32 arg1, u32 slotKind, void (*callback)(struct Gap8001E460Object*));
void fn_80017D28(void);
void fn_80017DBC(void);
void fn_80018024(void);
void fn_80018270(void);
void fn_800188C0(void);
void fn_800189B8(void);
void fn_800189E4(void);
void fn_80018B38(void);
void fn_80018B74(void);
void fn_80018DEC(void);
void fn_800196D8(void);
void fn_80019A60(void);
void fn_80019C00(void);
void fn_8001A25C(void);
void fn_8001A3FC(void);
void challengeMapRelated(void);
void fn_8001AAA4(void);
void fn_8001AAF0(void);
void fn_8001AB10(void);
void fn_8001AF98(void);

#endif // !__UNKNOWN_gap_8001196C_H_
