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
    /* 0x1E4 */ void** stadiumAramAddrs;
    /* 0x1E8 */ u8 unk1E8;
    u8 _pad1E9[1];
    /* 0x1EA */ u8 unk1EA;                   /* bit 0: body models, bit 1: skeletons, bit 3: stadium/extra models resident in ARAM */
    u8 _pad1EB[0x371];
    /* 0x55C */ s32 unk55C;
} Gap8001E460Flags;
extern Gap8001E460Flags lbl_803716B8;
/* character / stadium disc tables, defined (with their retail contents) in gap_8001E460.c */
extern DiskFileDesc lbl_800EFBE8[21];
extern DiskFileDesc lbl_800F1D68[1];
extern DiskFileDesc lbl_800F5D98[54 * 6];

extern s8 lbl_800F73B8[54][2];
extern s8 lbl_800F7424[2][6][2];
extern s8 lbl_800F743C[54];
typedef struct Gap8001E460LoadStatus { u8 _pad0[0x715]; s8 allowLoad; } Gap8001E460LoadStatus;
extern Gap8001E460LoadStatus lbl_803C6CF8;
void fn_80022620(DiskFileDesc* desc, void* dest, s32 param);
void fn_8002244C(DiskFileDesc* desc, void* dest, s32 param);
void fn_8002254C(DiskFileDesc* desc, void* dest, s32 param);
void fn_80022634(void);
#define MASTER_DESC_SUBITEM_BASE 54
#define MASTER_DESC_SKELETON_BASE 432
#define MASTER_DESC_STADIUM_BASE 486
#define STADIUM_MODELS 29               /* stadium/extra models by model ID (fn_80021ADC) */
extern DiskFileDesc lbl_800F71D8[STADIUM_MODELS + 1];
#define SUBITEMS_PER_CHAR 7
extern DiskFileDesc lbl_800EFD38[515];
/* per-character subfile table, flat: 19 tracks per character, track 15 is the skeleton */
#define SUBFILE_TRACKS 19
#define SUBFILE_TRACK_SKELETON 15
extern DiskFileDesc lbl_800F1D78[54 * SUBFILE_TRACKS];
void* ARAMTransfer(DiskFileDesc* desc, void* dest, s32 loadInfo, void* aramAddress);
void* _OSAllocFromHeap(s32 heap, u32 size);
/* Views of MusyX's SND_AUX_REVERBHI and SND_AUX_CHORUS (musyx.h is not included here). */
typedef struct Gap8001E460ReverbHi {
    u8 state[0x1C4];
    /* 0x1C4 */ u8 tempDisableFX;
    /* 0x1C8 */ f32 coloration;
    /* 0x1CC */ f32 mix;
    /* 0x1D0 */ f32 time;
    /* 0x1D4 */ f32 damping;
    /* 0x1D8 */ f32 preDelay;
    /* 0x1DC */ f32 crosstalk;
} Gap8001E460ReverbHi;
STATIC_ASSERT(sizeof(Gap8001E460ReverbHi) == 0x1E0);
typedef struct Gap8001E460Chorus {
    u8 state[0x90];
    /* 0x90 */ u32 baseDelay;
    /* 0x94 */ u32 variation;
    /* 0x98 */ u32 period;
} Gap8001E460Chorus;
STATIC_ASSERT(sizeof(Gap8001E460Chorus) == 0x9C);
typedef struct Gap8001E460Sound {
    u32 unk0;
    struct Gap8001E460Resource* resources[48]; /* 0x4, one per sound group */
    /* 0xC4 */ Gap8001E460ReverbHi reverb;
    /* 0x2A4 */ Gap8001E460Chorus chorus;
    /* 0x340 */ u8 groups[0x50];
    u8 groupCount; /* 0x390 */
    /* 0x391 */ u8 volumeFD; /* sndVolume for sequence group 0xFD */
    /* 0x392 */ u8 volumeFE; /* sndVolume for sequence group 0xFE */
    u8 _pad393[3];
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
typedef union Gap8001E460Entry {
    u8 _pad0[0x10];
    DiskFileDesc desc; /* common UI resource descriptor (res table, data_map.md) */
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
typedef struct Gap8001E460BonePair {
    /* 0x0 */ u16 a; /* bone ids swapped when the model is mirrored; a == 0xFFFF ends a list */
    /* 0x2 */ u16 b;
} Gap8001E460BonePair;
/* FAKEMATCH: one view from the unit's first data symbol, so the lists are reached as anchor +
   offset like the original; the lists themselves sit in lbl_800EE930 (+0x30, +0x68, +0x80). */
typedef struct Gap8001E460Data {
    u8 _pad0[0x160];
    /* 0x160 */ Gap8001E460BonePair mirrorCommon[14];    /* every character */
    /* 0x198 */ Gap8001E460BonePair mirrorParagoomba[6];
    /* 0x1B0 */ Gap8001E460BonePair mirrorShyGuy[1];     /* open-ended here */
} Gap8001E460Data;
extern Gap8001E460Data lbl_800EE800;
extern Gap8001E460BonePair lbl_803CB798[2]; /* Paratroopas */
extern Gap8001E460BonePair lbl_803CB7A0[2]; /* Birdo */
/* View of the per-slot record (Gap8001196CAnim in gap_8001196C.h, which declares this function
   with its own type). */
typedef struct Gap8001E460Anim {
    u8 _pad0[0x72];
    /* 0x072 */ u16 mirrorBones[120]; /* actor bone index -> its left/right counterpart */
    /* 0x162 */ u16 boneIndices[120]; /* bone id -> actor bone index, 0xFFFF = none */
    /* 0x252 */ s8 charID;
    u8 _pad253[2];
    /* 0x255 */ s8 blockIndex;
} Gap8001E460Anim;
/* Views of the actor block (a header, then 0x90-byte actor slots: Gap8002244CActorSlot) and of
   hugeAnimStruct (UnknownHeaders.h), neither of which this unit includes. */
typedef struct Gap8001E460ActorSlot {
    /* 0x00 */ struct Gap8001E460Actor* actor;
    u8 _pad4[0x6C - 0x4];
    /* 0x6C */ u8 unk6C;
    u8 _pad6D[0x90 - 0x6D];
} Gap8001E460ActorSlot;
typedef struct Gap8001E460ActorBlock {
    /* 0x00 */ u16 count;
    u8 _pad2[0x34 - 0x2];
    /* 0x34 */ Gap8001E460ActorSlot slots[1];
} Gap8001E460ActorBlock;
typedef struct Gap8001E460HugeAnim {
    u8 _pad0[0x60];
    /* 0x0060 */ Gap8001E460ActorBlock* actorBlock;
    u8 _pad64[0x2C50 - 0x64];
    /* 0x2C50 */ Gap8001E460Anim* slotPtrs[13];
    u8 _pad2C84[0x307A - 0x2C84];
    /* 0x307A */ u8 mode;
} Gap8001E460HugeAnim;
extern Gap8001E460HugeAnim g_hugeAnimStruct;
void fn_800B2D5C(struct Gap8001E460Actor* actor);
void fn_8001FC4C(Gap8001E460Anim* anim);
void fn_8001FDD4(struct Gap8001E460Object* obj);
void fn_8001FE00(void);
void calledWhenStartingMatch(void);
BOOL fn_80020218(void);
void fn_8002024C(void);
typedef struct Gap8001E460TexArchive {
    u8 _pad0[0x20];
    /* 0x20 */ u16 count;
} Gap8001E460TexArchive;
void* fn_800ACF34(u32 align, u32 size);
void convertTextureHeader(Gap8001E460TexArchive* textures);
BOOL fn_80020278(s32 index);
BOOL fn_80020388(void);
void fn_800203E0(u8 request, s8 unk14);
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
typedef struct Gap8001E460SndHooks {
    void* (*malloc)(u32 size);
    void (*free)(void* ptr);
} Gap8001E460SndHooks; /* MusyX SND_HOOKS */
extern Gap8001E460SndHooks lbl_803CB7D8;
extern u8 lbl_80118740[];
void sndSetHooks(Gap8001E460SndHooks* hooks);
void sndAuxCallbackPrepareReverbHI(Gap8001E460ReverbHi* reverb);
void sndAuxCallbackPrepareChorus(Gap8001E460Chorus* chorus);
void sndAuxCallbackReverbHI(u8 reason, void* info, void* user);
void sndAuxCallbackChorus(u8 reason, void* info, void* user);
void sndSetAuxProcessingCallbacks(u8 studio, void (*auxA)(u8, void*, void*), void* userA, u8 midiA, u32 seqIDA,
                                  void (*auxB)(u8, void*, void*), void* userB, u8 midiB, u32 seqIDB);
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
    /* 0x00 */ void (*callback)(void);
    u8 _pad4[0xC];
    /* 0x10 */ s16 unk10;
    u8 _pad12[2];
    u16 index;
} Gap8001E460QueueNode;
typedef struct Gap8001E460Script Gap8001E460Script;
extern Gap8001E460Script lbl_800EF470;
extern Gap8001E460QueueNode* lbl_803CC1B8;
void fn_80034E20(Gap8001E460QueueNode* scene, Gap8001E460Script* script);
Gap8001E460Task* fn_800B0A5C_insertQueue(void (*callback)(void), s32 priority);
void fn_800216F8(u8 a, s32 b);
void fn_80021758(void);
void fn_80021954(struct Gap8001E460Resource** resource);
void fn_80021980(struct Gap8001E460Resource* resource);
extern u8 lbl_80158740[0x4000];  /* stack check block; its first word is the magic 0xABF16D9C, then tagged "SND@" */
extern u8 lbl_8015C740[0x21BE0]; /* MusyX work memory */
extern u8 lbl_800EFBB4[0xC];
/* gap_800AD780.h declares initSound as a (void) stub; arguments from this call. */
void initSound(u8* config, s32 unk, u8* memory, u32 size);
void fn_800A8F68(void);
void fn_800A648C(void);
void sndVolume(u8 volume, u16 time, u8 group);
void f_initSound(void);
void fn_80021AA0(void);
void fn_80021AC0(void);
void fn_80021AC4(void);
void fn_80021AC8(void);
u8* fn_80021ADC(s32 modelID, u8* buf);
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
    union {
        Gap8001E460Resource* resource;
        struct Gap8001E460TexArchive* textures; /* texture archive loaded by fn_80020278 */
    };
    /* 0x04 */ u8* unk4;      /* past the archive's 0x20-byte texture records (fn_80020278) */
    u8 _pad8[4];
    /* 0x0C */ u16 requested; /* 1 when fn_800203E0 has stored a request */
    u8 _padE[2];
    u8 state; /* 0x10 */
    u8 unk11, pending; /* unk11: the requested state */
    u8 _pad13;
    /* 0x14 */ u8 unk14;
    u8 _pad15;
    u8 ready;
    u8 _pad17;
    /* 0x18 */ u8 textureIndex; /* fn_80020278 argument */
    /* 0x19 */ u8 textureStep;  /* 0 start, 1 loading, 2 done */
    /* 0x1A */ u8 unk1A;
    u8 _pad1B;
} Gap8001E460ResourceState;
extern Gap8001E460ResourceState lbl_8037169C;
typedef struct Gap8001E460Stage {
    u8 _pad0[0x54];
    /* 0x54 */ u32 flags;
    u8 _pad58[4];
    /* 0x5C */ u32 unk5C;
    u8 _pad60[8];
    /* 0x68 */ u8 unk68;
    /* 0x69 */ u8 status;
} Gap8001E460Stage;
typedef struct Gap8001E460StageRef { Gap8001E460Stage* stage; u32 unk4; } Gap8001E460StageRef;
extern Gap8001E460StageRef lbl_80371C30[];
void fn_80034CEC(Gap8001E460QueueNode* task);
void fn_800B0A14_removeQueue(void);
void fn_800ACF14(Gap8001E460Resource* resource);

void fn_800ACFB0(struct Gap8001E460Resource* resource);

void fn_800ACF78(Gap8001E460Resource* resource, u32 size);

u32 sndPopGroup(void);

#endif // !__UNKNOWN_gap_8001E460_H_
