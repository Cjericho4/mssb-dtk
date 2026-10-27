#ifndef __UNKNOWN_gap_800BD3A0_H_
#define __UNKNOWN_gap_800BD3A0_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
typedef struct Gap800BD3A0Color {
    u8 r, g, b, a;
} Gap800BD3A0Color;
typedef struct Gap800BD3A0Light {
    u8 _pad0[0x40];
    /* 0x40 */ f32 posX;
    /* 0x44 */ f32 posY;
    /* 0x48 */ f32 posZ;
    u8 _pad4C[0xC];
    /* 0x58 */ f32 dirX;
    /* 0x5C */ f32 dirY;
    /* 0x60 */ f32 dirZ;
    u8 _pad64[0xC];
    /* 0x70 */ Gap800BD3A0Color color;
    /* 0x74 */ u8 unk74;
    u8 _pad75[0x43];
    /* 0xB8 */ s32 unkB8;
    /* 0xBC */ s32 unkBC;
} Gap800BD3A0Light;
Gap800BD3A0Light* _OSAllocFromHeap(s32 heap, u32 size);
typedef struct Gap800BD3A0EntryData {
    u8 _pad0[0x70];
} Gap800BD3A0EntryData;
typedef struct Gap800BD3A0Actor {
    u8 _pad0[0x98];
    /* 0x98 */ u8 flags98;
} Gap800BD3A0Actor;
typedef struct Gap800BD3A0Model {
    /* 0x0 */ Gap800BD3A0Actor* actor;
    u8 _pad4[0x68];
    /* 0x6C */ u8 unk6C;
} Gap800BD3A0Model;
typedef struct Gap800BD3A0Transform {
    u8 _pad0[0x44];
} Gap800BD3A0Transform;
typedef struct Gap800BD3A0ActorObj {
    u8 _pad0[0x1C];
    /* 0x1C */ Gap800BD3A0Transform transform;
} Gap800BD3A0ActorObj;
typedef struct Gap800BD3A0Instance {
    /* 0x0 */ Gap800BD3A0ActorObj* obj;
    u8 _pad4[0xC];
    /* 0x10 */ Gap800BD3A0Transform transform;
    u8 _pad54[0x10];
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u16 unk66;
} Gap800BD3A0Instance;
void* memcpy(void* dest, const void* src, u32 size);
void fn_800B2BFC(Gap800BD3A0ActorObj* obj, u16 a, u16 b);
void AnimateActorBones(Gap800BD3A0ActorObj* obj);
void fn_800B3F20(Gap800BD3A0ActorObj* obj);
void fn_800B313C(Gap800BD3A0ActorObj* obj);
typedef void (*Gap800BD3A0Callback)(Gap800BD3A0Model* model, Gap800BD3A0EntryData* data);
typedef struct Gap800BD3A0Entry {
    u8 _pad0[0x40];
    /* 0x40 */ Gap800BD3A0EntryData data;
    /* 0xB0 */ u8 unkB0;
    u8 _padB1[0x2F];
} Gap800BD3A0Entry;
typedef struct Gap800BD3A0State {
    /* 0x0 */ u8 drawShadows;
    u8 _pad1[7];
    s32 unk_0x08;
    struct Gap800BD3A0Tlut* tlut; /* 0xC */
    u8 _pad10[0x4];
    /* 0x14 */ Gap800BD3A0Entry* entries;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ Gap800BD3A0Callback callback;
    /* 0x20 */ s32 unk20;
    u16 boundCount; /* 0x24 */
    u8 _pad26[2];
    f32 minX, maxX, minY, maxY, minZ, maxZ; /* 0x28 */
    f32 x, y, z; /* 0x40 */
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ s8 unk4D;
} Gap800BD3A0State;
extern Gap800BD3A0State lbl_803009F8;

