#ifndef __GAME_rep_1D58_H_
#define __GAME_rep_1D58_H_

#include "mssbTypes.h"
#include "C3/actor.h"
#include "C3/anim.h"
#include "Dolphin/stl.h"
#include "game/rep_D0.h"

typedef struct StadiumObject StadiumObject;

extern u8 lbl_3_data_11168[16];


void fn_3_B7FC8(s32 soundID, s32 arg1);
void fn_3_B80D0(void);
void fn_3_B8184(void);
struct StadiumObject* fn_3_B827C(void);
void fn_3_B828C(struct StadiumObject*);
void fn_3_B8298(void);
void fn_3_B8414(f32* arg0, f32* arg1);
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
BALL_COLLISION_TYPE processStadiumObjectFunction(s32, s32 index, BALL_COLLISION_TYPE ret, CollisionStruct* outCollision);
void fn_3_B91C8(void);
void fn_3_B939C(void);
void fn_3_B93C4(void);
void fn_3_B93C8(s32);                                    /* extern */
void fn_3_B93CC(void);
void fn_3_B950C(void);
void fn_3_B9510(int);
void fn_3_B9524(void);
void fn_3_B9534(void);
void fn_3_B95EC(void);
void fn_3_B97C8(struct StadiumObject*);
typedef struct ActorAnimState {
    Actor* actor;        /* 0x00 */
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
void fn_800B4BC8(Actor* actor, s32 arg1);
void fn_800B4C04(Actor* actor, f32 speed);
void fn_800B4AFC(Actor* actor, s32 loop);
void fn_800B4CA0(void* boneData, f32 val);
void fn_3_B98E8(void);
void fn_3_B99E4(void);
void fn_3_B9BB4(void);
void fn_3_B9D68(void);
void fn_3_B9FB8(void);

#endif // !__GAME_rep_1D58_H_
