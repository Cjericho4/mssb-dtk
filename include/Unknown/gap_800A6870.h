#ifndef __UNKNOWN_gap_800A6870_H_
#define __UNKNOWN_gap_800A6870_H_

#include "mssbTypes.h"
typedef struct Gap800A6870PoolNode { u32 next; } Gap800A6870PoolNode;
typedef struct Gap800A6870Pools {
    u8 _pad0[0x4C];
    u32* heads;
} Gap800A6870Pools;
extern Gap800A6870Pools lbl_803C7420;
extern u8 lbl_803CC134;
extern u8 lbl_803CC135;
extern s32 lbl_803CC12C;
extern s32 lbl_803CC13C;
typedef struct Gap800A6870Thread {
    u8 _pad0[0x318];
} Gap800A6870Thread;
typedef struct Gap800A6870Load {
    u8 _pad0[0x318];
    Gap800A6870Thread thread; /* 0x318 */
    u8 _pad630[0xA0];
    /* 0x6D0 */ s32 unk6D0;
    u8 _pad6D4[0x4];
    /* 0x6D8 */ u8 unk6D8;
} Gap800A6870Load;
extern Gap800A6870Load lbl_803C6CF8;
typedef struct Gap800A6870File {
    char* path; /* 0x0 */
} Gap800A6870File;
s32 DVDConvertPathToEntrynum(char* path);

extern s32 lbl_803CC140;
extern s32 lbl_803CC148;
extern s32 lbl_803CC154;

s32 fn_800A6870(u8 flag, s32 value);
void fn_800A6890(void);
void fn_800A68D4(void);
void fn_800A6900(void);
void fn_800A6C80(void);
void fn_800A6D10(void);
void fn_800A6E24(void);
void fn_800A6F94(void);
void ARAMTransfer(void);
void fn_800A750C(void);
s32 ConvertPathToEntryNum(Gap800A6870File* file);
void fn_800A7568(void);
void fn_800A75EC(void);
void fn_800A7670(void);
void fn_800A76BC(void);
void fn_800A77A0(void);
void fn_800A7A80(void);
void fn_800A7AD4(void);
void fn_800A7AD8(void);
void fn_800A7BAC(void);
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
void fn_800A8878(void);
s32 fn_800A88C0(void);
s32 fn_800A88C8(void);
s32 fn_800A88D0(void);
void fn_800A88D8(void);
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
void fn_800A9168(void);
void fn_800A91B0(void);
void fn_800A93AC(void);
void fn_800A9424(void);
void fn_800A94A8(u8 flag);
void fn_800A94C4(void);
void fn_800A9520(void);

s32 OSResumeThread(Gap800A6870Thread* thread);

#endif // !__UNKNOWN_gap_800A6870_H_
