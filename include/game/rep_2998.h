#ifndef __GAME_rep_2998_H_
#define __GAME_rep_2998_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct E22A4_Level6 {
    u8 _pad[0x04];
    u32 unk_04;
} E22A4_Level6;

typedef struct E22A4_Level5 {
    u8 _pad[0x04];
    E22A4_Level6 *unk_04;
} E22A4_Level5;

typedef struct E22A4_Level4 {
    u8 _pad[0x10];
    E22A4_Level5 *unk_10;
} E22A4_Level4;

typedef struct E22A4_Level3 {
    E22A4_Level4 *unk_00;
} E22A4_Level3;

typedef struct E22A4_Level2 {
    u8 _pad[0x10];
    E22A4_Level3 *unk_10;
} E22A4_Level2;

typedef struct E22A4_Level1 {
    u8 _pad[0x10];
    E22A4_Level2 *unk_10;
} E22A4_Level1;

typedef struct E22A4_Level0 {
    E22A4_Level1 *unk_00;
} E22A4_Level0;

typedef struct Arg_E22A4 {
    u8 _pad0[0x74];
    E22A4_Level0 *unk_74;     /* 0x74 */
    u8 _pad78[0xC4 - 0x78];
    u8 unk_C4;                /* 0xC4 */
    u8 unk_C5;                /* 0xC5 */
    u8 _padC6[0x02];
    u8 unk_C8;                /* 0xC8 */
} Arg_E22A4;

void fn_3_E1DB8(void);
void fn_3_E1FA8(UnknownStruct_EF3D4* obj);
struct CastleRotObj;
void fn_3_E2034(struct CastleRotObj* obj);
void fn_3_E2118(s32 idx);
void fn_3_E22A4(Arg_E22A4 *arg0);
void fn_3_E2324(void);
void fn_3_E25D0(castleThwompObj* arg, u32 idx);
void fn_3_E266C(void);
BOOL fn_3_E28DC(castleThwompObj* obj);
BOOL fn_3_E29B4(castleThwompObj* obj);
u8 fn_3_E2B70(struct CastleRotObj* obj);
void fn_3_E2E78(struct CastleRotObj* obj);
void fn_3_E2F4C(struct CastleRotObj* obj);
void fn_3_E3044(void);
u8 fn_3_E3284(struct CastleRotObj* obj);
void fn_3_E3668(struct CastleRotObj* obj);
void fn_3_E3764(struct CastleRotObj* obj);
void fn_3_E3914(void);
void fn_3_E3B88(void);
void fn_3_E4554(castleThwompObj *arg);
extern s32 lbl_3_bss_AE18[];
void fn_3_E45A8(castleThwompObj *param);
typedef struct {
    f32 rotValues[7]; /* 0x00: 7 floats per entry, stride 0x1C */
} RotTableEntry;

typedef struct {
    VecXYZ pos;      /* 0x00 */
    f32 rot;         /* 0x0C */
    u8 _pad10[0xC];
} CastleObjDef; /* size: 0x1C */

typedef union {
    CastleObjDef defs[1];
    struct {
        u8 _pad[0xC];
        RotTableEntry entries[1]; /* 0x0C: rotation table entries */
    };
} CastleRotData;

typedef struct CastleRotObj {
    Control control;     /* 0x00 */
    u8 _pad0[0x74 - 0x3C];
    struct ActorAnimState* anim; /* 0x74 */
    u8 _pad78[0x9C - 0x78];
    u8 rotIdx;           /* 0x9C */
    u8 _pad9D[3];
    VecXYZ pos;          /* 0xA0 */
    u8 _padAC[4];
    f32 curRotation;     /* 0xB0 */
    f32 scale;           /* 0xB4 */
    f32 animTime;        /* 0xB8 */
    u8 _padBC[0xC4 - 0xBC];
    u8 unkC4;            /* 0xC4 */
    u8 shrinkTimer;      /* 0xC5 */
    u8 shrinkFrames;     /* 0xC6 */
    u8 _padC7;
    u8 unkC8;            /* 0xC8 */
} CastleRotObj;

extern CastleRotData lbl_3_data_18ED0;
extern f32 lbl_3_rodata_2A5C;

void fn_3_E45F0(CastleRotObj *arg0);
void fn_3_E4658(CastleRotObj* obj);
void fn_3_E4760(void);
void fn_3_E48D0(void);
typedef struct E4A38PrimHdr {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u16 count;
} E4A38PrimHdr; /* size: 0x4 */

typedef struct E4A38Vtx {
    /* 0x0 */ Vec pos;
    /* 0xC */ f32 unkC;
} E4A38Vtx; /* size: 0x10 */

typedef struct E4A38Model {
    /* 0x0 */ u8 _pad0[0x8];
    /* 0x8 */ u8* data;
} E4A38Model;

extern u8 lbl_3_bss_AE01;

/* Overlay of the file-static bss block at lbl_3_bss_AE00 (ambient sound timers). */
typedef struct Rep2998Bss {
    u8 unk0;        /* 0x00 */
    u8 unk1;        /* 0x01 (lbl_3_bss_AE01) */
    u8 _pad2[2];
    s32 handle;     /* 0x04 */
    s32 timer8;     /* 0x08 */
    s32 timerC;     /* 0x0C */
    u8 active;      /* 0x10 */
} Rep2998Bss;
extern Rep2998Bss lbl_3_bss_AE00;
void fn_3_E4A38(MtxPtr mtx, E4A38Model* model);
struct StadiumModel* fn_3_E4BE8(s32 index, MtxPtr m);
void fn_3_E4CB0(s32* arg0, s32* arg1);
void fn_3_E4EF4(void);
void fn_3_E4FC4(void);

#endif // !__GAME_rep_2998_H_
