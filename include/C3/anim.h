#ifndef _DOLPHIN_CP_ANIM_H_
#define _DOLPHIN_CP_ANIM_H_

#include "mssbTypes.h"

typedef struct Control Control;
typedef struct KeyFrame KeyFrame; /* C3/unktypes.h: time, setting, interpolation (0xC bytes) */

/* One bone's keyframe stream inside a sequence. Offsets in the bank file are relocated by ANIMGet. */
struct ANIMAnimTrack {
    /* 0x00 */ f32 animTime;             /* duration of the track (same units as key times) */
    /* 0x04 */ struct KeyFrame * keyFrames;
    /* 0x08 */ u16 totalFrames;          /* number of key records */
    /* 0x0A */ u16 trackID;              /* bone ID this track drives */
    /* 0x0C */ u8 quantizeInfo;          /* high nibble type, low nibble fixed-point shift */
    /* 0x0D */ u8 animType;              /* ANIM_TYPE_* bits */
    /* 0x0E */ u8 interpolationType;     /* packed per-channel modes: bits 1..0 trans, 3..2 scale, 6..4 rot */
    /* 0x0F */ u8 replaceHierarchyCtrl;
};
STATIC_ASSERT(sizeof(struct ANIMAnimTrack) == 0x10);

#define ANIM_TYPE_TRANS      (1 << 0) /* 0x01 */
#define ANIM_TYPE_SCALE      (1 << 1) /* 0x02 */
#define ANIM_TYPE_ROT_EULER  (1 << 2) /* 0x04 */
#define ANIM_TYPE_ROT_QUAT   (1 << 3) /* 0x08 */
#define ANIM_TYPE_MTX        (1 << 4) /* 0x10 */
#define ANIM_TYPE_SCALE_QUAT (1 << 5) /* 0x20 */

/* Playback state of one bone (the game's version is 0x1C bytes; f_InitBone carves them at a 0x20 stride). */
typedef struct ANIMPipe {
    /* 0x00 */ f32 time;
    /* 0x04 */ f32 previousTime;         /* time sampled by the last ANIMTick */
    /* 0x08 */ f32 speed;                /* time units added (or subtracted) per tick */
    /* 0x0C */ struct ANIMAnimTrack * currentTrack;
    /* 0x10 */ Control * control;        /* the bone's animationCtrl */
    /* 0x14 */ u16 keyIndex;             /* cached key index for ANIMGetKeyFrameFromTrack */
    /* 0x16 */ u8 replaceHierarchyCtrl;  /* copied from the track */
    /* 0x17 */ u8 forward;               /* 1 = time advances, 0 = time runs backwards */
    /* 0x18 */ u8 loop;                  /* 1 = wrap at the track duration, 0 = clamp */
    /* 0x19 */ u8 _pad19[3];
} ANIMPipe;
STATIC_ASSERT(sizeof(ANIMPipe) == 0x1C);

typedef struct ANIMSequences {
    /* 0x00 */ char *sequenceName;
    /* 0x04 */ struct ANIMAnimTrack *trackArray;
    /* 0x08 */ u16 totalTracks;
    /* 0x0A */ u16 pad16;
} ANIMSequences;
STATIC_ASSERT(sizeof(ANIMSequences) == 0xC);

typedef struct ANIMBank {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ ANIMSequences *animSequences;
    /* 0x08 */ u16 bankID;
    /* 0x0A */ u16 numSequences;
    /* 0x0C */ u16 numTracks;
    /* 0x0E */ u16 numKeyFrames;
    /* 0x10 */ u32 userDataSize;
    /* 0x14 */ void * userData;
} ANIMBank;
STATIC_ASSERT(sizeof(ANIMBank) == 0x18);

// animBank.c (gap_800B117C.c / gap_800B508C.c)
void ANIMGet(ANIMBank *animBank);
ANIMSequences *ANIMGetSequence(ANIMBank *animBank, char *sequenceName, u16 seqNum);
struct ANIMAnimTrack *ANIMGetTrackFromSequence(ANIMSequences *animSeq, u16 animTrackID);
void ANIMGetKeyFrameFromTrack(struct ANIMAnimTrack * animTrack, f32 time, KeyFrame **currentFrame, KeyFrame **nextFrame,
                              u16 *keyIndex);

// animPipe.c (gap_800B508C.c)
void ANIMBind(ANIMPipe *animPipe, Control *control, struct ANIMAnimTrack *animTrack, f32 time);
void ANIMTick(ANIMPipe * animPipe, u8 mode);

#endif // _DOLPHIN_CP_ANIM_H_
