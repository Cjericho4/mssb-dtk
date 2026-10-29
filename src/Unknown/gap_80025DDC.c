#include "Unknown/gap_80025DDC.h"

// .text:0x80025DDC size:0x110
void fn_80025DDC(void) {
    return;
}

// .text:0x80025EEC size:0x110
extern ItemTrackDescriptor lbl_803CB7F0;
static inline void resetItemPlayback(ItemPlaybackState* state) {
    if (state) {
        state->frame = 0.0f;
        state->rate = 0.5f;
        state->playing = 1;
        state->cursor = 0;
        state->tick = 0;
        state->previous = -1;
        state->dirty = 1;
        state->callback = NULL;
    }
}
static inline void repeatItemPlayback(ItemPlaybackState* state) {
    if (state) state->repeat = 3;
}
static inline void modeItemPlayback(ItemPlaybackState* state) {
    if (state) state->mode = 3;
}
static inline void selectItemTrack(ItemPlaybackState* state, ItemAnimationSelector* selector, s32 selected) {
    if (state->active = selected > -1) {
        ItemAnimationTrack* track = selector->tracks[selected];
        state->cursor = 0;
        state->count = track->count;
        state->stride = track->stride;
        state->data = track->data;
    } else {
        state->track = lbl_803CB7F0;
    }
}
void fn_80025EEC(ItemAnimationSelector* selector, s32 category, s32 animation) {
    s8 selected;
    ItemPlaybackState* state = &selector->playback;
    selected = selector->categories[category][animation];
    if (selector->selected != -128 && selected == selector->selected) return;
    selectItemTrack(state, selector, selected);
    resetItemPlayback(state);
    repeatItemPlayback(state);
    modeItemPlayback(state);
    selector->selected = selected;
}

// .text:0x80025FFC size:0x134
void fn_80025FFC(void) {
    return;
}

// .text:0x80026130 size:0x4
void fn_80026130(void) {
    return;
}

// .text:0x80026134 size:0x2C8
void fn_80026134(void) {
    return;
}

// .text:0x800263FC size:0x59C
void fn_800263FC(void) {
    return;
}

// .text:0x80026998 size:0x4C0
void fn_80026998(void) {
    return;
}

// .text:0x80026E58 size:0x4A8
void fn_80026E58(void) {
    return;
}

// .text:0x80027300 size:0x374
void fn_80027300(void) {
    return;
}

// .text:0x80027674 size:0x2A4
void fn_80027674(void) {
    return;
}
