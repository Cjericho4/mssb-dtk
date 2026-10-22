#ifndef __UNKNOWN_gap_800B993C_H_
#define __UNKNOWN_gap_800B993C_H_

#include "mssbTypes.h"
extern f32 (*lbl_803CC204)[3][4];
extern u16* lbl_803CC208;
extern s32 lbl_803CC21C;
extern f32 lbl_803CC218;
extern f32 lbl_803CC1F8;
extern f32 lbl_803CC1FC;
typedef union Gap800B993CColor {
    struct { u8 r, g, b, a; };
    u32 word;
} Gap800B993CColor;
extern u8 lbl_803CC220;
extern Gap800B993CColor lbl_803CC224;
typedef struct Gap800B993CObj {
    u8 _pad0[0x18];
    /* 0x18 */ f32 worldMatrix[3][4];
    u8 _pad48[0x8];
    /* 0x50 */ s32 unk50;
    u8 _pad54[0x18];
} Gap800B993CObj;

extern s32 lbl_803CC1F0;
extern s32 lbl_803CC1F4;
extern s32 lbl_803CC200;
extern s32 lbl_803CC20C;

void fn_800B993C(void);
void fn_800B9948(s32 value);
void fn_800B9950(u32 flags, f32 a, f32 b);
void fn_800B996C(s32 value);
void SetFogNone(void);
typedef struct Gap800B993CFog {
    u32 type;
    f32 start, end, nearZ, farZ;
    Gap800B993CColor color;
} Gap800B993CFog;
extern Gap800B993CFog lbl_80111700;
void SetFog(void);
void SetFogNoneAgain(void);
void fn_800B9A9C(s32 a, f32 b);
void fn_800B9AA8(s32 value);
void fn_800B9AB0(void);
void fn_800B9EA8(void);
void fn_800BA44C(void);
void Custom_SetState(void);
void SetState(void);
void GetColorFromQuant(void);
void DOVARender(Gap800B993CObj* obj, f32 matrix[3][4], u32 a, u32 b);
void DOVARenderSkin(Gap800B993CObj* obj, f32 matrix[3][4], f32 skinMatrices[][3][4], u16* indices, u32 a, u32 b);
void fn_800BC824(Gap800B993CObj* obj, s32 value);
void DOSetWorldMatrix(Gap800B993CObj* obj, f32 matrix[3][4]);
struct Gap800B993CPart;
struct Gap800B993CModel;
void InitDisplayObjWithLayout(Gap800B993CObj* obj, struct Gap800B993CPart* part);
void DOGet(Gap800B993CObj** out, struct Gap800B993CModel* model, u16 index);
Gap800B993CObj* _OSAllocFromHeap(s32 alignment, u32 size);
void OSReport(char* format, ...);
extern char lbl_800E7F8C[];
typedef struct Gap800B993CGeo Gap800B993CGeo;
typedef struct Gap800B993CSkin Gap800B993CSkin;

/* On-disc GEOPalette (Dolphin charPipeline layout) with file-relative offsets; LoadGeoPalette turns every
 * offset into a pointer in place.  Offsets are kept as u32 so the relocation is plain integer arithmetic. */
typedef struct GeoRelocArray {        /* PositionData / ColorData (LightingData adds a f32) */
    /* 0x00 */ u32 array;
    /* 0x04 */ u16 num;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
} GeoRelocArray;

typedef struct GeoTextureData {
    /* 0x00 */ u32 textureCoordArray;
    /* 0x04 */ u16 numTextureCoords;
    /* 0x06 */ u8 quantizeInfo;
    /* 0x07 */ u8 compCount;
    /* 0x08 */ u32 texturePaletteName;
    /* 0x0C */ u32 texturePalette;
} GeoTextureData; /* 0x10 */

typedef struct GeoDisplayStateList {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 pad8;
    /* 0x02 */ u16 pad16;
    /* 0x04 */ u32 setting;
    /* 0x08 */ u32 primitiveList;
    /* 0x0C */ u32 listSize;
} GeoDisplayStateList; /* 0x10 */

typedef struct GeoDisplayData {
    /* 0x00 */ u32 primitiveBank;
    /* 0x04 */ u32 displayStateList; /* GeoDisplayStateList[] */
    /* 0x08 */ u16 numStateEntries;
    /* 0x0A */ u16 pad16;
} GeoDisplayData;

