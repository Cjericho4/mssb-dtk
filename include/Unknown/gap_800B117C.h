#ifndef __UNKNOWN_gap_800B117C_H_
#define __UNKNOWN_gap_800B117C_H_

#include "mssbTypes.h"
#include "C3/anim.h"
#include "C3/unktypes.h"
#include "C3/actor.h"
typedef struct Gap800B117CRequest {
    u32 unk0;
    u16 type;
} Gap800B117CRequest;
typedef struct Gap800B117CVertex Gap800B117CVertex;
typedef struct Gap800B117CTexture {
    u8 _pad0[8];
    u16 width;
    u16 height;
} Gap800B117CTexture;
typedef struct Gap800B117CMasks {
    u8 _pad0[6];
    u16 mask6, mask8, maskA, maskC;
} Gap800B117CMasks;
extern Gap800B117CMasks lbl_801115A0;
extern s32 lbl_803CC1C8;
typedef struct Gap800B117CSkinData Gap800B117CSkinData;
typedef struct Gap800B117CSkinOutput Gap800B117CSkinOutput;
typedef struct Gap800B117CSkinHeader {
    Gap800B117CSkinData* data;
    u8 _pad4[2];
    u8 format;
} Gap800B117CSkinHeader;
/* Skinning/sort view of the actor and its bones (one struct for both; the animation functions use
 * GameActor / ActBone from gap_8002244C.h instead -- the two views still need reconciling). */
