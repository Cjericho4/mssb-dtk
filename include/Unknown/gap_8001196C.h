#ifndef __UNKNOWN_gap_8001196C_H_
#define __UNKNOWN_gap_8001196C_H_

#include "mssbTypes.h"
#include "C3/control.h"
void fn_8003AC90(void);

void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011B64(void);
void fn_80011BE4(void);
void fn_80011CA8(void);
void fn_800126EC(void);
void LoadModel(void);
u8 fn_80013680(struct Gap8001196CAnim* anim);
u8 fn_80012B90(struct Gap8001196CAnim* anim);
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
BOOL fn_80016344(u8 charID, s32 slot, u8 stance, struct Gap8001196CLoadArg* arg);
BOOL fn_80016710(u8 charID, s32 slot);
BOOL fn_80016F7C(void);
typedef struct Gap8001196CModelFile { u8 _pad0[0x10]; u8* unk10; } Gap8001196CModelFile; /* relocated .gpc root header */
typedef struct Gap8001196CStadiumObj {
    /* 0x00 */ u8* buf;
    /* 0x04 */ u8* unk4;
    u8 _pad8[0x58];
    /* 0x60 */ u8 charID;
    /* 0x61 */ u8 slot;
    u8 _pad62[2];
} Gap8001196CStadiumObj;                     /* 0x64 */
extern Gap8001196CStadiumObj lbl_80118220[13];
extern u8 lbl_803CBBFA;
extern s16 lbl_800EEB18[54];                 /* charID -> model id (-1 = none) */
struct Gap8001196CLoadArg;
void* fn_80021BBC(s32 charID, void* buf);
u8* fn_80021ADC(s32 modelID, u8* buf);
void fn_80025FFC(u8* model, u8** out, Gap8001196CStadiumObj* obj);
void ANIMGet(u8* animBank);
void fn_80017098(s32 arg0, struct Gap8001196CLoadArg* arg, s32 arg2, s32 slot, s32 arg4, u8 charID);
void fn_80017340(void);

