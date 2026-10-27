#ifndef __UNKNOWN_gap_8002244C_H_
#define __UNKNOWN_gap_8002244C_H_
#define ACTOR_MEM_BLOCK_SIZE 0x86A0 /* one actor's memory block (fn_80023B04) */
#define LOAD_QUEUE_SIZE 18 /* ring of pending ARAM/disc loads (recs, flag1C8 write / flag1C9 read) */

#include "mssbTypes.h"

#include "Dolphin/mtx.h"
#include "Dolphin/os.h"
#include "C3/actor.h"



typedef struct Gap8002244CLoad { u8 _pad0[0x715]; s8 complete; } Gap8002244CLoad;
extern Gap8002244CLoad lbl_803C6CF8;
void fn_800B0A14_removeQueue(void);
u8* memset(u8* memory, s32 value, u32 size);
void OSSetProgressiveMode(u32 enable);
void fn_800A7E00(void);
typedef struct Gap8002244CProjParams {
    /* 0x00 */ f32 type;
    /* 0x04 */ f32 m00;
    /* 0x08 */ f32 m0x;
    /* 0x0C */ f32 m11;
    /* 0x10 */ f32 m1x;
    /* 0x14 */ f32 m22;
    /* 0x18 */ f32 m23;
} Gap8002244CProjParams;
typedef struct Gap8002244CStageEntry {
    u8 _pad0[2];
    /* 0x2 */ u8 id;
    u8 _pad3[3];
} Gap8002244CStageEntry;
extern Gap8002244CStageEntry lbl_800E8558[54];
extern u8 lbl_803CB748[8];
typedef struct Gap8002244CGameSettings {
    u8 _pad0[0x1A];
    /* 0x1A */ u8 unlocked[6];
    u8 _pad20[0x38];
} Gap8002244CGameSettings;
extern Gap8002244CGameSettings g_d_GameSettings;
void fn_800A7568(void);
void fn_800A6304(void);
/* disc file descriptor, 16 bytes (see gap_8001E460.h DiskFileDesc) */
typedef struct Gap8002244CDiskDesc {
    /* 0x0 */ u32 flags;
    /* 0x4 */ u32 sizeFlags;                 /* 0x40000000 | uncompressed size */
    /* 0x8 */ u32 discOffset;
    /* 0xC */ u32 compressedSize;
} Gap8002244CDiskDesc;
#define MASTER_DESC_SUBITEM_BASE 54
extern Gap8002244CDiskDesc lbl_800EFD38[];
/* memory block a sub-item is loaded into; the aligned file size is kept at 0xC */
typedef struct Gap8002244CLoadBlock {
    u8 _pad0[0xC];
    /* 0xC */ u32 size;
} Gap8002244CLoadBlock;
typedef void (*Gap8002244CLoadCallback)(s32 arg0, Gap8002244CLoadBlock* block, s32 packedID);
typedef struct Gap8002244CRecord {
    /* 0x00 */ Gap8002244CDiskDesc* desc;
    /* 0x04 */ void* dest;
    /* 0x08 */ s32 mode;
    /* 0x0C */ void* aramAddr;
    /* 0x10 */ Gap8002244CLoadCallback callback;
    /* 0x14 */ s32 param;
} Gap8002244CRecord;
typedef struct Gap8002244CFlags {
    union {
        u8 header[0x18];
        Gap8002244CRecord active;
    };
    union {
        u8 records[0x1B0];
        Gap8002244CRecord recs[LOAD_QUEUE_SIZE];
    };
    s8 flag1C8, flag1C9;
    /* 0x1CA */ s8 pending1CA;
    u8 _pad1CB;
    u32 current; /* 0x1CC */
    u32 pending; /* 0x1D0 */
    u8 _pad1D4[4];
    /* 0x1D8 */ void** bodyAramAddrs;
    /* 0x1DC */ void** subItemAramAddrs;
    /* 0x1E0 */ void** skeletonAramAddrs;
    u8 _pad1E4[4];
    /* 0x1E8 */ u8 unk1E8;
    u8 unk1E9;
    u8 flags;
} Gap8002244CFlags;
extern Gap8002244CFlags lbl_803716B8;
typedef struct Gap8002244CVector { f32 x, y, z; } Gap8002244CVector;
typedef struct Gap8002244CObj {
    union { s32 unk0; Gap8002244CVector* vectors; };
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
    /* 0xC */ s32 unkC;
    /* 0x10 */ s32 unk10;
    volatile s32 current; /* 0x14 */
    /* 0x18 */ s32 unk18;
} Gap8002244CObj;

extern s32 lbl_803CBC60;

void fn_8002244C(s32 arg0, Gap8002244CLoadBlock* block, s32 packedID);
void fn_8002254C(s32 desc, void* bodyBuffer, s32 masterIndex);
void fn_80022620(s32 arg0, Gap8002244CLoadBlock* block, s32 packedID);
void fn_80022634(void);
void fn_800227A0(void);
void fn_800227E4(void);
void fn_800229CC(void);
void fn_80022A24(void);
void fn_80022B14(void);
void fn_80022B68(void);
BOOL fn_80022CB4(Gap8002244CDiskDesc* desc, void* dest, s32 mode, void* aramAddr, Gap8002244CLoadCallback callback,
                 s32 param);
