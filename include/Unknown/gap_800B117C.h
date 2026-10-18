#ifndef __UNKNOWN_gap_800B117C_H_
#define __UNKNOWN_gap_800B117C_H_

#include "mssbTypes.h"
typedef struct Gap800B117CTrack {
    u8 _pad0[0xA];
    u16 id;
    u8 _padC[4];
} Gap800B117CTrack;
typedef struct Gap800B117CSequence {
    u32 unk0;
    Gap800B117CTrack* tracks;
    u16 count;
} Gap800B117CSequence;
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
typedef struct Gap800B117CVec { f32 x, y, z; } Gap800B117CVec;
typedef struct Gap800B117CList {
    u32 size;
    struct Gap800B117CObj* head;
    struct Gap800B117CObj* tail;
} Gap800B117CList;
typedef struct Gap800B117CDuration { f32 length; } Gap800B117CDuration;
typedef struct Gap800B117CAnimation {
    f32 time;
    u32 unk4;
    f32 speed;
    struct Gap800B117CDuration* duration; /* 0xC */
    u8 _pad10[7];
    u8 flags17;
    u8 flags18;
} Gap800B117CAnimation;
typedef struct Gap800B117CObj {
    u8 _pad0[6];
    u16 count;
    u8 _pad8[8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ struct Gap800B117CObj** entries;
    u8 _pad1C[0x44];
    f32 (*matrices)[3][4]; /* 0x60 */
    u8 _pad64[0xC];
    Gap800B117CList list; /* 0x70 */
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    u8 _pad86[0x2];
    /* 0x88 */ s32 unk88;
    u8 _pad8C[0x4];
    /* 0x90 */ f32 unk90;
    u8 _pad94[0x54];
    Gap800B117CAnimation* animation; /* 0xE8 */
    u8 _padEC[0x48];
    /* 0x134 */ u16 unk134;
} Gap800B117CObj;
typedef struct Gap800B117CFlags {
    u8 _pad0[0x78];
    u32 renderMode;
    u8 _pad7C[0xE];
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
void fn_800B21A8(void);
void fn_800B2240(void);
void fn_800B24D4(s32 index);
void fn_800B251C(void);
void fn_800B27A4(s32 index);
void fn_800B27DC(void);
void fn_800B2854(void);
void fn_800B2AC8(void);
void fn_800B2B4C(Gap800B117CObj* obj, f32 value);
void fn_800B2B54(Gap800B117CObj* obj, u16 index, u8 value);
void Set_FUN_800b2b6c(Gap800B117CObj* obj, s32 value);
void fn_800B2B74(Gap800B117CObj* obj, u16 index);
s32 fn_800B2BA8(Gap800B117CObj* obj, u16 index, Gap800B117CObj* other, u16 otherIndex);
void fn_800B2BE4(Gap800B117CObj* obj, u16 index);
void fn_800B2BFC(Gap800B117CObj* obj, s16 a, s16 b);
void fn_800B2C08(Gap800B117CObj* obj, s16 value);
void fn_800B2C10(Gap800B117CObj* obj, u16 index, Gap800B117CVec* vec);
void fn_800B2C44(Gap800B117CObj* obj, u16 index, Gap800B117CVec* vec);
void fn_800B2C88(Gap800B117CObj* obj, u16 index, f32 matrix[3][4]);
void ACTSort(void);
void fn_800B2D5C(void);
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
f32 fn_800B4A44(Gap800B117CObj* obj, u16 index);
f32 fn_800B4A94(Gap800B117CObj* obj);
void fn_800B4AFC(Gap800B117CObj* obj, u8 value);
void AnimateActorBones(void);
void fn_800B4BC8(Gap800B117CObj* obj, u8 value);
void fn_800B4C04(Gap800B117CObj* obj, f32 value);
f32 fn_800B4C40(Gap800B117CObj* obj);
void fn_800B4CA0(Gap800B117CObj* obj, f32 value);
void fn_800B4CDC(void);
void ACTSetAnimation(void);
void ANIMGetKeyFrameFromTrack(void);
Gap800B117CTrack* ANIMGetTrackFromSequence(Gap800B117CSequence* sequence, u16 id);
void ANIMGetSequence(void);

void DSInsertListObject(Gap800B117CList* list, Gap800B117CObj* tail, Gap800B117CObj* entry);
void PSMTXMultVec(f32 matrix[3][4], Gap800B117CVec* src, Gap800B117CVec* dst);
void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

#endif // !__UNKNOWN_gap_800B117C_H_
