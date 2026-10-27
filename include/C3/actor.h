#ifndef _DOLPHIN_CP_ACTOR_H_
#define _DOLPHIN_CP_ACTOR_H_

/* Dolphin charPipeline actor and bone records as this game lays them out (Ghidra: ActLayout,
 * ACTActor, ACTBone). Built by f_InitActorWithLayout / f_InitBone (gap_8002244C.c), animated by
 * ACTSetAnimation / ACTSetBoneTrack (gap_800B117C.c, gap_800B508C.c). */

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "charPipeline/structures/Tree.h"
#include "charPipeline/structures/List.h"
#include "C3/control.h"
#include "C3/anim.h"

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

typedef struct DODisplayObj {               /* DODisplayObj */
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

/* One bone record of the .gpc actor layout (0x1C bytes, contiguous after the ActLayout header).
 * Links are relocated to pointers by LoadActorLayout; NULL means no relation. */
typedef struct ActBoneLayout {
    /* 0x00 */ ControlExt* orientationCtrl;     /* rest pose (0x44 bytes), NULL = identity */
    /* 0x04 */ struct ActBoneLayout* prev;
    /* 0x08 */ struct ActBoneLayout* next;      /* next sibling */
    /* 0x0C */ struct ActBoneLayout* parent;
    /* 0x10 */ struct ActBoneLayout* children;  /* first child */
    /* 0x14 */ u16 geoFileID;                   /* geometry palette index, 0xFFFF = none */
    /* 0x16 */ u16 boneID;                      /* matched against ANIM track IDs */
    /* 0x18 */ u8 inheritanceFlag;
    /* 0x19 */ u8 drawingPriority;
    /* 0x1A */ u16 pad16;
} ActBoneLayout;
STATIC_ASSERT(sizeof(ActBoneLayout) == 0x1C);

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

/* Runtime bone (0x140 bytes; charPipeline ACTBone plus the game's blend control and flags).
 * Built by f_InitBone from an ActBoneLayout. */
typedef struct ActBone {
    /* 0x000 */ u16 boneID;
    /* 0x002 */ u8 inheritanceFlag;
    /* 0x003 */ u8 drawingPriority;
    /* 0x004 */ DSBranch branch;
    /* 0x014 */ ActDisplayObj* dispObj;
    /* 0x018 */ ActDisplayObj* unk18;           /* set to dispObj by f_InitBone */
    /* 0x01C */ ControlExt orientationCtrl;     /* rest pose copied from the layout */
    /* 0x060 */ ControlExt animationCtrl;       /* written by ANIMTick */
    /* 0x0A4 */ ControlExt blendFromCtrl;       /* pose at the last ACTSetBoneTrack, blended towards animationCtrl */
    /* 0x0E8 */ ANIMPipe* animPipe;
    /* 0x0EC */ MtxPtr forwardMtx;
    /* 0x0F0 */ MtxPtr skinMtx;
    /* 0x0F4 */ MtxPtr skinInvTransposeMtx;     /* inverse-transpose of skinMtx for normals; only with lighting data */
    /* 0x0F8 */ MtxPtr orientationInvMtx;       /* inverse bind pose (BuildBoneSkinOrientationMatrix) */
    /* 0x0FC */ DSLink drawPriorityLink;
    u8 _pad104[0x134 - 0x104];
    /* 0x134 */ u16 animFlags;                  /* 1 after init; ACTSetAnimation sets 0x20 when bits 0x1C are set */
    /* 0x136 */ u8 holdTranslation;             /* nonzero: translation keys are held, not interpolated */
    /* 0x137 */ u8 unk137;
    u8 _pad138[8];
} ActBone;
STATIC_ASSERT(sizeof(ActBone) == 0x140);

typedef struct GameActor {                  /* ACTActor + game fields */
    /* 0x00 */ ActLayout* layout;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ ActGeoPalette* pal;
    /* 0x14 */ ActDisplayObj* skinObject;
    /* 0x18 */ ActBone** boneArray;
    /* 0x1C */ ControlExt worldControl;
    /* 0x60 */ Mtx* forwardMtxArray;            /* one Mtx per bone, in boneArray order */
    /* 0x64 */ Mtx* skinMtxArray;
    /* 0x68 */ Mtx* skinInvTransposeMtxArray;   /* NULL without lighting data */
    /* 0x6C */ Mtx* orientationInvMtxArray;
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
STATIC_ASSERT(sizeof(GameActor) == 0xA0);

typedef struct ActMemBlock { u8 bytes[0x20]; } ActMemBlock; /* 32-byte DMA-aligned allocation units */

/* actorAnim (gap_800B117C.c): binds a bank sequence to every bone; blendStep 0 = snap, else the
 * blend weight grows by blendStep per AnimateActorBones tick. */
void ACTSetAnimation(GameActor* actor, ANIMBank* bank, char* sequenceName, u16 seqNum, f32 time, f32 blendStep);
void ACTSort(GameActor* actor);

#endif // _DOLPHIN_CP_ACTOR_H_
