#ifndef __UNKNOWN_gap_8001E460_H_
#define __UNKNOWN_gap_8001E460_H_

#include "mssbTypes.h"
void sndMasterVolume(u8 volume, u16 time, u8 music, u8 effects);
struct Gap8001E460Object;
struct Gap8001E460Resource;
extern s32 lbl_803CB7AC[2];
extern u8 lbl_803CBBC0;
extern u32 lbl_803CBC40;
typedef struct Gap8001E460Config {
    u8 _pad0[0x18];
    /* 0x18 */ s32 unk18;
} Gap8001E460Config;
extern Gap8001E460Config lbl_800EFBC0;

/* master descriptor table: 54 body files, 378 sub-item files (54*7), 54 skeletons, 29 stadiums */
/* disc file descriptor, 16 bytes */
typedef struct DiskFileDesc {
    /* 0x0 */ u32 flags;                     /* 0x40B */
    /* 0x4 */ u32 sizeFlags;                 /* 0x40000000 | uncompressed size */
    /* 0x8 */ u32 discOffset;
    /* 0xC */ u32 compressedSize;
} DiskFileDesc;
typedef void (*Gap8001E460DiskLoadCallback)(DiskFileDesc* desc, void* dest, s32 param);
typedef struct Gap8001E460LoadRecord {
    /* 0x00 */ DiskFileDesc* desc;
    /* 0x04 */ void* dest;
    /* 0x08 */ s32 mode;
    /* 0x0C */ void* aramAddr;
    /* 0x10 */ Gap8001E460DiskLoadCallback callback;
    /* 0x14 */ s32 param;
} Gap8001E460LoadRecord;
typedef struct Gap8001E460Flags {
    /* 0x000 */ Gap8001E460LoadRecord current;
    /* 0x018 */ Gap8001E460LoadRecord recs[18];
    /* 0x1C8 */ s8 head;
    /* 0x1C9 */ s8 tail;
    /* 0x1CA */ s8 pending;
    u8 _pad1CB[0xD];
    /* 0x1D8 */ void** bodyAramAddrs;        /* per-character ARAM copy of the body model */
    /* 0x1DC */ void** subItemAramAddrs;
    /* 0x1E0 */ void** aramAddrs;            /* per-character ARAM copy of the skeleton file */
    u8 _pad1E4[4];
    /* 0x1E8 */ u8 unk1E8;
    u8 _pad1E9[1];
    /* 0x1EA */ u8 unk1EA;                   /* bit 0: body models resident in ARAM, bit 1: skeletons */
    u8 _pad1EB[0x371];
    /* 0x55C */ s32 unk55C;
} Gap8001E460Flags;
extern Gap8001E460Flags lbl_803716B8;
/* The character/stadium disc-data block.  fn_8002204C / fn_80021CA4 address every sub-table
 * relative to lbl_800EFBE8 (0x800EFBE8, DOL file 0xECBE8), so it is typed as one struct here.
 * Separate symbols exist for the parts: lbl_800EFD38 (master), lbl_800F1D78 (subfiles),
 * lbl_800F5D98 (sub-item files), lbl_800F71D8 (pair/kind tables). */
