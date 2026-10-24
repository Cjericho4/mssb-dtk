#ifndef __UNKNOWN_gap_8002244C_H_
#define __UNKNOWN_gap_8002244C_H_

#include "mssbTypes.h"

#include "Dolphin/mtx.h"
#include "Dolphin/os.h"
#include "charPipeline/structures/Tree.h"
#include "charPipeline/structures/List.h"
#include "C3/control.h"

/* Dolphin charPipeline actor data as this game lays it out (Ghidra: ActLayout / ACTActor). */
typedef struct ActPositionData {
    /* 0x00 */ u32 positionArray;
    /* 0x04 */ u16 numPositions;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
} ActPositionData;

typedef struct ActLightingData {
    /* 0x00 */ u32 normalArray;
} ActLightingData;

typedef struct ActDOLayout {
    /* 0x00 */ ActPositionData* positionData;
    /* 0x04 */ u32 colorData;
    /* 0x08 */ u32 textureData;
    /* 0x0C */ ActLightingData* lightingData;
    /* 0x10 */ u32 displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 pad8;
    /* 0x16 */ u16 pad16;
} ActDOLayout;

typedef struct ActDisplayObj {              /* DODisplayObj */
    /* 0x00 */ ActPositionData* positionData;
    /* 0x04 */ u32 colorData;
    /* 0x08 */ u32 textureData;
    /* 0x0C */ ActLightingData* lightingData;
    /* 0x10 */ u32 displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 pad8;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ s32 visibility;
    /* 0x1C */ Mtx worldMatrix;
    /* 0x4C */ u32 shaderFunc;
    /* 0x50 */ u32 shaderData;
    u8 _pad54[0x80 - 0x54];
} ActDisplayObj; /* the game reserves 0x80 for the skin object */

typedef struct ActGeoDescriptor {
    /* 0x00 */ ActDOLayout* layout;
    /* 0x04 */ char* name;
} ActGeoDescriptor;

typedef struct ActGeoPalette {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u32 userDataSize;
    /* 0x08 */ u32 userData;
    /* 0x0C */ u32 numDescriptors;
    /* 0x10 */ ActGeoDescriptor* descriptorArray;
} ActGeoPalette;

typedef struct ActBoneLayout ActBoneLayout;

typedef struct ActLayout {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ u32 hierarchyOffset;
    /* 0x0C */ ActBoneLayout* hierarchyRoot;
    /* 0x10 */ ActGeoPalette* geoPalettePtr;
    /* 0x14 */ u16 skinFileID;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u32 userDataSize;
    /* 0x1C */ u32 userData;
} ActLayout;

typedef struct ActBone ActBone;

typedef struct GameActor {                  /* ACTActor + game fields */
    /* 0x00 */ ActLayout* layout;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ ActGeoPalette* pal;
    /* 0x14 */ ActDisplayObj* skinObject;
    /* 0x18 */ ActBone** boneArray;
    /* 0x1C */ Control worldControl;        /* 0x3C bytes */
    u8 _pad58[8];                            /* game's Control is 0x44 here */
    /* 0x60 */ MtxPtr forwardMtxArray;
    /* 0x64 */ MtxPtr skinMtxArray;
    /* 0x68 */ MtxPtr orientationInvMtxArray;
    /* 0x6C */ MtxPtr skinInvTransposeMtxArray;
    /* 0x70 */ DSList drawPriorityList;
    /* 0x7C */ u32 skHeader;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ u16 unk84;
    /* 0x86 */ u16 pad86;
    /* 0x88 */ u32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u32 unk94;
    /* 0x98 */ u8 unk98;
    /* 0x99 */ u8 unk99;
    u8 _pad9A[0xA0 - 0x9A];
} GameActor; /* size 0xA0, bone pointer array follows */

typedef struct ActMemBlock { u8 bytes[0x20]; } ActMemBlock; /* 32-byte DMA-aligned allocation units */

extern char lbl_800E6698[];                 /* "Display object id %d is greater than number of objects %d" etc. */

typedef struct Gap8002244CLoad { u8 _pad0[0x715]; u8 complete; } Gap8002244CLoad;
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
    u8 header[0x18];
    union {
        u8 records[0x1B0];
        Gap8002244CRecord recs[18];
    };
    s8 flag1C8, flag1C9;
    /* 0x1CA */ u8 pending1CA;
    u8 _pad1CB;
    u32 current; /* 0x1CC */
    u32 pending; /* 0x1D0 */
    u8 _pad1D4[8];
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
void fn_8002254C(void);
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
void f_InitBone(ActBone* parent, ActBoneLayout* layout, GameActor* actor, u16* numBones, ActMemBlock* mtxMem, ActMemBlock* boneMem);
ActMemBlock* fn_80023078(ActDisplayObj* obj, ActDOLayout* layout, ActMemBlock* mem);
GameActor* f_InitActorWithLayout(ActLayout* layout, ActMemBlock* mem);
void BuildBoneSkinOrientationMatrix(ActBone* root, Mtx m);
void ACTSort(GameActor* actor);
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
Gap8002244CActor* _OSAllocFromHeap(s32 alignment, u32 size);
void ActorObjectInitTable(s32 count);
void fn_80023AA4(void);
void fn_80023B04(void);
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
