#ifndef __UNKNOWN_gap_8001E460_H_
#define __UNKNOWN_gap_8001E460_H_

#include "mssbTypes.h"
void sndMasterVolume(u8 volume, u16 time, u8 music, u8 effects);
struct Gap8001E460Object;
struct Gap8001E460Resource;
extern s32 lbl_803CB7AC[2];
extern u8 lbl_803CBBC0;
extern u32 lbl_803CBC40;
typedef struct Gap8001E460Config {
    u8 _pad0[0x18];
    /* 0x18 */ s32 unk18;
} Gap8001E460Config;
extern Gap8001E460Config lbl_800EFBC0;
typedef struct Gap8001E460Flags {
    u8 _pad0[0x1E8];
    /* 0x1E8 */ u8 unk1E8;
    u8 _pad1E9[0x373];
    /* 0x55C */ s32 unk55C;
} Gap8001E460Flags;
extern Gap8001E460Flags lbl_803716B8;
typedef struct Gap8001E460Sound {
    u32 unk0;
    struct Gap8001E460Resource* resources[64]; /* 0x4 */
    u8 _pad104[0x28C];
    u8 groupCount; /* 0x390 */
    u8 _pad391[5];
    /* 0x396 */ u8 soundMode;
    u8 _pad397[0x1];
    /* 0x398 */ u8 unk398;
} Gap8001E460Sound;
extern Gap8001E460Sound lbl_800EF808;
typedef struct Gap8001E460Settings {
    u8 _pad0[0x23];
    /* 0x23 */ u8 unk23;
    /* 0x24 */ u8 unk24;
} Gap8001E460Settings;
extern Gap8001E460Settings lbl_800E8754;
void fn_800ACD44(void);

void fn_8001E460(s32 value);
void fn_8001E474(void);
void fn_8001E488(void);
void fn_8001E784(void);
void fn_8001F16C(void);
void fn_8001F228(void);
void challengeMapMaybe(void);
void fn_8001F5E8(void);
void fn_8001F8A4(void);
void fn_8001FC4C(void);
void fn_8001FDD4(struct Gap8001E460Object* obj);
void fn_8001FE00(void);
void calledWhenStartingMatch(void);
BOOL fn_80020218(void);
void fn_8002024C(void);
void fn_80020278(void);
void fn_80020388(void);
void fn_800203E0(void);
void changeScene(void);
void fn_8002059C(void);
void fn_80020624(void);
void fn_800206FC(void);
void fn_80021064(void);
s32 fn_80021188(void);
s32 fn_800211BC(void);
u8 fn_800211F0(void);
void fn_80021204(void);
void fn_80021228(void);
void fn_8002128C(void);
void fn_80021308(void);
void fn_800213F4(void);
void fn_800213F8(u32 size);
void fn_80021410(void);
void fn_8002149C(s32 index);
BOOL fn_800214D0(void);
void fn_80021518(void);
void fn_8002158C(void);
void fn_800215F8(void);
void fn_80021650(void);
void fn_800216F8(void);
void fn_80021758(void);
void fn_80021954(struct Gap8001E460Resource** resource);
void fn_80021980(void);
void f_initSound(void);
void fn_80021AA0(void);
void fn_80021AC0(void);
void fn_80021AC4(void);
void fn_80021AC8(void);
void fn_80021ADC(void);
void fn_80021BBC(void);
void fn_80021CA4(void);
void fn_8002204C(void);

typedef struct Gap8001E460Object {
    u8 _pad0[0x70];
    u32 fog; /* 0x70 */
} Gap8001E460Object;
void fn_800B9AA8(u32 value);
typedef struct Gap8001E460Resource {
    u8 _pad0[0x18];
    struct Gap8001E460Resource* end;
} Gap8001E460Resource;
typedef struct Gap8001E460ResourceState {
    Gap8001E460Resource* resource;
    u8 _pad4[0xC];
    u8 state; /* 0x10 */
    u8 _pad11[0xB];
} Gap8001E460ResourceState;
extern Gap8001E460ResourceState lbl_8037169C;
void fn_800ACF14(Gap8001E460Resource* resource);

void fn_800ACFB0(struct Gap8001E460Resource* resource);

void fn_800ACF78(Gap8001E460Resource* resource, u32 size);

u32 sndPopGroup(void);

#endif // !__UNKNOWN_gap_8001E460_H_