typedef struct Gap8001E460DataBlock {
    u8 _pad0[0x150];
    /* 0x0150 */ DiskFileDesc master[516];             /* master descriptors: 0..53 body, 54+c*7+k sub-items, 432+c skeletons, 486+id stadium */
    /* 0x2190 */ DiskFileDesc subfiles[54][19];        /* per-character disc files, track 15 = skeleton, 16/17 = anim banks */
    /* 0x61B0 */ DiskFileDesc subItemFiles[54][6];     /* per-character sub-item (bat/glove/...) disc files */
    u8 _pad71D8[0x77D0 - 0x71D8];
    /* 0x77D0 */ s8 bodyItems[54][2];                  /* {master body index, sub-item id or -1} per character (ARAM path) */
    /* 0x783C */ s8 subItemPairs[2][6][2];             /* [kind][itemSlot] = {sub-item k of the main file, k of the 2nd file} */
    /* 0x7854 */ s8 subItemKind[54];                   /* per-character row of subItemPairs */
} Gap8001E460DataBlock;
extern Gap8001E460DataBlock lbl_800EFBE8;
typedef struct Gap8001E460LoadStatus { u8 _pad0[0x715]; s8 allowLoad; } Gap8001E460LoadStatus;
extern Gap8001E460LoadStatus lbl_803C6CF8;
void fn_80022620(DiskFileDesc* desc, void* dest, s32 param);
void fn_8002244C(DiskFileDesc* desc, void* dest, s32 param);
void fn_8002254C(DiskFileDesc* desc, void* dest, s32 param);
void fn_80022634(void);
#define MASTER_DESC_SUBITEM_BASE 54
#define MASTER_DESC_SKELETON_BASE 432
#define SUBITEMS_PER_CHAR 7
extern DiskFileDesc lbl_800EFD38[];
/* per-character subfile table, flat: 19 tracks per character, track 15 is the skeleton */
#define SUBFILE_TRACKS 19
#define SUBFILE_TRACK_SKELETON 15
extern DiskFileDesc lbl_800F1D78[];
void* ARAMTransfer(DiskFileDesc* desc, void* dest, s32 loadInfo, void* aramAddress);
void* _OSAllocFromHeap(s32 heap, u32 size);
typedef struct Gap8001E460Sound {
    u32 unk0;
    struct Gap8001E460Resource* resources[64]; /* 0x4 */
    u8 _pad104[0x23C];
    /* 0x340 */ u8 groups[0x50];
    u8 groupCount; /* 0x390 */
    u8 _pad391[5];
    /* 0x396 */ u8 soundMode;
    /* 0x397 */ u8 unk397;
    /* 0x398 */ u8 unk398;
} Gap8001E460Sound;
extern Gap8001E460Sound lbl_800EF808;
typedef struct Gap8001E460Settings {
    u8 _pad0[0x23];
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
} Gap8001E460Settings;
extern Gap8001E460Settings lbl_800E8754;
void fn_800ACD44(void);
typedef struct Gap8001E460GameSettings {
    u8 _pad0[0x9];
    /* 0x09 */ u8 unk9;
    u8 _padA[0x4E];
} Gap8001E460GameSettings;
extern Gap8001E460GameSettings g_d_GameSettings;
typedef struct Gap8001E460Entry {
    u8 _pad0[0x10];
} Gap8001E460Entry;
extern Gap8001E460Entry lbl_800EEFD0[62];
extern u8 lbl_803CB7CC[8];
s32 fn_80035838(Gap8001E460Entry* entry, s32 arg1);

