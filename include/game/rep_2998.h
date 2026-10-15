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

void fn_3_E1FA8(UnknownStruct_EF3D4* obj);
struct CastleRotObj;
void fn_3_E2034(struct CastleRotObj* obj);
void fn_3_E2118(void);
void fn_3_E22A4(Arg_E22A4 *arg0);
void fn_3_E2324(void);
void fn_3_E25D0(castleThwompObj* arg, u32 idx);
void fn_3_E266C(void);
BOOL fn_3_E28DC(castleThwompObj* obj);
void fn_3_E29B4(void);
u8 fn_3_E2B70(struct CastleRotObj* obj);
void fn_3_E2E78(struct CastleRotObj* obj);
void fn_3_E2F4C(void);
void fn_3_E3044(void);
void fn_3_E3284(struct CastleRotObj* obj);
void fn_3_E3668(struct CastleRotObj* obj);
void fn_3_E3764(void);
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
    u8 _pad0[0x9C - 0x3C];
    u8 rotIdx;           /* 0x9C */
    u8 _pad9D[3];
    VecXYZ pos;          /* 0xA0 */
    u8 _padAC[4];
    f32 curRotation;     /* 0xB0 */
    f32 scale;           /* 0xB4 */
    u8 _padB8[0xC4 - 0xB8];
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
void fn_3_E4A38(void);
struct StadiumModel* fn_3_E4BE8(s32 index, MtxPtr m);
void fn_3_E4CB0(void);
void fn_3_E4EF4(void);
void fn_3_E4FC4(void);

#endif // !__GAME_rep_2998_H_