/* per-slot animation/actor record (AnimationStruct in UnknownHeaders.h), 0x27C bytes */
typedef struct Gap8001196CAnim {
    /* 0x000 */ struct Gap8001196CActor* actor;
    u8 _pad4[4];
    /* 0x008 */ u8* fileBuffer;              /* body .gpc / anim bank buffer */
    u8 _padC[4];
    union {
        /* 0x010 */ struct Gap8001196CSlotTable* slotTables[9];
        struct {
            u8 _pad10[4];
            /* 0x014 */ u8* auxBatter;       /* actor-slot aux for slotKind >= 9 */
            /* 0x018 */ u8* auxFielder;      /* actor-slot aux for slotKind < 9 */
            u8 _pad1C[8];
            /* 0x024 */ u8* animBank;
            u8 _pad28[4];
            /* 0x02C */ struct Gap8001196CStadiumObj* stadiumObj;
        };
    };
    u8 _pad34[0x60 - 0x34];
    /* 0x060 */ s16 unk60;
    /* 0x062 */ s16 animID;
    /* 0x064 */ s16 nextAnim;
    /* 0x066 */ s16 unk66;
    /* 0x068 */ s16 unk68;
    /* 0x06A */ s16 unk6A;
    /* 0x06C */ s16 unk6C;
    /* 0x06E */ s16 unk6E;
    u8 _pad70[0x162 - 0x70];
    /* 0x162 */ u16 boneIndices[120];        /* bone id -> actor bone index, 0xFFFF = none */
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
    /* 0x25D */ u8 unk25D;
    /* 0x25E */ u8 unk25E;
    /* 0x25F */ u8 unk25F;
    /* 0x260 */ u8 unk260;
    /* 0x261 */ u8 unk261;
    /* 0x262 */ u8 unk262;
    /* 0x263 */ u8 unk263;
    /* 0x264 */ u8 unk264;
    /* 0x265 */ u8 unk265;
    /* 0x266 */ u8 unk266;
    /* 0x267 */ u8 unk267;
    /* 0x268 */ u8 unk268;
    /* 0x269 */ u8 unk269;
    /* 0x26A */ u8 unk26A;
    /* 0x26B */ u8 unk26B;
    /* 0x26C */ u8 unk26C;
    /* 0x26D */ u8 unk26D;
    /* 0x26E */ u8 unk26E;
    u8 _pad26F;
    /* 0x270 */ u8 unk270;
    /* 0x271 */ u8 unk271;
    /* 0x272 */ u8 unk272;
    /* 0x273 */ u8 unk273;
    u8 _pad274[3];
    /* 0x277 */ u8 unk277;
    /* 0x278 */ u8 isBatter;
    u8 _pad279[0x27C - 0x279];
} Gap8001196CAnim;
typedef struct Gap8001196CSlotBank { u8* animBank; u8 _pad4[0x10]; } Gap8001196CSlotBank; /* 0x14 */
/* hugeAnimStruct (UnknownHeaders.h) seen from this unit */
/* actor as this unit sees it (GameActor in gap_8002244C.h) */
typedef struct Gap8001196CBone { u16 boneID; u8 _pad2[0x134]; u8 unk136; } Gap8001196CBone;
typedef struct Gap8001196CActor {
    u8 _pad0[6];
    /* 0x06 */ u16 totalBones;
    u8 _pad8[0x10];
    /* 0x18 */ Gap8001196CBone** boneArray;
    u8 _pad1C[0x99 - 0x1C];
    /* 0x99 */ u8 unk99;
} Gap8001196CActor;
/* per-slot actor record at +0x34 of each 0x90-byte entry (Gap8002244CActorSlot in gap_8002244C.h) */
typedef struct Gap8001196CActorSlot {
    /* 0x00 */ Gap8001196CActor* actor;
    /* 0x04 */ u8* aux;
    /* 0x08 */ void (*callback)(struct Gap8001E460Object*);
    u8 _padC[4];
    /* 0x10 */ Control control;
    u8 _pad4C[8];
    /* 0x54 */ f32 unk54;
    u8 _pad58[2];
    /* 0x5A */ u8 unk5A;
    u8 _pad5B;
} Gap8001196CActorSlot;                      /* 0x5C here; the real record runs past the entry */
typedef struct Gap8001196CActorEntry { u8 _pad0[0x34]; Gap8001196CActorSlot slot; } Gap8001196CActorEntry; /* 0x90 */
/* relocated .gpc root header (offsets become pointers in fn_80017814) */
typedef struct Gap8001196CRootHeader {
    /* 0x00 */ u32 texture;
    /* 0x04 */ u32 layout;
    /* 0x08 */ u32 geo;
    /* 0x0C */ u32 skn;
    /* 0x10 */ u32 unk10;
} Gap8001196CRootHeader;
typedef struct Gap8001196CAnimTable {
    u8 _pad0[0x60];
    /* 0x0060 */ Gap8001196CActorEntry* actorEntries;
    u8 _pad64[0xAC - 0x64];
    /* 0x00AC */ void* unkAC;
    /* 0x00B0 */ void* unkB0;
    /* 0x00B4 */ void* unkB4;
    /* 0x00B8 */ void* unkB8;
    u8 _padBC[0xC04 - 0xBC];
    /* 0x0C04 */ Gap8001196CAnim slots[13];
    /* 0x2C50 */ Gap8001196CAnim* slotPtrs[13];
    u8 _pad2C84[0x2CAC - 0x2C84];
    /* 0x2CAC */ u8* sharedAnimBank;
    u8 _pad2CB0[0x2CBC - 0x2CB0];
    /* 0x2CBC */ u8* batterAnimBank;
    u8 _pad2CC0[0x2CFC - 0x2CC0];
    union {
        /* 0x2CFC */ Gap8001196CSlotBank slotBanks[9]; /* overlaps the bytes below in the binary */
        struct {
            u8 _pad2CFC[0x2D77 - 0x2CFC];
            /* 0x2D77 */ u8 loadState;
            u8 _pad2D78[7];
            /* 0x2D7F */ u8 loadedCharID[9];
            /* 0x2D88 */ s8 loadSlot;        /* fn_80016F7C loop index */
            u8 _pad2D89[4];
            /* 0x2D8D */ u8 unk2D8D;
            /* 0x2D8E */ u8 loadStarted;
        };
        struct {
            u8 _pad2CFCb[0x2D3C - 0x2CFC];
            /* 0x2D3C */ void* cachedFielderData;
            /* 0x2D40 */ u32 cachedFielderSize;
            /* 0x2D44 */ s16 cachedFielderCharID;
            u8 _pad2D46[0x2D54 - 0x2D46];
            /* 0x2D54 */ void* cachedBatterData;
            /* 0x2D58 */ u32 cachedBatterSize;
            /* 0x2D5C */ s16 cachedBatterCharID;
        };
    };
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
void fn_80017814(Gap8001196CAnim* anim, s32 index, s32 slotKind, void (*callback)(struct Gap8001E460Object*));
struct Gap8001196CTexArchive;
struct Gap8001196CActLayout;
struct Gap8001196CGeoFile;
struct Gap8001196CSkin;
void convertTextureHeader(struct Gap8001196CTexArchive* tex);
void LoadActorLayout(struct Gap8001196CActLayout* layout);
void convertGeometryAndSknHeader(struct Gap8001196CGeoFile* geo, struct Gap8001196CSkin* skn);
void haveActLayoutPointToGeoHeader(struct Gap8001196CActLayout* layout, struct Gap8001196CGeoFile* geo);
void fn_800BD190(struct Gap8001196CGeoFile* geo, struct Gap8001196CTexArchive* tex);
void fn_8002399C(Gap8001196CActorSlot* slot, s32 blockIdx, u16 actorID, struct Gap8001196CActLayout* layout, u8* aux,
                 struct Gap8001196CSkin* skn);
void fn_80025DDC(u8* data);
void fn_80025C58(u8* data, Gap8001196CActorSlot* slot);
void fn_800B2B74(Gap8001196CActor* actor, u16 boneIdx);
void fn_800B2B54(Gap8001196CActor* actor, u16 boneIdx, u8 value);
void fn_800BD548(Gap8001196CActorSlot* slot, s32 count, ...);
s32 fn_800B2BA8(Gap8001196CActor* actor, u16 boneIdx, Gap8001196CActor* other, u16 otherIdx);
void fn_800B2C08(Gap8001196CActor* actor, u16 boneIdx);
void fn_8001FC4C(Gap8001196CAnim* anim);
void fn_800638B4(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_80063010(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_8004B7B4(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_800637BC(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_8004BD6C(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_800637D4(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_80052634(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
void fn_80062ED4(Gap8001196CAnim* anim, Gap8001196CActorSlot* slot);
u8* memset(u8* dst, s32 value, u32 size);
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
