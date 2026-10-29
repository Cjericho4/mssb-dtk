#include "challenge/rep_7BA0.h"
#include "stl/string.h"
typedef struct ChallengeMovie ChallengeMovie;
typedef struct ChallengeMovieName { u8 name[16]; } ChallengeMovieName;
typedef struct ChallengeMovieState {
    u32 bufferSize;
    void* buffer;
    void* frames;
    ChallengeMovie* movie;
} ChallengeMovieState;
extern ChallengeMovieState lbl_1_bss_47058;
extern ChallengeMovieName lbl_1_data_112D8[];
/* Movie owning headers retain stub signatures; these calls reveal their arguments. */
void* _OSAllocFromHeap(s32 heap, u32 size);
void fn_800ADC40(void* buffer, u32 size);
void fn_800ADB04(ChallengeMovieName* name, ChallengeMovie* movie, s32 mode, s32 flags);
s32 fn_800ADAFC(void);
u32 fn_800AD6BC(ChallengeMovie* movie);
void fn_800AD500(ChallengeMovie* movie, void* frames);
void fn_800AD95C(ChallengeMovie* movie, u8 mode);
void fn_800AD830(ChallengeMovie* movie);
s32 fn_800AD780(ChallengeMovie* movie);
void fn_800AD9F4(ChallengeMovie* movie);
void fn_800ADBFC(void);
void fn_800AD070(void);

// .text:0x000282F4 size:0x1B4
/* Allocate, load, play, and release the selected challenge movie. */
void fn_1_282F4(void) {
    ChallengeMovieState* state = &lbl_1_bss_47058;
    DrawingSceneStruct* scene = lbl_803CC1B8;
    switch (scene->flag14) {
    case 0:
        state->movie = _OSAllocFromHeap(32, 0x1C0);
        memset(state->movie, 0, 0x1C0);
        state->bufferSize = 0x400000;
        state->buffer = _OSAllocFromHeap(32, 0x400000);
        fn_800ADC40(state->buffer, state->bufferSize);
        scene->flag14++;
        break;
    case 1:
        fn_800ADB04(&lbl_1_data_112D8[scene->flag15], state->movie, 1, 0);
        scene->flag14++;
        /* fall through */
    case 2:
        if (fn_800ADAFC()) {
            u32 size = fn_800AD6BC(state->movie);
            state->frames = _OSAllocFromHeap(32, size);
            fn_800AD500(state->movie, state->frames);
            fn_800AD95C(state->movie, 1);
            scene->flag14++;
        }
        break;
    case 3:
        if (lbl_803C77B8.held & 0x200) {
            fn_800AD830(state->movie);
            scene->flag14++;
        }
        /* fall through */
    case 4:
        if (fn_800AD780(state->movie)) {
            fn_800AD9F4(state->movie);
            fn_800ADBFC();
            fn_800AD038(lbl_80366158.unk8);
            scene->flag14 = 0;
            lbl_803CC1B8->aFunctionPointer = fn_1_284A8;
        } else {
            fn_800AD070();
        }
        break;
    }
}

// .text:0x000284A8 size:0x84
void fn_1_284A8(void) {
    u16 pressed = lbl_803C77B8.pressed;
    DrawingSceneStruct* scene = lbl_803CC1B8;

    if (pressed & 3) {
        scene->flag15 ^= 1;
    } else if (pressed & 0x100) {
        scene->flag14 = 0;
        lbl_803CC1B8->aFunctionPointer = fn_1_282F4;
    } else if (pressed & 0x200) {
        scene->currentDrawingItem->loadingState = 1;
        fn_800B0A14_removeQueue();
    }
}

// .text:0x0002852C size:0x60
void fn_1_2852C(void) {
    DrawingSceneStruct* scene = lbl_803CC1B8;
    fn_800AD038(lbl_80366158.unk8);
    scene->flag14 = 0;
    scene->flag15 = 0;
    lbl_803CC1B8->aFunctionPointer = fn_1_284A8;
}
