#ifndef __UNKNOWN_gap_8000F8F4_H_
#define __UNKNOWN_gap_8000F8F4_H_

#include "mssbTypes.h"
typedef struct Gap8000F8F4Entry {
    u32 unk0;
    u32 data;
    u8 _pad8[0x10];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    s16 state; /* 0x28 */
    /* 0x2A */ u8 unk2A;
    u8 condition; /* 0x2B */
    u8 _pad2C[5];
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    u8 _pad33;
    u8 flags34, flags35;
    u8 _pad36[2];
} Gap8000F8F4Entry;
typedef struct Gap8000F8F4Table { u32 unk0; u32 values[256]; } Gap8000F8F4Table;
typedef struct Gap8000F8F4Object { u8 _pad0[0x54]; u32 flags; } Gap8000F8F4Object;
typedef struct Gap8000F8F4Slot { union { u32 value; Gap8000F8F4Object* object; }; u32 unk4; } Gap8000F8F4Slot;
typedef struct Gap8000F8F4Range { u8 _pad0[0x14]; u16 first, count; } Gap8000F8F4Range;
extern Gap8000F8F4Slot lbl_80371C30[];
typedef struct Gap8000F8F4State {
    union {
        Gap8000F8F4Entry entries[34];
        struct { u8 _pad0[0x690]; Gap8000F8F4Slot slots[30]; };
    };
    u8 _pad780[0x18];
    Gap8000F8F4Table* tables[8];
    u8 _pad7B8[0x7EC - 0x7B8];
    /* 0x7EC */ u32 unk7EC; /* text file words 1, 2, 5 and 6 (fn_80010FA0) */
    /* 0x7F0 */ u32 unk7F0;
    /* 0x7F4 */ u32 unk7F4;
    /* 0x7F8 */ u32 unk7F8;
    u8 _pad7FC[2];
    u8 flag7FE;
} Gap8000F8F4State;
extern Gap8000F8F4State lbl_80366B18;

extern s32 lbl_803CBC18;

void fn_8000F8F4(Gap8000F8F4Range* range);
void fn_8000F988(void);
void fn_8000FA9C(void);
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d);
void fn_8000FD9C(s32 index, s32 flag, s32 state);
void fn_8000FE08(s32 index, s32 table, s32 value);
void fn_8000FE54(void);
void fn_8000FEE8(s32 index);
void fn_8000FF04(void);
void fn_800100A4(void);
void DrawText(s32 index);
void DrawTextOnCondition(s32 condition);
extern u16 lbl_80366218[]; /* copy of the text file's first u16 list, without its 0x4001 end mark */
void fn_80010FA0(void);
void fn_80011000(void);
void fn_80011140(void);
typedef struct MenuPointerArchive {
    u16 count;
    u16 unk_0x2;
    u8* entries[1]; /* Variable-length table with count entries. */
} MenuPointerArchive;
void fn_800111B4(MenuPointerArchive* archive);
void fn_800111FC(void);
void fn_80011468(void);
s32 fn_80011570(void);
typedef struct Gap8000F8F4Mtx {
    f32 m[3][4];
} Gap8000F8F4Mtx;
extern Gap8000F8F4Mtx lbl_800E6630;
void PSMTXConcat(Gap8000F8F4Mtx* a, Gap8000F8F4Mtx* b, Gap8000F8F4Mtx* out);
void fn_80011640(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* dst);
void PSMTXCopy(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* dst);
void fn_800117CC(Gap8000F8F4Mtx* position, Gap8000F8F4Mtx* view, Gap8000F8F4Mtx* out);
extern Gap8000F8F4Mtx lbl_800E6600;
u32 PSMTXInverse(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* inv);
Gap8000F8F4Mtx* fn_800118AC(Gap8000F8F4Mtx* src, Gap8000F8F4Mtx* dst);

/* Local views of AnimLevel1, HugeAnimEntry68, AnimationStruct and hugeAnimStruct
   (UnknownHeaders.h); that header cannot be included here because this unit declares its own
   matrix types for the PSMTX functions. */
typedef struct Gap8000F8F4Bone {
    u8 _pad0[0x14];
    /* 0x14 */ u32 attachment; /* display object carried by the bone, 0 = none */
    u8 _pad18[0xEC - 0x18];
    /* 0xEC */ Gap8000F8F4Mtx* matrix;
} Gap8000F8F4Bone;
typedef struct Gap8000F8F4Model {
    u8 _pad0[6];
    /* 0x06 */ u16 totalBones;
    u8 _pad8[0x10];
    /* 0x18 */ Gap8000F8F4Bone** boneArray;
    u8 _pad1C[0x99 - 0x1C];
    /* 0x99 */ u8 unk99;
} Gap8000F8F4Model;
void fn_800116DC(Gap8000F8F4Model** model, Gap8000F8F4Mtx* view, u16 boneIndex);
typedef struct Gap8000F8F4Block {
    u8 _pad0[0x34];
    /* 0x34 */ Gap8000F8F4Model* model;
    u8 _pad38[0x90 - 0x38];
} Gap8000F8F4Block;
typedef struct Gap8000F8F4ActorSlot {
    u8 _pad0[0x5C];
    /* 0x5C */ void* callback; /* AnimationStruct.funcPtr_0x5c */
    u8 _pad60[2];
    /* 0x62 */ s16 animID;
    u8 _pad64[0x162 - 0x64];
    /* 0x162 */ u16 boneIndices[120]; /* bone id -> actor bone index, 0xFFFF = none */
    /* 0x252 */ s8 charID;
    u8 _pad253[2];
    /* 0x255 */ s8 blockIndex;
} Gap8000F8F4ActorSlot;
typedef struct Gap8000F8F4HugeAnim {
    u8 _pad0[0x60];
    /* 0x60 */ Gap8000F8F4Block* blocks;
    /* 0x64 */ Gap8000F8F4Block* blocks64; /* a second actor block; entries 21..24 hold the held-item models */
    u8 _pad68[0x2C50 - 0x68];
    /* 0x2C50 */ Gap8000F8F4ActorSlot* slots[13];
} Gap8000F8F4HugeAnim;
extern Gap8000F8F4HugeAnim g_hugeAnimStruct;
Gap8000F8F4Model** fn_800111D8(Gap8000F8F4ActorSlot* slot);
void fn_80011578(void);
void fn_800115C8(s8 id);
void fn_80011604(s8 id, void* callback);
s32 fn_800B2BA8(Gap8000F8F4Model* model, u16 boneIndex, Gap8000F8F4Model* other, u16 otherIndex);
void fn_80011358(s32 slotKind, s32 item);
/* Per-character slot updates called by fn_80011468 with the slot in r3 and its model pointer in r4; their owning headers
   (gap_80048BEC.h, gap_800506E8.h) still declare them as (void) stubs. */
void fn_8004B6EC(Gap8000F8F4ActorSlot* slot, Gap8000F8F4Model** model);
void fn_8004B7F4(Gap8000F8F4ActorSlot* slot, Gap8000F8F4Model** model);
void fn_8004BAEC(Gap8000F8F4ActorSlot* slot, Gap8000F8F4Model** model);
void fn_8005240C(Gap8000F8F4ActorSlot* slot, Gap8000F8F4Model** model);
#endif // !__UNKNOWN_gap_8000F8F4_H_
