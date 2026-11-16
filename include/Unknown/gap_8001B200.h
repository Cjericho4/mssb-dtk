#ifndef __UNKNOWN_gap_8001B200_H_
#define __UNKNOWN_gap_8001B200_H_

#include "mssbTypes.h"

void fn_8001B200(void);
void fn_8001B214(void);
void fn_8001B224(void);
void fn_8001B2D0(void);
void fn_8001B308(void);
void fn_8001B35C(void);
void fn_8001B4D8(void);
void fn_8001B5EC(void);
void fn_8001B728(void);
void getAnimRelatedCoordinates(void);
void QueueCharacterAnimation(void);
void AnimateCharacter(void);
void fn_8001BA44(s32 slot, s32 animation, s32 flags260, s32 flags263, s32 frames, s32 flags266, s32 flags26A);
void fn_8001BE50(s32 slot, s32 animation, s32 flags260, s32 flags263, s32 frames, s32 flags266, s32 flags26A);
void fn_8001C234(u32* changedSlots);
void fn_8001C528(void);
s32 fn_8001C588(s16 characterId);
void fn_8001C67C_animation(void);
s32 fn_8001C920(s32 charID);
typedef struct Gap8001B200LightSpec {
    u8 data[0xA];
} Gap8001B200LightSpec;
typedef struct Gap8001B200LightSet {
    /* 0x00 */ Gap8001B200LightSpec lights[4];
    u8 _pad28[4];
} Gap8001B200LightSet; /* 0x2C */
typedef struct Gap8001B200Light {
    /* 0x00 */ f32 x; /* direction; the first entry's is normalised and passed to fn_800BEBCC */
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    u8 _padC[4];
} Gap8001B200Light; /* 0x10 */
extern Gap8001B200LightSet lbl_800F7478[];
extern Gap8001B200Light lbl_80367318[4]; /* start of a larger block */
/* gap_8002244C.h declares this as a (void) stub; arguments from fn_8001CA40's loop. */
void fn_80023B90(Gap8001B200LightSpec* spec, Gap8001B200Light* light);
void fn_8001CA40(u8 lightSet);
void fn_8001CB10(Gap8001B200LightSpec* specs, s32 count);
void fn_8001CBD4(void);
void fn_8001CCC8(void);
void fn_8001CE74(void);
void fn_8001D074(void);
void fn_8001D0D0(void);
void fn_8001D110(s32 index, f32 x, f32 y, f32 z);
void fn_8001D148(s32 index, f32 x, f32 y, f32 z);
void fn_8001D180(s32 slotKind, s32 item, s32 attach);
void fn_8001D2D4(void);
void fn_8001DB74(void);
void fn_8001DD58(void);
void fn_8001DEA4(void);
void fn_8001E0D8(void);

#endif // !__UNKNOWN_gap_8001B200_H_
