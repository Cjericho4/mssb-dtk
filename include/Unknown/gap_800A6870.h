#ifndef __UNKNOWN_gap_800A6870_H_
#define __UNKNOWN_gap_800A6870_H_

#include "mssbTypes.h"
void AISetStreamVolLeft(u8 volume);
void AISetStreamVolRight(u8 volume);
void AISetStreamTrigger(u32 trigger);
extern u32 lbl_803CC138;
struct Gap800A6870DVDFile;
extern struct Gap800A6870DVDFile lbl_802EF200;
BOOL DVDGetStreamPlayAddrAsync(struct Gap800A6870DVDFile* file, void (*callback)(void));
typedef union Gap800A6870PoolNode {
    u32 next;
    struct { u32 pointer : 30; u32 flags : 2; };
} Gap800A6870PoolNode;
typedef struct Gap800A6870SleepQueue { u32 head, tail; } Gap800A6870SleepQueue;
typedef struct Gap800A6870Pools {
    u8* framebuffer;
    u8 _pad4[0x48];
    u32* heads;
    u8 _pad50[0xC];
    Gap800A6870SleepQueue waiters; /* 0x5C */
    u8 _pad64[0x31C];
    Gap800A6870SleepQueue queue380; /* 0x380 */
    u8 _pad388[0xC];
    u8 period; /* 0x394 */
    u8 counter;
    u8 paused;
    /* 0x397 */ u8 unk397;
} Gap800A6870Pools;
extern Gap800A6870Pools lbl_803C7420;
extern volatile u8 lbl_803CC134;
extern volatile u8 lbl_803CC135;
extern s32 lbl_803CC12C;
extern s32 lbl_803CC13C;
typedef struct Gap800A6870Thread {
    u8 _pad0[0x318];
} Gap800A6870Thread;
typedef struct Gap800A6870Semaphore { u8 _pad0[0xC]; } Gap800A6870Semaphore;
typedef struct Gap800A6870DVDFile Gap800A6870DVDFile;
typedef struct Gap800A6870Load {
    u8 _pad0[0x318];
    Gap800A6870Thread thread; /* 0x318 */
    Gap800A6870Semaphore semaphore; /* 0x630 */
    u8 _pad63C[0x94];
    /* 0x6D0 */ s32 unk6D0;
    u8 _pad6D4[0x4];
    /* 0x6D8 */ u8 unk6D8;
    u8 _pad6D9[0x17];
    s32 running; /* 0x6F0 */
    s32 pending; /* 0x6F4 */
    u8 _pad6F8[4];
    u8* memory; /* 0x6FC */
    u8 _pad700[0x14];
    union {
        u16 stateWord; /* 0x714 */
        struct { u8 state; u8 stateLow; };
    };
    u8 _pad716[2];
    s32 entryNumber; /* 0x718 */
} Gap800A6870Load;
extern Gap800A6870Load lbl_803C6CF8;
typedef struct Gap800A6870File {
    char* path; /* 0x0 */
} Gap800A6870File;
s32 DVDConvertPathToEntrynum(char* path);

extern s32 lbl_803CC140;
extern volatile u32 lbl_803CC148;
typedef struct Gap800A6870Stream {
    struct Gap800A6870Stream* previous;
    struct Gap800A6870Stream* next;
    u32 flags;
    void (*callback)(u32 flags);
} Gap800A6870Stream;
extern Gap800A6870Stream* lbl_803CC154;

s32 fn_800A6870(u8 flag, s32 value);
void fn_800A6890(void);
void fn_800A68D4(void);
void fn_800A6900(void);
void fn_800A6C80(void);
void fn_800A6D10(void);
void fn_800A6E24(void);
void fn_800A6F94(void);
void ARAMTransfer(void);
BOOL fn_800A750C(s32 unused, Gap800A6870DVDFile* file);
s32 ConvertPathToEntryNum(Gap800A6870File* file);
void fn_800A7568(void);
void fn_800A75EC(void);
void fn_800A7670(void);
void fn_800A76BC(void);
void fn_800A77A0(void);
void fn_800A7A80(s32 result);
void fn_800A7AD4(void);
void fn_800A7AD8(void);
void fn_800A7BAC(u8 flag);
void fn_800A7C08(void);
void fn_800A7D4C(s32 index, Gap800A6870PoolNode* node);
void fn_800A7D7C(Gap800A6870PoolNode* nodes, u32 count);
void fn_800A7DB0(void);
void fn_800A7E00(void);
void fn_800A7F10(void);
void initRenderMode(void);
void fn_800A84C4(void);
void fn_800A8518(void);
void fn_800A86B4(void);
u16 fn_800A8864(void);
void fn_800A8878(u8 left, u8 right);
Gap800A6870Stream* fn_800A88C0(void);
s32 fn_800A88C8(void);
s32 fn_800A88D0(void);
void fn_800A88D8(u32 value);
void fn_800A8AB0(s32 value);
void fn_800A8AB8(void);
void fn_800A8B78(void);
void LoadFile(void);
void fn_800A8E30(void);
void fn_800A8F68(void);
void fn_800A8FDC(void);
void fn_800A9034(void);
void fn_800A908C(void);
void fn_800A90E4(void);
void fn_800A9168(u32 trigger);
void fn_800A91B0(void);
void fn_800A93AC(void);
void fn_800A9424(void);
void fn_800A94A8(u8 flag);
void fn_800A94C4(void);
void fn_800A9520(void);

s32 OSResumeThread(Gap800A6870Thread* thread);

s32 OSSignalSemaphore(Gap800A6870Semaphore* semaphore);
BOOL DVDFastOpen(s32 entryNumber, Gap800A6870DVDFile* file);

void fn_800ACF14(u8* memory);

void OSSleepThread(Gap800A6870SleepQueue* queue);
void GXSetColorUpdate(u8 enable);
void VIFlush(void);
void GXDrawDone(void);
void GXCopyDisp(u8* destination, u8 clear);

void OSWakeupThread(Gap800A6870SleepQueue* queue);
void PPCSync(void);
BOOL PADRecalibrate(u32 mask);
typedef struct Gap800A6870Pad {
    u8 _pad0[0x8];
    /* 0x8 */ s8 err;
    u8 _pad9[0x17];
} Gap800A6870Pad;
extern Gap800A6870Pad lbl_803C77B8[4];

void AISetStreamPlayState(u32 state);
BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL enabled);
extern volatile u32 lbl_803CC144;

#endif // !__UNKNOWN_gap_800A6870_H_