void LITInitColor(Gap800BD3A0Light* light, Gap800BD3A0Color* color);
void LITInitDir(Gap800BD3A0Light* light, f32 x, f32 y, f32 z);
void LITInitPos(Gap800BD3A0Light* light, f32 x, f32 y, f32 z);
void LITInitAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void LITAlloc(Gap800BD3A0Light** out);
struct Gap800B993CObj;
void fn_800BC824(struct Gap800B993CObj* display, s32 value);
typedef struct GapBD478Object {
    u16 id; /* 0x00 */
    u8 _pad02[0x12];
    struct Gap800B993CObj* display; /* 0x14 */
} GapBD478Object;
typedef struct GapBD478List {
    u8 _pad00[6];
    u16 count; /* 0x06 */
    u8 _pad08[0x10];
    GapBD478Object** objects; /* 0x18 */
} GapBD478List;
typedef struct GapBD478Source {
    GapBD478List* list; /* 0x00 */
} GapBD478Source;
#define GAPBD478_INDEX_NONE 0xFFFF
#define GAPBD478_FLAGS_UNK_0x18 0x18 /* bits 3|4: record is processed; meaning unknown */
typedef struct GapBD478Record {
    u16 index; /* 0x00 */
    u16 objectId; /* 0x02 */
    u16 unk_0x04;
    u16 flags; /* 0x06 */
    u8 _pad08[0x14];
} GapBD478Record;
STATIC_ASSERT(sizeof(GapBD478Record) == 0x1C);
typedef struct GapBD478Table {
    u8 _pad00[6];
    u16 count; /* 0x06 */
    u8 _pad08[0x2C];
    GapBD478Record records[1]; /* 0x34 */
} GapBD478Table;
void fn_800BD478(GapBD478Source* source, GapBD478Table* table);
struct StadiumAnimEntry;
void fn_800BD548(struct StadiumAnimEntry* slots, u8 count, ...);
struct StadiumAnimTable;
void fn_800BD670(struct StadiumAnimTable* table, Mtx viewMtx);
/* gap_800B117C.h still declares this undecompiled callee as void(void). */
void fn_800B3A78(struct GameActor* actor, Mtx viewMtx, u8 lightCount, ...);
struct HugeAnimCtrlObj;
void fn_800BD8C4(struct HugeAnimCtrlObj* table, Mtx viewMtx);
/* Conflicting views: gap_800B117C.h declares these with Gap800B117CObj / (void) and sta_c6.c with StaC6Model; reconcile when the actor types merge. */
void Set_FUN_800b2b6c(struct GameActor* actor, s32 value);
u8 fn_800B3C04(s32 mode, struct GameActor* actor, Mtx viewMtx);
void fn_800BDA24(Gap800BD3A0Instance* inst);
void fn_800BDA94(void);
void fn_800BDC88(void);
struct HugeAnimEntry68* ActorObjectInitTable(u16 count);
void fn_800BDE8C(u8 value);
void fn_800BDEA0(void);
void fn_800BDF70(Gap800BD3A0Model* model);
void fn_800BDFE0(void);
void fn_800BE09C(void);
void fn_800BE158(void);
void fn_800BE498(void);
void fn_800BEA04(void);
void fn_800BEB3C(void);
u8* fn_800BEB80(u8 index);
u8 fn_800BEBA0(void);
u8 GetDrawShadows(void);
void DrawShadows(u8 enable);
void fn_800BEBCC(void);
void fn_800BEC00(BOOL enable);
void fn_800BEC30(void);
void fn_800BF008(void);
void fn_800BF038(s32 value);
void fn_800BF048(s32 value);
void fn_800BF058(Gap800BD3A0Callback value);
Gap800BD3A0State* fn_800BF068(void);
void SKNLoadFile(void);
void SKNFlushByIndex1(void);
void SKNFlushByIndex2(void);
void SKNBzero32B(void);
void SKNInit(void);
void fn_800BF2A8(void);
void SKNIt(void);
void SKN1Vecs16Norms16(void);
void fn_800BFF9C(void);
void SKN2Vecs16Norms16NoTouch(void);
void fn_800C02C8(void);
void SKNAccVecs16Norms16Iu161(void);
void SKNAccVecs16Norms16Iu162(void);
/* Namco texture archive (e.g. the texture section of a character .gpc). The 0x20-byte headers follow the
 * u16 count directly; convertTextureHeader turns the archive-relative offsets into pointers in place. */
typedef struct TextureHeader {
    /* 0x00 */ u32 dataOffset;      /* archive-relative, becomes a pointer */
    /* 0x04 */ u32 clutOffset;      /* archive-relative, becomes a pointer (0 = none) */
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 wrapS;
    /* 0x0D */ u8 wrapT;
    /* 0x0E */ u8 minFilt;
    /* 0x0F */ u8 magFilt;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 minLOD;
    /* 0x16 */ u8 maxLOD;
    /* 0x17 */ u8 format;
    /* 0x18 */ u16 tlutNumEntries;
    /* 0x1A */ u8 tlutFmt;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u16 texId;           /* set to the table index by convertTextureHeader */
    /* 0x1E */ u16 unk1E;
} TextureHeader; /* size 0x20 */

typedef struct TextureArchiveHeader {
    /* 0x00 */ u16 count;
    /* 0x02 */ u16 pad;
    /* 0x04 */ TextureHeader textures[1];
} TextureArchiveHeader;

void convertTextureHeader(TextureArchiveHeader* hdr);
void fn_800C07BC(void);

void GXInitLightAttn(Gap800BD3A0Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);

void GXLoadTlut(struct Gap800BD3A0Tlut* tlut, u32 slot);

#endif // !__UNKNOWN_gap_800BD3A0_H_
