#ifndef __UNKNOWN_gap_800AD780_H_
#define __UNKNOWN_gap_800AD780_H_

#include "mssbTypes.h"
typedef struct Gap800AD780DrawContext { u32 words[5]; } Gap800AD780DrawContext;
typedef struct Gap800AD780QueueNode {
    union { u32 active; void (*withContext)(Gap800AD780DrawContext* context); };
    struct Gap800AD780QueueNode* previous;
    struct Gap800AD780QueueNode* next;
} Gap800AD780QueueNode;
extern Gap800AD780QueueNode* lbl_803CC1B8;
extern u16 lbl_803CC1B2;
typedef struct Gap800AD780Ring {
    u8 _pad0[0xC];
    u32 end;
    u32 cursor;
    u32 unk14;
    u32 size;
    u32 remaining;
    u32 consumed;
} Gap800AD780Ring;
extern Gap800AD780Ring lbl_803C7A00;
typedef struct Gap800AD780Movie {
    u8 _pad0[0x198];
    u64 elapsed;
    u64 startTime;
    u8 _pad1A8[0x11];
    u8 mode; /* 0x1B9 */
    u8 flags; /* 0x1BA */
} Gap800AD780Movie;
u64 OSGetTime(void);
typedef struct Gap800AD780MessageQueue Gap800AD780MessageQueue;
extern Gap800AD780MessageQueue lbl_802FB870;
extern u8 lbl_803CC17F;
extern u8 lbl_803CC17C;
BOOL OSSendMessage(Gap800AD780MessageQueue* queue, u32 message, s32 flags);
typedef struct Gap800AD780Hooks {
    u8* (*alloc)(u32 size);
    void (*free)(u8* memory);
} Gap800AD780Hooks;
void sndSetHooks(Gap800AD780Hooks* hooks);
void sndQuit(void);
typedef struct Gap800AD780DrawScript {
    union { void (*callback)(void); void (*withContext)(Gap800AD780DrawContext* context); };
    struct Gap800AD780DrawScript* previous;
    struct Gap800AD780DrawScript* next;
    u8 _padC[0x74];
} Gap800AD780DrawScript;
extern Gap800AD780DrawScript lbl_803C7A24[3];
typedef struct Gap800AD780DrawEntry {
    void (*callback)(void);
    u32 unk4;
    u32 unk8;
} Gap800AD780DrawEntry;
typedef struct Gap800AD780DrawLists {
    Gap800AD780DrawEntry current[24];
    Gap800AD780DrawEntry previous[24];
} Gap800AD780DrawLists;
extern Gap800AD780DrawLists lbl_80111340;
extern s32 lbl_803CBB30;
extern s32 lbl_803CC19C;
extern s32 lbl_803CC1D8[2];
typedef struct Gap800AD780State {
    u8 _pad0[0x28];
    /* 0x28 */ u8 unk28;
} Gap800AD780State;
extern Gap800AD780State lbl_803C79D4;
void fn_800A63C8(void);

extern u8 lbl_803CC17D;

void fn_800AD780(void);
void fn_800AD830(void);
void fn_800AD914(Gap800AD780Movie* movie);
void fn_800AD95C(Gap800AD780Movie* movie, u8 mode);
void fn_800AD9F4(void);
u8 fn_800ADAFC(void);
void fn_800ADB04(void);
void fn_800ADBFC(void);
void fn_800ADC40(void);
void fn_800ADD70(void);
void YUV2RGB(void);
void YUV2RGB_(void);
void fn_800AE5B8(void);
void fn_800AE8B8(void);
void MovStreamThread(void);
BOOL fn_800AED24(void);
void MovDecodeThread(void);
void fn_800AF1A8(void);
void fn_800AF5FC(void);
void fn_800AF9B4(void);
void fn_800AFBF0(void);
void fn_800AFC10(void);
void fn_800AFD4C(void);
u8 fn_800AFFB0(void);
void fn_800AFFC0(u32 count);
void fn_800B0008(void);
void fn_800B0134(void);
void fn_800B0230(void);
void fn_800B0390(void);
void fn_800B03F4(void);
void fn_800B0580(void);
void fn_800B05E4(void);
void makeLookAtMatrix(void);
void soundQuit(void);
void initSound(void);
void fn_800B0934(u8* memory);
void SndFree(void);
u8* SndAlloc(u32 size);
void fn_800B0A14_removeQueue(void);
void fn_800B0A5C_insertQueue(void);
void resetAllDrawingStructs_tonop(void);
void resetAllDrawingStructs(void);
void fn_800B0C80(void (*callback)(void));
void nop_function(void);
extern Gap800AD780QueueNode lbl_80111300;
extern u16 lbl_803CC1B0;
void RunDrawScripts_with_stack_variables(void);
void fn_800B0D28(s32 value);
void fn_800B0D38(s32 index, void (*callback)(void));
void AllocateSprite(void);

#endif // !__UNKNOWN_gap_800AD780_H_
