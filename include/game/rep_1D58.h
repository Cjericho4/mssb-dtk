#ifndef __GAME_rep_1D58_H_
#define __GAME_rep_1D58_H_

#include "mssbTypes.h"
#include "C3/actor.h"
#include "Dolphin/stl.h"
#include "game/rep_D0.h"

typedef struct StadiumObject {
    /* 0x00 */ Control control;
} StadiumObject;

extern u8 lbl_3_data_11168[16];

typedef struct B98E8BoneInfo {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 _pad19[0x1C - 0x19];
} B98E8BoneInfo; // size: 0x1C

typedef struct C2310Bone {
    u8 _pad0[0x14];
    struct DODisplayObj* dispObj; /* 0x14 */
    u8 _pad18[0xE8 - 0x18];
    B98E8BoneInfo* info;          /* 0xE8 */
    MtxPtr worldMtx;              /* 0xEC */
    u8 _padF0[0x100 - 0xF0];
    struct C2310Bone* next;       /* 0x100 */
} C2310Bone;

typedef struct C2310Actor {
    u8 _pad0[0x6];
    u16 totalBones;                   /* 0x06 */
    u8 _pad8[0x14 - 0x8];
    struct DODisplayObj* skinObject;  /* 0x14 */
    C2310Bone** boneArray;            /* 0x18 */
    u8 _pad1C[0x64 - 0x1C];
    MtxPtr skinMtxArray;              /* 0x64 */
    MtxPtr skinInvTransposeMtxArray;  /* 0x68 */
    u8 _pad6C[0x74 - 0x6C];
    C2310Bone* drawList;              /* 0x74 */
    u8 _pad78[0x7C - 0x78];
    u32 unk7C;                        /* 0x7C */
} C2310Actor;

typedef struct C2310Holder {
    C2310Actor* actor; /* 0x00 */
} C2310Holder;

extern void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray,
                           u8 numLights, struct DOVaList* list);
extern void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m);
extern void fn_8003A8A0(struct DODisplayObj* dispObj, MtxPtr camera, s32 arg2);

void fn_3_B8184(C2310Holder* holder, MtxPtr camera);


s32 fn_3_B7FC8(s32 soundID, s32 arg1);
void fn_3_B80D0(void);
struct StadiumObject* fn_3_B827C(void);
void fn_3_B828C(struct StadiumObject*);
void fn_3_B8298(void);
void fn_3_B8414(f32* arg0, f32* arg1);
typedef struct StadiumPrimHdr {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 isStrip;
    /* 0x2 */ u16 count;
} StadiumPrimHdr;

typedef struct StadiumVtx {
    /* 0x0 */ Vec pos;
    /* 0xC */ u8 _padC[0x4];
} StadiumVtx; // size: 0x10

typedef struct StadiumModel {
    /* 0x0 */ u8 _pad0[0x8];
    /* 0x8 */ StadiumPrimHdr* prims;
} StadiumModel;

void fn_3_B8464(Mtx m, struct StadiumModel* model);
void fn_3_B8574(void);
u32 fn_3_B85A8(s32 index, u32* outPtr);
void fn_3_B85DC(s32 index, void* dest, void* src2, void* src);
s32 fn_3_B8658(f32*, f32*);
void fn_3_B867C(void);
void fn_3_B8828(void);
void fn_3_B8C08(void);
void fn_3_B902C(void);
void fn_3_B908C(void);
void fn_3_B9124(void);
void processStadiumObjectFunction(s32, s32 index, BALL_COLLISION_TYPE ret, CollisionStruct* outCollision);
struct StadiumModel* fn_3_B91C8(s32 stadium, s32 index, Mtx m);
void fn_3_B939C(void);
void fn_3_B93C4(void);
void fn_3_B93C8(s32);                                    /* extern */
void fn_3_B93CC(void);
void fn_3_B950C(void);
void fn_3_B9510(int);
void fn_3_B9524(void);
struct _GXTexObj;
u8* fn_3_B9534(s32 width, s32 height, struct _GXTexObj* texObj);
void fn_3_B95EC(void);
void fn_3_B97C8(struct StadiumObject*);
typedef struct ActorAnimState {
    GameActor* actor;    /* 0x00 */
    ANIMBank* bank;      /* 0x04 */
    u8 _pad08[0x6];
    u16 seqNum;          /* 0x0E */
    u8 _pad10[0x44];
    f32 speed;           /* 0x54 */
    u8 playAnim;         /* 0x58 */
    u8 setTime;          /* 0x59 */
    u8 setSpeed;         /* 0x5A */
    u8 loopFlags;        /* 0x5B */
    f32 time;            /* 0x5C */
    f32 startTime;       /* 0x60 */
    u8 _pad64[0x4];
    s32 unk68;           /* 0x68 */
} ActorAnimState;
typedef struct StadiumAnimEntry {
    ActorAnimState anim; /* 0x00 */
    u8 _pad6C[0x90 - 0x6C];
} StadiumAnimEntry; /* size: 0x90 */
typedef struct StadiumAnimTable {
    u8 _pad0[0x34];
    StadiumAnimEntry entries[1]; /* 0x34 */
} StadiumAnimTable;
void fn_3_B97DC(ActorAnimState* state, ANIMBank* bank);
/* Prototype conflict kept for the match: gap_800B117C.h declares the u8 arguments. */
void fn_800B4BC8(GameActor* actor, s32 arg1);
void fn_800B4C04(GameActor* actor, f32 speed);
void fn_800B4AFC(GameActor* actor, s32 loop);
void fn_800B4CA0(void* boneData, f32 val);
void fn_3_B98E8(C2310Holder* holder);
void fn_3_B99E4(void);
s32 fn_3_B9BB4(u32 idx);
void fn_3_B9D68(void);
void fn_3_B9FB8(void);

#endif // !__GAME_rep_1D58_H_