void fn_80022D58(void);
ActMemBlock* f_InitBone(ActBone* parent, ActBoneLayout* layout, GameActor* actor, u16* numBones, ActBone* bones,
                        ActMemBlock* cursor);
ActMemBlock* fn_80023078(ActDisplayObj* obj, ActDOLayout* layout, ActMemBlock* mem);
GameActor* f_InitActorWithLayout(ActLayout* layout, ActMemBlock* mem);
void BuildBoneSkinOrientationMatrix(ActBone* root, Mtx m);
void DOSetWorldMatrix(ActDisplayObj* obj, Mtx m);
struct Gap8001196CActorEntry;
struct Gap8001196CActLayout;
void fn_800238E0(struct Gap8001196CActorEntry* entries, s32 index, s32 actorID, struct Gap8001196CActLayout* layout);
/* per-slot actor record living at +0x34 of each 0x90 HugeAnimEntry68 (UnknownHeaders.h) */
struct Gap8002244CSlotAux;
typedef struct Gap8002244CActorSlot {
    /* 0x00 */ GameActor* actor;
    /* 0x04 */ struct Gap8002244CSlotAux* aux;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u16 actorID;
    /* 0x0E */ u16 unkE;
    u8 _pad10[0x44];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 unk5A;
    u8 _pad5B[5];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u16 unk66;
    /* 0x68 */ u32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D;
    u8 _pad6E[2];
    /* 0x70 */ u32 unk70;
    /* 0x74 */ u32 unk74;
    /* 0x78 */ u32 unk78;
    /* 0x7C */ u32 unk7C;
    /* 0x80 */ u32 unk80;
    /* 0x84 */ u32 unk84;
    /* 0x88 */ u32 unk88;
    /* 0x8C */ u32 unk8C;
} Gap8002244CActorSlot;
extern ActMemBlock* volatile lbl_8017EBB0[20]; /* per-slot actor memory blocks; volatile matches the original codegen */
extern u32 lbl_803CBC5C;                     /* size of one actor memory block */
void fn_800B4724(GameActor* actor, s32 skHeader);
void fn_8002399C(Gap8002244CActorSlot* slot, u16 slotIdx, u16 actorID, ActLayout* layout, struct Gap8002244CSlotAux* aux,
                 s32 skHeader);
typedef struct Gap8002244CActor { u8 _pad0[0x1BC0]; } Gap8002244CActor;
extern Gap8002244CActor* lbl_8017EB40[28];
void* _OSAllocFromHeap(s32 alignment, u32 size);
struct HugeAnimEntry68* ActorObjectInitTable(u16 count);
void fn_80023AA4(void);
void fn_80023B04(s32 count);
void fn_80023B90(void);
void fn_80023CF4(BOOL enabled);
s32 fn_80023D3C(void);
void fn_80023D44(s32 value);
BOOL fn_80023D4C(Gap8002244CObj* obj, Gap8002244CVector* out);
BOOL fn_80023D98(Gap8002244CObj* obj, Gap8002244CVector* out);
BOOL fn_80023DFC(Gap8002244CObj* obj, Gap8002244CVector* out);
void fn_80023E48(Gap8002244CObj* obj, Gap8002244CVector* v);
void fn_80023EEC(Gap8002244CObj* obj, s32 a, s32 b);
void fn_80023F0C(void);
void gOz_GXSetTexture(void);
void fn_80024390(f32 m[3][4], Gap8002244CProjParams* out, s32 type);
void SetDisplayStateTexture(void);
void fn_800245EC(void);
void fn_800246D4(void);
void fn_800247E4(void);
void challengeStarRelatedInd(void);
void multBottomBits_asFloat(void);
void byteWiseMultiply(void);
void LERPToNewRange_Float(void);
f32 LinearInterpolateToNewRange(f32 x, f32 inMin, f32 inMax, f32 outMin, f32 outMax);
BOOL fn_80024C04(s32 index);
void fn_80024C6C(void);
typedef union Gap8002244CKey {
    u32 word;
    struct { u16 time, value; };
} Gap8002244CKey;
typedef struct Gap8002244CKeyTrack { u16 unk0, count; Gap8002244CKey* keys; } Gap8002244CKeyTrack;
typedef struct Gap8002244CKeyAnimation {
    f32 time;
    u8 _pad4[6];
    u16 trackIndex;
    u8 _padC[0xC];
    Gap8002244CKeyTrack tracks[1];
} Gap8002244CKeyAnimation;
u32 fn_80024D2C(Gap8002244CKeyAnimation* animation);
void fn_80024DB0(void);
void fn_80024FA4(void);
void fn_80025C58(void);

#endif // !__UNKNOWN_gap_8002244C_H_