typedef struct Gap800B117CObj {
    u8 _pad0[3];
    /* 0x3 */ u8 priority;
    u8 _pad4[2];
    u16 count;
    u8 _pad8[8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ union { s32 unk14; Gap800B117CSkinHeader** skinHeaders; };
    /* 0x18 */ struct Gap800B117CObj** entries;
    u8 _pad1C[0x44];
    f32 (*matrices)[3][4]; /* 0x60 */
    u8 _pad64[0xC];
    DSList list; /* 0x70 */
    /* 0x7C */ union { s32 unk7C; Gap800B117CSkinOutput* skinOutput; };
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    u8 _pad86[0x2];
    /* 0x88 */ s32 unk88;
    f32 blend; /* 0x8C */
    /* 0x90 */ f32 unk90;
    u8 _pad94[5];
    u8 tickMode; /* 0x99 */
    u8 _pad9A[0x66];
    /* 0x100 */ struct Gap800B117CObj* next;
    u8 _pad104[0x30];
    /* 0x134 */ u16 unk134;
} Gap800B117CObj;
typedef struct Gap800B117CFlags {
    u8 _pad0[0x78];
    u32 renderMode;
    /* 0x7C */ u32 savedRenderMode;
    u8 _pad80[0xA];
    /* 0x8A */ u8 unk8A;
    u8 _pad8B[0x1];
    /* 0x8C */ u8 unk8C;
} Gap800B117CFlags;
extern Gap800B117CFlags* lbl_803CBB34;
typedef struct Gap800B117CFlagBanks {
    Gap800B117CFlags current[24];
    Gap800B117CFlags previous[24];
} Gap800B117CFlagBanks;
typedef struct Gap800B117CTextureSlot { u8 _pad0[0x1C]; } Gap800B117CTextureSlot;
typedef struct Gap800B117CCommandBuffer { u32 words[4]; } Gap800B117CCommandBuffer;
extern Gap800B117CFlagBanks lbl_802FEBF8;
extern Gap800B117CTextureSlot lbl_802FE918[];
extern Gap800B117CCommandBuffer* lbl_803CC1E4;
extern s32 lbl_803CC1D4;
extern Gap800B117CFlags* lbl_803CBB38;
extern Gap800B117CTextureSlot* lbl_803CBB40;
extern Gap800B117CCommandBuffer* lbl_803CC1C0;

void fn_800B117C(u8 value);
void fn_800B1188(void);
void DrawNullSprite(Gap800B117CVertex* vertices, s32 count);
void fn_800B12DC(Gap800B117CVertex* vertices, s32 count);
void fn_800B1314(Gap800B117CVertex* vertices, Gap800B117CTexture* texture, u32 height, u32 width);
void DrawSprite_TexObj(Gap800B117CVertex* vertices, Gap800B117CTexture* texture);
void fn_800B1388(Gap800B117CVertex* vertices);
void fn_800B13C0(void);
void fn_800B1468(void);
void DrawSprite(s32 primitive, Gap800B117CVertex* vertices, s32 count, Gap800B117CTexture* texture, u32 height, u32 width);
void fn_800B1EBC(void);
void fn_800B2160(u8 value);
BOOL fn_800B216C(u8 a, u32 b, u8 c);
void fn_800B21A8(s32 mode);
void fn_800B2240(void);
void fn_800B24D4(s32 index);
void fn_800B251C(void);
void fn_800B27A4(s32 index);
void fn_800B27DC(void);
void fn_800B2854(void);
typedef struct Gap800B117CDisplay Gap800B117CDisplay;
typedef struct Gap800B117CDisplayRef { Gap800B117CDisplay* display; u32 unk4; } Gap800B117CDisplayRef;
typedef struct Gap800B117CModel { u8 _pad0[0x10]; Gap800B117CDisplayRef* displays; } Gap800B117CModel;
typedef struct Gap800B117CDisplayRecord { u8 _pad0[0x14]; u16 index; u8 _pad16[4]; u16 flags; } Gap800B117CDisplayRecord;
typedef struct Gap800B117CDisplayAnimation {
    u8 _pad0[6]; u16 count;
    u8 _pad8[8]; Gap800B117CModel* model;
    u8 _pad14[0xC]; Gap800B117CDisplayRecord records[1];
} Gap800B117CDisplayAnimation;
typedef struct Gap800B117CSkinState { u8 _pad0[8]; s32 value; } Gap800B117CSkinState;
Gap800B117CSkinState* fn_800BF068(void);
void fn_800BC824(Gap800B117CDisplay* display, s32 value);
void fn_800B2AC8(Gap800B117CDisplayAnimation* animation);
void fn_800B2B4C(Gap800B117CObj* obj, f32 value);
void fn_800B2B54(Gap800B117CObj* obj, u16 index, u8 value);
void Set_FUN_800b2b6c(Gap800B117CObj* obj, s32 value);
void fn_800B2B74(Gap800B117CObj* obj, u16 index);
s32 fn_800B2BA8(Gap800B117CObj* obj, u16 index, Gap800B117CObj* other, u16 otherIndex);
void fn_800B2BE4(Gap800B117CObj* obj, u16 index);
void fn_800B2BFC(Gap800B117CObj* obj, s16 a, s16 b);
void fn_800B2C08(Gap800B117CObj* obj, s16 value);
void fn_800B2C10(Gap800B117CObj* obj, u16 index, Vec* vec);
void fn_800B2C44(Gap800B117CObj* obj, u16 index, Vec* vec);
void fn_800B2C88(Gap800B117CObj* obj, u16 index, f32 matrix[3][4]);
void GQRSetup5(u32 a, u32 b, u32 c, u32 d);
void SKNIt(Gap800B117CObj** entries, Gap800B117CSkinOutput* output, Gap800B117CSkinData* data);
void fn_800BF2A8(Gap800B117CObj** entries, Gap800B117CSkinOutput* output, Gap800B117CSkinData* data);
void fn_800B2D5C(Gap800B117CObj* obj);
void fn_800B2DD0(void);
void fn_800B313C(void);
void fn_800B34B4(void);
void f_BuildBoneSkinOrientationMatrix(void);
void fn_800B3A78(void);
void fn_800B3C04(void);
void fn_800B3F20(void);
BOOL fn_800B4048(u32* result, Gap800B117CRequest* request, u16 type);
void fn_800B4084(void);
void fn_800B4278(void);
u32 fn_800B43A0(Gap800B117CRequest* request);
void fn_800B4724(Gap800B117CObj* obj, s32 value);
void fn_800B472C(void);
void haveActLayoutPointToGeoHeader(Gap800B117CObj* obj, s32 value);
void LoadActorLayout(void);
void fn_800B49E4(void);
f32 fn_800B4A44(GameActor* actor, u16 index);
f32 fn_800B4A94(GameActor* actor);
void fn_800B4AFC(GameActor* actor, u8 loop);
void AnimateActorBones(GameActor* actor);
void fn_800B4BC8(GameActor* actor, u8 forward);
void fn_800B4C04(GameActor* actor, f32 speed);
f32 fn_800B4C40(GameActor* actor);
void fn_800B4CA0(GameActor* actor, f32 time);
void fn_800B4CDC(GameActor* actor);
void fn_800ACFB0(ANIMPipe* pipe);
s8 Strcmp(char* a, char* b);


#endif // !__UNKNOWN_gap_800B117C_H_
