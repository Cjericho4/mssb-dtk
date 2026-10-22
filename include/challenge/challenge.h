#ifndef __CHALLENGE_challenge_H_
#define __CHALLENGE_challenge_H_

#include "mssbTypes.h"
#include "UnknownHeaders.h"

typedef struct ChallengeScriptData ChallengeScriptData;
typedef struct ChallengeScriptEntry {
    u32 unk0;
    ChallengeScriptData* data;
    u8 _pad8[0x24];
} ChallengeScriptEntry;
typedef struct ChallengeScript {
    ChallengeScriptData* data;
    s32 count;
    s32 kind;
    s32 state;
    s32 timer;
    s32 enabled;
    ChallengeScriptEntry* entries;
} ChallengeScript;

typedef struct ChallengeAxes {
    u8 bytes[6];
} ChallengeAxes;

typedef struct ChallengeInput {
    /* 0x0 */ u16 buttons;
    /* 0x2 */ u16 held;
    /* 0x4 */ u16 pressed;
    /* 0x6 */ u8 _pad6[0xA];
    /* 0x10 */ ChallengeAxes axes;
} ChallengeInput;
extern ChallengeInput lbl_803C77B8;

/* Challenge scenes' view of a DrawingSceneStruct/QueueEntry: these scenes
   use the bytes after 0x14 as their own word/byte fields. */
typedef struct ChallengeScene {
    /* 0x00 */ void (*callback)(void);
    /* 0x04 */ u8 _pad4[8];
    /* 0x0C */ struct ChallengeScene* parent;
    /* 0x10 */ s16 loadingState;
    /* 0x12 */ u16 priority;
    union {
        struct {
        /* 0x14 */ union {
            s32 arg14;
            struct {
                s16 state14;
                s16 state16;
            };
        };
        /* 0x18 */ u8 byte18;
        /* 0x19 */ u8 byte19;
        /* 0x1A */ u8 _pad1A[0xE];
        /* 0x28 */ s32 mode28;
        };
        f32 parameters[6]; /* 0x14..0x28 */
        u32 words[6];
    };
    /* 0x2C */ union {
        u32 flags2C;
        f32 value2C;
    };
    /* 0x30 */ f32 value30;
    /* 0x34 */ u16 flags34;
    /* 0x36 */ u8 choice;
    /* 0x37 */ u8 cursor;
} ChallengeScene;

#endif // !__CHALLENGE_challenge_H_