typedef struct GeoLayout {             /* DODisplayLayout + one extra pointer */
    /* 0x00 */ u32 positionData;
    /* 0x04 */ u32 colorData;
    /* 0x08 */ u32 textureData;        /* GeoTextureData[numTextureChannels] */
    /* 0x0C */ u32 lightingData;
    /* 0x10 */ u32 displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 pad8;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u32 unk18;
} GeoLayout;

typedef struct GeoDescriptor {
    /* 0x00 */ u32 layout; /* GeoLayout* */
    /* 0x04 */ u32 name;   /* char* */
} GeoDescriptor;

typedef struct GeoPaletteHdr {
    /* 0x00 */ u32 versionNumber;      /* overwritten by the caller with LoadGeoPalette's result */
    /* 0x04 */ u32 userDataSize;
    /* 0x08 */ u32 userData;
    /* 0x0C */ u32 numDescriptors;
    /* 0x10 */ u32 descriptorArray;    /* GeoDescriptor[numDescriptors] */
} GeoPaletteHdr;

typedef struct Gap800B993CGeoFile {
    /* 0x00 */ Gap800B993CGeo* geo;
    u8 _pad4[0x10];
} Gap800B993CGeoFile;
Gap800B993CGeo* LoadGeoPalette(Gap800B993CGeoFile* file);
void SKNLoadFile(Gap800B993CSkin* skin, Gap800B993CGeo* geo);
void convertGeometryAndSknHeader(Gap800B993CGeoFile* file, Gap800B993CSkin* skin);
struct Gap800B993CModel;
void fn_800BCDBC(struct Gap800B993CModel* model);
void fn_800BCE38(void);
void fn_800BCEF8(void);
typedef struct Gap800B993CSubEntry {
    u8 _pad0[0xC];
    /* 0x0C */ u32 value;
} Gap800B993CSubEntry;
typedef struct Gap800B993CPart {
    u8 _pad0[0x8];
    /* 0x08 */ Gap800B993CSubEntry* entries;
    u8 _padC[0x8];
    /* 0x14 */ u8 count;
} Gap800B993CPart;
typedef struct Gap800B993CPartRef {
    /* 0x0 */ Gap800B993CPart* part;
    u8 _pad4[0x4];
} Gap800B993CPartRef;
typedef struct Gap800B993CModel {
    u8 _pad0[0xC];
    /* 0x0C */ u32 count;
    /* 0x10 */ Gap800B993CPartRef* parts;
} Gap800B993CModel;
typedef struct Gap800B993CAllocation Gap800B993CAllocation;
void fn_800ACFB0(Gap800B993CAllocation* allocation);
void fn_800BD190(Gap800B993CModel* model, u32 value);
void fn_800BD1E8(s32 value);
void __MTGQR5(void);
void __MTGQR6(void);
void __MTGQR7(void);
void GQRSetup7(void);
void GQRSetup6(void);
void GQRSetup5(void);
u8 fn_800BD2B0(Gap800B993CColor* out);
void fn_800BD2CC(u8 enable, Gap800B993CColor* color);
void fn_800BD2DC(void);
typedef struct Gap800B993CVec { f32 x, y, z; } Gap800B993CVec;
typedef struct Gap800B993CControl { u8 _pad0[0x44]; } Gap800B993CControl;
typedef struct Gap800B993CLight {
    u8 _pad0[0x40];
    Gap800B993CVec position, worldPosition, direction, worldDirection;
    u8 _pad70[4];
    Gap800B993CControl control;
    f32 (*parentMatrix)[4];
} Gap800B993CLight;
void CTRLBuildMatrix(Gap800B993CControl* control, f32 matrix[3][4]);
void PSMTXConcat(f32 a[3][4], f32 b[3][4], f32 out[3][4]);
void PSMTXMultVec(f32 matrix[3][4], Gap800B993CVec* src, Gap800B993CVec* dst);
u32 PSMTXInverse(f32 src[3][4], f32 dst[3][4]);
void PSMTXTranspose(f32 src[3][4], f32 dst[3][4]);
void LITXForm(Gap800B993CLight* light, f32 view[3][4]);

void PSMTXCopy(f32 src[3][4], f32 dst[3][4]);

void GXSetFog(u32 type, f32 start, f32 end, f32 nearZ, f32 farZ, Gap800B993CColor color);

#endif // !__UNKNOWN_gap_800B993C_H_
