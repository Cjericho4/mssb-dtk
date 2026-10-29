#ifndef __UNKNOWN_gap_80025DDC_H_
#define __UNKNOWN_gap_80025DDC_H_

#include "mssbTypes.h"

void fn_80025DDC(void);
typedef struct ItemAnimationTrack {
    u16 count;
    u16 stride;
    u8 data[1];
} ItemAnimationTrack;
typedef struct ItemTrackDescriptor { u16 count; u16 stride; u8* data; } ItemTrackDescriptor;
typedef struct ItemPlaybackState {
    f32 frame;
    f32 rate;
    u16 playing;
    u16 cursor;
    u16 tick;
    s16 previous;
    u8 dirty;
    u8 active : 1;
    u8 repeat : 2;
    u8 mode : 2;
    u8 reserved : 3;
    u16 _pad12;
    void* callback;
    union {
        struct { u16 count; u16 stride; u8* data; };
        ItemTrackDescriptor track;
    };
    u8 _pad20[4];
} ItemPlaybackState;
typedef struct ItemAnimationSelector {
    void* model;
    ItemAnimationTrack** tracks;
    void* unknown8;
    ItemPlaybackState playback;
    s8* categories[6];
    u8 _pad48[0x10];
    s8 selected;
} ItemAnimationSelector;
void fn_80025EEC(ItemAnimationSelector* selector, s32 category, s32 animation);
void fn_80025FFC(void);
void fn_80026130(void);
void fn_80026134(void);
void fn_800263FC(void);
void fn_80026998(void);
void fn_80026E58(void);
void fn_80027300(void);
void fn_80027674(void);

#endif // !__UNKNOWN_gap_80025DDC_H_