void fn_8001E460(s32 value);
void fn_8001E474(void);
void fn_8001E488(void);
void fn_8001E784(void);
void fn_8001F16C(void);
void fn_8001F228(void);
void challengeMapMaybe(void);
void fn_8001F5E8(void);
void fn_8001F8A4(void);
void fn_8001FC4C(void);
void fn_8001FDD4(struct Gap8001E460Object* obj);
void fn_8001FE00(void);
void calledWhenStartingMatch(void);
BOOL fn_80020218(void);
void fn_8002024C(void);
void fn_80020278(void);
BOOL fn_80020388(void);
void fn_800203E0(void);
void changeScene(void);
void fn_8002059C(void);
void fn_80020624(void);
void fn_800206FC(void);
void fn_80021064(void);
s32 fn_80021188(void);
s32 fn_800211BC(void);
u8 fn_800211F0(void);
void fn_80021204(void);
void sndOutputMode(u32 mode);
void OSSetSoundMode(u32 mode);
void fn_80021228(u8 mode);
u32 OSGetSoundMode(void);
void fn_8002128C(u8 mode);
void fn_80021308(void);
void fn_800213F4(void);
void fn_800213F8(u32 size);
BOOL fn_80021410(void);
void fn_8002149C(s32 index);
BOOL fn_800214D0(void);
BOOL fn_80021518(u16 gid, struct Gap8001E460Resource* res);
s32 fn_8002158C(void);
typedef struct Gap8001E460LoadSub {
    u8 _pad0[0x10];
    /* 0x10 */ s16 unk10;
} Gap8001E460LoadSub;
typedef struct Gap8001E460Load {
    /* 0x0 */ s32 index;
    u8 _pad4[0x4];
    /* 0x8 */ Gap8001E460LoadSub* sub;
} Gap8001E460Load;
typedef void (*Gap8001E460LoadCallback)(void);
extern Gap8001E460Entry lbl_800EF508[48];
void fn_80022CB4(Gap8001E460Entry* entry, s32 a, s32 b, s32 c, Gap8001E460LoadCallback cb, Gap8001E460Load* load);
void fn_800215F8(Gap8001E460Load* load);
void fn_80021650(void);
typedef struct Gap8001E460Task {
    u8 _pad0[0x14];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
} Gap8001E460Task;
typedef struct Gap8001E460QueueNode {
    u8 _pad0[0x10];
    /* 0x10 */ s16 unk10;
    u8 _pad12[2];
    u16 index;
} Gap8001E460QueueNode;
extern Gap8001E460QueueNode* lbl_803CC1B8;
Gap8001E460Task* fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
void fn_800216F8(u8 a, s32 b);
void fn_80021758(void);
void fn_80021954(struct Gap8001E460Resource** resource);
void fn_80021980(void);
void f_initSound(void);
void fn_80021AA0(void);
void fn_80021AC0(void);
void fn_80021AC4(void);
void fn_80021AC8(void);
void fn_80021ADC(void);
void* fn_80021BBC(s32 charID, void* buf);
u8* fn_8002204C(s32 charID, u8* buf);
u8* fn_80021CA4(s32 charID, s32 itemSlot, u8* buf);

typedef struct Gap8001E460Object {
    u8 _pad0[0x70];
    u32 fog; /* 0x70 */
} Gap8001E460Object;
void fn_800B9AA8(u32 value);
typedef struct Gap8001E460Resource {
    /* 0x00 */ u8* project;
    u8 _pad4[0x4];
    /* 0x08 */ u8* sdir;
    u8 _padC[0x4];
    /* 0x10 */ u8* pool;
    u8 _pad14[0x4];
    struct Gap8001E460Resource* end;
} Gap8001E460Resource;
u32 sndPushGroup(u8* project, u16 gid, Gap8001E460Resource* samples, u8* sdir, u8* pool);
typedef struct Gap8001E460ResourceState {
    Gap8001E460Resource* resource;
    u8 _pad4[0xC];
    u8 state; /* 0x10 */
    u8 unk11, pending;
    u8 _pad13[3];
    u8 ready;
    u8 _pad17[5];
} Gap8001E460ResourceState;
extern Gap8001E460ResourceState lbl_8037169C;
typedef struct Gap8001E460Stage { u8 _pad0[0x69]; u8 status; } Gap8001E460Stage;
typedef struct Gap8001E460StageRef { Gap8001E460Stage* stage; u32 unk4; } Gap8001E460StageRef;
extern Gap8001E460StageRef lbl_80371C30[];
void fn_80034CEC(Gap8001E460QueueNode* task);
void fn_800B0A14_removeQueue(void);
void fn_800ACF14(Gap8001E460Resource* resource);

void fn_800ACFB0(struct Gap8001E460Resource* resource);

void fn_800ACF78(Gap8001E460Resource* resource, u32 size);

u32 sndPopGroup(void);

#endif // !__UNKNOWN_gap_8001E460_H_
