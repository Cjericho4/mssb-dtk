#ifndef __GAME_m_sound_H_
#define __GAME_m_sound_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

BOOL fn_3_8B258(u8 arg1, u8 cmd, u8 arg2);
void fn_3_8B2E4(void);
void fn_3_8B318(s32 arg0);
void fn_3_8B718(Vec* pos, Vec* vel, Vec* dir);
void fn_3_8B7DC(void);
void fn_3_8B804(void);
void fn_3_8B890(void);
/* Game-side 3D sound emitter slot (0x50 bytes in this MusyX build). */
typedef struct SoundEmitterSlot {
    u8 data[0x50];
} SoundEmitterSlot;

#define SOUND_EMITTER_COUNT 100

typedef struct CommonBss32B20 {
    u8 _pad0[0x8];
    u32 field_0x8;                                /* 0x8: listener room */
    u8 _padC[0x90 - 0xC];
    SoundEmitterSlot emitters[SOUND_EMITTER_COUNT]; /* 0x90 */
    u8 _pad1FD0[0x2034 - 0x1FD0];
    u8 emitterActive[SOUND_EMITTER_COUNT];        /* 0x2034 */
    u8 _pad2098[0x2138 - 0x2098];
} CommonBss32B20;

u32 sndCheckEmitter(SoundEmitterSlot* em);
u32 sndRemoveEmitter(SoundEmitterSlot* em);

typedef struct Data8D70 {
    u8 data[0xC];
} Data8D70;

extern CommonBss32B20 lbl_3_common_bss_32B20;
extern Data8D70 lbl_3_data_8D70;

void sndUpdateListener(CommonBss32B20* listener, VecXYZ* pos, VecXYZ* vel, VecXYZ* orient, Data8D70* data, u32 unk7F, u32 unk0);
void fn_3_8B964(VecXYZ* pos, VecXYZ* vel, VecXYZ* orient);
BOOL sndAddListener(CommonBss32B20* listener, VecXYZ* pos, VecXYZ* dir, VecXYZ* heading, Data8D70* up, f32 frontSur, f32 backSur, f32 sideSur, u32 flags, u8 vol, struct SND_ROOM* room);
void fn_3_8B9BC(VecXYZ* pos);
void fn_3_8BA60(void);
void fn_3_8BBC4(s32 soundID, VecXYZ* pos, s32 arg2, s32 arg3);
void fn_3_8BDF4(void);
void fn_3_8BE8C(void);
void fn_3_8C07C(void);
void fn_3_8C104(void);
void fn_3_8C2DC(void);
void fn_3_8C4F0(void);
void fn_3_8C5C8(void);
void fn_3_8CD74(void);
void fn_3_8D9C0(void);
void fn_3_8DA80(void);
void fn_3_8F1C8(void);
void fn_3_8F21C(void);
void fn_3_8FC0C(void);
void fn_3_8FC80(void);
void fn_3_8FF18(void);
u32 fn_3_8FF5C(s32 soundID, f32 x, f32 z);
void fn_3_90064(void);
void fn_3_90150(void);
void sndRemoveListener(void* listener);



void sndVolume(u8 volume, u16 time, u8 volGroup);
u32 fn_3_90220(s32 arg0, s32 arg1);
u32 playSoundEffect(int arg0);
void fn_3_902FC(void);
void fn_3_90328(s32 time);
void fn_3_903B8(void);
void fn_3_90434(void);
s32 fn_3_9056C(s32 songIndex);
void fn_3_90674(s32 songIndex);
void fn_3_906FC(void);

extern s32 lbl_3_bss_1780;
#endif // !__GAME_m_sound_H_
